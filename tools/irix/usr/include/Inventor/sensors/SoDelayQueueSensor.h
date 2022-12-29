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
 |	Abstract base class for all sensors that are added to the delay
 |	queue, which means that they will be executed at some time in the
 |	future (when there is idle time, or when a user-defined timeout
 |	occurs-- see SoDB::setDelaySensorTimeout()).
 |
 |	Sensors in the delay queue are sorted by priorities. A priority of
 |	0 indicates that the sensor is immediate and should be triggered
 |	immediately when it is scheduled. Sensors with other priorities
 |	are sorted by increasing priority.
 |
 |   Author(s)		: Nick Thompson, Paul Strauss, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_DELAY_QUEUE_SENSOR_
#define  _SO_DELAY_QUEUE_SENSOR_

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoDelayQueueSensor
//
//
//////////////////////////////////////////////////////////////////////////////

#include <Inventor/sensors/SoSensor.h>

class SoDelayQueueSensor : public SoSensor {

  public:
    // Constructors. The second form takes standard callback function and data
    SoDelayQueueSensor();
    SoDelayQueueSensor(SoSensorCB *func, void *data);

    // Destructor
    virtual ~SoDelayQueueSensor();

    // Sets/returns the priority for the sensor. If the priority is
    // changed to 0 (immediate) and it is already scheduled, the
    // sensor is unscheduled and triggered.
    void		setPriority(uint32_t pri);
    uint32_t		getPriority() const		{ return priority; }

    // Returns default sensor priority
    static uint32_t getDefaultPriority()		{ return 100; }

    // Scheduling methods
    virtual void	schedule();
    virtual void	unschedule();
    virtual SbBool	isScheduled() const;

    // This method is overriden by IdleSensors to tell sensor manager
    // that they should only be processed when there really is idle
    // time (and not when the delay queue timeout expires).
    virtual SbBool	isIdleOnly() const;
  SoINTERNAL public:
    // Set/inquire counter when sensor was last triggered. This allows
    // the sensor manager to avoid triggering a sensor more than once
    // during the same call to processDelayQueue().
    void		setCounter(uint32_t c)		{ counter = c;  }
    uint32_t		getCounter() const		{ return counter; }

  protected:
    // Triggers the sensor, calling its callback function. This
    // overrides the method in SoSensor because it has to reset the
    // schedule flag before triggering.
    virtual void	trigger();

    SbBool		scheduled;	// Whether sensor is scheduled

  private:
    uint32_t		priority;	// Sensor priority
    uint32_t		counter;	// Used by sensor manager

    // Returns TRUE if this sensor should precede sensor s in the delay
    // queue: it must have a lower priority number than s.
    virtual SbBool	isBefore(const SoSensor *s) const;
};

#endif  /* _SO_DELAY_QUEUE_SENSOR_ */
