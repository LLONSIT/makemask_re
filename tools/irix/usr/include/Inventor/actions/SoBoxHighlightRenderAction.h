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
 |
 |   $Revision: 2.1 $
 |
 |   Description:
 |	This is the SoBoxHighlightRenderAction class, used to highlight
 |   the selection by drawing a wireframe box around the selected shapes.
 |
 |   Classes	: SoBoxHighlightRenderAction
 |
 |   Author(s)	: David Mott
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */


#ifndef _SO_BOX_HIGHLIGHT_RENDER_ACTION_
#define _SO_BOX_HIGHLIGHT_RENDER_ACTION_

#include <Inventor/actions/SoGLRenderAction.h>

class SbColor;
class SoSeparator;
class SoLightModel;
class SoBaseColor;
class SoDrawStyle;
class SoTexture2;
class SoTranslation;
class SoMatrixTransform;
class SoCube;

//////////////////////////////////////////////////////////////////////////////
//
// Box highlight - a subclass of SoGLRenderAction which renders the
// scene graph, then renders wireframe boxes surrounding each selected object.
//
//////////////////////////////////////////////////////////////////////////////

class SoBoxHighlightRenderAction : public SoGLRenderAction {
      SO_ACTION_HEADER(SoBoxHighlightRenderAction);
 public:
    // Constructor which takes no parameters. This sets up a dummy
    // viewport region. If passed to a render area, the render area
    // will correctly set the region. Otherwise, setViewportRegion()
    // should be called before applying this action.
    SoBoxHighlightRenderAction();
    
    // Constructor which takes the normal SoGLRenderAction parameters.
    SoBoxHighlightRenderAction(const SbViewportRegion &viewportRegion);
		  
    
    virtual ~SoBoxHighlightRenderAction();
    
    // Applies action to the graph rooted by a node. 
    // This renders the scene, then renders highlights for selected objects.
    virtual void    apply(SoNode *node);

    // Applies action to the graph defined by a path or path list.
    // These simply invoke the parent class apply() methods.
    // These do NOT highlight the path, whether selected or not.
    virtual void    apply(SoPath *path);
    virtual void    apply(const SoPathList &pathList,
			      SbBool obeysRules = FALSE);
    
    // Simple switch to turn highlighting on (TRUE) or off (FALSE)
    // App is responsible for redrawing after this state changes.
    void	    setVisible(SbBool b) { hlVisible = b; }
    SbBool	    isVisible() const { return hlVisible; }

    // Set the appearance of the highlight.
    // Application is responsible for redrawing the scene
    // after making changes here.
    void	    setColor( const SbColor &c );
    const SbColor & getColor();
    void            setLinePattern( unsigned short pattern );
    unsigned short  getLinePattern();
    void            setLineWidth( float width );
    float           getLineWidth();
   
 SoINTERNAL public: 
    static void initClass();

  protected:
    void updateBbox(SoPath *p);
    
    // Nodes which comprise the local highlight graph
    SoSeparator	    *localRoot;
    SoLightModel    *lightModel;
    SoBaseColor	    *baseColor;
    SoDrawStyle	    *drawStyle;
    SoTexture2	    *texture;
    SoTranslation   *xlate;
    SoMatrixTransform *xform;
    SoCube	    *cube;
    
    SbBool	    hlVisible;
    
    // Cached path to selection so we don't search every time
    SoPath	    *selPath;
    
  private:
    void	    constructorCommon();
};

#endif /* _SO_BOX_HIGHLIGHT_RENDER_ACTION_ */

