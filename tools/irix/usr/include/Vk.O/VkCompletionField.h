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
#ifndef VKCOMPLETIONFIELD_H
#define VKCOMPLETIONFIELD_H

#include <Vk/VkComponent.h>

class VkNameList;

class VkCompletionField : public VkComponent {

  public:

    static const char * const enterCallback;
    
    VkCompletionField(const char *name, Widget);
    ~VkCompletionField();

    void add(char* name);
    void addList(char* name); // Comma-separated list
    
    void clear(VkNameList *nameList = NULL);	// existing list deleted


    char *getText();	
    virtual const char* className();

    static VkComponent *CreateVkCompletionField(const char *name, Widget parent);
	
  private:

    static void expandCallback(Widget, XtPointer, XtPointer);
    static void activateCallback(Widget, XtPointer, XtPointer);

  protected:

    VkNameList *_currentMatchList;
    VkNameList   *_nameList;

    virtual void expand(XmTextVerifyCallbackStruct *);
    virtual void activate(XmTextVerifyCallbackStruct *);

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkCompletionField(const VkCompletionField&);
    VkCompletionField &operator= (const VkCompletionField&);
}; 

#endif
