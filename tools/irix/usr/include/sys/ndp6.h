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
/* This file contains constants defined in 
 * IPv6 ND draft XXX.
 */

#define ND6_MAX_INITIAL_RTR_ADVERT_INTERVAL	16	/* seconds */
#define ND6_MAX_INITIAL_RTR_ADVERTISEMENTS	3	/* transmissions */
#define ND6_MAX_FINAL_RTR_ADVERTISEMENTS	3	/* transmissions */
#define ND6_MIN_DELAY_BETWEEN_RAS		3	/* seconds */
#define ND6_MAX_RA_DELAY_TIME			500	/* milliseconds */

#define ND6_MAX_RTR_SOLICITATION_DELAY		1	/* second */
#define ND6_RTR_SOLICITATION_INTERVAL		4	/* seconds */
#define ND6_MAX_RTR_SOLICITATIONS		3 	/* transmissions */

#define ND6_MAX_MULTICAST_SOLICIT		3 	/* transmissions */
#define ND6_MAX_UNICAST_SOLICIT			3	/* transmissions */
#define ND6_MAX_ANYCAST_DELAY_TIME		1	/* second */
#define ND6_MAX_NEIGHBOR_ADVERTISEMENT		3	/* transmissions */
#define ND6_REACHABLE_TIME			30	/* seconds */
#define ND6_RETRANS_TIME			1	/* seconds */
#define ND6_DELAY_FIRST_PROBE_TIME		5	/* seconds */
#define ND6_MIN_RANDOM_FACTOR			0.5
#define ND6_MAX_RANDOM_FACTOR			1.5
