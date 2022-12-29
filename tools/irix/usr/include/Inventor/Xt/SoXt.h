/*
 * Copyright 1991-1996, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED
 *
 * UNPUBLISHED -- Rights reserved under the copyright laws of the United
 * States.   Use of a copyright notice is precautionary only and does not
 * imply publication or disclosure.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to restrictions
 * as set forth in FAR 52.227.19(c)(2) or subparagraph (c)(1)(ii) of the Rights
 * in Technical Data and Computer Software clause at DFARS 252.227-7013 and/or
 * in similar or successor clauses in the FAR, or the DOD or NASA FAR
 * Supplement.  Contractor/manufacturer is Silicon Graphics, Inc.,
 * 2011 N. Shoreline Blvd. Mountain View, CA 94039-7311.
 *
 * THE CONTENT OF THIS WORK CONTAINS CONFIDENTIAL AND PROPRIETARY
 * INFORMATION OF SILICON GRAPHICS, INC. ANY DUPLICATION, MODIFICATION,
 * DISTRIBUTION, OR DISCLOSURE IN ANY FORM, IN WHOLE, OR IN PART, IS STRICTLY
 * PROHIBITED WITHOUT THE PRIOR EXPRESS WRITTEN PERMISSION OF SILICON
 * GRAPHICS, INC.
 */
/*
* Copyright (C) 1990-93   Silicon Graphics, Inc.
*
_______________________________________________________________________
______________  S I L I C O N   G R A P H I C S   I N C .  ____________
|
|   $Revision: 2.3 $
|
|   This static class provides routines for Inventor/Xt compatibility.
|
|   Author(s): Nick Thompson, Paul Isaacs, David Mott, Gavin Bell
|		Alain Dumesny
|
______________  S I L I C O N   G R A P H I C S   I N C .  ____________
_______________________________________________________________________
*/

#ifndef _SO_XT_
#define _SO_XT_

#include <X11/Intrinsic.h>
#include <X11/extensions/XI.h>
#include <Xm/Xm.h>
#include <Inventor/SbBasic.h>
#include <Inventor/SbLinear.h>

class SbPList;
class SoEvent;
class SoXtEventHandler;

class SoXt {
  public:
    // This binds Inventor with Xt so that they may work together.
    // It calls SoDB::init(), SoNodeKit::init(), SoInteraction::init
    // and XtAppInitialize, and returns the top level shell widget.
    static Widget           init(const char *appName,
                                 const char *className = "Inventor");

    // This alternate form of init allows the app to initialize Xt.
    // This calls SoDB::init(), SoNodeKit::init(), SoInteraction::init
    static void             init(Widget topLevelWidget);

    // This retrieves and dispatches events (loops forever).
    // Unlike Xt which ignores extension devices, this mainLoop() 
    // will dispatch events from input extension devices like the spaceball.
    // It calls SoXt::nextEvent() and SoXt::dispatchEvent() to do this.
    static void             mainLoop();
    
    // Get the nextEvent() by calling XtAppNextEvent().
    // appContext can come from SoXt::getAppContext().
    static void		    nextEvent(XtAppContext appContext, XEvent *event)
				{ XtAppNextEvent(appContext, event); }

    // Dispatch the passed event to a handler. Normal events are dispatched
    // by calling XtDispatchEvent(). Events from input extension devices
    // are dispatched by code found here.
    // This returns True if a handler was found, else it returns False.
    static Boolean	    dispatchEvent(XEvent *event);

    // These are access routines
    static XtAppContext     getAppContext();
    static Display *        getDisplay();
    static Widget           getTopLevelWidget();
    
    //
    // Convenience routines
    //
    
    // Convenience routine which shows/hides the passed widget.
    //
    // for a shell widget, this is equivalent to calling:
    //		XtRealizeWidget() + XMapWindow()
    //	    or	XMapRaised() if window already exists (raise and de-iconify)
    //	    hide() will then call XUnmapWindow() (instead of XUnrealizeWidget
    //	    which doesn't generate unmap events and destroys the windows).
    //
    // for a subwidget, those simply calls XtManageChild() and XtUnmanageChild().
    //
    static void		    show(Widget widget);
    static void		    hide(Widget widget);
    
    // Convenience routines to convert a char* to an XmString and back.
    // Encoding uses the XmSTRING_DEFAULT_CHARSET.
    // The app is responsible for freeing memory afterwards.
    // (Call XmStringFree() to free an XmString, and free() to free the char*.)
    static XmString	    encodeString(char *s);
    static char *	    decodeString(XmString xs);
    
    // Convenience routine which sets/gets the size of the given widget
    // (Equivalent to calling XtSetValues()/XtGetValues() on XtNheight
    // and XtNwidth widget resources).
    static void		    setWidgetSize(Widget w, const SbVec2s &size);
    static SbVec2s	    getWidgetSize(Widget w);
    
    // Convenience routine which will return the ShellWidget 
    // containing the given widget. The widget tree is traversed up until
    // a shell widget is found (using XtIsShell()).
    static Widget	    getShellWidget(Widget w);
    
    // Convenience routine which brings a simple motif error dialog
    // box displaying the given error string(s) and window title. The OK
    // button, which distroys the dialog, is the only button displayed.
    // The argument widget is used to create the error dialog (using 
    // XmCreateErrorDialog()) which will be centered around
    static void		    createSimpleErrorDialog(
				    Widget widget, char *dialogTitle, 
				    char *errorStr1, char *errorStr2 = NULL);
    
    // Convenience routine which gets visual args for the popup planes.
    // These args can then be passed in to XmCreatePulldownMenu or
    // XmCreatePopupMenu to create menus in the popup planes.
    // registerColormapLoad() must be called for each pulldown menu to
    // properly load/unload the overlay color map on the shell when needed.
    static void		    getPopupArgs(
				Display *d, int scr,
				ArgList args, int *n);
    
    // Convenience routine which will register map/unmap callbacks to 
    // load and unload the pulldown menu color map right before the menu
    // is about to be posted. This should be called when creating 
    // pulldown or popup menus in the overlays. This will make sure that
    // the right color map is loaded into the shell widget (to make
    // the pulldown/popup look right) and remove it when no longer needed 
    // (to make sure the OpenGL overlay widget color map is correctly loaded
    // for 8 bit machines).
    static void		    registerColormapLoad(Widget widget, Widget shell);
    
    // Convenience routine to insert/remove the given widget colormap onto the
    // supplied shell widget. This will not replace the existing installed
    // colormaps (or list of windows), but instead insert the new 
    // colormap first into the existing list using XGetWMColormapWindows() and 
    // XSetWMColormapWindows().
    static void		    addColormapToShell(Widget widget, Widget shell);
    static void		    removeColormapFromShell(Widget widget, Widget shell);

SoINTERNAL public:
    // Add/remove the passed event handler for X extension device events
    // (Xt does not handle extension events.)
    // Extension event types are queried from the server at runtime.
    static void		    addExtensionEventHandler(
				Widget w,
				int extensionEventType,
				XtEventHandler proc, 
				XtPointer clientData);
    static void		    removeExtensionEventHandler(
				Widget w,
				int extensionEventType,
				XtEventHandler proc, 
				XtPointer clientData);
  protected:
    static void		    getExtensionEventHandler(
				XEvent *event, 
				Widget &w, 
				XtEventHandler &proc, 
				XtPointer &clientData);

  private:
    static Widget           mainWidget;
    static SoXtEventHandler *eventHandler;
    static SbPList	    *handlerList;
};

#endif  /* _SO_XT_ */
