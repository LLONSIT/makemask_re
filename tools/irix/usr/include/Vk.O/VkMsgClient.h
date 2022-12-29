#ifndef VK_MSG_CLIENT
#define VK_MSG_CLIENT

#include <Vk/VkMsgService.h>

typedef Boolean (*VkMsgClientAction)(
#if NeedFunctionPrototypes
  void*			/* client_data */,
  VkMsgFacilityReason	/* reason */,  
  VkMsgMessage		/* msg_in */,
  char*			/* op */,
  int			/* argc */,
  VkMsgArg*		/* argv */
#endif
);

typedef struct {
  char *name;
  VkMsgClientAction proc;
  void *client_data;
  Boolean deleteMessage;
} VkMsgClientTranslationPair;

class VkMsgClient {
public:
  VkMsgClient(VkMsgFacilityCallback callback = NULL, void *client_data = NULL);
  ~VkMsgClient();
 
  void registerPattern(char *op,
		       VkMsgCategory category = VK_MSG_OBSERVE)
    { theMessageService->registerPattern(op, category); }

  void updatePatterns() { theMessageService->updatePatterns(); }

  VkMsgPattern addAction(char *op, VkMsgClientAction proc,
			 void *client_data, VkMsgActionType type,
			 Boolean deleteMessage = True);
  VkMsgPattern createAction(char *op, VkMsgClientAction proc,
			    void *client_data, VkMsgActionType type,
			    Boolean deleteMessage = True);
  void removeAction(VkMsgPattern pat);

  void addTranslation(char *name, VkMsgClientAction proc, void *client_data,
		      Boolean deleteMessage = True);
  void removeTranslation(char *name);
  Boolean findAction(char *name, VkMsgClientAction *proc,
		     void **client_data, Boolean *deleteMessage);

  void sendNotice(char *op, int argc, VkMsgArg *argv)
    { theMessageService->sendNotice(op, argc, argv); }
  void sendNotice(char *op)
    { theMessageService->sendNotice(op); }
  void sendStringNotice(char *op ...);
  void sendIntNotice(char *op ...);

  void sendFileNotice(char *op, char *file, int argc, VkMsgArg *argv)
    { theMessageService->sendFileNotice(op, file, argc, argv); }
  void sendFileNotice(char *op, char *file)
    { theMessageService->sendFileNotice(op, file); }
  void sendStringFileNotice(char *op, char *file ...);
  void sendIntFileNotice(char *op, char *file ...);

  VkMsgMessage sendRequest(char *op, int argc, VkMsgArg *argv)
    { return theMessageService->sendRequest(this, op, argc, argv); }
  VkMsgMessage sendRequest(char *op)
    { return theMessageService->sendRequest(this, op); }
  VkMsgMessage sendSyncRequest(char *op, int argc, VkMsgArg *argv,
			       int timeout = DEFAULT_SYNC_TIMEOUT)
    { return theMessageService->sendSyncRequest(op, argc, argv, timeout); }
  VkMsgMessage sendSyncRequest(char *op, int timeout = DEFAULT_SYNC_TIMEOUT)
    { return theMessageService->sendSyncRequest(op, timeout); }
  VkMsgMessage sendRequest(VkMsgMessage msg_out)
    { return theMessageService->sendRequest(this, msg_out); }

  VkMsgMessage sendFileRequest(char *op, char *file, int argc, VkMsgArg *argv)
    { return theMessageService->sendFileRequest(this, op, file, argc, argv); }
  VkMsgMessage sendFileRequest(char *op, char *file)
    { return theMessageService->sendFileRequest(this, op, file); }
  VkMsgMessage sendSyncFileRequest(char *op, char *file,
				   int argc, VkMsgArg *argv,
				   int timeout = DEFAULT_SYNC_TIMEOUT)
    { return theMessageService->sendSyncFileRequest(op, file, argc, argv,
						    timeout); }
  VkMsgMessage sendSyncFileRequest(char *op, char *file,
				   int timeout = DEFAULT_SYNC_TIMEOUT)
    { return theMessageService->sendSyncFileRequest(op, file, timeout); }

  void composeBegin()
    { theMessageService->composeBegin(); }
  void composeAdd(VkMsgArg *arg)
    { theMessageService->composeAdd(arg); }
  void composeAdd(char *val, VkMsgMode mode = VK_MSG_IN)
    { theMessageService->composeAdd(val, mode); }
  void composeAdd(int ival, VkMsgMode mode = VK_MSG_IN)
    { theMessageService->composeAdd(ival, mode); }
  void composeAdd(unsigned char *val, int len, VkMsgMode mode = VK_MSG_IN)
    { theMessageService->composeAdd(val, len, mode); }
  VkMsgArg *composeList() { return theMessageService->composeList(); }
  int composeNum() { return theMessageService->composeNum(); }
 
  VkMsgStatus registerPattern(VkMsgPattern p);
  VkMsgStatus unregisterPattern(VkMsgPattern p);
  VkMsgStatus destroyPattern(VkMsgPattern p)
    { return theMessageService->destroyPattern(p); }

protected:
  int findActionIndex(char *name);
  void addMangledTranslation(char *name, VkMsgClientAction proc,
			     void *client_data, Boolean deleteMessage = True);

  int numTranslations, sizeTranslations;
  VkMsgClientTranslationPair *translationPairs;
  int numPatterns, sizePatterns;
  VkMsgPattern *patterns;
};

#endif
