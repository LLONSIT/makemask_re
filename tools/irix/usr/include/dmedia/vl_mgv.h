/*
 *  dev_mgv.h -- Galileo 1.5 video definitions
 *
 * $Revision: 1.47 $
 */

#if !defined(_MGV_DEV_INCLUDE)
#define _MGV_DEV_INCLUDE


/*==========================================================================*
 * The following constants used by IMPACT Video and may be of interest to   *
 * developers.                                                              *
 *==========================================================================*/
#define MGV_NDPHIVID 	35	/* Transfer thread's non-degrading priority */


/*===========================================================================
 *  Impact Video node number definitions.  Due to the complexity of this    *
 *  device, the node numbers are overloaded.  These constants provide a     *
 *  concise way to signify a particular node.                               *
 ===========================================================================*/

/*
 * Video sources and drains 
 */
#define VL_MGV_NODE_NUMBER_VIDEO_1	0 /* Video src/drain 1 (single link) */
#define VL_MGV_NODE_NUMBER_VIDEO_2	1 /* Video src/drain 2 (single link) */
#define VL_MGV_NODE_NUMBER_VIDEO_DL	2 /* Dual linked video src/drain */

/*
 * Memory sources and drains
 */
#define VL_MGV_NODE_NUMBER_MEM_VGI_1	0 /* Real-time DMA single link 1 */
#define VL_MGV_NODE_NUMBER_MEM_VGI_2	1 /* Real-time DMA single link 2 */
#define VL_MGV_NODE_NUMBER_MEM_VGI_DL	2 /* Real-time DMA dual link */
#define VL_MGV_NODE_NUMBER_MEM_CC	3 /* CC1 8-bit mem src  (VL_SRC only) */

/*
 * Screen sources and drains
 */
#define VL_MGV_NODE_NUMBER_SCREEN_A	0 /* Screen src/drain window A */
#define VL_MGV_NODE_NUMBER_SCREEN_B	1 /* Screen src/drain window B */
#define VL_MGV_NODE_NUMBER_SCREEN_C	2 /* Screen drain window C */

/*
 * Texture drain
 */
#define VL_MGV_NODE_NUMBER_TEXTURE	0 /* Gfx texture port (single link) */
#define	VL_MGV_NODE_NUMBER_TEXTURE_DL	1 /* Gfx texture port (dual link) */

/*
 * Internal nodes
 */
#define VL_MGV_NODE_NUMBER_FB		0 /* CC1 Internal frame buffer */
#define VL_MGV_NODE_NUMBER_BLENDER	0 /* CC1 Blender */
#define VL_MGV_NODE_NUMBER_CSC		0 /* Colorspace converter */



/*===========================================================================*
 * IMPACT Video specific controls. The values appropriate to each control    *
 * are listed in the following section.                                      *
 *===========================================================================*/

#define VL_MGV_CTL_BASE		(('M'<<24)|('G'<<16))

/*
 *	Blender Controls
 */
#define VL_MGV_WIPE_TYPE	(VL_MGV_CTL_BASE +  0)
#define VL_MGV_WIPE_DIRECTION   (VL_MGV_CTL_BASE +  1)	/* VL_MGV_WIPE_ANGLE */
#define VL_MGV_WIPE_SHARPNESS   (VL_MGV_CTL_BASE +  2)	/* VL_MGV_WIPE_FUZZ */
#define VL_MGV_WIPE_ANGLE	(VL_MGV_CTL_BASE +  3)
#define VL_MGV_WIPE_POSN	(VL_MGV_CTL_BASE +  4)
#define VL_MGV_WIPE_POSN_PERP	(VL_MGV_CTL_BASE +  5)
#define VL_MGV_WIPE_CENT	(VL_MGV_CTL_BASE +  6)
#define VL_MGV_WIPE_CENT_PERP	(VL_MGV_CTL_BASE +  7)
#define VL_MGV_WIPE_REPT	(VL_MGV_CTL_BASE +  8)
#define VL_MGV_WIPE_REPT_PERP	(VL_MGV_CTL_BASE +  9)
#define VL_MGV_WIPE_SPEED	(VL_MGV_CTL_BASE + 10)
#define VL_MGV_WIPE_FUZZ	(VL_MGV_CTL_BASE + 11)


/*
 * Device Controls 
 */
#define VL_MGV_AUTOPHASE			(VL_MGV_CTL_BASE + 12)
#define VL_MGV_INPUT_8BIT			(VL_MGV_CTL_BASE + 13)
#define VL_MGV_INPUT_STD			(VL_MGV_CTL_BASE + 14)
#define VL_MGV_INPUT_PRESENT			(VL_MGV_CTL_BASE + 15)
#define VL_MGV_INPUT_ALPHA_LUT_SELECT 		(VL_MGV_CTL_BASE + 16)
#define VL_MGV_OUTPUT_ALPHA_LUT_SELECT		(VL_MGV_CTL_BASE + 17)
#define VL_MGV_TRIGGER_WAIT			(VL_MGV_CTL_BASE + 18)
#define VL_MGV_CC1_BLANK_WIDTH_CH1		(VL_MGV_CTL_BASE + 19)
#define VL_MGV_CC1_BLANK_WIDTH_CH2		(VL_MGV_CTL_BASE + 33)
#define VL_MGV_CC1_RELATIVE_OUTPUT_TIMING	(VL_MGV_CTL_BASE + 79)
#define VL_MGV_CC1_INPUT_ROUNDING_CH1 		(VL_MGV_CTL_BASE + 124)
#define VL_MGV_CC1_INPUT_ROUNDING_CH2		(VL_MGV_CTL_BASE + 125)
#define VL_MGV_GFX_LOCK_REFRESH			(VL_MGV_CTL_BASE + 131)
#define VL_MGV_DMA_READ_BURST_LEN		(VL_MGV_CTL_BASE + 132)
#define VL_MGV_DMA_WRITE_BURST_LEN		(VL_MGV_CTL_BASE + 133)

/*
 * Digital Video Output Controls
 */
#define VL_MGV_OUTPUT_FSYNC		(VL_MGV_CTL_BASE + 20)
#define VL_MGV_OUTPUT_BLANK		(VL_MGV_CTL_BASE + 21)
#define VL_MGV_OUTPUT_HPHASE		(VL_MGV_CTL_BASE + 22)
#define VL_MGV_OUTPUT_CHROMA		(VL_MGV_CTL_BASE + 23)

#define VL_MGV_OUTPUT_DL_SELECT_FREEZE	(VL_MGV_CTL_BASE + 24)
#define VL_MGV_OUTPUT_DL_SELECT_FSYNC	(VL_MGV_CTL_BASE + 25)
#define VL_MGV_OUTPUT_DL_SELECT_BLANK	(VL_MGV_CTL_BASE + 26)
#define VL_MGV_OUTPUT_DL_SELECT_CHROMA	(VL_MGV_CTL_BASE + 27)
#define VL_MGV_OUTPUT_ALPHA_HPHASE	(VL_MGV_CTL_BASE + 28)
#define VL_MGV_SLAVE_ALPHA_HPHASE	(VL_MGV_CTL_BASE + 29)

#define VL_MGV_TRIGGER_POLARITY		(VL_MGV_CTL_BASE + 34)
#define VL_MGV_TRIGGER_LINE		(VL_MGV_CTL_BASE + 35)
#define VL_MGV_DOMINANCE_FIELD		(VL_MGV_CTL_BASE + 36)
#define VL_MGV_ALPHA_NOT_PIXEL		(VL_MGV_CTL_BASE + 37)

/*
 *	Keyer controls.
 */
#define VL_MGV_KEYER_SOURCE		(VL_MGV_CTL_BASE + 38)	/* defunct */
#define VL_MGV_KEYER_MODE		(VL_MGV_CTL_BASE + 39)
#define VL_MGV_KEYER_VALUE_LUMA		(VL_MGV_CTL_BASE + 40)
#define VL_MGV_KEYER_RANGE_LUMA		(VL_MGV_CTL_BASE + 41)
#define VL_MGV_KEYER_FG_OPACITY		(VL_MGV_CTL_BASE + 42)
#define VL_MGV_KEYER_VALUE_CHROMA_U	(VL_MGV_CTL_BASE + 43)
#define VL_MGV_KEYER_RANGE_CHROMA_U	(VL_MGV_CTL_BASE + 44)
#define VL_MGV_KEYER_VALUE_CHROMA_V	(VL_MGV_CTL_BASE + 45)
#define VL_MGV_KEYER_RANGE_CHROMA_V	(VL_MGV_CTL_BASE + 46)
#define VL_MGV_KEYER_DETAIL		(VL_MGV_CTL_BASE + 47)
#define VL_MGV_WIPE			(VL_MGV_CTL_BASE + 48)
#define VL_MGV_WIPE_SYMMETRY		(VL_MGV_CTL_BASE + 49)
#define VL_MGV_WIPE_INVERT		(VL_MGV_CTL_BASE + 50)
#define VL_MGV_WIPE_EXT_TRIG		(VL_MGV_CTL_BASE + 51)

/*
 * Blender Flat Background Controls
 *
 * Note: VL_MGV_BLEND_B_FLAT is obsolete; VL_MGV_BLEND_B_SELECT
 * should be used instead.
 */
#define VL_MGV_BLEND_B_FLAT		(VL_MGV_CTL_BASE + 52)
#define VL_MGV_BLEND_B_Y		(VL_MGV_CTL_BASE + 53)
#define VL_MGV_BLEND_B_U		(VL_MGV_CTL_BASE + 54)
#define VL_MGV_BLEND_B_V		(VL_MGV_CTL_BASE + 55)

#define VL_MGV_BLEND_H_FILT		(VL_MGV_CTL_BASE + 56)
#define VL_MGV_BLEND_SHADOW_ON		(VL_MGV_CTL_BASE + 57)
#define VL_MGV_BLEND_SHADOW_GAIN	(VL_MGV_CTL_BASE + 58)
#define VL_MGV_BLEND_SHADOW_OFFSET	(VL_MGV_CTL_BASE + 59)
#define VL_MGV_OUTPUT_ALPHA_CHROMA	(VL_MGV_CTL_BASE + 126)

/*
 * Screen Controls
 */
#define VL_MGV_DEINTERLACE		(VL_MGV_CTL_BASE + 60)
#define VL_MGV_SHOW_GFX			(VL_MGV_CTL_BASE + 128)

/*
 *	Blender MUX controls
 */
#define VL_MGV_BLENDER_FG_PIXEL		(VL_MGV_CTL_BASE + 61)
#define VL_MGV_BLENDER_FG_ALPHA		(VL_MGV_CTL_BASE + 62)
#define VL_MGV_BLENDER_BG_PIXEL		(VL_MGV_CTL_BASE + 63)
#define VL_MGV_BLENDER_BG_ALPHA		(VL_MGV_CTL_BASE + 64)

#define VL_MGV_BLEND_A_ALPHA_SELECT	(VL_MGV_CTL_BASE + 30)
#define VL_MGV_BLEND_B_SELECT		(VL_MGV_CTL_BASE + 31)
#define VL_MGV_BLEND_B_ALPHA_SELECT	(VL_MGV_CTL_BASE + 32)

#define VL_MGV_BLENDER_XYMIX		(VL_MGV_CTL_BASE + 65)
#define VL_MGV_BLENDER_THRESH		(VL_MGV_CTL_BASE + 66)
#define VL_MGV_BLENDER_VRAND		(VL_MGV_CTL_BASE + 67)
#define VL_MGV_BLENDER_HRAND		(VL_MGV_CTL_BASE + 68)
#define VL_MGV_BLENDER_SLICE_SEL	(VL_MGV_CTL_BASE + 69)
#define VL_MGV_BLENDER_SEL_MODE		(VL_MGV_CTL_BASE + 70)


/*
 *	VGI1 Memory Node DMA controls 
 */
#define VL_MGV_DMA_VIN_ROUND		(VL_MGV_CTL_BASE + 71)
#define VL_MGV_DMA_VOUT_EXPAND		(VL_MGV_CTL_BASE + 72)
#define VL_MGV_DMA_ROUND_TYPE		(VL_MGV_CTL_BASE + 73)
#define VL_MGV_DMA_RAND_ROUND_MODE	(VL_MGV_CTL_BASE + 74)
#define VL_MGV_DMA_VOUT_BLANK		(VL_MGV_CTL_BASE + 75)
#define VL_MGV_DMA_ERROR_RESTART	(VL_MGV_CTL_BASE + 76)

#define VL_MGV_BUFFER_QUANTUM		(VL_MGV_CTL_BASE + 77)
#define VL_MGV_DMA_VOUT_STARVATION	(VL_MGV_CTL_BASE + 78)

/*
 *   Color Space Converter Controls
 */
#define VL_MGV_CSC_IN_RANGE		(VL_MGV_CTL_BASE + 80)
#define VL_MGV_CSC_OUT_RANGE		(VL_MGV_CTL_BASE + 81)
#define VL_MGV_CSC_IN_PACKING		(VL_MGV_CTL_BASE + 82)
#define VL_MGV_CSC_OUT_PACKING		(VL_MGV_CTL_BASE + 83)
#define VL_MGV_CSC_CONST_HUE		(VL_MGV_CTL_BASE + 84)
#define VL_MGV_CSC_ALPHA_CORRECTION	(VL_MGV_CTL_BASE + 85)
#define VL_MGV_CSC_COEF			(VL_MGV_CTL_BASE + 86)
#define VL_MGV_CSC_LUT_IN_YG	        (VL_MGV_CTL_BASE + 87)
#define VL_MGV_CSC_LUT_IN_UB		(VL_MGV_CTL_BASE + 88)
#define VL_MGV_CSC_LUT_IN_VR		(VL_MGV_CTL_BASE + 89)
#define VL_MGV_CSC_LUT_OUT_YG		(VL_MGV_CTL_BASE + 90)
#define VL_MGV_CSC_LUT_OUT_UB		(VL_MGV_CTL_BASE + 91)
#define VL_MGV_CSC_LUT_OUT_VR		(VL_MGV_CTL_BASE + 92)
#define VL_MGV_CSC_LUT_ALPHA		(VL_MGV_CTL_BASE + 93)
#define VL_MGV_CSC_LUT_IN_PAGE          (VL_MGV_CTL_BASE + 94)
#define VL_MGV_CSC_LUT_ALPHA_PAGE	(VL_MGV_CTL_BASE + 95)
#define VL_MGV_CSC_OUTPUT_FILTER_DISABLE (VL_MGV_CTL_BASE + 96)

/*
 *   Texture Map Interface Controls
 */
#define	VL_MGV_TEXTURE_MIPMAP_MODE	(VL_MGV_CTL_BASE + 119)
#define	VL_MGV_TEXTURE_ROUND_MODE	(VL_MGV_CTL_BASE + 120)
#define	VL_MGV_TEXTURE_INPUT_LINK	(VL_MGV_CTL_BASE + 121)
#define	VL_MGV_TEXTURE_AUTOSWAP		(VL_MGV_CTL_BASE + 122)

/*
 *   Aspect Controls
 */
#define	VL_MGV_HASPECT			(VL_MGV_CTL_BASE + 129)
#define	VL_MGV_VASPECT			(VL_MGV_CTL_BASE + 130)


/*===========================================================================*
 * Control values. The following section lists the values appropriate to the *
 * controls defined above.                                                   *
 *===========================================================================*/

/*
 * Genlock (sync) source values.
 *
 * For use with: VL_SYNC_SOURCE
 */
#define GEN_PORT	1	/* Reference input */
#define GEN_DIN2	2	/* Digital in 2 */
#define GEN_DIN1	3	/* Digital in 1 */

/*
 * Use these values for Dual Link select controls 
 * 
 * For use with: VL_MGV_OUTPUT_DL_SELECT_*
 */
#define VL_MGV_DL_SELECT_PIXEL	(1 << 0)
#define VL_MGV_DL_SELECT_ALPHA	(1 << 1)
#define VL_MGV_DL_SELECT_ALL	(VL_MGV_DL_SELECT_PIXEL | VL_MGV_DL_SELECT_ALPHA)   /* Default: Pixel+Alpha at the same time. */

/*
 *	Keyer modes
 *
 * For use with: VL_MGV_KEYER_MODE
 */
#define VL_MGV_KEYERMODE_NONE		0
#define VL_MGV_KEYERMODE_LUMA		1
#define	VL_MGV_KEYERMODE_CHROMA		2
#define VL_MGV_KEYERMODE_SPATIAL	3

/*
 *	Keyer Wipe Types
 *
 * For use with: VL_MGV_WIPE_TYPE
 */
#define VL_MGV_WIPETYPE_NONE	0
#define VL_MGV_WIPETYPE_FADE	1
#define VL_MGV_WIPETYPE_TILE	2
#define VL_MGV_WIPETYPE_SINGLE	3
#define VL_MGV_WIPETYPE_DOUBLE	4
#define VL_MGV_WIPETYPE_CORNER	5

/*
 *	Keyer Wipe Directions 
 *
 * For use with: VL_MGV_WIPE_DIRECTION
 */
#define	VL_MGV_WIPEANGLE_NONE	0
#define	VL_MGV_WIPEANGLE_E	1
#define	VL_MGV_WIPEANGLE_NE	2
#define	VL_MGV_WIPEANGLE_N	3
#define	VL_MGV_WIPEANGLE_NW	4
#define	VL_MGV_WIPEANGLE_W	5
#define	VL_MGV_WIPEANGLE_SW	6
#define	VL_MGV_WIPEANGLE_S	7
#define	VL_MGV_WIPEANGLE_SE	8

/*
 * Blender input selections
 *
 * For use with VL_MGV_BLEND_A_ALPHA_SELECT, VL_MGV_BLEND_B_SELECT, 
 * VL_MGV_BLEND_B_ALPHA_SELECT
 */
#define VL_MGV_SELECT_BLEND_INPUT 0	/* Input selected by VL_BLEND_A, etc. */
#define VL_MGV_SELECT_FLAT_BG	1	/* Flat background  generator */
#define VL_MGV_SELECT_ALPHA_0	1	/* Use alpha = 0.0 */
#define VL_MGV_SELECT_ALPHA_1	2	/* Use alpha = 1.0 */
#define VL_MGV_SELECT_KEYER	2	/* Use key extractor output as alpha */


/*
 *  Autophase modes
 * 
 * For use with VL_MGV_AUTOPHASE
 */
#define VL_MGV_AUTOPHASE_NORMAL 	0
#define VL_MGV_AUTOPHASE_EXTENDED 	1
#define VL_MGV_AUTOPHASE_VARIABLE 	2
#define VL_MGV_AUTOPHASE_OFF		3

/*
 *  CC1 Input and Output Alpha Lut selections. 
 *
 *  Note: The range conversions shown apply to the input lut; on the output 
 *        lut, the inverse mapping applies.
 *
 * For use with: VL_MGV_INPUT_ALPHA_LUT_SELECT, VL_MGV_OUTPUT_ALPHA_LUT_SELECT 
 */
#define VL_MGV_ALPHA_LUT_PASS 			0	/* 2-253 -> 2-253 */
#define VL_MGV_ALPHA_LUT_CCIR601_RANGE		1	/* 17-234 -> 1-254 */
#define VL_MGV_ALPHA_LUT_SUPERBLACK_RANGE	2	/* 2-234 -> 1-254 */
#define VL_MGV_ALPHA_LUT_REDUCED_RANGE		3	/* 33-221 -> 1-254 */

/*
 * CC1 output vertical blanking (narrow or normal)
 *
 * For use with: VL_MGV_CC1_BLANK_WIDTH_CH1, VL_MGV_CC1_BLANK_WIDTH_CH2
 */
#define CC1_BLANKING_NORMAL	0
#define CC1_BLANKING_NARROW	1

/*
 * CC1 input rounding modes
 *
 * For use with: VL_MGV_CC1_INPUT_ROUNDING_CH1, VL_MGV_CC1_INPUT_ROUNDING_CH2
 */
#define CC1_INPUT_ROUND_DITHER 	0
#define CC1_INPUT_ROUND_STATIC	1
/*
 * CC1 relative output timing in pixels (2x pixel clock):
 *
 * For use with VL_MGV_CC1_RELATIVE_OUTPUT_TIMING
 */
#define CC1_OUTPUT_LATE_BY_2	0
#define CC1_OUTPUT_LATE_BY_1	1
#define CC1_OUTPUT_ALIGNED	2
#define CC1_OUTPUT_EARLY_BY_1	3

/*
 *  GIO DMA memory drain 10-bit -> 8-bit rounding enable.
 *
 * For use with: VL_MGV_DMA_VIN_ROUND
 */
#define VL_MGV_DMA_RND_OFF	0	/* Disable (10->10) - default */
#define VL_MGV_DMA_RND_ON	1	/* Enable (10->8) */

/*
 *  GIO DMA memory drain rounding type.
 *
 * For use with: VL_MGV_DMA_ROUND_TYPE
 */
#define VL_MGV_DMA_RND_SMPLE	0	/* Simple rounding - default */
#define VL_MGV_DMA_RND_RAND	1	/* Radomized rounding */

/*
 *  GIO DMA memory source expansion enable.
 *
 * For use with: VL_MGV_DMA_VOUT_EXPAND
 */
#define VL_MGV_DMA_EXPD_OFF	0	/* Disable (10->10) - default */
#define VL_MGV_DMA_EXPD_ON	1	/* Enable (8->10) (2 LSB=0) */

/*
 *  GIO DMA memory drain randomized rounding mode.
 *
 * For use with: VL_MGV_DMA_RAND_ROUND_MODE
 */
#define VL_MGV_DMA_RND_RAND_RPT	 0	/* Repeat random sequence - default */
#define VL_MGV_DMA_RND_RAND_FREE 1	/* Random sequence free wheels */

/*
 *  GIO DMA memory source blanking mode.
 *
 *  NOTE: The default output blanking is set according to VL_PACKING.
 *        This control allows that setting to be overridden.  To do so,
 *        set this control *after* VL_PACKING.
 *
 * For use with: VL_MGV_DMA_VOUT_BLANK
 */
#define VL_MGV_DMA_VO_BLK_YUVA	0	/* YUVA: Y = A = 16, U = V = 128 */
#define VL_MGV_DMA_VO_BLK_RGBA	1	/* RP175: R = G = B = A = 16 */

/*
 *  Field dominance can be set independently for each GIO DMA channel.
 *
 *  NOTE: This is a memory node control, not a device node control.
 *
 * For use with: VL_MGV_DOMINANCE_FIELD
 */
#define VL_MGV_DOMINANCE_F1	0	/* F1 dominance - default*/
#define VL_MGV_DOMINANCE_F2	1	/* F2 dominance */

/*
 *  DMA Restart Policy
 *
 *  DMA can be automatically restarted after reception of one of the
 *  error interrupt conditions, or a missed vertical interrupt condition.
 *  These are a result of:
 *
 *    1  The GIO bus bandwidth was insufficient to keep up with video,
 *	 resulting in a DMA FIFO under/over flow.
 *
 *    2  The video clock (timing/pixels) was interrupted.
 *
 *    3	 The video timing is not clean, resulting in short/long lines,
 *	 and/or short/long fields.  These errors are with respect to
 *	 the programmed size and offset.
 *
 *  By default, DMA will be terminated and the transfer will fail due
 *  such an error.  If the error restart mode is enabled, then an
 *  error is reported, but the transfer will continue.
 *
 * For use with: VL_MGV_DMA_ERROR_RESTART
 */
#define VL_MGV_DMA_RESTART_OFF	0	/* Transfer fails - default*/
#define VL_MGV_DMA_RESTART_ON	1	/* Report error, continue transfer */

/*
 *  DMA Starvataion Policy
 *
 *  When transferring from memory to video using a GIO DMA channel, if
 *  data is not provided quickly enough by the application (vlPutValid()),
 *  then one of the following three actions can be taken until more data
 *  becomes available:
 *
 *    VL_MGV_DMA_VO_STARV_BLK:
 *
 *     	 Go to black.  Black is output until the next transfer unit
 *	 becomes available.  Outputting black does not involve DMA.
 *
 *    VL_MGV_DMA_VO_STARV_RPT:
 *
 *     	 Repeat the last unit transferred (field or frame).  This
 *	 will occur until the next transfer unit becomes available.
 *	 In order to repeat, the unit is DMAed continuously.
 *
 *    VL_MGV_DMA_VO_STARV_FLD:
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
 *	 identical in behavior to VL_MGV_DMA_VO_STARV_RPT.
 *
 *	 NOTE: The buffer entry of the repeated unit does not again
 *	       become available to the application (vlGetnNextFree())
 *	       until another transfer unit is ready for DMA.  Therefore,
 *	       in order to use this mode, a buffer of at least two
 *	       entries must be created.  A minimum if four is required
 *	       for non-interleaved frames.
 *
 *    NOTE: This control is only available on VGI1 memory source nodes.
 *
 * For use with: VL_MGV_DMA_VOUT_STARVATION
 */
#define VL_MGV_DMA_VO_STARV_BLK	0	/* Go to black */
#define VL_MGV_DMA_VO_STARV_RPT	1	/* Repeat last field/frame - default */
#define VL_MGV_DMA_VO_STARV_FLD	2	/* Repeat last field of frame only */

/* 
 * For use with: VL_MGV_TEXTURE_MIPMAP_MODE
 */
#define	VL_MGV_TEXTURE_MIPMAP_OFF	0	/* mipmap is off - default */
#define	VL_MGV_TEXTURE_MIPMAP_ON 	1	/* mipmap is on */	

/*
 * For use with: VL_MGV_TEXTURE_ROUND_MODE
 */
#define	VL_MGV_TEXTURE_ROUND_8BIT	0	/* 8 bit - default */
#define	VL_MGV_TEXTURE_ROUND_RNG	1	/* random num gen */
#define	VL_MGV_TEXTURE_ROUND_RNGFRM	3	/* random num gen frame reset */

/*
 * For use with: VL_MGV_TEXTURE_INPUT_LINK
 */
#define	VL_MGV_TEXTURE_INPUT_LINK_A	0	/* input link is A - default */
#define	VL_MGV_TEXTURE_INPUT_LINK_B	1	/* input link is B */

/*
 * For use with: VL_MGV_TEXTURE_AUTOSWAP
 */
#define	VL_MGV_TEXTURE_AUTOSWAP_OFF	0	/* autoswap is off - default */
#define	VL_MGV_TEXTURE_AUTOSWAP_ON	1	/* autoswap is on */

/*
 * For use for dataType in VLExtendedValue.
 * MGV_CSC_COEF is coef type of VLExtendedValue. MGV_CSC_LUT_IN_ALPHA is
 * for input and alpha lut types of VLExtendedValue. MGV_CSC_LUT_OUT is
 * for output lut type of VLExtendedValue.
 */
enum VL_MGV_CSC_DataType {MGV_CSC_COEF, MGV_CSC_LUT_INPUT_AND_ALPHA, MGV_CSC_LUT_OUTPUT};

/*
 * For use with: VL_MGV_CSC_LUT_IN_{YG, UB, VR} and VL_MGV_CSC_LUT_ALPHA
 *
 * The following struct VL_MGVInAlphaLutValue is used as dataPointer
 * in VLExtendedValue.
 *
 * To set or get a lut, lut contains lut values. pageNumber is the 
 * page number this lut will be loaded to. This number can be from 
 * 0 (first page) to 3 (last page). 
 */

typedef struct {
    int lut[1024];
    int   pageNumber;		/* page number in a lut */
} VL_MGVInAlphaLutValue;

/*
 * For use with: VL_MGV_CSC_LUT_OUT_{YG, UB, VR}
 *
 * The following struct VL_MGVOutLutValue is used as dataPointer
 * in VLExtendedValue.
 *
 * To set or get a lut, lut contains lut values.
 */ 

typedef struct {
    int lut[4096];
} VL_MGVOutLutValue;

#endif /* _MGV_DEV_INCLUDE */

/* EOF dev_mgv.h */
