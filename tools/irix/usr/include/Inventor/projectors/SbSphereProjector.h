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
 |	This file contains the definition of the SbSphereProjector
 |	class. This is an abstract base class for projectors
 |	that somehow use a sphere in their projection.
 |	  
 |   Author(s)		: Howard Look
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef _SB_SPHERE_PROJECTOR_
#define _SB_SPHERE_PROJECTOR_

#include <Inventor/projectors/SbProjector.h>

class SbSphereProjector : public SbProjector
{
  public:
    // Apply the projector using the given point, returning the
    // point in three dimensions that it projects to.
    // The point should be normalized from 0-1, with (0,0) at the lower-left.
    virtual SbVec3f	project(const SbVec2f &point) = 0;

    // Same as above, but also get a rotation from the last
    // projected point to this one.
    SbVec3f		projectAndGetRotation(const SbVec2f &point,
					      SbRotation &rot);

    // Get a rotation given two points on this sphere projector.
    virtual SbRotation	getRotation(const SbVec3f &point1,
				    const SbVec3f &point2) = 0;

    // Set/get the sphere to use.
    void		setSphere(const SbSphere &sph);

    const SbSphere &	getSphere() const		  { return sphere; }

    // Set/get whether the projector should always be oriented towards the eye.
    // Set to FALSE if the tolerance should be evaluated in working space.
    void		setOrientToEye(SbBool orientToEye);
    SbBool		isOrientToEye()	const		{ return orientToEye; }

    // Set/get whether the projector should intersect the half of the 
    // sphere that faces the eye.
    // Set to FALSE if the projector should intersect with the rear half.
    void		setFront(SbBool inFront);
    SbBool		isFront()	const	{ return intersectFront; }
    SbBool		isPointInFront( const SbVec3f &point ) const;

    // Set the transform space to work in.
    virtual void	    setWorkingSpace(const SbMatrix &space);

    // Destructor
    ~SbSphereProjector(){};
    
  protected:
    // Constructors
    // The default sphere to use has a radius of 1.0 and is centered at (0,0,0).
    SbSphereProjector(SbBool orientToEye);
    SbSphereProjector(const SbSphere &s, SbBool orientToEye);

    // Are intersections done on the front half (if not, they're done on
    // the back half) of the sphere?
    SbBool      intersectFront;

    // Just like sphere::intersect, except always returns
    // the intersection that is in "front".
    SbBool	intersectSphereFront(const SbLine &l, SbVec3f &result);

    SbSphere	sphere;			// The sphere being used.
    SbBool	orientToEye;		// TRUE if always oriented to eye.
    SbBool	needSetup;		// Set TRUE whenever sphere, work space
					// or orientation changes.

    // cached last point on this projector
    SbVec3f	lastPoint;
};

#endif /* _SB_SPHERE_PROJECTOR_ */
