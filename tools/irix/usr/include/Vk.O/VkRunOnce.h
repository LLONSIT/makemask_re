#ifndef VKRUNONCE_H
#define VKRUNONCE_H

#include <Vk/VkCallbackObject.h>
#include <Xm/AtomMgr.h>

class VkNameList;

class VkRunOnce : public VkCallbackObject {

  public:

    static const char*  const invokedCallback;

    VkRunOnce(VkNameList*, Boolean perhost = FALSE, const char *name = NULL, Boolean autoRaise = TRUE);
    virtual ~VkRunOnce();

    int numArgs();
    char *arg(int);

  protected:

     Atom        _property;
     VkNameList *_args;
     void handleClientMessage();

   private:

     Boolean _autoRaise;
     static void handleClientMessageCallback(Widget, XtPointer, XEvent *, Boolean *);
     void show();

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkRunOnce(const VkRunOnce&);
    VkRunOnce &operator= (const VkRunOnce&);
};


#endif
