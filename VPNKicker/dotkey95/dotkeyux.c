#include "dotkeyux.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

int  hash_func;
int  seq;								// Sequence Number
char seed[SEED_MAX_LEN];				// Seed
char pass[ONETIME_KEY_MAX_LEN];			// One-Time KEY

int  (* KeyCrunchFunc)(char *, char *, char *);
void (* IterateFunc)  (char *);
char FuncName[128];


///////////////////////////////////////////////////////////
//	Scan buffer got from clipboard
//
char * ScanBuf(char *p, char *key)
{
	char *s, *e;
	int  klen;

	klen = strlen(key);

	for (s = p, e = p + strlen(p) - klen; s <= e; s++){
		if (!strncmp(s, key, klen))
			return (s + klen);
	}

	return NULL;
}


//////////////////////////////////////////////////////
//	Set hash functions and algorithm name
//
int SetFuncName(int funcspec)
{
	switch(funcspec){
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

int FindSeq(char *buffer)
{
	char *p;

	if ((p = ScanBuf(buffer, OTPMD4)) != NULL){
		SetFuncName(MD4);
	} else if ((p = ScanBuf(buffer, OTPMD5))     != NULL){
		SetFuncName(MD5);
	} else if ((p = ScanBuf(buffer, OTPSHA1))    != NULL){
		SetFuncName(SHA1);
	} else if ((p = ScanBuf(buffer, SKEY))       != NULL){
	  /*	SetFuncName(pref.bSKeyMD5 ? MD5 : MD4);*/
	  ;
	} else if ((p = ScanBuf(buffer, BSDOS_SKEYMD4)) != NULL){
		SetFuncName(MD4);
	} else if ((p = ScanBuf(buffer, BSDOS_SKEYMD5)) != NULL){
		SetFuncName(MD5);
	} else {
		return FALSE;
	}

	if (sscanf(p, SEQSEED_POS, &seq, seed) != 2)
		return FALSE;

	return TRUE;
}

char *readline(char *buf, size_t len)
{
  int i;
  char *p;

  p = fgets(buf, len, stdin);
  if (p == NULL)
    return NULL;

  for (i = 0; i < len && buf[i]; i++)
    ;

  if (i < len) {
    /* trunc trailing CRLF */
    --i;
    if (i >= 0 && buf[i] == '\n') {
      buf[i] = '\0';
      --i;
      if (i >= 0 && buf[i] == '\r') {
	buf[i] = '\0';
      }
    }
  }
  
  return p;
}

void init_funcs(char *hash)
{
  FindSeq(hash);
}

/*
int main(int argc, char *argv[])
{
  char seq[10];
  unsigned int seqnum;
  char seed[SEED_MAX_LEN];				// Seed
  char phrase[PASS_PHRASE_MAX_LEN];
  char key[8];
  char pass[ONETIME_KEY_MAX_LEN];			// One-Time KEY
  int i;

  fprintf(stderr, "hash: %s\n", OTPMD5);
  init_funcs(OTPMD5);

  fprintf(stderr, "seq(496): ");
  if (!readline(seq, sizeof(seq))) {
    fprintf(stderr, "EOF:%c,ERR:%c\n", feof(stdin) ? 'T' : 'F', ferror(stdin) ? 'T' : 'F');
    return 1;
  }
  seqnum = strtoul(seq, NULL, 10);
  fprintf(stderr, "seed(vp163): ");
  if (!readline(seed, sizeof(seed))) {
    fprintf(stderr, "EOF:%c,ERR:%c\n", feof(stdin) ? 'T' : 'F', ferror(stdin) ? 'T' : 'F');
    return 1;
  }
  fprintf(stderr, "passphrase: ");
  if (!readline(phrase, sizeof(phrase))) {
    fprintf(stderr, "EOF:%c,ERR:%c\n", feof(stdin) ? 'T' : 'F', ferror(stdin) ? 'T' : 'F');
  }

  printf("SEQ: %u, SEED: %s, PHRASE: %s\n", seqnum, seed, phrase);

  if (KeyCrunchFunc(key, seed, phrase) == -1){
    memset(phrase, 0, PASS_PHRASE_MAX_LEN);
    fprintf(stderr, "Error in KeyCrunchFunc\n");
    return 1;
  }

  for (i = 0; i < seqnum; i++) IterateFunc(key);
  OTP_btoe(pass, key);
  printf("OTP: %s\n", pass);

  return 0;
}
*/
int genOTP(char *pass, const char *challenge, const char *phrase)
{
    char key[8];
    int i;

    init_funcs(challenge);
    if (KeyCrunchFunc(key, seed, phrase) == -1) {
        memset(phrase, '\0', PASS_PHRASE_MAX_LEN);
        printf("Error in KeyCrunchFunc");
        return 1;
    }

    for (i = 0; i < seq; i++)
        IterateFunc(key);
    OTP_btoe(pass, key);
    return 0;
}
