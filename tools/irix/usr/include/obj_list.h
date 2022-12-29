/* Copyright (C) 1989, 2001 Silicon Graphics, Inc. 
   All rights reserved.  */
/*
 * |-----------------------------------------------------------|
 * | Copyright (c) 1991, 1990 MIPS Computer Systems, Inc.      |
 * | All Rights Reserved                                       |
 * |-----------------------------------------------------------|
 * |          Restricted Rights Legend                         |
 * | Use, duplication, or disclosure by the Government is      |
 * | subject to restrictions as set forth in                   |
 * | subparagraph (c)(1)(ii) of the Rights in Technical        |
 * | Data and Computer Software Clause of DFARS 252.227-7013.  |
 * |         MIPS Computer Systems, Inc.                       |
 * |         950 DeGuigne Avenue                               |
 * |         Sunnyvale, California 94088-3650, USA             |
 * |-----------------------------------------------------------|
 */
/* $Header: /isms/cmplrs.src/v7.4/include/RCS/obj_list.h,v 7.6 2001/10/24 19:57:30 davea Exp $ */

#ifndef __OBJ_LIST_H__
#define __OBJ_LIST_H__
/*
	This should be used only for apps that are o32.
	It is used by rld(1) at run time to communicate
	the list of DSOs to a debugger and other tools.
	See obj.h for a slightly fuller discussion of the 
	ABI compatibility issues.
*/

#ifdef __cplusplus
extern "C" {
#endif

typedef struct obj_list {
	unsigned long	data;
	struct obj_list	*next;
	struct obj_list	*prev;			/* back link */
} objList;
/*
	The above declaration is useless for a -64 app to read
	an o32 app's DSO list since the struct element sizes mismatch:
	unsigned long and pointer are not the same size o32 vs -64.

        One is probably better off
        not #including this
        if the app being built is -n32 or -64.
	Create your own struct using
	   "unsigned int" elements.

*/


#define LIST_BEGINNING	0
#define LIST_END	1
#define LIST_ADD_BEFORE         2
#define LIST_ADD_AFTER          3
#define LIST_DELETE             4
#define LIST_REPLACE            5

#ifdef __cplusplus
}
#endif

#endif	/* __OBJ_LIST_H__ */
