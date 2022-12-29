/*
 * FILE: eoe/cmd/miser/lib/libcpuset/src/cpuset.h
 *
 * DESCRIPTION:
 *	Cpuset library header file with definitions and function prototypes.
 */
 
/**************************************************************************
 *									  *
 * 		 Copyright (C) 1997 Silicon Graphics, Inc.		  *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/

#ifndef __CPUSET_H
#define __CPUSET_H
#include <sys/types.h>
#include <sys/cpuset.h>
#include <sys/mac.h>
#include <sys/mac_label.h>
#include <sys/acl.h>

#include <internal/sgimacros.h>

__SGI_LIBC_BEGIN_EXTERN_C

/* 
 * cpuset queue definition config flags
 *
 * Flags of the form MISER_CPUSET_* may become obsolete in the future.
 * The CPUSET_* flags are provided in lieu of the MISER_CPUSET_* flags.
 */

/* cpuset library defintions */

#define CPUSET_DSO		"libcpuset.so"
#define CPUSET_NAME_SIZE	8
#define CPUSET_QUEUE_NAME	0x01
#define	CPUSET_CPU_NAME		0x02

/* cpuset file permision bits */
#define CPUSET_PERM_UREAD       0x0100
#define CPUSET_PERM_UWRITE      0x080
#define CPUSET_PERM_UEXEC       0x040
#define CPUSET_PERM_GREAD       0x020
#define CPUSET_PERM_GWRITE      0x010
#define CPUSET_PERM_GEXEC       0x08
#define CPUSET_PERM_OREAD       0x04
#define CPUSET_PERM_OWRITE      0x02
#define CPUSET_PERM_OEXEC       0x01

/* Misc defines */
#define CPUSET_ID_ACTIVE       1

/* Misc defines */
#define CPUSET_TRUE             0x01
#define CPUSET_FALSE            0x00
#define CPUSET_GLOBAL		1

/* Cpuset operation ids use for cpusetMove() and cpusetMoveStaged() */
#define CPUSET_PID	1
#define CPUSET_ASH	2
#define CPUSET_JID	3
#define CPUSET_PGID	4
#define CPUSET_HID	5
#define CPUSET_SID	6

/* Data types for lists of data returned by CPUSET API functions */

typedef struct {
	int 	count;
	pid_t 	*list;
} cpuset_PIDList_t;

typedef struct {
	int 	count;
	cpuid_t	*list;
} cpuset_CPUList_t;

typedef struct {
	int	  count;
	cnodeid_t *list;
} cpuset_NodeList_t;
		
typedef struct {
	int	count;
	char	**list;
	int	*status;
} cpuset_NameList_t;


/* Data types used to input data for CPUSET API functions */

typedef struct {
	int			flags;
	char			*permfile;
	cpuset_CPUList_t 	*cpu;
} cpuset_QueueDef_t;


/* structure to return cpuset properties */ 
typedef struct {
	cpuset_CPUList_t	*cpuInfo; /* cpu count and list */
	int			pidCnt;	  /* number of process in cpuset */
	uid_t			owner;    /* owner id of config file */
	gid_t			group;    /* group id of config file */
	mode_t			DAC;      /* unx permissions of config file*/
	int			flags;    /* Config file flags for cpuset */
	int			extFlags; /* flags indicate valid ACL & MAC */
	struct acl		accAcl;   /* structure for valid access ACL */
	struct acl		defAcl;   /* structure for valid default ACL */
	mac_label		macLabel; /* structure for valid MAC label */
} cpuset_Properties_t;



/* Function declarations: public functions */

	/* Command */

int cpusetSetPermFile(cpuset_QueueDef_t *, char *);
#pragma optional cpusetSetPermFile

int cpusetSetCPUList(cpuset_QueueDef_t *, int, cpuid_t *);
#pragma optional cpusetSetCPUList

int cpusetSetMemList(cpuset_QueueDef_t *, int, nasid_t *);
#pragma optional cpusetSetMemList

int cpusetSetNodeList(cpuset_QueueDef_t *, int, nasid_t *);
#pragma optional cpusetSetNodeList

int cpusetSetFlags(cpuset_QueueDef_t *, int);
#pragma optional cpusetSetFlags

int cpusetSetCPULimits(cpuset_QueueDef_t *, int, int);
#pragma optional cpusetSetCPULimits

int cpusetSetMemLimits(cpuset_QueueDef_t *, uint64_t, uint64_t);
#pragma optional cpusetSetMemLimits

int cpusetCreate(char *, cpuset_QueueDef_t *);
#pragma optional cpusetCreate 

int cpusetLoad(cpuset_QueueDef_t *);
#pragma optional cpusetLoad

int cpusetAttach(char *);
#pragma optional cpusetAttach

int cpusetAttachPID(char *, pid_t);
#pragma optional cpusetAttachPID

int cpusetDestroy(char *);
#pragma optional cpusetDestroy

int cpusetDetachAll(char *);
#pragma optional cpusetDetachAll

int cpusetDetachPID(char *, pid_t);
#pragma optional cpusetDetachPID

int cpusetMove(char *, char *, int, int64_t);
#pragma optional cpusetMove

int cpusetMoveMigrate(char *, char *, int, int64_t);
#pragma optional cpusetMoveMigrate


	/* Query & Allocate */


cpuset_NameList_t *cpusetGetNameList(void);
#pragma optional cpusetGetNameList

cpuset_NameList_t *cpusetGetName(pid_t);	
#pragma optional cpusetGetName

cpuset_QueueDef_t *cpusetAllocQueueDef(int);
#pragma optional cpusetAllocQueueDef

int cpusetGetCPUCount(void);
#pragma optional cpusetGetCPUCount

int cpusetGetNodeCount(void);
#pragma optional cpusetGetNodeCount

cpuset_PIDList_t *cpusetGetPIDList(char *);
#pragma optional cpusetGetPIDList

cpuset_CPUList_t *cpusetGetCPUList(char *);
#pragma optional cpusetGetCPUList

cpuset_NodeList_t *cpusetGetMemList(char *);
#pragma optional cpusetGetMemList

cpuset_NodeList_t *cpusetGetNodeList(char *);
#pragma optional cpusetGetNodeList

int cpusetGetFlags(char *, int *);
#pragma optional cpusetGetFlags

int cpusetGetCPULimits(char *, int *, int *);
#pragma optional cpusetGetCPULimits

int cpusetGetMemLimits(char *, uint64_t *, uint64_t *);
#pragma optional cpusetGetMemLimits

int cpusetGetUnixPerm(char *, uid_t *, gid_t *, mode_t *);
#pragma optional cpusetGetUnixPerm

int cpusetGetTrustPerm(char *, struct acl *, struct acl *, 
						mac_label *);
#pragma optional cpusetGetTrustPerm

cpuset_Properties_t * 	cpusetGetProperties(char *);
#pragma optional cpusetGetProperties

cpuset_NodeList_t *cpusetGetVolatile(void);
#pragma optional cpusetGetVolatile


	/* Free Memory Objects */

void cpusetFreePIDList(cpuset_PIDList_t *);
#pragma optional cpusetFreePIDList

void cpusetFreeNameList(cpuset_NameList_t *);
#pragma optional cpusetFreeNameList

void cpusetFreeCPUList(cpuset_CPUList_t *);
#pragma optional cpusetFreeCPUList

void cpusetFreeNodeList(cpuset_NodeList_t *);
#pragma optional cpusetFreeNodeList

void cpusetFreeQueueDef(cpuset_QueueDef_t *);
#pragma optional cpusetFreeQueueDef

void cpusetFreeProperties(cpuset_Properties_t *pdef);
#pragma optional cpusetFreeProperties


__SGI_LIBC_END_EXTERN_C

#endif /* __CPUSET_H */
