/* $Id: dev_mvp.h,v 1.26 2000/05/26 21:29:23 travis Exp $ */
/*
 * Copyright 1995,1996 Silicon Graphics, Inc.
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


/*
 *  Multiport Video Processor (O2Video)
 */

#ifndef	_MVPDEV_H_
#define	_MVPDEV_H_

#include <dmedia/vl.h>

/*
 * Predefined video sources - see node list for additional ones.
 *
 * VLBadNode will be returned if one of the following inputs is
 * requested but does not exist on the running system (eg., the
 * camera is not plugged in.)
 *
 * Also note that these may or may not actually represent inputs
 * that can operate concurrently.
 */
#define	VL_MVP_VIDEO_SOURCE_CAMERA	1
#define	VL_MVP_VIDEO_SOURCE_COMPOSITE	2
#define	VL_MVP_VIDEO_SOURCE_SVIDEO	3

/*
 * MVP Private controls.
 */
#define	VL_MVP_CTL_BASE		( ('M' << 24 ) | ('V' << 16 ) )
#define	VL_MVP_VIDCTL_BASE	( VL_MVP_CTL_BASE + 0x1000 )

#define	VL_MVP_ACTIVE_SOURCE 		( VL_MVP_CTL_BASE + 1 )
#define	VL_MVP_DEFAULT_TIMING		( VL_MVP_CTL_BASE + 2 )
#define	VL_MVP_ALPHA			( VL_MVP_CTL_BASE + 3 )
#define	VL_MVP_I2CREG			( VL_MVP_CTL_BASE + 4 )
#define	VL_MVP_I2CREG_NONE		( -2 )

typedef union VL_MVP_I2C_U {
    VLControlValue value;
    struct {
	unsigned short address;		/* chip address */
	unsigned short offset;		/* register (or VL_MVP_I2CREG_NONE) */
	unsigned short mask;		/* bits to read or write */
	unsigned short value;		/* value to write or was read back */
    } chip;
} VL_MVP_I2CControlValue;

#define	VL_MVP_DOMINANT_FIELD		( VL_MVP_CTL_BASE + 5 )
#define	VL_MVP_TOP_FIELD		( VL_MVP_CTL_BASE + 6 )
#define	VL_MVP_MSC_BY_FIELDS		( VL_MVP_CTL_BASE + 7 )
#define	VL_MVP_UPDATE_CONTROLS		( VL_MVP_CTL_BASE + 8 )

#define	VL_MVP_GBE_SYNC_SOURCE		( VL_MVP_CTL_BASE + 9 )
#define VL_MVP_AUDIO_SYNC_SOURCE	( VL_MVP_CTL_BASE + 10 )
#define VL_MVP_ZOOMSIZE			( VL_MVP_CTL_BASE + 11 )
#define VL_MVP_FULLSCREEN		( VL_MVP_CTL_BASE + 12 )
#define VL_MVP_GENLOCK_DELAY		( VL_MVP_CTL_BASE + 13 )

/*
 * Replace *special* user timing entries
 *
 * The following timing modes are set via the "VL_TIMING" control
 * and the actual parameters used to capture/send the video can
 * be replaced using the following as the control, and the arg
 * is a (VL_MVP_TimingTableValue) entry (see union define below).
 *
 * Note that the timing is controllable on the video nodes only.
 * (also, these controls should stay consecutive and in this order)
 */
#define	VL_MVP_TIMING_525_USER_SQ	( VL_MVP_CTL_BASE + 14 )
#define	VL_MVP_TIMING_625_USER_SQ	( VL_MVP_CTL_BASE + 15 )
#define	VL_MVP_TIMING_525_USER_CCIR	( VL_MVP_CTL_BASE + 16 )
#define	VL_MVP_TIMING_625_USER_CCIR	( VL_MVP_CTL_BASE + 17 )

typedef struct mvptimingtable_s {
    
    /* 601 timing parameters */
    short	hstart;		/* horiz number of blank pixels */
    short	hactive;	/* horiz number of active pixels */

    char	sof_count_odd;	/* start of field after v==1 when to check f */
    char	sof_count_even;	/* start of field after v==1 when to check f */

    short	vstart_odd;	/* vert number of top blank odd lines */
    short	vstart_even;	/* vert number of top blank even lines */
    short	vactive_odd;	/* vert number of active video odd lines */
    short	vactive_even;	/* vert number of active video even lines */
    short	vend_odd;	/* vert number of bottom blank odd lines */
    short	vend_even;	/* vert number of bottom blank even lines */

    /* parameters after filtering (ie., non-sq to sq, etc.) */
    short	min_x;		/* allowed min offset.x */
    short	min_y;		/* allowed min offset.y */
    short	ref_x;		/* reference size.x (w/o offset) */
    short	ref_y;		/* reference size.x (w/o offset) */
    short	max_x;		/* allowed max offset.x + size.x */
    short	max_y;		/* allowed max offset.y + size.y */

    short	size_x;		/* standard size.x */
    short	size_y;		/* standard size.y */

    char	offset_x;	/* standard offset */
    char	offset_y;	/* standard offset */

    /* other */
    char	rate;		/* standard rate */

} mvptimingtable_t;

typedef union VL_MVP_TIMING_TABLE_U {
    VLControlValue value;
    mvptimingtable_t entry;
} VL_MVP_TimingTableValue;

/*
 * Note these next four are *not* timing change capable but are listed
 * here for completeness.  Basically they implement a mixed timing
 * standard for unusual cases where the horizontal timing is different
 * than the vertical timing.
 */
#define	VL_MVP_TIMING_525X625_CCIR	( VL_MVP_CTL_BASE + 18 )
#define	VL_MVP_TIMING_525X625_SQ	( VL_MVP_CTL_BASE + 19 )
#define	VL_MVP_TIMING_625X525_CCIR	( VL_MVP_CTL_BASE + 20 )
#define	VL_MVP_TIMING_625X525_SQ	( VL_MVP_CTL_BASE + 21 )

/*
 * Pixel/Alpha output enables  (device control)
 *
 * On O2:
 *  primary channel --> analog encoder
 *  secondary channel --> digital video
 */
#define	VL_MVP_OUTPUT_ENABLE		( VL_MVP_CTL_BASE + 22 )
#define	VL_MVP_OUTPUT_ENABLE_PRIMARY_PIXELS	0x2
#define	VL_MVP_OUTPUT_ENABLE_PRIMARY_ALPHA	0x3
#define	VL_MVP_OUTPUT_ENABLE_SECONDARY_PIXELS	0x8
#define	VL_MVP_OUTPUT_ENABLE_SECONDARY_ALPHA	0xc
#define	VL_MVP_OUTPUT_ENABLE_PRIMARY_PASSTHRU	0x12
#define	VL_MVP_OUTPUT_ENABLE_SECONDARY_PASSTHRU	0x28

#define	VL_MVP_OUTPUT_ENABLE_PRIMARY_MASK	0x13
#define	VL_MVP_OUTPUT_ENABLE_SECONDARY_MASK	0x2c

/*
 * YCrCb Clamping (path control)
 *
 * Restrict the data values by clamping the range.
 * (Note if not specified, clamping is "inferred" by the VL_FORMAT value)
 */
#define	VL_MVP_CLAMP_YUV		( VL_MVP_CTL_BASE + 23 )
#define	VL_MVP_CLAMP_DEFAULT		0	/* use VL_FORMAT value */
#define	VL_MVP_CLAMP_NONE		1	/* to pass all SAV/ALPHA */
#define	VL_MVP_CLAMP_1_254		2	/* "extended" YCrCb */
#define	VL_MVP_CLAMP_10_250		3	/* "normal" YCrCb */
#define	VL_MVP_CLAMP_SPECIAL		4	/* used by VL_FORMAT_RAW_DATA */

/* 
 * Allow setting resend of buffers during underflow 
 * ... seperately from the "default signal" control
 *
 * values "off" and "on" are still changed when the default signal
 * is changed on the control panel.  use "fixed off" or "fixed on"
 * to prevent this.
 */
#ifdef	MVP_RETRY_OUTPUT_ENABLED
    #define	VL_MVP_REPEAT_OUTPUT		( VL_MVP_CTL_BASE + 24 )
    #define	VL_MVP_REPEAT_OUTPUT_OFF	0
    #define	VL_MVP_REPEAT_OUTPUT_ON		1
    #define	VL_MVP_REPEAT_OUTPUT_FIXED_OFF	2
    #define	VL_MVP_REPEAT_OUTPUT_FIXED_ON	3
#endif

#endif	/* _MVPDEV_H_ */

/* === */
