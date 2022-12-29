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
 |	This file defines the base SoPickedPoint class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef _SO_PICKED_POINT_
#define _SO_PICKED_POINT_

#include <Inventor/SbLinear.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/SoLists.h>

class SoDetail;
class SoGetMatrixAction;
class SoPath;
class SoState;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoPickedPoint
//
//  An SoPickedPoint represents a point on the surface of an object
//  that was picked by applying an SoRayPickAction to a scene. It
//  contains the point of intersection, the surface normal and texture
//  coordinates at that point, and other items.
//
//////////////////////////////////////////////////////////////////////////////

class SoPickedPoint {

  public:
    // Copy constructor
    SoPickedPoint(const SoPickedPoint &pp);

    // Destructor
    ~SoPickedPoint();

    // Returns an instance that is a copy of this instance. The caller
    // is responsible for deleting the copy when done.
    SoPickedPoint *	copy() const;

    // These return the intersection point and surface normal in world
    // space, and the texture coordinates in image space:
    const SbVec3f &	getPoint() const	 { return worldPoint; }
    const SbVec3f &	getNormal() const	 { return worldNormal; }
    const SbVec4f &	getTextureCoords() const { return imageTexCoords; }

    // Returns the index into the current set of materials of the
    // material active at the intersection point. Note that if the
    // materials are interpolated between vertices, the index will
    // correspond to the material at one of the vertices.
    int			getMaterialIndex() const { return materialIndex; }

    // Returns the path to the object that was intersected
    SoPath *		getPath() const		 { return path; }

    // Returns whether the intersection is actually on the geometry of
    // the character that was hit, as opposed to being on the bounding
    // box. The pick style affects this decision.
    SbBool		isOnGeometry() const	 { return onGeometry; }

    //////////////////////
    //
    // The following methods all take a pointer to a node in the
    // returned path. If the node pointer is NULL (the default), the
    // information corresponding to the tail of the path is returned.
    //

    // Returns the detail that corresponds to the given node in the path
    const SoDetail *	getDetail(const SoNode *node = NULL) const;

    // These return the transformation matrices between world space
    // and the object space corresponding to the given node in the path
    SbMatrix		getObjectToWorld(const SoNode *node = NULL) const;
    SbMatrix		getWorldToObject(const SoNode *node = NULL) const;

    // These return the texture transformation matrices between image
    // space and the object space corresponding to the given node in
    // the path
    SbMatrix		getObjectToImage(const SoNode *node = NULL) const;
    SbMatrix		getImageToObject(const SoNode *node = NULL) const;

    // These return the intersection point, surface normal, and
    // texture coordinates in the object space corresponding to the
    // given node in the path
    SbVec3f		getObjectPoint(const SoNode *node = NULL) const;
    SbVec3f		getObjectNormal(const SoNode *node = NULL) const;
    SbVec4f		getObjectTextureCoords(const SoNode *node=NULL) const;

    //
    //////////////////////

  SoEXTENDER public:

    // NOTE: these methods should be called ONLY by the node that
    // causes the SoPickedPoint instance to be created, and ONLY at
    // the time it is created. Setting or changing the normal or
    // texture coordinates at a later time may cause undefined results.

    // Sets the normal in object space
    void		setObjectNormal(const SbVec3f &normal);

    // Sets the texture coordinates in object space
    void		setObjectTextureCoords(const SbVec4f &texCoords);

    // Sets the material index
    void		setMaterialIndex(int index)  { materialIndex = index; }

    // Sets the detail corresponding to the given node in the path.
    // NULL may be passed to remove a detail. All detail pointers are
    // NULL by default.
    void		setDetail(SoDetail *detail, SoNode *node);

  SoINTERNAL public:

    // The constructor is internal since instances are created only by
    // the SoRayPickAction
    SoPickedPoint(const SoPath *path, SoState *state,
		  const SbVec3f &objSpacePoint);

  private:
    // This action is used to get the world-to-object matrix
    static SoGetMatrixAction	*matrixAction;

    // Intersection point and normal in world space, and texture
    // coordinates in image space
    SbVec3f		worldPoint;
    SbVec3f		worldNormal;
    SbVec4f		imageTexCoords;

    // ViewportRegion, which is needed when figuring out matrices
    SbViewportRegion	vpRegion;

    // Material index
    int			materialIndex;

    // TRUE if pick was on geometry of shape as opposed to bbox
    SbBool		onGeometry;

    // The path to the shape that was picked
    SoPath		*path;

    // Details corresponding to nodes in path, one per node in path.
    // Many may be NULL.
    SoDetailList	details;

    // The pointer to the state allows us to access matrices to
    // convert from object space to world and image space. This
    // pointer is valid only during construction and setting of the
    // info inside the instance.
    SoState		*state;

    // Returns index in path of given node, or -1 if not found
    int			getNodeIndex(const SoNode *node) const;

    // Applies SoGetMatrixAction to path to node
    void		getMatrix(const SoNode *node) const;

    // Multiplies SbVec4f by matrix - for transforming texture coords
    static SbVec4f multVecMatrix4(const SbMatrix &m, const SbVec4f v);
};

#endif /* _SO_PICKED_POINT_ */
