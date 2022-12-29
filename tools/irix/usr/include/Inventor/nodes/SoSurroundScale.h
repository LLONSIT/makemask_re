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
 |   Description:
 |	This file defines the SoSurroundScale node class.
 |
 |   Author(s)		: Paul Isaacs
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_SURROUND_SCALE_
#define  _SO_SURROUND_SCALE_

#include <Inventor/fields/SoFieldData.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/nodes/SoTransformation.h>
#include <Inventor/fields/SoSFInt32.h>

class SoFullPath;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoSurroundScale
//
//  Appends a transform to the localMatrix so that a default size  cube will 
//  surround the objects specified by its fields.
//
//  To determine what to surround, the node looks at the current path in
//  the action.  An SoGetBoundingBoxAction is applied to the node that is
//  'numNodesUpToContainer' nodes above this node in the path.
//  The action will be told to reset the bounding box upon traversal of the
//  node that is 'numNodesUpToReset' nodes above this node in the path.
//
//  For example, when a trackballManip wants to surround the objects it
//  is going to move, the scene graph will look something like this:
//
//               Separator
//                |
//     -------------------------
//     |                       |
//   trackballManip       subGraphOfObjectsThatWilMove
//     |
//    trackballDragger
//     |
//    topSeparator(top part within of the dragger)
//     |
//    -----------------------------------
//    |            |                    |
//  motionMatrix  surroundScale     parts of the dragger.
//
//   The manip will set the fields on the surround scale node to be:
//   numNodesUpToContainer = 4;
//   numNodesUpToReset = 3;
//
//  The action will therefore be applied to the Separator, and will be
//  reset after traversing the trackballManip.
//  So the surroundScale will surround the objects below 'separator' and
//  not including 'trackballManip,' producing the desired effect.
//
//  Note that, therefore, designers of draggers and manipulators which use
//  this node should base their models on default size cubes (2 by 2 by 2).
//
//////////////////////////////////////////////////////////////////////////////

class SoSurroundScale : public SoTransformation {

    SO_NODE_HEADER(SoSurroundScale);

  public:

    // Constructor
    SoSurroundScale();

    // Fields
    SoSFInt32		numNodesUpToContainer;
    SoSFInt32		numNodesUpToReset;

    // If you call this, then next time through the node will re-calculate
    // it's cached matrix, translation and scale values.
    void invalidate();

  SoEXTENDER public:
    // Called by actions that need to change the state with a new matrix.
    void		doAction(SoAction *action);

    void setDoingTranslations( SbBool doEm ) { doTranslations = doEm; }
    SbBool isDoingTranslations() { return doTranslations; }

  SoINTERNAL public:
    static void		initClass();

  protected:

    virtual void	callback(SoCallbackAction *action);
    virtual void	GLRender(SoGLRenderAction *action);
    virtual void	getBoundingBox(SoGetBoundingBoxAction *action);
    virtual void	getMatrix(SoGetMatrixAction *action);
    virtual void	pick(SoPickAction *action);

    void updateMySurroundParams( SoAction *action, const SbMatrix &inv);

    void setIgnoreInBbox( SbBool newVal ) { ignoreInBbox = newVal; }
    SbBool isIgnoreInBbox() { return ignoreInBbox; }

    SbVec3f    cachedScale;
    SbVec3f    cachedInvScale;
    SbVec3f    cachedTranslation;
    SbBool     cacheOK;

    SbBool doTranslations;

    virtual ~SoSurroundScale();

  private:
    SbBool ignoreInBbox;
};

#endif /* _SO_SURROUND_SCALE_ */
