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
 |	This file defines the SoSwitchElement class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_SWITCH_ELEMENT
#define  _SO_SWITCH_ELEMENT

#include <Inventor/elements/SoInt32Element.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoSwitchElement
//
//  Element that stores the current switch index. This is set by
//  several nodes and is used to allow SoSwitch nodes to inherit the
//  index.
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoSwitchElement : public SoInt32Element {

    SO_ELEMENT_HEADER(SoSwitchElement);

  public:
    // Initializes element
    virtual void	init(SoState *state);

    // Sets the current switch index in the state
    static void		set(SoState *state, int32_t index)
	{ SoInt32Element::set(classStackIndex, state, index); }

#ifndef IV_STRICT
    static void         set(SoState *state, SoNode *, int32_t index)
        { set(state, index); }
#endif

    // Returns current switch index from the state
    static int32_t		get(SoState *state)
	{ return SoInt32Element::get(classStackIndex, state); }

    // Returns the default switch index
    static int32_t		getDefault()		{ return -1; }

  SoINTERNAL public:
    // Initializes the SoSwitchElement class
    static void		initClass();

  protected:
    virtual ~SoSwitchElement();
};

#endif /* _SO_SWITCH_ELEMENT */
