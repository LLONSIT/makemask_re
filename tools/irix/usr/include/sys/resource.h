/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)resource.h	7.1 (Berkeley) 6/4/86
 */
#ifndef _SYS_RESOURCE_H
#define _SYS_RESOURCE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>
#include <sgidefs.h>
#include <sys/types.h>

/*
 * from sys/time.h
 */
#ifndef _TIMEVAL_T
#define _TIMEVAL_T
struct timeval {
#if _MIPS_SZLONG == 64
	__int32_t :32;
#endif
        time_t  tv_sec;         /* seconds */
        long    tv_usec;        /* and microseconds */
};

/*
 * Since SVID API explicitly gives timeval struct to contain longs ...
 * Thus need a second timeval struct for 64bit binaries to correctly
 * access specific files (ie. struct utmpx in utmpx.h).
 */
struct __irix5_timeval {
        __int32_t    tv_sec;         /* seconds */
        __int32_t    tv_usec;        /* and microseconds */
};
#endif /* _TIMEVAL_T */

/*
 * Process priority specifications to get/setpriority.
 */
#define	PRIO_MIN	-20
#define	PRIO_MAX	20

#define	PRIO_PROCESS	0
#define	PRIO_PGRP	1
#define	PRIO_USER	2

/*
 * Resource utilization information.
 */

#define	RUSAGE_SELF	0
#define	RUSAGE_CHILDREN	-1

struct	rusage {
	struct timeval ru_utime;	/* user time used */
	struct timeval ru_stime;	/* system time used */
#if _ABIAPI
	long	ru_pad[14];
#else
	long	ru_maxrss;
#define	ru_first	ru_ixrss
	long	ru_ixrss;		/* integral shared memory size */
	long	ru_idrss;		/* integral unshared data " */
	long	ru_isrss;		/* integral unshared stack " */
	long	ru_minflt;		/* page reclaims */
	long	ru_majflt;		/* page faults */
	long	ru_nswap;		/* swaps */
	long	ru_inblock;		/* block input operations */
	long	ru_oublock;		/* block output operations */
	long	ru_msgsnd;		/* messages sent */
	long	ru_msgrcv;		/* messages received */
	long	ru_nsignals;		/* signals received */
	long	ru_nvcsw;		/* voluntary context switches */
	long	ru_nivcsw;		/* involuntary " */
#define	ru_last		ru_nivcsw
#endif	/* _ABIAPI */
};

/*
 * Resource limits
 */
#define	RLIMIT_CPU	0		/* cpu time in seconds */
#define	RLIMIT_FSIZE	1		/* maximum file size */
#define	RLIMIT_DATA	2		/* data size */
#define	RLIMIT_STACK	3		/* stack size */
#define	RLIMIT_CORE	4		/* core file size */
#define RLIMIT_NOFILE	5		/* file descriptors */
#define RLIMIT_VMEM	6		/* maximum mapped memory */
#define	RLIMIT_RSS	7		/* resident set size */
#define RLIMIT_AS	RLIMIT_VMEM
#define	RLIMIT_PTHREAD	8		/* pthreads */

#define	RLIM_NLIMITS	9		/* number of resource limits */


#ifdef _KERNEL
#define RLIM_INFINITY	0x7fffffffffffffffLL
#define	RLIM32_INFINITY	0x7fffffff
#elif (_MIPS_SZLONG == 64) || (_MIPS_SIM == _ABIN32)
#define	RLIM_INFINITY	0x7fffffffffffffffLL
#else
#define	RLIM_INFINITY	0x7fffffff
#endif /* _KERNEL */

#if _LFAPI
#define	RLIM64_SAVED_CUR	0x7ffffffffffffffdLL
#define	RLIM64_SAVED_MAX	0x7ffffffffffffffeLL
#define	RLIM64_INFINITY		0x7fffffffffffffffLL
#endif	/* _LFAPI */

#if _LFAPI || _XOPEN5
#define	RLIM_SAVED_CUR		0x7ffffffd
#define	RLIM_SAVED_MAX		0x7ffffffe
#endif

#ifdef _KERNEL
typedef __uint64_t rlim_t;
#elif _MIPS_SIM == _ABIN32
typedef __uint64_t rlim_t;
#else
typedef unsigned long rlim_t;
#endif

struct rlimit {
	rlim_t	rlim_cur;		/* current (soft) limit */
	rlim_t	rlim_max;		/* maximum value for rlim_cur */
};

#if _LFAPI
typedef __uint64_t rlim64_t;

struct rlimit64 {
	rlim64_t	rlim_cur;
	rlim64_t	rlim_max;		
};		
#endif	/* _LFAPI */

#if (_NO_POSIX && _NO_XOPEN4 && _NO_XOPEN5)
/*
 * Job Limits (not defined when standards enforced )
 */

#define	JLIMIT_CPU	0		/* cpu time in seconds */
#define	JLIMIT_DATA	1		/* data size */
#define	JLIMIT_VMEM	2		/* maximum mapped memory */
#define	JLIMIT_RSS	3		/* resident set size */
#define	JLIMIT_NOFILE	4		/* file descriptors */
#define	JLIMIT_PTHREAD 	5		/* max nom of pthreads */
#define	JLIMIT_NUMPROC	6		/* max number of processes */
#define JLIMIT_PMEM	7		/* physical memory */

#define JLIM_NLIMITS	8

/* 
 * Job limits enforcement flags 
 *	The enforcement actions flags begin at lowest value (0x1) and work
 *	their way up the bits.  The enforcement ignored flags begin at the 
 *	highest value and work their way down the bits.
 */
	/* flags indicate the enforcement action taken */
#define	JL_CPU_SIGXCPU	0x00000001	/* cpu enforcement SIGXCPU flag */
#define	JL_CPU_SIGKILL	0x00000002	/* cpu enforcement SIGKILL flag */
#define	JL_DATA		0x00000004	/* data size enforcement flag */
#define	JL_VMEM		0x00000008	/* mapped memory enforcement flag */
#define	JL_RSS		0x00000010	/* rss enforcement flag */
#define	JL_NOFILE	0x00000020	/* file descriptors enforcement flag */
#define	JL_PTHREAD	0x00000040	/* pthreads enforcement flag */
#define	JL_NUMPROC	0x00000080	/* num processes enforcement flag */
#define	JL_PMEM		0x00000100	/* physcial memory enforcement flag */
	/* flags indicate that enforcement of certain limits is ignored */
#define JL_PMEM_IGN	0x0100000000000000	/* ignore phys mem  limit */
#define JL_NUMPROC_IGN	0x0200000000000000	/* ignore num procs limit */
#define JL_PTHREAD_IGN	0x0400000000000000	/* ignore num pthread limit */
#define JL_NOFILE_IGN	0x0800000000000000	/* ignore num files limit */
#define JL_RSS_IGN	0x1000000000000000	/* ignore rss limit */
#define JL_VMEM_IGN	0x2000000000000000	/* ignore virt mem limit */
#define JL_DATA_IGN	0x4000000000000000	/* ignore data (heap) limit */
#define JL_CPU_IGN	0x8000000000000000	/* ignore CPU time limit */
 
/* Checks for set bits on ignored enforcement of certain limits */
#define jlimit_ign_pmem(jt)     (jt->job_limitflag & JL_PMEM_IGN)
#define jlimit_ign_numproc(jt)  (jt->job_limitflag & JL_NUMPROC_IGN)
#define jlimit_ign_pthread(jt)  (jt->job_limitflag & JL_PTHREAD_IGN)
#define jlimit_ign_nofile(jt)   (jt->job_limitflag & JL_NOFILE_IGN)
#define jlimit_ign_rss(jt)      (jt->job_limitflag & JL_RSS_IGN)
#define jlimit_ign_vmem(jt)     (jt->job_limitflag & JL_VMEM_IGN)
#define jlimit_ign_data(jt)     (jt->job_limitflag & JL_DATA_IGN)
#define jlimit_ign_cpu(jt)      (jt->job_limitflag & JL_CPU_IGN)



struct jobrusage {
	rlim_t	usage;			/* Current amount of resource used. */
	rlim_t	high_usage;		/* Maximum usage ever used. */
};

typedef struct jres_s {
	rlim_t	limit_cur;		/* enforced limit */
	rlim_t	limit_max;		/* maximum limit */
	rlim_t	usage;			/* amount of resource used */
	rlim_t	high_usage;		/* maximum usage ever used */
} jres_t;

typedef struct job_info_s {
	jid_t		job_id;			/* Job ID */
	__int64_t	job_limitflag;		/* limit enforcement flag */
	uid_t		job_uid;		/* uid of job initiator */
	time_t		job_start;		/* time of job start */
	__int64_t	fill1[2];		/* room to grow */
	jres_t		job_data[JLIM_NLIMITS];	/* job usage and limit data */
	__int64_t	fill2[8];		/* room to grow */
} job_info_t;

#endif	/* (_NO_POSIX && _NO_XOPEN4 && _NO_XOPEN5) */

#ifdef _KERNEL

#include <sys/types.h>

/*
 * Convert the given 32 bit limit spec to RLIM_INFINITY if it
 * is specified as RLIM32_INFINITY.
 */
#define	RLIM32_CONV(x)	(((x) == RLIM32_INFINITY) ? RLIM_INFINITY : (x))

struct uthread_s;
union rval;

extern void ruadd(struct rusage *, struct rusage *);
extern int setrlimitcommon(usysarg_t, struct rlimit *);
extern rlim_t getaslimit(struct uthread_s *, int);
extern rlim_t getfsizelimit(void);
extern struct rlimit rlimits[];
extern int syssgi_getjid(jid_t *);
extern int syssgi_getjlimit(jid_t, int, struct rlimit *);
extern int syssgi_setjlimit(jid_t, int, struct rlimit *);
extern int syssgi_killjob(jid_t, int);
extern int syssgi_makenewjob(jid_t, int, jid_t *);
extern int syssgi_getjobpid(jid_t, pid_t *, int, union rval *);
extern int syssgi_getjusage(jid_t, int, struct jobrusage *);
extern int syssgi_setjusage(jid_t, int, struct jobrusage *);
extern int syssgi_joinjob(jid_t);
extern int syssgi_setwaitjobpid(jid_t, pid_t);
extern int syssgi_waitjob(job_info_t *, jid_t *);

struct irix5_rlimit {
	app32_ulong_t	rlim_cur;
	app32_ulong_t	rlim_max;
};

struct irix5_jobrusage {
	app32_ulong_t	usage;
	app32_ulong_t	high_usage;
};

typedef struct irix5_jres_s {
      app32_ulong_t   limit_cur;              /* enforced limit */
      app32_ulong_t   limit_max;              /* maximum limit */
      app32_ulong_t   usage;                  /* amount of resource used */
      app32_ulong_t   high_usage;             /* maximum usage ever used */
} irix5_jres_t;

typedef struct irix5_job_info_s {
	jid_t		job_id;			/* Job ID */
	__int64_t	job_limitflag;		/* limit enforcement flag */
	uid_t		job_uid;		/* uid of job initiator */
	time_t		job_start;		/* time of job start */
	__int64_t	fill1[2];		/* room to grow */
	irix5_jres_t	job_data[JLIM_NLIMITS];	/* job usage and limit data */
	__int64_t	fill2[8];		/* room to grow */
} irix5_job_info_t;

#else	/* !_KERNEL */

extern int getrlimit(int, struct rlimit *);
extern int setrlimit(int, const struct rlimit *);
extern int getpriority(int, id_t);
extern int setpriority(int, id_t, int);
extern int getrusage(int, struct rusage *);

#if (_NO_POSIX && _NO_XOPEN4 && _NO_XOPEN5)
extern jid_t	getjid(void);
extern int	getjlimit(jid_t, int, struct rlimit *);
extern int	getjusage(jid_t, int, struct jobrusage *);
extern int	setjusage(jid_t, int, struct jobrusage *);
extern jid_t	jlimit_startjob(char *, uid_t, char *);
extern int	killjob(jid_t, int);
extern jid_t	makenewjob(jid_t, uid_t);
extern int	setjlimit(jid_t, int, struct rlimit *);
extern int	setwaitjobpid(jid_t, pid_t);
extern jid_t	waitjob(job_info_t *);

#if !defined(_SGI_COMPILING_LIBC)
#pragma optional getjid
#pragma optional getjlimit
#pragma optional getjusage
#pragma optional setjusage
#pragma optional jlimit_startjob
#pragma optional killjob
#pragma optional makenewjob
#pragma optional setjlimit
#pragma optional setwaitjobpid
#pragma optional waitjob
#endif

#endif

#if _LFAPI
extern int getrlimit64(int, struct rlimit64 *);
extern int setrlimit64(int, const struct rlimit64 *);
#endif	/* _LFAPI */

#endif /* !_KERNEL */

#ifdef __cplusplus
}
#endif

#endif /* _SYS_RESOURCE_H */
