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
// Copyright (C) 1990-93   Silicon Graphics, Inc.
//
//______________________________________________________________________
//_____________  S I L I C O N   G R A P H I C S   I N C .  ____________
//
//   $Revision: 2.5 $
//
//   Description:
//	SoSceneManager manages rendering and event handling operations
//      on a scene graph. 
//
//   Author(s): David Mott, Alain Dumesny
//
//_____________  S I L I C O N   G R A P H I C S   I N C .  ____________
//______________________________________________________________________
//

#ifndef _SO_SCENE_MANAGER_
#define _SO_SCENE_MANAGER_

#include <Inventor/SbColor.h>
#include <Inventor/actions/SoGLRenderAction.h>

class SoNodeSensor;
class SoEvent;
class SoHandleEventAction;
class SoNode;
class SoSceneManager;
class SoSensor;
class SoSFTime;
class SoOneShotSensor;

// callback function prototypes
typedef void SoSceneManagerRenderCB(void *userData, SoSceneManager *mgr);

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoSceneManager
//
//  Class which performs Inventor rendering and event handling
//  on a scene graph.
//
//////////////////////////////////////////////////////////////////////////////

class SoSceneManager {
  public:
    // Constructor. 
    SoSceneManager();
    // Destructor.
    ~SoSceneManager();
    
    // Render and process events.
    // reinitialize is called to initialize graphics, i.e. for a new window.
    // NOTE: a window MUST be set before calling render() and processEvent().
    // The window size must also be set (call setWindowSize()).
    virtual void	render(SbBool clearWindow = TRUE, SbBool clearZbuffer = TRUE);
    virtual SbBool	processEvent(const SoEvent *event);
    void		reinitialize();
    
    // Schedule a redraw for some time in the near future.
    // If there is no render callback set, or this is not active,
    // no redraw will be scheduled.
    void		scheduleRedraw();
    
    //
    // Set/get the scene graph to render.
    //
    virtual void	setSceneGraph(SoNode *newScene);
    virtual SoNode *	getSceneGraph() const;
    
    // Set/get the size of the window in which scene mgr should render.
    // This size must be set before render() and processEvent() are called.
    void		setWindowSize(const SbVec2s &newSize);
    const SbVec2s &	getWindowSize() const;
    
    // Set/get the size and origin of the viewport within the window.
    // Default is to render the entire window region, that is, 
    // origin = (0,0), size = getWindowSize().
    void		setSize(const SbVec2s &newSize);
    const SbVec2s &	getSize() const;
    void		setOrigin(const SbVec2s &newOrigin);    
    const SbVec2s &	getOrigin() const;
    
    // Sets/gets current viewport region to use for rendering.
    // This can be used instead of setting the size and origin separately.
    void	setViewportRegion(const SbViewportRegion &newRegion);
    const SbViewportRegion &getViewportRegion() const;

    //
    // Sets/gets the window background color when in RGB mode.
    // (default to black (0,0,0));
    //
    void		setBackgroundColor(const SbColor &c);
    const SbColor &	getBackgroundColor() const  { return bkgColor; }
    
    //
    // Sets/gets the window background color when in color index mode.
    // (default to black (index 0)).
    //
    void		setBackgroundIndex(int index);
    int			getBackgroundIndex() const  { return bkgIndex; }
    
    //
    // Set/get the color mode (TRUE - rgb mode, FALSE - color map mode)
    // Default is TRUE - rgb mode.
    //
    void		setRGBMode(SbBool onOrOff);
    SbBool		isRGBMode() const	    { return rgbMode; }
    
    // The scene manager will only employ sensors while it is active.
    virtual void	activate();
    virtual void	deactivate();

    // Render callback - the scene manager employs a sensor to redraw
    // the scene when something changes. This callback is invoked for that
    // to happen. The callback should set up its graphics window, then
    // call the scene manager render() method. If the callback is set to NULL
    // (the default), auto-redraw is turned off.
    void		setRenderCallback(
			    SoSceneManagerRenderCB *f,
			    void *userData = NULL);
    SbBool		isAutoRedraw() const { return (renderCB != NULL); }
    
    // Sets/returns the priority of the redraw sensor.
    void		setRedrawPriority(uint32_t priority);
    uint32_t	getRedrawPriority() const;

    // Returns the default priority of the redraw sensor
    static uint32_t getDefaultRedrawPriority() { return 10000; }
    
    // Enable/Disable the realTime global field update which normally
    // happen right after a redraw.
    static void		enableRealTimeUpdate(SbBool flag);
    static SbBool	isRealTimeUpdateEnabled()	{ return updateRealTime; }
    
    //
    // Anti-aliasing methods.
    //
    void    	    setAntialiasing(SbBool smoothing, int numPasses);
    void    	    getAntialiasing(SbBool &smoothing, int &numPasses) const;
    
  SoEXTENDER public:
    // User supplied render action. Highlights fall into this category.
    // SceneManager will never delete a render action passed to this method.
    void		setGLRenderAction(SoGLRenderAction *ra);
    SoGLRenderAction	*getGLRenderAction() const { return renderAction; }

    // User supplied handle event action. This should not be done in
    // the middle of event handling. Passing NULL turns event handling off.
    // SceneManager will never delete a handle event action passed to
    // this method.
    void		setHandleEventAction(SoHandleEventAction *hea);
    SoHandleEventAction	*getHandleEventAction() const { return handleEventAction; }

  protected:
    SoSceneManagerRenderCB  *renderCB;
    void		    *renderCBData;
    SbBool		isActive() const { return active; }
    
    // This tells the app it is time to redraw by invoking the renderCB.
    void		redraw();
    
  private:
    SbBool		raCreatedHere;
    SbBool		heaCreatedHere;
    SoGLRenderAction	*renderAction;
    SoHandleEventAction	*handleEventAction;
    SoNode		*scene;
    SoNodeSensor	*sceneSensor;	// attached to root for auto-redraw
    uint32_t	redrawPriority;	// Priority of sceneSensor
    SbBool		active;		// set TRUE if we are active
    SbBool		needZbuffer;
    SbBool		needToSendVP; // TRUE when glViewport() needs to be called
    
    SbColor		bkgColor;
    int			bkgIndex;
    SbBool		graphicsInitNeeded;
    SbBool		rgbMode;
    
    // static callbacks
    static void	    	antialiasingCallback(void *);
    static void		sceneSensorCallback(SoSceneManager *, SoSensor *);
    
    // realTime field update vars and callbacks
    static SbBool	updateRealTime;
    static SoSFTime	*realTime;
    static SoOneShotSensor *realTimeSensor; // touches realTime global field
    static void		realTimeSensorCB();
};


#endif // _SO_SCENE_MANAGER_
