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
 |	This file defines the SoCylinder node class.
 |
 |   Author(s)		: Paul S. Strauss, Nick Thompson
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_CYLINDER_
#define  _SO_CYLINDER_

#include <Inventor/SbLinear.h>
#include <Inventor/fields/SoSFBitMask.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/nodes/SoShape.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoCylinder
//
//  Simple cylinder, aligned with y-axis. Default size is -1 to +1 in
//  all 3 dimensions, but the radius and height fields can be used to
//  change that. There are essentially three parts to the cylinder:
//  the sides, the top face, and the bottom face (in that order).
//
//////////////////////////////////////////////////////////////////////////////

class SoCylinder : public SoShape {

    SO_NODE_HEADER(SoCylinder);

  public:

    enum Part {			// Cylinder parts
	SIDES	= 0x01,			// The tubular part
	TOP	= 0x02,			// The top circular face
	BOTTOM	= 0x04,			// The bottom circular face
	ALL	= 0x07			// All parts
    };

    // Fields
    SoSFBitMask		parts;		// Visible parts of cylinder
    SoSFFloat		radius;		// Radius in x and z dimensions
    SoSFFloat		height;		// Size in y dimension

    // Constructor
    SoCylinder();

    // Turns on/off a part of the cylinder. (Convenience functions)
    void		addPart(SoCylinder::Part part);
    void		removePart(SoCylinder::Part part);

    // Returns whether a given part is on or off. (Convenience function)
    SbBool		hasPart(SoCylinder::Part part) const;

  SoEXTENDER public:
    // Implements actions
    virtual void	GLRender(SoGLRenderAction *action);
    virtual void	rayPick(SoRayPickAction *action);

  SoINTERNAL public:
    static void		initClass();

  protected:
    // Generates triangles representing a cylinder
    virtual void	generatePrimitives(SoAction *action);

    // Computes bounding box of cylinder
    virtual void	computeBBox(SoAction *action, SbBox3f &box,
				    SbVec3f &center);

    virtual ~SoCylinder();

  private:
    static SbVec2f	*coordsArray;	// Storage for ring coords
    static int		maxCoords;	// Current max num of coords

    // Computes number of sides and sections to use to represent
    // cylinder (based on complexity), then computes ring of x,z
    // coordinates around cylinder and stores in ringCoords.
    void		computeRing(SoAction *action,
				    int &numSides, int &numSections,
				    SbVec2f *&ringCoords) const;

    // Computes real radius and half-height
    void		getSize(float &rad, float &hHeight) const;

    // These render the cylinder
    void		GLRenderGeneric(SoGLRenderAction *action,
					SbBool sendNormals, SbBool doTextures);
    void		GLRenderNvertTnone(SoGLRenderAction *action);
};

#endif /* _SO_CYLINDER_ */
