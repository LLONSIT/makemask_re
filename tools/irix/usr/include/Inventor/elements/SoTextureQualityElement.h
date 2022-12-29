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
 |   $Revision: 1.3 $
 |
 |   Description:
 |	This file defines the SoTextureQualityElement and
 |      SoTextureOverrideElement classes.
 |
 |   Author(s)		: Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_TEXTURE_QUALITY_ELEMENT
#define  _SO_TEXTURE_QUALITY_ELEMENT

#include <Inventor/elements/SoFloatElement.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTextureQualityElement
//
//  Element that stores the current texture quality
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoTextureQualityElement : public SoFloatElement {

    SO_ELEMENT_HEADER(SoTextureQualityElement);

  public:
    // Initializes element
    virtual void	init(SoState *state);

    // Sets the current TextureQuality in the state
    static void		set(SoState *state, float qual)
	{ SoFloatElement::set(classStackIndex, state, qual); }

    // Returns current TextureQuality from the state
    static float	get(SoState *state)
	{ return SoFloatElement::get(classStackIndex, state); }

    // Returns the default TextureQuality
    static float	getDefault()			{ return 0.5; }

  SoINTERNAL public:
    // Initializes the SoTextureQualityElement class
    static void		initClass();

  protected:
    virtual ~SoTextureQualityElement();
};

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTextureOverrideElement
//
//  Element that stores a flag for each type of element which can be
//  overridden.  Nodes implement override by setting the appropriate
//  bit if their override flag is on, and ignoring overridden elements
//  if the corresponding bit in the state's SoTextureOverrideElement is set.
//  
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoTextureOverrideElement : public SoElement {

    SO_ELEMENT_HEADER(SoTextureOverrideElement);

    enum {
	TEXTURE_QUALITY	= 0x1,
	TEXTURE_IMAGE	= 0x2
    };

  public:
    // Initializes element
    virtual void	init(SoState *state);

    // Comparison based on value of int32_ts
    virtual SbBool	matches(const SoElement *elt) const;

    // Overrides push() method to copy values from next instance in
    // the stack, and set up cache dependencies correctly
    virtual void	push(SoState *state);

    //
    // "get" methods for each element which can be overridden.
    //

    // Returns TRUE iff SoTextureQualityElement is overridden.
    static SbBool	getQualityOverride(SoState *state);

    // Returns TRUE iff SoTextureImageElement is overridden.
    static SbBool	getImageOverride(SoState *state);

    //
    // "set" methods for each element which can be overridden.
    //

    // set override flag for SoTextureQualityElement.
    static void		setQualityOverride(SoState *state,
					   SbBool override);
    
    // set override flag for SoTextureImageElement.
    static void		setImageOverride(SoState *state,
					 SbBool override);

    // Prints element (for debugging)
    virtual void	print(FILE *fp) const;

  SoINTERNAL public:
    // Initializes the SoTextureOverrideElement class
    static void		initClass();

    // Copy method, copies flags
    virtual SoElement 	*copyMatchInfo() const;
    
  private:
    // Used by ::print method
    void pFlag(FILE *, const char *, int) const;

    uint32_t flags;
};

#endif /* _SO_TEXTURE_QUALITY_ELEMENT */
