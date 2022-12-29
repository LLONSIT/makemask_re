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
 |	Component which displays a list of materials. 
 |
 |   Classes: 	SoXtMaterialList
 |
 |   Author(s): David Mott
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef _SO_XT_MATERIAL_LIST_H_
#define _SO_XT_MATERIAL_LIST_H_

#include <X11/Intrinsic.h>
#include <Inventor/SbBasic.h>
#include <Inventor/misc/SoCallbackList.h>
#include <Inventor/Xt/SoXtComponent.h>
#include <Inventor/nodes/SoMaterial.h>

// callback function prototypes
typedef void SoXtMaterialListCB(void *userData, const SoMaterial *mtl);

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoXtMaterialList
//
//
//////////////////////////////////////////////////////////////////////////////

class SoXtMaterialList : public SoXtComponent {
  public:
    // pass the home directory of the material palettes as dir
    SoXtMaterialList(
	Widget parent = NULL,
	const char *name = NULL, 
	SbBool buildInsideParent = TRUE, 
	const char *dir = NULL);
   ~SoXtMaterialList();

    // Callbacks - register functions that will be called whenever the user
    // chooses a new material from the list.
    // (This component cannot be attached to a database - it is read only)
    void    addCallback(
    	    	SoXtMaterialListCB *f,
		void *userData = NULL)
	{ callbackList->addCallback((SoCallbackListCB *) f, userData);}

    void    removeCallback(
    	    	SoXtMaterialListCB *f,
		void *userData = NULL)
	{ callbackList->removeCallback((SoCallbackListCB *) f, userData); }
    
  protected:

    // This constructor takes a boolean whether to build the widget now.
    // Subclasses can pass FALSE, then call SoXtMaterialList::buildWidget()
    // when they are ready for it to be built.
    SoEXTENDER
    SoXtMaterialList(
	Widget parent,
	const char *name, 
	SbBool buildInsideParent, 
	const char *dir, 
	SbBool buildNow);
    
    // redefine these
    virtual const char *    getDefaultWidgetName() const;
    virtual const char *    getDefaultTitle() const;
    virtual const char *    getDefaultIconTitle() const;
    
    // Build routines
    Widget		buildWidget(Widget parent);
    Widget   	    	buildPulldownMenu(Widget parent);
    
  private:
    char    	    	*materialDir;	// the parent directory of materials
    SoCallbackList  	*callbackList;	// funcs to invoke when a mtl is picked
    SbPList 	    	menuItems;  	// Widgets
    SbPList 	    	mtlPalettes;	// list of palettes
    SbPList 	    	palette;    	// the current palette
    int	    	    	curPalette; 	// index into mtlPalettes
    Widget  	    	mtlList;	// the Motif list of materials

    // Fill up the mtlList with a new palette
    void    	    	fillInMaterialList();
    SbBool		setupPalettes();

    // Callback routines from Xt/Motif
    static void	    	menuPick(Widget, int, XtPointer);
    static void	    	listPick(Widget, SoXtMaterialList *, XtPointer);

    // this is called by both constructors
    void constructorCommon(const char *dir, SbBool buildNow);
};

#endif // _SO_XT_MATERIAL_LIST_H_
