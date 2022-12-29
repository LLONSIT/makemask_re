/**************************************************************************
 *									  *
 * 		 Copyright (C) 1996 Silicon Graphics, Inc.		  *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/

/*
 * POSIX 1b Scheduling Header File.
 */

#ifndef _SCHED_H_
#define _SCHED_H_

#ident "$Id: sched.h,v 1.3 2002/05/24 17:57:55 csturtiv Exp $"

#include <standards.h>
#include <time.h>
#include <sys/timespec.h>
#include <sys/sched.h>
#include <internal/sgimacros.h>

__SGI_LIBC_BEGIN_EXTERN_C

/*
 * Interface Prototypes
 */
int sched_setparam(pid_t, const struct sched_param *);
int sched_getparam(pid_t, struct sched_param *);
int sched_setscheduler(pid_t, int, const struct sched_param *);
int sched_getscheduler(pid_t);
int sched_yield(void);
int sched_get_priority_max(int);
int sched_get_priority_min(int);
int sched_rr_get_interval(pid_t, timespec_t *);

__SGI_LIBC_END_EXTERN_C
#endif /* _SCHED_H_ */
