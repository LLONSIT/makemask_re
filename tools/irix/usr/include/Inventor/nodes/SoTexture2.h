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
 |	This file defines the SoTexture node class.
 |
 |   Author(s)		: John Rohlf, Thad Beier, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_TEXTURE_2_
#define  _SO_TEXTURE_2_

#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFImage.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/nodes/SoSubNode.h>

#include <GL/gl.h>

class SoSensor;
class SoFieldSensor;
class SoGLDisplayList;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTexture
//
//  Texture node.
//
//////////////////////////////////////////////////////////////////////////////

class SoTexture2 : public SoNode {

    SO_NODE_HEADER(SoTexture2);

  public:
    enum Model {			// Texture model
	MODULATE		= GL_MODULATE,
	DECAL			= GL_DECAL,
	BLEND			= GL_BLEND
    };

    enum Wrap {				// Texture wrap type
	REPEAT			= GL_REPEAT,
	CLAMP			= GL_CLAMP
    };

    // Fields.
    SoSFString		filename;	// file to read texture from
    SoSFImage		image;		// The texture
    SoSFEnum		wrapS;
    SoSFEnum		wrapT;
    SoSFEnum		model;
    SoSFColor		blendColor;

    // Constructor
    SoTexture2();
    
  SoEXTENDER public:
    virtual void	doAction(SoAction *action);
    virtual void	GLRender(SoGLRenderAction *action);
    virtual void	callback(SoCallbackAction *action);

  SoINTERNAL public:
    static void		initClass();

    // Read libimage-format file
    static SbBool   readImage(const SbString& fname, int &w, int &h, int &nc,
				unsigned char *&bytes);

  protected:
    // Reads stuff into instance. Returns FALSE on error.
    virtual SbBool	readInstance(SoInput *in, unsigned short flags);

    virtual ~SoTexture2();

    int		    getReadStatus()		{ return readStatus; }
    void	    setReadStatus(int s)	{ readStatus = s; }

  private:
    // These keep the image and filename fields in sync.
    SoFieldSensor *	imageSensor;
    static void		imageChangedCB(void *, SoSensor *);
    SoFieldSensor *	filenameSensor;
    static void		filenameChangedCB(void *, SoSensor *);
    
    int			readStatus;
    

    // Display list info for this texture:
    SoGLDisplayList *renderList;
    float	renderListQuality;
};

#endif /* _SO_TEXTURE_2_ */
