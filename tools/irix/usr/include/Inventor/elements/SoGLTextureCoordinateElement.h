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
 |	Subclass of TextureCoordinateElement that also support GL
 |   rendering-- it has send() methods, and has a getType() that can
 |   return NONE, meaning shapes don't have to do anything to get
 |   texture coordinates generated for them (the GL's TexGen will do
 |   it for them).
 |
 |   Author(s)		: Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_GL_TEXTURE_COORDINATE_ELEMENT
#define  _SO_GL_TEXTURE_COORDINATE_ELEMENT

#include <Inventor/SbLinear.h>
#include <Inventor/elements/SoTextureCoordinateElement.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoGLTextureCoordinateElement
//
//  Element storing the current gltexture coordinates
//
//////////////////////////////////////////////////////////////////////////////

//
// The TextureCoordinateFunction nodes that use the GL texgen function
// to generate texture coordinates must register a callback that makes
// the appropriate GL calls with the element so pop() can reset the GL
// state back to what it should be.  The TextureCoordinateFunction
// nodes that can't use the GL texgen function must register a NULL
// callback, in which case the element will disable the GL's automatic
// texture coordinate generation.
//
typedef void SoTexCoordTexgenCB(void *userdata);

SoEXTENDER class SoGLTextureCoordinateElement :
				public SoTextureCoordinateElement {

    SO_ELEMENT_HEADER(SoGLTextureCoordinateElement);

  public:
    // Initializes element.
    virtual void	init(SoState *state);

    // TextureCoordinateFunction nodes that use texgen must define and
    // register a callback that makes the appropriate GL calls.
    // TextureCoordinateFunction nodes that don't use texgen must
    // register a NULL callback to turn off texgen.
    // The texGen arguments point to a function that will issue GL
    // TexGen calls; the func arguments must point to a static
    // function that will return the results of the texgen function
    // (needed because some nodes render by using their
    // generatePrimitives method).
    static void		setTexGen(SoState *state, SoNode *node, 
	    SoTexCoordTexgenCB *texGenFunc, void *texGenData = NULL,
	    SoTextureCoordinateFunctionCB *func = NULL,
	    void *funcData = NULL);

    // Returns code indicating what has been set in state/element
    virtual CoordType	getType() const;

    // Returns the top (current) instance of the element in the state.
    // The send routines are called on an instance
    // because it is more efficient than calling a static method that
    // looks up the element in the state for every coordinate.
    static const SoGLTextureCoordinateElement * getInstance(SoState *state);

    // Send routine for EXPLICIT case:

    void		send(int index) const;

    // Override push() method to set up new instance
    virtual void	push(SoState *state);

    // Override pop() method to maintain GL state
    virtual void	pop(SoState *state, const SoElement *prevTopElement);

  SoINTERNAL public:
    // Initializes the SoGLTextureCoordinateElement class
    static void		initClass();

  protected:
    void	setElt(SoTexCoordTexgenCB *function,
		       void *userData = NULL);

    virtual ~SoGLTextureCoordinateElement();

  private:
    SoTexCoordTexgenCB	*texgenCB;
    void		*texgenCBData;
    SoState 		*copiedFromParent;
};

#endif /* _SO_GL_TEXTURE_COORDINATE_ELEMENT */
