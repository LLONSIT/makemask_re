#ifndef __net_if__
#define __net_if__
/*
 * Copyright (c) 1982, 1986, 1989, 1993
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
 *	@(#)if.h	8.1 (Berkeley) 6/10/93
 */
/**************************************************************************
 *                                                                        *
 *               Copyright (C) 2002 Silicon Graphics, Inc.         	  *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 **************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Structures defining a network interface, providing a packet
 * transport mechanism (ala level 0 of the PUP protocols).
 *
 * Each interface accepts output datagrams of a specified maximum
 * length, and provides higher level routines with input datagrams
 * received from its medium.
 *
 * Output occurs when the routine if_output is called, with three parameters:
 *	(*ifp->if_output)(ifp, m, dst, rte)
 * Here m is the mbuf chain to be sent and dst is the destination address.
 * rte is the routing table entry.  This may be NULL.
 * The output routine encapsulates the supplied datagram if necessary,
 * and then transmits it on its medium.
 *
 * On input, each interface unwraps the data received by it, and either
 * places it on the input queue of a internetwork datagram routine
 * and posts the associated software interrupt, or passes the datagram to a raw
 * packet input routine.
 *
 * Routines exist for locating interfaces by their addresses
 * or for locating a interface on a certain network, as well as more general
 * routing and gateway routines maintaining information used to locate
 * interfaces.  These routines live in the files if.c and route.c
 */

#include <sys/socket.h>
#include <sys/sema.h>
#include <sys/time.h>
#include <net/if_arp.h>
#include <sys/hashing.h>

#ifdef __STDC__
/*
 * Forward structure declarations for function prototypes [sic].
 */
struct	mbuf;
struct	socket;
struct	rtentry;
struct	in_addr;
struct	t6if_attrs;
#endif

/*
 * Length of interface external name, including terminating '\0'.
 * Note: this is the same size as a generic device's external name.
 */
#define	IFNAMSIZ	16
#define	IF_NAMESIZE	IFNAMSIZ

/*
 * Structure describing information about an interface
 * which may be of interest to management entities.
 * keep if_data separate to make C++ happy
 */
struct	if_data {

	/* generic interface information */
	u_char	ifi_type;		/* ethernet, tokenring, etc */
	u_char	ifi_addrlen;		/* media address length */
	u_char	ifi_hdrlen;		/* media header length */
	u_int	ifi_mtu;		/* maximum transmission unit */
	u_int	ifi_metric;		/* routing metric (external only) */
	struct ifspeed {
		u_int   ifs_log2:4;		/* linespeed shift */
		u_int   ifs_value:28;		/* linespeed */
	} ifi_baudrate;

	/* volatile statistics */
	u_int	ifi_ipackets;		/* packets received on interface */
	u_int	ifi_ierrors;		/* input errors on interface */
	u_int	ifi_opackets;		/* packets sent on interface */
	u_int	ifi_oerrors;		/* output errors on interface */
	u_int	ifi_collisions;		/* collisions on csma interfaces */
	u_int	ifi_ibytes;		/* total number of octets received */
	u_int	ifi_obytes;		/* total number of octets sent */
	u_int	ifi_imcasts;		/* packets received via multicast */
	u_int	ifi_omcasts;		/* packets sent via multicast */
	u_int	ifi_iqdrops;		/* dropped on input, this interface */
	u_int	ifi_odrops;		/* output pkts discarded w/o error */
	u_int	ifi_noproto;		/* destined for unsupported protocol */
	time_t	ifi_lastchange;		/* last updated */
};

/*
 * info for delayed memory free
 */
struct delayed_free {
	caddr_t df_addr;		/* ptr to area to free */	
	size_t df_size;			/* size to free */	
	time_t df_time;			/* time of free */
};
/*
 * ifnet extension. These fields must not be used before calling if_attach()
 * since the structure is allocated there. This structure is subject to
 * changes or additions and must not be embedded into any driver structures
 * for that reason.
 */
struct ifnet_ext {
	caddr_t ife_rti;		/* Address of router_info structure */
					/* for igmp */
	caddr_t ife_in6_ifaddr;		/* (struct in6_ifaddr *) primary v6 */ 
					/* interface addr */
	struct in6_ifaddr *ife_6llocal;	/* link local addr of interface */
	char *ife_6l2addr;		/* MAC addr */
	u_int32_t ife_nd_linkmtu;       /* min(if_mtu, MTU from Rtr Advts)*/
	u_int32_t ife_ndpt_reachable;   /* reachable timer */
	u_int32_t ife_ndpt_retrans;     /* retransmit timer */
	u_int	ife_ndtype;		/* IPV6 neighbor discovery type */
	u_short	ife_site6;		/* IPv6 site index */
	u_short	ife_hlim;		/* IPv6 CurHopLimit */
	u_short ife_dadxmit;		/* number of DAD xmits */
	u_short ife_link_hdrlen;	/* link header length for L2TCPSEG */
	struct delayed_free *ife_delfree;  /* null, unless detached & freeing */
	__uint64_t reserved2;		/* future expansion field */
	__uint64_t reserved3;		/* future expansion field */
	__uint64_t reserved4;		/* future expansion field */
	__uint64_t reserved5;		/* future expansion field */
	__uint64_t reserved6;		/* future expansion field */
};

struct ifnet {
	char	*if_name;		/* name, e.g. ``en'' or ``lo'' */
	struct	ifnet *if_next;		/* all struct ifnets are chained */
	caddr_t in_ifaddr; /* (struct in_ifaddr *) primary v4 interface addr */
	u_short	if_index;		/* numeric abbreviation for this if  */
	short	if_unit;		/* sub-unit for lower level driver */
	short	if_timer;		/* time until if_watchdog called */
	__uint32_t	if_flags;	/* up/down, broadcast, etc. */
	struct if_data if_data;

	/* procedure handles */
	int	(*if_output)(struct ifnet *, struct mbuf *, struct sockaddr *,
		struct rtentry *);
					/* output routine */
	int	(*if_ioctl)(struct ifnet *, int, void *); /* ioctl routine */
	int	(*if_reset)(int, int);	/* bus reset routine */
	void	(*if_watchdog)(struct ifnet *);	/* timer routine */
	void	(*if_rtrequest)(int,struct rtentry *,struct sockaddr *);
				/* driver-specified route initialization */
	struct in_ifaddr *(*if_findaddr)(struct ifnet *, struct in_addr *,
		struct in_addr *, u_char *, u_char *, int);
					/* driver-specified address lookup */

	struct	ifqueue {
		struct	mbuf *ifq_head;
		struct	mbuf *ifq_tail;
		int	ifq_len;
		int	ifq_maxlen;
		u_int	ifq_drops;
		lock_t	ifq_lock;
	} if_snd;			/* output queue */

	/*
	 * Trusted IRIX: Any changes to the security
	 * information must be made at splnet or equiv.
	 */
	struct t6if_attrs *if_sec;	/* interface security information */
	u_long	if_sendspace;		/* for TCP */
	u_long	if_recvspace;		/* for TCP */

	mutex_t	if_mutex;
	int ipalias_count;		/* Num alias address config'd on i/f */
	struct ifnet_ext *if_ext;	/* ifnet extended data */
};

#define if_rti			if_ext->ife_rti
#define if_in6addr		if_ext->ife_in6_ifaddr
#define if_6llocal		if_ext->ife_6llocal
#define if_6l2addr		if_ext->ife_6l2addr
#define if_nd_linkmtu		if_ext->ife_nd_linkmtu
#define if_ndpt_reachable	if_ext->ife_ndpt_reachable
#define if_ndpt_retrans		if_ext->ife_ndpt_retrans
#define if_ndtype		if_ext->ife_ndtype
#define if_site6		if_ext->ife_site6
#define if_hlim			if_ext->ife_hlim
#define if_dadxmit		if_ext->ife_dadxmit
#define if_delfree		if_ext->ife_delfree

#ifdef _KERNEL				/* all of these should go away */
#define	if_mtu		if_data.ifi_mtu
#define	if_type		if_data.ifi_type
#define	if_addrlen	if_data.ifi_addrlen
#define	if_hdrlen	if_data.ifi_hdrlen
#define	if_metric	if_data.ifi_metric
#define	if_baudrate	if_data.ifi_baudrate
#define	if_ipackets	if_data.ifi_ipackets
#define	if_ierrors	if_data.ifi_ierrors
#define	if_opackets	if_data.ifi_opackets
#define	if_oerrors	if_data.ifi_oerrors
#define	if_collisions	if_data.ifi_collisions
#define	if_ibytes	if_data.ifi_ibytes
#define	if_obytes	if_data.ifi_obytes
#define	if_imcasts	if_data.ifi_imcasts
#define	if_omcasts	if_data.ifi_omcasts
#define	if_iqdrops	if_data.ifi_iqdrops
#define if_odrops	if_data.ifi_odrops
#define	if_noproto	if_data.ifi_noproto
#define	if_lastchange	if_data.ifi_lastchange
#endif

#define	if_idrops	if_iqdrops	/* XXX compatibility */

#define	IFF_UP		0x1		/* interface is up */
#define	IFF_BROADCAST	0x2		/* broadcast address valid */
#define	IFF_DEBUG	0x4		/* turn on debugging */
#define	IFF_LOOPBACK	0x8		/* is a loopback net */

#define	IFF_POINTOPOINT	0x10		/* interface is point-to-point link */
#define	IFF_NOTRAILERS	0x20		/* avoid use of trailers */
#define	IFF_RUNNING	0x40		/* resources allocated */
#define	IFF_NOARP	0x80		/* no address resolution protocol */

#define	IFF_PROMISC	0x100		/* receive all packets */
#define	IFF_ALLMULTI	0x200		/* receive all multicast packets */
#define	IFF_FILTMULTI	0x400		/* need to filter multicast packets */
#define	IFF_INTELLIGENT	0x400		/* MIPS ABI - protocols on interface */
#define	IFF_MULTICAST	0x800		/* supports multicast */

#define	IFF_CKSUM	0x1000		/* does checksumming */
#define IFF_ALLCAST	0x2000		/* does SRCROUTE broadcast */
#define	IFF_DRVRLOCK	0x4000		/* n/w driver does its own MP locking*/
#define IFF_PRIVATE     0x8000          /* MIPS ABI - do not advertise */

/* high flags */
#define IFF_LINK0	0x10000		/* interface private flag ; full/half */
#define	IFF_LINK1	0x20000		/* interface private flag */
#define	IFF_LINK2	0x40000		/* interface private flag */

#define IFF_LINKDOWN    0x80000         /* hardware link is down */

#define IFF_L2IPFRAG	0x100000	/* Link Layer does ip fragmentation */
#define IFF_L2TCPSEG	0x200000	/* Link Layer does tcp segmentation */
#define IFF_IPALIAS	0x400000	/* Support IP alias ioctl SIOCAIFADDR */
					/*  and SIOCDIFADDR */
#define IFF_HIGHBW	0x800000	/* hint for TCP to not do aggressive */
					/* acking */
#define IFF_DETACH	0x1000000	/* detached */

/* IPv6 flags */
#define	IFF_IPV4TUNNEL	0x2000000	/* if it is a IPv4 tunnel; special */
					/* selection of IPv6 source address */
#define IFF_IPV6NDRTR	0x4000000	/* enabled as an IPv6 ND router */
#define IFF_IPV6	0x8000000	/* network driver is IPv6 capable */
/*
 * The IFF_MULTICAST flag indicates that the network can support the
 * transmission and reception of higher-level (e.g., IP) multicast packets.
 * It is independent of hardware support for multicasting; for example,
 * point-to-point links or pure broadcast networks may well support
 * higher-level multicasts.
 *
 * The IFF_FILTMULTI flag indicates that the interface has imperfect
 * hardware multicast filtering. Additional filtering is required before
 * a multicast packet is accepted.
 *
 * The IFF_ALLCAST flag indicates that the interface supports
 * 802.5 source routing broadcast so that the broadcast msg can
 * cross bridges.
 */

/* flags set internally only: */
#define	IFF_CANTCHANGE	(IFF_LOOPBACK | IFF_BROADCAST | IFF_POINTOPOINT |   \
			    IFF_RUNNING | IFF_MULTICAST | IFF_FILTMULTI | \
			    IFF_DRVRLOCK | IFF_L2IPFRAG | IFF_L2TCPSEG )

/*
 * Output queues (ifp->if_snd) and internetwork datagram level 
 * input routines have queues of messages stored on ifqueue structures
 * (defined above).  Entries are added to and deleted from these structures
 * by these macros, which should be called with an appropriate lock.
 */

/* 
 * Multi reader lock for the ifnet list. Only if_detach, if_attach and 
 * SIOCSIFHEAD processing currently obtains this lock for update.
 * It is double trippable from the if_slowtimo interface watchdog thread.
 */
extern mrlock_t ifhead_lock;

#define IFHEAD_MRINITLOCK()	mrlock_init(&ifhead_lock, MRLOCK_DBLTRIPPABLE, \
				   "ifhead_lock", 0)
#define IFHEAD_MRLOCK()		mraccess(&ifhead_lock)
#define IFHEAD_MRUNLOCK()	mrunlock(&ifhead_lock)
#define IFHEAD_MRUPDATE()	mrupdate(&ifhead_lock)
/*
 * For the list of detached interfaces
 */
extern mutex_t ifdefunct_lock;

#define IFDEFUNCT_INITLOCK()	mutex_init(&ifdefunct_lock, MUTEX_DEFAULT, \
				   "ifdefunct_lock")
#define IFDEFUNCT_LOCK()	mutex_lock(&ifdefunct_lock, PZERO);
#define IFDEFUNCT_UNLOCK()	mutex_unlock(&ifdefunct_lock);
/*
 * This lock is obsoleted and does nothing. There shouldn't be any instances
 * where it is used but leaving it defined for now to be entirely deleted
 * at a later date. 
 */
extern mutex_t ifhead_mutex;

#define IFHEAD_INITLOCK()	mutex_init(&ifhead_mutex, MUTEX_DEFAULT, \
					"ifheadmutex")
/*
 * Any compilations using the old lock picks up the new one.
 */
#define IFHEAD_LOCK()		IFHEAD_MRLOCK()
#define IFHEAD_UNLOCK()		IFHEAD_MRUNLOCK()

#define IFNET_ISIPV6(ifp)	((ifp)->if_flags & IFF_IPV6)
#define IFNET_ISNOTIPV6(ifp)	(((ifp)->if_flags & IFF_IPV6) == 0)

#define IFNET_INITLOCKS(ifp) { \
		mutex_init(&(ifp)->if_mutex, MUTEX_DEFAULT, "if_mutex"); \
		IFQ_INITLOCK(&(ifp)->if_snd); \
}
#define IFNET_ISLOCKED(ifp)  (((ifp)->if_flags & IFF_DRVRLOCK)  \
				|| (mutex_mine(&(ifp)->if_mutex)))


#define IFNET_UPPERLOCK(ifp)	{ 	\
	if (!(ifp->if_flags & (IFF_LOOPBACK | IFF_DRVRLOCK)))		\
		IFNET_LOCK(ifp); 	\
}
#define IFNET_UPPERUNLOCK(ifp) {	\
	if (!(ifp->if_flags & (IFF_LOOPBACK | IFF_DRVRLOCK)))		\
		IFNET_UNLOCK(ifp);	\
}
#define IFNET_LOCK(ifp)	        mutex_lock(&(ifp)->if_mutex, PZERO)
#define IFNET_UNLOCK(ifp)	mutex_unlock(&(ifp)->if_mutex)


#define IFQ_LOCK(q, s)		(s) = mutex_spinlock(&(q)->ifq_lock)
#define IFQ_UNLOCK(q, s)	mutex_spinunlock(&(q)->ifq_lock, (s))

#define	IF_ENQUEUE_NOLOCK(ifq, m) { \
	(m)->m_act = 0; \
	if ((ifq)->ifq_tail == 0) \
		(ifq)->ifq_head = m; \
	else \
		(ifq)->ifq_tail->m_act = m; \
	(ifq)->ifq_tail = m; \
	(ifq)->ifq_len++; \
}
#define	IF_DEQUEUE_NOLOCK(ifq, m) { \
	(m) = (ifq)->ifq_head; \
	if (m) { \
		if (((ifq)->ifq_head = (m)->m_act) == 0) \
			(ifq)->ifq_tail = 0; \
		(m)->m_act = 0; \
		(ifq)->ifq_len--; \
	} \
}

#define IFQ_INITLOCK(ifq) spinlock_init(&(ifq)->ifq_lock, "ifq_lock") 

#define	IF_QFULL(ifq)		((ifq)->ifq_len >= (ifq)->ifq_maxlen)
#define	IF_DROP(ifq)		((ifq)->ifq_drops++)
#define	IF_ENQUEUE(ifq, m) { \
	register s3; \
	IFQ_LOCK(ifq, s3); \
	(m)->m_act = 0; \
	if ((ifq)->ifq_tail == 0) \
		(ifq)->ifq_head = m; \
	else \
		(ifq)->ifq_tail->m_act = m; \
	(ifq)->ifq_tail = m; \
	(ifq)->ifq_len++; \
	IFQ_UNLOCK(ifq, s3); \
}
#define	IF_PREPEND(ifq, m) { \
	register s3; \
	IFQ_LOCK(ifq, s3); \
	(m)->m_act = (ifq)->ifq_head; \
	if ((ifq)->ifq_tail == 0) \
		(ifq)->ifq_tail = (m); \
	(ifq)->ifq_head = (m); \
	(ifq)->ifq_len++; \
	IFQ_UNLOCK(ifq, s3); \
}
/*
 * Packets destined for level-1 protocol input routines have the following
 * structure prepended to the data.  IF_DEQUEUEHEADER extracts and returns
 * this structure's interface pointer, and skips over the space indicated
 * by it, when dequeueing the packet.  Otherwise M_SKIPIFHEADER should be
 * used to adjust for the ifheader.
 */
struct ifheader {
	struct ifnet	*ifh_ifp;	/* pointer to receiving interface */
	u_short		ifh_hdrlen;	/* byte size of this structure */
	u_short		ifh_af;		/* address family for input */
};

#define	M_ADJ(m, adj) { \
	(m)->m_off += (adj); \
	(m)->m_len -= (adj); \
	if ((m)->m_len == 0) \
		(m) = m_free(m); \
}
#define	M_SKIPIFHEADER(m) { \
	register int hdrlen; \
	hdrlen = mtod((m), struct ifheader *)->ifh_hdrlen; \
	M_ADJ(m, hdrlen); \
}
#define	IF_DEQUEUEHEADER(ifq, m, ifp) { \
	register s3; \
	IFQ_LOCK(ifq, s3); \
	(m) = (ifq)->ifq_head; \
	if (m) { \
		struct ifheader *ifh; \
		(ifq)->ifq_head = (m)->m_act; \
		if ((ifq)->ifq_head == 0) \
			(ifq)->ifq_tail = 0; \
		(m)->m_act = 0; \
		--(ifq)->ifq_len; \
		ifh = mtod((m), struct ifheader *); \
		(ifp) = ifh->ifh_ifp; \
		M_ADJ(m, ifh->ifh_hdrlen); \
	} \
	IFQ_UNLOCK(ifq, s3); \
}

/*
 * Initialize a receive buffer's ifqueue header to point at ifp and to
 * have a data offset hdrlen bytes beyond buf.
 */
#define	IF_INITHEADER(buf, ifp, hdrlen) { \
	struct ifheader *ifh; \
	ifh = (struct ifheader *)(buf); \
	ifh->ifh_ifp = (ifp); \
	ifh->ifh_hdrlen = (hdrlen); \
}
#define	M_INITIFHEADER(m, ifp, hdrlen) { \
	struct ifheader *ifh; \
	ifh = mtod(m, struct ifheader *); \
	ifh->ifh_ifp = (ifp); \
	(m)->m_len = ifh->ifh_hdrlen = (hdrlen); \
}

#define	IF_DEQUEUE(ifq, m) { \
	register s3; \
	IFQ_LOCK(ifq, s3); \
	(m) = (ifq)->ifq_head; \
	if (m) { \
		if (((ifq)->ifq_head = (m)->m_act) == 0) \
			(ifq)->ifq_tail = 0; \
		(m)->m_act = 0; \
		(ifq)->ifq_len--; \
	} \
	IFQ_UNLOCK(ifq, s3); \
}

#define	IFQ_MAXLEN	50
#define	IFNET_SLOWHZ	1		/* granularity is 1 second */

/*
 * The ifaddr structure contains information about one address
 * of an interface.  They are maintained by the different address families,
 * are allocated and attached when an address is set, and are stored in
 * a hash table. If all addresses for an interface need to be located
 * the hash table can be enumerated for entries matching the interface address
 */
struct ifaddr {
	struct	sockaddr *ifa_addr;	/* address of interface */
	struct	sockaddr *ifa_dstaddr;	/* other end of p-to-p link */
#define	ifa_broadaddr	ifa_dstaddr	/* broadcast address interface */
#ifdef _HAVE_SIN_LEN
	struct	sockaddr *ifa_netmask;	/* used to determine subnet */
#else
	struct	sockaddr_new *ifa_netmask;	/* used to determine subnet */
#endif
	struct	ifnet *ifa_ifp;		/* back-pointer to interface */
	struct	ifaddr *ifa_next;	/* next interface address in list */

	void	(*ifa_rtrequest)(int,struct rtentry *,struct sockaddr *);
					/* check for clean routes (+ or -)'d */

	u_short	ifa_flags;		/* mostly rt_flags for cloning */
	u_int	ifa_refcnt;		/* extra to malloc for link info */
	int	ifa_metric;		/* cost of going out this interface */

	/*
	 * since the ifaddr structure is embedded inside an in_ifaddr structure
	 * we store the starting address of the in_ifaddr for free operations
	 * since the starting address of the entire block is required.
	 * This save lots of weird computation when the code free's the ifaddr
	 * structure since it holds the ref count covering both structures.
	 * NOTE: It's a caddr_t to avoid header file circularity problems.
	 */
	caddr_t ifa_start_inifaddr;	/* address of in_ifaddr struct */
};

#define IA_ADDRFLAGS(ifa) 	\
	( (ifa)->ifa_addr->sa_family == AF_INET ?	\
	(((struct in_ifaddr *)(ifa)->ifa_start_inifaddr)->ia_addrflags) : \
	(((struct in6_ifaddr *)(ifa)->ifa_start_inifaddr)->ia_addrflags) )

/*
 * ia_addrflags
 */
#define IADDR_PRIMARY   0x1     /* Primary address entry for ifp */
#define IADDR_ALIAS     0x2     /* Alias address entry for ifp */

/*
 * 'struct ifaddr field ifa_flags values defined in route.h
 */
#define IFA_ROUTE	RTF_UP		/* route installed */

/* convert 'data' address given SIOCSIFADDR */
#define _IFADDR_SA(d) (((struct ifaddr*)(d))->ifa_addr)

struct ifstats {
	u_int	ifs_ipackets;		/* packets received on interface */
	u_int	ifs_opackets;		/* packets sent on interface */
	u_short	ifs_ierrors;		/* input errors on interface */
	u_short	ifs_oerrors;		/* output errors on interface */
	u_int	ifs_collisions;		/* collisions on csma interfaces */
};

/*
 * Message format for use in obtaining information about interfaces
 * from getkerninfo and the routing socket
 */
struct if_msghdr {
	u_short	ifm_msglen;	/* to skip over non-understood messages */
	u_char	ifm_version;	/* future binary compatability */
	u_char	ifm_type;	/* message type */
	int	ifm_addrs;	/* like rtm_addrs */
	__uint32_t ifm_flags;	/* value of if_flags */
	u_short	ifm_index;	/* index for associated ifp */
	struct	if_data ifm_data;/* statistics and other data about if */
};

/*
 * Message format for use in obtaining information about interface addresses
 * from getkerninfo and the routing socket
 */
struct ifa_msghdr {
	u_short	ifam_msglen;	/* to skip over non-understood messages */
	u_char	ifam_version;	/* future binary compatability */
	u_char	ifam_type;	/* message type */
	int	ifam_addrs;	/* like rtm_addrs */
	int	ifam_flags;	/* value of ifa_flags */
	u_short	ifam_index;	/* index for associated ifp */
	int	ifam_metric;	/* value of ifa_metric */
};

/*
 * Message format announcing the arrival or departure of a network interface.
 */
struct if_announcemsghdr {
	u_short	ifan_msglen;	/* to skip over non-understood messages */
	u_char	ifan_version;	/* future binary compatibility */
	u_char	ifan_type;	/* message type */
	u_short	ifan_index;	/* index for associated ifp */
	char	ifan_name[IFNAMSIZ]; /* if name, e.g. "en0" */
	u_short	ifan_what;	/* what type of announcement */
};

#define	IFAN_ARRIVAL	0	/* interface arrival */
#define	IFAN_DEPARTURE	1	/* interface departure */

/*
 * Interface request structure used for socket
 * ioctl's.  All interface ioctl's must have parameter
 * definitions which begin with ifr_name.  The
 * remainder may be interface specific.
 */
struct	ifreq {
	char	ifr_name[IFNAMSIZ];		/* if name, e.g. "en0" */
	union {
		struct	sockaddr ifru_addr;
		struct	sockaddr ifru_dstaddr;
		struct	sockaddr ifru_broadaddr;
		__uint32_t	ifru_flags;
		int	ifru_metric;
		int 	ifru_mtu;
		__uint32_t ifru_ndmtu;          /* set/get if_nd_linkmtu */
		char	ifru_data[1];		/* MIPS ABI - unused by BSD */
		char	ifru_enaddr[6];		/* MIPS ABI */
		char	ifru_oname[IFNAMSIZ];	/* MIPS ABI */
		struct	ifstats ifru_stats;
		u_short ifru_site6;
		u_short ifru_dadxmit;

		/* Trusted IRIX */
		struct {
			caddr_t	ifruv_base;
			int	ifruv_len;
		}	ifru_vec;
		u_int	ifru_perf;
	} ifr_ifru;
#define	ifr_addr	ifr_ifru.ifru_addr	/* address */
#define	ifr_dstaddr	ifr_ifru.ifru_dstaddr	/* other end of p-to-p link */
#define	ifr_broadaddr	ifr_ifru.ifru_broadaddr	/* broadcast address */
#define	ifr_flags	ifr_ifru.ifru_flags	/* flags */
#define	ifr_mtu		ifr_ifru.ifru_mtu	/* mtu size */
#define	ifr_ndmtu	ifr_ifru.ifru_ndmtu	/* if_nd_linkmtu size */
#define	ifr_metric	ifr_ifru.ifru_metric	/* metric */
#define	ifr_data	ifr_ifru.ifru_data	/* for use by interface */
#define ifr_enaddr      ifr_ifru.ifru_enaddr    /* ethernet address */
#define ifr_oname       ifr_ifru.ifru_oname     /* other if name */
#define	ifr_stats	ifr_ifru.ifru_stats	/* statistics */
#define	ifr_perf	ifr_ifru.ifru_perf	/* performance tuning */
#define	ifr_site6	ifr_ifru.ifru_site6	/* IPv6 site index */
#define	ifr_dadxmit	ifr_ifru.ifru_dadxmit	/* num DAD xmits */
/* Trusted IRIX */
#define ifr_base	ifr_ifru.ifru_vec.ifruv_base
#define ifr_len		ifr_ifru.ifru_vec.ifruv_len
};

/* structure used by SIOCGIFDATA */
struct ifdatareq {
	char   ifd_name[IFNAMSIZ];
	struct if_data ifd_ifd;
};

#define	if_getbaud(x) ((__uint64_t)x.ifs_value << (__uint64_t)x.ifs_log2)

struct ifaliasreq {
	char	ifra_name[IFNAMSIZ];		/* if name, e.g. "en0" */
	struct	sockaddr ifra_addr;
	struct	sockaddr ifra_broadaddr;
	struct	sockaddr ifra_mask;
#define ifra_dstaddr ifra_broadaddr
	int	cookie;			/* SIOCLIFADDR enumeration cookie */
};

/* Structure used for SIOCLISTLINK, SIOCADDLINK, SIOCDELLINK */
struct ifstripereq {
	char	ifsr_name[IFNAMSIZ];	/* if name, e.g. "sp0" */
	struct	sockaddr ifsr_local;	/* link local address */
	struct	sockaddr ifsr_remote;	/* link remote address */
	int	ifsr_cookie;		/* for SIOCGSTRIPECONF */
};


/*
 * Structure used in SIOCGIFCONF request.
 * Used to retrieve interface configuration for the ystem.
 * Useful for programs which must know all networks accessible.
 */
struct	ifconf {
	int	ifc_len;		/* size of associated buffer */
	union {
		caddr_t	ifcu_buf;
		struct	ifreq *ifcu_req;	/* ipv4 addresses */
		struct	in6_ifreq *ifcu_req6;	/* ipv6 addresses */
	} ifc_ifcu;
#define	ifc_buf	ifc_ifcu.ifcu_buf	/* buffer address */
#define	ifc_req	ifc_ifcu.ifcu_req	/* array of structures returned */
#define	ifc_req6 ifc_ifcu.ifcu_req6	/* ipv6 array of structures returned */
};

/* for IPv6 basic API */

#if _NO_XOPEN4
struct if_nameindex {
	unsigned int     if_index;      /* 1, 2, ... */
	char            *if_name;       /* null terminated name */
};
#endif /* _NO_XOPEN4 */

#ifndef _KERNEL
#include <sys/cdefs.h>
/*
 * The following symbols will NOT be visible if _XOPEN4 is defined
 * and _NO_XOPEN4 is not defined.
 */
#if _NO_XOPEN4
__BEGIN_DECLS
extern unsigned int    if_nametoindex __P((const char *));
extern char    *if_indextoname __P((unsigned int, char *));
extern struct if_nameindex     *if_nameindex __P((void));
extern void    if_freenameindex __P((struct if_nameindex *));
__END_DECLS

/* pragma optional directives for the above functions */
#if !defined(_SGI_COMPILING_LIBC)
#pragma optional if_nametoindex
#pragma optional if_indextoname
#pragma optional if_nameindex
#pragma optional if_freenameindex
#endif /* _SGI_COMPILING_LIBC */
#endif /* _NO_XOPEN4 */
#endif /* !_KERNEL */

#ifdef _KERNEL

#define	IFAFREE(ifa) { \
	ASSERT(ROUTE_ISLOCKED()); \
	if ((ifa)->ifa_refcnt <= 0) \
		ifafree(ifa); \
	else \
		(ifa)->ifa_refcnt--; \
}

extern struct	ifnet *ifnet;

extern char	*ether_sprintf(u_char *);

extern void	if_attach(struct ifnet *);
extern int 	if_detach(struct ifnet *);
extern void	if_down(struct ifnet *);
extern void	if_slowtimo(void);
extern int	ifconf(int, caddr_t);
extern void	ifinit(void);
extern int	ifioctl(struct socket *, int , caddr_t);
extern struct	ifnet *ifunit(char *);

extern struct	ifaddr *ifa_ifwithaddr(struct sockaddr *);
extern struct	ifaddr *ifa_ifwithaf(int);
extern struct	ifaddr *ifa_ifwithdstaddr(struct sockaddr *);
extern struct	ifaddr *ifa_ifwithnet(struct sockaddr *);
extern struct ifaddr *ifa_ifwithroute(int, struct sockaddr*,struct sockaddr *);
extern struct	ifaddr *ifaof_ifpforaddr(struct sockaddr *, struct ifnet *);
extern void	ifafree(struct ifaddr *);

extern int	loioctl(struct ifnet *, int, caddr_t);
extern void	loattach(void);

extern int      ifioctl(struct socket *, int , caddr_t);
extern int	if_dropall(struct ifqueue*);
extern __uint32_t in_cksum_sub(u_short *, int, __uint32_t);

extern int  	if_delayed_free(struct ifnet *, caddr_t, size_t);

#include <sys/hwgraph.h>
graph_error_t	if_hwgraph_add(vertex_hdl_t, char *, char *, char *, 
			       vertex_hdl_t *);
graph_error_t	if_hwgraph_alias_add(vertex_hdl_t, char *);
graph_error_t	if_hwgraph_alias_remove(char *);

#endif /* _KERNEL */
#ifdef __cplusplus
}
#endif
#endif	/* !__net_if__ */
