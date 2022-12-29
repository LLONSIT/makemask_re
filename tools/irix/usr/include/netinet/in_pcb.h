/*
 * Copyright (c) 1982, 1986, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)in_pcb.h	8.1 (Berkeley) 6/10/93
 */
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

#ifndef __NETINET_INPCB_H__
#define __NETINET_INPCB_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "sys/sema.h"
#include <netinet/ipsec.h>
#include <netinet/icmp6.h>
struct in_addr;
struct mbuf;
struct route;
struct socket;
struct inpcbstat;


#if _NO_XOPEN4 && _NO_XOPEN5 

#define in6pcb          inpcb   /* for KAME src sync over BSD*'s */
#define in6p_sp         inp_sp  /* for KAME src sync over BSD*'s */
#define in6p_socket     inp_socket  /* for KAME src sync over BSD*'s */
#define in6p_flags      inp_flags  /* for KAME src sync over BSD*'s */

/*
 * because IPv6 addresses are huge !
  */
union route_6 {
	struct route route;
	struct {
		struct  rtentry *space_rt;
		struct  sockaddr_in6 spare_dst;
	} spare_route6;
};
#endif /* _NO_XOPEN4 && _NO_XOPEN5 */

/* 
 * the addresses and ports in struct inaddrpair are only valid when the 
 * associated socket is in the PF_INET domain.
 */
struct inaddrpair {
	struct	in_addr iap_faddr;	/* foreign host table entry */
	u_short	iap_fport;		/* foreign port */
	struct	in_addr	iap_laddr;	/* local host table entry */
	u_short	iap_lport;		/* local port */
};

#if _NO_XOPEN4 && _NO_XOPEN5
struct sa_4in6 {
#ifndef _offsetof                /* XXX */
#define _offsetof(type, member)  ((size_t)(&((type *)0)->member))
#endif
        u_int8_t sa46_pad1[_offsetof(struct sockaddr_in6, sin6_addr)]; /* XXX */
        u_int32_t sa46_pad2[3];
        struct in_addr sa46_addr4;
};

struct in_endpoints {
        /* protocol dependent part, local and foreign addr */
	union {
		 /* foreign host table entry */
		struct sa_4in6 ie46_foreign;
		struct sockaddr_in6 ie6_foreign;
	} ie_dependfaddr;
	union {
		/* local host table entry */
		struct  sa_4in6 ie46_local;
		struct sockaddr_in6 ie6_local;
	} ie_dependladdr;
#define ie_fport        ie_dependfaddr.ie6_foreign.sin6_port
#define ie_lport        ie_dependladdr.ie6_local.sin6_port
#define ie_faddr        ie_dependfaddr.ie46_foreign.sa46_addr4
#define ie_laddr        ie_dependladdr.ie46_local.sa46_addr4
#define ie6_fsa         ie_dependfaddr.ie6_foreign
#define ie6_lsa         ie_dependladdr.ie6_local
};
#endif /* _NO_XOPEN4 && _NO_XOPEN5 */

/*
 * To save space, each hash list uses a small head structure consisting
 * only of threading pointers.
 */
struct in_pcbhead {
	/* fields must line up with PCB below */
	struct	inpcb *hinp_next;
	struct	inpcb *hinp_prev;
	struct  inpcb *hinp_waste;
	int	hinp_refcnt;
#ifdef _PCB_DEBUG
	int	hinp_traceable;
#endif
        mutex_t hinp_sem;
};

#ifdef _PCB_DEBUG
struct inpcb_trace_rec {
	long 	*addr;
	short	op;
	short	cpu;
	int	refcnt;
};

#define	_N_PCB_TRACE	128	

extern int atomicIncPort(int *, int, int);
#define	_IN_PCB_TRACE(inp, opr) { \
	if (inp->inp_traceable) { \
		int t;	\
		t = atomicIncPort(&inp->inp_trace_ptr, _N_PCB_TRACE - 1, 0); \
		(inp)->inp_trace[t].addr = __return_address; \
		(inp)->inp_trace[t].op = (opr); \
		(inp)->inp_trace[t].cpu = cpuid(); \
		(inp)->inp_trace[t].refcnt = (inp)->inp_refcnt; \
	} \
}

#else
#define	_IN_PCB_TRACE(inp, opr)
#endif	/* _PCB_DEBUG */


/*
 * Common structure pcb for internet protocol implementation.
 * Here are stored pointers to local and foreign host table
 * entries, local and foreign socket numbers, and pointers
 * up (to a socket structure) and down (to a protocol-specific)
 * control block.
 */
struct inpcb {
	struct	inpcb *inp_next,*inp_prev;
					/* pointers to other pcb's */
	struct	inpcb *inp_head;	/* pointer back to chain of inpcb's
					   for this protocol */
	int	inp_refcnt;		/* reference count */
#ifdef _PCB_DEBUG
	int	inp_traceable;
#endif
	struct	in_pcbhead *inp_hhead;	/* pointer to hash head */
	struct	inaddrpair inp_iap;	/* foreign and local addr pair */
	/* needed by both heads and individual PCBs */
	u_short		inp_hashflags;	/* hashing flags */
	union {
	   /* The real PCB */		
	   struct {
		struct	socket *u1_socket;/* back pointer to socket */
		caddr_t	u1_ppcb;	  /* pointer to per-protocol pcb */
		struct	route u1_route;   /* (ipv4) route */
		u_short	u1_hashval;	  /* Hash value */
		u_char	u1_ip_tos;	  /* TOS */
		u_char	u1_ip_ttl;	  /* TTL */
		int	u1_flags;	  /* generic IP/datagram flags */
		struct	mbuf *u1_options; /* IP options */
		struct	mbuf *u1_moptions;/* IP multicast options */
	   } pcb_u1;
	   /* The hashing stuff */
	   struct {
		u_short		(*u2_hashfun)(struct inpcb *, void *,
					      u_short, void *, u_short, int);
		int		u2_wildport;	/* wildcard port */
	    	int		u2_tablesz;	/* size of table */

		struct in_pcbhead    *u2_table; /* hash tbl inpcb's ptrs, etc*/
		struct inpcb	**u2_cache;	/* cached pcb (obsoleted!) */
		mutex_t u2_mutex;        	/* mutex to protect the whole list */

#ifdef DEBUG
		u_int		*u2_dstats;	/* distribution statistics */
		u_short		u2_stats;	/* statistics */
#endif
	   } pcb_u2;
	} inp_u;

#if _NO_XOPEN4 && _NO_XOPEN5
	struct  inpcbpolicy *inp_sp; /* for IPSEC */
	u_int16_t inp_fatype;		/* foreign address type */
	u_int16_t inp_latype;		/* local address type */
	struct in_endpoints inp_ie;	/* foreign, local sockaddrs */
	union	route_6 inp_route6;	/* (ipv6) routing entry */

#ifdef INTERFACES_ARE_SELECTABLE	/* have we ever defined this? */
	struct ifaddr *inp_ifa;z	/* interface address to use */
#define INP_IFA (inp ? inp->inp_ifa : (struct ifaddr *)0)
#else
#define INP_IFA ((struct ifaddr *)0)
#endif /* INTERFACES_ARE_SELECTABLE */

	struct ip_soptions {
		struct ip_seclist *lh_first;
	} inp_soptions; /* IP security */

	u_int8_t inp_proto;		/* protocol */
	int inp_scope_id;		/* Latest scope if for local addr */
	u_int32_t       inp_flow;

	struct {
		/* IP options */
		struct	mbuf *inp6_options;
		/*
		 * IP6 options for incoming packets.
		 * XXX: currently unused but remained just in case.
		 */
		struct	ip6_recvpktopts *inp6_inputopts;
		/* IP6 options for outgoing packets */
		struct	ip6_pktopts *inp6_outputopts;
		/* IP multicast options */
		struct	ip6_moptions *inp6_moptions;
		/* ICMPv6 code type filter */
		/* XXX Note that KAME/BSD uses a struct icmp6_filter* here */
		struct	icmp6_filter in6_icmp6filt;
		/* IPV6_CHECKSUM setsockopt */
		int	inp6_cksum;
		u_short	inp6_ifindex;
		short	inp6_hops;
	} inp_depend6;

        struct ifqueue *inp_deferred_inputq;/* deferred input queue */
	__uint32_t inp_callout_active;  /* callout function active */
        __uint32_t inp_delcount;        /* count of delayed wakeup input */
        __uint64_t reserved3;           /* future expansion field */
        __uint64_t reserved4;           /* future expansion field */

#endif /* _NO_XOPEN4 && _NO_XOPEN5 */
#ifdef _PCB_DEBUG
	struct inpcb_trace_rec inp_trace[_N_PCB_TRACE];
	int inp_trace_ptr;
#define _PCB_SLOP	((_N_PCB_TRACE * sizeof(struct inpcb_trace_rec)) + \
			 (2 * sizeof(int)))

#endif	/* _PCB_DEBUG */
};

#define	inp_socket	inp_u.pcb_u1.u1_socket
#define	inp_ppcb	inp_u.pcb_u1.u1_ppcb
#define	inp_options	inp_u.pcb_u1.u1_options
#define	inp_faddr	inp_iap.iap_faddr /* ipv4 address */
#define	inp_fport	inp_iap.iap_fport /* port */
#define	inp_laddr	inp_iap.iap_laddr /* ipv4 address */
#define	inp_lport	inp_iap.iap_lport /* port */
#define	inp_route	inp_u.pcb_u1.u1_route /* ipv4 route */
#define	inp_moptions	inp_u.pcb_u1.u1_moptions
#define	inp_ip_ttl	inp_u.pcb_u1.u1_ip_ttl
#define	inp_ip_tos	inp_u.pcb_u1.u1_ip_tos
#define	inp_hashval	inp_u.pcb_u1.u1_hashval
#define inp_flags	inp_u.pcb_u1.u1_flags

#define	inp_hashfun	inp_u.pcb_u2.u2_hashfun
#define	inp_tablesz	inp_u.pcb_u2.u2_tablesz
#define	inp_table	inp_u.pcb_u2.u2_table
#define inp_mutex       inp_u.pcb_u2.u2_mutex
#ifdef DEBUG
#define inp_stats	inp_u.pcb_u2.u2_stats
#define inp_dstats	inp_u.pcb_u2.u2_dstats
#endif
#define inp_wildport	inp_u.pcb_u2.u2_wildport

#if _NO_XOPEN4 && _NO_XOPEN5
#define	inp_tos		inp_u.pcb_u1.u1_ip_tos
#define	inp_ttl		inp_u.pcb_u1.u1_ip_ttl
#define in6p_flowinfo   inp_flow
#define inp_filter      inp_depend6.in6_icmp6filt
#define in6p_hops       inp_depend6.inp6_hops /* deflt hop lim */
#define in6p_options    inp_depend6.inp6_options
#define in6p_inputopts  inp_depend6.inp6_inputopts
#define in6p_outputopts inp_depend6.inp6_outputopts
#define in6p_moptions   inp_depend6.inp6_moptions
#define in6p_icmp6filt  inp_depend6.inp6_icmp6filt
#define in6p_cksum      inp_depend6.inp6_cksum
#define inp_cksoff      in6p_cksum      
#define inp6_ifindex    inp_depend6.inp6_ifindex

#define sotopf(so)  ((so)->so_proto->pr_domain->dom_family)
#define INP_ISINET6(inp) \
 /* struct inpcb * inp; */ \
	((sotopf((inp)->inp_socket) == AF_INET6)? 1: 0)
#define inp_fport6 inp_ie.ie_fport
#define INP_FPORT(inp) \
 /* struct inpcb * inp; */ \
	(INP_ISINET6(inp) ? ((inp)->inp_fport6) : ((inp)->inp_fport))
#define	inp_faddr6	inp_ie.ie6_fsa.sin6_addr /* foreign ipv6 addr */
#define in6p_faddr inp_faddr6
#define INP_FADDR6(inp) \
 /* struct inpcb * inp; */ \
	((inp)->inp_faddr6)
#define INP_FADDR(inp) /* provide access to a mapped or compatible address */ \
 /* struct inpcb * inp; */ \
	(INP_ISINET6(inp) ? ((inp)->inp_ie.ie_faddr) : ((inp)->inp_faddr))

#define inp_lport6 inp_ie.ie_lport
#define INP_LPORT(inp) \
 /* struct inpcb * inp; */ \
	(INP_ISINET6(inp) ? ((inp)->inp_lport6) : ((inp)->inp_lport))
#define	inp_laddr6	inp_ie.ie6_lsa.sin6_addr /* local ipv6 addr */
#define in6p_laddr inp_laddr6
#define INP_LADDR6(inp) \
 /* struct inpcb * inp; */ \
	((inp)->inp_laddr6)
#define INP_LADDR(inp) /* provide access to a mapped or compatible address */ \
 /* struct inpcb * inp; */ \
	(INP_ISINET6(inp)? ((inp)->inp_ie.ie_laddr) : ((inp)->inp_laddr))
#define inp_route6 inp_route6.route
#define in6p_route inp_route6
#define INP_PROUTE(inp) \
 /* struct inpcb * inp; */ \
	(INP_ISINET6(inp) ? (&(inp)->inp_route6) : (&(inp)->inp_route))
#endif /* _NO_XOPEN4 && _NO_XOPEN5 */

/* address types */
#define IPATYPE_UNBD            0x0     /* unbound address */
#define IPATYPE_IPV4            0x1     /* IPv4 address */
#define IPATYPE_IPV6            0x2     /* IPv6 address */
#define IPATYPE_DUAL            0x3     /* both IPv4 & IPv6 address */

/* flags in inp_flags: */
#define	INP_RECVOPTS		0x01	/* receive incoming IP options */
#define	INP_RECVRETOPTS		0x02	/* receive IP options for reply */
#define	INP_RECVDSTADDR		0x04	/* receive IP dst address */
#define IN6P_PKTINFO            0x010000 /* receive packet info */
#define IN6P_HOPLIMIT           0x020000 /* receive TTL/hlim info */
#define IN6P_NEXTHOP            0x040000
#define IN6P_HOPOPTS            0x080000 /* receive hop-by-hop options */
#define IN6P_DSTOPTS            0x100000 /* receive destination options */
#define IN6P_RTHDR              0x200000 /* receive routing header */
#define IN6P_TCLASS             0x400000 /* receive traffic class */
#define IN6P_MTU                0x800000 /* receive path MTU */

#define IN6P_BINDV6ONLY         0x10000000 /* do not grab IPv4 traffic */

#define INP_CONTROLOPTS         (INP_RECVOPTS|INP_RECVRETOPTS|INP_RECVDSTADDR|\
                                 IN6P_PKTINFO|IN6P_HOPLIMIT|IN6P_NEXTHOP|\
                                 IN6P_HOPOPTS|IN6P_DSTOPTS|IN6P_RTHDR|\
                                 IN6P_TCLASS)
#define	INP_HDRINCL		0x08	/* user supplies entire IP header */
#define INP_NOPROBE             0x80    /* don't trigger NUD probes */

#define INP_COMPATV4            0x10    /* can be used by IPv4 stack */
#define INP_COMPATV6            0x20    /* can be used by IPv6 stack */
#define INP_COMPATANY           0x30    /* can be used by any stack */

#define INP_NEEDAUTH            0x100   /* need authentication */
#define INP_NEEDCRYPT           0x200   /* need confidentiality */
#define INP_HIGHBW		0x400

/* flags for in_pcblookup operation */
#define	INPLOOKUP_WILDCARD	0x1            
#define	INPLOOKUP_LISTEN	0x4     /* only search bucket 0 */
#define	INPLOOKUP_ALL		0x8     /* search one particular bucket */
#define	INPLOOKUP_BIND		0x10

/* flags in inp_hashflags */
#define INPFLAGS_CLTS		0x0001		/* Connectionless service */
#define INPFLAGS_LISTEN		0x0002		/* Listening endpoint */
#define INPFLAGS_MOVED		0x0004		/* PCB has moved */

#if _NO_XOPEN4 && _NO_XOPEN5
#define IP6_ADDRS_EQUAL(inp, laddr, lport, faddr, fport) \
			((INP_LPORT(inp) == (lport)) && \
			(INP_FPORT(inp) == (fport)) && \
			SAME_ADDR6((inp)->inp_faddr6, faddr) && \
			SAME_ADDR6((inp)->inp_laddr6, laddr))
#endif /* _NO_XOPEN4 && _NO_XOPEN5 */

#define IP_ADDRS_EQUAL(inp, laddr, lport, faddr, fport) \
			((INP_LPORT(inp) == (lport)) && \
			(INP_FPORT(inp) == (fport)) && \
			(INP_FADDR(inp).s_addr == (faddr).s_addr) && \
			(INP_LADDR(inp).s_addr == (laddr).s_addr))


#define	sotoinpcb(so)	((struct inpcb *)(so)->so_pcb)

#ifdef _KERNEL

extern int max_deferral;

#define _TBLELEM(inp)	(&(inp)->inp_head->inp_table[(inp)->inp_hashval])
#define _TBLELEMHEAD(inp)	_TBLELEM(inp)->hinp_next
#define _TBLELEMTAIL(inp)	_TBLELEM(inp)->hinp_prev

#include "sys/atomic_ops.h"
#if defined(_PCB_DEBUG) || (_PCB_UTRACE)
extern int in_pcbhold(struct inpcb *);
#define INPCB_HOLD(inp)			in_pcbhold(inp)
#else
#define INPCB_HOLD(inp)			atomicAddInt(&(inp)->inp_refcnt, 1)
#endif	/* _PCB_DEBUG */

#ifdef _PCB_UTRACE
#include "sys/pda.h"
#include "sys/rtmon.h"
#define PCB_UTRACE(name, inp, ra) \
	UTRACE(RTMON_ALLOC, (name), (__int64_t)(inp), \
		UTPACK((ra), (inp) ? (inp)->inp_refcnt : 0));
#else
#define PCB_UTRACE(name, inp, ra)
#endif	/* _PCB_UTRACE */

#define INPCB_RELE(inp)			in_pcbrele(inp)

#define INHHEAD_LOCK(hinp)   { \
        ASSERT(!mutex_mine(&(hinp)->hinp_sem)); \
        mutex_lock(&(hinp)->hinp_sem, PZERO); \
  }
#define INHHEAD_UNLOCK(hinp) { \
        ASSERT(mutex_mine(&(hinp)->hinp_sem)); \
	mutex_unlock(&(hinp)->hinp_sem); \
  }
#define INHHEAD_ISLOCKED(hinp) mutex_mine(&(hinp)->hinp_sem)

#define RANDOM_PORT(i) \
	(u_short)((i) % (ipport_maxport - IPPORT_RESERVED + 1) + \
		IPPORT_RESERVED)

extern void	in_pcbinitcb(struct inpcb *, int, u_short, u_short);
extern void	in_losing(struct inpcb *);
extern int	in_pcballoc(struct socket *, struct inpcb *);
extern int	in_pcbbind(struct inpcb *, struct mbuf *);
extern int	in_pcbconnect(struct inpcb *, struct mbuf *);
extern int	in_pcbdetach(struct inpcb *);
extern void	in_pcbdisconnect(struct inpcb *);
extern void	in_pcbnotify(struct inpcb *, struct sockaddr *, u_short,
			     struct in_addr, u_short, int,
			     void (*)(struct inpcb *, int, void *),
			     void *);
extern int	in_pcbsetaddr(struct inpcb *, struct sockaddr_in *,
				struct inaddrpair *);
extern int	in_pcbsetaddrx(struct inpcb *, struct sockaddr_in *, 
			struct in_addr, struct inaddrpair *);
extern void	in_setpeeraddr(struct inpcb *, struct mbuf *);
extern void	in_setsockaddr(struct inpcb *, struct mbuf *);
extern int	in_pcbrele(struct inpcb *);
extern void	in_pcbpurgeif(struct inpcb *, struct ifnet *);

extern int	in_pcb_hashtablesize(void);

struct inpcb *in_pcblookupx(struct inpcb *, void *, u_short,
	void *, u_short, int, int);
struct inpcb *in_pcbfusermatch(struct inpcb *, void *, u_short, int);
extern void	in_pcbunlink(struct inpcb *);
/* support for TCP listening endpoints */
extern void	in_pcblisten(struct inpcb *);
extern void	in_pcbunlisten(struct inpcb *);
/* support for TCP TIME-WAIT endpoints */
extern void	in_pcbmove(struct inpcb *);

#if _NO_XOPEN4 && _NO_XOPEN5
struct rtentry *in6_rthost __P((struct in6_addr *));
void        in6_rtalloc __P((struct route *, struct ifaddr *));

extern int  in6_pcbbind __P((struct inpcb *, struct mbuf *));
extern int  in6_pcbconnect __P((struct inpcb *, struct mbuf *));
void     in6_pcbnotify __P((struct inpcb *, struct sockaddr *,
        u_int, struct in6_addr *, u_int, int, void (*)(struct inpcb *, int,
	void *), void *));
void     in6_pcbnotifyall __P((struct inpcb *, struct sockaddr *,
	            int, void (*)(struct inpcb *, int, void *), void *));
int      in6_setifa __P((struct inpcb *, struct ifaddr *));

int      ipsec_attach __P((struct inpcb *, struct sockaddr_ipsec *, int));
int      ipsec_detach __P((struct inpcb *, struct sockaddr_ipsec *, int));
int      ipsec_match __P((struct inpcb *, struct mbuf *, int));

void     ip6_freesoptions __P((struct inpcb *));
int      ip6_setoptions __P((struct mbuf **, struct mbuf *,
                             struct inpcb *));
int      in6_pcbladdr(struct inpcb *, struct sockaddr *,
		      struct in6_addr *);
int in6_selectsrc(struct sockaddr_in6 *,
			struct ip6_pktopts *,
			struct ip6_moptions *,
			struct route *,
			struct in6_addr *,
			struct in6_addr *);
int     in6_selecthlim(struct in6pcb *, struct ifnet *);
int in6_pcbsetport(struct in6_addr *, struct inpcb *);

#endif /* _NO_XOPEN4 && _NO_XOPEN5 */
int	set_inp_faddr __P((struct inpcb *, const struct in_addr));
int	set_inp_fport __P((struct inpcb *, const in_port_t));
int	set_inp_laddr __P((struct inpcb *, const struct in_addr));
int	set_inp_lport __P((struct inpcb *, const in_port_t));

	/*struct route * get_inp_proute __P((struct inpcb *));*/

void	copy_if_hints __P((struct inpcb *, struct route *));

#endif /* _KERNEL */
#ifdef __cplusplus
}
#endif
#endif /* __NETINET_INPCB_H__ */
