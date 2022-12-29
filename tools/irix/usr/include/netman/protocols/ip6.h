#ifndef IP6_H
#define IP6_H
/*
 * Copyright 1990 Silicon Graphics, Inc.  All rights reserved.
 *
 * Internet Protocol utility routines and data.
 */
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>	/* prerequisite of <netinet/ip.h> */
#undef	IP_MSS			/* kill conditional define in tcp.h */
#include <netinet/ip6.h>
#include <netinet/ip6_var.h>
#include "protostack.h"

/*
 * Make the header double word aligned.
 */
#define IP6_ALIGN	sizeof(uint64_t)

/*
 * Get or put an IP header given a datastream.
 */
extern int ds_ip6(struct datastream *, struct ipv6 *);

struct ip6frame {
	ProtoStackFrame         ip6f_frame;     /* base class state */
	/* The next four are needed for upper layers to calculate the chksum */
	int			ip6f_len;	/* length of packet */
	struct in6_addr		ip6f_src;	/* source address */
	struct in6_addr		ip6f_dst;	/* destination address */
	int			ip6f_nh;	/* next header */
};

extern int ip6_checksum(struct ip6frame *, char *, int, int, u_short *);
extern int ip6_checksum_hdr(struct ip6frame *, char *, int, char *,
  int, int, u_short *);

#endif
