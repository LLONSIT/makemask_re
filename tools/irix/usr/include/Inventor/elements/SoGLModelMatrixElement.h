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
 |	This file defines the SoGLModelMatrixElement class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_GL_MODEL_MATRIX_ELEMENT
#define  _SO_GL_MODEL_MATRIX_ELEMENT

#include <Inventor/elements/SoModelMatrixElement.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoGLModelMatrixElement
//
//  Element that stores the current model matrix in GL. Overrides the
//  virtual methods on SoModelMatrixElement to send the matrix to GL
//  when necessary.
//
//  Note that this class relies on SoModelMatrixElement to store the
//  matrix in the instance. This is less expensive in the long run
//  than asking GL for the matrix when it is needed.
//
//  Because GL stores the model and view matrices in one matrix, this
//  has to do a little extra work when setting the model matrix to
//  identity or another matrix. (It has to set the GL model-view
//  matrix correctly.)
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoGLModelMatrixElement : public SoModelMatrixElement {

    SO_ELEMENT_HEADER(SoGLModelMatrixElement);

  public:
    // Initializes element
    virtual void	init(SoState *state);

    // Override push()/pop() methods so side effects can occur in GL
    virtual void	push(SoState *state);
    virtual void	pop(SoState *state, const SoElement *prevTopElement);

  SoINTERNAL public:
    // Initializes the SoGLModelMatrixElement class
    static void		initClass();

  protected:
    // Overrides SoModelMatrixElement::makeEltIdentity() to print an
    // error message
    virtual void	makeEltIdentity();

    // Sets the matrix in an instance to the given matrix. Assumes
    // that the passed matrix contains the correct combination of view
    // and model matrices.
    virtual void	setElt(const SbMatrix &matrix);

    // Multiplies into the matrix in an instance
    virtual void	multElt(const SbMatrix &matrix);

    // Each of these performs the appropriate operation on the matrix
    // in an instance
    virtual void	translateEltBy(const SbVec3f &translation);
    virtual void	rotateEltBy(const SbRotation &translation);
    virtual void	scaleEltBy(const SbVec3f &scaleFactor);
    virtual SbMatrix	pushMatrixElt();
    virtual void	popMatrixElt(const SbMatrix &m);

    virtual ~SoGLModelMatrixElement();

  private:
    // We need to save the state to access the viewing matrix
    SoState		*state;

    // And we need to remember the nodeId of the viewing matrix
    // element to see if it changes between pushMatrixElt() and
    // popMatrixElt().
    uint32_t		viewEltNodeId;
};

#endif /* _SO_GL_MODEL_MATRIX_ELEMENT */
