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
 |   $Revision: 1.3 $
 |
 |   Description:
 |	This file defines the SoWindowElement class.
 |
 |   Author(s)		: Alain Dumesny
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_WINDOW_ELEMENT
#define  _SO_WINDOW_ELEMENT

#include <Inventor/elements/SoSubElement.h>
#include <X11/Intrinsic.h>
#include <GL/glx.h>

class SoGLRenderAction;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoWindowElement
//
//  Element that stores the current window attributes. The current window
//  is defined as the OpenGL window underneath the cursor - or NULL if the
//  cursor is not over an OpenGL window.
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoWindowElement : public SoElement {

    SO_ELEMENT_HEADER(SoWindowElement);

  public:
    // Initializes element
    virtual void	init(SoState *state);

    // Always returns TRUE, since this element should never be a
    // criterion for cache invalidation.
    virtual SbBool	matches(const SoElement *elt) const;

    // Create and return a copy of this element
    virtual SoElement	*copyMatchInfo() const;

    // Sets the window, context and glRenderAction info
    static void		set(SoState *state, Window window, GLXContext context, 
			    Display *display, SoGLRenderAction *glAction);

    // Returns the current window, context and glRenderAction
    static void	get(SoState *state, Window &window, GLXContext &context, 
			    Display *&display, SoGLRenderAction *&glAction);
    
    virtual void    push(SoState *state);
    
  SoINTERNAL public:
    // Initializes the SoWindowElement class
    static void		initClass();

  protected:
    Window		window;
    GLXContext		context;
    Display		*display;
    SoGLRenderAction	*glRenderAction;
    
    virtual	~SoWindowElement();
};

#endif /* _SO_WINDOW_ELEMENT */
