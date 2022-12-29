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
#ifndef _4SpeedMacros_ 
#define _4SpeedMacros_

#define VkDBGFUNCENTRY			0x001
#define VkDBGFUNCEXIT			0x002
#define VkDBGCALLBACKENTRY		0x004	
#define VkDBGCALLBACKEXIT		0x008	
#define VkDBGLOOPENTRY			0x010	
#define VkDBGLOOPEXIT			0x020	
#define VkDBGLOOP			0x040	
#define VkDBGRESERVED			0x080	

#ifndef NODEBUG
#define NODEBUG

#include <stdio.h>

extern unsigned int VkDebugLevel;

//
// Use Vk*Debug() to trace various actions in the application
//   VkSODebug - Viewkit Standard Out Debugging message
//   VkSEDebug - Viewkit Standard Error Debugging message
//   VkFDebug  - Viewkit Debugging message written to File
//               you must provide the file descriptor as the first argument
//

#define VkSODebug(LEVEL,FORMAT) \
	if (::VkDebugLevel & (LEVEL)) { printf FORMAT; fflush (stdout); }

#define VkSEDebug(LEVEL,STRING) \
	if (::VkDebugLevel & (LEVEL)) fprintf (stderr, "%s", STRING);

#define VkFDebug(LEVEL,FORMAT) \
	if (::VkDebugLevel & (LEVEL)) fprintf FORMAT;

//
// Use Vk*assert() to check for assumptions or boundary conditions in the app.
//   VkSOAssert - Viewkit Standard Out Assertion message
//   VkSEAssert - Viewkit Standard Error Assertion message
//   VkFAssert  - Viewkit Assertion message written to File
//

#define VkSOAssert(CONDITION, FORMAT) if (!(CONDITION)) \
	{ printf FORMAT; fflush (stdout); }

#define VkSEAssert(CONDITION, MESSAGE) if (!(CONDITION)) \
	{ fprintf (stderr, "%s", MESSAGE); }

#define VkFAssert(CONDITION, MESSAGE) if (!(CONDITION)) \
	fprintf MESSAGE;

#else
#define VkFDebug(LEVEL, FORMAT)
#define VkSODebug(LEVEL, FORMAT)
#define VkSEDebug(LEVEL, FORMAT)
#define VkFAssert(CONDITION, FORMAT)
#define VkSOAssert(CONDITION, FORMAT)
#define VkSEAssert(CONDITION, FORMAT)
#endif

#endif
