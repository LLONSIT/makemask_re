/* $TOG: XineramaProto.h /main/4 1998/02/13 13:08:58 kaleb $ */
/****************************************************************
*                                                               *
*    Copyright (c) Digital Equipment Corporation, 1991, 1997    *
*                                                               *
*   All Rights Reserved.  Unpublished rights  reserved  under   *
*   the copyright laws of the United States.                    *
*                                                               *
*   The software contained on this media  is  proprietary  to   *
*   and  embodies  the  confidential  technology  of  Digital   *
*   Equipment Corporation.  Possession, use,  duplication  or   *
*   dissemination of the software and media is authorized only  *
*   pursuant to a valid written license from Digital Equipment  *
*   Corporation.                                                *
*                                                               *
*   RESTRICTED RIGHTS LEGEND   Use, duplication, or disclosure  *
*   by the U.S. Government is subject to restrictions  as  set  *
*   forth in Subparagraph (c)(1)(ii)  of  DFARS  252.227-7013,  *
*   or  in  FAR 52.227-19, as applicable.                       *
*                                                               *
*****************************************************************/

/* THIS IS NOT AN X PROJECT TEAM SPECIFICATION */

#ifndef _XINERAMAPROTO_H_
#define _XINERAMAPROTO_H_

#include <X11/Xmd.h>        /* CARD32, etc. */

/* make sure types have right sizes for protocol structures. */
#undef WINDOW
#undef DRAWABLE
#define WINDOW CARD32
#define DRAWABLE CARD32

#define XINERAMA_PROTOCOL_NAME "XINERAMA"
#define SGI_XINERAMA_PROTOCOL_NAME "SGI-XINERAMA"

/* Current version numbers */
#define XINERAMA_MAJOR_VERSION          1
#define XINERAMA_MINOR_VERSION          2

/* Current SGI-specific API version numbers */
#define SGI_XINERAMA_MAJOR_VERSION          1
#define SGI_XINERAMA_MINOR_VERSION          3


/* Xinerama Xorg public protocol packet IDs. To be finalized. */
#define X_XineramaQueryVersion          0
#define X_XineramaActive                1
#define X_XineramaGetData               2  /* XOrg 1.2 compliant changes*/
#define X_XineramaGetCenterHint         3



/* SGI internal protocol packet IDs, starting at 100. Internal use only ! */
#define X_SGIXineramaQueryVersion          100
#define X_SGIXineramaActive                101
#define X_SGIXineramaGetData               102  /* XOrg 1.2 compliant changes*/
#define X_SGIXineramaGetCenterHint         103

/* SGI private protocol packet IDs, starting at 128. Internal use only ! */
#define X_SGIXineramaGetFullData           128  /* XOrg 1.2 compliant changes*/
#define X_SGIXineramaGetDrawableGeometry   129
#define X_SGIXineramaQuerySibling          130
#define X_SGIXineramaGetVisualData         131
#define X_SGIXineramaGetFBConfigData       132
#define X_SGIXineramaManageAwareClients    133
#define X_SGIXineramaHasSibling            134

/* Deprecated protocol packet IDs. */
#define X_XineramaGetState              200
#define X_XineramaGetScreenCount        201
#define X_XineramaGetScreenSize         202
#define X_XineramaGetScreenGeometry     203


typedef struct _XineramaQueryVersion {
	CARD8	reqType;		/* always XineramaReqCode */
	CARD8	xineramaReqType;	/* always X_XineramaQueryVersion */
	CARD16	length B16;
	CARD16	clientMajor;
	CARD16	clientMinor;
} xXineramaQueryVersionReq;
#define sz_xXineramaQueryVersionReq	8

typedef struct {
	CARD8	type;			/* must be X_Reply */
	CARD8	pad1;			/* unused	*/
	CARD16	sequenceNumber  B16;	/* last sequence number */
	CARD32	length  B32;		/* 0 */
	CARD16	majorVersion  B16;	
	CARD16	minorVersion  B16;	
	CARD32	pad2	B32;		/* unused */
	CARD32	pad3	B32;		/* unused */
	CARD32	pad4	B32;		/* unused */
	CARD32	pad5	B32;		/* unused */
	CARD32	pad6	B32;		/* unused */
} xXineramaQueryVersionReply;
#define sz_xXineramaQueryVersionReply	32


typedef	struct _XineramaActive {
        CARD8   reqType;	        /* always XineramaReqCode */
        CARD8   xineramaReqType;    	/* always X_XineramaActive */
        CARD16  length B16;
	WINDOW  window B32;
} xXineramaActiveReq;
#define sz_xXineramaActiveReq	8	

typedef struct {
	BYTE	type;
	CARD8	pad1;			/* unused */
	CARD16	sequenceNumber B16;
	CARD32	length	B32;		/* 0 */
	BOOL	active;
	CARD8	pad2;			/* unused */
	CARD16	pad3	B16;		/* unused */
	CARD32	pad4	B32;		/* unused */
	CARD32	pad5	B32;		/* unused */
	CARD32	pad6	B32;		/* unused */
	CARD32	pad7	B32;		/* unused */
	CARD32	pad8	B32;		/* unused */
} xXineramaActiveReply;
#define sz_xXineramaActiveReply	32


typedef	struct _XineramaGetData {
        CARD8   reqType;	        /* always XineramaReqCode */
        CARD8   xineramaReqType;    	/* always X_XineramaGetData */
        CARD16  length B16;
	WINDOW  window B32;
} xXineramaGetDataReq;
#define sz_xXineramaGetDataReq	8	

typedef struct {
	BYTE	type;
	CARD8	pad1;
	CARD16	sequenceNumber B16;
	CARD32	length	B32;
	CARD32  numRects       B32;
	CARD32	pad2	B32;		/* unused */
	CARD32	pad3	B32;		/* unused */
	CARD32	pad4	B32;		/* unused */
	CARD32	pad5	B32;		/* unused */
	CARD32	pad6	B32;		/* unused */
} xXineramaGetDataReply;
#define sz_xXineramaGetDataReply	32
/*ToF: Following the reply header, there are
 * numRects * sizeof(XRectangle) bytes of data following.
 */


typedef	struct _XineramaGetCenterHint {
        CARD8   reqType;	        /* always XineramaReqCode */
        CARD8   xineramaReqType;    	/* always X_XineramaGetCenterHint */
        CARD16  length B16;
	WINDOW  window B32;
} xXineramaGetCenterHintReq;
#define sz_xXineramaGetCenterHintReq	8	

typedef struct {
	BYTE	type;
	CARD8	pad1;
	CARD16	sequenceNumber B16;
	CARD32	length	B32;		/* 0 */
	INT16   x       B32;
	INT16	y	B32;
	CARD32	pad2	B32;		/* unused */
	CARD32	pad3	B32;		/* unused */
	CARD32	pad4	B32;		/* unused */
	CARD32	pad5	B32;		/* unused */
	CARD32	pad6	B32;		/* unused */
} xXineramaGetCenterHintReply;
#define sz_xXineramaGetCenterHintReply	32


/****************************************************************************
 * SGI internal Xinerama protocol                                           *
 ****************************************************************************/

typedef xXineramaQueryVersionReq xSGIXineramaQueryVersionReq;
#define sz_xSGIXineramaQueryVersionReq	8

typedef xXineramaQueryVersionReply xSGIXineramaQueryVersionReply;
#define sz_xSGIXineramaQueryVersionReply	32

typedef	xXineramaActiveReq xSGIXineramaActiveReq;
#define sz_xSGIXineramaActiveReq	8	

typedef xXineramaActiveReply xSGIXineramaActiveReply;
#define sz_xSGIXineramaActiveReply	32

typedef	xXineramaGetDataReq xSGIXineramaGetDataReq;
#define sz_xSGIXineramaGetDataReq	8	

typedef xXineramaGetDataReply xSGIXineramaGetDataReply;
#define sz_xSGIXineramaGetDataReply	32

typedef	xXineramaGetCenterHintReq xSGIXineramaGetCenterHintReq;
#define sz_xSGIXineramaGetCenterHintReq	8	

typedef xXineramaGetCenterHintReply xSGIXineramaGetCenterHintReply;
#define sz_xSGIXineramaGetCenterHintReply	32


typedef	struct _SGIXineramaQuerySibling {
        CARD8   reqType;                /* always SGIXineramaReqCode */
        CARD8   xineramaReqType;	/* always X_SGIXineramaQuerySibling */
        CARD16  length B16;
	DRAWABLE drawable B32;
} xSGIXineramaQuerySiblingReq;
#define sz_xSGIXineramaQuerySiblingReq	8	

typedef struct {
	BYTE	type;
	CARD8	pad1;
	CARD16	sequenceNumber B16;
	CARD32	length	B32;
	DRAWABLE drawable B32;
	CARD32  numSiblings B32; /* return number of screens */
	CARD32	pad2	B32;		/* unused */
	CARD32	pad3	B32;		/* unused */
	CARD32	pad4	B32;		/* unused */
	CARD32	pad5	B32;		/* unused */
} xSGIXineramaQuerySiblingReply;
#define sz_xSGIXineramaQuerySiblingReply 32
/*ToF: Following the reply header, there are
 * numSiblings * sizeof(DRAWABLE) bytes of data following.
 */


typedef	struct _SGIXineramaGetVisualData {
        CARD8   reqType;                /* always SGIXineramaReqCode */
        CARD8   xineramaReqType;	/* always X_SGIXineramaGetVisualData */
        CARD16  length B16;
	WINDOW  window B32;
} xSGIXineramaGetVisualDataReq;
#define sz_xSGIXineramaGetVisualDataReq	8

typedef struct {
	BYTE	type;
	CARD8	pad1;
	CARD16	sequenceNumber B16;
	CARD32	length	B32;
	CARD32	nscreens B32;
	CARD32	nconfigs B32;
	CARD32	nattribs B32;
	CARD32	pad2	B32;		/* unused */
	CARD32	pad3	B32;		/* unused */
	CARD32	pad4	B32;		/* unused */
} xSGIXineramaGetVisualDataReply;
#define sz_xSGIXineramaGetVisualDataReply 32
/*
 * Claude: Following the reply header, there are
 * nscreens*nconfigs*sizeof(CARD32) +
 * nconfigs*nattribs*2*sizeof(CARD32) bytes of data following.
 */


typedef	struct _SGIXineramaGetFBConfigData {
        CARD8   reqType;                /* always SGIXineramaReqCode */
        CARD8   xineramaReqType;	/* always X_SGIXineramaGetFBConfigData */
        CARD16  length B16;
	WINDOW  window B32;
} xSGIXineramaGetFBConfigDataReq;
#define sz_xSGIXineramaGetFBConfigDataReq	8

typedef struct {
	BYTE	type;
	CARD8	pad1;
	CARD16	sequenceNumber B16;
	CARD32	length	B32;
	CARD32	nscreens B32;
	CARD32	nconfigs B32;
	CARD32	nattribs B32;
	CARD32	pad2	B32;		/* unused */
	CARD32	pad3	B32;		/* unused */
	CARD32	pad4	B32;		/* unused */
} xSGIXineramaGetFBConfigDataReply;
#define sz_xSGIXineramaGetFBConfigDataReply 32
/*
 * Claude: Following the reply header, there are
 * nscreens*nconfigs*sizeof(CARD32) +
 * nconfigs*nattribs*2*sizeof(CARD32) bytes of data following.
 */


typedef	struct _SGIXineramaGetDrawableGeometry {
        CARD8   reqType;                /* always SGIXineramaReqCode */
        CARD8   xineramaReqType;	/* always X_SGIXineramaGetDrawableGeometry */
        CARD16  length B16;
	CARD32	drawable B32;
} xSGIXineramaGetDrawableGeometryReq;
#define sz_xSGIXineramaGetDrawableGeometryReq	8	

typedef struct {
	BYTE	type;
	CARD8	pad1;			
	CARD16	sequenceNumber B16;
	CARD32	length	B32;
	CARD32	x	B32;
	CARD32	y	B32;
	CARD32	width	B32;
	CARD32	height	B32;
	CARD32	pad2	B32;		/* unused */
	CARD32	pad3	B32;		/* unused */
} xSGIXineramaGetDrawableGeometryReply;
#define sz_xSGIXineramaGetDrawableGeometryReply 32	


typedef	struct _SGIXineramaGetFullData {
        CARD8   reqType;	        /* always SGIXineramaReqCode */
        CARD8   xineramaReqType;    	/* always X_SGIXineramaGetFullData */
        CARD16  length B16;
	WINDOW  window B32;
} xSGIXineramaGetFullDataReq;
#define sz_xSGIXineramaGetFullDataReq	8

typedef struct {
	BYTE	type;
	CARD8	pad1;
	CARD16	sequenceNumber B16;
	CARD32	length	B32;
	CARD32  numRects       B32;
	CARD32	pad2	B32;		/* unused */
	CARD32	pad3	B32;		/* unused */
	CARD32	pad4	B32;		/* unused */
	CARD32	pad5	B32;		/* unused */
	CARD32	pad6	B32;		/* unused */
} xSGIXineramaGetFullDataReply;
#define sz_xSGIXineramaGetFullDataReply	32
/*ToF: Following the reply header, there are
 * 2 * numRects * sizeof(XRectangle) bytes of data following.
 */


typedef	struct _SGIXineramaManageAwareClients {
        CARD8   reqType;                /* always SGIXineramaReqCode */
        CARD8   xineramaReqType;	/* always X_SGIXineramaManageAwareClients */
        CARD16  length B16;
	CARD32  nWins B32;
} xSGIXineramaManageAwareClientsReq;
#define sz_xSGIXineramaManageAwareClientsReq	8
/*wjf: Following the request header, there are
 * 2 * nWins * sizeof(WINDOW) bytes of data.
 */

typedef struct {
	BYTE	type;
	CARD8	pad1;
	CARD16	sequenceNumber B16;
	CARD32	length	B32;		/* 0 */
        CARD16  pad2    B16;		/* unused */
	INT16   numManaged;		/* number of managed screens */
	CARD32  pad3    B32;		/* unused */
	CARD32	pad4	B32;		/* unused */
	CARD32	pad5	B32;		/* unused */
	CARD32	pad6	B32;		/* unused */
	CARD32	pad7	B32;		/* unused */
} xSGIXineramaManageAwareClientsReply;
#define sz_xSGIXineramaManageAwareClientsReply 32


typedef	struct _SGIXineramaHasSibling {
        CARD8   reqType;                /* always SGIXineramaReqCode */
        CARD8   xineramaReqType;	/* always X_SGIXineramaHasSibling */
        CARD16  length B16;
	DRAWABLE drawable B32;
} xSGIXineramaHasSiblingReq;
#define sz_xSGIXineramaHasSiblingReq	8

typedef struct {
	BYTE	type;
	CARD8	pad1;
	CARD16	sequenceNumber B16;
	CARD32	length	B32;		/* 0 */
	BOOL    hasSibs;
	CARD8	pad2;			/* unused */
	CARD16	pad3	B16;		/* unused */
	CARD32  pad4    B32;		/* unused */
	CARD32	pad5	B32;		/* unused */
	CARD32	pad6	B32;		/* unused */
	CARD32	pad7	B32;		/* unused */
	CARD32	pad8	B32;		/* unused */
} xSGIXineramaHasSiblingReply;
#define sz_xSGIXineramaHasSiblingReply 32


/****************************************************************************
 *                                                                          *
 * Protocol for Deprecated Interfaces                                       *
 *                                                                          *
 ****************************************************************************/

/****************************************************************************
 * Protocol for deprecated public API                                       *
 ****************************************************************************/

typedef	struct _XineramaGetState {
        CARD8   reqType;	        /* always XineramaReqCode */
        CARD8   xineramaReqType;    	/* always X_XineramaGetState */
        CARD16  length B16;
	CARD32  window B32;
} xXineramaGetStateReq;
#define sz_xXineramaGetStateReq	8	

typedef struct {
	BYTE	type;
	BYTE	state;
	CARD16	sequenceNumber B16;
	CARD32	length	B32;
	CARD32  window  B32;
	CARD32	pad1	B32;		/* unused */
	CARD32	pad2	B32;		/* unused */
	CARD32	pad3	B32;		/* unused */
	CARD32	pad4	B32;		/* unused */
	CARD32	pad5	B32;		/* unused */
} xXineramaGetStateReply;
#define sz_xXineramaGetStateReply	32


typedef	struct _XineramaGetScreenCount {
        CARD8   reqType;                /* always XineramaReqCode */
        CARD8   xineramaReqType;        /* always X_XineramaGetScreenCount */
        CARD16  length B16;
	CARD32  window B32;
} xXineramaGetScreenCountReq;
#define sz_xXineramaGetScreenCountReq	8

typedef struct {
	BYTE	type;
	BYTE	ScreenCount;
	CARD16	sequenceNumber B16;
	CARD32	length B32;
	CARD32  window  B32;
	CARD32	pad1	B32;		/* unused */
	CARD32	pad2	B32;		/* unused */
	CARD32	pad3	B32;		/* unused */
	CARD32	pad4	B32;		/* unused */
	CARD32	pad5	B32;		/* unused */
} xXineramaGetScreenCountReply;
#define sz_xXineramaGetScreenCountReply	32


typedef	struct _XineramaGetScreenSize {
        CARD8   reqType;                /* always XineramaReqCode */
        CARD8   xineramaReqType;	/* always X_XineramaGetScreenSize */
        CARD16  length B16;
	CARD32  window B32;
	CARD32	screen B32;
} xXineramaGetScreenSizeReq;
#define sz_xXineramaGetScreenSizeReq	12	

typedef struct {
	BYTE	type;
	CARD8	pad1;			
	CARD16	sequenceNumber B16;
	CARD32	length	B32;
	CARD32	width	B32;
	CARD32	height	B32;
	CARD32  window  B32;
	CARD32  screen  B32;
	CARD32	pad2	B32;		/* unused */
	CARD32	pad3	B32;		/* unused */
} xXineramaGetScreenSizeReply;
#define sz_xXineramaGetScreenSizeReply 32	


/****************************************************************************
 * Protocol for deprecated SGI internal API                                 *
 ****************************************************************************/

typedef	struct _XineramaGetScreenGeometry {
        CARD8   reqType;                /* always XineramaReqCode */
        CARD8   xineramaReqType;	/* always X_XineramaGetScreenGeometry */
        CARD16  length B16;
	CARD32	screen B32;
} xXineramaGetScreenGeometryReq;
#define sz_xXineramaGetScreenGeometryReq	8	

typedef struct {
	BYTE	type;
	CARD8	pad1;			
	CARD16	sequenceNumber B16;
	CARD32	length	B32;
	CARD32	x	B32;
	CARD32	y	B32;
	CARD32	width	B32;
	CARD32	height	B32;
	CARD32	pad2	B32;		/* unused */
	CARD32	pad3	B32;		/* unused */
} xXineramaGetScreenGeometryReply;
#define sz_xXineramaGetScreenGeometryReply 32	

#endif /* _XINERAMAPROTO_H_ */
