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
#ifndef VKAlignmentGroup_H
#define VKAlignmentGroup_H

#include <Vk/VkWidgetList.h>

class VkComponent;
class VkOptionMenu;

class VkAlignmentGroup : public VkWidgetList{
    
  public:
    
     VkAlignmentGroup ( );
    ~VkAlignmentGroup ( );

     virtual  void add(Widget);
     virtual  void add(VkComponent*);
     virtual  void add(VkOptionMenu*);

     void alignLeft();
     void alignRight(); // Not yet implemented
     void alignTop();
     void alignBottom(); // Not yet implemented
     void alignWidth();
     void alignHeight();
     void distributeVertical(); // Not yet implemented
     void distributeHorizontal(); // Not yet implemented
     void makeNormal();  // Not yet implemented

     Dimension  width() { return _maxWidth; }
     Dimension  height() { return _maxHeight; }
     Position  x() { return _x; }
     Position  y() { return _y; }

  protected:

    Dimension _maxWidth, _maxHeight;
    Position _x, _y;

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkAlignmentGroup(const VkAlignmentGroup&);
    VkAlignmentGroup &operator= (const VkAlignmentGroup&);
};
#endif

