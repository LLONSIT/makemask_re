/*
 * $Revision: 1.83 $
 */
/*	@(#)nfs.h	2.2 88/05/20 NFSSRC4.0 from  2.36 88/02/08 SMI 	*/

#ifndef __NFS_HEADER__
#define __NFS_HEADER__

/*
 * Programs are required to include rpc/types.h before this header file.
 * All other prerequisites are assumed idempotent and included here.
 */
#include <sys/errno.h>
#include <sys/time.h>
#include <sys/uio.h>
#include <rpc/xdr.h>

/* Maximum size of data portion of a remote request */
#define	NFS_MAXDATA	8192
#define	NFS_MAXNAMLEN	255
#define	NFS_MAXPATHLEN	1024

/*
 * Rpc retransmission parameters
 */
#define	NFS_TIMEO	11	/* initial timeout in tenths of a sec. */
#define	NFS_RETRIES	5	/* times to retry request */

/*
 * The value of UID_NOBODY/GIF_NOBODY presented to the world via NFS.
 * UID_NOBODY/GID_NOBODY is translated to NFS_UID_NOBODY/NFS_GID_NOBODY
 * when being sent out over the network and NFS_UID_NOBODY/NFS_GID_NOBODY
 * is translated to UID_NOBODY/GID_NOBODY when received.
 */
#define NFS_UID_NOBODY	-2
#define NFS_GID_NOBODY	-2

/*
 * Error status
 * Should include all possible net errors.
 * For now we just cast errno into an enum nfsstat.
 */
enum nfsstat {
	NFS_OK = 0,			/* no error */
	NFSERR_PERM=EPERM,		/* Not owner */
	NFSERR_NOENT=ENOENT,		/* No such file or directory */
	NFSERR_IO=EIO,			/* I/O error */
	NFSERR_NXIO=ENXIO,		/* No such device or address */
	NFSERR_JUKEBOX=EAGAIN,		/* Resource temporarily unavailable */
	NFSERR_ACCES=EACCES,		/* Permission denied */
	NFSERR_EXIST=EEXIST,		/* File exists */
	NFSERR_NODEV=ENODEV,		/* No such device */
	NFSERR_NOTDIR=ENOTDIR,		/* Not a directory */
	NFSERR_ISDIR=EISDIR,		/* Is a directory */
	NFSERR_INVAL=EINVAL,		/* Is a directory */
	NFSERR_FBIG=EFBIG,		/* File too large */
	NFSERR_NOSPC=ENOSPC,		/* No space left on device */
	NFSERR_ROFS=EROFS,		/* Read-only file system */
	/*
	 * Alas, these errnos differ between our <sys/errno.h> and the
	 * Sun/BSD version, which is part of the nfs protocol!
	 */
	NFSERR_NAMETOOLONG=63,		/* File name too long */
	NFSERR_NOTEMPTY=66,		/* Directory not empty */
	NFSERR_DQUOT=69,		/* Disc quota exceeded */
	NFSERR_STALE=70,		/* Stale NFS file handle */
	NFSERR_REMOTE=71,		/* Too many levels of remote in path */
	NFSERR_WFLUSH			/* write cache flushed */
};
/*
 * For SVR0, as with Sun, we just cast errno into an enum nfsstat.
 * For SVR3 we translate.
 */
extern enum nfsstat	nfs_statmap[];
extern short		nfs_errmap[];

/*
 * The translation table nfs_statmap[] does not have mappings for
 * IRIX specific errors EDQUOT (1133) and ENFSREMOTE (1135) which
 * do have corresponding nfs error value. Must check for these special
 * cases.
 */
#define puterrno(error) \
	((u_short)(error) > LASTERRNO ? \
		((u_short)(error) == EDQUOT ? NFSERR_DQUOT \
			: (u_short)(error) == ENFSREMOTE ? NFSERR_REMOTE \
				: NFSERR_IO) \
		: nfs_statmap[(short)error])

#define geterrno(status) \
	((u_short)(status) > (u_short)NFSERR_WFLUSH ? (short) EIO \
	    : nfs_errmap[(short)status])

/*
 * File types
 */
enum nfsftype {
	NFNON = 0,
	NFREG = 1,		/* regular file */
	NFDIR = 2,		/* directory */
	NFBLK = 3,		/* block special */
	NFCHR = 4,		/* character special */
	NFLNK = 5,		/* symbolic link */
	NFSOCK= 6		/* named socket */
};

/*
 * Special kludge for fifos (named pipes)  [to adhere to NFS Protocol Spec]
 *
 * VFIFO is not in the protocol spec (VNON will be replaced by VFIFO)
 * so the over-the-wire representation is VCHR with a 32 bit '-1' device number.
 * For 64-bit compatibility, we merely call this 0xFFFFFFFF and cast to the
 * appropriate type for na_rdev.
 */
#define NFS_FIFO_TYPE	NFCHR
#define NFS_FIFO_MODE	S_IFCHR
#define NFS_FIFO_DEV	((u_int)0xFFFFFFFF)

/* identify fifo in nfs attributes */
#define NA_ISFIFO(NA)	(((NA)->na_type == NFS_FIFO_TYPE) && \
			    ((NA)->na_rdev == NFS_FIFO_DEV))

/* set fifo in nfs attributes */
#define NA_SETFIFO(NA)	{ \
			(NA)->na_type = NFS_FIFO_TYPE; \
			(NA)->na_rdev = NFS_FIFO_DEV; \
			(NA)->na_mode = ((NA)->na_mode&~S_IFMT)|NFS_FIFO_MODE; \
			}


/*
 * Size of an fhandle in bytes
 */
#define	NFS_FHSIZE	32

#if defined NFSSERVER || defined SVCFH

/*
 * This struct is only used to find the size of the data field in the
 * fhandle structure below.
 */
struct fhsize {
	fsid_t	f0;
	u_short	f1;
	char	f2[4];
	u_short f3;
	char	f4[4];
};
#define	NFS_FHMAXDATA	((NFS_FHSIZE - sizeof (struct fhsize) + 8) / 2)

struct svcfh {
	fsid_t	fh_fsid;		/* filesystem id */
	u_short	fh_len;			/* file number length */
	char	fh_data[NFS_FHMAXDATA];	/* and data */
	u_short	fh_xlen;		/* export file number length */
	char	fh_xdata[NFS_FHMAXDATA];/* and data */
};
#endif

#ifdef NFSSERVER
typedef struct svcfh fhandle_t;
#else
/*
 * This is the client view of an fhandle
 */
typedef union {
	char	fh_data[NFS_FHSIZE];			/* opaque data */
	u_int	fh_hash[NFS_FHSIZE/sizeof(u_int)];	/* hash key */
} fhandle_t;
#endif


/*
 * Arguments to remote write and writecache
 */
struct nfswriteargs {
	fhandle_t	wa_fhandle;	/* handle for file */
	u_int		wa_begoff;	/* beginning byte offset in file */
	u_int		wa_offset;	/* current byte offset in file */
	u_int		wa_totcount;	/* total write cnt (to this offset) */
	u_int		wa_count;	/* size of this write */
	char		*wa_data;	/* data to write (up to NFS_MAXDATA) */
#ifdef _KERNEL
	struct uio	wa_uio;		/* uio to mimic mbuf chain */
#endif
	char		wa_putbuf_ok;	/* can we use xdrmbuf_putbuf? */
};


/*
 * File attributes
 */
struct nfsfattr {
	enum nfsftype	na_type;	/* file type */
	u_int		na_mode;	/* protection mode bits */
	u_int		na_nlink;	/* # hard links */
	u_int		na_uid;		/* owner user id */
	u_int		na_gid;		/* owner group id */
	u_int		na_size;	/* file size in bytes */
	u_int		na_blocksize;	/* prefered block size */
	u_int		na_rdev;	/* special device # */
	u_int		na_blocks;	/* Kb of disk used by file */
	u_int		na_fsid;	/* device # */
	u_int		na_nodeid;	/* inode # */
	struct irix5_timeval	na_atime;	/* time of last access */
	struct irix5_timeval	na_mtime;	/* time of last modification */
	struct irix5_timeval	na_ctime;	/* time of last change */
};

/*
 * NFS generic interface. syssgi(SGI_NFS_GENERIC, NFSGI_...);
 */
#define NFSGI_NULL            0 /* NOP */
#define NFSGI_TEST_CMD        1 /* Test command */
#define NFSGI_CHK_EXP_PATH    2 /* Check exported path */
#define NFSGI_LISTEN	      3 /* listen on the given transport for kernel RPC */
#define NFSGI_MANAGER	      4 /* Be an RPC manager thread (blocks) */
#define NFSGI_PRIME_AUTHCACHE 5 /* Prime the nfsauth cache */
#define NFSGI_DROP_CONNECTION 6 /* Drop connections at specificed address */
#define NFSGI_GETTHREADSTATS  99 /* read array of per-thread stats */
#define NFSGI_GETOPSTATS      100 /* read of per-client stats */
#define NFSGI_GETEXISTATS     101 /* read of per-export stats */

/* Opstats extraction interface for user space apps.
 *
 * generation, cookie and cookie must be zero for first call.
 * these must not be touched until last set of stats (eof = 1)
 * is extracted, at which time they should be zero'd and collection
 * can start again from scratch.
 *
 * eof is set to 1 when last set of stats is extracted.
 *
 * If an EIRDM is received when getting the stats, it means that
 * the tree has changed and we have lost our position in the list.
 * Hence we need to bzero generation, cookie and len, and restart
 * the gathering from the start. */
typedef struct nfs_getopstats_args {
#if (_MIPS_SZLONG == 32)
       	char		*nga_pad;	/* MUST BE ZERO */
       	char		*nga_buf;
#endif
#if (_MIPS_SZLONG == 64)
	char		*nga_buf;
#endif
	uint32_t	nga_tree_generation; /* persistent */
	uint32_t	nga_int_generation;  /* internal */
	int64_t		nga_buflen;
	int64_t		nga_cookielen;
	int64_t		nga_eof;
#define NGA_MAXCOOKIELEN	16
	char		nga_cookie[NGA_MAXCOOKIELEN];
} nfs_getopstats_args_t;

/* A pointer to one of these is passed as the argument to NFSGI_PRIME_AUTHCACHE */
struct nfs_primeauth_args {
        int             npa_access;     /* access bitmask */
	char		npa_netid[28];	/* transport name, e.g. "udp", "tcp6" */
	int		npa_addrlen;	/* address length */
	char	    	npa_addr[128];	/* sizeof(struct sockaddr_storage) */
        char            npa_path[1024]; /* MAXPATHLEN */
};

/* A pointer to one of these is passed as the argument to NFSGI_LISTEN */
struct nfs_listen_args {
	int		nla_fd; 	/* optional file descriptor (BSD socket) or -1 */
	int		nla_nconns;	/* optional maximal number of connections or 0 */
	char		nla_netid[28];	/* transport name, e.g. "udp", "tcp6" */
	int		nla_addrlen;	/* optional bind address or addrlen=0 */
	char	    	nla_addr[128];	/* sizeof(struct sockaddr_storage) */
};

#ifdef _KERNEL
#include <sys/kmem.h>
#include <sys/vnode.h>

#define n2v_type(x)	(NA_ISFIFO(x) ? VFIFO : ntype_to_vtype(((x)->na_type)))

enum vtype;
extern enum nfsftype	vtype_to_ntype(enum vtype);
extern enum vtype	ntype_to_vtype(enum nfsftype);
#endif

#define n2v_rdev(x)	(nfs_expdev(NA_ISFIFO(x) ? 0 : (x)->na_rdev))

/*
 * Arguments to remote read
 */
struct nfsreadargs {
	fhandle_t	ra_fhandle;	/* handle for file */
	u_int		ra_offset;	/* byte offset in file */
	u_int		ra_count;	/* immediate read count */
	u_int		ra_totcount;	/* total read cnt (from this offset) */
};

/*
 * Status OK portion of remote read reply
 */
struct nfsrrok {
	struct nfsfattr	rrok_attr;	/* attributes, need for pagin */
	u_int		rrok_count;	/* bytes of data */
	u_int		rrok_bsize;	/* buffer memory size */
	char		*rrok_data;	/* data (up to NFS_MAXDATA bytes) */
#ifdef _KERNEL
	struct buf	*rrok_bp;	/* buffer for copy avoidance */
#endif /* _KERNEL */
};

/*
 * Reply from remote read
 */
struct nfsrdresult {
	enum nfsstat	rr_status;		/* status of read */
	union {
		struct nfsrrok	rr_ok_u;	/* attributes, need for pagin */
	} rr_u;
};
#define	rr_ok		rr_u.rr_ok_u
#define	rr_attr		rr_u.rr_ok_u.rrok_attr
#define	rr_count	rr_u.rr_ok_u.rrok_count
#define	rr_data		rr_u.rr_ok_u.rrok_data
#define	rr_bsize	rr_u.rr_ok_u.rrok_bsize
#define rr_bp		rr_u.rr_ok_u.rrok_bp


/*
 * File attributes which can be set
 */
struct nfssattr {
	u_int		sa_mode;	/* protection mode bits */
	u_int		sa_uid;		/* owner user id */
	u_int		sa_gid;		/* owner group id */
	u_int		sa_size;	/* file size in bytes */
	struct irix5_timeval	sa_atime;	/* time of last access */
	struct irix5_timeval	sa_mtime;	/* time of last modification */
};


/*
 * Reply status with file attributes
 */
struct nfsattrstat {
	enum nfsstat	ns_status;		/* reply status */
	union {
		struct nfsfattr ns_attr_u;	/* NFS_OK: file attributes */
	} ns_u;
};
#define	ns_attr	ns_u.ns_attr_u


/*
 * NFS_OK part of read sym link reply union
 */
struct nfssrok {
	u_long	srok_count;	/* size of string */
	char	*srok_data;	/* string (up to NFS_MAXPATHLEN bytes) */
};

/*
 * Result of reading symbolic link
 */
struct nfsrdlnres {
	enum nfsstat	rl_status;		/* status of symlink read */
	union {
		struct nfssrok	rl_srok_u;	/* name of linked to */
	} rl_u;
};
#define	rl_srok		rl_u.rl_srok_u
#define	rl_count	rl_u.rl_srok_u.srok_count
#define	rl_data		rl_u.rl_srok_u.srok_data


/*
 * Arguments to readdir
 */
struct nfsrddirargs {
	fhandle_t rda_fh;	/* directory handle */
	u_int rda_offset;	/* offset in directory (opaque) */
	u_int rda_count;	/* number of directory bytes to read */
};

/*
 * NFS_OK part of readdir result
 */
struct nfsrdok {
	u_long	rdok_offset;		/* next offset (opaque) */
	u_long	rdok_size;		/* size in bytes of entries */
	bool_t	rdok_eof;		/* true if last entry is in result */
	struct dirent *rdok_entries;	/* variable number of entries */
	short	rdok_segflg;		/* transaction is to go to user space */
	u_char	rdok_abi;		/* Abi of calling process - */
					/* valid if segflg == userspace */
};

/*
 * Readdir result
 */
struct nfsrddirres {
	u_long		rd_bufsize;	/* client request size (not xdr'ed) */
	enum nfsstat	rd_status;
	union {
		struct nfsrdok rd_rdok_u;
	} rd_u;
};
#define	rd_rdok		rd_u.rd_rdok_u
#define	rd_offset	rd_u.rd_rdok_u.rdok_offset
#define	rd_size		rd_u.rd_rdok_u.rdok_size
#define	rd_eof		rd_u.rd_rdok_u.rdok_eof
#define	rd_entries	rd_u.rd_rdok_u.rdok_entries
#define	rd_abi		rd_u.rd_rdok_u.rdok_abi
#define	rd_segflg	rd_u.rd_rdok_u.rdok_segflg

/*
 * Arguments for directory operations
 */
struct nfsdiropargs {
	fhandle_t	da_fhandle;	/* directory file handle */
	char		*da_name;	/* name (up to NFS_MAXNAMLEN bytes) */
};

/*
 * NFS_OK part of directory operation result
 */
struct  nfsdrok {
	fhandle_t	drok_fhandle;	/* result file handle */
	struct nfsfattr	drok_attr;	/* result file attributes */
};

/*
 * Results from directory operation
 */
struct  nfsdiropres {
	enum nfsstat	dr_status;	/* result status */
	union {
		struct  nfsdrok	dr_drok_u;	/* NFS_OK result */
	} dr_u;
};
#define	dr_drok		dr_u.dr_drok_u
#define	dr_fhandle	dr_u.dr_drok_u.drok_fhandle
#define	dr_attr		dr_u.dr_drok_u.drok_attr

/*
 * arguments to setattr
 */
struct nfssaargs {
	fhandle_t	saa_fh;		/* fhandle of file to be set */
	struct nfssattr	saa_sa;		/* new attributes */
};

/*
 * arguments to create and mkdir
 */
struct nfscreatargs {
	struct nfsdiropargs	ca_da;	/* file name to create and parent dir */
	struct nfssattr		ca_sa;	/* initial attributes */
};

/*
 * arguments to link
 */
struct nfslinkargs {
	fhandle_t		la_from;	/* old file */
	struct nfsdiropargs	la_to;		/* new file and parent dir */
};

/*
 * arguments to rename
 */
struct nfsrnmargs {
	struct nfsdiropargs rna_from;	/* old file and parent dir */
	struct nfsdiropargs rna_to;	/* new file and parent dir */
};

/*
 * arguments to symlink
 */
struct nfsslargs {
	struct nfsdiropargs	sla_from;	/* old file and parent dir */
	char			*sla_tnm;	/* new name */
	struct nfssattr		sla_sa;		/* attributes */
};

/*
 * NFS_OK part of statfs operation
 */
struct nfsstatfsok {
	u_long fsok_tsize;	/* preferred transfer size in bytes */
	u_long fsok_bsize;	/* fundamental file system block size */
	u_long fsok_blocks;	/* total blocks in file system */
	u_long fsok_bfree;	/* free blocks in fs */
	u_long fsok_bavail;	/* free blocks avail to non-superuser */
};

/*
 * Results of statfs operation
 */
struct nfsstatfs {
	enum nfsstat	fs_status;	/* result status */
	union {
		struct	nfsstatfsok fs_fsok_u;	/* NFS_OK result */
	} fs_u;
};
#define	fs_fsok		fs_u.fs_fsok_u
#define	fs_tsize	fs_u.fs_fsok_u.fsok_tsize
#define	fs_bsize	fs_u.fs_fsok_u.fsok_bsize
#define	fs_blocks	fs_u.fs_fsok_u.fsok_blocks
#define	fs_bfree	fs_u.fs_fsok_u.fsok_bfree
#define	fs_bavail	fs_u.fs_fsok_u.fsok_bavail

/*
 * XDR routines for handling structures defined above
 */
#ifdef _KERNEL
struct __kxdr_s;
struct export;
extern bool_t xdr_attrstat(struct __kxdr_s *, struct nfsattrstat *);
extern bool_t xdr_creatargs(struct __kxdr_s *, struct nfscreatargs *);
extern bool_t xdr_diropargs(struct __kxdr_s *, struct nfsdiropargs *);
extern bool_t xdr_diropres(struct __kxdr_s *, struct nfsdiropres *);
extern bool_t xdr_drok(struct __kxdr_s *, struct nfsdrok *);
extern bool_t xdr_fattr(struct __kxdr_s *, struct nfsfattr *);
extern bool_t xdr_fhandle(struct __kxdr_s *, fhandle_t *);
extern bool_t xdr_fsok(struct __kxdr_s *, struct nfsstatfsok *);
extern bool_t xdr_linkargs(struct __kxdr_s *, struct nfslinkargs *);
extern bool_t xdr_rddirargs(struct __kxdr_s *, struct nfsrddirargs *);
extern bool_t xdr_putrddirres(struct __kxdr_s *, struct nfsrddirres *);
extern bool_t xdr_getrddirres(struct __kxdr_s *, struct nfsrddirres *);
extern bool_t xdr_rdlnres(struct __kxdr_s *, struct nfsrdlnres *);
extern bool_t xdr_rdresult(struct __kxdr_s *, struct nfsrdresult *);
extern bool_t xdr_readargs(struct __kxdr_s *, struct nfsreadargs *);
extern bool_t xdr_rnmargs(struct __kxdr_s *, struct nfsrnmargs *);
extern bool_t xdr_rrok(struct __kxdr_s *, struct nfsrrok *);
extern bool_t xdr_saargs(struct __kxdr_s *, struct nfssaargs *);
extern bool_t xdr_sattr(struct __kxdr_s *, struct nfssattr *);
extern bool_t xdr_slargs(struct __kxdr_s *, struct nfsslargs *);
extern bool_t xdr_srok(struct __kxdr_s *, struct nfssrok *);
extern bool_t xdr_irix5_timeval(struct __kxdr_s *, struct irix5_timeval *);
extern bool_t xdr_writeargs(struct __kxdr_s *, struct nfswriteargs *);
extern bool_t xdr_statfs(struct __kxdr_s *, struct nfsstatfs *);

extern void	sattr_to_vattr(struct nfssattr *, struct vattr *);
extern int	vattr_to_nattr(struct vattr *, struct nfsfattr *,
			struct export *);

#endif

/*
 * Remote file service routines for NFS v2
 */
#define	RFS_NULL	0
#define	RFS_GETATTR	1
#define	RFS_SETATTR	2
#define	RFS_ROOT	3
#define	RFS_LOOKUP	4
#define	RFS_READLINK	5
#define	RFS_READ	6
#define	RFS_WRITECACHE	7
#define	RFS_WRITE	8
#define	RFS_CREATE	9
#define	RFS_REMOVE	10
#define	RFS_RENAME	11
#define	RFS_LINK	12
#define	RFS_SYMLINK	13
#define	RFS_MKDIR	14
#define	RFS_RMDIR	15
#define	RFS_READDIR	16
#define	RFS_STATFS	17
#define	RFS_NPROC	18

/*
 * remote file service numbers
 */
#define	NFS_PROGRAM	((u_long)100003)
#define	NFS_VERSION	((u_long)2)
#define	NFS3_VERSION	((u_long)3)
#define	NFS_PORT	2049

/*
 * Version 3 declarations and definitions.
 */

#define NFS3_FHSIZE	64
#define NFS3_COOKIEVERFSIZE 8
#define NFS3_CREATEVERFSIZE 8
#define NFS3_WRITEVERFSIZE 8
#define MAX_READ_BLOCKS 8

typedef char *filename3;

typedef char *nfspath3;

typedef __uint64_t fileid3;

typedef __uint64_t cookie3;

typedef __uint32_t uid3;

typedef __uint32_t gid3;

typedef __uint64_t size3;

typedef __uint64_t offset3;

typedef __uint32_t mode3;

typedef __uint32_t count3;

typedef __uint32_t uint32;

typedef char cookieverf3[NFS3_COOKIEVERFSIZE];

typedef char createverf3[NFS3_CREATEVERFSIZE];

typedef char writeverf3[NFS3_WRITEVERFSIZE];

/*
 * Maximum file size. This is a direct plagerism of xfs header files. 
 * and the XFS_BIG_FILES stuff.
 * for files > 2^40-1, we need pgno_t to be 64 bits.
 * if bits(pgno_t == 64 max is 2^63 - 1 
 * else 2^40 - 1 (40=31+9) 
 * Note, we allow seeks to this offset, although you can't read or write.
 */

#if _MIPS_SIM != _ABI64
#define NFS3_MAX_FILE_OFFSET     ((1LL<<40)-1LL)
#else
#define NFS3_MAX_FILE_OFFSET     ((long long)((1ULL<<63)-1ULL))
#endif

#define	MAXOFF_T	NFS3_MAX_FILE_OFFSET

#define	PAGESIZE	NBPC
#define PAGEOFFSET	(PAGESIZE - 1)

#define IS_SWAPVP(vp)	(vp->v_flag & VISSWAP)

struct nfs_fh3 {
	u_int fh3_length;
	union nfs_fh3_u {
		struct nfs_fh3_i {
			fhandle_t fh3_i;
		} nfs_fh3_i;
		char data[NFS3_FHSIZE];
	} fh3_u;
};
#define fh3_fsid        fh3_u.nfs_fh3_i.fh3_i.fh_fsid
#define fh3_len         fh3_u.nfs_fh3_i.fh3_i.fh_len /* fid length */
#define fh3_data        fh3_u.nfs_fh3_i.fh3_i.fh_data /* fid bytes */
#define fh3_xlen        fh3_u.nfs_fh3_i.fh3_i.fh_xlen
#define fh3_xdata       fh3_u.nfs_fh3_i.fh3_i.fh_xdata
typedef struct nfs_fh3 nfs_fh3;

struct diropargs3 {
        nfs_fh3 dir;
        filename3 name;
};
typedef struct diropargs3 diropargs3;

struct nfstime3 {
        __uint32_t seconds;
        __uint32_t nseconds;
};
typedef struct nfstime3 nfstime3;

struct specdata3 {
        __uint32_t specdata1;
        __uint32_t specdata2;
};
typedef struct specdata3 specdata3;

enum nfsstat3 {
        NFS3_OK = 0,
        NFS3ERR_PERM = 1,
        NFS3ERR_NOENT = 2,
        NFS3ERR_IO = 5,
        NFS3ERR_NXIO = 6,
        NFS3ERR_ACCES = 13,
        NFS3ERR_EXIST = 17,
        NFS3ERR_XDEV = 18,
        NFS3ERR_NODEV = 19,
        NFS3ERR_NOTDIR = 20,
        NFS3ERR_ISDIR = 21,
        NFS3ERR_INVAL = 22,
        NFS3ERR_FBIG = 27,
        NFS3ERR_NOSPC = 28,
        NFS3ERR_ROFS = 30,
        NFS3ERR_MLINK = 31,
        NFS3ERR_NAMETOOLONG = 63,
        NFS3ERR_NOTEMPTY = 66,
        NFS3ERR_DQUOT = 69,
        NFS3ERR_STALE = 70,
        NFS3ERR_REMOTE = 71,
	NFS3ERR_NOATTR = 1009,
        NFS3ERR_BADHANDLE = 10001,
        NFS3ERR_NOT_SYNC = 10002,
        NFS3ERR_BAD_COOKIE = 10003,
        NFS3ERR_NOTSUPP = 10004,
        NFS3ERR_TOOSMALL = 10005,
        NFS3ERR_SERVERFAULT = 10006,
        NFS3ERR_BADTYPE = 10007,
        NFS3ERR_JUKEBOX = 10008
};
typedef enum nfsstat3 nfsstat3;

enum ftype3 {
	NF3NONE = 0,
        NF3REG = 1,
        NF3DIR = 2,
        NF3BLK = 3,
        NF3CHR = 4,
        NF3LNK = 5,
        NF3SOCK = 6,
        NF3FIFO = 7
};
typedef enum ftype3 ftype3;

struct fattr3 {
        ftype3 type;
        mode3 mode;
        __uint32_t nlink;
        uid3 uid;
        gid3 gid;
        size3 size;
        size3 used;
        specdata3 rdev;
        __uint64_t fsid;
        fileid3 fileid;
        nfstime3 atime;
        nfstime3 mtime;
        nfstime3 ctime;
};
typedef struct fattr3 fattr3;

struct post_op_attr {
        bool_t attributes;
        fattr3 attr;
};
typedef struct post_op_attr post_op_attr;

struct wcc_attr {
        size3 size;
        nfstime3 mtime;
        nfstime3 ctime;
};
typedef struct wcc_attr wcc_attr;

struct pre_op_attr {
        bool_t attributes;
        wcc_attr attr;
};
typedef struct pre_op_attr pre_op_attr;

struct wcc_data {
	pre_op_attr before;
	post_op_attr after;
};
typedef struct wcc_data wcc_data;

struct post_op_fh3 {
	bool_t handle_follows;
	nfs_fh3 handle;
};
typedef struct post_op_fh3 post_op_fh3;

enum time_how {
	DONT_CHANGE = 0,
	SET_TO_SERVER_TIME = 1,
	SET_TO_CLIENT_TIME = 2
};
typedef enum time_how time_how;

struct set_mode3 {
	bool_t set_it;
	mode3 mode;
};
typedef struct set_mode3 set_mode3;

struct set_uid3 {
	bool_t set_it;
	uid3 uid;
};
typedef struct set_uid3 set_uid3;

struct set_gid3 {
	bool_t set_it;
	gid3 gid;
};
typedef struct set_gid3 set_gid3;

struct set_size3 {
	bool_t set_it;
	size3 size;
};
typedef struct set_size3 set_size3;

struct set_atime {
	time_how set_it;
	nfstime3 atime;
};
typedef struct set_atime set_atime;

struct set_mtime {
	time_how set_it;
	nfstime3 mtime;
};
typedef struct set_mtime set_mtime;

struct sattr3 {
	set_mode3 mode;
	set_uid3 uid;
	set_gid3 gid;
	set_size3 size;
	set_atime atime;
	set_mtime mtime;
};
typedef struct sattr3 sattr3;

/*
 * A couple of defines to make resok and resfail look like the
 * correct things in a response type independent manner.
 */
#define resok   res_u.ok
#define resfail res_u.fail

struct GETATTR3args {
	nfs_fh3 object;
};
typedef struct GETATTR3args GETATTR3args;

struct GETATTR3resok {
	fattr3 obj_attributes;
};
typedef struct GETATTR3resok GETATTR3resok;

struct GETATTR3res {
	nfsstat3 status;
	union {
		GETATTR3resok ok;
	} res_u;
};
typedef struct GETATTR3res GETATTR3res;

struct sattrguard3 {
	bool_t check;
	nfstime3 obj_ctime;
};
typedef struct sattrguard3 sattrguard3;

struct SETATTR3args {
	nfs_fh3 object;
	sattr3 new_attributes;
	sattrguard3 guard;
};
typedef struct SETATTR3args SETATTR3args;

struct SETATTR3resok {
	wcc_data obj_wcc;
};
typedef struct SETATTR3resok SETATTR3resok;

struct SETATTR3resfail {
	wcc_data obj_wcc;
};
typedef struct SETATTR3resfail SETATTR3resfail;

struct SETATTR3res {
	nfsstat3 status;
	union {
		SETATTR3resok ok;
		SETATTR3resfail fail;
	} res_u;
};
typedef struct SETATTR3res SETATTR3res;

struct LOOKUP3args {
	diropargs3 what;
};
typedef struct LOOKUP3args LOOKUP3args;

struct LOOKUP3resok {
	nfs_fh3 object;
	post_op_attr obj_attributes;
	post_op_attr dir_attributes;
};
typedef struct LOOKUP3resok LOOKUP3resok;

struct LOOKUP3resfail {
	post_op_attr dir_attributes;
};
typedef struct LOOKUP3resfail LOOKUP3resfail;

struct LOOKUP3res {
	nfsstat3 status;
	union {
		LOOKUP3resok ok;
		LOOKUP3resfail fail;
	} res_u;
};
typedef struct LOOKUP3res LOOKUP3res;

struct ACCESS3args {
	nfs_fh3 object;
	uint32 access;
};
typedef struct ACCESS3args ACCESS3args;
#define	ACCESS3_READ 0x1
#define	ACCESS3_LOOKUP 0x2
#define	ACCESS3_MODIFY 0x4
#define	ACCESS3_EXTEND 0x8
#define	ACCESS3_DELETE 0x10
#define	ACCESS3_EXECUTE 0x20

struct ACCESS3resok {
	post_op_attr obj_attributes;
	uint32 access;
};
typedef struct ACCESS3resok ACCESS3resok;

struct ACCESS3resfail {
	post_op_attr obj_attributes;
};
typedef struct ACCESS3resfail ACCESS3resfail;

struct ACCESS3res {
	nfsstat3 status;
	union {
		ACCESS3resok ok;
		ACCESS3resfail fail;
	} res_u;
};
typedef struct ACCESS3res ACCESS3res;

struct READLINK3args {
	nfs_fh3 symlink;
};
typedef struct READLINK3args READLINK3args;

struct READLINK3resok {
	post_op_attr symlink_attributes;
	nfspath3 data;
};
typedef struct READLINK3resok READLINK3resok;

struct READLINK3resfail {
	post_op_attr symlink_attributes;
};
typedef struct READLINK3resfail READLINK3resfail;

struct READLINK3res {
	nfsstat3 status;
	union {
		READLINK3resok ok;
		READLINK3resfail fail;
	} res_u;
};
typedef struct READLINK3res READLINK3res;

struct READ3args {
	nfs_fh3 file;
	offset3 offset;
	count3 count;
};
typedef struct READ3args READ3args;

struct READ3resok {
	post_op_attr file_attributes;
	count3 count;
	bool_t eof;
	struct {
		u_int data_len;
		char *data_val;
	} data;
#ifdef _KERNEL
	struct buf	*bp;	/* buffer for copy avoidance */
	u_int		pboff;	/* buffer page offset */
#endif /* _KERNEL */
};
typedef struct READ3resok READ3resok;

struct READ3resfail {
	post_op_attr file_attributes;
};
typedef struct READ3resfail READ3resfail;

struct READ3res {
	nfsstat3 status;
	union {
		READ3resok ok;
		READ3resfail fail;
	} res_u;
};
typedef struct READ3res READ3res;

enum stable_how {
	UNSTABLE = 0,
	DATA_SYNC = 1,
	FILE_SYNC = 2
};
typedef enum stable_how stable_how;

struct WRITE3args {
	nfs_fh3 file;
	offset3 offset;
	count3 count;
	stable_how stable;
	struct {
		u_int data_len;
		char *data_val;
		char  putbuf_ok;	/* can we use xdrmbuf_putbuf? */
	} data;
#ifdef _KERNEL
	struct uio uio;
#endif /* _KERNEL */
};
typedef struct WRITE3args WRITE3args;

struct WRITE3resok {
	wcc_data file_wcc;
	count3 count;
	stable_how committed;
	writeverf3 verf;
};
typedef struct WRITE3resok WRITE3resok;

struct WRITE3resfail {
	wcc_data file_wcc;
};
typedef struct WRITE3resfail WRITE3resfail;

struct WRITE3res {
	nfsstat3 status;
	union {
		WRITE3resok ok;
		WRITE3resfail fail;
	} res_u;
};
typedef struct WRITE3res WRITE3res;

enum createmode3 {
	UNCHECKED = 0,
	GUARDED = 1,
	EXCLUSIVE = 2
};
typedef enum createmode3 createmode3;

struct createhow3 {
	createmode3 mode;
	union {
		sattr3 obj_attributes;
		createverf3 verf;
	} createhow3_u;
};
typedef struct createhow3 createhow3;

struct CREATE3args {
	diropargs3 where;
	createhow3 how;
};
typedef struct CREATE3args CREATE3args;

struct CREATE3resok {
	post_op_fh3 obj;
	post_op_attr obj_attributes;
	wcc_data dir_wcc;
};
typedef struct CREATE3resok CREATE3resok;

struct CREATE3resfail {
	wcc_data dir_wcc;
};
typedef struct CREATE3resfail CREATE3resfail;

struct CREATE3res {
	nfsstat3 status;
	union {
		CREATE3resok ok;
		CREATE3resfail fail;
	} res_u;
};
typedef struct CREATE3res CREATE3res;

struct MKDIR3args {
	diropargs3 where;
	sattr3 attributes;
};
typedef struct MKDIR3args MKDIR3args;

struct MKDIR3resok {
	post_op_fh3 obj;
	post_op_attr obj_attributes;
	wcc_data dir_wcc;
};
typedef struct MKDIR3resok MKDIR3resok;

struct MKDIR3resfail {
	wcc_data dir_wcc;
};
typedef struct MKDIR3resfail MKDIR3resfail;

struct MKDIR3res {
	nfsstat3 status;
	union {
		MKDIR3resok ok;
		MKDIR3resfail fail;
	} res_u;
};
typedef struct MKDIR3res MKDIR3res;

struct symlinkdata3 {
	sattr3 symlink_attributes;
	nfspath3 symlink_data;
};
typedef struct symlinkdata3 symlinkdata3;

struct SYMLINK3args {
	diropargs3 where;
	symlinkdata3 symlink;
};
typedef struct SYMLINK3args SYMLINK3args;

struct SYMLINK3resok {
	post_op_fh3 obj;
	post_op_attr obj_attributes;
	wcc_data dir_wcc;
};
typedef struct SYMLINK3resok SYMLINK3resok;

struct SYMLINK3resfail {
	wcc_data dir_wcc;
};
typedef struct SYMLINK3resfail SYMLINK3resfail;

struct SYMLINK3res {
	nfsstat3 status;
	union {
		SYMLINK3resok ok;
		SYMLINK3resfail fail;
	} res_u;
};
typedef struct SYMLINK3res SYMLINK3res;

struct devicedata3 {
	sattr3 dev_attributes;
	specdata3 spec;
};
typedef struct devicedata3 devicedata3;

struct mknoddata3 {
	ftype3 type;
	union {
		devicedata3 device;
		sattr3 pipe_attributes;
	} mknoddata3_u;
};
typedef struct mknoddata3 mknoddata3;

struct MKNOD3args {
	diropargs3 where;
	mknoddata3 what;
};
typedef struct MKNOD3args MKNOD3args;

struct MKNOD3resok {
	post_op_fh3 obj;
	post_op_attr obj_attributes;
	wcc_data dir_wcc;
};
typedef struct MKNOD3resok MKNOD3resok;

struct MKNOD3resfail {
	wcc_data dir_wcc;
};
typedef struct MKNOD3resfail MKNOD3resfail;

struct MKNOD3res {
	nfsstat3 status;
	union {
		MKNOD3resok ok;
		MKNOD3resfail fail;
	} res_u;
};
typedef struct MKNOD3res MKNOD3res;

struct REMOVE3args {
	diropargs3 object;
};
typedef struct REMOVE3args REMOVE3args;

struct REMOVE3resok {
	wcc_data dir_wcc;
};
typedef struct REMOVE3resok REMOVE3resok;

struct REMOVE3resfail {
	wcc_data dir_wcc;
};
typedef struct REMOVE3resfail REMOVE3resfail;

struct REMOVE3res {
	nfsstat3 status;
	union {
		REMOVE3resok ok;
		REMOVE3resfail fail;
	} res_u;
};
typedef struct REMOVE3res REMOVE3res;

struct RMDIR3args {
	diropargs3 object;
};
typedef struct RMDIR3args RMDIR3args;

struct RMDIR3resok {
	wcc_data dir_wcc;
};
typedef struct RMDIR3resok RMDIR3resok;

struct RMDIR3resfail {
	wcc_data dir_wcc;
};
typedef struct RMDIR3resfail RMDIR3resfail;

struct RMDIR3res {
	nfsstat3 status;
	union {
		RMDIR3resok ok;
		RMDIR3resfail fail;
	} res_u;
};
typedef struct RMDIR3res RMDIR3res;

struct RENAME3args {
	diropargs3 from;
	diropargs3 to;
};
typedef struct RENAME3args RENAME3args;

struct RENAME3resok {
	wcc_data fromdir_wcc;
	wcc_data todir_wcc;
};
typedef struct RENAME3resok RENAME3resok;

struct RENAME3resfail {
	wcc_data fromdir_wcc;
	wcc_data todir_wcc;
};
typedef struct RENAME3resfail RENAME3resfail;

struct RENAME3res {
	nfsstat3 status;
	union {
		RENAME3resok ok;
		RENAME3resfail fail;
	} res_u;
};
typedef struct RENAME3res RENAME3res;

struct LINK3args {
	nfs_fh3 file;
	diropargs3 link;
};
typedef struct LINK3args LINK3args;

struct LINK3resok {
	post_op_attr file_attributes;
	wcc_data linkdir_wcc;
};
typedef struct LINK3resok LINK3resok;

struct LINK3resfail {
	post_op_attr file_attributes;
	wcc_data linkdir_wcc;
};
typedef struct LINK3resfail LINK3resfail;

struct LINK3res {
	nfsstat3 status;
	union {
		LINK3resok ok;
		LINK3resfail fail;
	} res_u;
};
typedef struct LINK3res LINK3res;

struct READDIR3args {
	nfs_fh3 dir;
	cookie3 cookie;
	cookieverf3 cookieverf;
	count3 count;
};
typedef struct READDIR3args READDIR3args;

struct entry3 {
	fileid3 fileid;
	filename3 name;
	cookie3 cookie;
	struct entry3 *nextentry;
};
typedef struct entry3 entry3;

struct dirlist3 {
	entry3 *entries;
	bool_t eof;
};
typedef struct dirlist3 dirlist3;

struct READDIR3resok {
	post_op_attr dir_attributes;
	cookieverf3 cookieverf;
	dirlist3 reply;
	u_int size;
	u_int count;
	cookie3 cookie;
	u_char rddir_abi;
};
typedef struct READDIR3resok READDIR3resok;

struct READDIR3resfail {
	post_op_attr dir_attributes;
};
typedef struct READDIR3resfail READDIR3resfail;

struct READDIR3res {
	nfsstat3 status;
	union {
		READDIR3resok ok;
		READDIR3resfail fail;
	} res_u;
};
typedef struct READDIR3res READDIR3res;

struct READDIRPLUS3args {
	nfs_fh3 dir;
	cookie3 cookie;
	cookieverf3 cookieverf;
	count3 dircount;
	count3 maxcount;
};
typedef struct READDIRPLUS3args READDIRPLUS3args;

struct entryplus3 {
	fileid3 fileid;
	filename3 name;
	cookie3 cookie;
	post_op_attr name_attributes;
	post_op_fh3 name_handle;
	struct entryplus3 *nextentry;
};
typedef struct entryplus3 entryplus3;

struct dirlistplus3 {
	entryplus3 *entries;
	bool_t eof;
};
typedef struct dirlistplus3 dirlistplus3;

struct READDIRPLUS3resok {
	post_op_attr dir_attributes;
	cookieverf3 cookieverf;
	dirlistplus3 reply;
	u_int size;
	u_int count;
	u_int unused_left_for_bc_1;
	void *unused_left_for_bc_2;
	void *unused_left_for_bc_3;
	u_char unused_left_for_bc_4;
};
typedef struct READDIRPLUS3resok READDIRPLUS3resok;

struct READDIRPLUS3resfail {
	post_op_attr dir_attributes;
};
typedef struct READDIRPLUS3resfail READDIRPLUS3resfail;

struct READDIRPLUS3res {
	nfsstat3 status;
	union {
		READDIRPLUS3resok ok;
		READDIRPLUS3resfail fail;
	} res_u;
};
typedef struct READDIRPLUS3res READDIRPLUS3res;

struct FSSTAT3args {
	nfs_fh3 fsroot;
};
typedef struct FSSTAT3args FSSTAT3args;

struct FSSTAT3resok {
	post_op_attr obj_attributes;
	size3 tbytes;
	size3 fbytes;
	size3 abytes;
	size3 tfiles;
	size3 ffiles;
	size3 afiles;
	__uint32_t invarsec;
};
typedef struct FSSTAT3resok FSSTAT3resok;

struct FSSTAT3resfail {
	post_op_attr obj_attributes;
};
typedef struct FSSTAT3resfail FSSTAT3resfail;

struct FSSTAT3res {
	nfsstat3 status;
	union {
		FSSTAT3resok ok;
		FSSTAT3resfail fail;
	} res_u;
};
typedef struct FSSTAT3res FSSTAT3res;

struct FSINFO3args {
	nfs_fh3 fsroot;
};
typedef struct FSINFO3args FSINFO3args;

struct FSINFO3resok {
	post_op_attr obj_attributes;
	uint32 rtmax;
	uint32 rtpref;
	uint32 rtmult;
	uint32 wtmax;
	uint32 wtpref;
	uint32 wtmult;
	uint32 dtpref;
	size3 maxfilesize;
	nfstime3 time_delta;
	uint32 properties;
};
typedef struct FSINFO3resok FSINFO3resok;

struct FSINFO3resfail {
	post_op_attr obj_attributes;
};
typedef struct FSINFO3resfail FSINFO3resfail;
#define FSF3_LINK 0x1
#define FSF3_SYMLINK 0x2
#define FSF3_HOMOGENEOUS 0x8
#define FSF3_CANSETTIME 0x10

struct FSINFO3res {
	nfsstat3 status;
	union {
		FSINFO3resok ok;
		FSINFO3resfail fail;
	} res_u;
};
typedef struct FSINFO3res FSINFO3res;

struct PATHCONF3args {
	nfs_fh3 object;
};
typedef struct PATHCONF3args PATHCONF3args;

struct PATHCONF3resok {
	post_op_attr obj_attributes;
	uint32 link_max;
	uint32 name_max;
	bool_t no_trunc;
	bool_t chown_restricted;
	bool_t case_insensitive;
	bool_t case_preserving;
};
typedef struct PATHCONF3resok PATHCONF3resok;

struct PATHCONF3resfail {
	post_op_attr obj_attributes;
};
typedef struct PATHCONF3resfail PATHCONF3resfail;

struct PATHCONF3res {
	nfsstat3 status;
	union {
		PATHCONF3resok ok;
		PATHCONF3resfail fail;
	} res_u;
};
typedef struct PATHCONF3res PATHCONF3res;

struct COMMIT3args {
	nfs_fh3 file;
	offset3 offset;
	count3 count;
};
typedef struct COMMIT3args COMMIT3args;

struct COMMIT3resok {
	wcc_data file_wcc;
	writeverf3 verf;
};
typedef struct COMMIT3resok COMMIT3resok;

struct COMMIT3resfail {
	wcc_data file_wcc;
};
typedef struct COMMIT3resfail COMMIT3resfail;

struct COMMIT3res {
	nfsstat3 status;
	union {
		COMMIT3resok ok;
		COMMIT3resfail fail;
	} res_u;
};
typedef struct COMMIT3res COMMIT3res;


#define NFSPROC3_NULL ((u_long)0)
extern  void * nfsproc3_null_3();
#define NFSPROC3_GETATTR ((u_long)1)
extern  GETATTR3res * nfsproc3_getattr_3();
#define NFSPROC3_SETATTR ((u_long)2)
extern  SETATTR3res * nfsproc3_setattr_3();
#define NFSPROC3_LOOKUP ((u_long)3)
extern  LOOKUP3res * nfsproc3_lookup_3();
#define NFSPROC3_ACCESS ((u_long)4)
extern  ACCESS3res * nfsproc3_access_3();
#define NFSPROC3_READLINK ((u_long)5)
extern  READLINK3res * nfsproc3_readlink_3();
#define NFSPROC3_READ ((u_long)6)
extern  READ3res * nfsproc3_read_3();
#define NFSPROC3_WRITE ((u_long)7)
extern  WRITE3res * nfsproc3_write_3();
#define NFSPROC3_CREATE ((u_long)8)
extern  CREATE3res * nfsproc3_create_3();
#define NFSPROC3_MKDIR ((u_long)9)
extern  MKDIR3res * nfsproc3_mkdir_3();
#define NFSPROC3_SYMLINK ((u_long)10)
#define NFSPROC3_MKNOD ((u_long)11)
extern  MKNOD3res * nfsproc3_mknod_3();
extern  SYMLINK3res * nfsproc3_symlink_3();
#define NFSPROC3_REMOVE ((u_long)12)
extern  REMOVE3res * nfsproc3_remove_3();
#define NFSPROC3_RMDIR ((u_long)13)
extern  RMDIR3res * nfsproc3_rmdir_3();
#define NFSPROC3_RENAME ((u_long)14)
extern  RENAME3res * nfsproc3_rename_3();
#define NFSPROC3_LINK ((u_long)15)
extern  LINK3res * nfsproc3_link_3();
#define NFSPROC3_READDIR ((u_long)16)
extern  READDIR3res * nfsproc3_readdir_3();
#define NFSPROC3_READDIRPLUS ((u_long)17)
extern  READDIRPLUS3res * nfsproc3_readdirplus_3();
#define NFSPROC3_FSSTAT ((u_long)18)
extern  FSSTAT3res * nfsproc3_fsstat_3();
#define NFSPROC3_FSINFO ((u_long)19)
extern  FSINFO3res * nfsproc3_fsinfo_3();
#define NFSPROC3_PATHCONF ((u_long)20)
extern  PATHCONF3res * nfsproc3_pathconf_3();
#define NFSPROC3_COMMIT ((u_long)21)
extern  COMMIT3res * nfsproc3_commit_3();

#ifdef _KERNEL
/* the xdr functions */

#define xdr_nfsstat3(xdrs, objp) kxdr_enum(xdrs, (enum_t *)objp)

extern bool_t xdr_GETATTR3args(struct __kxdr_s *, GETATTR3args *);
extern bool_t xdr_GETATTR3resok(struct __kxdr_s *, GETATTR3resok *);
extern bool_t xdr_GETATTR3res(struct __kxdr_s *, GETATTR3res *);
extern bool_t xdr_sattrguard3(struct __kxdr_s *, sattrguard3 *);
extern bool_t xdr_SETATTR3args(struct __kxdr_s *, SETATTR3args *);
extern bool_t xdr_SETATTR3resok(struct __kxdr_s *, SETATTR3resok *);
extern bool_t xdr_SETATTR3resfail(struct __kxdr_s *, SETATTR3resfail *);
extern bool_t xdr_SETATTR3res(struct __kxdr_s *, SETATTR3res *);
extern bool_t xdr_LOOKUP3args(struct __kxdr_s *, LOOKUP3args *);
extern bool_t xdr_LOOKUP3resok(struct __kxdr_s *, LOOKUP3resok *);
extern bool_t xdr_LOOKUP3resfail(struct __kxdr_s *, LOOKUP3resfail *);
extern bool_t xdr_LOOKUP3res(struct __kxdr_s *, LOOKUP3res *);
extern bool_t xdr_ACCESS3args(struct __kxdr_s *, ACCESS3args *);
extern bool_t xdr_ACCESS3resok(struct __kxdr_s *, ACCESS3resok *);
extern bool_t xdr_ACCESS3resfail(struct __kxdr_s *, ACCESS3resfail *);
extern bool_t xdr_ACCESS3res(struct __kxdr_s *, ACCESS3res *);
extern bool_t xdr_READLINK3args(struct __kxdr_s *, READLINK3args *);
extern bool_t xdr_READLINK3resok(struct __kxdr_s *, READLINK3resok *);
extern bool_t xdr_READLINK3resfail(struct __kxdr_s *, READLINK3resfail *);
extern bool_t xdr_READLINK3res(struct __kxdr_s *, READLINK3res *);
extern bool_t xdr_READ3args(struct __kxdr_s *, READ3args *);
extern bool_t xdr_READ3resok(struct __kxdr_s *, READ3resok *);
extern bool_t xdr_READ3resfail(struct __kxdr_s *, READ3resfail *);
extern bool_t xdr_READ3res(struct __kxdr_s *, READ3res *);
extern bool_t xdr_stable_how(struct __kxdr_s *, stable_how *);
extern bool_t xdr_WRITE3args(struct __kxdr_s *, WRITE3args *);
extern bool_t xdr_WRITE3resok(struct __kxdr_s *, WRITE3resok *);
extern bool_t xdr_WRITE3resfail(struct __kxdr_s *, WRITE3resfail *);
extern bool_t xdr_WRITE3res(struct __kxdr_s *, WRITE3res *);
extern bool_t xdr_createmode3(struct __kxdr_s *, createmode3 *);
extern bool_t xdr_createhow3(struct __kxdr_s *, createhow3 *);
extern bool_t xdr_CREATE3args(struct __kxdr_s *, CREATE3args *);
extern bool_t xdr_CREATE3resok(struct __kxdr_s *, CREATE3resok *);
extern bool_t xdr_CREATE3resfail(struct __kxdr_s *, CREATE3resfail *);
extern bool_t xdr_CREATE3res(struct __kxdr_s *, CREATE3res *);
extern bool_t xdr_MKDIR3args(struct __kxdr_s *, MKDIR3args *);
extern bool_t xdr_MKDIR3resok(struct __kxdr_s *, MKDIR3resok *);
extern bool_t xdr_MKDIR3resfail(struct __kxdr_s *, MKDIR3resfail *);
extern bool_t xdr_MKDIR3res(struct __kxdr_s *, MKDIR3res *);
extern bool_t xdr_symlinkdata3(struct __kxdr_s *, symlinkdata3 *);
extern bool_t xdr_SYMLINK3args(struct __kxdr_s *, SYMLINK3args *);
extern bool_t xdr_SYMLINK3resok(struct __kxdr_s *, SYMLINK3resok *);
extern bool_t xdr_SYMLINK3resfail(struct __kxdr_s *, SYMLINK3resfail *);
extern bool_t xdr_SYMLINK3res(struct __kxdr_s *, SYMLINK3res *);
extern bool_t xdr_devicedata3(struct __kxdr_s *, devicedata3 *);
extern bool_t xdr_mknoddata3(struct __kxdr_s *, mknoddata3 *);
extern bool_t xdr_MKNOD3args(struct __kxdr_s *, MKNOD3args *);
extern bool_t xdr_MKNOD3resok(struct __kxdr_s *, MKNOD3resok *);
extern bool_t xdr_MKNOD3resfail(struct __kxdr_s *, MKNOD3resfail *);
extern bool_t xdr_MKNOD3res(struct __kxdr_s *, MKNOD3res *);
extern bool_t xdr_REMOVE3args(struct __kxdr_s *, REMOVE3args *);
extern bool_t xdr_REMOVE3resok(struct __kxdr_s *, REMOVE3resok *);
extern bool_t xdr_REMOVE3resfail(struct __kxdr_s *, REMOVE3resfail *);
extern bool_t xdr_REMOVE3res(struct __kxdr_s *, REMOVE3res *);
extern bool_t xdr_RMDIR3args(struct __kxdr_s *, RMDIR3args *);
extern bool_t xdr_RMDIR3resok(struct __kxdr_s *, RMDIR3resok *);
extern bool_t xdr_RMDIR3resfail(struct __kxdr_s *, RMDIR3resfail *);
extern bool_t xdr_RMDIR3res(struct __kxdr_s *, RMDIR3res *);
extern bool_t xdr_RENAME3args(struct __kxdr_s *, RENAME3args *);
extern bool_t xdr_RENAME3resok(struct __kxdr_s *, RENAME3resok *);
extern bool_t xdr_RENAME3resfail(struct __kxdr_s *, RENAME3resfail *);
extern bool_t xdr_RENAME3res(struct __kxdr_s *, RENAME3res *);
extern bool_t xdr_LINK3args(struct __kxdr_s *, LINK3args *);
extern bool_t xdr_LINK3resok(struct __kxdr_s *, LINK3resok *);
extern bool_t xdr_LINK3resfail(struct __kxdr_s *, LINK3resfail *);
extern bool_t xdr_LINK3res(struct __kxdr_s *, LINK3res *);
extern bool_t xdr_READDIR3args(struct __kxdr_s *, READDIR3args *);
extern bool_t xdr_putdirlist(struct __kxdr_s *, READDIR3resok *);
extern bool_t xdr_getdirlist(struct __kxdr_s *, READDIR3resok *);
extern bool_t xdr_READDIR3resok(struct __kxdr_s *, READDIR3resok *);
extern bool_t xdr_READDIR3resfail(struct __kxdr_s *, READDIR3resfail *);
extern bool_t xdr_READDIR3res(struct __kxdr_s *, READDIR3res *);
extern bool_t xdr_READDIRPLUS3args(struct __kxdr_s *, READDIRPLUS3args *);
extern int kxdr_encode_rdplus(struct __kxdr_s *, struct dirent *, post_op_attr *, post_op_fh3 *);
extern bool_t xdr_getdirpluslist(struct __kxdr_s *, READDIRPLUS3resok *);
extern bool_t xdr_READDIRPLUS3resok(struct __kxdr_s *, READDIRPLUS3resok *);
extern bool_t xdr_READDIRPLUS3resfail(struct __kxdr_s *, READDIRPLUS3resfail *);
extern bool_t xdr_READDIRPLUS3res(struct __kxdr_s *, READDIRPLUS3res *);
extern bool_t xdr_FSSTAT3args(struct __kxdr_s *, FSSTAT3args *);
extern bool_t xdr_FSSTAT3resok(struct __kxdr_s *, FSSTAT3resok *);
extern bool_t xdr_FSSTAT3resfail(struct __kxdr_s *, FSSTAT3resfail *);
extern bool_t xdr_FSSTAT3res(struct __kxdr_s *, FSSTAT3res *);
extern bool_t xdr_FSINFO3args(struct __kxdr_s *, FSINFO3args *);
extern bool_t xdr_FSINFO3resok(struct __kxdr_s *, FSINFO3resok *);
extern bool_t xdr_FSINFO3resfail(struct __kxdr_s *, FSINFO3resfail *);
extern bool_t xdr_FSINFO3res(struct __kxdr_s *, FSINFO3res *);
extern bool_t xdr_PATHCONF3args(struct __kxdr_s *, PATHCONF3args *);
extern bool_t xdr_PATHCONF3resok(struct __kxdr_s *, PATHCONF3resok *);
extern bool_t xdr_PATHCONF3resfail(struct __kxdr_s *, PATHCONF3resfail *);
extern bool_t xdr_PATHCONF3res(struct __kxdr_s *, PATHCONF3res *);
extern bool_t xdr_COMMIT3args(struct __kxdr_s *, COMMIT3args *);
extern bool_t xdr_COMMIT3resok(struct __kxdr_s *, COMMIT3resok *);
extern bool_t xdr_COMMIT3resfail(struct __kxdr_s *, COMMIT3resfail *);
extern bool_t xdr_COMMIT3res(struct __kxdr_s *, COMMIT3res *);

extern void	vattr_to_wcc_attr(struct vattr *, struct wcc_attr *);
extern void	vattr_to_wcc_data(struct vattr *, struct vattr *,
				struct wcc_data *, struct export *);
extern nfsstat3	puterrno3(int);
extern int	geterrno3(enum nfsstat3);
extern int	nfs3getattr(struct bhv_desc *, struct vattr *, int, struct cred *);
extern void	nfs3_cache_post_op_attr(struct bhv_desc *, post_op_attr *, struct cred *, int *);

typedef union nfs_args_u {
	union {
		struct nfswriteargs v_nfswriteargs;
		struct nfsreadargs v_nfsreadargs;
		struct nfsrddirargs v_nfsrddirargs;
		struct nfsdiropargs v_nfsdiropargs;
		struct nfssaargs v_nfssaargs;
		struct nfscreatargs v_nfscreatargs;
		struct nfslinkargs v_nfslinkargs;
		struct nfsrnmargs v_nfsrnmargs;
		struct nfsslargs v_nfsslargs;
	} v2;
	union {
		struct GETATTR3args v_GETATTR3args;
		struct SETATTR3args v_SETATTR3args;
		struct LOOKUP3args v_LOOKUP3args;
		struct ACCESS3args v_ACCESS3args;
		struct READLINK3args v_READLINK3args;
		struct READ3args v_READ3args;
		struct WRITE3args v_WRITE3args;
		struct CREATE3args v_CREATE3args;
		struct MKDIR3args v_MKDIR3args;
		struct SYMLINK3args v_SYMLINK3args;
		struct MKNOD3args v_MKNOD3args;
		struct REMOVE3args v_REMOVE3args;
		struct RMDIR3args v_RMDIR3args;
		struct RENAME3args v_RENAME3args;
		struct LINK3args v_LINK3args;
		struct READDIR3args v_READDIR3args;
		struct READDIRPLUS3args v_READDIRPLUS3args;
		struct FSSTAT3args v_FSSTAT3args;
		struct FSINFO3args v_FSINFO3args;
		struct PATHCONF3args v_PATHCONF3args;
		struct COMMIT3args v_COMMIT3args;
	} v3;
} nfs_args_t;

typedef union nfs_res_u {
	union {
		enum nfsstat st;
		struct nfsrdlnres v_nfsrdlnres;
		struct nfsrddirres v_nfsrddirres;
		struct nfsdiropres v_nfsdiropres;
	} v2;
	union {
		struct GETATTR3res v_GETATTR3res;
		struct SETATTR3res v_SETATTR3res;
		struct LOOKUP3res v_LOOKUP3res;
		struct ACCESS3res v_ACCESS3res;
		struct READLINK3res v_READLINK3res;
		struct READ3res v_READ3res;
		struct WRITE3res v_WRITE3res;
		struct CREATE3res v_CREATE3res;
		struct MKDIR3res v_MKDIR3res;
		struct SYMLINK3res v_SYMLINK3res;
		struct MKNOD3res v_MKNOD3res;
		struct REMOVE3res v_REMOVE3res;
		struct RMDIR3res v_RMDIR3res;
		struct RENAME3res v_RENAME3res;
		struct LINK3res v_LINK3res;
		struct READDIR3res v_READDIR3res;
		struct READDIRPLUS3res v_READDIRPLUS3res;
		struct FSSTAT3res v_FSSTAT3res;
		struct FSINFO3res v_FSINFO3res;
		struct PATHCONF3res v_PATHCONF3res;
		struct COMMIT3res v_COMMIT3res;
	} v3;
} nfs_res_t;

#endif /* _KERNEL */
#endif /* !__NFS_HEADER__ */
