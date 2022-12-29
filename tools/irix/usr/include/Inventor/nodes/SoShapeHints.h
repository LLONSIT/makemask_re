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
 |   $Revision: 2.3 $
 |
 |   Description:
 |	This file defines the SoShapeHints node class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_SHAPE_HINTS_
#define  _SO_SHAPE_HINTS_

#include <Inventor/elements/SoGLShapeHintsElement.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/nodes/SoSubNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoShapeHints
//
//  This node is used to give hints about subsequent shapes defined in
//  a scene graph. It allows Inventor to provide or optimize certain
//  features (such as back-face culling and two-sided lighting) based
//  on information about shapes. The vertexOrdering, faceType, and
//  shapeType fields hold this information. There is also a crease
//  angle field, which is used when default normals are generated for
//  a polyhedral shape. It defines the smallest edge angle that will
//  be shaded as a crease (faceted), rather than as smooth.
//
//////////////////////////////////////////////////////////////////////////////

class SoShapeHints : public SoNode {

    SO_NODE_HEADER(SoShapeHints);

  public:
    // Hints about ordering of face vertices: if ordering of all
    // vertices of all faces is known to be consistent when viewed
    // from "outside" shape or not.
    enum VertexOrdering {
	UNKNOWN_ORDERING = SoShapeHintsElement::UNKNOWN_ORDERING,
	CLOCKWISE	 = SoShapeHintsElement::CLOCKWISE,
	COUNTERCLOCKWISE = SoShapeHintsElement::COUNTERCLOCKWISE
    };

    // Hints about entire shape: if shape is known to be a solid
    // object, as opposed to a surface.
    enum ShapeType {
	UNKNOWN_SHAPE_TYPE = SoShapeHintsElement::UNKNOWN_SHAPE_TYPE,
	SOLID		   = SoShapeHintsElement::SOLID
    };

    // Hints about faces of shape: if all faces are known to be convex
    // or not.
    enum FaceType {
	UNKNOWN_FACE_TYPE = SoShapeHintsElement::UNKNOWN_FACE_TYPE,
	CONVEX		  = SoShapeHintsElement::CONVEX
    };

    // Fields
    SoSFEnum		vertexOrdering;	// Ordering of face vertices
    SoSFEnum		shapeType;	// Info about shape geometry
    SoSFEnum		faceType;	// Info about face geometry
    SoSFFloat		creaseAngle;	// Smallest angle for sharp edge

    // Constructor
    SoShapeHints();

  SoEXTENDER public:
    virtual void	doAction(SoAction *action);
    virtual void	GLRender(SoGLRenderAction *action);
    virtual void	callback(SoCallbackAction *action);
    virtual void	pick(SoPickAction *action);
    virtual void	getBoundingBox(SoGetBoundingBoxAction *action);

  SoINTERNAL public:
    static void		initClass();

  protected:
    virtual ~SoShapeHints();

  private:
    // Does regular doAction stuff, also sets shapehints element
    void		doAction2(SoAction *action);
};

#endif /* _SO_SHAPE_HINTS_ */
