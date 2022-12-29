#ifndef __RPC_CLNT_H__
#define __RPC_CLNT_H__
#ident "$Revision: 2.36 $"
/*
 *
 * Copyright 1992-2001, Silicon Graphics, Inc.
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

/*	@(#)clnt.h	1.3 90/07/19 4.1NFSSRC SMI	*/

/*
 * Copyright (c) 1990 by Sun Microsystems, Inc.
 *  1.31 88/02/08 SMI
 */


/*
 * clnt.h - Client side remote procedure call interface.
 */

#ifdef _KERNEL
#include "net/if.h"
#include "netinet/in.h"
#include "sys/socketvar.h"
#include "sys/vsocket.h"
#else
#include <netinet/in.h>
#include <sys/socketvar.h>
#endif

#if defined(_SVR4_TIRPC) || defined(_BSD_TIRPC)
#include <rpc/rpc_com.h>
#endif

/*
 * Rpc calls return an enum clnt_stat.  This should be looked at more,
 * since each implementation is required to live with this (implementation
 * independent) list of errors.
 */
enum clnt_stat {
	RPC_SUCCESS=0,			/* call succeeded */
	/*
	 * local errors
	 */
	RPC_CANTENCODEARGS=1,		/* can't encode arguments */
	RPC_CANTDECODERES=2,		/* can't decode results */
	RPC_CANTSEND=3,			/* failure in sending call */
	RPC_CANTRECV=4,			/* failure in receiving result */
	RPC_TIMEDOUT=5,			/* call timed out */
	RPC_INTR=18,			/* call interrupted */
	RPC_UDERROR=23,			/* recv got uderr indication */
	/*
	 * remote errors
	 */
	RPC_VERSMISMATCH=6,		/* rpc versions not compatible */
	RPC_AUTHERROR=7,		/* authentication error */
	RPC_PROGUNAVAIL=8,		/* program not available */
	RPC_PROGVERSMISMATCH=9,		/* program version mismatched */
	RPC_PROCUNAVAIL=10,		/* procedure unavailable */
	RPC_CANTDECODEARGS=11,		/* decode arguments error */
	RPC_SYSTEMERROR=12,		/* generic "other problem" */

	/*
	 * callrpc & clnt_create errors
	 */
	RPC_UNKNOWNHOST=13,		/* unknown host name */
	RPC_UNKNOWNPROTO=17,		/* unknown protocol */
	RPC_UNKNOWNADDR=19,		/* Remote address unknown */
	RPC_NOBROADCAST=21,		/* Broadcasting not supported */

	/*
	 * clnt*_create errors
	 */
	RPC_RPCBFAILURE=14,		/* the pmapper failed in its call */
#define RPC_PMAPFAILURE RPC_RPCBFAILURE /* ABI uses both symbols */
	RPC_PROGNOTREGISTERED=15,	/* remote program is not registered */
	RPC_N2AXLATEFAILURE=22,		/* Name to address translation failed */
	/*
	 * Misc error in the TLI library
	 */
	RPC_TLIERROR=20,

	/*
	 * asynchronous errors
	 */
	RPC_INPROGRESS = 24,

	/*
	 * unspecified error
	 */
	RPC_FAILED=16
};

/*
 * Error info.
 */
struct rpc_err {
	enum clnt_stat re_status;
	union {
		int RE_errno;		/* related system error */
#if defined(_SVR4_TIRPC) || defined(_BSD_TIRPC)
		/* The RE_err branch is only used with _SVR4_TIRPC or
		 * _BSD_TIRPC although with _BSD_TIRPC t_errno is always 0.
		 *
		 * NOTE. If you include a header which changes
		 * definition of errno (pthread.h does that), defining
		 * WILL_USE_REERR_ERRNO allows for this header to
		 * compile but you would have to modify the code to
		 * either use RE_errno or to use RE_err.REERR_errno. */
#ifndef WILL_USE_REERR_ERRNO
#define REERR_errno errno
#endif
		struct {
			int REERR_errno;	/* related system error */
			int t_errno;	/* related tli error number */
		} RE_err;
#endif
		enum auth_stat RE_why;	/* why the auth error occurred */
		struct {
			u_long low;	/* lowest verion supported */
			u_long high;	/* highest verion supported */
		} RE_vers;
		struct {		/* maybe meaningful if RPC_FAILED */
			long s1;
			long s2;
		} RE_lb;		/* life boot & debugging only */
	} ru;
#define	re_errno	ru.RE_errno
#define	re_why		ru.RE_why
#define	re_vers		ru.RE_vers
#define	re_lb		ru.RE_lb
#if defined(_SVR4_TIRPC) || defined(_BSD_TIRPC)
#define re_terrno       ru.RE_err.t_errno
#else
#define re_terrno       ru.RE_lb.s2
#endif
};

struct __client_s;
struct clnt_ops {
	/* call remote procedure */
	enum clnt_stat	(*cl_call)(struct __client_s *, rpcproc_t,
			    xdrproc_t, void *, xdrproc_t,
			    void *, struct timeval);
	/* abort a call */
	void		(*cl_abort)(struct __client_s *);

	/* get specific error code */
	void		(*cl_geterr)(struct __client_s *, struct rpc_err *);

	/* frees results */
	bool_t		(*cl_freeres)(struct __client_s *, xdrproc_t, void *);

	/* destroy this structure */
	void		(*cl_destroy)(struct __client_s *);

	/* the ioctl() of rpc */
	bool_t		(*cl_control)(struct __client_s *, int, void *);
};

/*
 * Client rpc handle.
 * Created by individual implementations, see e.g. rpc_udp.c.
 * Client is responsible for initializing auth, see e.g. auth_none.c.
 */
typedef struct __client_s {
    AUTH		*cl_auth;	/* authenticator */
    struct clnt_ops  	*cl_ops;
    void 		*cl_private;	/* private stuff */
    /*
     * These fields are always defined so that the CLIENT structure
     * is the same size for all compilation options, but are only
     * filled with meaningful information if you compile with
     * _SVR4_TIRPC or _BSD_TIRPC and use one of the new style functions
     * like clnt_dg_create() to create the CLIENT handle;
     */
    char		*cl_netid;	/* network token */
    char		*cl_tp;		/* device name */
} CLIENT;


/*
 * Client-side rpc interface ops
 *
 * Parameter types are:
 *
 */

/*
 * enum clnt_stat
 * CLNT_CALL(rh, proc, xargs, argsp, xres, resp, timeout)
 *	CLIENT *rh;
 *	rpcproc_t proc;
 *	xdrproc_t xargs;
 *	void *argsp;
 *	xdrproc_t xres;
 *	void *resp;
 *	struct timeval timeout;
 */
#define	CLNT_CALL(rh, proc, xargs, argsp, xres, resp, timeout)	\
	((*(rh)->cl_ops->cl_call)(rh, proc, xargs, argsp, xres, resp, timeout))
#define	clnt_call(rh, proc, xargs, argsp, xres, resp, timeout)	\
	((*(rh)->cl_ops->cl_call)(rh, proc, xargs, argsp, xres, resp, timeout))

/*
 * void
 * CLNT_ABORT(rh);
 *	CLIENT *rh;
 */
#define	CLNT_ABORT(rh)	((*(rh)->cl_ops->cl_abort)(rh))
#define	clnt_abort(rh)	((*(rh)->cl_ops->cl_abort)(rh))

/*
 * struct rpc_err
 * CLNT_GETERR(rh);
 *	CLIENT *rh;
 */
#define	CLNT_GETERR(rh,errp)	((*(rh)->cl_ops->cl_geterr)(rh, errp))
#define	clnt_geterr(rh,errp)	((*(rh)->cl_ops->cl_geterr)(rh, errp))


/*
 * bool_t
 * CLNT_FREERES(rh, xres, resp);
 *	CLIENT *rh;
 *	xdrproc_t xres;
 *	void *resp;
 */
#define	CLNT_FREERES(rh,xres,resp) ((*(rh)->cl_ops->cl_freeres)(rh,xres,resp))
#define	clnt_freeres(rh,xres,resp) ((*(rh)->cl_ops->cl_freeres)(rh,xres,resp))

/*
 * bool_t
 * CLNT_CONTROL(cl, request, info)
 *      CLIENT *cl;
 *      u_int request;
 *      void *info;
 */
#define	CLNT_CONTROL(cl,rq,in) ((*(cl)->cl_ops->cl_control)(cl,rq,in))
#define	clnt_control(cl,rq,in) ((*(cl)->cl_ops->cl_control)(cl,rq,in))

/*
 * control operations that apply to both UDP and TCP transports
 */
#define CLSET_TIMEOUT		1   /* set timeout (timeval) */
#define CLGET_TIMEOUT		2   /* get timeout (timeval) */
#define CLGET_SERVER_ADDR	3   /* get server's address (sockaddr) */
#define	CLGET_FD		6   /* get connections file descriptor */
#define CLGET_SVC_ADDR		7   /* get server's address (netbuf) */
#define	CLSET_FD_CLOSE		8   /* close fd while clnt_destroy */
#define	CLSET_FD_NCLOSE		9   /* Do not close fd while clnt_destroy */
#define	CLGET_XID 		10  /* Get xid (uint32_t) */
#define	CLSET_XID		11  /* Set xid (uint32_t) */
#define	CLGET_VERS		12  /* Get version number (rpcvers_t) */
#define	CLSET_VERS		13  /* Set version number (rpcvers_t) */
#define	CLGET_PROG		14  /* Get program number (rpcprog_t) */
#define	CLSET_PROG		15  /* Set program number (rpcprog_t) */
#define	CLSET_SVC_ADDR		16  /* Set server's address (netbuf) (UDP only) */
/*
 * UDP only control operations
 */
#define CLSET_RETRY_TIMEOUT 4   /* set retry timeout (timeval) */
#define CLGET_RETRY_TIMEOUT 5   /* get retry timeout (timeval) */
/*
 * TCP only control operations
 */
#define CLSET_EINTR_RETURN  106	/* set != 0 to return on EINTR */
#define CLGET_EINTR_RETURN  107	/* get return on EINTR flag */

/*
 * void
 * CLNT_DESTROY(rh);
 *	CLIENT *rh;
 */
#define	CLNT_DESTROY(rh)	((*(rh)->cl_ops->cl_destroy)(rh))
#define	clnt_destroy(rh)	((*(rh)->cl_ops->cl_destroy)(rh))


/*
 * RPCTEST is a test program which is accessable on every rpc
 * transport/port.  It is used for testing, performance evaluation,
 * and network administration.
 */

#define RPCTEST_PROGRAM		((rpcprog_t)1)
#define RPCTEST_VERSION		((rpcvers_t)1)
#define RPCTEST_NULL_PROC	((rpcproc_t)2)
#define RPCTEST_NULL_BATCH_PROC	((rpcproc_t)3)

/*
 * By convention, procedure 0 takes null arguments and returns them
 */

#define NULLPROC ((rpcproc_t)0)

/*
 * Below are the client handle creation routines for the various
 * implementations of client side rpc.  They can return NULL if a
 * creation failure occurs.
 */

#ifndef _KERNEL
/*
 * Generic client creation routine. Supported protocols are "udp" and "tcp"
 *
 *	const char *host;	-- hostname
 *	rpcprog_t prog; 	-- program number
 *	rpcvers_t vers; 	-- version number
 *	const char *prot;	-- protocol
 */
extern CLIENT * clnt_create(const char *, rpcprog_t, rpcprog_t, const char *);

/*
 * Generic client creation routine. Supported protocols are "udp" and "tcp"
 *
 *	const char *host;	-- hostname
 *	rpcprog_t prog; 	-- program number
 *	rpcvers_t *vers_out;	-- servers best  version number
 *	rpcvers_t vers_low;	-- low version number
 *	rpcvers_t vers_high;	-- high version number
 *	const char *prot;	-- protocol
 */
extern CLIENT *clnt_create_vers(
	const char *, rpcprog_t, rpcvers_t *, rpcvers_t, rpcvers_t, const char *);

#if defined(_SVR4_TIRPC) || defined(_BSD_TIRPC)

struct netconfig;
struct netbuf;
/*
 * Generic client creation routine. It takes a netconfig structure
 * instead of nettype
 */
extern CLIENT *
clnt_tp_create(
	const char *hostname,		/* hostname		*/
	rpcprog_t prog,			/* program number	*/
	rpcvers_t vers,			/* version number	*/
	struct netconfig *netconf); 	/* network config structure	*/

/*
 * Generic TLI create routine
 */
extern CLIENT *
clnt_tli_create(
	int fd,		    	    	/* fd			*/
	struct netconfig *nconf,	/* netconfig structure	*/
	struct netbuf *svcaddr,		/* servers address	*/
	rpcprog_t prog,			/* program number	*/
	rpcvers_t vers,			/* version number	*/
	u_int sendsz,			/* send size		*/
	u_int recvsz);			/* recv size		*/

/*
 * Low level clnt create routine for connectionful transports, e.g. tcp.
 */
extern CLIENT *
clnt_vc_create(
	int fd,				/* open file descriptor	*/
	struct netbuf *svcaddr,		/* servers address	*/
	rpcprog_t prog,			/* program number	*/
	rpcvers_t vers,			/* version number	*/
	u_int sendsz,			/* buffer recv size	*/
	u_int recvsz);			/* buffer send size	*/

/*
 * Low level clnt create routine for connectionless transports, e.g. udp.
 */
extern CLIENT *
clnt_dg_create(
	int fd,				/* open file descriptor	*/
	struct netbuf *svcaddr,		/* servers address	*/
	rpcprog_t program,		/* program number	*/
	rpcvers_t version,		/* version number	*/
	u_int sendsz,			/* buffer recv size	*/
	u_int recvsz);			/* buffer send size	*/

/*
 * Memory based rpc (for speed check and testing)
 * CLIENT *
 * clnt_raw_create(prog, vers)
 *	rpcprog_t prog;			-- program number
 *	rpcvers_t vers;			-- version number
 */
extern CLIENT *clnt_raw_create(rpcprog_t, rpcvers_t);

/*
 * The simplified interface:
 * enum clnt_stat
 * rpc_call(host, prognum, versnum, procnum, inproc, in, outproc, out, nettype)
 *	const char *host;
 *	rpcprog_t prognum;
 *	rpcvers_t versnum;
 *	rpcproc_t procnum;
 *	xdrproc_t inproc, outproc;
 *	void *in, *out;
 *	const char *nettype;
 */
extern enum clnt_stat rpc_call(
	const char *host,               /* host name */
	rpcprog_t prognum,              /* program number */
	rpcvers_t versnum,              /* version number */
	rpcproc_t procnum,              /* procedure number */
	xdrproc_t inproc,               /* int XDR procedures */
	void *in,                       /* recv/send data */
	xdrproc_t outproc,              /* out XDR procedures */
	void *out,                      /* recv/send data */
	const char *nettype);           /* nettype */

/*
 * RPC broadcast interface
 * extern enum clnt_stat
 * rpc_broadcast(prog, vers, proc, xargs, argsp, xresults, resultsp,
 *			eachresult, nettype)
 *	rpcprog_t	prog;		-- program number
 *	rpcvers_t	vers;		-- version number
 *	rpcproc_t	proc;		-- procedure number
 *	xdrproc_t	xargs;		-- xdr routine for args
 *	void		*argsp;		-- pointer to args
 *	xdrproc_t	xresults;	-- xdr routine for results
 *	void		*resultsp;	-- pointer to results
 *	resultproc_t	eachresult;	-- call with each result obtained
 *	const char	*nettype;	-- Transport type
 */
typedef bool_t (*resultproc_t)(caddr_t, struct netbuf *, struct netconfig *);
extern enum clnt_stat rpc_broadcast(rpcprog_t, rpcvers_t, rpcproc_t,
				xdrproc_t, void *, xdrproc_t, void *,
				resultproc_t, const char *);

#endif /* _SVR4_TIRPC||_BSD_TIRPC */

#if defined(_BSD_TIRPC) && !defined(_SGI_COMPILING_LIBC)
/*
 * BSD style TI-RPC over sockets introduced to IRIX libc at 6.5.20.
 */
#pragma optional clnt_tp_create
#pragma optional clnt_tli_create
#pragma optional clnt_vc_create
#pragma optional clnt_dg_create
#pragma optional clnt_raw_create
#pragma optional rpc_call
#pragma optional rpc_broadcast
#endif

/*
 * Print why creation failed
 */
extern void clnt_pcreateerror(const char *);	/* outputs to stderr */
extern char *clnt_spcreateerror(const char *);

/*
 * Like clnt_perror(), but is more verbose in its output
 */
extern void clnt_perrno(enum clnt_stat);	/* outputs to stderr */

/*
 * Print an error message, given the client error code
 */
extern void clnt_perror(CLIENT *, const char *);	/* outputs to stderr */
extern char *clnt_sperror(CLIENT *, const char *);

#ifndef _SVR4_TIRPC
/*
 * Logs a LOG_ERR error to syslog
 */
extern void clnt_syslog(CLIENT *rpch, const char *s);
#endif

#endif /* !_KERNEL */

/*
 * Copy error message to buffer.
 */
extern char *clnt_sperrno(enum clnt_stat);

/*
 * If a creation fails, the following allows the user to figure out why.
 */
struct rpc_createerr {
	enum clnt_stat cf_stat;
	struct rpc_err cf_error; /* useful when cf_stat == RPC_PMAPFAILURE */
};

extern struct rpc_createerr rpc_createerr;


#ifdef _KERNEL
/*
 * Kernel UDP-based rpc
 */
enum kudp_intr { KUDP_NOINTR, KUDP_INTR };
enum kudp_xid { KUDP_XID_SAME, KUDP_XID_CREATE, KUDP_XID_PERCALL };

struct sockaddr_in;
struct cred;
struct mac_label;
extern CLIENT	*clntkudp_create(struct sockaddr_in *, u_long, u_long, int,
				 enum kudp_intr, enum kudp_xid, struct cred *);
extern int 	clntkudp_init(CLIENT *, struct sockaddr_in *, int,
			      enum kudp_intr, enum kudp_xid, struct cred *);
extern void	clntkudp_soattr(CLIENT *, struct mac_label *);
extern int	getport_loop(struct sockaddr_in *, u_long, u_long, u_long, int);
extern int	ku_sendto_mbuf(struct socket *, struct mbuf *, struct sockaddr_in *);
extern struct mbuf *ku_recvfrom(struct socket *, struct sockaddr_in *,
				struct mac_label **);

extern int	bindresvport(struct vsocket *);
#endif

/*
 * Timers used for the pseudo-transport protocol when using datagrams
 */
struct rpc_timers {
	u_short		rt_srtt;	/* smoothed round-trip time */
	u_short		rt_deviate;	/* estimated deviation */
	u_long		rt_rtxcur;	/* current (backed-off) rto */
};

/*
 * Feedback values used for possible congestion and rate control
 */
#define	FEEDBACK_REXMIT1	1	/* first retransmit */
#define	FEEDBACK_OK		2	/* no retransmits */

/*
 * Stuff the machine's IPv4 address into *addr without consulting
 * the library routines that deal with /etc/hosts.
 */
extern void get_myaddress(struct sockaddr_in *);

#define RPCSMALLMSGSIZE	400	/* a more reasonable packet size */

#ifdef _SGI_COMPILING_LIBC
/*
 * Declarations of functions private to the RPC library.
 */
#ifndef _SVR4_TIRPC
bool_t __clnt_set_netid(CLIENT *, const char *, const char *);
void __clnt_free_netid(CLIENT *);
#endif
#endif /* _SGI_COMPILING_LIBC */


/* All the old-fashioned socket-based RPC APIs are declared in clnt_soc.h */
#include <rpc/clnt_soc.h>

#ifdef __cplusplus
}
#endif

#endif /* !__RPC_CLNT_H__ */
