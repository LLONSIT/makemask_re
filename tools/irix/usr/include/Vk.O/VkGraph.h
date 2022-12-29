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
#ifndef VKGRAPH_H
#define VKGRAPH_H

#include <Vk/VkComponent.h>

class VkNode;
class VkWindow;
class VkPopupMenu;
class VkMenuItem;
class VkOptionMenu;

class VkNodeDictionary;

typedef Boolean (*VkGraphFilterProc) (VkNode *);
typedef void (*VkGraphNodeProc) (VkNode *);

class VkGraph : public VkComponent {

    friend class VkNode;

 public:

    VkGraph(char * name, Widget);
    VkGraph(char * name, Widget, Boolean showPopupMenus);
    virtual ~VkGraph();

    void saveToFile();

    Widget twinsButton() { return _twinsButton; }
    Widget relayButton() { return _relayGraphButton; }
    Widget reorientButton() { return _toggleLayoutButton;}
    Widget workArea() { return _workArea;}

    void makeNodeVisible(VkNode *);

    virtual void buildGraph();
    virtual void tearDownGraph();

    void buildGraph(const char *attribute, Boolean showAttribute = TRUE);
    void present(const char *attribute);

    void showOverview();
    void hideOverview();
    VkWindow *overviewWindow() { return _overviewWindow; }

    void clearAll();
    virtual void displayAll();

    void sortAll();

    virtual void add(VkNode *node, int index1, VkNode *node2, int index2, char *attribute = NULL);
            void add(VkNode *node, int index1, VkNode *node2, int index2, char *attribute, void *data);
    virtual int  add(VkNode * , int index = -1);
    virtual void add(VkNode * , VkNode*, char *attribute = NULL);
            void add(VkNode * , VkNode*, char *attribute, void *data);

    virtual void remove(VkNode *node, Boolean deleteNode = FALSE);

    virtual void undisplay(VkNode * node);
    virtual void undisplayAllArcs();

    void setSize(int);
    void resetSize(int);

    virtual void display(VkNode *child);

    virtual VkNode *display(char *name);

    virtual void hideParentsAndChildren(VkNode *node);
    virtual void displayParentsAndChildren(VkNode *node);
    virtual VkNode *displayParentsAndChildren(char *name);

    virtual void hideNode(VkNode *node);

    virtual void hideParents(VkNode *node);
    virtual void displayWithParents(VkNode *node);
    virtual VkNode *displayWithParents(char *name);

    virtual void displayWithAllParents(VkNode *node);
    virtual VkNode *displayWithAllParents(char *name);

    virtual void displayWithChildren(VkNode *node);    
    virtual VkNode *displayWithChildren(char *name);

    virtual void displayWithAllChildren(VkNode *node);    
    virtual VkNode *displayWithAllChildren(char *name);

    virtual void displayButterfly(VkNode *node);    
    virtual VkNode *displayButterfly(char *name);

    virtual void displayIf(VkGraphFilterProc);

    virtual void hideAllChildren(VkNode *);
    virtual void hideWithAllChildren(VkNode *);

    virtual void expandNode(VkNode *);
    virtual void expandSubgraph(VkNode *);

    virtual void forAllNodesDo(VkGraphNodeProc);

    virtual void setLayoutStyle(char);

    VkNode *find(char *);
    VkNode *find(int );

    void doLayout();
    void doSubtreeLayout(VkNode *);
    void doSparseLayout();

    int numNodes() { return _numNodes; }

    Widget graphWidget() { return _graphWidget; }

    static const char *const arcCreatedCallback;
    static const char *const arcDestroyedCallback;

    static VkComponent*  CreateVkGraph(const char *name, Widget parent);

    Widget getTwinsButton() { return _twinsButton; }
    Widget getRelayButton() { return _relayGraphButton; }
    Widget getToggleLayoutButton() { return _toggleLayoutButton; }
    Widget getCmdPanel() { return _cmds;}
    Widget getZoomInButton() { return _zoomIn;}
    Widget getZoomOutButton() { return _zoomOut;}
    Widget getOverviewButton() { return _overviewButton;}
    
 protected:

    Boolean       _callArcDestroyedHook;

    VkNode  **_nodeList;
    int       _numNodes;
    int       _maxNodes;

    VkNode *_butterflyNode;

    VkPopupMenu  *_desktopMenu;

    VkMenuItem   *_collapse;
    VkMenuItem   *_collapseSelected;

    VkPopupMenu  *_popupMenu;
    VkMenuItem   *_expand;
    VkMenuItem   *_bigExpand;
    VkMenuItem   *_expandSelected;

    VkMenuItem   *_hide;
    VkMenuItem   *_hideSelected;
    VkMenuItem   *_hideParents;
    VkMenuItem   *_expandParents;

    VkMenuItem   *_popupTitleObj;
    VkNode       *_selectedNode;

    virtual void buildCmdPanel(Widget);
    virtual void buildZoomMenu(Widget);
    virtual void addMenuItems(VkPopupMenu *);
    virtual void addDesktopMenuItems(VkPopupMenu *);
    virtual void popupMenu(VkNode *, XEvent *);
    virtual void setZoomOption(int);

    virtual void arcCreatedHook(VkNode *, Widget, VkNode *);
    virtual void arcDestroyedHook(Widget);
    virtual void twinsVisibleHook(Boolean);

    void create(Widget parent, Boolean showPopupMenus);

  private:

    static String _resources[];

    VkNodeDictionary *_nodeDict;   

    void updateVisualState(VkNode *);
    void updateVisualState();
    void updateSubtreeVisualState(VkNode *node);

    void nodeDestroyed(VkCallbackObject *, void *, void *);

    Pixmap _simple, _simpleArm, _complex, _complexArm;

    Widget _fileBrowser;
    Widget _graphWidget, _twinsButton, _relayGraphButton, _toggleLayoutButton;
    Widget _cmds, _zoomIn, _zoomOut, _overviewButton;
    Widget _workArea;
    VkWindow *_overviewWindow;

    static void saveToFileCallback(Widget, XtPointer, XtPointer);
    static void popupMenuCallback(Widget, XtPointer, XtPointer);
    static void showOverviewCallback(Widget, XtPointer, XtPointer);
    static void hideNodeCallback(Widget, XtPointer, XtPointer);
    static void collapseSubgraphCallback(Widget, XtPointer, XtPointer);

    static void expandNodeCallback(Widget, XtPointer, XtPointer);
    static void expandSubgraphCallback(Widget, XtPointer, XtPointer);

    static void expandSelectedCallback(Widget, XtPointer, XtPointer);
    static void hideSelectedCallback(Widget, XtPointer, XtPointer);
    static void collapseSelectedCallback(Widget, XtPointer, XtPointer);

    static void hideParentsCallback(Widget, XtPointer, XtPointer);
    static void expandParentsCallback(Widget, XtPointer, XtPointer);

    static void relayCallback(Widget, XtPointer, XtPointer);
    static void twinsCallback(Widget, XtPointer, XtPointer);
    static void toggleLayoutCallback(Widget, XtPointer, XtPointer);
    static void optionSetCallback(Widget, XtPointer, XtPointer);
    static void zoomInCallback(Widget, XtPointer, XtPointer);
    static void zoomOutCallback(Widget, XtPointer, XtPointer);

    void overviewDeletedCallback(VkCallbackObject *, void *, void *);

    VkOptionMenu *_zoomOptionMenu;
    VkMenuItem   *_items[10];
    int           _childSpacing[10];
    int           _siblingSpacing[10];
    String        _labels[10];
    XmFontList    _fonts[10];
    int           _sizeOfZoomList;
    int           _zoomIndex;
    Boolean       _twinsVisible;

    void displayWithAllChildrenAux(VkNode *node);    
    void displayWithAllParentsAux(VkNode *node);    

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkGraph(const VkGraph&);
    VkGraph &operator= (const VkGraph&);

};

#endif

