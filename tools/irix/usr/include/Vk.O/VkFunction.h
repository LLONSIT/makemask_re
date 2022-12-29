////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//     Copyright 1992-1996, Silicon Graphics, Inc.  All Rights Reserved.      //
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
#ifndef VKFUNCTION_H
#define VKFUNCTION_H

#include <X11/Xlib.h>		// Needed for VkPrintEvent()

#ifndef Boolean
typedef char Boolean;
#endif


// ViewKit assertion handling is intended to bypass some of the limitations
// of traditional C assertion handling.  In doing so, we find these limitations:
//	* A macro gets a warning for an invariant, such as "assert(false)"
//	* An inline does not have access to __line__ and __file__.  Both of
//	  them evaluate to the header file location where the inline is
//	  defined, not the file where it is innvoked.
//	* An inline cannot use the boolean as both that and as a string
//
// As a result, we wrap an inline in a macro:
//	* There are several macros for each inline, because the inline takes
//	  optional parameters, and macros must have fixed parameters.
//	* There is one set for debug-opnly, and another set that is always
//	  there.  The latter set is rarely, if ever, used.
//
// Access macros -- all the programmer ever sees:
//
//  Operational iff !NDEBUG
//	* VkAssert        (Boolean condition)
//	* VkAssertM       (Boolean condition, char *message)
//	* VkAssertL       (Boolean condition, char *message, unsigned level)
//
//  Macros that are operational always.  Use these sparingly -- they are
//  generally a bad idea.  In most cases, your code should just handle the
//  condition as gracefully as you can.
//	* VkAssertAlways  (Boolean condition)
//	* VkAssertAlwaysM (Boolean condition, char *message)
//	* VkAssertAlwaysL (Boolean condition, char *message, unsigned level)
//
//  condition	If this is false, the assertion happens
//  message	What to print out if the assertion is "condition" is false
//  level	This works with $VK_ASSERT settings.  The level applies to
//		both printing and whether or not to abort.  VK_ASSERT can
//		select these individually
//  ViewKit usage of assert levels is:
//	0	Cannot be overridden by VK_ASSERT.  ViewKit does not have
//		any such usage (6/96).
//
//	1	Default value.  This is the commonest usage.
//
//	5	By default levels up to 5 abort, and all levels print
//
//	10	"Are you sure you did not forget something?" sorts of
//		things.  This can happen where it is harmless not to have
//		paired actions nested, but normally they would be so.  For
//		example, although it is harmless, you would not normally set
//		cursor busy if it was already busy.
//
// VK_ASSERT values -- VK_ASSERT takes abortLevel [optional print level].
// Examples:
//	command			abort level	print level
//	==================	===========	===========
//	unsetenv VK_ASSERT	<= 5		all
//	setenv VK_ASSERT	<= 5		all
//	setenv VK_ASSERT n	<=n		<=n
//	setenv VK_ASSERT m,n	<=m		<=n


// _VkAssert is called only by the access macros.  Like all _*() routines, it
// is not intended to be called by any application.  Doing so may result
// in future incompatibilities.
//
void _VkAssert2(const char *file, int num, char *msg, unsigned level);

// We use a ptrdiff_t, so it is big enough to hold and integral value.
inline void _VkAssertI(const char *file, int num,
		       ptrdiff_t condition, char *msg, unsigned level=1)
    { if (!condition) _VkAssert2(file, num, msg, level); }


#ifdef __ANSI_CPP__
#   define VkAssertAlways(condition) \
	 _VkAssertI(__FILE__, __LINE__, (ptrdiff_t)(condition), # condition);
#else  // Not ANSI cpp
#   define VkAssertAlways(condition) \
	 _VkAssertI(__FILE__, __LINE__, (ptrdiff_t)(condition), "condition");
#endif

#define VkAssertAlwaysM(condition, msg) \
	 _VkAssertI(__FILE__, __LINE__, (ptrdiff_t)(condition), msg);

#define VkAssertAlwaysL(condition, msg, level) \
	 _VkAssertI(__FILE__, __LINE__, (ptrdiff_t)(condition), msg, level);

#ifdef NDEBUG
#  define VkAssert( cond)		(void)0
#  define VkAssertM(cond, msg)		(void)0
#  define VkAssertL(cond, msg, level)	(void)0
#else
#  define VkAssert( cond)		VkAssertAlways(cond)
#  define VkAssertM(cond, msg)		VkAssertAlwaysM(cond, msg)
#  define VkAssertL(cond, msg, lvl)	VkAssertAlwaysL(cond, msg, lvl)
#endif


// Prints a description of the event to stderr.  Right now, not a lot is
// printed, but that can be expanded if the need arises.  The second
// argument is a provision for future enum control over just what is printed.
//
// Note that this is intended to help debug.  Just what it prints may
// change in the future.
//
   extern void VkPrintEvent (XEvent *, int=0);


#endif /* VKFUNCTION_H */
