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
 |	This file defines the SoGLViewingMatrixElement class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_GL_VIEWING_MATRIX_ELEMENT
#define  _SO_GL_VIEWING_MATRIX_ELEMENT

#include <Inventor/elements/SoViewingMatrixElement.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoGLViewingMatrixElement
//
//  Element that stores the current viewing matrix in GL. Overrides
//  the virtual methods on SoViewingMatrixElement to send the matrix
//  to GL when necessary.
//
//  Note that this class relies on SoViewingMatrixElement to store the
//  matrix in the instance.
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoGLViewingMatrixElement : public SoViewingMatrixElement {

    SO_ELEMENT_HEADER(SoGLViewingMatrixElement);

  public:
    // Override init() and push() to copy state pointer
    virtual void	init(SoState *state);
    virtual void	push(SoState *state);

    // Override pop() method so side effects can occur in GL
    virtual void	pop(SoState *state, const SoElement *prevTopElement);

  SoINTERNAL public:
    // Initializes the SoGLViewingMatrixElement class
    static void		initClass();

    // Used by SoGLModelMatrixElement when it need to figure out if
    // this element has changed between a glPushMatrix() and a
    // glPopMatrix():
    static uint32_t	getNodeId(SoState *state);

  protected:
    // Sets the matrix in an instance. Has GL side effects.
    virtual void	setElt(const SbMatrix &matrix);

    virtual ~SoGLViewingMatrixElement();

  private:
    // We need to store the state so we can get the model matrix element
    SoState		*state;

    // Sends matrix in element to GL
    void		send();
};

#endif /* _SO_GL_VIEWING_MATRIX_ELEMENT */
