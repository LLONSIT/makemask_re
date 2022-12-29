/*	Copyright (c) 1990, 1991 UNIX System Laboratories, Inc.	*/
/*	Copyright (c) 1984, 1986, 1987, 1988, 1989, 1990 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF     	*/
/*	UNIX System Laboratories, Inc.                     	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/


#ident	"@(#)uts-comm:net/rpc/rpcb_prot.h	1.2"

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
 * rpcb_prot.h
 * Protocol for the local rpcbinder service
 */

/*
 * The following procedures are supported by the protocol in version 3:
 *
 * RPCBPROC_NULL() returns ()
 * 	takes nothing, returns nothing
 *
 * RPCBPROC_SET(RPCB) returns (bool_t)
 * 	TRUE is success, FALSE is failure.  Registers the tuple
 *	[prog, vers, address, owner, netid] with address
 *	Finds out owner and netid information on its own.
 *
 * RPCBPROC_UNSET(RPCB) returns (bool_t)
 *	TRUE is success, FALSE is failure.  Un-registers tuple
 *	[prog, vers, netid].  address is ignored.
 *	If netid is NULL, unregister all.
 *
 * RPCBPROC_GETADDR(RPCB) returns (Universal address).
 *	0 is failure.  Otherwise returns the universal address where the tuple
 *	[prog, vers, netid] is registered.  Ignore address and owner.
 *
 * RPCBPROC_DUMP() RETURNS (RPCBLIST *)
 *	used for dumping the entire rpcbind maps
 *
 * RPCBPROC_CALLIT(unsigned, unsigned, unsigned, string<>)
 * 	RETURNS (address, string<>);
 * usage: encapsulatedresults = RPCBPROC_CALLIT(prog, vers, proc, encapsulatedargs);
 * 	Calls the procedure on the local machine.  If it is not registered,
 *	this procedure is quiet; i.e. it does not return error information!!!
 *	This routine only passes null authentication parameters.
 *	This file has no interface to xdr routines for RPCBPROC_CALLIT.
 *
 * RPCBPROC_GETTIME() returns (bool_t).
 *	TRUE is success, FALSE is failure.  Gets the remote machines time
 *
 * RPCBPROC_UADDR2TADDR(strint) RETURNS (struct netbuf)
 *	Returns the netbuf address from universal address.
 *
 * RPCBPROC_TADDR2UADDR(struct netbuf) RETURNS (string)
 *	Returns the universal address from netbuf address.
 *
 * END OF RPCBIND VERSION 3 PROCEDURES
 */
/*
 * Except for RPCBPROC_CALLIT, the procedures above are carried over to
 * rpcbind version 4.  Those below are added or modified for version 4.
 * NOTE: RPCBPROC_BCAST HAS THE SAME FUNCTIONALITY AND PROCEDURE NUMBER
 * AS RPCBPROC_CALLIT.
 *
 * RPCBPROC_BCAST(rpcb_rmtcallargs)
 * 	RETURNS (rpcb_rmtcallres);
 * 	Calls the procedure on the remote machine.  If it is not registered,
 *	this procedure IS quiet; i.e. it DOES NOT return error information!!!
 *	This routine should be used for broadcasting and nothing else.
 *
 * RPCBPROC_GETVERSADDR(rpcb) returns (string).
 *	0 is failure.  Otherwise returns the universal address where the
 *	triple [prog, vers, netid] is registered.  Ignore address and owner.
 *	Same as RPCBPROC_GETADDR except that if the given version number
 *	is not available, the address is not returned.
 *
 * RPCBPROC_INDIRECT(rpcb_rmtcallargs)
 * 	RETURNS (rpcb_rmtcallres);
 * 	Calls the procedure on the remote machine.  If it is not registered,
 *	this procedure is NOT quiet; i.e. it DOES return error information!!!
 * 	as any normal application would expect.
 *
 * RPCBPROC_GETADDRLIST(rpcb) returns (rpcb_entry_list_ptr).
 *	Same as RPCBPROC_GETADDR except that it returns a list of all the
 *	addresses registered for the combination (prog, vers) (for all
 *	transports).
 *
 * RPCBPROC_GETSTAT(void) returns (rpcb_stat_byvers)
 *	Returns the statistics about the kind of requests received by rpcbind.
 */

#ifndef _NET_RPC_RPCB_PROT_H	/* wrapper symbol for kernel use */
#define _NET_RPC_RPCB_PROT_H	/* subject to change without notice */

#ifndef _KERNEL
#include <rpc/types.h> /* COMPATIBILITY */
#endif /* _KERNEL */

#define RPCBPROG		((u_long)100000)
#define RPCBVERS		((u_long)3)
#define	RPCBVERS4	    	((u_long)4)

/*
 * All the defined procedures for version 3
 */
#define RPCBPROC_NULL		((u_long)0)
#define RPCBPROC_SET		((u_long)1)
#define RPCBPROC_UNSET		((u_long)2)
#define RPCBPROC_GETADDR	((u_long)3)
#define RPCBPROC_DUMP		((u_long)4)
#define RPCBPROC_CALLIT		((u_long)5)
#define RPCBPROC_GETTIME	((u_long)6)
#define RPCBPROC_UADDR2TADDR	((u_long)7)
#define RPCBPROC_TADDR2UADDR	((u_long)8)
/*
 * New in version 4.
 */
#define	RPCBPROC_BCAST	    	RPCBPROC_CALLIT
#define	RPCBPROC_GETVERSADDR	((u_long)9)
#define	RPCBPROC_INDIRECT	((u_long)10)
#define	RPCBPROC_GETADDRLIST	((u_long)11)
#define	RPCBPROC_GETSTAT	((u_long)12)

/*
 * All rpcbind stuff (vers 3)
 */

/*
 * A mapping of (program, version, network ID) to address
 */
struct rpcb {
	u_long r_prog;			/* program number */
	u_long r_vers;			/* version number */
	char *r_netid;			/* network id */
	char *r_addr;			/* universal address */
	char *r_owner;			/* owner of the mapping */
};
typedef struct rpcb RPCB;
extern bool_t xdr_rpcb(XDR *, RPCB *);
struct netbuf;

extern bool_t xdr_netbuf(XDR *, struct netbuf *);

/*
 * A list of mappings
 */
struct rpcblist {
	struct rpcb      rpcb_map;
	struct rpcblist *rpcb_next;
};
typedef struct rpcblist RPCBLIST;
typedef struct rpcblist rpcblist;
typedef struct rpcblist *rpcblist_ptr;
extern bool_t xdr_rpcblist(XDR *, RPCBLIST **);
extern bool_t xdr_rpcblist_ptr(XDR *, rpcblist_ptr *);

/*
 * Remote calls arguments
 */
struct rpcb_rmtcallargs {
	u_long prog;			/* program number */
	u_long vers;			/* version number */
	u_long proc;			/* procedure number */
	u_long arglen;			/* arg len */
	caddr_t args_ptr;		/* argument */
	xdrproc_t xdr_args;		/* XDR routine for argument */
};
typedef struct rpcb_rmtcallargs rpcb_rmtcallargs;
extern bool_t xdr_rpcb_rmtcallargs(XDR *, struct rpcb_rmtcallargs *);

/*
 * Remote calls results
 */
struct rpcb_rmtcallres {
	char *addr_ptr;			/* remote universal address */
	u_long resultslen;		/* results length */
	caddr_t results_ptr;		/* results */
	xdrproc_t xdr_results;		/* XDR routine for result */
};
typedef struct rpcb_rmtcallres rpcb_rmtcallres;
extern bool_t xdr_rpcb_rmtcallres(XDR *, struct rpcb_rmtcallres *);

/*
 * New structures for version 4.
 */
struct rpcb_entry {
	char *r_maddr;
	char *r_nc_netid;
	unsigned int r_nc_semantics;
	char *r_nc_protofmly;
	char *r_nc_proto;
};
typedef struct rpcb_entry rpcb_entry;
extern bool_t xdr_rpcb_entry(XDR *, rpcb_entry *);

/*
 * A list of addresses supported by a service.
 */

struct rpcb_entry_list {
	rpcb_entry rpcb_entry_map;
	struct rpcb_entry_list *rpcb_entry_next;
};
typedef struct rpcb_entry_list rpcb_entry_list;
typedef rpcb_entry_list *rpcb_entry_list_ptr;
extern bool_t xdr_rpcb_entry_list(XDR *, rpcb_entry_list *);
extern bool_t xdr_rpcb_entry_list_ptr(XDR *, rpcb_entry_list_ptr *);

/*
 * rpcbind statistics
 */
#define	rpcb_highproc_2 RPCBPROC_CALLIT
#define	rpcb_highproc_3 RPCBPROC_TADDR2UADDR
#define	rpcb_highproc_4 RPCBPROC_GETSTAT
#define	RPCBSTAT_HIGHPROC 13
#define	RPCBVERS_STAT 3
#define	RPCBVERS_4_STAT 2
#define	RPCBVERS_3_STAT 1
#define	RPCBVERS_2_STAT 0

/* Link list of all the stats about getport and getaddr */

struct rpcbs_addrlist {
	rpcprog_t prog;
	rpcvers_t vers;
	int success;
	int failure;
	char *netid;
	struct rpcbs_addrlist *next;
};
typedef struct rpcbs_addrlist rpcbs_addrlist;

/* Link list of all the stats about rmtcall */

struct rpcbs_rmtcalllist {
	rpcprog_t prog;
	rpcvers_t vers;
	rpcproc_t proc;
	int success;
	int failure;
	int indirect;
	char *netid;
	struct rpcbs_rmtcalllist *next;
};
typedef struct rpcbs_rmtcalllist rpcbs_rmtcalllist;
extern bool_t xdr_rpcbs_rmtcalllist(XDR *, rpcbs_rmtcalllist *);

typedef int rpcbs_proc[RPCBSTAT_HIGHPROC];

typedef rpcbs_addrlist *rpcbs_addrlist_ptr;

typedef rpcbs_rmtcalllist *rpcbs_rmtcalllist_ptr;
extern bool_t xdr_rpcbs_rmtcalllist_ptr(XDR *, rpcbs_rmtcalllist_ptr *);

struct rpcb_stat {
	rpcbs_proc info;
	int setinfo;
	int unsetinfo;
	rpcbs_addrlist_ptr addrinfo;
	rpcbs_rmtcalllist_ptr rmtinfo;
};
typedef struct rpcb_stat rpcb_stat;
extern bool_t xdr_rpcb_stat(XDR *, rpcb_stat *);

/*
 * One rpcb_stat structure is returned for each version of rpcbind
 * being monitored.
 */

typedef rpcb_stat rpcb_stat_byvers[RPCBVERS_STAT];
extern bool_t xdr_rpcb_stat_byvers(XDR *, rpcb_stat_byvers);

#ifndef _SGI_COMPILING_LIBC
/* Symbols which moved from libnsl to libc - only optional if
 * compiling with _BSD_TIRPC */
#ifdef _BSD_TIRPC
#pragma optional xdr_netbuf
#pragma optional xdr_rpcb
#pragma optional xdr_rpcb_rmtcallargs
#pragma optional xdr_rpcb_rmtcallres
#pragma optional xdr_rpcblist
#endif /* _BSD_TIRPC */

/* New symbols, added to libc */
#pragma optional xdr_rpcb_entry
#pragma optional xdr_rpcb_entry_list
#pragma optional xdr_rpcb_entry_list_ptr
#pragma optional xdr_rpcb_stat
#pragma optional xdr_rpcb_stat_byvers
#pragma optional xdr_rpcblist_ptr
#pragma optional xdr_rpcbs_rmtcalllist
#pragma optional xdr_rpcbs_rmtcalllist_ptr
#endif /* _SGI_COMPILING_LIBC */

#endif /* !_NET_RPC_RPCB_PROT_H*/
