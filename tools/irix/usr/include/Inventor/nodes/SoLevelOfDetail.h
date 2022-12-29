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
 |   Description:
 |	This file defines the SoLevelOfDetail node class.
 |
 |   Author(s)		: Paul S. Strauss, Nick Thompson
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_LEVEL_OF_DETAIL_
#define  _SO_LEVEL_OF_DETAIL_

#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/nodes/SoGroup.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoLevelOfDetail
//
//  Level-of-detail group node. The children of this node typically
//  represent the same object or objects at varying levels of detail,
//  from highest detail to lowest. The size of the objects when
//  projected into the viewport is used to determine which version to
//  use (i.e., which child to traverse).
//
//  The size is computed as the area of the screen rectangle enclosing
//  the projection of the 3D bounding box that encloses all of the
//  children. When rendering, this size is compared to the values in
//  the screenArea field. If the size is greater than the first value,
//  child 0 is traversed. If it is smaller than the first, but greater
//  than the second, child 1 is traversed, and so on. If there are
//  fewer children than are required by this rule, the last child is
//  traversed. The screenArea field contains just 0 by default, so the
//  first child is always traversed.
//
//  The size calculation takes the current complexity into account. If
//  the complexity is 0 or is of type BOUNDING_BOX, the last child is
//  always traversed. If the complexity is less than .5, the computed
//  size is scaled down appropriately to use (possibly) a less
//  detailed representation. If the complexity is greater than .5, the
//  size is scaled up. At complexity 1, the first child is always used.
//
//  Picking and the callback action use the same traversal rules as
//  rendering. Bounding boxes are computed to enclose all children (as
//  is needed to compute the projected size). All other actions are
//  implemented as for SoGroup, except that SoLevelOfDetail
//  saves/restores state (like a separator) when applying any action.
//
//////////////////////////////////////////////////////////////////////////////

class SoLevelOfDetail : public SoGroup {

    SO_NODE_HEADER(SoLevelOfDetail);

  public:
    // Fields
    SoMFFloat		screenArea;	// Areas to use for comparison

    // Default constructor
    SoLevelOfDetail();

    // Constructor that takes approximate number of children
    SoLevelOfDetail(int nChildren);

  SoEXTENDER public:
    // Implement actions:
    virtual void	doAction(SoAction *action);
    virtual void	callback(SoCallbackAction *action);
    virtual void	GLRender(SoGLRenderAction *action);
    virtual void	rayPick(SoRayPickAction *action);

  SoINTERNAL public:
    static void		initClass();

  protected:
    virtual ~SoLevelOfDetail();

  private:
    // This action is used to compute the screen-space bbox
    static SoGetBoundingBoxAction	*bboxAction;
};

#endif /* _SO_LEVEL_OF_DETAIL_ */
