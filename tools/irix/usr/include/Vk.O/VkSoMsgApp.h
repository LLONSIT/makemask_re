#ifndef _VK_SO_MSGAPP_H
#define _VK_SO_MSGAPP_H

#include <Vk/VkMsgApp.h>

class VkSoMsgApp  : public VkMsgApp { 

  public:

    VkSoMsgApp ( char           *appClassName,
            int              *arg_c, 
            char            **arg_v,
            XrmOptionDescRec *optionList       = NULL,
            int               sizeOfOptionList = 0);

    VkSoMsgApp ( char           *appClassName,
            int              *arg_c, 
            char            **arg_v,
	    ArgList	      argList,
	    Cardinal	      argCount,
	    void            (*preRealizeFunction)(Widget w),
            XrmOptionDescRec *optionList       = NULL,
            int               sizeOfOptionList = 0);
            
    ~VkSoMsgApp();

    void run();

  protected:

  private:
};

#endif

