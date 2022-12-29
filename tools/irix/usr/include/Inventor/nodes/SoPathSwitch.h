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
 |	This file defines the SoPathSwitch node class.
 |
 |   Author(s)		: Paul S. Strauss, Nick Thompson
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_PATH_SWITCH_
#define  _SO_PATH_SWITCH_

#include <Inventor/fields/SoSFPath.h>
#include <Inventor/nodes/SoGroup.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoPathSwitch
//
//  PathSwitch group node: traverses all children only if the path
//  traversed so far matches the one stored in the "path" field. A
//  successful match means that the N nodes in the stored path chain
//  are the same as the last N nodes in the current path, not
//  including the path switch node itself. A NULL path (the default)
//  means don't traverse the children.
//
//////////////////////////////////////////////////////////////////////////////

class SoPathSwitch : public SoGroup {

    SO_NODE_HEADER(SoPathSwitch);

  public:
    // Fields
    SoSFPath		path;		// Path to match

    // Default constructor
    SoPathSwitch();

    // Constructor that takes approximate number of children
    SoPathSwitch(int nChildren);

  SoEXTENDER public:
    // Implement actions
    virtual void	doAction(SoAction *action);
    virtual void	GLRender(SoGLRenderAction *action);
    virtual void	pick(SoPickAction *action);
    virtual void	getBoundingBox(SoGetBoundingBoxAction *action);
    virtual void	handleEvent(SoHandleEventAction *action);
    virtual void	getMatrix(SoGetMatrixAction *action);
    virtual void	search(SoSearchAction *action);

  SoINTERNAL public:
    static void		initClass();

  protected:
    virtual ~SoPathSwitch();

  private:

    // Checks for match of path with current path
    SbBool		matchesPath(const SoPath *switchPath,
				    const SoPath *currentPath) const;
};

#endif /* _SO_PATH_SWITCH_ */
