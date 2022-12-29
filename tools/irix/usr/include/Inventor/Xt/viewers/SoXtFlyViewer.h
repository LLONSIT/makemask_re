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
 |   $Revision: 2.5 $
 |
 |   Classes	: SoXtFlyViewer
 |
 |   Author(s)	: Alain Dumesny
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_XT_FLY_VIEWER_
#define  _SO_XT_FLY_VIEWER_

#include <Inventor/Xt/viewers/SoXtConstrainedViewer.h>
#include <Inventor/SbLinear.h>
#include <Inventor/SbTime.h>

class	SoFieldSensor;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoXtFlyViewer
//
//
//	Keys used by this viewer:
//	-------------------------
//
//  Left Mouse: Click to increase speed.
//  
//  <s> + Left Mouse: Alternative to the Seek button. Press (but do not
//	hold down) the <s> key, then click on a target object.
//  
//  <u> + Left Mouse: Press (but do not hold down) the <u> key, then
//	click on a target object to set the "up" direction to the surface normal.
//	By default +y is the "up" direction.
//  
//  Middle Mouse: Click to decrease speed.
//  
//  Left and Middle Mouse: Click boths simultaneously to stop.
//  
//  Ctrl: Hold the key down to temporary stop and rotate the viewpoint.
//  
//  Right Mouse: Open the popup menu.
//  
//////////////////////////////////////////////////////////////////////////////

class SoXtFlyViewer : public SoXtConstrainedViewer {
 public:
    
    SoXtFlyViewer(
	Widget parent = NULL,
	const char *name = NULL, 
	SbBool buildInsideParent = TRUE, 
	SoXtFullViewer::BuildFlag flag = BUILD_ALL,
	SoXtViewer::Type type = BROWSER);
    ~SoXtFlyViewer();
    
    //
    // redefine these to add fly viewer functionality
    //
    virtual void    setViewing(SbBool onOrOff);
    virtual void    resetToHomePosition();
    virtual void    setCamera(SoCamera *cam);
    virtual void    setCursorEnabled(SbBool onOrOff);
    
    // This is redefined to prevent the camera type from being changed 
    virtual void    setCameraType(SoType type);
    
 protected:
  
    // This constructor takes a boolean whether to build the widget now.
    // Subclasses can pass FALSE, then call SoXtFlyViewer::buildWidget()
    // when they are ready for it to be built.
    SoEXTENDER
    SoXtFlyViewer(
	Widget parent,
	const char *name, 
	SbBool buildInsideParent, 
	SoXtFullViewer::BuildFlag flag, 
	SoXtViewer::Type type, 
	SbBool buildNow);
	    
    // redefine these
    virtual const char *    getDefaultWidgetName() const;
    virtual const char *    getDefaultTitle() const;
    virtual const char *    getDefaultIconTitle() const;
    
    // redefine those routines to do viewer specific stuff
    virtual void	processEvent(XAnyEvent *anyevent);
    virtual void	setSeekMode(SbBool onOrOff);
    virtual void	actualRedraw();
    virtual void    	rightWheelMotion(float);
    
    // add viewer preference stuff
    virtual void	createPrefSheet();
    
    // Define this to bring the viewer help card
    virtual void	openViewerHelpCard();
    
 private:
    // viewer state variables
    int		    mode;
    SbBool	    createdCursors;
    Cursor	    viewerCursor, seekCursor, upCursor;
    SbVec2s	    locator; // mouse position
    SbVec2s	    startPos; // mouse starting position
    SbRotation	    camStartOrientation;
    
    // variables used for doing moving animation
    SoFieldSensor   *animationSensor;
    SbTime	    prevAnimTime;
    float	    speed, maxSpeed, maxStraightSpeed;
    float	    speedLimit, speedLimitFactor;
    
    // preference sheet stuff
    Widget	    createFlyPrefSheetGuts(Widget parent);
    static void	    incPrefSheetButtonCB(Widget, SoXtFlyViewer *, void *);
    static void	    decPrefSheetButtonCB(Widget, SoXtFlyViewer *, void *);
    
    void	    defineCursors();
    void	    drawViewerFeedback();
    void	    switchMode(int newMode);
    void	    changeMaxStraightSpeed(SbBool increase);
    void	    calculateMaxSpeed();
    static void	    animationSensorCB(void *, SoSensor *);
    void	    doCameraAnimation();

    // this is called by both constructors
    void constructorCommon(SbBool buildNow);
};

#endif  /* _SO_XT_FLY_VIEWER_ */
