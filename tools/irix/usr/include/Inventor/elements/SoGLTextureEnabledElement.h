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
 |	This file defines the SoGLTextureEnabledElement class.
 |
 |   Author(s)		: Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_GL_TEXTURE_ENABLED_ELEMENT
#define  _SO_GL_TEXTURE_ENABLED_ELEMENT

#include <Inventor/elements/SoInt32Element.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoGLTextureEnabledElement
//
//  Element that enables/disables textures.  This is implemented as a
//  separate element from the TextureImageElement so the texture image
//  can be changed without blowing caches containing shapes-- shapes
//  need to know if texturing is going on or not so they can decide to
//  send down texture coordinates or not.
//
//  This is set by the GLTextureImageElement and the
//  GLTextureImageElement; the interaction between the three is a
//  little complicated.  Each of the other two elements always sets up
//  the GL texture state appropriately; however, texturing is only
//  enabled if both elements agree that it should be enabled (they
//  check each other's value before calling set).
//
//  This element cannot be overridden, but, since the elements that
//  set it check each other's value, overriding those elements has
//  the same effect.
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoGLTextureEnabledElement :
	public SoInt32Element {

    SO_ELEMENT_HEADER(SoGLTextureEnabledElement);

  public:
    // Initializes element
    virtual void	init(SoState *state);

    // Used by GLTextureImageElement, set to TRUE when a non-null
    // image is set, set to FALSE when there is no texture image (the
    // default).
    static void		set(SoState *state, SbBool value);

#ifndef IV_STRICT
    static void         set(SoState *state, SoNode *, SbBool value)
        { set(state, value); }
#endif

    // Used by shapes to figure out if they need to send texture
    // coordinates:
    static SbBool	get(SoState *state)
	{ return (SbBool)SoInt32Element::get(classStackIndex, state); }

    // By default there is not texture
    static SbBool	getDefault()	{ return FALSE; }

    // Override push() so we can remember previous elements value and
    // avoid making GL calls if this element has the same value.
    virtual void	push(SoState *state);

    // Override pop() method so side effects can occur in GL
    virtual void	pop(SoState *state, const SoElement *prevTopElement);

  SoINTERNAL public:
    // Initializes the SoGLTextureEnabledElement class
    static void		initClass();

    // Override base class set to make GL calls.
    virtual void	setElt(int32_t value);

    virtual ~SoGLTextureEnabledElement();

  private:
    // We save the state to figure out if the lastPattern variable was
    // copied from a parent element; if it was, then caches will have
    // to depend on that element because if it changes we have to have
    // a chance to change our decision about what GL calls to make.
    // If this is NULL, then there are no cache dependencies.
    SoState *		copiedFromParent;

    // Sends enabled in element to GL
    void		send();
};

#endif /* _SO_GL_TEXTURE_ENABLED_ELEMENT */
