/*
 * Copyright 1996-1997, Silicon Graphics, Inc.
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
#ifndef _SYS_TIMESPEC_H
#define _SYS_TIMESPEC_H
#ident	"$Revision: 1.11 $"

/*
 * timespec is part of POSIX1c - but a bunch of other non-XPG and SGI
 * things need it, so we want a definition that we can always include.
 * Note that for XPG we need to be careful - "_t"s are permitted
 * but not the word 'timespec'
 * So all users of this really should use the timespec_t rather than
 * struct timespec
 * Note that this header ONLY defines "_t"s so it is safe to include in
 * any POSIX/XPG header.
 *
 * Thus, non XPG/POSIX headers that need a timespec should include
 * this rather than (or in addition to) sys/time.h
 *
 * According to Unix98 (XOPEN5), "timespec" should be defined in time.h.
 * But we can't define it here for XOPEN5 because this header is also
 * included by other headers (i.e. sys/stat.h), and Unix98 doesn't want
 * "timespec" defined in those headers.  Thus, for XOPEN5, time.h will
 * have to typedef it to this timespec_t.
 */
#include <standards.h>
#include <sys/types.h>

#if _POSIX93 || _ABIAPI || (_XOPEN5 && defined(__TIME_H__))
/*
 * POSIX93 and SGI get timespec, but not _XOPEN4
 * Unix98 (_XOPEN5) expects timespec to be defined in time.h
 */
#define __timespec timespec
#ifndef __TIMESPEC_DEFINED
#define __TIMESPEC_DEFINED
#endif
#endif

typedef struct __timespec {
#ifdef tv_sec
	time_t  __tv_sec;	/* seconds */
#else
	time_t  tv_sec;		/* seconds */
#endif
#ifdef tv_nsec
	long    __tv_nsec;
#else
	long    tv_nsec;
#endif
} timespec_t;

#endif	/* _SYS_TIMESPEC_H */
