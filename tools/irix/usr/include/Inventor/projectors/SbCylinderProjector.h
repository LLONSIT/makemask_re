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
 |	This file contains the definition of the SbCylinderProjector
 |	class. This is an abstract base class for projectors
 |	that somehow use a cylinder in their projection.
 |
 |	The getRotation methods for an SbCylinder will always
 |	return a rotation that is about the axis of the cylinder.
 |	  
 |   Author(s)		: Howard Look
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef _SB_CYLINDER_PROJECTOR_
#define _SB_CYLINDER_PROJECTOR_

#include <Inventor/projectors/SbProjector.h>

class SbCylinderProjector : public SbProjector
{
  public:
    // Destructor
    ~SbCylinderProjector(){};

    // Apply the projector using the given point, returning the
    // point in three dimensions that it projects to.
    // The point should be normalized from 0-1, with (0,0) at the lower-left.
    virtual SbVec3f	project(const SbVec2f &point) = 0;

    // Same as above, but also get a rotation from the last
    // projected point to this one.
    SbVec3f		projectAndGetRotation(const SbVec2f &point,
					      SbRotation &rot);

    // Get a rotation given two points on this cylinder projector.
    virtual SbRotation	getRotation(const SbVec3f &point1,
				    const SbVec3f &point2) = 0;

    // Set/get the cylinder to use.
    // Default cylinder is centered about Y axis and has radius 1.0.
    void		setCylinder(const SbCylinder &cyl);

    const SbCylinder &	getCylinder() const		{ return cylinder; }

    // Set/get whether the projector should always be oriented towards the eye.
    // Set to FALSE if the tolerance should be evaluated in working space.
    void		setOrientToEye(SbBool orientToEye);
    SbBool		isOrientToEye() const		{ return orientToEye; }


    // Set/get whether the projector should intersect the half of the
    // cylinder that faces the eye.
    // Set to FALSE if the projector should intersect with the rear half.
    void                setFront(SbBool isFront);
    SbBool              isFront()       const   { return intersectFront; }
    SbBool              isPointInFront( const SbVec3f &point ) const;


    // Set the transform space to work in.
    virtual void	setWorkingSpace(const SbMatrix &space);
    
  protected:
    // Constructors
    // The default cylinder to is centered about the Y axis and
    // has a radius of 1.0.
    SbCylinderProjector(SbBool orientToEye);
    SbCylinderProjector(const  SbCylinder &cyl,
			SbBool orientToEye);

    // Are intersections done on the front half ( if not, they're done on th e
    // back half) of the cylinder?
    SbBool      intersectFront;

    // Just like cylinder::intersect, except always returns
    // the intersection that is in "front".
    SbBool	intersectCylinderFront(const SbLine &line, SbVec3f &result);

    SbCylinder	cylinder;		// Cylinder for this projector.
    SbBool	orientToEye;		// TRUE if always oriented to eye.
    SbBool	needSetup;		// Set TRUE whenever cylinder,
					// work space or orientation changes.

    // Cached last point on this projector. Subclasses must set
    // this in their project and getRotation methods.
    SbVec3f	lastPoint;
};


#endif /* _SB_CYLINDER_PROJECTOR_ */
