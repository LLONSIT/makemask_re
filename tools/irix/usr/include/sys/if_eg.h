/*
 * Copyright 1998, Silicon Graphics, Inc. 
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics, Inc.;
 * the contents of this file may not be disclosed to third parties, copied or 
 * duplicated in any form, in whole or in part, without the prior written 
 * permission of Silicon Graphics, Inc.
 *
 * RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to restrictions 
 * as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data
 * and Computer Software clause at DFARS 252.227-7013, and/or in similar or 
 * successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished - 
 * rights reserved under the Copyright Laws of the United States.
 */
#ifndef _sys_if_eg_h
#define _sys_if_eg_h

/* $Revision: 1.23 $ */

#include <net/if.h>

#define EG_MAX_UNIT 32
#ifdef _KERNEL

#include <sys/misc/ether.h>
#include <sys/PCI/pciio.h>
#include "tigon.h"

/*
 * RX buffer
 */
#define	BUF_SIZE_STD	 2048
#define	BUF_SIZE_JMB	16384

/*
 * Note: The egrxbuf struct is a construct used for easy access to
 *       a frame's payload (just beyond the 14 byte frame header).  
 *       In addition to the ethernet frame header, the etherbufhead
 *       struct contains headers for interface (ifheader) and snoop
 *       info (snoopheader).  It also contains alignment padding 
 *       (ebh_pad) to ensure that the upper layer protocol routines
 *       have word-aligned access to the payload data (i.e. the 
 *       upper layer protocol headers and data).
 *
 *       The egrxbuf struct is "overlaid" in either a 2K (standard
 *       frame) or 16K (Jumbo Frame) mbuf.  The space required for
 *       the additional structures and padding reduces the amount
 *       of space available in the mbuf.  Thus the space available
 *       in the mbuf for payload data (excluding the frame header)
 *       is
 *             BUF_SIZE_XXX - sizeof(struct etherbufhead)
 * 
 *       Furthermore, because the offset of the mbuf's mdat buffer
 *       is potentially incremented in the driver for cache-line 
 *       alignment, the space available in the mbuf may be further
 *       reduced.  Thus, the rb_data field of the egrxbuf struct
 *       cannot be correctly sized at compile time without the
 *       risk of it over-running the mbuf in which it is overlaid.
 *
 *       Finally, since this field is just a place holder for the
 *       the beginning of the payload data in the mbuf allocated 
 *       for the frame, we can give it a symbolic (i.e. meaningless)
 *       length of "1".
 */

#define EG_DUMMY_RBDATA_LEN  1

struct egrxbuf {
	struct etherbufhead	rb_ebh;
	u_char			rb_data[EG_DUMMY_RBDATA_LEN];
};

#define EHDROFFSET (sizeof(struct etherbufhead) - sizeof(struct ether_header))

/*
 * principle per interface structure
 */

struct eg_info {
    struct etherif	ti_eif;			/* common ethernet interface */
    volatile tg_shmem_t	*ti_shmem;	/* shared memory area on NIC */

    volatile struct tg_gen_info	*ti_geninfo;	/* general info page on host */
    
    lock_t      tx_lock; /*Tx section lock */
    uint	ti_flags;
    sv_t    ti_sv;                          /* for multicast ioctls */ 
    time_t	ti_waittime;			/* time we went to sleep */

    pciio_dmamap_t	ti_fastmap;		/* pciio fast dmamap handle */

    volatile struct tg_event *ti_evring;		/* event ring in host memory */

    volatile struct send_bd	*ti_txring;		/* tx ring in board memory */

    lock_t intr_lock; /* interrupt Lock */

    __psint_t   clk_time;
    __psint_t   clk_time2;
    uint  ti_intr_cnt;

    lock_t      reclaim_lock;    /* reclaim lock */
    uint        tr_flags;         /* flags for reclaim bit lock */
    int		ti_txprod;		/* send producer index */
    int		ti_txcons_shad;		/* send consumer index */
    int             ti_cmdcons_shad;        /* shadow cmd consumer */
    int             ti_cmdprod;             /* cmd producer index */
    int             ti_evcons;           	/* event consumer */
    volatile U64   *ti_evprodptr;		/* event producer index in host memory */
    volatile U64   *ti_txconsptr;		/* send consumer index in host memory */

    struct mbuf	**ti_txm;		/* tx mbufs pending */

    struct tg_stats *ti_stats2;           	/* refresh stats */

    char pad[128];   /* remove later:  for cache */

    lock_t       rx_lock;   /*Rx section lock */
    uint    	 ti_rflags;  
    volatile struct recv_bd	*ti_rxring_std;		/* std rx ring in host memory */
    volatile struct recv_bd	*ti_rxring_jumbo;	/* jumbo rx ring in host memory */
    volatile struct recv_bd	*ti_rxring_rtn;		/* return rx ring in host memory */

    int		ti_rxstd_prod;		/* std recv ring prod index */
    int		ti_rxstd_cons;		/* std recv ring cons index */

    int		ti_rxjumbo_prod;	/* jumbo rx ring prod index */
    int		ti_rxjumbo_cons;	/* jumbo rx ring cons index */
  
    int		ti_rxrtn_cons_real;	/* return rx cons index */

    U64	        *ti_rxrtn_prod;		/* NIC writes into this */
    struct mbuf	**ti_rxm_std;		/* std rx mbufs posted */
    struct mbuf	**ti_rxm_jumbo;		/* jumbo rx mbufs posted */
    uint32_t	ti_randcount;		/* counter for entropy gathering */

    /* --- infrequently referenced fields below this line --- */
    mutex_t         sleep_mutex;    /* Sleep mutex for ioctl exclusion */

    vertex_hdl_t	ti_conn_vhdl;		/* vertex for requesting pci services */
    vertex_hdl_t	ti_enet_vhdl;		/* vertex for ethernet private info */
    pciio_intr_t	ti_intr;		/* interrupt handle */
    U32             ti_rev;                 /* FW revision */
    U32             ti_nrrbs;               /* number of bridge RRBs */
    U32             ti_gotrrbs;             /* rrb_alloc() done */
    U32		ti_dbg_mask;		/* debugging mask */
    U32		ti_dbg_level;		/* debugging mask */
    U32             ti_nmulti;              /* # multicast enabled */
    U32		ti_FWrefreshes;		/* # FW downloads */
    /* stats */
    U32		ti_defers;		/* # cumulative defers */
    U32		ti_runt;		/* # runt packets */
    U32		ti_crc;			/* # crc errors */
    U32		ti_framerr;		/* # coding error */
    U32		ti_giant;		/* # giant pkt errors */
    U32		ti_idrop;		/* # dropped input packets */
    U32		ti_memerr;		/* # rx/tx memory error */
    U32		ti_rtry;		/* # tx retry errors */
    U32		ti_exdefer;		/* # excessive defers */
    U32		ti_lcol;		/* # late collisions */
    U32		ti_txgiant;		/* # tx giant packets */
    U32		ti_linkdrop;		/* # tx dropped w/link down */
    U32		ti_nombufs;		/* # tx m_get failures */
    U32		ti_notxds;		/* # tx out of txds */
    U32		ti_restart;		/* # needed restart from intr */
    U32		ti_noq;			/* # tx no queue space */
    U32         ti_cmdoflo;             /* # cmdring out of free entries */
    /* More stats */
    U32         ti_reclaim_lock;        /*  */
    U32         ti_reclaim_held;
    /* firmware download variables */
    U32		ti_tigonFwStartAddr;
    U32		ti_tigonFwTextAddr;
    int		ti_tigonFwTextLen;
    U32		*ti_tigonFwText;
    U32		ti_tigonFwDataAddr;
    int		ti_tigonFwDataLen;
    U32		*ti_tigonFwData;
    U32		ti_tigonFwRodataAddr;
    int		ti_tigonFwRodataLen;
    U32		*ti_tigonFwRodata;
    U32		ti_tigonFwBssAddr;
    int		ti_tigonFwBssLen;
    U32		ti_tigonFwSbssAddr;
    int		ti_tigonFwSbssLen;


    U32			bid_base;	/* NIC addr of bid tabl		*/

    tigon_bufx_entry_t	*bufx_base;	/* base address of bufx table	*/
    int         ti_curlinkpref;     /* This is the current link pref setting */
    uint        eg_highbw_state;    /* IFF_HIGHBW flag state */
};

/* easy access macros */
#define ti_regs         ti_shmem->regs
#define ti_gencom	ti_shmem->gen_com
#define ti_memwindow    ti_shmem->loc_mem_window
#define ti_cmdcons	ti_gencom.command_cons_index
#define ti_shmemevcons	ti_gencom.event_cons_index
#define ti_tuneparams   ti_gencom.tuneParms
#define ti_macaddr	ti_gencom.mac_addr
#define ti_cmdring	ti_gencom.command_ring
#define ti_genctlregs   ti_regs.gen_control
#define ti_mhc          ti_genctlregs.misc_host_control
#define ti_cpuctlregs   ti_regs.cpu_control

#define	ti_ac		ti_eif.eif_arpcom	/* common arp stuff */
#define	ti_if		ti_ac.ac_if		/* ifnet */
#define	ti_unit		ti_if.if_unit		/* logical unit # */
#define	ti_curaddr	ti_ac.ac_enaddr		/* current ether addr */
#define	ti_addr		ti_eif.eif_addr		/* i/f official addr */
#define	ti_rawif	ti_eif.eif_rawif	/* raw domain interface */
#define	eiftoti(eif)	((struct eg_info*)(eif)->eif_private)

/*
 * Flags used with ti_flags.
 */
#define	TIF_CKSUM_MASK	0x3		/* enable tx/rx hw checksum */
#define	TIF_CKSUM_RX	0x1		/* enable rx hw checksum */
#define	TIF_CKSUM_TX	0x2		/* enable tx hw checksum */
#define	TIF_LINKUP	0x4		/* T/F link failure */
#define	TIF_LINKDOWN	0x8		/* T/F link failure */
#define TIF_FWLOADING   0x10            /* XXX: firmware being loaded now */
#define TIF_MULTI_ACTIVE  0x20          /* adding multicast address now */

#define TIF_ILOCK       0x1000

#define	TIF_TLOCK	0x1000		/* private driver tx bitlock */
#define	TIF_RLOCK	0x2000		/* private driver rx bitlock */
#define TIF_RCLOCK      0x4000
#define TIF_PSENABLED   0x8000          /* Enable RSVP packet scheduling */

#define EG_CACHELINE_SIZE	 128	/* secondary cache line size */

#define	GBE_JUMBO_MTU 		 9000
#define MAXBLOCKSIZE_JMB  	 9018
#define MAXBLOCKSIZE_STD	 1518

struct eg_bufxu {
        char    ifr_name[IFNAMSIZ];	/* if name, e.g. "eg0" 		*/
	U64	ptr;			/* pointer to bufx images	*/
	U32	len;			/* number of contig bufx entries*/
	U32	indx;			/* starting bufx index		*/

};

struct eg_bidu {
        char    ifr_name[IFNAMSIZ];	/* if name, e.g. "eg0" 		*/
	tigon_bid_entry_t	bimg;	/* bid image to copy		*/
	U32			indx;	/* bid index to update		*/
};

#endif	/* _KERNEL */

struct eg_treq {
        char    ifr_name[IFNAMSIZ];             /* if name, e.g. "eg0" */
        U64     tbufp;
        int     cmd;

};

struct eg_rreq {
	char    ifr_name[IFNAMSIZ];
	U32     data;
	U32     addr;   /* really an offset */
};

struct eg_mreq {
	char    ifr_name[IFNAMSIZ];
	U32     egAddr;
	U32     len;
	U64	userAddr;
};

struct eg_dreq {
	char    ifr_name[IFNAMSIZ];
	U32     debug_mask;
	U32     debug_level;   
};

struct eg_fwreq {
        char    ifr_name[IFNAMSIZ];
	U32 releaseMajor;
	U32 releaseMinor;
	U32 releaseFix;
	U32 startAddr;
	U32 textAddr;
	int textLen;
	U32 dataAddr;
	int dataLen;
	U32 rodataAddr;
	int rodataLen;
	U32 bssAddr;
	int bssLen;
	U32 sbssAddr;
	int sbssLen;
	U64 fwText;
	U64 fwData;
	U64 fwRodata;
};

/* internal ioctls; not intended for general use */
#define ALT_GETNTRACE		_IOWR('G', 1, struct ifreq)
#define ALT_SETTRACE		_IOW('G', 2, struct ifreq)
#define ALT_READTRACE		_IOR('G', 3, struct ifreq)
#define ALT_GET_NIC_STATS	_IOWR('G', 4, struct ifreq)
#define ALT_CLEARPROFILE	_IOW('G', 5, struct ifreq)
#define ALT_READ_EG_REG		_IOWR('G', 6, struct ifreq)
#define ALT_WRITE_EG_REG	_IOW('G', 7, struct ifreq)
#define ALT_CLEARSTATS		_IOW('G', 8, struct ifreq)
#define ALT_SETPROMISC		_IOW('G', 9, struct ifreq)
#define ALT_UNSETPROMISC	_IOW('G', 10, struct ifreq)
#define ALT_CACHE_FW		_IOW('G', 11, struct eg_fwreq)
#define ALT_SETDEBUG		_IOW('G', 13, struct ifreq)
#define ALT_LINK_NEG		_IOW('G', 14, struct ifreq)
#define ALT_READMEM		_IOWR('G',15, struct ifreq)
#ifdef _KERNEL
#define ALT_ST_BUFX_UPDATE	_IOW('G', 16, struct eg_bufxu)
#define ALT_ST_BID_CLEAR	_IOW('G', 17, struct eg_bidu)
#define ALT_ST_BID_UPDATE	_IOW('G', 18, struct eg_bidu)
#endif	/* _KERNEL */
#define	ALT_WRITE_EG_MEM	_IOW('G', 20, struct ifreq)
#define ALT_SETLINKPREF         _IOW('G', 21, struct ifreq)
#define ALT_EGDUMMY            _IOWR('G', 22, struct ifreq)

#define MAX_TEXT_LEN   82*1024
#define MAX_RODATA_LEN 7*1024
#define MAX_DATA_LEN   3*1024

#define ALT_DEFAULT_LINK   0
#define ALT_10_100_LINK    1
#define ALT_1000_FULL_LINK 2
#define ALT_1000_HALF_LINK 3
#define ALT_100_FULL_LINK  4
#define ALT_100_HALF_LINK  5
#define ALT_10_FULL_LINK   6
#define ALT_10_HALF_LINK   7

#define ALT_QUERY_NEG_FCTL     0x00000001
#define ALT_CHANGE_LINK_NEG    0x00000002
#define ALT_CHANGE_FCTL        0x00000004
#define ALT_NEW_LINK_NEG_VAL   0x00000008
#define ALT_NEW_FCTL_VAL       0x00000010
#define ALT_LINK_NEG_QUERY     0x00000020
#define ALT_FCTL_QUERY         0x00000040

#define EG_MAX_UNIT 32

#endif	/* _sys_if_eg_h */
