#ifndef __STDLIB_CORE_H__
#define __STDLIB_CORE_H__
#ident "$Revision: 1.6 $"
/*
*
* Copyright 1992-1996 Silicon Graphics, Inc.
* All Rights Reserved.
*
* This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics, Inc.;
* the contents of this file may not be disclosed to third parties, copied or
* duplicated in any form, in whole or in part, without the prior written
* permission of Silicon Graphics, Inc.
*
* RESTRICTED RIGHTS LEGEND:
* Use, duplication or disclosure by the Government is subject to restrictions
* as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data
* and Computer Software clause at DFARS 252.227-7013, and/or in similar or
* successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -
* rights reserved under the Copyright Laws of the United States.
*/
/*	Copyright (c) 1988 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
 * WARNING - this is an ANSI/XPG4 header. Watch for name space pollution
 */

#include <standards.h>
#include <sgidefs.h>
#include <internal/sgimacros.h>

#ifndef	NULL
#define NULL	0L
#endif

/* Arguments to exit(2). */
#define EXIT_FAILURE	1
#define EXIT_SUCCESS	0

/* Maximum value returned by rand(3C). */
#define RAND_MAX	32767

#ifdef _LANGUAGE_ASSEMBLY
/* assembly-level offsets of quot, rem fields into [l ]div_t structure below */
#define _QUOT_OFFSET 	0
#define _REM_OFFSET	4
#if (_MIPS_SZLONG == 32)
#define _LQUOT_OFFSET 	0
#define _LREM_OFFSET	4
#endif
#if (_MIPS_SZLONG == 64)
#define _LQUOT_OFFSET 	0
#define _LREM_OFFSET	8
#endif
#if _SGIAPI
#define _LLQUOT_OFFSET 	0
#define _LLREM_OFFSET	8
#endif
#endif 

#if (_XOPEN4 || _XOPEN5) && _NO_ANSIMODE
/*
 * The following defines have been copied from "sys/wait.h"
 * for XOpen XPG4.  These defines are used in the return 
 * codes from 'system()' system call.
 */
#ifndef _W_INT
#define _W_INT(i)	(i)
#endif	/* !_W_INT */

#ifndef WUNTRACED
#define	WUNTRACED	0004
#define WNOHANG		0100
#define	_WSTOPPED	0177	/* value of s.stopval if process is stopped */
#define WIFEXITED(stat)         ((_W_INT(stat)&0377)==0)
#define WIFSIGNALED(stat)       ((_W_INT(stat)&0377)>0&&((_W_INT(stat)>>8)&0377)==0)
#define WIFSTOPPED(stat)        ((_W_INT(stat)&0377)==_WSTOPPED&&((_W_INT(stat)>>8)&0377)!=0)
#define WEXITSTATUS(stat)	((_W_INT(stat)>>8)&0377)
#define WTERMSIG(stat)		(_W_INT(stat)&0177)
#define WSTOPSIG(stat)		((_W_INT(stat)>>8)&0377)
#endif	/* !WUNTRACED */
#endif	/* (_XOPEN4 || _XOPEN5) && _NO_ANSIMODE */

#if (defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS))
__SGI_LIBC_BEGIN_EXTERN_C

__SGI_LIBC_BEGIN_NAMESPACE_STD

#if !defined(_SIZE_T) && !defined(_SIZE_T_)
#define _SIZE_T
#if (_MIPS_SZLONG == 32)
typedef unsigned int	size_t;
#endif
#if (_MIPS_SZLONG == 64)
typedef unsigned long	size_t;
#endif
#endif

#ifndef _WCHAR_T
#define _WCHAR_T
#if (_MIPS_SZLONG == 32)
typedef long wchar_t;
#endif
#if (_MIPS_SZLONG == 64)
typedef __int32_t wchar_t;
#endif
#endif

__SGI_LIBC_END_NAMESPACE_STD

typedef	struct {
	 int	quot;
	 int	rem;
	} div_t;

typedef struct {
	 long	quot;
	 long	rem;
	} ldiv_t;

#if defined(__c99) || ((_SGIAPI || _ABIAPI) && _NO_ANSIMODE)

typedef struct {
	 long long	quot;
	 long long	rem;
	} lldiv_t;

#endif /* __c99 || _SGIAPI || _ABIAPI */

#if _NO_ANSIMODE
#ifndef _SSIZE_T
#define _SSIZE_T
#if (_MIPS_SZLONG == 32)
typedef int	ssize_t;
#endif
#if (_MIPS_SZLONG == 64)
typedef long	ssize_t;
#endif
#endif
#endif /* _NO_ANSIMODE */

#ifndef _KERNEL
__SGI_LIBC_END_EXTERN_C
#include <internal/locale_attr_core.h>
__SGI_LIBC_BEGIN_EXTERN_C
#define MB_CUR_MAX	((int)(__libc_attr._csinfo._mb_cur_max))

#else	/* _KERNEL */
extern unsigned char	__ctype[];

#define MB_CUR_MAX	(int)__ctype[520]
#endif	/* _KERNEL */

/* ANSI functions */
__SGI_LIBC_BEGIN_NAMESPACE_STD

/* C99: 7.20.1 Numeric conversion functions */

extern double atof(const char *);

extern int atoi(const char *);
extern long int atol(const char *);
#if defined(__c99) || ((_SGIAPI || _ABIAPI) && _NO_ANSIMODE)
extern long long atoll(const char *);
#endif /* __c99 || _SGIAPI || _ABIAPI */

extern double strtod(const char * __restrict, char ** __restrict);
#if defined(__c99)
extern float strtof(const char * __restrict, char ** __restrict);
#if !defined(_SGI_COMPILING_LIBC)
#pragma optional strtof
#endif
#endif /* __c99 */
#if defined(__c99) || (_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64)
extern long double strtold(const char * __restrict, char ** __restrict);
#endif /* __c99 */

extern long int strtol(const char * __restrict, char ** __restrict, int);
#if defined(__c99) || ((_SGIAPI || _ABIAPI) && _NO_ANSIMODE)
extern long long strtoll(const char * __restrict, char ** __restrict, int);
#endif /* __c99 || _SGIAPI || _ABIAPI */
extern unsigned long int strtoul(const char * __restrict, char ** __restrict, int);
#if defined(__c99) || ((_SGIAPI || _ABIAPI) && _NO_ANSIMODE)
#ifndef _STANDALONE
extern unsigned long long strtoull(const char * __restrict, char ** __restrict, int);
#endif /* _STANDALONE */
#endif /* __c99 || _SGIAPI || _ABIAPI */

/* C99: 7.20.2 Pseudo-random sequence generation functions */

extern int rand(void);

extern void srand(unsigned int);

/* C99: 7.20.3 Memory management functions */

extern void *calloc(size_t, size_t);

extern void free(void *);

extern void *malloc(size_t);

extern void *realloc(void *, size_t);

#if _NO_XOPEN4 && _NO_XOPEN5 && (defined(__INLINE_INTRINSICS) && \
        defined(_COMPILER_VERSION) && (_COMPILER_VERSION >= 710))
#pragma intrinsic (calloc)
#pragma intrinsic (free)
#pragma intrinsic (malloc)
#pragma intrinsic (realloc)
#endif

/* C99: 7.20.4 Communications with the environment */

extern void abort(void);

extern int atexit(void (*)(void));

extern void exit(int);
#if _NO_XOPEN4 && _NO_XOPEN5 && (defined(__INLINE_INTRINSICS) && \
        defined(_COMPILER_VERSION) && (_COMPILER_VERSION >= 710))
#pragma intrinsic (exit)
#endif

#if defined(__c99)
extern void _Exit(int);
#endif /* __c99 */

extern char *getenv(const char *);

extern int system(const char *);

/* C99: 7.20.5 Searching and sorting utilities */

extern void *bsearch(const void *, const void *, size_t, size_t,
	int (*)(const void *, const void *));

extern void qsort(void *, size_t, size_t,
	int (*)(const void *, const void *));

/* C99: 7.20.6 Integer arithmetic functions */

#ifdef __cplusplus
#ifndef _ABS_
#define _ABS_
inline int abs(int x) {return x > 0 ? x : -x;}
#endif /* _ABS_ */
#else
extern int abs(int);
#endif /* __cplusplus */
extern long int labs(long);
#if defined(__c99) || ((_SGIAPI || _ABIAPI) && _NO_ANSIMODE)
extern long long llabs(long long);
#endif /* __c99 || _SGIAPI || _ABIAPI */
#if _NO_XOPEN4 && _NO_XOPEN5 && (defined(__INLINE_INTRINSICS) && \
        defined(_COMPILER_VERSION) && (_COMPILER_VERSION >= 710))
#ifndef __cplusplus
#pragma intrinsic (abs)
#endif
#pragma intrinsic (labs)
#if defined(__c99) || ((_SGIAPI || _ABIAPI) && _NO_ANSIMODE)
#pragma intrinsic (llabs)
#endif /* __c99 || _SGIAPI || _ABIAPI */
#endif

extern div_t div(int, int);
extern ldiv_t ldiv(long, long);
#if defined(__c99) || ((_SGIAPI || _ABIAPI) && _NO_ANSIMODE)
extern lldiv_t lldiv(long long, long long);
#endif /* __c99 || _SGIAPI || _ABIAPI */

/* C99: 7.20.7 Multibyte/wide character conversion functions */

extern int mblen(const char *, size_t);

extern int mbtowc(wchar_t * __restrict, const char * __restrict, size_t);

extern int wctomb(char *, wchar_t);

/* C99: 7.20.8 Multibyte/wide string conversion functions */

extern size_t mbstowcs(wchar_t * __restrict, const char * __restrict, size_t);

extern size_t wcstombs(char * __restrict, const wchar_t * __restrict, size_t);

__SGI_LIBC_END_NAMESPACE_STD

#if (_XOPEN4 || _XOPEN5) && _NO_ANSIMODE
	/* XOPEN additions */
#if (defined(_XOPEN_SOURCE) && (_XOPEN_SOURCE+0 >= 500))
extern int	putenv(char *);
#else
extern int	putenv(const char *);
#endif
extern double	drand48(void);
extern double	erand48(unsigned short [3]);
extern long	lrand48(void);
extern long	nrand48(unsigned short [3]);
extern long	mrand48(void);
extern long	jrand48(unsigned short [3]);
extern void	srand48(long);
extern void	lcong48(unsigned short int [7]);
extern void     setkey(const char *);
extern unsigned short * seed48(unsigned short int [3]);
#endif /* _XOPEN4 || _XOPEN5 */

#if (_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE
	/* XOPEN-UX additions */
extern long a64l(const char *);
extern char *ecvt(double, int, int *, int *);
extern char *fcvt(double, int, int *, int *);
extern char *gcvt(double, int, char *);
extern int getsubopt(char **, char * const *, char **);
extern int grantpt(int);
extern char *initstate(unsigned int, char *, __SGI_LIBC_NAMESPACE_QUALIFIER size_t);
extern char *l64a(long);
extern char *mktemp(char *);
extern int mkstemp(char *);
extern char *ptsname(int);
extern long random(void);
extern char *realpath(const char *, char *);
extern char *setstate(const char *);
extern void srandom(unsigned);
extern int ttyslot(void);
extern int unlockpt(int);
extern void *valloc(__SGI_LIBC_NAMESPACE_QUALIFIER size_t);
#if _NO_XOPEN4 && _NO_XOPEN5 && (defined(__INLINE_INTRINSICS) && \
        defined(_COMPILER_VERSION) && (_COMPILER_VERSION >= 710))
#pragma intrinsic (valloc)
#endif
#endif  /* _XOPEN4UX || _XOPEN5 */

#if _POSIX1C && _NO_ANSIMODE
extern int rand_r(unsigned int *);
#endif

#if _SGIAPI && _NO_ANSIMODE
	/* non ANSI/XOPEN/POSIX but 'standard' unix */
__SGI_LIBC_END_EXTERN_C
#include <getopt.h>
__SGI_LIBC_BEGIN_EXTERN_C
extern int atcheckpoint(void (*)(void));
extern int atrestart(void (*)(void));
extern int dup2(int, int);
extern int getpw(int, char *);
extern char *getcwd(char *, __SGI_LIBC_NAMESPACE_QUALIFIER size_t);
extern char *getlogin(void);
extern char *getpass(const char *);
extern int isatty(int);
extern void l3tol(long *, const char *, int);
extern void ltol3(char *, const long *, int);
extern void *memalign(__SGI_LIBC_NAMESPACE_QUALIFIER size_t, __SGI_LIBC_NAMESPACE_QUALIFIER size_t);
#if _NO_XOPEN4 && _NO_XOPEN5 && (defined(__INLINE_INTRINSICS) && \
        defined(_COMPILER_VERSION) && (_COMPILER_VERSION >= 710))
#pragma intrinsic (memalign)
extern void swab(const void *, void *, ssize_t);
extern char *ttyname(int);
#endif

	/* SGI extensions */
#if _COMPILER_VERSION >= 400
extern long double atold(const char *);
extern char *qecvt(long double, int, int *, int *);
extern char *qfcvt(long double, int, int *, int *);
extern char *qgcvt(long double, int, char *);
extern char *ecvtl(long double, int, int *, int *);
extern char *fcvtl(long double, int, int *, int *);
extern char *gcvtl(long double, int, char *);
#endif
#endif /* _SGIAPI */

#if _ABIAPI && _NO_ANSIMODE
__SGI_LIBC_END_EXTERN_C
#include <inttypes.h>
__SGI_LIBC_BEGIN_EXTERN_C
#endif

#if (_SGIAPI || _REENTRANT_FUNCTIONS) && _NO_ANSIMODE
extern char *ecvt_r(double, int, int *, int *, char *);
extern char *fcvt_r(double, int, int *, int *, char *);
#if _COMPILER_VERSION >= 400
extern char *qecvt_r(long double, int, int *, int *, char *);
extern char *qfcvt_r(long double, int, int *, int *, char *);
extern char *ecvtl_r(long double, int, int *, int *, char *);
extern char *fcvtl_r(long double, int, int *, int *, char *);
#endif
#endif

__SGI_LIBC_END_EXTERN_C
#endif /* _LANGUAGE_C || _LANGUAGE_C_PLUS_PLUS */

#if defined(__cplusplus) && \
     defined(_MIPS_SIM) && _MIPS_SIM != _MIPS_SIM_ABI32 && \
     defined(_COMPILER_VERSION) && (_COMPILER_VERSION >= 720) && \
     defined(__LIBC_OVERLOAD__) && __LIBC_OVERLOAD__

__SGI_LIBC_BEGIN_NAMESPACE_STD
#ifndef __sgi_cpp_abs_long_defined
#define __sgi_cpp_abs_long_defined
inline long abs(long x) {return x > 0 ? x : -x;}
#ifdef _LONGLONG
inline long long abs(long long x) {return x > 0 ? x : -x;}
#endif /* _LONGLONG */
#endif /* __sgi_cpp_abs_long_defined */

inline ldiv_t div(long x, long y) { return ldiv(x,y); }
__SGI_LIBC_END_NAMESPACE_STD

#endif /* __cplusplus && n32 && version >= 7.2 && __LIBC_OVERLOAD__ */

#endif /* !__STDLIB_CORE_H__ */
