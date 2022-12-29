/**************************************************************************
 *                                                                        *
 *               Copyright (C) 2002 Silicon Graphics, Inc.                *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 **************************************************************************/

#ifndef _NETINET_IF_NDP6_H_
#define _NETINET_IF_NDP6_H_

#if _NO_XOPEN4 && _NO_XOPEN5
/*
 * Definitions for if_ndtype
 */

#define IFND6_TYPE	0xff000000	/* type of the interface */
#define IFND6_FLAGS	0x00ff0000	/* flags */
#define IFND6_LLOFF	0x0000ff00	/* link-local address offset */
#define IFND6_L2OFF	0x000000ff	/* link-layer address offset */

#define IFND6_UNKNOWN	0x00000000	/* unknown ND type */
#define IFND6_LOOP	0x01000000	/* loopback */
#define IFND6_IEEE	0x02000000	/* IEEE LAN */
#define IFND6_SIT	0x03000000	/* SIT IPv6 over IPv4 */
#define IFND6_TUG	0x04000000	/* TUG IPv6 over IPv6 */
#define IFND6_TUN	0x05000000	/* TUN interface/device */
#define IFND6_PPP	0x06000000	/* PPP serial */
#define IFND6_ATM	0x07000000	/* ATM */
#define IFND6_LLINK	0xff000000	/* link-local pseudo interface */

#define IFND6_IS_LLINK(ifp) \
	(((ifp)->if_ndtype & IFND6_TYPE) == IFND6_LLINK)

#define IFND6_INLL	0x00010000	/* participate to llink */
#define IFND6_ADDRES	0x00020000	/* use address resolution */
#define IFND6_MTU	0x00040000	/* fancy MTU values */

#define IFND6_LLSET	0x00100000	/* link-local address is set */

#define GETLLADDR(ifp) (&(ifp)->if_6llocal->ia_addr.sin6_addr) /* link local */

#define GETL2ADDR(ifp) ((ifp)->if_6l2addr)  /* link layer addr */

/*
 * IPv6 Neighbor Discovery Protocol.
 *
 * See RFC xxxx for protocol description.
 */

struct llinfo_ndp6 {
	struct	rtentry *ln_rt;
	struct	mbuf *ln_hold;		/* last packet until resolved/timeout */
	long	ln_asked;		/* last time we QUERIED for this addr */
	short	ln_state;		/* state */
	short	ln_flags;		/* flags (is_router) */
/* deletion time in seconds, 0 == locked */
#define ln_timer ln_rt->rt_rmx.rmx_expire
};
#define LLNDP6_PHASEDOUT	0	/* invalid but refcnt > 0 */
#define LLNDP6_INCOMPLETE	1	/* no info yet */
#define LLNDP6_PROBING		2	/* probe */
#define LLNDP6_REACHABLE	3	/* reachable */
#define LLNDP6_STALE            4       /* stale */
#define LLNDP6_DELAY            5       /* delay */
#define LLNDP6_BUILTIN		6	/* don't fall into probing */

#define M_NOPROBE		M_BCAST	/* don't trigger NUD probes */

#ifdef _KERNEL
/*
 * Neighbor Discovery specific interface flag.
 */
#define IFA_BOOTING	RTF_XRESOLVE


void	ndsol6_output __P((struct ifnet *,
		struct mbuf *, struct in6_addr *, struct in6_addr *, int));
void	ndadv6_output __P((struct ifnet *, struct in6_addr *, 
		struct in6_addr *, struct in6_addr *, int));
void	redirect6_output __P((struct mbuf *, struct rtentry *));
int	ndsol6_input __P((struct mbuf *, struct ifnet *));
int	ndadv6_input __P((struct mbuf *, struct ifnet *));
int	rtsol6_input __P((struct mbuf *, struct ifnet *));
int	rtadv6_input __P((struct mbuf *, struct ifnet *));
int	redirect6_input __P((struct mbuf *, struct ifnet *));

int	ndp6_resolve __P((struct ifnet *,
	   struct rtentry *, struct mbuf *, struct sockaddr *, u_char *));
void	ndp6_ifinit __P((struct ifnet *, struct ifaddr *));
void	ndp6_rtrequest __P((int, struct rtentry *, struct sockaddr *));
void	ndp6_rtlost __P((struct rtentry *, int));
struct	llinfo_ndp6 *ndplookup __P((struct in6_addr *, int, struct ifnet *));
struct rtentry *rtlookup __P((struct in6_addr *, int, struct ifnet *));
int	ndp6_do_dad (struct in6_addr *, struct ifnet *);

#endif /* KERNEL */
#endif /* _NO_XOPEN4 && _NO_XOPEN5 */

#endif /* !_NETINET_IF_NDP6_H_ */
