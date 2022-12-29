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
#ifndef _VK_MODIFIED_
#define _VK_MODIFIED_

#include <X11/Intrinsic.h>
#include <Vk/VkCallbackObject.h>

enum VkModifiedReason { VM_activate, VM_valueChanged };

typedef struct {
  VkModifiedReason reason;
  class VkModified *obj;
  XEvent *event;
} VkModifiedCallback;

class VkModified : public VkCallbackObject {

  public:

    VkModified(Boolean blankIsValue = False);
    virtual ~VkModified();

    Boolean blankIsValue() { return _blankIsValue; }
    Boolean modified() { return _modified; }
    virtual void setModified(Boolean v);

    Boolean latestDisplay() { return _latest; }
    virtual void toggleDisplay();

    char *value() { return _value; }
    char *previousValue() { return _previousValue; }
    virtual void setValue(const char *v);

    virtual void fixPreviousValue(char *v, Boolean setValueAlso = True);

  protected:

    void updateModified();

    Boolean _modified, _latest;
    Dimension _width, _height;
    char *_value, *_previousValue;
    Boolean _blankIsValue, _fixedPrevious;

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkModified(const VkModified&);
    VkModified &operator= (const VkModified&);
};

class VkModifiedAttachment : public VkModified {

  public:

    static const char *const modifiedCallback;
    
    VkModifiedAttachment(Boolean blankIsValue = False,
			 Boolean autoAdjust = True,
			 Boolean incrementalChange = False);
    ~VkModifiedAttachment();
    
    virtual void setModified(Boolean v);
    virtual void toggleDisplay();
    virtual void setValue(const char *v);
    virtual void fixPreviousValue(char *v, Boolean setValueAlso = True);
    
    virtual void setParameters(Dimension width, Dimension height);
    void getParameters(Dimension *width, Dimension *height);
    
    Widget widget() { return _w; }
    Boolean autoAdjust() { return _autoAdjust; }
    
    void attach(Widget w);
    void detach();
    
    void show();
    void hide();
    
    void expose();
    void displayValue();
    
    void adjustGeometry();
    
protected:
    void buildWindow(Widget w);
    void reparentWindow(Widget w);
    void adjustWindow();
    void forceExpose();
    void setCursor();
    void setWidgetValue(Widget w, char *v);
    char *getWidgetValue(Widget w);
    void setupCallbacks(Widget w);
    void removeCallbacks(Widget w);
    void drawCornerShadows(Pixel shadow1, Pixel shadow2, Boolean etched);
    void callCallback(VkModifiedReason reason, XEvent *event = NULL);
    void updateDisplay();
    
    static void reconfig_stub(Widget w, XtPointer client_data, XEvent *ev,
			      Boolean *dispatch);
    static void expose_stub(Widget w, XtPointer client_data,
			    XtPointer call_data);
    static void input_stub(Widget w, XtPointer client_data,
			   XtPointer call_data);
    static void destroy_stub(Widget w, XtPointer client_data,
			     XtPointer call_data);
    static void activate_stub(Widget w, XtPointer client_data,
			      XtPointer call_data);
    static void value_stub(Widget w, XtPointer client_data,
			   XtPointer call_data);
    
    Display *_dpy;
    Widget _w, _parent, _area;
    Pixel _bg, _fg, _topShadow, _bottomShadow, _parentBg;
    GC _gc;
    Dimension _shadow, _highlight;
    Cursor _cursorBack, _cursorForward;
    Boolean _shown;
    unsigned char _shadowType;
    Boolean _inhibitCallback;
    Boolean _displayModified;
    Boolean _incrementalChange;
    Boolean _inhibitUpdate;
    Boolean _autoAdjust;

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkModifiedAttachment(const VkModifiedAttachment&);
    VkModifiedAttachment &operator= (const VkModifiedAttachment&);
};

#endif
