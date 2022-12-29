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
 |   $Revision: 2.4 $
 |
 |   Description:
 |	This file defines the SoPointSet node class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_POINT_SET_
#define  _SO_POINT_SET_

#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/nodes/SoNonIndexedShape.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoPointSet
//
//  Set of points, using the current coordinates. The startIndex field
//  gives the starting coordinate index for the first point. The number of
//  points to draw is determined by the numPoints field.
//
//////////////////////////////////////////////////////////////////////////////

// This value, when used in the numPoints field, means use the rest of
// the coordinates as points
#define SO_POINT_SET_USE_REST_OF_POINTS	(-1)

class SoPointSet : public SoNonIndexedShape {

    SO_NODE_HEADER(SoPointSet);

  public:
    // Fields
    SoSFInt32		numPoints;	// Number of points to draw

    // Constructor
    SoPointSet();

  SoEXTENDER public:
    // Implements actions
    virtual void	GLRender(SoGLRenderAction *action);

    // Redefine this to tell open caches that they contain points
    virtual void	getBoundingBox(SoGetBoundingBoxAction *action);

  SoINTERNAL public:
    static void		initClass();

  protected:
    // Generates points representing point set
    virtual void	generatePrimitives(SoAction *action);

    // Computes bounding box of point set
    virtual void	computeBBox(SoAction *action, SbBox3f &box,
				    SbVec3f &center);

    // Overrides standard method to create an SoPointDetail instance
    virtual SoDetail *	createPointDetail(SoRayPickAction *action,
					  const SoPrimitiveVertex *v,
					  SoPickedPoint *pp);

  protected:
    virtual ~SoPointSet();

  private:
    // Returns TRUE if materials/normals are bound to individual points
    SbBool		areMaterialsPerPoint(SoAction *action) const;
    SbBool		areNormalsPerPoint(SoAction *action) const;
};

#endif /* _SO_POINT_SET_ */
