/**************************************************************************
 *									  *
 * 		 Copyright (C) 1995-1996 Silicon Graphics, Inc.		  *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/
#ifndef _KSYS_BEHAVIOR_H
#define _KSYS_BEHAVIOR_H

#ident	"$Revision: 1.59 $"

/*
 * Header file used to associate behaviors with virtualized objects.
 * 
 * A virtualized object is an internal, virtualized representation of 
 * OS entities such as persistent files, processes, or sockets.  Examples
 * of virtualized objects include vnodes, vprocs, and vsockets.  Often
 * a virtualized object is referred to simply as an "object."
 *
 * A behavior is essentially an implementation layer associated with 
 * an object.  Multiple behaviors for an object are chained together,
 * the order of chaining determining the order of invocation.  Each 
 * behavior of a given object implements the same set of interfaces 
 * (e.g., the VOP interfaces).
 *
 * Behaviors may be dynamically inserted into an object's behavior chain,
 * such that the addition is transparent to consumers that already have 
 * references to the object.  Typically, a given behavior will be inserted
 * at a particular location in the behavior chain.  Insertion of new 
 * behaviors is synchronized with operations-in-progress (oip's) so that 
 * the oip's always see a consistent view of the chain.
 *
 * The term "interpostion" is used to refer to the act of inserting
 * a behavior such that it interposes on (i.e., is inserted in front 
 * of) a particular other behavior.  A key example of this is when a
 * system implementing distributed single system image wishes to 
 * interpose a distribution layer (providing distributed coherency)
 * in front of an object that is otherwise only accessed locally.
 *
 * Note that the traditional vnode/inode combination is simply a virtualized 
 * object that has exactly one associated behavior.
 *
 * Behavior synchronization is logic which is necessary under certain 
 * circumstances that there is no conflict between ongoing operations
 * traversing the behavior chain and those dunamically modifying the
 * behavior chain.  Because behavior synchronization adds extra overhead
 * to virtual operation invocation, we want to restrict, as much as
 * we can, the requirement for this extra code, to those situations
 * in which it is truly necessary.
 *
 * Behavior synchronization is needed whenever there's at least one class 
 * of object in the system for which:
 * 1) multiple behaviors for a given object are supported, 
 * -- AND --
 * 2a) insertion of a new behavior can happen dynamically at any time during 
 *     the life of an active object, 
 * 	-- AND -- 
 * 	3a) insertion of a new behavior needs to synchronize with existing 
 *    	    ops-in-progress.
 * 	-- OR --
 * 	3b) multiple different behaviors can be dynamically inserted at 
 *	    any time during the life of an active object
 * 	-- OR --
 * 	3c) removal of a behavior can occur at any time during the life of
 *	    an active object.
 * -- OR --
 * 2b) removal of a behavior can occur at any time during the life of an
 *     active object
 *
 * For now, behavior synchornization, is controlled if CELL is
 * defined.  
 * 
 * In order to allow binary compatibility with 6.5, platforms that might 
 * support Cellular or Cluster Irix have reserved space in 6.5 in several kernel
 * structures (ex., kthread_t) which can be used to implement behavior 
 * synchronization functionality. Reservation of this space is controled
 * by the CELL_PREPARE define. 
 *
 *     Note that currently, the CELL code, takes up more space than will be 
 *     available in 6.5 systems. This needs to be addressed, at some point.
 *
 * The makefile (Makefile.kernio) that is used for compiling 3rd party 
 * drivers also defines CELL_PREPARE for the platforms that might
 * support Cellular or Cluster Irix. In addition, this makefile also defines
 * BHV_PREPARE. This causes calls to be generated to the appropriate
 * BHV locking code. In 6.5, these function are stubs but they will be
 * replaced with real locking code in CELL systems.
 *
 * Note that modifying the behavior chain due to insertion of a new behavior
 * is done atomically w.r.t. ops-in-progress.  This implies that even if 
 * CELL is off, a racing op-in-progress will always see a consistent 
 * view of the chain.  However, correctness is not guaranteed if an 
 * op-in-progress is dependent on whether or not a new behavior is 
 * inserted while it is executing.  The same applies to removal
 * of an existing behavior.
 *
 */

#include <sys/sema.h>
#include <sys/debug.h>
#include <ksys/kcallout.h>
#include <ksys/cell_config.h>

/*
 * Behavior head lock structure.
 * This structure contains the mrlock for the behavior head
 * as well as the deferred callout info. A pointer to
 * this structure is located in the behavior head.
 */
struct bhv_head_lock;
struct kcallout;
typedef struct {
	mrlock_t	bhl_lock;	/* MUST BE FIRST - behavior head lock */
	struct kcallout	*bhl_ucallout;	/* deferred update callout queue */
}  bhv_head_lock_t;

#define MR_TO_BHVL(mrp)	((bhv_head_lock_t*) (mrp))


/*
 * Behavior head.  Head of the chain of behaviors.
 * Contained within each virtualized object data structure.
 */
typedef struct bhv_head {
	struct bhv_desc	*bh_first;	/* first behavior in chain */
#if defined(CELL_CAPABLE) || defined(CELL_PREPARE)
	bhv_head_lock_t *bh_lockp;	/* pointer to lock info struct */
        void            *bh_unused1;
        __int64_t       bh_unused2;
#endif
} bhv_head_t;

/*
 * Behavior descriptor.  Descriptor associated with each behavior.
 * Contained within the behavior's private data structure.
 */
typedef struct bhv_desc {
	void		*bd_pdata;	/* private data for this behavior */
	void		*bd_vobj;	/* virtual object associated with */
	void		*bd_ops;	/* ops for this behavior */
	struct bhv_desc	*bd_next;	/* next behavior in chain */
} bhv_desc_t;

/*
 * Behavior identity field.  A behavior's identity determines the position 
 * where it lives within a behavior chain, and it's always the first field
 * of the behavior's ops vector. The optional id field further identifies the
 * subsystem responsible for the behavior.
 */
typedef struct bhv_identity {
	ushort	bi_id;		/* owning subsystem id */
	uchar_t	bi_version;	/* subsystem version level */
	uchar_t	bi_position;	/* position in chain */
} bhv_identity_t;
typedef bhv_identity_t bhv_position_t;

#define	BHV_VERSION_1	1
#define	BHV_VERS_CUR	BHV_VERSION_1

#ifdef CELL_CAPABLE
#define BHV_IDENTITY_INIT(id,vers,pos)	{id, vers, pos}
#else
#define BHV_IDENTITY_INIT(id,vers,pos)	{0, 0, pos}
#endif
#define BHV_IDENTITY_INIT_POSITION(pos)	BHV_IDENTITY_INIT(0, BHV_VERS_CUR, pos)


/*
 * Define boundaries of position values.  
 */
#define BHV_POSITION_INVALID	0	/* invalid position number */
#define BHV_POSITION_BASE	1	/* base (last) implementation layer */
#define BHV_POSITION_TOP	63	/* top (first) implementation layer */

/*
 * Define stuff for behavior position masks
 */
typedef __uint64_t bhv_posmask_t;
#define BHV_POSMASK_NULL	((bhv_posmask_t) 0)
#define BHV_POSMASK_ONE(a)      (((bhv_posmask_t) 1) << (a))
#define BHV_POSMASK_RANGE(a, b) (((((bhv_posmask_t) 1) << ((b)-(a)))-1) << (a))
#define BHV_POSMASK_TEST(a, b)  ((a) & BHV_POSMASK(b))
#define BHV_POMASK_TESTID(a, b) BHV_POS_MASK((b)->bi_position)

/*
 * Plumbing macros.
 */
#define BHV_HEAD_FIRST(bhp)	(ASSERT((bhp)->bh_first), (bhp)->bh_first)
#define BHV_NEXT(bdp)		(ASSERT((bdp)->bd_next), (bdp)->bd_next)
#define BHV_NEXTNULL(bdp)	((bdp)->bd_next)
#define BHV_VOBJ(bdp)		(ASSERT((bdp)->bd_vobj), (bdp)->bd_vobj)
#define BHV_VOBJNULL(bdp)	((bdp)->bd_vobj)
#define BHV_PDATA(bdp)		(bdp)->bd_pdata
#define BHV_OPS(bdp)		(bdp)->bd_ops
#define BHV_IDENTITY(bdp)	((bhv_identity_t *)(bdp)->bd_ops)
#define BHV_POSITION(bdp)	(BHV_IDENTITY(bdp)->bi_position)
#define	BHV_VERSION(bdp)	(BHV_IDENTITY(bdp)->bi_version)

/*
 * This is used to mark an op table entry for an operation that has
 * been deleted but the entry remains reserved so that alignment 
 * is maintained for compatibility for all subsequent operations.
 */
#define BHV_OP_DELETED		NULL




#ifdef CELL_CAPABLE

/* 
 * Macros for manipulation of behavior locks. The following
 * macros operate on the lock itself. Currently, BHV locks are
 * simply mrlocks but this implementation could change in the
 * future. These macros should insulate us from this change.
 *	These macros take a mrlock_t* as an argument.
 */

#define BHV_MRACCESS(l)			mraccess(l)
#define BHV_MRACCUNLOCK(l)		mraccunlock(l)
#define BHV_MRTRYACCESS(l)		mrtryaccess(l)
#define BHV_MRTRYPROMOTE(l)		mrtrypromote(l)

#define BHV_MRUPDATE(l)			mrupdate(l)
#define BHV_MRTRYUPDATE(l)		mrtryupdate(l)
#define BHV_MRUNLOCK(l)			mrunlock(l)
#define BHV_MRDEMOTE(l)			mrdemote(l)
#define BHV_MRDIVEST(l)                 mrdivest(l)

#define BHV_MR_IS_READ_LOCKED(l) 	mrislocked_access(l)
#define BHV_MR_NOT_READ_LOCKED(l) 	(!mrislocked_access(l))
#define BHV_MR_IS_WRITE_LOCKED(l) 	mrislocked_update(l)
#define BHV_MR_NOT_WRITE_LOCKED(l) 	(!mrislocked_update(l))
#define BHV_MR_IS_EITHER_LOCKED(l)	mrislocked_any(l)
#define BHV_MR_NOT_EITHER_LOCKED(l)	(!mrislocked_any(l))
#define BHV_MR_LOCK_MINE(l)             mrlock_mine(l,curthreadp)

/* 
 * Behavior chain lock macros - typically used by ops-in-progress to 
 * synchronize with behavior insertion and object migration.
 *	Theses macros take a behavior (bhv_head_t*) as an 
 *	argument.
 */
#define BH_LOCK(bhp)			(&(bhp)->bh_lockp->bhl_lock)	
#define	BH_LOCKPP_TO_BHP(lpp)		\
	((bhv_head_t *)((char *)(lpp) - sizeof(struct bhv_desc *)))

#define BHV_READ_LOCK(bhp)		CELL_ONLY(BHV_MRACCESS(BH_LOCK(bhp)))
#define BHV_READ_UNLOCK(bhp)		CELL_ONLY(BHV_MRACCUNLOCK(BH_LOCK(bhp)))
#define BHV_TRYACCESS(bhp)		CELL_MUST(BHV_MRTRYACCESS(BH_LOCK(bhp)))
#define BHV_TRYPROMOTE(bhp)		CELL_MUST(BHV_MRTRYPROMOTE(BH_LOCK(bhp)))

#define BHV_WRITE_LOCK(bhp)		CELL_ONLY(BHV_MRUPDATE(BH_LOCK(bhp)))
#define BHV_WRITE_UNLOCK(bhp)		CELL_ONLY(BHV_MRUNLOCK(BH_LOCK(bhp)))
#define BHV_TRYUPDATE(bhp)		CELL_MUST(BHV_MRTRYUPDATE(BH_LOCK(bhp)))
#define BHV_WRITE_TO_READ(bhp)		CELL_ONLY(BHV_MRDEMOTE(BH_LOCK(bhp)))
#define BHV_DEMOTE(bhp)			CELL_MUST(BHV_MRDEMOTE(BH_LOCK(bhp)))

#define BHV_IS_READ_LOCKED(bhp) 	CELL_IF(BHV_MR_IS_READ_LOCKED(BH_LOCK(bhp)), 1)
#define BHV_NOT_READ_LOCKED(bhp) 	CELL_IF(BHV_MR_NOT_READ_LOCKED(BH_LOCK(bhp)), 1)
#define BHV_IS_WRITE_LOCKED(bhp) 	CELL_IF(BHV_MR_IS_WRITE_LOCKED(BH_LOCK(bhp)), 1)
#define BHV_NOT_WRITE_LOCKED(bhp) 	CELL_IF(BHV_MR_NOT_WRITE_LOCKED(BH_LOCK(bhp)), 1)
#define BHV_IS_EITHER_LOCKED(bhp) 	CELL_IF(BHV_MR_IS_EITHER_LOCKED(BH_LOCK(bhp)), 1)
#define BHV_NOT_EITHER_LOCKED(bhp) 	CELL_IF(BHV_MR_NOT_EITHER_LOCKED(BH_LOCK(bhp)), 1)
#define BHV_LOCK_MINE(bhp) 		CELL_IF(BHV_MR_LOCK_MINE(BH_LOCK(bhp)), 1)
#define BHV_AM_WRITE_OWNER(bhp) \
  	CELL_IF(BHV_MR_IS_WRITE_LOCKED(BH_LOCK(bhp)) && \
                BHV_MR_LOCK_MINE(BH_LOCK(bhp)), 1)

/*
 * Variations of the above that check for behavior layer.  That's only
 * going to be there in cell_enabled kenel, so a cell check is redundant
 */
#define	BHV_IS_BHVL(bhp)		((bhp)->bh_first != NULL &&	\
					 BHV_PDATA((bhp)->bh_first) == bhp)
#define	BHVL_IF(bhp, x, r)		((BHV_IS_BHVL(bhp))? (x) : r)
#define	BHVL_ONLY(bhp, x)		\
	{ if (BHV_IS_BHVL((bhp))) { cell_never(); x; } }

#define BHVL_READ_LOCK(bhp)		BHVL_ONLY(bhp,BHV_MRACCESS(BH_LOCK(bhp)))
#define BHVL_READ_UNLOCK(bhp)		BHVL_ONLY(bhp,BHV_MRACCUNLOCK(BH_LOCK(bhp)))
#define BHVL_TRYACCESS(bhp)		BHVL_IF(bhp, BHV_TRYACCESS(bhp), 1)
#define BHVL_TRYPROMOTE(bhp)		BHVL_IF(bhp, BHV_TRYPROMOTE(bhp), 1)

#define BHVL_WRITE_LOCK(bhp)		BHVL_ONLY(bhp,BHV_MRUPDATE(BH_LOCK(bhp)))
#define BHVL_WRITE_UNLOCK(bhp)		BHVL_ONLY(bhp,BHV_MRUNLOCK(BH_LOCK(bhp)))
#define BHVL_TRYUPDATE(bhp)		BHVL_IF(bhp, BHV_TRYUPDATE(bhp), 1)
#define BHVL_WRITE_TO_READ(bhp)		BHVL_ONLY(bhp,BHV_MRDEMOTE(BH_LOCK(bhp)))
#define BHVL_DEMOTE(bhp)		BHVL_ONLY(BHV_DEMOTE(bhp))

#define BHVL_IS_READ_LOCKED(bhp) 	BHVL_IF(bhp,BHV_MR_IS_READ_LOCKED(BH_LOCK(bhp)), 1)
#define BHVL_NOT_READ_LOCKED(bhp) 	BHVL_IF(bhp,BHV_MR_NOT_READ_LOCKED(BH_LOCK(bhp)), 1)
#define BHVL_IS_WRITE_LOCKED(bhp) 	BHVL_IF(bhp,BHV_MR_IS_WRITE_LOCKED(BH_LOCK(bhp)), 1)
#define BHVL_NOT_WRITE_LOCKED(bhp) 	BHVL_IF(bhp,BHV_MR_NOT_WRITE_LOCKED(BH_LOCK(bhp)), 1)
#define BHVL_IS_EITHER_LOCKED(bhp) 	BHVL_IF(bhp,BHV_MR_IS_EITHER_LOCKED(BH_LOCK(bhp)), 1)
#define BHVL_NOT_EITHER_LOCKED(bhp) 	BHVL_IF(bhp,BHV_MR_NOT_EITHER_LOCKED(BH_LOCK(bhp)), 1)
#define BHVL_LOCK_MINE(bhp) 		BHVL_IF(bhp,BHV_MR_LOCK_MINE(BH_LOCK(bhp)), 1)
#define BHVL_AM_WRITE_OWNER(bhp) \
  	BHVL_IF(bhp,BHV_MR_IS_WRITE_LOCKED(BH_LOCK(bhp)) && \
		BHV_MR_LOCK_MINE(BH_LOCK(bhp)), 1)

/*
 * Variations that make no checks.  Called only fom where must be a cell enabled
 * and a lock layer installed
 */
#define BHVLOCK_READ_LOCK(bhp)		BHV_MRACCESS(BH_LOCK(bhp))
#define	BHVLOCK_TRYACCESS(bhp)		BHV_MRTRYACCESS(BH_LOCK(bhp))
#define BHVLOCK_READ_UNLOCK(bhp)	BHV_MRACCUNLOCK(BH_LOCK(bhp))
#define BHVLOCK_WRITE_LOCK(bhp)		BHV_MRUPDATE(BH_LOCK(bhp))
#define BHVLOCK_WRITE_UNLOCK(bhp)	BHV_MRUNLOCK(BH_LOCK(bhp))
/*
 * Request a callout to be made ((*func)(bhp, arg1, arg2, arg3, argv, argvsz))
 * with the behavior chain update locked.
 *
 * Must have read lock before calling this routine.
 * Note that the callouts will occur in the context of the last
 * accessor unlocking the behavior.
 */
typedef void bhv_ucallout_t(bhv_head_t *bhp, void *, void *, caddr_t, size_t);



#define BHV_WRITE_LOCK_CALLOUT(bhp, flags, func, arg1, arg2, argv, argvsz) \
	bhv_queue_ucallout(bhp, flags, func, arg1, arg2, argv, argvsz)

#define bhv_lock_init(bhp,name)		CELL_ONLY(mrbhinit(BH_LOCK(bhp), (name)))
#define bhv_lock_free(bhp)		CELL_ONLY(mrfree(BH_LOCK(bhp)))

extern void bhv_version_read_lock(bhv_head_t *);
extern void bhv_version_read_unlock(bhv_head_t *);
extern int bhv_version_read_lock_rv(bhv_head_t *);
extern void bhv_version_read_unlock_rv(bhv_head_t *, int);
extern void bhv_version_write_lock(bhv_head_t *);
extern void bhv_version_write_unlock(bhv_head_t *);

#define	BHV_VERSION_READ_LOCK(bhp)	   \
				CELL_ONLY(bhv_version_read_lock(bhp))
#define	BHV_VERSION_READ_UNLOCK(bhp)	   \
				CELL_ONLY(bhv_version_read_unlock(bhp))
#define	BHV_VERSION_READ_LOCK_RV(bhp,rv)   \
				CELL_ONLY(rv = bhv_version_read_lock_rv(bhp))
#define	BHV_VERSION_READ_UNLOCK_RV(bhp,rv) \
				CELL_ONLY(bhv_version_read_unlock_rv(bhp,rv))
#define	BHV_VERSION_WRITE_LOCK(bhp)	   \
				CELL_ONLY(bhv_version_write_lock(bhp))
#define	BHV_VERSION_WRITE_UNLOCK(bhp)	   \
				CELL_ONLY(bhv_version_write_unlock(bhp))

#elif BHV_PREPARE

/*
 * Not running a CELL system. If BHV_PREPARE is defined, then the
 * read/write BHV locking macros should call external routines. This
 * is currently done for 3rd party drivers.
 * Otherwise, just NOOP the calls.
 */

#define BHV_READ_LOCK(bhp)              bhv_read_lock(&(bhp)->bh_lockp);
#define BHV_READ_UNLOCK(bhp)		bhv_read_unlock(&(bhp)->bh_lockp);
#define BHV_WRITE_LOCK(bhp)		bhv_write_lock(&(bhp)->bh_lockp);
#define BHV_WRITE_UNLOCK(bhp)		bhv_write_unlock(&(bhp)->bh_lockp);

extern void bhv_read_lock(bhv_head_lock_t **);
extern void bhv_read_unlock(bhv_head_lock_t **);
extern void bhv_write_lock(bhv_head_lock_t **);
extern void bhv_write_unlock(bhv_head_lock_t **);

#define	BHV_VERSION_READ_LOCK(bhp)		BHV_READ_LOCK(bhp)
#define	BHV_VERSION_READ_UNLOCK(bhp)		BHV_READ_UNLOCK(bhp)

extern void bhv_version_read_lock(bhv_head_t *);
extern void bhv_version_read_unlock(bhv_head_t *);
extern void bhv_version_write_lock(bhv_head_t *);
extern void bhv_version_write_unlock(bhv_head_t *);

#define	BHV_VERSION_READ_LOCK(bhp)	bhv_version_read_lock(bhp)
#define	BHV_VERSION_READ_UNLOCK(bhp)	bhv_version_read_unlock(bhp)
#define	BHV_VERSION_WRITE_LOCK(bhp)	bhv_version_write_lock(bhp)
#define	BHV_VERSION_WRITE_UNLOCK(bhp)	bhv_version_write_unlock(bhp)

#else	/* not CELL_CAPABLE or BHV_PREPARE, ie non-cell kernel */

#define	BHVL_ONLY(bhp, x)
#define	BHVL_IF(bhp, x, r)

#define BHV_READ_LOCK(bhp)
#define BHV_READ_UNLOCK(bhp)
#define BHV_WRITE_LOCK(bhp)
#define BHV_WRITE_UNLOCK(bhp)


#define BHV_WRITE_TO_READ(bhp)
#define BHV_WRITE_LOCK_CALLOUT(bhp, func, arg1, arg2, argv, argvsz)
#define BHV_IS_READ_LOCKED(bhp)		1
#define BHV_NOT_READ_LOCKED(bhp)	1
#define BHV_IS_WRITE_LOCKED(bhp)	1
#define BHV_LOCK_MINE(bhp) 		1
#define BHV_NOT_WRITE_LOCKED(bhp)	1
#define bhv_lock_init(bhp,name)
#define bhv_lock_free(bhp)
#define bhv_ucq_init(bhp,name)
#define bhv_ucq_free(bhp)

#define	BHV_VERSION_READ_LOCK(bhp)
#define	BHV_VERSION_READ_UNLOCK(bhp)
#define	BHV_VERSION_READ_LOCK_RV(bhp,rv)
#define	BHV_VERSION_READ_UNLOCK_RV(bhp,rv)

#define	BHV_IS_BHVL(bhp)		(0)
#define	BHVL_READ_LOCK(bhp)
#define	BHVL_READ_UNLOCK(bhp)
#define	BHVL_WRITE_LOCK(bhp)
#define BHVL_WRITE_UNLOCK(bhp)
#define BHVL_WRITE_TO_READ(bhp)
#define BHVL_IS_READ_LOCKED(bhp)	1
#define BHVL_NOT_READ_LOCKED(bhp)	1
#define BHVL_IS_WRITE_LOCKED(bhp)	1
#define BHVL_LOCK_MINE(bhp)		1
#define BHVL_NOT_WRITE_LOCKED(bhp)	1


#endif /* CELL_CAPABLE */
#if defined(CELL_CAPABLE) && !defined(_MASTER_C)
extern int			bhv_try_deferred_ucalloutp(bhv_head_lock_t *bhl);

static __inline int
bhv_try_deferred_ucallout(mrlock_t *mrp)
{
	bhv_head_lock_t	*bhl;

	bhl = MR_TO_BHVL(mrp);
	if (bhl->bhl_ucallout)
		return bhv_try_deferred_ucalloutp(bhl);

	return 0;
}

#endif

extern void bhv_head_init(bhv_head_t *, char *);
extern void bhv_head_destroy(bhv_head_t *);
extern void bhv_head_reinit(bhv_head_t *);
extern void bhv_insert_initial(bhv_head_t *, bhv_desc_t *);
extern void bhv_append_initial(bhv_head_t *, bhv_desc_t *);

/*
 * Initialize a new behavior descriptor.
 * Arguments:
 * 	bdp - pointer to behavior descriptor
 *	pdata - pointer to behavior's private data
 *	vobj - pointer to associated virtual object
 *	ops - pointer to ops for this behavior
 */
#define bhv_desc_init(bdp, pdata, vobj, ops)		\
{							\
	(bdp)->bd_pdata = pdata;			\
	(bdp)->bd_vobj = vobj;				\
	(bdp)->bd_ops = ops;				\
	(bdp)->bd_next = NULL;				\
}

/*
 * Remove a behavior descriptor from a behavior chain.
 */
#define bhv_remove(bhp, bdp)				\
{							\
	if ((bhp)->bh_first == (bdp)) {			\
               /*					\
	        * Remove from front of chain.		\
                * Atomic wrt oip's.			\
		*/					\
	       (bhp)->bh_first = (bdp)->bd_next;	\
        } else {					\
	       /* remove from non-front of chain */	\
	       bhv_remove_not_first(bhp, bdp);		\
	}						\
}

/*
 * Given a bhv chain, do an "insert" for each bhv on that chain.
 */
#define bhv_chain_insert(bhp,bhv_chain)			\
{							\
	bhv_desc_t *bdp, *nbdp;				\
	bdp = (bhv_chain);				\
	while(bdp) {					\
		nbdp = bdp->bd_next;			\
		bdp->bd_next = NULL;			\
		bhv_insert((bhp), bdp);			\
		bdp = nbdp;				\
	}						\
}



/*
 * Behavior module prototypes.
 */
extern int      	bhv_insert(bhv_head_t *bhp, bhv_desc_t *bdp);
extern int      	bhv_forced_insert(bhv_head_t *bhp, bhv_desc_t *bdp);
extern int      	bhv_append(bhv_head_t *bhp, bhv_desc_t *bdp);
extern int      	bhv_truncate(bhv_head_t *bhp, bhv_desc_t *bdp);
extern void		bhv_remove_not_first(bhv_head_t *bhp, bhv_desc_t *bdp);
extern bhv_desc_t 	*bhv_lookup(bhv_head_t *bhp, void *ops);
extern bhv_desc_t 	*bhv_lookup_unlocked(bhv_head_t *bhp, void *ops);
extern bhv_desc_t 	*bhv_lookup_range(bhv_head_t *bhp, int lpos, int hpos);
extern bhv_desc_t	*bhv_base_unlocked(bhv_head_t *bhp);

extern void		bhv_global_init(void);
extern struct zone	*bhv_global_zone;

#ifdef CELL_CAPABLE
extern void		bhv_queue_ucallout(bhv_head_t *bhp,
				int flags, bhv_ucallout_t *func,
				void *, void *, caddr_t, size_t);
#endif /* CELL_CAPABLE */

#endif /* _KSYS_BEHAVIOR_H */
