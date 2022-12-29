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
 |   $Revision: 2.3 $
 |
 |   Description:
 |	This file defines the SoText2 node class.
 |
 |   Author(s)		: Thad Beier
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_TEXT_2_
#define  _SO_TEXT_2_

#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/nodes/SoShape.h>

class SoBitmapFontCache;  // Internal class

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoText2
//
//  2D, screen-aligned text.  The origin of the text is always 0,0,0
//  in object space, but the text is always the same size (based on
//  the fontSize from the SoFont node) and is always aligned with the
//  screen.
//
//////////////////////////////////////////////////////////////////////////////

class SoText2 : public SoShape {

    SO_NODE_HEADER(SoText2);

  public:
    enum Justification {		// Justification types
	LEFT	= 0x01,
	RIGHT	= 0x02,
	CENTER	= 0x03
    };

    // Fields
    SoMFString		string;		// the strings to display
    SoSFFloat		spacing;	// interval between strings
    SoSFEnum		justification;

    // Constructor
    SoText2();

  SoEXTENDER public:
    virtual void	GLRender(SoGLRenderAction *action);
    virtual void	rayPick(SoRayPickAction *action);

  SoINTERNAL public:
    static void		initClass();

  protected:
    // This method is a no-op for SoText2, since there are no
    // primitives it can generate
    virtual void	generatePrimitives(SoAction *action);

    // Computes bounding box of text
    virtual void	computeBBox(SoAction *action, SbBox3f &box,
				    SbVec3f &center);

    virtual ~SoText2();

  private:
    // Based on justification and line spacing, this returns the
    // offset (in pixels) for one of the lines of text.
    SbVec3f		getPixelStringOffset(int whichLine);

    // Internal class that allows Text2 nodes to share font
    // information, GL display lists, etc.
    SoBitmapFontCache	*myFont;
};

#endif /* _SO_TEXT_2_ */
