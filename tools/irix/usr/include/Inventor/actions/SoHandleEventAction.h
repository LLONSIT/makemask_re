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
 |   $Revision: 2.2 $
 |
 |   Description:
 |	Defines the SoHandleEventAction class
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_HANDLE_EVENT_ACTION_
#define  _SO_HANDLE_EVENT_ACTION_

#include <Inventor/SbViewportRegion.h>
#include <Inventor/actions/SoSubAction.h>
#include <Inventor/actions/SoRayPickAction.h>

class SoEvent;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoHandleEventAction
//
//  Event handling action. This traverses a graph looking for a node
//  or nodes interested in a particular event.
//
//////////////////////////////////////////////////////////////////////////////

class SoHandleEventAction : public SoAction {

    SO_ACTION_HEADER(SoHandleEventAction);

  public:
    // Constructor takes viewport region to use for handling events.
    SoHandleEventAction(const SbViewportRegion &viewportRegion);

    // Destructor
    virtual ~SoHandleEventAction();

    // Sets current viewport region to use for the event processing
    void		setViewportRegion(const SbViewportRegion &newRegion);


    // Returns current viewport region
    const SbViewportRegion &getViewportRegion() const	{ return vpRegion; }


    // Sets/returns the event to handle
    void		setEvent(const SoEvent *ev)	{ event = ev; }
    const SoEvent *	getEvent() const		{ return event; }

    // Sets/returns whether any node has yet handled the event
    void		setHandled()		{ setTerminated(TRUE); }
    SbBool		isHandled() const	{ return hasTerminated(); }

    // grab() - node will receive all events until release() is called.
    // grabber() returns which node is currently grabbing events.
    void    	    	setGrabber(SoNode *node);
    void    	    	releaseGrabber()	    { setGrabber(NULL); }
    SoNode *	    	getGrabber() const	    { return eventGrabber; }

    // Sets/returns the root node used for initiating a pick action
    // for those nodes that want to know who is under the cursor
    void		setPickRoot(SoNode *node);
    SoNode *		getPickRoot() const		{ return pickRoot; }

    // Set the radius (in pixels) around the point. This is used when
    // testing the ray against lines and points.
    void		setPickRadius(float radiusInPixels) 
			    { pickAct->setRadius(radiusInPixels); }

    // Returns the object hit (as an SoPickedPoint) by performing a
    // pick based on the current mouse location as specified in the
    // event the action is being applied for. This initiates a pick
    // action if necessary to find this object. The storage for the
    // pickedPoint remains valid as long as the SoHandleEventAction is
    // not re-used or deleted.
    const SoPickedPoint *getPickedPoint();

    // Return a list of objects hit, sorted from front to back
    const SoPickedPointList &getPickedPointList();

  SoINTERNAL public:
    static void		initClass();

  protected:
    // Initiates action on graph
    virtual void	beginTraversal(SoNode *node);

  private:
    const SoEvent	*event;		// Event being handled
    SoNode		*pickRoot;	// Root node for initiating picking
    SoPickedPoint	*pickedPoint;	// PickedPoint from last pick
    SbBool		pickValid;	// Whether last pick is still valid
    SbBool		usedPickAll;	// TRUE if last pick used pickAll=TRUE
    SoRayPickAction	*pickAct;	// Pick action
    SoNode  	    	*eventGrabber;  // Event grabber - gets all events
    SbViewportRegion	vpRegion;	// Current viewport region
};

#endif /* _SO_HANDLE_EVENT_ACTION_ */
