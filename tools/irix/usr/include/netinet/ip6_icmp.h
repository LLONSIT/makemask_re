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
/*
 *
 * RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to restrictions
 * as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data
 * and Computer Software clause at DFARS 252.227-7013, and/or in similar or
 * successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -
 * rights reserved under the Copyright Laws of the United States.
 *
 *
 *	This file contains kernel specific ICMPv6 related definitions.
 *
 *	@(#)ip6_icmp.h	8.1 (SGI) 10/1/99
 */

#ifndef _NETINET_IP6_ICMP_H_
#define _NETINET_IP6_ICMP_H_
#if _NO_XOPEN4 && _NO_XOPEN5

#define ICMP6_GRPLEN	24		/* group stuff */
#define ICMP6_RSLEN	sizeof(struct nd_router_solicit)
#define ICMP6_RALEN	sizeof(struct nd_router_advert)
#define ICMP6_NSLEN	sizeof(struct nd_neighbor_solicit)
#define ICMP6_NALEN	sizeof(struct nd_neighbor_advert)
#define ICMP6_RDLEN	sizeof(struct nd_redirect)

/*
 * Useful offsets to ICMPv6 fields
 */
#define ICMP6_CKSUM_OFFSET (int)((long)&(((struct icmp6_hdr *)0)->icmp6_cksum))
#define	ICMP6_INFOTYPE(type)	((type) >= ICMP6_ECHO_REQUEST)
#define ICMP6_ND_PRIORITY	IPV6_PRIORITY_15

/* IPSec flags */

#define	ICMP6SEC_ERRORS		1	/* auth error types */
#define ICMP6SEC_REQUESTS	2	/* auth echo requests */
#define ICMP6SEC_GROUPS		4	/* auth group management */
#define ICMP6SEC_NEIGHBORS	8	/* auth neighbor management */

#if defined(_KERNEL)

#define ICMP6_TIMER_SCALE	1000
#define ICMP6_TIMER2HZ(mrd)	(ntohs(mrd) * PR_FASTHZ / ICMP6_TIMER_SCALE)
/*
 * Macro to compute a random timer value between 1 and its argument
 * in countdown period units.  We assume that the routine random()
 * is defined somewhere (and that it returns a positive number).
 */
#define	ICMP6_RANDOM_DELAY(maxdelay)	(random() % (maxdelay) + 1)
#define ICMP6_DEFAULT_DELAY()		(random() % (9 * PR_FASTHZ) + 1)

#define ICMP6_MAX_RATE		10

void	icmp6_error __P((struct mbuf *, int, int, caddr_t, struct ifnet *));
void	icmp6_errparam __P((struct mbuf *, struct mbuf *,
  int, struct ifnet *, int));
void	icmp6_fasttimo __P((void));
int     icmp6_filter __P((struct inpcb *, struct ipv6 *));
int     icmp6_filter_set __P((struct inpcb *, struct mbuf *));
int     icmp6_filter_get __P((struct inpcb *, struct mbuf **));
void	icmp6_init __P((void));
int	icmp6_input __P((struct mbuf **, struct ifnet *,
  struct ipsec *, int *, int));
void	icmp6_joingroup __P((struct in6_multi *));
void	icmp6_leavegroup __P((struct in6_multi *));
void	icmp6_reflect __P((struct mbuf *, struct ifnet *, struct mbuf *));
struct route * get_ll_route(struct in6_addr*, struct ifnet *, union route_6 *);

#endif /* defined(_KERNEL) */
#endif /* _NO_XOPEN4 && _NO_XOPEN5 */
#endif
