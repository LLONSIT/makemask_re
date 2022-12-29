/*
 * dev_sirius.h
 *
 *	device-dependant header file for sirius video
 *
 * Copyright 1993, Silicon Graphics, Inc.
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

#ident "$Revision: 1.35 $"

#ifndef __DEV_SIRIUS_H__
#define	__DEV_SIRIUS_H__

/*
 * Sirius Device Dependant Controls
 */

/* Device related controls
 */
#define VL_SIR_DEV_BASE		(('S'<<24)|('I'<<16))


/* VL_DEFAULT_SOURCE defines */
#define      SIR_SRC_DIGITAL_VIDEO_1	0
#define      SIR_SRC_DIGITAL_VIDEO_2	1
#define      SIR_SRC_ANALOG_VIDEO	2
#define      SIR_SRC_GRAPHICS		3
#define      SIR_SRC_MEMORY		4


/* VL_PACKING formats for Sirius Texture node */
/* These formats are for Reality Engine Graphics */
#define      SIR_TEX_PACK_RGB_5		0x1000
#define      SIR_TEX_PACK_RGBA_4	0x1001
#define      SIR_TEX_PACK_RGBA_8	0x1002

/* These formats are for Infinite Reality Graphics */
#define      SIR_PACK_RGB_8		0x1000
#define      SIR_PACK_RGBA_6		0x1001
#define      SIR_PACK_RGBA_12		0x1002
#define      SIR_PACK_YYYY_12		0x1003

/* Graphics related controls
 */
#define   VL_SIR_GFX_SIZE	  (VL_SIR_DEV_BASE + 0)

/* Analog Video related controls
 */
#define   VL_SIR_RED_GAIN	  (VL_SIR_DEV_BASE + 1)
#define   VL_SIR_GREEN_GAIN	  (VL_SIR_DEV_BASE + 2)
#define   VL_SIR_BLUE_GAIN	  (VL_SIR_DEV_BASE + 3)
#define   VL_SIR_ALPHA_GAIN	  (VL_SIR_DEV_BASE + 4)
#define   VL_SIR_RED_OFFSET	  (VL_SIR_DEV_BASE + 5)
#define   VL_SIR_GREEN_OFFSET	  (VL_SIR_DEV_BASE + 6)
#define   VL_SIR_BLUE_OFFSET	  (VL_SIR_DEV_BASE + 7)
#define   VL_SIR_ALPHA_OFFSET	  (VL_SIR_DEV_BASE + 8)
#define   VL_SIR_AUTO_GAIN_CONTROL (VL_SIR_DEV_BASE + 9)

/* Digital Video related controls
 */
#define   VL_SIR_FILTER		  (VL_SIR_DEV_BASE + 10)
#define   VL_SIR_LINK_DELAY_A	  (VL_SIR_DEV_BASE + 11)
#define   VL_SIR_LINK_DELAY_B	  (VL_SIR_DEV_BASE + 12)


/* Sync related controls
 */
#define   VL_SIR_SYNC_LEVEL	  (VL_SIR_DEV_BASE + 13)
#define      SIR_SYNC_LEVEL_VIDEO   1   /* 1 Volt peak to peak */
#define      SIR_SYNC_LEVEL_TTL	    4   /* 4 Volts peak to peak */
#define   VL_SIR_GENLOCK_LEVEL    (VL_SIR_DEV_BASE + 14)
#define      SIR_SYNC_STANDALONE    1
#define      SIR_SYNC_HOUSE	    2	/* Genlock connector */
#define      SIR_SYNC_DIGITAL_1	    3
#define      SIR_SYNC_DIGITAL_2	    4
#define      SIR_SYNC_YC	    5
#define      SIR_SYNC_COMPOSITE	    6
#define      SIR_SYNC_COMPONENT	    7  /* Component Sync connector */
#define      SIR_SYNC_GREEN	    8
#define   VL_SIR_SYNC_BURSTLOCK	  (VL_SIR_DEV_BASE + 15)


/* Phase related controls
 */
#define   VL_SIR_H_PHASE_ALPHA	  (VL_SIR_DEV_BASE + 16)
#define   VL_SIR_SCH_PHASE	  (VL_SIR_DEV_BASE + 17)

/*
 * Transfers to or from the Sirius board can be triggered from one of three
 * possible sources: the on-board VLAN transmitter's frame coincidence pulse,
 * GPI input 1, or GPI input 2.
 */
#define   VL_SIR_TRIGGER	  (VL_SIR_DEV_BASE + 18)
#define      SIR_TRIGGER_NONE	    0
#define      SIR_TRIGGER_GPI_1	    1
#define      SIR_TRIGGER_GPI_2	    2
#define      SIR_TRIGGER_VLAN	    3

/*
 * VLAN related controls
 */
#define   VL_SIR_VLAN_NODE	  (VL_SIR_DEV_BASE + 19)
#define   VL_SIR_VLAN_INIT	  (VL_SIR_DEV_BASE + 20)
#define   VL_SIR_VLAN_STATUS	  (VL_SIR_DEV_BASE + 21)
#define   VL_SIR_VLAN_CMD	  (VL_SIR_DEV_BASE + 22)

/*
 * GPI related controls
 *
 * The transfer start notify trigger will wiggle the GPI output line at the
 * start of a DMA transfer (driving it low for 20msec).  If a GPI trigger
 * event is requested, the transfer will pause and wait for a GPI event to
 * come from the external device.  When/If this event is recevied, the
 * read/write dma transfer proceeds.  When the last dma request has been
 * serviced, we check to see if an end transfer notify trigger was requested;
 * if so, we pull the requested GPI line low for 20msec.
 */
#define   VL_SIR_GPI_XFER_START_NOTIFY	  (VL_SIR_DEV_BASE + 23)
#define   VL_SIR_GPI_XFER_STOP_NOTIFY	  (VL_SIR_DEV_BASE + 24)

/*
 * The GPI input can be configured in one of two possible states:
 *
 * 1.  Active Low (also known as the Abekas switch closure mode):
 *
 *     In this mode, the triggering device (e.g. the Abekas) must drive
 *     the GPI_IN + line low with its GPI_OUT + line.  The GPI_IN - line from
 *     the triggering device should be connected to the Sirius BOB's ground
 *     pin (pin 5 on the DB-9).
 *
 * 2.  Active High:
 *
 *     In this mode, the triggering device must drive the GPI_IN + line high
 *     with its GPI_OUT + line.  The GPI_IN - line from the triggering device
 *     should be connected to the Sirius BOB's ground pin (pin 5 on the DB-9).
 *
 *     The pinout for the 9 pin D-subminature connector for the GPI on the
 *     Sirius Break-out Box (BOB) follows:
 *
 *     <1> VL_SIR_GPI_CHAN1_IN +
 *     <6> VL_SIR_GPI_CHAN1_IN -
 *     <2> VL_SIR_GPI_CHAN2_IN +
 *     <7> VL_SIR_GPI_CHAN2_IN -
 *
 *     <3> VL_SIR_GPI_CHAN1_OUT +
 *     <8> VL_SIR_GPI_CHAN1_OUT -
 *     <4> VL_SIR_GPI_CHAN2_OUT +
 *     <9> VL_SIR_GPI_CHAN2_OUT -
 *
 *     <5> Ground
 *
 */
#define   VL_SIR_GPI_CHAN1_IN_MODE	(VL_SIR_DEV_BASE + 25)
#define   VL_SIR_GPI_CHAN2_IN_MODE	(VL_SIR_DEV_BASE + 26)

#define      SIR_GPI_IN_MODE_ACTIVE_LOW			1
#define      SIR_GPI_IN_MODE_ABEKAS_SWITCH_CLOSURE	1
#define      SIR_GPI_IN_MODE_ACTIVE_HIGH		3

/*
 * The GPI output can either be driven high or driven low.  When it is
 * driven high, the photovoltaic relay is reverse biased and turned off,
 * which induces a high resistance between the GPI_OUT[1,2] + and
 * GPI_OUT[1,2] - * terminals on the 9 pin D-sub connector.  When it is
 * driven low, the photovoltaic relay turns on, and there is effectively
 * no resistance between the + and - terminals; this is called 'Abekas
 * switch closure mode' in the Abekas documentation.
 */

#define   VL_SIR_GPI_OUT_CHAN1		(VL_SIR_DEV_BASE + 27)
#define   VL_SIR_GPI_OUT_CHAN2		(VL_SIR_DEV_BASE + 28)

#define      SIR_GPI_OUT_ON		0
#define      SIR_GPI_OUT_OFF		1

/*
 * KEYGEN ( Chroma Key generator) controls
 */
#define	    VL_SIR_KEYGEN_A_VALUE	(VL_SIR_DEV_BASE + 29) /* V or R */
#define	    VL_SIR_KEYGEN_A_RANGE	(VL_SIR_DEV_BASE + 30)
#define	    VL_SIR_KEYGEN_A_SOFTNESS    (VL_SIR_DEV_BASE + 31)

#define	    VL_SIR_KEYGEN_B_VALUE	(VL_SIR_DEV_BASE + 32) /* Y or G */
#define	    VL_SIR_KEYGEN_B_RANGE	(VL_SIR_DEV_BASE + 33)
#define	    VL_SIR_KEYGEN_B_SOFTNESS    (VL_SIR_DEV_BASE + 34)

#define	    VL_SIR_KEYGEN_C_VALUE	(VL_SIR_DEV_BASE + 35) /* U or B */
#define	    VL_SIR_KEYGEN_C_RANGE	(VL_SIR_DEV_BASE + 36)
#define	    VL_SIR_KEYGEN_C_SOFTNESS    (VL_SIR_DEV_BASE + 37)

/*
 *	The VL_SIR_KEYGEN_MATRIX defines conversion from YUV space
 *	to the desired key generation space.
 *	THe default is an identity matrix.
 *	For example the matrix for conversion from YUV space
 *	to RGB space is:
 *
 *	{  1.401687,  1.000000, -0.000927 }
 *      { -0.714169,  1.000000, -0.343695 }
 *      {  0.000990,  1.000000,  1.772160 }
 */
#define	    VL_SIR_KEYGEN_MATRIX        (VL_SIR_DEV_BASE + 38)

/*
 *
 */
#define	    VL_SIR_GFX_FLICKER          (VL_SIR_DEV_BASE + 39)

/*
 * vlists - a way of changing board parameters without video disturbance
 */
#define     VL_SIR_VLIST_ENABLE         (VL_SIR_DEV_BASE + 40)

/*
 * The following two controls are associated with the Sirius video drain.
 *
 * The analog output of the Sirius board has a blanking enable; when set,
 * the video signal will be blanked for the duration of the frame.
 * When clear, normal vertical/horizontal blanking ensues.
 *
 * This control is provided so that users may turn off the analog output's
 * signal when running digital output formats; when the board is run in a
 * digital format, the analog output runs, but with incorrect timing.
 *
 * For orthogonality, a similar control is provided to allow individual
 * control on the digitial video output.  The VL_SIGNAL control may be used
 * to effect blanking on both outputs simultaneously;  a control changed
 * event will be issued to update the status of the individual analog and
 * digital drain enables accordingly.
 */
#define	    VL_SIR_ANALOG_DRAIN_BLANK_ENABLE	(VL_SIR_DEV_BASE + 41)
#define	    VL_SIR_DIGITAL_DRAIN_BLANK_ENABLE	(VL_SIR_DEV_BASE + 42)

/*
 * Sirius provides user-selectable field dominance for the video input or
 * video output nodes.  Users will typically want to edit on F1 boundaries,
 * where F1 is defined as the first field in the video standards two field
 * output sequence.  525 standards send the second (whole) raster line out to
 * begin the first field, and the first (half) raster line out to begin the
 * second field; 625 standards send the first (half) raster line out to begin
 * the first field, and the second (whole) raster line to begin the second
 * field.  Some users may want to edit on F2 boundaries, which falls on the
 * field in between the video standard's frame boundary.  To do so, use this
 * control, then program your deck to select F2 edits.
 *
 * When toggling field dominance, you will have to reverse the frame
 * de-interleaving (on output) or interleaving (on input).  For details,
 * consult the user's guide or release notes.
 */
#define     VL_SIR_FIELD_DOMINANCE		(VL_SIR_DEV_BASE + 43)

#define      SIR_F1_IS_DOMINANT			1
#define      SIR_F2_IS_DOMINANT			2

#define     VL_SIR_525_PEDESTAL_DIS		(VL_SIR_DEV_BASE + 44)

/* following is used in subtexload call for gl side (video) texturing */
#define SIR_VEN_16BIT_TEXEL		3
#define SIR_VEN_32BIT_TEXEL		4

/* following is used in gl side code using gfx drain (see examples) */
#define SIR_VEN_SKIP                    6970
#define SIR_VEN_INTERFACE               1005
#define SIR_VEN_VIDEOCOPY               9000

#define SIR_VEN_PIXMODE_SKIP_LINES(skip) {                      \
    long sirven_buf[2];                                         \
    sirven_buf[0] = SIR_VEN_SKIP;                               \
    sirven_buf[1] = (skip);                                     \
    glcompat(SIR_VEN_INTERFACE, (long) sirven_buf);             \
}

#define SIR_VEN_RECTCOPY_VIDEO_FIELD(field_width,field_height,newx,newy) { \
    long sirven_buf[6];                                         \
    sirven_buf[0] = (field_width);                              \
    sirven_buf[1] = (field_height);                             \
    sirven_buf[2] = (newx);                                     \
    sirven_buf[3] = (newy);                                     \
    sirven_buf[4] = 0;                                          \
    sirven_buf[5] = 0;                                          \
    glcompat(SIR_VEN_VIDEOCOPY, (long) sirven_buf);             \
}

#endif	/* __DEV_SIRIUS_H__ */

