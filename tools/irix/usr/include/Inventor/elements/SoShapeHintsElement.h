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
 |   $Revision: 2.5 $
 |
 |   Description:
 |	This file defines the SoShapeHintsElement class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_SHAPE_HINTS_ELEMENT
#define  _SO_SHAPE_HINTS_ELEMENT

#include <Inventor/elements/SoReplacedElement.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoShapeHintsElement
//
//  Element that stores current shape hints.
//  All three hints must be set at the same time; to
//  leave any hint as is, use the "AS_IS" enum value.
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoShapeHintsElement : public SoElement {

    SO_ELEMENT_HEADER(SoShapeHintsElement);

  public:
    enum VertexOrdering {	// Hints about ordering of face vertices:
	UNKNOWN_ORDERING,	//	No ordering info is known
	CLOCKWISE,		//	Vertices are ordered CW around faces
	COUNTERCLOCKWISE,	//	Vertices are ordered CCW around faces
	ORDERING_AS_IS		//	Indicates to set() to leave as is
    };

    enum ShapeType {		// Hints about entire shape:
	UNKNOWN_SHAPE_TYPE,	//	Nothing is known about shape
	SOLID,			//	Shape is known to be solid
	SHAPE_TYPE_AS_IS	//	Indicates to set() to leave as is
    };

    enum FaceType {		// Hints about faces of shape:
	UNKNOWN_FACE_TYPE,	//	Nothing is known about faces
	CONVEX,			//	Faces are all convex
	FACE_TYPE_AS_IS		//	Indicates to set() to leave as is
    };

    // Initializes element
    virtual void	init(SoState *state);

    // Sets the current shape hints in the state.  Calls virtual
    // method that subclasses can override.
    static void		set(SoState *state, VertexOrdering vertexOrdering,
			    ShapeType shapeType, FaceType faceType);

#ifndef IV_STRICT
    static void         set(SoState *state, SoNode *, 
			    VertexOrdering vertexOrdering,
                            ShapeType shapeType, FaceType faceType)
        { set(state, vertexOrdering, shapeType, faceType); }
#endif

    // Returns current shape hints from the state
    static void		get(SoState *state,
			    VertexOrdering &vertexOrdering,
			    ShapeType &shapeType, FaceType &faceType);

    // Returns each default hint
    static VertexOrdering getDefaultVertexOrdering() {return UNKNOWN_ORDERING;}
    static ShapeType	  getDefaultShapeType()  { return UNKNOWN_SHAPE_TYPE; }
    static FaceType	  getDefaultFaceType()   { return CONVEX; }

    // Push copies the values from the previous element, so set
    // doesn't have to set them if they are set AS_IS.
    virtual void	push(SoState *state);

    // Returns TRUE if the hints match in both elements
    virtual SbBool	matches(const SoElement *elt) const;

    // Create and return a copy of this element
    virtual SoElement	*copyMatchInfo() const;

    // Prints element (for debugging)
    virtual void	print(FILE *fp) const;

  SoINTERNAL public:
    // Initializes the SoShapeHintsElement class
    static void		initClass();

  protected:
    // Virtual set methods that subclasses can override.
    virtual void	setElt(VertexOrdering vertexOrdering,
			       ShapeType shapeType, FaceType faceType);

    VertexOrdering	vertexOrdering;
    ShapeType		shapeType;
    FaceType		faceType;

    virtual ~SoShapeHintsElement();
};

#endif /* _SO_SHAPE_HINTS_ELEMENT */

