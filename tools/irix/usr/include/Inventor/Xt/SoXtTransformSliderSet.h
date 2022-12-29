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
* Copyright (C) 1990-93   Silicon Graphics, Inc.
*
_______________________________________________________________________
______________  S I L I C O N   G R A P H I C S   I N C .  ____________
|
|   $Revision: 2.0 $
|
|   Description:
|      Defines SoXtTransformSliderSet, a subclass of SoXtSliderSet
|      The SoXtTransformSliderSet is used to manipulate the fields of 
|      a SoXtTransform node using an arrangement of motif sliders and buttons.
|
|   Author(s)          : Paul Isaacs
|
______________  S I L I C O N   G R A P H I C S   I N C .  ____________
_______________________________________________________________________
*/



#ifndef _SO_XT_TRANSFORM_SLIDER_SET_
#define _SO_XT_TRANSFORM_SLIDER_SET_

#include <Inventor/Xt/SoXtSliderSet.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoXtTransformSliderSet
//
//  For editing transformation nodes.
//
//  The SoXtTransformSliderSet allocates:
//     1 SoXtTransSliderModule       (for editing translation)
//     1 SoXtScaleSliderModule       (for editing scaling)
//     1 SoXtRotateSliderModule      (for editing rotation)
//     1 SoXtCenterSliderModule      (for editing center of rotation and scale)
//
//////////////////////////////////////////////////////////////////////////////

class SoXtTransformSliderSet : public SoXtSliderSet {
  public:
    SoXtTransformSliderSet( 
	Widget parent = NULL,
	const char *name = NULL, 
	SbBool buildInsideParent = TRUE,
	SoNode *newEditNode = NULL );
    ~SoXtTransformSliderSet();
  
  protected:

    // This constructor takes a boolean whether to build the widget now.
    // Subclasses can pass FALSE, then call the buildWidget() method on
    // this class when they are ready for it to be built.
    SoEXTENDER
    SoXtTransformSliderSet(
	Widget parent,
	const char *name, 
	SbBool buildInsideParent, 
	SoNode *newEditNode,
	SbBool buildNow);
    
    // redefine these
    virtual const char *    getDefaultWidgetName() const;
    virtual const char *    getDefaultTitle() const;
    virtual const char *    getDefaultIconTitle() const;
    
    Widget  	buildWidget( Widget parent);
  
    // this is called by both constructors
    void constructorCommon(SbBool buildNow);
};

#endif // _SO_XT_TRANSFORM_SLIDER_SET_
