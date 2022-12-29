/*
 * Copyright (c) 1989, 1990, 1991 by Sun Microsystems, Inc.
 */

/*
 * Loopback mount info - one per mount
 */

#ifndef _SYS_FS_LOFS_INFO_H
#define	_SYS_FS_LOFS_INFO_H

#include <sys/atomic_ops.h>

#ifdef	__cplusplus
extern "C" {
#endif

/* Compute hash index for the vnode pointer "v".
 * LTABLESIZE must be a power of 2 for this to work.
 */
#define LTABLESIZE          8

#if _PAGESZ == 16384
/* 
 * 256 byte zone is used if page size is 16384 -- vnode size = 256
 * 192 byte zone is used if page size is 4096  -- vnode size = 160
 * If vnode size moves up to the next zone, then we need to change these
 * sizes too.
 */
#define LNODE_TABLE_HASH(v) (((__psunsigned_t)(v) >> 8) % LTABLESIZE)
#else
#define LNODE_TABLE_HASH(v) (((__psunsigned_t)(v) >> 6) % LTABLESIZE)
#endif

typedef struct lnodelist_s {
        lnode_t *head;
        kmutex_t   lock;
} lnodelist_t;

struct loinfo {
	bhv_desc_t	 li_bhv;	/* vfs lofs behavior */
	struct vfs	*li_realvfs;	/* real vfs of mount */
	struct vfs	*li_mountvfs;	/* loopback vfs */
	struct vnode	*li_rootvp;	/* root vnode of this vfs */
	struct lfsnode	*li_lfs;	/* list of other vfss */
        mutex_t          li_lock;       /* protect loinfo data */
	int		 li_mflag;	/* mount flags to inherit */
	int		 li_refct;	/* # outstanding vnodes */
	dev_t		 li_rdev;	/* distinguish lofs mounts */
	lnodelist_t      li_lnodes[LTABLESIZE]; /* array of our lnodes */
};

#define LOINFO_LOCK(l)      mutex_enter(&(((struct loinfo*)(l))->li_lock))
#define LOINFO_UNLOCK(l)    mutex_exit(&(((struct loinfo*)(l))->li_lock))

/* inheritable mount flags - propagated from real vfs to loopback */
#define	INHERIT_VFS_FLAG	(VFS_RDONLY|VFS_NOSUID)

/*
 * lfsnodes are allocated as new real vfs's are encountered
 * when looking up things in a loopback name space
 * It contains a new vfs which is paired with the real vfs
 * so that vfs ops (fsstat) can get to the correct real vfs
 * given just a loopback vfs
 */
struct lfsnode {
	bhv_desc_t	lfs_bhv;	/* vfs lofs behavior */
	struct lfsnode *lfs_next;	/* next in loinfo list */
	struct vfs     *lfs_realvfs;	/* real vfs */
	int		lfs_refct;	/* # outstanding vnodes */
	struct vfs	lfs_vfs;	/* new loopback vfs */
};

#define vfs_bhvtoli(bdp)	((struct loinfo *)BHV_PDATA(bdp))

extern struct vfs *lofs_realvfs(struct vfs *, struct loinfo *);

extern struct vfsops lofs_vfsops;

extern int lofsfstype;

extern void lofs_dprint(int var, int level, char *str, ...);

extern int lnode_flush(struct loinfo *li);

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_FS_LOFS_INFO_H */
