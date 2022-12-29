// -*- c++ -*-
////////////////////////////////////////////////////////////////////////////////
///////   Copyright 1997  Silicon Graphics, Inc.  All Rights Reserved.   ///////
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

#pragma once
#ifndef WV_NAV_H
#define WV_NAV_H

#include <vector.h>
#include <map.h>

///////////////////////////////////////////////////////////////////////////////
//
// Navigation model:
//
// The stack consists of changes separated by separator objects
//
// [0] redo toplevel browser to url ..
// [1] sep
// [2] redo frame1 browser to url ..
// [3] sep
// [4] redo frame2 browser to url ..
// [5] undo frame1 browser to old url...
// [6] redo frame1 browser to url ..
// [7] sep 
// [8] undo toplevel browser to old url...
// [9] redo toplevel browser to url ..
// ... etc ...
//
// The Navigator maintains an index into the stack,  always pointing at
// the beginning of the current displayed changeset.  Navigating forward
// and back causes sets to be applied back to or forward to the next item.
// 
// The toplevel browser runs the match function to extract information for
// the menu or other history display.  The match function also tells the
// browser which item is the current displayed item.  Note that direct menu
// navigation *must* navigate to a changeset on the toplevel browser!  Otherwise
// further frame navigation will fail.
//
// As each browser's documentLoaded method is called,  a BrowserChangeSet is pushed
// onto the Navigator's stack.  The browser is referred to by name since the
// exact instance may be different when renavigating the stack.
//
// A second parallel stack is kept for direct navigation by the toplevel
// browser.  This stack, _tf_stack, contains indecies into _nav_stack which
// correspond to changes in the top frame.  For the above example it would
// contain:
//
// 0. 0
// 1. 7
// ...
//
// _current_index points somewhere into the current set of changes.  Maybe it
// would be better if it pointed to the separators,  but it isn't so bad this
// way.  It is important to make it point to the first change when navigating
// so that applySet works properly.
//
// applySet takes a boolean which tells it which direction we're navigating
// in.  If the boolean is true then we're navigating backward and we apply
// the current undo set,  otherwise we're navigating forward and we apply
// the next redo set.
//
///////////////////////////////////////////////////////////////////////////////

class wvChangeSet;
class wvBrowser;

// This class it subclassed to link it to the Browser object
class wvNavigator {
protected:
  typedef map < cstring, cstring, less<cstring> > pathmap;
  unsigned int			_ref_count;

  wvBrowser*			_top_frame;
  vector<wvChangeSet*>		_nav_stack;
  vector<unsigned int>		_tf_stack;
  int				_current_index;
  // The bool argument to MatchCB is whether this item is the current
  // displayed item in that browser,  the third item is any data which
  // match was called width
  typedef void (*MatchCB)(wvChangeSet*, bool, void*);

  void 		applySet(bool undo);
  void 		trimBackTo(int i);
public:
  pathmap			_frame_map;

  wvNavigator(wvBrowser* t);
  virtual ~wvNavigator();

  typedef enum { First, Next, Prev, Last } Direction;
  void			copy();
  void			free();

  // Move in stack in direction
  bool			navigate(Direction);
  // Move to position in stack,  must be at the start of 
  // a toplevel browser's change set.  If you navigate 
  // somewhere else then beware
  bool  		navigate(unsigned int);
  // Get extent of current stack for this navigator
  unsigned int 		getStackDepth() const;
  // Reset stack to empty.  Otherwise the first item will always remain
  void			resetStack();
  // Add information to stack, truncates the stack if we aren't at the end
  // of the stack.  That is,  if we're currently navigated to an intermediate
  // position in the stack,  the new item will be pushed after the next
  // separator,  and the old items will be freed.
  void			push(wvChangeSet *, bool replace_current = false);
  // Get current stack position
  int			currentPos() const { return _current_index; }
  // Traverse stack calling function for each matching item
  // limit tells match to only match subframes within the current parent's
  // range
  void			match(const char* browser_path, MatchCB, 
			      void* callback_data, bool limit);
  // Find nearest entry with given matching substring 0 is a nomatch.
  // Result is suitable to be passed to navigate
  int			find(const char* substr);

  // Query map for frame loading in navigation
  cstring		lookupMap(const cstring& path, const cstring& def) const;
  void			resetMap();

  // Finds the current set for the specified browser frame so we can
  // update information about this frame while navigating
  wvChangeSet*		getCurrentSet(const char* browser_path);
  // Get the top frame browser
  wvBrowser*		getTopFrameBrowser() const {
    return _top_frame; 
  }
  // Detect edge conditions for UI
  bool			atFirst() const;
  bool			atLast() const;
  // Call after failed load,  will snip off sep and undo information
  void			cleanup();
#ifdef DEBUG
  ostream&		output(ostream& s) const;
  ostream& operator<<(ostream& s) {
    return output(s);
  }
#endif // DEBUG
};

#endif // Navigator
