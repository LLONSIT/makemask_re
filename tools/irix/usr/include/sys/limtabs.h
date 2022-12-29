#ident "$Revision: 1.9 $"
/*
*
* Copyright 1999, Silicon Graphics, Inc.
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
/*
 * NOTE: Best viewed if TABS are set to 4
 */

#ifndef __LIMIT_TABLES_H__
#define __LIMIT_TABLES_H__

#include <sys/resource.h>

/* Tell the compiler not to complain about unreferenced symbols. */

#pragma set woff 1174

/* Units designation for kernel defined limit values */
#define LIM_NUMBER      0
#define LIM_BYTES       1
#define LIM_SECONDS     2

/*
 * Job Limits Cross Reference - These structs are for cross referencing the
 * job limit name with the defined job limit id.
 */
typedef struct limits_xlate_s {
    char    *lim_name;
    int     lim_id;
    int     lim_unit;
} limits_xlate_t;

/* job limits cross reference table */
static limits_xlate_t jlxtable[JLIM_NLIMITS*2+1] = {
    "jlimit_cpu_cur",       JLIMIT_CPU,		LIM_SECONDS,
    "jlimit_cpu_max",       JLIMIT_CPU,		LIM_SECONDS,
    "jlimit_data_cur",      JLIMIT_DATA,	LIM_BYTES,
    "jlimit_data_max",      JLIMIT_DATA,	LIM_BYTES,
    "jlimit_nofile_cur",    JLIMIT_NOFILE,	LIM_NUMBER,
    "jlimit_nofile_max",    JLIMIT_NOFILE,	LIM_NUMBER,
    "jlimit_vmem_cur",      JLIMIT_VMEM,	LIM_BYTES,
    "jlimit_vmem_max",      JLIMIT_VMEM,	LIM_BYTES,
    "jlimit_rss_cur",       JLIMIT_RSS,		LIM_BYTES,
    "jlimit_rss_max",       JLIMIT_RSS,		LIM_BYTES,
    "jlimit_pthread_cur",   JLIMIT_PTHREAD,	LIM_NUMBER,
    "jlimit_pthread_max",   JLIMIT_PTHREAD,	LIM_NUMBER,
    "jlimit_numproc_cur",   JLIMIT_NUMPROC,	LIM_NUMBER,
    "jlimit_numproc_max",   JLIMIT_NUMPROC,	LIM_NUMBER,
    "jlimit_physmem_cur",   JLIMIT_PMEM,	LIM_BYTES,
    "jlimit_physmem_max",   JLIMIT_PMEM,	LIM_BYTES,
    NULL, -1, -1
};

 /* process limits cross reference table */
static limits_xlate_t  rlxtable[RLIM_NLIMITS*2+1] = {
    "rlimit_cpu_cur",       RLIMIT_CPU,		LIM_SECONDS,
    "rlimit_cpu_max",       RLIMIT_CPU,		LIM_SECONDS,
    "rlimit_fsize_cur",     RLIMIT_FSIZE,	LIM_BYTES,
    "rlimit_fsize_max",     RLIMIT_FSIZE,	LIM_BYTES,
    "rlimit_data_cur",      RLIMIT_DATA,	LIM_BYTES,
    "rlimit_data_max",      RLIMIT_DATA,	LIM_BYTES,
    "rlimit_stack_cur",     RLIMIT_STACK,	LIM_BYTES,
    "rlimit_stack_max",     RLIMIT_STACK,	LIM_BYTES,
    "rlimit_core_cur",      RLIMIT_CORE,	LIM_BYTES,
    "rlimit_core_max",      RLIMIT_CORE,	LIM_BYTES,
    "rlimit_nofile_cur",    RLIMIT_NOFILE,	LIM_NUMBER,
    "rlimit_nofile_max",    RLIMIT_NOFILE,	LIM_NUMBER,
    "rlimit_vmem_cur",      RLIMIT_VMEM,	LIM_BYTES,
    "rlimit_vmem_max",      RLIMIT_VMEM,	LIM_BYTES,
    "rlimit_rss_cur",       RLIMIT_RSS,		LIM_BYTES,
    "rlimit_rss_max",       RLIMIT_RSS,		LIM_BYTES,
    "rlimit_pthread_cur",   RLIMIT_PTHREAD,	LIM_NUMBER,
    "rlimit_pthread_max",   RLIMIT_PTHREAD,	LIM_NUMBER,
    NULL, -1, -1
};

static limits_xlate_t prt_jlxtable[] = { /* Printable names for Job Limits */
	"cputime",		JLIMIT_CPU,     LIM_SECONDS,
	"datasize",		JLIMIT_DATA,	LIM_BYTES,
	"files",		JLIMIT_NOFILE,  LIM_NUMBER,
	"vmemory", 		JLIMIT_VMEM,    LIM_BYTES,
	"ressetsize",		JLIMIT_RSS,     LIM_BYTES,
	"threads",		JLIMIT_PTHREAD, LIM_NUMBER,
	"processes",		JLIMIT_NUMPROC, LIM_NUMBER,
	"physmem",		JLIMIT_PMEM, 	LIM_BYTES,
	NULL, -1, -1
};

#pragma reset woff 1174

#endif	/* __LIMIT_TABLES_H__ */
