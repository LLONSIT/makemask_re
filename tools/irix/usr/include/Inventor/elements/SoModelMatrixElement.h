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
 |	This file defines the SoModelMatrixElement class.
 |
 |   Author(s)		: Paul S. Strauss, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_MODEL_MATRIX_ELEMENT
#define  _SO_MODEL_MATRIX_ELEMENT

#include <Inventor/SbLinear.h>
#include <Inventor/elements/SoAccumulatedElement.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoModelMatrixElement
//
//  Element that stores the current model matrix - the cumulative
//  transformation applied to subsequent shapes. Because the matrix is
//  cumulative, this class is derived from SoAccumulatedElement. The
//  set() method replaces the current matrix, while all the others
//  (mult(), translateBy(), etc.) multiply into it. Node id's of the
//  nodes that affect the element are accumulated properly.
//
//  This element also stores the current view-volume culling
//  transformation, which is normally the view*projection matrices
//  (set by cameras), but which may be modified by sophisticated
//  culling schemes.
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoModelMatrixElement : public SoAccumulatedElement {

    SO_ELEMENT_HEADER(SoModelMatrixElement);

  public:
    // Initializes element
    virtual void	init(SoState *state);
    
    // Override standard matches to invalidate on cull-test
    virtual SbBool	matches(const SoElement *elt) const;


    // Overrides push() method to copy values from next instance in the stack
    virtual void	push(SoState *state);

    // Sets the model matrix to the identity matrix
    static void		makeIdentity(SoState *state, SoNode *node);

    // Sets the model matrix to the given matrix
    static void		set(SoState *state, SoNode *node,
			    const SbMatrix &matrix);

    // Multiplies the given matrix into the model matrix
    static void		mult(SoState *state, SoNode *node,
			     const SbMatrix &matrix);

    // Each of these multiplies a matrix that performs the specified
    // transformation into the model matrix
    static void		translateBy(SoState *state, SoNode *node,
				    const SbVec3f &translation);
    static void		rotateBy(SoState *state, SoNode *node,
				 const SbRotation &rotation);
    static void		scaleBy(SoState *state, SoNode *node,
				const SbVec3f &scaleFactor);

    // These methods are used by the TransformSeparator node.
    // WARNING!  For proper caching behavior, the matrix returned by
    // ::pushMatrix() must be used ONLY as a later argument to
    // ::popMatrix(), and you must NOT modify the matrix between the
    // push and the pop.  If you need the matrix for any other reason,
    // you MUST use the ::get() routine.
    static SbMatrix	pushMatrix(SoState *state);
    static void		popMatrix(SoState *state, const SbMatrix &m);

    // Sets the transformation that defines the volume that
    // view-volume culling should be tested against.
    static void		setCullMatrix(SoState *state, SoNode *node,
				      const SbMatrix &matrix);

    // This method gets the model*cullMatrix combined matrix (which is
    // cached by this element).
    static const SbMatrix &	getCombinedCullMatrix(SoState *state);

    // Returns current model matrix from the state
    static const SbMatrix &	get(SoState *state);

    // Returns current model matrix from the state, sets given flag to TRUE
    // if matrix is known to be identity
    static const SbMatrix &	get(SoState *state, SbBool &isIdent);

    // Prints element (for debugging)
    virtual void	print(FILE *fp) const;

  SoINTERNAL public:
    // Initializes the SoModelMatrixElement class
    static void		initClass();

  protected:
    // Sets the matrix in an instance to identity
    virtual void	makeEltIdentity();

    // Sets the matrix in an instance to given matrix
    virtual void	setElt(const SbMatrix &matrix);

    // Multiplies into the matrix in an instance
    virtual void	multElt(const SbMatrix &matrix);

    // Each of these performs the appropriate operation on the matrix
    // in an instance
    virtual void	translateEltBy(const SbVec3f &translation);
    virtual void	rotateEltBy(const SbRotation &translation);
    virtual void	scaleEltBy(const SbVec3f &scaleFactor);

    // virtual methods for push/pop so GL element can Do The Right Thing:
    virtual SbMatrix	pushMatrixElt();
    virtual void	popMatrixElt(const SbMatrix &m);

    virtual ~SoModelMatrixElement();

  private:
    SbMatrix		modelMatrix;
    SbMatrix		cullMatrix;
    SbMatrix		modelCullMatrix;
    struct {
	unsigned int 	isModelIdentity : 1;
	unsigned int	haveCullMatrix	: 1; // TRUE if cullMatrix set
	unsigned int	haveModelCull	: 1; // TRUE if model*cull computed
    } flags;

    friend class SoLocalBBoxMatrixElement;
};

#endif /* _SO_MODEL_MATRIX_ELEMENT */
