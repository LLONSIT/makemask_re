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
 |	This file defines the SoLightModelElement class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */
#ifndef  IV_STRICT
#ifndef  _SO_LIGHT_MODEL_ELEMENT
#define  _SO_LIGHT_MODEL_ELEMENT

#include <Inventor/elements/SoGLLazyElement.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoLightModelElement
//
//  Element that stores the current lighting model.
//  This element has been superceded by SoLazyElement.  Methods included for
//  compatibility.
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoLightModelElement  {

  public:
    // These are the available lighting models:
    enum Model {
	BASE_COLOR,	// No lighting; just use base color
	PHONG		// Phong lighting
    };

    // Sets the current lighting model in the state
    static void		set(SoState *state, Model model)
	{SoLazyElement::setLightModel(state, model);}


    static void         set(SoState *state, SoNode *, Model model)
        { set(state, model); }


    // Returns current lighting model from the state
    static Model	get(SoState *state)
	{ return (Model)(SoLazyElement::getLightModel(state)); }

    // Returns the default lighting model
    static Model	getDefault()		
    { return (Model)SoLazyElement::getDefaultLightModel(); }

 
};

#endif /* _SO_LIGHT_MODEL_ELEMENT */
#endif /*IV_STRICT*/
