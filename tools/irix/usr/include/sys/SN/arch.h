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

#ifndef __SYS_SN_ARCH_H__
#define __SYS_SN_ARCH_H__

#if defined(SN0) || defined(SN1)		/* most of file */
#if defined (SN0)
#include <sys/SN/SN0/arch.h>
#elif defined (SN1)
#include <sys/SN/SN1/arch.h>
#endif

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)
typedef __uint64_t	hubreg_t;
typedef __uint64_t	bdrkreg_t;
typedef __uint64_t	nic_t;
#endif

#ifdef SN0
#define CPUS_PER_NODE		2	/* CPUs on a single hub */
#define CPUS_PER_NODE_SHFT	1	/* Bits to shift in the node number */
#define CPUS_PER_SUBNODE	2	/* CPUs on a single hub PI */
#endif
#ifdef SN1
#define CPUS_PER_NODE		4	/* CPUs on a single hub */
#define CPUS_PER_NODE_SHFT	2	/* Bits to shift in the node number */
#define CPUS_PER_SUBNODE	2	/* CPUs on a single hub PI */
#endif
#define CNODE_NUM_CPUS(_cnode)		(NODEPDA(_cnode)->node_num_cpus)
#define CNODE_TO_CPU_BASE(_cnode)	(NODEPDA(_cnode)->node_first_cpu)
#define cputocnode(cpu)				\
               (ASSERT(pdaindr[(cpu)].pda), (pdaindr[(cpu)].pda->p_nodeid))
#define cputonasid(cpu)				\
               (ASSERT(pdaindr[(cpu)].pda), (pdaindr[(cpu)].pda->p_nasid))
#define makespnum(_nasid, _slice)					\
		(((_nasid) << CPUS_PER_NODE_SHFT) | (_slice))


/*
 * There are 2 very similar macros for dealing with "slices". Make sure
 * you use the right one. 
 * Unfortunately, on all platforms except SN1 (currently), the 2 macros 
 * are interchangible. 
 *
 * On SN1, there are 4 cpus per node. Each cpu is refered to by it's slice.
 * The slices are numbered 0 thru 3. 
 *
 * There are also 2 PI interfaces per node. Each PI interface supports 2 cpus.
 * The term "local slice" specifies the cpu number relative to the PI.
 *
 * The cpus on the node are numbered:
 *	slice	localslice
 *	  0          0
 *	  1          1
 *	  2          0
 *	  3          1
 *
 *	cputoslice - returns a number 0..3 that is the slice of the specified cpu.
 *	cputolocalslice - returns a number 0..1 that identifies the local slice of
 *			the cpu within it's PI interface.
 */
#define cputoslice(cpu)				\
               (ASSERT(pdaindr[(cpu)].pda), (pdaindr[(cpu)].pda->p_slice))
#define cputolocalslice(cpu)			\
               (ASSERT(pdaindr[(cpu)].pda), (LOCALCPU(pdaindr[(cpu)].pda->p_slice)))
#define cputosubnode(cpu)			\
		(ASSERT(pdaindr[(cpu)].pda), (SUBNODE(pdaindr[(cpu)].pda->p_slice)))

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)

#define INVALID_NASID		(nasid_t)-1
#define INVALID_CNODEID		(cnodeid_t)-1
#define INVALID_PNODEID		(pnodeid_t)-1
#define INVALID_MODULE		(moduleid_t)-1
#define	INVALID_PARTID		(partid_t)-1

extern int     get_slice(void);
extern cnodeid_t get_cpu_cnode(int);
extern cpuid_t get_cnode_cpu(cnodeid_t);
extern int get_cpu_slice(cpuid_t);
extern cpuid_t cnodetocpu(cnodeid_t);
extern cpuid_t cnode_subnode_to_cpu(cnodeid_t, int);
extern cpuid_t cnode_slice_to_cpuid(cnodeid_t, int);

#ifndef _STANDALONE
extern nasid_t get_nasid(void);
extern int cnode_exists(cnodeid_t cnode);
/*
 * NO ONE should access these arrays directly.  The only reason we refer to
 * them here is to avoid the procedure call that would be required in the
 * macros below.  (Really want private data members here :-)
 */
extern cnodeid_t nasid_to_compact_node[MAX_NASIDS];
extern nasid_t compact_to_nasid_node[MAX_COMPACT_NODES];
extern cnodeid_t cpuid_to_compact_node[MAXCPUS];
#endif

/*
 * These macros are used by various parts of the kernel to convert
 * between the three different kinds of node numbering.   At least some
 * of them may change to procedure calls in the future, but the macros
 * will continue to work.  Don't use the arrays above directly.
 */

#define	NASID_TO_REGION(nnode)	      	\
    ((nnode) >> \
     (is_fine_dirmode() ? NASID_TO_FINEREG_SHFT : NASID_TO_COARSEREG_SHFT))

#if !defined(DEBUG) && (!defined(SABLE) || defined(_STANDALONE))

#define NASID_TO_COMPACT_NODEID(nnode)	(nasid_to_compact_node[nnode])
#define COMPACT_TO_NASID_NODEID(cnode)	(compact_to_nasid_node[cnode])
#define CPUID_TO_COMPACT_NODEID(cpu)	(cpuid_to_compact_node[(cpu)])
#else

/*
 * These functions can do type checking and fail if they need to return
 * a bad nodeid, but they're not as fast so just use 'em for debug kernels.
 */
cnodeid_t nasid_to_compact_nodeid(nasid_t nasid);
nasid_t compact_to_nasid_nodeid(cnodeid_t cnode);

#define NASID_TO_COMPACT_NODEID(nnode)	nasid_to_compact_nodeid(nnode)
#define COMPACT_TO_NASID_NODEID(cnode)	compact_to_nasid_nodeid(cnode)
#define CPUID_TO_COMPACT_NODEID(cpu)	(cpuid_to_compact_node[(cpu)])
#endif

extern int node_getlastslot(cnodeid_t);

#endif /* _LANGUAGE_C || _LANGUAGE_C_PLUS_PLUS */

#define SLOT_BITMASK    	(MAX_MEM_SLOTS - 1)
#define SLOT_SIZE		(1LL<<SLOT_SHIFT)

#define node_getnumslots(node)	(MAX_MEM_SLOTS)
#define NODE_MAX_MEM_SIZE	SLOT_SIZE * MAX_MEM_SLOTS


#else	/* !defined(SN0) && !defined(SN1) */
/* provide some useful definitions without requiring SN0 or SN1 to
 * be defined (so commands don't have to be targetted to SN0/SN1.
 */
#define SN0_MAX_NASIDS		256
#define SN1_MAX_NASIDS		128
#endif	/* defined(SN0) || defined(SN1) */


#endif /* __SYS_SN_ARCH_H__ */
