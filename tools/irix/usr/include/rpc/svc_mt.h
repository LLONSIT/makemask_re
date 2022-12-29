/*
 * Copyright (c) 1986 - 1996 by Sun Microsystems, Inc.
 * All rights reserved.
 */

#ifndef _RPC_SVC_MT_H
#define	_RPC_SVC_MT_H

/*
 * Private service definitions
 */

#ifdef __cplusplus
extern "C" {
#endif

/*
 * SVC flags
 */
#define	SVC_VERSQUIET	0x0001	/* keep quiet about version mismatch */
#define	SVC_DEFUNCT	0x0002	/* xprt is defunct, release asap */
#define	SVC_DGRAM	0x0004	/* datagram type */
#define	SVC_RENDEZVOUS	0x0008	/* rendezvous */
#define	SVC_CONNECTION	0x000c	/* connection */
#define	SVC_DOOR	0x0010	/* door ipc */
#define	SVC_TYPE_MASK	0x001c	/* type mask */
#define	SVC_FAILED	0x0020	/* send/receive failed, used for VC */
#define	SVC_ARGS_CHECK	0x0040	/* flag to check for argument completion */

#define	svc_flags(xprt)		(SVCEXT(xprt)->flags)
#define	svc_defunct(xprt)	((svc_flags(xprt) & SVC_DEFUNCT) ? TRUE : FALSE)
#define	svc_failed(xprt)	((svc_flags(xprt) & SVC_FAILED) ? TRUE : FALSE)
#define	svc_type(xprt)		(svc_flags(xprt) & SVC_TYPE_MASK)

/*
 * Copy of GSS parameters.
 * 
 * It would be logical to keep it with the rest of rq_clntcred in the
 * svc_req, but we don't get svc_req in svc_reply and we need to get
 * to this stuff there, so here it goes.
 */
typedef struct {
	bool_t			established;
	rpc_gss_service_t	service;
	int			qop_rcvd;
	void			*context;
	uint_t			seq_num;
} svc_rpc_gss_parms_t;

/*
 * Interface to server-side authentication flavors, may vary with
 * each request.
 *
 * NOTE: This structure is part of an interface between libc and rpcsec_gss.so.
 */
typedef struct __svcauth_s {
	struct svc_auth_ops {
		int		(*svc_ah_wrap)(struct __svcauth_s *, XDR *, xdrproc_t, void *);
		int		(*svc_ah_unwrap)(struct __svcauth_s *, XDR *, xdrproc_t, void *);
	} svc_ah_ops;
	caddr_t			svc_ah_private;
	svc_rpc_gss_parms_t	svc_gss_parms;
	rpc_gss_rawcred_t	raw_cred;
} SVCAUTH;

typedef struct svcxprt_list_t {
	struct svcxprt_list_t	*next;
	SVCXPRT			*xprt;
} SVCXPRT_LIST;

/*
 * The xp_p3 field the the service handle points to the SVCXPRT_EXT
 * extension structure.
 */
typedef struct svcxprt_ext_t {
	int		flags;		/* VERSQUIET, DEFUNCT flag */
	SVCXPRT		*parent;	/* points to parent (NULL in parent) */

	struct rpc_msg	*msg;		/* message */
	struct svc_req	*req;		/* request */
	char		*cred_area;	/* auth work area */
	int		refcnt;		/* number of parent references */
	SVCXPRT_LIST	*my_xlist;	/* list header for this copy */
	SVCAUTH		xp_auth;	/* raw response verifier */
} SVCXPRT_EXT;

#define	SVCEXT(xprt)		((SVCXPRT_EXT *)((xprt)->xp_p3))

#ifdef _SGI_COMPILING_LIBC
bool_t __svc_unwrap_args (SVCXPRT *xprt, XDR *xdrs, xdrproc_t xp, void *args);
bool_t __svc_wrap_reply (SVCXPRT *xprt, struct rpc_msg *msg, XDR *xdrs, xdrproc_t xp, void * res);
#endif

/*
 * Global/module private data and functions
 */
extern XDR **svc_xdrs;
extern int svc_mt_mode;
extern int svc_nfds;
extern int svc_nfds_set;
extern int svc_max_fd;
extern int svc_pipe[2];
extern bool_t svc_polling;
extern SVCXPRT **svc_xports;

SVCXPRT *svc_xprt_alloc(void);
SVCXPRT *svc_copy(SVCXPRT *);
SVCXPRT *svcudp_xprtcopy(SVCXPRT *);
void svc_xprt_free(SVCXPRT *);
void svc_xprt_destroy(SVCXPRT *);
void svc_args_done(SVCXPRT *);
void _svcudp_destroy_private(SVCXPRT *);
void _svc_destroy_private(SVCXPRT *);
int _libc_rpc_mt_init(void);

#ifdef __cplusplus
}
#endif

#endif /* !_RPC_SVC_MT_H */
