// -*- c++ -*-
////////////////////////////////////////////////////////////////////////////////
///////   Copyright 1996  Silicon Graphics, Inc.  All Rights Reserved.   ///////
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
#ifndef VkWebViewer_H
#define VkWebViewer_H

#include <Vk/VkComponent.h>
#include <Vk/wvObjects.h>
#include <Xm/DropSMgr.h>
#include <sys/param.h>
#include <stdio.h>
#include <Vk/wvBrowser.h>

typedef enum { SG_FIRST, SG_LAST, SG_PREV, SG_NEXT } VkWebViewerDirection;
typedef enum { SG_POST, SG_GET } VkWebViewerMethod;
typedef enum {
  SG_NONE = 0,
  SG_BACKARROW = 1 << 1,
  SG_FOREARROW = 1 << 2,
  SG_HOME = 1 << 3,
  SG_RELOAD = 1 << 4,
  SG_STOP = 1 << 5,
  SG_COMBO = 1 << 6
} VkWebViewerControlsEnum;

#define SG_MINIMAL (VkWebViewerControlsEnum)(SG_BACKARROW | SG_FOREARROW | SG_RELOAD | SG_STOP)
#define SG_FULL  (VkWebViewerControlsEnum)(SG_BACKARROW | SG_FOREARROW | SG_HOME | SG_RELOAD | SG_STOP | SG_COMBO)

class ostream;

class VkOptionMenu;
class VkMenuAction;
class VkMenuToggle;
class VkMenuItem;
class VkPopupMenu;
class VkGenericDialog;

class VkWebViewerDocument;
class VkWebViewerData;
class VkWebViewerBaseData;
class VkWebViewerDropInfo;
class VkWebViewerBaseCallbacks;

class wvPen;

class VkWebViewerBase : public VkComponent, public wvBrowser
{
  friend class MarkupFrame;
  friend class LoaderContext;
  friend class DocumentContext;
  friend class ImageContext;
  friend class VkWebViewerBaseCallbacks;
  friend class wvXFrameControl;

public:

  VkWebViewerBase(const char *, Widget, Arg* = NULL, Cardinal = 0);
  VkWebViewerBase(const char *);
  virtual 	~VkWebViewerBase();
  void 		create ( Widget, Arg* = NULL, Cardinal = 0 );
  const 	char *  className();
    
  static VkComponent *CreateVkWebViewerBase( const char *name, Widget parent );
  
  VkWebViewerBaseData*  _base;
  Widget  		_viewer;
protected:

  Widget  		_scrolledw;
  Widget  		_vertSB;
  Widget  		_horizSB;

  // Background menu on button3
  VkPopupMenu	        *_popupmenu;
  VkGenericDialog	*_gotoDialog;

private:

  static String      	_defaultVkWebViewerBaseResources[];
  static void 		*RegisterVkWebViewerBaseInterface();

  //
  // Methods
  //
  const VkWebViewerAList* dropSiteSearch(int, int, int*, XtPointer*);

protected:
  // Called by the base constructor
  void		web_init();
  void		web_destroy();
  virtual void  dnd_init();

  // Used internally,  don't override in subclasses.  Work around downcast
  // problems with multiple inheritence
  void*		getComponent() const { return (void*) this; }

  // virtuals:
  virtual Atom* getDropTargets(unsigned long&);
  virtual void	registerDropSite();
  virtual Widget getDragIcon(const VkWebViewerAList &, XEvent*);
  virtual Widget startDrag(const VkWebViewerAList &, XEvent *, 
			   Atom, XtPointer);
  virtual Atom*	getTargets(const VkWebViewerAList &attrs, unsigned long&);
  virtual Boolean convertProc(Widget, Atom*, Atom*, Atom*, 
			      XtPointer*, unsigned long*, int*);
  virtual void	dragUnder(const VkWebViewerAList&, XtPointer);
  virtual VkWebViewerDropInfo* dropSearch(Widget, XmDropProcCallbackStruct *);
  virtual void	drop(VkWebViewerDropInfo*, XmDropProcCallbackStruct*);
  virtual void 	dropSelect(VkWebViewerDropInfo*,
			   XtPointer, Atom, unsigned long, int);
  virtual void  loaderFeedback(XtIntervalId *id=0);
  void		postErrorCheck(VkWebViewerLoaderContext *lc, const char* message);

  // mailto
  virtual void parseMailto(const char *link);
  virtual void handleMailto(const char *link, VkWebViewerAList &attrs);

  // viewing source code or specified file
  virtual void viewSource(FILE* filehandle = NULL); 

  virtual void	activate(void*);

  virtual wvBrowser *findWindowTarget(const char *window_name);
  virtual void	formActivate(const char* url, const char* query, 
			     const char* method);
  virtual void authenticate(WV(LoaderContext) *lc, int attempt);
  virtual void setScrollPosition(const char* target); // Go to fragment in doc
  virtual void setScrollPosition(const wvPoint&);
  virtual wvPoint getScrollPosition() const;
public:
  virtual void*	getParentControl() const { return (void*) _viewer; }
  virtual wvBrowser *createFrame(const char *name, void* parent,
				 WV(AList) &attrs);
  virtual bool documentLoaded(WV(LoaderContext) *lc);
  char*		canonicalizeUrl(const char*);
  virtual void	setDocument(wvPtr<WV(Document)>&);
  wvPtr<WV(Document)> getDocument() const { return currentDoc; }

  virtual void	notify(const char *message);
  virtual void	notify(NotifyReason reason, const char*);
  
  virtual void	showBusy(bool);
  virtual void	stopTransfer(); // Stop in progress web access

  virtual void	setURL(const char* url);
  virtual void	loadFile(const char* filename);
  virtual void	setQuery(const char* s);
  virtual void	gotoLink(const char* url, VkWebViewerMethod method = SG_GET);

  virtual void setFollowLinks(bool f);
  virtual bool getFollowLinks();

  virtual void	postError(const char*);
  virtual bool	yesNoDialog(const char*);
  virtual cstring promptDialog(const char*);
  FILE          *getDocumentFile();
  const char    *getDocumentFileName();
  void		dumpDocument(ostream&) const;
  void		dumpStructure(ostream&) const;
  void		enableTimer(bool enable) const;
  wvPen*	getPen() const;

  // We cannot add a virtual functions without breaking binary compatibility,
  // so single instance callback functions are provided instead.  Note
  // that cookies (and their callbacks) are shared between all instances.
  static VkWebViewerCookie::CookieVerifier
    setCookieVerifier(const VkWebViewerCookie::CookieVerifier &callback);
  static VkWebViewerCookie::FileChangedNotifier
    setFileChangedNotifier(const VkWebViewerCookie::FileChangedNotifier &cb);

  int	reverifyCookies(const char *url = "",
			bool permanent_cookies = TRUE,
			bool session_cookies = TRUE);
};

class wvChangeSet;

class VkWebViewer : public VkWebViewerBase
{ 
  friend class VkWebViewerBase;
  friend class VkWebViewerCallbacks;

public:

  VkWebViewer(const char *, Widget, Arg* = NULL, Cardinal = 0);
  VkWebViewer(const char *);
  virtual 	~VkWebViewer();
  void 		create ( Widget );
  const char *  className();
    
  static VkComponent *CreateVkWebViewer( const char *name, Widget parent );

protected:

  VkWebViewerData* _viewer_e;

  // Widgets created by this class

  Widget  _button_form;
  Widget  _backArrow;
  Widget  _forwardArrow;
  Widget  _home;
  Widget  _reload;
  Widget  _label;
  Widget  _stop_button;
  Widget  _comboBox;
  Widget  _comboBoxList;

  // 
  static void	     UpdateMenu(wvChangeSet*, bool, void*);
    
private:
  // Private data -  Array of default resources
  static String      	_defaultVkWebViewerResources[];
  static void 		*RegisterVkWebViewerInterface();
    
protected:
  virtual void	notify(NotifyReason reason, const char*);
  virtual void	showBusy(bool);
  virtual void  changingPage();

public:
  virtual bool  documentLoaded(WV(LoaderContext) *lc);
  virtual void	navigate(VkWebViewerDirection direction);
  virtual void	navigate(unsigned int i);
  virtual void  resetStack();
  virtual unsigned int  getStackDepth();
  virtual void	setControls(bool); // True to show, False to hide
  virtual void	setControls(VkWebViewerControlsEnum);
  virtual void  updateInterface();
  virtual void  setMessageArea(bool visible);
};

class VkWebViewerDropInfo {
public:
  VkWebViewerDropInfo();
  VkWebViewerBase 		*viewer;
  const VkWebViewerAList 	*attrs;
  VkWebViewerForm 	 	*form;
  Atom		 		request_type;
};  
#endif

