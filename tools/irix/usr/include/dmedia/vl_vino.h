/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1994, Silicon Graphics, Inc.               *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 **************************************************************************/

#ifndef __DEV_VINO_H__
#define __DEV_VINO_H__

/*
 *  dev_vino.h
 *
 *  VINO device dependent control definitions.
 *
 * $Revision$
 */

/*
 * VINO Input Node definitions
 */
#define VL_VINO_SRC_DV_IN		0	/* Digital video in */
#define VL_VINO_SRC_AV_IN		1	/* Analog video in */

/*
 * VINO Input VL_MUXSWITCH definitions
 */

/* Analog node */
#define	VL_VINO_COMPOSITE		0	/* composite (RCA-type conn.) */
#define	VL_VINO_SVIDEO			1	/* S Video (Mini-DIN conn.) */

/* Digital node */
#define	VL_VINO_INDYCAM			0	/* IndyCam digital input */
#define	VL_VINO_CCIR601			1	/* D1 digital input */

/* Color Mode Select */
#define	VL_VINO_COLOR_MODE_AUTO		0
#define	VL_VINO_COLOR_MODE_COLOR	1
#define	VL_VINO_COLOR_MODE_MONO		2

/*
 * VINO device-specific controls start at VL_VINO_CTL_BASE
 *
 */
#define VL_VINO_CTL_BASE		(('V' << 24)|('I' << 16))

/*
 * VINO digital camera (IndyCam) controls
 */
#define VL_VINO_INDYCAM_AGCENA          (VL_VINO_CTL_BASE + 0)
#define VL_VINO_INDYCAM_AWBCTL          (VL_VINO_CTL_BASE + 1)
#define VL_VINO_INDYCAM_SHUTTER         (VL_VINO_CTL_BASE + 2)
#define VL_VINO_INDYCAM_GAIN            (VL_VINO_CTL_BASE + 3)
#define VL_VINO_INDYCAM_RED_BALANCE     (VL_VINO_CTL_BASE + 4)
#define VL_VINO_INDYCAM_BLUE_BALANCE    (VL_VINO_CTL_BASE + 5)
#define VL_VINO_INDYCAM_SATURATION      (VL_VINO_CTL_BASE + 6)

/*
 * VINO Analog input device-specific controls.
 */
#define VL_VINO_MISC_BASE		(VL_VINO_CTL_BASE + 7)
#define VL_VINO_VTR_LOCK		(VL_VINO_MISC_BASE +  0)
#define VL_VINO_CORING			(VL_VINO_MISC_BASE +  1)
#define VL_VINO_APERTURE		(VL_VINO_MISC_BASE +  2)
#define VL_VINO_BANDPASS		(VL_VINO_MISC_BASE +  3)
#define VL_VINO_PREFILTER		(VL_VINO_MISC_BASE +  4)
#define VL_VINO_COLOR_MODE		(VL_VINO_MISC_BASE +  5)
#define VL_VINO_CHROMA_AGC		(VL_VINO_MISC_BASE +  6)
#define VL_VINO_LUMA_DELAY		(VL_VINO_MISC_BASE +  7)
#define VL_VINO_CHROMA_DELAY		(VL_VINO_MISC_BASE +  8)
#define VL_VINO_VNOISE_REDUCER		(VL_VINO_MISC_BASE +  9)
#define VL_VINO_CHROMA_GAIN		(VL_VINO_MISC_BASE + 10)
#define VL_VINO_COLOR_KILL_THRES	(VL_VINO_MISC_BASE + 11)
#define VL_VINO_H_PICTURE_POSITION	(VL_VINO_MISC_BASE + 12)
#define VL_VINO_ZOOM_X			(VL_VINO_MISC_BASE + 13)
#define VL_VINO_HREF_GENERATION		(VL_VINO_MISC_BASE + 14)
#define	VL_VINO_FORCE_COLOR		(VL_VINO_MISC_BASE + 15)
#define	VL_VINO_ALPHA			(VL_VINO_MISC_BASE + 16)
#define VL_VINO_H_SYNC_BEGIN		(VL_VINO_MISC_BASE + 17)
#define VL_VINO_H_SYNC_STOP		(VL_VINO_MISC_BASE + 18)
#define VL_VINO_H_CLAMP_BEGIN		(VL_VINO_MISC_BASE + 19)
#define VL_VINO_H_CLAMP_STOP		(VL_VINO_MISC_BASE + 20)
#define VL_VINO_BYPASS_CHROMA		(VL_VINO_MISC_BASE + 21)
#define VL_VINO_PAL_SENS		(VL_VINO_MISC_BASE + 22)
#define VL_VINO_AUFD			(VL_VINO_MISC_BASE + 23)
#define	VL_VINO_EVEN_OFFSET		(VL_VINO_MISC_BASE + 24)
#define	VL_VINO_ODD_OFFSET		(VL_VINO_MISC_BASE + 25)
#define	VL_VINO_DEFAULT_TIMING		(VL_VINO_MISC_BASE + 26)
#define	VL_VINO_ACTIVE_SOURCE		(VL_VINO_MISC_BASE + 27)
#define VL_VINO_INDYCAM_BRIGHTNESS	(VL_VINO_MISC_BASE + 28) /* readonly */
#define VL_VINO_I2CREG			(VL_VINO_MISC_BASE + 29)

/*
 *      values to load into shutter control
 */
#define VL_VINO_INDYCAM_SHUTTER_60          0       /* 1/60 second */
#define VL_VINO_INDYCAM_SHUTTER_100         1       /* 1/100 second */
#define VL_VINO_INDYCAM_SHUTTER_125         2       /* 1/125 second */
#define VL_VINO_INDYCAM_SHUTTER_250         3       /* 1/250 second */
#define VL_VINO_INDYCAM_SHUTTER_500         4       /* 1/500 second */
#define VL_VINO_INDYCAM_SHUTTER_1000        5       /* 1/1000 second */
#define VL_VINO_INDYCAM_SHUTTER_2000        6       /* 1/2000 second */
#define VL_VINO_INDYCAM_SHUTTER_4000        7       /* 1/4000 second */
#define VL_VINO_INDYCAM_SHUTTER_10000       8       /* 1/10000 second */

typedef union __i2c {	
    int	word;
    struct {
	unsigned char address;
	unsigned char offset;
	unsigned short value;
    } chip;
} vinoI2CControlValue;
#define	VL_VINO_I2CREG_READ	0xf1f2	/* initiates I2C read operation */

#endif /* __DEV_VINO_H__ */
