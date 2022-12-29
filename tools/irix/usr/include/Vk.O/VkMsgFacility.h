#ifndef VK_MSG_FACILITY
#define VK_MSG_FACILITY

#include <X11/Intrinsic.h>
#include "VkMsg.h"

#define DEFAULT_SYNC_TIMEOUT	-1

class VkMsgFacility;

extern VkMsgFacility *theMessageFacility;

enum VkMsgFacilityReason { VK_MSG_FACILITY_NOTICE, VK_MSG_FACILITY_REQUEST,
			   VK_MSG_FACILITY_REQUEST_SPECIFIC,
			   VK_MSG_FACILITY_REPLY, VK_MSG_FACILITY_FAILED,
			   VK_MSG_FACILITY_STARTED };

enum VkMsgActionType { VK_MSG_ACTION_OBSERVE, VK_MSG_ACTION_HANDLE,
		       VK_MSG_ACTION_HANDLE_SPECIFIC,
		       VK_MSG_ACTION_REPLY, VK_MSG_ACTION_FAIL,
		       VK_MSG_ACTION_START };

typedef Boolean (*VkMsgFacilityCallback)(
#if NeedFunctionPrototypes
  VkMsgFacility*	/* obj */,
  void*			/* client_data */,
  VkMsgFacilityReason	/* reason */,  
  VkMsgMessage		/* msg_in */,
  char*			/* op */,
  int			/* argc */,
  VkMsgArg*		/* argv */
#endif
);

typedef struct {
  VkMsgMessage pendingMessage;
  VkMsgState pendingState;
  Boolean pendingReceived;
  Boolean expired;
} ReplyWaitInfo;

class VkMsgFacility {
public:
  VkMsgFacility(Widget w, const char *ptid = NULL, const char *sessid = NULL);
  ~VkMsgFacility();

  void connect(char *sessid = NULL);
  VkMsgStatus joinFile(char *filepath);
  void setCallback(VkMsgFacilityCallback callback, void *client_data);
  char *getPtype() { return ptype; }

  VkMsgPattern registerPattern(char *op,
			       VkMsgCategory category = VK_MSG_OBSERVE);
  VkMsgPattern createPattern(char *op,
			     VkMsgCategory category = VK_MSG_OBSERVE);
  VkMsgStatus registerPattern(VkMsgPattern p)
    { return VkMsgPatternRegister(p); }
  VkMsgStatus unregisterPattern(VkMsgPattern p)
    { return VkMsgPatternUnregister(p); }
  VkMsgStatus destroyPattern(VkMsgPattern p)
    { return VkMsgPatternDestroy(p); } 

  void sendNotice(char *op, int argc, VkMsgArg *argv);
  void sendNotice(char *op);
  void sendStringNotice(char *op ...);
  void sendIntNotice(char *op ...);

  void sendFileNotice(char *op, char *file, int argc, VkMsgArg *argv);
  void sendFileNotice(char *op, char *file);
  void sendStringFileNotice(char *op, char *file ...);
  void sendIntFileNotice(char *op, char *file ...);

  VkMsgMessage sendRequest(char *op, int argc, VkMsgArg *argv);
  VkMsgMessage sendRequest(char *op);
  VkMsgMessage sendSyncRequest(char *op, int argc, VkMsgArg *argv,
			       int timeout = DEFAULT_SYNC_TIMEOUT);
  VkMsgMessage sendSyncRequest(char *op, int timeout = DEFAULT_SYNC_TIMEOUT);

  VkMsgMessage sendFileRequest(char *op, char *file, int argc, VkMsgArg *argv);
  VkMsgMessage sendFileRequest(char *op, char *file);
  VkMsgMessage sendSyncFileRequest(char *op, char *file,
				   int argc, VkMsgArg *argv,
				   int timeout = DEFAULT_SYNC_TIMEOUT);
  VkMsgMessage sendSyncFileRequest(char *op, char *file,
				   int timeout = DEFAULT_SYNC_TIMEOUT);

  VkMsgMessage sendRequest(VkMsgMessage msg_out);

  void composeBegin();
  void composeAdd(VkMsgArg *arg);
  void composeAdd(char *val, VkMsgMode mode = VK_MSG_IN);
  void composeAdd(int ival, VkMsgMode mode = VK_MSG_IN);
  void composeAdd(unsigned char *val, int len, VkMsgMode mode = VK_MSG_IN);
  VkMsgArg *composeList() { return compose; }
  int composeNum() { return composeCount; }

  char *sessionID();
  Atom sessionProperty() { return _sessionProperty; }

  void setDefaultSession(const char *sessid);
  char *computeSGISession();

protected:
  char *startPrivateSession();
  char *getCaseSession(Boolean checkSelection = True);
  char *getCaseProperty();
  char *getDefaultSession();
  void breakOutOfEventLoop();
  ReplyWaitInfo *findReplyWaitInfo(VkMsgMessage msg);
  int newReplyWaitInfo();
  void popReplyWaitInfo();
  char *getRootProperty(char *pname);

  virtual Boolean defaultCallback(VkMsgFacilityReason reason,
				  VkMsgMessage msg_in,
				  char *op, int argc, VkMsgArg *argv,
				  Boolean *deleteMessage);
  virtual VkMsgCallbackAction receiveReply(VkMsgMessage msg_in,
					   VkMsgPattern pat);

  void connectToXt(Widget w);
  void receiveMessage();
  Boolean callCallback(VkMsgFacilityReason reason, VkMsgMessage msg_in,
		       char *op, int argc, VkMsgArg *argv);
  char *makePathExplicit(char *path);
  VkMsgScope messageScope();
  Boolean waitForReply(VkMsgMessage msg, int timeout);

  static void waitTimeOut(XtPointer client_data, XtIntervalId *);
  static void receive_message(XtPointer client_data, int *source,
			      XtInputId *id);
  static VkMsgCallbackAction receive_reply(VkMsgMessage msg_in,
					   VkMsgPattern pat);

  VkMsgFacilityCallback callback;
  void *callbackData;
  VkMsgID msg;
  VkMsgArg *compose;
  int composeSize, composeCount;
  char *sgi_session;
  Atom _sessionProperty;
  char *ptype;
  char *sessionId;
  int numReplyWait, sizeReplyWait;
  ReplyWaitInfo *replyWaitInfo;
  Boolean firstConnect;
  Atom selectionAtom;
  int defaultSyncTimeout;
};

#endif
