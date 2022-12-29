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
 |   $Revision: 2.3 $
 |
 |   Description:
 |	This file defines the SoFontSizeElement class.
 |
 |   Author(s)		: Paul S. Strauss, Nick Thompson, Thad Beier
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_FONT_SIZE_ELEMENT
#define  _SO_FONT_SIZE_ELEMENT

#include <Inventor/SbString.h>
#include <Inventor/elements/SoFloatElement.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoFontSizeElement
//
//  Element storing the current font size
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoFontSizeElement : public SoFloatElement {

    SO_ELEMENT_HEADER(SoFontSizeElement);

  public:
    // Initializes element
    virtual void	init(SoState *state);

    // set the current font size
    static void		set(SoState *state, float size)
	{ SoFloatElement::set(classStackIndex, state, size); }

#ifndef IV_STRICT
    static void         set(SoState *state, SoNode *, float size)
        { set(state, size); }
#endif

    // return the current font name from the state
    static float	get(SoState *state)
	{ return SoFloatElement::get(classStackIndex, state); }

    // Returns the default font size
    static float	getDefault()	{ return 10.0; }

  SoINTERNAL public:
    // Initializes class
    static void		initClass();

  protected:
    virtual ~SoFontSizeElement();
};

#endif /* _SO_FONT_SIZE_ELEMENT */
