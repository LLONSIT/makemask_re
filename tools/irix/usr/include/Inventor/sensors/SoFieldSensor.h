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
 |	Data sensor that is attached to a field in a node or elsewhere.
 |	The sensor is scheduled when a change is made to that field. Note:
 |	the field must be contained within a node or function, or
 |	attachment will not work.
 |
 |   Author(s)		: Paul Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_FIELD_SENSOR_
#define  _SO_FIELD_SENSOR_

#include <Inventor/sensors/SoDataSensor.h>

class SoFieldContainer;

class SoFieldSensor : public SoDataSensor {

  public:
    // Constructors. The second form takes standard callback function and data
    SoFieldSensor();
    SoFieldSensor(SoSensorCB *func, void *data);

    // Destructor
    virtual ~SoFieldSensor();

    // Attaches the sensor to the given field. Will not attach if the
    // field is not contained in a node or function.
    void		attach(SoField *field);

    // Detaches the sensor if it is attached to a field
    void		detach();

    // Returns the field to which the sensor is attached, or NULL if it
    // is not attached.
    SoField *		getAttachedField() const	{ return field; }

  SoINTERNAL public:
    // Override trigger to evaluate the field we're connected to, just
    // in case the trigger method doesn't get the value.
    virtual void trigger();

  private:
    SoField *		field;		// Field sensor is attached to

    // Propagates modification notification through an instance. This
    // checks to see if the field that triggered notification matches
    // the field we are attached to. (It also checks indices if necessary.)
    virtual void	notify(SoNotList *list);

    // Called by the attached path when it (the path) is about to be deleted
    virtual void	dyingReference();
};

#endif  /* _SO_FIELD_SENSOR_ */
