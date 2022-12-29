/* $Xorg: CloseHook.h,v 1.5 2001/02/09 02:03:51 xorgcvs Exp $ */

/* 

Copyright 1988, 1998  The Open Group

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation.

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from The Open Group.

*/

/*
 * The interfaces described by this header file are for miscellaneous utilities
 * and are not part of the Xlib standard.
 */

#ifndef _XMU_CLOSEHOOK_H_
#define _XMU_CLOSEHOOK_H_

#include <X11/Xlib.h>
#include <X11/Xfuncproto.h>

typedef XPointer CloseHook;

typedef int (*XmuCloseHookProc)(
#if NeedFunctionPrototypes
    Display*	/* dpy */,
    XPointer	/* data */
#endif 
);

_XFUNCPROTOBEGIN

extern CloseHook XmuAddCloseDisplayHook(
#if NeedFunctionPrototypes
    Display *	/* dpy */,
    XmuCloseHookProc	/* proc */,
    XPointer	/* arg */
#endif
);

extern Bool XmuLookupCloseDisplayHook(
#if NeedFunctionPrototypes
    Display *	/* dpy */,
    CloseHook	/* handle */,
    XmuCloseHookProc	/* proc */,
    XPointer	/* arg  */
#endif
);

extern Bool XmuRemoveCloseDisplayHook(
#if NeedFunctionPrototypes
    Display *	/* dpy */,
    CloseHook	/* handle */,
    XmuCloseHookProc	/* proc */,
    XPointer	/* arg */
#endif
);

_XFUNCPROTOEND

#endif /* _XMU_CLOSEHOOK_H_ */
