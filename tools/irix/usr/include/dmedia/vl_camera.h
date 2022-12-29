/* $Id: vl_camera.h,v 1.8 1996/07/21 22:57:05 travis Exp $ */
/*
 *	vl_camera.h -- Header file for Video Library supported Cameras
 *
 * Copyright 1996 Silicon Graphics, Inc.
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

#ifndef _VL_CAMERA_H_
#define _VL_CAMERA_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 *
 * Not all controls are available and some controls are Read Only.
 * (This is strictly camera dependent).
 *
 * VL Return Codes:
 *
 *	VLBadControl - Camera does not support the control
 *	VLBadValue	- Camera can not set the value specified (might be ReadOnly)
 *	VLOutOfRange - Value is not within bounds but the closest value was set.
 *
 */


#define VL_CAMERA_CTL_BASE		( ('V' << 24) | ('C' << 16) )

/*
 * Camera Identification - string values
 */
#define VL_CAMERA_VENDOR_ID		( VL_CAMERA_CTL_BASE + 1 ) /*R/O*/

/*
 * This string is PREPENDED to all SGI digital cameras
 */
#define VL_CAMERA_VENDOR_ID_SGI		"SGI Digital Video Camera"

/*
 * Camera Revision - numeric values
 */
#define VL_CAMERA_VERSION		( VL_CAMERA_CTL_BASE + 2 ) /*R/O*/

/*
 * These values are valid when VL_CAMERA_VENDOR_ID_SGI appears as
 * the prefix of VL_CAMERA_VENDOR_ID.
 */
#define VL_CAMERA_VERSION_SGI_INDYCAM		101
#define VL_CAMERA_VERSION_SGI_DVC1		201
#define VL_CAMERA_VERSION_SGI_DVC2		202

/*
 * Turn camera on/off
 */
#define	VL_CAMERA_POWER			( VL_CAMERA_CTL_BASE + 3 )
#define	VL_CAMERA_POWER_OFF			0
#define	VL_CAMERA_POWER_ON			1


/*
 * Momentary control - reset camera
 * (Note some delay may be required before use.)
 */
#define VL_CAMERA_RESET			( VL_CAMERA_CTL_BASE + 4 )

/*
 * Momentary control - initialize camera
 * This is different than "RESET" in that it initializes
 * the camera registers to some known default values.
 * (Normally supplied by the camera manufacturer.l)
 */
#define VL_CAMERA_INITIALIZE		( VL_CAMERA_CTL_BASE + 5 )


/*
 * Automatic controls - awb is a single shot control
 */
#define VL_CAMERA_AUTO_WHITE_BALANCE	( VL_CAMERA_CTL_BASE + 10 )

#define VL_CAMERA_AUTO_GAIN_CONTROL	( VL_CAMERA_CTL_BASE + 11 )
#define VL_CAMERA_AUTO_GAIN_CONTROL_OFF		0
#define VL_CAMERA_AUTO_GAIN_CONTROL_ON		1

/*
 * Data Controls
 */
#define VL_CAMERA_FORMAT		( VL_CAMERA_CTL_BASE + 20 )
#define VL_CAMERA_PIXEL_COUNT		( VL_CAMERA_CTL_BASE + 21 )
#define VL_CAMERA_LINE_COUNT		( VL_CAMERA_CTL_BASE + 22 )

/*
 * Note that NTSC rates are even, while PAL rates are odd
 */
#define VL_CAMERA_RATE			( VL_CAMERA_CTL_BASE + 30 )
#define	VL_CAMERA_RATE_30			0
#define	VL_CAMERA_RATE_25			1
#define	VL_CAMERA_RATE_15			2
#define	VL_CAMERA_RATE_12_5			3
#define	VL_CAMERA_RATE_7_5			4
#define	VL_CAMERA_RATE_6_25			5
#define	VL_CAMERA_RATE_3_75			6
#define	VL_CAMERA_RATE_3_125			7


/*
 *	Camera Feature Controls
 */
#define VL_CAMERA_BRIGHTNESS		( VL_CAMERA_CTL_BASE + 40 )
#define VL_CAMERA_EXPOSURE		( VL_CAMERA_CTL_BASE + 41 )
#define VL_CAMERA_SHARPNESS		( VL_CAMERA_CTL_BASE + 42 )
#define VL_CAMERA_HUE			( VL_CAMERA_CTL_BASE + 43 )

#define VL_CAMERA_RED_BALANCE		( VL_CAMERA_CTL_BASE + 50 )
#define VL_CAMERA_BLUE_BALANCE		( VL_CAMERA_CTL_BASE + 51 )
#define VL_CAMERA_GREEN_BALANCE		( VL_CAMERA_CTL_BASE + 52 )

#define VL_CAMERA_SATURATION		( VL_CAMERA_CTL_BASE + 60 )
#define VL_CAMERA_RED_SATURATION	( VL_CAMERA_CTL_BASE + 61 )
#define VL_CAMERA_BLUE_SATURATION	( VL_CAMERA_CTL_BASE + 62 )
#define VL_CAMERA_GREEN_SATURATION	( VL_CAMERA_CTL_BASE + 63 )

#define VL_CAMERA_GAMMA			( VL_CAMERA_CTL_BASE + 70 )
#define VL_CAMERA_GAIN			( VL_CAMERA_CTL_BASE + 71 )
#define VL_CAMERA_FOCUS			( VL_CAMERA_CTL_BASE + 72 )

#define VL_CAMERA_SCAN			( VL_CAMERA_CTL_BASE + 73 )
#define VL_CAMERA_SCAN_INTERLACED		0
#define VL_CAMERA_SCAN_PROGRESSIVE		1

#define VL_CAMERA_SHUTTER		( VL_CAMERA_CTL_BASE + 80 )
#define	VL_CAMERA_SHUTTER_60			0
#define	VL_CAMERA_SHUTTER_100			1
#define	VL_CAMERA_SHUTTER_125			2
#define	VL_CAMERA_SHUTTER_250			3
#define	VL_CAMERA_SHUTTER_500			4
#define	VL_CAMERA_SHUTTER_1000			5
#define	VL_CAMERA_SHUTTER_2000			6
#define	VL_CAMERA_SHUTTER_4000			7
#define	VL_CAMERA_SHUTTER_10000			8

/*
 * Positioning Controls
 */
#define VL_CAMERA_ZOOM			( VL_CAMERA_CTL_BASE + 90 )
#define VL_CAMERA_PAN			( VL_CAMERA_CTL_BASE + 91 )
#define VL_CAMERA_TILT			( VL_CAMERA_CTL_BASE + 92 )

/*
 * Physical Camera Controls
 */
#define VL_CAMERA_ORIENTATION		( VL_CAMERA_CTL_BASE + 110)
#define VL_CAMERA_ORIENTATION_NORMAL		0
#define VL_CAMERA_ORIENTATION_ROTATED_180	1

#define VL_CAMERA_BUTTON		( VL_CAMERA_CTL_BASE + 111 )
#define VL_CAMERA_BUTTON_2		( VL_CAMERA_CTL_BASE + 112 )
#define	VL_CAMERA_BUTTON_RELEASED		0
#define	VL_CAMERA_BUTTON_DEPRESSED		1

#define VL_CAMERA_LED			( VL_CAMERA_CTL_BASE + 113 )
#define VL_CAMERA_LED_GREEN		( VL_CAMERA_CTL_BASE + 114 )
#define VL_CAMERA_LED_RED		( VL_CAMERA_CTL_BASE + 115 )
#define VL_CAMERA_LED_AMBER		( VL_CAMERA_CTL_BASE + 116 )
#define	VL_CAMERA_LED_ACTIVE			1
#define	VL_CAMERA_LED_INACTIVE			0


/*
 * Embedded Microphone Controls
 *
 * Mono typically uses the left channel as input. (bit 0)
 */
#define	VL_CAMERA_MICROPHONE		( VL_CAMERA_CTL_BASE + 200 )
#define	VL_CAMERA_MICROPHONE_DISABLE		0
#define	VL_CAMERA_MICROPHONE_ENABLE_MONO	1
#define	VL_CAMERA_MICROPHONE_ENABLE_STEREO	3
#define	VL_CAMERA_MICROPHONE_ENABLE_4_CHANNEL	15

#define	VL_CAMERA_MICROPHONE_GAIN_LEFT	( VL_CAMERA_CTL_BASE + 201 )
#define	VL_CAMERA_MICROPHONE_GAIN_RIGHT	( VL_CAMERA_CTL_BASE + 202 )

#define	VL_CAMERA_MICROPHONE_TONE_LEFT	( VL_CAMERA_CTL_BASE + 203 )
#define	VL_CAMERA_MICROPHONE_TONE_RIGHT	( VL_CAMERA_CTL_BASE + 204 )

/*
 * Camera TimeCode Controls
 *
 * Note: either or both can be enabled
 */
#define	VL_CAMERA_TIMECODE		( VL_CAMERA_CTL_BASE + 300 )
#define	VL_CAMERA_TIMECODE_DISABLE		0
#define	VL_CAMERA_TIMECODE_ENABLE_VITC		1
#define	VL_CAMERA_TIMECODE_ENABLE_LTC		2

/*
 * Camera Test Controls
 */
#define	VL_CAMERA_GENERATE_PATTERN	( VL_CAMERA_CTL_BASE + 400 )
#define	VL_CAMERA_GENERATE_PATTERN_DISABLE	0
#define	VL_CAMERA_GENERATE_PATTERN_WHITE	1
#define	VL_CAMERA_GENERATE_PATTERN_BLACK	2
#define	VL_CAMERA_GENERATE_PATTERN_COLOR_BARS 4

#ifdef __cplusplus
}
#endif
#endif /* _VL_CAMERA_H_ */

/* === */
