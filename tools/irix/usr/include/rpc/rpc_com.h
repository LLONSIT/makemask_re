/*	Copyright (c) 1990, 1991 UNIX System Laboratories, Inc.	*/
/*	Copyright (c) 1984, 1986, 1987, 1988, 1989, 1990 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF     	*/
/*	UNIX System Laboratories, Inc.                     	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#ifndef _NET_RPC_RPC_COM_H	/* wrapper symbol for kernel use */
#define _NET_RPC_RPC_COM_H	/* subject to change without notice */

#ident	"@(#)uts-comm:net/rpc/rpc_com.h	1.2"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*	PROPRIETARY NOTICE (Combined)
*
* This source code is unpublished proprietary information
* constituting, or derived under license from AT&T's UNIX(r) System V.
* In addition, portions of such source code were derived from Berkeley
* 4.3 BSD under license from the Regents of the University of
* California.
*
*
*
*	Copyright Notice 
*
* Notice of copyright on this source code product does not indicate 
*  publication.
*
*	(c) 1986,1987,1988,1989  Sun Microsystems, Inc
*	(c) 1983,1984,1985,1986,1987,1988,1989  AT&T.
*          All rights reserved.
*/ 
/*
 * rpc_com.h, Common definitions for both the server and client side.
 * All for the topmost layer of rpc
 *
 * Copyright (C) 1988, Sun Microsystems, Inc.
 */ 

/*
 * Also contains code derived from NetBSD's basesrc/lib/libc/rpc/rpc_com.h
 * which bore this message in addition to the others above:
 */
/*	$NetBSD: rpc_com.h,v 1.3 2000/12/10 04:10:08 christos Exp $	*/

/*
 * File descriptor to be used on xxx_create calls to get default descriptor
 */
#define	RPC_ANYSOCK	-1
#define RPC_ANYFD	RPC_ANYSOCK

/*
 * The max size of the transport, if the size cannot be determined
 * by other means.
 */
#define MAXTR_BSIZE 9000
#define RPC_MAXDATASIZE 9000
/* This is used internally in NetBSD's code */
#define	_RPC_MAXADDRSIZE 1024

extern u_int _rpc_get_t_size( int, long );
extern u_int _rpc_get_a_size( long );
extern int _rpc_dtbsize( void );
extern char *_rpc_gethostname( void );

#ifndef _KERNEL

bool_t rpc_control(int, void *);

/*
 * rpc_control commands
 */
#define	RPC_SVC_MTMODE_SET	1	/* set MT mode */
#define	RPC_SVC_MTMODE_GET	2	/* get MT mode */
#define	RPC_SVC_THRMAX_SET	3	/* set maximum number of threads */
#define RPC_SVC_THRMAX_GET	4	/* get maximum number of threads */
#define RPC_SVC_THRTOTAL_GET	5	/* get total number of threadsi */
#define RPC_SVC_THRCREATES_GET	6	/* get total threads created */
#define RPC_SVC_THRERRORS_GET	7	/* get total thread create errors */
#define	__RPC_CLNT_MINFD_SET	8	/* set min fd used for a clnt handle */
#define	__RPC_CLNT_MINFD_GET	9	/* get min fd used for a clnt handle */
#define RPC_SVC_CONNMAXREC_SET  11      /* set COT maximum record size */
#define RPC_SVC_CONNMAXREC_GET  12      /* get COT maximum record size */

#endif /* !_KERNEL */

#ifdef _BSD_TIRPC
struct netconfig;

/*
 * Internal library use. This is not an exported interface, do not use.
 */
struct __rpc_sockinfo {
	int si_af; 
	int si_proto;
	int si_socktype;
	int si_alen;
};

/*
 * The following are strictly internal interfaces and are not covered by the
 * IRIX Binary Compatibility Policy. i.e. are subject to change without notice.
 */
int __rpc_nconf2fd(const struct netconfig *);
int __rpc_nconf2sockinfo(const struct netconfig *, struct __rpc_sockinfo *);


#ifdef _SGI_COMPILING_LIBC
/*
 * The following are internal to libc and not exported from the DSO
 */
struct sockaddr;

u_int __rpc_get_t_size(int, int, int);
unsigned int __rpc_get_a_size(int);
int __rpc_fixup_addr(struct netbuf *, const struct netbuf *);
int __rpc_sockinfo2netid(const struct __rpc_sockinfo *, const char **);
int __rpc_seman2socktype(int);
int __rpc_socktype2seman(int);
int __rpc_fd2sockinfo(int, struct __rpc_sockinfo *);
u_int __rpc_get_t_size(int, int, int);
int __rpc_socktype2seman(int);
int __rpc_sockisbound(int);

struct __client_s;
struct netbuf *__rpcb_findaddr(rpcprog_t, rpcvers_t,
			       struct netconfig *,
			       const char *, struct __client_s **);
bool_t __rpc_control(int, void *);

struct sockaddr *__rpc_netbuf_sockaddr(struct netbuf *);

struct __svcxprt_s;
struct __svcxprt_s *__svc_vc_create_si(int, u_int, u_int,
    	    	    	    	       const struct __rpc_sockinfo *);
struct __svcxprt_s *__svc_dg_create_si(int, u_int, u_int,
	    	    	    	       const struct __rpc_sockinfo *);
#else /* __SGI_COMPILING_LIBC */
#pragma optional __rpc_nconf2fd
#pragma optional __rpc_nconf2sockinfo
#endif

#endif /* _BSD_TIRPC */


#endif /* _NET_RPC_RPC_COM_H */
