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
 |	This file defines the SoTransform node class.
 |
 |   Author(s)		: Paul S. Strauss, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_TRANSFORM_
#define  _SO_TRANSFORM_

#include <Inventor/fields/SoSFRotation.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/nodes/SoTransformation.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTransform
//
//  Geometric transformation node.
//
//////////////////////////////////////////////////////////////////////////////

class SoTransform : public SoTransformation {

    SO_NODE_HEADER(SoTransform);

  public:
    // Fields
    SoSFVec3f		translation;	 // Translation vector
    SoSFRotation	rotation;	 // Rotation
    SoSFVec3f		scaleFactor;	 // Scale factors
    SoSFRotation	scaleOrientation;// Defines rotational space for scale
    SoSFVec3f		center;	         // Center point for scale and rotate

    // Constructor
    SoTransform();

    // Sets the transform to translate the origin to the fromPoint and
    // rotate the negative z-axis (0,0,-1) to lie on the vector from
    // fromPoint to toPoint. This always tries to keep the "up"
    // direction the positive y-axis, unless that is impossible.
    // All current info in the node is wiped out.
    void		pointAt(const SbVec3f &fromPoint,
				const SbVec3f &toPoint);

    // returns composite matrices that take you from object space to each
    // of scale/rotation/translation spaces
    void		getScaleSpaceMatrix(SbMatrix &mat, SbMatrix &inv) const;
    void		getRotationSpaceMatrix(SbMatrix &mat,
                                               SbMatrix &inv) const;
    void		getTranslationSpaceMatrix(SbMatrix &mat,
                                                  SbMatrix &inv) const;

    // Convenience functions that combine the effects of a matrix
    // transformation into the transformation stored in this node. The
    // first method premultiplies the transformation and the second
    // postmultiplies it.
    void		multLeft(const SbMatrix &mat);
    void		multRight(const SbMatrix &mat);

    // These are the same as multLeft() and multRight(), except that
    // the transformation to multiply into this node comes from
    // another transformation node.
    void		combineLeft(SoTransformation *nodeOnLeft);
    void		combineRight(SoTransformation *nodeOnRight);

    // Sets the fields in the node to implement the transformation
    // represented by the given matrix
    void		setMatrix(const SbMatrix &mat);

    // Changes the center of the transformation to the given point
    // without affecting the overall effect of the transformation
    void		recenter(const SbVec3f &newCenter);

  SoEXTENDER public:
    virtual void	doAction(SoAction *action);
    virtual void	callback(SoCallbackAction *action);
    virtual void	GLRender(SoGLRenderAction *action);
    virtual void	getBoundingBox(SoGetBoundingBoxAction *action);
    virtual void	getMatrix(SoGetMatrixAction *action);
    virtual void	pick(SoPickAction *action);

  SoINTERNAL public:
    static void		initClass();

  protected:
    virtual ~SoTransform();
};

#endif /* _SO_TRANSFORM_ */
