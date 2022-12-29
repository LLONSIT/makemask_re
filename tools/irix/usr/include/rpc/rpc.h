#ifndef __RPC_RPC_H__
#define __RPC_RPC_H__
#ident "$Revision: 2.14 $"
/*
 *
 * Copyright 1992, Silicon Graphics, Inc.
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

#ifdef __cplusplus
extern "C" {
#endif

/*	@(#)rpc.h	1.3 90/07/17 4.1NFSSRC SMI	*/

/* 
 * Copyright (c) 1990 by Sun Microsystems, Inc.
 *	@(#)rpc.h 1.9 88/02/08 SMI	  
 */

/*
 * rpc.h, Just includes the billions of rpc header files necessary to 
 * do remote procedure calling.
 */


#include <stdio.h>
#include <rpc/types.h>		/* some typedefs */
#include <netinet/in.h>
#ifdef _SVR4_TIRPC
#include <tiuser.h>
#include <fcntl.h>
#endif

/* external data representation interfaces */
#include <rpc/xdr.h>		/* generic (de)serializer */

/* Client side only authentication */
#include <rpc/auth.h>		/* generic authenticator (client side) */

/* Client side (mostly) remote procedure call */
#include <rpc/clnt.h>		/* generic rpc stuff */

/* semi-private protocol headers */
#include <rpc/rpc_msg.h>	/* protocol for rpc messages */
#include <rpc/auth_unix.h>	/* protocol for unix style cred */
#include <rpc/auth_des.h>	/* protocol for des style cred */
#include <rpc/rpcsec_gss.h>	/* protocol for GSS stype authentication */

/* Server side only remote procedure callee */
#include <rpc/svc.h>		/* service manager and multiplexer */
#include <rpc/svc_auth.h>	/* service side authenticator */
#if defined(_SVR4_TIRPC) || defined(_BSD_TIRPC)
#include <rpc/rpcb_clnt.h>	/* rpcbind interface functions */
#endif
#ifndef _KERNEL
#include <rpc/svc_mt.h>		/* private server definitions */
#endif


#ifdef _BSD_TIRPC
/*
 * BSD style TI-RPC definitions...basically fake versions of the
 * functions of the same names in libnsl, which work over sockets
 * instead of TLI.
 */
struct netconfig;
char *taddr2uaddr(const struct netconfig *, const struct netbuf *);
struct netbuf *uaddr2taddr(const struct netconfig *, const char *);

#ifndef _SGI_COMPILING_LIBC
#pragma optional taddr2uaddr
#pragma optional uaddr2taddr
#endif
#endif /* _BSD_TIRPC */


#ifdef __cplusplus
}
#endif
#endif /* !__RPC_RPC_H__ */
