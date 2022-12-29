#ifndef VK_MSG_SERVICE
#define VK_MSG_SERVICE

#include <Vk/VkMsgFacility.h>

class VkMsgClient;
class VkMsgService;

extern VkMsgService *theMessageService;

#define VK_MSG_TRANSLATIONS_RESOURCE_NAME	"vkmsgTranslations"
#define VK_MSG_TRANSLATIONS_CLASS_NAME		"VkmsgTranslations"

typedef struct {
  VkMsgClient *client;
  VkMsgFacilityCallback callback;
  void *callbackData;
} VkMsgServiceInfo;

typedef struct {
  VkMsgClient *client;
  VkMsgMessage msg_out;
} VkMsgServiceRequest;

typedef struct {
  char *op;
  char *action;
  VkMsgFacilityReason reason;
  VkMsgPattern pat;
  VkMsgClient *client;
} VkMsgServicePair;

class VkMsgService : public VkMsgFacility {
public:
  VkMsgService(Widget w, const char *ptid = NULL, const char *sessid = NULL);
  ~VkMsgService();

  void registerPatterns(VkMsgClient *client, Widget w);

  void registerClient(VkMsgClient *client,
		      VkMsgFacilityCallback callback, void *client_data);
  void unregisterClient(VkMsgClient *client);

  VkMsgMessage sendRequest(VkMsgClient *client,
			   char *op, int argc, VkMsgArg *argv);
  VkMsgMessage sendRequest(VkMsgClient *client, char *op);
  VkMsgMessage sendRequest(VkMsgClient *client, VkMsgMessage msg_out);

  VkMsgMessage sendFileRequest(VkMsgClient *client,
			       char *op, char *file, int argc, VkMsgArg *argv);
  VkMsgMessage sendFileRequest(VkMsgClient *client, char *op, char *file);

  VkMsgPattern addAction(char *op, char *action, VkMsgActionType type,
			 VkMsgClient *client);
  VkMsgPattern createAction(char *op, char *action, VkMsgActionType type,
			    VkMsgClient *client);
  void removeAction(VkMsgPattern pat);
  VkMsgServicePair *findAction(VkMsgPattern pat);

  void updatePatterns();

  char *mangleTranslationName(char *name, VkMsgClient *client,
			      Boolean useCounter);

protected:
  virtual Boolean defaultCallback(VkMsgFacilityReason reason,
				  VkMsgMessage msg_in,
				  char *op, int argc, VkMsgArg *argv,
				  Boolean *deleteMessage);

  Boolean handleOneTranslation(VkMsgClient *client, char *str);
  void addOpActionPair(char *op, char *action, VkMsgFacilityReason reason,
		       VkMsgPattern pat, VkMsgClient *client);
  int findActionIndex(VkMsgPattern pat);
  char *findMatchingPattern(VkMsgPattern pat, VkMsgFacilityReason reason);
  char *findMatchingAction(char *op, VkMsgFacilityReason reason);
  char *findMatchingClientAction(char *op, VkMsgFacilityReason reason,
				 VkMsgClient *client);

  Boolean callInfoCallback(int index,
			   VkMsgFacilityReason reason, VkMsgMessage msg_in,
			   char *op, int argc, VkMsgArg *argv);
  void addRequest(VkMsgClient *client, VkMsgMessage msg_out);
  void removeRequest(int index);
  VkMsgClient *retrieveRequest(VkMsgMessage msg_in);
  Boolean callActions(VkMsgMessage msg_in, VkMsgFacilityReason reason,
		      char *op, int argc, VkMsgArg *argv,
		      Boolean *deleteMessage);
  Boolean callAction(VkMsgMessage msg_in, VkMsgFacilityReason reason,
		     char *action, char *op, int argc, VkMsgArg *argv,
		     Boolean *deleteMessage);

  int sizeInfo, numInfo;
  VkMsgServiceInfo *info;
  int sizeRequests, numRequests;
  VkMsgServiceRequest *requests;
  int sizePairs, numPairs;
  VkMsgServicePair *pairs;
};

#endif
