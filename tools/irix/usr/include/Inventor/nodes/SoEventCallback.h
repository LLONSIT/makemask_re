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
 |   $Revision: 2.1 $
 |
 |   Description:
 |	SoEventCallback node class - invokes callbacks when the handle
 |   event action is applied to this node.
 |
 |   Author(s): David Mott
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_EVENT_CALLBACK_
#define  _SO_EVENT_CALLBACK_

#include <Inventor/misc/SoCallbackList.h>
#include <Inventor/SoPath.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/actions/SoHandleEventAction.h>

class SoEvent;
class SoEventCallback;

// callback function prototypes
typedef void SoEventCallbackCB(void *userData, SoEventCallback *node);

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoEventCallback
//
//////////////////////////////////////////////////////////////////////////////

class SoEventCallback : public SoNode {

    SO_NODE_HEADER(SoEventCallback);

  public:
    // Constructor
    SoEventCallback();
    
    // Set the path to monitor - the callbacks are only invoked
    // if this path is picked. If path is NULL, then the callbacks
    // are invoked automatically on every event of the type specified
    // in setEventInterest, without a pick occurring.
    // This makes its own copy of path.
    void		setPath(SoPath *path);
    const SoPath *	getPath()		{ return pathOfInterest; }

    // Specify callback functions to be invoked. When invoked, the
    // callback will be passed userData, and a pointer to this. To
    // specify interest in all event types, pass
    // SoEvent::getClassTypeId() as the eventType. Else, pass the type
    // of event you are interested in (e.g.
    // SoLocation2Event::getClassTypeId() for mouse motion)
    void		addEventCallback(SoType eventType,
					 SoEventCallbackCB *f,
					 void *userData = NULL);
    void		removeEventCallback(SoType eventType,
					    SoEventCallbackCB *f,
					    void *userData = NULL);

    //////////////////////
    //
    // These all provide information to callback functions. They
    // return NULL when called from anywhere but a callback function.
    //
    
    // Returns the SoHandleEventAction being applied
    SoHandleEventAction *	getAction() const { return eventAction; }

    // Returns the event being handled by the action
    const SoEvent *		getEvent() const
	{ return (eventAction != NULL ? eventAction->getEvent() : NULL); }

    // Returns pick information from the action
    const SoPickedPoint *	getPickedPoint() const
	{ return (eventAction != NULL ? eventAction->getPickedPoint() : NULL);}
    
    //
    //////////////////////

    // Tells the node the event was handled. The callback function is
    // responsible for setting whether the event was handled or not.
    // If there is more than one callback function, all of them will be
    // invoked, regardless of whether one has handled the event or not.
    void		setHandled()
	{ if (eventAction != NULL) eventAction->setHandled(); }

    // Returns whether the event was handled
    SbBool		isHandled() const
	{ return (eventAction != NULL) ? eventAction->isHandled() : FALSE; }
    
    // Tells the event callback node to grab events or release the
    // grab. While grabbing, the node will consume all events;
    // however, the callback functions are still only invoked for
    // events of interest.
    void		grabEvents()
	{ if (eventAction != NULL) eventAction->setGrabber(this); }

    void		releaseEvents()
	{ if (eventAction != NULL) eventAction->releaseGrabber(); }

  SoINTERNAL public:
    static void		initClass();	// initialize the class

  protected:
    // Destructor - protected since ref/unref is what should destroy this
    virtual ~SoEventCallback();

    // This will be called during handleEventAction traversal.
    virtual void    	handleEvent(SoHandleEventAction *ha);
    
  private:
    // Only invoke callbacks if this path was picked.
    // If path is NULL, always invoke callbacks.
    SoPath		*pathOfInterest;
    
    // List of callback functions, event types, and user data.
    SbPList *		cblist;
    
    // This is set for each SoHandleEventAction traversal of this node
    // so that the apps callback routine can invoke methods on the action.
    SoHandleEventAction	*eventAction;
    
    // This will look through cblist and invoke each callback function
    // that is interested in the passed event.
    void		invokeCallbacks(const SoEvent *e);
};

#endif /* _SO_EVENT_CALLBACK_ */
