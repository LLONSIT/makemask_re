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
 |	Defines the SoSensor base class. 
 |	The sensor hierarchy is:
 |
 |		*SoSensor
 |			*SoDelayQueueSensor
 |				*SoDataSensor
 |					SoNodeSensor
 |					SoPathSensor
 |					SoFieldSensor
 |				SoIdleSensor
 |				SoOneShotSensor
 |			*SoTimerQueueSensor
 |				SoAlarmSensor
 |				SoTimerSensor
 |
 |	* means the class is abstract.
 |
 | 	Sensors provide a callback mechanism based on some event: a
 |	particular time being reached, a change to a scene graph, or
 |	lack of other events to process.
 |
 |   Author(s)		: Nick Thompson, Paul Strauss, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_SENSOR_
#define  _SO_SENSOR_

#include <Inventor/SbBasic.h>

class SoField;
class SoMField;
class SoSensor;

//////////////////////////////////////////////////////////////////////////////
//
// This typedef defines the calling sequence for all callbacks from sensors
//
//////////////////////////////////////////////////////////////////////////////

typedef void SoSensorCB(void *data, SoSensor *sensor);

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoSensor
//
//  Abstract base class for all sensors. Defines basic callback
//  definition (explicit or in constructor) and scheduling and
//  triggering methods.
//
//////////////////////////////////////////////////////////////////////////////
class SoSensor {

  public:

    // Constructors. The second form takes callback function and data
    SoSensor()				{ func = NULL; funcData = NULL; }
    SoSensor(SoSensorCB *f, void *d)	{ func = f;    funcData = d; }

    // Virtual destructor so that subclasses are deleted properly
    virtual ~SoSensor();

    // Sets/returns callback function and user data pointers.
    void		setFunction(SoSensorCB *f)	{ func = f;	}
    void		setData(void *d)		{ funcData = d;	}
    SoSensorCB *	getFunction() const		{ return func; }
    void *		getData() const			{ return funcData; }

    // Schedules the sensor for triggering at the appropriate time
    virtual void	schedule() = 0;

    // Unschedules sensor to keep it from being triggered
    virtual void	unschedule() = 0;

    // Returns whether the sensor is scheduled
    virtual SbBool	isScheduled() const = 0;

  SoINTERNAL public:
    // Initialize static members, etc.
    static void		initClass();

    // Triggers the sensor, calling its callback function
    virtual void	trigger();

    // This returns TRUE if this sensor should precede sensor s in
    // whichever queue this sensor would be in.
    virtual SbBool	isBefore(const SoSensor *s) const = 0;

    // Sets/returns the next sensor in whichever queue the sensor is in
    void		setNextInQueue(SoSensor *next) { nextInQueue = next; }
    SoSensor *		getNextInQueue() const	       { return nextInQueue; }

  protected:
    SoSensorCB *	func;		// Callback function
    void *		funcData;	// Data to pass to callback

  private:
    SoSensor		*nextInQueue;	// Next sensor in queue
};

#endif /* _SO_SENSOR_ */
