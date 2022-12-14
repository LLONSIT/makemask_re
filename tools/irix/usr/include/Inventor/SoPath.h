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
 |   $Revision: 2.5 $
 |
 |   Description:
 |	This file contains the definition of the SoPath and SoFullPath
 |	classes, and the related class SoLightPath
 |
 |   Author(s)		: Paul S. Strauss, Nick Thompson, Alan Norton
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_PATH_
#define  _SO_PATH_

#include <Inventor/misc/SoBase.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/SoLists.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoPath
//
//  A SoPath represents a scene graph or subgraph. It contains
//  pointers to a chain of nodes, each of which is a child of the
//  previous. The child index of each node is also stored, to
//  disambiguate cases where a node appears more than once as a child
//  of the same group.
//
//  The graph defined by the path consists of all of the nodes in the
//  path, all nodes below the last node in the chain, and any other
//  nodes that have an effect on these nodes.
//
//////////////////////////////////////////////////////////////////////////////

class SoPathList;
class SoWriteAction;

class SoPath : public SoBase {

  public:

    // Default constructor
    SoPath();

    // Constructor given approximate number of nodes in chain
    SoPath(int approxLength);

    // Constructor given head node to insert in path
    SoPath(SoNode *node);

    // Sets head node (first node in chain)
    void		setHead(SoNode *node);

    // Adds node to end of chain; node is nth child of current last node
    void		append(int childIndex);

    // Adds node to end of chain; uses first occurrance of node as
    // child of current last node. If path is empty, this is
    // equivalent to setHead().
    void		append(SoNode *childNode);

    // Adds all nodes in path to end of chain; head node of fromPath must
    // be the same as or a child of current last node
    void		append(const SoPath *fromPath);

    // Allows path to be treated as a stack: push a node at the end of
    // the chain and pop the last node off
    void		push(int childIndex) { append(childIndex); }
    void		pop()		     { truncate(getFullLength() - 1); }

    // Returns the first/last node in a path chain.
    SoNode *		getHead() const	{ return nodes[0]; }
    SoNode *		getTail() const	{ return (nodes[getLength() - 1]); }

    // Returns pointer to ith node in chain
    SoNode *		getNode(int i) const	{ return (nodes[i]); }

    // Returns pointer to ith node from the tail in chain
    // i.e. index 0 == tail, index 1 == 1 before tail, 2 == 2 before tail
    SoNode *		getNodeFromTail(int i) const
	{ return (nodes[getLength() - 1 - i]); }

    // Returns index of ith node in chain
    int			getIndex(int i) const	{ return (indices[i]); }

    // Returns index of ith node in chain
    int			getIndexFromTail(int i) const
	{ return (indices[getLength() - 1 - i]); }

    // Returns length of path chain (number of nodes)
    int			getLength() const;

    // Removes all nodes from indexed node on
    void		truncate(int start);

    // Returns TRUE if the passed node is in the path chain
    SbBool		containsNode(const SoNode *node) const;
    
    // Returns TRUE if the nodes in the chain in the passed path are
    // contained (in consecutive order) in this path chain
    SbBool		containsPath(const SoPath *path) const;
    
    // If the paths have different head nodes, this returns -1.
    // Otherwise, it returns the index into the chain of the last node
    // (starting at the head) that is the same for both paths.
    int			findFork(const SoPath *path) const;

    // Creates and returns a new path that is a copy of some or all of
    // this path. Copying starts at the given index (default is 0,
    // which is the head node). numNodes = 0 (the default) means copy
    // all nodes from the starting index to the end. Returns NULL on
    // error.
    SoPath *		copy(int startFromNodeIndex = 0,
			     int numNodes = 0) const;

    // Comparison operator: returns TRUE if all nodes in paths are identical
    friend int		operator ==(const SoPath &p1, const SoPath &p2);

    // Returns type identifier for path instance
    virtual SoType	getTypeId() const;

    // Returns type identifier for SoPath class
    static SoType	getClassTypeId()	{ return classTypeId; }

    // A path can be given a name using setName() (which is a method on
    // SoBase).  These methods allow paths to be looked up by name.
    static SoPath *	getByName(const SbName &name);
    static int		getByName(const SbName &name, SoPathList &list);

  SoINTERNAL public:
    // Initializes path class
    static void		initClass();

    // This is called when a node in the path chain has a child added.
    // The passed index is the index of the new child
    void		insertIndex(SoNode *parent, int newIndex);

    // This is called when a node in the path chain has a child removed.
    // The passed index is the index of the child to be removed
    void		removeIndex(SoNode *parent, int oldIndex);

    // This is called when a node in the path chain replaces a child.
    // The passed index is the index of the child to be removed
    void		replaceIndex(SoNode *parent, int index,
				     SoNode *newChild);

    // Writes path using given write action
    virtual void	write(SoWriteAction *writeAction) const;

    // Returns TRUE if the given notification list involves a change
    // to a node that affects the path. It is assumed that the last
    // (most recent) node in the list is the head node of the path.
    SbBool		isRelevantNotification(SoNotList *list) const;

  protected:
    // Allows internal SoTempPath subclass to forego auditor overhead
    void		auditPath(SbBool flag)	{ doAuditors = flag; }

    ~SoPath();

  private:
    SoNodeList		nodes;		// Pointers to nodes
    SbIntList		indices;	// Child indices
    int			numPublic;	// How many children are public
    int			minNumPublic;	// Minimum we KNOW are public
    SbBool		doAuditors;	// TRUE if auditors to be maintained
    static SoType	classTypeId;	// TypeId of paths

    // Returns real length of path, including hidden children
    int			getFullLength() const	{ return nodes.getLength(); }

    // Appends the given node and index to the lists, updating
    // numPublic as appropriate
    void		append(SoNode *node, int index);

    // Returns new SoPath; called by SoType::createInstance()
    static void *	createInstance();

    // Reads stuff into instance of SoPath. Returns FALSE on error.
    virtual SbBool	readInstance(SoInput *in, unsigned short flags);

    // Really does a truncate. Flag indicates whether to notify.
    void		truncate(int start, SbBool doNotify);

friend class SoFullPath;
friend class SoTempPath;
friend class SoAction;
};

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoFullPath
//
//  This SoEXTENDER class allows expert users to examine "hidden"
//  children in paths. SoPath allows access from the head node down to
//  the first node with hidden children, but no further. Casting an
//  SoPath to an SoFullPath (which is always guaranteed to be safe)
//  allows you to get at hidden children. SoFullPath overrides some of
//  the methods defined on paths to make this possible.
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoFullPath : public SoPath {

  public:
    //
    // Override methods that normally stop at last public child:
    //

    void		pop()		{ truncate(getFullLength() - 1); }

    SoNode *		getTail() const
	{ return (nodes[getFullLength() - 1]); }

    SoNode *		getNodeFromTail(int i) const
	{ return (nodes[getFullLength() - 1 - i]); }

    int			getIndexFromTail(int i) const
	{ return (indices[getFullLength() - 1 - i]); }

    int			getLength() const	{ return getFullLength(); }

  private:
    SoFullPath(int approxLength) : SoPath(approxLength)	{}
    virtual ~SoFullPath();

friend class SoTempPath;
};



//////////////////////////////////////////////////////////////////////////////
//
//  SoINTERNAL Class: SoLightPath
//
//  A SoLightPath is a light-weight version of an SoTempPath, intended to
//  be used just to keep track of the current path during traversal.
//  Eventually it is intended to replace SoTempPath (when appropriate 
//  modifications are made to SoDraggers).
//  Unlike SoPath, it keeps only a chain of childIndices and a headnode.
//  The methods implemented are only those needed for traversal.
//
//////////////////////////////////////////////////////////////////////////////


class SoLightPath  {

  SoINTERNAL public:

    // Constructor given approximate number of nodes in chain
    SoLightPath(int approxLength);
 

    // Sets head node (first node in chain)
    // Resulting path has only one node.
    void		setHead(SoNode *node);

    // Adds node specified by childindex to end of chain. 
    void		append(int childIndex) 
	{ indices.append(childIndex);}


    // Allows path to be treated as a stack: push a node at the end of
    // the chain and pop the last node off
    void		push(int childIndex)	{ append(childIndex); }
    void		push()			{ append(-1);}
    void		pop()		{ truncate(getFullLength() - 1); }
    void		setTail(int childIndex) 
	   	{ indices.set(getFullLength()-1,(void *)childIndex);}
    SoNode *		getTail()
		{ return getNode(getFullLength()-1);}

    // Returns the first node in a path chain.
    SoNode *		getHead() const	{ return headNode; }

    // Returns pointer to ith node in chain
    SoNode *		getNode(int i) const;	

    // Returns full length of path chain (number of nodes)
    // note that public/private distinction is ignored.
    int			getFullLength() const {return indices.getLength();}

    // Removes all nodes from indexed node on
    void		truncate(int start) { indices.truncate(start);}

    
    // fills in nodes for a TempPath that is represented by this 
    // SoLightPath.  Called by SoAction::getCurPath(); 
    void 		makeTempPath(SoTempPath *) const;

  private:

    ~SoLightPath();
    SoNode *		headNode;	// Pointer to headnode
    SbIntList		indices;	// Child indices


  friend class SoAction;
};



#endif /* _SO_PATH_ */
