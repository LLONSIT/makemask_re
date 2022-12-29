////////////////////////////////////////////////////////////////////////////////
///////   Copyright 1995, Silicon Graphics, Inc.  All Rights Reserved.   ///////
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

//////////////
//
// An interruptible Busy dialog which displays a progress meter.
//
//////////////


#ifndef VKPROGRESSDIALOG_H
#define VKPROGRESSDIALOG_H

#include <Vk/VkInterruptDialog.h>

class VkProgressDialog : public VkInterruptDialog {

  public:
    
    VkProgressDialog(const char* name, Boolean showCancel = TRUE);
    ~VkProgressDialog();
    
    virtual void setPercentDone(int);

  protected:

    Widget prepost ( const char      *msg, 
		     XtCallbackProc   okCB,
		     XtCallbackProc   cancelCB,
		     XtCallbackProc   applyCB,
		     XtPointer       clientData,
		     const char      *helpString,
		     VkSimpleWindow  *parentWindow);
    
    virtual Widget createDialog(Widget);
    
    Widget		_thermometer;
    int			_percentDone;

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkProgressDialog(const VkProgressDialog&);
    VkProgressDialog &operator= (const VkProgressDialog&);

};

extern VkProgressDialog *getTheProgressDialog();
extern VkProgressDialog *getTheDefaultProgressDialog();
    
#define theProgressDialog getTheProgressDialog()
#define theDefaultProgressDialog getTheDefaultProgressDialog()

#endif
