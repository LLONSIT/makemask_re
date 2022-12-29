/*
 * This work is held in copyright as an unpublished work by Silicon
 * Graphics, Inc. All rights reserved.
 */

#ifndef __FS_XFS_XFS_CXFS_H__
#define __FS_XFS_XFS_CXFS_H__

#include <ksys/cell_types.h>

/*
 * xfs_cxfs.h -- Interface cxfs presents to non-cell xfs code
 *
 * This header specifies the interface that cxfs V1 code presents to the 
 * non-cellular parts of xfs.  When the specfied routines are not present,
 * stubs will be provided.
 */

struct xfs_inode;
struct xfs_mount;
struct xfs_args;
struct mounta;
struct vfs;
struct vfsops;
struct vnode;
struct buf;
struct cred;

/*
 * Array mount routines.  Stubs provided for the non-CELL case.
 */
extern void cxfs_arrinit(void); /* Initialization for array mount logic. */
extern int cxfs_mount(	        /* For any specia mount handling. */
		struct xfs_mount    *mp,
                struct xfs_args     *ap,
		dev_t		    dev,
		int	            *client);
extern void cxfs_unmount(       /* For any special unmount handling. */
		struct xfs_mount    *mp, struct vfs *, int mount_failure);
extern void cxfs_server_set_io_ops( /* Updates the io_ops vector */
		struct xfs_mount    *mp);

/*
 * Other cxfs routines.  Stubs provided in non-CELL case.
 */
extern void cxfs_inode_quiesce(             /* Quiesce new inode for vfs */
		struct xfs_inode    *ip);   /* relocation. */
extern int cxfs_inode_qset(                 /* Set quiesce flag on inode. */
		struct xfs_inode    *ip);  
extern int cxfs_remount_server(             /* Modify mount parameters.  This */
                struct xfs_mount    *mp,    /* may result in vfs relocation. */
                struct xfs_args     *ap,   /* tions for arrays and ssi as */
                                            /* well as a stub for non-CELL. */
		int	copy);

extern struct xfs_mount *get_cxfs_mountp(struct vfs *);

extern void cxfs_strat_complete_buf(struct buf *);
extern void cfs_xfsd_remap_ioptr(struct bhv_head *, void **);

/* DMAPI routines.  Stubs provided for the non-CELL case. */
extern int cxfs_dm_fcntl(
		bhv_desc_t *,
		void *,
		int,
		off_t,
		struct cred *,
		union rval *);

int	dmapi_bnc_alloc(struct vnode *, int);

#endif /* __FS_XFS_XFS_CXFS_H__ */
