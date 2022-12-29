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
#ifndef VKCHECKBOX_H
#define VKCHECKBOX_H

#include <Vk/VkComponent.h>


class VkWidgetList;

class VkCheckBox : public VkComponent {

  public:

    static const char * const itemChangedCallback;
    
    VkCheckBox(const char * name, Widget);
    ~VkCheckBox();

    Widget addItem(char *, Boolean state = 0, XtCallbackProc proc = 0, XtPointer clientData = 0);

    void setValue(int index, Boolean newValue);
    void setValues(Boolean *values, int numValues);
    int getValue(int index);

    virtual const char* className();


  protected:

    VkWidgetList *_widgetList;

    Widget     _rc;
    Widget     _label;

    virtual void valueChanged(int index, Boolean newValue);

    
  private:

    static void valueChangedCallback(Widget, XtPointer, XtPointer);

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkCheckBox(const VkCheckBox&);
    VkCheckBox &operator= (const VkCheckBox&);
    
}; 

#endif
