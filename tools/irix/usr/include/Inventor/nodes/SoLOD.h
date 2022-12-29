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
 |   Description:
 |	This file defines the SoLOD node class.
 |
 |   Author(s)		: Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_LOD_
#define  _SO_LOD_

#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/nodes/SoGroup.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoLOD
//
//  Level-of-detail group node. The children of this node typically
//  represent the same object or objects at varying levels of detail,
//  from highest detail to lowest.  The world-space distance of the
//  eye from the transformed center of the LOD is computed, and one
//  child is drawn, based on the values in the ranges field.
//
//  More precisely, if the distance from the eyepoint to the
//  transformed center is D and the ranges array contains LAST_RANGE+1
//  values (numbered 0...LAST_RANGE), then:
//
//  D < ranges[0]  : Child 0 is drawn
//  ranges[i-1] < D < ranges[i] : Child i is drawn
//  D > ranges[LAST_RANGE] : Child LAST_RANGE+1 is drawn
//
//  So, you should specify N ranges and N+1 children.  If you specify
//  too few children, the last child will be used for the extra
//  ranges.  If you specify too few ranges, the extra children will
//  never be used.
//
//  Add an SoInfo node as a child if you want a level of detail
//  that doesn't draw anything.
//
//////////////////////////////////////////////////////////////////////////////

class SoLOD : public SoGroup {

    SO_NODE_HEADER(SoLOD);

  public:
    // Fields
    SoMFFloat		range;	// World-space distances
    SoSFVec3f		center; // Center for computation

    // Default constructor
    SoLOD();

    // Constructor that takes approximate number of children
    SoLOD(int nChildren);

  SoEXTENDER public:
    // Implement actions:
    virtual void	doAction(SoAction *action);
    virtual void	callback(SoCallbackAction *action);
    virtual void	GLRender(SoGLRenderAction *action);
    virtual void	rayPick(SoRayPickAction *action);
    virtual void	getBoundingBox(SoGetBoundingBoxAction *action);

    // These methods make render traversal faster by implementing
    // different rendering paths corresponding to different action
    // path codes.
    virtual void	GLRenderBelowPath(SoGLRenderAction *action);
    virtual void	GLRenderInPath(SoGLRenderAction *action);
    virtual void	GLRenderOffPath(SoGLRenderAction *action);

  SoINTERNAL public:
    static void		initClass();

  protected:
    virtual ~SoLOD();

    virtual int		whichToTraverse(SoAction *);
};

#endif /* _SO_LOD_ */
