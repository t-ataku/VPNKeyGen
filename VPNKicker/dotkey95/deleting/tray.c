//
//  dotkey95 - Dotkey95 is One-Time KEY calculater for Windows95/98/NT4.0
//
//  Copyright(C) 1996-1998 NEC Corporation
//	All rights reserved.
//  Author(s): Mizukoshi, Yasuhiro <mizukosi@ccs.mt.nec.co.jp>
//

//	    $Archive: /sotools/dotkey95/TRAY.C $
//			$Revision: 7 $
//			$Date: 98/10/22 6:49p $
static char VssID[] = "$Header: /sotools/dotkey95/TRAY.C 7     98/10/22 6:49p Mizukosi $";


#include	<windows.h>
#include	"resource.h"
#include	"dotkey95.h"

extern HINSTANCE	hInst;


//
//	Add dotkey ICON to the Task Tray
//
int TrayAdd(HWND hWnd)
{
	BOOL			res;
	NOTIFYICONDATA	nid;
	HICON			hIcon;

	hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_DOTKEY95));

	nid.cbSize				= sizeof(NOTIFYICONDATA);
	nid.hWnd				= hWnd;
	nid.uID					= IDT_DOTKEY95;
	nid.uFlags				= NIF_MESSAGE | NIF_ICON | NIF_TIP;
	nid.uCallbackMessage	= WM_DOTKEY95NOTIFY;
	nid.hIcon				= hIcon;
	lstrcpyn(nid.szTip, DOTKEY95_NAME, sizeof(nid.szTip));

	res = Shell_NotifyIcon(NIM_ADD, &nid);

	DestroyIcon(hIcon);

	return res;
}


//
//	Delete dotkey ICON from the Task Tray
//
int TrayDelete(HWND hWnd)
{
	NOTIFYICONDATA	nid;

	nid.cbSize				= sizeof(NOTIFYICONDATA);
	nid.hWnd				= hWnd;
	nid.uID					= IDT_DOTKEY95;

	return Shell_NotifyIcon(NIM_DELETE, &nid);
}


//
//	Change dotkey ICON
//
int TrayModify(HWND hWnd, BOOL flag)
{
	BOOL			res;
	NOTIFYICONDATA	nid;
	HICON			hIcon;

	if (flag){
		hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_DOTKEY95));
	} else {
		hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_DISABLE));
	}

	nid.cbSize				= sizeof(NOTIFYICONDATA);
	nid.hWnd				= hWnd;
	nid.uID					= IDT_DOTKEY95;
	nid.uFlags				= NIF_MESSAGE | NIF_ICON | NIF_TIP;
	nid.uCallbackMessage	= WM_DOTKEY95NOTIFY;
	nid.hIcon				= hIcon;
	lstrcpyn(nid.szTip, DOTKEY95_NAME, sizeof(nid.szTip));

	res = Shell_NotifyIcon(NIM_MODIFY, &nid);

	DestroyIcon(hIcon);

	return res;
}
