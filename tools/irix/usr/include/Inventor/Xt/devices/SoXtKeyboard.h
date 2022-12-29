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
//  -*- C++ -*-

/*
 *
 _______________________________________________________________________
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 |
 |   $Revision: 2.0 $
 |
 |   Classes:
 |	SoXtMouse
 |
 |   Author(s): David Mott, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_XT_KEYBOARD_
#define  _SO_XT_KEYBOARD_

#include <X11/X.h>
#include <Inventor/Xt/devices/SoXtDevice.h>
#include <Inventor/events/SoKeyboardEvent.h>

#define SO_XT_ALL_KEYBOARD_EVENTS (KeyPressMask | KeyReleaseMask)

class SoXtKeyboard : public SoXtDevice {
  public:
    //
    // valid event mask values:
    //	    KeyPressMask	- keyboard press events
    //	    KeyReleaseMask	- keyboard release events
    // Bitwise OR these to specify whichEvents this device should queue.
    //
    SoXtKeyboard(EventMask mask = SO_XT_ALL_KEYBOARD_EVENTS);
    ~SoXtKeyboard();
    
    // these functions will enable/disable this device for the passed widget.
    // the callback function f will be invoked when events occur in w.
    // data is the clientData which will be passed.
    virtual void        enable(Widget w, XtEventHandler f,
			       XtPointer data, Window win = NULL);
    virtual void        disable(Widget w, XtEventHandler f, XtPointer data);
    
    //
    // this converts an X event into an SoEvent,
    // returning NULL if the event is not from this device.
    //
    virtual const SoEvent * translateEvent(XAnyEvent *xevent);
  
  private:
    EventMask		eventMask;	// X event interest for this device
    SoKeyboardEvent	*keyEvent;	// keyboard press or release

    SoKeyboardEvent	*translateKeyEvent(XKeyEvent *ke, SoButtonEvent::State s);
};

#endif /* _SO_XT_KEYBOARD_ */
