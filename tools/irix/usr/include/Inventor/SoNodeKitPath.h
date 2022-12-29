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
 |   $Revision: 2.2 $
 |
 |   Description:
 |	This file contains the definition of the SoNodeKitPath class
 |
 |   Author(s)		: Paul Isaacs, Paul S. Strauss, Nick Thompson
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_NODE_KIT_PATH_
#define  _SO_NODE_KIT_PATH_

#include <Inventor/SoPath.h>

class SoBaseKit;
class SoSearchAction;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoNodeKitPath
//
//  A SoNodeKitPath represents a scene graph or subgraph. It contains
//  pointers to a chain of nodeKitss, each of which is a child of the
//  previous. 
//  
//  Intermediary nodes between nodeKits are not included in the nodeKit path.
//
//  
//////////////////////////////////////////////////////////////////////////////

class SoNodeKitPath : public SoPath {

  public:

    // Returns length of path chain (number of nodes)
    int			getLength() const;

    // Returns the last nodeKit in a path chain.
    SoNode *		getTail() const;

    // Returns pointer to ith nodeKit in chain
    SoNode *		getNode(int i) const;

    // Returns pointer to ith node from the tail in chain
    // i.e. index 0 == tail, index 1 == 1 before tail, 2 == 2 before tail
    SoNode *		getNodeFromTail(int i) const;

    // Removes all nodes from indexed nodeKit on
    void		truncate(int start);

    // Allows path to be treated as a stack: pop the last nodeKit
    void		pop();

    // Adds nodeKit to end of chain; uses first occurrance of nodeKit as
    // part of current last nodekit. If path is empty, this is 
    // equivalent to setHead().
    void		append(SoBaseKit *childKit);

    // Adds all nodeKits in path to end of chain; head node of fromPath must
    // be a part of current last node
    void		append(const SoNodeKitPath *fromPath);

    // Returns TRUE if the passed nodeKit is in the path chain
    SbBool		containsNode(SoBaseKit *node) const;
    
    // If the paths have different head nodes, this returns -1.
    // Otherwise, it returns the index into the chain of the last nodeKit
    // (starting at the head) that is the same for both paths.
    int			findFork(const SoNodeKitPath *path) const;

    // Comparison operator: returns TRUE if all nodes on the nodekit path
    // are equal
    friend int operator ==(const SoNodeKitPath &p1, const SoNodeKitPath &p2);

  protected:
    // Hide the constructor
    SoNodeKitPath(int approxLength) : SoPath(approxLength)	{}
    // Destructor
    virtual ~SoNodeKitPath();

  private:
    // This action is used to search for nodes.
    static SoSearchAction *searchAction;

    // Hide these methods. They make no sense for a SoNodeKitPath.

    // The methods that take an index or a node are replaced by
    // methods that take a nodekit argument.
    void		append(int childIndex);
    void		append(SoNode *childNode);
    void		append(const SoPath *fromPath);
    void		push(int childIndex);
    int			getIndex(int i) const;
    int			getIndexFromTail(int i) const;
    void                insertIndex(SoNode *parent,int newIndex);
    void                removeIndex(SoNode *parent,int oldIndex);
    void                replaceIndex(SoNode *parent,int index,SoNode *newChild);
};

#endif /* _SO_NODE_KIT_PATH_ */
