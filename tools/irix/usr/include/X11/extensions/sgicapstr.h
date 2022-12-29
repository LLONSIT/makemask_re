/************************************************************

Copyright (c) 1989  X Consortium

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
X CONSORTIUM BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of the X Consortium shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from the X Consortium.

********************************************************/

/* $XConsortium: sgicapstr.h,v 1.13 94/04/17 20:11:24 rws Exp $ */

#ifndef _SGICAPSTR_H_
#define _SGICAPSTR_H_

/*
 * Protocol requests constants and alignment values
 * These would really be in SGICAP's X.h and Xproto.h equivalents
 */

#include "sgicap.h"

#ifdef _SGICAP_SERVER_
extern RESTYPE RT_SGICapInterest;

typedef struct _SGICapInterest {
    ScreenPtr pScreen;
    BoxRec intBox; 
    Bool started;
    RegionPtr pDirtyRegion;
    struct _SGICapInterest *nextCapturing;
    BoxRec lastCursorBox; 
    int lastspritex;
    int lastspritey;
    Bool GLonly;
} SGICapInterest, *SGICapInterestPtr;

void SGICapCaptureGLWindows(
	SGICapInterestPtr pSI);

void SGICapStartCapture(
	SGICapInterestPtr pSI);

void SGICapStopCapture(
	SGICapInterestPtr pSI);

void SGICapValidateDirtyRegion(
	SGICapInterestPtr pSI);

#endif

#define Drawable CARD32
#define Time CARD32
#define XID CARD32

#define SGICAPNAME "SGI-SCREEN-CAPTURE"

#define SGICAP_MAJOR_VERSION	1	/* current version numbers */
#define SGICAP_MINOR_VERSION	0

typedef struct _SGICapQueryVersion {
	CARD8	reqType;		/* always SGICapReqCode */
	CARD8	sgiCapReqType;		/* always X_SGICapQueryVersion */
	CARD16	length B16;
} xSGICapQueryVersionReq;
#define sz_xSGICapQueryVersionReq	4

typedef struct {
	BYTE	type;			/* X_Reply */
	CARD8	unused;			/* not used */
	CARD16	sequenceNumber B16;
	CARD32	length B32;
	CARD16	majorVersion B16;	/* major version of SGICAP protocol */
	CARD16	minorVersion B16;	/* minor version of SGICAP protocol */
	CARD32	pad0 B32;
	CARD32	pad1 B32;
	CARD32	pad2 B32;
	CARD32	pad3 B32;
	CARD32	pad4 B32;
} xSGICapQueryVersionReply;
#define sz_xSGICapQueryVersionReply	32

typedef struct _SGICapRegisterInterest {
	CARD8	reqType;	/* always SGICapReqCode */
	CARD8	sgiCapReqType;	/* always X_SGICapRegisterInterest */
	CARD16	length B16;
	Drawable drawable B32;
	INT16	x B16;
	INT16	y B16;
	CARD16	width B16;
	CARD16	height B16;
	XID	sgiCapInterest B32;
} xSGICapRegisterInterestReq;
#define sz_xSGICapRegisterInterestReq	20

typedef struct _SGICapStart {
	CARD8	reqType;	/* always SGICapReqCode */
	CARD8	sgiCapReqType;	/* always X_SGICapStart */
	CARD16	length B16;
	XID	sgiCapInterest B32;
} xSGICapStartReq;
#define sz_xSGICapStartReq	8
	
typedef struct _SGICapQueryAndReset {
    CARD8   reqType;		/* always SGICapReqCode */
    CARD8   sgiCapReqType;	/* always X_SGICapQueryAndReset */
    CARD16  length B16;
    XID     sgiCapInterest B32;
} xSGICapQueryAndResetReq;
#define sz_xSGICapQueryAndResetReq	8

typedef struct {
	BYTE	type;			/* X_Reply */
	CARD8	ordering;	/* UnSorted, YSorted, YXSorted, YXBanded */
	CARD16	sequenceNumber B16;
	CARD32	length B32;		/* not zero */
	CARD32	nrects B32;		/* number of rectangles */
	Time    time_return B32;
	CARD32 pad1 B32;
	CARD32 pad2 B32;
	CARD32 pad3 B32;
	CARD32 pad4 B32;
} xSGICapQueryAndResetReply;		/* followed by xRectangles */
#define sz_xSGICapQueryAndResetReply 32

typedef struct _SGICapStop {
	CARD8	reqType;	/* always SGICapReqCode */
	CARD8	sgiCapReqType;	/* always X_SGICapStop */
	CARD16	length B16;
	XID	sgiCapInterest B32;
} xSGICapStopReq;
#define sz_xSGICapStopReq	8
	
typedef struct _SGICapWithdrawInterest {
	CARD8	reqType;	/* always SGICapReqCode */
	CARD8	sgiCapReqType;	/* always X_SGICapWithdrawInterest */
	CARD16	length B16;
	XID	sgiCapInterest B32;
} xSGICapWithdrawInterestReq;
#define sz_xSGICapWithdrawInterestReq	8

typedef struct _SGICapQueryCopyAndReset {
    CARD8   reqType;		/* always SGICapReqCode */
    CARD8   sgiCapReqType;	/* always X_SGICapQueryCopyAndReset */
    CARD16  length B16;
    XID     sgiCapInterest B32;
    CARD16  width B16;
    CARD16  height B16;
    CARD32  shmseg B32;
    CARD32  offset B32;
} xSGICapQueryCopyAndResetReq;
#define sz_xSGICapQueryCopyAndResetReq	20

typedef struct {
	BYTE	type;			/* X_Reply */
	CARD8	ordering;	/* UnSorted, YSorted, YXSorted, YXBanded */
	CARD16	sequenceNumber B16;
	CARD32	length B32;		/* not zero */
	CARD32	nrects B32;		/* number of rectangles */
	Time    time_return B32;
	CARD32 pad1 B32;
	CARD32 pad2 B32;
	CARD32 pad3 B32;
	CARD32 pad4 B32;
} xSGICapQueryCopyAndResetReply;	/* followed by xRectangles */
#define sz_xSGICapQueryCopyAndResetReply 32

#undef Drawable
#undef Time
#undef XID 

#endif /* _SGICAPSTR_H_ */
