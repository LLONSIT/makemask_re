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
 |   $Revision: 2.9 $
 |
 |   Description:
 |	This file defines the SoShininessElement class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */
#ifdef IV_STRICT
#error SoShininessElement is obsolete. See SoLazyElement.h instead.
#endif /*IV_STRICT*/
#ifndef  _SO_SHININESS_ELEMENT
#define  _SO_SHININESS_ELEMENT


#include <Inventor/elements/SoLazyElement.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/errors/SoDebugError.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoShininessElement
//
//  Mostly superceded by SoLazyElement.
//  get() and set() methods retained for compatibility
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoShininessElement {


  public:

    // Sets the current shininess(es)
    static void		set(SoState *state, SoNode *,
			    int32_t numShininesses, const float *shininesses)
	{
	    SoLazyElement::setShininess(state, *shininesses);
#ifdef DEBUG
	    if(numShininesses>1){
		SoDebugError::post("SoShininessElement::set",
			"multiple shininess not supported");
	    }
#endif /*DEBUG*/
	}

    // Returns the top (current) instance of the element in the state
    static const SoShininessElement * getInstance(SoState *state)
	{
	    SoShininessElement* se = new SoShininessElement;
	    se->saveState = state;
	    return(se);
	}

    // Returns the number of shininess values in an instance
    int32_t		getNum() const		{ return 1; }

    // Returns the indexed shininess from an element
    float		get(int index) const
    	{
#ifdef DEBUG
	if(index >1)
	    	SoDebugError::post("SoShininessElement::get",
				"multiple shininess values not supported");
#endif /*DEBUG*/
	return(SoLazyElement::getShininess(saveState));
    	}


    // Returns the default shininess
    static float	getDefault()		
    { return SoLazyElement::getDefaultShininess(); }


  private:
    SoState * saveState;
};

#endif /* _SO_SHININESS_ELEMENT */

