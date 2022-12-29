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
 |	This file defines the SoCube node class.
 |
 |   Author(s)		: Paul S. Strauss, Nick Thompson
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_CUBE_
#define  _SO_CUBE_

#include <Inventor/SbLinear.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/nodes/SoShape.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoCube
//
//  Simple cube. Default size is -1 to +1 in all 3 dimensions, but the
//  width, height, and depth fields can be used to change these.
//
//////////////////////////////////////////////////////////////////////////////

class SoCube : public SoShape {

    SO_NODE_HEADER(SoCube);

  public:
    // Fields
    SoSFFloat		width;		// Size in x dimension
    SoSFFloat		height;		// Size in y dimension
    SoSFFloat		depth;		// Size in z dimension

    // Constructor
    SoCube();

  SoEXTENDER public:
    // Implements actions
    virtual void	GLRender(SoGLRenderAction *action);
    virtual void	rayPick(SoRayPickAction *action);

  SoINTERNAL public:
    static void		initClass();

  protected:
    // Generates triangles representing a cube
    virtual void	generatePrimitives(SoAction *action);

    // Computes bounding box of cube
    virtual void	computeBBox(SoAction *action, SbBox3f &box,
				    SbVec3f &center);

    // Overrides standard method to create an SoCubeDetail instance
    virtual SoDetail *	createTriangleDetail(SoRayPickAction *action,
					     const SoPrimitiveVertex *v1,
					     const SoPrimitiveVertex *v2,
					     const SoPrimitiveVertex *v3,
					     SoPickedPoint *pp);

    virtual ~SoCube();

  private:
    static SbVec3f	coords[8];	// Corner coordinates
    static SbVec2f	texCoords[4];	// Face corner texture coordinates
    static SbVec3f	normals[6];	// Face normals
    static SbVec3f	edgeNormals[12];// Edge normals (for wire-frame)
    static const SbVec3f *verts[6][4];	// Vertex references to coords

    // This flag indicates whether picking is done on a real cube or a
    // cube that is just a bounding box representing another shape. If
    // this flag is TRUE, a pick on the cube should not generate a
    // detail, since the bounding box is not really in the picked path.
    SbBool		pickingBoundingBox;

    // Returns TRUE if per face materials are specified
    SbBool		isMaterialPerFace(SoAction *action) const;

    // Computes number of divisions per side based on complexity
    int			computeNumDivisions(SoAction *action) const;

    // Computes real half-width, -height, -depth
    void		getSize(float &hWidth,
				float &hHeight,
				float &hDepth) const;

    // These render the cube
    void		GLRenderGeneric(SoGLRenderAction *action,
					SbBool sendNormals, SbBool doTextures);
    void		GLRenderNvertTnone(SoGLRenderAction *action);

    // Renders or picks cube representing given bounding box. These
    // are used by SoShape to implement BOUNDING_BOX complexity.
    void		GLRenderBoundingBox(SoGLRenderAction *action,
					    const SbBox3f &bbox);
    void		rayPickBoundingBox(SoRayPickAction *action,
					   const SbBox3f &bbox);

    // SoShape needs to get at the above methods
friend class SoShape; 
};

#endif /* _SO_CUBE_ */
