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
 |   $Revision: 1.2 $
 |
 |   Description:
 |	This file defines the abstract SoEXTENDER SoInt32Element class.
 |      This is a base class used to make the library smaller by
 |      sharing code.
 |
 |   Classes:
 |	SoInt32Element
 |
 |   Author(s)		: Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_INT32_ELEMENT
#define  _SO_INT32_ELEMENT

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoInt32Element
//
//  Subclasses store a single int32_t, int, or enum value.  This class
//  defines generic matches() and copy() methods.
//
//////////////////////////////////////////////////////////////////////////////

#include <Inventor/elements/SoSubElement.h>

SoEXTENDER class SoInt32Element : public SoElement {

    SO_ELEMENT_ABSTRACT_HEADER(SoInt32Element);

  public:
    // Comparison based on value of int32_ts
    virtual SbBool	matches(const SoElement *elt) const;

  SoINTERNAL public:
    // Initializes the SoInt32Element class
    static void		initClass();

    // Copy method, takes care copying the data.
    virtual SoElement 	*copyMatchInfo() const;
    
    // Set value.  Derived classes have static inline methods
    // that pass in the stack index and cast their type into a int32_t.
    // This just gets an appropriate instance and calls the virtual
    // set.
    static void		set(int stackIndex, SoState *state, int32_t value);

#ifndef IV_STRICT
    static void         set(int stackIndex, 
				SoState *state, SoNode *, int32_t value)
        { set(stackIndex, state, value); }
    static void         set(int stackIndex, 
				SoState *state, SoNode *, 
			  	long value)	// System long
        { set(stackIndex, state, (int32_t) value); }
#endif

    // Virtual set that subclasses can override to implement
    // side-effect behaviors.
    virtual void	setElt(int32_t value);

    // Get value.  Derived classes have static inline methods to pass
    // in the stackIndex and cast the returned value to the right type.
    static int32_t		get(int stackIndex, SoState *state)
    	{return((const SoInt32Element *)
	    getConstElement(state, stackIndex))->data;}

    // Prints element (for debugging)
    virtual void	print(FILE *fp) const;

  protected:
    // Storage for data.
    int32_t data;

    virtual ~SoInt32Element();
};

#endif /* _SO_INT32_ELEMENT */
