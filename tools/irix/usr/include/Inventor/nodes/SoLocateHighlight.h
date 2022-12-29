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
 |   $Revision: 1.7 $
 |
 |   Description:
 |	This file defines the SoLocateHighlight node class.
 |
 |   It has two fields, 
 |      color and style
 |
 |   When the cursor is over the stuff below this node,
 |   it will be redrawn (to the front buffer) with the color 
 |   emissive and/or diffuse in the state and the override flag ON.
 |
 |   Author(s)	: Alain Dumesny, Paul Isaacs
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_LOCATE_HIGHLIGHT_
#define  _SO_LOCATE_HIGHLIGHT_

#include <GL/gl.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/nodes/SoSeparator.h>

class SoAction;
class SoHandleEventAction;
class SoGLRenderAction;
class SoFullPath;
class SoColorPacker;


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoLocateHighlight
//
//////////////////////////////////////////////////////////////////////////////

class SoLocateHighlight : public SoSeparator {

    SO_NODE_HEADER(SoLocateHighlight);

  public:

    enum Styles {	    // Possible values for draw style
	EMISSIVE,	    // changes emissive color only (default)
	EMISSIVE_DIFFUSE    // changes emissive and diffuse colors
    };

    enum Modes {	    // Possible values for the mode
	AUTO, 		    // highlight when mouse is over (default)
	ON,		    // always highlight
	OFF		    // never highlight
    };

    // Fields
    SoSFColor	color;	// highlighting color - default [.3, .3, .3]
    SoSFEnum	style;	// EMISSIVE/EMISSIVE_DIFFUSE
    SoSFEnum	mode;	// ON/OFF/AUTO

    // Constructor
    SoLocateHighlight();

  SoEXTENDER public:
    // Override handleEvent to look for mouse motion, to do a
    // pick and highlight if mouse is over us. The GLRender methods
    // are redefined to draw highlighted if needed.
    virtual void	handleEvent( SoHandleEventAction *action );
    virtual void	GLRenderBelowPath(SoGLRenderAction *action);
    virtual void	GLRenderInPath(SoGLRenderAction *action);

  SoINTERNAL public:
    static void		initClass();	// initialize the class

    // This will de-highlight the currently highlighted node if any.
    // this should be called when the cursor leaves a window or a mode
    // changes happen which would prevent a highlighted node from receiving
    // more mouse motion events. The GL render action used to render into
    // that window needs to be passed to correctly un-highlight.
    static void		turnOffCurrentHighlight(SoGLRenderAction *action);

  protected:
    virtual ~SoLocateHighlight();
    
    // This is called when this nodes needs to highlight or de-highlight. It
    // can be used by subclasses to be told when the status change.
    virtual void	redrawHighlighted(SoAction *act, SbBool flag);
    
  private:
    // highlighting stuff
    SbBool		highlightingPass;
    static SoFullPath   *currentHighlightPath;
    SbBool		isHighlighted(SoAction *action);
    SbBool		preRender(SoGLRenderAction *act, GLint &oldDepthFunc);
    SoColorPacker	*colorPacker;
};


#endif /* _SO_LOCATE_HIGHLIGHT_ */
