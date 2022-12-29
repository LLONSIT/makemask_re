/* $TOG: Xinerama.h /main/3 1998/02/13 13:08:51 kaleb $ */
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

/*  
 *	Xinerama definitions
 */

#ifndef _XINERAMAEXT
#define _XINERAMAEXT


/* THIS IS NOT AN X PROJECT TEAM SPECIFICATION */
#include <X11/Xfuncproto.h>
#include <X11/Xlib.h>       /* Display, XRectangle, etc. */

_XFUNCPROTOBEGIN

/*
 * Xinerama Xorg public interface.
 *
 * Since Xinerama is about to become a proposal for a standard, changes may
 * still occur to this interface.
 *
 * Interface to be finalized.
 */

extern Bool XineramaQueryExtension(
#if NeedFunctionPrototypes
    Display             *dpy,
    int                 *event_basep,
    int                 *error_basep
#endif
);
#pragma optional XineramaQueryExtension
	    
extern Status XineramaQueryVersion(
#if NeedFunctionPrototypes
    Display             *dpy, 
    int                 *major_versionp, 
    int                 *minor_versionp
#endif
);

extern Bool XineramaActive(
#if NeedFunctionPrototypes
    Display             *dpy,
    int                 screen_number
#endif
);

extern Status XineramaGetData(
#if NeedFunctionPrototypes
    Display             *dpy,
    int                 screen_number,
    XRectangle          **screen_rects,
    int                 *num_rects
#endif
);
#pragma optional XineramaGetData

/* XineramaGetInfo will be deprecated */
extern Status XineramaGetInfo(
#if NeedFunctionPrototypes
    Display             *dpy,
    int                 screen_number,
    XRectangle          **screen_rects,
    int                 *num_rects
#endif
);

extern Status XineramaGetCenterHint(
#if NeedFunctionPrototypes
    Display             *dpy,
    int                 screen_number,
    int                 *x,
    int                 *y
#endif
);  


/*
 * Deprecated public interface.
 * It is strongly recommanded not to use these functions.
 * The Xinerama Xorg public interface (see above) replaces the interface
 * below.
 */
/* There are no deprecated public functions at this time. */



/*
 * SGI private Xinerama interface. Internal use only !
 * 
 * A new SGI-XINERAMA extension is introduced in order to guaranty the full
 * SGI internal API.
 * 
 * SGIXinerama* functions replace the older _Xinerama* ones.
 * - Backward runtime compatibility is provided (ie. compiled applications
 *   using the _Xinerama* functions will still work.
 * - For compilation, use the new SGIXinerama* functions. Check for the
 *   SGIXinerama version to know which API is supported.
 * 
 */

/*
 * API supported by SGIXinerama version 1.2
 */

extern Bool SGIXineramaQueryExtension(
#if NeedFunctionPrototypes
    Display             *dpy,
    int                 *event_basep,
    int                 *error_basep
#endif
);
#pragma optional SGIXineramaQueryExtension
	    
extern Status SGIXineramaQueryVersion(
#if NeedFunctionPrototypes
    Display             *dpy, 
    int                 *major_versionp, 
    int                 *minor_versionp
#endif
);

extern Bool SGIXineramaActive(
#if NeedFunctionPrototypes
    Display             *dpy,
    int                 screen_number
#endif
);

extern Status SGIXineramaGetData(
#if NeedFunctionPrototypes
    Display             *dpy,
    int                 screen_number,
    XRectangle          **screen_rects,
    int                 *num_rects
#endif
);
#pragma optional SGIXineramaGetData

/* SGIXineramaGetInfo will be deprecated */
extern Status SGIXineramaGetInfo(
#if NeedFunctionPrototypes
    Display             *dpy,
    int                 screen_number,
    XRectangle          **screen_rects,
    int                 *num_rects
#endif
);

extern Status SGIXineramaGetCenterHint(
#if NeedFunctionPrototypes
    Display             *dpy,
    int                 screen_number,
    int                 *x,
    int                 *y
#endif
);  

extern Status SGIXineramaQuerySibling (
#if NeedFunctionPrototypes
    Display		*dpy,
    Drawable		drawable,
    Drawable	        **siblings,
    int			*num_siblings
#endif
);

extern Status SGIXineramaGetVisualData (
#if NeedFunctionPrototypes
    Display		*dpy,
    int                 xin_screen_num,
    int			*nscreens,
    int			**ids,
    int			**configs,
    int			*nconfigs,
    int			*nattribs
#endif
);

extern Status SGIXineramaGetFBConfigData (
#if NeedFunctionPrototypes
    Display		*dpy,
    int                 xin_screen_num,
    int			*nscreens,
    int			**ids,
    int			**configs,
    int			*nconfigs,
    int			*nattribs
#endif
);

extern Status SGIXineramaGetDrawableGeometry (
#if NeedFunctionPrototypes
    Display             *dpy,
    Drawable            drawable,
    int                 *x,
    int                 *y,
    int                 *width,
    int                 *height
#endif
);

extern Status SGIXineramaGetFullData(
#if NeedFunctionPrototypes
    Display             *dpy,
    int                 xin_screen_num,
    XRectangle          **screen_rects,
    XRectangle          **screen_viewports,
    int                 *num_rects
#endif
);
#pragma optional SGIXineramaGetFullData

/* SGIXineramaGetFullInfo will be deprecated */
extern Status SGIXineramaGetFullInfo(
#if NeedFunctionPrototypes
    Display             *dpy,
    int                 xin_screen_num,
    XRectangle          **screen_rects,
    XRectangle          **screen_viewports,
    int                 *num_rects
#endif
);

extern Display *SGIXineramaOpenAwareDisplay (
#if NeedFunctionPrototypes
    register _Xconst char *display
#endif
);


/*
 * API added in SGIXinerama version 1.3
 */

extern Status SGIXineramaManageAwareClients (
#if NeedFunctionPrototypes
    Display             *dpy
#endif
);

extern Bool SGIXineramaHasSibling (
#if NeedFunctionPrototypes
    Display		*dpy,
    Drawable		drawable
#endif
);

_XFUNCPROTOEND

#endif

/* $TOG: Xinerama.h /main/3 1998/02/13 13:08:51 kaleb $ */
