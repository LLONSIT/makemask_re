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
 |   Description:
 |	Component for editing materials. 
 |
 |   Classes	: SoXtMaterialEditor
 |
 |   Author(s)	: Alain Dumesny, David Mott
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef _SO_XT_MATERIAL_EDITOR_
#define _SO_XT_MATERIAL_EDITOR_

#include <X11/Intrinsic.h>
#include <Xm/Xm.h>
#include <Inventor/SbBasic.h>
#include <Inventor/misc/SoCallbackList.h>
#include <Inventor/Xt/SoXtComponent.h>

class SoBaseColor;
class SoXtClipboard;
class _SoXtColorEditor;
class SoNodeSensor;
class SoSensor;
class SoDirectionalLight;
class SoMaterial;
class SoXtMaterialList;
class SoPathList;
class SoXtRenderArea;
class SoSelection;
class _SoXtColorSlider;
class SoMFColor;
class SbColor;
class SoBase;
class SoSeparator;

// callback function prototypes
typedef void SoXtMaterialEditorCB(void *userData, const SoMaterial *mtl);

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoXtMaterialEditor
//
//  This editor lets you interactively edit a material
//
//////////////////////////////////////////////////////////////////////////////

class SoXtMaterialEditor : public SoXtComponent {
  public:
    // UpdateFrequency is how often new values should be sent
    // to the node or the callback routine.
    enum UpdateFrequency {
	CONTINUOUS,	// send updates with every mouse motion
	AFTER_ACCEPT 	// only send updates after user hits accept button
    };
    
    SoXtMaterialEditor(
	Widget parent = NULL,
	const char *name = NULL, 
	SbBool buildInsideParent = TRUE);
   ~SoXtMaterialEditor();
    
    // attach the editor to the given node and edits the material
    // of the given index (default is the first material)
    void		attach(SoMaterial *material, int index = 0);
    void		detach();
    SbBool		isAttached()	{ return (material != NULL); }
    
    //
    // Additional way of using the material editor, by registering a callback
    // and setting the material. At the time dictated by setUpdateFrequency
    // the callbacks will be called with the new material.
    //
    inline void		addMaterialChangedCallback(
				SoXtMaterialEditorCB *f, 
				void *userData = NULL);
    inline void		removeMaterialChangedCallback(
				SoXtMaterialEditorCB *f, 
				void *userData = NULL);
    
    //
    // Set/get the update frequency of when materialChanged callbacks should 
    // be called. (default CONTINUOUS).
    //
    void	setUpdateFrequency(SoXtMaterialEditor::UpdateFrequency freq);
    SoXtMaterialEditor::UpdateFrequency getUpdateFrequency()
						    { return updateFreq; }
    
    // Redefine these since there are multiple windows -
    // the color editor, directional light editor, and this component
    virtual void    	show();
    virtual void    	hide();
    
    // Set new values for the material editor, or get current values
    void    	    	setMaterial(const SoMaterial &mtl);
    const SoMaterial &	getMaterial() const { return *localMaterial; }
    
  protected:

    // This constructor takes a boolean whether to build the widget now.
    // Subclasses can pass FALSE, then call SoXtMaterialEditor::buildWidget()
    // when they are ready for it to be built.
    SoEXTENDER
    SoXtMaterialEditor(
	Widget parent,
	const char *name, 
	SbBool buildInsideParent, 
	SbBool buildNow);
    
    Widget		    buildWidget(Widget parent);
    
    // redefine these
    virtual const char *    getDefaultWidgetName() const;
    virtual const char *    getDefaultTitle() const;
    virtual const char *    getDefaultIconTitle() const;
    
  private:
    // attach vars
    SoMaterial		*material;  // material we are editing
    int			index;	    // material index number
    SoNodeSensor    	*sensor;
    SoCallbackList	*callbackList;
    Widget  	    	acceptButton, diamondButtons[4], radioButtons[4];
    SoXtMaterialEditor::UpdateFrequency	updateFreq;
    
    // widgets to edit the material
    Widget		mgrWidget;	// topmost widget
    _SoXtColorEditor	*colorEditor;
    _SoXtColorSlider	*sliders[6];
    SbBool              changedIt[6];
    SoXtMaterialList  	*materialList;
    SbBool  	    	ignoreCallback; // TRUE while callback should be ignored
    SbBool		openMaterialList;
    static void     	colorEditorCloseCB(void *, SoXtComponent *);
    static void     	materialListCloseCB(void *, SoXtComponent *);
    
    // copy/paste support
    SoXtClipboard	*clipboard;
    
    // local scene vars
    SoXtRenderArea    	*renderArea;
    SoMaterial		*localMaterial;	    // local copy of the material
    SoDirectionalLight	*light0;
    SoDirectionalLight	*light1;
    SoBaseColor	    	*tileColor;
    SoSeparator	    	*root;
    
    // keep the menu items around so we can update them before menu display
    Widget  	    	*menuItemsList;
    
    int32_t	    	activeColor;	    // field which color editor edits
    
    // update the sliders/colorEditor based on the local material
    void    	    	updateLocalComponents();
    
    // update the colorEditor based on the activeColor flag
    void    	    	updateColorEditor(SbBool updateTitle = FALSE);
    
    // update a color slider (amb/diff/spec/emiss) based of a material color
    // (split the base color from the intensity).
    void    	    	updateColorSlider(_SoXtColorSlider *, const float rgb[3]);
    
    // update a material field when a color slider changes.
    void    	    	updateMaterialColor(
    	    	    	    SoMFColor	*editMtlColor,
			    SoMFColor	*localMtlColor,
			    const float	*rgb,
			    float   	intensity);
    
    // copies mat2 onto mat1
    void    	    	copyMaterial(SoMaterial *mat1, int index1, 
				    const SoMaterial *mat2, int index2);
    
    // For each of the 6 sliders (or sets of sliders) sets the ignore flag of 
    // the material node being editted to FALSE if it has been changed.
    void		undoIgnoresIfChanged();
        
    // copy/paste support
    static void    	pasteDone(void *userData, SoPathList *pathList);

    // Callback routines from components
    static void	    	materialListCB(void *, const SoMaterial *);
    static void		colorEditorCB(void *, const SbColor *);
    static void		ambientSliderCB(void *, float);
    static void		diffuseSliderCB(void *, float);
    static void		specularSliderCB(void *, float);
    static void		emissiveSliderCB(void *, float);
    static void		shininessSliderCB(void *, float);
    static void		transparencySliderCB(void *, float);
    
    // Callback routines from Xt/Motif
    static void	    	menuPick(Widget, int, XmAnyCallbackStruct *);
    static void	    	menuDisplay(Widget, SoXtMaterialEditor *, XtPointer);
    static void	    	radioButtonPick(Widget, int, XtPointer);
    static void	    	diamondButtonPick(Widget, int, XtPointer);
    static void     	acceptButtonCB(Widget, SoXtMaterialEditor *, XtPointer);
    
    // Sensor callbacks
    static void	    	sensorCB(void *, SoSensor *);

    // Build routines
    Widget   	    	buildPulldownMenu(Widget parent);
    Widget  	    	buildControls(Widget parent);
    Widget  	    	buildSlidersForm(Widget parent);
    
    static void visibilityChangeCB(void *pt, SbBool visible);
    void        activate();		// connects the sensor
    void        deactivate();		// disconnects the sensor

    // this is called by both constructors
    void constructorCommon(SbBool buildNow);
};


// Inline functions
void
SoXtMaterialEditor::addMaterialChangedCallback(
    SoXtMaterialEditorCB *f, 
    void *userData)
{ callbackList->addCallback((SoCallbackListCB *) f, userData); }

void
SoXtMaterialEditor::removeMaterialChangedCallback(
    SoXtMaterialEditorCB *f, 
    void *userData)
{ callbackList->removeCallback((SoCallbackListCB *) f, userData); }

#endif // _SO_XT_MATERIAL_EDITOR_


