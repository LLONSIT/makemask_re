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
 |   $Revision: 2.2 $
 |
 |   Description:
 |	This file defines the SoTextureImageElement class.
 |
 |   Author(s)		: Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_TEXTURE_IMAGE_ELEMENT
#define  _SO_TEXTURE_IMAGE_ELEMENT

#include <Inventor/SbColor.h>
#include <Inventor/elements/SoReplacedElement.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTextureImageElement
//
//  Element storing the current texture image.
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoTextureImageElement : public SoReplacedElement {

    SO_ELEMENT_HEADER(SoTextureImageElement);

  public:
    // Initializes element.
    virtual void	init(SoState *state);

    // sets the current image, wrap, and model:
    static void		set(SoState *state, SoNode *node,
			    const SbVec2s &size, int numComponents,
			    const unsigned char *bytes,
			    int wrapS, int wrapT, int model,
			    const SbColor &blendColor);

    static const unsigned char *get(SoState *state, SbVec2s &size,
				    int &numComponents, int &wrapS,
				    int &wrapT, int &model, 
				    SbColor &blendColor);

    // Returns TRUE if the texture contains transparency info
    static SbBool	containsTransparency(SoState *state);

    // Returns the default texture image
    static const unsigned char *getDefault(SbVec2s &s, int &nc);

    // Print info about image for debugging
    virtual void	print(FILE *fp) const;

  SoINTERNAL public:
    // Initializes the class
    static void		initClass();

  protected:
    virtual void	setElt(const SbVec2s &s, int nc,
			       const unsigned char *bytes,
			       int wrapS, int wrapT, int model,
			       const SbColor &blendColor);

    SbVec2s	size;
    int		numComponents;
    const unsigned char *bytes;
    int		wrapS, wrapT, model;
    SbColor	blendColor;

    virtual ~SoTextureImageElement();
};

#endif /* _SO_TEXTURE_IMAGE_ELEMENT */
