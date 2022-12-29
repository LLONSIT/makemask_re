////////////////////////////////////////////////////////////////////////////////
///////   Copyright 1992, Silicon Graphics, Inc.  All Rights Reserved.   ///////
//                                                                            //b
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

#ifndef VKINTERRUPTDIALOG_H
#define VKINTERRUPTDIALOG_H

#include <Vk/VkBusyDialog.h>

/*******************************************************
CLASS
    VkInterruptDialog

OVERVIEW





AUTHOR
   Doug Young
******************************************************/


class VkInterruptDialog : public VkBusyDialog {

  public:


    ////////////
    //
    //    
    VkInterruptDialog(const char* name) ;

    ////////////
    //
    //
    ~VkInterruptDialog() ;


    ////////////
    //
    //
    static const char * const interruptedCallback;


    ////////////
    //
    //
    Boolean wasInterrupted();

  protected:


    ////////////
    //
    //
    virtual Widget createDialog(Widget);

  private:

    static void fixCursorCallback(Widget, XtPointer, XtPointer);

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkInterruptDialog(const VkInterruptDialog&);
    VkInterruptDialog &operator= (const VkInterruptDialog&);
    
};

extern VkInterruptDialog *getTheInterruptDialog();
    
#define theInterruptDialog getTheInterruptDialog()


#endif
