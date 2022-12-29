////////////////////////////////////////////////////////////////////////////////
///////   Copyright 1992, Silicon Graphics, Inc.  All Rights Reserved.   ///////
//                                                                            //
// This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics, Inc.;     //
// the contents of this file may not be disclosed to third parties, copied    //
// or duplicated in any form, in whole or in part, without the prior written  //
// permission of Silicon Graphics, Inc.                                       //
//                                                                            //
// RESTRICTED RIGHTS LEGEND:                                                  //
// Use,duplication or disclosure by the Government is subject to restrictions //
// as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data     //
// and Computer Software clause at DFARS 252.227-7013, and/or in similar or   //
// successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -    //
// rights reserved under the Copyright Laws of the United States.             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
#ifndef VKNODE_H
#define VKNODE_H

#include <Vk/VkComponent.h>

class VkNode;

typedef int (*VkNodeSortFunction)(VkNode *, VkNode *);

/*******************************************************
CLASS
    VkNode

OVERVIEW





******************************************************/

class VkNode : public VkComponent {

    friend class VkGraph;

 public:

    ////////////
    // Constructor
    VkNode();

    ////////////
    // Constructor, with a name (identifier), which should be unique,
    // and an optional label, used by the default class as the text
    // to be displayed.
    VkNode(const char *name, const char *label = NULL);

    ////////////
    // Constructor, with a name (identifier), which should be unique,
    // the parent node in the graph, and an optional label, used by the
    // default class as the text to be displayed.
    VkNode(const char *name, VkNode *parent, const char *label = NULL);

    ////////////
    // Allows a sort function to be set for sorting the order in which
    // nodes appear in the graph
    static void setSortFunction(VkNodeSortFunction f) { VkNode::_sortFunction = f; }

    ////////////
    // Destructor
    virtual ~VkNode();

    ////////////
    // Retrieve the name of this object
    char *name() const {return _name;}

    ////////////
    // Retrieve the label displayed by this object
    virtual char *label();


    ////////////
    // Return the number of children supported by this node
    int nChildren() const { return _nChildren;}

    ////////////
    // Return the number of parent nodes associated with this node
    int nParents() const { return _nParents;}


    ////////////
    // Finda child by name
    VkNode *findChild(char * name);

    ////////////
    // Find a parent by name
    VkNode *findParent(char * name);


    ////////////
    // Retrieve a child by index
    VkNode *child(int index) const { return _children[index];}

    ////////////
    // Retrieve a parent by index
    VkNode *parent(int index) const { return _parents[index];}


    ////////////
    // Apply the current sort function to all children
    void sortChildren();

    ////////////
    // Select this node. Must be currently displayed
    void select();

    ////////////
    // unselect this node. Must be currently displayed.
    void unselect();

    // "private" functions for internal use. Do not use.

    void markAsConnected(int index) { _buildList[index] = TRUE;}
    void markAsDisconnected(int index) { _buildList[index] = FALSE;}
    Boolean connected(int index) ;
    Atom attribute(int index) ;
    void * getAttributeData(int index) ;
    String attributeName(int index) ;

  protected:

    int   _index;


    char          *_label;
    void clear();
    class VkNode **_children;
    int            _nChildren;
    int            _maxChildren;

    Boolean        *_buildList;
    void           *_attributeList;
    VkNode         **_parents;
    int            _nParents;
    int            _maxParents;
    Boolean        _hasChildren;
    Boolean        _hasVisibleChildren;
    Boolean        _hasVisibleParents;
    Boolean        _hasParents;


    ////////////
    // 
    Boolean hasChildren() { return _hasChildren; };

    ////////////
    //
    //
    Boolean hasVisibleChildren() { return _hasVisibleChildren; };

    ////////////
    //
    //
    Boolean hasParents() { return _hasParents; };

    ////////////
    //
    //
    Boolean hasVisibleParents() { return _hasVisibleParents; };
    

    ////////////
    //
    //
    void display(Widget parent);


    ////////////
    //
    //
    void undisplay();


    ////////////
    //
    //
    void addParent(VkNode *, char *attribute = NULL);

    ////////////
    //
    //
    void addParent(VkNode *, char *attribute, void *data);

    ////////////
    //
    //
    void addChild(VkNode *);


    ////////////
    //
    //
    void removeChild(char *name);

    ////////////
    //
    //
    void removeChild(VkNode *child);

    ////////////
    //
    //
    void removeParent(char *name);

    ////////////
    //
    //
    void removeParent(VkNode *child);

    ////////////
    //
    //
    virtual void updateVisualState();

    ////////////
    //
    //
    virtual void build(Widget);


    ////////////
    //
    //
    void widgetDestroyed();
    
  private:

    static VkNodeSortFunction _sortFunction;
    static int sortStub(const void *, const void *);

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkNode(const VkNode&);
    VkNode &operator= (const VkNode&);
};

#endif


