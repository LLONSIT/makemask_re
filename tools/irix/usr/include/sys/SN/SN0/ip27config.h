/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1992-2000, Silicon Graphics, Inc.          *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 **************************************************************************/

#ifndef __SYS_SN_SN0_IP27CONFIG_H__
#define __SYS_SN_SN0_IP27CONFIG_H__

#include <sys/mips_addrspace.h>

/*
 * Structure: 	ip27config_s
 * Typedef:	ip27config_t
 * Purpose: 	Maps out the region of the boot prom used to define
 *		configuration information.
 * Notes:       Corresponds to ip27config structure found in start.s.
 *		Members are ulong where possible to facilitate PROM fetches.
 */

#define CONFIG_INFO_OFFSET		0x60

#define IP27CONFIG_ADDR			(LBOOT_BASE	    + \
					 CONFIG_INFO_OFFSET)
#define IP27CONFIG_ADDR_NODE(n)		(NODE_RBOOT_BASE(n) + \
					 CONFIG_INFO_OFFSET)

#define IP27CONFIG_SN00_ADDR		(IP27CONFIG_ADDR + 48)
#define IP27CONFIG_SN00_ADDR_NODE(n)	(IP27CONFIG_ADDR_NODE(n) + 48)

/* Offset to the config_type field within local ip27config structure */
#define CONFIG_FLAGS_ADDR			(IP27CONFIG_ADDR + 72)
/* Offset to the config_type field in the ip27config structure on 
 * node with nasid n
 */
#define CONFIG_FLAGS_ADDR_NODE(n)		(IP27CONFIG_ADDR_NODE(n) + 72)

/* Meaning of each valid bit in the config flags 
 * Right now only bit 0 is valid.
 * If it is set the config corresponds to 12p 4io
 */
#define CONFIG_FLAG_12P4I		0x1
/*
 * Since 800 ns works well with various HUB frequencies, (such as 360,
 * 380, 390, and 400 MHZ), we now use 800ns rtc cycle time instead of
 * 1 microsec.
 */
#define IP27_RTC_FREQ			1250	/* 800ns cycle time */

#if _LANGUAGE_C

typedef	struct ip27config_s {		/* KEEP IN SYNC w/ start.s & below  */
    uint		time_const;	/* Time constant 		    */
    uint		r10k_mode;	/* R10k boot mode bits 		    */

    __uint64_t		magic;		/* CONFIG_MAGIC			    */

    __uint64_t		freq_cpu;	/* Hz 				    */
    __uint64_t		freq_hub;	/* Hz 				    */
    __uint64_t		freq_rtc;	/* Hz 				    */

    uint		ecc_enable;	/* ECC enable flag		    */
    uint		fprom_cyc;	/* FPROM_CYC speed control  	    */

    uint		mach_type;	/* Inidicate SN0 (0) or Sn00 (1)    */

    uint		check_sum_adj;	/* Used after config hdr overlay    */
					/* to make the checksum 0 again     */
    uint		flash_count;	/* Value incr'd on each PROM flash  */
    uint		fprom_wr;	/* FPROM_WR speed control  	    */

    uint		pvers_vers;	/* Prom version number		    */
    uint		pvers_rev;	/* Prom revision number		    */
    uint		config_type;	/* To support special configurations
					 * If bit 0 is set it means that
					 * we are looking 12P4I config
					 */
} ip27config_t;

typedef	struct {
    uint		r10k_mode;	/* R10k boot mode bits 		    */
    uint		freq_cpu;	/* Hz 				    */
    uint		freq_hub;	/* Hz 				    */
    char		fprom_cyc;	/* FPROM_CYC speed control  	    */
    char		mach_type;	/* Inidicate SN0 (0) or Sn00 (1)    */
    char		fprom_wr;	/* FPROM_WR speed control  	    */
} ip27config_modifiable_t;

#define IP27CONFIG		(*(ip27config_t *) IP27CONFIG_ADDR)
#define IP27CONFIG_NODE(n)	(*(ip27config_t *) IP27CONFIG_ADDR_NODE(n))
#define SN00			(*(uint *) (IP27CONFIG_SN00_ADDR))
#define SN00_NODE(n)		(*(uint *) (IP27CONFIG_SN00_ADDR_NODE(n)))

/* Get the config flags from local ip27config */
#define CONFIG_FLAGS		(*(uint *) (CONFIG_FLAGS_ADDR))
/* Get the config flags from ip27config on the node
 * with nasid n
 */
#define CONFIG_FLAGS_NODE(n)	(*(uint *) (CONFIG_FLAGS_ADDR_NODE(n)))

/* Macro to check if the local ip27config indicates a config
 * of 12 p 4io
 */
#define CONFIG_12P4I		(CONFIG_FLAGS & CONFIG_FLAG_12P4I)
/* Macro to check if the ip27config on node with nasid n
 * indicates a config of 12 p 4io
 */
#define CONFIG_12P4I_NODE(n)	(CONFIG_FLAGS_NODE(n) & CONFIG_FLAG_12P4I)

#endif /* _LANGUAGE_C */

#if _LANGUAGE_ASSEMBLY
	.struct		0		/* KEEP IN SYNC WITH C structure */

ip27c_time_const:	.word	0
ip27c_r10k_mode:	.word	0

ip27c_magic:		.dword	0

ip27c_freq_cpu:		.dword	0
ip27c_freq_hub:		.dword	0
ip27c_freq_rtc:		.dword	0

ip27c_ecc_enable:	.word	1
ip27c_fprom_cyc:	.word	0

ip27c_mach_type:	.word	0
ip27c_check_sum_adj:	.word	0

ip27c_flash_count:	.word	0
ip27c_fprom_wr:		.word	0

ip27c_pvers_vers:	.word	0
ip27c_pvers_rev:	.word	0

ip27c_config_type:	.word 	0	/* To recognize special configs */
#endif /* _LANGUAGE_ASSEMBLY */

/*
 * R10000 Configuration Cycle - These define the SYSAD values used
 * during the reset cycle.
 */

#define IP27C_MHZ(x)			(1000000 * (x))
#define IP27C_KHZ(x)			(1000 * (x))
#define IP27C_MB(x)			((x) << 20)

/*
 * PROM Configurations
 */

#define CONFIG_MAGIC		0x69703237636f6e66

#define CONFIG_TIME_CONST	0xb

#define CONFIG_ECC_ENABLE	1
#define CONFIG_CHECK_SUM_ADJ	0
#define CONFIG_DEFAULT_FLASH_COUNT    0
#define CONFIG_SN0_FPROM_WR 1
#define CONFIG_SN00_FPROM_WR 4
#define CONFIG_SN0_FPROM_CYC 8
#define CONFIG_SN00_FPROM_CYC 15

/*
 * Some promICEs have trouble if FPROM_CYC is too low.
 * The nominal value for 100 MHz hub is 5.
 * any update to the below should also reflected in the logic in
 *   IO6prom/flashprom.c function _verify_config_info and _fill_in_config_info
 */

#define SN0_MACH_TYPE	      0
#define SN00_MACH_TYPE	      1

#define CONFIG_FREQ_RTC	IP27C_KHZ(IP27_RTC_FREQ)

#if _LANGUAGE_C


#define NUMB_IP27_CONFIGS 0x1a


#define O200_DEF        CONFIG_SN00_FPROM_CYC,\
			SN00_MACH_TYPE,\
			CONFIG_SN00_FPROM_WR

#define O2K_DEF         CONFIG_SN0_FPROM_CYC,\
			SN0_MACH_TYPE,\
                        CONFIG_SN0_FPROM_WR


#ifdef DEF_IP27_CONFIG_TABLE

/*
 *	DO NOT REMOVE ANY EMPTY ENTRIES FROM THIS TABLE 
 *
 *	The IP31 PSC is used as an index into this table, so empty
 * 	entries should not be removed.
 *
 *	0x0-0x1		reserved for IP27
 *	0x2-0xe		reserved for IP31
 *	0xf		no PIMM present indication for IP31
 *	0x10-0x19	reserved for O200
 */


/*
 * list of currently know configurations. Please update this list when
 * a new configuration is added. The output can be easily generated
 * by irix/cmd/mips/modechk
 *
 *
 * -------------------------------------------------------------------------------
 * O2000 Configurations : 
 * Table 0x00 Hub= 90.0 CPU=180MHZ [ok ] mode=0x1211a785 L2$ 1MB/120 MHZ tap=0x9
 * Table 0x01 Hub= 97.5 CPU=195MHZ [ok ] mode=0x1213a785 L2$ 4MB/130 MHZ tap=0x9
 * Table 0x05 Hub=100.0 CPU=450MHZ [ok ] mode=0x069bb185 L2$ 4MB/225 MHZ tap=0x3
 * Table 0x06 Hub=100.0 CPU=350MHZ [ok ] mode=0x1213ad85 L2$ 4MB/233 MHZ tap=0x9
 * Table 0x07 Hub=100.0 CPU=500MHZ [ok ] mode=0x089cb385 L2$ 8MB/250 MHZ tap=0xa
 * Table 0x08 Hub=100.0 CPU=400MHZ [ok ] mode=0x1414af85 L2$ 8MB/266 MHZ tap=0xa
 * Table 0x09 Hub=100.0 CPU=300MHZ [ok ] mode=0x1414ab85 L2$ 8MB/200 MHZ tap=0xa
 * Table 0x0a Hub=100.0 CPU=250MHZ [ok ] mode=0x120ba985 L2$ 4MB/250 MHZ tap=0x9
 * -------------------------------------------------------------------------------
 * O200 Configurations : 
 * Table 0x10 Hub= 90.0 CPU=180MHZ [ok ] mode=0x1211a785 L2$ 1MB/120 MHZ tap=0x9
 * Table 0x11 Hub= 90.0 CPU=180MHZ [ok ] mode=0x100aa785 L2$ 2MB/180 MHZ tap=0x8
 * Table 0x12 Hub= 90.0 CPU=225MHZ [ok ] mode=0x120aa985 L2$ 2MB/225 MHZ tap=0x9
 * Table 0x13 Hub= 90.0 CPU=270MHZ [ok ] mode=0x1213ab85 L2$ 4MB/180 MHZ tap=0x9
 * Table 0x14 Hub= 90.0 CPU=360MHZ [ok ] mode=0x1613af85 L2$ 4MB/240 MHZ tap=0xb
 *
 */


static ip27config_modifiable_t ip27config_table[NUMB_IP27_CONFIGS] = {

#define	SYSCLK(x)	R10KC_SYSCLKDIV(x)
#define	SCACHESZ(x)	R10KC_SCSIZE(x)
#define	SCACHECLK(x)	R10KC_SCCLKDIV(x)
#define	TAP(x)		R10KC_TAP(x)
#define	SCACHE_DDR	R10KC_DDR(1)

/* **********************************************************************
 *
 *		O 2 0 0 0	IP27
 *		---------
 *
 * IP27 PIMMs do not have a PSC. Simply reserve slot 0 and 1 for this,
 * there will be no new IP27 boards
 * **********************************************************************
 */

{/*0x0*/ (R10KC_DEF | SYSCLK(3) | SCACHESZ(1) | SCACHECLK(2) | TAP(0x9)),
	 IP27C_MHZ(180), IP27C_MHZ(90), O2K_DEF, },
{/*0x1*/ (R10KC_DEF | SYSCLK(3) | SCACHESZ(3) | SCACHECLK(2) | TAP(9)),
	 IP27C_MHZ(195), IP27C_KHZ(97500), O2K_DEF, },

/* **********************************************************************
 *
 *		O 2 0 0 0	IP31
 *		---------
 *
 * The index in this table is the PSC. 
 * **********************************************************************
 */
{/*0x2*/ 0,},
{/*0x3*/ 0,},
{/*0x4*/ 0,},
{/*0x5 	 450Mhz R14K O2K pimm */
	 (R10KC_DEF | SYSCLK(8) | SCACHESZ(3) | SCACHECLK(3) | TAP(0x3) | SCACHE_DDR),
	 IP27C_MHZ(450), IP27C_MHZ(100), O2K_DEF, },

{/*0x6   IP31 PSC 0x6 R12KS SGI2100 */
         (R10KC_DEF | SYSCLK(6) | SCACHESZ(3) | SCACHECLK(2) | TAP(0x9)),
         IP27C_MHZ(350), IP27C_MHZ(100), O2K_DEF, },

{/*0x7 	 500Mhz R14K O2K pimm 030-1547-001 */
	 (R10KC_DEF | SYSCLK(9) | SCACHESZ(4) | SCACHECLK(3) | TAP(0xa) | SCACHE_DDR),
	 IP27C_MHZ(500), IP27C_MHZ(100), O2K_DEF, },

{/*0x8   IP31 PSC 0x8 R12KS */
         (R10KC_DEF | SYSCLK(7) | SCACHESZ(4) | SCACHECLK(2) | TAP(0xa)),
         IP27C_MHZ(400), IP27C_MHZ(100), O2K_DEF, },
{/*0x9*/ (R10KC_DEF | SYSCLK(5) | SCACHESZ(4) | SCACHECLK(2) | TAP(0xa)),
         IP27C_MHZ(300), IP27C_MHZ(100), O2K_DEF, },
{/*0xa*/ (R10KC_DEF | SYSCLK(4) | SCACHESZ(3) | SCACHECLK(1) | TAP(0x9)),
         IP27C_MHZ(250), IP27C_MHZ(100), O2K_DEF, },

{/*0xb*/ 0,},
{/*0xc*/ 0,},
{/*0xd*/ 0,},


{/*0xe*/ 0, },

/*
 * reserved. IP31s use PSC 0xf to indicate a headless node.
 */
{/*0xf*/ 0, },

/* **********************************************************************
 *
 *		O 2 0 0
 *		-------
 *
 * **********************************************************************
 */

{/*0x10*/ (R10KC_DEF | SYSCLK(3) | SCACHESZ(1) | SCACHECLK(2) | TAP(0x9)),
	  IP27C_MHZ(180), IP27C_MHZ(90), O200_DEF, },
{/*0x11*/ (R10KC_DEF | SYSCLK(3) | SCACHESZ(2) | SCACHECLK(1) | TAP(0x8)),
	  IP27C_MHZ(180), IP27C_MHZ(90), O200_DEF, },
{/*0x12*/ (R10KC_DEF | SYSCLK(4) | SCACHESZ(2) | SCACHECLK(1) | TAP(0x9)),
	  IP27C_MHZ(225), IP27C_MHZ(90), O200_DEF, },
{/*0x13*/ (R10KC_DEF | SYSCLK(5) | SCACHESZ(3) | SCACHECLK(2) | TAP(0x9)),
	  IP27C_MHZ(270), IP27C_MHZ(90), O200_DEF, },
{/*0x14*/ (R10KC_DEF | SYSCLK(7) | SCACHESZ(3) | SCACHECLK(2) | TAP(0xb)),
            IP27C_MHZ(360), IP27C_MHZ(90), O200_DEF, },
{/*0x15*/ 0, },
{/*0x16*/ 0, },
{/*0x17*/ 0, },
{/*0x18*/ 0, },
{/*0x19*/ 0, },

};

#else	/* DEF_IP27_CONFIG_TABLE */
extern	ip27config_modifiable_t	ip27config_table[];
#endif  /* DEF_IP27_CONFIG_TABLE */


#endif /* _LANGUAGE_C */

#endif /* __SYS_SN_SN0_IP27CONFIG_H__ */
