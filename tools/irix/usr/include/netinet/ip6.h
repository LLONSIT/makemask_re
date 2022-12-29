/*
 * Copyright (C) 1995, 1996, 1997, and 1998 WIDE Project.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE PROJECT AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE PROJECT OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * Copyright (c) 1982, 1986, 1993
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
 *	@(#)ip.h	8.1 (Berkeley) 6/10/93
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

#ifndef _NETINET_IP6_H_
#define _NETINET_IP6_H_

/*
 * Definitions for internet protocol version 6.
 * Per RFC 2460
 */

#if _NO_XOPEN4 && _NO_XOPEN5
/*
 * Structure of an IPv6 (first) header.
 */

struct ipv6 {
	u_int32_t ip6_head;		/* version, traffic class, flow label */
	u_int16_t ip6_len;		/* payload length */
	u_int8_t  ip6_nh;		/* next header */
	u_int8_t  ip6_hoplim;		/* hop limit */
	struct    in6_addr ip6_src;	/* source address */
	struct	  in6_addr ip6_dst;	/* destination address */
};

/*
 * Definitions of next header field values.
 */

#define IP6_NHDR_HOP	0	/* hop-by-hop IPv6 header */
#define IP6_NHDR_RT	43	/* routing IPv6 header */
#define IP6_NHDR_FRAG	44	/* fragment IPv6 header */
#define IP6_NHDR_AUTH	51	/* authentication IPv6 header */
#define IP6_NHDR_ESP	50	/* encryption IPv6 header */
#define IP6_NHDR_DOPT	60	/* destination options IPv6 header */
#define IP6_NHDR_NONH	59	/* no next header */

#ifdef _KERNEL
/*
 * Flag bit to be ored with above IP6_NHDR_* constants to indicate
 * that an extension header should appear _before_ s source-route
 * header, if present.
 */
#define IP6_NHF_PRERT	0x80000000

/*
 * The following definitions are for kernel use only and should
 * not be used by applications.  Another set of structure definitions
 * for extension headers, which conform to <draft-ietf-ipngwg-2292bis-00.txt>
 *  can be found further down in this file.
 */

struct ip6_genexthdr {
	u_int8_t	igen6_nh;
	u_int8_t	igen6_hlen;
};

/*
 * Fragment Header.
 */
struct ipv6_fraghdr {
	u_int8_t  if6_nh;	/* next header */
	u_int8_t  if6_res;	/* reserved */
	u_int16_t if6_off;	/* offset */
#define IP6_MF 0x1		/* more flag */
#define IP6_OFFMASK 0xfff8	/* mask of real offset field */
	u_int32_t if6_id;	/* identifier */
};

/*
 * Hop-by-Hop Options Header.
 */

struct ipv6_h2hhdr {
	u_int8_t  ih6_nh;	/* next header */
	u_int8_t  ih6_hlen;	/* header extension length */
	u_int16_t ih6_pad1;	/* to 4 byte length */
	u_int32_t ih6_pad2;	/* to 8 byte length */
};

#define IPV6_RTHDR_TYPE_0	0	/* type 0 routing header */

/*
 * Routing Header.
 */

struct ipv6_rthdr {
	u_int8_t  ir6_nh;	/* next header */
	u_int8_t  ir6_hlen;	/* header extension length, in 8 octet units, */
				/*   not including 1st 8 octets */
	u_int8_t  ir6_type;	/* routing type */
	u_int8_t  ir6_sglt;	/* index of next address */
	u_int32_t ir6_reserved;
};

/* 
 * Type 0 Routing header 
 */

struct ipv6_rthdr0 {
	u_int8_t  ir6_0_nh;	/* next header */
	u_int8_t  ir6_0_hlen;	/* header extension length, in 8 octet units, */
				/*   not including 1st 8 octets */
	u_int8_t  ir6_0_type;	/* routing type */
	u_int8_t  ir6_0_sglt;	/* index of next address */
	u_int32_t ir6_0_reserved;
	struct in6_addr  ip6r0_addr[1];   /* variable length addr list */
};

/*
 * Destination Options Header.
 */

struct ipv6_dopthdr {
	u_int8_t  io6_nh;	/* next header */
	u_int8_t  io6_hlen;	/* header extension length */
	u_int16_t io6_pad1;	/* to 4 byte length */
	u_int32_t io6_pad2;	/* to 8 byte length */
};

/*
 * Authentication Header.
 */

struct ipv6_authhdr {
	u_int8_t  ah6_nh;	/* next header */
	u_int8_t  ah6_hlen;	/* header extension length */
	u_int16_t ah6_pad;	/* to 4 byte length */
	u_int32_t ah6_spi;	/* security parameter index */
};

/*
 * Encryption Security Payload Header.
 */

struct ipv6_esphdr {
	u_int32_t esp6_spi;	/* security parameter index */
};

#endif /* _KERNEL */
/*
 * IPv6 implementation parameters.
 */

/*
 * This next section is specified by RFC 2292 section 2.1
 */

struct ip6_hdr {
    union {
	struct ip6_hdrctl {
	    u_int32_t	ip6_un1_flow;	/* 24 bits of flow-ID */
	    u_int16_t	ip6_un1_plen;	/* payload length */
	    u_int8_t	ip6_un1_nxt;	/* next header */
	    u_int8_t	ip6_un1_hlim;	/* hop limit */
	} ip6_un1;
	u_int8_t ip6_un2_vfc;		/* 4 bits version, 4 bits priority */
    } ip6_ctlun;
    struct in6_addr ip6_src;		/* source address */
    struct in6_addr ip6_dst;		/* destination address */
};

#define	ip6_vfc		ip6_ctlun.ip6_un2_vfc
#define ip6_flow	ip6_ctlun.ip6_un1.ip6_un1_flow
#define ip6_plen	ip6_ctlun.ip6_un1.ip6_un1_plen
#define ip6_nxt		ip6_ctlun.ip6_un1.ip6_un1_nxt
#define ip6_hlim	ip6_ctlun.ip6_un1.ip6_un1_hlim
#define ip6_hops	ip6_ctlun.ip6_un1.ip6_un1_hlim

/*
 * These structures are used by the user to pass options to the kernel that the
 * user would like to have appear in the packet.  They could possible be
 * merged with the structures further up in the file but they may not
 * necessarily always match the format that is in the packet in the future
 * so they are separate for now.
 */

/*
 * Extension Headers
 */

struct  ip6_ext {
        u_char  ip6e_nxt;
        u_char  ip6e_len;
};

/* Hop-by-Hop options header */
struct ip6_hbh {
	uint8_t	ip6h_nxt;	/* next header */
	uint8_t	ip6h_len;	/* length in units of 8 octets */
	/* followed by options */
};

/* Destination options header */
struct ip6_dest {
	uint8_t	ip6d_nxt;	/* next header */
	uint8_t	ip6d_len;	/* length in units of 8 octets */
	/* followed by options */
};

/* Option types and related macros */

/*
 * The high-order 3 bits of the option type define the behavior
 * when processing an unknown option and whether or not the option
 * content changes in flight.
 */

#define IP6OPT_PAD1             0x00    /* 00 0 00000 */
#define IP6OPT_PADN             0x01    /* 00 0 00001 */
#define IP6OPT_JUMBO            0xC2    /* 11 0 00010 = 194 */
#define IP6OPT_NSAP_ADDR        0xc3    /* 11 0 00011 */
#define IP6OPT_TUNNEL_LIMIT     0x04    /* 00 0 00100 */
#define IP6OPT_RTALERT          0x05    /* 00 0 00101 */
#define IP6OPT_ROUTER_ALERT     0x05    /* (2292bis def, recommended) */

#define IP6OPT_RTALERT_LEN      4
#define IP6OPT_MINLEN           2

/* Router alert values (in network byte order) */
#if _BYTE_ORDER == _BIG_ENDIAN
#define IP6_ALERT_MLD      0x0000
#define IP6_ALERT_RSVP     0x0001
#define  IP6_ALERT_AN      0x0002
#else /* _BYTE_ORDER == _LITTLE_ENDIAN */
#define IP6_ALERT_MLD      0x0000
#define IP6_ALERT_RSVP     0x0100
#define IP6_ALERT_AN       0x0200
#endif


#define IP6OPT_TYPE(o)          ((o) & 0xC0)
#define IP6OPT_TYPE_SKIP        0x00
#define IP6OPT_TYPE_DISCARD     0x40
#define IP6OPT_TYPE_FORCEICMP   0x80
#define IP6OPT_TYPE_ICMP        0xC0

#define IP6OPT_MUTABLE          0x20

/* IPv6 options: common part */
struct ip6_opt {
	uint8_t  ip6o_type;
	uint8_t  ip6o_len;
};

/* Jumbo Payload Option */
struct ip6_opt_jumbo {
	uint8_t  ip6oj_type;
	uint8_t  ip6oj_len;
	uint8_t  ip6oj_jumbo_len[4];
};
#define IP6OPT_JUMBO_LEN   6

/* NSAP Address Option */
struct ip6_opt_nsap {
	uint8_t  ip6on_type;
	uint8_t  ip6on_len;
	uint8_t  ip6on_src_nsap_len;
	uint8_t  ip6on_dst_nsap_len;
	/* followed by source NSAP */
	/* followed by destination NSAP */
};

/* Tunnel Limit Option */
struct ip6_opt_tunnel {
	uint8_t  ip6ot_type;
	uint8_t  ip6ot_len;
	uint8_t  ip6ot_encap_limit;
};

/* Router Alert Option */
struct ip6_opt_router {
	uint8_t  ip6or_type;
	uint8_t  ip6or_len;
	uint8_t  ip6or_value[2];
};

/* Home Address Option */
struct ip6_opt_home_address {
        u_int8_t ip6oh_type;
        u_int8_t ip6oh_len;
        u_int8_t ip6oh_addr[16];/* Home Address */
        /* followed by sub-options */
};

/* Routing header */
struct ip6_rthdr {
	uint8_t	ip6r_nxt;	/* next header */
	uint8_t	ip6r_len;	/* length in units of 8 octets */
	uint8_t	ip6r_type;	/* routing type */
	uint8_t	ip6r_segleft;	/* segments left */
	/* followed by routing type specific data */
};
#define IP6_RT_MAX	128	/* max num of addresses (8 bit hdr size) */

/* Type 0 Routing header */
struct ip6_rthdr0 {
	uint8_t	 ip6r0_nxt;	/* next header */
	uint8_t	 ip6r0_len;	/* length in units of 8 octets */
	uint8_t	 ip6r0_type;	/* always zero */
	uint8_t	 ip6r0_segleft;	/* segmentis left */
	uint32_t ip6r0_reserved;/* reserved field */
	 /* followed by up to 127 struct in6_addr */
};

/* Fragment header */
struct ip6_frag {
	uint8_t	ip6f_nxt;	/* next header */
	uint8_t	ip6f_reserved;	/* 8-bit reserved field */
	uint16_t ip6f_offlg;	/* offset, reserved, and flag */
	uint32_t ip6f_ident;	/* identification */
};

#if     BYTE_ORDER == BIG_ENDIAN
#define IP6F_OFF_MASK       0xfff8  /* mask out offset from _offlg */
#define IP6F_RESERVED_MASK  0x0006  /* reserved bits in ip6f_offlg */
#define IP6F_MORE_FRAG      0x0001  /* more-fragments flag */
#else   /* BYTE_ORDER == LITTLE_ENDIAN */
#define IP6F_OFF_MASK       0xf8ff  /* mask out offset from _offlg */
#define IP6F_RESERVED_MASK  0x0600  /* reserved bits in ip6f_offlg */
#define IP6F_MORE_FRAG      0x0100  /* more-fragments flag */
#endif

/* Mobility header */
struct ip6_mobility {
        u_int8_t ip6m_pproto;   /* following payload protocol (for PG) */
        u_int8_t ip6m_len;      /* length in units of 8 octets */
        u_int16_t ip6m_type;    /* message type */
        u_int16_t ip6m_cksum;   /* sum of IPv6 pseudo-header and MH */
        /* followed by type specific data */
};

/* Mobility Header min. */
#define IP6M_MINLEN     8

/*
 * Internet implementation parameters.
 */

#define IPV6_DEFHLIM    64      /* default hlim */
#define	IP6FRAGTTL	120	/* time to live for frags, slowhz */
#define IPV6_FRAGTTL    120     /* Kame compatability */

#define IP6_MMTU	1280	/* minimal MTU and reassembly */
#define IPV6_MAXPACKET  65535   /* ip6 max packet size without Jumbo payload*/

#endif /* _NO_XOPEN4 && _NO_XOPEN5 */
#endif /* _NETINET_IP6_H_ */
