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
 |   $Revision: 2.7 $
 |
 |   Description:
 |	This file defines the SoDrawStyleElement class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_DRAW_STYLE_ELEMENT
#define  _SO_DRAW_STYLE_ELEMENT

#include <Inventor/elements/SoInt32Element.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoDrawStyleElement
//
//  Element that stores the current draw style.
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoDrawStyleElement : public SoInt32Element {

    SO_ELEMENT_HEADER(SoDrawStyleElement);

  public:
    // These are the available draw styles:
    enum Style {
	FILLED,			// Filled regions
	LINES,			// Outlined regions
	POINTS,			// Points
	INVISIBLE		// Nothing!
    };

    // Initializes element
    virtual void	init(SoState *state);

    // Sets the current draw style in the state
    static void		set(SoState *state, Style style);

#ifndef IV_STRICT
    static void         set(SoState *state, SoNode *, Style style)
        { set(state, style); }
#endif

    // Returns current draw style from the state
    static Style	get(SoState *state)
	{ return (Style)SoInt32Element::get(classStackIndex, state); }

    // Returns the default draw style
    static Style	getDefault()		{ return FILLED; }

    // Prints element (for debugging)
    virtual void	print(FILE *fp) const;

  SoINTERNAL public:
    // Initializes the SoDrawStyleElement class
    static void		initClass();

  protected:
    virtual ~SoDrawStyleElement();
};

#endif /* _SO_DRAW_STYLE_ELEMENT */
