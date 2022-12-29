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

#ifndef _SGIACCESS_H_
#define _SGIACCESS_H_

/*
 *  These are the defines for the accessReqType (minor opcode).
 */
#define X_AccessQueryVersion  	    0
#define X_AccessSetWindowLabel      1
#define X_AccessGetWindowLabel	    2
#define X_AccessSetClientPriv       3
#define X_AccessGetClientPriv       5
#define X_AccessSetTPState          6
#define X_AccessGetTPState          7
#define X_AccessSetClientTCB        8
#define X_AccessGetClientTCB        9
#define X_AccessSetMonoMode         10 
#define X_AccessGetMonoMode         11
#define X_AccessSetMonoLabel        12
#define X_AccessGetMonoLabel        13

#define AccessGrabNotifyEvent      0
#define AccessLabelChangeEvent     1
#define AccessTPChangeEvent        2
#define AccessNumberEvents         (AccessTPChangeEvent + 1)
	   
#define AccessNumberErrors			0

#ifndef _SGIACCESS_SERVER_

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */

#ifndef NeedWidePrototypes
#if defined(NARROWPROTO)
#define NeedWidePrototypes 0
#else
#define NeedWidePrototypes 1		/* default to make interropt. easier */
#endif
#endif

#ifdef __cplusplus			/* do not leave open across includes */
extern "C" {					/* for C++ V2.0 */
#endif

extern Status XAccessQueryVersion (
#if NeedFunctionPrototypes
    Display *		/* dpy */,
    int *		/* major_versionp */,
    int *		/* minor_versionp */,
    unsigned long *     /* access_features */
#endif
);

extern Status XAccessSetWindowLabel(
#if NeedFunctionPrototypes
    Display *		/* dpy */, 
    Window		/* window */,
    char *              /* label */
#endif
);

extern char * XAccessGetWindowLabel(
#if NeedFunctionPrototypes
    Display*		/* dpy */, 
    Window		/* window */
#endif
);

extern Status XAccessSetClientPriv(
#if NeedFunctionPrototypes
    Display *		/* dpy */, 
    Window              /* window */,
    unsigned long       /* privilege */
#endif
);

extern Status XAccessGetClientPriv(
#if NeedFunctionPrototypes
    Display *		/* dpy */, 
    Window              /* window */,
    unsigned long *     /* client_priv */
#endif
);

extern Status XAccessSetTPState(
#if NeedFunctionPrototypes
    Display *		/* dpy */, 
    int		        /* screen */,
    int                 /* state */
#endif
);

extern Status XAccessGetTPState(
#if NeedFunctionPrototypes
    Display *		/* dpy */, 
    int		        /* screen */,
    int *               /* state */
#endif
);

extern Status XAccessSetClientTCB(
#if NeedFunctionPrototypes
    Display *		/* dpy */,
    XID                 /* rid */,    
    int                 /* mode */
#endif
);

extern Status XAccessGetClientTCB(
#if NeedFunctionPrototypes
    Display *		/* dpy */, 
    XID		        /* rid */,
    int *               /* mode */
#endif
);

extern Status XAccessSetMonoMode(
#if NeedFunctionPrototypes
    Display *		/* dpy */,
    int		        /* screen */,
    int 		/* mode */
#endif
);

extern Status XAccessGetMonoMode(
#if NeedFunctionPrototypes
    Display *		/* dpy */, 
    int		        /* screen */,
    int *               /* mode */
#endif
);

extern Status XAccessSetMonoLabel(
#if NeedFunctionPrototypes
    Display *		/* dpy */,   
    int                 /* screen */,   
    XID                 /* rid */ 
#endif
);

extern Status XAccessGetMonoLabel(
#if NeedFunctionPrototypes
    Display *		/* dpy */, 
    int                 /* screen */, 
    unsigned long *     /* uid */,
    unsigned long *     /* label */
#endif
);

#endif
#endif 
