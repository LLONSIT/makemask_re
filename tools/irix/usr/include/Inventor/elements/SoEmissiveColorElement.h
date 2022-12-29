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
 |	This file defines the SoEmissiveColorElement class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */
#ifdef  IV_STRICT
#error SoEmissiveColorElement is obsolete.  See SoLazyElement instead.
#endif /*IV_STRICT*/
#ifndef  _SO_EMISSIVE_COLOR_ELEMENT
#define  _SO_EMISSIVE_COLOR_ELEMENT


#include <Inventor/SbColor.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/elements/SoLazyElement.h>
#include <Inventor/errors/SoDebugError.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoEmissiveColorElement
//
//  This class is being superceded by the SoLazyElement class.
//  All methods are converted inline to SoLazyElement methods for
//  compatibility.  This only uses the first emissive color, not an 
//  array of them.
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoEmissiveColorElement {


  public:

    // Sets the current emissive color(s)
    static void		set(SoState *state, SoNode *,
			    int32_t numColors, const SbColor *colors)
	{
	    SoLazyElement::setEmissive(state,colors);
#ifdef DEBUG
	    if(numColors>1){
		SoDebugError::post("SoEmissiveColorElement::set",
			"multiple emissive colors not supported");
	    }
#endif /*DEBUG*/
	}


    // Returns the top (current) instance of the element in the state
    static const SoEmissiveColorElement * getInstance(SoState *state)
	{
	    SoEmissiveColorElement* ece = new SoEmissiveColorElement;
	    ece->saveState = state;
	    return(ece);
	}


    // Returns the number of emissive colors in any instance
    int32_t		getNum() const		{ return 1; }

    // Returns the current emissive color 
    const SbColor &	get(int index) const
    {
#ifdef DEBUG
	    if(index >1)
	    	SoDebugError::post("SoEmissiveColorElement::get",
				"multiple emissive colors not supported");
#endif /*DEBUG*/
	return(SoLazyElement::getEmissive(saveState));
    }

    // Returns the default emissive color
    static SbColor getDefault()		
    { return SoLazyElement::getDefaultEmissive(); }
    
    private:
    SoState* saveState;
};

#endif /* _SO_EMISSIVE_COLOR_ELEMENT */
