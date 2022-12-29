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
 |   $Revision: 2.0 $
 |
 |   Description:
 |	Xt component (widget) for editing directional lights; includes
 |	color, intensity, and direction editting. 
 |
 |   Classes: 	SoXtDirectionalLightEditor
 |
 |   Author(s): David Mott
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef _SO_XT_DIRECTIONAL_LIGHT_EDITOR_
#define _SO_XT_DIRECTIONAL_LIGHT_EDITOR_

#include <X11/Intrinsic.h>
#include <Xm/Xm.h>
#include <Inventor/SbBasic.h>
#include <Inventor/SbColor.h>
#include <Inventor/misc/SoCallbackList.h>
#include <Inventor/Xt/SoXtComponent.h>


class SoBase;
class SoCamera;
class SoDirectionalLight;
class SoDirectionalLightManip;
class SoDragger;
class SoGroup;
class SoNodeSensor;
class SoPath;
class SoPathList;
class SoPerspectiveCamera;
class SoSensor;
class SoSeparator;
class SoXtClipboard;
class _SoXtColorEditor;
class _SoXtColorSlider;
class SoXtRenderArea;


// callback function prototypes
typedef void SoXtDirectionalLightEditorCB(void *userData, const SoDirectionalLight *light);

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoXtDirectionalLightEditor
//
//////////////////////////////////////////////////////////////////////////////

class SoXtDirectionalLightEditor : public SoXtComponent {
  public:
    SoXtDirectionalLightEditor(
	Widget parent = NULL,
	const char *name = NULL, 
	SbBool buildInsideParent = TRUE);
   ~SoXtDirectionalLightEditor();

    // Edit a directional light node - 
    void		attach(SoPath *pathToLight);
    void		detach();
    SbBool		isAttached()	{ return (dirLight != NULL); }
    
    // Set new values in the light editor
    void    	    	setLight(const SoDirectionalLight &newLight);
    const SoDirectionalLight &getLight() const { return *dirLight; }
    
    //
    // Additional way of using the material editor, by registering a callback
    // and setting the material. At the time dictated by setUpdateFrequency
    // the callbacks will be called with the new material.
    //
    inline void		addLightChangedCallback(
				SoXtDirectionalLightEditorCB *f, 
				void *userData = NULL);
    inline void		removeLightChangedCallback(
				SoXtDirectionalLightEditorCB *f, 
				void *userData = NULL);

    // Redefined here since there are two windows to deal with -
    // the color editor and the light manipulator
    virtual void    	show();
    virtual void    	hide();

  protected:

    // This constructor takes a boolean whether to build the widget now.
    // Subclasses can pass FALSE, then call SoXtDirectionalLightEditor::buildWidget()
    // when they are ready for it to be built.
    SoEXTENDER
    SoXtDirectionalLightEditor(
	Widget parent,
	const char *name, 
	SbBool buildInsideParent, 
	SbBool buildNow);

    // redefine these
    virtual const char *    getDefaultWidgetName() const;
    virtual const char *    getDefaultTitle() const;
    virtual const char *    getDefaultIconTitle() const;
    
    SoDirectionalLight	*dirLight;  	    // light we are editing
    SoSeparator	    	*root;	    	    // root of local scene graph
    SoSeparator	    	*litStuff;    	    // what's on display under thelight

    SoPerspectiveCamera *myCamera;
    SoCamera            *cameraToWatch;
    
    // components, manips, sensors
    _SoXtColorEditor	*colorEditor;
    _SoXtColorSlider	*intensitySlider;
    SoXtRenderArea      *renderArea;    
    SoNodeSensor    	*lightSensor;
    SoNodeSensor    	*cameraSensor;
    SoDirectionalLightManip 	*dirLightManip;
    static char		*geomBuffer;
    SbBool  	    	ignoreCallback; // TRUE while callback should be ignored
    SoCallbackList	*callbackList;
    
    // Copy/paste support
    SoXtClipboard	*clipboard;
    
    // copy the src light values to the dst light values
    void		copyLight(SoDirectionalLight *dst, 
			    const SoDirectionalLight *src);
			    
    void    	    	updateLocalComponents();

  private:
    // Callback routines from components and manipulators
    static void		colorEditorCB(void *, const SbColor *);
    static void		intensitySliderCB(void *, float);
    static void	    	pasteDoneCB(void *, SoPathList *);
    static void		dirLightManipCB(void *, SoDragger *);

    // Callback routines from Xt/Motif
    static void	    	menuPick(Widget, int, XmAnyCallbackStruct *);
    
    // Sensor callbacks
    static void	    	cameraSensorCB(SoXtDirectionalLightEditor *, SoSensor *);
    static void	    	lightSensorCB(SoXtDirectionalLightEditor *, SoSensor *);

    // Build routines
    Widget		buildWidget(Widget parent);
    Widget   	    	buildPulldownMenu(Widget parent);

    static void visibilityChangeCB(void *pt, SbBool visible);
    void        activate();		// connects the sensor
    void        deactivate();		// disconnects the sensor
    
    // this is called by both constructors
    void constructorCommon(SbBool buildNow);
};

// Inline functions
void
SoXtDirectionalLightEditor::addLightChangedCallback(
    SoXtDirectionalLightEditorCB *f, 
    void *userData)
{ callbackList->addCallback((SoCallbackListCB *) f, userData); }

void
SoXtDirectionalLightEditor::removeLightChangedCallback(
    SoXtDirectionalLightEditorCB *f, 
    void *userData)
{ callbackList->removeCallback((SoCallbackListCB *) f, userData); }

#endif // _SO_XT_DIRECTIONAL_LIGHT_EDITOR_
