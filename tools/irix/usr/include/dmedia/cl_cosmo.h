#ifndef _INC_CL_COSMO_H
#define _INC_CL_COSMO_H

/*****************************************************************************
 *
 * SGI compression library 
 *
 * cl_cosmo.h
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
 *This header file defines contains Cosmo-specific codec and video
 *back end controls.
 *
 *
 *NOTE: The parameters CL_ParamID (1, [0..CL_JPEG_NUM_PARAMS-1]) are JPEG-
 *      specific. 
 *
 *      These parameters apply to both the Independent JPEG Group
 *      software codec and the Cosmo hardware codec.
 */

#ifdef __cplusplus
extern "C" {
#endif

#define CL_COSMO_VALUE_BASE             (1000)

/*
 * Cosmo video port transfer mode.
 *
 * AUTO_2_FIELD is the standard mode of operation. It may be used 
 * during JPEG video capture or playback.
 *
 *	AUTO_2_FIELD ->   display/capture interlaced video at standard
 *                        NTSC or PAL field rate
 *
 * These modes apply only to JPEG video playback.
 *
 *	AUTO_1_FIELD ->   Cosmo video back-end displays each field
 *                        supplied by the application as a frame (via
 *                        line replication). This mode may be used to play 
 *                        back video at half speed, for example.
 *
 *	MANUAL	     ->   Application manually triggers field advance.
 *                        Manual advance takes effect only if there is a
 *                        valid decompressed field in the output queue
 *                        waiting to be displayed. The video back-end will
 *                        loop on a given field (scanning it out for both
 *                        odd and even field display) until a new field
 *                        is available from the decompressor and 
 *                        a VIDEO_MANUAL_ADVANCE command is issued by the
 *                        application (see below).
 */
#define CL_COSMO_VIDEO_TRANSFER_MODE    (CL_ParamID (1, CL_JPEG_NUM_PARAMS+0))

#define        	CL_COSMO_VIDEO_TRANSFER_AUTO_1_FIELD  	(CL_COSMO_VALUE_BASE+10)
#define        	CL_COSMO_VIDEO_TRANSFER_AUTO_2_FIELD  	(CL_COSMO_VALUE_BASE+11)
#define        	CL_COSMO_VIDEO_TRANSFER_MANUAL        	(CL_COSMO_VALUE_BASE+12)

/*
 * Manual video field advance for use when operating in MANUAL transfer mode.
 */
#define CL_COSMO_VIDEO_MANUAL_CONTROL   (CL_ParamID (1, CL_JPEG_NUM_PARAMS+1))

#define        	CL_COSMO_VIDEO_MANUAL_ADVANCE		(CL_COSMO_VALUE_BASE+20)

/*
 * Video back end input control. 
 * Selects which port of the cosmo SGI-D1 connector cosmo receives
 * timing input on (and if compressing, which port the data will arrive on).
 *	CL_COSMO_VIDEO_INPUT_PORT0	[uni-directional port]
 *	CL_COSMO_VIDEO_INPUT_PORT1	[bi-directional port]
 */
#define	CL_COSMO_VIDEO_INPUT_CONTROL	(CL_ParamID (1, CL_JPEG_NUM_PARAMS+2))

#define		CL_COSMO_VIDEO_INPUT_PORT0		(CL_COSMO_VALUE_BASE+30)
#define		CL_COSMO_VIDEO_INPUT_PORT1	   	(CL_COSMO_VALUE_BASE+31)

/*
 * Codec shutdown command for use when operating in compressor/decompressor
 * in continuous mode.
 */
#define CL_COSMO_CODEC_CONTROL          (CL_ParamID (1, CL_JPEG_NUM_PARAMS+3))

#define        	CL_COSMO_STOP                      	(CL_COSMO_VALUE_BASE+40)

/*
 * this includes some additional private parameters which are used 
 * internally by the compression library
 */
#define CL_COSMO_NUM_PARAMS		(14)

#ifdef __cplusplus
}
#endif

#endif /* _INC_CL_COSMO_H */
