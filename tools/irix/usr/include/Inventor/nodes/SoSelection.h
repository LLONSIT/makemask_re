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
 |
 |   $Revision: 2.2 $
 |
 |   Description:
 |	This file defines the SoSelection node class.
 |
 |   Classes:   SoSelection
 |
 |   Author(s)	: David Mott, Thad Beier
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_SELECTION_
#define  _SO_SELECTION_

#include <Inventor/SbColor.h>
#include <Inventor/misc/SoCallbackList.h>
#include <Inventor/nodes/SoSeparator.h>

class SoCallbackList;
class SoEvent;
class SoHandleEventAction;
class SoSearchAction;
class SoPickedPoint;
class SoPickedPointList;
class SoTypeList;
class SoSelection;
class SoPath;

// callback function prototypes
typedef void SoSelectionPathCB(void *userData, SoPath *path);
typedef void SoSelectionClassCB(void *userData, SoSelection *sel);
typedef SoPath * SoSelectionPickCB(void *userData, const SoPickedPoint *pick);

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoSelection
//
//  Selection group node: Manages selection list from picks of its children.
//
//////////////////////////////////////////////////////////////////////////////

class SoSelection : public SoSeparator {

    SO_NODE_HEADER(SoSelection);

  public:
    // Constructor. nChildren is the approximate number of children.
    SoSelection();
    SoSelection(int nChildren);
    
    //
    // Selection policy
    // ----------------

    // Default selection policy is SoSelection::SHIFT.
    enum Policy {
	// left mouse pick on object clears selection, then selects object.
	// left mouse pick on nothing clears selection.
	// only one object may be selected at a time. 
	SINGLE,
	
	// left mouse pick on object toggles its selection status.
	// left mouse pick on nothing does nothing.
	// multiple objects may be selected.
	TOGGLE,
	
	// when shift key is down, selection policy is TOGGLE.
	// when shift key is up, selection policy is SINGLE.
	// multiple objects may be selected.
	SHIFT
    };

    // Fields
    SoSFEnum		policy;	// Selection policy - default is SHIFT

    //
    // Selection list management
    // -------------------------

    // select adds a path to the selection list.
    // 'this' must lie in the path, and when added to the list,
    // the path will be truncated such that 'this' is the head.
    // select() makes a copy of the passed path.
    void		select(const SoPath *path);    
    // This convenience version of select will search for the first instance
    // of the passed node under this selection node, and select that path.
    void		select(SoNode *node);

    // deselect removes a path from the selection list by path or by index.
    void		deselect(const SoPath *path);
    void		deselect(int which);
    // This convenience version of deselect will search for the first instance
    // of the passed node under this selection node, and deselect that path.
    void		deselect(SoNode *node);

    // toggles a path in the selection list - if the path is not there,
    // it is selected; if a path is there, it is deselected.
    void		toggle(const SoPath *path);
    // This convenience version of toggle will search for the first instance
    // of the passed node under this selection node, and toggle
    // the selection status on that path.
    void		toggle(SoNode *node);

    // returns TRUE if the path is selected
    SbBool  	    	isSelected(const SoPath *path) const;
    // This convenience version of deselect will search for the first instance
    // of the passed node under this selection node, and return whether
    // that path is selected.
    SbBool		isSelected(SoNode *node) const;
    
    // deselect all the paths in the selection list (i.e. clear)
    void		deselectAll();

    // return the selection list, or one item in the list
    int			getNumSelected() const	{ return selectionList.getLength(); }
    const SoPathList	*getList() const { return &selectionList; }
    SoPath		*getPath(int index) const;

    // [] indexes into the selection list
    SoPath *            operator [](int i) const
			{ return getPath(i); }


    //
    // Selection change callbacks
    // --------------------------
    //
    // Callbacks are invoked when an object is selected or deselected.
    //
    
    // These callbacks are invoked every time an object is selected, whether
    // it be from user interaction or from program call to select() or toggle().
    // This is invoked after the object has been added to the selection list.
    void    addSelectionCallback(SoSelectionPathCB *f, void *userData = NULL);
    void    removeSelectionCallback(SoSelectionPathCB *f, void *userData = NULL);
    
    // These callbacks are invoked every time an object is deselected, whether
    // it be from user interaction or from program call to deselect() or toggle().
    // This is invoked after the object has been removed from the selection list.
    void    addDeselectionCallback(SoSelectionPathCB *f, void *userData = NULL);
    void    removeDeselectionCallback(SoSelectionPathCB *f, void *userData = NULL);

    // Invoked when the user has initiated a change to the selection list
    // by picking objects. This will be followed by invocations of the select
    // and/or deselect callbacks, finally followed by the finish callback.
    void    addStartCallback(SoSelectionClassCB *f, void *userData = NULL);
    void    removeStartCallback(SoSelectionClassCB *f, void *userData = NULL);
    
    // Invoked when the user has finished changing the selection list
    // by picking objects. This was preceeded by an invocation of the start
    // callback, and invocations of the select and/or deselect callbacks.
    void    addFinishCallback(SoSelectionClassCB *f, void *userData = NULL);
    void    removeFinishCallback(SoSelectionClassCB *f, void *userData = NULL);

    // Invoked when a pick has occurred and the selection node is about
    // to change the selection list. The callback function returns the
    // path that the selection node should use when selecting and deselecting.
    // If no pick callback is registered (the default), the selection node
    // will use the path returned by SoPickedPoin::getPath().
    // The returned path need not be ref'd - selection will ref() and unref() it.
    //
    // Note that a picked object may or may not be a child of the selection
    // node. A selection node will only select paths that pass through it.
    //
    //	    Nothing picked - selection policy applied, traversal halts
    //	    Object picked under selection - policy applied, traversal halts
    //	    Object picked not under selection - event ignored, traversal continues
    //
    // In the case of nothing picked, the pick callback is not invoked.
    // In the other cases, the pick callback is invoked, giving it the chance
    // to decide what path gets selected and deselected.
    // 
    // Return values from the callback:
    //
    //	    NULL - selection behaves as if nothing was picked (i.e. for
    //		SINGLE and SHIFT policies, this clears the selection list)
    //
    //	    path - this path will be selected/deselected according to
    //		the selection policy (it must lie under the selection node)
    //
    //	    path not passing through the selection node - selection ignores
    //		this pick event and no change is made to the selection list
    //
    //	    path containing ONLY the selection node - apply the selection
    //		policy as if nothing was picked, but continue traversal
    //
    // A simple way to tell selection to ignore the pick is to return
    // an SoPath with no nodes in it. (i.e. return new SoPath;)
    //
    // Selection will always ref the path returned by the callback, make a
    // copy of the path, then unref the path.
    //
    void    setPickFilterCallback(
		SoSelectionPickCB *f,
		void *userData = NULL, 
		SbBool callOnlyIfSelectable = TRUE); 
    
    //
    // Selection interaction - selection will pick once on mouse down
    // and once on mouse up, and make sure the picks match before changing
    // the selection list. This allows the user to pick down on an object,
    // change their mind and drag off the object, release the mouse button
    // and not affect the selection. Pass TRUE to enable this behavior.
    // Pass FALSE to disable this, meaning whatever is picked on a mouse
    // release is added to/removed from the selection list.
    // Default is pick-matching on.
    //
    void    setPickMatching(SbBool pickTwice) { pickMatching = pickTwice; }
    SbBool  isPickMatching() const { return pickMatching; }
    
    // Provided for backwards compatibility
    SbBool  getPickMatching() const { return pickMatching; }
    
  SoINTERNAL public:
    // Selection notify callbacks - invoked whenever the selection changes.
    // Used by the render area to redraw for selection highlighting.
    void   addChangeCallback(SoSelectionClassCB *f, void *userData = NULL);
    void   removeChangeCallback(SoSelectionClassCB *f, void *userData = NULL);

  // Internal:
    static void		initClass();

  protected:
    // List of paths of selected objects
    SoPathList		selectionList;

    // Selection callback lists
    SoCallbackList	*selCBList;
    SoCallbackList	*deselCBList;
    SoCallbackList	*startCBList;
    SoCallbackList	*finishCBList;
    
    // Pick filter is a single callback function, not a list
    SoSelectionPickCB	*pickCBFunc;
    void		*pickCBData;
    SbBool		callPickCBOnlyIfSelectable;
    
    // Change callbacks
    SoCallbackList	*changeCBList;
    
    // Mouse down picked path
    SoPath		*mouseDownPickPath;
    SbBool		pickMatching;

    // Selection policies (shiftSelection is a combination of these)
    // invokeSelectionPolicy() is called from handleEvent() - for a customized
    // selection policy, either derive a class and write a new handleEvent()
    // method, or use an SoEventCallback node placed such that it receives
    // events before the selection node.
    void    	    	invokeSelectionPolicy(SoPath *path, SbBool shiftDown);
    void    	    	performSingleSelection(SoPath *path);
    void    	    	performToggleSelection(SoPath *path);
    
    // This copies the path so the copy is rooted by 'this'.
    // Returns NULL if 'this' not found in the passed path.
    SoPath  	    	*copyFromThis(const SoPath *path) const;
    
    // addPath() assumes the path is rooted by 'this'
    void    	    	addPath(SoPath *path);
    void    	    	removePath(int which);
    
    // This locates path in the selection list. The head of this path
    // does not necessarily have to be 'this'.
    int			findPath(const SoPath *path) const;

    // Traversal routine for SoHandleEventAction - this will call
    // action->setHandled() if the event is handled
    virtual void	handleEvent(SoHandleEventAction *action);
    
    // Destructor removes everything from the list.
    ~SoSelection();

  private:

    // This action is used to search for nodes.
    static SoSearchAction *searchAction;

    // this is called from the two constructors.
    void    	    	constructorCommon();  
};



#endif /* _SO_SELECTION_ */
