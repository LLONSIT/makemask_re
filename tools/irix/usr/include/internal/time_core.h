#ifndef __TIME_CORE_H__
#define __TIME_CORE_H__
#ident "$Revision: 1.7 $"

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
 * WARNING - this is an ANSI/POSIX/XPG4 header. Watch for name space pollution
 */
#include <standards.h>
#include <internal/sgimacros.h>
#include <sys/types.h>
		
__SGI_LIBC_BEGIN_EXTERN_C

__SGI_LIBC_BEGIN_NAMESPACE_STD

#ifndef NULL
#define NULL	0L
#endif

#if !defined(_SIZE_T) && !defined(_SIZE_T_)
#define _SIZE_T
#if (_MIPS_SZLONG == 32)
typedef unsigned int	size_t;
#endif
#if (_MIPS_SZLONG == 64)
typedef unsigned long	size_t;
#endif
#endif 

#ifndef _CLOCK_T
#define _CLOCK_T
#if (_MIPS_SZLONG == 32)
typedef long 	clock_t;
#endif
#if (_MIPS_SZLONG == 64)
typedef int 	clock_t;
#endif
#endif 

#ifndef _TIME_T
#define _TIME_T
#if (_MIPS_SZLONG == 32)
typedef long 	time_t;
#endif
#if (_MIPS_SZLONG == 64)
typedef int 	time_t;
#endif
#endif /* !_TIME_T */

__SGI_LIBC_END_NAMESPACE_STD

__SGI_LIBC_END_EXTERN_C

#if (_POSIX93 || _ABIAPI || _XOPEN5) && _NO_ANSIMODE

#if !defined(_STANDALONE)
#include <sys/ptimers.h>
#endif
#endif /* _POSIX93 || _ABIAPI || _XOPEN5 */

#ifndef _CLOCK_ID_T
#define _CLOCK_ID_T
typedef int             clockid_t;
#endif
#ifndef _TIMER_T
#define  _TIMER_T
typedef int		timer_t;
#endif

#if _SGIAPI && _NO_ANSIMODE
#ifndef timespec_to_timeval
#define timespec_to_timeval(t, ts) \
        (t)->tv_sec = (ts)->tv_sec; \
        (t)->tv_usec = (ts)->tv_nsec / 1000;

#define timeval_to_timespec(ts, t) \
        (ts)->tv_sec = (t)->tv_sec; \
        (ts)->tv_nsec = (t)->tv_usec * 1000;
 
#endif
#ifndef NSEC_PER_SEC
#define NSEC_PER_SEC    1000000000L
#endif
#endif /* SGIAPI */

__SGI_LIBC_BEGIN_EXTERN_C

#define CLOCKS_PER_SEC		1000000

struct	tm {	/* see ctime(3) */
	int	tm_sec;
	int	tm_min;
	int	tm_hour;
	int	tm_mday;
	int	tm_mon;
	int	tm_year;
	int	tm_wday;
	int	tm_yday;
	int	tm_isdst;
};

/*
 * Std ANSI functions
 */
__SGI_LIBC_BEGIN_NAMESPACE_STD

/* C99: 7.23.2 Time manipulation functions */

extern clock_t clock(void);			
extern double difftime(time_t, time_t);		
extern time_t mktime(struct tm *);		
extern time_t time(time_t *);			

/* C99: 7.23.3 Time conversion functions */

extern char *asctime(const struct tm *);		
extern char *ctime (const time_t *);		
extern struct tm *gmtime(const time_t *);		
extern struct tm *localtime(const time_t *);	
extern size_t strftime(char * __restrict, size_t, const char * __restrict, const struct tm * __restrict);

/* SGI IRIX specific functions */
#if _NO_XOPEN4 && _NO_XOPEN5
extern uint64_t rdrtc(void);
#if !defined(_SGI_COMPILING_LIBC)
#pragma optional rdrtc
#endif /* !_SGI_COMPILING_LIBC */
#endif /* _NO_XOPEN$ && _NO_XOPEN5 */

__SGI_LIBC_END_NAMESPACE_STD

#if (_POSIX90 || _XOPEN5) && _NO_ANSIMODE
/*
 * POSIX1003.1 additions
 */
extern void tzset(void);
extern char *tzname[2];

#ifndef CLK_TCK
extern long _sysconf(int);
#define CLK_TCK	_sysconf(3)	/* clock ticks per second */
				/* 3 is _SC_CLK_TCK */
#endif /* CLK_TCK */
#endif /*  _POSIX90 */

__SGI_LIBC_END_EXTERN_C

#if ((_POSIX93 || _XOPEN5) && !defined(_STANDALONE)) && _NO_ANSIMODE
/*
 * POSIX 1003.1b-1993 clock and timer functions
 */
#include <sys/timespec.h>
__SGI_LIBC_BEGIN_EXTERN_C
#if defined(_XOPEN_SOURCE) && (_XOPEN_SOURCE+0 >= 500)
#ifndef __TIMESPEC_DEFINED
#define timespec __timespec
#endif
#endif
struct sigevent;
extern int clock_settime(clockid_t, const timespec_t *);
extern int clock_gettime(clockid_t, timespec_t *);
extern int clock_getres(clockid_t, timespec_t *);
extern int nanosleep(const timespec_t *, timespec_t *);
extern int timer_create(clockid_t, struct sigevent *, timer_t *);
extern int timer_delete(timer_t);
extern int timer_settime(timer_t, int, const struct itimerspec *, struct itimerspec *);
extern int timer_gettime(timer_t, struct itimerspec *);
extern int timer_getoverrun(timer_t);
__SGI_LIBC_END_EXTERN_C

#ifndef _SGI_COMPILING_LIBC
#pragma optional nanosleep
#endif /* !_SGI_COMPILING_LIBC */

#endif /* (_POSIX93 || _XOPEN5) && _NO_ANSIMODE */

__SGI_LIBC_BEGIN_EXTERN_C

#if (_XOPEN4 || _XOPEN5) && _NO_ANSIMODE
/*
 * XPG4 additions
 */
extern time_t timezone;
extern int daylight;
extern char *strptime(const char *, const char *, struct tm *);
#endif

#if (_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE
/*
 * XPG4-UX additions
 */
extern struct tm *getdate(const char *);
extern int getdate_err;
#endif	/* (_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE */

#if _SGIAPI && _NO_ANSIMODE
extern int cftime(char *, char *, const __SGI_LIBC_NAMESPACE_QUALIFIER time_t *);
extern int ascftime(char *, const char *, const struct tm *);
extern time_t altzone;
#endif	/* _SGIAPI */

#if _POSIX1C && _NO_ANSIMODE
/*
 * POSIX1c additions
 */
extern char *asctime_r(const struct tm *, char *);
extern char *ctime_r(const __SGI_LIBC_NAMESPACE_QUALIFIER time_t *, char *);
extern struct tm *gmtime_r(const __SGI_LIBC_NAMESPACE_QUALIFIER time_t *,
                           struct tm *);
extern struct tm *localtime_r(const __SGI_LIBC_NAMESPACE_QUALIFIER time_t *,
                              struct tm *);
#endif /* _POSIX1C */

__SGI_LIBC_END_EXTERN_C

#endif /* !__TIME_CORE_H__ */
