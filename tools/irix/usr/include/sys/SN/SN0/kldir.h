/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1992-1999, Silicon Graphics, Inc.          *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 **************************************************************************/

#ifndef __SYS_SN_SN0_KLDIR_H__
#define __SYS_SN_SN0_KLDIR_H__

#ident "$Revision: 1.4 $"

/*
 * The upper portion of the memory map applies during boot
 * only and is overwritten by IRIX/SYMMON.  The minimum memory bank
 * size on SN0 is 32M, which provides a limit on the amount of space
 * the PROM can assume it has available.
 *
 * Most of the addresses below are defined as macros in this file, or
 * in SN/addrs.h or SN/SN0/addrs.h.
 *
 *                                    MEMORY MAP PER NODE
 *
 * 0x2000000 (32M)         +-----------------------------------------+
 *                         |      IO6 BUFFERS FOR FLASH ENET IOC3    |
 * 0x1F80000 (31.5M)       +-----------------------------------------+
 *                         |                              (3M SN0,   |
 *                         |      IO6 TEXT/DATA/BSS/stack  4M SN0XXL)|
 * 0x1C00000 (28M)         +-----------------------------------------+
 *                         |      IP27 Topology (PCFG), stack, misc. |
 * 0x1B00000 (27M)         +-----------------------------------------+
 *                         |      IP27 PROM TEXT/DATA/BSS            |
 * 0x1A00000 (26M)         +-----------------------------------------+
 *                         |      Routing temp. space                |
 * 0x1800000 (24M)         +-----------------------------------------+
 *                         |      Diagnostics temp. space            |
 * 0x1500000 (21M)         +-----------------------------------------+
 *                         |      Free                               |
 * 0x1400000 (20M)         +-----------------------------------------+
 *                         |      IO6 PROM temporary copy            |
 * 0x1300000 (19M)         +-----------------------------------------+
 *                         |                                         |
 *                         |      Free                               |
 *                         |      (UNIX DATA starts above 0x1000000) |
 *                         |                                         |
 *                         +-----------------------------------------+
 *                         |      UNIX DEBUG Version                 |
 * 0x0300000 (3M)          +-----------------------------------------+
 *  (0x0360000 on SN0XXL)  |      SYMMON, loaded just below UNIX     |
 *                         |      (For UNIX Debug only)              |
 *                         |                                         |
 *                         |                                         |
 * 0x0034000 (208K)        +-----------------------------------------+
 *                         |      SYMMON STACK [NUM_CPU_PER_NODE]    |
 *                         |      (For UNIX Debug only)              |
 * 0x0025000 (148K)        +-----------------------------------------+
 *                         |                                         |
 *                         |                                         |
 *                         |      UNIX NON-DEBUG Version             |
 * 0x0019000 (100K)        +-----------------------------------------+
 *
 *
 * The lower portion of the memory map contains information that is
 * permanent and is used by the IP27PROM, IO6PROM and IRIX.
 *
 * 0x19000 (100K)          +-----------------------------------------+
 *                         |      Unused                             |
 * 0x17000 (92K)           +-----------------------------------------+
 *                         |      GPDA                               |
 * 0x16000 (88K)           +-----------------------------------------+
 *                         |                                         |
 *                         |      PI Error Spools (16K)              |
 *                         |                                         |
 * 0x12000 (72K)           +-----------------------------------------+
 *                         |      Unused                             |
 * 0x11c00 (71K)           +-----------------------------------------+
 *                         |      CPU 1 NMI Eframe area       	     |
 * 0x11a00 (70.5K)         +-----------------------------------------+
 *                         |      CPU 0 NMI Eframe area       	     |
 * 0x11800 (70K)           +-----------------------------------------+
 *                         |      CPU 1 NMI Register save area       |
 * 0x11600 (69.5K)         +-----------------------------------------+
 *                         |      CPU 0 NMI Register save area       |
 * 0x11400 (69K)           +-----------------------------------------+
 *                         |      GDA (1k)                           |
 * 0x11000 (68K)           +-----------------------------------------+
 *                         |      Early cache Exception stack (CPU 1)|
 * 0x10800 (66k)	   +-----------------------------------------+
 *			   |      cache error eframe (CPU 1)	     |
 * 0x10400 (65K)           +-----------------------------------------+
 *                         |      Exception Handlers (CPU 1, UALIAS) |
 * 0x10000 (64K)           +-----------------------------------------+
 *                         |                                         |
 *                         |                                         |
 *                         |      KLCONFIG (48K)                     |
 *                         |                                         |
 *                         |                                         |
 *                         |                                         |
 * 0x04000 (16K)           +-----------------------------------------+
 *                         |      NMI Handler (Protected Page)       |
 * 0x03000 (12K)           +-----------------------------------------+
 *                         |      ARCS PVECTORS (master node only)   |
 * 0x02c00 (11K)           +-----------------------------------------+
 *                         |      ARCS TVECTORS (master node only)   |
 * 0x02800 (10K)           +-----------------------------------------+
 *                         |      LAUNCH [NUM_CPU]                   |
 * 0x02400 (9K)            +-----------------------------------------+
 *                         |      Low memory directory (KLDIR)       |
 * 0x02000 (8K)            +-----------------------------------------+
 *                         |      ARCS SPB (1K)                      |
 * 0x01000 (4K)            +-----------------------------------------+
 *                         |      Early cache Exception stack (CPU 0)|
 * 0x00800 (2k)	           +-----------------------------------------+
 *			   |      cache error eframe (CPU 0)	     |
 * 0x00400 (1K)            +-----------------------------------------+
 *                         |      Exception Handlers (CPU 0)         |
 * 0x00000 (0K)            +-----------------------------------------+
 */

/*
 * NOTE:  To change the kernel load address, you must update:
 *  - the appropriate elspec files in irix/kern/master.d
 *  - NODEBUGUNIX_ADDR in SN/SN0/addrs.h
 *  - IP27_FREEMEM_OFFSET below
 *  - the memory map above
 *
 * To change the kernel debug load address, you must update:
 *  - the appropriate elspec files in irix/kern/master.d
 *  - DEBUGUNIX_ADDR in SN/SN0/addrs.h
 *  - UNIX_DEBUG_LOADADDR in SN/addrs.h
 *  - DBGLOADADDR in stand/arcs/symmon/Makefile
 *  - the memory map above
 */


/*
 * This is defined here because IP27_SYMMON_STK_SIZE must be at least what
 * we define here.  Since it's set up in the prom.  We can't redefine it later
 * and expect more space to be allocated.  The way to find out the true size
 * of the symmon stacks is to divide SYMMON_STK_SIZE by SYMMON_STK_STRIDE
 * for a particular node.
 */
#define SYMMON_STACK_SIZE		0x8000

#if defined (PROM) || defined (SABLE)

/*
 * These defines are prom version dependent.  No code other than the IP27
 * prom should attempt to use these values.
 */
#define IP27_LAUNCH_OFFSET		0x2400
#define IP27_LAUNCH_SIZE		0x400
#define IP27_LAUNCH_COUNT		2
#define IP27_LAUNCH_STRIDE		0x200

#define IP27_KLCONFIG_OFFSET		0x4000
#define IP27_KLCONFIG_SIZE		0xc000
#define IP27_KLCONFIG_COUNT		1
#define IP27_KLCONFIG_STRIDE		0

#define IP27_NMI_OFFSET			0x3000
#define IP27_NMI_SIZE			0x40
#define IP27_NMI_COUNT			2
#define IP27_NMI_STRIDE			0x40

#define IP27_PI_ERROR_OFFSET		0x12000
#define IP27_PI_ERROR_SIZE		0x4000
#define IP27_PI_ERROR_COUNT		1
#define IP27_PI_ERROR_STRIDE		0

#define IP27_SYMMON_STK_OFFSET		0x25000
#define IP27_SYMMON_STK_SIZE		0xe000
#define IP27_SYMMON_STK_COUNT		2
/* IP27_SYMMON_STK_STRIDE must be >= SYMMON_STACK_SIZE */
#define IP27_SYMMON_STK_STRIDE		0x7000

#define IP27_FREEMEM_OFFSET		0x19000
#define IP27_FREEMEM_SIZE		-1
#define IP27_FREEMEM_COUNT		1
#define IP27_FREEMEM_STRIDE		0

#endif /* PROM || SABLE*/
/*
 * There will be only one of these in a partition so the IO6 must set it up.
 */
#define IO6_GDA_OFFSET			0x11000
#define IO6_GDA_SIZE			0x400
#define IO6_GDA_COUNT			1
#define IO6_GDA_STRIDE			0

/*
 * save area of kernel nmi regs in the prom format
 */
#define IP27_NMI_KREGS_OFFSET		0x11400
#define IP27_NMI_KREGS_CPU_SIZE		0x200
/*
 * save area of kernel nmi regs in eframe format 
 */
#define IP27_NMI_EFRAME_OFFSET		0x11800
#define IP27_NMI_EFRAME_SIZE		0x200

#define GPDA_OFFSET			0x16000

#endif /* __SYS_SN_SN0_KLDIR_H__ */
