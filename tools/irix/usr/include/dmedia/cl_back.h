/*****************************************************************************
 *
 * SGI compression library 
 *
 * cl_back.h
 *      Defines for backwards compatibility.  Use of these definitions
 *      is not recommended.
 *
 * Copyright 1992 & 1993, Silicon Graphics, Inc.
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

#ifndef _INC_CL_BACK_H_
#define _INC_CL_BACK_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Undocumented 
 */
#define CL_HDCC_SOFTWARE                 CL_Algorithm(CL_VIDEO, 6)
#define CL_HDCC_TILE_THRESHOLD           (CL_ParamID(1, 0))
#define CL_HDCC_SAMPLES_PER_TILE         (CL_ParamID(1, 1))
#define CL_TILE_THRESHOLD                CL_HDCC_TILE_THRESHOLD 
#define CL_SAMPLES_PER_TILE              CL_HDCC_SAMPLES_PER_TILE

#define FRAME_SIZE                       1
#define TOTAL_FRAMES                     2

/*
 * Old format names
 */
#define CL_MONO                 CL_FORMAT_MONO
#define CL_STEREO_INTERLEAVED   CL_FORMAT_STEREO_INTERLEAVED
  
#define CL_RGB                  CL_FORMAT_BGR
#define CL_RGBX                 CL_FORMAT_XBGR
#define CL_RGBA                 CL_FORMAT_ABGR
#define CL_RGB332               CL_FORMAT_RBG323

#define CL_GRAYSCALE            CL_FORMAT_GRAYSCALE
#define CL_Y                    CL_FORMAT_GRAYSCALE
#define CL_YUV                  CL_FORMAT_YCbCr
#define CL_YCbCr                CL_FORMAT_YCbCr
#define CL_YUV422               CL_FORMAT_YCbCr422
#define CL_YCbCr422             CL_FORMAT_YCbCr422
#define CL_YUV422HC             CL_FORMAT_YCbCr422DC
#define CL_YCbCr422HC           CL_FORMAT_YCbCr422DC
#define CL_YUV422DC             CL_FORMAT_YCbCr422DC
#define CL_YCbCr422DC           CL_FORMAT_YCbCr422DC

#define CL_RGB8                 CL_FORMAT_BGR233

#define CL_NUMBER_OF_FORMATS    CL_NUMBER_OF_VIDEO_FORMATS
  
#define CL_BytesPerSample(s) \
(   /* if */ (((s) == CL_FORMAT_MONO) || ((s) == CL_FORMAT_YCbCr)) ? \
        /* return */ 2 : \
    /* else if */ ((s) == CL_FORMAT_STEREO_INTERLEAVED) ?  \
        /* return */ 4 : \
    /* else */ \
        /* return */ 0 \
)

/*
 * Old parameter names
 */
#define CL_ORIGINAL_FORMAT               CL_FORMAT
#define CL_FRAME_BUFFER_SIZE             CL_FRAME_SIZE     
#define CL_BLOCK_SIZE                    CL_FRAMES_PER_CHUNK
#define CL_LAST_FRAME_INDEX              CL_FRAME_INDEX

/*
 * Old types
 */
#define CL_FRAME                         CL_BUF_FRAME            
#define CL_DATA                          CL_BUF_COMPRESSED
#define CL_BUF_DATA                      CL_BUF_COMPRESSED

#define CL_FunctionPtr                   CLfunctionPtr
#define CL_ErrFunc                       CLerrFunc

#define CL_Handle                        CLhandle
#define CL_CompressorHdl                 CLhandle
#define CLcompressorHdl                  CLhandle
#define CL_BufferHdl                     CLbufferHdl

/*
 * Old algorithm types
 */
#define CL_AUDIO                         CL_ALG_AUDIO
#define CL_VIDEO                         CL_ALG_VIDEO

/*
 * Old algorithms
 */
#define CL_G711_ULAW                     CL_G711_ULAW_SOFTWARE
#define CL_ULAW                          CL_G711_ULAW_SOFTWARE
#define CL_G711_ALAW                     CL_G711_ALAW_SOFTWARE
#define CL_ALAW                          CL_G711_ALAW_SOFTWARE
#define CL_AWARE_MPEG_AUDIO              CL_MPEG1_AUDIO_AWARE
#define CL_AWARE_MULTIRATE               CL_MULTIRATE_AWARE

#define CL_UNCOMPRESSED                  CL_UNCOMPRESSED_VIDEO
#define CL_RLE                           CL_RLE_SOFTWARE
#define CL_JPEG                          CL_JPEG_SOFTWARE
#define CL_MVC1                          CL_MVC1_SOFTWARE
#define CL_RTR                           CL_MVC3_SOFTWARE
#define CL_RTR1                          CL_MVC3_SOFTWARE
#define CL_HDCC                          CL_HDCC_SOFTWARE
#define CL_MVC2                          CL_MVC2_SOFTWARE
#define CL_RLE24                         CL_RLE24_SOFTWARE

/*
 * Old calls
 */
int clReadData(CLbufferHdl bufferHdl, 
    int requestedDataSize, void **compressedData);
int clDone(CLbufferHdl bufferHdl, int size);

/*
 * Defines that should not be exposed
 */
#define CL_MAX_NUMBER_OF_FORMATS                (32)
#define CL_MAX_NUMBER_OF_ORIGINAL_FORMATS       CL_MAX_NUMBER_OF_FORMATS

#define CL_MAX_NUMBER_OF_AUDIO_ALGORITHMS       (32)
#define CL_MAX_NUMBER_OF_VIDEO_ALGORITHMS       (32)
#define CL_AlgorithmNumber(scheme)      ((scheme) & 0x3fff)

#define CL_MAX_NUMBER_OF_PARAMS (256)
#define CL_NUMBER_OF_PARAMS     (32)
#define CL_ParamNumber(paramID) (((paramID) & 0x80000000) == 0 ? \
                                 (paramID) & 0x7fffffff : \
                                (((paramID) & 0x7fffffff) + \
                                 CL_NUMBER_OF_PARAMS))

#define CL_HEADER_START_CODE    0xc1C0DEC  /* for SGI proprietary algs */

#ifdef __cplusplus
}
#endif

#endif  /* _INC_CL_BACK_H_ */
