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
#ifndef VKHELP_H
#define VKHELP_H

#include <Vk/VkHelpAPI.h>
#include <Vk/VkComponent.h>

extern void VkAddContextSmartHelpCallback(Widget);
extern void VkHelpCallback(Widget , XtPointer , XtPointer );
extern void VkAddContextHelpCallback(Widget , char * ); 
extern void VkAddContextHelpCallback(class VkComponent *, Widget , char * );
extern void VkAddContextHelpCallback(class VkComponent *, Widget );
extern void VkInitHelp();

#define XmCR_SMARTHELP  57

struct XmHelpCallbackStruct {
    int      reason;
    XEvent  *event;
    Widget   widget;
};

#endif
