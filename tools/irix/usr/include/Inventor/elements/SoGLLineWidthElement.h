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
 |	This file defines the SoGLLineWidthElement class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_GL_LINE_WIDTH_ELEMENT
#define  _SO_GL_LINE_WIDTH_ELEMENT

#include <Inventor/elements/SoLineWidthElement.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoGLLineWidthElement
//
//  Element that stores the current line width in GL. Overrides the
//  virtual methods on SoLineWidthElement to send the line width to GL
//  when necessary.
//
//  Note that this class relies on SoLineWidthElement to store the
//  width in the instance.
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoGLLineWidthElement : public SoLineWidthElement {

    SO_ELEMENT_HEADER(SoGLLineWidthElement);

  public:
    // Initializes element
    virtual void	init(SoState *state);

    // Override push() method to copy state pointer and value of
    // previous element, to avoid sending GL commands if the elements
    // are the same.
    virtual void	push(SoState *state);

    // Override pop() method so side effects can occur in GL
    virtual void	pop(SoState *state, const SoElement *prevTopElement);

  SoINTERNAL public:
    // Initializes the SoGLLineWidthElement class
    static void		initClass();

  protected:
    // Sets the line width in an instance. Has GL side effects.
    virtual void	setElt(float width);

    virtual ~SoGLLineWidthElement();

  private:
    // This variable is TRUE if the value in this element was copied
    // from our parent.  If set is called with the same value, no GL
    // commands have to be done-- it is as if this element doesn't
    // exist, and the parent's value is used.  Of course, a cache
    // dependency will have to be added in this case (if the parent
    // changes, the cache is not valid).  Set sets this flag to false.
    SbBool		copiedFromParent;

    // We need to store the state so we can get the viewport region element
    SoState		*state;

    // Sends line width in element to GL
    void		send();
};

#endif /* _SO_GL_LINE_WIDTH_ELEMENT */
