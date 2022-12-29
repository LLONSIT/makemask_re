#ifndef _VK_SO_APP_H
#define _VK_SO_APP_H

#include <Vk/VkApp.h>

class VkSoApp  : public VkApp { 

  public:

    VkSoApp ( char           *appClassName,
            int              *arg_c, 
            char            **arg_v,
            XrmOptionDescRec *optionList       = NULL,
            int               sizeOfOptionList = 0);

    VkSoApp ( char           *appClassName,
            int              *arg_c, 
            char            **arg_v,
	    ArgList	      argList,
	    Cardinal	      argCount,
	    void            (*preRealizeFunction)(Widget w),
            XrmOptionDescRec *optionList,
            int               sizeOfOptionList);
            
    ~VkSoApp();

    void run();

  protected:

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkSoApp(const VkSoApp&);
    VkSoApp &operator= (const VkSoApp&);
};

#endif

