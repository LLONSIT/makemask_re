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
 |   $Revision: 2.6 $
 |
 |   Description:
 |	This file defines the SoComplexityTypeElement class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_COMPLEXITY_TYPE_ELEMENT
#define  _SO_COMPLEXITY_TYPE_ELEMENT

#include <Inventor/elements/SoInt32Element.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoComplexityTypeElement
//
//  Element that stores the current complexity type.
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoComplexityTypeElement : public SoInt32Element {

    SO_ELEMENT_HEADER(SoComplexityTypeElement);

  public:
    // These are the available complexity types:
    enum Type {
	OBJECT_SPACE,		// Complexity computed in object space
	SCREEN_SPACE,		// Complexity computed in screen space
	BOUNDING_BOX		// Bounding box used to represent object
    };

    // Initializes element
    virtual void	init(SoState *state);

    // Sets the current complexity type in the state
    static void		set(SoState *state, Type type);

#ifndef IV_STRICT
    static void         set(SoState *state, SoNode *, Type type)
        { set(state, type); }
#endif

    // Returns current complexity type from the state
    static Type		get(SoState *state)
	{ return (Type)SoInt32Element::get(classStackIndex, state); }

    // Returns the default complexity type
    static Type		getDefault()		{ return OBJECT_SPACE; }

    // Prints element (for debugging)
    virtual void	print(FILE *fp) const;

  SoINTERNAL public:
    // Initializes the SoComplexityTypeElement class
    static void		initClass();

  protected:
    virtual ~SoComplexityTypeElement();
};

#endif /* _SO_COMPLEXITY_TYPE_ELEMENT */
