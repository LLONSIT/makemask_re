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
|      Defines the SoXtSliderSetBase class
|      This is the base class for the SoXtSliderSet and for the
|      smaller components of which it is composed. (Such as the compound
|      sliderTool and the combined groups of sliderTools that make up 
|      each subPanel of an editor
|      
|
|   Author(s)          : Paul Isaacs
|
______________  S I L I C O N   G R A P H I C S   I N C .  ____________
_______________________________________________________________________
*/


#ifndef _SO_XT_SLIDER_SET_BASE_
#define _SO_XT_SLIDER_SET_BASE_

#include <Inventor/Xt/SoXtComponent.h>
#include <Inventor/nodes/SoNode.h>

///////////////////////////////////////////////////////////////////////
//
// class: SoXtSliderSetBase
//
///////////////////////////////////////////////////////////////////////

class SoXtSliderSetBase : public SoXtComponent {
  public:
      virtual void setNode( SoNode *newNode );

      SoNode * getNode() const { return _editNode; }
  // internal:
      virtual void getLayoutSize( int &w, int &h );

      virtual void show();
      
  protected:
      Widget	      widget;//??? huh? why not SoXtComponent::widget?

      int             _layoutWidth;
      int             _layoutHeight;
      SoNode          *_editNode;
      int             _numSubComponents;
      SoXtSliderSetBase **_subComponentArray;
      SoXtSliderSetBase(
	Widget parent = NULL,
	const char *name = NULL, 
	SbBool buildInsideParent = TRUE,
	SoNode *newEditNode = NULL);
      ~SoXtSliderSetBase();
};

#endif // _SO_XT_SLIDER_SET_BASE_
