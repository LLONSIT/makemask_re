/*	Copyright (c) 1990, 1991 UNIX System Laboratories, Inc.	*/
/*	Copyright (c) 1984, 1986, 1987, 1988, 1989, 1990 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF     	*/
/*	UNIX System Laboratories, Inc.                     	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <internal/sgimacros.h>

#ifndef __GETWIDTH_H__
#define __GETWIDTH_H__
__SGI_LIBC_BEGIN_EXTERN_C

#ident	"@(#)libw:inc/getwidth.h	1.1"

#if defined(_MODERN_C)
extern void getwidth(eucwidth_t *);
#else
extern void getwidth();
#endif

__SGI_LIBC_END_EXTERN_C
#endif /* !__GETWIDTH_H__ */
