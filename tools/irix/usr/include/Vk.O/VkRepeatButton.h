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
#ifndef _VK_REPEAT_BUTTON
#define _VK_REPEAT_BUTTON

#include <Vk/VkComponent.h>

enum VkRepeatButtonType { RB_pushButton, RB_pushButtonGadget,
			  RB_arrowButton, RB_arrowButtonGadget };

class VkRepeatButton : public VkComponent {
  
  public:
    
    static const char *const buttonCallback;
    
    VkRepeatButton(char *name, Widget, VkRepeatButtonType type);
    ~VkRepeatButton();
    
    virtual const char* className();
    
    VkRepeatButtonType type() { return _type; }
    void setParameters(long initial, long repeat){ initialDelay = initial; repeatDelay = repeat; }

  protected:

    void armButton(XmAnyCallbackStruct *cb);
    void disarmButton(XmAnyCallbackStruct *cb);
    void activateButton(XmAnyCallbackStruct *cb);
    void doRepeat();
    void clearTimeOuts();
    void activateCallback();
    
    
    VkRepeatButtonType _type;
    int lastReason;
    XEvent lastEvent;
    Boolean validEvent;
    long initialDelay, repeatDelay;
    XtIntervalId initialTimeOut, repeatTimeOut;

  private:
    
    static void arm_button(Widget w, XtPointer client_data, XtPointer call_data);
    static void disarm_button(Widget w, XtPointer client_data,
			      XtPointer call_data);
    static void activate_button(Widget w, XtPointer client_data,
				XtPointer call_data);
    static void repeat_timeout(XtPointer client_data, XtIntervalId *id);

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkRepeatButton(const VkRepeatButton&);
    VkRepeatButton &operator= (const VkRepeatButton&);
};

#endif
