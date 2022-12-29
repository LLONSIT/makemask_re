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
 |   $Revision $
 |
 |   Description:
 |	This file defines the SoDrawStyle node class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_DRAW_STYLE_
#define  _SO_DRAW_STYLE_

#include <Inventor/SbString.h>
#include <Inventor/elements/SoDrawStyleElement.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFUShort.h>
#include <Inventor/nodes/SoSubNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoDrawStyle
//
//  Draw style node.
//
//////////////////////////////////////////////////////////////////////////////

class SoGLRenderAction;
class SoCallbackAction;

class SoDrawStyle : public SoNode {

    SO_NODE_HEADER(SoDrawStyle);

  public:
    enum Style {
	FILLED	  = SoDrawStyleElement::FILLED,		// Filled regions
	LINES	  = SoDrawStyleElement::LINES,		// Outlined regions
	POINTS	  = SoDrawStyleElement::POINTS,		// Points
	INVISIBLE = SoDrawStyleElement::INVISIBLE	// Nothing!
    };

    // Fields
    SoSFEnum		style;		// Drawing style
    SoSFFloat		pointSize;	// Radius of points (for POINTS style)
    SoSFFloat		lineWidth;	// Width of lines (for LINES style)
    SoSFUShort		linePattern;	// Line pattern (for LINES style)

    // Constructor
    SoDrawStyle();

  SoEXTENDER public:
    virtual void	doAction(SoAction *action);
    virtual void	GLRender(SoGLRenderAction *action);
    virtual void	callback(SoCallbackAction *action);

  SoINTERNAL public:
    static void		initClass();

  protected:
    virtual ~SoDrawStyle();
};

#endif /* _SO_DRAW_STYLE_ */
