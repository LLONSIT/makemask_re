/* $Xorg: MenuButtoP.h,v 1.4 2001/02/09 02:03:44 xorgcvs Exp $ 
 *
Copyright 1989,1998  The Open Group

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

/***********************************************************************
 *
 * MenuButton Widget
 *
 ***********************************************************************/

/*
 * MenuButtonP.h - Private Header file for MenuButton widget.
 *
 * This is the private header file for the Athena MenuButton widget.
 * It is intended to provide an easy method of activating pulldown menus.
 *
 * Date:    May 2, 1989
 *
 * By:      Chris D. Peterson
 *          MIT X Consortium 
 *          kit@expo.lcs.mit.edu
 */

#ifndef _XawMenuButtonP_h
#define _XawMenuButtonP_h

#include <X11/Xaw/MenuButton.h>
#include <X11/Xaw/CommandP.h>

/************************************
 *
 *  Class structure
 *
 ***********************************/


   /* New fields for the MenuButton widget class record */
typedef struct _MenuButtonClass 
{
  int makes_compiler_happy;  /* not used */
} MenuButtonClassPart;

   /* Full class record declaration */
typedef struct _MenuButtonClassRec {
  CoreClassPart	    core_class;
  SimpleClassPart	    simple_class;
  LabelClassPart	    label_class;
  CommandClassPart	    command_class;
  MenuButtonClassPart     menuButton_class;
} MenuButtonClassRec;

extern MenuButtonClassRec menuButtonClassRec;

/***************************************
 *
 *  Instance (widget) structure 
 *
 **************************************/

    /* New fields for the MenuButton widget record */
typedef struct {
  /* resources */
  String menu_name;

} MenuButtonPart;

   /* Full widget declaration */
typedef struct _MenuButtonRec {
    CorePart         core;
    SimplePart	     simple;
    LabelPart	     label;
    CommandPart	     command;
    MenuButtonPart   menu_button;
} MenuButtonRec;

#endif /* _XawMenuButtonP_h */


