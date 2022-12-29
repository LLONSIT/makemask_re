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
 |	This file defines the SoComplexityElement class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_COMPLEXITY_ELEMENT
#define  _SO_COMPLEXITY_ELEMENT

#include <Inventor/elements/SoFloatElement.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoComplexityElement
//
//  Element that stores the current shape complexity.
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoComplexityElement : public SoFloatElement {

    SO_ELEMENT_HEADER(SoComplexityElement);

  public:
    // Initializes element
    virtual void	init(SoState *state);

    // Sets the current complexity in the state
    static void		set(SoState *state, float comp)
	{ SoFloatElement::set(classStackIndex, state, comp); }

#ifndef IV_STRICT
    static void		set(SoState *state, SoNode *, float comp)
	{ set(state, comp); }
#endif

    // Returns current complexity from the state
    static float	get(SoState *state)
	{ return SoFloatElement::get(classStackIndex, state); }

    // Returns the default complexity
    static float	getDefault()			{ return 0.5; }

  SoINTERNAL public:
    // Initializes the SoComplexityElement class
    static void		initClass();

  protected:
    virtual ~SoComplexityElement();
};

#endif /* _SO_COMPLEXITY_ELEMENT */
