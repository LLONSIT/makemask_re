/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#ifndef __SYS_SYSINFO_H__
#define __SYS_SYSINFO_H__
#ifdef __cplusplus
extern "C" {
#endif

#ident	"$Revision: 3.52 $"

#include "sys/sema.h"

/*
 *	System Information.
 *	Most of the info from the data structures herein, is 
 *	retrieved for user programs via the sysmp() system call, not by
 *	reading kernel memory.
 */

#if _ABIAPI
#define abi_sysinfo	sysinfo
#define pad_time	wait
#define CPU_STATES	8
#else
#define CPU_STATES	6
#endif

/* 
 *	struct sysinfo is mirrored in eoe/cmd/sa/sa.h with larger data types
 *	as struct acc_sysinfo (used for a sar accumulator).  Any changes to
 *	struct sysinfo must be propagated to struct acc_sysinfo or sar will
 *	break.
 *
 */     

struct sysinfo {
	time_t	cpu[CPU_STATES];
#define	CPU_IDLE	0
#define	CPU_USER	1
#define	CPU_KERNEL	2
#define	CPU_WAIT	3
#define CPU_SXBRK	4
#define CPU_INTR	5
	time_t	wait[5];
#define	W_IO	0
#define	W_SWAP	1
#define	W_PIO	2
#define	W_GFXC	3
#define	W_GFXF	4
#define WAIT_STATES	5
#if _ABIAPI
	unsigned int	pad[30];
#else
	unsigned int	bread;
	unsigned int	bwrite;
	unsigned int	lread;
	unsigned int	lwrite;
	unsigned int	phread;
	unsigned int	phwrite;
	unsigned int	swapin;
	unsigned int	swapout;
	unsigned int	bswapin;
	unsigned int	bswapout;
	unsigned int	pswapout;
	unsigned int	pswitch;
	unsigned int	syscall;
	unsigned int 	remcall;	/* REMOTE: remote call */
	unsigned int	fileop;		/* REMOTE: remote fileop */
	unsigned int	serve;		/* REMOTE: remote server */
	unsigned int	sysread;
	unsigned int	syswrite;
	unsigned int	sysfork;
	unsigned int	sysexec;
	unsigned int	runque;
	unsigned int	runocc;
	unsigned int	swpque;
	unsigned int	swpocc;
	unsigned int	iget;
	unsigned int	namei;
	unsigned int	dirblk;
	unsigned int	readch;
	unsigned int	writech;
	unsigned int	rcvint;
	unsigned int	xmtint;
	unsigned int	mdmint;
	unsigned int	rawch;
	unsigned int	canch;
	unsigned int	outch;
	unsigned int	msg;
	unsigned int	sema;
	unsigned int	pnpfault;
	unsigned int	wrtfault;
	unsigned int	ptc;		/* pty controller character count */
	unsigned int	pts;		/* pty slave character count */
	unsigned int	intr_svcd;	/* interrupts serviced */
	unsigned int	vmeintr_svcd;	/* vme interrupts serviced */
	unsigned int	reccnt;         /* record locks currently in use */
	unsigned int	rectot;         /* record locks reserved by system */
	unsigned int	vidintr;	/* video vertical retrace ints */
	unsigned int	vidioctl;	/* # of ioctls calls */
	unsigned int	viddrop_add;	/* # fields that were dropped or added
				   to equalize video and graphics frequencies */
	unsigned int	wcancel;	/* buffer cache write cancelled */
	unsigned int	kswitch;	/* kernel thread context switch */
	unsigned int	kpreempt;	/* thread preempted */
	unsigned int	sysioctl;
	unsigned int	mesgsnt;	/* IDL messages sent */
	unsigned int	mesgrcv;	/* IDL messages received */
	unsigned int	bwrite_pending;
	unsigned int	wioque;		/* cumulative wait/io count */
	unsigned int	wioocc;		/* wait/io queue occupied */
	unsigned int	filecnt;	/* open files */
	unsigned int	pad[1];		/* padding for future expansion */
#endif	/* _ABIAPI */
};

struct syswait {
	int	iowait;
	int	swap;
	int	physio;
};

struct sysinfo_cpu {
	time_t	cpu[CPU_STATES];
	time_t	wait[WAIT_STATES];
};

/* 
 *	struct dinfo is mirrored in eoe/cmd/sa/sa.h with larger data types
 *	as struct acc_dinfo (used for a sar accumulator).  Any changes to
 *	struct dinfo must be propagated to struct acc_dinfo or sar will break.
 *
 */     

struct dinfo {
			/* ELEMENT FOR sar -Du */
	time_t	serve;		/* ticks in serve() since boot */
			/* ELEMENTS FOR sar -Dc */
	unsigned int	isyscall;	/* # of incoming syscalls since boot */
	unsigned int	isysread;	/* # of incoming read's since boot */
	unsigned int	ireadch;	/* char's read by incoming read's */
	unsigned int	isyswrite;	/* # of incoming write's since boot */
	unsigned int	iwritech;	/* char's written by incoming writes */
	unsigned int	isysexec;	/* # of incoming exec's since boot */
	unsigned int	osyscall;	/* # of outgoing syscalls since boot */
	unsigned int	osysread;	/* # of outgoing read's since boot */
	unsigned int	oreadch;	/* char's read by outgoing read's */
	unsigned int	osyswrite;	/* # of outgoing write's since boot */
	unsigned int	owritech;	/* char's written by outgoing writes */
	unsigned int	osysexec;	/* # of outgoing exec's since boot */
			/* ELEMENTS FOR sar -S*/
	unsigned int	nservers;	/* sum of all servers since boot */
	unsigned int	srv_que;	/* sum of server Q lgth since boot */
	unsigned int	srv_occ;	/* ticks server Q found occupied */
	unsigned int	rcv_que;	/* sum of receive Q lgth since boot */
	unsigned int	rcv_occ;	/* clock ticks receive Q occupied */
	unsigned int	pad[3];		/* padding for future expansion */
};

/* 
 *	struct rcinfo is mirrored in eoe/cmd/sa/sa.h with larger data types
 *	as struct acc_rcinfo (used for a sar accumulator).  Any changes to
 *	struct rcinfo must be propagated to struct acc_rcinfo or sar will
 *	break.
 *
 */     

struct rcinfo {
	unsigned int	cbread;		/* read blocks sent to remote server*/
					/* (not found in cache) */
	unsigned int	cbwrite;	/* write blocks not found in local cache*/
	unsigned int	clread;		/* total blocks in remote read */
	unsigned int	clwrite;	/* total blocks in remote write */
	unsigned int	snd_dis;	/* cache disable messages sent (server) */
	unsigned int	snd_msg;	/* total RFS messages sent */
	unsigned int	rcv_dis;	/* cache disable messages received (client) */
	unsigned int	rcv_msg;	/* total RFS messages received */
	unsigned int	dis_bread;	/* # of per-file blocks flushed from cache*/
	unsigned int	blk_inval;	/* # of per-file blocks flushed from cache*/
	unsigned int	inval;		/* # of per-file cache flushes */
};

/* 
 *	struct minfo is mirrored in eoe/cmd/sa/sa.h with larger data types
 *	as struct acc_minfo (used for a sar accumulator).  Any changes to
 *	struct minfo must be propagated to struct acc_minfo or sar will break.
 *
 */     

struct minfo {
	unsigned int	freemem[2]; 	/* freemem in pages */
					/* "double" unsigned int format*/
					/* freemem[0] least significant */
	unsigned int	freeswap;	/* free swap space */
	unsigned int	vfault;  	/* translation fault */
	unsigned int	demand;		/*  demand zero and demand fill pages */
	unsigned int	swap;		/*  pages on swap */
	unsigned int	cache;		/*  pages in cache */
	unsigned int	file;		/*  pages on file */
	unsigned int	pfault;		/* protection fault */
	unsigned int	cw;		/*  copy on write */
	unsigned int	steal;		/*  steal the page */
	unsigned int	freedpgs;	/* pages are freed */
	unsigned int	unmodsw;	/* getpages finds unmodified pages */
					/* on swap */
	unsigned int	unmodfl;	/* getpages finds unmodified pages */
					/* in file */ 
	unsigned int	tlbpids;	/* new tlbpids assigned */
	unsigned int	tfault;		/* double tlb miss */
	unsigned int	rfault;		/* reference bit vfault */
	unsigned int	tlbflush;	/* entire tlb flushed on a processor */
	unsigned int	tlbsync;	/* site-wide tlb flushes */
	unsigned int	tvirt;		/* flush caused by virtual address */
					/* depletion */
	unsigned int	tphys;		/* tlb invalidation caused by */
					/* changing virt/phys association */
	unsigned int	twrap;		/* flush caused by tlbpid wrap */
	unsigned int	tdirt;		/* tlbs marked stale for process */
					/* on another processor (MP only) */
	unsigned int	halloc;		/* requests to kern malloc */
	unsigned int	hfree;		/* requests to kern free */
	int		heapmem;	/* total bytes in heap */
	int		hovhd;		/* heap headers and such */
	int		hunused;	/* unallocated heap bytes */
	__uint32_t	iclean;		/* # icache cleans from pagelists */
	__uint64_t	sfault;		/* # 1.5 level misses */
	unsigned int	bsdnet;		/* total bytes in bsd networking */
	unsigned int	palloc;		/* page allocations */
	unsigned int	sptalloc;	/* system page table alloc */
	unsigned int	sptfree;	/* system page table free */
	int		sptclean;	/* clean system page table entries */
	int		sptdirty;	/* dirty system page table entries */
	int		sptintrans;	/* intrans system page table entries */
	int		sptaged;	/* aged system page table entries */
	int		sptbp;		/* system VM in buffer cache */
	int		sptheap;	/* system VM in kernel heap */
	int		sptzone;	/* system VM in kernel zones */
	int		sptpt;		/* system VM in page tables */
	unsigned int	pad[4];		/* padding for future expansion */
};

/*
 * 64-bit version of struct info to handle large memory sizes
 */
struct minfo64 {
	unsigned int	freemem[2]; 	/* freemem in pages */
					/* "double" unsigned int format*/
					/* freemem[0] least significant */
	__uint64_t	freeswap;	/* free swap space */
	__uint64_t	vfault;  	/* translation fault */
	__uint64_t	demand;		/*  demand zero and demand fill pages */
	__uint64_t	swap;		/*  pages on swap */
	__uint64_t	cache;		/*  pages in cache */
	__uint64_t	file;		/*  pages on file */
	__uint64_t	pfault;		/* protection fault */
	__uint64_t	cw;		/*  copy on write */
	__uint64_t	steal;		/*  steal the page */
	__uint64_t	freedpgs;	/* pages are freed */
	__uint64_t	unmodsw;	/* getpages finds unmodified pages */
					/* on swap */
	__uint64_t	unmodfl;	/* getpages finds unmodified pages */
					/* in file */ 
	__uint64_t	tlbpids;	/* new tlbpids assigned */
	__uint64_t	tfault;		/* double tlb miss */
	__uint64_t	rfault;		/* reference bit vfault */
	__uint64_t	tlbflush;	/* entire tlb flushed on a processor */
	__uint64_t	tlbsync;	/* site-wide tlb flushes */
	__uint64_t	tvirt;		/* flush caused by virtual address */
					/* depletion */
	__uint64_t	tphys;		/* tlb invalidation caused by */
					/* changing virt/phys association */
	__uint64_t	twrap;		/* flush caused by tlbpid wrap */
	__uint64_t	tdirt;		/* tlbs marked stale for process */
					/* on another processor (MP only) */
	__uint64_t	halloc;		/* requests to kern malloc */
	__uint64_t	hfree;		/* requests to kern free */
	__int64_t	heapmem;	/* total bytes in heap */
	__int64_t	hovhd;		/* heap headers and such */
	__int64_t	hunused;	/* unallocated heap bytes */
	__uint32_t	iclean;		/* # icache cleans from pagelists */
	__uint64_t	sfault;		/* # 1.5 level misses */
	__uint64_t	bsdnet;		/* total bytes in bsd networking */
	__uint64_t	palloc;		/* page allocations */
	__uint64_t	sptalloc;	/* system page table alloc */
	__uint64_t	sptfree;	/* system page table free */
	__int64_t	sptclean;	/* clean system page table entries */
	__int64_t	sptdirty;	/* dirty system page table entries */
	__int64_t	sptintrans;	/* intrans system page table entries */
	__int64_t	sptaged;	/* aged system page table entries */
	__int64_t	sptbp;		/* system VM in buffer cache */
	__int64_t	sptheap;	/* system VM in kernel heap */
	__int64_t	sptzone;	/* system VM in kernel zones */
	__int64_t	sptpt;		/* system VM in page tables */
	__uint64_t	pad[4];		/* padding for future expansion */
};

/* 
 *	struct gfxinfo is mirrored in eoe/cmd/sa/sa.h with larger data types
 *	as struct acc_gfxinfo (used for a sar accumulator).  Any changes to
 *	struct gfxinfo must be propagated to struct acc_gfxinfo or sar will
 *	break.
 *
 */     

/* structure to hold gfx statistics */
typedef struct gfxinfo {
	int             p_gfx_waitc;    /* waiting for gfx context swtch */
        int             p_gfx_waitf;    /* waiting for gfx fifo */
	unsigned int    gswitch;        /* # of graphics context switches */
	unsigned int    griioctl;       /* # of griioctl calls */
	unsigned int    gintr;          /* # of gm interrupts */
        unsigned int    gswapbuf;       /* # of swap buffers calls */
	unsigned int    fifowait;       /* fifo interrupts that block */
        unsigned int    fifonowait;     /* fifo interrupts that don't block */
} gfxinfo_t;
	

/*
 * Information per node. Used by OSVIEW.
 */
typedef struct	nodeinfo {
	dev_t   node_device;	/* Device decsriptor for this node (The dev_t
				 * changes from boot to boot, but the path it
				 * converts to doesn't.
				 */
	uint	totalmem;	/* Total memory in a given node (bytes) */
	uint	freemem;	/* Free memory in a given node (bytes) */
	uint 	num64kpages;	/* Number of 64k pages on the node */
	uint 	num256kpages;	/* Number of 256k pages on the node */
	uint 	num1mpages;	/* Number of 1m pages on the node */
	uint 	num4mpages;	/* Number of 4m pages on the node */
	uint 	num16mpages;	/* Number of 16m pages on the node */
} nodeinfo_t;

typedef struct	nodeinfo64 {
	dev_t   node_device;	/* Device decsriptor for this node (The dev_t
				 * changes from boot to boot, but the path it
				 * converts to doesn't.
				 */
	__uint64_t totalmem;	/* Total memory in a given node (bytes) */
	__uint64_t freemem;	/* Free memory in a given node (bytes) */
	uint 	num64kpages;	/* Number of 64k pages on the node */
	uint 	num256kpages;	/* Number of 256k pages on the node */
	uint 	num1mpages;	/* Number of 1m pages on the node */
	uint 	num4mpages;	/* Number of 4m pages on the node */
	uint 	num16mpages;	/* Number of 16m pages on the node */
} nodeinfo64_t;

typedef	struct	lpg_stat_info {
	int	coalesce_atts;
	int	coalesce_succ;
	int	num_lpg_faults;
	int	num_lpg_allocs;
	int	num_lpg_downgrade;
	int	num_page_splits;
	uint	enabled_16k:1;
	uint	enabled_64k:1;
	uint	enabled_256k:1;
	uint	enabled_1m:1;
	uint	enabled_4m:1;
	uint	enabled_16m:1;
	uint	reserved:26;
} lpg_stat_info_t;

typedef struct cellinfo {
	uint	short_read;
	uint	short_write;
	uint	short_readdir;
	uint	short_readlink;
	uint	listio_read;
	uint	listio_write;
} cellinfo_t;

#if defined(_KERNEL) || defined (_KMEMUSER)
struct syserr {
	unsigned int	inodeovf;
	unsigned int	fileovf;
	unsigned int	textovf;
	unsigned int	procovf;
	unsigned int	pad[2];		/* padding for future expansion */
};
#endif /* _KERNEL || _KMEMUSER */

#ifdef _KERNEL

extern struct syswait syswait;

/* ksa must come after syserr */
#include "sys/ksa.h"

struct shlbinfo {
	unsigned int	shlbs;	/* Max # of libs a process can link in	*/
				/*   at one time.			*/
	unsigned int	shlblnks;/* # of times processes that have used	*/
				/*   static shared libraries.		*/
	unsigned int	shlbovf;/* # of processes needed more shlibs	*/
				/*   than the system imposed limit.	*/
	unsigned int	shlbatts;/* # of times processes have attached	*/
				/*   run time libraries.		*/
};

extern struct shlbinfo shlbinfo;

#endif /* _KERNEL */
#ifdef __cplusplus
}
#endif
#endif /* __SYS_SYSINFO_H__ */
