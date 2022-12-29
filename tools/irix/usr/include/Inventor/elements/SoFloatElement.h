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
 |	This file defines the abstract SoEXTENDER SoFloatElement class.
 |      This is a base class used to make the library smaller by
 |      sharing code.
 |
 |   Classes:
 |	SoFloatElement
 |
 |   Author(s)		: Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_FLOAT_ELEMENT
#define  _SO_FLOAT_ELEMENT


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoFloatElement
//
//  Subclasses store a single float, int, or enum value.  This class
//  defines generic matches() and copy() methods.
//
//////////////////////////////////////////////////////////////////////////////

#include <Inventor/elements/SoSubElement.h>

SoEXTENDER class SoFloatElement : public SoElement {

    SO_ELEMENT_ABSTRACT_HEADER(SoFloatElement);

  public:
    // Comparison based on value of floats
    virtual SbBool	matches(const SoElement *elt) const;

    // Copy method, takes care copying the data.
    virtual SoElement 	*copyMatchInfo() const;
    
    // Prints element (for debugging)
    virtual void	print(FILE *fp) const;

  SoINTERNAL public:
    // Initializes the SoFloatElement class
    static void		initClass();

  protected:
    // Set value.  Derived classes have static inline methods
    // that pass in the stack index and cast their type into a float.
    // This just gets an appropriate instance and calls the virtual
    // set.
    static void		set(int stackIndex, SoState *state, float value);

    // Virtual set that subclasses can override to implement
    // side-effect behaviors.
    virtual void	setElt(float value);

    // Get value.  Derived classes have static inline methods to pass
    // in the stackIndex and cast the returned value to the right type.

    static float	get(int stackIndex, SoState *state)
        {return ((const SoFloatElement *)
	    getConstElement(state, stackIndex))->data;}
    
    // Storage for data.
    float data;

    // Destructor
    virtual ~SoFloatElement();
};

#endif /* _SO_FLOAT_ELEMENT */
