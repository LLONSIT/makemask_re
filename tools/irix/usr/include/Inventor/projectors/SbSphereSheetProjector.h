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
 |	This file defines the SbSphereSheetProjector class. This is a
 |	sphere with a hyperbolic sheet draped over it. As the
 |	mouse moves away from the sphere, rotation gradually
 |	turns into pure roll.
 |
 |	This projector is good for trackballs that want to do
 |	constinuous roll. It allows pure roll as you move away
 |	from the sphere. (This projector uses the same paradigm 
 |	as the "Flip" demo.)
 |
 |	Warning: This projector tends to become unstable when
 |	the mouse position is beyond about 2*radius from the
 |	center of the sphere. Therefore, it is best to use this
 |	as a large, window-sized trackball.
 |
 |   Author(s)		: Howard Look, Gavin Bell, Paul Isaacs
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef _SB_SPHERE_SHEET_PROJECTOR_
#define _SB_SPHERE_SHEET_PROJECTOR_

#include <Inventor/projectors/SbSphereProjector.h>

class SbSphereSheetProjector : public SbSphereProjector
{
  public:
    // Default constructor.
    // The default view volume is undefined.
    // The default working space is identity (world space).
    // The default sphere to use has a radius of 1.0 and is centered at (0,0,0).
    // The default eye orientation is TRUE.
    SbSphereSheetProjector(SbBool orientToEye = TRUE);

    // Constructor taking the sphere.
    SbSphereSheetProjector(const SbSphere &sph,
			   SbBool orientToEye = TRUE);

    // Destructor
    ~SbSphereSheetProjector() {}
    
    // Returns an instance that is a copy of this instance. The caller
    // is responsible for deleting the copy when done.
    virtual SbProjector *    copy() const;

    // Apply the projector using the given point, returning the
    // point in three dimensions that it projects to.
    // The point should be normalized from 0-1, with (0,0) at the lower-left.
    virtual SbVec3f	project(const SbVec2f &point);

    // Computes a rotation based on two points on this projector.
    virtual SbRotation	getRotation(const SbVec3f &point1,
				    const SbVec3f &point2);

  protected:
    // Sets up the plane use to project on to.
    void		setupPlane();

    // The projection point in working space.
    SbVec3f		workingProjPoint;
    
    // Information about the plane used for intersection testing.
    SbVec3f	planePoint;		// point on plane
    SbVec3f	planeDir;		// normal direction
    float	planeDist;		// distance from sphere center
    SbPlane	tolPlane;		// the plane itself
};

#endif /* _SB_SPHERE_SHEET_PROJECTOR_ */
