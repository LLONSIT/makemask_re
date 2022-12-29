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
 |	Abstract base class for sensors that attach to some part of a
 |	scene graph and detect changes to it. A data sensor is scheduled
 |	when a change is made to the thing to which it is attached. This
 |	change is detected via the notification mechanism.
 |
 |   Author(s)		: Nick Thompson, Gavin Bell, Paul Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_DATA_SENSOR_
#define  _SO_DATA_SENSOR_

class SoBase;
class SoNode;
class SoPath;
class SoNotList;

#include <Inventor/sensors/SoDelayQueueSensor.h>

class SoDataSensor : public SoDelayQueueSensor {

  public:
    // Constructors. The second form takes standard callback function and data
    SoDataSensor();
    SoDataSensor(SoSensorCB *func, void *data);

    // Destructor
    virtual ~SoDataSensor();

    // Sets a callback to call when the item (SoBase) to which the
    // sensor is attached is about to be deleted. Set this to NULL to
    // remove the callback.
    void		setDeleteCallback(SoSensorCB *func, void *data = NULL)
	{ deleteFunc = func; deleteData = data; }

    // This may be called from the callback function of immediate
    // (priority 0) sensors. It returns the node in the scene graph
    // that caused the sensor to be scheduled and triggered, if
    // there was such a node.  If there wasn't such a node, or if the
    // sensor is not an immediate sensor, NULL is returned.
    // This is only valid for immediate sensors because if the sensor
    // isn't immediate then the sensor may be scheduled several times,
    // and there isn't one particular node that can be said to have
    // caused the trigger.
    SoNode *		getTriggerNode() const;

    // Like getTriggerNode(), but returns the field that started
    // notification (NULL if the sensor isn't priority 0 or if
    // notification didn't start at a field).
    SoField *		getTriggerField() const;
    
    // Returns the path from the node to which this sensor is attached
    // down to the child node that changed.  setTriggerPathFlag(TRUE)
    // must be called before the sensor is scheduled, or this will
    // return NULL.  It will also return NULL if the sensor is not
    // immediate or if the notification doesn't go through a node
    SoPath *		getTriggerPath() const;

    // Sets/returns the flag that indicates whether the trigger path
    // (see getTriggerPath()) is available to callback methods. This
    // is FALSE by default. Note that setting this to TRUE will add a
    // little overhead when the sensor is notified.
    void		setTriggerPathFlag(SbBool flag) { doTrigPath = flag; }
    SbBool		getTriggerPathFlag() const	{ return doTrigPath; }

    // Override unschedule() to reset trigNode and trigPath.
    virtual void unschedule();

  SoINTERNAL public:
    // Override trigger to reset trigNode and trigPath, if
    // necessary.
    virtual void trigger();

    // Propagates modification notification through an instance. By
    // default, this schedules the sensor to be triggered and saves
    // some information from the notification list for use by the
    // callback function.  Called by SoBase.
    virtual void	notify(SoNotList *list);

    // This is called when the base (path, field, node, whatever) is
    // deleted. All subclasses must implement this to do the right
    // thing.
    virtual void	dyingReference() = 0;

  protected:
    // Invokes the delete callback
    void		invokeDeleteCallback();

  private:
    SoSensorCB		*deleteFunc;    // CB and data for when attached SoBase
    void		*deleteData;	//     is about to be deleted
    SoNode		*trigNode;	// Node that triggered sensor
    SoField		*trigField;	// Field that triggered sensor
    SoPath		*trigPath;	// Path to trigNode
    SbBool		doTrigPath;	// Whether to compute trigger path
};

#endif  /* _SO_DATA_SENSOR_ */
