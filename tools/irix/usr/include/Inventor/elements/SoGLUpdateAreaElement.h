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
 |	This file defines the SoGLUpdateAreaElement class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_UPDATE_AREA_ELEMENT
#define  _SO_UPDATE_AREA_ELEMENT

#include <Inventor/SbLinear.h>
#include <Inventor/elements/SoSubElement.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoGLUpdateAreaElement
//
//  Element that stores the rectangular area within the current
//  viewport region that needs to be updated when rendering. It can be
//  used for partial rendering updates when applications know that
//  only a portion of the objects need to be rerendered. Cameras can
//  use the info in this element to set up a view volume against which
//  culling can be performed. This element also sets up the GL scissor
//  box to limit drawing. 
//
//  The update area is specified in normalized viewport coordinates,
//  where (0,0) is the lower left corner of the viewport and (1,1) is
//  the upper right corner. The area is given as an origin and a size.
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoGLUpdateAreaElement : public SoElement {

    SO_ELEMENT_HEADER(SoGLUpdateAreaElement);

  public:
    // Initializes element
    virtual void	init(SoState *state);

    // Sets the current update area in the state. May have GL side effects.
    static void		set(SoState *state,
			    const SbVec2f &origin, const SbVec2f &size);

    // Returns current update area from the state. Returns TRUE if the
    // update area is the default, namely, the entire viewport.
    static SbBool	get(SoState *state, SbVec2f &origin, SbVec2f &size);

    // Returns the default update area origin and size
    static SbVec2f	getDefaultOrigin()	{ return SbVec2f(0.0, 0.0); }
    static SbVec2f	getDefaultSize()	{ return SbVec2f(1.0, 1.0); }

    // Override push() and pop() methods to keep GL up to date
    virtual void	push(SoState *state);
    virtual void	pop(SoState *state, const SoElement *prevTopElement);

    // Returns TRUE if the update areas match in both elements
    virtual SbBool	matches(const SoElement *elt) const;

    // Create and return a copy of this element
    virtual SoElement	*copyMatchInfo() const;

    // Prints element (for debugging)
    virtual void	print(FILE *fp) const;

  SoINTERNAL public:
    // Initializes the SoGLUpdateAreaElement class
    static void		initClass();

  protected:
    SbVec2f		origin, size;

    virtual ~SoGLUpdateAreaElement();

  private:
    // This flag lets us know if the element is set to its initial
    // default value, which is not sent to GL. This is so we can tell
    // whether the GL value is up to date.
    SbBool		isDefault;

    // Sends region in element to GL
    void		send(SoState *state);
};

#endif /* _SO_UPDATE_AREA_ELEMENT */
