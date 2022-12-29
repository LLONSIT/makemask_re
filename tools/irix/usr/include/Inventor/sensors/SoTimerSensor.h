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
 |	Timer sensors trigger repeatedly at regular
 |	intervals, starting at a given base time. By default, the base
 |	time is the current time (at the time the sensor is scheduled or
 |	rescheduled) and the interval is 1/30 of a second; both of these
 |	values may be changed.  If more than one interval passes while
 |	sensors are being triggered, then the extra intervals will be lost
 |	(timers always reschedule themselves to occur in the future).
 |	If more than one timer has expired (and therefore more than one
 |	needs to be rescheduled), all of them are first triggered, and are
 |	then rescheduled relative to the current time.  The reschedule()
 |	method is called by the sensor manager to accomplish this (see the
 |	comments there about saturating the timer queue).
 |
 |   Author(s)		: Nick Thompson, Paul Strauss, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_TIMER_SENSOR_
#define  _SO_TIMER_SENSOR_

#include <Inventor/sensors/SoTimerQueueSensor.h>

class SoTimerSensor : public SoTimerQueueSensor {

  public:
    // Constructors. The second form takes standard callback function and data
    SoTimerSensor();
    SoTimerSensor(SoSensorCB *func, void *data);

    // Destructor
    virtual ~SoTimerSensor();

    // Sets/returns the base time and interval length. The base time
    // is undefined unless it has been specified by the user or the
    // sensor is currently scheduled.
    void		setBaseTime(const SbTime &base)  { baseTime = base;
						           baseTimeSet = TRUE;}
    void		setInterval(const SbTime &intvl) { interval = intvl; }
    const SbTime &	getBaseTime() const		 { return baseTime;  }
    const SbTime &	getInterval() const		 { return interval;  }

    // Overrides the regular schedule() method because we have to set
    // up the trigger time first.
    virtual void	schedule();

    // Overrides the regular unschedule() because the timer could be
    // in either the timer queue or the waiting-to-be-rescheduled
    // queue, depending on the state of the 'triggering' flag.
    virtual void	unschedule();

  SoINTERNAL public:

    // Reschedule this timer relative to the given time
    void		reschedule(const SbTime &);

  private:
    SbTime		baseTime;	// Base time for scheduling triggering
    SbTime		interval;	// Interval between triggering
    SbBool		baseTimeSet;	// Whether base time was set by user

    SbBool		triggering;	// True if in trigger() code

    // Triggers the sensor, calling its callback function. This
    // overrides the method in SoSensor because it has to reschedule
    // itself for the next interval after triggering.
    virtual void	trigger();
};

#endif  /* _SO_TIMER_SENSOR_ */
