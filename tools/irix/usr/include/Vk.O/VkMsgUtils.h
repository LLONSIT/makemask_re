#ifndef VK_MSG_UTILS
#define VK_MSG_UTILS

#ifdef __cplusplus			/* do not leave open across includes */
extern "C" {					/* for C++ V2.0 */
#endif

typedef struct vkMsgBValue {
  unsigned char *val;
  int len;
} VkMsgBValue;

typedef union vkMsgValue {
  int ival;
  char *val;
  VkMsgBValue bval;
} VkMsgValue;

typedef struct vkMsgArg {
  char *type;
  VkMsgValue value;
  VkMsgMode mode;
} VkMsgArg;

#define VkMsgTypeIsInt(type)	 ((type) && !strcmp((type), VK_MSG_INT_MSG_ARG_TYPE))
#define VkMsgTypeIsString(type)	 ((type) && !strcmp((type), VK_MSG_STRING_MSG_ARG_TYPE))
#define VkMsgTypeIsBString(type) ((type) && !strcmp((type), VK_MSG_BSTRING_MSG_ARG_TYPE))

extern VkMsgPattern VkMsgCreatePattern(char *op, VkMsgCategory category,
				       VkMsgScope scope);
extern void VkMsgParseArguments(VkMsgMessage msg_in, int *argc_return,
				VkMsgArg **argv_return);
extern void VkMsgFreeArguments(int argc, VkMsgArg *argv);
extern VkMsgMessage VkMsgCreateANotice(char *op, int argc, VkMsgArg *argv,
				       VkMsgScope scope);
extern VkMsgMessage VkMsgCreateARequest(char *op, int argc, VkMsgArg *argv,
					VkMsgScope scope);
extern void VkMsgAddArgs(VkMsgMessage msg_out, int argc, VkMsgArg *argv);

#ifdef __cplusplus
}
#endif

#endif
