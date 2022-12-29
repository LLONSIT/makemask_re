/*
 *  dev_evo.h -- EVO video definitions
 *
 * $Revision: 1.34 $
 */

#if !defined(_EVO_DEV_INCLUDE)
#define _EVO_DEV_INCLUDE


/*
 * The following constants used by EVO Video and may be of interest to 
 * developers.
 */

#define EVO_NDPHIVID 	35	/* Transfer thread's non-degrading priority */


/*
 *  Evo Video node number definitions.  Due to the complexity of this 
 *  device, the node numbers are overloaded.  These constants provide a
 *  concise way to signify a particular node.
 */

/*
 * Video sources and drains 
 */

#define VL_EVO_NODE_NUMBER_VIDEO_1	0 /* Video src/drain */
#define VL_EVO_NODE_NUMBER_VIDEO_2	1 /* Video camera src only */
#define VL_EVO_NODE_NUMBER_VIDEO_3	2 /* Video analog src only */

/*
 * Memory sources and drains
 */

#define VL_EVO_NODE_NUMBER_MEM_1	0 /* Real-time DMA single link 1 */
#define VL_EVO_NODE_NUMBER_MEM_2	1 /* Real-time DMA single link 2 */

/*
 * Screen source
 */

#define VL_EVO_NODE_NUMBER_SCREEN	0


/****************************************************
 * additional VL_FORMAT values for EVO
 ****************************************************/
#define	VL_EVO_FORMAT_LOOPBACK		128	/* loopback for analog in */


/*===========================================================================*
 * EVO Video specific controls. The values appropriate to each control       *
 * are listed in the following section.                                      *
 *===========================================================================*/

#define VL_EVO_CTL_BASE		(('M'<<24)|('G'<<16))


/****************************************************
 * Device Controls                                  *
 ****************************************************/
#define VL_EVO_COLOR_FRAME_LOCK         (VL_EVO_CTL_BASE + 11)


/****************************************************
 * Analog Video Output Node Controls                *
 ****************************************************/


#define VL_EVO_VOUT_COLOR_BAR_ENABLE 	(VL_EVO_CTL_BASE + 25)
#define		VL_EVO_CB_PORT		0	/* data from input ports encoded */
#define		VL_EVO_CB_PRGM_COLOR	1	/* programable colors are encoded */

#define VL_EVO_VOUT_COLOR_HPHASE     	(VL_EVO_CTL_BASE + 50)
#define		VL_EVO_COLOR_HPHASE_MIN	-180
#define		VL_EVO_COLOR_HPHASE_MAX	180

#define VL_EVO_VOUT_U_GAIN           	(VL_EVO_CTL_BASE + 51)
#define		VL_EVO_U_GAIN_MIN_NTSC 	-118	
#define		VL_EVO_U_GAIN_MAX_NTSC  393	
#define		VL_EVO_U_GAIN_MIN_PAL 	-112	
#define		VL_EVO_U_GAIN_MAX_PAL   399	

#define VL_EVO_VOUT_V_GAIN           	(VL_EVO_CTL_BASE + 52)
#define		VL_EVO_V_GAIN_MIN_NTSC	-165	
#define		VL_EVO_V_GAIN_MAX_NTSC	346	
#define		VL_EVO_V_GAIN_MIN_PAL	-175	
#define		VL_EVO_V_GAIN_MAX_PAL	336	

#define VL_EVO_VOUT_BLACK_LEVEL      	(VL_EVO_CTL_BASE + 53)
#define		VL_EVO_BLACK_LEV_MIN_NTSC	-60	
#define		VL_EVO_BLACK_LEV_MAX_NTSC	3
#define		VL_EVO_BLACK_LEV_MIN_PAL	-45	
#define		VL_EVO_BLACK_LEV_MAX_PAL	18	

#define VL_EVO_VOUT_LUMA_WT_GN_92_5  	(VL_EVO_CTL_BASE + 60)
#define		VL_EVO_WT_GN_100	0
#define		VL_EVO_WT_GN_92_5	1

#define VL_EVO_VOUT_COLOR_BURST_AMP  	(VL_EVO_CTL_BASE + 63)
#define		VL_EVO_BURST_MIN_NTSC	-80	
#define		VL_EVO_BURST_MAX_NTSC	47	
#define		VL_EVO_BURST_MIN_PAL	-66	
#define		VL_EVO_BURST_MAX_PAL	61

/*
 * the following 5 controls have ranges 0..255
 */

#define VL_EVO_VOUT_CAP_1ST_BYTE_ODD 	(VL_EVO_CTL_BASE + 66)
#define VL_EVO_VOUT_CAP_2ND_BYTE_ODD 	(VL_EVO_CTL_BASE + 67)
#define VL_EVO_VOUT_XTN_1ST_BYTE_EVN 	(VL_EVO_CTL_BASE + 68)
#define VL_EVO_VOUT_XTN_2ND_BYTE_EVN 	(VL_EVO_CTL_BASE + 69)
#define VL_EVO_VOUT_CC_LINE          	(VL_EVO_CTL_BASE + 70)

#define VL_EVO_VOUT_CC_ENCODING      	(VL_EVO_CTL_BASE + 79)
#define		VL_EVO_ENCODING_OFF	0
#define		VL_EVO_ENCODING_ODD	1
#define		VL_EVO_ENCODING_EVN	2
#define		VL_EVO_ENCODING_BOTH	3

#define VL_EVO_VOUT_FIRST_ACTIVE_LN  	(VL_EVO_CTL_BASE + 90)
#define		VL_EVO_FIRST_ACTIVE_MIN_NTSC	-16
#define		VL_EVO_FIRST_ACTIVE_MIN_PAL	-21
#define		VL_EVO_FIRST_ACTIVE_MAX		0

#define VL_EVO_ALPHA_NOT_PIXEL          (VL_EVO_CTL_BASE + 91)


/****************************************************
 * Analog Video Input Node Controls                 *
 ****************************************************/

#define VL_EVO_VIN_GAIN_HYSTERESIS           (VL_EVO_CTL_BASE + 101)
#define		VL_EVO_GAIN_HYST_MIN		0
#define		VL_EVO_GAIN_HYST_MAX		7

#define VL_EVO_VIN_ANALOG_PROCESS            (VL_EVO_CTL_BASE + 102)
#define		VL_EVO_INPUT_PROCESS_BYPASS	0
#define		VL_EVO_INPUT_PROCESS_AMPLIFY	2
#define		VL_EVO_INPUT_PROCESS_AMPLIFY_ALIAS_FILTER	3

#define VL_EVO_VIN_GAIN_CONTROL_FIX          (VL_EVO_CTL_BASE + 103)
#define		VL_EVO_GAIN_CTL_AUTO		0
#define		VL_EVO_GAIN_CTL_USER		1

#define VL_EVO_VIN_GAIN_HOLD                 (VL_EVO_CTL_BASE + 104)
#define		VL_EVO_GAIN_HOLD_ACTIVE		0
#define		VL_EVO_GAIN_HOLD_FREEZE		1

#define VL_EVO_VIN_WHITE_PEAK                (VL_EVO_CTL_BASE + 105)
#define		VL_EVO_WHITE_PEAK_ON		0
#define		VL_EVO_WHITE_PEAK_OFF		1

/*
 * both gain ch1 and ch2 share the same value ranges
 */

#define VL_EVO_VIN_GAIN_CH1                  (VL_EVO_CTL_BASE + 108)
#define VL_EVO_VIN_GAIN_CH2                  (VL_EVO_CTL_BASE + 109)
#define		VL_EVO_GAIN_MIN			-6
#define		VL_EVO_GAIN_MAX			6

/*
 * both HSYNC start and stop share the same value ranges
 */

#define VL_EVO_VIN_HSYNC_START               (VL_EVO_CTL_BASE + 110)
#define VL_EVO_VIN_HSYNC_STOP                (VL_EVO_CTL_BASE + 111)
#define		VL_EVO_HSYNC_MIN		-107
#define		VL_EVO_HSYNC_MAX		108

#define VL_EVO_VIN_VERT_NOISE_REDUCT         (VL_EVO_CTL_BASE + 112)
#define		VL_EVO_VNOISE_NORMAL		0
#define		VL_EVO_VNOISE_SEARCH		1
#define		VL_EVO_VNOISE_FREE		2
#define		VL_EVO_VNOISE_BYPASS		3

#define VL_EVO_VIN_TV_VTR_SEL                (VL_EVO_CTL_BASE + 114)
#define		VL_EVO_TV_VTR_POOR		0
#define		VL_EVO_TV_VTR_NORMAL		1

#define VL_EVO_VIN_APERTURE_FACTOR           (VL_EVO_CTL_BASE + 118)
#define		VL_EVO_APERTURE_0		0
#define		VL_EVO_APERTURE_QTR		1
#define		VL_EVO_APERTURE_HALF		2
#define		VL_EVO_APERTURE_FULL		3

#define VL_EVO_VIN_AGC_UPDATE_INTERVAL       (VL_EVO_CTL_BASE + 119)
#define		VL_EVO_UPDT_INTVL_LINE		0
#define		VL_EVO_UPDT_INTVL_FIELD		1

#define VL_EVO_VIN_APERTURE_BAND_PASS        (VL_EVO_CTL_BASE + 121)
#define		VL_EVO_APERTURE_BAND_PASS_4_1	0
#define		VL_EVO_APERTURE_BAND_PASS_3_8	1
#define		VL_EVO_APERTURE_BAND_PASS_2_6	2
#define		VL_EVO_APERTURE_BAND_PASS_2_9	3

#define VL_EVO_VIN_PREFILTER_ACTIVE          (VL_EVO_CTL_BASE + 122)
#define		VL_EVO_PREFILTER_ACTIVE		0
#define		VL_EVO_PREFILTER_BYPASS		1

#define VL_EVO_VIN_LUMA_BRIGHTNESS           (VL_EVO_CTL_BASE + 124)
#define		VL_EVO_LUMA_BRIGHTNESS_MIN	0	/* dark */
#define		VL_EVO_LUMA_BRIGHTNESS_MAX	255	/* bright */

#define VL_EVO_VIN_LUMA_CONTRAST             (VL_EVO_CTL_BASE + 125)
#define		VL_EVO_LUMA_CONTRAST_MIN	-2
#define		VL_EVO_LUMA_CONTRAST_MAX	2

#define VL_EVO_VIN_CHROMA_SATURATION         (VL_EVO_CTL_BASE + 126)
#define		VL_EVO_CHROMA_SAT_MIN		-2
#define		VL_EVO_CHROMA_SAT_MAX		2

#define VL_EVO_VIN_CHROMA_HUE                (VL_EVO_CTL_BASE + 127)
#define		VL_EVO_CHROMA_HUE_MIN		-180
#define		VL_EVO_CHROMA_HUE_MAX		180

#define VL_EVO_VIN_CHROMA_BANDWIDTH          (VL_EVO_CTL_BASE + 128)
#define		VL_EVO_CHROMA_BAND_SMALL	0
#define		VL_EVO_CHROMA_BAND_NOMINAL	1
#define		VL_EVO_CHROMA_BAND_MEDIUM	2
#define		VL_EVO_CHROMA_BAND_WIDE		3

#define VL_EVO_VIN_FAST_COLOR_TIME_CNSTNT    (VL_EVO_CTL_BASE + 129)
#define		VL_EVO_COLOR_TIME_NOMINAL	0
#define		VL_EVO_COLOR_TIME_FAST		1

#define VL_EVO_VIN_DISABLE_CHROMA_COMB_FILTER  (VL_EVO_CTL_BASE + 130)
#define		VL_EVO_CHROMA_COMB_ON		0
#define		VL_EVO_CHROMA_COMB_OFF		1

#define VL_EVO_VIN_COLOR_STANDARD            (VL_EVO_CTL_BASE + 131)
#define		VL_EVO_COLOR_STD_PAL_NTSC	0
#define		VL_EVO_COLOR_STD_NTSC_PAL	1
#define		VL_EVO_COLOR_STD_PALN_NTSC	2
#define		VL_EVO_COLOR_STD_NTSCN_PAL	3

#define VL_EVO_VIN_LUMA_DELAY_COMPENSATE     (VL_EVO_CTL_BASE + 134)
#define		VL_EVO_LUMA_DELAY_MIN		-4
#define		VL_EVO_LUMA_DELAY_MAX		3

#define VL_EVO_VIN_VREF_PULSE_POSITION       (VL_EVO_CTL_BASE + 135)
#define		VL_EVO_VREF_PULSE_MIN		0
#define		VL_EVO_VREF_PULSE_MAX		1

/****************************************************
 *	VGI1 Memory Node DMA controls               *
 ****************************************************/

/*
 *  GIO DMA memory source blanking mode.
 *
 *  NOTE: The default output blanking is set according to VL_PACKING.
 *        This control allows that setting to be overridden.  To do so,
 *        set this control *after* VL_PACKING.
 */

#define VL_EVO_DMA_VOUT_BLANK		(VL_EVO_CTL_BASE + 303)
#define 	VL_EVO_DMA_VO_BLK_YUVA	0	/* YUVA: Y = A = 16, U = V = 128 */
#define 	VL_EVO_DMA_VO_BLK_RGBA	1	/* RP175: R = G = B = A = 16 */

/*
 *  GIO DMA memory source expansion enable.
 *
 */

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
 * For use with: VL_EVO_DMA_ERROR_RESTART
 */

#define VL_EVO_DMA_ERROR_RESTART	(VL_EVO_CTL_BASE + 305)
#define 	VL_EVO_DMA_RESTART_OFF	0	/* Transfer fails - default*/
#define 	VL_EVO_DMA_RESTART_ON	1	/* Report error, continue transfer */

#define VL_EVO_BUFFER_QUANTUM		(VL_EVO_CTL_BASE + 306)

/*
 *  DMA Starvataion Policy
 *
 *  When transferring from memory to video using a GIO DMA channel, if
 *  data is not provided quickly enough by the application (vlPutValid()),
 *  then one of the following three actions can be taken until more data
 *  becomes available:
 *
 *    VL_EVO_DMA_VO_STARV_BLK:
 *
 *     	 Go to black.  Black is output until the next transfer unit
 *	 becomes available.  Outputting black does not involve DMA.
 *
 *    VL_EVO_DMA_VO_STARV_RPT:
 *
 *     	 Repeat the last unit transferred (field or frame).  This
 *	 will occur until the next transfer unit becomes available.
 *	 In order to repeat, the unit is DMAed continuously.
 *
 *    VL_EVO_DMA_VO_STARV_FLD:
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
 *	 identical in behavior to VL_EVO_DMA_VO_STARV_RPT.
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
 * For use with: VL_EVO_DMA_VOUT_STARVATION
 */

#define VL_EVO_DMA_VOUT_STARVATION	(VL_EVO_CTL_BASE + 307)
#define 	VL_EVO_DMA_VO_STARV_BLK	0	/* Go to black */
#define 	VL_EVO_DMA_VO_STARV_RPT	1	/* Repeat last field/frame - default */
#define 	VL_EVO_DMA_VO_STARV_FLD	2	/* Repeat last field of frame only */

/*
 *  Field dominance can be set independently for each GIO DMA channel.
 *
 *  NOTE: This is a memory node control, not a device node control.
 */

/*
 *   Color Space Converter Controls
 */

#define VL_EVO_CSC_CONST_HUE		(VL_EVO_CTL_BASE + 400)
#define VL_EVO_CSC_ALPHA_CORRECTION	(VL_EVO_CTL_BASE + 401)
#define VL_EVO_CSC_COEF                 (VL_EVO_CTL_BASE + 402)
#define VL_EVO_CSC_LUT_IN_YG            (VL_EVO_CTL_BASE + 403)
#define VL_EVO_CSC_LUT_IN_UB            (VL_EVO_CTL_BASE + 404)
#define VL_EVO_CSC_LUT_IN_VR            (VL_EVO_CTL_BASE + 405) 
#define VL_EVO_CSC_LUT_OUT_YG           (VL_EVO_CTL_BASE + 406)
#define VL_EVO_CSC_LUT_OUT_UB           (VL_EVO_CTL_BASE + 407)
#define VL_EVO_CSC_LUT_OUT_VR           (VL_EVO_CTL_BASE + 408)
#define VL_EVO_CSC_LUT_ALPHA            (VL_EVO_CTL_BASE + 409)
#define VL_EVO_CSC_LUT_IN_PAGE          (VL_EVO_CTL_BASE + 410)
#define VL_EVO_CSC_LUT_ALPHA_PAGE       (VL_EVO_CTL_BASE + 411)

/*
 * sqr <-> nsqr filter type
 */

#define	VL_EVO_FILTER_TYPE		  (VL_EVO_CTL_BASE + 550)
#define 	VL_EVO_FILTER_TYPE_FREQ	0	/* frequency preserving */
#define 	VL_EVO_FILTER_TYPE_SPAT 1	/* spatially preserving */

/*
 * sqr <-> nsqr filter quality
 */

#define	VL_EVO_FILTER_QUALITY		  (VL_EVO_CTL_BASE + 551)
#define 	VL_EVO_FILTER_QUALITY_LO  0	/* low filter quality */
#define 	VL_EVO_FILTER_QUALITY_MED 1	/* medium filter quality */
#define 	VL_EVO_FILTER_QUALITY_HI  2	/* hi filter quality */


/*
 * Genlock (sync) source values.
 *
 * For use with: VL_SYNC_SOURCE
 */

#define GEN_PORT       1	/* Reference input */
#define GEN_AVIN       2	/* analog video input */
#define GEN_KSYNC      3	/* ksync input */
#define GEN_DVIN       4	/* digital video input */
#define GEN_YCIN       5	/* Y/C analog input */



/*
 * For use for dataType in VLExtendedValue.
 * EVO_CSC_COEF is coef type of VLExtendedValue. EVO_CSC_LUT_IN_ALPHA is
 * for input and alpha lut types of VLExtendedValue. EVO_CSC_LUT_OUT is
 * for output lut type of VLExtendedValue.
 */
enum VL_EVO_CSC_DataType {EVO_CSC_COEF, EVO_CSC_LUT_INPUT_AND_ALPHA, EVO_CSC_LUT_OUTPUT};

/*
 * For use with: VL_EVO_CSC_LUT_IN_{YG, UB, VR} and VL_EVO_CSC_LUT_ALPHA
 *
 * The following struct VL_EVOInAlphaLutValue is used as dataPointer
 * in VLExtendedValue.
 *
 * To set or get a lut, lut contains lut values. pageNumber is the 
 * page number this lut will be loaded to. This number can be from 
 * 0 (first page) to 3 (last page). 
 */

typedef struct {
    int lut[1024];
    int   pageNumber;		/* page number in a lut */
} VL_EVOInAlphaLutValue;

/*
 * For use with: VL_EVO_CSC_LUT_OUT_{YG, UB, VR}
 *
 * The following struct VL_EVOOutLutValue is used as dataPointer
 * in VLExtendedValue.
 *
 * To set or get a lut, lut contains lut values.
 */ 

typedef struct {
    int lut[1024];
} VL_EVOOutLutValue;

#endif /* _EVO_DEV_INCLUDE */

/* EOF dev_evo.h */
