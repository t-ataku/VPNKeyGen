//
//  dotkey95 - Dotkey95 is One-Time KEY calculater for Windows95/98/NT4.0
//
//  Copyright(C) 1996-1998 NEC Corporation
//	All rights reserved.
//  Author(s): Mizukoshi, Yasuhiro <mizukosi@ccs.mt.nec.co.jp>
//

//	    $Archive: /sotools/dotkey95/PREFS.C $
//			$Revision: 16 $
//			$Date: 98/10/22 6:49p $
static char VssID[] = "$Header: /sotools/dotkey95/PREFS.C 16    98/10/22 6:49p Mizukosi $";


#ifdef WINDOWS
#include	<windows.h>
#endif
#include	"resource.h"
#include	"dotkey95.h"

extern Preference	pref;
extern PassCache	passcache[PASSCACHE_NUM];
extern int			PassCachePos;

//
//	Initialize Preferences
//
int InitPrefs()
{
	int i;

	pref.bWithCRLF       = TRUE;
	pref.bAutoPaste      = TRUE;
	pref.bPassCache      = FALSE;
	pref.bConfirmation   = TRUE;
	pref.bSKeyMD5        = FALSE;
	pref.bClearOnSuspend = TRUE;
	pref.cRotateKey      = (char)GetTickCount();
	pref.iSleepAtCopy    = DEFAULT_SLEEP_AT_COPY;

	for (i = 0; i < PASSCACHE_NUM; i++)
		passcache[i].HashFunc = -1;

	return TRUE;
}


//
//
//
BOOL LoadRegistory()
{
	HKEY  hKey;
	DWORD dwType;
	DWORD dwLength;
	DWORD dwData;

	if (RegOpenKeyEx(HKEY_CURRENT_USER, DOTKEY95_SUBKEY, 0, KEY_QUERY_VALUE, &hKey) != ERROR_SUCCESS){
		return FALSE;
	}

	dwType   = REG_DWORD;
	dwLength = sizeof(dwData);
	if (RegQueryValueEx(hKey, WITHCRLF_VALNAME, NULL, &dwType, (LPBYTE)&dwData, &dwLength) == ERROR_SUCCESS)
		pref.bWithCRLF = (BOOL)dwData;

	dwType   = REG_DWORD;
	dwLength = sizeof(dwData);
	if (RegQueryValueEx(hKey, AUTOPASTE_VALNAME, NULL, &dwType, (LPBYTE)&dwData, &dwLength) == ERROR_SUCCESS)
		pref.bAutoPaste = (BOOL)dwData;

#ifndef NOCACHE
	dwType   = REG_DWORD;
	dwLength = sizeof(dwData);
	if (RegQueryValueEx(hKey, PASSCACHE_VALNAME, NULL, &dwType, (LPBYTE)&dwData, &dwLength) == ERROR_SUCCESS)
		pref.bPassCache = (BOOL)dwData;

	dwType   = REG_DWORD;
	dwLength = sizeof(dwData);
	if (RegQueryValueEx(hKey, CONFIRMATION_VALNAME, NULL, &dwType, (LPBYTE)&dwData, &dwLength) == ERROR_SUCCESS)
		pref.bConfirmation = (BOOL)dwData;
#endif

	dwType   = REG_DWORD;
	dwLength = sizeof(dwData);
	if (RegQueryValueEx(hKey, SKEY_MD5_VALNAME, NULL, &dwType, (LPBYTE)&dwData, &dwLength) == ERROR_SUCCESS)
		pref.bSKeyMD5 = (BOOL)dwData;

	dwType   = REG_DWORD;
	dwLength = sizeof(dwData);
	if (RegQueryValueEx(hKey, CLEARCACHE_VALNAME, NULL, &dwType, (LPBYTE)&dwData, &dwLength) == ERROR_SUCCESS)
		pref.bClearOnSuspend = (BOOL)dwData;

	dwType   = REG_DWORD;
	dwLength = sizeof(dwData);
	if (RegQueryValueEx(hKey, SLEEPATCOPY_VALNAME, NULL, &dwType, (LPBYTE)&dwData, &dwLength) == ERROR_SUCCESS)
		pref.iSleepAtCopy = (DWORD)dwData;

	RegCloseKey(hKey);

	return TRUE;
}

//
//
//
BOOL SaveRegistory()
{
	HKEY  hKey;
	DWORD dwType;
	DWORD dwLength;
	DWORD dwData;

	if (RegCreateKeyEx(HKEY_CURRENT_USER, DOTKEY95_SUBKEY, 0, "", REG_OPTION_NON_VOLATILE,
						KEY_WRITE, NULL, &hKey, &dwType) != ERROR_SUCCESS){
		return FALSE;
	}

	dwType   = REG_DWORD;
	dwLength = sizeof(dwData);
	dwData   = (DWORD)pref.bWithCRLF;
	RegSetValueEx(hKey, WITHCRLF_VALNAME, 0, dwType, (LPBYTE)&dwData, dwLength);

	dwType   = REG_DWORD;
	dwLength = sizeof(dwData);
	dwData   = (DWORD)pref.bAutoPaste;
	RegSetValueEx(hKey, AUTOPASTE_VALNAME, 0, dwType, (LPBYTE)&dwData, dwLength);

#ifndef NOCACHE
	dwType   = REG_DWORD;
	dwLength = sizeof(dwData);
	dwData   = (DWORD)pref.bPassCache;
	RegSetValueEx(hKey, PASSCACHE_VALNAME, 0, dwType, (LPBYTE)&dwData, dwLength);

	dwType   = REG_DWORD;
	dwLength = sizeof(dwData);
	dwData   = (DWORD)pref.bConfirmation;
	RegSetValueEx(hKey, CONFIRMATION_VALNAME, 0, dwType, (LPBYTE)&dwData, dwLength);
#endif

	dwType   = REG_DWORD;
	dwLength = sizeof(dwData);
	dwData   = (DWORD)pref.bSKeyMD5;
	RegSetValueEx(hKey, SKEY_MD5_VALNAME, 0, dwType, (LPBYTE)&dwData, dwLength);

	dwType   = REG_DWORD;
	dwLength = sizeof(dwData);
	dwData   = (DWORD)pref.bClearOnSuspend;
	RegSetValueEx(hKey, CLEARCACHE_VALNAME, 0, dwType, (LPBYTE)&dwData, dwLength);

	dwType   = REG_DWORD;
	dwLength = sizeof(dwData);
	dwData   = (DWORD)pref.iSleepAtCopy;
	RegSetValueEx(hKey, SLEEPATCOPY_VALNAME, 0, dwType, (LPBYTE)&dwData, dwLength);

	RegCloseKey(hKey);

	return TRUE;
}


//
//
//
BOOL CALLBACK OptionDlgProc(HWND hDlg, UINT uMessage,
			    WPARAM wParam, LPARAM lParam)
{
    switch(uMessage) {
    case WM_INITDIALOG:
		CheckDlgButton(hDlg, IDC_CRLF,       pref.bWithCRLF);
		CheckDlgButton(hDlg, IDC_AUTOPASTE,  pref.bAutoPaste);
		CheckDlgButton(hDlg, IDC_SKEY_MD5,   pref.bSKeyMD5);

#ifndef NOCACHE
		CheckDlgButton(hDlg, IDC_PASSCACHE,  pref.bPassCache);
		CheckDlgButton(hDlg, IDC_CONFIRMATION,  pref.bConfirmation);
		EnableWindow(GetDlgItem(hDlg,IDC_CONFIRMATION),pref.bPassCache);
		CheckDlgButton(hDlg, IDC_CLEARCACHE,  pref.bClearOnSuspend);
		EnableWindow(GetDlgItem(hDlg,IDC_CLEARCACHE),pref.bPassCache);
#endif
		break;

    case WM_COMMAND:
		switch(wParam) {
		case IDOK:
			pref.bWithCRLF       = IsDlgButtonChecked(hDlg, IDC_CRLF);
			pref.bAutoPaste      = IsDlgButtonChecked(hDlg, IDC_AUTOPASTE);
			pref.bSKeyMD5        = IsDlgButtonChecked(hDlg, IDC_SKEY_MD5);

#ifndef NOCACHE
			pref.bPassCache      = IsDlgButtonChecked(hDlg, IDC_PASSCACHE);
			pref.bConfirmation   = IsDlgButtonChecked(hDlg, IDC_CONFIRMATION);
			pref.bClearOnSuspend = IsDlgButtonChecked(hDlg, IDC_CLEARCACHE);
#endif
			SaveRegistory();

			EndDialog(hDlg, TRUE);
			break;

		case IDCANCEL:
			EndDialog(hDlg, FALSE);
			break;

		default:
#ifndef NOCACHE
			if (LOWORD(wParam) == IDC_PASSCACHE &&
				HIWORD(wParam) == BN_CLICKED){
				EnableWindow(GetDlgItem(hDlg,IDC_CONFIRMATION),
							 IsDlgButtonChecked(hDlg, IDC_PASSCACHE));
				EnableWindow(GetDlgItem(hDlg,IDC_CLEARCACHE),
							 IsDlgButtonChecked(hDlg, IDC_PASSCACHE));
			}
#endif
			return FALSE;
	    }
	    break;

	default:
	    return FALSE;
	}
	return TRUE;
}
