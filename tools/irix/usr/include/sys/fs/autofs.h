/*
 * Copyright (c) 1993 by Sun Microsystems, Inc.
 */

/*
 * Autofs mount info - one per mount
 */

#ifndef	_SYS_FS_AUTOFS_H
#define	_SYS_FS_AUTOFS_H

#ifdef	__cplusplus
extern "C" {
#endif

#undef	MAXNAMLEN
#define	MAXNAMLEN	255

#include <netinet/in.h>
#include <sys/time.h>

/* Private well-known port */
#define AUTOFS_PORT 2048

/* Sub-operations for syssgi(SGI_AUTOFS_SYS,....) call */
#define AUTOFS_SYSSGI_NOP	0   /* nop */
#define AUTOFS_SYSSGI_GETINT	1   /* get AutoFS integer value (32 bits) */
				    /* see AUTOFSINT_... */
#define AUTOFS_SYSSGI_SETINT	2   /* set AutoFS integer value (32 bits) */
				    /* see AUTOFSINT_... */
#define AUTOFS_SYSSGI_AUTOFSD	3   /* autofsd daemon control */

/* Sub-sub-operations for AUTOFS_SYSSGI_GETINT and AUTOFS_SYSSGI_SETINT */
#define AUTOFSINT_LOOPBACK	0   /* nop */
#define AUTOFSINT_AUTOFSD	1   /* status of autofsd daemon */
#define AUTOFSINT_UMNT_TIMEOUT	2   /* timeout of 'do_unmount' thread (seconds) */
#define AUTOFSINT_SHUTDOWN	3   /* shutdown flag */
#define AUTOFSINT_AUTOFSD_MTHR	4   /* autofsd mutithreaded flag */
#define AUTOFSINT_SHUTDOWN_TIME 5   /* AutoFS shutdown timeout (sec.) */

struct autofs_args {
	char			*path;		/* autofs mountpoint */
	char			*opts;		/* default mount options */
	char			*map;		/* name of map */
	time_t			mount_to;	/* seconds fs remains */
						/* mounted after last ref */
	time_t 			rpc_to;		/* timeout for rpc calls */
	int			direct;		/* 1 = direct mount */
};

#ifdef	_KERNEL

struct irix5_autofs_args {
	app32_ptr_t		path;		/* autofs mountpoint */
	app32_ptr_t		opts;		/* default mount options */
	app32_ptr_t		map;		/* name of map */
	time_t			mount_to;	/* seconds fs remains */
						/* mounted after last ref */
	time_t 			rpc_to;		/* timeout for rpc calls */
	int			direct;		/* 1 = direct mount */
};

/*
 * The autonode is the "inode" for autofs.  It contains
 * all the information necessary to handle automatic mounting.
 *
 * Access rules for the members of this structure:
 * 
 * - an_name, an_mode, an_gid, an_nodeid, an_flags, an_ainfo - static 
 *   members, which are set once and will not change for the life of
 *   an autonode. Can be accessed without a lock.
 * - an_mntflags, an_dirents, an_size, an_error -
 *   protected by an_rwlock which must be held for read to peek and for
 *   write to change.
 * - an_rwlock, an_wait - dynamic.
 * - an_ref_time - not protected AT ALL. It only increases monotonically
 *   so the worst thing which could happen is that we're going to unmount
 *   a bit earlier.
 * - an_bhv_desc, an_vnode - follow the rules for behaviour
 *   descriptors and vnodes
 * - an_next, an_offset - protected by the an_rwlock from the parent vnode
 * - an_parent - protected by the parent's RWLOCK and guaranteed to be valid
 *   for the life of the autonode. Could be NULL for the short period when
 *   autonode is created but not entered into the parent's list, to close
 *   the race autonode must be locked before being submitted for inclusion.
 * - an_tryunmount - protected either by parent's lock or by autonode_list_lock
 *   for the ROOT nodes
 */
typedef struct autonode {
	char		an_name[MAXNAMLEN + 1];
	u_short		an_mode;	/* file mode bits */
	uid_t		an_uid;
	gid_t		an_gid;
	ino_t		an_nodeid;	/* inode number */
	off_t		an_offset;	/* offset within parent dir */
	u_short		an_tryunmount;	/* unmount candidate */
	u_short		an_flags;	/* autonode flags */
	u_int		an_mntflags;	/* mount flags */
	u_int		an_size;	/* size of directory */
	bhv_desc_t	an_bhv_desc;	/* autofs behavior descriptor */
	struct vnode	an_vnode;	/* place hldr vnode for file */
	time_t		an_ref_time;    /* time last referred */
	int		an_error;	/* mount error */
	struct autonode *an_parent;	/* parent dir for .. lookup */
	struct autonode *an_next;	/* next sibling */
	struct autonode *an_dirents;	/* autonode list under this */
	struct autoinfo	*an_ainfo;	/* points to autoinfo */
	krwlock_t	an_rwlock;	/* protects *entire* node */
	kcondvar_t	an_wait;	/* wait here for slow operations */
	char 		*an_linkname;	/* symlink name */
} autonode_t;

struct autoinfo {
	struct vnode		*ai_rootvp;	/* root vnode */
	struct autonode		*ai_root;	/* root autonode */	
	int		 	ai_refcnt;	/* reference count */
	char			*ai_path;	/* autofs mountpoint */
	int		 	ai_pathlen;	/* autofs mountpoint len */
	char			*ai_opts;	/* default mount options */
	int		 	ai_optslen;	/* default mount options len */
	char			*ai_map;	/* name of map */
	int		 	ai_maplen;	/* name of map len */
	time_t		 	ai_mount_to;
	time_t		 	ai_rpc_to;
	int		 	ai_direct;	/* 1 = direct mount */
	bhv_desc_t		ai_bhv;		/* autofs behavior descriptor */
};


/*
 * Mount flags - an_mntflags
 */
#define	MF_MNTPNT		0x001	/* A DIRECT  mountpoint, left
					 * here for compatibility only,
					 * use AN_DIRECT instead */
#define	MF_INPROG		0x002	/* slow operation in progress */
#define	MF_MOUNTED		0x010	/* mount(s) below - this is a
					 * trigger node */

/* Autonode Flags - an_flags */
#define AN_DIRECT		0x001	/* Direct-map autonode */

/*
 * Convert between vfs/autoinfo & vnode/autonode
 */
#define antovn(ap)      (&((ap)->an_vnode))
#define	bhvtoan(bdp)	((autonode_t *) (BHV_PDATA(bdp)))
#define	antobhv(ap)	(&((ap)->an_bhv_desc))
#define vfs_bhvtoai(bdp)	((struct autoinfo *)BHV_PDATA(bdp))

extern kmutex_t autonode_list_lock;
extern struct autonode *autonode_list;
extern kmutex_t autonode_count_lock;
extern int anode_cnt, freeautonode_count;

extern int	do_mount(autonode_t *, struct autoinfo *, char *, struct cred *);
extern int	autodir_lookup(bhv_desc_t *, char *, bhv_desc_t **, struct cred *);
extern int	auto_direnter(autonode_t *, autonode_t *);
extern int	auto_dirdrop(autonode_t *, autonode_t *, char *);
extern void	do_unmount(void);
extern autonode_t	*makeautonode(vtype_t, vfs_t *, struct autoinfo *,
				      struct cred *, char *, vattr_t *);
extern void	freeautonode(autonode_t *anp);
extern int rm_autonode_forgiving(autonode_t *, autonode_t *);


extern vfsops_t autofs_vfsops;

#ifdef AUTODEBUG

extern int autodebug;
/*PRINTFLIKE2*/
extern void	auto_dprint(int level, char *str, ...);


#define AUTODEBUG_VNOPS		0x001
#define AUTODEBUG_TRACE_VNOPS	0x002
#define AUTODEBUG_MOUNT		0x004
#define AUTODEBUG_TRACE_MOUNT	0x008
#define AUTODEBUG_UNMOUNT	0x010
#define AUTODEBUG_TRACE_UNMOUNT	0x020
#define AUTODEBUG_AUTONODE	0x040
#define AUTODEBUG_LOCKS		0x080
#define AUTODEBUG_VFSOPS	0x100

#define AN_RWLOCK(an, mode) \
	do { auto_dprint(AUTODEBUG_LOCKS, "%s(%d):Locking %s for %c(%d)\n", \
		__FILE__, __LINE__, an->an_name, "?RW"[mode%3], mode); \
	rw_enter (&an->an_rwlock, mode); } while(0)

#define AN_RWUNLOCK(an) \
	do { auto_dprint(AUTODEBUG_LOCKS, "%s(%d): Dropping %s lock\n",\
		__FILE__, __LINE__, an->an_name); \
	rw_exit (&an->an_rwlock); } while (0)

#define AUTO_DPRINT(a) auto_dprint a
#else
#define AN_RWLOCK(an, mode) rw_enter (&(an)->an_rwlock, mode)
#define AN_RWUNLOCK(an) rw_exit(&(an)->an_rwlock)

#define AUTO_DPRINT(a)
#endif

#define AN_UPDATE_REFTIME(ap,v) ((ap)->an_ref_time = (v))
#define AN_GET_REFTIME(ap) ((ap)->an_ref_time)

#endif	/* _KERNEL */

#ifdef	__cplusplus
}
#endif
#endif	/* _SYS_FS_AUTOFS_H */
