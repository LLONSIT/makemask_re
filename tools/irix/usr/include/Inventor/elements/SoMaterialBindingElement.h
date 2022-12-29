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
 |   $Revision: 2.10 $
 |
 |   Description:
 |	This file defines the SoMaterialBindingElement class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_MATERIAL_BINDING_ELEMENT
#define  _SO_MATERIAL_BINDING_ELEMENT

#include <Inventor/elements/SoInt32Element.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoMaterialBindingElement
//
//  Element that stores the current material binding.
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoMaterialBindingElement : public SoInt32Element {

    SO_ELEMENT_HEADER(SoMaterialBindingElement);

  public:
    // The (seemingly random) choice of values is for compatibility
    // with Inventor 2.0 binary format files:
    enum Binding {
	OVERALL = 2,		// Whole object has same material
	PER_PART = 3,		// One material for each part of object
	PER_PART_INDEXED = 4,	// One material for each part, indexed
	PER_FACE = 5,		// One material for each face of object
	PER_FACE_INDEXED = 6,	// One material for each face, indexed
	PER_VERTEX = 7,		// One material for each vertex
	PER_VERTEX_INDEXED = 8	// One material for each vertex, indexed

#ifndef IV_STRICT
        // Obsolete bindings:
	,			// Comma to continue list
	DEFAULT = OVERALL,
	NONE = OVERALL
#endif

    };

    // Initializes element
    virtual void	init(SoState *state);

    // Sets the current material binding in the state
    static void		set(SoState *state, Binding binding)
	{ SoInt32Element::set(classStackIndex, state, (int32_t)binding); }

#ifndef IV_STRICT
    static void         set(SoState *state, SoNode *, Binding binding)
        { set(state, binding); }
#endif

    // Returns current material binding from the state
    static Binding	get(SoState *state)
	{ return (Binding)SoInt32Element::get(classStackIndex, state); }

    // Returns the default material binding
    static Binding	getDefault()		{ return OVERALL; }

    // Prints element (for debugging)
    virtual void	print(FILE *fp) const;

  SoINTERNAL public:
    // Initializes the SoMaterialBindingElement class
    static void		initClass();

  protected:
    virtual ~SoMaterialBindingElement();
};

#endif /* _SO_MATERIAL_BINDING_ELEMENT */
