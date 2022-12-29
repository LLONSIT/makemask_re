/*
 * |-----------------------------------------------------------|
 * | Copyright (c) 1991, 1990 MIPS Computer Systems, Inc.      |
 * | All Rights Reserved                                       |
 * |-----------------------------------------------------------|
 * |          Restricted Rights Legend                         |
 * | Use, duplication, or disclosure by the Government is      |
 * | subject to restrictions as set forth in                   |
 * | subparagraph (c)(1)(ii) of the Rights in Technical        |
 * | Data and Computer Software Clause of DFARS 252.227-7013.  |
 * |         MIPS Computer Systems, Inc.                       |
 * |         950 DeGuigne Avenue                               |
 * |         Sunnyvale, California 94088-3650, USA             |
 * |-----------------------------------------------------------|
 */

#ifndef _SYS_XTI_INET_H
#define _SYS_XTI_INET_H

#include <sys/xti.h>

/*
 *  TCP level
 *
 *  The values defined for the TCP Level are recommended-only,
 *  not mandatory.
 */

#define T_INET_TCP 0x6

/*
 *  TCP-level Options
 *
 */


#define T_TCP_NODELAY   0x1 /* don't delay packets to coalesce */
#define T_TCP_MAXSEG    0x2 /* get maximum segment size        */
#define T_TCP_KEEPALIVE 0x8 /* check, if connections are alive */

/*
 *  UDP level
 *
 */
#define T_INET_UDP      0x11

/*
 *  UDP-level Options
 *
 *  Note: UDP_CHECKSUM is supposed to be defined as TCO_CHECKSUM,
 *        which is defeined to be 0x0600 in <sys/xti.h>. However,
 *        TCO_CHECKSUM is not an allowed define as to VST xti_inet header
 *        test's concern, so we have to explicitly defined it to 0x0600.
 *        If we ever change define of TCO_CHECKSUM in <sys/xti.h>, we should
 *        change the value here as well.
 */

#define T_UDP_CHECKSUM  0x0600  /* checksum computation */

/*
 *  IP level
 *
 */
#define T_INET_IP      0x0

/*
 *  IP-level Options
 *
 */

#define T_IP_OPTIONS   1	/* IP per-packet options            */
#define T_IP_TOS       3	/* IP per-packet type of service    */
#define T_IP_TTL       4	/* IP per-packet time to live       */
#define T_IP_REUSEADDR 29	/* allow local address reuse        */
#define T_IP_DONTROUTE 30	/* just use interface addresses     */
#define T_IP_BROADCAST 31	/* permit sending of broadcast msgs */
#define T_LOCOST (1 << 1)

#endif /* _SYS_XTI_INET_H */
