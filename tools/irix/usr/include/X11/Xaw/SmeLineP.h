/*
 * $Xorg: SmeLineP.h,v 1.4 2001/02/09 02:03:46 xorgcvs Exp $
 *
Copyright 1989, 1998  The Open Group

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
 *
 * Author:  Chris D. Peterson, MIT X Consortium
 */

/* 
 * SmeLineP.h - Private definitions for SmeLine widget
 * 
 */

#ifndef _XawSmeLineP_h
#define _XawSmeLineP_h

/***********************************************************************
 *
 * SmeLine Widget Private Data
 *
 ***********************************************************************/

#include <X11/Xaw/SmeP.h>
#include <X11/Xaw/SmeLine.h>

/************************************************************
 *
 * New fields for the SmeLine widget class record.
 *
 ************************************************************/

typedef struct _SmeLineClassPart {
  XtPointer extension;
} SmeLineClassPart;

/* Full class record declaration */
typedef struct _SmeLineClassRec {
    RectObjClassPart    rect_class;
    SmeClassPart	sme_class;
    SmeLineClassPart	sme_line_class;
} SmeLineClassRec;

extern SmeLineClassRec smeLineClassRec;

/* New fields for the SmeLine widget record */
typedef struct {
    /* resources */
    Pixel foreground;		/* Foreground color. */
    Pixmap stipple;		/* Line Stipple. */
    Dimension line_width;	/* Width of the line. */

    /* private data.  */

    GC gc;			/* Graphics context for drawing line. */
} SmeLinePart;

/****************************************************************
 *
 * Full instance record declaration
 *
 ****************************************************************/

typedef struct _SmeLineRec {
  ObjectPart     object;
  RectObjPart    rectangle;
  SmePart	 sme;
  SmeLinePart	 sme_line;
} SmeLineRec;

/************************************************************
 *
 * Private declarations.
 *
 ************************************************************/

#endif /* _XawSmeLineP_h */
