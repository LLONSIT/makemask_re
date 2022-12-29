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
 |	Manager for scheduling and triggering sensors. The manager
 |	maintains a queue of delay sensors (derived from SoDelayQueueSensor)
 |	and timer sensors (derived from SoTimerQueueSensor).
 |
 |   Classes
 |	SoSensorManager
 |
 |   Author(s)		: Nick Thompson, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_SENSOR_MANAGER_
#define  _SO_SENSOR_MANAGER_

#include <Inventor/misc/SoBasic.h>
#include <Inventor/SbTime.h>

class SoSensor;
class SoDelayQueueSensor;
class SoTimerQueueSensor;
class SoTimerSensor;
class SoAlarmSensor;

SoINTERNAL class SoSensorManager {
  public:

    // Constructor, destructor
    SoSensorManager();
    ~SoSensorManager();

    // Set up a function to call when either queue has a sensor added
    // or removed
    void		setChangedCallback(void (*func)(void *), void *data)
	{ changedFunc = func; changedFuncData = data; }

    // Insert/remove an delay or timer event into/from the appropriate queue
    void		insertDelaySensor(SoDelayQueueSensor *s);
    void		insertTimerSensor(SoTimerQueueSensor *s);
    void		removeDelaySensor(SoDelayQueueSensor *s);
    void		removeTimerSensor(SoTimerQueueSensor *s);

    // Timers are all rescheduled at the same time, after they have
    // been triggered.  This avoids timer queue saturation.
    void		rescheduleTimer(SoTimerSensor *s);
    void		removeRescheduledTimer(SoTimerQueueSensor *s);

    // Set/get delay queue sensors (OneShot, Node, Path, etc)
    // timeout value.  Delay sensor go off whenever there is idle time
    // or when the timeout expires.
    void		setDelaySensorTimeout(const SbTime &t);
    const SbTime	&getDelaySensorTimeout();

    // Process all sensors in the delay queue.  The isIdle flag should
    // be TRUE if the delay queue is being processed because there is
    // idle time; it should be false if it is being processed because
    // the delay sensor timeout has expired.
    void		processDelayQueue(SbBool isIdle);

    // Process all immediate (priority 0) sensors in the delay queue
    void		processImmediateQueue();

    // Process appropriate sensors in the timer queue based on current time
    void		processTimerQueue();

    // Returns TRUE if there is at least one sensor in the delay queue
    SbBool		isDelaySensorPending()
	    			{ return (delayQueue != NULL); }

    // Returns TRUE if there is at least one sensor in the timer
    // queue. If there is one, the time of the first sensor is placed
    // in tm.
    SbBool		isTimerSensorPending(SbTime &tm);

    // Just like UNIX select() call, but checks sensor queues while
    // waiting for events.
    int			doSelect(int nfds, fd_set *readfds, fd_set *writefds,
				 fd_set *exceptfds,
				 struct timeval *userTimeOut);
  private:
    SoSensor		*delayQueue;	// Head of delay sensor queue
    SoSensor		*timerQueue;	// Head of timer sensor queue
    SoSensor		*rescheduleQueue;// Timers ready to be rescheduled

    // These are used to process the delay queue every once in a
    // while:
    SbTime		delayQTimeout;
    SoAlarmSensor	*delayQTimeoutSensor;
    static void		delayQTimeoutCB(void *, SoSensor *);

    // Non-zero when processing a queue.  The changedCallback will not
    // be called when we are in the middle of processing a queue, and
    // the immediate queue uses this to avoid recursion.  Because a
    // timer sensor might decide to process the delay queue in its
    // trigger method, this is an integer instead of a simple Boolean.
    int			processingQueue;

    uint32_t		delayQCount;	// Avoids loops processing delay queue

    // Insert/remove an entry into/from the queue with the given head
    void		insert(SoSensor *s, SoSensor *&head);
    void		remove(SoSensor *s, SoSensor *&head);

    // Callback which is called whenever a sensor is inserted or removed
    void		(*changedFunc)(void *);
    void		*changedFuncData;

    // Calls the changed callback, if there is one
    void		notifyChanged();
};

#endif /* _SO_SENSOR_MANAGER_ */
