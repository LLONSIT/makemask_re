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
 |	This file defines the SoGroup node class.
 |
 |   Author(s)		: Paul S. Strauss, Nick Thompson
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_GROUP_
#define  _SO_GROUP_

class SoChildList;
#include <Inventor/nodes/SoSubNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoGroup
//
//  Base group node: all children are traversed.
//
//////////////////////////////////////////////////////////////////////////////

class SoGroup : public SoNode {

    SO_NODE_HEADER(SoGroup);

  public:
    // Default constructor
    SoGroup();

    // Constructor that takes approximate number of children
    SoGroup(int nChildren);

    // Adds a child as last one in group
    void		addChild(SoNode *child);

    // Adds a child so that it becomes the one with the given index
    void		insertChild(SoNode *child, int newChildIndex);

    // Returns pointer to nth child node
    SoNode *		getChild(int index) const;

    // Finds index of given child within group
    int			findChild(const SoNode *child) const;

    // Returns number of children
    int			getNumChildren() const;

    // Removes child with given index from group
    void		removeChild(int index);

    // Removes first instance of given child from group
    void		removeChild(SoNode *child)
	{ removeChild(findChild(child)); }

    // Removes all children from group
    void		removeAllChildren();

    // Replaces child with given index with new child
    void		replaceChild(int index, SoNode *newChild);

    // Replaces first instance of given child with new child
    void		replaceChild(SoNode *oldChild, SoNode *newChild)
	{ replaceChild(findChild(oldChild), newChild); }

  SoEXTENDER public:
    // Implement actions
    virtual void	doAction(SoAction *action);
    virtual void	callback(SoCallbackAction *action);
    virtual void	GLRender(SoGLRenderAction *action);
    virtual void	getBoundingBox(SoGetBoundingBoxAction *action);
    virtual void	getMatrix(SoGetMatrixAction *action);
    virtual void	handleEvent(SoHandleEventAction *action);
    virtual void	pick(SoPickAction *action);
    virtual void	search(SoSearchAction *action);
    virtual void	write(SoWriteAction *action);

  SoINTERNAL public:
    static void		initClass();

    // Returns pointer to children
    virtual SoChildList *getChildren() const;

  protected:
    SoChildList		*children;

    // Reads stuff into instance of SoGroup. Returns FALSE on error
    virtual SbBool	readInstance(SoInput *in, unsigned short flags);

    // Reads just the children into instance of SoGroup. Returns FALSE on error
    virtual SbBool	readChildren(SoInput *in);

    virtual ~SoGroup();

    // Copies the contents of the given node into this instance
    virtual void	copyContents(const SoFieldContainer *fromFC,
				     SbBool copyConnections);
};

#endif /* _SO_GROUP_ */
