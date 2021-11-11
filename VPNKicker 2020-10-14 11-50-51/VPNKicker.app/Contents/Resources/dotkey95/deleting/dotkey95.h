//
//  dotkey95 - Dotkey95 is One-Time KEY calculater for Windows95/98/NT4.0
//
//  Copyright(C) 1996-1998 NEC Corporation
//	All rights reserved.
//  Author(s): Mizukoshi, Yasuhiro <mizukosi@ccs.mt.nec.co.jp>
//

//	    $Archive: /sotools/dotkey95/Dotkey95.h $
//			$Revision: 18 $
//			$Date: 98/10/22 6:49p $


#ifdef WINDOWS
#include	<windows.h>
#endif
#include	"resource.h"


/////////////////////////////////////////////////////////
//
//	Program Title
//
#define		DOTKEY95_NAME		"dotkey95"
#define		DOTKEY95_VERSION	"Ver.0.8.0"
#define		DOTKEY95_COPYRIGHT	"Copyright (C) 1996-1998 NEC Corporation"


/////////////////////////////////////////////////////////
//
//	Messages
//
#define		WM_DOTKEY95NOTIFY	(WM_APP+100)
#define		WM_PASSPHRASE		(WM_APP+101)
#define		WM_DOTKEY95TITLE	(WM_APP+102)

#define		IDT_DOTKEY95TITLE	200

/////////////////////////////////////////////////////////
//
//	Task Tray
//
#define		IDT_DOTKEY95		100

int TrayAdd(HWND hWnd);
int TrayDelete(HWND hWnd);
int TrayModify(HWND hWnd, BOOL flag);


/////////////////////////////////////////////////////////
//
//	Context Menu
//
#define		IDM_ABOUT			100
#define		IDM_OPTION			101
#define		IDM_EXIT			102
#define		IDM_CLEARCACHE		103
#define		IDM_REPEAT			104

int ContextMenu(HWND hWnd);


/////////////////////////////////////////////////////////
//
//	Hash Function
//
#define		PASS_PHRASE_MIN_LEN	8
#define		PASS_PHRASE_MAX_LEN	256
#define		SEED_MAX_LEN		1024
#define		ONETIME_KEY_MAX_LEN	256


/////////////////////////////////////////////////////////
//
//	Keyword of OTP Systems
//
//	RFC 1938
#define		OTPMD4				"otp-md4"
#define		OTPMD5				"otp-md5"
#define		OTPSHA1				"otp-sha1"
//	RFC 1760
#define		SKEY				"s/key"
//	BSD/OS 
#define		BSDOS_SKEYMD4		"S/Key MD4"
#define		BSDOS_SKEYMD5		"S/Key MD5"



#define		SEQSEED_POS			" %d %s"

#define		FUNCNAME_MD2		"md2"
#define		FUNCNAME_MD4		"md4"
#define		FUNCNAME_MD5		"md5"
#define		FUNCNAME_SHA1		"sha1"

#define		MD2					0
#define		MD4					1
#define		MD5					2
#define		SHA1				3

int FindSeq(char *buffer);
char *ScanBuf(char *p, char *key);
int SetFuncName();
int CheckSeqNum(HWND hWnd);


extern char *OTP_btoe(char *, char *);

extern int  _otp_MD4_keycrunch(char *, char *, char *);
extern void _otp_MD4_iterate(char *);
extern int  _otp_MD5_keycrunch(char *, char *, char *);
extern void _otp_MD5_iterate(char *);
extern int  _otp_SHA1_keycrunch(char *result, char *seed, char *passwd);
extern void _otp_SHA1_iterate(char *x);


//	Title Type
#define		TITLE_NAME			1
#define		CLASS_NAME			2
//	Paste Type
#define		KEY_STROKE_PASTE	1
#define		DOS_PROMPT_PASTE	2

#define		CRLF				"\r\n"
#define		VK_E				0x45
#define		VK_P				0x50
#define		VK_T				0x54
#define		VK_V				0x56

//
//	Preference
//
#define		DOTKEY95_SUBKEY			"Software\\NEC\\" DOTKEY95_NAME
#define		WITHCRLF_VALNAME		"bWithCRLF"
#define		AUTOPASTE_VALNAME		"bAutoPaste"
#define		PASSCACHE_VALNAME		"bPassCache"
#define		CONFIRMATION_VALNAME	"bConfirmation"
#define		SKEY_MD5_VALNAME		"bSKeyMD5"
#define		CLEARCACHE_VALNAME		"bClearOnSuspend"
#define		SLEEPATCOPY_VALNAME		"iSleepAtCopy"

#define		DEFAULT_SLEEP_AT_COPY	500

typedef struct {
	BOOL	bWithCRLF;			// Save One-Time KEY with CRLF
	BOOL	bAutoPaste;			// Paste One-Time KEY Automatically
	BOOL	bPassCache;			// Use Password Cache
	BOOL	bConfirmation;		// Check before send a one-time password
	BOOL	bSKeyMD5;			// Calculate s/key as MD5
	BOOL	bClearOnSuspend;	// Clear Password Cache on Suspend
	char	cRotateKey;			// Rotate Password in Cache with this key
	int		iSleepAtCopy;		// Sleep time at copied; Delayed post SHIFT+ALT+TAB
} Preference;

#define		PASSCACHE_NUM		10

//	for Password Cache
typedef struct {
	int		HashFunc;							// Hash Function ID
	int		Sequence;							// Sequence Number
	char	Seed[SEED_MAX_LEN];					// Seed
	char	Passphrase[PASS_PHRASE_MAX_LEN];	// Secret key
} PassCache;

int	 InitPrefs();
BOOL LoadRegistory();
BOOL SaveRegistory();
int  PasteEvent(HWND hWnd);
int  SavePassCache(char *passphrase, int pos);
int  CheckPassCache();
int  RotatePassphrase(char *passphrase);
int  ClearPassCache();
