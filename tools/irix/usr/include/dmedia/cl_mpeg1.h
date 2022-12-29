/*****************************************************************************
 *
 * SGI compression library 
 *
 * cl_mpeg1.h : MPEG1 support (audio, video)
 *
 * Copyright 1994, Silicon Graphics, Inc.
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

#ifndef _INC_CL_MPEG1_H
#define _INC_CL_MPEG1_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Parameters
 */

#define CL_MPEG1_END_OF_STREAM                  (CL_ParamID(1, 0))
#define CL_MPEG1_NUM_PARAMS                     20

/******************************************************************************
*
* MPEG1 Audio
*
******************************************************************************/

/*
 * Parameters
 */

#define CL_MPEG1_AUDIO_LAYER      (CL_ParamID(1, CL_MPEG1_NUM_PARAMS + 0))
#define CL_MPEG1_AUDIO_MODE       (CL_ParamID(1, CL_MPEG1_NUM_PARAMS + 1))

/*
 * Values
 */

#define CL_MPEG1_AUDIO_LAYER_I                  1
#define CL_MPEG1_AUDIO_LAYER_II                 2

#define CL_MPEG1_AUDIO_MODE_STEREO              0
#define CL_MPEG1_AUDIO_MODE_JOINT               1
#define CL_MPEG1_AUDIO_MODE_DUAL                2
#define CL_MPEG1_AUDIO_MODE_SINGLE              3

/******************************************************************************
*
* MPEG1 Video
*
******************************************************************************/

/*
 * Parameters
 */

#define CL_MPEG1_VIDEO_M           (CL_ParamID(1, CL_MPEG1_NUM_PARAMS + 0))
#define CL_MPEG1_VIDEO_N           (CL_ParamID(1, CL_MPEG1_NUM_PARAMS + 1))
#define CL_MPEG1_VIDEO_MAX_MOTION_VECTOR_LENGTH_P_X \
                                   (CL_ParamID(1, CL_MPEG1_NUM_PARAMS + 2))
#define CL_MPEG1_VIDEO_MAX_MOTION_VECTOR_LENGTH_P_Y \
                                   (CL_ParamID(1, CL_MPEG1_NUM_PARAMS + 3))
#define CL_MPEG1_VIDEO_MAX_MOTION_VECTOR_LENGTH_B_X \
                                   (CL_ParamID(1, CL_MPEG1_NUM_PARAMS + 4))
#define CL_MPEG1_VIDEO_MAX_MOTION_VECTOR_LENGTH_B_Y \
                                   (CL_ParamID(1, CL_MPEG1_NUM_PARAMS + 5))
#define CL_MPEG1_VIDEO_SOFTNESS    (CL_ParamID(1, CL_MPEG1_NUM_PARAMS + 6))

/*
 * Values
 */

#define CL_MPEG1_VIDEO_SOFTNESS_NONE            0
#define CL_MPEG1_VIDEO_SOFTNESS_MEDIUM          1
#define CL_MPEG1_VIDEO_SOFTNESS_MAXIMUM         2

/******************************************************************************
*
* Backwards Compatibility
*
******************************************************************************/

#define CL_MPEG_VIDEO			 CL_MPEG1_VIDEO_SOFTWARE
#define CL_END_OF_SEQUENCE		 CL_MPEG1_END_OF_STREAM

#ifdef __cplusplus
}
#endif

#endif /* _INC_CL_MPEG1_H */
