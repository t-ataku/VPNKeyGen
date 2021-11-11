#include "sizes.h"

#define OTP_ACCEPTANCE_WINDOW 2

#ifndef MSDOS
struct passwd; /* forward reference to keep compilers happy */
#endif

/* Server-side data structure for reading keys file during login */
struct skey 
{
	FILE *keyfile;
	char buf[256];
	char *logname;
	int n;
	char *seed;
	char *val;
	char *alg;
        uint32 expire;
	uint32 lastchg;
        char *shared_upd_pw;
        int  valid;
};

typedef struct skey OTPstruct;

typedef int           (*OTPkeycrunchfcn) __ARGS((char *result, char *seed, char *passwd));
typedef void          (*OTPiteratefcn)   __ARGS((char *x));
typedef int           (*OTPaltdictfcn)   __ARGS((unsigned char *));
typedef unsigned char *(*OTPgenhashfcn)   __ARGS((unsigned char *, int));
typedef unsigned char *(*OTPgenfoldfcn)   __ARGS((unsigned char *, int));

char *OTP_btoe               __ARGS((char *engout,char *c));
char *OTP_put8               __ARGS((char *out,char *s));
int  _otp_std_to_binary      __ARGS((char *out,char *e));
int  _otp_alt_to_binary      __ARGS((char *out,char *a, OTPaltdictfcn));
char *OTP_btoalt             __ARGS((char *altout, char *c, char **altlist));
void _otp_rip                __ARGS((char *buf));
char *_otp_readpass          __ARGS((char *, int));
void _otp_sevenbit           __ARGS((char *));
void _otp_backspace          __ARGS((char *));
void _otp_standard           __ARGS((char *));

/*
 * backward compatibility functions. dont depend on them.
 */

int skeychallenge __ARGS((struct skey *mp,char *name, char *buf));
int skeylookup    __ARGS((struct skey *mp,char *name));
int skeyverify    __ARGS((struct skey *mp,char *response));

char *OTP_timed_getpass __ARGS((char *, OTPstruct *));
#ifndef MSDOS
char *OTP_crypt __ARGS((OTPstruct *, char *, char *, struct passwd *, int));
#endif

int       OTP_create_user __ARGS((char *, char *, int, char *, char *));
void      OTP_delete_user __ARGS((char *));

int       OTP_is_otp_user __ARGS((char *));
int       OTP_lookup      __ARGS((OTPstruct *, char *));
int       OTP_verify      __ARGS((OTPstruct *, char *));
void      OTP_release     __ARGS((OTPstruct *));
char     *OTP_challenge   __ARGS((OTPstruct *));

//void     OTP_ClearTimeoutAlarm ();
void     OTP_SetExpireSignal             __ARGS((int));

void     OTP_SetCallback                 __ARGS((int, void *));
void     OTP_DefaultCallback             __ARGS((int));

int      OTP_NormalPasswdOK              __ARGS((char *));

OTPkeycrunchfcn OTP_GetKeyCrunchFcn __ARGS((char *alg));
OTPiteratefcn   OTP_GetIterateFcn   __ARGS((char *alg));
OTPaltdictfcn   OTP_GetAltDictFcn   __ARGS((char *alg));
OTPgenhashfcn   OTP_GetGenHashFcn   __ARGS((char *alg));
OTPgenfoldfcn   OTP_GetGenFoldFcn   __ARGS((char *alg));

char **OTP_GetAltDictList __ARGS((char *alg));

int  OTP_KeyCrunch   __ARGS((char *, char *, char *, OTPkeycrunchfcn));
void OTP_IterateHash __ARGS((char *, OTPiteratefcn));

/* callback function hooks - look in otp_callbacks.c */

#define OTP_CALLBACK_TIMEOUT        1
#define OTP_CALLBACK_AUTHWINDOW     2
#define OTP_CALLBACK_QSTATUS        3
#define OTP_CALLBACK_UPD_COLLIDE    4
#define OTP_CALLBACK_UPDATEOK       5
#define OTP_CALLBACK_UPDATEFAIL     6
#define OTP_CALLBACK_OVERWRITE      7

#ifndef OTP_CALLBACK_INIT 
//extern void (*OTP_WindowProc) ();
//extern void (*OTP_TimeoutProc) ();
//extern void (*OTP_QueueStatusProc) ();
//extern void (*OTP_UpdateCollisionProc) ();
//extern void (*OTP_UpdateProc) ();
//extern void (*OTP_FailedUpdateProc) ();
//extern void (*OTP_OverwriteAlertProc) ();
#endif

unsigned char *HashWithMD4  __ARGS((unsigned char *, int));
unsigned char *HashWithMD5  __ARGS((unsigned char *, int));
unsigned char *HashWithSHA1 __ARGS((unsigned char *, int));

