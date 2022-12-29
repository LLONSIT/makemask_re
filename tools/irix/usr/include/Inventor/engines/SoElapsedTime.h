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
 |   $Revision: 2.3 $
 |
 |   Description:
 |	This file contains the implementation of the ElapsedTime engine
 |
 |   Classes:
 |	SoElapsedTime
 |
 |   Author(s)		: Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_ELAPSED_TIME_
#define  _SO_ELAPSED_TIME_

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFTime.h>
#include <Inventor/fields/SoSFTrigger.h>

class SoElapsedTime : public SoEngine {

    SO_ENGINE_HEADER(SoElapsedTime);

  public:
    // Inputs
    SoSFTime		timeIn;		// Running (clock) time
    SoSFFloat		speed;		// Scale factor for time
    SoSFBool		on;		// TRUE to run, FALSE to stop
    SoSFBool		pause;		// TRUE to freeze, FALSE to run
    SoSFTrigger		reset;

    // Output: 
    //
    // While the engine is on, it keeps track of 'clock' time.
    // This is the amount of real time that passes multiplied by the speed.
    // If the speed input varies while the engine is on, then 'clock' time 
    // advances non-uniformly.
    //
    // Pausing the engine will freeze the timeOut value, but internally the 
    // 'clock' time will continue to advance.
    // Unpause the engine and the timeOut will jump forward to display
    // 'clock' time.
    //
    // Stop the engine (by setting 'on' to FALSE) to freeze both the
    // timeOut value and the 'clock' time. Re-start (by setting 'on'
    // to TRUE) and both timeOut and 'clock' will continue from where
    // they were at the time the engine was stopped.
    //
    SoEngineOutput	timeOut;

    // Constructor
    SoElapsedTime();

  SoINTERNAL public:

    static void initClass();

  protected:

    // Detects when the running time input changed
    virtual void	inputChanged(SoField *whichInput);

    // Writes instance to SoOutput. Takes care of not writing out
    // connection to realTime that is created in constructor.
    virtual void	writeInstance(SoOutput *out);

    // Reads stuff into instance.  Works around a problem with old
    // files that contain explicit references to the default
    // connection to realTime.
    virtual SbBool	readInstance(SoInput *in, unsigned short flags);

  private:
    enum Todo {
	CHECK_ON	= (1<<0),
	CHECK_PAUSE	= (1<<1),
	RESET		= (1<<2)
    };
    enum State {
	STOPPED,	// Clock is not running
	RUNNING,	// Clock is running
	PAUSED		// Clock is running, but output is frozen
    };

    enum State		state;
    unsigned int	todo;
    SbTime		prevTimeOfDay;	 // Time of day when last
					 // evaluate was called.
    SbTime		prevTimeOut;	 // Last 'clock' time that 
					 // was output.
    float		prevClockTime;   // 'Clock' time when last 
					 // evaluate was called.

    // Destructor
    ~SoElapsedTime();

    // Evaluation method
    virtual void	evaluate();
};

#endif  /* _SO_ELAPSED_TIME_ */
