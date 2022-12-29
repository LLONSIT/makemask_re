/*
 * Copyright (c) 1982, 1985, 1986, 1988, 1993, 1994
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

#ifndef __SYS_TPI_SOCKET_H__
#ifndef _SYS_SOCKET_H_
#define	_SYS_SOCKET_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>
#include <sys/types.h>
#if _SGIAPI
#include <sys/bsd_types.h>
#endif /* _SGIAPI */

/*
 * socklen_t type definition
 */
#ifndef _SOCKLEN_T
#define _SOCKLEN_T
#if _NO_XOPEN4 && _NO_XOPEN5
typedef int socklen_t;
#else
typedef u_int32_t socklen_t;
#endif /* _NO_XOPEN4 && _NO_XOPEN5 */
#endif /*_SOCKLEN_T */

/*
 * Definitions related to sockets: types, address families, options.
 */

/*
 * Types
 */

#if _SGIAPI
#ifndef NC_TPI_CLTS
#define NC_TPI_CLTS	1		/* must agree with netconfig.h */
#define NC_TPI_COTS	2		/* must agree with netconfig.h */
#define NC_TPI_COTS_ORD	3		/* must agree with netconfig.h */
#define	NC_TPI_RAW	4		/* must agree with netconfig.h */
#endif /* !NC_TPI_CLTS */
#endif /* _SGIAPI  */

#define _NC_TPI_CLTS		1
#define _NC_TPI_COTS		2
#define _NC_TPI_COTS_ORD	3
#define _NC_TPI_RAW		4

#define	SOCK_RAW	_NC_TPI_RAW	/* raw-protocol interface */
#define	SOCK_RDM	5		/* reliably-delivered message */
#define	SOCK_DGRAM	_NC_TPI_CLTS	/* datagram socket */
#define	SOCK_STREAM	_NC_TPI_COTS	/* stream socket */
#define	SOCK_SEQPACKET	6		/* sequenced packet stream */

/*
 * Option flags per-socket.
 */
#define	SO_DEBUG	0x0001		/* turn on debugging info recording */
#define	SO_ACCEPTCONN	0x0002		/* socket has had listen() */
#define	SO_REUSEADDR	0x0004		/* allow local address reuse */
#define	SO_KEEPALIVE	0x0008		/* keep connections alive */
#define	SO_DONTROUTE	0x0010		/* just use interface addresses */
#define	SO_BROADCAST	0x0020		/* permit sending of broadcast msgs */
#define	SO_USELOOPBACK	0x0040		/* bypass hardware when possible */
#define	SO_LINGER	0x0080		/* linger on close if data present */
#define	SO_OOBINLINE	0x0100		/* leave received OOB data in line */
#define	SO_REUSEPORT	0x0200		/* allow local address,port reuse */
#define SO_ORDREL	0x0200		/* MIPS ABI - unimplemented */
#define SO_IMASOCKET	0x0400		/* use libsocket (not TLI) semantics */
#define	SO_CHAMELEON	0x1000		/* (cipso) set label to 1st req rcvd */
#define SO_PASSIFNAME	0x2000		/* Pass the Ifname in front of data */
#define SO_XOPEN	0x4000		/* XOPEN socket behavior */

#define SHUT_RD			0	/* disable further receive oper's   */
#define SHUT_WR			1	/* disable further send oper's      */
#define SHUT_RDWR		2	/* disable further send/recv oper's */

/*
 * Additional options, not kept in so_options.
 */
#define SO_SNDBUF	0x1001		/* send buffer size */
#define SO_RCVBUF	0x1002		/* receive buffer size */
#define SO_SNDLOWAT	0x1003		/* send low-water mark */
#define SO_RCVLOWAT	0x1004		/* receive low-water mark */
#define SO_SNDTIMEO	0x1005		/* send timeout */
#define SO_RCVTIMEO	0x1006		/* receive timeout */
#define	SO_ERROR	0x1007		/* get error status and clear */
#define	SO_TYPE		0x1008		/* get socket type */
#define SO_PROTOTYPE	0x1009		/* get protocol type (libsocket) */
#define	SO_PROTOCOL	0x100a		/* get protocol (cpr) */
#define	SO_BACKLOG	0x100b		/* get backlog (cpr) */



/*
 * linux-specific, might as well be the same as on i386
 */
#define SO_NO_CHECK	11		/* turn off UDP checksum */

/*
 * Structure used for manipulating linger option.
 */
struct	linger {
	int	l_onoff;		/* option on/off */
	int	l_linger;		/* linger time */
};

/*
 * Level number for (get/set)sockopt() to apply to socket itself.
 */
#define	SOL_SOCKET	0xffff		/* options for socket level */

/*
 * Address families.
 */
#define	AF_UNSPEC	0		/* unspecified */
#define	AF_LOCAL	1		/* local to host (pipes, portals) */
#define	AF_UNIX		AF_LOCAL	/* backward compatibility */
#define	AF_INET		2		/* internetwork: UDP, TCP, etc. */
#define	AF_IMPLINK	3		/* arpanet imp addresses */
#define	AF_PUP		4		/* pup protocols: e.g. BSP */
#define	AF_CHAOS	5		/* mit CHAOS protocols */
#define	AF_NS		6		/* XEROX NS protocols */
#define	AF_ISO		7		/* ISO protocols */
#define	AF_ECMA		8		/* european computer manufacturers */
#define	AF_DATAKIT	9		/* datakit protocols */
#define	AF_CCITT	10		/* CCITT protocols, X.25 etc */
#define	AF_SNA		11		/* IBM SNA */
#define AF_DECnet	12		/* DECnet */
#define AF_DLI		13		/* DEC Direct data link interface */
#define AF_LAT		14		/* LAT */
#define	AF_HYLINK	15		/* NSC Hyperchannel */
#define	AF_APPLETALK	16		/* Apple Talk */
#define	AF_ROUTE	17		/* Internal Routing Protocol */
#ifdef __sgi
#define	AF_RAW		18		/* Raw link layer interface */
#else
#define	AF_LINK		18		/* Link layer interface */
#endif
#if _SGIAPI
#define	pseudo_AF_XTP	19		/* eXpress Transfer Protocol (no AF) */
#endif /* _SGIAPI */

/* MIPS ABI VALUES - unimplemented - notice these overlap real values */
#define AF_NIT		17		/* Network Interface Tap */
#define AF_802		18		/* IEEE 802.2, also ISO 8802 */
#define AF_OSI		19		/* umbrella for all families used */
#define AF_X25		20		/* CCITT X.25 in particular */
#define AF_OSINET	21		/* AFI = 47, IDI = 4 */
#define AF_GOSIP	22		/* U.S. Government OSI */

#define AF_SDL		23		/* SGI Data Link for DLPI */
#define AF_INET6	24		/* Internet Protocol version 6 */
#define	AF_LINK		25		/* Link layer interface */
#define	AF_ATMARP	26		/* (Cray) ATM signaling daemons */
#define	AF_STP		27		/* Scheduled Transfer protocol */

#define AF_MAX		(AF_STP+1)

/*
 * integral type mandated by X/Open to be both here and netinet/in.h
 */

#if !defined(_SA_FAMILY_T)
#define _SA_FAMILY_T
typedef unsigned short sa_family_t;
#endif

/*
 * Structure used by kernel to store most
 * addresses.
 * NOTE: For Raganarok compilers we MUST have a union for sockaddr which
 * specifies integer data, otherwise the compiler will only enforce
 * half-word alignment and modules using alternate defines (sockaddr_in)
 * will get Address Error exceptions on word accesses.
 */

struct sockaddr {
  union {
    struct {
#undef _HAVE_SA_LEN			/* marker for some places to change */
#ifdef _HAVE_SA_LEN			/* when we have sin_len */
	u_char	sa_len2;		/* total length */
	u_char	sa_family2;		/* address family */
#else
	sa_family_t sa_family2;		/* address family */
#endif
	char	sa_data2[14];		/* up to 14 bytes of direct address */
      } sa_generic;
    int sa_align;
  } sa_union;
};
#define sa_len		sa_union.sa_generic.sa_len2
#define sa_family	sa_union.sa_generic.sa_family2
#define	sa_data		sa_union.sa_generic.sa_data2

/*
 * Desired design of maximum size and alignment
 */
#define _SS_MAXSIZE	128  	/* Implementation specific max size */
#define _SS_ALIGNSIZE	(sizeof (int64_t))
				/* Implementation specific desired alignment */

/*
 * sockaddr_storage structure will be visible
 * only when _NO_XOPEN4 && _NO_XOPEN5 is defined.
 */

#if _NO_XOPEN4 && _NO_XOPEN5

/*
 * Definitions used for sockaddr_storage structure paddings design.
 */
#define _SS_PAD1SIZE	(_SS_ALIGNSIZE - sizeof (sa_family_t))
#define _SS_PAD2SIZE	(_SS_MAXSIZE - (sizeof (sa_family_t) + \
				_SS_PAD1SIZE + _SS_ALIGNSIZE))

struct sockaddr_storage {
    sa_family_t  ss_family;	/* address family */
    /* Following fields are implementation specific */
    char	_ss_pad1[_SS_PAD1SIZE];
		/* 6 byte pad, this is to make implementation */
		/* specific pad up to alignment field that */
		/* follows explicit in the data structure */
    int64_t	_ss_align;	/* field to force desired structure */
		/* storage alignment */
    char	_ss_pad2[_SS_PAD2SIZE];
		/* 112 byte pad to achieve desired size, */
		/* _SS_MAXSIZE value minus size of ss_family */
		/* _ss_pad1, _ss_align fields is 112 */
};

#endif /* _NO_XOPEN4 && _NO_XOPEN5 */


#if _SGIAPI
#ifndef _HAVE_SIN_LEN
struct sockaddr_new {
  union {
    struct {
	u_char	sa_len2;		/* total length */
	u_char	sa_family2;		/* address family */
	char	sa_data2[14];		/* up to 14 bytes of direct address */
      } sa_generic;
    int sa_align;
  } sa_union;
};

/*
 * XXX To avoid circular #include problems, define the values of
 * these socket size macros manually here, rather than using sizeof().
 */
#define _SIN_ADDR_SIZE		16		/* size of sockaddr_in data */
#define _SINDL_ADDR_SIZE	20		/* size of sockaddr_dl data */
#define _SIN6_ADDR_SIZE		32		/* size of sockaddr_in6 data */
#define _SIN_SA_DATA_SIZE	14		/* size of sa_data array */

#define _MAX_SA_LEN	24		/* largest sockaddr for now (_in6) */
/* Fake .sa_len for sources or destinations.
 */
#define _FAKE_SA_LEN_SRC(sa) (((struct sockaddr_new*)(sa))->sa_len      \
			      ? ((struct sockaddr_new*)(sa))->sa_len    \
			      : ((sa)->sa_family == AF_INET ? _SIN_ADDR_SIZE \
			       : ((sa)->sa_family == AF_INET6 ? _SIN6_ADDR_SIZE\
			       : ((sa)->sa_family == AF_LINK ? _SINDL_ADDR_SIZE\
				    : sizeof(struct sockaddr)))))
#define _FAKE_SA_LEN_DST(sa) (((struct sockaddr_new*)(sa))->sa_len      \
			      ? ((struct sockaddr_new*)(sa))->sa_len    \
			      : ((sa)->sa_family == AF_LINK ? _SINDL_ADDR_SIZE \
			       : ((sa)->sa_family == AF_INET6 ? _SIN6_ADDR_SIZE\
				 : sizeof(struct sockaddr))))

#define _FAKE_SA_FAMILY(sa) (((struct sockaddr_new*)(sa))->sa_family)
#endif  /* _HAVE_SIN_LEN  */

#if defined (_KERNEL) /* Trusted IRIX */
struct mac_label;

/*
 * CIPSO: structure passed in MT_SONAME mbuf from sbappendaddr() to recvit()
 */
struct sockaddrlbl {
	struct sockaddr  sal_addr;	/* datagram source address */
	struct mac_label *sal_lbl;	/* label of datagram */
	uid_t sal_uid;			/* uid of datagram */
};
#endif  /*  _KERNEL  */

struct recvluinfo {			/* argument to recvlumsg */
	struct mac_label *rlu_label;
	uid_t		 *rlu_uidp;
};

/*
 * Structure used by kernel to pass protocol
 * information in raw sockets.
 */
struct sockproto {
	u_short	sp_family;		/* address family */
	u_short	sp_protocol;		/* protocol */
};

/*
 * An option specification consists of an opthdr, followed by the value of
 * the option.  An options buffer contains one or more options.  The len
 * field of opthdr specifies the length of the option value in bytes.  This
 * length must be a multiple of sizeof(int) (use OPTLEN macro).
 */

struct opthdr {
	int	       level;  /* protocol level affected */
	int	       name;   /* option to modify */
	int	       len;    /* length of option value */
};

#define OPTLEN(x) ((((x) + sizeof(int) - 1) / sizeof(int)) * sizeof(int))
#define OPTVAL(opt) ((char *)(opt + 1))

/*
 * the optdefault structure is used for internal tables of option default
 * values.
 */
struct optdefault {
	int	optname;	/* the option */
	char	*val;		/* ptr to default value */
	int	len;		/* length of value */
};

struct tpisocket;
struct T_optmgmt_req;
struct msgb;

/*
 * the opproc structure is used to build tables of options processing
 * functions for dooptions().
 */
struct opproc {
	int	level;		/* options level this function handles */
	int	(*func)(struct tpisocket *, struct T_optmgmt_req *,
			struct opthdr *, struct msgb *);
				/* the function */
};

/*
 * This structure is used to encode pseudo system calls
 */
struct socksysreq {
	int		args[7];
};

/*
 * This structure is used for adding new protocols to the list supported by
 * sockets.
 */

struct socknewproto {
	int		family;	/* address family (AF_INET, etc.) */
	int		type;	/* protocol type (SOCK_STREAM, etc.) */
	int		proto;	/* per family proto number */
	dev_t		dev;	/* major/minor to use (must be a clone) */
	int		flags;	/* protosw flags */
};
#endif /*  _SGIAPI  */

/*
 * Protocol families, same as address families for now.
 */
#define	PF_UNSPEC	AF_UNSPEC
#define	PF_LOCAL	AF_LOCAL
#define	PF_UNIX		PF_LOCAL	/* backward compatibility */
#define	PF_INET		AF_INET
#define	PF_IMPLINK	AF_IMPLINK
#define	PF_PUP		AF_PUP
#define	PF_CHAOS	AF_CHAOS
#define	PF_NS		AF_NS
#define	PF_ISO		AF_ISO
#define	PF_OSI		AF_ISO
#define	PF_ECMA		AF_ECMA
#define	PF_DATAKIT	AF_DATAKIT
#define	PF_CCITT	AF_CCITT
#define	PF_SNA		AF_SNA
#define PF_DECnet	AF_DECnet
#define PF_DLI		AF_DLI
#define PF_LAT		AF_LAT
#define	PF_HYLINK	AF_HYLINK
#define	PF_APPLETALK	AF_APPLETALK
#define	PF_ROUTE	AF_ROUTE
#define	PF_LINK		AF_LINK
#define	PF_XTP		pseudo_AF_XTP	/* really just proto family, no AF */
#define	PF_RAW		AF_RAW
#define	PF_STP		AF_STP

/* MIPS ABI VALUES - unimplemented */
#define PF_NIT		AF_NIT		/* Network Interface Tap */
#define PF_802		AF_802		/* IEEE 802.2, also ISO 8802 */
#define PF_X25		AF_X25		/* CCITT X.25 in particular */
#define PF_OSINET	AF_OSINET	/* AFI = 47, IDI = 4 */
#define PF_GOSIP	AF_GOSIP	/* U.S. Government OSI */
#define	PF_INET6	AF_INET6

#define	PF_MAX		AF_MAX

#if _SGIAPI

/*
 * Definitions for network related sysctl, CTL_NET.
 *
 * Second level is protocol family.
 * Third level is protocol number.
 */

/*
 * PF_ROUTE - Routing table
 *
 * Three additional levels are defined:
 *	Fourth: address family, 0 is wildcard
 *	Fifth: type of info, defined below
 *	Sixth: flag(s) to mask with for NET_RT_FLAGS
 */
#define NET_RT_DUMP	1		/* dump; may limit to a.f. */
#define NET_RT_FLAGS	2		/* by flags, e.g. RESOLVING */
#define NET_RT_IFLIST	3		/* survey interface list */

/*
 * Fourth level sysctl() variables for IPPROTO_IP
 */
#define	IPCTL_FORWARDING	1	/* act as router */
#define	IPCTL_SENDREDIRECTS	2	/* may send redirects when forwarding */

/*
 * Fourth level sysctl() variables for PF_INET6
 */
#define	IP6CTL_FORWARDING	1	/* act as router */

/*
 * Fourth level sysctl() variables for IPPROTO_UDP
 */
#define	UDPCTL_CHECKSUM		1	/* checksum UDP packets */

#endif /*  _SGIAPI  */

/*
 * Maximum queue length specifiable by listen.
 * Applications can always reduce this in the listen call.
 */
#define	SOMAXCONN	1000

#if !defined (_IOVEC_T)
#define _IOVEC_T
typedef struct iovec {
	void *iov_base;
	size_t  iov_len;
} iovec_t;
#endif  /* _IOVEC_T */

/*
 * Message header for recvmsg and sendmsg calls.
 * Used value-result for recvmsg, value only for sendmsg.
 */
#if _SGIAPI
struct msghdr {
	caddr_t	msg_name;		/* optional address */
	int	msg_namelen;		/* size of address */
	struct	iovec *msg_iov;		/* scatter/gather array */
	int	msg_iovlen;		/* # elements in msg_iov */
	caddr_t	msg_accrights;		/* access rights sent/received */
	int	msg_accrightslen;
};

/* XXX This will become msghdr in the next release */
struct nmsghdr {
	caddr_t	msg_name;		/* optional address */
	int	msg_namelen;		/* size of address */
	struct	iovec *msg_iov;		/* scatter/gather array */
	int	msg_iovlen;		/* # elements in msg_iov */
	caddr_t	msg_control;		/* ancillary data, see below */
	int	msg_controllen;		/* ancillary data buffer len */
	int	msg_flags;		/* flags on received message */
};

/*
 * XPG4 message header
 */
struct xpg4_msghdr {
	void	*msg_name;		/* optional address */
	size_t	msg_namelen;		/* size of address */
	struct  iovec *msg_iov;		/* scatter/gather array */
	int     msg_iovlen;		/* # elements in msg_iov */
	void	*msg_ctrl;		/* ancillary data */
	size_t	msg_ctrllen;		/* ancillary data buffer len */
	int	msg_flags;		/* flags on rec'd message */
};
#if (_MIPS_SIM != _ABIO32)
/*
 * XPG5 message header
 */
struct xpg5_msghdr {
	void    *msg_name;              /* optional address */
	socklen_t msg_namelen;          /* size of address */
	struct  iovec *msg_iov;         /* scatter/gather array */
	int     msg_iovlen;             /* # elements in msg_iov */
	void    *msg_ctrl;              /* ancillary data */
	socklen_t msg_ctrllen;          /* ancillary data buffer len */
	int     msg_flags;              /* flags on rec'd message */
};
#endif /* (_MIPS_SIM != _ABIO32) */

/* This goes away in the next release XXX */
#define	msg_control	msg_accrights
#define	msg_controllen	msg_accrightslen

#elif _XOPEN5
#if (_MIPS_SIM != _ABIO32)
struct msghdr {
	void    *msg_name;              /* optional address */
	socklen_t msg_namelen;          /* size of address */
	struct  iovec *msg_iov;         /* scatter/gather array */
	int     msg_iovlen;             /* # elements in msg_iov */
	void    *msg_control;           /* ancillary data */
	socklen_t msg_controllen;       /* ancillary data buffer len */
	int     msg_flags;              /* flags on rec'd message */
};
#else
struct msghdr {
	caddr_t	msg_name;		/* optional address */
	int	msg_namelen;		/* size of address */
	struct	iovec *msg_iov;		/* scatter/gather array */
	int	msg_iovlen;		/* # elements in msg_iov */
	caddr_t	msg_accrights;		/* access rights sent/received */
	int	msg_accrightslen;
};
#endif /* (_MIPS_SIM != _ABIO32) */

#else /* XPG 4 case */
struct msghdr {
	void	*msg_name;		/* optional address */
	size_t	msg_namelen;		/* size of address */
	struct  iovec *msg_iov;		/* scatter/gather array */
	int     msg_iovlen;		/* # elements in msg_iov */
	void	*msg_control;		/* ancillary data */
	size_t	msg_controllen;		/* ancillary data buffer len */
	int	msg_flags;		/* flags on rec'd message */
};
#endif  /* _SGIAPI  */

#if defined(_KERNEL)
/*
 * socket interface version specifiers: xpg4 or BSD 4.3
 */
#define XPG4_SOCKETS    1
#define BSD43_SOCKETS   2
#define XPG5_SOCKETS    3

#endif /* _KERNEL */

#define	MSG_OOB		0x1		/* process out-of-band data */
#define	MSG_PEEK	0x2		/* peek at incoming message */
#define	MSG_DONTROUTE	0x4		/* send without using routing tables */
#define	MSG_EOR		0x8		/* data completes record */
#define	MSG_TRUNC	0x10		/* data discarded before delivery */
#define	MSG_CTRUNC	0x20		/* control data lost before delivery */
#define	MSG_WAITALL	0x40		/* wait for full request or error */
#define	MSG_DONTWAIT	0x80		/* this message should be nonblocking */
#define MSG_DONT_BRKPG 0x100            /* don't break up pages for send */
#define MSG_TRIX 	0x200            /* TRIX single-level, don't detect recv buf after it has been check by sesmgr_soreceive */
#ifdef XTP
#define	MSG_BTAG	0x40		/* XTP packet with BTAG field */
#define	MSG_ETAG	0x80		/* XTP packet with ETAG field */
#endif

#if _SGIAPI
/* IRIX-specific MSG_ flags */

#define	_MSG_NOINTR	0x80000000	/* ignore interrupts when blocking */
/* Following is to be used only with AF_UNIX domain */

#define MSG_CONTROL	0x40000000	/* access rights has cmsghdr + data */
#endif

#define	MSG_MAXIOVLEN	16

/*
 * Header for ancillary data objects in msg_control buffer.
 * Used for additional information with/about a datagram
 * not expressible by flags.  The format is a sequence
 * of message elements headed by cmsghdr structures.
 */
struct cmsghdr {
	size_t		cmsg_len;	/* data byte count, including hdr */
	int		cmsg_level;	/* originating protocol */
	int		cmsg_type;	/* protocol-specific type */
	/* followed by	u_char  cmsg_data[]; */
};

#define	_ALIGNBYTES	7
#define	_ALIGN(p)	(((uint_t)(p) + _ALIGNBYTES) & ~_ALIGNBYTES)


/* given pointer to struct cmsghdr, return pointer to data */
#define       CMSG_DATA(cmsg)         ((uchar_t *)((cmsg) + 1))
 
/* given pointer to struct cmsghdr, return pointer to next cmsghdr */
#define       CMSG_NXTHDR(mhdr, cmsg) \
      (((caddr_t)(cmsg) + (cmsg)->cmsg_len + sizeof(struct cmsghdr) > \
          (caddr_t)(mhdr)->msg_control + (mhdr)->msg_controllen) ? \
          (struct cmsghdr *)0L : \
          (struct cmsghdr *)((caddr_t)(cmsg) + _ALIGN((cmsg)->cmsg_len)))

#define       CMSG_FIRSTHDR(mhdr)     ((struct cmsghdr *)(mhdr)->msg_control)

#define CMSG_SPACE(length)	_ALIGN(sizeof(struct cmsghdr) + (length))

#define CMSG_LEN(length)	(sizeof(struct cmsghdr) + length)	

#ifdef _KERNEL
/* Not part of the API */
#define CMSG_DATALEN(cp) ((cp)->cmsg_len - (sizeof(struct cmsghdr)))
#endif


#ifdef _HAVE_SA_LEN
#define _SA_LEN(x) (x)->sa_len
#else
#if _SGIAPI
#define _SA_LEN(x) _FAKE_SA_LEN_SRC(x)
#else
#define _SA_LEN(sa) ((sa)->sa_family == AF_INET ? _SIN_ADDR_SIZE \
	       : ((sa)->sa_family == AF_INET6 ? _SIN6_ADDR_SIZE\
	       : ((sa)->sa_family == AF_LINK ? _SINDL_ADDR_SIZE\
		    : sizeof(struct sockaddr))))
#endif
#endif

#if defined(_KERNEL) || defined(_XOPEN_SOURCE)
/* "Socket"-level control message types: */
#define	SCM_RIGHTS	0x01		/* access rights (array of int) */
#endif /* (_KERNEL || _XOPEN_SOURCE) */

#if !defined(_KERNEL)
extern int listen(int, int);
extern int shutdown(int, int);
extern int socketpair(int, int, int, int *);
#if _NO_XOPEN4 && _NO_XOPEN5
/* Std BSD4.3/SGI */
extern int recvmsg(int, struct msghdr *, int);
extern int sendmsg(int, const struct msghdr *, int);
extern int accept(int, void *, socklen_t *);
extern int bind(int, const void *, socklen_t);
extern int connect(int, const void *, socklen_t);
extern int getpeername(int, void *, socklen_t *);
extern int getsockname(int, void *, socklen_t *);
extern int getsockopt(int, int, int, void *, socklen_t *);
extern int recv(int, void *, int, int);
extern int recvfrom(int, void *, int, int, void *, socklen_t *);
extern int send(int, const void *, int, int);
extern int sendto(int, const void *, int, int, const void *, socklen_t);
extern int setsockopt(int, int, int, const void *, socklen_t);
extern int socket(int, int, int);
#else
#if _ABIAPI
/* BB3.0 is XPG compliant but can't use hidden names */
extern ssize_t recvmsg(int, struct msghdr *, int);
extern ssize_t sendmsg(int, const struct msghdr *, int);
extern int accept(int, struct sockaddr *, size_t *);
extern int bind(int, const struct sockaddr *, size_t);
extern int connect(int, const struct sockaddr *, size_t);
extern int getpeername(int, struct sockaddr *, size_t *);
extern int getsockname(int, struct sockaddr *, size_t *);
extern int getsockopt(int, int, int, void *, size_t *);
extern ssize_t recv(int, void *, size_t, int);
extern ssize_t recvfrom(int, void *, size_t, int, struct sockaddr *,
	size_t*);
extern ssize_t send(int, const void *, size_t, int);
extern ssize_t sendto(int, const void *, size_t, int,
	const struct sockaddr *, size_t);
extern int setsockopt(int, int, int, const void *, size_t );
extern int socket(int, int, int);
/* xpg5 functions */
#elif _XOPEN5 
#if (_MIPS_SIM != _ABIO32) 
extern ssize_t _xpg5_recvmsg(int, struct msghdr *, int);
extern ssize_t _xpg5_sendmsg(int, const struct msghdr *, int);
extern int _xpg5_accept(int, struct sockaddr *, socklen_t *);
extern int _xpg5_bind(int, const struct sockaddr *, socklen_t);
extern int _xpg5_connect(int, const struct sockaddr *, socklen_t);
extern int _xpg5_getpeername(int, struct sockaddr *, socklen_t *);
extern int _xpg5_getsockname(int, struct sockaddr *, socklen_t *);
extern int _xpg5_getsockopt(int, int, int, void *, socklen_t *);
extern ssize_t _xpg5_recv(int, void *, size_t, int);
extern ssize_t _xpg5_recvfrom(int, void *, size_t, int, struct sockaddr *,
	socklen_t *);
extern ssize_t _xpg5_send(int, const void *, size_t, int);
extern ssize_t _xpg5_sendto(int, const void *, size_t, int,
	const struct sockaddr *, socklen_t);
extern int _xpg5_setsockopt(int, int, int, const void *, socklen_t);
extern int _xpg5_socket(int, int, int);

#if !defined(_SGI_COMPILING_LIBC)
#pragma optional _xpg5_recvmsg
#pragma optional _xpg5_sendmsg
#pragma optional _xpg5_accept
#pragma optional _xpg5_bind
#pragma optional _xpg5_connect
#pragma optional _xpg5_getpeername
#pragma optional _xpg5_getsockname
#pragma optional _xpg5_getsockopt
#pragma optional _xpg5_recv
#pragma optional _xpg5_recvfrom
#pragma optional _xpg5_send
#pragma optional _xpg5_sendto
#pragma optional _xpg5_setsockopt
#pragma optional _xpg5_socket
#endif /* !defined(_SGI_COMPILING_LIBC) */

/*
 * If you need to define your own functions for accept, bind, etc, use
 * the appropriate -D_XPG5_***_USER_DEFINED option at compile time.  And the
 * user defined function for any of these functions must be defined with the 
 * correct prototype given below for each of these functions.
 */

#ifdef _XPG5_ACCEPT_USER_DEFINED
extern int accept(int, struct sockaddr *, socklen_t *);

/*
 * The following comment is applicable to every static inline functions given 
 * below. 
 * 
 * Since the static function is defined in each source file that includes
 * this header file, these static functions will have different addresses
 * in cases where inline expansion is not performed.  This may cause problems
 * if the address of the function is examined in programs.
 */
#else
/*REFERENCED*/ static __inline int
accept(int _s, struct sockaddr *_sap, socklen_t *_lenp)
{
	return(_xpg5_accept(_s, _sap, _lenp));
}
#endif /* _XPG5_ACCEPT_USER_DEFINED */

#ifdef _XPG5_RECVMSG_USER_DEFINED
extern ssize_t recvmsg(int, struct msghdr *, int);
#else
/*REFERENCED*/ static __inline ssize_t
recvmsg(int _s, struct msghdr *_msg, int _flags)
{
	return(_xpg5_recvmsg(_s, _msg, _flags));
}
#endif /* _XPG5_RECVMSG_USER_DEFINED */

#ifdef _XPG5_RECV_USER_DEFINED
extern ssize_t recv(int, size_t, int);
#else
/*REFERENCED*/ static __inline ssize_t
recv(int _s, void *_buf, size_t _len, int _flags)
{
	return(_xpg5_recv(_s, _buf, _len, _flags));
}
#endif /* _XPG5_RECV_USER_DEFINED */

#ifdef _XPG5_RECVFROM_USER_DEFINED
extern ssize_t recvfrom(int, void *, size_t, int, struct sockaddr *,
					socklen_t *);
#else
/*REFERENCED*/ static __inline ssize_t
recvfrom(int _s, void *_buf, size_t _len, int _flags, struct sockaddr *_addr,
	socklen_t *_addrlen)
{
	return(_xpg5_recvfrom(_s, _buf, _len, _flags, _addr, _addrlen));
}
#endif /* _XPG5_RECVFROM_USER_DEFINED */

#ifdef _XPG5_SENDMSG_USER_DEFINED
extern ssize_t sendmsg(int, const struct msghdr *, int);
#else
/*REFERENCED*/ static __inline ssize_t
sendmsg(int _s, const struct msghdr *_msg, int _flags)
{
	return(_xpg5_sendmsg(_s, _msg, _flags));
}
#endif /* _XPG5_SENDMSG_USER_DEFINED */

#ifdef _XPG5_SEND_USER_DEFINED
extern ssize_t send(int, const void *, size_t, int);
#else
/*REFERENCED*/ static __inline ssize_t
send(int _s, const void *_buf, size_t _len, int _flags)
{
	return(_xpg5_send(_s, _buf, _len, _flags));
}
#endif /* _XPG5_SEND_USER_DEFINED */

#ifdef _XPG5_SENDTO_USER_DEFINED
extern ssize_t sendto(int, const void *, size_t, int,
			const struct sockaddr *, socklen_t);
#else
/*REFERENCED*/ static __inline ssize_t
sendto(int _s, const void *_buf, size_t _len, int _flags,
	const struct sockaddr *_addr, socklen_t _addrlen)
{
	return(_xpg5_sendto(_s, _buf, _len, _flags, _addr, _addrlen));
}
#endif /* _XPG5_SENDTO_USER_DEFINED */

#ifdef _XPG5_BIND_USER_DEFINED
extern int bind(int, const struct sockaddr *, socklen_t);
#else
/*REFERENCED*/ static __inline int
bind(int _s, const struct sockaddr *_name, socklen_t _namelen)
{
	return(_xpg5_bind(_s, _name, _namelen));
}
#endif /* _XPG5_BIND_USER_DEFINED */

#ifdef _XPG5_CONNECT_USER_DEFINED
extern int connect(int, const struct sockaddr *, socklen_t);
#else
/*REFERENCED*/ static __inline int
connect(int _s, const struct sockaddr *_name, socklen_t _namelen)
{
	return(_xpg5_connect(_s, _name, _namelen));
}
#endif /* _XPG5_CONNECT_USER_DEFINED */

#ifdef _XPG5_GETPEERNAME_USER_DEFINED
extern int getpeername(int, struct sockaddr *, socklen_t *);
#else
/*REFERENCED*/ static __inline int
getpeername(int _s, struct sockaddr *_addr, socklen_t *_len)
{
	return(_xpg5_getpeername(_s, _addr, _len));
}
#endif /* _XPG5_GETPEERNAME_USER_DEFINED */

#ifdef _XPG5_GETSOCKNAME_USER_DEFINED
extern int getsockname(int, struct sockaddr *, socklen_t *);
#else
/*REFERENCED*/ static __inline int
getsockname(int _s, struct sockaddr *_addr, socklen_t *_len)
{
	return(_xpg5_getsockname(_s, _addr, _len));
}
#endif /* _XPG5_GETSOCKNAME_USER_DEFINED */

#ifdef _XPG5_GETSOCKOPT_USER_DEFINED
extern int getsockopt(int, int, int, void *, socklen_t *);
#else
/*REFERENCED*/ static __inline int
getsockopt(int _s, int _level, int _optname, void *_optval, socklen_t *_optlen)
{
	return(_xpg5_getsockopt(_s, _level, _optname, _optval, _optlen));
}
#endif /* _XPG5_GETSOCKOPT_USER_DEFINED */

#ifdef _XPG5_SETSOCKOPT_USER_DEFINED
extern int setsockopt(int, int, int, const void *, socklen_t);
#else
/*REFERENCED*/ static __inline int
setsockopt(int _s, int _level, int _name, const void *_optval,
                socklen_t _optlen)
{
	return(_xpg5_setsockopt(_s, _level, _name, _optval, _optlen));
}
#endif /* _XPG5_SETSOCKOPT_USER_DEFINED */

#ifdef _XPG5_SOCKET_USER_DEFINED
extern int socket(int, int, int);
#else
/*REFERENCED*/ static __inline int
socket(int _domain, int _type, int _protocol) {
	return(_xpg5_socket(_domain, _type, _protocol));
}
#endif /* _XPG5_SOCKET_USER_DEFINED */

#else
extern int recvmsg(int, struct msghdr *, int);
extern int sendmsg(int, const struct msghdr *, int);
extern int accept(int, void *, int *);
extern int bind(int, const void *, int);
extern int connect(int, const void *, int);
extern int getpeername(int, void *, int *);
extern int getsockname(int, void *, int *);
extern int getsockopt(int, int, int, void *, int *);
extern int recv(int, void *, int, int);
extern int recvfrom(int, void *, int, int, void *, int *);
extern int send(int, const void *, int, int);
extern int sendto(int, const void *, int, int, const void *, int);
extern int setsockopt(int, int, int, const void *, int);
extern int socket(int, int, int);
#endif /* (_MIPS_SIM != _ABIO32) */
#else
/* this is XPG4 */
extern ssize_t __xpg4_recvmsg(int, struct msghdr *, int);
extern ssize_t __xpg4_sendmsg(int, const struct msghdr *, int);
extern int __xpg4_accept(int, struct sockaddr *, size_t *);
extern int __xpg4_bind(int, const struct sockaddr *, size_t);
extern int __xpg4_connect(int, const struct sockaddr *, size_t);
extern int __xpg4_getpeername(int, struct sockaddr *, size_t *);
extern int __xpg4_getsockname(int, struct sockaddr *, size_t *);
extern int __xpg4_getsockopt(int, int, int, void *, size_t *);
extern ssize_t __xpg4_recv(int, void *, size_t, int);
extern ssize_t __xpg4_recvfrom(int, void *, size_t, int, struct sockaddr *,
	size_t*);
extern ssize_t __xpg4_send(int, const void *, size_t, int);
extern ssize_t __xpg4_sendto(int, const void *, size_t, int,
	const struct sockaddr *, size_t);
extern int __xpg4_setsockopt(int, int, int, const void *, size_t );
extern int __xpg4_socket(int, int, int);

/*REFERENCED*/ static ssize_t
recvmsg(int _s, struct msghdr *_msg, int _flags)
{
	return(__xpg4_recvmsg(_s, _msg, _flags));
}

/*REFERENCED*/ static ssize_t
sendmsg(int _s, const struct msghdr *_msg, int _flags)
{
	return(__xpg4_sendmsg(_s, _msg, _flags));
}

/*REFERENCED*/ static int
accept(int _s, struct sockaddr *_sap, size_t *_lenp)
{
	return(__xpg4_accept(_s, _sap, _lenp));
}

/*REFERENCED*/ static int
bind(int _s, const struct sockaddr *_name, size_t _namelen)
{
	return(__xpg4_bind(_s, _name, _namelen));
}

/*REFERENCED*/ static int
connect(int _s, const struct sockaddr *_name, size_t _namelen)
{
	return(__xpg4_connect(_s, _name, _namelen));
}

/*REFERENCED*/ static ssize_t
recv(int _s, void *_buf, size_t _len, int _flags)
{
	return(__xpg4_recv(_s, _buf, _len, _flags));
}

/*REFERENCED*/ static int
recvfrom(int _s, void *_buf, size_t _len, int _flags, struct sockaddr *_addr,
	size_t *_addrlen)
{
	return(__xpg4_recvfrom(_s, _buf, _len, _flags, _addr, _addrlen));
}

/*REFERENCED*/ static int
getpeername(int _s, struct sockaddr *_addr, size_t *_len)
{
	return(__xpg4_getpeername(_s, _addr, _len));
}

/*REFERENCED*/ static int
getsockname(int _s, struct sockaddr *_addr, size_t *_len)
{
	return(__xpg4_getsockname(_s, _addr, _len));
}

/*REFERENCED*/ static int
getsockopt(int _s, int _level, int _optname, void *_optval, size_t *_optlen)
{
	return(__xpg4_getsockopt(_s, _level, _optname, _optval, _optlen));
}

/*REFERENCED*/ static ssize_t
send(int _s, const void *_buf, size_t _len, int _flags)
{
	return(__xpg4_send(_s, _buf, _len, _flags));
}

/*REFERENCED*/ static ssize_t
sendto(int _s, const void *_buf, size_t _len, int _flags,
	const struct sockaddr *_addr, size_t _addrlen)
{
	return(__xpg4_sendto(_s, _buf, _len, _flags, _addr, _addrlen));
}

/*REFERENCED*/ static int
setsockopt(int _s, int _level, int _name, const void *_optval, size_t _optlen)
{
	return(__xpg4_setsockopt(_s, _level, _name, _optval, _optlen));
}

/*REFERENCED*/ static int
socket(int _domain, int _type, int _protocol)
{
	return(__xpg4_socket(_domain, _type, _protocol));
}

#endif /* _ABIAPI */
#endif /* _NO_XOPEN4 && _NO_XOPEN5 */
#endif  /* _KERNEL  */

#ifdef __cplusplus
}
#endif
#endif /* !__SYS_SOCKET_H__ */
#endif /* !__SYS_TPI_SOCKET_H__ */
