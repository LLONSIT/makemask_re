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
 |   Classes	: SoXtExaminerViewer
 |
 |   Author(s)	: Alain Dumesny
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_XT_EXAMINER_VIEWER_
#define  _SO_XT_EXAMINER_VIEWER_

#include <Inventor/Xt/viewers/SoXtFullViewer.h>
#include <Inventor/SbLinear.h>

// classes used
class SbSphereSheetProjector;
class SoFieldSensor;
class SoSeparator;
class SoSwitch;
class SoTranslation;
class SoScale;
class SoXtBitmapButton;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoXtExaminerViewer
//
//	Examiner viewer - allows the user to change the camera position
//  by spinning a sphere in front of the viewpoint.
//
//
//	Keys used by this viewer:
//	-------------------------
//
//	Left Mouse: Tumbles the virtual trackball.
//
//	Middle Mouse: 
//	Ctrl + Left Mouse: Translate up, down, left and right.
//
//	Ctrl + Middle Mouse: 
//	Left + Middle Mouse: Dolly in and out (gets closer to and further
//			    away from the object).
//
//	<s> + click: Alternative to the Seek button. Press (but do not hold 
//		    down) the <s> key, then click on a target object.
//
//	Right Mouse: Open the popup menu.
//
//////////////////////////////////////////////////////////////////////////////

class SoXtExaminerViewer : public SoXtFullViewer {
  public:
    SoXtExaminerViewer(
	Widget parent = NULL,
	const char *name = NULL, 
	SbBool buildInsideParent = TRUE, 
	SoXtFullViewer::BuildFlag flag = BUILD_ALL, 
	SoXtViewer::Type type = BROWSER);
    ~SoXtExaminerViewer();
    
    //
    // Show/hide the point of rotation feedback, which only appears while
    // in Viewing mode. (default OFF)
    //
    void	setFeedbackVisibility(SbBool onOrOff);
    SbBool	isFeedbackVisible() const	{ return feedbackFlag; }
    
    //
    // Set/get the point of rotation feeedback size in pixels (default 20). 
    //
    void	setFeedbackSize(int newSize);
    int		getFeedbackSize() const		{ return feedbackSize; }
    
    //
    // Enable/disable the animation feature of the viewer. 
    // (enabled by default)
    //
    void    	setAnimationEnabled(SbBool onOrOff);
    SbBool  	isAnimationEnabled()		{ return animationEnabled; }
    
    //
    // Stop animation, if it is occurring, and queuery if the viewer is 
    // currently animating.
    //
    void    	stopAnimating();
    SbBool  	isAnimating()  			{ return animatingFlag; }
    
    //
    // redefine these to add Examiner viewer functionality
    //
    virtual void	viewAll();
    virtual void	resetToHomePosition();
    virtual void	setCamera(SoCamera *cam);
    virtual void	setViewing(SbBool onOrOff);
    virtual void	setCursorEnabled(SbBool onOrOff);
    
 protected:
  
    // This constructor takes a boolean whether to build the widget now.
    // Subclasses can pass FALSE, then call SoXtExaminerViewer::buildWidget()
    // when they are ready for it to be built.
    SoEXTENDER
    SoXtExaminerViewer(
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
    
    // Get X resources for the widget.
    Widget 		buildWidget(Widget parent);
    
    // Define those thumb wheels to rotate the object
    virtual void    	bottomWheelMotion(float newVal);
    virtual void    	leftWheelMotion(float newVal);
    virtual void    	rightWheelMotion(float newVal);
    
    // redefine those routines to also stop animation if any
    virtual void    	bottomWheelStart();
    virtual void    	leftWheelStart();
    
    // add viewer preference stuff
    virtual void	createPrefSheet();
    
    // add some viewer buttons
    virtual void	createViewerButtons(Widget parent);
    
    // Define this to bring the viewer help card
    virtual void	openViewerHelpCard();
    
 private:
    // viewer state variables
    int		    mode;
    SbBool	    createdCursors;
    Cursor	    spinCursor, panCursor, dollyCursor, seekCursor;
    SbSphereSheetProjector *sphereSheet;
    SbVec2s	    locator; // mouse position
    SbBool	    firstBuild; // set FALSE after buildWidget called once
    
    // point of rotation feedback vars
    SbBool	    feedbackFlag;
    float	    feedbackSize;
    SoSeparator	    *feedbackRoot;
    SoSwitch	    *feedbackSwitch;
    SoTranslation   *feedbackTransNode;
    SoScale	    *feedbackScaleNode;
    static char	    *geometryBuffer;
    void	    createFeedbackNodes();
    
    // variables used for doing spinning animation
    SbBool	    animationEnabled, animatingFlag;
    SoFieldSensor   *animationSensor;
    SbRotation	    *rotBuffer;
    int		    firstIndex, lastIndex;
    int32_t	    lastMotionTime;
    SbRotation	    averageRotation;
    SbBool	    computeAverage;
    static void	    animationSensorCB(void *v, SoSensor *s);
    static void	    visibilityChangeCB(void *pt, SbBool visible);
    void	    doSpinAnimation();
    
    // camera panning vars
    SbVec3f	    locator3D;
    SbPlane	    focalplane;
    
    void	    updateViewerMode(unsigned int state);
    void	    switchMode(int newMode);
    void	    updateCursor();
    void	    defineCursors();
    void	    rotateCamera(const SbRotation &rot);
    void	    panCamera(const SbVec2f &newLocator);
    void	    spinCamera(const SbVec2f &newLocator);
    void	    dollyCamera(const SbVec2s &newLocator);
    
    // preference sheet stuff
    Widget	    createExamPrefSheetGuts(Widget parent);
    static void	    animPrefSheetToggleCB(Widget, SoXtExaminerViewer *, void *);
    
    // point of rotation pref sheet stuff
    int		    feedbackSizeWheelVal;
    Widget	    feedbackLabel[2], feedbackField, feedbackSizeWheel;
    static void	    feedbackSizeWheelCB(Widget, SoXtExaminerViewer *p, XtPointer *d);
    static void	    feedbackSizeFieldCB(Widget, SoXtExaminerViewer *, void *);
    static void	    feedbackPrefSheetToggleCB(Widget, SoXtExaminerViewer *, void *);
    void	    toggleFeedbackWheelSize(Widget toggle);
    
    // push button vars and callbacks
    SoXtBitmapButton  *buttonList[10];
    static void	    camPushCB(Widget, SoXtExaminerViewer *, void *);

    // this is called by both constructors
    void constructorCommon(SbBool buildNow);
};

#endif  /* _SO_XT_EXAMINER_VIEWER_ */
