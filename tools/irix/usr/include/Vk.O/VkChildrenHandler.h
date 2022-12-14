////////////////////////////////////////////////////////////////////////////////
///////   Copyright 1992, Silicon Graphics, Inc.  All Rights Reserved.   ///////
//                                                                            //
// This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics, Inc.;     //
// the contents of this file may not be disclosed to third parties, copied    //
// or duplicated in any form, in whole or in part, without the prior written  //
// permission of Silicon Graphics, Inc.                                       //
//                                                                            //
// RESTRICTED RIGHTS LEGEND:                                                  //
// Use,duplication or disclosure by the Government is subject to restrictions //
// as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data     //
// and Computer Software clause at DFARS 252.227-7013, and/or in similar or   //
// successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -    //
// rights reserved under the Copyright Laws of the United States.             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
#ifndef _VK_CHILDREN_HANDLER_
#define _VK_CHILDREN_HANDLER_

// NOTE: VkExecCommand and VkInitializeChildrenHandler have been
//	 superceded by VkSubProcess.  This header continues to be supplied
//	 only to maintain compatibility for any legacy applications that
//	 may be using it.

// These routines are useful for clients which fork and exec children
// processes:
//	* VkInitializeChildrenHandler will take care of signals
//	  generated by dying children and reap them.
//
//	* VkExecCommand will take a command string and call execvp, similar
//	  to system() but without using an extra process for the shell, and
//	  it closes the file descriptors once forked.
//
//	* VkParseCommand will take a command string and return arguments
//	  suitable for execvp.
//
//	* VkFreeParsedCommand frees the memory allocated by VkParseCommand.
//

extern void VkInitializeChildrenHandler();
extern void VkParseCommand(char *cmd, char **file, char ***argv);
extern void VkFreeParsedCommand(char *file, char **argv);
extern int VkExecCommand(char *cmdString, int terminateWithParent = 0);

#endif //_VK_CHILDREN_HANDLER_
