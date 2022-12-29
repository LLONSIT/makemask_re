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
 |	SoMouseButtonEvent
 |
 |   Author(s): David Mott, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_MOUSE_BUTTON_EVENT_
#define  _SO_MOUSE_BUTTON_EVENT_

#include <Inventor/SbBasic.h>
#include <Inventor/events/SoButtonEvent.h>

// some convenience macros for determining if an event matches

#define SO_MOUSE_PRESS_EVENT(EVENT,BUTTON) \
    (SoMouseButtonEvent::isButtonPressEvent(EVENT,SoMouseButtonEvent::BUTTON))

#define SO_MOUSE_RELEASE_EVENT(EVENT,BUTTON) \
    (SoMouseButtonEvent::isButtonReleaseEvent(EVENT,SoMouseButtonEvent::BUTTON))




class SoMouseButtonEvent : public SoButtonEvent {

    SO_EVENT_HEADER();
    
  public:
    enum Button {
	ANY = 0, 
	BUTTON1 = 1, 
	BUTTON2 = 2, 
	BUTTON3 = 3
    };
    
    // constructor
    SoMouseButtonEvent();
    virtual ~SoMouseButtonEvent();
    
    // set/get which button generated the event, either SO_MOUSE_BUTTON1, 
    // SO_MOUSE_BUTTON2, or SO_MOUSE_BUTTON3
    void		setButton(SoMouseButtonEvent::Button b)  { button = b; }
    SoMouseButtonEvent::Button	getButton() const	    { return button; }
    
    // convenience routines to see if an SoEvent is a press or release
    // of the passed mouse button
    static SbBool	isButtonPressEvent(
			    const SoEvent *e,
			    SoMouseButtonEvent::Button whichButton);
			    
    static SbBool	isButtonReleaseEvent(
			    const SoEvent *e,
			    SoMouseButtonEvent::Button whichButton);
    
  SoINTERNAL public:
    static void		initClass();
    
  private:
    Button   	    button;	// which button
};


#endif /* _SO_MOUSE_BUTTON_EVENT_ */
