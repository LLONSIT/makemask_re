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
 |   $Revision: 2.5 $
 |
 |   Description:
 |	This file defines the SoGLTextureImageElement class.
 |
 |   Author(s)		: Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_GL_TEXTURE_IMAGE_ELEMENT
#define  _SO_GL_TEXTURE_IMAGE_ELEMENT

class SoGLDisplayList;

#include <Inventor/elements/SoTextureImageElement.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoGLTextureImageElement
//
//  Element that stores the current texture image in GL. Overrides the
//  virtual methods on SoTextureImageElement to send the image
//  to GL when necessary.
//
//  Note that this class relies on SoTextureImageElement to store the
//  image in the instance.
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoGLTextureImageElement : public SoTextureImageElement {

    SO_ELEMENT_HEADER(SoGLTextureImageElement);
    
  public:
    // Initializes element
    virtual void	init(SoState *state);

    // Sets the current image, wrap modes and model.
    // This will try to build or use a GL
    // display list, if it can; the display list ID is returned (-1 if
    // there is none), and should be saved and passed in the next time
    // the element is set.  The node calling this routine is
    // responsible for calling glDeleteLists to free up the display
    // list at the right time.
    static SoGLDisplayList *
	set(SoState *state, SoNode *node,
	    const SbVec2s &s, int nc,
	    const unsigned char *bytes,
	    float texQuality,
	    int wrapS, int wrapT, int model, 
	    const SbColor &blendColor, SoGLDisplayList *list);

    // Override pop() method so side effects can occur in GL
    virtual void	pop(SoState *state, const SoElement *prevTopElement);

  SoINTERNAL public:
    // Initializes the SoGLTextureImageElement class
    static void		initClass();

  protected:
    // Catch setElt; if this setElt is called, it is an error...
    virtual void	setElt(const SbVec2s &s, int nc,
			       const unsigned char *bytes,
			       int wrapS, int wrapT, int model,
			       const SbColor &blendColor);

    virtual ~SoGLTextureImageElement();

  private:
    // Send texture environment information
    void		sendTexEnv(SoState *state);

    // Sends image in element to GL. The state is needed to determine
    // whether or not OpenGL extensions are available.  This will
    // build or use a texture object or display list, if possible.
    void		sendTex(SoState *state);

    SoGLDisplayList	*list;
    float		quality;
};

#endif /* _SO_GL_TEXTURE_IMAGE_ELEMENT */
