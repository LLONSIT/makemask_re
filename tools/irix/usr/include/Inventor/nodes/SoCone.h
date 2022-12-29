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
 |   $Revision: 2.1 $
 |
 |   Description:
 |	This file defines the SoCone node class.
 |
 |   Author(s)		: Paul S. Strauss, Nick Thompson
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_CONE_
#define  _SO_CONE_

#include <Inventor/SbLinear.h>
#include <Inventor/fields/SoSFBitMask.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/nodes/SoShape.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoCone
//
//  Simple cone, aligned with y-axis. Default has apex point at y = 1,
//  bottom radius 1, and height 2, so that the size is -1 to +1 in all
//  3 dimensions. There are two parts to the cone: the sides and the
//  bottom face (in that order).
//
//////////////////////////////////////////////////////////////////////////////

class SoCone : public SoShape {

    SO_NODE_HEADER(SoCone);

  public:

    enum Part {			// Cone parts:
	SIDES	= 0x01,			// The conical part
	BOTTOM	= 0x02,			// The bottom circular face
	ALL	= 0x03		 	// All parts
    };

    // Fields
    SoSFBitMask		parts;		// Visible parts of cone
    SoSFFloat		bottomRadius;	// Radius of bottom circular face
    SoSFFloat		height;		// Size in y dimension

    // Constructor
    SoCone();

    // Turns on/off a part of the cone. (Convenience functions)
    void		addPart(SoCone::Part part);
    void		removePart(SoCone::Part part);

    // Returns whether a given part is on or off. (Convenience function)
    SbBool		hasPart(SoCone::Part part) const;

  SoEXTENDER public:
    // Implements actions
    virtual void	GLRender(SoGLRenderAction *action);
    virtual void	rayPick(SoRayPickAction *action);

  SoINTERNAL public:
    static void		initClass();

  protected:
    // Generates triangles representing a cone
    virtual void	generatePrimitives(SoAction *action);

    // Computes bounding box of cone
    virtual void	computeBBox(SoAction *action, SbBox3f &box,
				    SbVec3f &center);
    virtual ~SoCone();

  private:
    static SbVec2f	*coordsArray;	// Storage for base coords
    static SbVec3f	*normalsArray;	// Storage for base normals
    static int		maxCoords;	// Current max num of coords/normals

    // Computes number of sides and sections to use to represent
    // cone (based on complexity), then computes ring of x,z
    // coordinates around base of cone and stores in baseCoords. It
    // computes and stores normals in sideNormals, too.
    void		computeBase(SoAction *action,
				    int &numSides, int &numSections,
				    SbVec2f *&baseCoords,
				    SbVec3f *&sideNormals) const;

    // Computes real radius and half-height
    void		getSize(float &rad, float &hHeight) const;

    // These render the cone
    void		GLRenderGeneric(SoGLRenderAction *action,
					SbBool sendNormals, SbBool doTextures);
    void		GLRenderNvertTnone(SoGLRenderAction *action);

    // Computes intersection of ray with infinite canonical cone
    SbBool		intersectInfiniteCone(const SbLine &ray,
					      SbVec3f &enterPoint,
					      SbVec3f &exitPoint) const;
};

#endif /* _SO_CONE_ */
