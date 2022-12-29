/*****************************************************************************
 *
 * SGI compression library 
 *
 * cl.h
 *      header file for use with /usr/lib/libcl.so
 *
 * Copyright 1992-1995, Silicon Graphics, Inc.
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

#ident "$Revision: 1.62 $"

#ifndef _INC_CL_H_
#define _INC_CL_H_ 1

#include <dmedia/dmedia.h>
#include <dmedia/dm_audio.h>
#include <dmedia/dm_image.h>
#include <dmedia/dm_params.h>

#ifdef __cplusplus
extern "C" {
#endif

#if     !defined(TRUE) || ((TRUE) != 1)
#define TRUE    (1)
#endif
#if     !defined(FALSE) || ((FALSE) != 0)
#define FALSE   (0)
#endif
#if     !defined(SUCCESS) || ((SUCCESS) != 0)
#define SUCCESS (0)
#endif
#if     !defined(FAILURE) || ((FAILURE) != -1)
#define FAILURE (-1)
#endif
#if     !defined(byte)
typedef unsigned char   byte;
#endif
#if     !defined(FunctionPtr)
typedef int (*FunctionPtr)();
#endif

/*
 * Audio Formats
 */

#define CL_FORMAT_MONO                 (0)
#define CL_FORMAT_STEREO_INTERLEAVED   (1)

#define CL_AudioFormatName(f) \
(   /* if */ ((f) == CL_FORMAT_MONO) ? \
        /* return */ "MONO" : \
    /* else if */ ((f) == CL_FORMAT_STEREO_INTERLEAVED) ?  \
        /* return */ "STEREO_INTERLEAVED" : \
    /* else */ \
        /* return */ "Not a valid format" \
)

/*
 * Video Pixel Formats
 *
 * These are the values to be used with CL_FORMAT and CL_INTERNAL_FORMAT.
 *
 * All pixel formats have 8 bits per component, except for
 * CL_FORMAT_RBG323 and CL_FORMAT_BGR233 which have have fewer.
 *
 * The YCbCr formats follow the CCIR-601 standard which means
 * that the Y has a nominal range of 16-235 and the Cb and Cr
 * are in the range of 128 +/- 112.  The YCbCr422 format has
 * subsampled chrominance with left co-siting.
 */
#define CL_FORMAT_BGR           (0)	/* 24 bits, BGR packing  */
#define CL_FORMAT_XBGR          (1)	/* 32 bits, XBGR packing */
#define CL_FORMAT_ABGR          (2)	/* 32 bits, ABGR packing */
#define CL_FORMAT_RBG323        (3)     /* Indigo Entry & SV 8 bit: RRR BB GGG*/
#define CL_FORMAT_GRAYSCALE     (4)	/* 8 bits, luminance only  */
#define CL_FORMAT_YCbCr         (5)     /* 4:4:4 sampling: CbYCr packing */
#define CL_FORMAT_YCbCr422      (6)     /* 4:2:2 sampling: CbYCrY packing  */
#define CL_FORMAT_YCbCr422DC    (7)     /* 4:1:1 sampling: CbYCrY packing */
#define CL_FORMAT_BGR233        (8)     /* Indy/XL & Vino 8 bit: BB GGG RRR */

#define CL_NUMBER_OF_VIDEO_FORMATS	9

#define CL_BEST_FIT             (-1)    

#define CL_BytesPerPixel(f) \
(   /* if */ (((f) == CL_FORMAT_BGR) || ((f) == CL_FORMAT_YCbCr)) ? \
        /* return */ 3 : \
    /* else if */ (((f) == CL_FORMAT_XBGR) || ((f) == CL_FORMAT_ABGR)) ?  \
        /* return */ 4 : \
    /* else if */ (((f) == CL_FORMAT_RBG323) || ((f) == CL_FORMAT_GRAYSCALE) || \
                ((f) == CL_FORMAT_BGR233)) ? \
        /* return */ 1 : \
    /* else */ \
        /* return */ 2 \
)

#define CL_VideoFormatName(f) \
(   /* if */ ((f) == CL_FORMAT_BGR) ? \
        /* return */ "BGR" : \
    /* else if */ ((f) == CL_FORMAT_XBGR) ?  \
        /* return */ "XBGR" : \
    /* else if */ ((f) == CL_FORMAT_ABGR) ?  \
        /* return */ "ABGR": \
    /* else if */ ((f) == CL_FORMAT_RBG323) ?  \
        /* return */ "RBG323": \
    /* else if */ ((f) == CL_FORMAT_GRAYSCALE) ? \
        /* return */ "GRAYSCALE" : \
    /* else if */ ((f) == CL_FORMAT_YCbCr) ? \
        /* return */ "YCbCr" : \
    /* else if */ ((f) == CL_FORMAT_YCbCr422) ? \
        /* return */ "YCbCr422" : \
    /* else if */ ((f) == CL_FORMAT_YCbCr422DC) ? \
        /* return */ "YCbCr422DC" : \
    /* else if */ ((f) == CL_FORMAT_BGR233) ?  \
        /* return */ "BGR233": \
    /* else */ \
        /* return */ "Not a valid format" \
)

/*
 * Algorithm Types
 */
#define CL_ALG_AUDIO                (0)
#define CL_ALG_VIDEO                (1)

/* 
 * Algorithms 
 */
#define CL_AlgorithmType(scheme)    ((3 - (((scheme) >> 14) & 3)) % 3)
#define CL_Algorithm(type, n)       ((n) | (((3 - (type)) % 3) & 3) << 14)

#define CL_UNKNOWN_SCHEME       (-1)

#define CL_UNCOMPRESSED_AUDIO   CL_Algorithm(CL_ALG_AUDIO, 0)
#define CL_G711_ULAW_SOFTWARE   CL_Algorithm(CL_ALG_AUDIO, 1)
#define CL_G711_ALAW_SOFTWARE   CL_Algorithm(CL_ALG_AUDIO, 2)
#define CL_MPEG1_AUDIO_AWARE    CL_Algorithm(CL_ALG_AUDIO, 3)
#define CL_MULTIRATE_AWARE      CL_Algorithm(CL_ALG_AUDIO, 4)
#define CL_MPEG1_AUDIO_SOFTWARE CL_Algorithm(CL_ALG_AUDIO, 5)

#define CL_UNCOMPRESSED_VIDEO   CL_Algorithm(CL_ALG_VIDEO, 0)
#define CL_RLE_SOFTWARE         CL_Algorithm(CL_ALG_VIDEO, 1)
#define CL_JPEG_SOFTWARE        CL_Algorithm(CL_ALG_VIDEO, 2)
#define CL_MPEG1_VIDEO_SOFTWARE CL_Algorithm(CL_ALG_VIDEO, 3)
#define CL_MVC1_SOFTWARE        CL_Algorithm(CL_ALG_VIDEO, 4)
#define CL_MVC3_SOFTWARE        CL_Algorithm(CL_ALG_VIDEO, 5)
#define CL_JPEG_COSMO           CL_Algorithm(CL_ALG_VIDEO, 7)
#define CL_MVC2_SOFTWARE        CL_Algorithm(CL_ALG_VIDEO, 8)
#define CL_RLE24_SOFTWARE       CL_Algorithm(CL_ALG_VIDEO, 9)
#define CL_JPEG_IMPACT          CL_Algorithm(CL_ALG_VIDEO, 10)

/*
 * Parameters
 */
#define CL_ParamType(paramID)   (((paramID) >> 31) & 1)
#define CL_ParamID(type, n)     ((n) | (((type) & 1) << 31))

/* General Parameters */
#define CL_IMAGE_WIDTH              (0)
#define CL_IMAGE_HEIGHT             (1) 
#define CL_FORMAT                   (2)
#define CL_INTERNAL_FORMAT          (3)
#define CL_COMPONENTS               (4)
#define CL_BITS_PER_COMPONENT       (5)
#define CL_FRAME_RATE               (6)
#define CL_COMPRESSION_RATIO        (7)
#define CL_EXACT_COMPRESSION_RATIO  (8)
#define CL_FRAME_SIZE               (9) 
#define CL_COMPRESSED_BUFFER_SIZE   (10)
#define CL_FRAMES_PER_CHUNK         (11)
#define CL_PREROLL                  (12)
#define CL_FRAME_TYPE               (13)
#define CL_ALGORITHM_ID             (14)
#define CL_ALGORITHM_VERSION        (15)
#define CL_ORIENTATION              (16)
#define CL_NUMBER_OF_FRAMES         (17)
#define CL_SPEED                    (18)
#define CL_FRAME_INDEX              (19)
#define CL_ENABLE_IMAGEINFO         (20)
#define CL_INTERNAL_IMAGE_WIDTH     (21)
#define CL_INTERNAL_IMAGE_HEIGHT    (22)
#define CL_IMAGE_CROP_LEFT          (23)
#define CL_IMAGE_CROP_RIGHT         (24)
#define CL_IMAGE_CROP_TOP           (25)
#define CL_IMAGE_CROP_BOTTOM        (26)
#define CL_PIXEL_ASPECT             (27)
#define CL_BITRATE                  (28)
#define CL_QUALITY_SPATIAL          (29)
#define CL_QUALITY_TEMPORAL         (30)
#define CL_KEYFRAME_DISTANCE        (31)

/*
 * Casting
 */
#define CL_TypeIsFloat(v)                  (*(float *)&(v))
#define CL_TypeIsInt(v)                    (*(int *)&(v))

/*
 * Parameter Value Types
 */
#define CL_ENUM_VALUE           (0) /* only certain constant values are valid*/
#define CL_RANGE_VALUE          (1) /* any value in a given range is valid */
#define CL_FLOATING_ENUM_VALUE  (2) /* only certain constant floating point 
                                       values are valid */
#define CL_FLOATING_RANGE_VALUE (3) /* any value in a given floating point 
                                       range is valid */

/*
 * Algorithm Functionality
 */
#define CL_DECOMPRESSOR         (1)
#define CL_COMPRESSOR           (2)
#define CL_CODEC                (3)

/*
 * Buffer Types
 */
#define CL_NONE                 (0)
#define CL_BUF_FRAME            (1)
#define CL_BUF_COMPRESSED       (2)

/*
 * Frame Types
 */
#define CL_NONE                 (0)
#define CL_KEYFRAME             (1)
#define CL_INTRA                (1)
#define CL_PREDICTED            (2)
#define CL_BIDIRECTIONAL        (3)

/*
 * Orientations
 */
#define CL_TOP_DOWN             (0)
#define CL_BOTTOM_UP            (1)

/*
 * Special Values for clCompress/clDecompress Counts
 */
#define CL_CONTINUOUS_BLOCK	(-1)
#define CL_CONTINUOUS_NONBLOCK	(-2)

/*
 * Special Value for clCompress/clDecompress Frame or Compressed
 * Buffer when Connected to External Video.
 */
#define CL_EXTERNAL_DEVICE	((void*)-1)

/*
 * Handle Definitions
 */
struct CL_CompressorStorage;
typedef struct CL_CompressorStorage      *CLhandle;
struct CL_BufferStorage;
typedef struct CL_BufferStorage          *CLbufferHdl;

/*
 * Function Pointer Definitions
 */
typedef int  (*CLfunctionPtr)();
typedef void (*CLerrFunc)(CLhandle handle, int code, const char *format, ...);

/*
 * Argument to clGetNextImageInfo
 */
typedef struct {
    unsigned size;              /* size of compressed image in bytes */
    unsigned long long ustime;  /* time in nanoseconds */
    unsigned imagecount;        /* absolute media stream counter */
    unsigned status;		/* additional information */
} CLimageInfo;

/*
 * Values for CLimageInfo Status Field
 */
#define CL_IMAGEINFO_FIELDMASK	3		/* Bits in status */
#define	CL_IMAGEINFO_FIELD_ODD	1	        /* image was an odd field */
#define	CL_IMAGEINFO_FIELD_EVEN	2	        /* image was an even field */

/*
 * Error Codes
 */
#define CL_BAD_NO_BUFFERSPACE       ( -2) /* no space for internal buffers */
#define CL_BAD_PVBUFFER             ( -3) /* param/val buffer doesn't make 
                                             sense */
#define CL_BAD_BUFFERLENGTH_NEG     ( -4) /* negative buffer length */
#define CL_BAD_BUFFERLENGTH_ODD     ( -5) /* odd length parameter/value 
                                             buffer */
#define CL_BAD_PARAM                ( -6) /* invalid parameter */
#define CL_BAD_COMPRESSION_SCHEME   ( -7) /* compression scheme parameter 
                                             invalid */
#define CL_BAD_COMPRESSOR_HANDLE    ( -8) /* compression handle parameter 
                                             invalid */
#define CL_BAD_COMPRESSOR_HANDLE_POINTER \
                                    ( -9) /* compression handle pointer 
                                             invalid */
#define CL_BAD_BUFFER_HANDLE        (-10) /* buffer handle invalid */
#define CL_BAD_BUFFER_QUERY_SIZE    (-11) /* buffer query size too large or 
                                             small */
#define CL_JPEG_ERROR               (-12) /* JPEG data is corrupt */
#define CL_BAD_FRAME_SIZE           (-13) /* frame size invalid */
#define CL_PARAM_OUT_OF_RANGE       (-14) /* parameter out of range */
#define CL_ADDED_ALGORITHM_ERROR    (-15) /* added algorithm had a unique 
                                             error */
#define CL_BAD_ALGORITHM_TYPE       (-16) /* bad algorithm type */
#define CL_BAD_ALGORITHM_NAME       (-17) /* bad algorithm name */
#define CL_BAD_BUFFERING            (-18) /* bad buffering calls */
#define CL_BUFFER_NOT_CREATED       (-19) /* buffer not created */
#define CL_BAD_BUFFER_EXISTS        (-20) /* buffer already created */
#define CL_BAD_INTERNAL_FORMAT      (-21) /* invalid internal format */
#define CL_BAD_BUFFER_POINTER       (-22) /* invalid buffer pointer */
#define CL_FRAME_BUFFER_SIZE_ZERO   (-23) /* frame buffer has zero size */
#define CL_BAD_STREAM_HEADER        (-24) /* invalid stream header */

#define CL_BAD_LICENSE              (-25) /* netls license not valid */
#define CL_AWARE_ERROR              (-26) /* error from Aware audio codec*/

#define CL_BAD_BUFFER_SIZE_POINTER  (-27) /* invalid buffer size pointer */
#define CL_BAD_BUFFER_SIZE          (-28) /* invalid buffer size */
#define CL_BAD_BUFFER_TYPE          (-29) /* invalid buffer type */
#define CL_BAD_HEADER_SIZE          (-30) /* invalid header size */
#define CL_BAD_FUNCTION_POINTER     (-31) /* null function pointer */
#define CL_BAD_SCHEME_POINTER       (-32) /* null scheme pointer */
#define CL_BAD_STRING_POINTER       (-33) /* null string pointer */
#define CL_BAD_MIN_GT_MAX           (-33) /* min greater than max */
#define CL_BAD_INITIAL_VALUE        (-34) /* bad initial value */
#define CL_BAD_PARAM_ID_POINTER     (-35) /* bad arg to clAddParam */
#define CL_BAD_PARAM_TYPE           (-36) /* bad arg to clAddParam */
#define CL_BAD_TEXT_STRING_PTR      (-37) /* bad arg to clAddParam */
#define CL_BAD_FUNCTIONALITY        (-38) /* bad arg to clQueryLicense */
#define CL_BAD_NUMBER_OF_BLOCKS     (-39) /* bad arg to clCreateBuf */
#define CL_BAD_BLOCK_SIZE           (-40) /* bad arg to clCreateBuf */
#define CL_BAD_POINTER              (-41) /* bad pointer*/
#define CL_BAD_BOARD                (-42) /* invalid board details*/
#define CL_MVC2_ERROR               (-43) /* error in MVC2 operation */
#define CL_NEXT_NOT_AVAILABLE       (-44) /* no image ready
						      (clGetNextImageInfo) */
#define CL_SCHEME_BUSY              (-45) /* resources required by
					     a scheme are in use */
#define CL_SCHEME_NOT_AVAILABLE     (-46) /* support for the requested scheme
					     is not installed */
#define CL_MPEG1_ERROR              (-47) /* error from MPEG1 scheme */
#define CL_ALGORITHM_TABLE_FULL	    (-48) /* can't add any more algorithms */
#define CL_DSO_ERROR                (-49) /* dso error */

/*************************************************************************** 
*
* Public Routine Prototypes
*
***************************************************************************/

/*
 * Processing Data (compress, decompress)
 */
int clOpenCompressor(int scheme, CLhandle *compressorHdl);
int clCompress(CLhandle compressorHdl, int numberOfFrames, 
    void *frameBuffer, int *compressedBufferSize, void *compressedBuffer);
int clCloseCompressor(CLhandle compressorHdl);

int clOpenDecompressor(int scheme, CLhandle *decompressorHdl);
int clDecompress(CLhandle decompressorHdl, int numberOfFrames, 
    int compressedBufferSize, void *compressedBuffer, void *frameBuffer);
int clCloseDecompressor(CLhandle decompressorHdl);

/*
 * Managing Implicit Buffers
 */
CLbufferHdl clCreateBuf(CLhandle handle, int bufferType, 
    int blocks, int blockSize, void **buffer);
int clDestroyBuf(CLbufferHdl bufferHdl);
CLbufferHdl clQueryBufferHdl(CLhandle handle, 
    int bufferType, void **buffer);
CLhandle clQueryHandle(CLbufferHdl bufferHdl);

int clQueryFree(CLbufferHdl bufferHdl, int freeAmount, 
    void **freeData, int *freeWrap);
int clUpdateHead(CLbufferHdl bufferHdl, int amountToAdd);
int clQueryValid(CLbufferHdl bufferHdl, int validAmount,
    void **validData, int *validWrap);
int clUpdateTail(CLbufferHdl bufferHdl, int amountToRelease);
int clDoneUpdatingHead(CLbufferHdl bufferHdl);

/*
 * Managing Parameters
 */
int clQueryParams(CLhandle handle, 
    int *paramValueBuffer, int bufferLength);
int clQueryParamsIntoDMparams(CLhandle handle,
			      DMparams *params );
int clGetParamID(CLhandle handle, char *paramName);

int clGetParams(CLhandle handle, 
    int *paramValueBuffer, int bufferLength);
int clSetParams(CLhandle handle, 
    int *paramValueBuffer, int bufferLength);
int clGetParam(CLhandle handle, int paramID);
int clSetParam(CLhandle handle, int paramID, int value);

int clGetDefault(CLhandle handle, int paramID);
int clGetMinMax(CLhandle handle, int paramID, int *min, int *max);
char *clGetName(CLhandle handle, int paramID);

/* 
 * Adding Algorithms and Parameters
 */ 
int clAddAlgorithm(char *name, int algType, int maxHeaderSize, 
    FunctionPtr openCompressor, FunctionPtr compress, 
    FunctionPtr closeCompressor, 
    FunctionPtr openDecompressor, FunctionPtr decompress, 
    FunctionPtr closeDecompressor, 
    FunctionPtr readHeader, FunctionPtr queryScheme, 
    FunctionPtr queryLicense, 
    FunctionPtr getParams, FunctionPtr setParams, 
    int *scheme);
void *clSetUnique(CLhandle handle, void *unique);
void *clGetUnique(CLhandle handle);
int  clFetchParam(CLhandle handle, int paramID);
void clStoreParam(CLhandle handle, int paramID, int value);
extern void (*clError)(CLhandle handle, int code, const char *format, ...);

int clAddParam(int scheme, char *name, int paramType, 
    int min, int max, int initial, int *paramID);
int clSetDefault(int scheme, int paramID, int initial);
int clSetMin(int scheme, int paramID, int min);
int clSetMax(int scheme, int paramID, int max);
int clSetMinMax(int scheme, int paramID, int min, int max);
int clSetRange(int scheme, int paramID, int min, int max, int initial);

/*
 * Other Features
 */
int clCompressImage(int scheme, int width, int height, 
    int format, float compressionRatio, void *frameBuffer, 
    int *compressedBufferSize, void *compressedBuffer);
int clDecompressImage(int scheme, int width, int height, 
    int format, int compressedBufferSize, 
    void *compressedBuffer, void *frameBuffer);

int clQueryAlgorithms(int algType, int *buffer, int bufferLength);
int clQuerySchemeFromHandle(CLhandle handle);
int clQuerySchemeFromName(int algType, const char *name);
int clQuerySchemeFromDMparams ( int algorithmType, DMparams *params );
char *clGetAlgorithmName(int scheme);
int clQueryLicense(int scheme, int functionality, char **message);

int clQueryScheme(void *header);
int clQueryMaxHeaderSize(int scheme);
int clReadHeader(CLhandle handle, int headerSize, void *header);

int clGetNextImageInfo(CLhandle handle, 
    CLimageInfo *imageInfo, int sizeOfImageInfo);

CLerrFunc clSetErrorHandler(CLerrFunc efunc);

/*************************************************************************** 
*
* Individual Header Files
*
***************************************************************************/

#include <dmedia/cl_aware.h>
#include <dmedia/cl_cosmo.h>
#include <dmedia/cl_jpeg.h>
#include <dmedia/cl_mpeg1.h>
#include <dmedia/cl_mvc2.h>
#include <dmedia/cl_mvc3.h>

/*************************************************************************** 
*
* Backwards Compatibility
*
***************************************************************************/

#include <dmedia/cl_back.h>

#ifdef __cplusplus
}
#endif

#endif  /* _INC_CL_H_ */
