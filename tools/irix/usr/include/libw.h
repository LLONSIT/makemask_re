/*	Copyright (c) 1990, 1991 UNIX System Laboratories, Inc.	*/
/*	Copyright (c) 1984, 1986, 1987, 1988, 1989, 1990 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF     	*/
/*	UNIX System Laboratories, Inc.                     	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#ifndef __LIBW_H__
#define __LIBW_H__

#ident	"@(#)libw:inc/libw.h	1.1.1.1"

#include	<stdlib.h>
#include	<sys/euc.h>
#include	<internal/sgimacros.h>

__SGI_LIBC_BEGIN_EXTERN_C

#if defined(_MODERN_C)
void getwidth(eucwidth_t *);
int mbftowc(char *, wchar_t *, int (*)(void), int *);
int scrwidth(wchar_t);
int wisprint(wchar_t);
#else
void getwidth();
int mbftowc();
int scrwidth();
int wisprint();
#endif /* __STDC__ */

__SGI_LIBC_END_EXTERN_C
#endif /* !__LIBW_H__ */
