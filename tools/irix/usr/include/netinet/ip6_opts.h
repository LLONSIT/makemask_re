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

#ifndef _NETINET_IP6_OPTS_H_
#define _NETINET_IP6_OPTS_H_

#if _NO_XOPEN4 && _NO_XOPEN5
/*
 * Definition of IPv6 options and extensions for Neighbor Discovery
 */
#define OPT6_PAD_0		0	/* Single Pad */
#define OPT6_PAD_N		1	/* Multiple Pad */
#define OPT6_ROUTER_ALERT	5	/* Router Alert */
#define OPT6_JUMBO		194	/* Jumbo-Payload */

#define NDX6_LLADDR_SRC		1	/* Source Link-layer Address */
#define NDX6_LLADDR_TGT		2	/* Target Link-layer Address */
#define NDX6_PREF_INFO		3	/* Prefix-Information */
#define NDX6_RDRT_HDR		4	/* Redirected-Header */
#define NDX6_MTU		5	/* Maximum-Transmit-Unit */

/*
 * Macros on type bits.
 */
#define	OPT6_ACTION(t)		((t)&0xc0)  /* action */
#define OPT6_A_SKIP		0x00	    /* skip over */
#define OPT6_A_DISC		0x40	    /* discard silently */
#define OPT6_A_FERR		0x80	    /* discard and send error */
#define OPT6_A_OERR		0xc0	    /* discard & send err if unicast */
#define OPT6_RTCHANGE(t)	((t)&0x20)	/* change en-route */

/*
 * Options and Extensions layouts.
 */

struct opt6_any {			/* common header */
	u_int8_t	o6any_ext;	/* extension type */
	u_int8_t	o6any_len;	/* length */
};

struct opt6_jbo {			/* Jumbo-Payload */
	u_int16_t	jbo_pad;	/* for alignment */
	u_int8_t	jbo_ext;	/* extension type (194) */
	u_int8_t	jbo_len;	/* length (4) */
	u_int32_t	jbo_plen;	/* payload length */
};

struct opt6_ra {                        /* Router-Alert */
	u_int8_t        ra_ext;         /* extension type (TBD) */
	u_int8_t        ra_len;         /* length (2) */
	u_int16_t       ra_code;        /* code */
};
#define OPT6_RA_GROUP   0               /* ICMPv6 Group Membership */
#define OPT6_RA_RSVP    1               /* RSVP */

struct ndx6_any {			/* common header */
	u_int8_t	x6any_ext;	/* extension type */
	u_int8_t	x6any_len;	/* length */
	u_int16_t	x6any_res1;	/* reserved */
	u_int32_t	x6any_res2;	/* reserved */
};

struct ndx6_lladdr {			/* Link-layer Address */
	u_int8_t	lla_ext;	/* extension type (1 or 2) */
	u_int8_t	lla_len;	/* length (>=1) */
	u_int8_t	lla_addr[6];	/* media address */
};

struct ndx6_pref {			/* Prefix-Information */
	u_int8_t	pref_ext;	/* extension type (3) */
	u_int8_t	pref_len;	/* length (4) */
	u_int8_t	pref_plen;	/* prefix size (0..128) */
	u_int8_t	pref_flg;	/* flags */
	u_int32_t	pref_ilife;	/* invalidation lifetime */
	u_int32_t	pref_dlife;	/* deprecation lifetime */
	u_int32_t	pref_res2;
	struct in6_addr	pref_pref;	/* prefix */
};
#define	NDX6_PREF_FLG_L	0x80		/* On-link flag */
#define	NDX6_PREF_FLG_A	0x40		/* Address-configuration flag */

struct ndx6_mtu {			/* Maximum-Transmit-Unit */
	u_int8_t	mtu_ext;	/* extension type (5) */
	u_int8_t	mtu_len;	/* length (1) */
	u_int16_t	mtu_res;	/* reserved (0) */
	u_int32_t	mtu_mtu;	/* MTU value */
};

#endif /* _NO_XOPEN4 && _NO_XOPEN5 */
#endif
