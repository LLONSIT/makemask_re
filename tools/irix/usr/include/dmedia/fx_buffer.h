/***********************************************************************
**
** fx_buffer.h
**	
**	Buffer management for applications that use image processing
**      plug-ins.
**
** Copyright 1995, Silicon Graphics, Inc.
** ALL RIGHTS RESERVED
**
** UNPUBLISHED -- Rights reserved under the copyright laws of the United
** States.   Use of a copyright notice is precautionary only and does not
** imply publication or disclosure.
**
** U.S. GOVERNMENT RESTRICTED RIGHTS LEGEND:
** Use, duplication or disclosure by the Government is subject to restrictions
** as set forth in FAR 52.227.19(c)(2) or subparagraph (c)(1)(ii) of the Rights
** in Technical Data and Computer Software clause at DFARS 252.227-7013 and*or
** in similar or successor clauses in the FAR, or the DOD or NASA FAR
** Supplement.  Contractor*manufacturer is Silicon Graphics, Inc.,
** 2011 N. Shoreline Blvd. Mountain View, CA 94039-7311.
**
** THE CONTENT OF THIS WORK CONTAINS CONFIDENTIAL AND PROPRIETARY
** INFORMATION OF SILICON GRAPHICS, INC. ANY DUPLICATION, MODIFICATION,
** DISTRIBUTION, OR DISCLOSURE IN ANY FORM, IN WHOLE, OR IN PART, IS STRICTLY
** PROHIBITED WITHOUT THE PRIOR EXPRESS WRITTEN PERMISSION OF SILICON
** GRAPHICS, INC.
**
***********************************************************************/

#ifndef _DM_FX_BUFFER_H
#define _DM_FX_BUFFER_H

#include <dmedia/dm_params.h>	/* DMparams */
#include <dmedia/fx_utils.h>	/* General stuff for libfxplugutils */
#include <dmedia/moviefile.h>	/* MVtimescale, MVtime */
#include "PremiereXAPI.h"	/* PRX_ScanlineBuffer */

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************
**
** Buffer management functions
**
** These are used by the plug-in manager to set up buffers for
** plug-ins, or directly by applications that call plug-ins directly.
**
***********************************************************************/

typedef struct __FXbuffer DMfxbuffer;

extern DMstatus	dmFXAllocateImageBuffers(
    Display*		dpy,
    const DMparams*	imageFormat,
    int             	inputUsage,
    int             	outputUsage,
    int             	numberOfBuffers,
    DMfxbuffer*       	returnBuffers[]
    );

extern void dmFXFreeImageBuffers(
    int             	numberOfBuffers,
    DMfxbuffer*       	buffers[]
    );

extern DMstatus dmFXMovieRenderImage(
    MVid            	movie,
    MVtime          	time,
    MVtimescale     	timeScale,
    int             	inputUsage,
    DMfxbuffer*      	destinationBuffer
    );

extern DMstatus dmFXMovieInsertImage(
    MVid 		track,
    MVtime 		time,
    MVtime 		duration,
    MVtimescale 	timeScale,
    DMfxbuffer*		buffer
    );

extern DMstatus dmFXSetupInputImageBuffer(
    DMfxbuffer*         sourceBuffer
    );

extern DMstatus dmFXSetupInputImageBufferWithUsage(
    int			inputUsage,
    DMfxbuffer*         sourceBuffer
    );

extern DMstatus dmFXSetupOutputImageBuffer(
    int			outputUsage,
    int                	inputUsage,
    DMfxbuffer*		destinationBuffer
    );

extern void* dmFXGetDataPtr(
    DMfxbuffer*		buffer
    );

extern int dmFXGetRowLength(
    DMfxbuffer*		buffer
    );

extern DMstatus dmFXSetupScanlineBuffer(
    DMfxbuffer*         buffer,
    PRX_ScanlineBuffer 	scanlineBuf
    );

extern DMstatus dmFXCleanupInputImageBuffer(
    DMfxbuffer*       	buffer
    );

extern DMstatus dmFXCheckOutputImageBufferState(
    DMfxbuffer*       	buffer
    );

extern DMstatus dmFXCleanupOutputImageBuffer(
    DMfxbuffer*       	buffer
    );

extern DMstatus dmFXGetDMBuffer(
    DMfxbuffer*		buffer,
    DMbuffer*		returnDMBuffer,
    DMparams**		returnFormat
    );


/*
 * Field processing:
 */ 

extern DMparams* dmFXGetBufferFormat(
    DMfxbuffer*         buffer
    );

extern DMstatus dmFXUpdateImageBuffer(
    const DMparams      *imageFormat,
    DMfxbuffer          *buffer
    );

extern DMstatus dmFXUpdateImageBuffers(
    const DMparams      *imageFormat,
    int			numberOfBuffers,
    DMfxbuffer		*buffers[]
    );

extern DMstatus dmFXMovieRenderFields(
    MVid        movie,
    MVtime      time,
    MVtimescale timeScale,
    int         inputUsage,
    DMfxbuffer  *field1,
    DMfxbuffer  *field2
    );

extern DMstatus dmFXMovieInsertFields(
    MVid        track,
    MVtime      time,
    MVtime      duration,
    MVtimescale timeScale,
    DMfxbuffer  *hiField,
    DMfxbuffer  *loField
    );

extern DMstatus dmFXSplitFields(
    int		inputUsage,
    DMfxbuffer  *srcFrame,
    DMfxbuffer  *field1,
    DMfxbuffer  *field2
    );

extern DMstatus dmFXJoinFields(
    int		inputUsage,
    DMfxbuffer	*field1,
    DMfxbuffer	*field2,
    DMfxbuffer	*dstFrame
    );

    
/**********************************************************************
*
* Rendering functions that use FXbuffers
*
* These all take FXbuffers indirectly by taking a PRX_ScanlineBuffer
* that was created with dmFXSetupScanlineBuffer.
*
**********************************************************************/

DMstatus dmFXDrawPixels(
    PRX_ScanlineBuffer	dest,		/* where to draw it */
    int			xPosition,	/* lower-left pixel */
    int			yPosition,	/* lower-left pixel */
    PRX_ScanlineBuffer	source,		/* what image to draw */
    GLsizei		xOffset,
    GLsizei		yOffset,
    GLsizei		width,
    GLsizei		height
    );

DMstatus dmFXTexImage2D(
    PRX_ScanlineBuffer	dest,		/* where it will be drawn */
    PRX_ScanlineBuffer	source,
    DMboolean		mipmap
    );


DMstatus dmFXConvolve(
    PRX_ScanlineBuffer	dest,		/* where to draw it */
    PRX_ScanlineBuffer	src,		/* what image to draw convolved  */
    int 		matrixW,	/* width of convolve matrix */
    int 		matrixH, 	/* height of convolve matrix */
    const GLfloat* 	matrix,		/* mW*mH coeffcients, offset, scale */
    const GLfloat	bias,		/* post convolution bias (offset) */
    const GLfloat	scale		/* post convolution scale */
    );

DMstatus dmFXScaleBias(
    PRX_ScanlineBuffer	dest,		/* where to draw it */
    PRX_ScanlineBuffer	src,		/* what image to draw convolved  */
    const GLfloat	redScale,	/* multiply red components by this */
    const GLfloat	redBias,	/* then add this to red components */
    const GLfloat	greenScale,	/* multiply green components by this */
    const GLfloat	greenBias,	/* then add this to green components */
    const GLfloat	blueScale,	/* multiply blue components by this */
    const GLfloat	blueBias,	/* then add this to blue components */
    const GLfloat	alphaScale,	/* multiply alpha components by this */
    const GLfloat	alphaBias	/* then add this to alpha components */
    );

DMstatus dmFXMatrixMultiply(
    PRX_ScanlineBuffer	dest,		/* where to draw it */
    PRX_ScanlineBuffer	src,		/* what image to draw  */
    const GLfloat* 	coeff,		/* 16 matrix coeffcients */
    const GLfloat	bias,		/* add this to to each pixel comp */
    const GLfloat	scale		/* multiply each pixel comp by this */
    );

DMboolean dmFXIsGLExtensionSupported(
    PRX_ScanlineBuffer	buffer,
    const char		*extension);

#ifdef __cplusplus
}
#endif

#endif /* _DM_FX_BUFFER_H */
