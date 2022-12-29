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
 |   $Revision: 2.2 $
 |
 |   Description:
 |	This file defines the SoBBoxModelMatrixElement class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_BBOX_MODEL_MATRIX_ELEMENT
#define  _SO_BBOX_MODEL_MATRIX_ELEMENT

#include <Inventor/elements/SoModelMatrixElement.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoBBoxModelMatrixElement
//
//  Element that stores the current model matrix for use with the
//  SoGetBoundingBoxAction. Overrides the virtual methods on
//  SoModelMatrixElement to also set the current
//  SoLocalBBoxMatrixElement.
//
//  This class relies on SoModelMatrixElement to store the matrix in
//  the instance, and inherits most of its methods from it.
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoBBoxModelMatrixElement : public SoModelMatrixElement {

    SO_ELEMENT_HEADER(SoBBoxModelMatrixElement);

  public:
    // Initializes element
    virtual void	init(SoState *state);

    // Overrides push() method to copy values from next instance in the stack
    virtual void	push(SoState *state);

    // Allows the SoGetBoundingBoxAction to reset the current model
    // matrix to identity and all currently-open local matrices to
    // identity
    static void		reset(SoState *state, SoNode *node);

    // Because two model matrices are kept track of during the
    // getBoundingBoxAction (the local model matrix, used by
    // Separators to calculate their bbox caches, and the real model
    // matrix), replacement routines for pushMatrix/popMatrix must be
    // given; TransformSeparator::getBoundingBox uses these methods to
    // correctly keep both matrices up-to-date.
    static void		pushMatrix(SoState *state,
				   SbMatrix &matrix,
				   SbMatrix &localmatrix);
    static void		popMatrix(SoState *state,
				   const SbMatrix &matrix,
				   const SbMatrix &localmatrix);

  SoINTERNAL public:
    // Initializes the SoBBoxModelMatrixElement class
    static void		initClass();

  protected:
    // These all override the methods on SoModelMatrixElement to also
    // set the SoLocalBBoxMatrixElement
    virtual void	makeEltIdentity();
    virtual void	setElt(const SbMatrix &matrix);
    virtual void	multElt(const SbMatrix &matrix);
    virtual void	translateEltBy(const SbVec3f &translation);
    virtual void	rotateEltBy(const SbRotation &translation);
    virtual void	scaleEltBy(const SbVec3f &scaleFactor);

    // These must never be called; they print debug errors if called:
    virtual SbMatrix	pushMatrixElt();
    virtual void	popMatrixElt(const SbMatrix &m);

    virtual ~SoBBoxModelMatrixElement();

  private:
    // Stores pointer to state so we can access the SoLocalBBoxMatrixElement
    SoState		*state;

    // This is used to make sure the pushMatrix/popMatrix methods are
    // called correctly.
    static SbBool	pushPopCallOK;
};

#endif /* _SO_BBOX_MODEL_MATRIX_ELEMENT */
