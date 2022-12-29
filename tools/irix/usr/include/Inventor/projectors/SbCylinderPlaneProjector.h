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
 |	This file contains the definition of the SbCylinderPlaneProjector
 |	class. This projector projects the mouse position onto the 
 |	surface of a cylinder with a plane cutting through it.
 |
 |	When the mouse position projects on to the plane, the
 |	rotations will be as if the plane is being dragged,
 |	causing the cylinder to rotate beneath it.
 |
 |   Author(s)		: Howard Look, Paul Isaacs
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef _SB_CYLINDER_PLANE_PROJECTOR_
#define _SB_CYLINDER_PLANE_PROJECTOR_

#include <Inventor/projectors/SbCylinderSectionProjector.h>

class SbCylinderPlaneProjector : public SbCylinderSectionProjector
{
  public:
  
    // Default constructor.
    // The default view volume is undefined.
    // The default working space is identity (world space).
    // The default cylinder is centered about the Y axis and has radius 1.0.
    // The default edge tolerance is .9.
    // The default eye orientation is TRUE.
    SbCylinderPlaneProjector(float edgeTol = .9, SbBool orientToEye = TRUE);

    // Constructor taking the cylinder.
    SbCylinderPlaneProjector( const SbCylinder &cyl,
			      float edgeTol = .9,
			      SbBool orientToEye = TRUE);

    // Destructor
    ~SbCylinderPlaneProjector() {}
    
    // Returns an instance that is a copy of this instance. The caller
    // is responsible for deleting the copy when done.
    virtual SbProjector *    copy() const;

    // Apply the projector using the given point, returning the
    // point in three dimensions that it projects to.
    // The point should be normalized from 0-1, with (0,0) at
    // the lower-left.
    virtual SbVec3f	project(const SbVec2f &point);

    // Computes a rotation based on two points on this projector.
    virtual SbRotation	getRotation(const SbVec3f &point1,
				    const SbVec3f &point2);

  protected:
    SbRotation		getRotation(const SbVec3f &point1, SbBool tol1, 
				    const SbVec3f &point2, SbBool tol2);
};

#endif /* _SB_CYLINDER_PLANE_PROJECTOR_ */
