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
 |	Defines the abstract SoPickAction class
 |
 |   Author(s)		: Paul S. Strauss, Nick Thompson
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_PICK_ACTION_
#define  _SO_PICK_ACTION_

#include <Inventor/SbViewportRegion.h>
#include <Inventor/actions/SoSubAction.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoPickAction
//
//  Base class for picking actions.
//
//////////////////////////////////////////////////////////////////////////////

class SoPickAction : public SoAction {

    SO_ACTION_HEADER(SoPickAction);

  public:
    // Sets current viewport region to use for picking. Even though
    // picking may not involve a window per se, some nodes need this
    // information to determine their size and placement.
    void		setViewportRegion(const SbViewportRegion &newRegion);

    // Returns current viewport region
    const SbViewportRegion &getViewportRegion() const	{ return vpRegion; }

  SoEXTENDER public:
    // Setting this flag to FALSE disables any pick culling that might
    // take place (as in SoSeparators). This can be used for nodes
    // (such as SoArray and SoMultipleCopy) that traverse their
    // children multiple times in different locations, thereby
    // avoiding computing bounding boxes each time. (This problem is
    // very severe when each bounding box traversal also traverses the
    // children N times.) The default setting is TRUE.
    void		enableCulling(SbBool flag)	{ culling = flag; }
    SbBool		isCullingEnabled() const	{ return culling; }

  SoINTERNAL public:
    static void		initClass();

  protected:
    SbViewportRegion	vpRegion;	// Current viewport region

    // Constructor takes viewport region. See comments for the
    // setViewportRegion() method.
    SoPickAction(const SbViewportRegion &viewportRegion);

    // Destructor
    virtual ~SoPickAction();

    // Initiates action on graph
    virtual void	beginTraversal(SoNode *node);

  private:
    SbBool		culling;	// Pick culling enabled?
};

#endif /* _SO_PICK_ACTION_ */
