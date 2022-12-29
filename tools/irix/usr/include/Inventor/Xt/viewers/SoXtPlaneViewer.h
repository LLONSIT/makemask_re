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
 |   $Revision: 2.4 $
 |
 |   Classes	: SoXtPlaneViewer
 |
 |   Author(s)	: Alain Dumesny
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_XT_PLANE_VIEWER_
#define  _SO_XT_PLANE_VIEWER_

#include <Inventor/Xt/viewers/SoXtFullViewer.h>
#include <Inventor/SbLinear.h>

class SoXtBitmapButton;


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoXtPlaneViewer
//
//  Plane Viewer - allows the user to move the camera in a plane, zoom in
//	and out, as well as rotate the viewing plane.
//
//	Keys used by this viewer:
//	-------------------------
//
//     Left Mouse: Dolly in and out (gets closer to and further away from the
//     object).
//
//     Middle Mouse: 
//     Ctrl + Left Mouse: Translate up, down, left and right.
//
//     Ctrl + Middle Mouse: Used for roll action (rotates around the viewer
//     forward direction).
//
//     <s> + click: Alternative to the Seek button. Press (but do not hold down)
//     the <s> key, then click on a target object.
//
//     Right Mouse: Open the popup menu.
//  
//////////////////////////////////////////////////////////////////////////////

class SoXtPlaneViewer : public SoXtFullViewer {
 public:
    SoXtPlaneViewer(
	Widget parent = NULL,
	const char *name = NULL, 
	SbBool buildInsideParent = TRUE, 
	SoXtFullViewer::BuildFlag flag = BUILD_ALL, 
	SoXtViewer::Type type = BROWSER);
    ~SoXtPlaneViewer();
    
    //
    // redefine these to add Plane viewer functionality
    //
    virtual void	setViewing(SbBool onOrOff);
    virtual void	setCamera(SoCamera *cam);
    virtual void	setCursorEnabled(SbBool onOrOff);
    
 protected:
  
    // This constructor takes a boolean whether to build the widget now.
    // Subclasses can pass FALSE, then call SoXtPlaneViewer::buildWidget()
    // when they are ready for it to be built.
    SoEXTENDER
    SoXtPlaneViewer(
	Widget parent,
	const char *name, 
	SbBool buildInsideParent, 
	SoXtFullViewer::BuildFlag flag, 
	SoXtViewer::Type type, 
	SbBool buildNow);

    Widget		buildWidget(Widget parent);
        
    // redefine these
    virtual const char *    getDefaultWidgetName() const;
    virtual const char *    getDefaultTitle() const;
    virtual const char *    getDefaultIconTitle() const;
    
    // redefine those routines to do viewer specific stuff
    virtual void	processEvent(XAnyEvent *anyevent);
    virtual void	setSeekMode(SbBool onOrOff);
    virtual void	actualRedraw();
    
    // Define those thumb wheels to translate in the viewer plane
    virtual void    	bottomWheelMotion(float newVal);
    virtual void    	leftWheelMotion(float newVal);
    virtual void    	rightWheelMotion(float newVal);
    
    // add viewer preference stuff
    virtual void	createPrefSheet();
    
    // add some viewer buttons
    virtual void	createViewerButtons(Widget parent);
    
    // Define this to bring the viewer help card
    virtual void	openViewerHelpCard();
    
    // Redefine this to keep the same camera rotation when seeking
    virtual void	computeSeekFinalOrientation();

 private:
    // viewer state variables
    int		    mode;
    SbBool	    createdCursors;
    Cursor	    transCursor, dollyCursor, seekCursor;
    SbVec2s	    locator; // mouse position
    
    // camera translation vars
    SbVec3f	    locator3D;
    SbPlane	    focalplane;
    float	    transXspeed, transYspeed;
    
    // push button vars and callbacks
    SoXtBitmapButton  *buttonList[10];
    static void	    pushButtonCB(Widget, int id, void *);
    
    void	    updateViewerMode(unsigned int state);
    void	    switchMode(int newMode);
    void	    updateCursor();
    void	    defineCursors();
    void	    rollCamera(const SbVec2s &newLocator);
    void	    translateCamera(const SbVec2f &newLocator);
    void	    dollyCamera(const SbVec2s &newLocator);
    void	    setPlane(const SbVec3f &newNormal, const SbVec3f &newRight);
    
    // redefine these to also call computeTranslateValues()
    virtual void    bottomWheelStart();
    virtual void    leftWheelStart();
    void	    computeTranslateValues();
    
    // this is called by both constructors
    void constructorCommon(SbBool buildNow);
};

#endif  /* _SO_XT_PLANE_VIEWER_ */
