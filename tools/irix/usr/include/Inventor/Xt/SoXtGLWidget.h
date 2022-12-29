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
 |   $Revision: 2.6 $
 |
 |   Description:
 |	This is a c++ wrapper for the Glx mixed mode widget.
 |
 |   Author(s): Alain Dumesny, David Mott
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef _SO_XT_GL_WIDGET_H_
#define _SO_XT_GL_WIDGET_H_

#include <X11/Intrinsic.h>
#include <GL/glx.h>
#include <Inventor/Xt/SoXtComponent.h>

/*
 * Defines used when specifying the glModes flag to the constructor.
 * (used instead of the glx.h defines which do overlap)
 */
#define SO_GLX_RGB	(1<<0)
#define SO_GLX_DOUBLE	(1<<1)
#define SO_GLX_ZBUFFER	(1<<2)
#define SO_GLX_OVERLAY	(1<<3)
#define SO_GLX_STEREO	(1<<4)


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoXtGLWidget
//
//
//////////////////////////////////////////////////////////////////////////////

class SoXtGLWidget : public SoXtComponent {
  public:
    
    //
    // Get the current normal and overlay GLX windows, which are needed
    // as arguments to glXMakeCurrent() when doing drawing in the normal 
    // or overlay planes.
    //
    // NOTE: These should NOT be cached by users because these will 
    // change dynamically when the visual is changed (like when
    // setDoubleBuffer() is called).
    //
    Window  	getNormalWindow();
    Window   	getOverlayWindow();
    
    GLXContext	getNormalContext()     	    { return ctxNormal; }
    GLXContext	getOverlayContext()    	    { return ctxOverlay; }
    
    Widget	getNormalWidget()     	    { return (glModes & SO_GLX_DOUBLE) ? doubleBufferWidget : singleBufferWidget; }
    Widget	getOverlayWidget()    	    { return overlayWidget; }
    
    //
    // Specify exactly what the visual should be for the normal and overlay
    // window. This allows the user to create all possible visuals supported 
    // by OpenGL. The XVisualInfo structure should be a valid OpenGL visual
    // returned by glXChooseVisual().
    //
    virtual void    setNormalVisual(XVisualInfo *vis);
    XVisualInfo *   getNormalVisual();
    virtual void    setOverlayVisual(XVisualInfo *vis);
    XVisualInfo *   getOverlayVisual();
    
    //
    // Routine which allows to dynamically change between single and
    // double buffering.
    //
    virtual void    setDoubleBuffer(SbBool onOrOff);
    SbBool  	    isDoubleBuffer()  	    { return (glModes & SO_GLX_DOUBLE); }
    
    //
    // shows/hides a border of thickness 3 around the glx widgets. This
    // if OFF by default, but turned on by the render area.
    //
    void	setBorder(SbBool onOrOff);
    SbBool	isBorder() const	    { return borderSize != 0; }
    
    //
    // Inventor 2.1 changed the behavior of double buffered windows to
    // redraw temporary to the front buffer when an expose event is received
    // or when a new sceneGraph() is set on an SoXtRenderArea. This does not
    // apply for general interactive rendering. The idea is that it is 
    // better to see something redraw (especially if it is slow) than
    // to see garbage in the window (in the expose case) or an old invalid 
    // scene graph (in the SoXtRenderArea::setSceneGraph() case).
    //
    // This API enables you to turn this functionality OFF if for some reason
    // you are unable to prevent repeated expose from causing a redraw (which
    // is bad and should be fixed, as it gets worse for large scenes). 
    // This will be the case for example if you can't create a pulldown 
    // menu in the popup planes.
    //
    // NOTE: this api might be removed in some future releases and is only
    // intended as a porting help for Inventor 2.0 to 2.1
    //
    void	setDrawToFrontBufferEnable(SbBool enableFlag);
    SbBool	isDrawToFrontBufferEnable() const   { return enableDrawToFrontBuffer; }
    
  protected:
    
    // Subclasses can pass in a bitwise OR specifying the GL modes
    // (e.g. SO_GLX_RGB | SO_GLX_DOUBLE | SO_GLX_ZBUFFER | SO_GLX_OVERLAY)
    // If buildNow is FALSE, this will not build its widget tree until
    // buildWidget() is explicity called; else, buildWidget() is called here.
    SoXtGLWidget(
	    Widget parent = NULL,
	    const char *name = NULL, 
	    SbBool buildInsideParent = TRUE, 
	    int glModes = SO_GLX_RGB, 
	    SbBool buildNow = TRUE);
    virtual ~SoXtGLWidget();
    
    // subclasses MUST redefine redraw() to draw in the normal bit planes.
    // redrawOverlay() should be defined if the overlay planes are being
    // used, and processEvent() should be defined if X events are being 
    // received (see eventMask).
    virtual void	redraw() = 0;
    virtual void	redrawOverlay();
    virtual void	processEvent(XAnyEvent *anyevent);
    
    // subclasses can redefine these to do something useful.
    // initGraphic() is called whenever a GLX window gets created
    // sizeChanged() is called whenever the window changes size
    // widgetChanged() is called whenever the widget is changed (i.e. at
    //    initialization or after switching from single->double buffer)
    virtual void	initGraphic();
    virtual void	initOverlayGraphic();
    virtual void	sizeChanged(const SbVec2s &newSize);
    virtual void	widgetChanged(Widget newWidget);
    
    // sets/gets the size of the glx widget(s) - Note this size could be
    // different from the SoXtComponent::getSize() method which return
    // the size of the component, not necessary the same as the glx widget
    // window (because of extra stuff like the decoration in the viewers).
    void		setGlxSize(SbVec2s newSize);
    const SbVec2s &	getGlxSize() const			{ return glxSize; }
    
    // subclasses can use this routine as the event handler for any
    // devices they wish to get input from.
    static void eventHandler(Widget, SoXtGLWidget *, XAnyEvent *, Boolean *);
    
    // set/get stereo buffering visual. This routine (like setDoubleBuffer)
    // can be called interactively, althought slower since a new window
    // with the needed visual is always created on the fly.
    void		setStereoBuffer(SbBool flag);
    SbBool		isStereoBuffer()  { return (glModes & SO_GLX_STEREO); }
    
    // returns TRUE if main window is in rgb mode (FALSE if color index)
    SbBool		isRGBMode()	    { return (glModes & SO_GLX_RGB); }
    
    // returns the display lists share group for given context:
    int			getDisplayListShareGroup(GLXContext ctx);

    Colormap	    	colorMap;	// set when color index is used
    Colormap	    	overlayColorMap; // set when overlay is used
    SbBool		waitForExpose;	// prevent redraws until an expose is received
    SbBool		drawToFrontBuffer; // used by RA to draw new scenes to front buffer
    
    // make those methods protected to enable the SoXtRenderArea to use them
    // directly when it needs to build the widget and get its resources.
    Widget		buildWidget(Widget parent);
    Widget		getGlxMgrWidget()		{ return mgrWidget; }
    
  private:
    // local vars
    Widget		mgrWidget;
    Widget  	    	doubleBufferWidget, singleBufferWidget, overlayWidget;
    GLXContext		ctxNormal, ctxOverlay, ctxSingle, ctxDouble;
    SbVec2s		glxSize; // size of glx widgets which is always up to date
    int			*attribList;
    int			glModes;
    int			borderSize;
    SbBool		enableDrawToFrontBuffer;
    
    // specify if sizeChanged() should be called when an expose event
    // is received (as opposed to when a resize event is received, where
    // the window hasn't yet been maped to the new size).
    // ??? a GlxDraw bug ?
    SbBool		windowResized;
    
    // creates a GLX widget of the correct current type and get the current
    // set of windows, color maps, etc...
    void  	    	buildNormalGLXWidget(XVisualInfo *vis = NULL);
    void		buildOverlayGLXWidget(XVisualInfo *vis = NULL);
    void		destroyNormalWindows();
    void		destroyGLXWidget(Widget &w, GLXContext &ctx, SbBool normalWindow);
    
    // callbacks from glx widget
    static void	ginitCB(Widget, SoXtGLWidget *, XtPointer);
    static void	overlayGinitCB(Widget, SoXtGLWidget *, XtPointer);
    static void	exposeCB(Widget, SoXtGLWidget *, XtPointer);
    static void	overlayExposeCB(Widget, SoXtGLWidget *, XtPointer);
    static void	resizeCB(Widget, SoXtGLWidget *, XtPointer);
};


#endif // _SO_XT_GL_WIDGET_H_

