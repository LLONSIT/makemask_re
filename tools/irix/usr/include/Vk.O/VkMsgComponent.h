#ifndef VK_MSG_COMPONENT
#define VK_MSG_COMPONENT

#include <Vk/VkComponent.h>
#include <Vk/VkMsgClient.h>

class VkMsgComponent : public VkComponent {
public:
  VkMsgComponent(const char *name);
  ~VkMsgComponent();

  virtual void show();

  VkMsgClient *messageClient() { return client; }

  void updatePatterns() { client->updatePatterns(); }

  VkMsgPattern addAction(char *name, VkMsgClientAction proc, void *client_data,
			 VkMsgActionType type, Boolean deleteMessage = True)
    { return client->addAction(name, proc, client_data, type, deleteMessage); }
  VkMsgPattern createAction(char *name, VkMsgClientAction proc,
			    void *client_data, VkMsgActionType type,
			    Boolean deleteMessage = True)
    { return client->createAction(name, proc, client_data, type,
				  deleteMessage); }
  void removeAction(VkMsgPattern pat)
    { client->removeAction(pat); }
  void addTranslation(char *name, VkMsgClientAction proc, void *client_data,
		      Boolean deleteMessage = True)
    { client->addTranslation(name, proc, client_data, deleteMessage); }
  void removeTranslation(char *name)
    { client->removeTranslation(name); }

  VkMsgStatus registerPattern(VkMsgPattern p)
    { return client->registerPattern(p); }
  VkMsgStatus unregisterPattern(VkMsgPattern p)
    { return client->unregisterPattern(p); }
  VkMsgStatus destroyPattern(VkMsgPattern p)
    { return client->destroyPattern(p); }

protected:
  virtual Boolean messageCallback(VkMsgFacilityReason reason,
				  VkMsgMessage msg_in,
				  char *op, int argc, VkMsgArg *argv);

  static Boolean message_callback(VkMsgFacility *obj, void *client_data,
				  VkMsgFacilityReason reason,
				  VkMsgMessage msg_in,
				  char *op, int argc, VkMsgArg *argv);

  VkMsgClient *client;
};

#endif
