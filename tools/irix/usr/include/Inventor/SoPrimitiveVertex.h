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
 |	This file defines the base SoPrimitiveVertex class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef _SO_PRIMITIVE_VERTEX_
#define _SO_PRIMITIVE_VERTEX_

#include <Inventor/SbLinear.h>

class SoDetail;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoPrimitiveVertex
//
//  An SoPrimitiveVertex represents a vertex of a primitive (triangle,
//  line segment, point) that is being generated via the
//  SoCallbackAction.
//
//  An SoPrimitiveVertex contains an object-space point, normal,
//  texture coordinates, material index, and a pointer to an instance
//  of some SoDetail subclass. This detail may contain more
//  information about the vertex, or may be a NULL pointer if there is
//  no such info.
//
//  Instances of SoPrimitiveVertex are typically created on the stack
//  by shape classes while they are generating primitives. Anyone who
//  wants to save them as return values from SoCallbackAction should
//  probably make copies of them.
//
//////////////////////////////////////////////////////////////////////////////

class SoPrimitiveVertex {

  public:
    // Constructors
    SoPrimitiveVertex();
    SoPrimitiveVertex(const SoPrimitiveVertex &pv);

    // Destructor
    ~SoPrimitiveVertex();

    // These return the surface point, normal, and texture coordinates
    // in object space:
    const SbVec3f &	getPoint() const		{ return point; }
    const SbVec3f &	getNormal() const		{ return normal; }
    const SbVec4f &	getTextureCoords() const	{ return texCoords; }

    // Returns the index into the current set of materials of the
    // material active at the vertex
    int			getMaterialIndex() const    { return materialIndex; }

    // Returns the detail giving more info about the vertex. Note that
    // this pointer may be NULL.
    const SoDetail *	getDetail() const		{ return detail; }

    // Copy assignment operator. Note that just the pointer to the
    // detail is copied, and not the detail itself.
    SoPrimitiveVertex &	operator =(const SoPrimitiveVertex &pv);

  SoEXTENDER public:

    // These methods are typically called by shape classes during
    // primtiive generation

    // These set the object space point, normal, and texture coordinates:
    void		setPoint(const SbVec3f &pt)	  { point     = pt; }
    void		setNormal(const SbVec3f &norm)	  { normal    = norm; }
    void		setTextureCoords(const SbVec4f &t){ texCoords = t; }

    // Sets the material index. The index is set to 0 during construction.
    void		setMaterialIndex(int index)  { materialIndex = index; }

    // Sets the detail corresponding to the vertex. The pointer may be
    // NULL, although it is set to NULL during construction.
    void		setDetail(SoDetail *d)		  { detail = d; }

  private:
    SbVec3f		point;		// Object-space point
    SbVec3f		normal;		// Object-space normal
    SbVec4f		texCoords;	// Object-space texture coordinates
    int			materialIndex;	// Material index
    SoDetail		*detail;	// Extra detail info
};

#endif /* _SO_PRIMITIVE_VERTEX_ */
