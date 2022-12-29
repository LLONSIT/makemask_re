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
 |	This file defines the SoNonIndexedShape node class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_NON_INDEXED_SHAPE_
#define  _SO_NON_INDEXED_SHAPE_

#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/nodes/SoVertexShape.h>
#include <Inventor/nodes/SoVertexProperty.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoNonIndexedShape
//
//  Abstract nonindexed shape node class. All nodes derived from this
//  (such as SoFaceSet and SoTriangleStripSet) are shapes constructed
//  from vertices defined by consecutive entries in the current
//  coordinates. The startIndex field gives the index into the current
//  coordinates at which the shape begins.
//
//////////////////////////////////////////////////////////////////////////////

class SoNonIndexedShape : public SoVertexShape {

    SO_NODE_ABSTRACT_HEADER(SoNonIndexedShape);

  public:
    // Fields inherited by all subclasses:
    SoSFInt32		startIndex;	// Index of 1st coordinate of shape

  SoINTERNAL public:
    static void		initClass();

  protected:
    // Constructor - makes this abstract
    SoNonIndexedShape();

    // This is a convenience method to simplify the job of computing
    // bounding boxes for subclasses; it can be called from a
    // subclass's computeBBox() method. It sets the given bounding box
    // to contain all vertices of the shape, assuming that the shape
    // uses the numVertices coordinates beginning at the value in
    // startIndex. (If numVertices is negative, it uses all
    // coordinates from startIndex on.) It also sets the center to the
    // average of the vertices' coordinates.
    void		computeCoordBBox(SoAction *action, int numVertices,
					 SbBox3f &box, SbVec3f &center);

    virtual ~SoNonIndexedShape();
};

#endif /* _SO_NON_INDEXED_SHAPE_ */
