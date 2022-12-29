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
 |   $Revision: 2.8 $
 |
 |   Classes	: SoXtFullViewer
 |
 |   Author(s)	: Alain Dumesny
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_XT_FULL_VIEWER_
#define  _SO_XT_FULL_VIEWER_

#include <Xm/Xm.h>
#include <Inventor/Xt/viewers/SoXtViewer.h>
#include <Inventor/SbPList.h>

// classes used
class	SoXtResource;
class	SoXtBitmapButton;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoXtFullViewer
//
//	The SoXtFullViewer component class is the abstract base class for all
//  viewers which include a decoration around the rendering area. The 
//  decoration is made of thumbwheels, sliders and push/toggle buttons. There
//  is also a popup menu which includes all of the viewing options and methods.
//
//////////////////////////////////////////////////////////////////////////////

class SoXtFullViewer : public SoXtViewer {
  public:
    // This specifies what should be build by default in the constructor
    enum BuildFlag {
	BUILD_NONE	    = 0x00, 
	BUILD_DECORATION    = 0x01, 
	BUILD_POPUP	    = 0x02, 
	BUILD_ALL	    = 0xff
    };
    
    //
    // Show/hide the viewer component trims (default ON)
    //
    void    	    setDecoration(SbBool onOrOff);
    SbBool  	    isDecoration()	    { return decorationFlag; }
    
    //
    // Enable/disable the popup menu (default enabled)
    //
    void    	    setPopupMenuEnabled(SbBool trueOrFalse);
    SbBool  	    isPopupMenuEnabled()    { return popupEnabled; }
    
    //
    // Add/remove push buttons for the application, which will be placed 
    // in the left hand side decoration trim.
    // The add() method appends the button to the end of the list, while 
    // insert() places the button at the specified index (starting at 0).
    //
    // returns the parent widget, which is needed when creating new buttons
    // NOTE that this will be NULL if the decoration is NOT created in the
    // constructor (see the BuildFlag) until it is shown.
    Widget	    getAppPushButtonParent() const { return appButtonForm; }
    void	    addAppPushButton(Widget newButton);
    void	    insertAppPushButton(Widget newButton, int index);
    void	    removeAppPushButton(Widget oldButton);
    int		    findAppPushButton(Widget oldButton)
				{ return appButtonList->find(oldButton); }
    int		    lengthAppPushButton()
				{ return appButtonList->getLength(); }
    
    Widget	    getRenderAreaWidget()   { return raWidget; }
    
    // redefine these from the base class
    virtual void    setViewing(SbBool onOrOff);
    virtual void    setHeadlight(SbBool onOrOff);
    virtual void    setDrawStyle(SoXtViewer::DrawType type, 
				SoXtViewer::DrawStyle style);
    virtual void    setBufferingType(SoXtViewer::BufferType type);
    virtual void    setCamera(SoCamera *cam);
    virtual void    hide();
    
  protected:
    // Constructor/Destructor
    SoXtFullViewer(
	Widget parent,
	const char *name, 
	SbBool buildInsideParent, 
	SoXtFullViewer::BuildFlag flag, 
	SoXtViewer::Type type, 
	SbBool buildNow);
    ~SoXtFullViewer();
    
    // general decoration vars
    SbBool	    decorationFlag;
    Widget	    mgrWidget; // form which manages all other widgets
    Widget	    raWidget;  // render area widget
    Widget	    leftTrimForm, bottomTrimForm, rightTrimForm;
    
    // thumb wheel vars
    Widget	    rightWheel, bottomWheel, leftWheel;
    char    	    *rightWheelStr, *bottomWheelStr, *leftWheelStr;
    float   	    rightWheelVal, bottomWheelVal, leftWheelVal;
    Widget  	    rightWheelLabel, bottomWheelLabel, leftWheelLabel;
    
    // widget list of viewer buttons
    SbPList	    *viewerButtonWidgets;
    
    // The button widget should be used as the parent widget
    // when creating new buttons
    Widget	    getButtonWidget() const { return appButtonForm; }
    
    // popup menu vars
    SbBool  	    popupEnabled;
    Widget  	    popupWidget, *popupToggleWidgets;
    Widget  	    *drawStyleWidgets, *bufferStyleWidgets;
    char    	    *popupTitle;
    
    //
    // Build/destroy decoration routines
    //
    Widget 		buildWidget(Widget parent);
    void		buildLeftWheel(Widget parent);
    
    virtual void    	buildDecoration(Widget parent);
    virtual Widget    	buildLeftTrim(Widget parent);
    virtual Widget    	buildBottomTrim(Widget parent);
    virtual Widget    	buildRightTrim(Widget parent);
    Widget		buildAppButtons(Widget parent);
    Widget		buildViewerButtons(Widget parent);
    virtual void	createViewerButtons(Widget parent);
    
    //
    // popup menu build routines
    //
    virtual void  	buildPopupMenu();
    virtual void    	destroyPopupMenu();
    void		setPopupMenuString(const char *name);
    Widget		buildFunctionsSubmenu(Widget popup);
    Widget		buildDrawStyleSubmenu(Widget popup);
    
    //
    // Preference sheet build routines
    //
    void	    setPrefSheetString(const char *name);
    virtual void    createPrefSheet();
    void	    createPrefSheetShellAndForm(Widget &shell, Widget &form);
    void	    createDefaultPrefSheetParts(Widget widgetList[], 
				int &num, Widget form);
    void	    layoutPartsAndMapPrefSheet(Widget widgetList[], 
				int num, Widget form, Widget shell);
    Widget	    createSeekPrefSheetGuts(Widget parent);
    Widget	    createSeekDistPrefSheetGuts(Widget parent);
    Widget	    createZoomPrefSheetGuts(Widget parent);
    Widget	    createClippingPrefSheetGuts(Widget parent);
    Widget	    createStereoPrefSheetGuts(Widget parent);
    Widget	    createSpeedPrefSheetGuts(Widget parent);
    
    // Subclasses SHOULD redefine these to do viewer specific tasks
    // since these do nothing in the base class. those routines are 
    // called by the thumb wheels whenever they rotate.
    virtual void    	rightWheelMotion(float);
    virtual void    	bottomWheelMotion(float);
    virtual void    	leftWheelMotion(float);
    
    // Subclasses can redefine these to add viewer functionality. They
    // by default call start and finish interactive viewing methods.
    // (defined in the base class).
    virtual void    	rightWheelStart();
    virtual void    	bottomWheelStart();
    virtual void    	leftWheelStart();
    virtual void    	rightWheelFinish();
    virtual void    	bottomWheelFinish();
    virtual void    	leftWheelFinish();
    
    // Subclasses SHOULD set those wheel string to whatever functionality
    // name they are redefining the thumb wheels to do. Default names are
    // "Motion X, "Motion Y" and "Motion Z" for bottom, left and right wheels.
    void		setBottomWheelString(const char *name);
    void		setLeftWheelString(const char *name);
    void		setRightWheelString(const char *name);
    
    // Subclasses SHOULD redefine the openViewerHelpCard() routine to bring 
    // their help card (called by push button and popup menu entry).
    // They can simply call SoXtComponent::openHelpCard() to open their
    // specific help card.
    virtual void	openViewerHelpCard();
    
 private:
    SbBool	    firstBuild; // set FALSE after buildWidget called once
    
    // app button vars
    Widget	    appButtonForm;
    SbPList	    *appButtonList;
    void	    doAppButtonLayout(int start);

    // this is called the first time the widget is built
    void	    getResources(SoXtResource *xr);
    
    // popup menu callbacks
    static void     popMenuCallback(Widget, SoXtFullViewer *, XEvent *, Boolean *);
    static void     drawStyleMenuPick(Widget, int id, void *);
    static void     bufferStyleMenuPick(Widget, int id, void *);
    static void     menuPick(Widget, int id, XmAnyCallbackStruct *);
    
    // push buttons vars and callbacks
    SoXtBitmapButton  *buttonList[10];
    static void	    pushButtonCB(Widget, int id, void *);
    
    // pref sheet variables
    Widget	    prefSheetShellWidget;
    char	    *prefSheetStr;
    static void	    prefSheetDestroyCB(Widget, SoXtFullViewer *, void *);
    
    // seek pref sheet callbacks
    static void	    seekPrefSheetFieldCB(Widget, SoXtFullViewer *, void *);
    static void	    seekPrefSheetToggle1CB(Widget, Widget, void *);
    static void	    seekPrefSheetToggle2CB(Widget, Widget, void *);
    
    // zoom pref sheet vars and callbacks
    Widget	    *zoomWidgets;
    SbVec2f	    zoomSldRange;
    void    	    setCameraZoom(float zoom);
    float	    getCameraZoom();
    void	    setZoomSliderPosition(float zoom);
    void	    setZoomFieldString(float zoom);
    static void	    zoomSliderCB(Widget, SoXtFullViewer *, XtPointer *);
    static void	    zoomFieldCB(Widget, SoXtFullViewer *, XtPointer *);
    static void	    zoomPrefSheetMinFieldCB(Widget, SoXtFullViewer *, void *);
    static void	    zoomPrefSheetMaxFieldCB(Widget, SoXtFullViewer *, void *);
    
    // seek dist pref sheet vars and callbacks
    int		    seekDistWheelVal;
    Widget	    seekDistField;
    static void	    seekDistWheelCB(Widget, SoXtFullViewer *v, XtPointer *d);
    static void	    seekDistFieldCB(Widget, SoXtFullViewer *, void *);
    static void	    seekDistPercPrefSheetToggleCB(Widget, Widget, void *);
    static void	    seekDistAbsPrefSheetToggleCB(Widget, Widget, void *);
    
    // clipping plane pref sheet callbacks and variables
    Widget	    clipWheelForm;
    int		    clipNearWheelVal, clipFarWheelVal;
    Widget	    clipNearField, clipFarField;
    static void	    clipPrefSheetToggleCB(Widget, Widget, void *);
    static void	    clipNearWheelCB(Widget, SoXtFullViewer *v, XtPointer *d);
    static void	    clipFarWheelCB(Widget, SoXtFullViewer *v, XtPointer *d);
    static void	    clipFieldCB(Widget, SoXtFullViewer *, void *);
    
    // stereo viewing pref sheet callbacks and variables
    Widget	    stereoWheelForm, stereoField, stereoLabel;
    int		    stereoWheelVal;
    static void	    stereoPrefSheetToggleCB(Widget, Widget, void *);
    static void	    stereoWheelCB(Widget, SoXtFullViewer *, XtPointer *);
    static void	    stereoFieldCB(Widget, SoXtFullViewer *, void *);
    
    // dolly speed pref sheet callbacks
    static void	    speedIncPrefSheetButtonCB(Widget, SoXtFullViewer *, void *);
    static void	    speedDecPrefSheetButtonCB(Widget, SoXtFullViewer *, void *);
    
    // callback functions for thumbwheels
    static  void    rightWheelCB(Widget, SoXtFullViewer *v, XtPointer *d);
    static  void    bottomWheelCB(Widget, SoXtFullViewer *v, XtPointer *d);
    static  void    leftWheelCB(Widget, SoXtFullViewer *v, XtPointer *d);
};


#endif  /* _SO_XT_FULL_VIEWER_ */
