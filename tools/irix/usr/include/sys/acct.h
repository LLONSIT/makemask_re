/*	Copyright (c) 1990, 1991 UNIX System Laboratories, Inc.	*/
/*	Copyright (c) 1984, 1986, 1987, 1988, 1989, 1990 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF     	*/
/*	UNIX System Laboratories, Inc.                     	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#ifndef _PROC_ACCT_H	/* wrapper symbol for kernel use */
#define _PROC_ACCT_H	/* subject to change without notice */

#ifdef __cplusplus
extern "C" {
#endif

/*#ident	"@(#)uts-3b2:proc/acct.h	1.4"*/
#ident	"$Revision: 3.22 $"
/*
 * Accounting structures
 *
 * NOTE: These structures apply only to the BSD-style process
 *	 accounting and Comprehensive System Accounting (CSA).
 *	 Structures for the IRIX extended accounting (process and
 *	 session accounting) can be found in extacct.h and sat.h.
 */
#include <sys/types.h>
#include <sys/cdefs.h>

typedef	ushort_t comp_t;  /* "floating point" 13-bit fraction,
	     * 3-bit exponent; decode using the formula:
	     *    val_in_Hz = (comp_t & 0x1fff) << (3 * (comp_t >> 13))
	     */

/* Max number representable by a comp_t */
#if _MIPS_SZLONG == 32
#define MAX_COMP_T MAXLONG           /* 0xffffffff */
#endif
#if _MIPS_SZLONG == 64
#define MAX_COMP_T 17177772032L      /* 0x1fff * 8**7 */
#endif

/* SVR4 acct structure */
struct	acct
{
	char	ac_flag;	/* Accounting flag */
	char	ac_stat;	/* Exit status */
	uid_t	ac_uid;		/* Accounting user ID */
	gid_t	ac_gid;		/* Accounting group ID */
	dev_t	ac_tty;		/* control typewriter */
	time_t	ac_btime;	/* Beginning time */
	comp_t	ac_utime;	/* acctng user time in clock ticks */
	comp_t	ac_stime;	/* acctng system time in clock ticks */
	comp_t	ac_etime;	/* acctng elapsed time in clock ticks */
	comp_t	ac_mem;		/* memory usage */
	comp_t	ac_io;		/* chars transferred */
	comp_t	ac_rw;		/* blocks read or written */
	char	ac_comm[8];	/* command name */
};	

/*
 * Account commands will use this header to read SVR3 accounting data files.
 */
struct	o_acct
{
	char	ac_flag;	/* Accounting flag */
	char	ac_stat;	/* Exit status */
	o_uid_t	ac_uid;		/* Accounting user ID */
	o_gid_t	ac_gid;		/* Accounting group ID */
	o_dev_t	ac_tty;		/* control typewriter */
	time_t	ac_btime;	/* Beginning time */
	comp_t	ac_utime;	/* acctng user time in clock ticks */
	comp_t	ac_stime;	/* acctng system time in clock ticks */
	comp_t	ac_etime;	/* acctng elapsed time in clock ticks */
	comp_t	ac_mem;		/* memory usage */
	comp_t	ac_io;		/* chars transferred */
	comp_t	ac_rw;		/* blocks read or written */
	char	ac_comm[8];	/* command name */
};


/*
 * Record flags - some are for acct.ac_flag, some are for achead.ah_flag,
 *                some are for both.
 */
#define	AFORK	0001	/* Has executed fork, but no exec */
#define	ASU	0002	/* Used privilege */
#define AMORE	0010	/* There are more acct records for this process */
#define AINC	0020	/* Incremental accounting structure */
#define AEXPND	0040	/* Expanded acct structure - SV4<-SV3 */
#define	ACCTF	0300	/* Record type: 00 = acct */

/*
 * Magic number - for achead.ah_magic in the 1st header.  The magic number
 *                in the 2nd header is the inverse of this.
 */
#define ACCT_MAGIC_BIG		030510	/* IRIX big-endian */
#define ACCT_MAGIC_LITTLE	030512	/* SV2 little-endian */
#define ACCT_MAGIC ACCT_MAGIC_BIG

/*
 * Record types - for achead.ah_type in the 1st header.
 */
#define	ACCT_KERNEL_CSA		0001	/* Kernel: CSA base record */
#define	ACCT_KERNEL_MEM		0002	/* Kernel: memory record */
#define	ACCT_KERNEL_IO		0004	/* Kernel: input/output record */
#define	ACCT_KERNEL_MT 		0006	/* Kernel: multi-tasking record */
#define	ACCT_KERNEL_MPP		0010	/* Kernel: multi-PE appl record */
#define	ACCT_KERNEL_SOJ		0012	/* Kernel: start-of-job record */
#define	ACCT_KERNEL_EOJ		0014	/* Kernel: end-of-job record */
#define	ACCT_KERNEL_CFG		0020	/* Kernel: configuration record */
#define	ACCT_KERNEL_SGI1	0040	/* Kernel: SGI reserved */
#define	ACCT_KERNEL_SGI2	0042	/* Kernel: SGI reserved */

#define	ACCT_KERNEL_SITE0	0100	/* Kernel: reserved for site */
#define	ACCT_KERNEL_SITE1	0101	/* Kernel: reserved for site */
#define	ACCT_KERNEL_SITE2	0102	/* Kernel: reserved for site */
#define	ACCT_KERNEL_SITE3	0103	/* Kernel: reserved for site */
#define	ACCT_KERNEL_SITE4	0104	/* Kernel: reserved for site */
#define	ACCT_KERNEL_SITE5	0105	/* Kernel: reserved for site */
#define	ACCT_KERNEL_SITE6	0106	/* Kernel: reserved for site */
#define	ACCT_KERNEL_SITE7	0107	/* Kernel: reserved for site */

#define	ACCT_DAEMON_NQS		0120	/* Daemon: NQS record */
#define	ACCT_DAEMON_WKMG      	0122	/* Daemon: workload management record,
					           i.e., LSF */
#define	ACCT_DAEMON_TAPE	0124	/* Daemon: tape record */
#define	ACCT_DAEMON_DMIG	0126	/* Daemon: data migration record */
#define	ACCT_DAEMON_SOCKET	0130	/* Daemon: socket record */
#define	ACCT_DAEMON_SGI1	0150	/* Daemon: SGI reserved */
#define	ACCT_DAEMON_SGI2	0152	/* Daemon: SGI reserved */

#define	ACCT_DAEMON_SITE0	0200	/* Daemon: reserved for site */
#define	ACCT_DAEMON_SITE1	0201	/* Daemon: reserved for site */
#define	ACCT_DAEMON_SITE2	0202	/* Daemon: reserved for site */
#define	ACCT_DAEMON_SITE3	0203	/* Daemon: reserved for site */
#define	ACCT_DAEMON_SITE4	0204	/* Daemon: reserved for site */
#define	ACCT_DAEMON_SITE5	0205	/* Daemon: reserved for site */
#define	ACCT_DAEMON_SITE6	0206	/* Daemon: reserved for site */
#define	ACCT_DAEMON_SITE7	0207	/* Daemon: reserved for site */

#define	ACCT_JOB_HEADER		0220	/* csabuild: job header record */
#define	ACCT_CACCT		0222	/* cacct:    consolidated data */
#define	ACCT_CMS		0224	/* cms:      command summary data */

/*
 * Record types - for achead.ah_type in the 2nd header.
 */
#define	ACCT_MEM	1<<0	/* Process generated memory record */
#define	ACCT_IO		1<<1	/* Process generated I/O record */
#define	ACCT_MT		1<<2	/* Process used multi-tasking */
#define	ACCT_MPP	1<<3	/* Process used multi-PE */

/*
 * Record revision levels.
 *
 * These are incremented to indicate that a record's format has changed since
 * a previous release.  We use 6570 as a starting point because CSA is first
 * released in IRIX 6.5.7.
 */
#define	REV_CSA		06570	/* Kernel: CSA base record */
#define	REV_MEM		06570	/* Kernel: memory record */
#define	REV_IO		06570	/* Kernel: I/O record */
#define	REV_MT 		06570	/* Kernel: multi-tasking record */
#define	REV_MPP		06570	/* Kernel: multi-PE appl record */
#define	REV_SOJ		06570	/* Kernel: start-of-job record */
#define	REV_EOJ		06570	/* Kernel: end-of-job record */
#define	REV_CFG		06570	/* Kernel: configuration record */
#define REV_K_SGI1	06570	/* Kernel: SGI reserved */
#define REV_K_SGI2	06570	/* Kernel: SGI reserved */

#define REV_NQS		06570 	/* Daemon: NQS record */
#define REV_WKMG	06570 	/* Daemon: workload management (i.e., LSF)
				           record */
#define REV_TAPE	06570	/* Daemon: tape record */
#define REV_DMIG	06570	/* Daemon: data migration record */
#define REV_SOCKET	06570	/* Daemon: socket record */
#define REV_D_SGI1	06570	/* Daemon: SGI reserved */
#define REV_D_SGI2	06570	/* Daemon: SGI reserved */

#define REV_JOB		06570	/* csabuild: job header record */
#define REV_CACCT	06570	/* cacct:    consolidated data */
#define REV_CMS		06570	/* cms:      command summary data */


/* CSA structures */

/*
 * Record header
 *
 */
struct achead
{
	unsigned int	ah_magic:17;	/* Magic */
	unsigned int	ah_revision:15;	/* Revision */
	unsigned int	ah_type:8;	/* Record type */
	unsigned int	ah_flag:8;	/* Record flags */
	unsigned int	ah_size:16;	/* Size of record */
};

/*
 * Per process base accounting record.
 *
 */
struct acctcsa
{
	struct achead	ac_hdr1;	/* Header */
	struct achead	ac_hdr2;	/* 2nd header for continued records */ 

	double 		ac_sbu;		/* System billing units */

	unsigned int	ac_stat:8;	/* Exit status */
	unsigned int	ac_nice:8;	/* Nice value */
	unsigned char	ac_sched;	/* Scheduling discipline */
	unsigned int	:8;		/* Unused */
	dev_t		ac_tty;		/* Control typewriter */
	
	uid_t		ac_uid;		/* User ID */
	gid_t		ac_gid;		/* Group ID */

	ash_t		ac_ash;		/* Array session handle */
	jid_t		ac_jid;		/* Job ID */
	prid_t		ac_prid;	/* Project ID -> account ID */

	pid_t		ac_pid;		/* Process ID */
	pid_t		ac_ppid;	/* Parent process ID */

	int64_t		ac_appid;	/* Application ID - not used */

	time_t		ac_btime;	/* Beginning time [sec since 1970] */
	
	char		ac_comm[16];	/* Command name */
	
	int		ac_spare2;	/* Spare field */

/*	CPU resource usage information. */
	uint64_t	ac_qwtime;	/* Run queue wait time [usecs] */
	uint64_t	ac_etime;	/* Elapsed time [usecs] */
	uint64_t	ac_ctime;	/* Process connect time [usecs] -
					   currently not used */

	uint64_t	ac_utime;	/* User CPU time [usec] */
	uint64_t	ac_stime;	/* System CPU time [usec] */
	uint64_t	ac_spare;	/* Spare field */
};

/*
 * Memory accounting structure
 *
 * This structure is part of the acctmem record.
 */
struct memint
{
	uint64_t	himem;	/* High-water memory usage value [Kbytes] */
	uint64_t	mem1;	/* Memory integral 1 [Mbytes/uSec] */
	uint64_t	mem2;	/* Memory integral 2 [Mbytes/uSec] - not used */
	uint64_t	mem3;	/* Memory integral 3 [Mbytes/uSec] - not used */
};

/*
 * Memory accounting record
 *
 */
struct acctmem
{
	struct achead	ac_hdr;		/* Header */

	double 		ac_sbu;		/* System billing units */

	struct memint	ac_core;	/* Core memory integrals */
	struct memint	ac_virt;	/* Virtual memory integrals */
	
	uint64_t	ac_pgswap;	/* # of pages swapped - not used */
	uint64_t	ac_swaps;	/* Number of swaps - not used */
	uint64_t	ac_spare;	/* Spare field */
};

/*
 * Input/Output accounting record
 *
 */
struct acctio
{
	struct achead	ac_hdr;		/* Header */

	double 		ac_sbu;		/* System billing units */

	uint64_t	ac_bwtime;	/* Block I/O wait time [usecs] */
	uint64_t	ac_rwtime;	/* Raw I/O wait time [usecs] */
	uint64_t	ac_chr; 	/* Number of chars (bytes) read */

	uint64_t	ac_chw;		/* Number of chars (bytes) written */
	uint64_t	ac_bkr;		/* Number of blocks read */
	uint64_t	ac_bkw;		/* Number of blocks written */

	uint64_t	ac_scr;		/* Number of read system calls */
	uint64_t	ac_scw;		/* Number of write system calls */
	uint64_t	ac_spare;	/* Spare field */
};

/*
 * Multi-tasking accounting structure
 *
 * This structure is part of the acctmt record.
 */
struct mtask
{
	uint64_t	mt;		/* CPU+1 connect time [usecs] */
	uint64_t	spare1;		/* Spare field */
	uint64_t	spare2;		/* Spare field */
};

/*
 * Multi-tasking accounting record - currently not used, adapted from UNICOS.
 *
 */
#define	ACCT_MAXCPUS	512	/* Maximum number of CPUs supported */

struct acctmt
{
	struct achead	ac_hdr;		/* Header */

	double 		ac_sbu;		/* System billing units */

	unsigned int	ac_numcpu:16;	/* Max number of CPUs used */
	unsigned int	ac_maxcpu:16;	/* Max number of CPUs available -
					   might not need */
	unsigned int	:32;		/* Unused */
	int64_t		ac_smwtime;	/* Semaphore wait time [usec] */

	struct mtask	ac_mttime[ACCT_MAXCPUS]; /* Time connected to (i+1)
						    CPUs [usec] */
};

/*
 * MPP PE accounting structure - MPP hardware specific.
 *
 * This structure is part of the acctmpp record.
 */
struct acctpe
{
	uint64_t	utime;		/* User CPU time [usecs] */
	uint64_t	srtime;		/* System & remote CPU time [usecs] */
	uint64_t	io;		/* Number of chars transferred */
};

/*
 * MPP accounting record - MPP hardware specific, taken from UNICOS/mk.
 *
 */
#define	ACCT_MAXPES	4096	/* Maximum number of PEs */

struct acctmpp
{
	struct achead 	ac_hdr;		/* Header */

	double 		ac_sbu;		/* System billing units */

	unsigned int	ac_mpbesu:8;	/* Number of BESUs used	*/
	unsigned int	ac_mppe:24;	/* Number of PEs used */
	uint64_t	ac_himem;	/* Maximum memory hiwater [Mbytes] */

	struct acctpe	ac_mpp[ACCT_MAXPES];	/* Per PE information */
};

/*
 * MPP Detailed PE accounting structure - MPP hardware specific.
 *
 */
struct acctdpe
{
	struct achead 	ac_hdr;		/* Header */

	uint64_t	utime;		/* User CPU time [usecs] */
	uint64_t	stime;		/* System CPU time [usecs] */
	uint64_t	rtime;		/* Remote CPU time [usecs] */

	uint64_t	ctime;		/* Connect CPU time [usecs] */
	uint64_t	io;		/* Number of chars transferred */
	uint64_t	spare;		/* Spare field */
};

/*
 * Start-of-job record
 *
 * Written when a job is initiated.
 */
typedef	enum
{
	AC_INIT_LOGIN, 		/* Initiated by login */
	AC_INIT_NQS,		/* Initiated by NQS */
	AC_INIT_LSF,		/* Initiated by LSF */
	AC_INIT_CROND,		/* Initiated by crond */
	AC_INIT_FTPD,		/* Initiated by ftpd */
	AC_INIT_INETD,		/* Initiated by inetd */
	AC_INIT_TELNETD,	/* Initiated by telnetd */
	AC_INIT_MAX
} ac_inittype;

#define AC_SOJ	1	/* Start-of-job record type */
#define AC_ROJ	2	/* Restart-of-job record type */

struct acctsoj
{
	struct achead 	ac_hdr;		/* Header */

	unsigned int	ac_type:8;	/* Record type (AC_SOJ, AC_ROJ) */
	ac_inittype	ac_init:8;	/* Initiator - currently not used */
	unsigned int	:16;		/* Unused */

	uid_t		ac_uid;		/* User ID */
	jid_t		ac_jid;		/* Job ID */

	time_t	 	ac_btime;	/* Start time [secs since 1970] */
	time_t	 	ac_rstime;	/* Restart time [secs since 1970] */
};

/*
 * End-of-job record
 *
 * Written when the last process exits.
 */
struct accteoj
{
	struct achead	ac_hdr1;	/* Header */ 
	struct achead	ac_hdr2;	/* 2nd header for continued records */ 

	double 		ac_sbu;		/* System billing units */

	ac_inittype	ac_init:8;	/* Initiator - currently not used */
	unsigned int	ac_nice:8;	/* Nice value */
	unsigned int	:16;		/* Unused */
	dev_t		ac_tty;		/* Control typewriter */
	
	uid_t		ac_uid;		/* User ID */
	gid_t		ac_gid;		/* Group ID */

	ash_t		ac_ash;		/* Array session handle; not used */
	jid_t		ac_jid;		/* Job ID */
	prid_t		ac_prid;	/* Project ID -> account ID; not used */

	time_t	 	ac_btime;	/* Job start time [secs since 1970] */
	time_t  	ac_etime;	/* Job end time   [secs since 1970] */

	uint64_t	ac_corehimem;	/* High-water core memory [Kbytes] */
	uint64_t	ac_virthimem;	/* High-water virtual mem [Kbytes] */
	
/*	CPU resource usage information. */
	uint64_t	ac_qwtime;	/* Run queue wait time [usecs] -
					   currently not used */
	uint64_t	ac_ctime;	/* Process connect time [usecs] -
					   currently not used */

	uint64_t	ac_utime;	/* User CPU time [usec] - not used */
	uint64_t	ac_stime;	/* System CPU time [usec] - not used */
};

/*
 * Accounting configuration uname structure
 *
 * This structure is part of the acctcfg record.
 */
struct ac_utsname
{
	char	 sysname[9];
	char	 nodename[9];
	char	 release[24];
	char	 version[9];
	char	 machine[9];
};

/*
 * Accounting configuration record
 *
 * Written upon accounting configuration changes.
 */
typedef	enum
{
	AC_CONFCHG_BOOT,	/* Boot time (always first) */
	AC_CONFCHG_FILE,	/* Reporting pacct file change */
	AC_CONFCHG_ON,		/* Reporting xxx ON */
	AC_CONFCHG_OFF,		/* Reporting xxx OFF */
	AC_CONFCHG_INC_DELTA,	/* Report incremental accounting clock delta
				   change */
	AC_CONFCHG_INC_EVENT,	/* Report incremental accounting event */
	AC_CONFCHG_MAX
} ac_eventtype;

struct acctcfg
{
	struct achead	ac_hdr;		/* Header */

	unsigned int	ac_kdmask;	/* Kernel and daemon config mask */
	unsigned int	ac_rmask;	/* Record configuration mask */

	int64_t		ac_uptimelen;	/* Bytes from the end of the boot
					   record to the next boot record */
	ac_eventtype	ac_event:8;	/* Accounting configuration event */
	unsigned int	:24;		/* Unused */

	time_t		ac_boottime;	/* System boot time [secs since
					   1970] */
	time_t		ac_curtime;	/* Current system time [secs since
					   1970] */

	struct ac_utsname  ac_uname;	/* Condensed uname information */
};


/*
 * Accounting control status values.
 */
typedef	enum
{
	ACS_OFF,	/* Accounting stopped for this entry */
	ACS_ERROFF,	/* Accounting turned off by kernel */
	ACS_ON		/* Accounting started for this entry */
} ac_status;

/*
 * Function codes for acctctl(int, void *) system call.
 */
typedef	enum
{
	AC_START,	/* Start kernel, daemon, or record accounting */
	AC_STOP,	/* Stop kernel, daemon, or record accounting */
	AC_HALT,	/* Stop all kernel, daemon, and record accounting */
	AC_CHECK,	/* Check a kernel, daemon, or record accounting
			   state */
	AC_KDSTAT,	/* Check all kernel & daemon accounting states */
	AC_RCDSTAT,	/* Check all record accounting states */
	AC_JASTART,	/* Start user job accounting  */
	AC_JASTOP,	/* Stop user job accounting */
	AC_WRACCT,	/* Write accounting record for daemon */
	AC_AUTH,	/* Verify executing user is authorized */
	AC_INCACCT,	/* Control incremental accounting */
	AC_MREQ
} ac_request;

/*
 * Define the acctctl(int, void *) accounting record indices.
 */
typedef	enum
{
	ACCT_KERN_CSA,		/* Kernel CSA accounting */
	ACCT_KERN_JOB_PROC,	/* Kernel job process summary accounting */
	ACCT_KERN_ASH,		/* Kernel array session summary accounting */
	ACCT_DMD_NQS, 		/* Daemon NQS accounting */
	ACCT_DMD_WKMG, 		/* Daemon workload management (i.e., LSF)
				   accounting */
	ACCT_DMD_TAPE,		/* Daemon tape accounting */
	ACCT_DMD_DMIG,		/* Daemon data migration accounting */
	ACCT_DMD_SOCKET,	/* Daemon socket accounting */
	ACCT_DMD_SGI1,		/* SGI  reserved daemon acct */
	ACCT_DMD_SGI2,		/* SGI  reserved daemon acct */
	ACCT_DMD_SITE1,		/* Site reserved daemon acct */
	ACCT_DMD_SITE2,		/* Site reserved daemon acct */
	ACCT_MAXKDS,		/* Max # kernel and daemon entries */

	ACCT_RCD_MPPDET,	/* Record acct for MPP detail exit info */
	ACCT_RCD_MEM,		/* Record acct for memory */
	ACCT_RCD_IO,		/* Record acct for input/output */
	ACCT_RCD_MT,		/* Record acct for multi-tasking */
	ACCT_RCD_MPP,		/* Record acct for MPP accumulated info */
	ACCT_THD_MEM,		/* Record acct for memory size threshhold */
	ACCT_THD_TIME,		/* Record acct for CPU time threshhold */
	ACCT_RCD_INCACCT,	/* Record acct for incremental accounting */
	ACCT_RCD_APPACCT,	/* Record acct for application accounting */
	ACCT_RCD_SGI1,		/* SGI  reserved record acct */
	ACCT_RCD_SGI2,		/* SGI  reserved record acct */
	ACCT_RCD_SITE1,		/* Site reserved record acct */
	ACCT_RCD_SITE2,		/* Site reserved record acct */
	ACCT_MAXRCDS		/* Max # record entries */
} ac_kdrcd;

#define	ACCT_RCDS	ACCT_RCD_MPPDET /* Record acct low range definition */
#define	NUM_KDS		(ACCT_MAXKDS - ACCT_KERN_CSA)
#define	NUM_RCDS	(ACCT_MAXRCDS - ACCT_RCDS)
#define	NUM_KDRCDS	(NUM_KDS + NUM_RCDS)


/*
 * The following structures are used by the acctctl system call.
 */

/*
 * Accounting entry status structure
 */
struct actstat
{
	ac_kdrcd	ac_ind;		/* Entry index */
	ac_status	ac_state;	/* Entry status */
	int64_t		ac_param;	/* Entry parameter */
};

/*
 * Accounting control and status structure
 */
#define	ACCT_PATH	128	/* Max path length for accounting file */

struct actctl
{
	int	ac_sttnum;		/* Number of status array entries */
	char	ac_path[ACCT_PATH];	/* Path name for accounting file */
	struct actstat	ac_stat[NUM_KDRCDS];	/* Entry status array */
};

/*
 * Function codes for incremental accounting
 */
typedef	enum
{
	IA_NONE,	/* Zero entry place holder */
	IA_DELTA,	/* Change clock delta for incremental accounting */
	IA_EVENT,	/* Cause incremental accounting event now */
	IA_MAX
} ac_iafnc;

/*
 * Incremental accounting structure
 */
struct actinc
{
	int		ac_ind;		/* Entry index */
	ac_iafnc	ac_fnc;		/* Entry function */
	int64_t		ac_param;	/* Entry parameter */
};

/*
 * Daemon write accounting structure
 */
#define	MAX_WRACCT	1024	/* Maximum buffer size of wracct() */

struct actwra
{
	int	ac_did;		/* Daemon index */
	int	ac_len;		/* Length of buffer (bytes) */
	jid_t	ac_jid;		/* Job ID */
	char	*ac_buf;	/* Daemon accounting buffer */
};

#ifndef _KERNEL
extern int	acct __P((const char *));

#if (_NO_POSIX && _NO_XOPEN4 && _NO_XOPEN5)
extern int	acctctl(int func, void *act);

#if !defined(_SGI_COMPILING_LIBC)
#pragma optional acctctl
#endif

#endif

#else /* _KERNEL */
struct proc;
extern void	acct(char);
extern void	extacct(struct proc *);
extern void	csa_acct(char, struct proc *);

/* Additional flag for proc.p_acflag/acct.ac_flag */
#define ACKPT	04		/* process has been checkpointed */
#endif /* _KERNEL */

#ifdef __cplusplus
}
#endif

#endif	/* _PROC_ACCT_H */
