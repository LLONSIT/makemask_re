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

//
// Copyright (C) 1990-94   Silicon Graphics, Inc.
//
//______________________________________________________________________
//_____________  S I L I C O N   G R A P H I C S   I N C .  ____________
//
//   $Revision: 2.8 $
//
//   Description:
//	Inventor rendering in a GL/X Motif widget. 
//
//   Author(s): David Mott, Alain Dumesny
//
//_____________  S I L I C O N   G R A P H I C S   I N C .  ____________
//______________________________________________________________________
//

#ifndef _SO_XT_RENDER_AREA_H_
#define _SO_XT_RENDER_AREA_H_

#include <X11/Intrinsic.h>
#include <X11/Xlib.h>

#include <Inventor/SbColor.h>
#include <Inventor/sensors/SoNodeSensor.h>
#include <Inventor/SoSceneManager.h>
#include <Inventor/Xt/SoXtGLWidget.h>
#include <Inventor/actions/SoGLRenderAction.h>

class	SoHandleEventAction;
class	SoXtDevice;
class	SoNode;
class	SoXtMouse;
class	SoXtKeyboard;
class	SoSelection;


// callback function prototype
typedef SbBool SoXtRenderAreaEventCB(void *userData, XAnyEvent *anyevent);

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoXtRenderArea
//
//  Class to do Inventor rendering in a GLX Motif widget.
//
//////////////////////////////////////////////////////////////////////////////

class SoXtRenderArea : public SoXtGLWidget {
  public:
    // Passing FALSE for getMouseInput means the mouse will be ignored.
    // Passing FALSE for getKeyboardInput means the keyboard will be ignored.
    SoXtRenderArea(
	Widget parent = NULL,
	const char *name = NULL, 
	SbBool buildInsideParent = TRUE, 
	SbBool getMouseInput = TRUE,
	SbBool getKeyboardInput = TRUE);
    ~SoXtRenderArea();
    
    //
    // Sets/gets the scene graph to render.
    //
    virtual void	    setSceneGraph(SoNode *newScene);
    virtual SoNode *	    getSceneGraph();
    
    //
    // Sets/gets the scene graph to render in the overlay bit planes.
    //
    void		    setOverlaySceneGraph(SoNode *newScene);
    SoNode *		    getOverlaySceneGraph()
				{ return overlaySceneMgr->getSceneGraph();}
    
    //
    // Handle/Unhandle devices. When registerDevice is called, the 
    // render area will register interest in events which that device
    // generates, and pass those events into the scene graph.
    // unregisterDevice means the render area will no longer listen
    // to events from the passed device.
    //
    void		    registerDevice(SoXtDevice *d);
    void		    unregisterDevice(SoXtDevice *d);
    
    //
    // Sets/gets the window background color when in RGB mode.
    // (default to black (0,0,0));
    //
    void		    setBackgroundColor(const SbColor &c)
				{ sceneMgr->setBackgroundColor(c); }
    const SbColor &	    getBackgroundColor() const
				{ return sceneMgr->getBackgroundColor(); }
    
    //
    // Sets/gets the window background color when in color index mode.
    // (default to black (index 0)).
    //
    void		    setBackgroundIndex(int index)
				{ sceneMgr->setBackgroundIndex(index); }
    int			    getBackgroundIndex() const
				{ return sceneMgr->getBackgroundIndex(); }
    
    //
    // Sets/gets the overlay window background color index.
    // (default to 0 (clear color)).
    //
    void		    setOverlayBackgroundIndex(int index)
				{ overlaySceneMgr->setBackgroundIndex(index); }
    int			    getOverlayBackgroundIndex() const
				{ return overlaySceneMgr->getBackgroundIndex(); }
    
    //
    // Sets the colors to use when displaying in color index mode.
    //
    void	setColorMap(int startIndex, int num, const SbColor *colors);
    
    //
    // Sets the colors to use for overlay bit planes.
    //
    void	setOverlayColorMap(int startIndex, int num, const SbColor *colors);
    
    // Sets/gets current viewport region to use for rendering
    void	setViewportRegion(const SbViewportRegion &newRegion) 
		    { sceneMgr->getGLRenderAction()->setViewportRegion(newRegion); }
    const SbViewportRegion &getViewportRegion() const
		    { return sceneMgr->getGLRenderAction()->getViewportRegion(); }
    
    //
    // Transparency level setting methods which specifies how 
    // transparent objects are rendered (quality/speed trade off).
    // 
    void	setTransparencyType(SoGLRenderAction::TransparencyType type);
    SoGLRenderAction::TransparencyType	getTransparencyType() const
		    { return sceneMgr->getGLRenderAction()->getTransparencyType(); }

    
    //
    // Anti-aliasing methods.
    //
    void    	    setAntialiasing(SbBool smoothing, int numPasses);
    void    	    getAntialiasing(SbBool &smoothing, int &numPasses) const
			    { sceneMgr->getAntialiasing(smoothing, numPasses); }
    
    //
    // Enable/prevent window clearing from happening before a rendering
    // starts (default is clearBeforeRender TRUE).
    //
    void		    setClearBeforeRender(SbBool trueOrFalse)
					    { clearFirst = trueOrFalse; }
    SbBool		    isClearBeforeRender() const
					    { return clearFirst; }
    void		    setClearBeforeOverlayRender(SbBool trueOrFalse)
					    { clearOverlayFirst = trueOrFalse; }
    SbBool		    isClearBeforeOverlayRender() const
					    { return clearOverlayFirst; }
    
    //
    // The render area will automatically redraw whenever something
    // in the scene graph changes. Passing FALSE to setAutoRedraw()
    // will disable this feature. NOTE: the render area will always
    // redraw in response to window system events (e.g. resize, exposure)
    // regardless of the setting of the auto redraw flag.
    void		    setAutoRedraw(SbBool trueOrFalse);
    SbBool		    isAutoRedraw() const { return autoRedraw; }
    
    // Sets/gets the priority of the redraw sensor and get the
    // default priority number.
    void		setRedrawPriority(uint32_t priority)
				{ sceneMgr->setRedrawPriority(priority);
				  overlaySceneMgr->setRedrawPriority(priority); }
    uint32_t	getRedrawPriority() const
				{ return sceneMgr->getRedrawPriority(); }
    static uint32_t getDefaultRedrawPriority()
				{ return SoSceneManager::getDefaultRedrawPriority(); }

    //
    // Calling this forces the render area to be redrawn now.
    // It is not necessary to call this method if auto redraw is enabled
    // (which is the default).
    //
    void		    render()		{ redraw(); }
    void		    renderOverlay()	{ redrawOverlay(); }
    
    //
    // Schedule a redraw to happen sometime soon. This will schedule the redraw sensor
    // if auto-redraw is TRUE (default) else cause an immediate redraw of the scene if
    // auto-redraw if FALSE.
    //
    void		    scheduleRedraw();
    void		    scheduleOverlayRedraw();
    
    // Call this convenience method to have this render area redraw
    // whenever the selection list changes in the passed node. This
    // is useful if using a highlight render action like the
    // SoBoxHighlightRenderAction to correctly render whenever the
    // selection changes. Pass NULL to turn this off.
    void		    redrawOnSelectionChange(SoSelection *s);
    void		    redrawOverlayOnSelectionChange(SoSelection *s);
    
    //
    // Register an application callback for handling events that
    // occurs in the window, instead of sending them down the graph.
    // Callback should return TRUE if it handled the event.
    // If callback returns FALSE, then the event will be sent
    // to the scene graph.
    //
    void    	    setEventCallback(
		    	    SoXtRenderAreaEventCB *fcn, 
			    void *userData = NULL)
			    { appEventHandler = fcn; appEventHandlerData = userData; }
    
    // Access to the scene manager
    void		setSceneManager(SoSceneManager *sm) { sceneMgr = sm; }
    SoSceneManager *	getSceneManager() const { return sceneMgr; }
    void		setOverlaySceneManager(SoSceneManager *sm) { overlaySceneMgr = sm; }
    SoSceneManager *	getOverlaySceneManager() const { return overlaySceneMgr; }
    
    // Access to GL render action
    void		setGLRenderAction(SoGLRenderAction *ra) 
			    { sceneMgr->setGLRenderAction(ra); }
    SoGLRenderAction	*getGLRenderAction() const
			    { return sceneMgr->getGLRenderAction(); }

    // Access to overlay GL render action
    void		setOverlayGLRenderAction(SoGLRenderAction *ra) 
			    { overlaySceneMgr->setGLRenderAction(ra); }
    SoGLRenderAction	*getOverlayGLRenderAction() const
			    { return overlaySceneMgr->getGLRenderAction(); }

  protected:
  
    //
    // This constructor takes a boolean whether to build the widget now.
    // Subclasses can pass FALSE, then call SoXtRenderArea::buildWidget()
    // when they are ready for it to be built.

    SoXtRenderArea(
	    Widget parent,
	    const char *name, 
	    SbBool buildInsideParent, 
	    SbBool getMouseInput,
	    SbBool getKeyboardInput, 
	    SbBool buildNow);
	
    //
    // redraw() calls actualRedraw(), followed by swapbuffers if necessary.
    // actualRedraw will have the scene manager render the scene. Rendering
    // is broken up into two routines like this so that subclasses can
    // redefine or simply add to rendering (in actualRedraw) without having
    // to worry about being visible, seting up the window or 
    // single/double buffer swapping.
    //
    virtual void	redraw();
    virtual void	actualRedraw();
    virtual void	redrawOverlay();
    virtual void	actualOverlayRedraw();
    
    //
    // Redefine these to do Inventor-specific things
    //
    virtual void	processEvent(XAnyEvent *anyevent);
    virtual void	initGraphic();
    virtual void	initOverlayGraphic();
    virtual void	sizeChanged(const SbVec2s &newSize);
    virtual void	widgetChanged(Widget);

    Widget		buildWidget(Widget parent);
    
    // redefine these
    virtual const char *    getDefaultWidgetName() const;
    virtual const char *    getDefaultTitle() const;
    virtual const char *    getDefaultIconTitle() const;
    
    // subclasses have access to the device list for event processing
    SbPList		*deviceList;	// list of devices
    
    // application event callback variables
    SoXtRenderAreaEventCB *appEventHandler;
    void    	    	  *appEventHandlerData;
    // invoke the application event callback - returns what the app cb returns
    SbBool		invokeAppCB(XAnyEvent *anyevent);
    
  private:
    // these make rendering/redrawing happen
    SoSceneManager	*sceneMgr;	// this manages rendering and events
    SoSceneManager	*overlaySceneMgr; // manages the overlay scene graph
    SbBool  	    	clearFirst, clearOverlayFirst;	// call clear() before rendering
    SbBool		autoRedraw;	// if TRUE, then we automatically redraw
    XColor		*mapColors, *overlayMapColors; // saved colors
    int			mapColorNum, overlayMapColorNum; // number of saved colors

    SoXtMouse		*mouseDevice;
    SoXtKeyboard	*keybdDevice;
    void		reinstallDevices(Widget newWidget);
    
    static void		selectionChangeCB(void *userData, SoSelection *s);
    static void		overlaySelectionChangeCB(void *userData, SoSelection *s);
    SoSelection		*selection, *overlaySelection;
    Widget		deviceWidget;

    // static callbacks
    SbBool		firstEvent; // used to init the action SoWindowElement
    static void		windowEventCB(Widget, SoXtRenderArea *, XAnyEvent *, Boolean *);
    static void		renderCB(void *, SoSceneManager *);
    static void		renderOverlayCB(void *, SoSceneManager *);
    
    static void visibilityChangeCB(void *pt, SbBool visible);
    void        activate();		// connects the sensor
    void        deactivate();		// disconnects the sensor
    
    // this is called by both constructors
    void constructorCommon(
	    SbBool getMouseInput,
	    SbBool getKeyboardInput, 
	    SbBool buildNow);
};


#endif /* _SO_XT_RENDER_AREA_H_ */

