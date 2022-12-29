/************************************************************
Copyright 1995 by Silicon Graphics, Inc.

Permission to use, copy, modify, and distribute this
software and its documentation for any purpose and without
fee is hereby granted, provided that the above copyright
no- tice appear in all copies and that both that copyright
no- tice and this permission notice appear in supporting
docu- mentation, and that the name of SGI not be used in
advertising or publicity pertaining to distribution of the
software without specific prior written permission.
S.G.I. makes no representation about the suitability of
this software for any purpose. It is provided "as is"
without any express or implied warranty.

SGI DISCLAIMS ALL WARRANTIES WITH REGARD TO  THIS  SOFTWARE,
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FIT-
NESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL SUN BE  LI-
ABLE  FOR  ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,  DATA  OR
PROFITS,  WHETHER  IN  AN  ACTION OF CONTRACT, NEGLIGENCE OR
OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION  WITH
THE USE OR PERFORMANCE OF THIS SOFTWARE.

********************************************************/

#include "sgiAC.h"

#define NEED_REPLIES
#define NEED_EVENTS

/* Define the name for the extension */
#define SGIACNAME      "SGI-AccessControl"

#define SGIAC_MAJOR_VERSION 1
#define SGIAC_MINOR_VERSION 0

/* Values for access_features field in xAccessQueryVersionReply */
#define SGIAC_AUDIT             0x01
#define SGIAC_MAC	        0x02
#define SGIAC_DAC		0x03
#define SGIAC_TP	        0x04

/* Values for Trusted Path (TP) state in the X server */
#define TP_OFF                 0
#define TP_ON                  1

/* Values for client Trusted Computing Base (TCB) */
#define TCB_DISABLE            0
#define TCB_ENABLE             1

/* Values for Mono Label  mode in the Xserver */
#define MONO_OFF            0
#define MONO_ON             1

typedef struct {
    CARD8 reqType;	/* always AccessReqCode */
    CARD8 accessReqType;/* always X_AccessQueryVersion */
    CARD16 length B16;
    CARD32  pad0 B32;
} xAccessQueryVersionReq;

#define sz_xAccessQueryVersionReq	8

typedef struct {
    BYTE    type;    /* X_Reply */
    BYTE    access_features_enabled;
    CARD16  sequenceNumber B16;
    CARD32  length B32;
    CARD16  major_version_number B16;
    CARD16  minor_version_number B16;
    CARD32  access_features B32;
    CARD32  pad0 B32;
    CARD32  pad1 B32;
    CARD32  pad2 B32;
    CARD32  pad3 B32;
} xAccessQueryVersionReply;
#define sz_xAccessQueryVersionReply      32

typedef struct {
    CARD8	reqType;	/* always AccessReqCode */
    CARD8	accessReqType;	/* always X_AccessSetWindowLabel */
    CARD16	length B16;
    CARD32  	window B32;
    CARD16 	labelLength B16; /* # of characters in label */
    CARD16      pad0;
} xAccessSetWindowLabelReq;
#define sz_xAccessSetWindowLabelReq	12

typedef struct {
    CARD8	reqType;	/* always AccessReqCode */
    CARD8	accessReqType;	/* always X_AccessGetWindowLabel */
    CARD16	length B16;
    CARD32  	window B32;
} xAccessGetWindowLabelReq;
#define sz_xAccessGetWindowLabelReq	8

typedef struct {
    BYTE	type;			/* X_Reply */
    BYTE	pad1;
    CARD16	sequenceNumber B16;
    CARD32	length B32;             /* of additional bytes */
    CARD16 	labelLength B16;        /* # of characters in label */
    CARD16	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
    CARD32	pad6 B32;
    CARD32	pad7 B32;
} xAccessGetWindowLabelReply;
#define sz_xAccessGetWindowLabelReply	32

typedef struct {
    CARD8       reqType;
    CARD8       accessReqType;
    CARD16      length B16;
    Window      window B32;
    CARD32      privilege B32;
} xAccessSetClientPrivReq;
#define sz_xAccessSetClientPrivReq      12

typedef struct {
    CARD8       reqType;
    CARD8       accessReqType;
    CARD16      length B16;
    Window      window B32;
} xAccessGetClientPrivReq;
#define sz_xAccessGetClientPrivReq      8

typedef struct  {
    BYTE        type; /* X_Reply */
    BYTE        data1;
    CARD16      sequenceNumber B16;   
    CARD32      length B32;
    CARD32      privilege;   
    CARD32      pad1 B32;
    CARD32      pad2 B32;
    CARD32      pad3 B32;
    CARD32      pad4 B32;
    CARD32      pad5 B32;
} xAccessGetClientPrivReply;
#define sz_xAccessGetClientPrivReply	12

typedef struct {
    CARD8       reqType;
    CARD8       accessReqType;
    CARD16      length B16;
    CARD32      screen B32;
} xAccessGetTPStateReq;
#define sz_xAccessGetTPStateReq          8

typedef struct  {
    BYTE        type; /* X_Reply */
    BYTE        data1;
    CARD16      sequenceNumber B16;    
    CARD32      length B32;    
    CARD16      state B16;
    CARD16      pad0 B16;
    CARD32      pad1 B32;
    CARD32      pad2 B32;
    CARD32      pad3 B32;
    CARD32      pad4 B32;
    CARD32      pad5 B32;
} xAccessGetTPStateReply;
#define sz_xAccessGetTPStateReply	32

typedef struct {
    CARD8       reqType;
    CARD8       accessReqType;
    CARD16      length B16;
    CARD16      state B16;
    CARD16      pad0 B16;
    CARD32      screen B32;
} xAccessSetTPStateReq;
#define sz_xAccessSetTPStateReq      12

typedef struct {
    CARD8       reqType;
    CARD8       accessReqType;
    CARD16      length B16;
    CARD16      mode B16;
    CARD16      pad0 B16;
    CARD32      rid B32;
} xAccessSetClientTCBReq;
#define sz_xAccessSetClientTCBReq     12

typedef struct {
    CARD8       reqType;
    CARD8       accessReqType;
    CARD16      length B16;
    CARD32      rid B32;
} xAccessGetClientTCBReq;
#define sz_xAccessGetClientTCBReq          8

typedef struct  {
    BYTE        type; /* X_Reply */
    BYTE        data1;
    CARD16      sequenceNumber B16;    
    CARD32      length B32;    
    CARD16      mode B16;
    CARD16      pad0 B16;
    CARD32      pad1 B32;
    CARD32      pad2 B32;
    CARD32      pad3 B32;
    CARD32      pad4 B32;
    CARD32      pad5 B32;
} xAccessGetClientTCBReply;
#define sz_xAccessGetClientTCBReply	32

typedef struct {
    CARD8       reqType;
    CARD8       accessReqType;
    CARD16      length B16;
    CARD16      mode B16;
    CARD16      pad0 B16;
    CARD32      screen B32;
} xAccessSetMonoModeReq;
#define sz_xAccessSetMonoModeReq      12


typedef struct {
    CARD8       reqType;
    CARD8       accessReqType;
    CARD16      length B16;
    CARD16      state B16;
    CARD16      pad0 B16;
    CARD32      screen B32;
} xAccessGetMonoModeReq;
#define sz_xAccessGetMonoModeReq      12


typedef struct  {
    BYTE        type; /* X_Reply */
    BYTE        data1;
    CARD16      sequenceNumber B16;    
    CARD32      length B32;    
    CARD16      mode B16;
    CARD16      pad0 B16;
    CARD32      pad1 B32;
    CARD32      pad2 B32;
    CARD32      pad3 B32;
    CARD32      pad4 B32;
    CARD32      pad5 B32;
} xAccessGetMonoModeReply;
#define sz_xAccessGetMonoModeReply	32

typedef struct {
    CARD8       reqType;
    CARD8       accessReqType;
    CARD16      length B16;
    CARD32      rid B32;
    CARD32      screen B32; 
} xAccessSetMonoLabelReq;
#define sz_xAccessSetMonoLabelReq          12

typedef struct {
    CARD8       reqType;
    CARD8       accessReqType;
    CARD16      length B16;
    CARD32      screen; 
    CARD32      pad0 B32;
} xAccessGetMonoLabelReq;
#define sz_xAccessGetMonoLabelReq          12

typedef struct  {
    BYTE        type; /* X_Reply */
    BYTE        data1;
    CARD16      sequenceNumber B16;    
    CARD32      length B32; 
    CARD32      uid B32;
    CARD32      label B32;     
    CARD32      pad0 B32;
    CARD32      pad1 B32;
    CARD32      pad2 B32;
    CARD32      pad3 B32;
} xAccessGetMonoLabelReply;
#define sz_xAccessGetMonoLabelReply	32


/*
 *  Event Structures.
 */
typedef struct {
        BYTE    type;
        BYTE    unused;
        CARD16  sequenceNumber B16;
        CARD32  unused1 B32;
        CARD32  unused2 B16;
        CARD32  unused3 B32;
        CARD32  unused4 B32;
        CARD32  unused5 B32;
        CARD32  unused6 B32;
        CARD32  unused7 B32;
} xAccessGrabNotifyEvent;

typedef struct {
        BYTE    type;
        BYTE    unused;
        CARD16  sequenceNumber B16;
        CARD32  unused1 B32;
        CARD32  unused2 B32;
        CARD32  unused3 B32;
        CARD32  unused4 B32;
        CARD32  unused5 B32;
        CARD32  unused6 B32;
        CARD32  unused7 B32;
} xAccessLabelChangeEvent;

typedef struct {
        BYTE    type;
        BYTE    unused;
        CARD16  sequenceNumber B16;
        CARD32  unused1 B32;
        CARD32  unused2 B32;
        CARD32  unused3 B32;
        CARD32  unused4 B32;
        CARD32  unused5 B32;
        CARD32  unused6 B32;
        CARD32  unused7 B32;
} xAccessTPChangeEvent;

#ifndef _SGIACCESS_SERVER_

typedef struct {
        int type;              /* of event */
        unsigned long serial;  /* # of last request processed by server */
        int send_event;        /* true if this came from a SendEvent request */
        Display *display;      /* Display the event was read from */
} XAccessGrabNotifyEvent;

typedef struct {
        int type;              /* of event */
        unsigned long serial;  /* # of last request processed by server */
        int send_event;        /* true if this came from a SendEvent request */
        Display *display;      /* Display the event was read from */
} XAccessLabelChangeEvent;

typedef struct {
        int type;              /* of event */
        unsigned long serial;  /* # of last request processed by server */
        int send_event;        /* true if this came from a SendEvent request */
        Display *display;      /* Display the event was read from */
} XAccessTPChangeEvent;

#endif



