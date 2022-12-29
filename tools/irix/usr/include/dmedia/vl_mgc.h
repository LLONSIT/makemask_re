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

#ifndef __DEV_MGC_H__
#define __DEV_MGC_H__

/*
 *  dev_mgc.h
 *
 *  MGC device dependent control definitions.
 *
 * $Revision: 1.6 $
 */

/*
 * MGC Input Node definitions
 */
#define VL_MGC_VID_ANALOG     4 	/*Analog Video node id*/
/*
 * MGC Input VL_MUXSWITCH definitions
 */

/* Analog node */
#define	VL_MGC_COMPOSITE		0	/* composite (RCA-type conn.) */
#define	VL_MGC_SVIDEO			1	/* S Video (Mini-DIN conn.) */

/*
 * MGC Input VL_SYNC_SOURCE definition
 */
#define	VL_MGC_GENLOCK			2	/* Genlock sync source*/

/*SYNC definitions*/

#define VL_MGC_SYNC_SLAVE	0x10000000	/*same as GAL 1.0 VL_EV1_SYNC_SLAVE*/


/*
 * MGC device-specific controls start at VL_MGC_CTL_BASE
 *
 */
/*must match the definition in vl_mgv.h*/
#define VL_MGC_MGV_CTL_BASE (('M'<<24)|('G'<<16))
#define VL_MGC_CTL_BASE		(VL_MGC_MGV_CTL_BASE+512)

/*
 * MGC impact video like memory controls
 * must be the same as in impact video dev_mgv.h
 */


/*
 *	VGI1 Memory Node DMA controls 
 */
#define VL_MGC_DOMINANCE_FIELD          (VL_MGC_MGV_CTL_BASE + 36)
#define VL_MGC_DMA_VIN_ROUND		(VL_MGC_MGV_CTL_BASE + 71)
#define VL_MGC_DMA_ROUND_TYPE		(VL_MGC_MGV_CTL_BASE + 73)
#define VL_MGC_DMA_RAND_ROUND_MODE	(VL_MGC_MGV_CTL_BASE + 74)
#define VL_MGC_BUFFER_QUANTUM		(VL_MGC_MGV_CTL_BASE + 77)
#define VL_MGC_DMA_VOUT_STARVATION	(VL_MGC_MGV_CTL_BASE + 78)

/*
 *  Field dominance can be set independently for each GIO DMA channel.
 *
 *  NOTE: This is a memory node control, not a device node control.
 *
 * For use with: VL_MGC_DOMINANCE_FIELD
 */
#define VL_MGC_DOMINANCE_F1     0       /* F1 dominance - default*/
#define VL_MGC_DOMINANCE_F2     1       /* F2 dominance */

/*
 *  DMA Starvataion Policy
 *
 *  When transferring from memory to video using a GIO DMA channel, if
 *  data is not provided quickly enough by the application (vlPutValid()),
 *  or when data is repeated due to rate control
 *  then one of the following two actions can be taken until more data
 *  becomes available:
 *
 *
 *    VL_MGC_DMA_VO_STARV_RPT:
 *
 *     	 Repeat the last unit transferred (field or frame).  This
 *	 will occur until the next transfer unit becomes available.
 *	 In order to repeat, the unit is DMAed continuously.
 *
 *    VL_MGC_DMA_VO_STARV_FLD:
 *
 *     	 For frames, repeat only the last field until the next transfer
 *	 unit becomes available.  Once starvation is detected, the
 *	 non-dominant field is output as both the F1 and F2 fields.  This
 *	 results in halving the vertical resolution, but eliminates
 *	 inter-field motion blur.  In order to repeat, the field is DMAed
 *	 continuously.
 *
 *	 If the capture type is not either of interleaved or non-interleaved
 *	 frames (it is a field in other words), then this control value is
 *	 identical in behavior to VL_MGC_DMA_VO_STARV_RPT.
 *
 *	 NOTE: The buffer entry of the repeated unit does not again
 *	       become available to the application (vlGetnNextFree())
 *	       until another transfer unit is ready for DMA.  Therefore,
 *	       in order to use this mode, a buffer of at least two
 *	       entries must be created.  A minimum if four is required
 *	       for non-interleaved frames.
 *
 *    NOTE: This control is only available on memory/codec source nodes.
 *
 * For use with: VL_MGC_DMA_VOUT_STARVATION
 */
#define VL_MGC_DMA_VO_STARV_RPT	1	/* Repeat last field/frame - default */
#define VL_MGC_DMA_VO_STARV_FLD	2	/* Repeat last field of frame only */


/* Note that following rounding modes only affect capture/compression when
 * the source is 10 bit digital video from impact video
 */

/*
 *  GIO DMA memory / codec drain 10-bit -> 8-bit rounding enable.
 *
 * For use with: VL_MGC_DMA_VIN_ROUND
 */
#define VL_MGC_DMA_RND_OFF	0	/* Disable causes truncation - default */
#define VL_MGC_DMA_RND_ON	1	/* Enable  causes rounding */

/*
 *  GIO DMA memory / codec drain rounding type.
 *
 * For use with: VL_MGC_DMA_ROUND_TYPE
 */
#define VL_MGC_DMA_RND_SMPLE	0	/* Simple rounding - default */
#define VL_MGC_DMA_RND_RAND	1	/* Radomized rounding */


/*
 *  GIO DMA memory / codec drain randomized rounding mode.
 *
 * For use with: VL_MGC_DMA_RAND_ROUND_MODE
 */
#define VL_MGC_DMA_RND_RAND_RPT	 0	/* Repeat random sequence - default */
#define VL_MGC_DMA_RND_RAND_FREE 1	/* Random sequence free wheels */




#define VL_MGC_MISC_BASE		(VL_MGC_CTL_BASE + 0)


/*
 * MGC Analog input device-specific controls.
 */


#define VL_MGC_VTR_LOCK			(VL_MGC_MISC_BASE +  0)
#define VL_MGC_CORING			(VL_MGC_MISC_BASE +  1)
#define VL_MGC_APERTURE			(VL_MGC_MISC_BASE +  2)
#define VL_MGC_BANDPASS			(VL_MGC_MISC_BASE +  3)
#define VL_MGC_PREFILTER		(VL_MGC_MISC_BASE +  4)
#define VL_MGC_CHROMA_AGC		(VL_MGC_MISC_BASE +  6)
#define VL_MGC_LUMA_DELAY		(VL_MGC_MISC_BASE +  7)
#define VL_MGC_CHROMA_DELAY		(VL_MGC_MISC_BASE +  8)
#define VL_MGC_VNOISE_REDUCER		(VL_MGC_MISC_BASE +  9)
#define VL_MGC_CHROMA_GAIN		(VL_MGC_MISC_BASE + 10)
#define VL_MGC_COLOR_KILL_THRES		(VL_MGC_MISC_BASE + 11)
#define	VL_MGC_FORCE_COLOR		(VL_MGC_MISC_BASE + 12)
#define VL_MGC_PAL_SENS			(VL_MGC_MISC_BASE + 13)
#define VL_MGC_AUFD			(VL_MGC_MISC_BASE + 14)


/*
 * MGC Analog output device-specific controls.
 */

#define VL_MGC_SCH_PHASE		(VL_MGC_MISC_BASE + 27)
#define VL_MGC_SUB_FREQ		 	(VL_MGC_MISC_BASE + 28)
#define VL_MGC_COLOR_OUT_KILL		(VL_MGC_MISC_BASE + 29)
#define VL_MGC_CHROMA_BAND		(VL_MGC_MISC_BASE + 30)
#define VL_MGC_INCREMENT_DELAY		(VL_MGC_MISC_BASE + 31)
#define VL_MGC_DELAY_SYNC		(VL_MGC_MISC_BASE + 32)
#define VL_MGC_MOD_7199			(VL_MGC_MISC_BASE + 33)
#define VL_MGC_DD_7199			(VL_MGC_MISC_BASE + 34)
#define VL_MGC_STD_7199			(VL_MGC_MISC_BASE + 35)
#define VL_MGC_C_GAIN			(VL_MGC_MISC_BASE + 36)
#define VL_MGC_YC_GAIN			(VL_MGC_MISC_BASE + 37)
#define VL_MGC_ANTI_DITHER		(VL_MGC_MISC_BASE + 38)

/*for output genlock also works on memory src nodes*/
#define VL_MGC_H_OFFSET			(VL_MGC_MISC_BASE + 39)
#define VL_MGC_V_OFFSET			(VL_MGC_MISC_BASE + 40)

/*
 MGC Memory node controls
*/


#define VL_MGC_HASPECT			(VL_MGC_MISC_BASE + 41)
#define VL_MGC_VASPECT			(VL_MGC_MISC_BASE + 42)

#define VL_MGC_PAD_TOP			(VL_MGC_MISC_BASE + 43)
#define VL_MGC_PAD_BOTTOM		(VL_MGC_MISC_BASE + 44)
#define VL_MGC_PAD_LEFT			(VL_MGC_MISC_BASE + 45)
#define VL_MGC_PAD_RIGHT		(VL_MGC_MISC_BASE + 46)
#define VL_MGC_PAD_ENABLE		(VL_MGC_MISC_BASE + 47)
#define VL_MGC_PAD_Y			(VL_MGC_MISC_BASE + 48)
#define VL_MGC_PAD_U			(VL_MGC_MISC_BASE + 49)
#define VL_MGC_PAD_V			(VL_MGC_MISC_BASE + 50)

#define VL_MGC_VIDEO_TOP_CLIP		(VL_MGC_MISC_BASE + 51)

#define VL_MGC_NO_MSC_UST		(VL_MGC_MISC_BASE + 52)

#define VL_MGC_UNZOOMED_OFFSET		(VL_MGC_MISC_BASE + 53)
#define VL_MGC_UNZOOMED_UNPAD_SIZE	(VL_MGC_MISC_BASE + 54)
#define VL_MGC_UNZOOMED_SIZE		(VL_MGC_MISC_BASE + 55)
#define VL_MGC_F1_EXTRA_OFFSET		(VL_MGC_MISC_BASE + 56)
#define VL_MGC_F2_EXTRA_OFFSET		(VL_MGC_MISC_BASE + 57)
#define VL_MGC_NO_INTER		(VL_MGC_MISC_BASE + 60) /*gal 1.0 mode*/

/*
MGC Device node controls
*/

#define VL_MGC_DEFAULT_ANALOG_PLAY_SYNC_SOURCE	(VL_MGC_MISC_BASE + 58)
#define VL_MGC_DEFAULT_DIGITAL_PLAY_SYNC_SOURCE	(VL_MGC_MISC_BASE + 59)

#define VL_MGC_SYNC_SOURCE_DEFAULT 0
#define VL_MGC_SYNC_SOURCE_ANALOG_IN 1
#define VL_MGC_SYNC_SOURCE_ANALOG_GENLOCK 2
#define VL_MGC_SYNC_SOURCE_DIGITAL_GENLOCK 3


#endif /* __DEV_MGC_H__ */
