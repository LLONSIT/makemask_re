/* $Xorg: ListP.h,v 1.4 2001/02/09 02:03:44 xorgcvs Exp $ */

/*
Copyright 1989, 1994, 1998  The Open Group

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
 * ListP.h - Private definitions for List widget
 * 
 * This is a List widget.  It allows the user to select an item in a list and
 * notifies the application through a callback function.
 *
 *	Created: 	8/13/88
 *	By:		Chris D. Peterson
 *                      MIT - Project Athena
 */

#ifndef _XawListP_h
#define _XawListP_h

/***********************************************************************
 *
 * List Widget Private Data
 *
 ***********************************************************************/

#include <X11/Xaw/SimpleP.h>
#include <X11/Xaw/List.h>

#define NO_HIGHLIGHT            XAW_LIST_NONE
#define OUT_OF_RANGE            -1
#define OKAY                     0

/* New fields for the List widget class record */

typedef struct {int foo;} ListClassPart;

/* Full class record declaration */
typedef struct _ListClassRec {
    CoreClassPart	core_class;
    SimpleClassPart	simple_class;
    ListClassPart	list_class;
} ListClassRec;

extern ListClassRec listClassRec;

/* New fields for the List widget record */
typedef struct {
    /* resources */
    Pixel	foreground;
    Dimension	internal_width, /* if not 3d, user sets directly. */
        	internal_height,
                column_space,	/* half of *_space is add on top/bot/left of*/
                row_space;	/* each item's text bounding box. half added to longest for right */
    int         default_cols;
    Boolean     force_cols,
                paste,
                vertical_cols;
    int         longest;	/* in pixels */
    int         nitems;		/* number of items in the list. */
    XFontStruct	*font;
    XFontSet 	fontset;	/* Sheeran, Omron KK, 93/03/05 */
    String *    list;		/* for i18n, always in multibyte format */
    XtCallbackList callback;

    /* private state */
    int         is_highlighted,	/* set to the item currently highlighted. */
                highlight,	/* set to the item that should be highlighted.*/
                col_width,	/* width of each column. */
                row_height,	/* height of each row. */
                nrows,		/* number of rows in the list. */
                ncols;		/* number of columns in the list. */
    GC		normgc,		/* a couple of GC's. */
                revgc,
                graygc;		/* used when inactive. */

    int         freedoms;       /* flags for resizing height and width */

} ListPart;


/****************************************************************
 *
 * Full instance record declaration
 *
 ****************************************************************/

typedef struct _ListRec {
    CorePart	core;
    SimplePart	simple;
    ListPart	list;
} ListRec;

#endif /* _XawListP_h */
