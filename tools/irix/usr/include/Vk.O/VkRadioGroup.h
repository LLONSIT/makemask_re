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
#ifndef VKRadioGroup_H
#define VKRadioGroup_H

#include <Xm/Xm.h>
#include <Vk/VkWidgetList.h>

class VkComponent;

class VkRadioGroup : public VkWidgetList {
    
  public:
    
     VkRadioGroup ( );
    ~VkRadioGroup ( );
     void add(Widget);
     void add(VkComponent *);

    void clear(); // Caution: This function is not virtual wrt. to VkWidgetList
                  // Due to binary compatibility issues

  protected:

     Pixel _ts, _bs, _bg;
     Widget _selected;
     Pixmap _selectedNormalPixmap;

     void updateSelected(Widget w);

    virtual void valueChanged ( Widget, XtPointer );
    virtual void arm ( Widget, XtPointer );

  private:
  
    static void valueChangedCallback ( Widget, XtPointer, XtPointer );
    static void armCallback ( Widget, XtPointer, XtPointer );

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkRadioGroup(const VkRadioGroup&);
    VkRadioGroup &operator= (const VkRadioGroup&);
    
};
#endif

