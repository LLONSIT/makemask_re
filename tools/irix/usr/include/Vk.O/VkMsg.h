#ifndef VK_MSG
#define VK_MSG

/*
 * Vk message library, currently based on ToolTalk.  All Vk applications should
 * only use these routines and/or VkMsgFacility and not ToolTalk routines, in
 * case the underlying messaging mechanism changes.
 */

#include <tt_c.h>
#include <Vk/VkMsgDefs.h>
#include <Vk/VkMsgUtils.h>

#ifdef __cplusplus			/* do not leave open across includes */
extern "C" {					/* for C++ V2.0 */
#endif

extern VkMsgStatus VkMsgOpen(VkMsgID *msg);
extern VkMsgStatus VkMsgConnect(VkMsgID *msg, const char *session);
extern VkMsgStatus VkMsgClose(VkMsgID *msg);
extern VkMsgStatus VkMsgDestroyRequest(VkMsgMessage msg);
extern VkMsgStatus VkMsgSend(VkMsgMessage msg);
extern VkMsgStatus VkMsgReply(VkMsgMessage msg);
extern VkMsgMessage VkMsgReceive();
extern VkMsgStatus VkMsgDestroy(VkMsgMessage msg);

#ifdef __cplusplus
}
#endif

#define VkMsgAddArg		tt_message_arg_add
#define VkMsgAddCallback	tt_message_callback_add
#define VkMsgArgBVal		tt_message_arg_bval
#define VkMsgArgIVal		tt_message_arg_ival
#define VkMsgArgMode		tt_message_arg_mode
#define VkMsgArgType		tt_message_arg_type
#define VkMsgArgVal		tt_message_arg_val
#define VkMsgArgsCount		tt_message_args_count
#define VkMsgClass		tt_message_class
#define VkMsgCreateNotice	tt_pnotice_create
#define VkMsgCreateRequest	tt_prequest_create
#define VkMsgDefaultProcId	tt_default_procid
#define VkMsgDefaultSession	tt_default_session
#define VkMsgFail		tt_message_fail
#define VkMsgFile		tt_message_file
#define VkMsgFree		tt_free
#define VkMsgIntError		tt_int_error
#define VkMsgIsErr		tt_is_err
#define VkMsgJoinFile		tt_file_join
#define VkMsgMark		tt_mark
#define VkMsgMessageState	tt_message_state
#define VkMsgOp			tt_message_op
#define VkMsgOpNum		tt_message_opnum
#define VkMsgPat		tt_message_pattern
#define VkMsgPatternArg		tt_pattern_arg_add
#define VkMsgPatternBArg	tt_pattern_barg_add
#define VkMsgPatternIArg	tt_pattern_iarg_add
#define VkMsgPatternCat		tt_pattern_category
#define VkMsgPatternCategory	tt_pattern_category_set
#define VkMsgPatternCreate	tt_pattern_create
#define VkMsgPatternDestroy	tt_pattern_destroy
#define VkMsgPatternOp		tt_pattern_op_add
#define VkMsgPatternRegister	tt_pattern_register
#define VkMsgPatternUnregister	tt_pattern_unregister
#define VkMsgPatternScope	tt_pattern_scope_add
#define VkMsgPatternSender	tt_pattern_sender_add
#define VkMsgPatternSenderPtype	tt_pattern_sender_ptype_add
#define VkMsgPatternUser	tt_pattern_user_set
#define VkMsgPatternUserVal	tt_pattern_user
#define VkMsgPtrError		tt_ptr_error
#define VkMsgPtypeDeclare	tt_ptype_declare
#define VkMsgQuitFile		tt_file_quit
#define VkMsgRelease		tt_release
#define VkMsgReject		tt_message_reject
#define VkMsgSender		tt_message_sender
#define VkMsgSetBVal		tt_message_arg_bval_set
#define VkMsgSetDefaultSession	tt_default_session_set
#define VkMsgSetFile		tt_message_file_set
#define VkMsgSetIVal		tt_message_arg_ival_set
#define VkMsgSetStatusCode	tt_message_status_set
#define VkMsgSetStatusString	tt_message_status_string_set
#define VkMsgSetVal		tt_message_arg_val_set
#define VkMsgStatusCode		tt_message_status
#define VkMsgStatusString	tt_message_status_string
#define VkMsgStatusMessage	tt_status_message

#endif
