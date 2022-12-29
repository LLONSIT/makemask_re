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
 |	This file contains the definition of the extender SoChildList
 |	class.
 |	  
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef _SO_CHILD_LIST_
#define _SO_CHILD_LIST_

#include <Inventor/SoLists.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoChildList
//
//  This class maintains a list of child nodes for any node. It allows
//  children to be added, removed, replaced, and accessed. The SoGroup
//  class has an instance of this class and provides public methods
//  for dealing with children. Other classes can also have an instance
//  of this class and may choose to publicize whatever methods they
//  wish for dealing with them. The SoNode::getChildren() method
//  returns the child list for any node class.
//
//  SoChildList automatically maintains the auditor list for parent
//  nodes. That is, when a child is added to the list, the parent node
//  is automatically added as a parent auditor of the child. To make
//  this possible, the parent node must be passed in to the
//  constructors of the SoChildList class.
//
//////////////////////////////////////////////////////////////////////////////

class SoAction;

SoEXTENDER class SoChildList : public SoNodeList {

  public:
    // Constructors and destructor.
    SoChildList(SoNode *parentNode);
    SoChildList(SoNode *parentNode, int size);
    SoChildList(SoNode *parentNode, const SoChildList &l);
    ~SoChildList();

    // All of these override the standard SoBaseList methods so they
    // can maintain auditors correctly.
    void		append(SoNode * child);
    void		insert(SoNode *child, int addBefore);
    void		remove(int which);
    void		truncate(int start);
    void		copy(const SoChildList &l);
    void		set(int i, SoNode *child);

    // Traverses all children to apply action. Stops if action's
    // termination condition is reached
    void		traverse(SoAction *action)
	{ traverse(action, 0, getLength() - 1); }

    // Traverses just one child
    void		traverse(SoAction *action, int childIndex)
	{ traverse(action, childIndex, childIndex); }

    // Traverses all children between two indices, inclusive. Stops if
    // action's termination condition is reached.
    void		traverse(SoAction *action,
				 int firstChild, int lastChild);

  SoINTERNAL public:
    // SoPath calls these to be notified of changes in scene graph
    // topology:
    void addPathAuditor(SoPath *p) { auditors.append(p); }
    void removePathAuditor(SoPath *p) 
		{ auditors.remove(auditors.find(p)); }

  private:
    SoNode		*parent;
    // This is a PList and not a PathList because PathList ref()s the
    // paths it contains, and that screws up Path reference counting.
    SbPList		auditors;
};

#endif /* _SO_CHILD_LIST_ */
