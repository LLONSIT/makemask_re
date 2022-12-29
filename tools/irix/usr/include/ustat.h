#ifndef __USTAT_H__
#define __USTAT_H__
/* Copyright (C) 1989 Silicon Graphics, Inc. All rights reserved.  */
/* ------------------------------------------------------------------ */
/* | Copyright Unpublished, MIPS Computer Systems, Inc.  All Rights | */
/* | Reserved.  This software contains proprietary and confidential | */
/* | information of MIPS and its suppliers.  Use, disclosure or     | */
/* | reproduction is prohibited without the prior express written   | */
/* | consent of MIPS.                                               | */
/* ------------------------------------------------------------------ */
/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#ident "$Revision: 1.10 $"

#include <sys/types.h>
#include <sys/ustat.h>	/* for ustat struct */
#include <internal/sgimacros.h>

__SGI_LIBC_BEGIN_EXTERN_C

extern int ustat(dev_t, struct ustat *);

__SGI_LIBC_END_EXTERN_C
#endif /* !__USTAT_H__ */

