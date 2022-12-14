/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1992-1997, Silicon Graphics, Inc.          *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 **************************************************************************/

#ifndef __SYS_SN_XTALKADDRS_H__
#define __SYS_SN_XTALKADDRS_H__

/*
 * CrossTalk to SN0 Hub addressing support
 *
 * This file defines the mapping conventions used by the Hub's
 * I/O interface when it receives a read or write request from 
 * a CrossTalk widget.  
 *
 * Format for non-Memory accesses:
 *
 *  +--------------+------------------------------------------------+
 *  | 0  | XXXXX   |        SN0Addr                                |
 *  +----+---------+------------------------------------------------+
 *    47  46     40 39                                             0
 *	bit 47 indicates Memory (0)
 *	bits 46..40 are unused
 *	bits 39..0 hold the memory address
 *			(bits 39..31 hold the nodeID in N mode
 *			 bits 39..32 hold the nodeID in M mode
 * By design, this looks exactly like a 0-extended SN0 Address, so
 * we don't need to do any conversions.
 *
 *
 *
 * Format for non-Memory accesses:
 *
 *  +--------------+------+---------+------+--+---------------------+
 *  | 1  | DstNode | XXXX | BigW=0  | SW=1 | 1|   Addr              |
 *  +----+---------+------+---------+------+--+---------------------+
 *    47  46     38 37  31 30     28 27  24 23 22                  0
 *
 *	bit 47 indicates IO (1)
 *      bits 46..38 hold the destination node ID
 *      bits 37..31 are unused
 *      bits 30..28 hold the big window being addressed
 *      bits 27..24 hold the small window being addressed
 *                  0 always refers to the xbow
 *                  1 always refers to the hub itself
 *      bit 23 indicates local (0) or remote (1)
 *             no accessing checks are done if this bit is 0
 *      bits 22..0 hold the register address
 *                 bits 22..21 determine which section of the hub
 *                              00 -> PI
 *                              01 -> MD
 *                              10 -> IO
 *                              11 -> NI
 * This looks very much like a REMOTE_HUB access, except the nodeID
 * is in a different place, and the highest xtalk bit is set.
 */

#ident "$Revision: 1.7 $"


/* Hub-specific xtalk definitions */

#define HX_MEM_BIT		0L	/* Hub's idea of xtalk memory access */
#define HX_IO_BIT		1L	/* Hub's idea of xtalk register access */
#define HX_ACCTYPE_SHIFT	47

#if SN0
#define HX_NODE_SHIFT		38
#elif SN1
#define HX_NODE_SHIFT		39
#endif

#define HX_BIGWIN_SHIFT		28

#define HX_SWIN_SHIFT		23

#define HX_LOCACC		0L	/* local access */
#define HX_REMACC		1L	/* remote access */
#define HX_ACCESS_SHIFT		23

/*
 * Pre-calculate the fixed portion of a crosstalk address that maps
 * to local register space on a hub.
 */
#define HX_REG_BASE		((HX_IO_BIT<<HX_ACCTYPE_SHIFT) + \
				(0L<<HX_BIGWIN_SHIFT) + \
				(1L<<HX_SWIN_SHIFT) + IALIAS_SIZE + \
				(HX_REMACC<<HX_ACCESS_SHIFT))

/* 
 * Return a crosstalk address which a widget can use to access a
 * designated register on a designated node.
 */
#define HUBREG_AS_XTALKADDR(nasid, regaddr) \
	((iopaddr_t)(HX_REG_BASE + (((long)nasid)<<HX_NODE_SHIFT) + ((long)regaddr)))

#if TBD
#assert sizeof(iopaddr_t) == 8
#endif /* TBD */

/*
 * Get widget part number, given node id and widget id. 
 * Always do a 32-bit read, because some widgets, e.g., Bridge, require so.
 * Widget ID is at offset 0 for 64-bit access.  Add 4 to get lower 32 bits
 * in big endian mode. 
 * XXX Double check this with Hub, Xbow, Bridge and other hardware folks.
 */
#define XWIDGET_ID_READ(nasid, widget) \
        (widgetreg_t)(*(volatile __uint32_t *)(NODE_SWIN_BASE(nasid, widget) + 0x00 + 4))


#endif /* __SYS_SN_XTALKADDRS_H__ */
