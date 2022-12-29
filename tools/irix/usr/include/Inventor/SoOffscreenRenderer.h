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
 |	This file contains the definition of the SoOffscreenRenderer class.
 |
 |   Classes:
 |	SoOffscreenRenderer
 |
 |   Author(s)		: Dave Immel
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_OFFSCREEN_RENDERER_
#define  _SO_OFFSCREEN_RENDERER_

#include <stdio.h>
#include <GL/glx.h>
#include <Inventor/SbColor.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/SbLinear.h>
#include <X11/Xlib.h>

class SoNode;
class SoPath;
class SoGLRenderAction;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoOffscreenRenderer
//
//  This file contains the definition of the SoOffscreenRenderer class.
//  This class is used for rendering a scene graph to an offscreen memory
//  buffer which can be used for printing or generating textures.
//
//  The implementation of this class uses the X Pixmap for rendering.
//
//////////////////////////////////////////////////////////////////////////////

class SoOffscreenRenderer {
 public:

    // Constructor
    SoOffscreenRenderer( const SbViewportRegion &viewportRegion );
    SoOffscreenRenderer( SoGLRenderAction *ra );

    // Destructor
    ~SoOffscreenRenderer();

    enum Components {
        LUMINANCE = 1,
        LUMINANCE_TRANSPARENCY = 2,
        RGB = 3,                      // The default
        RGB_TRANSPARENCY = 4
    };

    static float	getScreenPixelsPerInch();

    // Set/get the components to be rendered
    void		setComponents( Components components )
				{comps = components;}
    Components		getComponents() const
				{return comps;}

    // Set/get the viewport region
    void		setViewportRegion( const SbViewportRegion &region );
    const SbViewportRegion  &getViewportRegion() const;

    // Get the maximum supported resolution of the viewport.
    static SbVec2s	getMaximumResolution();

    // Set/get the background color
    void		setBackgroundColor( const SbColor &c )
				{backgroundColor = c;}
    const SbColor & getBackgroundColor() const
				{return backgroundColor;}

    // Set and get the render action to use
    void                      setGLRenderAction(SoGLRenderAction *ra);
    SoGLRenderAction *        getGLRenderAction() const;

    // Render the given scene into a buffer
    SbBool		render( SoNode *scene );
    SbBool		render( SoPath *scene );

    // Return the buffer containing the rendering
    unsigned char *     getBuffer() const;

    // Write the buffer as a .rgb file into the given FILE
    SbBool		writeToRGB( FILE *fp ) const;

    // Write the buffer into encapsulated PostScript.  If a print size is
    // not given, adjust the size of the print so it is WYSIWYG with respect
    // to the viewport region on the current device.
    SbBool		writeToPostScript( FILE *fp ) const;
    SbBool		writeToPostScript( FILE *fp,
                                const SbVec2f &printSize ) const;

  private:
    unsigned char *	pixelBuffer;
    Components          comps;
    SbColor		backgroundColor;
    SoGLRenderAction	*userAction, *offAction;
    SbViewportRegion    renderedViewport;

    // These are used for rendering to the offscreen pixmap
    Display 		*display;
    XVisualInfo  	*visual;
    GLXContext 		context;
    GLXPixmap 		pixmap;
    Pixmap 		pmap;

    // Setup the offscreen pixmap
    SbBool		setupPixmap();

    // Initialize an offscreen pixmap
    static SbBool 	initPixmap( Display * &dpy, XVisualInfo * &vi,
                                GLXContext &cx, const SbVec2s &sz,
                                GLXPixmap &glxPmap, Pixmap &xpmap );

    // Read pixels back from the Pixmap
    void		readPixels();

    // Set the graphics context
    SbBool		setContext() const;

    // Return the format used in the rendering
    void		getFormat( GLenum &format ) const;

    static void		putHex( FILE *fp, char val, int &hexPos );
};

#endif /* _SO_OFFSCREEN_RENDERER_ */

