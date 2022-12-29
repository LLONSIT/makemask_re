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
 |	This file defines the SoPickStyle node class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_PICK_STYLE_
#define  _SO_PICK_STYLE_

#include <Inventor/SbString.h>
#include <Inventor/elements/SoPickStyleElement.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/nodes/SoSubNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoPickStyle
//
//  Pick style node. Allows picking in subgraphs to be defined in one
//  of the following ways:
//
//	SHAPE (default): points on the surfaces of shapes may be picked
//	BOUNDING_BOX:	 points on the surfaces of bounding boxes of
//			 shapes may be picked
//	UNPICKABLE:	 objects in the subgraph are transparent to picks
//
//////////////////////////////////////////////////////////////////////////////

class SoPickStyle : public SoNode {

    SO_NODE_HEADER(SoPickStyle);

  public:
    enum Style {			// Picking style:
	SHAPE		= SoPickStyleElement::SHAPE,
	BOUNDING_BOX	= SoPickStyleElement::BOUNDING_BOX,
	UNPICKABLE	= SoPickStyleElement::UNPICKABLE
    };

    // Fields
    SoSFEnum		style;		// Picking style

    // Constructor
    SoPickStyle();

  SoEXTENDER public:
    virtual void	doAction(SoAction *action);
    virtual void	callback(SoCallbackAction *action);
    virtual void	pick(SoPickAction *action);

  SoINTERNAL public:
    static void		initClass();

  protected:
    virtual ~SoPickStyle();
};

#endif /* _SO_PICK_STYLE_ */
