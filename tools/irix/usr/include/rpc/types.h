#ifndef __RPC_TYPES_H__
#define __RPC_TYPES_H__
#ident "$Revision: 2.28 $"
/*
 *
 * Copyright 1992-2003, Silicon Graphics, Inc.
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics, Inc.;
 * the contents of this file may not be disclosed to third parties, copied or
 * duplicated in any form, in whole or in part, without the prior written
 * permission of Silicon Graphics, Inc.
 *
 * RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to restrictions
 * as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data
 * and Computer Software clause at DFARS 252.227-7013, and/or in similar or
 * successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -
 * rights reserved under the Copyright Laws of the United States.
 */
 
/*
 * Portions of this file are derived from NetBSD's basesrc/include/rpc/types.h
 * which contained the following messages:
 */
/*	$NetBSD: types.h,v 1.13 2000/06/13 01:02:44 thorpej Exp $	*/

/*
 * Sun RPC is a product of Sun Microsystems, Inc. and is provided for
 * unrestricted use provided that this legend is included on all tape
 * media and as a part of the software program in whole or part.  Users
 * may copy or modify Sun RPC without charge, but are not authorized
 * to license or distribute it to anyone else except as part of a product or
 * program developed by the user.
 * 
 * SUN RPC IS PROVIDED AS IS WITH NO WARRANTIES OF ANY KIND INCLUDING THE
 * WARRANTIES OF DESIGN, MERCHANTIBILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE, OR ARISING FROM A COURSE OF DEALING, USAGE OR TRADE PRACTICE.
 * 
 * Sun RPC is provided with no support and without any obligation on the
 * part of Sun Microsystems, Inc. to assist in its use, correction,
 * modification or enhancement.
 * 
 * SUN MICROSYSTEMS, INC. SHALL HAVE NO LIABILITY WITH RESPECT TO THE
 * INFRINGEMENT OF COPYRIGHTS, TRADE SECRETS OR ANY PATENTS BY SUN RPC
 * OR ANY PART THEREOF.
 * 
 * In no event will Sun Microsystems, Inc. be liable for any lost revenue
 * or profits or other special, indirect and consequential damages, even if
 * Sun has been advised of the possibility of such damages.
 * 
 * Sun Microsystems, Inc.
 * 2550 Garcia Avenue
 * Mountain View, California  94043
 *
 *	from: @(#)types.h 1.18 87/07/24 SMI
 *	@(#)types.h	2.3 88/08/15 4.0 RPCSRC
 */


#ifdef __cplusplus
extern "C" {
#endif

/*	@(#)types.h	1.6 90/07/19 4.1NFSSRC SMI	*/

/* 
 * Copyright (c) 1990 by Sun Microsystems, Inc.
 *      @(#)types.h 1.20 88/02/08 SMI      
 */

/*
 * Rpc additions to <sys/types.h>
 */

/* the rpc headers rely heavily on BSD typedefs that aren't available normally
 * in POSIX mode. We define _BSD_TYPES to getget these useful defines
 */
#define _BSD_TYPES	1
#include <sys/types.h>

/*
 * Also need to include sys/bsd_types.h as the user may have
 * previously included sys/types.h
 */
#include <sys/bsd_types.h>
#include <sys/time.h>

#define	bool_t	int
#define	enum_t	int
#define __dontcare__	-1

#ifndef FALSE
#	define	FALSE	0
#endif

#ifndef TRUE
#	define	TRUE	1
#endif

#ifndef NULL
#	define	NULL	0
#endif

#ifndef _KERNEL
#include <stdlib.h>

#define mem_alloc(bsize)	malloc(bsize)
#define mem_free(ptr, bsize)	free(ptr)
#else
#include "sys/kmem.h"

#define mem_alloc(bsize)	kmem_alloc(bsize, KM_SLEEP)
#define mem_free(ptr, bsize)	kmem_free(ptr, bsize)
#endif	/* _KERNEL */

#ifdef _BSD_TIRPC

/* Enforce mutual exclusion between SVR4 and BSD TI-RPC. */
#ifdef _SVR4_TIRPC
#error both -D_SVR4_TIRPC and -D_BSD_TIRPC used
#endif

/*
 * NetBSD says:
 * The netbuf structure is defined here, because NetBSD only uses it inside
 * the RPC code. It's in <xti.h> on SVR4, but it would be confusing to
 * have an xti.h, since NetBSD does not support XTI/TLI.
 * 
 * The IRIX situation is more complex.  Real definitions of netbuf and
 * t_bind exist in <sys/tiuser.h> but we can't include that here for
 * various reasons.  We do know that those definitions should never be
 * included with -D_BSD_TIRPC by correct (i.e. compilable) applications
 * so we define our own versions of the structure here.
 */

/*
 * The netbuf structure is used for transport-independent address storage.
 */
struct netbuf {
	unsigned int maxlen;
	unsigned int len;
	void *buf;
};

/*
 * The format of the addres and options arguments of the XTI t_bind call.
 * Only provided for compatibility, it should not be used.
 */

struct t_bind {
	struct netbuf   addr;
	unsigned int    qlen;
};

#endif /* _BSD_TIRPC */

/* On IRIX RPC programm number, version and procedure number has always been
 * an u_long, so just define it as u_long */
typedef u_long rpcprog_t;
typedef u_long rpcvers_t;
typedef u_long rpcproc_t;
typedef u_long rpcprot_t;
typedef u_long rpcport_t;

/* This type represent XDR marshalling uint. It should always be
 * unsigned and its size should always be 4 bytes, regardless of
 * ABI */
typedef unsigned int rpc_inline_t;

#ifdef __cplusplus
}
#endif
#endif /* !__RPC_TYPES_H__ */
