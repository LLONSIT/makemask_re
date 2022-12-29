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
 |	This file contains the implementation of the TimeCounter engine
 |
 |   Classes:
 |	SoTimeCounter
 |
 |   Author(s)		: Ronen Barzel
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_TIME_COUNTER_
#define  _SO_TIME_COUNTER_

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFTime.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFTrigger.h>

class SoTimeCounter : public SoEngine {

    SO_ENGINE_HEADER(SoTimeCounter);

  public:
    // Inputs
    SoSFShort		min;		// min value for counter (default 0)
    SoSFShort		max;		// max value for counter (default 1)
    SoSFShort		step;		// value to step by (default 1)
    SoSFBool		on;		// counter pauses while this is FALSE
    SoSFFloat		frequency;	// cycles-per-second
    SoMFFloat		duty;		// duty-cycle array
    SoSFTime		timeIn;		// time source (else internal is used)
    SoSFTrigger		syncIn;		// restart cycle
    SoSFShort		reset;		// reset cycle to value at setValue

    // Outputs
    SoEngineOutput	output;		// (SoSFShort) counts min...max
    SoEngineOutput	syncOut;	// (SoSFTrigger) triggers at cycle start

    // Constructor
    SoTimeCounter();

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
	ON,			// counting
	PAUSED			// holding
    }			state;
    enum Todo {
	RECALC	= (1<<0),
	RESET	= (1<<1),
	SYNC	= (1<<2),
	PAUSE	= (1<<3),
	UNPAUSE	= (1<<4)
    };
    unsigned int	todo;
    SbTime		period;		// total cycle time
    int			nStages;
    int			curStage;
    int			prevStage;
    struct Stage {
	int	val;		// counter value for stage
	float	duty;		// normalized fraction of cycle
	SbTime	offset;		// time from start of cycle
    }			*stages;
    SbTime		baseTime;	// Starting time for cycle
    SbTime		pauseOffset;	// Starting time for cycle

    // Destructor
    ~SoTimeCounter();

    // Evaluation method
    virtual void	evaluate();
};

#endif  /* _SO_TIME_COUNTER_ */
