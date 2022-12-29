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
#ifndef VKTABPANEL_H
#define VKTABPANEL_H

#include <Vk/VkComponent.h>
#include <Vk/VkDoubleBuffer.h>

typedef struct {
  char *label;
  void *clientData;
  int tabIndex;
  XEvent *event;
} VkTabCallbackStruct;

class VkTabArea;
class VkPopupMenu;

class VkTabPanel : public VkComponent {

  public:

    static const char *const tabSelectCallback;
    static const char *const tabPopupCallback;
    
    VkTabPanel(const char *name, Widget parent,
	       Boolean horizOrientation = True,
	       int tabHeight = 0);
    ~VkTabPanel();
    
    virtual const char* className();
    
    Boolean horiz();
    Boolean uniformTabs();
    int size();
    Pixel tabBg();
    Pixel selectedTabBg();
    Pixel labelFg();
    Pixel labelBg();
    GC gc();			// Obsolete
    Pixel getSelectedTabBg(), getSelectedTabTs(), getUnselectedTabBg();
    int lineThickness();
    int tabHeight();
    
    int selectedTab();
    
    Widget area1() { return _area1; }
    Widget area2() { return _area2; }
    
    Boolean getTab(int index, char **label_return, void **clientData_return);
    
    int addTab(char *label, void *clientData, Boolean sorted = False);
    void addTabs(char **labels, void **clientDatas, int numLabels,
		 Boolean sorted = False);
    
    void addTabs(char *list);   // Mostly for rapidapp, add a comma-separated list of tabs
    void setOrientation(int orientation); // XmHORIZONTAL or XmVERTICAL
    
    Boolean selectTab(int index, XEvent *event = NULL);
    Boolean selectTab(char *label, XEvent *event = NULL);
    
    Boolean removeTab(int index);
    Boolean removeTab(char *label);
    
    Boolean tabPixmap(int index, Pixmap *pixmap_return);
    Boolean tabPixmap(char *label, Pixmap *pixmap_return);
    Boolean setTabPixmap(int index, Pixmap pixmap);
    Boolean setTabPixmap(char *label, Pixmap pixmap);
    Boolean setTabLabel(int index, char *label);
    Boolean setTabClientData(int index, void *clientData);
    
    static VkComponent *CreateVkTabPanel(const char *name, Widget parent);
    
  protected:
    
    void tabSelect(VkComponent *comp, void *clientData, void *callData);
    void tabPopup(VkComponent *comp, void *clientData, void *callData);
    
    Widget _area1, _area2, _outer1, _outer2, _marg1, _marg2;
    VkTabArea *_tabArea;
    int _margin, _margin1, _margin2;
    Pixel _tabBg;

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkTabPanel(const VkTabPanel&);
    VkTabPanel &operator= (const VkTabPanel&);
}; 

/**********************************************************************/
/*         VkTabArea is a private class used by VkTabPanel            */
/**********************************************************************/

typedef struct {
  char *ascii;
  void *clientData;
  XmString label;
  int width;
  Pixmap pixmap;
  unsigned int pwidth, pheight, pdepth;
} VkTabInfo;

class VkTabArea : public VkDoubleBuffer {
public:

  static const char *const tabSelectCallback;
  static const char *const tabPopupCallback;

  VkTabArea(const char *name, Widget parent,
	    Boolean horizOrientation = True,
	    int tabHeight = 0);
  ~VkTabArea();

  virtual const char* className();

  Boolean horiz() { return _horiz; }

  void setHoriz(Boolean horiz) { _horiz = horiz;}

  Boolean uniformTabs() { return _uniform; }
  int size() { return _numInfo; }
  Pixel selectedTabBg() { return _selectedTabBg; }
  Pixel unselectedTabBg();
  Pixel selectedTabTs();
  Pixel labelFg() { return _labelFg; }
  Pixel labelBg() { return _labelBg; }
  GC gc() { return _gc; }  // Obsolete -- use selectedGC() or unselectedGC()
  GC selectedGC(), unselectedGC();
  int lineThickness() { return _lineThickness; }
  int tabHeight() { return _tabHeight; }

  int selectedTab() { return _selected; }

  Boolean getTab(int index, char **label_return, void **clientData_return);

  int addTab(char *label, void *clientData, Boolean sorted = False);
  void addTabs(char **labels, void **clientDatas, int numLabels,
	       Boolean sorted = False);

  Boolean selectTab(int index, XEvent *event = NULL);
  Boolean selectTab(char *label, XEvent *event = NULL);

  Boolean removeTab(int index);
  Boolean removeTab(char *label);

  Boolean tabPixmap(int index, Pixmap *pixmap_return);
  Boolean tabPixmap(char *label, Pixmap *pixmap_return);
  Boolean setTabPixmap(int index, Pixmap pixmap);
  Boolean setTabPixmap(char *label, Pixmap pixmap);
  Boolean setTabLabel(int index, char *label);
  Boolean setTabClientData(int index, void *clientData);

protected:
  virtual void draw();
  virtual void resize();
  void scheduleUpdate();
  void drawTab(int index, Boolean selected = False);
  void input(XEvent *event);
  int findLabel(char *label);
  int findTab(int x, int y);
  Boolean matchTab(int index, int x, int y);
  int tabWidth(int index);
  int computeWidth(int index);
  int tabOffset(int index);
  void computeTabLayout();
  int computeEndTab(int startIndex);
  void drawLeftEnd();
  void drawRightEnd();
  void postMenu(XButtonEvent *event, Boolean right);
  void menuSelect(Widget w);
  void createTabMenu();
  void tabsChanged();
  void invalidateMenu();
  void curveCorner(int x, int y, int dx, int dy, XPoint *points);

  static void input_stub(Widget w, XtPointer clientData, XtPointer callData);
  static void menu_stub(Widget w, XtPointer clientData, XtPointer callData);
  static Boolean update_stub(XtPointer clientData);

  Widget _label;
  Boolean _horiz, _uniform;
  int _numInfo, _sizeInfo;
  VkTabInfo *_info;
  Pixel _selectedTabBg, _labelBg, _labelFg;
  Dimension _marginWidth, _marginHeight, _tabHeight;
  XmFontList _fontList;
  int _lineThickness, _sideOffset, _endSpacing, _endMultiplier, _pixmapSpacing;
  int _curvature, _curveMultiplier;
  GC _gc, _gcErase, _gcSelected;
  int _selected;
  XtWorkProcId _updateId;
  int _startTab, _endTab;
  Boolean _freezeLayout;
  VkPopupMenu *_tabMenu;
  int _maxWidth, _vertHeight;
  int _leftMenuOffset, _rightMenuOffset;
  XFontStruct *_fs;

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkTabArea(const VkTabArea&);
    VkTabArea &operator= (const VkTabArea&);
};

#endif
