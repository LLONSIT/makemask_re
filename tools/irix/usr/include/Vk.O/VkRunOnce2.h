#ifndef VkRunOnce2_H
#define VkRunOnce2_H

#include <Vk/VkCallbackObject.h>
#include <Xm/AtomMgr.h>

class VkNameList;

class VkRunOnce2 : public VkCallbackObject {

  public:

    static const char*  const invokedCallback;

    VkRunOnce2(Boolean autoRaise = FALSE);
  
    VkRunOnce2(VkNameList*,
	      Boolean perhost = FALSE,
	      const char *name = NULL,
	      Boolean autoRaise = TRUE);

    VkRunOnce2(char **args, int numArgs,
	      Boolean perhost = FALSE,
	      const char *name = NULL,
	      Boolean autoRaise = TRUE);    
  
    virtual ~VkRunOnce2();

    int numArgs();
    char *arg(int);

  void notifyOthers(VkNameList*,
		    Boolean perhost = FALSE,
		    const char *name = NULL);

  void notifyOthers(char **args, int numArgs,
		    Boolean perhost = FALSE,
		    const char *name = NULL);    

  void takeCharge();

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
    VkRunOnce2(const VkRunOnce2&);
    VkRunOnce2 &operator= (const VkRunOnce2&);
};


#endif
