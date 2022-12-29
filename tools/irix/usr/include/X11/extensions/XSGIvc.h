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

#ifndef _XSGIVC_H_
#define _XSGIVC_H_

#include <X11/Xfuncproto.h>
#include "XSGIvcstr.h"

/* 
 * Extension Name
 */
#define   XSGIVC_PROTOCOL_NAME "SGI-VIDEO-CONTROL"

/*----------------------------------------------------
		R E Q U E S T S
 ----------------------------------------------------*/
/*
 * SGI Video Control Extension Requests
 */
#define X_SGIvcQueryVersion			0
#define X_SGIvcQueryVideoScreenInfo		1
#define X_SGIvcListVideoFormats			2
#define X_SGIvcListVideoFormatCombinations	3
#define X_SGIvcListFormatsInCombination		4
#define X_SGIvcLoadVideoFormat			5
#define X_SGIvcLoadVideoCombination		6
#define X_SGIvcDisableChannel			7
#define X_SGIvcQueryChannelInfo			8
#define X_SGIvcQueryMonitorName			9
#define X_SGIvcSetControl			10
#define X_SGIvcQueryControl			11
#define X_SGIvcSetOutputSync			12
#define X_SGIvcQueryOutputSync			13
#define X_SGIvcSetScreenInputSyncSource		14
#define X_SGIvcQueryScreenInputSyncSource	15
#define X_SGIvcSetPlatformParameter		16
#define X_SGIvcQueryPlatformParameter		17
#define X_SGIvcQueryScreenGammaMaps		18
#define X_SGIvcQueryGammaMap			19
#define X_SGIvcStoreGammaColors8		20
#define X_SGIvcStoreGammaColors16		21
#define X_SGIvcQueryGammaColors			22
#define X_SGIvcSelectInput			23

/* Introduced with XSGIvc 1.1 */
#define X_SGIvcChannelInputRectangle		24
#define X_SGIvcMonitorCommand			25
#define X_SGIvcMonitorBaseProtocol		26
#define X_SGIvcSetScreenExternalSyncSource	27
#define X_SGIvcQueryScreenExternalSyncSource	28
#define X_SGIvcQueryExternalSyncSourceName	29
#define X_SGIvcNVListVideoFormats		30
#define X_SGIvcNVListVideoFormatCombinations	31
#define X_SGIvcNVLoadVideoFormat		32
#define X_SGIvcNVLoadVideoCombination		33
#define X_SGIvcLoadFormatByName			34

/* (apparently) Introduced with XSGIvc 1.2 */
#define X_SGIvcInitMonitorBaseProtocol		35

/* Introduced with XSGIvc 1.3 */
#define X_SGIvcMultiCursorSetMode		36


/*----------------------------------------------------
		E V E N T S
 ----------------------------------------------------*/
/*
 * Events and errors related defines
 */
#define XSGIvcEventCode				0
#define XSGIvcNumberEvents			(XSGIvcEventCode + 1)
#define XSGIvcNumberErrors			0

/*
 * SGI Video Control events
 */
#define XSGIvcVideoFormatNotify			0
#define XSGIvcScreenInputSyncSourceNotify	1
#define XSGIvcScreenLockStatusChangedNotify	2
#define XSGIvcOutputGainNotify			3
#define XSGIvcPedestalNotify			4
#define XSGIvcPhaseHNotify			5
#define XSGIvcPhaseSCHNotify			6
#define XSGIvcPhaseVNotify			7
#define XSGIvcOutputSyncNotify			8
#define XSGIvcPlatformParamNotify		9
#define XSGIvcGammaMapNotify			10
#define XSGIvcBlankingNotify			11

/* Introduced with XSGIvc 1.1 */
#define XSGIvcChannelInputRectangleNotify	12

/*
 * SGI Video Control events value masks
 */
#define XSGIvcVideoFormatNotifyMask		(1L << 0)
#define XSGIvcScreenInputSyncSourceNotifyMask	(1L << 1)
#define XSGIvcScreenLockStatusChangedNotifyMask (1L << 2)
#define XSGIvcOutputGainNotifyMask		(1L << 3)
#define XSGIvcPedestalNotifyMask		(1L << 4)
#define XSGIvcPhaseHNotifyMask			(1L << 5)
#define XSGIvcPhaseSCHNotifyMask		(1L << 6)
#define XSGIvcPhaseVNotifyMask			(1L << 7)
#define XSGIvcOutputSyncNotifyMask		(1L << 8)
#define XSGIvcPlatformParamNotifyMask		(1L << 9)
#define XSGIvcGammaMapNotifyMask		(1L << 10)
#define XSGIvcBlankingNotifyMask		(1L << 11)

/* Introduced with XSGIvc 1.1 */
#define XSGIvcChannelInputRectangleNotifyMask	(1L << 12)

#define XSGIvcAllEventsMask			0x0FFF

/* Introduced with XSGIvc 1.3 */

/* mode values for SGIvcMultiCursorSetMode */
#define XSGIvcMultiCursor_OFF		0
#define XSGIvcMultiCursor_ON		1
#define XSGIvcMultiCursor_IDENTXY	2
#define XSGIvcMultiCursor_DEFAULT	3


/*----------------------------------------------------
		P R O T O T Y P E S
 ----------------------------------------------------*/
#ifndef _XSGIVC_SERVER_

_XFUNCPROTOBEGIN
/* Function prototypes */

extern Status XSGIvcQueryVersion(
#if NeedFunctionPrototypes
    Display *		/* display */,
    int *		/* major */,
    int *		/* minor */
#endif
);

extern Status XSGIvcQueryVideoScreenInfo(
#if NeedFunctionPrototypes
    Display *		/* display */,
    int			/* screen */,
    XSGIvcScreenInfo *  /* sinfo_return */
#endif
);

XSGIvcVideoFormatInfo *XSGIvcListVideoFormats(
#if NeedFunctionPrototypes
    Display *		/* display */,
    int 		/* screen */,
    int 		/* channel */,
    const XSGIvcVideoFormatInfo * /* pattern */,
    unsigned long 		  /* querymask */,
    Bool 			  /* matchMonitor */,
    int 			  /* maxformats */,
    int *			  /* actual_count_return */
#endif
);

char **XSGIvcListVideoFormatCombinations(
#if NeedFunctionPrototypes
    Display *		/* display */,
    int 		/* screen */,
    const char *	/* pattern */,
    int 		/* maxnames */,
    int *		/* actual_count_return */
#endif
);

XSGIvcVideoFormatInfo *XSGIvcListVideoFormatsInCombination(
#if NeedFunctionPrototypes
    Display *		/* display */,
    int 		/* screen */,
    const char *	/* combinationName */,
    int *		/* actual_count_return */
#endif
);

Status XSGIvcLoadVideoFormat(
#if NeedFunctionPrototypes
    Display *		/* display */,
    int 		/* screen */,
    int 		/* channel */,
    const XSGIvcVideoFormatInfo *  /* pattern */,
    unsigned long 	/* querymask */,
    Bool 		/* matchMonitor */
#endif
);

Status XSGIvcLoadVideoFormatCombination(
#if NeedFunctionPrototypes
    Display *		/* display */,
    int 		/* screen */,
    const char *	/* combinationName */
#endif
);

void XSGIvcFreeVideoFormatInfo(
#if NeedFunctionPrototypes
    XSGIvcVideoFormatInfo *	/* info */
#endif
);

Status XSGIvcDisableChannel(
#if NeedFunctionPrototypes
    Display *		/* display */,
    int 		/* screen */,
    int 		/* channel */
#endif
);

Status XSGIvcQueryChannelInfo(
#if NeedFunctionPrototypes
    Display *		/* display */,
    int 		/* screen */,
    int 		/* channel */,
    XSGIvcChannelInfo ** /* cinfo_return */
#endif
);

Status XSGIvcQueryMonitorName(
#if NeedFunctionPrototypes
    Display *		/* display */,
    int 		/* screen */,
    int 		/* channel */,
    char **		/* mname_return */
#endif
);

void XSGIvcSetOutputBlanking(
#if NeedFunctionPrototypes
    Display *		/* dpy */,
    int 		/* screen */,
    int 		/* channel */,
    Bool 		/* enable */
#endif
);

void XSGIvcSetOutputGain(
#if NeedFunctionPrototypes
    Display *		/* dpy */,
    int 		/* screen */,
    int 		/* channel */,
    int 		/* componentID */,
    float 		/* gain */
#endif
);

void XSGIvcSetOutputPhaseSCH(
#if NeedFunctionPrototypes
    Display *		/* dpy */,
    int 		/* screen */,
    int 		/* channel */,
    int 		/* phaseSCH */
#endif
);

void XSGIvcSetOutputPedestal(
#if NeedFunctionPrototypes
    Display *		/* dpy */,
    int 		/* screen */,
    int 		/* channel */,
    Bool 		/* enable */
#endif
);

void XSGIvcSetOutputPhaseH(
#if NeedFunctionPrototypes
    Display *		/* dpy */,
    int 		/* screen */,
    int 		/* channel */,
    int 		/* phaseH */
#endif
);

void XSGIvcSetOutputPhaseV(
#if NeedFunctionPrototypes
    Display *		/* dpy */,
    int 		/* screen */,
    int 		/* channel */,
    int 		/* phaseV */
#endif
);

Status XSGIvcQueryOutputBlanking(
#if NeedFunctionPrototypes
    Display *		/* dpy */,
    int 		/* screen */,
    int 		/* channel */,
    Bool *		/* enableReturn */
#endif
);

Status XSGIvcQueryOutputGain(
#if NeedFunctionPrototypes
    Display *		/* dpy */,
    int 		/* screen */,
    int 		/* channel */,
    int 		/* componentID */,
    float *		/* gainReturn */
#endif
);

Status XSGIvcQueryOutputPhaseSCH(
#if NeedFunctionPrototypes
    Display *		/* dpy */,
    int 		/* screen */,
    int 		/* channel */,
    int *		/* phaseSCHReturn */
#endif
);

Status XSGIvcQueryOutputPedestal(
#if NeedFunctionPrototypes
    Display *		/* dpy */,
    int 		/* screen */,
    int 		/* channel */,
    Bool *		/* enableReturn */
#endif
);

Status XSGIvcQueryOutputPhaseH(
#if NeedFunctionPrototypes
    Display *		/* dpy */,
    int 		/* screen */,
    int 		/* channel */,
    int *		/* phaseHReturn */
#endif
);

Status XSGIvcQueryOutputPhaseV(
#if NeedFunctionPrototypes
    Display *		/* dpy */,
    int 		/* screen */,
    int 		/* channel */,
    int *		/* phaseVReturn */
#endif
);

void XSGIvcSetOutputSync(
#if NeedFunctionPrototypes
    Display *		/* display */,
    int 		/* screen */,
    int 		/* channel */,
    int 		/* syncPortIndex */,
    int 		/* syncType */
#endif
);

Status XSGIvcQueryOutputSync(
#if NeedFunctionPrototypes
        Display *	/* display */,
        int 		/* screen */,
        int 		/* channel */,
        int 		/* syncPortIndex */,
        int *		/* syncTypeReturn */
#endif
);

void XSGIvcSetScreenInputSyncSource(
#if NeedFunctionPrototypes
    Display *		/* display */,
    int 		/* screen */,
    int 		/* syncVoltage */,
    int 		/* genlockSource */
#endif
);

Status XSGIvcQueryScreenInputSyncSource(
#if NeedFunctionPrototypes
    Display *		/* display */,
    int 		/* screen */,
    int *		/* syncVoltageReturn */,
    int *		/* genlockSourceReturn */,
    Bool *		/* genlockAchievedReturn */
#endif
);

void XSGIvcSetPlatformParameter(
#if NeedFunctionPrototypes
    Display *		/* display */,
    int 		/* screen */,
    int 		/* channel */,
    int 		/* parameterID */,
    void *		/* parameterBlock */,
    int 		/* sizeofParameterBlock */
#endif
);

Bool XSGIvcQueryPlatformParameter(
#if NeedFunctionPrototypes
    Display *		/* display */,
    int 		/* screen */,
    int 		/* channel */,
    int 		/* parameterID */,
    void *		/* parameterBlock */,
    int 		/* sizeofParameterBlock */
#endif
);

Status XSGIvcQueryScreenGammaMaps(
#if NeedFunctionPrototypes
    Display *		/* display */,
    int 		/* screen */,
    int *		/* gammaMapsReturn */
#endif
);

Status XSGIvcQueryGammaMap(
#if NeedFunctionPrototypes
    Display *		/* display */,
    int 		/* screen */,
    int 		/* gammaMap */,
    int *		/* gammaSizeReturn */,
    int *		/* gammaPrecisionReturn */,
    int *		/* gammaMapAttributes */
#endif
);

void XSGIvcStoreGammaColors8(
#if NeedFunctionPrototypes
    Display *		/* display */,
    int 		/* screen */,
    int 		/* gammaMap */,
    int 		/* itemCount */,
    long 		/* loadTables */,
    const unsigned char * /* gammaValue */
#endif
);

void XSGIvcStoreGammaColors16(
#if NeedFunctionPrototypes
    Display *		/* display */,
    int 		/* screen */,
    int 		/* gammaMap */,
    int 		/* itemCount */,
    long 		/* loadTables */,
    const unsigned short * /* gammaValue */
#endif
);

Status XSGIvcQueryGammaColors(
#if NeedFunctionPrototypes
    Display *		/* display */,
    int 		/* screen */,
    int 		/* gammaMap */,
    int 		/* requestedColor */,
    int *		/* itemCountReturn */,
    unsigned short **	/* gammaValueReturn */
#endif
);

void XSGIvcSetChannelGammaMap(
#if NeedFunctionPrototypes
    Display *		/* dpy */,
    int 		/* screen */,
    int 		/* channel */,
    int 		/* gammaMap */
#endif
);

Status XSGIvcQueryChannelGammaMap(
#if NeedFunctionPrototypes
    Display *		/* dpy */,
    int 		/* screen */,
    int 		/* channel */,
    int *		/* gammaMapReturn */
#endif
);

void XSGIvcSelectInput(
#if NeedFunctionPrototypes
    Display *		/* display */,
    int 		/* screen */,
    unsigned long 	/* event_mask */
#endif
);

/* New API introduced for XSGIvc 1.1 */
void XSGIvcSetChannelInputRectangle(
#if NeedFunctionPrototypes
    Display *		/* display */,
    int			/* screen */,
    int 		/* channel */,
    XSGIvcRectangle	/* rct */
#endif
);

Status XSGIvcQueryBestChannelRectangle(
#if NeedFunctionPrototypes
    Display *		/* display */,
    int			/* screen */,
    int 		/* channel */,
    XSGIvcRectangle	/* rct */,
    XSGIvcRectangle *	/* rrct */
#endif
);

void XSGIvcSendMonitorCommand(
#if NeedFunctionPrototypes
    Display *		/* display */,
    int			/* screen */,
    int			/* channel */,
    const char *	/* monitorCommand */,
    int			/* commandLength */
#endif
);

Status XSGIvcSendMonitorQuery(
#if NeedFunctionPrototypes
    Display *		/* display */,
    int			/* screen */,
    int			/* channel */,
    const char *	/* monitorCommand */,
    int			/* commandLength */,
    char **		/* monitorResponse */,
    int *		/* responseLength */
#endif
);

int XSGIvcQueryMonitorBaseProtocol(
#if NeedFunctionPrototypes
    Display * 		/* display */,
    int			/* screen */,
    int			/* channel */
#endif
);

void XSGIvcInitMonitorBaseProtocol(
#if NeedFunctionPrototypes
    Display * 		/* display */,
    int			/* screen */,
    int			/* channel */
#endif
);

void XSGIvcSetScreenExternalSyncSource(
#if NeedFunctionPrototypes
    Display *		/* display */,
    int			/* screen */,
    int			/* externalSyncSource */
#endif
);

Status XSGIvcQueryScreenExternalSyncSource(
#if NeedFunctionPrototypes
    Display *		/* display */,
    int			/* screen */,
    int *		/* externalSyncSource */
#endif
);

char *XSGIvcQueryExternalSyncSourceName(
#if NeedFunctionPrototypes
    Display *		/* display */,
    int			/* screen */,
    int			/* externalSyncSource */
#endif
);

XSGIvcVideoFormatInfo *XSGIvcNVListVideoFormats(
#if NeedFunctionPrototypes
    Display *		/* display */,
    int			/* screen */,
    int			/* channel */,
    const XSGIvcVideoFormatInfo * /* pattern */,
    unsigned long 		  /* querymask */,
    Bool 			  /* matchMonitor */,
    Bool 			  /* matchOnlyNV */,
    int 			  /* maxformats */,
    int *			  /* actual_count_return */
#endif
);

char **XSGIvcNVListVideoFormatCombinations(
#if NeedFunctionPrototypes
    Display *		/* display */,
    int 		/* screen */,
    const char *	/* pattern */,
    Bool		/* matchOnlyNV */,
    int 		/* maxnames */,
    int *		/* actual_count_return */
#endif
);

Status XSGIvcNVLoadVideoFormat(
#if NeedFunctionPrototypes
    Display *		/* display */,
    int 		/* screen */,
    int 		/* channel */,
    const XSGIvcVideoFormatInfo *  /* pattern */,
    unsigned long 	/* querymask */,
    Bool 		/* matchMonitor */,
    int			/* syncSource */,
    int			/* externalSyncSource */
#endif
);

Status XSGIvcNVLoadVideoFormatCombination(
#if NeedFunctionPrototypes
    Display *		/* display */,
    int			/* screen */,
    const char *	/* combinationName */
#endif
);

Status XSGIvcLoadVideoFormatByName(
#if NeedFunctionPrototypes
    Display *		/* display */,
    int			/* screen */,
    int			/* channel */,
    const char *	/* path */
#endif
);

Status XSGIvcNVLoadVideoFormatByName(
#if NeedFunctionPrototypes
    Display *		/* display */,
    int			/* screen */,
    int			/* channel */,
    const char *	/* path */
#endif
);

/* New API introduced for XSGIvc 1.3 */
extern Status XSGIvcMultiCursorSetMode(
#if NeedFunctionPrototypes
    Display *		/* display */,
    int			/* mode */
#endif
);
#pragma optional XSGIvcMultiCursorSetMode


_XFUNCPROTOEND

#endif /* _XSGIVC_SERVER_ */

#endif /* _XSGIVC_H_ */
