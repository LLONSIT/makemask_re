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
 |	This file contains the declaration of the OneShot engine
 |
 |   Classes:
 |	SoOneShot
 |
 |   Author(s)		: Ronen Barzel
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_ONE_SHOT_
#define  _SO_ONE_SHOT_

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFTrigger.h>
#include <Inventor/fields/SoSFTime.h>
#include <Inventor/fields/SoSFBitMask.h>

class SoOneShot : public SoEngine {

    SO_ENGINE_HEADER(SoOneShot);

  public:
    enum Flags	{
	RETRIGGERABLE	= (1<<0),	// can start over during cycle?
	HOLD_FINAL	= (1<<1)	// ramp & timeOut stay high after cycle?
    };

    // Inputs
    SoSFTime		duration;	// duration of active cycle
    SoSFTrigger		trigger;	// start the cycle
    SoSFBitMask		flags;
    SoSFBool		disable;	// if TRUE, timer is disabled, output=0
    SoSFTime		timeIn;

    // Outputs
    SoEngineOutput	timeOut;	// (SoSFTime) time counts from trigger
    SoEngineOutput	isActive;	// (SoSFBool)
    SoEngineOutput	ramp;		// (SoSFFloat) ramps linearly 0 to 1

    // Constructor
    SoOneShot();

  SoINTERNAL public:

    static void initClass();

  protected:
    virtual void	inputChanged(SoField *whichInput);

    // Writes instance to SoOutput. Takes care of not writing out
    // connection to realTime that is created in constructor.
    virtual void	writeInstance(SoOutput *out);

    // Reads stuff into instance.  Works around a problem with old
    // files that contain explicit references to the default
    // connection to realTime.
    virtual SbBool	readInstance(SoInput *in, unsigned short flags);

  private:
    enum State {
	DISABLED,		// everything clamped at 0 (via disable input)
	OFF,			// normal idle state
	TRIGGERED,		// has been triggered, need to start running
	ON,			// running, watching the time
	PEAKED			// have reached the end, need to reset
    }			state;
    SbTime		baseTime;	// Starting time for elapsed time 
    SbTime		timeVal;	// holds output time value
    double		rampVal;	// holds ramp value
    SbBool		outputPending;	// keeps outputs enabled until data is read

    // Destructor
    ~SoOneShot();

    // Evaluation method
    virtual void	evaluate();
};

#endif  /* _SO_ONE_SHOT_ */
