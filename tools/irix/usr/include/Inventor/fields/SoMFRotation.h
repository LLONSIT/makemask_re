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
 |   Classes:
 |	SoMFRotation
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_MF_ROTATION_
#define  _SO_MF_ROTATION_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbLinear.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoMFRotation subclass of SoMField.
//
//////////////////////////////////////////////////////////////////////////////

class SoMFRotation : public SoMField {
    // Use standard field stuff
    SO_MFIELD_HEADER(SoMFRotation, SbRotation, const SbRotation &);

  public:

    //
    // Some additional convenience functions:
    //

    // Set values from array of arrays of 4 floats
    void	setValues(int start, int num, const float q[][4]);

    // Set one value from 4 floats
    void	set1Value(int index, float q0, float q1, float q2, float q3);

    // Set one value from 4 floats in array
    void	set1Value(int index, const float q[4]);

    // Set one value from axis and angle
    void	set1Value(int index, const SbVec3f &axis, float angle);

    // Set to one value from 4 floats
    void	setValue(float q0, float q1, float q2, float q3);

    // Set to one value from 4 floats in array
    void	setValue(const float q[4]);

    // Set to one value from axis and angle
    void	setValue(const SbVec3f &axis, float angle);

  SoINTERNAL public:
    static void		initClass();
};

#endif /* _SO_MF_ROTATION_ */
