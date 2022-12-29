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
//////////////////////////////////////////////////////////////
//
// Header file for VkGang
//
//////////////////////////////////////////////////////////////

// VkGang is a very narrow specialized component that never was fully
// implemented, and is not used.  There is no man page.  You should avoid
// VKGang, too.

#ifndef _VKGANG_H
#define _VKGANG_H
#include <Vk/VkComponent.h>

class VkGangedGroup;

class VkGang : public VkComponent
{ 

  public:

    VkGang(const char *, Widget);
    ~VkGang();
    const char* className();

  private: 

    // Array that describes interactions with Xt resource manager

    static String      _defaultVkGangResources[];

    static void gangCallback(Widget, XtPointer, XtPointer);

  VkGangedGroup *_group;

  protected: 

    virtual void gang(Widget, XtPointer);

    // Widgets created by this class

    Widget  _gangToggle;
    Widget  _grid;
    Widget  _dash;
    Widget  _leftLabel;
    Widget  _rightLabel;
    Widget  _leftScale;
    Widget  _rightScale;
    Widget  _springBox;

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkGang(const VkGang&);
    VkGang &operator= (const VkGang&);
};
#endif

