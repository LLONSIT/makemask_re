/**************************************************************************
 *									  *
 * 		 Copyright (C) 1995 Silicon Graphics, Inc.		  *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/

#ifndef __DBACC_H__
#define __DBACC_H__

#ifdef __cplusplus
extern "C" {
#endif
#ident "$Revision: 1.6 $"

/*
 * Database accelerator config - determine what features are installed, limits, etc.
 * syssgi(SGI_DBA_CONFIG, SGI_DBCF_GET|SGI_DBCF_PUT, struct dba_conf *);
 */
#define SGI_DBCF_GET	0
#define SGI_DBCF_PUT	1
/*
 * Always add new fields to the end of this structure. Users will pass
 * in a size parameter, so older binaries can share this struct with newer ones
 * as it grows over time.
 */
struct dba_conf {
	int		dbcf_sizeused;		/* bytes of structure used in kernel */
	int		dbcf_pad0;
#if (_MIPS_SZLONG == 32)
	long long	dbcf_installed;		/* see bits below */
#endif
#if (_MIPS_SZLONG == 64)
	long		dbcf_installed;
#endif
	int		dbcf_pphysio_max;	/* PPHYSIO */
	int		dbcf_pw_maxinst;	/* POSTWAIT */
	int		dbcf_pw_maxent;
	int		dbcf_pw_timer;
	int		dbcf_aio_max;		/* KAIO */
	int		dbcf_lpg_n256k;		/* Large Pages */
	int		dbcf_lpg_n1m;
	int		dbcf_lpg_n4m;
	int		dbcf_lpg_n16m;
	int		dbcf_lpg_maxwired;
	int		dbcf_lpg_n64k;
};
	/*
	 * The dba_getconfig system call was first available in IRIX 6.2. If
	 * your application calls it and gets EINVAL, you can assume the OS is
	 * pre-6.2 and
	 *	- postwait	may be available (first release: IRIX 5.3 DBA)
	 *	- large pages	not available (first release: IRIX 6.2)
	 *	- klistio32	may be available (first release: IRIX 5.3 DBA)
	 *	- klistio64	not available (first release: IRIX 6.2 DBA)
	 *	- kaio		not available (first release: IRIX 6.2)
	 *	- no other features are available (post-6.2)
	 */

/* bits for dbcf_installed */
#define SGI_DBACF_POSTWAIT	0x0001	/* Post & wait driver */
#define SGI_DBACF_LPG		0x0002  /* Old large page interface */
#define SGI_DBACF_PPHYSIO32	0x0004  /* klistio w/ 32-bit offsets */
#define SGI_DBACF_PPHYSIO64	0x0008  /* klistio w/ 64-bit offsets */
#define SGI_DBACF_AIO		0x0010  /* kernel raw async i/o */
#define SGI_DBACF_AIO_PARAMS	0x0020  /* KAIO params are valid */
#define SGI_DBACF_LPG2		0x0040	/* New 6.4 interface for large pages */

#if (_MIPS_SZLONG == 64)
typedef long dba_field_t;
#else
typedef long long dba_field_t;
#endif

typedef struct dba_stats {
	/* 6.2 */
	dba_field_t     kaio_nobuf;
	dba_field_t     kaio_inprogress;
	dba_field_t     kaio_proc_maxinuse;
	dba_field_t     kaio_aio_inuse;
	/* 6.4 */
	dba_field_t     kaio_reads;
	dba_field_t     kaio_writes;
	dba_field_t     kaio_read_bytes;
	dba_field_t     kaio_write_bytes;
	dba_field_t     kaio_io_errs;
	/* 6.5 */
	dba_field_t     kaio_free;
} dba_stat_t;

#ifdef _KERNEL
#define DBA_STATS ((struct dba_stats*)private.dbastat)

extern int dba_getconfig(struct dba_conf *);
extern int dba_putconfig(struct dba_conf *);
extern int postwait_installed(void);
extern int klistio_installed(void);
extern void postwait_getparams(struct dba_conf *);
extern void klistio_getparams(struct dba_conf *);
extern int dba_getstats(dba_stat_t *dbuf, int dlen, int cpu);
extern int dba_clearstats(void);
#endif

#ifdef __cplusplus
}
#endif
#endif /* __DBACC_H__ */
