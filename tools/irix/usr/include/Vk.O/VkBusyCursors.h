///////////////////////////////////////////////////
// VkBusyCursors.h
///////////////////////////////////////////////////

#ifndef VKBUSYCURSORS_H
#define VKBUSYCURSORS_H

#include <Vk/VkCursorList.h>

class VkBusyCursors : public VkCursorList {
    
  public:
    
    VkBusyCursors( );

  protected:
    
    void createCursor(int index);   // Overrides base class' pure virtual

  private:
    
    XColor  xcolors[2];    

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkBusyCursors(const VkBusyCursors&);
    VkBusyCursors &operator= (const VkBusyCursors&);
};


#endif
