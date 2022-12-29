#ifndef __SYS_XVM_BASE_H__
#define __SYS_XVM_BASE_H__

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
#ident "$Revision: 1.41 $"

/* This file is included in both kernel and user-space code */
#ifdef _KERNEL
#   ifdef _HAVE_XVM_SYS_HEADERS_
#       include <xvm_sys_headers.h>
#   else
#       include <sys/uuid.h>
#   endif
#   include <xvm_platform_defs.h>
#else /* ! _KERNEL */
#   ifdef _HAVE_XVM_USER_SYS_HEADERS_
#       include <xvm_user_sys_headers.h>
#   else
#       include <sys/uuid.h>
#   endif
#   include <sys/xvm_user_platform_defs.h>
#endif /* _KERNEL */

#include <sys/volume.h>
#include <sys/xvm_errno.h>
#include <ksys/cell_types.h>

#define XVM_MIN(a,b) (((a)<(b))?(a):(b))
#define XVM_MAX(a,b) (((a)>(b))?(a):(b))

#define XVM_MIRROR_MAX	8

typedef uint32_t	xvm_tid_t;	/* transaction identifer */

/*
 * Default permissions and mode
 */
#define XVM_PERM_UID    0
#define XVM_PERM_GID    0
#define XVM_PERM_MODE   0600

/*
 * Default stripe unit
 */

#define XVM_DEF_STRIPEUNIT	128

/*
 * Length of names in the physvol and ve on-disk labels.
 */
#define LAB_HOST_NAME_SIZE	32
#define LAB_VE_NAME_SIZE	48

/*
 * Maximum length of user defined names for volumes, subvolumes, volume
 * elements, and physical disks.
 *
 * The system name length maximum is larger than what the user is
 * allowed to create because:
 *	1. possible .dupXXXX extension to handle name collisions
 * 	2. auto-slice naming with a max length physvol name
 */
#define USER_VE_NAME_MAX	32		/* max name user can define */
#define VE_NAME_MAX             48
#define VE_EDGE_NAME_MAX	VE_NAME_MAX

/*
 * Maximum depth of a volume tree
 */

#define XVM_MAXDEPTH	10

/*
 * Volume Element Types - update the VETYPE_ISDISK or VETYPE_ISVE macro
 * when adding new volume element types
 */

typedef enum ve_type_e {
	VETYPE_FREE,			 /* Unused */
	VETYPE_SLICE,			 /* Partition */
	VETYPE_CONCAT,			 /* Concatenated Volume Elements */
	VETYPE_STRIPE,			 /* Striped Volume Elements */
	VETYPE_RAID,			 /* RAID: Fixed(4)/Rotating(5) parity */
	VETYPE_MIRROR,			 /* Mirror */
	VETYPE_SUBVOL,			 /* Subvolume - configuration root */
	VETYPE_VOL,			 /* Volume - subvolume grouping */
	VETYPE_PHYSVOL,			 /* Physical Volume */
	VETYPE_UNLAB,			 /* Unlabeled (non-xvm) disk */
	VETYPE_FOREIGN,			 /* xvm disk not owned by us */
        VETYPE_COW,			 /* copy on write subvolume */
        VETYPE_SNAPSHOT,                 /* virtual snapshot subvolume */
	VETYPE_NEXT,			 /* next available ve type */
	VETYPE_LAST		=255
} ve_type_t; 

#define VETYPE_ISDISK(t)	((t)==VETYPE_PHYSVOL || (t)==VETYPE_UNLAB)

#define VETYPE_ISVE(t)		(((t)>=VETYPE_SLICE && (t)<=VETYPE_VOL) || \
				(t)==VETYPE_COW || (t)==VETYPE_SNAPSHOT)

#define SVTYPE_ISSYS(svtype)	((svtype) < SVTYPE_USER1)
#define SVMASK(svtype)		(SVTYPE_ISSYS(svtype) ? (1 << (svtype)) : 0)

/* 
 * RAID types
 */
typedef enum rd_type_e {
	RAID4,				 /* fixed parity RAID */
	RAID5_LEFT_ASYMMETRIC		 /* rotating parity: left asymmetric */
} rd_type_t;

/*
 * Mirror read policies
 */
typedef enum xvm_mrpolicy_e {
	MR_ROUND_ROBIN,		/* ping-pong between pieces */	
	MR_SEQUENTIAL   	/* affinity for sequential i/o*/
} xvm_mrpolicy_t;

/*
 * Mirror configuration policies 
 */
typedef enum xvm_mrconfig_e {
	MRC_NONE	= 0,		/* initialization value */
	MRC_PRIMARY	= (1<<0),	/* mirror has a primary piece for read*/
	MRC_B1		= (1<<1),	/* unused */
	MRC_B2		= (1<<2), 	/* unused */
	MRC_NOREVIVE	= (1<<3),	/* don't revive on boot or create */
	MRC_CLEAN	= (1<<4)	/* don't revive on create */
} xvm_mrconfig_t;

/*
 * Mirror defaults
 */

#define XVM_DEF_MRPOLICY	MR_ROUND_ROBIN
#define XVM_DEF_MCONFIG		MRC_NONE

/*
 * Volume Element State bits.  Note that VESTATE_USERONLINE is really a
 * VESTATE_ONLINE state modifier.  xvm_propagate() will not propagate this
 * bit up the tree, rather it will use it to help determine a ve's ONLINE
 * state.
 *
 * The state definition used for both the ve state and the ve piece state.
 */
typedef enum ve_state_e {
	VESTATE_NONE          	=0,	 /* initialization value */
	VESTATE_CLEAN         	=(1<<0), /* '01' clean */
	VESTATE_VALID         	=(1<<1), /* '02' valid */
	VESTATE_MEDIAERROR    	=(1<<2), /* '04' media error; DON'T CARE on disk */
	VESTATE_ONLINE        	=(1<<3), /* '08' online; DON'T CARE on disk */
	VESTATE_DISABLED    	=(1<<4), /* '10' administrative disable */
	VESTATE_B5		=(1<<5), /* bit 5 */
	VESTATE_B6		=(1<<6), /* bit 6 */
	VESTATE_B7            	=(1<<7)	 /* bit 7 */
} ve_state_t;

#define INVALID_VE(state)        \
 (((state) & (VESTATE_ONLINE|VESTATE_VALID)) != (VESTATE_ONLINE|VESTATE_VALID))

#define VALID_VE(vhdl, state)   \
 ((vhdl != GRAPH_VERTEX_NONE) &&  \
 (((state) & (VESTATE_ONLINE|VESTATE_VALID)) == (VESTATE_ONLINE|VESTATE_VALID)))

#define ONLINE_VE(vhdl, state)   \
 ((vhdl != GRAPH_VERTEX_NONE) &&  \
 (((state) & (VESTATE_ONLINE|VESTATE_VALID)) == VESTATE_ONLINE))

#define ONLINE_SET(vhdl, state)   \
 ((vhdl != GRAPH_VERTEX_NONE) && ((state) & VESTATE_ONLINE))

/*
 * VESTATE_MASK_DISK bits are written to disk for non-physvols ve's.
 * VESTATE_MASK_MRPIECE bits are written to disk for mirror ve's.
 * VESTATE_MASK_PROPAGATE bits depend on the ve's piece states.
 */
#define	VESTATE_MASK_DISK	(VESTATE_DISABLED)
#define	VESTATE_MASK_MRPIECE	(VESTATE_VALID|VESTATE_CLEAN)
#define	VESTATE_MASK_PROPAGATE	(VESTATE_ONLINE|VESTATE_VALID|VESTATE_CLEAN)


/* Physical Volume State Bits 
 * -- common between in-core and on disk structures.
 */
typedef enum pv_state_e {
	PVSTATE_NONE		=0,	 /* initialization value */
	PVSTATE_ONLINE		=(1<<0), /* Online */
	PVSTATE_SPARE		=(1<<1), /* Spare Pool */
	PVSTATE_MEDIAERROR	=(1<<2), /* Media Error seen */
	PVSTATE_RECOVERING	=(1<<3), /* Recovering */
	PVSTATE_PRIVATE		=(1<<4), /* Private to a given host */
	PVSTATE_CLUSTER		=(1<<5), /* Global/clustered */
	PVSTATE_DRAINING	=(1<<6), /* I/O is being drained */
	PVSTATE_B7		=(1<<7)	 /* bit 7 */
} pv_state_t;

/*  Physical Volume Locality - local (private) or shared (clustered)
 */
#define	PV_DOMAINMASK	(PVSTATE_PRIVATE|PVSTATE_CLUSTER)
#define PV_DOMAIN(s)	((s) & PV_DOMAINMASK)
#define	PV_LOCAL(s)	(((s) & PV_DOMAINMASK) == PVSTATE_PRIVATE)
#define	PV_CLUSTER(s)	(((s) & PV_DOMAINMASK) == PVSTATE_CLUSTER)

/* Physical Volume Flag Bits
 * -- some common values between in-core and on disk structures.  
 */
typedef enum pv_flag_e {
	PVFLAG_IDLE        	=0,	 /* physvol idle */
	PVFLAG_LABPROCESSED	=(1<<0), /* labels have been processed */
	PVFLAG_BOOTABLE    	=(1<<1), /* bootable */
	PVFLAG_DUPLICATE   	=(1<<2), /* duplicate physvol name */
	PVFLAG_SYNC         	=(1<<3), /* physvol label update needed */
	PVFLAG_NAMEDEDGES	=(1<<4), /* physvol has edges in hwgraph */
	PVFLAG_STAT		=(1<<5), /* tracking physvol stats */
	PVFLAG_FOREIGN		=(1<<6), /* physvol doesn't belong to us */
	PVFLAG_COUNTREFS	=(1<<7)  /* label references need counting */
} pv_flag_t;

/*
 * flags which are persistent across reboots
 */
#define PVFLAG_PERSIST_MASK	(PVFLAG_BOOTABLE|PVFLAG_DUPLICATE)

/* Label Record Types */
typedef enum lab_type_e {
	LABTYPE_FREE		=0,	 /* Free sector: must be zero based */
	LABTYPE_INVALID,		 /* in-core only: garbled label */
	LABTYPE_VE,			 /* Volume Element */
	LABTYPE_ATTR,			 /* Attribute */
	LABTYPE_LAST			 /* first undefined label type */
} lab_type_t;

#define INVALID_LABEL(t)	((t) < LABTYPE_VE || (t) >= LABTYPE_LAST)

 /* Attribute Label Record */
typedef enum attr_type_e {
	ATTRTYPE_FREE=0,		/* Unused */
	ATTRTYPE_NAME,			/* user defined name */
	ATTRTYPE_PERM,			/* user specified permissions */
	ATTRTYPE_LAST			/* first undefined attribute type */
} attr_type_t;

#define ATTRTYPE_ISVALID(t)	((t)==ATTRTYPE_NAME || (t)==ATTRTYPE_PERM)

/* Disk attribute flags */
typedef enum attr_flag_e {
	ATTRFLAG_NONE		=0,	 /* initialization value */
	ATTRFLAG_DUPLICATE	=(1<<0), /* duplicate name */
	ATTRFLAG_B1 		=(1<<1), /* bit 1 */
	ATTRFLAG_B2 		=(1<<2), /* bit 2 */
	ATTRFLAG_B3 		=(1<<3), /* bit 3 */
	ATTRFLAG_B4 		=(1<<4), /* bit 4 */
	ATTRFLAG_B5 		=(1<<5), /* bit 5 */
	ATTRFLAG_B6 		=(1<<6), /* bit 6 */
	ATTRFLAG_B7		=(1<<7)  /* bit 7 */
} attr_flag_t;

/*
 * Flags for i/o requests
 */
typedef enum xvm_ioflg_e {
	XVM_WRITE	= 0,		/* pseudo write flag */
	XVM_READ	= (1<<0),	/* xvm read io request */
	XVM_LABEL	= (1<<1),	/* label rather than data request */
	XVM_NOPROPAGATE = (1<<2),	/* don't propagate label op to parent */
	XVM_UNUSED2	= (1<<3),  	/* no longer used */
	XVM_NOWRITE	= (1<<4),  	/* don't write label i/o to disk */
	XVM_RETRY	= (1<<5),  	/* this I/O is being retried */
	XVM_STAT	= (1<<6),	/* gather stats on i/o completion */
	XVM_SKIPOVERLAP	= (1<<7),  	/* don't use overlap queuing */
	XVM_OVERLAP	= (1<<8),  	/* I/O is on mirror overlap queue */
	XVM_MASTER_SENT	= (1<<9),  	/* I/O was sent to a remote master */
	XVM_UNUSED	= (1<<10),  	/* Unused */
	XVM_BUSY	= (1<<11), 	/* layer specific in-use flag */
	XVM_REVIVE	= (1<<12), 	/* revive I/O */
	XVM_WRITEBACK   = (1<<13), 	/* a writeback is needed for this i/o */
	XVM_PRIVATE	= (1<<14),	/* local (non cell) I/O */
	XVM_INJECT_ERR =  (1<<15)	/* inject error on this ior */
} xvm_ioflg_t;

/*
 * io flags to propagate to the next layer
 */
#define IOFLAG_MASK	(XVM_READ|XVM_SKIPOVERLAP|XVM_PRIVATE)

/*
 * Common permission information passed from the API and used in various 
 * internal structures.  cell_mode_t is used because the linux kernel mode_t
 * is a different size.  xvm_gid_t is used because the linux kernel size matches
 * other platforms, but the user space size can be different.  
 */
typedef struct xvm_perm_s {
        xvm_uid_t   	xp_uid;			/* user id bits */
        xvm_gid_t   	xp_gid;			/* group id bits */
        cell_mode_t  	xp_mode;		/* permissions mask */
} xvm_perm_t;

/* vertex handle information */
typedef struct xvm_vhdl_s {
	vertex_hdl_t	xv_vhdl;	/* vertex handle */
	uint32_t	xv_vgen;	/* vertex generation value */
} xvm_vhdl_t;

typedef enum attr_class_e {
	AC_GENERIC,		/* generic attributes - stats, name, etc. */
	AC_SUBVOL,		/* subvol-specific attributes */
	AC_PHYSVOL,		/* physvol-specific attributes */
	AC_MIRROR,		/* mirror-specific attributes */
	AC_ERROR_INJECT,	/* error-injection attributes */
	AC_SNAPSHOT,		/* snapshot attributes (first, next) */
	AC_VOL			/* volume attributes */
} attr_class_t;

/*
 * Generic attributes
 */

typedef enum gen_attr_e {
	GEN_NAME,		/* change object name */
	GEN_STAT_ON,		/* turn stats on */
	GEN_STAT_OFF,		/* turn stats off */
	GEN_STAT_RESET,		/* reset stats */
	GEN_ONLINE,		/* change object online */
	GEN_DISABLE,		/* change disable ve */
	GEN_ENABLE		/* re-enable ve */
} gen_attr_t;

/*
 * subvolume attributes
 */

typedef enum sv_attr_e {
	SV_UID,			/* change subvol uid */
	SV_GID,			/* change subvol gid */
	SV_MODE			/* change subvol mode */
} sv_attr_t;

/*
 * physvol attributes
 */

typedef enum pv_attr_e {
	PV_OPTION		/* change physvol to an option disk */
} pv_attr_t;

/*
 * mirror attributes
 */

typedef enum mr_attr_e {
	MR_UNUSED1,		/* unused */
	MR_UNUSED2,		/* unused */
	MR_UNUSED3,		/* unused */
	MR_UNUSED4,		/* unused */
	MR_PIECE_ENABLE,	/* KERNEL only: set bits in piece state*/
	MR_PIECE_DISABLE, 	/* KERNEL only: clear bits in piece state */
	MR_PRIMARY_ENABLE,	/* make ve a primary member */
	MR_PRIMARY_DISABLE,	/* turn off primary mirror handling */
	MR_UNUSED5,		/* unused */
	MR_POLICY 		/* set the mirror read policy */
} mr_attr_t;

/*
 * values for repository full recovery method (AC_VOL)
 */
typedef enum xvm_rep_repfull_s {
	XVM_REP_NONE		=0,	/* none (default) */
	XVM_REP_ERR,			/* return error */
	XVM_REP_DEL_OLDEST,		/* delete oldest snapshot */
	XVM_REP_MAX
} xvm_rep_repfull_t;

#define	XVM_REP_DEFAULT	XVM_REP_ERR	/* default = return error */

/*
 * Generic attribute modification structure.  In an attempt to save some
 * space, the attributes to change are divided into classes.
 */

typedef struct chgattr_s {
	uint8_t		attr_class;
	uchar_t		pad[7];

	union {
		struct generic_attr_s {
			uint8_t		gen_attr;	/* attr to change */
			uchar_t		pad[7];

			char		gen_name[VE_NAME_MAX]; /* new name */
		} generic_attr;

		struct subvol_attr_s {
			uint8_t		sv_attr;	/* attr to change */
			uchar_t		pad[7];
			xvm_perm_t	sv_mode;	/* new modes */
			uchar_t		spad[20];
		} subvol_attr;

		struct physvol_attr_s {
			uint8_t		pv_attr;	/* attr to change */
			uchar_t		pad[39];
		} physvol_attr;

		struct mirror_attr_s {
			uint8_t		mr_attr;	/* attr to change */
			uint8_t		mr_policy;	/* read policy */
			uint16_t	mr_flushint;	/* new flush interval */
			uchar_t		pad[4];

			/* KERNEL RESERVED */
			uchar_t		mr_reserved[32];/* overlay field */
		} mirror_attr;

		struct error_attr_s {
			/* 
			 * XXX error injection will break if we exceed 64 cells.
			 */
			int32_t		ei_interval;	/* #reqs between errs */
			int32_t		ei_duration;	/* #consecutive errs */
			uint64_t	ei_cellmask;	/* cells to modify */
			uchar_t		ei_pad[24];	/* explicit pad */
		} error_attr;

		struct snapshot_attr_s {
			uint16_t	sn_first;	/* first snapshot */
			uint16_t	sn_next;	/* next snapshot */
			uint8_t		sn_repfull;	/* rep full method */
			uchar_t		sn_pad[35];	/* explicit pad */
		} snapshot_attr;

		struct vol_attr_s {
			uint8_t		vo_repfull;	/* rep full method */
			uchar_t		vo_pad[39];	/* explicit pad */
		} vol_attr;
	} attr;
} chgattr_t;

#define attr_genattr	attr.generic_attr.gen_attr
#define attr_name	attr.generic_attr.gen_name

#define attr_pvattr	attr.physvol_attr.pv_attr

#define attr_svattr	attr.subvol_attr.sv_attr
#define attr_svmode	attr.subvol_attr.sv_mode

#define attr_mrattr	attr.mirror_attr.mr_attr
#define attr_policy	attr.mirror_attr.mr_policy
#define attr_flushint	attr.mirror_attr.mr_flushint
#define attr_mreserved	attr.mirror_attr.mr_reserved

#define attr_ei_interval	attr.error_attr.ei_interval
#define attr_ei_duration	attr.error_attr.ei_duration
#define attr_ei_cellmask	attr.error_attr.ei_cellmask

#define attr_snfirst		attr.snapshot_attr.sn_first
#define attr_snnext		attr.snapshot_attr.sn_next

#define attr_volrepfull		attr.vol_attr.vo_repfull
/*
 * ve statistics.  This structure is shared between xvmlib and the
 * kernel.  If its size is changed, you must bump XVM_API_VERSION in
 * sys/xvmlib.h
 */

typedef	struct concat_stats_s {
	uint32_t	concat_straddle_read;
	uint32_t	concat_straddle_write;
} concat_stats_t;

typedef	struct stripe_stats_s {
	uint32_t	stripe_equal_aligned_both;
	uint32_t	stripe_equal_unaligned;
	uint32_t	stripe_small_aligned_both;	/* start/end aligned and < stripe width */
	uint32_t	stripe_small_aligned_end;
	uint32_t	stripe_small_aligned_start;
	uint32_t	stripe_small_unaligned;
	uint32_t	stripe_large_aligned_both;
	uint32_t	stripe_large_aligned_end;
	uint32_t	stripe_large_aligned_start;
	uint32_t	stripe_large_unaligned;
} stripe_stats_t;

typedef	struct mirror_stats_s {
	uint32_t	mirror_sync_read;	/* read ops for mirror 
							synchronization */
	uint32_t	mirror_sync_write;	/* write ops for mirror 
							synchronization */
	uint32_t	mirror_piece_read[XVM_MIRROR_MAX];
	uint32_t	mirror_piece_write[XVM_MIRROR_MAX];
} mirror_stats_t;

typedef struct ve_stat_s {
        cell_time_t     start;
        cell_time_t     stop;
	uint32_t	s_read;		/* # of read requests initiated */
	uint32_t	s_write;	/*   "  write   "         "     */
	uint64_t	s_blkread;	/* total 512 blks read */
	uint64_t	s_blkwrite;	/* total 512 blks written */

	union {
		concat_stats_t	s_concat;	/* Statistics for concatenation */
		stripe_stats_t	s_stripe;	/* Statistics for stripes */
		mirror_stats_t	s_mirror;	/* Ststistics for mirrors */
	} s;

} ve_stat_t;

#define c_straddle_read s.s_concat.concat_straddle_read	
#define c_straddle_write s.s_concat.concat_straddle_write	

#define st_equal_aligned_both  s.s_stripe.stripe_equal_aligned_both	
#define st_equal_unaligned     s.s_stripe.stripe_equal_unaligned
#define st_small_aligned_both  s.s_stripe.stripe_small_aligned_both	
#define st_small_aligned_end   s.s_stripe.stripe_small_aligned_end	
#define st_small_aligned_start s.s_stripe.stripe_small_aligned_start	
#define st_small_unaligned     s.s_stripe.stripe_small_unaligned	
#define st_large_aligned_both  s.s_stripe.stripe_large_aligned_both	
#define st_large_aligned_end   s.s_stripe.stripe_large_aligned_end	
#define st_large_aligned_start s.s_stripe.stripe_large_aligned_start
#define st_large_unaligned     s.s_stripe.stripe_large_unaligned	

#define mr_sync_read s.s_mirror.mirror_sync_read	
#define mr_sync_write s.s_mirror.mirror_sync_write	
#define mr_piece_read s.s_mirror.mirror_piece_read	
#define mr_piece_write s.s_mirror.mirror_piece_write	

/*
 * physvol statistics.  This structure is shared between xvmlib and the
 * kernel.  If its size is changed, you must bump XVM_API_VERSION in
 * sys/xvmlib.h.
 *
 * ###maule:  For now, this has the same fields as ve_stat_t, but I assume
 * physvol and ve stats will evolve independently.
 */

typedef struct pv_stat_s {
	uint32_t	ps_cliread;	/* # io read requests */
	uint32_t	ps_cliwrite;	/* # io write requests */

	uint64_t	ps_cliblkread;	/* total 512 blks read (normal io) */

	uint64_t	ps_cliblkwrite;	/* total 512 blks written (normal io) */
} pv_stat_t;

/*
 * Slice-specific flags
 */

typedef enum slice_flag_e {
	SL_NONE		= 0,
	SL_SWAPSLICE	= (1<<0),	/* slice covers a swap partition */
	SL_ROOTSLICE	= (1<<1),	/* slice covers a root partition */
	SL_USRSLICE	= (1<<2),	/* slice covers a usr partition  */
	SL_PARTVALID	= (1<<3),	/* set if sl_partition is valid  */
	SL_B4		= (1<<4),
	SL_B5		= (1<<5),
	SL_B6		= (1<<6),
	SL_B7		= (1<<7)
} slice_flag_t;

/*
 * xvm domain types
 */

typedef enum xvm_domain_e {
	DOMAIN_NONE	= 0,		/* no use for this right now */
	DOMAIN_ALL	= 1,		/* search in all domains */
	DOMAIN_LOCAL	= 2,		/* search only in the local domain */
	DOMAIN_CLUSTER	= 3,		/* only check the cluster domain */
	DOMAIN_FOREIGN	= 4,		/* non-local and non-cluster domain */
	DOMAIN_CURRENT	= 5		/* used by xvmlib routines as an */
					/* alias for the  current domain. */
} xvm_domain_t;

/*
 * Performance measurement.
 *
 * Note that the parameter for XVM_STARTTM isn't used, but is provided for
 * documentation purposes.  This parameter will also cause a reference for
 * cscope.
 */
#ifdef	XVM_PERF_STATS
#define	XVM_STARTTM(stat, start)	start = absolute_rtc_current_time()
#define	XVM_STOPTM(stat, start) \
		xvm_perf.pe_perf[stat].perf_count++; \
		xvm_perf.pe_perf[stat].perf_time += absolute_rtc_current_time() - (start);
#define XVM_STOPTM_IO(stat, start, blocks) \
		XVM_STOPTM(stat, (start)); \
		xvm_perf.pe_perf[stat].perf_blocks += (blocks);
#else	/* XVM_PERF_STATS */
#define	XVM_STARTTM(stat, start)
#define	XVM_STOPTM(stat, start) 
#define XVM_STOPTM_IO(stat, start, blocks) 
#endif	/* XVM_PERF_STATS */

/*
 * Snapshot specific constants.
 */
#define XVM_MAX_SNAPSHOT 256
#define XVM_MAX_SNAPSHOT_IDX 0x10000
#define XVM_REPOSITORY_BASE "/xvm/repositories"
/* Region size = approximately 64K for starters */
#define XVM_SNAP_REGBLKS_DEF 128
#define XVM_SNAP_REGSZ_DEF dbtob(XVM_SNAP_REGBLKS_DEF)

#define XVM_SNAP_VERSION	2
#define XVM_SNAP_TIME_VERSION	2

#define XVM_REP_DELETED	1

typedef struct xvm_last_region_s {
      uint32_t        version;        /* Version for on disk info */
      uchar_t         pad[4];         /* Explicit pad */
      uint64_t        ve_size;        /* Original size of snapshot volume. */
      uint32_t        ctime;          /* Snapshot creation time */
      uint32_t        flags;	      /* Snapshot flags */
} xvm_last_region_t;


#endif /* __SYS_XVM_BASE_H__ */
