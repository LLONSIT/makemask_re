/**************************************************************************
 *									  *
 * 		 Copyright (C) 1998, Silicon Graphics, Inc.		  *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/
/*
 * oplock.h - opportunistic lock definitions
 *
 * $Revision: 1.4 $
 * $Date: 2005/09/15 14:42:53 $
 */

#ifndef _SYS_OPLOCK_H
#define _SYS_OPLOCK_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _KERNEL
/*
 * Oplock private per-vnode data.
 */

typedef struct oplock_data {
	kqueue_t	o_list;
	bhv_desc_t	o_bhv;
	int		o_flags;
	int		o_state;
	toid_t		o_timeoutid;
#ifdef CELL_CAPABLE
	int		o_sleepers;
#endif	/* CELL_CAPABLE */
	pid_t		o_pid;
	dev_t		o_dev;
	ino_t		o_ino;
	int		o_opencnt;
	vnode_t		*o_backchan;
#ifdef CELL_CAPABLE
	mutex_t		o_lock;
#else	/* CELL_CAPABLE */
	lock_t		o_lock;
#endif /* CELL_CAPABLE */
	sv_t		o_sv;
} oplock_data_t;
#define	o_next	o_list.kq_next
#define	o_prev	o_list.kq_prev

#ifdef CELL_CAPABLE

/* oplock flags */
#define OPLK_CXFS_SERVER	0x1	/* we are the cxfs server */
#define OPLK_CXFS_CLIENT_HELD	0x2	/* oplock held by a cxfs client */

/* cxfs oplock commands */
#define CXFS_CHECK		1 	/* check if vnode is cxfs exported */
#define CXFS_REVOKE		2	/* revoke the oplock */
#define CXFS_CLIENT_RECOVERY	3	/* client recovery */
#define CXFS_SKIP_OPLK_CLEAR	4	/* skip clearing of dsxvn oplock state */

/* cxfs oplock cell types */
#define CXFS_SERVER		1
#define CXFS_CLIENT		2

/* Determine whether we are in a RPC from the cell where the oplock holder
 * resides.
 */
#define CXFS_CELL_OWNS_OPLOCK(bdp)	cxfs_cell_owns_oplock(bdp)

/* Oplock type registration supported. */
#define OPLOCK_HAS_TYPE_REG_SUPPORT     1

extern int cxfs_cell_owns_oplock(bhv_desc_t *bdp);

#endif	/* CELL_CAPABLE */

extern int oplock_fcntl(vfile_t *, int, sysarg_t, rval_t *);
extern int oplocks_enabled;
extern int oplock_timeout;
extern int oplock_cxfs_req(vnode_t *, int, int, int, int *);

#endif /* _KERNEL */

#ifdef __cplusplus
}
#endif

#endif /* _SYS_OPLOCK_H */
