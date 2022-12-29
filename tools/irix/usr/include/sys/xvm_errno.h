
#ifndef _XVM_ERRNO_H
#define _XVM_ERRNO_H

/**************************************************************************
 *                                                                        *
 *            Copyright (C) 1998-1999, Silicon Graphics, Inc.             *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 **************************************************************************/
#ident "$Revision: 1.57 $"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*
 * xvm_errno.h
 *
 * XVM Errors
 */

#define XVM_ERROR_MAGIC (unsigned)0xbe
#define xvm_error(subsystem, error)     \
	((XVM_ERROR_MAGIC<<24)|((subsystem)<<16)|(error))

typedef enum xvm_subsystem_e {
	XVM_GENERIC = 0,          /* 0: non layer specific */
	XVM_MIRROR,		/* 1: mirror specific errors */
        XVM_IOBREAKUP,         	/* 2: io breakup layer */
        XVM_PAL,		/* 3: pal layer */
	XVM_CONFPATH,		/* 4: configuration path */
	XVM_API,		/* 5: User level API to kernel */
	XVM_HWG,		/* 6: xvm hwgraph layer errors */
	XVM_VE,			/* 7: xvm ve/config manipulation */
	XVM_MULTICAST,		/* 8: xvm multicast layer */
	XVM_LAB,		/* 9: xvm multicast layer */
	XVM_RELOCATION,		/*10: xvm relocation module */
	XVM_TCL,			/* 11: snapshot tcl interp errors */
	XVM_PARSER,			/* 12: Nested XVM CLI Parser errors */
	XVM_SNAPSHOT,		/* 13: xvm copy-on-write snapshot facility */
	XVM_FAILOVER,		/* 14: xvm device path management */
	XVM_LAST = 255		/* 255: last valid subsystem */
} xvm_subsystem_t;

#define	XVM_ENONE         0  			      /* No error. */
#define	XVM_ENOMEM	  xvm_error(XVM_GENERIC, 1)  /* mem alloc failed */
#define	XVM_EFAULT	  xvm_error(XVM_GENERIC, 2)  /* copyin/out error */
#define	XVM_EVERSION      xvm_error(XVM_GENERIC, 3)  /* version mismatch */
#define	XVM_ENOREMOTE     xvm_error(XVM_GENERIC, 4)  /* no remote-io yet */
#define	XVM_EINTR	  xvm_error(XVM_GENERIC, 5)  /* unexpected interrupt */
#define	XVM_EINJECT	  xvm_error(XVM_GENERIC, 6)  /* fault injected */
#define XVM_ENOSPC	  xvm_error(XVM_GENERIC, 7)  /* no space left in
						        user allocated buffer */
#define XVM_EEXIST	  xvm_error(XVM_GENERIC, 8)  /* item already exists */

#define	XVM_EOVERLAP	  xvm_error(XVM_MIRROR, 1)   /* i/o overlaps another */
#define	XVM_EMASTER	  xvm_error(XVM_MIRROR, 2)   /* sync. with master */
#define	XVM_ENOTMASTER	  xvm_error(XVM_MIRROR, 3)   /* io misdirected */
#define	XVM_EREVIVESTOP   xvm_error(XVM_MIRROR, 4)   /* revive stopped! */
#define	XVM_EPROCESSED    xvm_error(XVM_MIRROR, 5)   /* i/o error handled */
#define	XVM_ENOMASTER	  xvm_error(XVM_MIRROR, 6)   /* couldn't determine */
						      /* mirror master */
#define	XVM_ETOOSMALL	  xvm_error(XVM_MIRROR, 7)   /* leg to attach is smaller */
						      /* than mirror */
#define	XVM_ELASTVALID	  xvm_error(XVM_MIRROR, 8)   /* last valid leg in mirror */

	/* io breakup path errors */
#define	XVM_VE_OFFLINE    xvm_error(XVM_IOBREAKUP, 1)/* ve is offline */
#define	XVM_VE_NODEV      xvm_error(XVM_IOBREAKUP, 2)/* i/o to missing ve */
#define	XVM_VE_BOGUS      xvm_error(XVM_IOBREAKUP, 3)/* init val for mrwrites*/
#define	XVM_NO_USER_LICENSE  xvm_error(XVM_IOBREAKUP, 4) /* No user license */
#define	XVM_IORECURS_LIMIT  xvm_error(XVM_IOBREAKUP, 5) /* recursion limit */

	/* pal errors */
#define	XVM_PAL_EIO       xvm_error(XVM_PAL, 1)      /* i/o error */
#define	XVM_EPALNODEV     xvm_error(XVM_PAL, 2)      /* no-such-physvol */
#define	XVM_EPALAGAIN     xvm_error(XVM_PAL, 3)      /* retry-request */
#define	XVM_EPALALTPATH   xvm_error(XVM_PAL, 4)      /* retry on alt path */
#define	XVM_EBADMEDIA	  xvm_error(XVM_PAL, 5)      /* media has problems */
#define	XVM_ERETARGET     xvm_error(XVM_PAL, 6)      /* disk not attached */
#define	XVM_EINTERNAL     xvm_error(XVM_PAL, 7)      /* pal internal error */
#define	XVM_EPALISALTPATH xvm_error(XVM_PAL, 8)      /* is an alternate path */
#define	XVM_EBADLABEL 	  xvm_error(XVM_PAL, 9)      /* problem with label contents */

	/* configuration layer errors */
#define XVM_EPALCONFIG	  xvm_error(XVM_CONFPATH, 1)
#define	XVM_ECONFIG       xvm_error(XVM_CONFPATH, 2) /* generic conf changed */
#define	XVM_ECONFIG_BUSY   xvm_error(XVM_CONFPATH, 3)/* conf in progress */
#define	XVM_EPALCONFIG_BUSY   xvm_error(XVM_CONFPATH, 4) /* conf in progress */

	/* User level API to kernel */
#define	XVMLIB_GEN_VARIABLE_NOT_ALLOCATED   	xvm_error(XVM_API, 1)
#define	XVMLIB_NOT_IMPLEMENTED   		xvm_error(XVM_API, 2)

#define	XVMLIB_CREATE_INVALID_TYPE  		xvm_error(XVM_API, 3)
#define	XVMLIB_GET_VE_LIST_OPENDIR_FAILED  	xvm_error(XVM_API, 4)
#define	XVMLIB_GET_ATTRIBUTES_TYPE_MISMATCH   	xvm_error(XVM_API, 5)

        /*  xvmlib_execute_ioctl errors */
#define XVMLIB_EXECUTE_IOCTL_ACCESS   		xvm_error(XVM_API, 6)
#define XVMLIB_EXECUTE_IOCTL_NOENT   		xvm_error(XVM_API, 7)
#define XVMLIB_EXECUTE_IOCTL_ERRORED   		xvm_error(XVM_API, 8)

        /*  xvmlib_set_ioctl_errors */
#define XVMLIB_SET_IOCTL_MALLOC_FAILED   	xvm_error(XVM_API, 9)

        /*  xvmlabel  write/read volume label errors */
#define XVMLIB_LABEL_INVALID_PATH         	xvm_error(XVM_API, 10)
#define XVMLIB_LABEL_CANNOT_OPEN_VH       	xvm_error(XVM_API, 11)
#define XVMLIB_LABEL_INVALID_VH           	xvm_error(XVM_API, 12)
#define XVMLIB_LABEL_INVALID_VOLUME       	xvm_error(XVM_API, 13)
#define XVMLIB_LABEL_LSEEK_FAILED         	xvm_error(XVM_API, 14)
#define XVMLIB_LABEL_WRITE_FAILED         	xvm_error(XVM_API, 15)
#define XVMLIB_LABEL_READ_FAILED          	xvm_error(XVM_API, 16)
#define XVMLIB_LABEL_DVHTOOL_FAILED       	xvm_error(XVM_API, 17)
#define XVMLIB_LABEL_CANNOT_OPEN_VH_TEMP       	xvm_error(XVM_API, 18)

	/* available error values */
#define XVMLIB_LABEL_FREE1 		  	xvm_error(XVM_API, 18)
#define XVMLIB_LABEL_FREE2 		  	xvm_error(XVM_API, 19)
#define XVMLIB_FREE3    		  	xvm_error(XVM_API, 21)
#define XVMLIB_LABEL_FREE4       	  	xvm_error(XVM_API, 22)

#define XVMLIB_PACK_VH_ERROR              	xvm_error(XVM_API, 20)
#define XVMLIB_LABEL_INVALID_LABEL        	xvm_error(XVM_API, 23)
#define XVMLIB_LABEL_INVALID_UUID         	xvm_error(XVM_API, 24)
#define XVMLIB_LABEL_INVALID_LABEL_SIZES   	xvm_error(XVM_API, 25)
#define	XVMLIB_SWAP_TOOSMALL		 	xvm_error(XVM_API, 26)
#define	XVMLIB_ROOT_TOOSMALL		   	xvm_error(XVM_API, 27)
#define	XVMLIB_CANNOT_GET_ALL_PARTS	   	xvm_error(XVM_API, 28)
#define XVMLIB_LABEL_PHYSVOL 		  	xvm_error(XVM_API, 29)
#define XVMLIB_UNLABEL_PHYSVOL 		  	xvm_error(XVM_API, 30)
#define XVMLIB_API_MISMATCH		  	xvm_error(XVM_API, 31)
#define XVMLIB_INUSE_PARTS		 	xvm_error(XVM_API, 32)
#define XVMLIB_CANNOT_GET_VH		 	xvm_error(XVM_API, 33)
#define XVMLIB_BAD_REGEXP		  	xvm_error(XVM_API, 34)
#define XVMLIB_NO_SUCH_TYPE		 	xvm_error(XVM_API, 35)
#define XVMLIB_CANNOT_SET_VH		 	xvm_error(XVM_API, 36)
#define XVMLIB_NO_SPACE			 	xvm_error(XVM_API, 37)

#define XVMLIB_NOT_OWNER		 	xvm_error(XVM_API, 38)

#define XVMLIB_LABEL_INVALID_GPT                xvm_error(XVM_API, 39)


	/* hwgraph layer errors */

#define XVM_NAMECOL	  xvm_error(XVM_HWG, 1)   /* name collision */
#define XVM_PIECECOL	  xvm_error(XVM_HWG, 2)   /* piece collision */
#define XVM_BADVETYPE	  xvm_error(XVM_HWG, 3)   /* invalid/unknown ve type */
#define XVM_VEHASEDGES	  xvm_error(XVM_HWG, 4)   /* ve has outgoing edges */
#define XVM_NONAME	  xvm_error(XVM_HWG, 5)   /* no such ve/pvol name */
#define XVM_BADREQUEST	  xvm_error(XVM_HWG, 6)   /* invalid xvm_hwg request */
#define XVM_HWGINTERNAL	  xvm_error(XVM_HWG, 7)   /* internal hwgraph error */
#define XVM_EINVAL	  xvm_error(XVM_HWG, 8)   /* invalid hwg argument */
#define XVM_INITFAILURE   xvm_error(XVM_HWG, 9)   /* error in xvm_init() */
#define XVM_RESERVED	  xvm_error(XVM_HWG, 10)  /* name is reserved */
#define XVM_LIMIT	  xvm_error(XVM_HWG, 11)  /* no more edges present */

	/* configuration and ve-manip layer errors */

#define XVM_CONFIG_IN_PROGRESS    xvm_error(XVM_VE, 1)
#define XVM_OPEN_SUBVOL		  xvm_error(XVM_VE, 2)
#define XVM_NOSPACE		  xvm_error(XVM_VE, 3)
#define XVM_SLICE_OVERLAP	  xvm_error(XVM_VE, 4)
#define XVM_NOT_SECT_MULTIPLE     xvm_error(XVM_VE, 5)
#define XVM_MULTICAST_NOT_INITIALIZED   xvm_error(XVM_VE, 6)
#define XVM_OP_NOT_SUPPORTED	  xvm_error(XVM_VE, 7)
#define XVM_INVCURSOR		  xvm_error(XVM_VE, 8)
#define XVM_NOT_A_VE		  xvm_error(XVM_VE, 9)
#define XVM_NOT_A_PHYSVOL	  xvm_error(XVM_VE, 10)
#define XVM_BAD_VEMAGIC		  xvm_error(XVM_VE, 11)
#define XVM_AMBIGUOUS_NAME	  xvm_error(XVM_VE, 12)
#define XVM_TREE_TOO_DEEP	  xvm_error(XVM_VE, 13)
#define XVM_TOO_MANY_PIECES	  xvm_error(XVM_VE, 14)
#define XVM_INVALID_PIECE	  xvm_error(XVM_VE, 15)
#define XVM_SYSTYPE_OVERLAP	  xvm_error(XVM_VE, 16)
#define XVM_CFG_INTERNAL	  xvm_error(XVM_VE, 17)
#define XVM_INVALID_VE		  xvm_error(XVM_VE, 18)
#define XVM_ORPHAN_VE		  xvm_error(XVM_VE, 19)
#define XVM_VE_HASPIECES	  xvm_error(XVM_VE, 20)
#define XVM_INSERT_HASPIECES	  xvm_error(XVM_VE, 21)
#define XVM_NOT_AUTOPROMOTED	  xvm_error(XVM_VE, 22)
#define XVM_COLLAPSE_TOOMANYPIECES	  xvm_error(XVM_VE, 23)
#define XVM_INVALID_NAME	  xvm_error(XVM_VE, 24)
#define XVM_REMAKE_INVALIDPIECES	  xvm_error(XVM_VE, 25)
#define XVM_PIECE_OUTOFRANGE	  xvm_error(XVM_VE, 26)
#define XVM_BAD_PVMAGIC		  xvm_error(XVM_VE, 27)
#define XVM_PIECE_NOT_OCCUPIED    xvm_error(XVM_VE, 28)
#define XVM_UUID_COLLISION	  xvm_error(XVM_VE, 29)
#define XVM_NO_ATTACHMENT	  xvm_error(XVM_VE, 30)
#define XVM_CIRCULAR_ATTACH	  xvm_error(XVM_VE, 31)
#define XVM_ATTACH_AFFECTS_LAYOUT	  xvm_error(XVM_VE, 32)
#define XVM_SUBVOL_WILLGO_OFFLINE	  xvm_error(XVM_VE, 33)
#define XVM_ATTACH_AFFECTS_STATE	  xvm_error(XVM_VE, 34)
#define XVM_SLICE_ISSWAPPART		  xvm_error(XVM_VE, 35)
#define XVM_CANT_NAME_SYSSV	  xvm_error(XVM_VE, 36)
#define XVM_ALREADY_ATTACHED	  xvm_error(XVM_VE, 37)
#define XVM_MULTIPLY_LISTED	  xvm_error(XVM_VE, 38)
#define XVM_INVALID_MIRROR	  xvm_error(XVM_VE, 39)
#define XVM_REVIVE_BUSY		  xvm_error(XVM_VE, 40)
#define XVM_MIRROR_TOO_WIDE	  xvm_error(XVM_VE, 41)
#define XVM_INTERFACE_USAGE	  xvm_error(XVM_VE, 42)
#define XVM_EINJECT_NOT_ENABLED   xvm_error(XVM_VE, 43)
#define XVM_VE_DISABLED		  xvm_error(XVM_VE, 44)
#define XVM_VE_INCOMPLETE	  xvm_error(XVM_VE, 45)
#define XVM_VE_CANT_BRING_ONLINE  xvm_error(XVM_VE, 46)
#define XVM_PERMISSION_ERROR	  xvm_error(XVM_VE, 47)
#define XVM_NOVOL		  xvm_error(XVM_VE, 48)
#define XVM_INVALID_DOMAIN	  xvm_error(XVM_VE, 49)
#define XVM_NOT_A_DISK		  xvm_error(XVM_VE, 50)
#define XVM_DOMAIN_MISMATCH	  xvm_error(XVM_VE, 51)
#define XVM_NO_LICENSE		  xvm_error(XVM_VE, 52)
#define XVM_DEV_CREATION_FAILED	  xvm_error(XVM_VE, 53)

	/* xvm failover errors */
#define	XVM_FO_UUID_MISMATCH	xvm_error(XVM_FAILOVER,1)	/* config error, dev found in group with differing uuid */
#define XVM_FO_NODEV		xvm_error(XVM_FAILOVER,2)	/* device not found */
#define XVM_FO_EINVAL		xvm_error(XVM_FAILOVER,3)	/* invalid argument */
#define XVM_FO_NO_PREFERRED_MEMBER xvm_error(XVM_FAILOVER,4)	/* no preferred member */
#define XVM_FO_NO_MATCHING_AFFINITY xvm_error(XVM_FAILOVER,5)	/* no device of specified affinity */
#define XVM_FO_UUID_NOT_FOUND	xvm_error(XVM_FAILOVER,6)	/* uuid in failover group not found */
#define XVM_FO_NOT_A_PHYSVOL	xvm_error(XVM_FAILOVER,7)	/* not a physvol */
#define XVM_FO_PHYDATA_NOT_FOUND xvm_error(XVM_FAILOVER,8)	/* physdata not found */
#define XVM_FO_EAGAIN		xvm_error(XVM_FAILOVER,9)	/* try again */
#define XVM_FO_GROUP_NOT_FOUND	xvm_error(XVM_FAILOVER,10)	/* no group for specified dev */
#define XVM_FO_NOT_AVT		xvm_error(XVM_FAILOVER,11)	/* device is not in avt mode */
#define XVM_FO_SWITCH_PATHS_EXHAUSTED	xvm_error(XVM_FAILOVER,12)	/* paths exhausted */
#define XVM_FO_AFFINITY_SWITCH_FAILED	xvm_error(XVM_FAILOVER,13)	/* switch to affinity failed */

        /*  Kernel Primitive Errors */
#define XVMLIB_PRIM_MULTIPLE_NAMES        	xvm_error(XVM_API, 26)

	/* multicast specific errors */

#define XVM_CELLDOWN		  xvm_error(XVM_MULTICAST, 1)
#define XVM_SERVER_REQ_FAILED	  xvm_error(XVM_MULTICAST, 2)
#define XVM_NO_OBJECT		  xvm_error(XVM_MULTICAST, 3)
#define XVM_OBJECT_UUID		  xvm_error(XVM_MULTICAST, 4)
#define XVM_CLIENT_CALL_BROADCAST   xvm_error(XVM_MULTICAST, 5)
#define XVM_REISSUE_REQUEST	  xvm_error(XVM_MULTICAST, 6)
#define XVM_MIGRATING		  xvm_error(XVM_MULTICAST, 7)
#define XVM_INVALID_CELL	  xvm_error(XVM_MULTICAST, 8)
#define XVM_NOT_SERVER		  xvm_error(XVM_MULTICAST, 9)
#define XVM_IPC_ERROR		  xvm_error(XVM_MULTICAST, 10)
#define XVM_SHUTDOWN		  xvm_error(XVM_MULTICAST, 11)
#define XVM_INVALCFGTYPE	  xvm_error(XVM_MULTICAST, 12)
#define XVM_UNKNOWN_FACILITY	  xvm_error(XVM_MULTICAST, 13)

	/* label path errors */
#define XVM_ELABEL_NOSPACE	  xvm_error(XVM_LAB, 1)
#define XVM_ELABEL_NOTFOUND	  xvm_error(XVM_LAB, 2)
#define XVM_CANTREAD_LABEL	  xvm_error(XVM_LAB, 3)

	/* relocation specific errors */
#define XVM_ESTART_RELOCATION	  xvm_error(XVM_RELOCATION, 1)

	/* Tcl errors */
#define XVM_TCL_SCRIPT_ERROR   xvm_error(XVM_TCL, 1)
#define XVM_TCL_CONFIG_ERROR   xvm_error(XVM_TCL, 2)

	/* Nested CLI parser error */
#define XVM_PARSER_ERROR   xvm_error(XVM_PARSER, 1)

	/* Copy-on-write snapshot errors */
#define XVM_SNAP_LIMIT			  xvm_error(XVM_SNAPSHOT, 1)
#define XVM_CANT_MOUNT_REPOSITORY	  xvm_error(XVM_SNAPSHOT, 2)
#define XVM_CANT_ALLOC_SNAP_PRIV	  xvm_error(XVM_SNAPSHOT, 3)
#define XVM_CANT_ALLOC_REGMAP		  xvm_error(XVM_SNAPSHOT, 4)
#define XVM_CANT_OPEN_REPOSITORY	  xvm_error(XVM_SNAPSHOT, 5)
#define XVM_CANT_ALLOC_VE		  xvm_error(XVM_SNAPSHOT, 6)
#define XVM_CANT_GET_SUBVOL		  xvm_error(XVM_SNAPSHOT, 7)
#define XVM_CANT_GET_COW_VE		  xvm_error(XVM_SNAPSHOT, 8)
#define XVM_CANT_GEN_REGMAP		  xvm_error(XVM_SNAPSHOT, 9)
#define XVM_CANT_RSV_REGION		  xvm_error(XVM_SNAPSHOT, 10)
#define XVM_CANT_UNRSV_REGION		  xvm_error(XVM_SNAPSHOT, 11)
#define XVM_CANT_LOCK_REGION		  xvm_error(XVM_SNAPSHOT, 12)
#define XVM_CANT_UNLOCK_REGION		  xvm_error(XVM_SNAPSHOT, 13)
#define XVM_CANT_COPY_REGION		  xvm_error(XVM_SNAPSHOT, 14)
#define XVM_CANT_READ_REPOSITORY	  xvm_error(XVM_SNAPSHOT, 15)
#define XVM_CANT_WRITE_REPOSITORY	  xvm_error(XVM_SNAPSHOT, 16)
#define XVM_CANT_CHANGE_REPOSITORY	  xvm_error(XVM_SNAPSHOT, 17)
#define XVM_CANT_CHANGE_REGSZ		  xvm_error(XVM_SNAPSHOT, 18)
#define XVM_SNAPSHOT_CREATE		  xvm_error(XVM_SNAPSHOT, 19)
#define XVM_SNAPSHOT_CONFIG		  xvm_error(XVM_SNAPSHOT, 20)
#define XVM_CANT_FREEZE			  xvm_error(XVM_SNAPSHOT, 21)
#define XVM_CANT_UNFREEZE		  xvm_error(XVM_SNAPSHOT, 22)
#define XVM_SNAP_LICENSE		  xvm_error(XVM_SNAPSHOT, 23)
#define XVM_MAX_SPACE			  xvm_error(XVM_SNAPSHOT, 24)
#define XVM_COW_NOT_INITIALIZED		  xvm_error(XVM_SNAPSHOT, 25)
#define XVM_BASE_CONFIG			  xvm_error(XVM_SNAPSHOT, 26)
#define XVM_REPOSITORY_CONFIG		  xvm_error(XVM_SNAPSHOT, 27)
#define XVM_SNAP_SNAPSHOT		  xvm_error(XVM_SNAPSHOT, 28)
#define XVM_REP_SNAP_OR_COW		  xvm_error(XVM_SNAPSHOT, 29)
#define XVM_CANT_READ_SB		  xvm_error(XVM_SNAPSHOT, 30)
#define XVM_CANT_SET_ROOT_ATTR		  xvm_error(XVM_SNAPSHOT, 31)
#define XVM_CANT_ADD_BUF_AVOID		  xvm_error(XVM_SNAPSHOT, 32)
#define XVM_REPOSITORY_DISABLED		  xvm_error(XVM_SNAPSHOT, 33)
#define XVM_REPOSITORY_REQUIRED		  xvm_error(XVM_SNAPSHOT, 34)
#define XVM_RDWR			  xvm_error(XVM_SNAPSHOT, 35)
#define XVM_BMAP			  xvm_error(XVM_SNAPSHOT, 36)
#define XVM_ADDR			  xvm_error(XVM_SNAPSHOT, 37)

#define XVM_LAST_ERROR    xvm_error(XVM_LAST, 0xffff) /* end of error range */

typedef unsigned int xvm_errno_t;

/*
 * Define a table of xvm_errno_t to strings.  In order to get the table
 * declared, #define XVM_ERRMSG_DECL before including this file.  Generally
 * only 1 module should set XVM_ERRMSG_DECL to declare space for the table.
 * In user space, xvmlib.c defines XVM_ERRMSG_DECL.  In the kernel,
 * xvm.c defines XVM_ERRMSG_DECL.
 *
 * To convert an xvm_errno_t to its error string, use xvm_error_message().
 *
 * This allows user and kernel code to make use of these error strings, and
 * also places the table close to the xvm_errno_t enum, making it easier to
 * keep up to date.
 */

#ifdef XVM_ERRMSG_DECL
/*
 * Declare as static - in case multiple declarations happen.
 */

typedef struct xvm_errnomap_s {
	xvm_errno_t	err;
	char		*errmsg;
} xvm_errnomap_t;

static xvm_errnomap_t xvm_errnomap[] = {
	/* generic errors non-layer specific */
	{ XVM_ENONE,
		"xvm no error" },
	{ XVM_ENOMEM,
		"kmem memory allocation failed" },
	{ XVM_EFAULT,
		"copyin/copyout error between kernel and api" },
	{ XVM_EVERSION,
		"io request version mismatch" },
	{ XVM_ENOREMOTE,
		"xvm has no access to disk on xvm server)" },
	{ XVM_EINTR,
		"operation was interrupted" },
	{ XVM_EINJECT,
		"operation failed due to fault injection" },
	{ XVM_EEXIST,
		"operation failed because object already exists" },

	/* mirror specific errors */
	{ XVM_EOVERLAP,
		"i/o overlaps with another request" },
	{ XVM_EMASTER,
		"mirror synchronization with master is required" },
	{ XVM_ENOTMASTER,
		"mirror i/o directed towards a non-master" },
	{ XVM_EREVIVESTOP,
		"mirror revive prematurely stopped" },
	{ XVM_EPROCESSED,
		"mirror i/o error already processed" },
	{ XVM_ENOMASTER,
		"could not determine the mirror master cell" },
	{ XVM_ETOOSMALL,
	        "size of attach is smaller than existing mirror"  },
	{ XVM_ELASTVALID,
	        "operation leaves no valid legs in mirror" },

	/* io breakup path errors */
	{ XVM_VE_OFFLINE,
		"volume element offline" },
	{ XVM_VE_NODEV,
		"no such volume element" },
	{ XVM_VE_BOGUS,
		"error initialization value (should never be returned)" },
	{ XVM_NO_USER_LICENSE,
		"no user license" },
	{ XVM_IORECURS_LIMIT,
		"XVM internal error: I/O recursion limit exceeded" },

	/* pal errors */
	{ XVM_PAL_EIO,
		"pal i/o error" },
	{ XVM_EPALNODEV,
		"no such physvol" },
	{ XVM_EPALAGAIN,
		"retry request" },
	{ XVM_EPALALTPATH,
		"retry on alt path" },
	{ XVM_EBADMEDIA,
		"device media error" },
	{ XVM_ERETARGET,
		"retarget request to new server" },
	{ XVM_EPALISALTPATH,
		"is an alternate path" },
	{ XVM_EBADLABEL,
		"resulting label would be invalid" },

	/* configuration layer errors */
	{ XVM_EPALCONFIG,
		"PAL config changed" },
	{ XVM_ECONFIG,
		"generic config changed" },
	{ XVM_ECONFIG_BUSY,
		"configuration or cellup in process" },
	{ XVM_EPALCONFIG_BUSY,
		"physical volume is being configured" },

	/* User level API to kernel */
	{ XVMLIB_GEN_VARIABLE_NOT_ALLOCATED,
		"XVMLIB API called with unallocated variable" },
	{ XVMLIB_NOT_IMPLEMENTED,
		"routine not implemented" },

	{ XVMLIB_CREATE_INVALID_TYPE,
		"xvmlib_get_ve_list:  Invalid VE TYPE specified" },
	{ XVMLIB_GET_VE_LIST_OPENDIR_FAILED,
		"xvmlib get ve list opendir failed" },
        { XVMLIB_GET_ATTRIBUTES_TYPE_MISMATCH,
		"xvmlib get attributes type mismatch" },

        /*  xvmlib_execute_ioctl errors */
        { XVMLIB_EXECUTE_IOCTL_ACCESS,
		"Cannot open XVM control device.  Permission denied." },
        { XVMLIB_EXECUTE_IOCTL_NOENT,
		"XVM not installed on this system." },
        { XVMLIB_EXECUTE_IOCTL_ERRORED,
		"xvmlib_execute_ioctl: system call failed." },


        /*  xvmlib_set_ioctl_errors */
        { XVMLIB_SET_IOCTL_MALLOC_FAILED,
		"xvmlib_set_ioctl:  calloc failed" },

        /*  xvmlabel write/read volume label errors */
        { XVMLIB_LABEL_INVALID_PATH,
		"The specified disk does not exist." },
        { XVMLIB_LABEL_CANNOT_OPEN_VH,
		"Cannot open the disk volume header." },
        { XVMLIB_LABEL_INVALID_VH,
		"The disk volume header partition is invalid." },
        { XVMLIB_LABEL_INVALID_VOLUME,
		"The disk volume partition is invalid." },
        { XVMLIB_LABEL_LSEEK_FAILED,
		"Cannot seek to the XVM label area." },
        { XVMLIB_LABEL_WRITE_FAILED,
		"Unable to write the XVM label information." },
        { XVMLIB_LABEL_READ_FAILED,
		"Unable to read the XVM label information." },
        { XVMLIB_LABEL_DVHTOOL_FAILED,
		"The dvhtool command failed." },
        { XVMLIB_LABEL_CANNOT_OPEN_VH_TEMP,
		"Cannot open a temp file to copy vol header."},
        { XVMLIB_LABEL_PHYSVOL,
		"Cannot re-label an XVM physical volume." },
        { XVMLIB_UNLABEL_PHYSVOL,
		"disk contains a physical volume which is in use." },
        { XVMLIB_PACK_VH_ERROR,
		"An error occured while compacting the volume header." },
        { XVMLIB_LABEL_INVALID_LABEL,
		"The specified disk is not an XVM physical volume." },
        { XVMLIB_LABEL_INVALID_UUID,
		"Could not generate a correct uuid for the label." },
        { XVMLIB_LABEL_INVALID_LABEL_SIZES,
		"Invalid label parameters specified." },
	{ XVMLIB_SWAP_TOOSMALL,
		"label defined swap size is too small." },
	{ XVMLIB_ROOT_TOOSMALL,
		"label defined root size is too small." },
	{ XVMLIB_CANNOT_GET_ALL_PARTS,
		"cannot get all requested partitions for system disk." },
	{ XVMLIB_API_MISMATCH,
		"kernel/user api version mismatch." },
	{ XVMLIB_INUSE_PARTS,
		"disk has partitions that are in use." },
	{ XVMLIB_CANNOT_GET_VH,
		"cannot retrieve the disk volume header." },
	{ XVMLIB_BAD_REGEXP,
		"invalid regular expression in object name." },
	{ XVMLIB_NO_SUCH_TYPE,
		"no names matching the given type." },
	{ XVMLIB_CANNOT_SET_VH,
		"cannot set the disk volume header." },
	{ XVMLIB_NO_SPACE,
		"not enough space on device." },
	{ XVMLIB_NOT_OWNER,
		"owner or domain specified not current owner." },
	{ XVMLIB_LABEL_INVALID_GPT,
		"gpt label not usable by xvm." },

	/* hwgraph layer errors */

	{ XVM_NAMECOL,
		"name collision - ve or physvol name already exists" },
	{ XVM_PIECECOL,
		"piece collision - piece already exists" },
	{ XVM_BADVETYPE,
		"invalid ve type" },
	{ XVM_VEHASEDGES,
		"ve/physvol is not empty" },
	{ XVM_NONAME,
		"no object matching the specified name" },
	{ XVM_BADREQUEST,
		"invalid xvm hwgraph layer request" },
	{ XVM_HWGINTERNAL,
		"hardware graph internal error" },
	{ XVM_EINVAL,
		"invalid argument" },
	{ XVM_RESERVED,
		"ve/physvol name is reserved" },

	{ XVM_LIMIT,
		"no more edges found" },

	/* ve manipulation/configuration errors */

	{ XVM_CONFIG_IN_PROGRESS,
		"configuration change is currently in progress" },
	{ XVM_OPEN_SUBVOL,
		"subvolume of target ve is currently open" },
	{ XVM_NOSPACE,
		"no free area large enough on physvol" },
	{ XVM_SLICE_OVERLAP,
		"slice request overlaps an existing slice on physvol" },
	{ XVM_NOT_SECT_MULTIPLE,
		"slice start and/or length not a sector multiple" },
	{ XVM_MULTICAST_NOT_INITIALIZED,
		"xvm multicast layer not initialized yet - try again" },
	{ XVM_OP_NOT_SUPPORTED,
		"operation not supported by the kernel yet" },
	{ XVM_INVCURSOR,
		"stale ve/physvol cursor - retry the operation" },
	{ XVM_NOT_A_VE,
		"object is not a ve" },
	{ XVM_NOT_A_PHYSVOL,
		"object is not a physvol" },
	{ XVM_BAD_VEMAGIC,
		"ve structure is NULL or has a bad magic number" },
	{ XVM_AMBIGUOUS_NAME,
		"object name is ambiguous" },
	{ XVM_TREE_TOO_DEEP,
		"operation would exceed maximum tree depth" },
	{ XVM_TOO_MANY_PIECES,
		"Too many pieces" },
	{ XVM_INVALID_PIECE,
		"Invalid piece number" },
	{ XVM_SYSTYPE_OVERLAP,
		"System subvolume types must be unique" },
	{ XVM_CFG_INTERNAL,
		"Internal kernel configuration error" },
	{ XVM_INVALID_VE,
		"Invalid ve type for operation" },
	{ XVM_ORPHAN_VE,
		"Ve is an orphan" },
	{ XVM_VE_HASPIECES,
		"Ve has attached pieces" },
	{ XVM_INSERT_HASPIECES,
		"Ve to insert must have zero pieces" },
	{ XVM_NOT_AUTOPROMOTED,
		"one or more source ve's are not autopromoted" },
	{ XVM_COLLAPSE_TOOMANYPIECES,
		"Ve to collapse must have only one piece" },
	{ XVM_INVALID_NAME,
		"Invalid name supplied" },
	{ XVM_REMAKE_INVALIDPIECES,
		"Incorrect number of pieces supplied to remake" },
	{ XVM_PIECE_OUTOFRANGE,
		"Out of range piece number" },
	{ XVM_BAD_PVMAGIC,
		"physvol struct is NULL or has a bad magic number" },
	{ XVM_PIECE_NOT_OCCUPIED,
		"specified piece is not occupied" },
	{ XVM_UUID_COLLISION,
		"specified uuid is already in use" },
	{ XVM_NO_ATTACHMENT,
		"physvol is not directly connected on this cell" },
	{ XVM_CIRCULAR_ATTACH,
		"operation will cause a circular topology" },
	{ XVM_ATTACH_AFFECTS_LAYOUT,
		"operation will change the data layout of an ancestor ve" },
	{ XVM_SUBVOL_WILLGO_OFFLINE,
		"operation will cause the ve's subvolume to go offline" },
	{ XVM_ATTACH_AFFECTS_STATE,
		"operation will cause an ancestor ve to go offline" },
	{ XVM_SLICE_ISSWAPPART,
		"slice corresponds to the swap partition" },
	{ XVM_CANT_NAME_SYSSV,
		"cannot name system subvolumes" },
	{ XVM_ALREADY_ATTACHED,
		"ve is already attached to the target" },
	{ XVM_MULTIPLY_LISTED,
		"ve is listed multiple times in the source list" },
	{ XVM_INVALID_MIRROR,
		"operation results in an invalid mirror configuration" },
	{ XVM_REVIVE_BUSY,
		"mirror ve is being revived" },
	{ XVM_MIRROR_TOO_WIDE,
		"mirror ve's are limited to 8 children" },
	{ XVM_INTERFACE_USAGE,
		"improper use of interface" },
	{ XVM_EINJECT_NOT_ENABLED,
		"xvm kernel error injection not enabled on one or more targeted cells" },
	{ XVM_VE_DISABLED,
		"ve is disabled" },
	{ XVM_VE_INCOMPLETE,
		"ve is incomplete" },
	{ XVM_VE_CANT_BRING_ONLINE,
		"ve cannot be brought back online" },
	{ XVM_PERMISSION_ERROR,
		"permission denied - operation is not allowed by the "
		"current user" },
	{ XVM_NOVOL,
		"not valid operation on volumes.  Set at or "
		"below the subvolume level" },
	{ XVM_INVALID_DOMAIN,
		"domain name is invalid or unavailable" },
	{ XVM_NOT_A_DISK,
		"object name is not a disk" },
	{ XVM_DOMAIN_MISMATCH,
		"domain of ve does not match its parent ve or physvol" },
	{ XVM_NO_LICENSE,
		"mirror creation and usage requires a plexing license" },
	{ XVM_DEV_CREATION_FAILED,
		"device file could not be created" },

        /*  Kernel Primitive Errors */

        { XVMLIB_PRIM_MULTIPLE_NAMES,
		"xvmlib primitive multiple names" },

	/* Multicast errors */

	{ XVM_CELLDOWN,
		"xvm multicast layer detected cell down" },

	{ XVM_SERVER_REQ_FAILED,
		"xvm multicast layer detected server rejected request" },

	{ XVM_NO_OBJECT,
		"multicast layer detected invalid multicast object" },

	{ XVM_OBJECT_UUID,
		"no multicast object for given UUID" },

	{ XVM_INVALID_CELL,
		"The indicated cell is not part of the membership." },

	{ XVM_SHUTDOWN,
		" The membership is being shutdown." },

	{ XVM_INVALCFGTYPE,
		" received an invalid mc_cfg_t type." },

	{ XVM_UNKNOWN_FACILITY,
		" received an unknown multicast facility.  Probably downrev node." },

	{ XVM_MIGRATING,
		"object is being relocated" },

	{ XVM_ELABEL_NOSPACE,
		"attempt to issue i/o beyond XVM label area" },

	{ XVM_ELABEL_NOTFOUND,
		"expected label entry was not found" },

	{ XVM_CANTREAD_LABEL,
		"can't read label into label cache" },

	{ XVM_TCL_SCRIPT_ERROR,
		"error in Tcl script" },

	{ XVM_TCL_CONFIG_ERROR,
		"error in snapshot Tcl configuration" },

	{ XVM_PARSER_ERROR,
		"error in nested XVM call" },

	/* Copy-on-write snapshot errors */

	{ XVM_SNAP_LIMIT,
		"too many snapshots for volume" },

	{ XVM_CANT_MOUNT_REPOSITORY,
		"can't mount repository" },

	{ XVM_CANT_ALLOC_SNAP_PRIV,
		"can't allocate private area for snapshot" },

	{ XVM_CANT_ALLOC_REGMAP,
		"can't allocate region map for snapshot" },

	{ XVM_CANT_OPEN_REPOSITORY,
		"can't open repository" },

	{ XVM_CANT_ALLOC_VE,
		"can't alloc ve while creating snapshot" },

	{ XVM_CANT_GET_SUBVOL,
		"can't get subvol ve for snapshot" },

	{ XVM_CANT_GET_COW_VE,
		"can't get cow ve for snapshot" },

	{ XVM_CANT_GEN_REGMAP,
		"getbmap error while generating region map for snapshot" },

	{ XVM_CANT_RSV_REGION,
		"error while reserving snapshot repository space" },

	{ XVM_CANT_UNRSV_REGION,
		"error while unreserving snapshot repository space" },

	{ XVM_CANT_LOCK_REGION,
		"can't lock repository region" },

	{ XVM_CANT_UNLOCK_REGION,
		"can't unlock repository region" },

	{ XVM_CANT_COPY_REGION,
		"can't copy snapshot region" },

	{ XVM_CANT_READ_REPOSITORY,
		"can't read to snapshot repository" },

	{ XVM_CANT_WRITE_REPOSITORY,
		"can't write to snapshot repository" },

	{ XVM_CANT_CHANGE_REPOSITORY,
		"the repository may not be changed on an existing snapshot" },

	{ XVM_SNAPSHOT_CREATE,
		"snapshot and copy-on-write ve-s may not be created or "
			"deleted directly" },

	{ XVM_SNAPSHOT_CONFIG,
		"can't perform direct operations on snapshot volumes" },

	{ XVM_CANT_FREEZE,
		"can't freeze filesystem" },

	{ XVM_CANT_UNFREEZE,
		"can't unfreeze filesystem" },

	{ XVM_SNAP_LICENSE,
		"no snapshot license" },

	{ XVM_MAX_SPACE,
		"maximum licensed snapshot space exceeded" },

	{ XVM_COW_NOT_INITIALIZED,
		"xvm not yet initialized - try again." },

	{ XVM_BASE_CONFIG,
		"can't change configuration of a volume being snapshotted" },

	{ XVM_REPOSITORY_CONFIG,
		"can't remove part of a snapshot repository" },

	{ XVM_SNAP_SNAPSHOT,
		"can't snapshot a snapshot or repository volume" },

	{ XVM_REP_SNAP_OR_COW,
	        "can't use a snapshot or base volume for a repository volume" },

	{ XVM_CANT_READ_SB,
	        "can't read superblock of snapshot volume" },

	{ XVM_CANT_SET_ROOT_ATTR,
	        "can't set root attribute on snapshot volume" },

	{ XVM_CANT_ADD_BUF_AVOID,
	        "can't add subvol to buffer avoid list" },

	{ XVM_REPOSITORY_DISABLED,
	        "snapshot disabled" },

	{ XVM_REPOSITORY_REQUIRED,
	        "repository required for snapshot" },

	{ XVM_RDWR,
	        "read/write to xvm volume for snapshot failed" },

	{ XVM_BMAP,
	        "can't get extent info for repository file" },

	{ XVM_ADDR,
	        "can't get address from alenlist" },

	/* xvm failover errors */
	{ XVM_FO_UUID_MISMATCH,
		"failover: dev found in fo group with wrong uuid" },
	{ XVM_FO_NODEV,
		"failover: device not found" },
	{ XVM_FO_EINVAL,
		"failover: invalid argument" },
	{ XVM_FO_NO_PREFERRED_MEMBER,
		"failover: group has no preferred member" },
	{ XVM_FO_NO_MATCHING_AFFINITY,
		"failover: no device of specified affinity" },
	{ XVM_FO_UUID_NOT_FOUND,
		"failover: unable to locate uuid associated with failover group" },
	{ XVM_FO_NOT_A_PHYSVOL,
		"failover: not a physvol" },
	{ XVM_FO_PHYDATA_NOT_FOUND,
		"failover: physvol has no associated physdata" },
	{ XVM_FO_EAGAIN,
		"failover: potentially recoverable error, try again" },
	{ XVM_FO_GROUP_NOT_FOUND,
		"failover: device not in xvm failover group" },
	{ XVM_FO_NOT_AVT,
		"failover: device not in avt mode, try [x]scsifo" },
	{ XVM_FO_SWITCH_PATHS_EXHAUSTED,
		"failover: can't fail over - paths exhausted" },
	{ XVM_FO_AFFINITY_SWITCH_FAILED,
		"failover: switch to specified affinity failed" },

	/* LAST ERROR!!!!!!!!!!!!!!!!!!!!!!!!! */

	{ XVM_LAST_ERROR,
		"unknown xvm error" }
};


char *
xvm_error_message(xvm_errno_t error_code)
{
	xvm_errnomap_t	*mp;
	static char     unknown_err[128];

	for (mp = xvm_errnomap; mp->err != error_code &&
				mp->err != XVM_LAST_ERROR; mp++) {
		;
	}

	if (mp->err == XVM_LAST_ERROR) {
		sprintf((char *)unknown_err, "%s (0x%x)",
			mp->errmsg, error_code);
		return unknown_err;
	} else {
		return mp->errmsg;
	}
}
#endif /* XVM_ERRMSG_DECL */

/*
 * External prototype for xvm_error_message()
 */

extern char *xvm_error_message(xvm_errno_t error_code);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _XVM_ERRNO_H */

