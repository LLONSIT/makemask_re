#ifndef __SYS_MBUFPRIVATE_H__
#define __SYS_MBUFPRIVATE_H__
/*
 * Copyright (C) 1997 Silicon Graphics, Inc. All rights reserved.
 *
 * Private mbuf allocatr related constants and definitions.
 * This allows for "private" symbols and the definition of the 'struct mb'
 * to be shared with the bsdidbg.c code and icrash any others without the
 * consequences of changing the public mbuf.h header file.
 *
 * mbuf cluster field shorthands
 * NOTE: Some of these conflict with other field names in other header files
 * so including this file requires caution with respect to name conflicts.
 */
#define	m_p		m_u.m_us.mu_p
#define m_refp		m_u.m_us.mu_refp
#define m_ref		m_u.m_us.mu_ref
#define m_size		m_u.m_us.mu_size

/*
 * One mbcache structure per cpu is allocated
 * index mbcache array using cpu number to find associated mbcache structure
 */
#include <sys/cpumask.h> /* for MAXCPUS */
#define MBMAXCPU MAXCPUS
#define	GOODVA(index, va)

#if SN
/*
 * multi-processor definitions
 */
#define	MBINDEX()	(cpuid())
#define	MBCNODEID(i)	(cputocnode(i))
/*
 * use maxcpus since kernel sometimes boots with "holes" in cpuid() space
 * we check if the cpu has been enabled on initialization
 */
#define	MBNUM		(maxcpus)

#elif EVEREST

#define	MBINDEX()	(cpuid())

#define	MBCNODEID(i)	(cputocnode(i))
#define	MBNUM		(maxcpus)
#else
/*
 * uniprocessor definitions
 */
#define	MBINDEX()	0
#define	MBCNODEID(i)	0
#define	MBNUM		1
#endif /* SN0 */

#ifndef CACHELINE_SIZE
#define CACHELINE_SIZE 128
#endif

/*
 * 	Mbuf cache source and sink structures
 *
 * 	Note: numbers in comments such as:
 *
 * 		.....
 *		struct mbuf *mb_big;
 *	\* 24 *\
 *		lock_t  mb_lock;
 *		.....
 *
 *	indicate the offset into the cacheline that has been consumed
 *	by the elements of the structure so far. In the above case, it
 *	means that the mb_lock element will start 24 bytes into the
 *	structure.
 *
 *	If you modify these structures, please ensure that the offsets
 *	are updated, and the current cacheline formatting is retained.
 */
struct mb_source {

	struct mbuf *mb_sml;		/* MSIZE regular mbufs */
	struct mbuf *mb_med;		/* MBUFCL_SIZE cluster mbufs */
	struct mbuf *mb_big;		/* PAGE size NBPP cluster mbufs */
/* 24 */
	lock_t  mb_lock;		/* cache lock */
	int     mb_index;		/* index of this mb */
/* 32 */

	/* m_*get*() counters */
	int	mb_types[MT_MAX];	/* type specific mbuf allocations */
/* 116 */
	uint	mb_smlgets;		/* num sml mbufs taken from free list */
	uint	mb_medgets;		/* num med mbufs taken from free list */
	uint	mb_biggets;		/* num big mbufs taken from free list */
/* 128 */
/*
 *	New 128 byte cacheline for everything that is not used
 *	in the m_get fast path. I don't care much about the ordering
 *	of the rest of the structure at this point.
 */
	struct mb_sink *mb_sink;	/* pointer to sink structure */

	/* Zone data */
	zone_t *mb_smlzone;		/* small list private zone handle */
	zone_t *mb_medzone;		/* medium list private zone handle */
/* 24 */

	uint	mb_smltot;		/* num active small mbufs from zone */
	uint	mb_medtot;		/* num active med mbufs from zone */
	uint	mb_bigtot;		/* num active big mbufs from pages */

	uint	mb_drops;		/* total number allocation failures */
	uint	mb_wait;		/* total number times slept */

	int	mb_mcbtot;		/* total mcb_get() */
	__int64_t	mb_mcbbytes;	/* mcb_get() byte count */
/* 56 */

	int	mb_pcbtot;		/* total m_pcbinc() */
	__int64_t	mb_pcbbytes;	/* m_pcbinc() bytes */

	int	mb_mcbfail;		/* failures of memory allocation */

	uint	mb_smlfree_avg;		/* average num free small mbufs */
	uint	mb_smlfree_threshold;	/* release above this threshold */

	uint	mb_medfree_avg;		/* average num free med mbufs */
	uint	mb_medfree_threshold;	/* release above this threshold */

	uint	mb_bigfree_avg;		/* average num free big mbufs */
	uint	mb_bigfree_threshold;	/* release above this threshold */
/* 96 */

};

/*
 * 	The sink lock is placed on it's own cache line because this
 * 	is where most of the contention will be coming from.
 */
struct mb_sink {
	lock_t  mb_lock;		/* mb tail spinlock */
	char	mb_pad0[CACHELINE_SIZE - sizeof(lock_t)];

/* New cacheline */

	struct mbuf *mb_sml_tail;	/* MSIZE regular mbufs */
	struct mbuf *mb_med_tail;	/* MBUFCL_SIZE cluster mbufs */
	struct mbuf *mb_big_tail;	/* PAGE size NBPP cluster mbufs */
/* 24 */

	int     mb_index;		/* index of this mb */
	uint	mb_smlfrees;		/* num sml mbufs returns to free list */
	uint	mb_medfrees;		/* num med mbufs returns to free list */
	uint	mb_bigfrees;		/* num big mbufs returns to free list */
/* 40 */

	/* m_*free*() counters */
	int	mb_types[MT_MAX];	/* type specific mbuf allocations */
/* 124 */

/*
 *	New 128 byte cacheline for everything that is not used
 *	in the m_free fast path. I don't care much about the ordering
 *	of the rest of the structure at this point
 */
	struct mb_source *mb_src;	/* pointer to src structure */
	uint    mb_needwake;		/* anyone waiting? */
	sv_t	mb_sv;			/* what we wait on */

};

typedef struct mb_source mb_src_t;
typedef struct mb_sink mb_sink_t;

#ifdef MP
#pragma set type attribute mb_src_t align=128
#pragma set type attribute mb_sink_t align=128

/*
 * Ensure internal structure alignment if in future someone changes
 * the structures and gets them wrong.
 */
#pragma set field attribute mb_src_t mb_sink align=128
#pragma set field attribute mb_sink_t mb_sml_tail align=128
#pragma set field attribute mb_sink_t mb_src align=128
#endif /* MP */

#endif /* __SYS_MBUFPRIVATE_H__ */

