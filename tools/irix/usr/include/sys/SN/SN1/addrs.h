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

#ifndef __SYS_SN_SN1_ADDRS_H__
#define __SYS_SN_SN1_ADDRS_H__


/*
 * SN1 (on a TRex) Address map
 *
 * This file contains a set of definitions and macros which are used
 * to reference into the major address spaces (CAC, HSPEC, IO, MSPEC,
 * and UNCAC) used by the SN1 architecture.  It also contains addresses
 * for "major" statically locatable PROM/Kernel data structures, such as
 * the partition table, the configuration data structure, etc.
 * We make an implicit assumption that the processor using this file
 * follows the R12K's provisions for specifying uncached attributes;
 * should this change, the base registers may very well become processor-
 * dependent.
 *
 * For more information on the address spaces, see the "Local Resources"
 * chapter of the Hub specification.
 *
 * NOTE: This header file is included both by C and by assembler source
 *	 files.  Please bracket any language-dependent definitions
 *	 appropriately.
 */

#ident "$Revision: 1.19 $"

/*
 * Some of the macros here need to be casted to appropriate types when used
 * from C.  They definitely must not be casted from assembly language so we
 * use some new ANSI preprocessor stuff to paste these on where needed.
 */

#if defined(_RUN_UNCACHED)
#define CAC_BASE		0x9600000000000000
#else
#define CAC_BASE		0xa800000000000000
#endif

#define HSPEC_BASE		0x9000000000000000
#define IO_BASE			0x9200000000000000
#define MSPEC_BASE		0x9400000000000000
#define UNCAC_BASE		0x9600000000000000

#define TO_PHYS(x)		(	      ((x) & TO_PHYS_MASK))
#define TO_CAC(x)		(CAC_BASE   | ((x) & TO_PHYS_MASK))
#define TO_UNCAC(x)		(UNCAC_BASE | ((x) & TO_PHYS_MASK))
#define TO_MSPEC(x)		(MSPEC_BASE | ((x) & TO_PHYS_MASK))
#define TO_HSPEC(x)		(HSPEC_BASE | ((x) & TO_PHYS_MASK))


/*
 * The following couple of definitions will eventually need to be variables,
 * since the amount of address space assigned to each node depends on
 * whether the system is running in N-mode (more nodes with less memory)
 * or M-mode (fewer nodes with more memory).  We expect that it will
 * be a while before we need to make this decision dynamically, though,
 * so for now we just use defines bracketed by an ifdef.
 */

#if defined(N_MODE)

#define NODE_SIZE_BITS		32
#define BWIN_SIZE_BITS		28

#define NASID_BITS		8
#define NASID_BITMASK		(0xffLL)
#define NASID_SHFT		32
#define NASID_META_BITS		1
#define NASID_LOCAL_BITS	7

#define BDDIR_UPPER_MASK	(UINT64_CAST 0x1ffffff0)
#define BDECC_UPPER_MASK	(UINT64_CAST 0x1fffffff)

#else /* !defined(N_MODE), assume that M-mode is desired */

#define NODE_SIZE_BITS		33
#define BWIN_SIZE_BITS		29

#define NASID_BITMASK		(0x7fLL)
#define NASID_BITS		7
#define NASID_SHFT		33
#define NASID_META_BITS		0
#define NASID_LOCAL_BITS	7

#define BDDIR_UPPER_MASK	(UINT64_CAST 0x3ffffff0)
#define BDECC_UPPER_MASK	(UINT64_CAST 0x3fffffff)

#endif /* defined(N_MODE) */

#define NODE_ADDRSPACE_SIZE	(UINT64_CAST 1 << NODE_SIZE_BITS)

#define NASID_MASK		(UINT64_CAST NASID_BITMASK << NASID_SHFT)
#define NASID_GET(_pa)		(int) ((UINT64_CAST (_pa) >>		\
					NASID_SHFT) & NASID_BITMASK)

#if _LANGUAGE_C && !defined(_STANDALONE)
#define NODE_SWIN_BASE(nasid, widget)					\
	((widget == 0) ? NODE_BWIN_BASE((nasid), SWIN0_BIGWIN)		\
	: RAW_NODE_SWIN_BASE(nasid, widget))
#else
#define NODE_SWIN_BASE(nasid, widget) \
     (NODE_IO_BASE(nasid) + (UINT64_CAST (widget) << SWIN_SIZE_BITS))
#endif /* _LANGUAGE_C */

/*
 * The following definitions pertain to the IO special address
 * space.  They define the location of the big and little windows
 * of any given node.
 */

#define BWIN_INDEX_BITS		3
#define BWIN_SIZE		(UINT64_CAST 1 << BWIN_SIZE_BITS)
#define	BWIN_SIZEMASK		(BWIN_SIZE - 1)
#define	BWIN_WIDGET_MASK	0x7
#define NODE_BWIN_BASE0(nasid)	(NODE_IO_BASE(nasid) + BWIN_SIZE)
#define NODE_BWIN_BASE(nasid, bigwin)	(NODE_BWIN_BASE0(nasid) + 	\
			(UINT64_CAST (bigwin) << BWIN_SIZE_BITS))

#define	BWIN_WIDGETADDR(addr)	((addr) & BWIN_SIZEMASK)
#define	BWIN_WINDOWNUM(addr)	(((addr) >> BWIN_SIZE_BITS) & BWIN_WIDGET_MASK)
/*
 * Verify if addr belongs to large window address of node with "nasid"
 *
 *
 * NOTE: "addr" is expected to be XKPHYS address, and NOT physical
 * address
 *
 *
 */

#define	NODE_BWIN_ADDR(nasid, addr)	\
		(((addr) >= NODE_BWIN_BASE0(nasid)) && \
		 ((addr) < (NODE_BWIN_BASE(nasid, HUB_NUM_BIG_WINDOW) + \
				BWIN_SIZE)))

/*
 * The following define the major position-independent aliases used
 * in SN0.
 *	CALIAS -- Varies in size, points to the first n bytes of memory
 *		  	on the reader's node.
 */

#define CALIAS_BASE		CAC_BASE



#define BRIDGE_REG_PTR(_base, _off)	((volatile bridgereg_t *) \
	((__psunsigned_t)(_base) + (__psunsigned_t)(_off)))

#define SN0_WIDGET_BASE(_nasid, _wid)	(NODE_SWIN_BASE((_nasid), (_wid)))

#if _LANGUAGE_C
#define KERN_NMI_ADDR(nasid, slice)					\
                    TO_NODE_UNCAC((nasid), IP27_NMI_KREGS_OFFSET + 	\
				  (IP27_NMI_KREGS_CPU_SIZE * (slice)))
#endif /* _LANGUAGE_C */

#ifdef PROM

#define MISC_PROM_BASE		PHYS_TO_K0(0x01300000)
#define MISC_PROM_SIZE		0x200000

#define DIAG_BASE		PHYS_TO_K0(0x01500000)
#define DIAG_SIZE		0x300000

#define ROUTE_BASE		PHYS_TO_K0(0x01800000)
#define ROUTE_SIZE		0x200000

#define IP27PROM_FLASH_HDR	PHYS_TO_K0(0x01300000)
#define IP27PROM_FLASH_DATA	PHYS_TO_K0(0x01301000)
#define IP27PROM_CORP_MAX	32
#define IP27PROM_CORP		PHYS_TO_K0(0x01800000)
#define IP27PROM_CORP_SIZE	0x10000
#define IP27PROM_CORP_STK	PHYS_TO_K0(0x01810000)
#define IP27PROM_CORP_STKSIZE	0x2000
#define IP27PROM_DECOMP_BUF	PHYS_TO_K0(0x01900000)
#define IP27PROM_DECOMP_SIZE	0xfff00

#define IP27PROM_BASE		PHYS_TO_K0(0x01a00000)
#define IP27PROM_BASE_MAPPED	(K2BASE | 0x1fc00000)
#define IP27PROM_SIZE_MAX	0x200000

/* Note:  the PROM stacks are accessed via the TLB, so must lie
 * within 2M of IP27PROM_BASE (or IP35prom/tlb.s must be fixed)
 */
#define IP27PROM_STACK_A	PHYS_TO_K0(0x01be0000)
#define IP27PROM_STACK_C	PHYS_TO_K0(0x01bf0000)
#define IP27PROM_STACK_SHFT	15
#define IP27PROM_STACK_SIZE	(1 << IP27PROM_STACK_SHFT)

#define SLAVESTACK_BASE		PHYS_TO_K0(0x01580000)
#define SLAVESTACK_SIZE		0x40000

#define ENETBUFS_BASE		PHYS_TO_K0(0x01f80000)
#define ENETBUFS_SIZE		0x20000

/* The route cache is only used by the CPU PROM and can be
   safely overwritten as the IO PROM is loaded. */
#define IP27PROM_DRT_CACHE_BASE IO6PROM_BASE
#define IP27PROM_DRT_CACHE_SIZE 0x2000

#define IO6PROM_BASE		PHYS_TO_K0(0x03000000)
#define IO6PROM_SIZE		0x400000
#define	IO6PROM_BASE_MAPPED	(K2BASE | 0x13000000)
#define IO6DPROM_BASE		PHYS_TO_K0(0x03000000)
#define IO6DPROM_SIZE		0x200000

#define IP27PROM_PCFG_K1	PHYS_TO_K1(0x02000000)
#define IP27PROM_PCFG		PHYS_TO_K0(0x02000000)
#define IP27PROM_PCFG_SIZE	0xd0000
#define IP27PROM_ERRDMP		PHYS_TO_K1(0x020d0000)
#define IP27PROM_ERRDMP_SIZE	0xf000

#define IP27PROM_INIT_START	PHYS_TO_K1(0x020d0000)
#define IP27PROM_CONSOLE	PHYS_TO_K1(0x020df000)
#define IP27PROM_CONSOLE_SIZE	0x200
#define IP27PROM_NETUART	PHYS_TO_K1(0x020df200)
#define IP27PROM_NETUART_SIZE	0x100
#define IP27PROM_UNUSED1	PHYS_TO_K1(0x020df300)
#define IP27PROM_UNUSED1_SIZE	0xd00
#define IP27PROM_INIT_END	PHYS_TO_K0(0x020e2000)

#define NODEBUGUNIX_ADDR	PHYS_TO_K0(0x00040000)
#define DEBUGUNIX_ADDR		PHYS_TO_K0(0x00310000)

#define IP27PROM_INT_LAUNCH	10	/* and 11 */
#define IP27PROM_INT_NETUART	12	/* through 17 */
#endif /* PROM */

/*
 * needed by symmon so it needs to be outside #if PROM
 * (see also POD_ELSCSIZE)
 */
#define IP27PROM_ELSC_BASE_A	PHYS_TO_K0(0x020e0000)
#define IP27PROM_ELSC_BASE_B	PHYS_TO_K0(0x020e0800)
#define IP27PROM_ELSC_BASE_C	PHYS_TO_K0(0x020e1000)
#define IP27PROM_ELSC_BASE_D	PHYS_TO_K0(0x020e1800)
#define IP27PROM_ELSC_SHFT	11
#define IP27PROM_ELSC_SIZE	(1 << IP27PROM_ELSC_SHFT)

#define FREEMEM_BASE		PHYS_TO_K0(0x4000000)

#define IO6PROM_STACK_SHFT	14	/* stack per cpu */
#define IO6PROM_STACK_SIZE	(1 << IO6PROM_STACK_SHFT)

/*
 * IP27 PROM vectors
 */

#define IP27PROM_ENTRY		PHYS_TO_COMPATK1(0x1fc00000)
#define IP27PROM_RESTART	PHYS_TO_COMPATK1(0x1fc00008)
#define IP27PROM_SLAVELOOP	PHYS_TO_COMPATK1(0x1fc00010)
#define IP27PROM_PODMODE	PHYS_TO_COMPATK1(0x1fc00018)
#define IP27PROM_IOC3UARTPOD	PHYS_TO_COMPATK1(0x1fc00020)
#define IP27PROM_FLASHLEDS	PHYS_TO_COMPATK1(0x1fc00028)
#define IP27PROM_REPOD		PHYS_TO_COMPATK1(0x1fc00030)
#define IP27PROM_LAUNCHSLAVE	PHYS_TO_COMPATK1(0x1fc00038)
#define IP27PROM_WAITSLAVE	PHYS_TO_COMPATK1(0x1fc00040)
#define IP27PROM_POLLSLAVE	PHYS_TO_COMPATK1(0x1fc00048)

#define KL_UART_BASE	LOCAL_HSPEC(HSPEC_UART_0)	/* base of UART regs */
#define KL_UART_CMD	LOCAL_HSPEC(HSPEC_UART_0)	/* UART command reg */
#define KL_UART_DATA	LOCAL_HSPEC(HSPEC_UART_1)	/* UART data reg */

#if !_LANGUAGE_ASSEMBLY
/* Address 0x400 to 0x1000 ualias points to cache error eframe + misc
 * CACHE_ERR_SP_PTR could either contain an address to the stack, or
 * the stack could start at CACHE_ERR_SP_PTR
 */
#if defined (HUB_ERR_STS_WAR)
#define CACHE_ERR_EFRAME	0x480
#else /* HUB_ERR_STS_WAR */
#define CACHE_ERR_EFRAME	0x400
#endif /* HUB_ERR_STS_WAR */

#define CACHE_ERR_ECCFRAME	(CACHE_ERR_EFRAME + EF_SIZE)
#define CACHE_ERR_SP_PTR	(0x1000 - 32)	/* why -32? TBD */
#define CACHE_ERR_IBASE_PTR	(0x1000 - 40)
#define CACHE_ERR_SP		(CACHE_ERR_SP_PTR - 16)
#define CACHE_ERR_AREA_SIZE	(ARCS_SPB_OFFSET - CACHE_ERR_EFRAME)

#endif	/* !_LANGUAGE_ASSEMBLY */

/* Each CPU accesses UALIAS at a different physaddr, on 32k boundaries
 * This determines the locations of the exception vectors
 */
#define UALIAS_FLIP_BASE	UALIAS_BASE
#define UALIAS_FLIP_SHIFT	15
#define UALIAS_FLIP_ADDR(_x)	((_x) ^ (cputoslice(getcpuid())<<UALIAS_FLIP_SHIFT))

#define EX_HANDLER_OFFSET(slice) ((slice) << UALIAS_FLIP_SHIFT)
#define EX_HANDLER_ADDR(nasid, slice)					\
	PHYS_TO_K0(NODE_OFFSET(nasid) | EX_HANDLER_OFFSET(slice))
#define EX_HANDLER_SIZE		0x0400

#define EX_FRAME_OFFSET(slice)	((slice) << UALIAS_FLIP_SHIFT | 0x400)
#define EX_FRAME_ADDR(nasid, slice)					\
	PHYS_TO_K0(NODE_OFFSET(nasid) | EX_FRAME_OFFSET(slice))
#define EX_FRAME_SIZE		0x0c00

#define _ARCSPROM

#ifdef _STANDALONE

/*
 * The PROM needs to pass the device base address and the
 * device pci cfg space address to the device drivers during
 * install. The COMPONENT->Key field is used for this purpose.
 * Macros needed by SN0 device drivers to convert the
 * COMPONENT->Key field to the respective base address.
 * Key field looks as follows:
 *
 *  +----------------------------------------------------+
 *  |devnasid | widget  |pciid |hubwidid|hstnasid | adap |
 *  |   2     |   1     |  1   |   1    |    2    |   1  |
 *  +----------------------------------------------------+
 *  |         |         |      |        |         |      |
 *  64        48        40     32       24        8      0
 *
 * With the introduction of PIC (PX-Brick) the pciid takes on new
 * meaning. We now have the concept of upto 8 slots (really  only 4
 * when an IO9/IOC4 is installed and otherwise 2) and multiple buses.
 * For PIC there are 2 buses (0 and 1). On top of all this, the PIC
 * bridge associates slot 1 with bridge device 0, 2 with 1 etc. where
 * BRIDGE and XBRIDGE associated the slot number with the bridge device
 * number. So any time we want to address device memory space we need to
 * subtract the slot number by 1 to get the proper association. NOTE this
 * does NOT apply to config space which maps the same as previous bridges.
 * So with this in mind the pciid field will be broken up as follows.
 *     --------------------
 *     |Type | Bus | Slot |
 *     --------------------
 *     |     |     |      |
 *     40    37    35     32
 *
 * In an attempt to provide some level of support multifunction PCI cards in
 * the prom, the Type field is being further subdivided.  So, we can support
 * functions 0 & 1 of multifunction cards in the Prom.
 *     ------------------
 *     |Function | Type |
 *     ------------------
 *     |         |      |
 *     40        39     37
 *
 * These are used by standalone drivers till the io infrastructure
 * is in place.
 */

#if _LANGUAGE_C

#include <sys/PCI/bridge.h>

extern __uint64_t make_sn_key(nasid_t nasid, int widid, int pciid, int busid, int funcid);

#define uchar unsigned char

#define KEY_DEVNASID_SHFT  48
#define KEY_WIDID_SHFT	   40
#define KEY_FUNCID_SHFT    39
#define KEY_TYPEID_SHFT    37
#define KEY_BUSID_SHFT     35
#define KEY_PCIID_SHFT     32
#define KEY_HUBWID_SHFT	   24
#define KEY_HSTNASID_SHFT  8

#define MK_SN0_KEYF(nasid, widid, pciid, busid, funcid) \
		make_sn_key(nasid, widid, pciid, busid, funcid)
#define MK_SN0_KEY(nasid, widid, pciid, busid) \
		MK_SN0_KEYF(nasid, widid, pciid, busid, 0)

#define ADD_HUBWID_KEY(key,hubwid)\
			(key|=((__psunsigned_t)hubwid << KEY_HUBWID_SHFT))

#define ADD_HSTNASID_KEY(key,hstnasid)\
			(key|=((__psunsigned_t)hstnasid << KEY_HSTNASID_SHFT))

#define ADD_FUNCID_KEY(key,funcid)\
                        (key|=((__psunsigned_t)funcid << KEY_FUNCID_SHFT))

#define ADD_TYPEID_KEY(key,typeid)\
                        (key|=((__psunsigned_t)typeid << KEY_TYPEID_SHFT))

#define ADD_BUSID_KEY(key,busid)\
                        (key|=((__psunsigned_t)busid << KEY_BUSID_SHFT))

#define GET_DEVNASID_FROM_KEY(key)	((short)(key >> KEY_DEVNASID_SHFT))
#define GET_WIDID_FROM_KEY(key)		((uchar)(key >> KEY_WIDID_SHFT))
#define GET_FUNCID_FROM_KEY(key)	((uchar)(key >> KEY_FUNCID_SHFT)& 0x1)
#define GET_TYPEID_FROM_KEY(key)	((uchar)(key >> KEY_TYPEID_SHFT)& 0x3)
#define GET_BUSID_FROM_KEY(key)		((uchar)(key >> KEY_BUSID_SHFT)& 0x3)
#define GET_PCIID_FROM_KEY(key)		((uchar)(key >> KEY_PCIID_SHFT)& 0x7)
#define GET_HUBWID_FROM_KEY(key)	((uchar)(key >> KEY_HUBWID_SHFT))
#define GET_HSTNASID_FROM_KEY(key)	((short)(key >> KEY_HSTNASID_SHFT))

#define	PCI_BUS1_SHIFT	23
#define	PCIBUS_GET(_pa) ((_pa & PIC_BUS1_OFFSET) >> PCI_BUS1_SHIFT)

#define PCI_64_TARGID_SHFT		60

/*
 * When handing out PCI BAR addresses on bridge-based platforms, pci_mem_base
 * aligns BAR's on 2^20 boundaries.  With the addition of multifunction
 * support, we further subdivide the lower 20 bits among the possible
 * functions (currently only 2).  These macros need to change if we support
 * more than 2 functions in the future, or if the algorithm in pci_mem_base
 * changes.
 */

#define PCIBASE_SHIFT			19
#define PCIBASE_OFFSET(func)		(func << PCIBASE_SHIFT)

/* This change should handle xbridge as well as PIC bridges as long as the Bus Id
 * and "especially" the type id have been added to the created key. Currently bus 1
 * of a PIC bridge should not even have to be detected as we really only care about 
 * the baseio in prom. And the PCI baseio will always be in bus 0 slot 1 widget C of
 * an IX-brick. 
 * 
 * The TYPEID for a PIC bridge should be 1. Since our PCI base for a PIC device is
 * always slot number - 1 we subtract the TYPEID from the PCIID in calculating the
 * pci base. THis is probably not the best way of handling this since a new bridge
 * type will require this to be reworked, but it currently works for PIC/Xbridge.
 */
#define GET_PCIBASE_FROM_KEY(key)  (NODE_SWIN_BASE(GET_DEVNASID_FROM_KEY(key),\
					GET_WIDID_FROM_KEY(key))\
				| PCIBRIDGE_DEVIO(GET_BUSID_FROM_KEY(key),\
						GET_PCIID_FROM_KEY(key) -\
						GET_TYPEID_FROM_KEY(key)) \
				| PCIBASE_OFFSET(GET_FUNCID_FROM_KEY(key)))

#define GET_PCICFGBASE_FROM_KEY(key) \
			(NODE_SWIN_BASE(GET_DEVNASID_FROM_KEY(key),\
			      GET_WIDID_FROM_KEY(key))\
			| PCIBRIDGE_TYPE0_CFG_DEVF(GET_BUSID_FROM_KEY(key), \
		                              GET_PCIID_FROM_KEY(key),\
					      GET_FUNCID_FROM_KEY(key)))

#define GET_WIDBASE_FROM_KEY(key) \
                        (NODE_SWIN_BASE(GET_DEVNASID_FROM_KEY(key),\
                              GET_WIDID_FROM_KEY(key)) +           \
						      (GET_BUSID_FROM_KEY(key) ? PIC_BUS1_OFFSET : 0))


#define PUT_INSTALL_STATUS(c,s)		c->Revision = s
#define GET_INSTALL_STATUS(c)		c->Revision

#endif /* LANGUAGE_C */

#endif /* _STANDALONE */

#if defined (HUB_ERR_STS_WAR)

#define	ERR_STS_WAR_NASID	63
#define ERR_STS_WAR_OFFSET	((MD_MEM_BANKS * MD_BANK_SIZE) - 0x100)

#endif /* HUB_ERR_STS_WAR */
#endif /* __SYS_SN_SN1_ADDRS_H__ */
