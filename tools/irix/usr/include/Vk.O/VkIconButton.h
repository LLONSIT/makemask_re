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
#ifndef _VK_ICON_BUTTON
#define _VK_ICON_BUTTON

#include <Vk/VkComponent.h>


class VkIconButton : public VkComponent {
  
  public:

  VkIconButton(char *name, Widget, char **, Boolean showLabel = TRUE);
  ~VkIconButton();

  virtual const char* className();

  protected:

    static void enterHandler(Widget, XtPointer, XEvent *, Boolean *);
    static void leaveHandler(Widget, XtPointer, XEvent *, Boolean *);

    void enter();
    void leave();

    void doRealMotif(Widget parent, char **xpmIcon, Boolean showLabel);
    void doBuffy(Widget parent, char **xpmIcon, Boolean showLabel);

    Pixmap _pixmap, _highlitePixmap;
    Pixel _hilite, _bg;

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkIconButton(const VkIconButton&);
    VkIconButton &operator= (const VkIconButton&);

};

#endif
