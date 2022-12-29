#ifndef _INC_CL_IMPACT_H
#define _INC_CL_IMPACT_H

/*****************************************************************************
 *
 * SGI compression library 
 *
 * cl_impact.h
 *      header file for use with /usr/lib/libcl.a
 *
 * Copyright 1992, 1993 & 1994, Silicon Graphics, Inc.
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
 *
 ****************************************************************************/

/*
 *This header file defines contains impact-specific codec and video
 *back end controls.
 *
 *
 *NOTE: The parameters CL_ParamID (1, [0..CL_JPEG_NUM_PARAMS-1]) are JPEG-
 *      specific. 
 *
 *      These parameters apply to both the Independent JPEG Group
 *      software codec and the impact hardware codec.
 */

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Video back end input control. 
 * selects which channel of the impact board we have/want
 */
#define	CL_IMPACT_VIDEO_INPUT_CONTROL	(CL_ParamID (1, CL_JPEG_NUM_PARAMS+0))

#define		CL_IMPACT_VIDEO_CHANNEL0		(4)
#define		CL_IMPACT_VIDEO_CHANNEL1	   	(5)

/*
 * Codec shutdown command for use when operating in compressor/decompressor
 * in continuous mode.
 */
#define CL_IMPACT_CODEC_CONTROL          (CL_ParamID (1, CL_JPEG_NUM_PARAMS+1))

#define        	CL_IMPACT_STOP                      	(40)
#define        	CL_IMPACT_START                      	(41)

/*
 * Select fields interleaved in memory as a single frame
 */
#define CL_IMPACT_FRAME_INTERLEAVE	(CL_ParamID (1, CL_JPEG_NUM_PARAMS+2))

/*
 * select dominance of interleaved frames
 */
#define	CL_IMPACT_INTERLEAVE_MODE	(CL_ParamID (1, CL_JPEG_NUM_PARAMS+3))

#define		CL_IMPACT_INTERLEAVE_ODD		(1)
#define		CL_IMPACT_INTERLEAVE_EVEN		(2)

/*
 * Select JPEG lossless mode (available only for compression)
 */
#define	CL_IMPACT_LOSSLESS_JPEG		(CL_ParamID (1, CL_JPEG_NUM_PARAMS+4))

/*
 * Utilize software decimation and color space conversion, regardless
 * of the image size.  (for video size images, hardware decimate and csc
 * functionality is available, and is the default)
 */
#define	CL_IMPACT_SW_DECIM_CSC		(CL_ParamID (1, CL_JPEG_NUM_PARAMS+5))

/*
 * The application promises to never access the uncompressed data ring
 * buffer contents, and has already marked the ring as uncacheable and
 * cache invalidated via cachectl(2)
 */
#define	CL_IMPACT_BUFFER_ADVISE		(CL_ParamID (1, CL_JPEG_NUM_PARAMS+6))

#define		CL_BUFFER_ADVISE_ACCESS			(1)
#define		CL_BUFFER_ADVISE_NOACCESS		(2)

/*
 * this includes some additional private parameters which are used 
 * internally by the compression library
 */
#define CL_IMPACT_NUM_PARAMS		(7)

#ifdef __cplusplus
}
#endif

#endif /* _INC_CL_COSMO_H */
