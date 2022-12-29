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
 |   $Revision: 2.11 $
 |
 |   Description:
 |	This file defines the SoNormalBindingElement class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_NORMAL_BINDING_ELEMENT
#define  _SO_NORMAL_BINDING_ELEMENT

#include <Inventor/elements/SoInt32Element.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoNormalBindingElement
//
//  Element that stores the current normal binding.
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoNormalBindingElement : public SoInt32Element {

    SO_ELEMENT_HEADER(SoNormalBindingElement);

  public:
    // The (seemingly random) choice of values is for compatibility
    // with Inventor 2.0 binary format files:
    enum Binding {
	OVERALL = 2,		// Whole object has same normal
	PER_PART = 3,		// One normal for each part of object
	PER_PART_INDEXED = 4,	// One normal for each part, indexed
	PER_FACE = 5,		// One normal for each face of object
	PER_FACE_INDEXED = 6,	// One normal for each face, indexed
	PER_VERTEX = 7,		// One normal for each vertex
	PER_VERTEX_INDEXED = 8	// One normal for each vertex, indexed
        
#ifndef IV_STRICT
        // Obsolete bindings:
        ,                       // Comma to continue list
        DEFAULT = PER_VERTEX_INDEXED,
        NONE = OVERALL
#endif

    };

    // Initializes element
    virtual void	init(SoState *state);

    // Sets the current normal binding in the state
    static void		set(SoState *state, Binding binding)
	{ SoInt32Element::set(classStackIndex, state, (int32_t)binding); }

#ifndef IV_STRICT
    static void         set(SoState *state, SoNode *, Binding binding)
        { set(state, binding); }
#endif

    // Returns current normal binding from the state
    static Binding	get(SoState *state)
	{ return (Binding)SoInt32Element::get(classStackIndex, state); }

    // Returns the default normal binding
    static Binding	getDefault()		{ return PER_VERTEX_INDEXED; }

    // Prints element (for debugging)
    virtual void	print(FILE *fp) const;

  SoINTERNAL public:
    // Initializes the SoNormalBindingElement class
    static void		initClass();

  protected:
    virtual ~SoNormalBindingElement();
};

#endif /* _SO_NORMAL_BINDING_ELEMENT */
