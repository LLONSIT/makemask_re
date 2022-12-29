/*
 * Copyright (c) 1989, 1990, 1991 by Sun Microsystems, Inc.
 */

/*
 * Loop-back file information structure.
 */

#ifndef _SYS_FS_LOFS_NODE_H
#define	_SYS_FS_LOFS_NODE_H

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * The lnode is the "inode" for loop-back files.  It contains
 * all the information necessary to handle loop-back file on the
 * client side.
 */
typedef struct lnode {
	struct bhv_desc	lo_bhv_desc;	/* loopback behavior descriptor */
	struct lnode	*lo_next;	/* link for hash chain */
	struct vnode	*lo_vp;		/* pointer to real vnode */
	struct vnode	*lo_vnode;	/* place holder vnode for file */
	struct vnode    *lo_crossedvp;  /* ptr to rootvp of crossed lofs */
	vmap_t          lo_xvmap;	/* vmap for lo_vp */
	int             lo_xvcount;     /* reference counts on lo_vp */
	uint_t          lo_looping;     /* detect looping */
	unsigned char   lo_xvshare;     /* lo_vp is VSHARE type ? -- boolean*/
	unsigned char   lo_vhash;       /* store the hash index here */
} lnode_t;

/*
 * Convert between vnode and lnode
 */
#define	ltov(lp)	((lp)->lo_vnode)
#define	ltobhv(lp)	(&((lp)->lo_bhv_desc))
#define	bhvtol(bdp)	((struct lnode *)(BHV_PDATA((bdp))))
#define	realvp(bdp)	(bhvtol(bdp)->lo_vp)

#ifndef TRUE
#define TRUE  1
#define FALSE 0
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_FS_LOFS_NODE_H */
