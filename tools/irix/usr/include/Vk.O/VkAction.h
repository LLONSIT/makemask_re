#ifndef  VKACTION_H
#define VKACTION_H

#include <Xm/Xm.h> // For widget definition

class VkAction {

  public:
    
    VkAction(const char *name);
    virtual ~VkAction();

    void execute();

  protected:

    virtual void undoit() = 0;
    virtual void doit()   = 0;
    char *_name;


  private:

    static void undoCallback(Widget, XtPointer, XtPointer);

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkAction(const VkAction&);
    VkAction &operator= (const VkAction&);
    
};

#endif

