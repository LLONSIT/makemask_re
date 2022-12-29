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
 |	Timer queue sensor that is scheduled to be triggered at a specific
 |	time, which is specified either absolutely (e.g., 2pm) or
 |	relatively (e.g., 5 minutes from now). Once an alarm sensor is
 |	triggered, it is not rescheduled.
 |
 |   Author(s)		: Gavin Bell, Paul Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_ALARM_SENSOR_
#define  _SO_ALARM_SENSOR_

#include <Inventor/sensors/SoTimerQueueSensor.h>

class SoAlarmSensor : public SoTimerQueueSensor {

  public:
    // Constructors. The second form takes standard callback function and data
    SoAlarmSensor();
    SoAlarmSensor(SoSensorCB *func, void *data);

    // Destructor
    virtual ~SoAlarmSensor();

    // Set the time to trigger the sensor. The first method specifies
    // an absolute time, the second a time relative to the current time.
    void		setTime(const SbTime &absTime);
    void		setTimeFromNow(const SbTime &relTime);

    // Returns the time the sensor is scheduled to be triggered. This
    // differs from getTriggerTime() in that this method returns the
    // time the sensor was set to be scheduled, even if it has not yet
    // been scheduled.
    const SbTime &	getTime() const			{ return time; }

    // Overrides the regular schedule() method because we have to set
    // up the trigger time first.
    virtual void	schedule();

  private:
    SbTime		time;		// Time sensor is scheduled for
    SbBool		timeSet;	// Whether time value was set
};

#endif  /* _SO_ALARM_SENSOR_ */
