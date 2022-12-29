/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1992-1998, Silicon Graphics, Inc.          *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 **************************************************************************/

#ifndef __SYS_SN_SN1_IP35_H__
#define __SYS_SN_SN1_IP35_H__

#if defined(_KERNEL) || defined(_STANDALONE)
/*
 * Simple definitions for the masks which remove SW bits from pte.
 */

#define TLBLO_HWBITSHIFT	0		/* Shift value, for masking */

#if !_LANGUAGE_ASSEMBLY

#define CAUSE_BERRINTR 		CAUSE_IP7

#define ECCF_CACHE_ERR  0
#define ECCF_TAGLO      1
#define ECCF_ECC        2
#define ECCF_ERROREPC   3
#define ECCF_PADDR      4
#define ECCF_SIZE       (5 * sizeof(long))

#endif /* !_LANGUAGE_ASSEMBLY */


/*
 * Because we actually assume that the normal status register state
 * isn't zero, we define a value which is written into the status
 * register when we want to clear it.
 */

#ifdef _STANDALONE
#  define NORMAL_SR	(SR_KX|SR_FR|SR_BEV|SR_CU1)
#endif /* _STANDALONE */

/*
 * R10000 status register interrupt bit mask usage for IP35.
 */
#define SRB_SWTIMO	CAUSE_SW1	/* 0x00100 */
#define SRB_NET		CAUSE_SW2	/* 0x00200 */
#define SRB_DEV0	CAUSE_IP3	/* 0x00400 */
#define SRB_DEV1	CAUSE_IP4	/* 0x00800 */
#define SRB_TIMOCLK	CAUSE_IP5	/* 0x01000 */
#define SRB_PROFCLK	CAUSE_IP6	/* 0x02000 */
#define SRB_ERR		CAUSE_IP7	/* 0x04000 */
#define SRB_SCHEDCLK	CAUSE_IP8	/* 0x08000 */

#define SPLHI_DISABLED_INTS	SRB_SWTIMO|SRB_NET|SRB_TIMOCLK|SRB_SCHEDCLK|SRB_DEV0
#define SPLPROF_DISABLED_INTS	SRB_SWTIMO|SRB_NET|SRB_TIMOCLK|SRB_SCHEDCLK|SRB_DEV0|SRB_PROFCLK
#define SPL7_DISABLED_INTS	SRB_SWTIMO|SRB_NET|SRB_TIMOCLK|SRB_SCHEDCLK|SRB_DEV0|SRB_PROFCLK|SRB_DEV1|SRB_ERR 

#define SR_HI_MASK	(SRB_DEV1 | SRB_PROFCLK | SRB_ERR)
#define SR_PROF_MASK	(SRB_DEV1 | SRB_ERR)
#define SR_ALL_MASK	(0)
#define SR_IBIT_HI	SRB_DEV0
#define SR_IBIT_PROF	SRB_PROFCLK

#define SRB_SWTIMO_IDX		0
#define SRB_NET_IDX		1
#define SRB_DEV0_IDX		2
#define SRB_DEV1_IDX		3
#define SRB_TIMOCLK_IDX		4
#define SRB_PROFCLK_IDX		5
#define SRB_ERR_IDX		6
#define SRB_SCHEDCLK_IDX	7

#define NUM_CAUSE_INTRS		8

#define SCACHE_LINESIZE	128
#define SCACHE_LINEMASK	(SCACHE_LINESIZE - 1)

#include <sys/SN/addrs.h>

#define LED_CYCLE_MASK  0x0f
#define LED_CYCLE_SHFT  4

#define SEND_NMI(_nasid, _slice)	\
          REMOTE_HUB_PI_S((_nasid), SUBNODE(_slice), (PI_NMI_A + PI_NMI_OFFSET * LOCALCPU(_slice)), 1)

#endif	/* defined(_KERNEL) || defined(_STANDALONE) */


/*
 * PIMM_PSC codes for values read from the HSPEC_SYNERGY0_0 register
 * N.B.: When adding a new config, the psc_to_flash_config[] table in
 * sys/SN/SN1/ip27config.h needs to be updated
 *
 * The PIMM codes are used by the flashio command, and so are
 * exported to user space
 */

#define	PIMM_NOT_PRESENT		0xf
#define PIMM_2__400__R12__1_08__4__270  0x0
#define PIMM_2__500__R14__1_08__8__250  0x1
#define	PIMM_2__300__R12__2_60__4__200	0xe /* o200 PIMM w/xlator */

#if defined(_KERNEL) || defined(_STANDALONE)

/*
 * The speedo2 system (SN10) is flagged by bits 2^14 and 2^15
 * (HS_NON_CBRICK_MASK) of the junk bus supplying the PSC code
 * being set to binary 10 (HS_SN10_BITS).  For a speedo2 system
 * there are not two PSC codes occupying the lower two 4-bit
 * nibbles of the bus, but one 8-bit PSC code.
 */

#define SN10							\
    ((LOCAL_HSPEC_L(HSPEC_SYNERGY0_0) & HS_NON_CBRICK_MASK)	\
      == HS_SN10_BITS)
#define SN10_NODE(nasid)						\
    ((REMOTE_HSPEC_L(nasid, HSPEC_SYNERGY0_0) & HS_NON_CBRICK_MASK)	\
      == HS_SN10_BITS)

/*
 * Runtime check macro for Asterix system - "SN11".
 * Much like speedo2 above, the Asterix system is flagged
 * by bits 15 and 14 of the junk bus supplying the PSC
 * code being set to binary 01 (HS_SN11_BITS).
 */

#define SN11							\
    ((LOCAL_HSPEC_L(HSPEC_SYNERGY0_0) & HS_NON_CBRICK_MASK)	\
      == HS_SN11_BITS)
#define SN11_NODE(nasid)						\
    ((REMOTE_HSPEC_L(nasid, HSPEC_SYNERGY0_0) & HS_NON_CBRICK_MASK)	\
      == HS_SN11_BITS)

/*
 * Runtime check macro for the IP53 node board. This board
 * is used in chimera and twister systems.
 */

#define IP53							\
    ((LOCAL_HSPEC_L(HSPEC_SYNERGY0_0) & HS_NON_CBRICK_MASK)	\
      == HS_IP53_BITS)
#define IP53_NODE(nasid)						\
    ((REMOTE_HSPEC_L(nasid, HSPEC_SYNERGY0_0) & HS_NON_CBRICK_MASK)	\
      == HS_IP53_BITS)

/*
 * The PE-brick requires a runtime check similar to speedo2
 * and asterix.  A PE-brick is indicated by bits 15 and 14 on
 * the junk bus both being set (HS_PEBRICK_BITS == binary 11).
 *
 * PEBRICK_NODE() does not have a 'local' counterpart (as SN10_NODE
 * and SN11_NODE do) because the macro should never be run locally--
 * if you have CPUs, you're obviously not a PE-brick.
 */
#define PEBRICK_NODE(nasid)						\
    ((REMOTE_HSPEC_L(nasid, HSPEC_SYNERGY0_0) & HS_NON_CBRICK_MASK)	\
      == HS_PEBRICK_BITS)

/* 
 * If the PSC is for a speedo2, then add 16 to the PSC index in order
 * to index into an expansion table for speedo2 only PSC values.
 * For Asterix (SN11), we add 32 (0x20) so that the PSC values are indexed
 * in the range of 0x2?
 */


#define	PIMM_PSC(nasid, subnode)	\
    (IP53_NODE(nasid) ? \
     ((REMOTE_HSPEC_L(nasid, HSPEC_SYNERGY0_0) & HS_IP53_PSC_MASK) >> \
      HS_IP53_PSC_SHFT) + 48 : \
    (SN11_NODE(nasid) ? \
     ((REMOTE_HSPEC_L(nasid, HSPEC_SYNERGY0_0) & HS_SN11_PSC_MASK) >> \
      HS_SN11_PSC_SHFT) + 32 : \
    (SN10_NODE(nasid) ? \
     ((REMOTE_HSPEC_L(nasid, HSPEC_SYNERGY0_0) & HS_SN10_PSC_MASK) >> \
      HS_SN10_PSC_SHFT) + 16 : \
     ((REMOTE_HSPEC_L(nasid, HSPEC_SYNERGY0_0) & HS_PIMM_PSC_MASK(subnode)) >> \
      HS_PIMM_PSC_SHFT(subnode)))))

#define	PIMM_PRESENT(nasid, subnode) \
    (PIMM_PSC(nasid, subnode) != PIMM_NOT_PRESENT)

#endif	/* defined(_KERNEL) || defined(_STANDALONE) */

#if !_LANGUAGE_ASSEMBLY

/*
 * Runtime checks for "chimera" machines.
 *
 * Example usages:
 *
 * if (SN12) - to tell if we on a chimera.
 * if (SN12_WS) - to tell if we are on a chimera workstation.
 * if (SN12_NODE(nasid)) - to tell if node <nasid> is a chimera.
 *
 * NOTE - because these defintions end up calling the L1
 * directly, there are some limitations on how/where the definitions
 * can be used. Bascially, they cannot be used any place where
 * an sc_open call has been made and it's corresponding sc_close
 * has yet to be made, such as:
 * sc_open()
 * <code>
 * if (SN12)
 * <code>
 * sc_close()
 *
 * This will fail because SN12 calls sc_open and sc_open cannot be 
 * reinvoked without first calling sc_close. If necessary, assign
 * the result of SN12 to a local variable first to solve the
 * above problem, like so:
 * int is_sn12 = SN12
 * sc_open()
 * <code>
 * if (is_sn12)
 * <code>
 * sc_close()
 *
 * Luckily, there are very few places where these limitations exist
 * in the code currently, mainly only l1.c, l1_command.c and eeprom.c.
 */
#define	SN12_TYPE_UNKNOWN -1
#define SN12_2U_TYPE	1
#define SN12_GB_TYPE	2
#define SN12_WS_TYPE	3
#define SN12_CGN_TYPE	4
#define SN12_RWS_TYPE	5

#define	SN12		(get_chimera_type(get_nasid()) != 0)
#define SN12_2U		(get_chimera_type(get_nasid()) == SN12_2U_TYPE)
#define SN12_GB		(get_chimera_type(get_nasid()) == SN12_GB_TYPE)
#define SN12_WS		(get_chimera_type(get_nasid()) == SN12_WS_TYPE)
#define SN12_CGN	(get_chimera_type(get_nasid()) == SN12_CGN_TYPE)
#define SN12_RWS	(get_chimera_type(get_nasid()) == SN12_RWS_TYPE)
#define SN12_NODE(nasid)	((get_chimera_type(nasid)) != 0)
#define SN12_2U_NODE(nasid)	((get_chimera_type(nasid)) == SN12_2U_TYPE)
#define SN12_GB_NODE(nasid)	((get_chimera_type(nasid)) == SN12_GB_TYPE)
#define SN12_WS_NODE(nasid)	((get_chimera_type(nasid)) == SN12_WS_TYPE)
#define SN12_CGN_NODE(nasid)	((get_chimera_type(nasid)) == SN12_CGN_TYPE)
#define SN12_RWS_NODE(nasid)	((get_chimera_type(nasid)) == SN12_RWS_TYPE)

#if defined(_STANDALONE)
extern int get_chimera_type(nasid_t nasid); /* defined in stand/arcs/lib/libkl/ml/SN.c */
#else
extern int get_chimera_type(nasid_t nasid); /* defined in ml/SN/SN1/IP35.c */
extern void set_sn12_type(nasid_t nasid); /* defined in ml/SN/SN1/IP35.c */
#endif /* _STANDALONE */
#endif /* !_LANGUAGE_ASSEMBLY */
 

#endif /* __SYS_SN_SN1_IP35_H__ */
