#ifndef __INC_DM_AUDIOCONVERT_H__
#define __INC_DM_AUDIOCONVERT_H__  

/***************************************************************************
 * SGI Digital Media Library: Audio Conversion Routines
 *
 * <dmedia/dm_audioconvert.h>
 *    header file for use with /usr/lib/libdmedia.so
 *
 ***************************************************************************
 * 
 * Copyright 1996, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED
 *
 * UNPUBLISHED -- Rights reserved under the copyright laws of the United
 * States.   Use of a copyright notice is precautionary only and does not
 * imply publication or disclosure.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to restrictions
 * as set forth in FAR 52.227.19(c)(2) or subparagraph (c)(1)(ii) of the Rights
 * in Technical Data and Computer Software clause at DFARS 252.227-7013 and/or
 * in similar or successor clauses in the FAR, or the DOD or NASA FAR
 * Supplement.  Contractor/manufacturer is Silicon Graphics, Inc.,
 * 2011 N. Shoreline Blvd. Mountain View, CA 94039-7311.
 *
 * THE CONTENT OF THIS WORK CONTAINS CONFIDENTIAL AND PROPRIETARY
 * INFORMATION OF SILICON GRAPHICS, INC. ANY DUPLICATION, MODIFICATION,
 * DISTRIBUTION, OR DISCLOSURE IN ANY FORM, IN WHOLE, OR IN PART, IS STRICTLY
 * PROHIBITED WITHOUT THE PRIOR EXPRESS WRITTEN PERMISSION OF SILICON
 * GRAPHICS, INC.
 *
 ****************************************************************************/

#ident "$Revision: 1.5 $"

#ifdef __cplusplus
extern "C" {
#endif

#include <dmedia/dmedia.h>
#include <dmedia/dm_audio.h>
#include <dmedia/dm_params.h>

typedef struct _DMaudioconverter *DMaudioconverter;

/********
*
* Audio sampling rate conversion algorithms
*
********/

#define DM_AUDIO_RC_ALGORITHM      	"DM_AUDIO_RC_ALGORITHM"

#define DM_AUDIO_RC_JITTER_FREE    	"DM_AUDIO_RC_JITTER_FREE"
#define DM_AUDIO_RC_POLYNOMIAL_ORDER_1  "DM_AUDIO_RC_POLYNOMIAL_ORDER_1"
#define DM_AUDIO_RC_POLYNOMIAL_ORDER_3  "DM_AUDIO_RC_POLYNOMIAL_ORDER_3"

/********
*
* Algorithm-specific parameters for the jitter-free rate conversion algorithm
*
********/

#define DM_AUDIO_RC_JITTER_FREE_STOPBAND_ATTENUATION \
		"DM_AUDIO_RC_JITTER_FREE_STOPBAND_ATTENUATION"

#define DM_AUDIO_RC_JITTER_FREE_STOPBAND_ATTENUATION_78_DB	78.0
#define DM_AUDIO_RC_JITTER_FREE_STOPBAND_ATTENUATION_96_DB	96.0
#define DM_AUDIO_RC_JITTER_FREE_STOPBAND_ATTENUATION_120_DB	120.0

#define DM_AUDIO_RC_JITTER_FREE_TRANSITION_BANDWIDTH \
		"DM_AUDIO_RC_JITTER_FREE_TRANSITION_BANDWIDTH"

#define	DM_AUDIO_RC_JITTER_FREE_TRANSITION_BANDWIDTH_1_PERCENT	1.0
#define	DM_AUDIO_RC_JITTER_FREE_TRANSITION_BANDWIDTH_10_PERCENT	10.0
#define	DM_AUDIO_RC_JITTER_FREE_TRANSITION_BANDWIDTH_20_PERCENT	20.0

/********
*
* Parameters for compression and decompression
*
********/

/*  Conversion (Transform) Parameters
 *
 *  These are used by libdmedia's dmACSetParams()
 *	and by libaudiofile's afSetConversionParams()
 */

/* channel matrix for distributing input channels to output channels.
 * This is type DM_TYPE_FLOAT_ARRAY (defined in <dmedia/dm_params.h>)
 */

#define DM_AUDIO_CHANNEL_MATRIX 	"DM_AUDIO_CHANNEL_MATRIX"

/* dithering algorithms */

#define DM_AUDIO_DITHER_ALGORITHM   "DM_AUDIO_DITHER_ALGORITHM"

#define DM_AUDIO_DITHER_NONE        0
#define DM_AUDIO_DITHER_LSB_TPDF    1

/* maximum requested input or output buffer size for DMaudioconverter */

#define DM_AUDIO_MAX_REQUEST_LEN	"DM_AUDIO_MAX_REQUEST_LEN"	

/* calculated minimum input or output buffer needed to match the above */

#define DM_AUDIO_MIN_INPUT_LEN		"DM_AUDIO_MIN_INPUT_LEN"
#define DM_AUDIO_MIN_OUTPUT_LEN		"DM_AUDIO_MIN_OUTPUT_LEN"

/* the mode in which the converter will be running.  PULL means the user 
 * requests a fixed output size; PUSH means the user gives the converter a 
 * fixed input buffer size.  The converter determines which of these will be
 * used, though there may be occasions when the user may request one.
 */

#define DM_AUDIO_PROCESS_MODE		"DM_AUDIO_PROCESS_MODE"
#define DM_AUDIO_PROCESS_PULL		1
#define DM_AUDIO_PROCESS_PUSH		2

/* the value used to flush the Rate Converter during dmAC flush mode
 * It is type float.
 */

#define DM_AUDIO_RC_FLUSH_VALUE		"DM_AUDIO_RC_FLUSH_VALUE"

/* public routines */

extern DMstatus dmACCreate(DMaudioconverter* converter);

extern DMstatus dmACDestroy(DMaudioconverter converter);

extern DMstatus dmACReset(DMaudioconverter converter);

extern DMstatus	dmACSetParams( DMaudioconverter converter, 
                               DMparams *sourceparams,
                               DMparams *destparams,
                               DMparams *conversionparams);

/*
 *  This allows an application to query whether a given set of conversion
 *  parameters needed to be "adjusted" in any fashion by the converter.
 *  This allows the possibility of intelligent internal adjustments (such as
 *  alternate rate conversion algorithms and process mode selection).
 */

extern DMstatus	dmACGetParams( DMaudioconverter converter, 
                               DMparams *sourceparams,
                               DMparams *destparams,
                               DMparams *conversionparams);

extern DMstatus	dmACConvert( DMaudioconverter converter,
			                 void *inbuf,	/* input buffer */
                             void *outbuf,	/* output buffer */

			/* amount of data provided in inbuf in frames or bytes, reset
			   to amount of data taken from inbuf by dmACConvert 
			 */

                             int *inframes,

			/* amount of data desired/space provided in outbuf in frames 
			   or bytes, reset to amount of data placed in outbuf by
			   dmACConvert 
			 */

                             int *outframes);

/*
 *  Utility for retrieving mininum necessary output buffer size 
 *  for a given input size
 */

extern DMstatus dmACGetMinOutputSize(
            DMaudioconverter converter,
			int inputSize, /* input size in frames */
            int* outputSize); /* returned minimum necessary output size */

/*
 *  Utility for retrieving the mininum necessary input buffer size 
 *  for a given output size
 */

extern DMstatus dmACGetMinInputSize(
			DMaudioconverter converter,
			int outputSize,		/* desired output size in frames */
			int* inputSize);	/* returned minimum necessary input size */

/**********************************************************************
 *	 Error messages for compression/decompression, rate conversion, and 
 *	 audio conversion.  Returned by dmGetError().
 **********************************************************************/

#define DM_AUDIO_UNSUPPORTED		5001  /* unsupported function / feature */
#define DM_AUDIO_MISSING_PARAM		5002  /* missing DMparam value */
#define DM_AUDIO_BAD_PARAM			5003  /* invalid or missing DMparam */
#define DM_AUDIO_BAD_RC_ALGORITHM	5004  /* invalid rate convert alg. */
#define DM_AUDIO_BAD_RC_RATIO		5005  /* invalid ratio for rate conv.  */
#define DM_AUDIO_BAD_FRAMESIZE		5006  /* invalid frame size */
#define DM_AUDIO_CODEC_ERROR		5007  /* general encoder/decoder error */
#define DM_AUDIO_ENCODER_ERROR		5008
#define DM_AUDIO_DECODER_ERROR		5009
#define DM_AUDIO_BAD_FORMAT			5010  /* invalid format or sample width */
#define DM_AUDIO_BAD_RATE			5011  /* invalid sample rate */
#define DM_AUDIO_BAD_CHANNELS		5012  /* invalid channel count */
#define DM_AUDIO_BAD_BITRATE		5013  /* invalid bitrate for codec */
#define DM_AUDIO_NO_LICENCE 		5014  /* no licence found for codec */
#define DM_AUDIO_BAD_HEADER			5015  /* bad compressed header */
#define DM_AUDIO_NOT_CONFIGURED		5016  /* handle not yet configured */
#define DM_AUDIO_BAD_REQUEST		5017  /* illegal request */

#ifdef __cplusplus 
}
#endif

#endif /* ! __INC_DM_AUDIOCONVERT_H__ */
