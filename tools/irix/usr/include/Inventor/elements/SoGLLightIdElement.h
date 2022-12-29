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
 |   $Revision: 2.4 $
 |
 |   Description:
 |	This file defines the SoGLLightIdElement class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_GL_LIGHT_ID_ELEMENT
#define  _SO_GL_LIGHT_ID_ELEMENT

#include <Inventor/elements/SoInt32Element.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoGLLightIdElement
//
//  Element that stores the id of the current light. The first light
//  active in a scene has id 0, the next has 1, and so on. This
//  element can be used to determine how many lights are currently
//  active. The initial value of this element is -1 to indicate that
//  there are no lights active.
//
//  Note that even though the effects of this element accumulate (each
//  light source increments the id), it is derived from
//  SoInt32Element. This is because each call to increment()
//  effectively does a "get" of the current top instance, so caching
//  knows about the dependency of each instance on the previous one.
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoGLLightIdElement : public SoInt32Element {

    SO_ELEMENT_HEADER(SoGLLightIdElement);

  public:
    // Initializes element
    virtual void	init(SoState *state);

    // Increments the current light id. This should be called when a
    // light source becomes active. This returns the new id, or -1 if
    // the maximum number of GL light sources has been exceeded.
    // Otherwise, enables light source.
    static int		increment(SoState *state);

#ifndef IV_STRICT
    static int		increment(SoState *state, SoNode *)
	{ return increment(state); }
#endif

    // Returns current light id from the state
    static int		get(SoState *state)
	{ return (int)SoInt32Element::get(classStackIndex, state); }

    // Returns the default light id
    static int		getDefault()			{ return -1; }

    // Returns the maximum number of concurrent light sources
    // supported by GL implementation
    static int		getMaxGLSources();

    // Overrides push() method to copy values from next instance in the stack
    virtual void	push(SoState *state);

    // Override pop() method so side effects can occur in GL
    virtual void	pop(SoState *state, const SoElement *prevTopElement);

    // Prints element (for debugging)
    virtual void	print(FILE *fp) const;

  SoINTERNAL public:
    // Initializes the SoGLLightIdElement class
    static void		initClass();

  protected:
    virtual ~SoGLLightIdElement();

  private:
    static int		maxGLSources;	// Holds max number of GL sources
};

#endif /* _SO_GL_LIGHT_ID_ELEMENT */
