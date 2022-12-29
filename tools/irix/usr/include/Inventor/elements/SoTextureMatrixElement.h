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
 |	This file defines the SoTextureMatrixElement class.
 |
 |   Author(s)		: Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_TEXTURE_MATRIX_ELEMENT
#define  _SO_TEXTURE_MATRIX_ELEMENT

#include <Inventor/SbLinear.h>
#include <Inventor/elements/SoAccumulatedElement.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTextureMatrixElement
//
//  Element that stores the current texture matrix - the cumulative
//  transformation applied to subsequent shapes. Because the matrix is
//  cumulative, this class is derived from SoAccumulatedElement. The
//  set() method replaces the current matrix, while all the others
//  (mult(), translateBy(), etc.) multiply into it. Node id's of the
//  nodes that affect the element are accumulated properly.
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoTextureMatrixElement : public SoAccumulatedElement {

    SO_ELEMENT_HEADER(SoTextureMatrixElement);

  public:
    // Initializes element
    virtual void	init(SoState *state);

    // Overrides push() method to copy values from next instance in the stack
    virtual void	push(SoState *state);

    // Sets the texture matrix to the identity matrix
    static void		makeIdentity(SoState *state, SoNode *node);

    // Multiplies the given matrix into the texture matrix
    static void		mult(SoState *state, SoNode *node,
			     const SbMatrix &matrix);

    // Each of these multiplies a matrix that performs the specified
    // transformation into the texture matrix
    static void		translateBy(SoState *state, SoNode *node,
				    const SbVec3f &translation);
    static void		rotateBy(SoState *state, SoNode *node,
				 const SbRotation &rotation);
    static void		scaleBy(SoState *state, SoNode *node,
				const SbVec3f &scaleFactor);

    // Returns current matrix from the state
    static const SbMatrix &	get(SoState *state);

    // Prints element (for debugging)
    virtual void	print(FILE *fp) const;

  SoINTERNAL public:
    // Initializes the SoTextureMatrixElement class
    static void		initClass();

  protected:
    SbMatrix		textureMatrix;

    // Sets the matrix in an instance to identity
    virtual void	makeEltIdentity();

    // Multiplies into the matrix in an instance
    virtual void	multElt(const SbMatrix &matrix);

    // Each of these performs the appropriate operation on the matrix
    // in an instance
    virtual void	translateEltBy(const SbVec3f &translation);
    virtual void	rotateEltBy(const SbRotation &translation);
    virtual void	scaleEltBy(const SbVec3f &scaleFactor);

    // Gets the matrix from an instance
    virtual const SbMatrix &	getElt() const;

    virtual ~SoTextureMatrixElement();
};

#endif /* _SO_TEXTURE_MATRIX_ELEMENT */
