#if !defined( __INC_DM_IMAGECONVERT_H__ )
#define __INC_DM_IMAGECONVERT_H__

/***************************************************************************
 * SGI Digital Media Library: Image Conversion Routines
 *
 * <dmedia/dm_imageconvert.h>
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

#include <dmedia/dmedia.h>
#include <dmedia/dm_params.h>
#include <dmedia/dm_buffer.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DM_IC_CODE_DIRECTION    "DM_IC_CODE_DIRECTION"

#define DM_IC_ID		"DM_IC_ID"
#define DM_IC_ENGINE 		"DM_IC_ENGINE"
#define DM_IC_SPEED 		"DM_IC_SPEED"
#define DM_IC_CODE_DIRECTION 	"DM_IC_CODE_DIRECTION"
#define DM_IC_VERSION 		"DM_IC_VERSION"
#define DM_IC_REVISION 		"DM_IC_REVISION"
#define DM_IC_THREADS 		"DM_IC_THREADS"

/*
 * enums
 */

typedef enum {
    DM_IC_SPEED_UNDEFINED,
    DM_IC_SPEED_REALTIME,
    DM_IC_SPEED_NONREALTIME
}DMicspeed;

typedef enum {
    DM_IC_THREADS_UNDEFINED,
    DM_IC_THREADS_ENABLED,
    DM_IC_THREADS_DISABLED
}DMicthreads;

typedef enum DMcodedirection{
    DM_IC_CODE_DIRECTION_UNDEFINED,
    DM_IC_CODE_DIRECTION_ENCODE,
    DM_IC_CODE_DIRECTION_DECODE
}DMcodedirection;

/*
 * typedef DMimageconverter
 */
typedef struct _DMimageconverter *DMimageconverter;

int	 dmICGetNum		( void );
DMstatus dmICGetDescription	( int i, DMparams *converterParams );
int	 dmICChooseConverter	( DMparams *srcParams, 
				  DMparams *dstParams,
				  DMparams *convParams );

DMstatus dmICCreate		( int i, DMimageconverter *converter );
void	 dmICDestroy		( DMimageconverter converter );

DMstatus dmICGetSrcParams	( DMimageconverter converter, DMparams *srcParams );
DMstatus dmICSetSrcParams	( DMimageconverter converter, DMparams *srcParams );
DMstatus dmICGetDefaultSrcParams( DMimageconverter converter, DMparams *srcParams );

DMstatus dmICGetDstParams	( DMimageconverter converter, DMparams *dstParams );
DMstatus dmICSetDstParams	( DMimageconverter converter, DMparams *dstParams );
DMstatus dmICGetDefaultDstParams( DMimageconverter converter, DMparams *dstParams );
 
DMstatus dmICGetConvParams	( DMimageconverter converter, DMparams *convParams );
DMstatus dmICSetConvParams	( DMimageconverter converter, DMparams *convParams );
DMstatus dmICGetDefaultConvParams( DMimageconverter converter, DMparams *convParams );

DMstatus dmICGetSrcPoolParams	( DMimageconverter converter, DMparams *poolParams );
DMstatus dmICGetDstPoolParams	( DMimageconverter converter, DMparams *poolParams );
DMstatus dmICSetDstPool		( DMimageconverter converter, DMbufferpool pool );

int 	 dmICGetDstQueueFD	( DMimageconverter converter );
int 	 dmICGetSrcQueueFilled	( DMimageconverter converter );
int 	 dmICGetDstQueueFilled	( DMimageconverter converter );

DMstatus dmICSend		( DMimageconverter converter, DMbuffer srcBuffer, 
				  int numRefBuffers, DMbuffer *refBuffers );
DMstatus dmICWork		( DMimageconverter converter, int *status, 
				  int *n_input_dequeued, int *n_output_enqueued );
DMstatus dmICReceive		( DMimageconverter converter, DMbuffer *dstBuffer );

DMstatus dmICAnyToAny		( void *src, void *dst,
				  DMparams *srcParams, DMparams *dstParams, 
				  DMparams *convParams );

int      dmICFindCustom		( unsigned long fourcc,
				  DMcodedirection direction );

#pragma optional dmICFindCustom

/*
 * dmIC error codes
 */
#define DM_IC_INVALID_INDEX	DM_IC_EBASE+1	/* "Invalid dmIC index" */
#define DM_IC_INVALID_VALUE	DM_IC_EBASE+2	/* "Invalid value" */
#define DM_IC_INSUFFICIENT_PARAMS DM_IC_EBASE+3 /* "Insufficient parameter list" */
#define DM_IC_CONVERTER_NOT_FOUND DM_IC_EBASE+4 /* "Converter Not Found" */
#define DM_IC_FUNCTION_UNIMPLEMENTED DM_IC_EBASE+5 /* "Function unimplemented" */
#define DM_IC_Q_EMPTY		DM_IC_EBASE+6	/* "Queue is Empty" */
#define DM_IC_COMPRESS_FAILED	DM_IC_EBASE+7	/* "Compress failed" */
#define DM_IC_DECOMPRESS_FAILED	DM_IC_EBASE+8   /* "Decompress failed" */
#define DM_IC_UNSUPPORTED_PACKING DM_IC_EBASE+9   /* "Unsupported packings" */

/*
 * dmIC "Work" function status bit flags
 */
#define DM_IC_WORK_NO_STATUS	0	/* No Work Status */
#define DM_IC_WORK_ERROR	(1<<1)	/* An error occurred */
#define DM_IC_WORK_NOT_NEEDED	(1<<2)	/* This codec doesn't use dmICWork() */
#define DM_IC_WORK_INSUFFICIENT_INPUT_DATA (1<<3)   /* not enough input yet */
#define DM_IC_WORK_INSUFFICIENT_OUTPUT_SPACE (1<<4) /* not enough output space*/

#ifdef __cplusplus 
}
#endif

#endif /* __INC_DM_IMAGECONVERT_H__ */
