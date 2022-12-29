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
 |	This file defines the SoBlinker node class.
 |
 |   Author(s)		: Ronen Barzel
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_BLINKER_
#define  _SO_BLINKER_

#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFBool.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoBlinker
//
//  SoSwitch node cycles between all its children.
//  with only one child, cycles that child on and off.
//
//////////////////////////////////////////////////////////////////////////////

class SoBlinker : public SoSwitch {

    SO_NODE_HEADER(SoBlinker);

  public:
    // Fields
    SoSFFloat		speed;	// cycles per second
    SoSFBool		on;	// FALSE to stop blinking

    // Constructor
    SoBlinker();

  SoEXTENDER public:
    // Bounding box computation takes all children into account
    virtual void	getBoundingBox(SoGetBoundingBoxAction *action);

    // overload write method not to write internal engines
    virtual void	write(SoWriteAction *action);

  SoINTERNAL public:
    static void		initClass();

  protected:
    virtual ~SoBlinker();

    virtual void	notify(SoNotList *);

  private:
    SbBool		wasOn;	// Remembers previous state of "on" field

    // keep track of internal connection
    class SoEngineOutput	*internalConnection;

    class SoTimeCounter	*count;
    void		setupCounter();
    int			nchildren;

    class SoOneShotSensor	*childrenSensor;
    class SoOneShotSensor	*whichChildSensor;
    class SoFieldSensor		*onSensor;

    static void childrenSensorCB(void *data, class SoSensor *sensor);
    static void whichChildSensorCB(void *data, class SoSensor *sensor);
    static void onSensorCB(void *data, class SoSensor *sensor);
};

#endif /* _SO_BLINKER_ */
