
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

#ifndef VKOUTLINE_H
#define VKOUTLINE_H

#include <Vk/VkComponent.h>

const int MaxAttributeSets = 5;

class VkOlDisplayParams {

    public:

	VkOlDisplayParams (Widget);
	~VkOlDisplayParams ();

	void	setIndentationWidth (int);
	int	setAttributeSet (Pixel, Pixel, Pixel, XmFontList);

	Widget	widget		();
	int	indentation	();

	Pixel	foreground 	(int);
	Pixel	background	(int);
	Pixmap	closedPixmap	(int);
	Pixmap	closedPixmap	();
	Pixmap	openPixmap	();
	GC	gc		(int);
	XmFontList font		(int);

	int	maxAttrIndex	();

    private:

	Widget	_listW; 
	int	_indentationWidth;

	Pixel		_fgs		[MaxAttributeSets];
	Pixel		_bgs		[MaxAttributeSets];
	XmFontList	_fonts		[MaxAttributeSets];
	Pixmap		_closedPMs	[MaxAttributeSets];
	GC		_gcs		[MaxAttributeSets];

	Pixmap	_openPixmap;

	int	_attrTableSize;

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkOlDisplayParams(const VkOlDisplayParams&);
    VkOlDisplayParams &operator= (const VkOlDisplayParams&);
};
	

class VkOlNode {

	public:

	    void*	operator new (size_t);
	    void	operator delete (void*, size_t);

	    VkOlNode	(char*);
	    VkOlNode	(char*, void*);
	    VkOlNode	(char*, char*, void*);
	    
	    ~VkOlNode ();

	    void	addChild	(VkOlNode*);
	    void	removeChild	(VkOlNode*);

	    VkOlNode*	search		(int, int);
	    VkOlNode*	search		(XmString, int);
	    VkOlNode*	search		(char*, int);

	    void	print		(int);

	    void	setItemCount	(int);
	    int		getItemCount	();
	    void	walkToCount	();
	    int		countVisibleItems();

	    unsigned int	setMaxChildAttrIndex (int);
	    unsigned int	unsetMaxChildAttrIndex (int);
	    int		maxChildAttrIndex();
	    int		attrIndex	(); 
	    void	setAttrIndex	(int);

	    int		whereDisplayed	();
	    void	initCorrection	();
	    void	correctPositions(VkOlNode*);

	    void	display		(int, VkOlDisplayParams*);
	    void	highlight	(int, VkOlDisplayParams*);
	    void	unhighlight	(int, VkOlDisplayParams*);

	    VkOlNode*	getNodeAt	(int,	int *);
	    VkOlNode*	getNodeOf	(char*,	int *);
	    VkOlNode*	getNodeOf	(XmString, int *);
	    VkOlNode*	pathToNode	(char**);

	    XmString	name		();
	    char*	key		();
	    int		nchild		();
	    VkOlNode*	child		(int);

	    void	setParent	(VkOlNode*);
	    VkOlNode*	getParent	();

	    void	setKey		(char*);
	    char*	getKey		();

	    int		isOpen		();
	    void	Open		();
	    void	Close		();

	    void*	getHook		();

	private:

	    enum {NALL = 1024};		    // used in overloading NEW;
	    static VkOlNode* freeNodesHead; // taking a leaf out of VkGraph
	    VkOlNode*	next;		    // with due respect to copyrights!

	    static int _foundLevel;
	    static int _itemCount;
	    static Boolean _correctionOn;
	    static int	_itemAttrIndex;

	    char*	_key;		// displayed string could be different
	    XmString	_name;		// display string
	    VkOlNode**	_children; 
	    VkOlNode*	_parent;
	    int		_nchild;	// number of children
	    Boolean	_showKids; 	// TRUE when children are shown
	    short	_attrIndex;	// index to display attributes
	    unsigned int _maxChildAttr;	// max of (childrens' index) 
	    int		_displayedPosition;     // item# on the list
	    void*	_hook;

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkOlNode(const VkOlNode&);
    VkOlNode &operator= (const VkOlNode&);
};


class VkOutline : public VkComponent {

public:

    VkOutline (const char *, Widget );
    virtual ~VkOutline ();

    void reset ();
    Widget listWidget ();

    void add	     (	char*, char*);
    void addChildren (	char**, char**);
    void addChildren (	char**, char**, char**, void**);
    void createPath  (  char**, char**);
    void printTree   ();
    virtual void toggleChildren (int position);
    void displayAll  ();

    void setHighlightClosedIcon (Boolean);
    void setIndentationWidth (int);
    void setKeywordAttributes (Pixel, Pixel, XmFontList);
    int  setHighlightAttributes (Pixel, Pixel, Pixel, XmFontList);

    void displayAsKeyword (char** path);

    void highlight (char** items, int); 

    void highlight (int position, int); 

	// int is what you get out of setHighlightAt...; so you can have
	// multiple highlighting active at the same time; but you cant have two
	// highlights apply to a same item; if display mechanism could be found
	// then probably we can change the way int is interpreted

    void unhighlight (int);
	// you have to know which group you are unhighlighting

    void* getHookAt  (int position);

    void closePath (char** path);
	// path has to exist! no display activities

    int  isPathClosed (char** path);
        // result valid for an existing path

    int effectOfLastToggle (int& from, int& count);
	// the above method returns 1 if the last call to toggleChildren
	// resulted in opening of a subtree or 0 otherwise;
	// on return *from* gives the position from where the list display is 
	// affected and *count* gives the number of list items inserted or
	// deleted; a call to this methods yields meaningless results if
	// the outline has never been toggled

    void select (int position);

    void walkAllKeywords (void*, void (*)(void*, VkOlNode*));

    void setTabProcessing (Boolean);	
	// sets a flag whether to process tabs in the display strings of items
	// added after this method is called. Once added, items will retain the
	// property even if this flag is changed. Tab processing apply to a group
        // of leaf items under the same parent. The display string is searched
	// for tabs and words following tabs are aligned.
	// Limitaion: This processing is limited to the children added using
	//		void addChildren (  char**, char**, char**, void**);

    static VkComponent* CreateVkOutline(char *name, Widget parent);

 protected:

    char*       _rootName;
    VkOlNode*	_rootNode;

    Boolean     _treeModified;
    Widget	_listWidget;

    VkOlDisplayParams* _displayParams;

    int		_keywordAttrIndex;

    int		_lastToggleOperation;   // these variables store the effect
    int		_lastToggleFrom;	// of last call to toggleChildren
    int		_lastToggleCount;	// it is provided to enable application
					// to handle its part of toggling
					// efficiently (use if true) 

    Boolean	_processTabs;		// alignment to tabs on or off

    void init ();

    void visitEveryKeyword (VkOlNode*, void*, void (*) (void*, VkOlNode*));
    void processTabs (char**, int);

  private:

    static void activateCallback(Widget, XtPointer, XtPointer);

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkOutline(const VkOutline&);
    VkOutline &operator= (const VkOutline&);
};

#endif

