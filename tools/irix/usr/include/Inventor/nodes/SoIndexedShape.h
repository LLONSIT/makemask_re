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
 |	This file defines the SoIndexedShape node class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_INDEXED_SHAPE_
#define  _SO_INDEXED_SHAPE_

#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/nodes/SoVertexShape.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoIndexedShape
//
//  Abstract indexed shape node class. All nodes derived from this
//  (such as SoIndexedFaceSet and SoIndexedLineSet) are shapes
//  that are constructed from vertices defined by indexing into the
//  current coordinates. The coordinate indices are stored in the
//  coordIndex field, which is used by all subclasses.
//
//  One rule is used: all coordinate indices less than 0 may be used
//  for special purposes, such as to denote the end of a face or
//  polyline. This means that all indices < 0 can be ignored safely
//  when looking at vertices.
//
//  Depending on the current material, normal, and texture coordinate
//  binding values, materials, normals, and texture coordinates may be
//  accessed in order or may be indexed using the materialIndex,
//  normalIndex, and textureCoordIndex fields.
//
//////////////////////////////////////////////////////////////////////////////

class SoIndexedShape : public SoVertexShape {

    SO_NODE_ABSTRACT_HEADER(SoIndexedShape);

  public:
    // Fields inherited by all subclasses:
    SoMFInt32		coordIndex;		// Coordinate indices
    SoMFInt32		materialIndex;		// Material indices
    SoMFInt32		normalIndex;		// Surface normal indices
    SoMFInt32		textureCoordIndex;	// Texture Coordinate indices

  SoINTERNAL public:
    static void		initClass();

  protected:
    // Constructor - makes this abstract
    SoIndexedShape();

    // This handles bounding box computation for all shapes derived
    // from this class. It sets the bounding box to contain all
    // vertices of the shape, assuming that the shape uses the
    // coordinates indexed by all non-negative values in the
    // coordIndex field. It also sets the center to the average of the
    // vertices' coordinates.
    virtual void	computeBBox(SoAction *action, SbBox3f &box,
				    SbVec3f &center);

    // Returns TRUE if texture coordinates should be indexed
    static SbBool	areTexCoordsIndexed(SoAction *action);

    // Starting at a given index in the coordIndex array, figure out
    // how many vertices there are before either the end of the array
    // or the next 'border' index
    int			getNumVerts(int startCoord);

    // Setup for fast rendering.  This should be called by subclasses,
    // which can then use the textureI/colorI/normalI arrays (which
    // will either point to one of the coordIndex arrays, or to a
    // consective array of integers.  This must be called AFTER the
    // vpCache has been filled in.
    void		setupIndices(int numParts, int numFaces,
				SbBool needNormals, SbBool needTexCoords);

    // These must not be called unless setupIndices has been called first:
    const int32_t *	getNormalIndices()
	{ return (normalI ? normalI : consecutiveIndices); }
    const int32_t *	getColorIndices()
	{ return (colorI ? colorI : consecutiveIndices); }
    const int32_t *	getTexCoordIndices()
	{ return (texCoordI ? texCoordI : consecutiveIndices); }

    // Keep indices up to date if things change
    virtual void	notify(SoNotList *list);

    virtual ~SoIndexedShape();

  private:
    // Internal routines used to allocate sequential indices so the
    // same rendering loops can be used for indexed or non-indexed
    // cases:
    void	allocateSequential(int howMany);
    int32_t*	allocateSequentialWithHoles();

    // These are filled in by the setupIndices routine:
    const int32_t	*texCoordI;
    const int32_t	*colorI;
    const int32_t	*normalI;
    static int32_t	*consecutiveIndices;
    static int	numConsecutiveIndicesAllocated;

    unsigned char materialBinding;
    unsigned char normalBinding;
    unsigned char texCoordBinding;
};

#endif /* _SO_INDEXED_SHAPE_ */
