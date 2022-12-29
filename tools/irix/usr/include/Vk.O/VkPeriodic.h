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
#ifndef VKPERIODIC_H
#define VKPERIODIC_H

#include <Xm/Xm.h>

#include <Vk/VkCallbackObject.h>  // for callback-related declaration>

class VkPeriodic : public VkCallbackObject {
    

  public:
    
    static const char *const timerCallback;

    VkPeriodic ( int );
    ~VkPeriodic ( );

    void start(int newInterval = 0);     
    void stop();

  private:
    
    static void tickCallback ( XtPointer, XtIntervalId* );
    
    int          _interval;   // Time in milliseconds between updates
    XtIntervalId _id;         // Identifier of current TimeOut

  protected:

    virtual void tick();  // Called every _interval milliseconds    

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkPeriodic(const VkPeriodic&);
    VkPeriodic &operator= (const VkPeriodic&);
};
#endif

