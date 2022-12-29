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
#ifndef VKOVERVIEW_H
#define VKOVERVIEW_H

// This class is solely for the internal use of VkGraph.  It is not
// otherwise useful to applications.  This header file should not have been
// shipped, and may get removed.

#include <Vk/VkWindow.h>


class VkOverview : public VkWindow {

  public:

    VkOverview(const char * name, Widget);
    ~VkOverview();
    virtual const char* className();
    virtual Widget setUpInterface(Widget );

  protected:

    virtual void    handleWmDeleteMessage();

    Widget _graphWidget;

    static void skewOverviewScaleCallback(Widget, XtPointer, XtPointer);
    static void showOverviewArcsCallback(Widget, XtPointer, XtPointer);
    static void closeOverviewCallback(Widget, XtPointer, XtPointer);

  private:

    static String _resources[];

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkOverview(const VkOverview&);
    VkOverview &operator= (const VkOverview&);
}; 

#endif
