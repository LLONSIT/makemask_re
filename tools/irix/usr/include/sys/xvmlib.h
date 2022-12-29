#ifndef __XVMLIB_H__
#define __XVMLIB_H__

/**************************************************************************
 *                                                                        *
 *            Copyright (C) 1999, Silicon Graphics, Inc.                  *
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

#ifdef _KERNEL
#   include <xvm_platform_defs.h>
#else
#   include <sys/xvm_user_platform_defs.h>
#endif

#include <sys/xvm_typedefs.h>

#ifdef _KERNEL
#   ifdef _HAVE_XVM_SYS_HEADERS_
#       include <xvm_sys_headers.h>
#   else
#       include <sys/types.h>
#       include <sys/uuid.h>
#       include <invent.h>
#   endif /* _HAVE_XVM_SYS_HEADERS_ */
#else /* ! _KERNEL */
#   ifdef _HAVE_XVM_USER_SYS_HEADERS_
#       include <xvm_user_sys_headers.h>
#   else
#       include <sys/types.h>
#       include <sys/uuid.h>
#       include <invent.h>
#   endif /* _HAVE_XVM_USER_SYS_HEADERS_ */
#endif

#include <sys/xvm_base.h>
#include <sys/xvm_errno.h>

#define	XVMLIB_NAMESIZE	VE_EDGE_NAME_MAX

typedef uint16_t     xvm_apivers_t;

#define XVM_API_VERSION	24		/* version must fit in 16 bits */

/*
 * generic xvm object id
 *
 * Note the size of id_name.  It is *2 because subvolume names must include
 * the volume name as well (eg. vol/data).
 */

typedef struct xvm_id_s {
	char		id_name[XVMLIB_NAMESIZE*2];

	uuid_t		id_uuid;	/* ve/physvol uuid */

        uint8_t		id_type;	/* object type */
	uchar_t		id_permname:1,	/* object name is permanent */
			id_unused:7;
	uint8_t		id_domain;	/* domain object lives in */
	uchar_t		pad[5];
} xvm_id_t;

/*
 * generic ve info structure - encapsulates all the ve types (not including
 * physvols)
 */

typedef struct xvm_veinfo_s {
	xvm_id_t	ve_vol;			/* vol this ve is part of */
	xvm_id_t	ve_subvol;		/* subvol this ve is part of */
						/* n/a if ve is a volume */
	xvm_id_t	ve_parent;		/* parent - n/a if ve is vol */

	uint64_t	ve_size;		/* size in 512 byte blocks */

	uint16_t	ve_pieces;
	uint16_t	ve_mypiece;		/* ve's position under parent */
	xvm_tid_t	ve_tid;

	uint8_t		ve_state;		/* ve state */
	uint8_t		ve_type;
	uint16_t	ve_iou;			/* io unit (sectorsize) */
	uchar_t		ve_partition;		/* partition number (slice) */
	uchar_t		ve_pad[3];		/* padding */

	uint32_t	ve_validstat : 1,	/* ve has valid ve_stat */
			ve_mrprimary : 1,	/* ve is mirror primary memb */
			ve_open      : 1,	/* part of an open subvol */
			ve_inconsistent : 1,	/* ve is inconsistent */
			ve_name      : 1,	/* ve has persistent name */
			ve_attachable : 1,	/* ve can be attached without */
						/* detaching first */
			ve_incomplete : 1,	/* ve has missing pieces */
			ve_childoffline : 1,	/* ve has an offline child */
			ve_disabled : 1,	/* ve is disabled */
			ve_online : 1,		/* ve is online */
			ve_mediaerror : 1,	/* ve has encountered errors */
			ve_reviving : 1,	/* child mirror is reviving */
			ve_rootslice : 1,	/* ve is a root slice */
			ve_swapslice : 1,	/* ve is a swap slice */
			ve_usrslice : 1,	/* ve is a usr slice */
			ve_validpart : 1,	/* ve_partition is valid */
			ve_snapshot : 1,	/* ve is part of snapshot vol */
			ve_base : 1,		/* ve is part of base vol */
			ve_repository : 1,	/* ve is part of repository */
			ve_loc_mediaerror: 1,   /* local mediaerror encountered */
			ve_loc_nodev: 1,	/* no local connection to physical device */
			ve_extrabits : 11;	/* unused bits */
	ve_stat_t	ve_stat;		/* stats (if ve_validstat !0) */

	/*
	 * Type-specific information.  Type is stored in ve_id.id_type;
	 * Elements should be padded to 64 bits.
	 */
	
	union {
		struct {
			xvm_uid_t	sv_uid;
			xvm_gid_t	sv_gid;

			xvm_mode_t	sv_mode;
			uint8_t		sv_ve_type;
			uint32_t	sv_autopromoted : 1,
				        sv_extrabits : 31;
			char            sv_pad[4];
		} subvol;
                struct {
			xvm_id_t	cw_repid;	/* id of repository */
			uint16_t	cw_first;	/* first cow ord */
			uint16_t	cw_next;	/* next cow ord */
			uint16_t	cw_regsz;	/* region size */
			uchar_t		cw_pad[2];
                } cow;
                struct {
			xvm_id_t	sn_cowid;	/* id of cow ve */
			uint32_t	sn_index;	/* snapshot index */
			uint32_t	sn_ctime;	/* creation time */
                } snapshot;
		struct {
			uint32_t	st_susize;
			uchar_t		st_pad1[4];
		} stripe;

		struct {
			xvm_id_t	sl_physvol;
			uint64_t	sl_start;	/* length is ve_size */
		} slice;

		struct {
			uint16_t	vo_svmap;
			uint16_t	vo_autopromoted : 1,
				        vo_extrabits : 15;
			uint16_t	vo_repcnt;	/* number of base 
							 * volumes using this
							 * volume as a 
							 * repository */
			uint8_t		vo_repfull;	/* repository full
							   recovery method */
			uchar_t		vo_pad[1];
			uint32_t	vo_rephold;	/* rep hold count */
			uchar_t		vo_pad1[8];
		} vol;

		struct {
			uint16_t	mr_unused1;
			uint16_t	mr_rpolicy;
			uint8_t		mr_config;

			uchar_t		mr_reviving : 1,
					mr_hasprimary : 1,
					mr_revivequeued : 1,
					mr_no_license : 1,
					unused : 4;
			uchar_t		mr_pad[3];
			cell_t		mr_mastercell;
			uint16_t	mr_primary;

			uint64_t	mr_revive_startblk;
			uint64_t	mr_revive_endblk;
			uint64_t	mr_revive_blkno;
		} mirror;

		/*
		 * No specific info for these types yet, they are listed
		 * here just for completeness.
		 */

		struct {
			uchar_t	pad[8];
		} raid, concat;
	} ve_spec;
} xvm_veinfo_t;

#define subvol_uid		ve_spec.subvol.sv_uid
#define subvol_gid		ve_spec.subvol.sv_gid
#define subvol_mode		ve_spec.subvol.sv_mode
#define subvol_type		ve_spec.subvol.sv_ve_type
#define subvol_autopromoted	ve_spec.subvol.sv_autopromoted
#define cow_repid		ve_spec.cow.cw_repid
#define cow_first		ve_spec.cow.cw_first
#define cow_next		ve_spec.cow.cw_next
#define cow_regsz		ve_spec.cow.cw_regsz
#define snapshot_cowid          ve_spec.snapshot.sn_cowid
#define snapshot_index          ve_spec.snapshot.sn_index
#define snapshot_ctime          ve_spec.snapshot.sn_ctime
#define stripe_susize		ve_spec.stripe.st_susize
#define slice_physvol		ve_spec.slice.sl_physvol
#define slice_start		ve_spec.slice.sl_start
#define vol_svmap		ve_spec.vol.vo_svmap
#define vol_autopromoted	ve_spec.vol.vo_autopromoted
#define vol_repcnt		ve_spec.vol.vo_repcnt
#define vol_repfull		ve_spec.vol.vo_repfull
#define vol_rephold		ve_spec.vol.vo_rephold
#define mirror_rpolicy		ve_spec.mirror.mr_rpolicy
#define mirror_config		ve_spec.mirror.mr_config
#define mirror_reviving		ve_spec.mirror.mr_reviving
#define mirror_revivequeued	ve_spec.mirror.mr_revivequeued
#define mirror_no_license	ve_spec.mirror.mr_no_license
#define mirror_hasprimary	ve_spec.mirror.mr_hasprimary
#define mirror_primary		ve_spec.mirror.mr_primary
#define mirror_mastercell	ve_spec.mirror.mr_mastercell
#define mirror_revive_startblk	ve_spec.mirror.mr_revive_startblk
#define mirror_revive_endblk	ve_spec.mirror.mr_revive_endblk
#define mirror_revive_blkno	ve_spec.mirror.mr_revive_blkno

/*
 * Physvol info structure
 * pv_volhdrblks, pv_xvmlabelblks, and pv_systemdisk are only valid
 * if there is a direct connection to the physvol on the calling cell
 * (ie. pv_dksc_dev != NODEV).
 */

typedef struct xvm_pvinfo_s {
        uint8_t		pv_state;		/*  state bitmaks 	*/
	uchar_t		pv_systemdisk;
        uint16_t	pv_blocksize;		/*  size of a block (bytes)*/
	uchar_t		pv_validstat;
	uchar_t		pad[3];

        xvm_dev_t      	pv_dksc_dev;            /* dksc vhdl for disk */
	uint16_t	pv_volhdrblks;
	uint16_t	pv_xvmlabelblks;

	uint64_t	pv_nbr_blocks;		/*  number blocks on disk  */

	pv_stat_t	pv_stat;		/* if pv_validstat != 0 */
} xvm_pvinfo_t;

/*
 * Unlabeled disk info.
 */

typedef struct xvm_udinfo_s {
	char		ud_volalias[64];	/* shortcut path to vol */
	char		ud_volfullpath[256];	/* full vol canonical path */
	inventory_t	ud_inventory;		/* disk inventory */
} xvm_udinfo_t;

/*
 * foreign disk info
 */

typedef struct xvm_fdinfo_s {
	char		fd_volalias[64];	/* shortcut path to vol */
	char		fd_volfullpath[256];	/* full vol canonical path */
	inventory_t	fd_inventory;		/* disk inventory */
} xvm_fdinfo_t;

/*
 * Global info
 */

typedef struct xvm_ssinfo_s {
	xvm_apivers_t	ss_apivers;	/* api vers kernel is running with */
	uchar_t		ss_priv : 1,	/* set if caller is privleged.  This */
					/* bit is a user-only bit, set in */
					/* xvm_subsystem_info() in xvm_user.c */
					/* on a per-call basis. */
			ss_clcapable:1,	/* 1 if kernel is cluster-capable */
			ss_clinit:1,	/* 1 if xvm cluster code has */
					/* been initialized */
			ss_mirrors_enabled:1, /* 1 if mirrors enabled */
			ss_snapshot_enabled:1, /* 1 if snapshot enabled */
			ss_user_enabled:1,	/* 1 if user license enabled */
			ss_hotplug_invent:1,	/* 1 if user-space inventory */
			ss_unused:1;
	uchar_t		ss_pad[1];
	uint32_t        ss_cfggen;      /* config generation value */
	int64_t		ss_snapshot_max; /* maximum licensed virtual space */
	int64_t		ss_snapshot_blocks; /* snapshot virtual space in use */
} xvm_ssinfo_t;

/*
 * Performance info
 */
typedef	struct	xvm_perf_s	{
	uint64_t	perf_count;	/* occurrance count */
	uint64_t	perf_time;	/* accumulated time */
	uint64_t	perf_blocks;	/* total blocks */
} xvm_perf_t;

typedef	struct	xvm_peinfo_s	{
	uint32_t	pe_timer_freq;	/* system timer frequency */
	char		pe_pad[4];	/* explicit pad */

	uint64_t	pe_inittime;	/* time table last initialized */

	xvm_perf_t	pe_perf[25];	/* individual performance counters */

} xvm_peinfo_t;
	
/*
 * Performance counters types.  This uses an array rather than conventional 
 * field names in order to make it easier to add or delete performance counters
 * and still allow the kernel and cli to work together. 
 *
 * NOTE:	The size of the counter array was set to 25 because this will
 * 		fit within the current size of xvm_info_t.  If more counters
 * 		are added, the size of xvm_info_t will change and may require
 * 		versioning.
 */
typedef	enum {
	PETYPE_BASERD,	/* base reads */
	PETYPE_BASEWR,	/* base writes */
	PETYPE_SNAPRD,	/* snapshot reads */
	PETYPE_SNAPWR,	/* snapshot writes */
	PETYPE_KMEM,	/* kmem_alloc calls */
	PETYPE_RESVSP,	/* xfs space reservation */
	PETYPE_MRUPD,	/* mrupdate calls */
	PETYPE_MRACC,	/* mraccess calls */
	PETYPE_SETFL,	/* set file lock calls */
	PETYPE_BMAP,	/* getbmapx calls */
	PETYPE_SNRD,	/* vn_rdwr calls reads from I/O path */
	PETYPE_SNWR,	/* vn_rdwr writes from I/O path */
	PETYPE_SNBRD,	/* base read for snap I/O */
	PETYPE_CPBRD,	/* base read for copy */
	PETYPE_VNRD,	/* vn_rdwr reads for repository copy */
	PETYPE_VNWR,	/* vn_rdwr writes for repository copy */
	PETYPE_XVMRD,	/* XVM reads */
	PETYPE_XVMWR,	/* XVM writes */
	PETYPE_B2R,	/* base to repository copies */
	PETYPE_R2R,	/* repository to repository copies */
	PETYPE_FSYNC,	/* fsync after rep copy */
	PETYPE_19,	/* counter type 19 */
	PETYPE_20,	/* counter type 20 */
	PETYPE_21,	/* counter type 21 */
	PETYPE_22,	/* counter type 22 */
	PETYPE_23,	/* counter type 23 */
	PETYPE_24,	/* counter type 24 */
	PETYPE_MAX = 25	/* maximum type */
} xvm_petype_t;

#ifdef PERF_ENABLE
/*
 * Declare the text table for performance statistics.
 */
typedef	struct	xvm_pemsgmap_s {
	xvm_petype_t	petype;
	char		*text;
} xvm_pemsgmap_t;

extern	xvm_pemsgmap_t	xvm_pemsgmap[];
#endif /* PERF_ENABLE */

/*
 * Supported info types
 */

typedef enum {
	ITYPE_NONE 	= 0,	/* placeholder */
	ITYPE_OBJECT	= 1,	/* info type is an object (ve, phys) */
	ITYPE_SUBSYSTEM	= 2,	/* info is xvm subsystem info */
	ITYPE_PERF	= 3	/* info is performance info */
} xvm_itype_t;

/*
 * Generic info structure - used by the XVM_OBJINFO ioctl
 */
 
typedef struct xvm_info_s {
	uint8_t		xi_type;
	uchar_t		xi_pad;		/* unused */
	cell_t		xi_cell;	/* cell info came from */
	uint32_t	xi_cfggen;	/* config generation value */

	xvm_id_t	xi_id;		/* id if type is ITYPE_OBJECT*/

	union {
		xvm_veinfo_t	ve;	/* ve info */
		xvm_pvinfo_t	pv;	/* physvol info */
		xvm_udinfo_t	ud;	/* unlabeled info */
		xvm_ssinfo_t	ss;	/* subsystem info */
		xvm_fdinfo_t	fd;	/* foreign info */
		xvm_peinfo_t	pe;	/* performance info */
	} xi_info;
} xvm_info_t;

/*
 * Macros to get various pieces of an xvm_info_t structure.  Use these
 * instead of accessing the xi_id and xi_info fields directly.
 */

#define id_info(_ip_)	(&((_ip_)->xi_id))
#define ve_info(_ip_)	(&((_ip_)->xi_info.ve))
#define pv_info(_ip_)	(&((_ip_)->xi_info.pv))
#define ss_info(_ip_)	(&((_ip_)->xi_info.ss))
#define ud_info(_ip_)	(&((_ip_)->xi_info.ud))
#define fd_info(_ip_)	(&((_ip_)->xi_info.fd))
#define pe_info(_ip_)	(&((_ip_)->xi_info.pe))

/*
 * List structures returned or used or used by various xvmlib functions
 */

typedef struct xvm_idlist_s {
	int32_t	nids;
	int32_t	maxids;

	xvm_id_t	*id;
} xvm_idlist_t;

typedef struct xvm_strlist_s {
        int32_t  nstr;           /* # strings in strlist */
        int32_t  maxstr;         /* # strings strlist can hold without realloc*/ 
        char    **strlist;      /* the strings */
} xvm_strlist_t;

typedef struct xvm_infolist_s {
        int32_t     	ninfo;
        int32_t     	maxinfo;

	xvm_info_t	*info;
} xvm_infolist_t;

/*
 * GPT Label constants
 */

#define XVM_LABEL_SCAN_NUM_SECT 64

/*
 * Externalized xvmlib functions
 */

/*
 * info-generation functions
 */

extern char *xvmlib_veinfo2userstate(xvm_veinfo_t *ve);

/*
 * List maniuplation functions
 */

extern xvm_infolist_t *xvmlib_infolist_alloc(void);
extern xvm_errno_t xvmlib_infolist_add(xvm_info_t *info, xvm_infolist_t *list);
extern void xvmlib_infolist_free(xvm_infolist_t *list);
extern xvm_idlist_t *xvmlib_idlist_alloc(void);
extern xvm_errno_t xvmlib_idlist_add(xvm_id_t *id, xvm_idlist_t *idlist);
extern void xvmlib_idlist_free(xvm_idlist_t *idlist);
extern xvm_strlist_t *xvmlib_strlist_alloc(void);
extern xvm_errno_t xvmlib_strlist_add(char *str, xvm_strlist_t *l);
extern void xvmlib_strlist_free(xvm_strlist_t *l);

/*
 * XVM Object manipulation functions
 */

extern xvm_errno_t xvmlib_get_names(xvm_domain_t domain, ve_type_t type,
                                    xvm_strlist_t *list, int addprefix);
extern xvm_errno_t xvmlib_expand_path(char *path, xvm_strlist_t *strlist);
extern xvm_errno_t xvmlib_get_attributes(char *path, xvm_info_t *info);
/* xvmlib_id_attributes is an old iterface - use xvmlib_getinfo_byid */
extern xvm_errno_t xvmlib_id_attributes(xvm_id_t *id, xvm_info_t *info);

extern xvm_errno_t xvmlib_getinfo_byid(xvm_id_t *id, cell_t *cell_list,
				       int ncells, xvm_info_t *infoarray,
					xvm_errno_t *errno_array);
extern xvm_errno_t xvmlib_get_pieces(xvm_id_t *ve, xvm_idlist_t  **pieces);
extern char *xvmlib_id2name(xvm_id_t *id);
extern xvm_errno_t xvmlib_kern_apivers(xvm_apivers_t *kvers);
extern xvm_errno_t xvmlib_get_infolist(xvm_strlist_t *sl,
				xvm_infolist_t **ilp, int *errindex);
extern xvm_errno_t xvmlib_get_infolist_bytype(xvm_domain_t domain, 
						ve_type_t type,
                        			xvm_strlist_t **namelist, 
						xvm_infolist_t **infolist);
extern xvm_errno_t xvmlib_change_attributes(xvm_id_t *obj,
				chgattr_t *attr, xvm_info_t *objinfo);


/*
 * Misc
 */

extern xvm_errno_t xvmlib_subsystem_info(cell_t *cell_list, int ncells,
					 xvm_ssinfo_t *sinfo);
extern xvm_errno_t xvmlib_perf_info(cell_t *cell_list, int ncells,
					xvm_peinfo_t *pinfo, int type);
extern int xvmlib_check_user_license(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __XVMLIB_H__ */

