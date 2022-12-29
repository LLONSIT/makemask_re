#ifndef VK_MSG_APP
#define VK_MSG_APP

#include <Vk/VkApp.h>
#include <Vk/VkMsgService.h>
#include <Vk/VkMsgClient.h>

class VkMsgApp;

extern VkMsgApp *theMsgApplication;

class VkMsgApp : public VkApp {
public:
  VkMsgApp(char             *appClassName,
	   int              *arg_c, 
	   char            **arg_v,
	   XrmOptionDescRec *optionList       = NULL,
	   int               sizeOfOptionList = 0,
	   const char       *ptid = NULL,
	   const char	    *sessid = NULL,
	   Boolean	     noProtocol = False);

  VkMsgApp(char             *appClassName,
	   int              *arg_c, 
	   char            **arg_v,
	   ArgList	     argList,
	   Cardinal	     argCount,
	   void            (*preRealizeFunction)(Widget w),
	   XrmOptionDescRec *optionList,
	   int               sizeOfOptionList,
	   const char       *ptid,
	   const char	    *sessid,
	   Boolean	     noProtocol);

  ~VkMsgApp();

  virtual void run();

  VkMsgClient *messageClient() { return _client; }

  Boolean noProtocol() { return _noProtocol; }

protected:

  VkMsgService *_service;
  VkMsgClient *_client;
  Boolean _noProtocol;

private:

  static Boolean iconify_handler(void *client_data, VkMsgFacilityReason reason,
				 VkMsgMessage msg_in,
				 char *op, int argc, VkMsgArg *argv);
  static Boolean raise_handler(void *client_data, VkMsgFacilityReason reason,
			       VkMsgMessage msg_in,
			       char *op, int argc, VkMsgArg *argv);
  static Boolean quit_handler(void *client_data, VkMsgFacilityReason reason,
			      VkMsgMessage msg_in,
			      char *op, int argc, VkMsgArg *argv);
  static Boolean forced_quit(void *client_data, VkMsgFacilityReason reason,
			     VkMsgMessage msg_in,
			     char *op, int argc, VkMsgArg *argv);
  void VkMsgAppInitialize(char   *appClassName,
	   int              *arg_c, 
	   char            **arg_v,
	   XrmOptionDescRec *optionList       = NULL,
	   int               sizeOfOptionList = 0,
	   const char       *ptid = NULL,
	   const char	    *sessid = NULL,
	   Boolean	     noProtocol = False);
};

#endif
