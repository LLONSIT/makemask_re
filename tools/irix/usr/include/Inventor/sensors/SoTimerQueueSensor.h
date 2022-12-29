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
 |   Description:
 |	Abstract base class for all sensors that are added to the timer
 |	queue. Each sensor in the timer queue contains an SbTime
 |	indicating when the sensor should be triggered. Sensors in the
 |	timer queue are sorted by their trigger times.
 |	Each subclass defines public methods for specifying when and how
 |	to trigger the sensor.
 |
 |   Author(s)		: Nick Thompson, Paul Strauss, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_TIMER_QUEUE_SENSOR_
#define  _SO_TIMER_QUEUE_SENSOR_

#include <Inventor/sensors/SoSensor.h>
#include <Inventor/SbTime.h>

class SoTimerQueueSensor : public SoSensor {

  public:
    // Constructors. The second form takes standard callback function and data
    SoTimerQueueSensor();
    SoTimerQueueSensor(SoSensorCB *func, void *data);

    // Destructor
    virtual ~SoTimerQueueSensor();

    // Returns the time at which the sensor is scheduled to be
    // triggered. Results are undefined if the sensor is not scheduled.
    const SbTime &	getTriggerTime() const		{ return trigTime; }

    // Scheduling methods
    virtual void	schedule();
    virtual void	unschedule();
    virtual SbBool	isScheduled() const;

  protected:
    // Used by subclasses to set the time at which the sensor is to be
    // triggered.
    void		setTriggerTime(const SbTime &time);

    // Triggers the sensor, calling its callback function. This
    // overrides the method in SoSensor because it has to reset the
    // schedule flag before triggering.
    virtual void	trigger();

    SbBool		scheduled;	// Whether sensor is scheduled

  private:
    SbTime		trigTime;	// Time when sensor is to be triggered

    // Returns TRUE if this sensor should precede sensor s in the delay
    // queue: it must have a lower priority number than s.
    virtual SbBool	isBefore(const SoSensor *s) const;
};

#endif  /* _SO_TIMER_SENSOR_ */
