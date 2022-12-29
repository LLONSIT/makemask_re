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
 |	This file defines the SoCreaseAngleElement class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_CREASE_ANGLE_ELEMENT
#define  _SO_CREASE_ANGLE_ELEMENT

#include <Inventor/elements/SoFloatElement.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoCreaseAngleElement
//
//  Element that stores the current crease angle that is used to
//  determine whether default normals should be computed to create a
//  sharp edge or a smooth surface.
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoCreaseAngleElement : public SoFloatElement {

    SO_ELEMENT_HEADER(SoCreaseAngleElement);

  public:
    // Initializes element
    virtual void	init(SoState *state);

    // Sets the current crease angle in the state
    static void		set(SoState *state, float angle)
	{ SoFloatElement::set(classStackIndex, state, angle); }

#ifndef IV_STRICT
    static void         set(SoState *state, SoNode *, float angle)
        { set(state, angle); }
#endif

    // Returns current crease angle from the state
    static float	get(SoState *state)
	{ return SoFloatElement::get(classStackIndex, state); }

    // Returns the default crease angle
    static float	getDefault()			{ return 0.0; }

    // Prints element (for debugging)
    virtual void	print(FILE *fp) const;

  SoINTERNAL public:
    // Initializes the SoCreaseAngleElement class
    static void		initClass();

  protected:
    virtual ~SoCreaseAngleElement();
};

#endif /* _SO_CREASE_ANGLE_ELEMENT */
