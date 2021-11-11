//
//  dotkey95 - Dotkey95 is One-Time KEY calculater for Windows95/98/NT4.0
//
//  Copyright(C) 1996-1998 NEC Corporation
//	All rights reserved.
//  Author(s): Mizukoshi, Yasuhiro <mizukosi@ccs.mt.nec.co.jp>
//

//	    $Archive: /sotools/dotkey95/Dotkey95.c $
//			$Revision: 20 $
//			$Date: 98/10/22 6:49p $
static char VssID[] = "$Header: /sotools/dotkey95/Dotkey95.c 20    98/10/22 6:49p Mizukosi $";


#include    <windows.h>
#include	<process.h>
#include	<stdio.h>
#include	"resource.h"
#include	"dotkey95.h"
#include	<pbt.h>

static char ProgNameID[]  = DOTKEY95_NAME;
static char VersionID[]   = DOTKEY95_VERSION;
static char CopyRightID[] = DOTKEY95_COPYRIGHT " All rights reserved.";


HINSTANCE   hInst;
HWND		hWndNextChain = NULL;

BOOL		fEnableDotkey;				// This flag for toggle
BOOL		fEnableRepeat;				// for Repeat Mode

BOOL		fPostSAT;					// Post SHIFT+ALT+TAB (substitute for SetForegroundWindow)

Preference	pref;
PassCache	passcache[PASSCACHE_NUM];
int			PassCachePos = 0;

int  hash_func;
int  seq;								// Sequence Number
char seed[SEED_MAX_LEN];				// Seed
char pass[ONETIME_KEY_MAX_LEN];			// One-Time KEY

char FuncName[128];

int  (* KeyCrunchFunc)(char *, char *, char *);
void (* IterateFunc)  (char *);

BOOL CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK PassphraseDlgProc(HWND, UINT, WPARAM, LPARAM);
extern BOOL CALLBACK OptionDlgProc(HWND, UINT, WPARAM, LPARAM);
void PostSAT(void *notused);


/////////////////////////////////////////////////////////////
//	WinMain
//
int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		    LPSTR lpszCmdLine, int nCmdShow)
{
    MSG		msg;
    HWND	hWnd;
    
	FuncName[0] = 0;

    hInst = hInstance;

	hWnd = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DOTKEY95), NULL, MainWndProc);

    while (GetMessage(&msg, 0, 0, 0)) {
		if (!IsDialogMessage(hWnd, &msg)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
    }
    return msg.wParam;
}


////////////////////////////////////////////////////////////
//	Main Window (About Dialog) Procedure
//
BOOL CALLBACK MainWndProc(HWND hWnd, UINT uMessage,
				WPARAM wParam, LPARAM lParam)
{
    switch(uMessage) {
    case WM_INITDIALOG:
		SetDlgItemText(hWnd, IDC_PROGNAME,
#ifndef NOCACHE
					   DOTKEY95_NAME " " DOTKEY95_VERSION "\n" DOTKEY95_COPYRIGHT);
#else
					   DOTKEY95_NAME " " DOTKEY95_VERSION ".nc\n" DOTKEY95_COPYRIGHT);
#endif

		InitPrefs();
		LoadRegistory();
		TrayAdd(hWnd);
		hWndNextChain = SetClipboardViewer(hWnd);
		fEnableDotkey = TRUE;
		fEnableRepeat = FALSE;
	{
		OSVERSIONINFO	osVer;
		osVer.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		GetVersionEx(&osVer);
		if ((osVer.dwMajorVersion*100+osVer.dwMinorVersion) >= 410){
			fPostSAT = TRUE;
		} else {
			fPostSAT = FALSE;
		}
	}
		PostMessage(hWnd, WM_DOTKEY95TITLE, 0, 0);
		break;

	case WM_DOTKEY95TITLE:
		ShowWindow(hWnd, SW_SHOWDEFAULT);
		SetTimer(hWnd, IDT_DOTKEY95TITLE, 1500, NULL);
		break;

	case WM_TIMER:
		KillTimer(hWnd, wParam);
		if (wParam == IDT_DOTKEY95TITLE){
			PostMessage(hWnd, WM_COMMAND, IDOK, 0);
		}
		break;

	case WM_COMMAND:
		switch(wParam){
		case IDOK:						// OK Button on the About Dialog
			ShowWindow(hWnd, SW_MINIMIZE);
			ShowWindow(hWnd, SW_HIDE);
			break;
		default:
			break;
		}
		break;

	case WM_DRAWCLIPBOARD:
		if (fEnableDotkey){
			if (OpenClipboard(hWnd) == TRUE){
				HANDLE hClipMem;
				hClipMem = GetClipboardData(CF_TEXT);
				if (hClipMem != NULL){
					char * pClipMem = (char *) GlobalLock(hClipMem);
					if (FindSeq(pClipMem)){
						PostMessage(hWnd, WM_PASSPHRASE, 0, 0);
						fEnableDotkey = FALSE;
					}
					GlobalUnlock(hClipMem);
				}
				CloseClipboard();
			}
		}
		if (hWndNextChain)
			SendMessage(hWndNextChain, uMessage, wParam, lParam);
		return 0;

	case WM_CHANGECBCHAIN:
		if (hWndNextChain == (HWND)wParam)
			hWndNextChain = (HWND)lParam;
		if (hWndNextChain)
			SendMessage(hWndNextChain, uMessage, wParam, lParam);
		return 0;

	case WM_COPYDATA:
		// This I/F provides one-time key calculater to otpsock
	{
		int		res;
		COPYDATASTRUCT *pcds;
		HANDLE hClipMem;
		char * pClipMem;
		HWND	hFGWnd;

		res = FALSE;
		pcds = (COPYDATASTRUCT *)lParam;

		hFGWnd = GetForegroundWindow();

		if (fEnableDotkey && FindSeq(pcds->lpData)){

			// Display Passphrase Dialog
			res = DialogBox(hInst, 
							MAKEINTRESOURCE(fEnableRepeat ?
												IDD_PASSPHRASEREPEAT :
												IDD_PASSPHRASE),
							hWnd,
							PassphraseDlgProc);

			SetForegroundWindow(hFGWnd);
		}

		hClipMem = GlobalAlloc(GMEM_DDESHARE, strlen(pass)+1);
		pClipMem = (char *)GlobalLock(hClipMem);

		if (res){
			strcpy(pClipMem, pass);		// Success
		} else {
			pClipMem[0] = 0;			// Failure
		}

		GlobalUnlock(hClipMem);

		// copy one-time key to clipboard
		if (OpenClipboard(hWnd)){
			EmptyClipboard();
			SetClipboardData(CF_TEXT, hClipMem);
			CloseClipboard();
		}
	}
		return TRUE;

	case WM_PASSPHRASE:
	{
		HWND hFGWnd;
		int  res;

		hFGWnd = GetForegroundWindow();

		res = DialogBox(hInst,
						MAKEINTRESOURCE(fEnableRepeat ?
											IDD_PASSPHRASEREPEAT :
											IDD_PASSPHRASE),
						hWnd,
						PassphraseDlgProc);

		if (res){
			HANDLE hClipMem = GlobalAlloc(GMEM_DDESHARE, strlen(pass)+sizeof(CRLF)+1);
			char * pClipMem = (char *) GlobalLock(hClipMem);

			strcpy(pClipMem, pass);
			if (pref.bWithCRLF)
				strcat(pClipMem, CRLF);

			GlobalUnlock(hClipMem);

			if (OpenClipboard(hWnd)){
				EmptyClipboard();
				SetClipboardData(CF_TEXT, hClipMem);
				CloseClipboard();
			}
		}

		fEnableDotkey = TRUE;

		SetForegroundWindow(hFGWnd);

		if (res && pref.bAutoPaste){
			PasteEvent(hFGWnd);
		}

	}
		break;

	case WM_DOTKEY95NOTIFY:
		switch(lParam){
		case WM_RBUTTONDOWN:
			ContextMenu(hWnd);
			break;
		case WM_LBUTTONDOWN:
			fEnableDotkey = fEnableDotkey ? FALSE : TRUE;
			TrayModify(hWnd, fEnableDotkey);
			ShowWindow(hWnd, SW_MINIMIZE);
			ShowWindow(hWnd, SW_HIDE);
			break;
		default:
			break;
		}
		break;

	case WM_POWERBROADCAST:
		switch(wParam){
		case PBT_APMSUSPEND:
			if (pref.bClearOnSuspend)
				ClearPassCache();
			break;
		default:
			break;
		}
		return TRUE;

	case WM_DESTROY:
		ChangeClipboardChain(hWnd, hWndNextChain);
		TrayDelete(hWnd);
		PostQuitMessage(0);
		break;  

	default:
		break;
	}
	return 0L;
}


//////////////////////////////////////////////////////
//	Context Menu
//
int ContextMenu(HWND hWnd)
{
	HMENU hMenu;
	UINT  uMenuID;
	POINT pt;

	hMenu = CreatePopupMenu();

	AppendMenu(hMenu, MF_STRING, IDM_ABOUT,      "&About");
	AppendMenu(hMenu, MF_STRING | fEnableRepeat ? MF_CHECKED : 0,
								 IDM_REPEAT,	 "&Repeat Mode");

#ifndef NOCACHE
	AppendMenu(hMenu, MF_STRING, IDM_CLEARCACHE, "&Clear Cache");
#endif

	AppendMenu(hMenu, MF_STRING, IDM_OPTION,     "&Option");
	AppendMenu(hMenu, MF_STRING, IDM_EXIT,       "E&xit");

	SetForegroundWindow(hWnd);

	GetCursorPos(&pt);
	uMenuID = TrackPopupMenu(hMenu,
		TPM_BOTTOMALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON | TPM_RETURNCMD,
		pt.x, pt.y, 0, hWnd, NULL);

	DestroyMenu(hMenu);

	switch(uMenuID){
	case IDM_ABOUT:
		if (fPostSAT){
			ShowWindow(hWnd, SW_MINIMIZE);
			ShowWindow(hWnd, SW_HIDE);
		}
		ShowWindow(hWnd, SW_SHOWDEFAULT);
		break;

	case IDM_REPEAT:
		fEnableRepeat = fEnableRepeat ? FALSE : TRUE;
		if (fPostSAT){
			SetActiveWindow(hWnd);
			PostMessage(hWnd, WM_COMMAND, IDOK, 0);
		}
		break;

	case IDM_CLEARCACHE:
		ClearPassCache();
		MessageBeep(MB_OK);
		if (fPostSAT){
			SetActiveWindow(hWnd);
			PostMessage(hWnd, WM_COMMAND, IDOK, 0);
		}
		break;

	case IDM_OPTION:
#ifndef NOCACHE
		DialogBox(hInst, MAKEINTRESOURCE(IDD_OPTION), hWnd, OptionDlgProc);
#else
		DialogBox(hInst, MAKEINTRESOURCE(IDD_OPTION_NOCACHE), hWnd, OptionDlgProc);
#endif
		if (fPostSAT){
			SetActiveWindow(hWnd);
			PostMessage(hWnd, WM_COMMAND, IDOK, 0);
		}
		break;

	case IDM_EXIT:
		DestroyWindow(hWnd);
		break;
	}

	return 0;
}


////////////////////////////////////////////////////////////
//	Post SHIFT+ALT+TAB (for Windows98 or later)
//
void PostSAT(void *notused)
{
	if (!fPostSAT)
		return;

	Sleep(pref.iSleepAtCopy);

	keybd_event(VK_SHIFT, 0, 0, 0);
	keybd_event(VK_MENU,  0, 0, 0);
	keybd_event(VK_TAB,   0, 0, 0);
	keybd_event(VK_TAB,   0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU,  0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
}


//////////////////////////////////////////////////////////
//	Check Sequence Number
//		When sequence number is smaller than 30,
//		warning message is shown to users.
//
int CheckSeqNum(HWND hWnd)
{
	char szbuf[128];

	switch (seq){
	case 20: case 10: case  5: case  4:
	case  3: case  2: case  1: case  0:
		wsprintf(szbuf, "***** Warning!!  %d times to go. *****", seq);
		_beginthread(PostSAT, 4096, NULL);
		MessageBox(hWnd, szbuf, "dotkey95", MB_OK | MB_SYSTEMMODAL);
		return FALSE;
	default:
		break;
	}
	return TRUE;
}


////////////////////////////////////////////////////////////
//	Passphrase Input Dialog Procedure
//
BOOL CALLBACK PassphraseDlgProc(HWND hWnd, UINT uMessage,
				WPARAM wParam, LPARAM lParam)
{
    switch(uMessage) {
    case WM_INITDIALOG:
	{
		char Title[SEED_MAX_LEN + 10];
		POINT pt, spt;
		RECT  r;
		BOOL  bCSNDlg;

		if (!fPostSAT)
			SetForegroundWindow(hWnd);
		else
			SetWindowPos(hWnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOSIZE);

		bCSNDlg = CheckSeqNum(hWnd);

#ifndef NOCACHE
		if (pref.bPassCache && CheckPassCache()) {
			if (pref.bConfirmation){
				int i;
				if (bCSNDlg)
					_beginthread(PostSAT, 4096, NULL);
				i = MessageBox(hWnd, "Do you want to send your one-time password by passphrase cache ?", DOTKEY95_NAME, MB_YESNO | MB_SYSTEMMODAL);
				if (i == IDYES){
					EndDialog(hWnd, TRUE);
				} else {
					EndDialog(hWnd, FALSE);
				}
			} else {
				EndDialog(hWnd, TRUE);
			}
			break;
		}
#endif

		wsprintf(Title, "%d %s", seq, seed);
		SetWindowText(hWnd, Title);		

		SetWindowText(GetDlgItem(hWnd, IDC_FUNC), FuncName);

		GetCursorPos(&pt);
		GetWindowRect(hWnd, &r);
		spt.x = GetSystemMetrics(SM_CXSCREEN) - pt.x - (r.right - r.left) - 1;
		spt.y = GetSystemMetrics(SM_CYSCREEN) - pt.y - (r.bottom - r.top) - 1;
		if (spt.x < 0) pt.x += spt.x;
		if (spt.y < 0) pt.y += spt.y;

		MoveWindow(hWnd, pt.x + 1, pt.y + 1, r.right - r.left, r.bottom - r.top, TRUE);
		ShowWindow(hWnd, SW_SHOWNORMAL);

		if (bCSNDlg)
			_beginthread(PostSAT, 4096, NULL);
	}
		break;

	case WM_COMMAND:
		switch(wParam){
		case IDOK:
		{
			char passphrase[PASS_PHRASE_MAX_LEN];
			char key[8];
			int  i;

			GetDlgItemText(hWnd, IDC_PASS, passphrase, PASS_PHRASE_MAX_LEN);

			if (fEnableRepeat){
				char passphrase_repeat[PASS_PHRASE_MAX_LEN];
				int  n;

				GetDlgItemText(hWnd, IDC_PASS_REPEAT, passphrase_repeat, PASS_PHRASE_MAX_LEN);

				n = strcmp(passphrase, passphrase_repeat);
				memset(passphrase_repeat, 0, PASS_PHRASE_MAX_LEN);

				if (n){
					// Password Mismatch
					MessageBox(hWnd, "Mismatched.", "dotkey95", MB_OK | MB_ICONSTOP);
					memset(passphrase, 0, PASS_PHRASE_MAX_LEN);
					SetDlgItemText(hWnd, IDC_PASS, "");
					SetDlgItemText(hWnd, IDC_PASS_REPEAT, "");
					SetFocus(GetDlgItem(hWnd, IDC_PASS));
					break;
				}
			}

			if (KeyCrunchFunc(key, seed, passphrase) == -1){
				memset(passphrase, 0, PASS_PHRASE_MAX_LEN);
				EndDialog(hWnd, FALSE);
				break;
			}

			for (i = 0; i < seq; i++) IterateFunc(key);
			OTP_btoe(pass, key);

			if (pref.bPassCache){
				for (i = 0; i < PASSCACHE_NUM; i++){
					if (passcache[i].HashFunc == -1){
						SavePassCache(passphrase, -1);
						break;
					}

					if (passcache[i].HashFunc == hash_func &&
						passcache[i].Sequence >= seq       &&
						!strcmp(passcache[i].Seed, seed)){
						SavePassCache(passphrase, i);
						break;
					}
				}
			}

			memset(passphrase, 0, PASS_PHRASE_MAX_LEN);
			EndDialog(hWnd, TRUE);
		}
			break;

		case IDCANCEL:
			EndDialog(hWnd, FALSE);
			break;

		default:
			return FALSE;
		}
		break;

	default:
		return FALSE;
	}

	return TRUE;
}																	   	


////////////////////////////////////////////////////////////////
//	Find out a request string and get sequence number and seed.
//
int FindSeq(char *buffer)
{
	char *p;

	if ((p = ScanBuf(buffer, OTPMD4)) != NULL){
		hash_func = MD4;
	} else if ((p = ScanBuf(buffer, OTPMD5))     != NULL){
		hash_func = MD5;
	} else if ((p = ScanBuf(buffer, OTPSHA1))    != NULL){
		hash_func = SHA1;
	} else if ((p = ScanBuf(buffer, SKEY))       != NULL){
		hash_func = pref.bSKeyMD5 ? MD5 : MD4;
	} else if ((p = ScanBuf(buffer, BSDOS_SKEYMD4)) != NULL){
		hash_func = MD4;
	} else if ((p = ScanBuf(buffer, BSDOS_SKEYMD5)) != NULL){
		hash_func = MD5;
	} else {
		return FALSE;
	}

	SetFuncName();

	if (sscanf(p, SEQSEED_POS, &seq, seed) != 2)
		return FALSE;

	return TRUE;
}


///////////////////////////////////////////////////////////
//	Scan buffer got from clipboard
//
char * ScanBuf(char *p, char *key)
{
	char *s, *e;
	int  klen;

	klen = strlen(key);

	for (s = p, e = p + strlen(p) - klen; s < e; s++){
		if (!strncmp(s, key, klen))
			return (s + klen);
	}

	return NULL;
}


//////////////////////////////////////////////////////
//	Set hash functions and algorithm name
//
int SetFuncName()
{
	switch(hash_func){
	case MD4:
		KeyCrunchFunc = (void *)_otp_MD4_keycrunch;
		IterateFunc   = (void *)_otp_MD4_iterate;
		strcpy(FuncName, FUNCNAME_MD4);
		break;
	case MD5:
		KeyCrunchFunc = (void *)_otp_MD5_keycrunch;
		IterateFunc   = (void *)_otp_MD5_iterate;
		strcpy(FuncName, FUNCNAME_MD5);
		break;
	case SHA1:
		KeyCrunchFunc = (void *)_otp_SHA1_keycrunch;
		IterateFunc   = (void *)_otp_SHA1_iterate;
		strcpy(FuncName, FUNCNAME_SHA1);
		break;

	default:
		return FALSE;
	}

	return TRUE;
}


struct {
	char	*title;
	int		titletype;
	int		pastetype;
} applist[] = {
	"ftp",		TITLE_NAME,		DOS_PROMPT_PASTE,
	NULL,		0,				0
};


//////////////////////////////////////////////////////////
//	Get Paste Type
//
int GetPasteType(HWND hWnd)
{
	int  i;
	char AppTitle[32+1];

	GetWindowText(hWnd, AppTitle, 32);
	for (i = 0; applist[i].title != NULL; i++){
		if (applist[i].titletype == TITLE_NAME &&
			strlen(applist[i].title) == strlen(AppTitle) &&
			!stricmp(applist[i].title, AppTitle))
			return applist[i].pastetype;
	}

	GetClassName(hWnd, AppTitle, 32);
	for (i = 0; applist[i].title != NULL; i++){
		if (applist[i].titletype == CLASS_NAME &&
			strlen(applist[i].title) == strlen(AppTitle) &&
			!stricmp(applist[i].title, AppTitle))
			return applist[i].pastetype;
	}

	return KEY_STROKE_PASTE;
}

//////////////////////////////////////////////////////////
//	Make Keyboard Event for Auto Paste Mode
//
int PasteEvent(HWND hWnd)
{
	int  bCapsLock;
	char *p;

	switch(GetPasteType(hWnd)){
	case DOS_PROMPT_PASTE:
		keybd_event(VK_MENU,  0, 0, 0);
		keybd_event(VK_SPACE, 0, 0, 0);
		keybd_event(VK_SPACE, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_MENU,  0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_E,     0, 0, 0);
		keybd_event(VK_E,     0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_P,     0, 0, 0);
		keybd_event(VK_P,     0, KEYEVENTF_KEYUP, 0);
		break;

	case KEY_STROKE_PASTE:
	default:
		bCapsLock = GetKeyState(VK_CAPITAL);

		if (!bCapsLock)
			keybd_event(VK_SHIFT,  0, 0, 0);

		for (p = pass; p && *p; p++){
			keybd_event(*p, 0, 0, 0);
			keybd_event(*p, 0, KEYEVENTF_KEYUP, 0);
		}

		if (!bCapsLock)
			keybd_event(VK_SHIFT,  0, KEYEVENTF_KEYUP, 0);

		if (pref.bWithCRLF){
			keybd_event(VK_RETURN, 0, 0, 0);
			keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
		}
		break;
	}

	return TRUE;
}


/////////////////////////////////////////////////////
//	Save Password Cache
//
int SavePassCache(char *passphrase, int pos)
{
	if (pos != -1){
		passcache[pos].HashFunc = hash_func;
		passcache[pos].Sequence = seq;
		strcpy(passcache[pos].Seed, seed);
		strcpy(passcache[pos].Passphrase, passphrase);
		RotatePassphrase(passcache[pos].Passphrase);
	} else {
		passcache[PassCachePos].HashFunc = hash_func;
		passcache[PassCachePos].Sequence = seq;
		strcpy(passcache[PassCachePos].Seed, seed);
		strcpy(passcache[PassCachePos].Passphrase, passphrase);
		RotatePassphrase(passcache[PassCachePos].Passphrase);

		PassCachePos++;
		if (PassCachePos >= PASSCACHE_NUM)
			PassCachePos = 0;
	}

	return TRUE;
}


//////////////////////////////////////////////////////
//
//
BOOL CheckPassCache()
{
	int i, j;

	for (i = 0; i < PASSCACHE_NUM; i++){
		if (passcache[i].HashFunc == -1)
			return FALSE;

		if (passcache[i].HashFunc == hash_func &&
			passcache[i].Sequence >  seq       &&
			!strcmp(passcache[i].Seed, seed)){
				char key[8];
				char passphrase[PASS_PHRASE_MAX_LEN];

				memcpy(passphrase, passcache[i].Passphrase, PASS_PHRASE_MAX_LEN);

				RotatePassphrase(passphrase);

				if (KeyCrunchFunc(key, seed, passphrase) == -1){
					memset(passphrase, 0, PASS_PHRASE_MAX_LEN);
					return FALSE;
				}
				for (j = 0; j < seq; j++) IterateFunc(key);
				OTP_btoe(pass, key);

				SavePassCache(passphrase, i);

				memset(passphrase, 0, PASS_PHRASE_MAX_LEN);

				return TRUE;
		}
	}
	return FALSE;
}


////////////////////////////////////////////////////////
//
//
int RotatePassphrase(char *passphrase)
{
	int i;

	for (i = 0; i < PASS_PHRASE_MAX_LEN; i++)
		passphrase[i] ^= pref.cRotateKey;

	return TRUE;
}


////////////////////////////////////////////////////////
//
//
int ClearPassCache()
{
	int i;
	for (i = 0; i < PASSCACHE_NUM; i++){
		passcache[i].HashFunc = -1;
		memset(passcache[i].Passphrase, 0, PASS_PHRASE_MAX_LEN);
	}
	PassCachePos = 0;

	return TRUE;
}			
