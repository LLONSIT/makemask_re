/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1995-1997, Silicon Graphics, Inc.          *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 **************************************************************************/

#ifndef __SYS_SN_SN1_ARCH_H__
#define __SYS_SN_SN1_ARCH_H__

#if defined(N_MODE)
#error "ERROR constants defined only for M-mode"
#endif

/*
 * This is the maximum number of NASIDS that can be present in a system.
 * (Highest NASID plus one.)
 */
#define MAX_NASIDS              128

/*
 * MAXCPUS refers to the maximum number of CPUs in a single kernel.
 * This is not necessarily the same as MAXNODES * CPUS_PER_NODE
 */
#define MAXCPUS                 512

/*
 * This is the maximum number of nodes that can be part of a kernel.
 * Effectively, it's the maximum number of compact node ids (cnodeid_t).
 * This is not necessarily the same as MAX_NASIDS.
 */
#define MAX_COMPACT_NODES       128

/*
 * The number of PE Bricks we can have on a sprouter.
 */
#define MAX_PEBRICKS		4

/*
 * The number of headless nodes that can be assigned to a node for
 * monitoring.
 */
#define MAX_NODE_WARDS		8

/*
 * MAX_REGIONS refers to the maximum number of hardware partitioned regions.
 */
#define	MAX_REGIONS		64
#define MAX_NONPREMIUM_REGIONS  16
#define MAX_PREMIUM_REGIONS     MAX_REGIONS


/*
 * MAX_PARITIONS refers to the maximum number of logically defined 
 * partitions the system can support.
 */
#define MAX_PARTITIONS		MAX_REGIONS


#define NASID_MASK_BYTES	((MAX_NASIDS + 7) / 8)

/*
 * Slot constants for SN1
 */

#define MAX_MEM_SLOTS    8                     /* max slots per node */

#if defined(N_MODE)
#error "N-mode not supported"
#endif

#define SLOT_SHIFT      	(30)
#define SLOT_MIN_MEM_SIZE	(64*1024*1024)

/*
 * two PIs per bedrock, two CPUs per PI
 */
#define NUM_SUBNODES	2
#define SUBNODE_SHFT	1
#define SUBNODE_MASK	(0x1 << SUBNODE_SHFT)
#define LOCALCPU_SHFT	0
#define LOCALCPU_MASK	(0x1 << LOCALCPU_SHFT)
#define SUBNODE(slice)	(((slice) & SUBNODE_MASK) >> SUBNODE_SHFT)
#define LOCALCPU(slice)	(((slice) & LOCALCPU_MASK) >> LOCALCPU_SHFT)
#define TO_SLICE(subn, local)	(((subn) << SUBNODE_SHFT) | \
				 ((local) << LOCALCPU_SHFT))

#endif /* __SYS_SN_SN1_ARCH_H__ */
