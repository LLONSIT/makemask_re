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
 |	This file defines the SoGLDrawStyleElement class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_GL_DRAW_STYLE_ELEMENT
#define  _SO_GL_DRAW_STYLE_ELEMENT

#include <Inventor/elements/SoDrawStyleElement.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoGLDrawStyleElement
//
//  Element that changes the current draw style in GL. Overrides the
//  virtual methods on SoDrawStyleElement to send the draw style to GL
//  when necessary.
//
//  Note that this class relies on SoDrawStyleElement to store the
//  style in the instance.
//
//  Also note that this tells GL only how to draw polygons. Shapes
//  that contain lines still have to check for POINTS draw styles and
//  act accordingly.
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoGLDrawStyleElement : public SoDrawStyleElement {

    SO_ELEMENT_HEADER(SoGLDrawStyleElement);

  public:
    // Initializes element
    virtual void	init(SoState *state);

    // Override push() so we can remember the previous element's draw
    // style, and perhaps avoid sending unnecessary GL calls if this
    // element is the same.
    virtual void	push(SoState *state);

    // Override pop() method so side effects can occur in GL
    virtual void	pop(SoState *state, const SoElement *prevTopElement);

  SoINTERNAL public:
    // Initializes the SoGLDrawStyleElement class
    static void		initClass();

  protected:
    // Sets the draw style in an instance. Has GL side effects.
    virtual void	setElt(int32_t style);

    virtual ~SoGLDrawStyleElement();

  private:
    // We save the state to figure out if the lastPattern variable was
    // copied from a parent element; if it was, then caches will have
    // to depend on that element because if it changes we have to have
    // a chance to change our decision about what GL calls to make.
    // If this is NULL, then there are no cache dependencies.
    SoState *		copiedFromParent;

    // Sends draw style in element to GL
    void		send();
};

#endif /* _SO_GL_DRAW_STYLE_ELEMENT */
