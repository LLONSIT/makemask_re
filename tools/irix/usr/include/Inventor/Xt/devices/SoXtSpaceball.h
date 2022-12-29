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
 |	SoXtSpaceball
 |
 |   Author(s): David Mott
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_XT_SPACEBALL_
#define  _SO_XT_SPACEBALL_

#include <X11/X.h>
#include <X11/extensions/XInput.h>
#include <Inventor/Xt/SoXt.h>
#include <Inventor/Xt/devices/SoXtDevice.h>
#include <Inventor/events/SoMotion3Event.h>
#include <Inventor/events/SoSpaceballButtonEvent.h>

class SoXtSpaceball : public SoXtDevice {
  public:
    enum Mask {
	MOTION  = 0x01, 
	PRESS   = 0x02, 
	RELEASE = 0x04, 
	ALL     = 0x07
    };
    
    //
    // valid event mask values:
    //	    SoXtSpaceball::MOTION   - spaceball translation and rotation
    //	    SoXtSpaceball::PRESS    - spaceball button press
    //	    SoXtSpaceball::RELEASE  - spaceball button release
    //	    SoXtSpaceball::ALL	    - all spaceball events
    // Bitwise OR these to specify whichEvents this device should queue.
    //
    // The second constructor allows the spaceball to be attached
    // to a different display than the one used by SoXt::init().

    SoXtSpaceball(SoXtSpaceball::Mask mask = SoXtSpaceball::ALL);
    SoXtSpaceball(Display *d, SoXtSpaceball::Mask mask = SoXtSpaceball::ALL);
    ~SoXtSpaceball();
    
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
  
    // the spaceball reports rotations and translations as integers.
    // these values must be scaled to be useful. these methods allow
    // the scale values to be set. 
    // default values are .006 for translation and .006 for scale.
    void		setRotationScaleFactor(float f)    { rotScale = f; }
    float		getRotationScaleFactor() const     { return rotScale; }
    void		setTranslationScaleFactor(float f) { transScale = f; }
    float		getTranslationScaleFactor() const  { return transScale; }
    
    // Return whether or not the spaceball device exists for use.
    // Method with no argument checks on the primary display.
    static SbBool	exists() { return exists(SoXt::getDisplay()); }
    static SbBool	exists(Display *d);
    
  private:
    Mask	    	    eventMask;	    // X event interest for this device
    SoMotion3Event	    *motionEvent;   // spaceball rotation/translation
    SoSpaceballButtonEvent  *buttonEvent;   // spball button press/release
    
    // scale factors
    float		    rotScale;
    float		    transScale;
    
    // these event types are retrieved from the X server at run time
    int			motionEventType;
    int			buttonPressEventType;
    int			buttonReleaseEventType;

    // event classes passed to XSelectExtensionEvent
    XEventClass		eventClasses[3];    // max of 3 event classes for this
    int			numEventClasses;    // actual number we will queue
    int			eventTypes[3];	    // max of 3 event types for this
	
    // device id is set at runtime
    XDevice		*device;
    
    // event translators!
    SoMotion3Event	   *translateMotionEvent(XDeviceMotionEvent *me);
    SoSpaceballButtonEvent *translateButtonEvent(
				XDeviceButtonEvent *be,
				SoButtonEvent::State whichState);

    void constructorCommon(Display *d, SoXtSpaceball::Mask mask);		
};

#endif /* _SO_XT_SPACEBALL_ */
