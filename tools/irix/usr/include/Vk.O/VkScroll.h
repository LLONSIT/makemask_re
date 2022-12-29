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
#ifndef _VK_SCROLL_
#define _VK_SCROLL_

#include <Vk/VkComponent.h>

enum VkScrollReason { VS_none, VS_initialExpose, VS_resize, VS_troughPixmap };

typedef struct {
  class VkScroll *obj;
  VkScrollReason reason;
  int width, height, depth, maximum;
  Pixmap pixmap;
} VkScrollCallback;

class VkScroll : public VkComponent {

  public:
    
    static const char *const scrollCallback;
    
    VkScroll(const char *name, Widget);
    ~VkScroll();
    
    virtual const char* className();
    
    void setChild(Widget c);
    int getScrollPos() { return scrollPos; }
    void setScrollPos(int pos);
    Widget getClip() { return clip; }
    Widget getFrame() { return frame; }
    Widget getScrollBar() { return sb; }
    void recomputeScrollBar() { resizeClip(); }
    void reannotateScrollBar();
    void setAnnotations();

  protected:
    void scrollChanged(int value);
    void exposeClip();
    void resizeClip();
    void troughPixmap(int width, int height, int depth, int maximum,
		      Pixmap pixmap);
    void callCallback(VkScrollReason reason);
    
    Widget frame, sb, clip, child;
    int scrollPos;
    Boolean annotations;
    Dimension lastHeight;

  private:
    
    static void resize_clip(Widget w, XtPointer client_data, XEvent *event);
    static void expose_clip(Widget w, XtPointer client_data, XEvent *event);
    static void resize_child(Widget w, XtPointer client_data, XEvent *event);
    static void scroll_changed(Widget w, XtPointer client_data,
			       XtPointer call_data);
    static void trough_pixmap(Widget w, XtPointer client_data,
			      XtPointer call_data);

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkScroll(const VkScroll&);
    VkScroll &operator= (const VkScroll&);
};

#endif
