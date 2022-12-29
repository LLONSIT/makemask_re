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
 |	This file defines the SoProjectionMatrixElement class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_PROJECTION_MATRIX_ELEMENT
#define  _SO_PROJECTION_MATRIX_ELEMENT

#include <Inventor/SbLinear.h>
#include <Inventor/elements/SoReplacedElement.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoProjectionMatrixElement
//
//  Element that stores the current projection matrix - the projective
//  part of the matrix set up by the camera. Because most operations
//  on this matrix are atomic, it is considered a non-accumulating
//  element.
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoProjectionMatrixElement : public SoReplacedElement {

    SO_ELEMENT_HEADER(SoProjectionMatrixElement);

  public:
    // Initializes element
    virtual void	init(SoState *state);

    // Sets the projection matrix to the given matrix
    static void		set(SoState *state, SoNode *node,
			    const SbMatrix &matrix);

    // Returns current matrix from the state
    static const SbMatrix &	get(SoState *state);

    // Prints element (for debugging)
    virtual void	print(FILE *fp) const;

  SoINTERNAL public:
    // Initializes the SoProjectionMatrixElement class
    static void		initClass();

  protected:
    SbMatrix		projectionMatrix;

    // Sets the matrix in an instance
    virtual void	setElt(const SbMatrix &matrix);

    virtual ~SoProjectionMatrixElement();
};

#endif /* _SO_PROJECTION_MATRIX_ELEMENT */
