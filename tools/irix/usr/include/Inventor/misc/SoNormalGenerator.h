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
 |	This file contains the definition of the SoNormalGenerator class.
 |
 |   Author(s)		: Thad Beier, Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */


#ifndef  _SO_NORMAL_GENERATOR_
#define  _SO_NORMAL_GENERATOR_

#include <Inventor/SbLinear.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoNormalGenerator (extender)
//
//  This class can be used by polyhedral shape classes to generate
//  surface normals when they do not have valid ones specified. To
//  generate normals, create an instance of this class, then specify
//  each polygon in the shape, then call generate(). After generate()
//  is called, the normals can be accessed from the instance. There
//  will be one normal generated for each vertex of each polygon, in
//  the order passed in.
//
//  For convenience, there is a method to send down a triangle of
//  vertices.
//
//  For efficiency, a constructor is provided that takes an
//  approximate number of vertices that will be specified. Use this
//  constructor if you know roughly how many vertices will be sent;
//  this will cut down on allocation overhead.
//
//  The generate() method takes a crease angle that is used to
//  determine whether to create normals that simulate a sharp crease
//  at an edge between two polygons or to create normals that simulate
//  smooth shading over the edge. The crease angle is the minimum
//  angle (in radians) between the face normals on either side of an
//  edge that will be used to consider the edge a crease. For example,
//  a crease angle of pi/4 radians (45 degrees) means that adjacent
//  face normals must be within 45 degrees of each other for the edge
//  to be shaded smoothly.
//
//  Note that the SoNormalGenerator destructor DOES NOT delete the
//  array of generated normals. The caller is responsible for doing
//  so. This allows the normals to be cached elsewhere without having
//  to copy them.
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoNormalGenerator {

  public:
    // Constructors and destructor
    SoNormalGenerator(SbBool isCCW);
    SoNormalGenerator(SbBool isCCW, int approxNumVertices);
    ~SoNormalGenerator();

    // Send a polygon's worth of vertices. Begin a polygon, send as
    // many vertices as you want, and then end the polygon.
    void		beginPolygon();
    void		polygonVertex(const SbVec3f &point);
    void		endPolygon();

    // Send a triangle
    void		triangle(const SbVec3f &p1,
				 const SbVec3f &p2,
				 const SbVec3f &p3);

    // Calculate the normals once all vertices have been sent
    void		generate(float creaseAngle);

    //
    // The rest of the methods may be called only AFTER generate() has
    // been called:
    //

    // Returns number of normals generated. This will be equal to the
    // number of points sent.
    int			getNumNormals() const	{ return numVertNormals; }

    // Truncate the array so there are only the given number of normals
    void		setNumNormals(int newNum);

    // Returns a pointer to the array of normals
    const SbVec3f *	getNormals() const 	{ return vertNormals; }

    // Returns the i'th normal in the array
    const SbVec3f &	getNormal(int32_t i) const	{ return vertNormals[i]; }

    // Some shapes may need to adjust or reorder normals after
    // generation. This method can be used to change a normal. It will
    // insert room in the array if necessary to accommodate the new
    // normal.
    void		setNormal(int32_t index, const SbVec3f &newNormal);

  private:
    // Arrays of vertex points, face normals, and vertex normals. The
    // face normals are stored one per vertex. The other vars are the
    // number of items in the arrays, and the allocated sizes of the
    // arrays. Since the points and faceNormals arrays are always the
    // same size, no need for extra variables.
    SbVec3f		*points, *faceNormals, *vertNormals;
    int32_t		numPoints, numVertNormals;
    int32_t		maxPoints, maxVertNormals;

    // Flag: if TRUE, polygons are oriented counter-clockwise
    SbBool		isCCW;

    // Index into points array where current polygon started
    int32_t		beginPolygonIndex;

    // Returns TRUE if the two points are the same within given tolerance
    static SbBool	equal(const SbVec3f &a, const SbVec3f &b, float tol);
};

#endif /* _SO_NORMAL_GENERATOR_ */
