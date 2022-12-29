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
 |	SoSpaceballButtonEvent
 |
 |   Author(s): David Mott, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_SPACEBALL_BUTTON_EVENT_
#define  _SO_SPACEBALL_BUTTON_EVENT_

#include <Inventor/SbBasic.h>
#include <Inventor/events/SoButtonEvent.h>

// some convenience macros for determining if an event matches
#define SO_SPACEBALL_PRESS_EVENT(EVENT,BUTTON) \
    (SoSpaceballButtonEvent::isButtonPressEvent(EVENT, \
			SoSpaceballButtonEvent::BUTTON))

#define SO_SPACEBALL_RELEASE_EVENT(EVENT,BUTTON) \
    (SoSpaceballButtonEvent::isButtonReleaseEvent(EVENT, \
			SoSpaceballButtonEvent::BUTTON))



class SoSpaceballButtonEvent : public SoButtonEvent {

    SO_EVENT_HEADER();
    
  public:
    enum Button {
	ANY = 0, 
	BUTTON1 = 1, 
	BUTTON2 = 2, 
	BUTTON3 = 3, 
	BUTTON4 = 4, 
	BUTTON5 = 5, 
	BUTTON6 = 6, 
	BUTTON7 = 7, 
	BUTTON8 = 8, 
	PICK = 9
    };
    
    // constructor
    SoSpaceballButtonEvent();
    virtual ~SoSpaceballButtonEvent();
    
    // which button generated the event, e.g. SoSpaceballButtonEvent::BUTTON1
    void		setButton(SoSpaceballButtonEvent::Button b)
	{ button = b; }
    SoSpaceballButtonEvent::Button	getButton() const
	{ return button; }
    
    // convenience routines to see if an SoEvent is a press or release
    // of the passed spaceball button
    static SbBool	isButtonPressEvent(
			    const SoEvent *e,
			    SoSpaceballButtonEvent::Button whichButton);
			    
    static SbBool	isButtonReleaseEvent(
			    const SoEvent *e,
			    SoSpaceballButtonEvent::Button whichButton);
    
  SoINTERNAL public:
    static void		initClass();
    
  private:
    Button   		button;		    // which button
};

#endif /* _SO_SPACEBALL_BUTTON_EVENT_ */
