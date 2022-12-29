/**********************************************************
  Copyright c(encircled) 1991 Silicon Graphics, Inc.  ALL RIGHTS RESERVED.
  UNPUBLISHED -- Rights reserved under the copyright laws of the United
  States.   Use of a copyright notice is precautionary only and does not
  imply publication or disclosure.

  U.S. GOVERNMENT RESTRICTED RIGHTS LEGEND
  Use, duplication or disclosure by the Government is subject to
  restrictions as set forth in FAR 52.227.19(c)(2) or subparagraph
  (c)(1)(ii) of the Rights in Technical Data and Computer Software clause
  at DFARS 252.227-7013 and/or in similar or successor clauses in the FAR,
  or the DOD or NASA FAR Supplement. Contractor/manufacturer is Silicon
  Graphics, Inc., 2011 N. Shoreline Blvd., Mountain View, CA 94039-7311.

  THIS SOFTWARE CONTAINS CONFIDENTIAL AND PROPRIETARY INFORMATION OF
  SILICON GRAPHICS, INC. ANY DUPLICATION, MODIFICATION, DISTRIBUTION, OR
  DISCLOSURE IS STRICTLY PROHIBITED WITHOUT THE PRIOR EXPRESS WRITTEN
  PERMISSION OF SILICON GRAPHICS, INC.

***********************************************************/

#ifndef _XSGIVCPROTO_H_
#define _XSGIVCPROTO_H_

#include <X11/Xmd.h>

/* Current version numbers */
#define XSGIVC_MAJOR_VERSION	1
#define XSGIVC_MINOR_VERSION	3

	/****************************************************************
	 *  SGI VIDEO CONTROL EXTENSION REQUESTS AND REPLIES STRUCTURES
	 ****************************************************************/
/*---------------------------------
 *	SGIvcQueryVersion
 */
typedef struct _xSGIvcQueryVersion {
    CARD8	reqType;
    CARD8	xsgivcReqType;	/* always X_SGIvcQueryVersion */
    CARD16	length B16;
    CARD16	clientMajorVersion B16;
    CARD16	clientMinorVersion B16;
} xSGIvcQueryVersionReq;
#define sz_xSGIvcQueryVersionReq	8

typedef struct _xSGIvcQueryVersionReply {
    BYTE	type;		/* X_Reply */
    CARD8	pad1;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD16	serverMajorNumber B16;
    CARD16	serverMinorNumber B16;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
    CARD32	pad6 B32;
} xSGIvcQueryVersionReply;
#define sz_xSGIvcQueryVersionReply	32


/*---------------------------------
 *	SGIvcQueryVideoScreenInfo
 */
typedef struct _xSGIvcQueryVideoScreenInfo {
    CARD8	reqType;
    CARD8	xsgivcReqType;  /* always X_SGIvcQueryVideoScreenInfo */
    CARD16	length B16;
    CARD32	screen B32;
} xSGIvcQueryVideoScreenInfoReq;
#define sz_xSGIvcQueryVideoScreenInfoReq 8

typedef struct _xSGIvcQueryVideoScreenInfoReply {
    BYTE	type;           /* X_Reply */
    BOOL	implemented;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD32	nchannels B32;
    CARD32	flags B32;
    BOOL	lockAvail;
    BYTE	pad1;
    CARD16	pad2 B16;
    CARD32	pad3 B32;	/* In XSGIvc 1.1 used for returning num of 
				   external sync ports */
    CARD32	pad4 B32;
    CARD32	pad5 B32;
} xSGIvcQueryVideoScreenInfoReply;
#define sz_xSGIvcQueryVideoScreenInfoReply	32


/*---------------------------------
 *	SGIvcListVideoFormats
 */
typedef struct _xSGIvcListVideoFormats {
    CARD8	reqType;
    CARD8	xsgivcReqType;	/* always X_SGIvcListVideoFormats */
    CARD16	length B16;
    CARD32	screen B32;
    CARD32	channel B32;
    CARD8	matchMonitor;
    CARD8	pad1;
    CARD16	pad2 B16;
    CARD32	maxFormats B32;
    CARD32	mask B32;
} xSGIvcListVideoFormatsReq;
#define sz_xSGIvcListVideoFormatsReq	24

typedef struct _xSGIvcListFormatsReply {
    BYTE	type;		/* X_Reply */
    BOOL	implemented;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD32	actualCount B32;
    CARD32	nfinfo B32;
    CARD32	pad1 B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
} xSGIvcListFormatsReply;
#define sz_xSGIvcListFormatsReply	32

typedef struct _xsgivcHTimeDesc {
    INT32	backPorch B32;
    INT32	sync B32;
    INT32	frontPorch B32;
    INT32	active B32;
} xsgivcHTimeDesc;
#define sz_xSGIvcHTimeDesc 16

typedef struct _xsgivcVTimeDesc {
    INT32	backPorch B32;
    INT32	sync B32;
    INT32	syncPulse B32;
    INT32	frontPorch B32;
    INT32	active B32;
} xsgivcVTimeDesc;
#define sz_xSGIvcVTimeDesc	20

typedef struct _xsgivcFieldInfoDesc {
    INT32	offset B32;
    INT32	stride B32;
    xsgivcVTimeDesc vDuration;
    CARD32	colEyeActive B32;
    CARD32	eyeActive B32;
} xsgivcFieldInfoDesc;
#define sz_xSGIvcFieldInfoDesc	36

typedef struct _xsgivcFormatInfo {
    INT16	width	B16;
    INT16	height	B16;
    INT16	totWidth B16;
    INT16	totHeight B16;
    CARD32	vRetraceRate	B32; /* float value * 1000  cast to integer value */
    CARD32	swapBufferRate	B32; /* float value * 1000  cast to integer value */
    CARD32	pixelClock	B32;
    xsgivcHTimeDesc hDuration;
    CARD32	formatFlags	B32;
    CARD32	nameLength B32;
    CARD32	fieldCount B32;
} xsgivcFormatInfoDesc;
#define sz_xSGIvcFormatInfo	48


/*---------------------------------
 *	SGIvcListVideoFormatCombinations
 */
typedef struct _xSGIvcListVideoFormatCombinations {
    CARD8	reqType;
    CARD8	xsgivcReqType;	/* always X_SGIvcListVideoFormatCombinations */
    CARD16	length B16;
    CARD32	screen B32;
    CARD32	numStrings B32;
} xSGIvcListVideoFormatCombinationsReq;
#define sz_xSGIvcListVideoFormatCombinationsReq	12

typedef struct _xSGIvcListVideoFormatCombinationsReply {
    BYTE	type;		/* X_Reply */
    BOOL	implemented;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD32	actualCount B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
    CARD32	pad6 B32;
} xSGIvcListVideoFormatCombinationsReply;
#define sz_xSGIvcListVideoFormatCombinationReq	32 


/*-----------------------------------------
 *	SGIvcListFormatsInCombination
 */
typedef struct _xSGIvcListFormatsInCombination {
    CARD8	reqType;
    CARD8	xsgivcReqType;	/* always X_SGIvcListFormatsInCombination */
    CARD16	length B16;
    CARD32	screen B32;
    CARD32	nbytes B32;	/* num of name string bytes following struct */
} xSGIvcListFormatsInCombinationReq;
#define sz_xSGIvcListFormatsInCombinationReq	12

typedef xSGIvcListFormatsReply xSGIvcListFormatsInCombinationReply;
#define sz_xSGIvcListFormatsInCombinationReply	32


/*---------------------------------
 *	SGIvcLoadVideoFormat
 */
typedef struct _xSGIvcLoadVideoFormat {
    CARD8	reqType;
    CARD8	xsgivcReqType;	/* always X_SGIvcLoadVideoFormat */
    CARD16	length B16;
    CARD32	screen B32;
    CARD32	channel B32;
    CARD8	matchMonitor;
    CARD8	pad1;
    CARD16	pad2 B16;
    CARD32	mask B32;
} xSGIvcLoadVideoFormatReq;
#define sz_xSGIvcLoadVideoFormatReq	20 


/*---------------------------------
 *	SGIvcLoadVideoCombination
 */
typedef struct _xSGIvcLoadVideoCombination {
    CARD8	reqType;
    CARD8	xsgivcReqType;	/* always X_SGIvcLoadVideoCombination */
    CARD16	length B16;
    CARD32	screen B32;
    CARD32	nbytes B32;	/* num of name string bytes following struct */
} xSGIvcLoadVideoCombinationReq;
#define sz_xSGIvcLoadVideoCombinationReq	12


/*---------------------------------
 *	SGIvcDisableChannel
 */
typedef struct _xSGIvcDisableChannel {
    CARD8	reqType;
    CARD8	xsgivcReqType;  /* always X_SGIvcDisableChannel */
    CARD16	length B16;
    CARD32	screen B32;
    CARD32	channel B32;
} xSGIvcDisableChannelReq;
#define sz_xSGIvcDisableChannelReq		12

/*---------------------------------
 *	SGIvcQueryChannelInfo
 */
typedef struct _xSGIvcQueryChannelInfo {
    CARD8	reqType;
    CARD8	xsgivcReqType;  /* always X_SGIvcQueryChannelInfo */
    CARD16	length B16;
    CARD32	screen B32;
    CARD32	channel B32;
} xSGIvcQueryChannelInfoReq;
#define sz_xSGIvcQueryChannelInfoReq		12

typedef struct _xSGIvcQueryChannelInfoReply {
    BYTE	type;           /* X_Reply */
    BOOL	active;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    INT32	orgX;
    INT32	orgY;
    INT32	width;
    INT32	height;
    CARD32	flags;
    CARD32	gammaCount B32;
    INT32	phaseHMin B32;
    INT32	phaseHMax B32;
    INT32	phaseVMin B32;
    INT32	phaseVMax B32;
    INT32	phaseSCHMin B32;
    INT32	phaseSCHMax B32;
    INT32	physicalId B32;
    BOOL	blankingAvail;
    BOOL	gainAvail;
    BOOL	pedestalAvail;
    BOOL	phaseHAvail;
    BOOL	phaseVAvail;
    BOOL	phaseSCHAvail;
    BOOL	syncAvail;
    BYTE	pad1;
    INT32	syncPortCount B32;
    CARD32	syncDataLength B32;
    xsgivcFormatInfoDesc format;
} xSGIvcQueryChannelInfoReply;
#define sz_xSGIvcQueryChannelInfoReply	(70 + sz_xSGIvcFormatInfo)

typedef struct _xsgivcSynInfoDesc {
    INT32	syncPort B32;
    INT32	numTypes B32;
} xsgivcSyncInfoDesc;
#define sz_xSGIvcSyncInfoDesc	36

/*---------------------------------
 *	SGIvcQueryMonitorName
 */
typedef xSGIvcQueryChannelInfoReq xSGIvcQueryMonitorNameReq;
#define sz_xSGIvcQueryMonitorNameReq	12

typedef struct _xSGIvcQueryMonitorNameReply {
    BYTE	type;           /* X_Reply */
    BOOL	implemented;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD32	namelength B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
    CARD32	pad6 B32;
} xSGIvcQueryMonitorNameReply;
#define sz_xSGIvcQueryMonitorNameReply	32


/*---------------------------------
 *	SGIvcSetControl
 */
typedef struct _xSGIvcSetControl {
    CARD8	reqType;
    CARD8	xsgivcReqType;  /* always X_SGIvcSetControl */
    CARD16	length B16;
    CARD32	screen B32;
    CARD32	channel B32;
    CARD32	control B32;
    CARD32	value B32;
} xSGIvcSetControlReq;
#define sz_xSGIvcSetControlReq	20


/*---------------------------------
 *	SGIvcQueryControl
 */
typedef struct _xSGIvcQueryControl {
    CARD8	reqType;
    CARD8	xsgivcReqType;  /* always X_SGIvcSetControl */
    CARD16	length B16;
    CARD32	screen B32;
    CARD32	channel B32;
    CARD32	control B32;
} xSGIvcQueryControlReq;
#define sz_xSGIvcQueryControlReq	16

typedef struct _xSGIvcQueryControlReply {
    BYTE	type;           /* X_Reply */
    BOOL	implemented;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD32	value B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
    CARD32	pad6 B32;
} xSGIvcQueryControlReply;
#define sz_xSGIvcQueryControlReply	32


/*---------------------------------
 *	SGIvcSetOutputSync
 */
typedef struct _xSGIvcSetOutputSync {
    CARD8	reqType;
    CARD8	xsgivcReqType;	/* always X_SGIvcSetOutputSync */
    CARD16	length B16;
    CARD32	screen B32;
    CARD32	channel B32;
    INT32	syncPortIndex B32;
    CARD32	syncType B32;
} xSGIvcSetOutputSyncReq;
#define sz_xSGIvcSetOutputSyncReq	20


/*---------------------------------
 *	SGIvcQueryOutputSync
 */
typedef struct _xSGIvcQueryOutputSync {
    CARD8	reqType;
    CARD8	xsgivcReqType;	/* always X_SGIvcQueryOutputSync */
    CARD16	length B16;
    CARD32	screen B32;
    CARD32	channel B32;
    INT32	syncPortIndex B32;
} xSGIvcQueryOutputSyncReq;
#define sz_xSGIvcQueryOutputSyncReq	16

typedef struct _xSGIvcQueryOutputSyncReply {
    BYTE	type;           /* X_Reply */
    BOOL	implemented;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD32	syncType B32;
    CARD32	pad1 B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
} xSGIvcQueryOutputSyncReply;
#define sz_xSGIvcQueryOutputSyncReply	32


/*------------------------------------
 *      SGIvcSetScreenInputSyncSource
 */
typedef struct _xSGIvcSetScreenInputSource {
    CARD8	reqType;
    CARD8	xsgivcReqType;	/* always X_SGIvcSetScreenInputSource */
    CARD16	length B16;
    CARD32	screen B32;
    CARD32	syncVoltage B32;
    INT32	lockSource B32;
} xSGIvcSetScreenInputSyncSourceReq;
#define sz_xSGIvcSetScreenInputSyncSourceReq  16


/*--------------------------------------
 *      SGIvcQueryScreenInputSyncSource
 */
typedef struct _xSGIvcQueryScreenInputSyncSource {
    CARD8	reqType;
    CARD8	xsgivcReqType;	/* always X_SGIvcQueryScreenInputSyncSource */
    CARD16	length B16;
    CARD32	screen B32;
} xSGIvcQueryScreenInputSyncSourceReq;
#define sz_xSGIvcQueryScreenInputSyncSourceReq  8

typedef struct _xSGIvcQueryScreenInputSyncSourceReply {
    BYTE	type;           /* X_Reply */
    BOOL	implemented;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD32	voltage B32;
    INT32	source B32;
    BOOL	achieved;
    BYTE	pad2;
    CARD16	pad3 B16;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
    CARD32	pad6 B32;
} xSGIvcQueryScreenInputSyncSourceReply;
#define sz_xSGIvcQueryScreenInputSyncSourceReply	32;


/*---------------------------------
 *	SGIvcSetPlatformParameter
 */
typedef struct _xSGIvcSetPlatformParameter {
    CARD8	reqType;
    CARD8	xsgivcReqType;  /* always X_SGIvcSetPlatformParameter */
    CARD16	length B16;
    CARD32	screen B32;
    CARD32	channel B32;
    INT32	paramid B32;
    INT32	blockSize B32;
} xSGIvcSetPlatformParameterReq;
#define sz_xSGIvcSetPlatformParameterReq	20

/*---------------------------------
 *	SGIvcQueryPlatformParameter
 */
typedef xSGIvcSetPlatformParameterReq xSGIvcQueryPlatformParameterReq;
#define sz_xSGIvcQueryPlatformParameterReq  sz_xSGIvcSetPlatformParameterReq

typedef struct _xSGIvcQueryPlatformParameterReply {
    BYTE	type;           /* X_Reply */
    BOOL	implemented;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD32	blockLen B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
    CARD32	pad6 B32;
} xSGIvcQueryPlatformParameterReply;
#define sz_xSGIvcPlatformParameterReply	32

/*---------------------------------
 *	SGIvcQueryScreenGammaMaps
 */
typedef struct _xSGIvcQueryScreenGammaMaps {
    CARD8	reqType;
    CARD8	xsgivcReqType;  /* always X_SGIvcQueryScreenGammaMaps */
    CARD16	length B16;
    CARD32	screen B32;
} xSGIvcQueryScreenGammaMapsReq;
#define sz_xSGIvcQueryScreenGammaMapsReq	8

typedef struct _xSGIvcQueryScreenGammaMapsReply {
    BYTE	type;           /* X_Reply */
    BOOL	implemented;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD32	number B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
    CARD32	pad6 B32;
} xSGIvcQueryScreenGammaMapsReply;
#define sz_xSGIvcQueryScreenGammaMapsReply	32


/*---------------------------------
 *	SGIvcQueryGammaMap
 */
typedef struct _xSGIvcQueryGammaMap {
    CARD8	reqType;
    CARD8	xsgivcReqType;  /* always X_SGIvcQueryGammaMap */
    CARD16	length B16;
    CARD32	screen B32;
    CARD32	gammamap B32;
} xSGIvcQueryGammaMapReq;
#define sz_xSGIvcQueryGammaMapReq	12

typedef struct _xSGIvcQueryGammaMapReply {
    BYTE 	type;		/* X_Reply */
    BOOL	implemented;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD32	size B32;
    CARD32	precision B32;
    CARD32	attributes;
    CARD32	pad1 B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
} xSGIvcQueryGammaMapReply;
#define sz_xSGIvcQueryGammaMapReply    32


/*---------------------------------
 *	SGIvcStoreGammaColors8
 */
typedef struct _xSGIvcStoreGammaColors8 {
    CARD8	reqType;
    CARD8	xsgivcReqType;  /* always X_SGIvcStoreGammaColors8 */
    CARD16	length B16;
    CARD32	screen B32;
    CARD32	gammaMap B32;
    CARD32	itemCount B32;
    CARD32	component B32;
} xSGIvcStoreGammaColors8Req;
#define sz_xSGIvcStoreGammaColors8Req	20


/*---------------------------------
 *	SGIvcStoreGammaColors16
 */
typedef xSGIvcStoreGammaColors8Req xSGIvcStoreGammaColors16Req;
#define sz_xSGIvcStoreGammaColors16Req sz_xSGIvcStoreGammaColors8Req


/*---------------------------------
 *	SGIvcQueryGammaColors
 */
typedef struct _xSGIvcQueryGammaColors {
    CARD8	reqType;
    CARD8	xsgivcReqType;  /* always X_SGIvcQueryGammaColors */
    CARD16	length B16;
    CARD32	screen B32;
    CARD32	gammaMap B32;
    CARD32	component B32;
} xSGIvcQueryGammaColorsReq;
#define sz_xSGIvcQueryGammaColorsReq 16

typedef struct _xSGIvcQueryGammaColorsReply {
    BYTE	type;           /* X_Reply */
    BOOL	implemented;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD32	number B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
    CARD32	pad6 B32;
} xSGIvcQueryGammaColorsReply;
#define sz_xSGIvcQueryGammaColorsReply 32


/*---------------------------------
 *      SGIvcSelectInput
 */
typedef struct _xSGIvcSelectInput {
    CARD8	reqType;
    CARD8	xsgivcReqType;	/* always X_SGIvcSelectInput */
    CARD16	length B16;
    CARD32	screen B32;
    CARD32	mask B32;    
} xSGIvcSelectInputReq;
#define sz_xSGIvcSelectInputReq 12


/*****  New requests/replies introduced for XSGIvc 1.1  *****/

/*---------------------------------------
 *	SGIvcChannelInputRectangle
 */
typedef struct _xSGIvcChannelInputRectangle {
    CARD8	reqType;
    CARD8	xsgivcReqType;	/* always X_SGIvcChannelInputRectangle */
    CARD16	length B16;
    CARD32	screen B32;
    CARD32	channel B32;
    INT32	orgX B32;
    INT32	orgY B32;
    INT32	width B32;
    INT32	height B32;
    BOOL	set;
    CARD8	pad1;
    CARD16	pad2 B16;
} xSGIvcChannelInputRectangleReq;
#define sz_xSGIvcChannelInputRectangleReq 32

typedef struct _xSGIvcChannelInputRectangleReply {
    BYTE	type;           /* X_Reply */
    BOOL	implemented;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    INT32	orgX B32;
    INT32	orgY B32;
    INT32	width B32;
    INT32	height B32;
    CARD32	pad1 B32;
    CARD32	pad2 B32;
} xSGIvcChannelInputRectangleReply;
#define sz_xSGIvcChannelInputRectangleReply 32;


/*---------------------------------------
 *	SGIvcMonitorCommand
 */
typedef struct _xSGIvcMonitorCommand {
    CARD8	reqType;
    CARD8	xsgivcReqType;	/* always X_SGIvcMonitorCommand */
    CARD16	length B16;
    CARD32	screen B32;
    CARD32	channel B32;
    CARD32	cmdlength B32;
    BOOL	rep;
    CARD8	pad1;
    CARD16	pad2 B16;
} xSGIvcMonitorCommandReq;
#define sz_xSGIvcMonitorCommandReq	20

typedef struct _xSGIvcMonitorCommandReply {
    BYTE	type;           /* X_Reply */
    BOOL	implemented;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD32	rsplength B32;
    CARD32	pad1 B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
} xSGIvcMonitorCommandReply;
#define sz_xSGIvcMonitorCommandReply	32


/*---------------------------------------
 *	SGIvcMonitorBaseProtocol
 */
typedef xSGIvcDisableChannelReq  xSGIvcMonitorBaseProtocolReq;
#define sz_xSGIvcMonitorBaseProtocolReq	sz_xSGIvcDisableChannelReq

typedef struct _xSGIvcMonitorBaseProtocolReply {
    BYTE	type;           /* X_Reply */
    BOOL	implemented;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD32	proto B32;
    CARD32	pad1 B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
} xSGIvcMonitorBaseProtocolReply;
#define sz_xSGIvcMonitorBaseProtocolReply	32

/*---------------------------------------
 *	SGIvcInitMonitorBaseProtocol
 */
typedef xSGIvcDisableChannelReq  xSGIvcInitMonitorBaseProtocolReq;
#define sz_xSGIvcInitMonitorBaseProtocolReq	sz_xSGIvcDisableChannelReq

/*---------------------------------------
 *	SGIvcSetScreenExternalSyncSource
 */
typedef struct _xSGIvcSetScreenExternalSyncSource {
    CARD8	reqType;
    CARD8	xsgivcReqType;	/* always X_SGIvcSetScreenExternalSyncSource */
    CARD16	length B16;
    CARD32	screen B32;
    CARD32	externalSyncSource B32;
} xSGIvcSetScreenExternalSyncSourceReq;
#define sz_xSGIvcSetScreenExternalSyncSourceReq		12


/*---------------------------------------
 *	SGIvcQueryScreenExternalSyncSource
 */
typedef xSGIvcQueryScreenInputSyncSourceReq  xSGIvcQueryScreenExternalSyncSourceReq;
#define sz_xSGIvcQueryScreenExternalSyncSourceReq sz_xSGIvcQueryScreenInputSyncSourceReq

typedef struct _xSGIvcQueryScreenExternalSyncSourceReply {
    BYTE	type;           /* X_Reply */
    BOOL	implemented;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    INT32	externalSyncSource B32;
    CARD32	pad1 B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
} xSGIvcQueryScreenExternalSyncSourceReply;
#define sz_xSGIvcQueryScreenExternalSyncSourcereply	32


/*---------------------------------------------
 *	SGIvcQueryScreenExternalSyncSourceName
 */
typedef xSGIvcSetScreenExternalSyncSourceReq xSGIvcQueryExternalSyncSourceNameReq; 
#define sz_xSGIvcQueryExternalSyncSourceNameReq sz_xSGIvcSetScreenExternalSyncSourceReq

typedef xSGIvcQueryMonitorNameReply xSGIvcQueryExternalSyncSourceNameReply;
#define sz_xSGIvcQueryExternalSyncSourceNameReply  sz_xSGIvcQueryMonitorNameReply;


/*---------------------------------
 *	SGIvcNVListVideoFormats
 */
typedef struct _xSGIvcNVListVideoFormats {
    CARD8	reqType;
    CARD8	xsgivcReqType;	/* always X_SGIvcNVListVideoFormats */
    CARD16	length B16;
    CARD32	screen B32;
    CARD32	channel B32;
    CARD8	matchMonitor;
    CARD8	matchOnlyNV;
    CARD16	pad1 B16;
    CARD32	maxFormats B32;
    CARD32	mask B32;
} xSGIvcNVListVideoFormatsReq;
#define sz_xSGIvcNVListVideoFormatsReq	24

typedef xSGIvcListFormatsReply xSGIvcNVListFormatsReply;
#define sz_xSGIvcNVListFormatsReply	sz_xSGIvcListFormatsReply


/*----------------------------------------
 *	SGIvcNVListVideoFormatCombinations
 */
typedef struct _xSGIvcNVListVideoFormatCombinations {
    CARD8	reqType;
    CARD8	xsgivcReqType;	/* always X_SGIvcNVListVideoFormatCombinations */
    CARD16	length B16;
    CARD32	screen B32;
    CARD32	numStrings B32;
    BOOL	matchOnlyNV;
    CARD8	pad1;
    CARD16	pad2 B16;
} xSGIvcNVListVideoFormatCombinationsReq;
#define sz_xSGIvcNVListVideoFormatCombinationsReq	16

typedef xSGIvcListVideoFormatCombinationsReply xSGIvcNVListVideoFormatCombinationsReply;
#define sz_xSGIvcNVListVideoFormatCombinationReq sz_xSGIvcListVideoFormatCombinationReq


/*---------------------------------
 *	SGIvcNVLoadVideoFormat
 */
typedef struct _xSGIvcNVLoadVideoFormat {
    CARD8	reqType;
    CARD8	xsgivcReqType;	/* always X_SGIvcNVLoadVideoFormat */
    CARD16	length B16;
    CARD32	screen B32;
    CARD32	channel B32;
    CARD8	matchMonitor;
    CARD8	pad1;
    CARD16	pad2 B16;
    CARD32	mask B32;
    INT32	syncSource B32;
    INT32	externalSyncSource B32;
} xSGIvcNVLoadVideoFormatReq;
#define sz_xSGIvcNVLoadVideoFormatReq	28 


/*---------------------------------
 *	SGIvcNVLoadVideoCombination
 */
typedef xSGIvcLoadVideoCombinationReq xSGIvcNVLoadVideoCombinationReq;
#define sz_xSGIvcNVLoadVideoCombinationReq sz_xSGIvcLoadVideoCombinationReq


/*----------------------------------------
 *	SGIvcLoadFormatByName
 */
typedef struct _xSGIvcLoadFormatByName {
    CARD8	reqType;
    CARD8	xsgivcReqType;	/* always X_SGIvcNVLoadFormatByName */
    CARD16	length B16;
    CARD32	screen B32;
    CARD32	channel B32;
    CARD32	nonvolatile B32;
    CARD32	nbytes B32;	/* num of name string bytes following */
} xSGIvcLoadFormatByNameReq;
#define sz_xSGIvcLoadFormatByNameReq	20


	/***********************************
	 *  Controls definition
	 ***********************************/
#define		CTRLRedOutputGain	0x1
#define		CTRLGreenOutputGain	0x2
#define		CTRLBlueOutputGain	0x3
#define		CTRLAlphaOutputGain	0x4
#define		CTRLAllOutputGain	0x5
#define		CTRLOutputPedestal	0x6
#define		CTRLOutputPhaseH	0x7
#define		CTRLOutputPhaseSCH	0x8
#define		CTRLOutputPhaseV	0x9
#define		CTRLGammaMap		0xa
#define		CTRLBlanking		0xb

	/**************************************************
	 *  SGI VIDEO CONTROL EXTENSION EVENTS STRUCTURES
	 **************************************************/

typedef struct _xSGIvcAnyEventNotify {
    BYTE	type;
    BYTE	xsgivcType;
    CARD16	sequenceNumber B16;
    CARD32	screen B32;
    CARD32	pad1 B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
    CARD32	pad6 B32;
} xSGIvcAnyEventNotify;
#define sz_xSGIvcAnyEventNotify		32

typedef struct _xSGIvcVideoFormatNotify {
    BYTE	type;
    BYTE	xsgivcType;
    CARD16	sequenceNumber B16;
    CARD32	screen B32;
    CARD32	channel B32;
    CARD32	pad1 B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
} xSGIvcVideoFormatNotify;
#define sz_xSGIvcVideoFormatNotify 32

typedef struct _xSGIvcScreenInputSyncSourceNotify {
    BYTE	type;
    BYTE	xsgivcType;
    CARD16	sequenceNumber B16;
    CARD32	screen B32;
    CARD32	source B32;
    CARD32	voltage B32;
    CARD32	pad1 B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
} xSGIvcScreenInputSyncSourceNotify;
#define sz_xSGIvcScreenInputSyncSourceNotify 32

typedef struct _xSGIvcScreenLockStatusChangedNotify {
    BYTE	type;
    BYTE	xsgivcType;
    CARD16	sequenceNumber B16;
    CARD32	screen B32;
    CARD32	status B32;
    CARD32	pad1 B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
} xSGIvcScreenLockChangedNotify;
#define sz_xSGIvcScreenLockStatusChangedNotify 32

typedef struct _xSGIvcOutputGainNotify {
    BYTE	type;
    BYTE	xsgivcType;
    CARD16	sequenceNumber B16;
    CARD32	screen B32;
    CARD32	channel B32;
    CARD32	component B32;
    INT32	value B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
} xSGIvcOutputGainNotify;
#define sz_xSGIvcOutputGainNotify 32

typedef struct _xSGIvcPedestalNotify {
    BYTE	type;
    BYTE	xsgivcType;
    CARD16	sequenceNumber B16;
    CARD32	screen B32;
    CARD32	channel B32;
    CARD8	enable;
    CARD8	pad1;
    CARD16	pad2;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
    CARD32	pad6 B32;
} xSGIvcPedestalNotify;
#define sz_xSGIvcPedestalNotify	32

typedef struct _xSGIvcPhaseHNotify {
    BYTE	type;
    BYTE	xsgivcType;
    CARD16	sequenceNumber B16;
    CARD32	screen B32;
    CARD32	channel B32;
    INT32	value B32;
    CARD32	pad1 B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
} xSGIvcPhaseHNotify;
#define sz_xSGIvcPhaseHNotify	32

typedef xSGIvcPhaseHNotify xSGIvcPhaseSCHNotify;
#define sz_xSGIvcPhaseSCHNotify	32

typedef xSGIvcPhaseHNotify xSGIvcPhaseVNotify;
#define sz_xSGIvcPhaseVNotify	32

typedef struct _xSGIvcOutputSyncNotify {
    BYTE	type;
    BYTE	xsgivcType;
    CARD16	sequenceNumber B16;
    CARD32	screen B32;
    CARD32	channel B32;
    INT32	syncPortIndx B32;
    CARD32	syncType B32;
    CARD32	pad1 B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
} xSGIvcOutputSyncNotify;
#define sz_xSGIvcOutputSyncNotify	32

typedef struct _xSGIvcPlatformParamNotify {
    BYTE	type;
    BYTE	xsgivcType;
    CARD16	sequenceNumber B16;
    CARD32	screen B32;
    CARD32	channel B32;
    INT32	parameterid B32;
    CARD32	pad1 B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
} xSGIvcPlatformParamNotify;
#define sz_xSGIvcPlatformParamNotify 32

typedef struct _xSGIvcGammaMapNotify {
    BYTE	type;
    BYTE	xsgivcType;
    CARD16	sequenceNumber B16;
    CARD32	screen B32;
    CARD32	channel B32;
    CARD32	mapid B32;
    CARD32	pad1 B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
} xSGIvcGammaMapNotify;
#define sz_xSGIvcGammaMapNotify 32

typedef xSGIvcPedestalNotify xSGIvcBlankingNotify;
#define sz_xSGIvcBlankingNotify	32


/*****  New events introduced for XSGIvc 1.1  *****/

typedef struct _xSGIvcChannelInputRectangleNotify {
    BYTE	type;
    BYTE	xsgivcType;
    CARD16	sequenceNumber B16;
    CARD32	screen B32;
    CARD32	channel B32;
    INT32	orgX B32;
    INT32	orgY B32;
    INT32	width B32;
    INT32	height B32;
    CARD32	pad1 B32;
} xSGIvcChannelInputRectangleNotify;
#define sz_xSGIvcChannelInputRectangleNotify 32

typedef struct _xSGIvcEvent {
    union {
	xSGIvcAnyEventNotify			any;
	xSGIvcVideoFormatNotify			format;
	xSGIvcScreenInputSyncSourceNotify	insynclock;
	xSGIvcScreenLockChangedNotify		lockstatus;
	xSGIvcOutputGainNotify			gain;
	xSGIvcPedestalNotify			pedestal;
	xSGIvcPhaseHNotify			phaseh;
	xSGIvcPhaseSCHNotify			phasesch;
	xSGIvcPhaseVNotify			phasev;
	xSGIvcOutputSyncNotify			syncoutput;
	xSGIvcPlatformParamNotify		platform;
	xSGIvcGammaMapNotify			gamma;
	xSGIvcBlankingNotify			blanking;
	xSGIvcChannelInputRectangleNotify	inprectangle;	/* New since XSGIvc 1.1 */
    } u;
} xSGIvcEventRec, *xSGIvcEventPtr;
#define sz_xSGIvcEvent	32


/*
 * Bitmask values used by SGIvcStoreGammaColors8 SGIvcStoreGammaColors16
 */
#define RedMask			(1L << 0)
#define GreenMask		(1L << 1)
#define BlueMask		(1L << 2)
#define AlphaMask		(1L << 3)

/*****  New request introduced for XSGIvc 1.3  *****/

/*---------------------------------
 *      SGIvcMultiCursorSetMode
 */
typedef struct _SGIvcMultiCursorSetMode {
    CARD8       reqType;
    CARD8       xsgivcReqType;
    CARD16      length B16;     /* length in words */
    CARD8       mode;
    CARD8       pad1;
    CARD16      pad2 B16;
} xSGIvcMultiCursorSetModeReq;
#define sz_xSGIvcMultiCursorSetModeReq 8


#endif /* _XSGIVCPROTO_H_ */
