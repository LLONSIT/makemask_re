
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

#ifndef VKOUTLINE_ASB_H
#define VKOUTLINE_ASB_H

#include <Vk/VkOutline.h>
#include <Sgm/ScrollBar.h>

class VkOutlineASB : public VkOutline {

 public:

    VkOutlineASB (const char *, Widget );
    virtual ~VkOutlineASB ();

    void displayAll ();
    virtual void toggleChildren (int position);

    void highlight (char** items, int highlightIndex);
    void highlight (int position, int highlightIndex);
    void unhighlight (int highlightIndex);

    void setAnnotation (int highlightIndex, Boolean);

 protected:

    Widget _scrollBarW;
    Boolean _annotationStates [MaxAttributeSets];

    void paintAsbPixmap (ASBCallbackStruct*);

  private:

    static int autoScrollPos;

    void walkToPaint (VkOlNode*, Pixmap, float, int, int);
    static void ASBpixmapCallback (Widget, XtPointer, XtPointer);

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkOutlineASB(const VkOutlineASB&);
    VkOutlineASB &operator= (const VkOutlineASB&);
};

#endif

