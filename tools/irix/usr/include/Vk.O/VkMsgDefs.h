#ifndef VK_MSG_DEFS
#define VK_MSG_DEFS

typedef struct {
  char *procid;
  int fd;
} VkMsgID;

#define VK_MSG_ALL_MSG_ARG_TYPE		"ALL"
#define VK_MSG_BOTH			TT_BOTH
#define VK_MSG_BSTRING_MSG_ARG_TYPE	"bstring"
#define VK_MSG_CALLBACK_CONTINUE	TT_CALLBACK_CONTINUE
#define VK_MSG_CALLBACK_PROCESSED	TT_CALLBACK_PROCESSED
#define VK_MSG_CATEGORY_UNDEFINED	TT_CATEGORY_UNDEFINED
#define VK_MSG_CREATED			TT_CREATED
#define VK_MSG_FAILED			TT_FAILED
#define VK_MSG_FILE_IN_SESSION		TT_FILE_IN_SESSION
#define VK_MSG_HANDLE			TT_HANDLE
#define VK_MSG_HANDLED			TT_HANDLED
#define VK_MSG_IN			TT_IN
#define VK_MSG_INOUT			TT_INOUT
#define VK_MSG_INT_MSG_ARG_TYPE		TT_INT_MSG_ARG_TYPE
#define VK_MSG_NOTICE			TT_NOTICE
#define VK_MSG_OBSERVE			TT_OBSERVE
#define VK_MSG_OK			TT_OK
#define VK_MSG_OUT			TT_OUT
#define VK_MSG_QUEUED			TT_QUEUED
#define VK_MSG_REJECTED			TT_REJECTED
#define VK_MSG_REQUEST			TT_REQUEST
#define VK_MSG_SCOPE_NONE		TT_SCOPE_NONE
#define VK_MSG_SENT			TT_SENT
#define VK_MSG_SESSION			TT_SESSION
#define VK_MSG_STARTED			TT_STARTED
#define VK_MSG_STATE_LAST		TT_STATE_LAST
#define VK_MSG_STRING_MSG_ARG_TYPE	TT_STRING_MSG_ARG_TYPE
#define VK_MSG_WRN_LAST			TT_WRN_LAST

#define VkMsgCallbackAction		Tt_callback_action
#define VkMsgCategory			Tt_category
#define VkMsgMemory			int
#define VkMsgMessage			Tt_message
#define VkMsgMode			Tt_mode
#define VkMsgPattern			Tt_pattern
#define VkMsgScope			Tt_scope
#define VkMsgState			Tt_state
#define VkMsgStatus			Tt_status

#endif
