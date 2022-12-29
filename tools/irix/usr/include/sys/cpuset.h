/*
 * FILE: /usr/include/sys/cpuset.h
 *
 * DESCRIPTION:
 *      Cpuset header file.
 */

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

#ifndef __SYS_CPUSET_H
#define __SYS_CPUSET_H

#include <sys/types.h>
#include <sys/mac.h>
#include <sys/mac_label.h>
#include <sys/acl.h>

/*
typedef __uint64_t	id_type_t;
typedef __int32_t	ncpus_t;
*/

extern int32_t max_cpusets; 

/* cpuset operation flags */

#define CPUSET_ATTACH		1	/* attach an executable to a cpuset */
#define CPUSET_CREATE		2	/* create a cpuset */
#define CPUSET_DESTROY		3	/* destry a cpuset */
#define CPUSET_LIST_PROCS	4	/* list pids attached to the cpuset */
#define CPUSET_PROCS_COUNT	5	/* Process count in a cpu */
#define CPUSET_MOVE_PROCS	6	/* move all procs out of the cpuset */
#define CPUSET_QUERY_CPUS	7	/* list cpus in a cpuset */
#define CPUSET_QUERY_CURRENT	8	/* get cpuset name for curr process */ 
#define CPUSET_QUERY_NAMES	9	/* list cpuset names configured */
#define CPUSET_ATTACH_PID       10      /* attach process to a cpuset */
#define CPUSET_DETACH_PID       11      /* detach process from cpuset */
#define CPUSET_GET_PROPS	12 	/* get cpuset properties */
#define CPUSET_MOVE_MIGRATE	13	/* move pid with memory move */
#define CPUSET_MOVE		14	/* move pid without memory move */
#define CPUSET_GET_NAME		CPUSET_QUERY_CURRENT
#define CPUSET_GET_NAMES	CPUSET_QUERY_NAMES
#define CPUSET_GET_PIDS		CPUSET_LIST_PROCS
#define CPUSET_GET_PIDCNT	CPUSET_PROCS_COUNT
#define CPUSET_GET_CPUS		CPUSET_QUERY_CPUS
#define CPUSET_GET_MEMS		15
#define CPUSET_GET_NODES	16
#define CPUSET_GET_CPULIMITS	17
#define CPUSET_GET_MEMLIMITS	18
#define CPUSET_GET_UNIXPERM	19
#define CPUSET_GET_TRUSTPERM	20
#define CPUSET_GET_FLAGS	21
#define CPUSET_LOAD		22
#define CPUSET_GET_VOLATILE	23


/* cpuset config flags */

#define CPUSET_CPU_EXCLUSIVE		0x00000100 /* cpus restricted */
#define CPUSET_KERN			0x00000200 /* indicate MP_ISOLATE,
					            * MP_EMPOWER,
						    * MP_RESTRICT */
#define CPUSET_MEMORY_LOCAL		0x00000400 /* get local memory */
#define CPUSET_MEMORY_EXCLUSIVE		0x00000800 /* protect local mem */
#define CPUSET_MEMORY_KERNEL_AVOID	0x00001000 /* protect from kernel*/
#define CPUSET_MEMORY_MANDATORY        	0x00002000
#define CPUSET_POLICY_PAGE             	0x00004000
#define CPUSET_POLICY_KILL             	0x00008000
#define CPUSET_MANDATORYPOLICYMASK	(CPUSET_POLICY_PAGE | \
					 CPUSET_POLICY_KILL)
#define CPUSET_EVENT_NOTIFY             0x00010000
#define CPUSET_UNUSED	                0x00020000
#define CPUSET_POLICY_SHARE_WARN	0x00040000
#define CPUSET_POLICY_SHARE_FAIL	0x00080000
#define CPUSET_SHAREPOLICYMASK		(CPUSET_POLICY_SHARE_WARN | \
					 CPUSET_POLICY_SHARE_FAIL)
#define CPUSET_EXPLICIT			0x00100000
#define CPUSET_VOLATILE			0x00200000 /* tear down when empty */
#define CPUSET_FAILSOFT			0x00400000

/* cpuset extended permissions check bits */
#define CPUSET_ACCESS_ACL	0x01
#define CPUSET_DEFAULT_ACL	0x02
#define CPUSET_MAC_LABEL	0x04

/* misc defines */
#define CPUSET_TRUE		0x01
#define CPUSET_FALSE		0x00


/* cpuset data structures */

typedef struct cpuset_qname {
	uint16_t	count;	/* # of qnames in the list */
	uint64_t	qname;	/* hold pointer to qname list in a uint64 */
} cpuset_qname_t;


typedef struct cpuset_queue {
	id_type_t	queue;		/* cpuset queue ID */
	uint64_t	flags;		/* cpuset creation attributes */
	int32_t		cpucnt;		/* number of CPUs in list */
	uint64_t	cpu;		/* ptr to list of CPU IDs */
	int32_t		memcnt;		/* number of memory nodes in list */
	uint64_t	mem;		/* ptr to list of memory nodes */
	int32_t		nodecnt;	/* number of nodes in list */
	uint64_t	node;		/* ptr to list of nodes */
	int32_t		cpu_advisory;	/* advisory number of CPUs */
	int32_t		cpu_mandatory;	/* mandatory number of CPUs */
	uint64_t	mem_advisory;	/* advisory amount of memory */
	uint64_t	mem_mandatory;	/* mandatory amount of memory */
} cpuset_queue_t;

typedef struct cpuset_pid {
	id_type_t	queue;	   /* cpuset queue id */
	int16_t		count;	   /* # of pids in the list */
	int16_t		max_count; /* max # of pids */
	uint64_t	pid;	   /* hold pointer to pid list in a uint64 */
} cpuset_pid_t;

/* structure for all the file permissions */
typedef struct {
        uint32_t                owner;     /* owner id of file */
        uint32_t                group;     /* group id of file */
        uint32_t                fDAC;      /* standard file permissions */
        uint32_t                ext_flags; /* flags for ACLs and MAC labels */
        struct acl              acc_acl;   /* used for Irix and TRIX */
        struct acl              def_acl;   /* dir default Acl */
        mac_label               mac_label; /* used for TRIX */
} cpuset_file_perms_t;

/* structure to return cpuset properties */
typedef struct {
        id_type_t               queue;   /* queue id */
        uint64_t                flags;   /* cpuset flags */
        uint64_t                fperms;  /* pointer file permissions struct */
} cpuset_properties_t;

typedef struct {
	id_type_t		queue;	/* cpuset queue id */
	uint32_t		owner;  /* owner id of file */
	uint32_t		group;  /* group id of file */
	uint32_t		mode;   /* standard file permissions */
} cpuset_unixperm_t;

typedef struct {
	id_type_t		queue;	   /* cpuset queue id */
	struct acl		acc_acl;   /* used for Irix and TRIX */
	struct acl		def_acl;   /* dir default Acl */
	mac_label		mac_label; /* used for TRIX */
} cpuset_trustperm_t;


/* generic structure for a list of cpuset information */
typedef struct {
	id_type_t	queue;	   /* queue ID of cpuset */
	int16_t 	count;     /* number of items returned in list */
	int16_t		max_count; /* max number of items list may return */
	uint64_t	list;      /* ptr to the list of items */
} cpuset_list_t;


typedef struct {
	id_type_t	queue;     /* queue ID of cpuset */
	uint32_t	advisory;  /* advisory number of CPUs to return */
	uint32_t	mandatory; /* mandatory number of CPUs to return */
} cpuset_cpulimits_t;

typedef struct {
	id_type_t	queue;	   /* queue ID of the cpuset */
	uint64_t	advisory;  /* advisory size of memory to return */
	uint64_t	mandatory; /* mandatory size of memory to return */
} cpuset_memlimits_t;

typedef struct {
	id_type_t	queue;   /* queue ID of the cpuset */
	uint32_t	flags;   /* flags being returned */
} cpuset_flags_t;

typedef struct cpuset_request {
	int16_t		request;	/* request type flag */
	int16_t		error;		/* error type	*/ 
	union {
		cpuset_qname_t	    cs_qname;     /* overlay for qname data */
		cpuset_queue_t	    cs_queue;	  /* overlay for queue data */
		cpuset_pid_t	    cs_pid;	  /* ovly for pid count/list */
		cpuset_list_t	    cs_list;	  /* overlay for lists */
		cpuset_cpulimits_t  cs_cpulimits; /* overlay for CPU limits */
		cpuset_memlimits_t  cs_memlimits; /* overlay for Mem limits */
		cpuset_unixperm_t   cs_unixperm;  /* ovly: unix file perm */
		cpuset_trustperm_t  cs_trustperm; /* ovly: trust file perm */
		cpuset_flags_t	    cs_flags;	  /* overlay for flags info */
                cpuset_properties_t cs_prop;      /* overlays for prop data */
	} csr_u;
} cpuset_request_t;


#ifdef _KERNEL

#include <sys/space.h>

/* cpuset kernel function prototypes */

void	cpuset_init(void);
int 	cpuset_process(sysarg_t, sysarg_t);
int 	cpuset_check_access(void *kt, int cpu);

int     cpuset_attach(cpuset_queue_t *);
int     cpuset_attach_pid (cpuset_queue_t *,pid_t );
int     cpuset_detach_pid (cpuset_queue_t *,pid_t);
int	cpuset_move_op(cpuset_queue_t *, cpuset_pid_t *, int);
int	cpuset_create(cpuset_queue_t *, sysarg_t);
int     cpuset_destroy(cpuset_queue_t *);
int     cpuset_get_properties(cpuset_properties_t *);
int	cpuset_list_procs(cpuset_pid_t *);
int	cpuset_move_procs(cpuset_queue_t *);
void	cpuset_move_thread(kthread_t *, cpuid_t);
int	cpuset_query_cpus(cpuset_queue_t *);
int	cpuset_query_current(cpuset_qname_t *, pid_t);
int	cpuset_query_names(cpuset_qname_t *);
int	cpuset_procs_count(cpuset_pid_t *);
int     cpuset_memalloc_ok(int, size_t);
void    cpuset_init_memsys(cpuset_t *);
void    cpuset_destroy_memsys(cpuset_t *);
void    cpuset_kick_vhand(void *);
int	cpuset_default(kthread_t *);
void	cpuset_teardown(id_type_t);
cpuid_t failsoft_avoid(kthread_t *, cpuid_t);
int	failsoft_panic_check(eframe_t *);

#endif /* _KERNEL */


#endif /* __SYS_CPUSET_H */
