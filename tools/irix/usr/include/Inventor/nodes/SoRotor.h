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
 |	This file defines the SoRotor node class.
 |
 |   Author(s)		: Ronen Barzel
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_ROTOR_
#define  _SO_ROTOR_

#include <Inventor/nodes/SoRotation.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFBool.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoRotor
//
//  SoRotation node that spins the rotation angle, keeping the axis constant
//
//////////////////////////////////////////////////////////////////////////////

class SoRotor : public SoRotation {

    SO_NODE_HEADER(SoRotor);

  public:
    // Fields
    SoSFFloat	speed;	// revolutions per second
    SoSFBool	on;	// FALSE to stop rotation

    // Constructor
    SoRotor();

  SoINTERNAL public:
    static void		initClass();

  protected:
    virtual ~SoRotor();

  private:
    // internal engines to compute the rotation
    class SoElapsedTime		*time;
    class SoCalculator		*calc;
    class SoComposeRotation	*compose;
    class SoDecomposeRotation	*decompose; // COMPAT 2.0 ???

    // overload write method not to write internal engines
    virtual void	write(class SoWriteAction *action);

    // keep track of internal connection
    class SoEngineOutput	*internalConnection;

    // overload notify method to check for field updates
    virtual void notify(SoNotList *list);

    class SoOneShotSensor	*rotationSensor;
    class SoFieldSensor		*onSensor; // COMPAT 2.0 ???

    static void rotationSensorCB(void *data, class SoSensor *sensor);
    static void onSensorCB(void *data, class SoSensor *sensor);
};

#endif /* _SO_ROTOR_ */
