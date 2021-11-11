/*
 * sizes.h - define 32 bit and 16 bit signed and unsigned types for your
 *           machine
 */

#ifndef OTP_SIZES_H
# define OTP_SIZES_H

#ifdef MSDOS
typedef long                int32;
typedef unsigned long      uint32;

typedef unsigned long      UINT4;
typedef unsigned int       UINT2;

#else

typedef int                int32;
typedef unsigned int      uint32;

typedef unsigned int       UINT4;
typedef unsigned short int UINT2;

#endif

/* how to deal with function prototypes */

#ifndef __ARGS

#if	defined(__TURBOC__) || defined(__STDC__) || defined(LATTICE)
#define	ANSIPROTO	1
#endif

# ifdef	ANSIPROTO
#  define	__ARGS(x)	x
# else
#  define	__ARGS(x)	()
# endif

#endif  /* __ARGS */

typedef unsigned char *POINTER;

#endif

