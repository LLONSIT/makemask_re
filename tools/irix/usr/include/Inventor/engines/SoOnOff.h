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
 |	This file contains the declaration of the OnOff engine
 |
 |   Classes:
 |	SoOnOff
 |
 |   Author(s)		: Ronen Barzel
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_ON_OFF_
#define  _SO_ON_OFF_

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFTrigger.h>

class SoOnOff : public SoEngine {

    SO_ENGINE_HEADER(SoOnOff);
    
  public:

    // Inputs
    SoSFTrigger	on;	// turns on
    SoSFTrigger	off;	// turns off
    SoSFTrigger	toggle;	// changes state
    
    SoEngineOutput isOn;	// (SoSFBool)
    SoEngineOutput isOff;	// (SoSFBool)
    
    // Constructor
    SoOnOff();
    
  SoINTERNAL public:

    static void initClass();

  protected:
    virtual void	inputChanged(SoField *whichInput);

  private:

    // Destructor
    ~SoOnOff();

    // Evaluation method
    virtual void evaluate();

    SbBool	state;
};

#endif  /* _SO_ON_OFF_ */
