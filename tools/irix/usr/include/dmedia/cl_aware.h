/*************************************************************************\
*                                                                         *
*                  C O P Y R I G H T   N O T I C E                        *
*                                                                         *
\*************************************************************************/

/* 
 * Copyright (c) 1992 Aware, Inc. All rights reserved.
 * 
 * Copyright Unpublished, Aware Inc.  All Rights Reserved.
 * This software contains proprietary and confidential
 * information of Aware, Inc.  Use, disclosure or
 * reproduction is prohibited without the prior express
 * written consent of Aware, Inc.
 * 
 */

#ifndef __INC_AWARE_H__
#define __INC_AWARE_H__

/*
 * Need to freeze number of common params for DSO compatibility
 */

#define CL_NUMBER_OF_PARAMS_FREEZE 23

/*
 * Parameters
 */

/* Aware Audio Specific Parameters - For both MPEG Audio and Multirate */
#define CL_AWARE_CHANNEL_POLICY	    (CL_NUMBER_OF_PARAMS_FREEZE + 0)
#define CL_AWARE_NOISE_MARGIN	    (CL_NUMBER_OF_PARAMS_FREEZE + 1)
#define CL_AWARE_BITRATE_POLICY	    (CL_NUMBER_OF_PARAMS_FREEZE + 2)

/* Additional parameters for MPEG Audio */
#define CL_AWARE_BITRATE_TARGET	    (CL_NUMBER_OF_PARAMS_FREEZE + 3)
#define CL_AWARE_LAYER		    (CL_NUMBER_OF_PARAMS_FREEZE + 4)

/* read/write for compression configuration
 * read for state during compression/decompression 
 */
/*
 * Channel Policy
 */
#define CL_AWARE_STEREO                  1
#define CL_AWARE_JOINT_STEREO            2
#define CL_AWARE_INDEPENDENT             3

/* 
 * read/write for compression configuration,
 * read for state during compression
 */
/*
 * Bit-rate Policy
 */
#define CL_AWARE_FIXED_RATE              1
#define CL_AWARE_CONST_QUAL              2
#define CL_AWARE_LOSSLESS                4

/*
 * Layer values
 */
#define CL_AWARE_MPEG_LAYER_I            1
#define CL_AWARE_MPEG_LAYER_II           2

/****************************************************************************
*
* Backward Compatibility
*
****************************************************************************/

/*
 * Old parameters
 */

#define CL_CHANNEL_POLICY	    CL_AWARE_CHANNEL_POLICY
#define CL_NOISE_MARGIN		    CL_AWARE_NOISE_MARGIN
#define CL_BITRATE_POLICY	    CL_AWARE_BITRATE_POLICY

#define CL_BITRATE_TARGET	    CL_AWARE_BITRATE_TARGET
#define CL_LAYER		    CL_AWARE_LAYER

/*
 * Old types
 */

#ifndef AWCMP_STEREO
#define AWCMP_STEREO                CL_AWARE_STEREO
#define AWCMP_JOINT_STEREO          CL_AWARE_JOINT_STEREO
#define AWCMP_INDEPENDENT           CL_AWARE_INDEPENDENT
#endif

#ifndef AWCMP_FIXED_RATE
#define AWCMP_FIXED_RATE            CL_AWARE_FIXED_RATE
#define AWCMP_CONST_QUAL            CL_AWARE_CONST_QUAL
#define AWCMP_LOSSLESS              CL_AWARE_LOSSLESS
#endif

#ifndef AWCMP_MPEG_LAYER_I
#define AWCMP_MPEG_LAYER_I          CL_AWARE_MPEG_LAYER_I
#define AWCMP_MPEG_LAYER_II         CL_AWARE_MPEG_LAYER_II
#endif

#endif /* __INC_AWARE_H__ */
