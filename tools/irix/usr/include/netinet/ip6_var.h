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

#ifndef _NETINET_IP6_VAR_H_
#define _NETINET_IP6_VAR_H_

#if _NO_XOPEN4 && _NO_XOPEN5
/*
 * Overlay for IPv6 header used for checksum by other protocols.
 */
struct ip6ovck {
	u_int32_t ih6_len;			/* first word */
	union {
		u_int32_t ihuw6_wrd1;		/* second word */
		struct {
			u_int8_t  ihu6_x;	/* reserved (0) */
			u_int8_t  ihu6_pr;	/* protocol */
			u_int16_t ihu6_y;	/* reserved (0) */
		} ihus6_wrd1;
	} ihu6_wrd1;
};

#define ih6_wrd0	ih6_len
#define ih6_wrd1	ihu6_wrd1.ihuw6_wrd1
#define ih6_x		ihu6_wrd1.ihus6_wrd1.ihu6_x
#define ih6_pr		ihu6_wrd1.ihus6_wrd1.ihu6_pr
#define ih6_y		ihu6_wrd1.ihus6_wrd1.ihu6_y

#if defined(_KERNEL)
/*
 * Structure for ctlinput routines.
 */
struct ctli_arg {
	struct ipv6 *ctli_ip;
	struct mbuf *ctli_m;
	void * ip6c_cmdarg;
};

/*
 * IPv6 reassembly queue structure.  Each fragment
 * being reassembled is attached to one of these structures.
 * They are timed out after ipq_ttl drops to 0, and may also
 * be reclaimed if memory becomes tight.
 */
struct ip6q {
	u_int32_t ip6q_head;		/* ip6q_head <-> ip6q_hlim: ipv6 header */
	u_int8_t  ip6q_len;		
	u_int8_t  ip6q_nxt;		/* next header type of this fragment */
	u_int8_t  ip6q_hlim;		/* for alignment */

	struct	  ip6asfrag *ip6q_down; /* to IPv6 headers of fragments */
	struct    ip6asfrag *ip6q_up;

	u_int32_t ip6q_id;		/* sequence id for reassembly */
	u_int32_t ip6q_ttl;		/* time for reass q to live (aligned) */

	struct	  in6_addr ip6q_src, ip6q_dst;

	struct	  ip6q *ip6q_next;	/* to other reass headers */
	struct    ip6q *ip6q_prev;

	int       ip6q_unfrglen;	/* leng of unfragmentable part */
	struct    ifnet *ip6q_ifp;	/* received interface (for icmp errs) */
};

/*
 * IPv6 header, when holding a fragment.
 *
 * Note: ip6f_down must be at same offset as ip6q_down above
 */
struct	ip6asfrag {
	u_int32_t ip6af_head;		/* IPv6 header */
	u_int16_t ip6af_hlen;		/* IPv6 header */
	u_int8_t  ip6af_nxt;		/* IPv6 header */
	u_int8_t  ip6af_hlim;		/* IPv6 header */

	struct	  ip6asfrag *ip6af_down;/* ip6q_down */
	struct	  ip6asfrag *ip6af_up;	/* ip6q_up */

	struct mbuf *ip6af_m;		/* pointer to fragment mbuf */

	u_int16_t ip6af_offset;		/* offset of next header in IPv6 */
	u_int16_t ip6af_frglen;		/* fragment length */
	u_int16_t ip6af_off;		/* fragment offset */
	u_int16_t ip6af_mff;		/* more fragment bit */
};

/*
 * Helper struct for all the memberships on a given socket
 * This list protected by the socket lock.
 */

struct ip6_membership {
	struct ip6_membership *next;
	struct in6_multi *ip6m_membership;
};

/*
 * Structure stored in an mbuf attached to inpcb.ip_moptions and
 * passed to ip_output when IP multicast options are in use.
 */
struct ip6_moptions {
	struct	ifnet   *im6o_multicast_ifp;  /* ifp for outgoing multicasts */
	u_char	         im6o_multicast_hlim; /*hop lim for outgoing mcasts */
	u_char		 im6o_multicast_loop; /* 1 => hear sends if a member */
	int		 im6o_multicast_vif;  /* vif num outgoing multicasts */
	struct ip6_membership *im6o_membership; /* list of memberships */
};



/*
 * Control options for outgoing packets
 */

/* Routing header related info */
struct	ip6po_rhinfo {
	struct	ip6_rthdr *ip6po_rhi_rthdr; /* Routing header */
	struct	route_in6 ip6po_rhi_route; /* Route to the 1st hop */
};
#define ip6po_rthdr	ip6po_rhinfo.ip6po_rhi_rthdr
#define ip6po_route	ip6po_rhinfo.ip6po_rhi_route
#define ip6po_rthdr2    ip6po_rhinfo2.ip6po_rhi_rthdr
#define ip6po_route2    ip6po_rhinfo2.ip6po_rhi_route

/* Nexthop related info */
struct  ip6po_nhinfo {
        struct  sockaddr_in6 *ip6po_nhi_nexthop; /* XXX Arthur - 
						    BSD uses sockaddr* */
        struct  route_in6 ip6po_nhi_route; /* Route to the nexthop */
};
#define ip6po_nexthop   ip6po_nhinfo.ip6po_nhi_nexthop
#define ip6po_nextroute ip6po_nhinfo.ip6po_nhi_route

struct  ip6_pktopts {
        int     ip6po_hlim;     /* Hoplimit for outgoing packets */

        /* Outgoing IF/address information */
        struct  in6_pktinfo *ip6po_pktinfo;

        /* Next-hop address information */
        struct  ip6po_nhinfo ip6po_nhinfo;

        struct  ip6_hbh *ip6po_hbh; /* Hop-by-Hop options header */

        /* Destination options header (before a routing header) */
        struct  ip6_dest *ip6po_dest1;

        /* Routing header related info. */
        struct  ip6po_rhinfo ip6po_rhinfo;

        /* Mobile IPv6 type 2 Routing header. */
        struct  ip6po_rhinfo ip6po_rhinfo2;

        /* Destination options header (after a routing header) */
        struct  ip6_dest *ip6po_dest2;

        /* Mobility header (just before an upper layer header) */
        struct  ip6_mobility *ip6po_mobility;

        int     ip6po_tclass;   /* traffic class */

        int     ip6po_minmtu;  /* fragment vs PMTU discovery policy */
#define IP6PO_MINMTU_MCASTONLY  -1 /* default; send at min MTU for multicast*/
#define IP6PO_MINMTU_DISABLE     0 /* always perform pmtu disc */
#define IP6PO_MINMTU_ALL         1 /* always send at min MTU */

        int ip6po_flags;
#define IP6PO_REACHCONF 0x01    /* upper-layer reachability confirmation */
#if 0                           /* obsoleted; do not reuse the value */
#define IP6PO_MINMTU    0x02    /* use minimum MTU (IPV6_USE_MIN_MTU) */
#endif
#define IP6PO_DONTFRAG  0x04    /* disable fragmentation (IPV6_DONTFRAG) */
#define IP6PO_USECOA    0x08    /* use care of address */

        int     needfree;       /* members dynamically allocated */
};

/*
 * Control options for incoming packets
 */

struct ip6_recvpktopts {
	struct mbuf *head;	/* mbuf chain of data passed to a user */

#ifdef SO_TIMESTAMP
	struct mbuf *timestamp;	/* timestamp */
#endif
	struct mbuf *hlim;	/* received hop limit */
	struct mbuf *pktinfo;	/* packet information of rcv packet */
	struct mbuf *hbh;	/* HbH options header of rcv packet */
	struct mbuf *dest;	/* Dest opt header of rcv packet */
	struct mbuf *rthdr;	/* Routing header of rcv packet */
};



#define IP6_DONTFRAG	0x4		/* ip6_outpt must not fragment */
#define IPV6_UNSPECSRC	0x200		/* allow :: as source address */

#define IP6_INSOPT_NOALLOC	1
#define IP6_INSOPT_RAW          2

extern u_int32_t  ip6_id;		/* IPv6 packet ctr, for ids */
extern struct socket *ip6_mrouter;	/* multicasr routing daemon */

extern int	  ip6printfs;
#define D6_INPUT	0x00000001
#define D6_CTLIN	0x00000002
#define D6_MCASTIN	0x00000004
#define D6_REASS	0x00000008
#define D6_OPTIN	0x00000010
#define D6_ETHERIN	0x00000020
#define D6_SITIN	0x00000040
#define D6_FORWARD	0x00000080
#define D6_OUTPUT	0x00000100
#define D6_CTLOUT	0x00000200
#define D6_MCASTOUT	0x00000400
#define D6_FRAG		0x00000800
#define D6_OPTOUT	0x00001000
#define D6_ETHEROUT	0x00002000
#define D6_SITOUT	0x00004000
#define D6_SITCTL	0x00008000
#define D6_INIT		0x00010000
#define D6_RAW		0x00020000
#define D6_NDP0		0x00040000
#define D6_NDP1		0x00080000
#define D6_NDP2		0x00100000
#define D6_UDP		0x00200000
#define D6_PMTU		0x00400000
#define D6_TCP0		0x00800000
#define D6_TCP1		0x01000000
#define D6_AH		0x02000000
#define D6_ESP		0x04000000
#define D6_KEY		0x08000000
#define D6_TUGCTL	0x10000000
#define D6_TUGIN	0x20000000
#define D6_TUGOUT	0x40000000

int	 ah6_input __P((struct mbuf **, struct ifnet *,
  struct ipsec *, int *, int));
struct mbuf *
	 ah6_output __P((struct mbuf *, struct mbuf *, struct ip_soptions *));
int	 dopt6_dontfrag __P((struct mbuf *));
int	 dest6_input __P((struct mbuf **, struct ifnet *,
  struct ipsec *, int *, int));
int	 end6_input __P((struct mbuf **, struct ifnet *,
  struct ipsec *, int *, int));
int	 esp6_input __P((struct mbuf **, struct ifnet *,
  struct ipsec *, int *, int));
struct mbuf *
	 esp6_output __P((struct mbuf *, struct mbuf *,
			  struct ip_soptions *, int, int));
void	 frag6_deq __P((struct ip6asfrag *));
void	 frag6_drain __P((void));
void	 frag6_enq __P((struct ip6asfrag *, struct ip6asfrag *));
int	 frag6_input __P((struct mbuf **, struct ifnet *,
  struct ipsec *, int *, int));
void	 frag6_slowtimo __P((void));
void	 hd6_outoptions __P((struct mbuf *));
int     ip6_process_hopopts __P((struct mbuf *, u_int8_t *, int, u_int32_t *,
                                 u_int32_t *, struct ifnet*)); 
int	 ip6_ctloutput __P((int, struct socket *, int, int, struct mbuf **));
struct mbuf *
	 ip6_dropoption __P((struct mbuf *, int));
void	 ip6_freemoptions __P((struct ip6_moptions *));
int	 ip6_getoptions __P((struct mbuf *, struct mbuf **, int));
void	 ip6_init __P((void));
void	 ip6_rtflush __P((struct in6_addr *, struct ifnet *));
void	 ip6_input __P((struct mbuf *, struct route *));
int	 ip6_mforward __P((struct ipv6 *, struct ifnet *,
			   struct mbuf *, struct ip6_moptions *));
int	 ip6_output __P((struct mbuf *, struct ip6_pktopts *, struct route *,
			 int, struct ip6_moptions *, struct inpcb *, int));
void	 ip6_cksum __P((struct mbuf *, struct mbuf *, struct in6_addr *,
			u_int32_t, u_int8_t, int));
void    ip6_notify_pmtu(struct inpcb *, struct sockaddr_in6 *, u_int32_t *);
void    ip6_savecontrol __P((struct inpcb *, struct ip6_hdr *, struct mbuf *,
			     struct ip6_recvpktopts *, struct ifnet *));
void    init_ip6pktopts(struct ip6_pktopts *);
int     ip6_setpktoptions(struct mbuf *, struct ip6_pktopts *,
			  struct ip6_pktopts *, int, int, int);
void    ip6_clearpktopts(struct ip6_pktopts *, int);
struct ip6_pktopts *ip6_copypktopts(struct ip6_pktopts *, int);
int in6_selectroute(struct sockaddr_in6 *, struct ip6_pktopts *,
		    struct ip6_moptions *, struct route *, 
		    struct ifnet **,
		    struct rtentry **, int);
int	 ip6_sysctl __P((int *, u_int, void *, size_t *, void *, size_t));
void	 ip6ip6_input __P((struct mbuf *, struct ifnet *,
  struct ipsec *, int *, int));
void	 opt6_ctlinput __P((int, struct sockaddr *, void *));
void	 rip6_init __P((void));
int	 rip6_ctloutput __P((int, struct socket *, int, int, struct mbuf **));
void     rip6_ctlinput __P((int, struct sockaddr *, void *));
int	 rip6_input __P((struct mbuf **, struct ifnet *,
  struct ipsec *ipsec, int *, int));
int	 rip6_usrreq __P((struct socket *,
	    int, struct mbuf *, struct mbuf *, struct mbuf *));
int	 route6_input __P((struct mbuf **, struct ifnet *,
  struct ipsec *, int *, int));
void	 opt6_reverse __P((struct ipv6 *, struct mbuf *));

extern void log(int level, char *fmt, ...);

#endif /* defined(_KERNEL) */
#endif /* _NO_XOPEN4 && _NO_XOPEN5 */

#endif
