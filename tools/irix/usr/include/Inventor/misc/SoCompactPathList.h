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
 |	This file contains the definition of the SoCompactPathList class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */


#ifndef  _SO_COMPACT_PATH_LIST_
#define  _SO_COMPACT_PATH_LIST_

#include <Inventor/SoLists.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoCompactPathList (internal)
//
//  This class represents a list of paths (like an SoPathList) in a
//  more compact form. Since many paths in a path list may share
//  common sub-paths from common head nodes, this class stores them
//  with less redundancy.
//
//  The SoCompactPathList constructor is passed an SoPathList. It is
//  assumed that the SoPathList is not empty and that all paths in the
//  SoPathList have a common head node; an error will occur otherwise.
//  It is also assumed that no two paths are identical, and that if
//  one path goes through node X, then no other path will end at node
//  X.
//
//  While an SoPathList provides random access to any node in any
//  path, an SoCompactPathList provides only sequential access. That
//  is, you can only access the paths in the list in order. Each
//  instance maintains the notion of the "current node" - the node
//  that traversal has last reached - to support this access.
//
//////////////////////////////////////////////////////////////////////////////

SoINTERNAL class SoCompactPathList {

  public:
    // Constructor given path list
    SoCompactPathList(const SoPathList &list);
    ~SoCompactPathList();

    // Resets traversal to the beginning. This allows an instance to
    // be traversed more than once.
    void		reset();

    // Returns the indices of the current node that are in paths in
    // the list. The number of indices is returned in "numIndices",
    // and the indices are returned in "indices". numIndices will be 0
    // if the current node has no children in any path.
    void		getChildren(int &numIndices, const int *&indices);

    // Traverses the child with given index of the current node. The
    // child becomes the new current node. If the child is on a path
    // in the list, then getChildren() can be called to get the next
    // set of children. Otherwise, it will always return no children.
    // This method returns TRUE if the given childIndex is in one of
    // the paths in the list, and FALSE otherwise.
    SbBool		push(int childIndex);

    // Restores current node to what it was before the most recent push()
    void		pop();

  private:
    int			*array;		// Path list as a series of integers
    int			curNode;	// Index of current node in array
    int			*stack;		// Current traversal stack of indices
    int			stackDepth;	// Depth of stack

    // Returns number of path child indices of current node
    int			getNumIndices()	{ return array[curNode]; }

    // Returns index in array of first child index of current node
    int			getStartIndex()	{ return curNode + 1; }

    // Returns index in array of i'th on-path child of current node
    int			getChild(int i)
	{ return array[getStartIndex() + getNumIndices() + i]; }

    // Pushes curNode on stack
    void		pushCurNode()	{ stack[stackDepth++] = curNode; }

    // Pops stack, setting curNode to resulting top node
    void		popCurNode()	{ curNode = stack[--stackDepth - 1]; }

    // Computes number of array indices needed to store stuff
    int			computeArraySize(const SoPathList &list);

    // Stores the paths in a compact form, recursively
    int			compactPaths(int curSlot, int depth,
				     const SoPathList &list,
				     int firstPath, int numPaths);
};

#endif /* _SO_COMPACT_PATH_LIST_ */
