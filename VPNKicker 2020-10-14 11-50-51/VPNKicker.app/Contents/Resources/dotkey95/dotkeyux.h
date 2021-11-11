#ifndef DOTKEYUX_H
#define DOTKEYUX_H

#define FALSE (0)
#define TRUE (!FALSE)

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
int CheckSeqNum();


extern char *OTP_btoe(char *, char *);

extern int  _otp_MD4_keycrunch(char *, char *, char *);
extern void _otp_MD4_iterate(char *);
extern int  _otp_MD5_keycrunch(char *, char *, char *);
extern void _otp_MD5_iterate(char *);
extern int  _otp_SHA1_keycrunch(char *result, char *seed, char *passwd);
extern void _otp_SHA1_iterate(char *x);

extern int genOTP(char *pass, const char *challenge, const char *phrase);
#endif
