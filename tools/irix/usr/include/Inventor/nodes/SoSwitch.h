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
 |   $Revision: 2.4 $
 |
 |   Description:
 |	This file defines the SoSwitch node class.
 |
 |   Author(s)		: Paul S. Strauss, Nick Thompson
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_SWITCH_
#define  _SO_SWITCH_

#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/nodes/SoGroup.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoSwitch
//
//  Switch group node: traverses only the child indicated by integer
//  "whichChild" field. If this field is SO_SWITCH_NONE, no children
//  are traversed, while SO_SWITCH_INHERIT means inherit the index
//  from the current switch state, doing a modulo operation to make
//  sure the child index is within the correct bounds of the switch
//  node.
//
//////////////////////////////////////////////////////////////////////////////

#define SO_SWITCH_NONE		(-1)	/* Don't traverse any children	*/
#define SO_SWITCH_INHERIT	(-2)	/* Inherit value from state	*/
#define SO_SWITCH_ALL		(-3)	/* Traverse all children	*/

class SoSwitch : public SoGroup {

    SO_NODE_HEADER(SoSwitch);

  public:
    // Fields
    SoSFInt32		whichChild;	// Child to traverse

    // Default constructor
    SoSwitch();

    // Constructor that takes approximate number of children
    SoSwitch(int nChildren);

    // Overrides method in SoNode to return FALSE if there is no
    // selected child or the selected child does not affect the state.
    virtual SbBool	affectsState() const;

  SoEXTENDER public:
    // Implement actions
    virtual void	doAction(SoAction *action);
    virtual void	callback(SoCallbackAction *action);
    virtual void	GLRender(SoGLRenderAction *action);
    virtual void	pick(SoPickAction *action);
    virtual void	getBoundingBox(SoGetBoundingBoxAction *action);
    virtual void	handleEvent(SoHandleEventAction *action);
    virtual void	getMatrix(SoGetMatrixAction *action);
    virtual void	search(SoSearchAction *action);
    virtual void	write(SoWriteAction *action);

  SoINTERNAL public:
    static void		initClass();

  protected:
    // Generic traversal of children
    void		traverseChildren(SoAction *action);

    virtual ~SoSwitch();

  private:
    // Traverses correct child. If matchIndex >=0, child index must match
    void		doChild(SoAction *action, int matchIndex = -1);
};

#endif /* _SO_SWITCH_ */
