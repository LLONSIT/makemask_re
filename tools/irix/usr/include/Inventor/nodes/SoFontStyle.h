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
 |   $Revision: 1.6 $
 |
 |   Description:
 |	Defines the SoFontStyle class
 |
 |   Author(s): Chris Marrin
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_FONTSTYLE_
#define  _SO_FONTSTYLE_

#include <Inventor/fields/SoSFBitMask.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/nodes/SoFont.h>
#include <Inventor/actions/SoCallbackAction.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoFontStyle
//
//////////////////////////////////////////////////////////////////////////////

class SoFontStyle : public SoFont {

    SO_NODE_HEADER(SoFontStyle);

  public:
    // Constructor
    SoFontStyle();

    enum Family {
	SERIF,		    // Use Serif style (such as Times-Roman)
	SANS, 		    // Use Sans Serif style (such as Helvetica)
	TYPEWRITER	    // Use fixed pitch style (such as Courier)
    };

    enum Style {
	NONE = 0,	    // No modification to Family
	BOLD = 0x1, 	    // Embolden Family
	ITALIC = 0x2	    // Italicize or Slant Family
    };

    // Fields
    SoSFEnum	family;
    SoSFBitMask	style;
    
    // Return the font name used by this node based on the settings of family and style
    SbString		getFontName();

  SoEXTENDER public:
    virtual void        doAction(SoAction *action);
    virtual void        callback(SoCallbackAction *action);
    virtual void        GLRender(SoGLRenderAction *action);
    virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
    virtual void        pick(SoPickAction *action);

  SoINTERNAL public:
    static void		initClass();

  protected:
    virtual ~SoFontStyle();
    
  private:
    static char *fontList[][4];
};

#endif /* _SO_FONTSTYLE_ */
