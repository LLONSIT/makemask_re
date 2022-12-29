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
|      Defines the SoXtSliderSet Component class, a base class for the
|          SoXtTransformSliderSet
|          SoXtMaterialSliderSet
|      and SoXtLightSliderSet
|
|   Author(s)          : Paul Isaacs
|
______________  S I L I C O N   G R A P H I C S   I N C .  ____________
_______________________________________________________________________
*/


#ifndef _SO_XT_SLIDER_SET_
#define _SO_XT_SLIDER_SET_

#include <Inventor/Xt/SoXtSliderSetBase.h>

#define SLIDER_SET_DEFAULT_BORDER_WIDTH 3

///////////////////////////////////////////////////////////////////////
//
// class: SoXtSliderSet
//
///////////////////////////////////////////////////////////////////////

class SoXtSliderSet : public SoXtSliderSetBase {
  public:
  // internal:
      void updateLayout();        // Called after button presses that may
				  // cause the size or layout of the SoXtSliderSet 
				  // to be altered.
				  
  protected:
    SoXtSliderSet(
	Widget parent,
	const char *name, 
	SbBool buildInsideParent,
	SoNode *newEditNode);
      ~SoXtSliderSet();
      Widget _parentShellWidget;  // since this class can resize itself when
				  // buttons are pressed, it needs to know
				  // about its parent shell, so that it
				  // query and change the size.
};

#endif // _SO_XT_SLIDER_SET_
