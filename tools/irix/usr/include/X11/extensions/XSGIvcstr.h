#ifndef __XSGIVC_H__
#define __XSGIVC_H__

/*
 * XSGIvc.h
 *
 *      Video control of SGI graphics.
 *
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
 * $Revision: 1.21 $
 */

#include <limits.h>
#include <wctype.h>

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)

#define XSGIVC_NAME_MAX 32
#define XSGIVC_FORMATNAME_MAX NAME_MAX

#define XSGIVC_SYNC_SOURCE_INTERNAL -1 
#define XSGIVC_SYNC_SOURCE_EXTERNAL -2

#define XSGIVC_SYNC_VOLTAGE_VIDEO 1 
#define XSGIVC_SYNC_VOLTAGE_TTL 2 


/* Color components */
#define XSGIVC_COMPONENT_RED	1
#define XSGIVC_COMPONENT_GREEN	2
#define XSGIVC_COMPONENT_BLUE	3
#define XSGIVC_COMPONENT_ALPHA	4
#define XSGIVC_COMPONENT_ALL	5
#define XSGIVC_MComponentRed		(1L << 0)
#define XSGIVC_MComponentGreen		(1L << 1)
#define XSGIVC_MComponentBlue  		(1L << 2)
#define XSGIVC_MComponentAlpha		(1L << 3)

#define XSGIVC_QVFHeight		(1L << 1)
#define XSGIVC_QVFWidth			(1L << 2)
#define XSGIVC_QVFTotalHeight		(1L << 3)
#define XSGIVC_QVFTotalWidth		(1L << 4)
#define XSGIVC_QVFRetraceRate		(1L << 5)
#define XSGIVC_QVFSwapbufferRate	(1L << 6)
#define XSGIVC_QVFFieldCount		(1L << 7)
#define XSGIVC_QVFFlags			(1L << 8)



typedef struct {
    float           x, y;
    float           height, width;
}               XSGIvcRectangle;

/* See eyeActive in XSGIvcFieldInfo */
#define XSGIVC_FIEyeActiveLeft		(1L << 0)   /* Left eye shown */
#define XSGIVC_FIEyeActiveRight		(1L << 1)   /* Right eye shown */

typedef struct {
    int             offset;		/* Line on which this field starts */
    int             stride;		/* y-increment to next line */
    struct {
	int             backPorch;	/* Duration in pixels */
	int             sync;		/* Duration in pixels */
	int             syncPulse;	/* Duration in pixels */
	int             frontPorch;	/* Duration in pixels */
	int             active;		/* Duration in pixels */
    }               vertical;
    long            colorActive;	/* Colors in field; XSGIVC_Component... */
    long            eyeActive;		/* Eye this field; XSGIVC_FI... */
}               XSGIvcFieldInfo;


/* See formatFlags in XSGIvcVideoFormatInfo */
#define XSGIVC_VFIStereo		(1L << 0)   /* Eye differs field to field */
#define XSGIVC_VFIFieldSequentialColor	(1L << 1)   /* Color differs field to field */
#define XSGIVC_VFIFullScreenStereo	(1L << 2)   /* SGI stereo of the old style */

typedef struct {
    char            name[XSGIVC_FORMATNAME_MAX];	/* Typically is filename */
    int             height, width;	/* Active pixels */
    int             totalHeight;	/* Includes blanking */
    int             totalWidth;		/* Includes blanking */
    float           verticalRetraceRate;/* i.e., frame rate, in Hz */
    float           swapbufferRate;	/* Can be different from frame rate */
    int             pixelClock;		/* Pixels/second */
    struct {
	int             backPorch;	/* Duration in pixels */
	int             sync;		/* Duration in pixels */
	int             frontPorch;	/* Duration in pixels */
	int             active;		/* Duration in pixels */
    }               horizontal;
    int             fieldCount;
    XSGIvcFieldInfo *fieldInfo;		/* Array of items, size=fieldCount */
    long            formatFlags;	/* See XSGIVC_VFI... masks */
}               XSGIvcVideoFormatInfo;

/* Used in XSGIvcChannelInfo structure */
typedef struct {
    int		    syncPort;		/* One of XSGIVC_SP... values */
    int		   *syncTypeList;	/* The list of XSGIVC_SC... */
    int		    syncTypeListCount;	/* Count of items in syncTypeList */
}		XSGIvcChannelSyncInfo;

/* See channelFlags in XSGIvcChannelInfo */
#define XSGIVC_CIFCompositeVideo	(1L << 0)   /* Composite video output */
#define XSGIVC_CIFPerComponentGain	(1L << 1)   /* Independent gain adjustment */

typedef struct {
    Bool            active;		/* channel is operating */
    XSGIvcRectangle source;		/* Position on display surface */
    XSGIvcVideoFormatInfo vfinfo;	/* Video format details */
    long            channelFlags;	/* See XSGIVC_CIF... masks */
    int            *gammaMaps;		/* Assignable gamma maps (ptr to array) */
    int             gammaCount;		/* Returned count of gammaMaps */
    Bool            blankingOp;		/* XSGIvcSetOutputBlanking usable */
    Bool            gainOp;		/* XSGIvcSetOutputGain usable */
    Bool            pedestalOp;		/* XSGIvcSetOutputPedestal usable */
    Bool            phaseHOp;		/* XSGIvcSetOutputPhaseH usable */
    int             phaseHMin;		/* Range of OutputPhaseH */
    int             phaseHMax;
    Bool            phaseVOp;		/* XSGIvcSetOutputPhaseV usable */
    int             phaseVMin;		/* Range of OutputPhaseV */
    int             phaseVMax;
    Bool            phaseSCHOp;		/* XSGIvcSetOutputPhaseSCH usable */
    int             phaseSCHMin;	/* Range of OutputPhaseSCH */
    int             phaseSCHMax;
    Bool	    syncOp;		/* XSGIvcSetOutputSync usable */
    int             syncPortCount;	/* Number of sync ports */
    XSGIvcChannelSyncInfo *syncInfo;	/* Information on all sync ports */
    int		    physicalID;         /* Physical port number */
}               XSGIvcChannelInfo;

/* See flags in XSGIvcScreenInfo */
#define XSGIVC_SIFFormatPerChannel	(1L << 0)   /* Formats change per channel */
#define XSGIVC_SIFFormatCombination	(1L << 1)   /* Formats change via combination */

typedef struct {
    int             numChannels;	/* Number of output channels */
    long            flags;		/* See XSGIVC_SIF... masks */
    Bool            lockOp;		/* XSGIvcSetScreenInputSyncSource usable */
    char	    graphicsType[XSGIVC_NAME_MAX]; /* Names of gfx hw */
    int		    numExternalSync;	/* Number of external sync ports */
}               XSGIvcScreenInfo;


/* See channelFlags in XSGIvcMonitorName */
#define XSGIVC_MIVariableFrequency	(1L << 0)   /* Accepts range of frequencies */
#define XSGIVC_MIColor			(1L << 1)   /* Displays color (not monochrome) */
#define XSGIVC_MIHalfLines		(1L << 2)   /* Displays half lines */
#define XSGIVC_MIFieldSequential	(1L << 3)   /* Requires field sequential, not parallel */
#define XSGIVC_MIAuxiliarySync		(1L << 4)   /* Requires separate H- and V-Sync */
#define XSGIVC_MICombinedHVSync		(1L << 5)   /* Requires combined H- and V-Sync */
#define XSGIVC_MIPowerSavingHVSync	(1L << 6)   /* Power reduction switch by H- and V-Sync  */

/* Special sync port IDs */
#define XSGIVC_SPRed			-1
#define XSGIVC_SPGreen			-2
#define XSGIVC_SPBlue			-3
#define XSGIVC_SPAlpha			-4
#define XSGIVC_SPAux0			0
#define XSGIVC_SPAux1			1
#define XSGIVC_SPAux2			2
#define XSGIVC_SPAux3			3

/* See syncType in XSGIvcSyncInfo (also in XSGIvcQueryChannelInfo) */
#define XSGIVC_SFNone			0   /* No sync */
#define XSGIVC_SFHorizontalVideo	1   /* Horizontal sync, video level */
#define XSGIVC_SFVerticalVideo		2   /* Vertical sync, video level */
#define XSGIVC_SFCompositeVideo		3   /* Composite sync, video level */
#define XSGIVC_SFHorizontalTTL  	4   /* Horizontal sync, TTL level */
#define XSGIVC_SFVerticalTTL  		5   /* Vertical sync, TTL level */
#define XSGIVC_SFCompositeTTL  		6   /* Composite sync, TTL level */
#define XSGIVC_SFHorizontalTriLevel	7   /* Horizontal sync, tri-level */
#define XSGIVC_SFVerticalTriLevel	8   /* Vertical sync, tri-level */
#define XSGIVC_SFCompositeTriLevel	9   /* Composite sync, tri-level */

typedef struct {
    long	    syncType;		/* See XSGIVC_SC... values */
    Bool	    ttlSync;		/* Enable TTL level */
}		XSGIvcSyncInfo;

/* See gammaMapAttributes argument in XSGIvcQueryGammaMap */
#define XSGIVC_GMAlphaPresent		(1L << 0)   /* gamma map has un alpha component */
#define XSGIVC_GMHardwareApproximation	(1L << 1)   /* server uses approximation of stated size and precision*/
#define XSGIVC_GMWriteLock		(1L << 2)   /* gamma map cannot be modified*/
#define XSGIVC_GMReadLock		(1L << 3)   /* gamma map cannot be queried*/

/* See XSGIvcQueryMonitorBaseProtocol */
#define XSGIVC_MBPUninitialized -1  /* monitor protocol hasn't yet been initialized */
#define XSGIVC_MBPNone 0	    /* Server or monitor do not support communication */
#define XSGIVC_MBPAccessBus 1	    /* Server uses Access.Bus protocol */

#define XSGIVC_MCAccessBusMessageLength	128	    /* Max length of message */

#ifndef _XSGIVC_SERVER_
/* See XSGIvcSelectInput - Events*/
typedef struct {
    int type;
    unsigned long serial;
    Bool send_event;
    Display *dpy;
    Window root;
    int xsgivctype;				/* XSGIvcVideoFormatNotify */
    int screen;
    int channel;
}  XSGIvcVideoFormatEvent;


typedef struct {
    int type;
    unsigned long serial;
    Bool send_event;
    Display *dpy;
    Window root;
    int xsgivctype;				/* XSGIvcScreenInputSyncSourceNotify */
    int screen;
    int voltage;
    int source;
}  XSGIvcScreenInputSyncSourceEvent;


typedef struct {
    int type;
    unsigned long serial;
    Bool send_event;
    Display *dpy;
    Window root;
    int xsgivctype;			/* XSGIvcScreenLockStatusChangedNotify */
    int screen;
    int status;
}  XSGIvcScreenLockStatusChangedEvent;


typedef struct {
    int type;
    unsigned long serial;
    Bool send_event;
    Display *dpy;
    Window root;
    int xsgivctype;				/* XSGIvcOutputGainNotify */
    int screen;
    int channel;
    int component;
    int value;
}  XSGIvcOutputGainEvent;


typedef struct {
    int type;
    unsigned long serial;
    Bool send_event;
    Display *dpy;
    Window root;
    int xsgivctype;				/* XSGIvcPedestalNotify */
    int screen;
    int channel;
    Bool enable;
}  XSGIvcPedestalEvent;


typedef struct {
    int type;
    unsigned long serial;
    Bool send_event;
    Display *dpy;
    Window root;
    int xsgivctype;				/* XSGIvcPhaseHNotify */
    int screen;
    int channel;
    int value;
}  XSGIvcPhaseHEvent;


typedef struct {
    int type;
    unsigned long serial;
    Bool send_event;
    Display *dpy;
    Window root;
    int xsgivctype;				/* XSGIvcPhaseSCHNotify */
    int screen;
    int channel;
    int value;
}  XSGIvcPhaseSCHEvent;


typedef struct {
    int type;
    unsigned long serial;
    Bool send_event;
    Display *dpy;
    Window root;
    int xsgivctype;				/* XSGIvcPhaseVNotify */
    int screen;
    int channel;
    int value;
}  XSGIvcPhaseVEvent;


typedef struct {
    int type;
    unsigned long serial;
    Bool send_event;
    Display *dpy;
    Window root;
    int xsgivctype;				/* XSGIvcOutputSyncNotify */
    int screen;
    int channel;
    int syncPortIndex;
    int syncType;
}  XSGIvcOutputSyncEvent;


typedef struct {
    int type;
    unsigned long serial;
    Bool send_event;
    Display *dpy;
    Window root;
    int xsgivctype;				/* XSGIvcPlatformParamNotify */
    int screen;
    int channel;
    int parameterId;
}  XSGIvcPlatformParamEvent;


typedef struct {
    int type;
    unsigned long serial;
    Bool send_event;
    Display *dpy;
    Window root;
    int xsgivctype;				/* XSGIvcGammaMapNotify */
    int screen;
    int channel;
    int mapid;
}  XSGIvcGammaMapEvent;


typedef struct {
    int type;
    unsigned long serial;
    Bool send_event;
    Display *dpy;
    Window root;
    int xsgivctype;				/* XSGIvcBlankingNotify */
    int screen;
    int channel;
    Bool enable;
}  XSGIvcBlankingEvent;


/* NEW events for XSGIvc 1.1 */

typedef struct {
    int type;
    unsigned long serial;
    Bool send_event;
    Display *dpy;
    Window root;
    int xsgivctype;				/* SGIvcChannelInputRectangleNotify */
    int screen;
    int channel;
    XSGIvcRectangle rct;
} XSGIvcChannelInputRectangleEvent;

    
#endif /* !_XSGIVC_SERVER_ */

#endif /* C || C++ */

#endif /* !__XSGIVC_H__ */
