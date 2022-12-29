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
 |	SoEvent
 |
 |   Author(s): David Mott, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_EVENT_
#define  _SO_EVENT_

#include <Inventor/SbBasic.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/SbLinear.h>
#include <Inventor/SbTime.h>
#include <Inventor/SoType.h>

class SoEvent {
  public:
  
    // Constructor and destructor
    SoEvent();
    virtual ~SoEvent();
    
    // returns typeId of this event
    virtual SoType	getTypeId() const;
    
    // typeId of the class
    static SoType	getClassTypeId() { return classTypeId; }
    
    // returns TRUE if event is of given type or is derived from it
    SbBool		isOfType(SoType type) const;
    
    // returns the time stamp specifying when this event occurred
    void		setTime(SbTime t)		{ timestamp = t; }
    SbTime		getTime() const			{ return timestamp; }
    
    // set/get window pixel position of the locator when the event occurred.
    // position is relative to the lower left corner of the viewport
    void		setPosition(const SbVec2s &p)	{ position = p; }
    const SbVec2s &	getPosition() const		{ return position; }

    // get position reletive to the specified viewport bounds
    const SbVec2s &	getPosition(const SbViewportRegion &vpRgn) const;

    // get position reletive to the specified viewport bounds
    // and normalize this value between 0.0 and 1.0
    const SbVec2f & getNormalizedPosition(const SbViewportRegion &vpRgn) const;

    // set the state of the modifier keys when the event occurred
    void		setShiftDown(SbBool isDown)	{ shiftDown = isDown; }
    void		setCtrlDown(SbBool isDown)	{ ctrlDown = isDown; }
    void		setAltDown(SbBool isDown)	{ altDown = isDown; }
    
    // return the state of the modifier keys when the event occurred
    SbBool		wasShiftDown() const		{ return shiftDown; }
    SbBool		wasCtrlDown() const		{ return ctrlDown; }
    SbBool		wasAltDown() const		{ return altDown; }
    
  SoINTERNAL public:
    // Initializes base event class
    static void		initClass();

    // Initialize ALL Inventor event classes
    static void		initClasses();
    
  private:
    // all of these are set according to when the event occurred
    SbTime		timestamp;  // time the event occurred
    SbBool		shiftDown;  // TRUE if shift key was down 
    SbBool		ctrlDown;   // TRUE if ctrl key was down 
    SbBool		altDown;    // TRUE if alt key was down 

    SbVec2s		position;   // locator position when event occurred
    SbVec2s		viewportPos;	// position relative to viewport
    SbVec2f		normalizedPos;	// normalized position

    static SoType	classTypeId; // base typeId for all events
};


#endif /* _SO_EVENT_ */
