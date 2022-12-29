/*	@(#)export.h	1.6 D/NFS */
/*      @(#)export.h 1.4 88/02/08 SMI      */

#ifdef _KERNEL
#include "netinet/in.h"
#include "sys/socketvar.h"
#include "sys/socket.h"
#else
#include <netinet/in.h>
#include <sys/socketvar.h>
#include <sys/socket.h>
#endif

/*
 * exported vfs flags.
 */
#ifndef EX_RDONLY
#define EX_RDONLY	0x01		/* exported read only */
#endif
#define EX_RDMOSTLY	0x02		/* exported read mostly */
#define	EX_NOHIDE	0x04		/* visible from upper exported fs */
#define	EX_WSYNC	0x08		/* write synchronously to disk */
#define	EX_B32CLNT	0x10		/* mask off high 32bits of xfs cookie */
					/* so client won't reject xdr */
#define EX_NOXATTR	0x20		/* reject extended attribute requests
					   unless client is trusted */
#define	EX_ACCESS	0x40		/* exported access */

#define EX_FSID		0x80		/* fsid */
#define EX_OFFLINE	0x100		/* drop all calls to this entry */
#define EX_ASYNC	0x200
#define EX_NEEDAUTH	0x400		/* Call upstairs required for this
					 * export entry */
#define EX_NOMKNOD	0x800		/* Reject mknod calls */
#define EX_DIRECTIO     0xf000		/* Mask for directio size */
#define EX_DIO_SHIFT    12		/* Shift position for DirectIO bits */
#define EX_ACCEPT_RPCSEC 0x10000	/* Accept RPCSEC_GSS creds */
#define EX_ANON_NLM	0x20000		/* Allow anonymous NLM calls */
#define EX_MANDLOCK	0x40000		/* Allow access to files with
					 * mandatory locking enabled */

#define	EX_ALLFLAGS	 0x7ffff
#define OLD_EX_ALLFLAGS	0x7f

#define EX_VERSION	0x10000000	/* export structure version */
					/* version 0 is the old version */
					/* the version number is in the */
					/* highest 8 bits, allowing for */
					/* 16 versions, including the oldest */
#define EX_VERSMASK	0xf0000000	/* mask to extract the version */

#define EXMAXADDRS	8192		/* max number in address list */

struct exaddrlist {
      unsigned naddrs;			/* number of addresses */
      struct sockaddr *addrvec;		/* pointer to array of addresses */
};

/*
 * Associated with AUTH_UNIX is an array of internet addresses
 * to check root permission.
 */
#define EXMAXROOTADDRS	8192		/* should be config option */
struct unixexport {
	struct exaddrlist rootaddrs;
};


/*
 * The export information passed to exportfs()
 */
struct export {
	int ex_flags;	/* flags */
	int ex_anon;	/* uid for unauthenticated requests */
	int ex_auth;	/* switch */
	union {
		struct unixexport exunix;	/* case AUTH_UNIX */
	} ex_u;
	struct exaddrlist ex_writeaddrs;
	struct exaddrlist ex_accessaddrs;
	dev_t ex_fsid;	/* fsid value to be used if EX_FSID is set */
};
#define ex_unix ex_u.exunix

#ifdef _KERNEL
/*
 * This is the old export structure, without the ex_fsid field.
 */
struct old_export {
	int ex_flags;	/* flags */
	int ex_anon;	/* uid for unauthenticated requests */
	int ex_auth;	/* switch */
	union {
		struct unixexport exunix;	/* case AUTH_UNIX */
	} ex_u;
	struct exaddrlist ex_writeaddrs;
	struct exaddrlist ex_accessaddrs;
};

/*
 * A node associated with an export entry on the list of exported
 * filesystems.
 */
struct __exi_auth_s;
struct kcdb_stats;


struct exportinfo {
	struct exportinfo	*exi_next;
	fsid_t			exi_fsid;
	struct fid 		*exi_fid;
	int			exi_loopback;
	struct vfs 		*exi_vfsp;
	struct export 		exi_export;
	struct __exi_auth_s	*exi_auth;
	char			exi_path[MAXPATHLEN];
	/*
	 * NFS3 only
	 */
	fhandle_t		exi_fh;
	char 			*exi_statpath;	/* status monitor path name */
	int 			exi_statlen;	/* length of status monitor path name */
	vnode_t 		*exi_statvp;
	struct kcdb_stats	*exi_stats;	/* per export stats */
	int			exi_refcnt;	/* reference counter */
	int			exi_state;	/* state of the exportinfo */
};

struct irix5_exaddrlist {
      unsigned naddrs;			/* number of addresses */
      app32_ptr_t addrvec;		/* pointer to array of addresses */
};

struct irix5_unixexport {
	struct irix5_exaddrlist rootaddrs;
};

struct old_irix5_export {
	int ex_flags;	/* flags */
	int ex_anon;	/* uid for unauthenticated requests */
	int ex_auth;	/* switch */
	union {
		struct irix5_unixexport exunix;	/* case AUTH_UNIX */
	} ex_u;
	struct irix5_exaddrlist ex_writeaddrs;
	struct irix5_exaddrlist ex_accessaddrs;
};

struct irix5_export {
	int ex_flags;	/* flags */
	int ex_anon;	/* uid for unauthenticated requests */
	int ex_auth;	/* switch */
	union {
		struct irix5_unixexport exunix;	/* case AUTH_UNIX */
	} ex_u;
	struct irix5_exaddrlist ex_writeaddrs;
	struct irix5_exaddrlist ex_accessaddrs;
	dev_t ex_fsid;	/* fsid value to be used if EX_FSID is set */
};
extern	struct	exportinfo *exihashtab[];
#define	EXIHASHTABSIZE	256
#define	EXIHASH(fsid)	(exihashtab[(fsid)->val[0] % EXIHASHTABSIZE])

struct bhv_desc;

extern struct exportinfo *findexport(fsid_t *, struct fid *);
extern struct exportinfo *findexport_path(char *path, enum uio_seg seg);
extern struct exportinfo *findexport_path_r(char *path, enum uio_seg seg);
extern int	nfs_exportinit(void);
extern int	findexivp(struct exportinfo **, struct vnode *,
			  struct vnode *, struct bhv_desc *);
extern int	makefh(fhandle_t *, struct vnode *, struct exportinfo *);
extern int      unexport(fsid_t *, struct fid *);
extern void	export(struct exportinfo*);
extern void	release_statmon_dir(struct exportinfo *);

extern int	makefh3(nfs_fh3 *, struct vnode *, struct exportinfo *);
extern void	exi_rele(struct exportinfo *exi);
extern void	nfs_exilock(void);
extern void	nfs_exiunlock(void);

#endif	/* _KERNEL */
