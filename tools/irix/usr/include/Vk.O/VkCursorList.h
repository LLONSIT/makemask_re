#ifndef VKCURSORLIST_H
#define VKCURSORLIST_H

#include <Xm/Xm.h>

class VkCursorList {
    
  public:
    
    virtual ~VkCursorList();
    
    Cursor next();
    Cursor current();
    void reset();

  protected:
    
    int       _numCursors;
    int       _current;   
    Pixmap   *_cursorList; 

    virtual void createCursor(int index) = 0; // Derived class must implement    
    VkCursorList ( int  );   

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkCursorList(const VkCursorList&);
    VkCursorList &operator= (const VkCursorList&);
};
#endif
