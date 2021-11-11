/*
 * Copyright (C) 1995 Phil Servita (meister@ftp.com)
 * Permission granted to use this code for non-commercial purposes.
 */
/*
 * otp_hash.c - hooks into the various hash functions we use in the 
 *              OTP system. Each hash method (MD4, MD5, or anything else
 *              that gets added in later) needs three functions defined 
 *              here; one to do a "keycrunch" operation, one to
 *              do a hash iteration, and one to do an alternate dictionary 
 *              hash.  Currently we support md4, md5, and SHA1
 *
 *              The keycrunch function should return 0 on success and -1 on 
 *              failure.
 */              

//#ifdef USE_STDLIB_H
# include <stdlib.h>
//#endif

#ifdef USE_STRINGS_H
# include <strings.h>
#endif

#ifdef USE_STRING_H
# include <string.h>
#endif

#include <stdio.h>

#include "sizes.h"
#include "md4.h"
#include "md5.h"
#include "sha.h"
#include "otp.h"

void _otp_sevenbit(char *s)
{
	while(*s){
		*s = 0x7f & (*s);
		s++;
	}
}

#ifndef OTP_DONT_DO_MD4

int _otp_MD4_keycrunch (result, seed, passwd)
        char *result;	/* 8-byte result */
        char *seed;	/* Seed, any length */
        char *passwd;	/* Password, any length */
{
	MDstruct md;
	char *buf;
        unsigned int buflen;

	int i;
	register uint32 tmp;
	
	buflen = strlen (seed) + strlen(passwd);
	if ((buf = malloc (buflen+1)) == NULL)
	    return -1;
	strcpy (buf,seed);
	strcat (buf,passwd);

	/* Crunch the key through MD4 */
	_otp_sevenbit (buf);
	MDbegin  (&md);
	MDupdate (&md, (unsigned char *) buf, 8 * buflen);

	free(buf);

	/* Fold result from 128 to 64 bits */
	md.buffer[0] ^= md.buffer[2];
	md.buffer[1] ^= md.buffer[3];

	/* Default (but slow) code that will convert to
	 * little-endian byte ordering on any machine
	 */
	for(i=0;i<2;i++){
		tmp = md.buffer[i];
		*result++ = (unsigned char)tmp;
		tmp >>= 8;
		*result++ = (unsigned char)tmp;
		tmp >>= 8;
		*result++ = (unsigned char)tmp;
		tmp >>= 8;
		*result++ = (unsigned char)tmp;
	}

        return 0;
}

void _otp_MD4_iterate (x)
      char *x;
{
	MDstruct md;
	register uint32 tmp;

	MDbegin(&md);
	MDupdate(&md,(unsigned char *)x,64);

	/* Fold 128 to 64 bits */
	md.buffer[0] ^= md.buffer[2];
	md.buffer[1] ^= md.buffer[3];

	/* Default (but slow) code that will convert to
	 * little-endian byte ordering on any machine
	 */
	tmp = md.buffer[0];
	*x++ = (unsigned char)tmp;
	tmp >>= 8;
	*x++ = (unsigned char)tmp;
	tmp >>= 8;
	*x++ = (unsigned char)tmp;
	tmp >>= 8;
	*x++ = (unsigned char)tmp;

	tmp = md.buffer[1];
	*x++ = (unsigned char)tmp;
	tmp >>= 8;
	*x++ = (unsigned char)tmp;
	tmp >>= 8;
	*x++ = (unsigned char)tmp;
	tmp >>= 8;
	*x = (unsigned char)tmp;
}

unsigned char *_otp_MD4_foldhash (in, n)
        unsigned char *in;
        int n;
{
        static unsigned char retval [8];
        unsigned char *result = retval;

	MDstruct md;

	int i;
	register uint32 tmp;
	
	MDbegin  (&md);
	MDupdate (&md, in, 8 * n);

	/* Fold result from 128 to 64 bits */
	md.buffer[0] ^= md.buffer[2];
	md.buffer[1] ^= md.buffer[3];

	/* Default (but slow) code that will convert to
	 * little-endian byte ordering on any machine
	 */
	for(i=0;i<2;i++){
		tmp = md.buffer[i];
		*result++ = (unsigned char)tmp;
		tmp >>= 8;
		*result++ = (unsigned char)tmp;
		tmp >>= 8;
		*result++ = (unsigned char)tmp;
		tmp >>= 8;
		*result++ = (unsigned char)tmp;
	}

        return retval;
}

/*
 * compute alternate dictionary encoding for a word using MD4
 */

int _otp_MD4_altdict (word)
    char *word;
{
    unsigned char *digest;
    unsigned char xor_odd;
    unsigned char xor_even;

    digest = HashWithMD4 ((unsigned char *) word, strlen (word));
 
    xor_even = digest [14];
    xor_odd = digest [15];
#ifdef DEBUG_ALTDICT 
    printf ("md4 altdict %s returns %d\n", word,
            (int) (( ((short) xor_even << 8) + xor_odd ) % 2048));
#endif
    return (int) (( ((short) xor_even << 8) + xor_odd ) % 2048);
}

unsigned char *HashWithMD4 (buf, len)
    unsigned char *buf;
    int len;
{
    MDstruct md;
    static unsigned char digest[16];
    unsigned char *bptr = buf;

    MDbegin  (&md);

    while (len >= 64)
    {      MDupdate (&md, bptr, 512);
           len -= 64;
           bptr += 64;
    }
    MDupdate (&md, bptr, 8 * len);

    /* extract out the digest */

    digest [0] = (unsigned char)md.buffer [0] & 0xFF;     md.buffer [0] >>= 8;
    digest [1] = (unsigned char)md.buffer [0] & 0xFF;     md.buffer [0] >>= 8;
    digest [2] = (unsigned char)md.buffer [0] & 0xFF;     md.buffer [0] >>= 8;
    digest [3] = (unsigned char)md.buffer [0] & 0xFF;     

    digest [4] = (unsigned char)md.buffer [1] & 0xFF;     md.buffer [1] >>= 8;
    digest [5] = (unsigned char)md.buffer [1] & 0xFF;     md.buffer [1] >>= 8;
    digest [6] = (unsigned char)md.buffer [1] & 0xFF;     md.buffer [1] >>= 8;
    digest [7] = (unsigned char)md.buffer [1] & 0xFF;     

    digest [8] = (unsigned char)md.buffer [2] & 0xFF;     md.buffer [2] >>= 8;
    digest [9] = (unsigned char)md.buffer [2] & 0xFF;     md.buffer [2] >>= 8;
    digest [10] = (unsigned char)md.buffer [2] & 0xFF;     md.buffer [2] >>= 8;
    digest [11] = (unsigned char)md.buffer [2] & 0xFF;     

    digest [12] = (unsigned char)md.buffer [3] & 0xFF;     md.buffer [3] >>= 8;
    digest [13] = (unsigned char)md.buffer [3] & 0xFF;     md.buffer [3] >>= 8;
    digest [14] = (unsigned char)md.buffer [3] & 0xFF;     md.buffer [3] >>= 8;
    digest [15] = (unsigned char)md.buffer [3] & 0xFF;     

    return digest;
}

void test_MD4 ()
{
    int i;
    unsigned char *X = HashWithMD4 ((unsigned char *) "", 0);
    for (i = 0 ; i < 16 ; i++)
         printf ("%x ", X [i]);
    printf ("\n");
    printf ("should be \n");
}

#endif /* OTP_DONT_DO_MD4 */

#ifndef OTP_DONT_DO_MD5
/*
 * functions for MD5. not surprisingly, they look a lot like the 
 * ones for MD4...
 */

int _otp_MD5_keycrunch (result, seed, passwd)
        char *result;	/* 8-byte result */
        char *seed;	/* Seed, any length */
        char *passwd;	/* Password, any length */
{

        MD5_CTX md;
	char *buf;

        UINT4 results [4];
        unsigned int buflen;
	
	buflen = strlen (seed) + strlen(passwd);
	if ((buf = malloc (buflen+1)) == NULL)
	    return -1;
	strcpy (buf,seed);
	strcat (buf,passwd);

	_otp_sevenbit (buf);

        MD5Init(&md);
        MD5Update(&md,(unsigned char *)buf,buflen);
        MD5Final((unsigned char *)results,&md);

	free(buf);

        results[0] ^= results[2];
        results[1] ^= results[3];

        memcpy (result, (char *) results, 8);
        return 0;
}

char bufx [32];

void _otp_MD5_iterate (x)
        char *x;
{
        MD5_CTX md;
        UINT4 results[4];

        MD5Init (&md);
        MD5Update (&md, (unsigned char *) x, 8);

        MD5Final ((unsigned char *) results, &md);

        /* Fold 128 to 64 bits */
        results[0] ^= results[2];
        results[1] ^= results[3];

        /* Only works on byte-addressed little-endian machines!! */
        memcpy (x, (char *) results, 8);

}

unsigned char *_otp_MD5_foldhash (in, n)
        unsigned char *in;
        int n;
{
        static unsigned char retval [8];
	MD5_CTX md;

        UINT4 results [4];
	
        MD5Init(&md);
        MD5Update(&md, in, n);
        MD5Final((unsigned char *) results, &md);

        results[0] ^= results[2];
        results[1] ^= results[3];

        memcpy (retval, (char *) results, 8);

        return retval;
}

/*
 * compute alternate dictionary encoding for a word using MD5
 */

int _otp_MD5_altdict (word)
    char *word;
{
    unsigned char *digest;
    unsigned char xor_odd;
    unsigned char xor_even;

    digest = HashWithMD5 ((unsigned char *) word, strlen (word));
 
    xor_even = digest [14];
    xor_odd = digest [15];
#ifdef DEBUG_ALTDICT 
    printf ("md5 altdict %s returns %d\n", word,
            (int) (( ((short) xor_even << 8) + xor_odd ) % 2048));
#endif            
    return (int) (( ((short) xor_even << 8) + xor_odd ) % 2048);
}

unsigned char *HashWithMD5 (buf, len)
    unsigned char *buf;
    int len;
{
   static unsigned char digest[16];
   MD5_CTX mdstr;	         /* MD5 data structures */
   MD5_CTX *mdbuf;	         

   /* 
    * Do MD5 magic; 
    */

   mdbuf = &mdstr;
   MD5Init (mdbuf);
   MD5Update (mdbuf, buf, len);
   MD5Final (digest, mdbuf);         
   return digest;
}

void test_MD5 ()
{
    int i;
    unsigned char *X = HashWithMD5 ((unsigned char *) "", 0);
    for (i = 0 ; i < 16 ; i++)
         printf ("%x ", X [i]);
    printf ("\n");
    printf ("should be \nd4 1d 8c d9 8f 00 b2 04 e9 80 09 98 ec f8 42 7e\n");
}

#endif /* OTP_DONT_DO_MD5 */

#ifndef OTP_DONT_DO_SHA1

/*
 * same functions for SHA1
 */

int _otp_SHA1_keycrunch (result, seed, passwd)
        char *result;	/* 8-byte result */
        char *seed;	/* Seed, any length */
        char *passwd;	/* Password, any length */
{
        uint32 HASH [5];
        uint32 buflen;
        char *buf;
        register uint32 tmp;
	
	buflen = strlen (seed) + strlen(passwd);
	if ((buf = malloc (buflen+1)) == NULL)
	    return -1;

	strcpy (buf,seed);
	strcat (buf,passwd);

	_otp_sevenbit (buf);

        sha_memory (buf, buflen, HASH);

        /* fold 160 bits down to 64 bits */
        HASH [0] ^= HASH [2];
        HASH [1] ^= HASH [3];
        HASH [0] ^= HASH [4];    

#if 1
	/* Default (but slow) code that will convert to
	 * little-endian byte ordering on any machine
	 */
	tmp = HASH [0];
	*result++ = (unsigned char)tmp & 0xFF;
	tmp >>= 8;
	*result++ = (unsigned char)tmp & 0xFF;
	tmp >>= 8;
	*result++ = (unsigned char)tmp & 0xFF;
	tmp >>= 8;
	*result++ = (unsigned char)tmp & 0xFF;

	tmp = HASH [1];
	*result++ = (unsigned char)tmp & 0xFF;
	tmp >>= 8;
	*result++ = (unsigned char)tmp & 0xFF;
	tmp >>= 8;
	*result++ = (unsigned char)tmp & 0xFF;
	tmp >>= 8;
	*result = (unsigned char)tmp & 0xFF;
#else
        memcpy (result, (unsigned char *) HASH, 8);
#endif

        return 0;
}

void _otp_SHA1_iterate (x)
	char *x;
{
        uint32 HASH [5];
//        uint32 buflen;
        register uint32 tmp;

        sha_memory (x, (uint32) 8, HASH);

        /* fold 160 bits down to 64 bits */
        HASH [0] ^= HASH [2];
        HASH [1] ^= HASH [3];
        HASH [0] ^= HASH [4];    

#if 1
	/* 
         * Default (but slow) code that will convert to
	 * little-endian byte ordering on any machine
	 */

	tmp = HASH [0];
	*x++ = (unsigned char)tmp & 0xFF;
	tmp >>= 8;
	*x++ = (unsigned char)tmp & 0xFF;
	tmp >>= 8;
	*x++ = (unsigned char)tmp & 0xFF;
	tmp >>= 8;
	*x++ = (unsigned char)tmp & 0xFF;

	tmp = HASH [1];
	*x++ = (unsigned char)tmp & 0xFF;
	tmp >>= 8;
	*x++ = (unsigned char)tmp & 0xFF;
	tmp >>= 8;
	*x++ = (unsigned char)tmp & 0xFF;
	tmp >>= 8;
	*x = (unsigned char)tmp & 0xFF;
#else
        memcpy (x, (unsigned char *) HASH, 8);
#endif
}

unsigned char *_otp_SHA1_foldhash (in, n)
        unsigned char *in;
        int n;
{
        uint32 HASH [5];
        static unsigned char retval [8];
        unsigned char *result = retval;

        register uint32 tmp;

        sha_memory ((char *)in, (uint32) n, HASH);

        /* fold 160 bits down to 64 bits */
        HASH [0] ^= HASH [2];
        HASH [1] ^= HASH [3];
        HASH [0] ^= HASH [4];    

#if 1
	/* Default (but slow) code that will convert to
	 * little-endian byte ordering on any machine
	 */
	tmp = HASH [0];
	*result++ = (unsigned char)tmp & 0xFF;
	tmp >>= 8;
	*result++ = (unsigned char)tmp & 0xFF;
	tmp >>= 8;
	*result++ = (unsigned char)tmp & 0xFF;
	tmp >>= 8;
	*result++ = (unsigned char)tmp & 0xFF;

	tmp = HASH [1];
	*result++ = (unsigned char)tmp & 0xFF;
	tmp >>= 8;
	*result++ = (unsigned char)tmp & 0xFF;
	tmp >>= 8;
	*result++ = (unsigned char)tmp & 0xFF;
	tmp >>= 8;
	*result = (unsigned char)tmp & 0xFF;
#else
        memcpy (retval, (unsigned char *) HASH, 8);
#endif
        return retval;
}

/*
 * compute alternate dictionary encoding for a word using SHA1
 */

int _otp_SHA1_altdict (word)
    char *word;
{
    unsigned char *digest;
    unsigned char xor_odd;
    unsigned char xor_even;

    digest = HashWithSHA1 ((unsigned char *) word, strlen (word));
 
    xor_even = digest [18];
    xor_odd = digest [19];
#ifdef DEBUG_ALTDICT 
    printf ("sha1 altdict %s returns %d\n", word,
            (int) (( ((short) xor_even << 8) + xor_odd ) % 2048));
#endif             
    return (int) (( ((short) xor_even << 8) + xor_odd ) % 2048);
}

unsigned char *HashWithSHA1 (buf, len)
    unsigned char *buf;
    int len;
{
   uint32 HASH [5];
   static unsigned char digest [20];

   /* 
    * Do SHS magic; 
    */

   sha_memory ((char*)buf, (uint32) len, HASH);

#if 1
   digest [3] = (unsigned char)HASH [0] & 0xFF;  HASH [0] >>= 8;
   digest [2] = (unsigned char)HASH [0] & 0xFF;  HASH [0] >>= 8;
   digest [1] = (unsigned char)HASH [0] & 0xFF;  HASH [0] >>= 8;
   digest [0] = (unsigned char)HASH [0] & 0xFF;  

   digest [7] = (unsigned char)HASH [1] & 0xFF;  HASH [1] >>= 8;
   digest [6] = (unsigned char)HASH [1] & 0xFF;  HASH [1] >>= 8;
   digest [5] = (unsigned char)HASH [1] & 0xFF;  HASH [1] >>= 8;
   digest [4] = (unsigned char)HASH [1] & 0xFF;  

   digest [11] = (unsigned char)HASH [2] & 0xFF;  HASH [2] >>= 8;
   digest [10] = (unsigned char)HASH [2] & 0xFF;  HASH [2] >>= 8;
   digest [9] = (unsigned char)HASH [2] & 0xFF;  HASH [2] >>= 8;
   digest [8] = (unsigned char)HASH [2] & 0xFF;  

   digest [15] = (unsigned char)HASH [3] & 0xFF;  HASH [3] >>= 8;
   digest [14] = (unsigned char)HASH [3] & 0xFF;  HASH [3] >>= 8;
   digest [13] = (unsigned char)HASH [3] & 0xFF;  HASH [3] >>= 8;
   digest [12] = (unsigned char)HASH [3] & 0xFF;  

   digest [19] = (unsigned char)HASH [4] & 0xFF;  HASH [4] >>= 8;
   digest [18] = (unsigned char)HASH [4] & 0xFF;  HASH [4] >>= 8;
   digest [17] = (unsigned char)HASH [4] & 0xFF;  HASH [4] >>= 8;
   digest [16] = (unsigned char)HASH [4] & 0xFF;  
#else
   memcpy (digest, HASH, 20);
#endif

   return digest;
}

void test_SHA1 ()
{
    int i;
    unsigned char *X = HashWithSHA1 ((unsigned char *) "abc", 3);
    for (i = 0 ; i < 20 ; i++)
         printf ("%x ", X [i]);
    printf ("\n");
    printf ("should be \na9 99 3e 36 47 06 81 6a ba 3e 25 71 78 50 c2 6c 9c d0 d8 9d\n");
}

#endif  /* OTP_DONT_DO_SHA1 */

/*
 * List of hash algorithms with corresponding keycrunch, iteration,
 * and altdict functions.
 */

struct otp_hashlist 
{    char *alg_name;
     OTPkeycrunchfcn keycrunch_fcn;
     OTPiteratefcn   iterate_fcn;
     OTPaltdictfcn   altdict_fcn;
     OTPgenhashfcn   genhash_fcn;
     OTPgenfoldfcn   genfold_fcn;
};

static struct otp_hashlist OTP_HASHLIST [] = 
{
#ifndef OTP_DONT_DO_MD4
    { "MD4", (OTPkeycrunchfcn) _otp_MD4_keycrunch, 
             (OTPiteratefcn) _otp_MD4_iterate, 
             (OTPaltdictfcn) _otp_MD4_altdict,
             (OTPgenhashfcn) HashWithMD4,
             (OTPgenfoldfcn) _otp_MD4_foldhash
    }, 
    { "md4", (OTPkeycrunchfcn) _otp_MD4_keycrunch, 
             (OTPiteratefcn) _otp_MD4_iterate,
             (OTPaltdictfcn) _otp_MD4_altdict,
             (OTPgenhashfcn) HashWithMD4,
             (OTPgenfoldfcn) _otp_MD4_foldhash
    }, 
#endif /* OTP_DONT_DO_MD4 */
#ifndef OTP_DONT_DO_MD5
    { "MD5", (OTPkeycrunchfcn) _otp_MD5_keycrunch, 
             (OTPiteratefcn) _otp_MD5_iterate,
             (OTPaltdictfcn) _otp_MD5_altdict,
             (OTPgenhashfcn) HashWithMD5,
             (OTPgenfoldfcn) _otp_MD5_foldhash
    },
    { "md5", (OTPkeycrunchfcn) _otp_MD5_keycrunch, 
             (OTPiteratefcn) _otp_MD5_iterate,
             (OTPaltdictfcn) _otp_MD5_altdict,
             (OTPgenhashfcn) HashWithMD5,
             (OTPgenfoldfcn) _otp_MD5_foldhash
    },
#endif /* OTP_DONT_DO_MD5 */
#ifndef OTP_DONT_DO_SHA1
    { "SHA1",(OTPkeycrunchfcn) _otp_SHA1_keycrunch,
             (OTPiteratefcn) _otp_SHA1_iterate,
             (OTPaltdictfcn) _otp_SHA1_altdict,
             (OTPgenhashfcn) HashWithSHA1,
             (OTPgenfoldfcn) _otp_SHA1_foldhash
    },
    { "sha1",(OTPkeycrunchfcn) _otp_SHA1_keycrunch, 
             (OTPiteratefcn) _otp_SHA1_iterate,
             (OTPaltdictfcn) _otp_SHA1_altdict,
             (OTPgenhashfcn) HashWithSHA1,
             (OTPgenfoldfcn) _otp_SHA1_foldhash
    },
#endif /* OTP_DONT_DO_SHA1 */
    { (char *) 0, (OTPkeycrunchfcn) 0, (OTPiteratefcn) 0, (OTPaltdictfcn) 0,
                  (OTPgenhashfcn) 0, (OTPgenfoldfcn) 0 }
};

/*
 * this function returns the correct keycrunch function to use for a given
 * algorithm, or ((int (*) ()) 0 if an unknown algorithm is specified.
 * Currently supported algorithms are listed above.
 */

OTPkeycrunchfcn OTP_GetKeyCrunchFcn (alg)
     char *alg;   
{
     struct otp_hashlist *hptr = OTP_HASHLIST;
     int i = 0;
     
     while (hptr [i].alg_name)
     {      if (strcmp (alg, hptr [i].alg_name) == 0)
                return hptr [i].keycrunch_fcn;
            i++;
     }

     return (OTPkeycrunchfcn) 0;
}


/*
 * this function returns the correct hash iteration function to use for
 * a given hash algorithm, or ((int (*) ()) 0 if an unknown algorithm is
 * specified. Currently supported algorithms are listed above.
 */

OTPiteratefcn OTP_GetIterateFcn (alg)
     char *alg;   
{
     struct otp_hashlist *hptr = OTP_HASHLIST;
     int i = 0;
     
     while (hptr [i].alg_name)
     {
            if (strcmp (alg, hptr [i].alg_name) == 0)
                return hptr [i].iterate_fcn;
            i++;
     }

     return (OTPiteratefcn) 0;
}


/*
 * this function returns the alternate dictionary hash to use for
 * a given hash algorithm, or ((int (*) ()) 0 if an unknown algorithm is
 * specified. Currently supported algorithms are listed above.
 */

OTPaltdictfcn OTP_GetAltDictFcn (alg)
     char *alg;   
{
     struct otp_hashlist *hptr = OTP_HASHLIST;
     int i = 0;
     
     while (hptr [i].alg_name)
     {
            if (strcmp (alg, hptr [i].alg_name) == 0)
                return hptr [i].altdict_fcn;
            i++;
     }

     return (OTPaltdictfcn) 0;
}

/*
 * this function returns the generic hash function to use for
 * a given hash algorithm, or ((int (*) ()) 0 if an unknown algorithm is
 * specified. Currently supported algorithms are listed above.
 */

OTPgenhashfcn OTP_GetGenHashFcn (alg)
     char *alg;   
{
     struct otp_hashlist *hptr = OTP_HASHLIST;
     int i = 0;
     
     while (hptr [i].alg_name)
     {
            if (strcmp (alg, hptr [i].alg_name) == 0)
                return hptr [i].genhash_fcn;
            i++;
     }

     return (OTPgenhashfcn) 0;
}

/*
 * this function returns the folded generic hash fcn to use for
 * a given hash algorithm, or ((int (*) ()) 0 if an unknown algorithm is
 * specified. Currently supported algorithms are listed above.
 */

OTPgenfoldfcn OTP_GetGenFoldFcn (alg)
     char *alg;   
{
     struct otp_hashlist *hptr = OTP_HASHLIST;
     int i = 0;
     
     while (hptr [i].alg_name)
     {
            if (strcmp (alg, hptr [i].alg_name) == 0)
                return hptr [i].genfold_fcn;
            i++;
     }

     return (OTPgenfoldfcn) 0;
}
       

