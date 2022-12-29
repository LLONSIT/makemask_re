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
 |   $Revision: 2.1 $
 |
 |   Description:
 |	This file contains the implementation of the
 |	SoComputeBoundingBox engine
 |
 |   Classes:
 |	SoComputeBoundingBox
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_COMPUTE_BOUNDING_BOX_
#define  _SO_COMPUTE_BOUNDING_BOX_

#include <Inventor/SbViewportRegion.h>
#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFPath.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/fields/SoSFVec3f.h>

class SoGetBoundingBoxAction;

/////////////////////////////////////////////////////////////////////////////
//
// Class: SoComputeBoundingBox
//
//  This engine has two input fields: "node" (SoSFNode) and "path"
//  (SoSFPath). By default, these fields contain NULL pointers. If the
//  "path" field is not NULL, this engine computes the bounding box
//  and center of the graph defined by the path, using an
//  SoGetBoundingBoxAction, and outputs the results. If the "path"
//  field is NULL but the "node" field isn't, it computes the bounding
//  box and center of the graph rooted by the node.
//
//  If both the node and the path are NULL, the outputs are disabled.
//
//  The "boxCenter" output is the center of the computed bounding box,
//  and the "objectCenter" output is the center defined by the objects
//  themselves, as returned by SoGetBoundingBoxAction::getCenter().
//
//  The engine uses a default viewport region when constructing the
//  SoGetBoundingBoxAction, so screen-based objects (such as 2D text)
//  may not be dealt with correctly. If this feature is needed, you
//  can call setViewportRegion() on an engine instance to set up the
//  correct viewport region to use.
//
/////////////////////////////////////////////////////////////////////////////

class SoComputeBoundingBox : public SoEngine {

    SO_ENGINE_HEADER(SoComputeBoundingBox);

  public:
    // Inputs:
    SoSFNode		node;		// Pointer to root node of graph
    SoSFPath		path;		// Pointer to path defining graph

    // Outputs:
    SoEngineOutput	min;		// (SoSFVec3f) Minimum point of bbox
    SoEngineOutput	max;		// (SoSFVec3f) Maximum point of bbox
    SoEngineOutput	boxCenter;	// (SoSFVec3f) Center point of bbox
    SoEngineOutput	objectCenter;	// (SoSFVec3f) Center of object(s)

    // Constructor
    SoComputeBoundingBox();

    // Sets/returns viewport region to use for bounding box computation
    void		   setViewportRegion(const SbViewportRegion &vpReg);
    const SbViewportRegion &getViewportRegion() const;

  SoINTERNAL public:
    static void			initClass();

  protected:
    // Indicates that an input has changed - we use this to determine
    // whether to use the node or path, or to disable output entirely
    virtual void		inputChanged(SoField *whichInput);

  private:
    // Pointer to SoGetBoundingBoxAction
    SoGetBoundingBoxAction	*bba;

    // Each of these is TRUE if the corresponding input pointer is non-NULL
    SbBool			gotNode;
    SbBool			gotPath;

    // Destructor
    virtual ~SoComputeBoundingBox();

    // Evaluation method
    virtual void	evaluate();
};

#endif  /* _SO_COMPUTE_BOUNDING_BOX_ */
