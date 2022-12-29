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
 |	SoXtDevice
 |
 |   Author(s): David Mott, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_XT_DEVICE_
#define  _SO_XT_DEVICE_

#include <X11/Intrinsic.h>
#include <Inventor/SbLinear.h>
#include <Inventor/events/SoEvent.h>

class SoXtDevice {
  public:
    // these functions will enable/disable this device for the passed widget.
    // the callback function f will be invoked when events occur in w.
    // data is the clientData which will be passed.
    // For enable, the window is also passed, since Glx widgets can have
    // more than one window (normal, overlay, popup)
    virtual void        enable(Widget w, XtEventHandler f,
			       XtPointer data, Window win = NULL) = 0;
    virtual void        disable(Widget w, XtEventHandler f, XtPointer data) = 0;
    
    // this converts an X event into an SoEvent.
    // this returns NULL if the event is not from this device.
    virtual const SoEvent * translateEvent(XAnyEvent *xevent) = 0;

    // set the window size so that the device can correctly convert X
    // window coordinates (origin at top,left) into Inventor window
    // coordinates (origin at bottom,left).
    void		setWindowSize(const SbVec2s &s)	{ winSize = s; }
    const SbVec2s &	getWindowSize() const		{ return winSize; }

  protected:
    // set the window coordinate from the passed x,y value. This will flip
    // the y value to convert from X coordinates to So coordinates.
    inline void		setEventPosition(SoEvent *event, int x, int y) const;
    
  private:
    SbVec2s		winSize;    // size of the window this device works in
};

// Inline functions
void
SoXtDevice::setEventPosition(SoEvent *event, int x, int y) const
{
    event->setPosition(SbVec2s(x, (winSize[1] - 1) - y));
}

#endif /* _SO_XT_DEVICE_ */
