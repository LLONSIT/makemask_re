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
#ifndef BROWSER_H
#define BROWSER_H


// Needed because o32 doesn't define bool,  but n32 does
#ifndef _BOOL
#define _BOOL 1
typedef unsigned char bool;
static const unsigned char true = 1;
static const unsigned char false = 0;
#endif // _BOOL

#include <mstring.h>
#include <list.h>
#include "wvObjects.h"
#include "wvNavigator.h"

class DocumentContext;
class LoaderContext;
class Loader;

class wvPen;
class wvFrameControl;

class wvBrowser {
  friend class wvPen;
  friend class wvXFrameControl;
  friend class MarkupFrame;
  friend class JSWindow;
  friend class JSLocation;
  friend class DocumentContext;
  friend class LoaderContext;
  friend class ImageData;
protected:
  wvPen		        *_pen;
  wvNavigator		*_navigator;
  cstring		_frame_name;
  wvBrowser		*_parent; // NULL for toplevel
  static list<wvBrowser*> instance_list;
  // State
  unsigned	     	follow_links :1;
  unsigned 	     	reloading :1;
  unsigned 		_is_loading :1;
  unsigned 		_dont_navigate :1;
  unsigned 		_add_referer :1;
  unsigned		_valid :1;
  unsigned		_scrolling :1;

  // Information about the current document
  wvPtr<WV(Document)>	_oldDoc;
  char*		     	_oldAnchor;
  char*		     	currentAnchor;
  wvPtr<WV(Document)> 	currentDoc;
  char*		     	requestQuery;
  cstring	    	_currentTarget;
  Loader                *_loader;
  wvFrameControl        *_control;
  // Loading information
  int 			num_simul;
  static int	     	webLibInitLevel;
  static wvPen		*servicePen;
  static class Loader 	*loader;
  LoaderContext      	*load_context;

  void			init();
  virtual void*		getComponent() const = 0;
  void*                 script_object;
public:
  wvBrowser();
  wvBrowser(wvPen*, const cstring& frame_name, wvBrowser* p = NULL);
  virtual ~wvBrowser();

  typedef enum {NR_INFO, NR_BUSY, NR_LOADER, NR_TITLE} NotifyReason;
  typedef enum {NAV_NONE, NAV_NOUPDATE, NAV_REPLACE} NavigationFlags;
  typedef enum {SCROLL_NONE, SCROLL_AUTO } ScrollState;

  // 
  wvPen*	getPen() const 		{ return _pen; }
  void	        setPen(wvPen* p) 	{ _pen = p; }
  wvBrowser*	getParent() const 	{ return _parent; }
  virtual void*	getParentControl() const = 0;
  void		setParent(wvBrowser* p) { _parent = p; }

  wvFrameControl *getControl() { return _control; }
  void          setControl(wvFrameControl* p) { _control = p; }
  void		setScrolling(ScrollState s) { _scrolling = s != SCROLL_NONE; }
  ScrollState   getScrolling() const 	    {
    return _scrolling ? SCROLL_AUTO : SCROLL_NONE;
  }

  // Finding browser frame
  const cstring& getFrameName() const { return _frame_name; }
  void 		setFrameName(const cstring& name) { _frame_name = name; }
  cstring  	getFramePath() const;
  virtual wvBrowser* findTargetBrowser(const cstring& frame_path);

  // Loading a document
  virtual void 	fetchUrl(const cstring& url, const cstring& query, 
			 const cstring& method, NavigationFlags nav = NAV_NONE);
  virtual void	changingPage();
  virtual bool	documentLoaded(WV(LoaderContext)*);
  // User actions
  virtual void  activate(void*) = 0;
  virtual void  activate(const cstring& url, cstring frame_target,
			 bool isMap = false, int dx = 0, int dy = 0);
  virtual void  formActivate(const char* url, 
			     const char* query,
			     const char* method);
  // Manipulating the interface
  virtual void  fetchFile(const cstring& filename, 
			  NavigationFlags nav = NAV_NONE);
  virtual wvPtr<WV(Document)> getDocument() const = 0;
  virtual void	setDocument(wvPtr<WV(Document)>&) = 0;
  virtual void  setScrollPosition(const wvPoint&) = 0;
  virtual wvPoint getScrollPosition() const = 0;
  virtual void  setScrollPosition(const char* target) = 0; // Go to fragment in doc
  virtual void	notify(NotifyReason, const char* message) = 0;
  virtual void	showBusy(bool) = 0;
  virtual void	postError(const char*) = 0;
  virtual bool	yesNoDialog(const char*) = 0;
  virtual cstring promptDialog(const char*) = 0;
  // Update UI for new navigation info
  virtual void  updateInterface();

  // Behaviors
  virtual void	stopFetch();
  virtual void	authenticate(WV(LoaderContext)*, int attempt) = 0;
  virtual int	reverifyCookies(const char* url, bool permanent, bool session) = 0;
  // mailto
  virtual void parseMailto(const char *link);
  virtual void handleMailto(const char *link, WV(AList) &attrs) = 0;
  // Utilities
  virtual char*	canonicalizeUrl(const char*) = 0;
  // Create a new Frame pane
  virtual wvBrowser *createFrame(const char* name, void* parent,
				 WV(AList) &attributes) = 0;
  // Navigator
  virtual void	setNavigator(wvNavigator *n);
  wvNavigator*  getNavigator() const { return _navigator; }
  int		getNavFlags() const;

  // Scripting
  void* getScriptObject() { return script_object; }
  void setScriptObject(void *p) { script_object = p; }
};

#endif // BROWSER_H
