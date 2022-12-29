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
 |	This file defines the SoGLColorIndexElement class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */
#ifdef  IV_STRICT
#error SoGLColorIndexElement is obsolete. See So[GL]LazyElement.h instead.
#endif /*IV_STRICT*/
#ifndef  _SO_GL_COLOR_INDEX_ELEMENT
#define  _SO_GL_COLOR_INDEX_ELEMENT

#include <Inventor/SbColor.h>
#include <Inventor/elements/SoLazyElement.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoGLColorIndexElement
//
//  This class is being superceded by the SoLazyElement class.
//  All methods are converted inline to SoLazyElement methods for
//  compatibility.   
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoGLColorIndexElement {


  public:

    // Sets the current indexed color(s)
    static void		set(SoState *state, SoNode * node,
			    int32_t numIndices, const int32_t *indices)
	{
	    SoLazyElement::setColorIndices(state, node, numIndices, indices);
	}


    // Returns the top (current) instance of the element in the state
    static const SoGLColorIndexElement * getInstance(SoState *state)
	{
	    SoGLColorIndexElement* cie = new SoGLColorIndexElement;
	    cie->saveState = state;
	    return(cie);
	}


    // Returns the number of color indices in current instance
    int32_t		getNum() const		
    {
	return(SoLazyElement::getInstance(saveState)->getNumColorIndices());
    }
	
    // Returns a current color index 
    int32_t	get(int index) const
    {
	return(SoLazyElement::getColorIndex(saveState, index));
    }
	
    // Returns the default index
    static int32_t		getDefault()		
    { return SoLazyElement::getDefaultColorIndex(); }

    private:
    SoState* saveState;
};
#endif /* _SO_GL_COLOR_INDEX_ELEMENT */
