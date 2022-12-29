/**************************************************************************
 *									  *
 * 		 Copyright (C) 2001 Silicon Graphics, Inc.		  *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/

#ifndef _SYS_DEVPOLL_H
#define _SYS_DEVPOLL_H

#include <sys/poll.h>
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * ioctl() requests for /dev/poll
 */
#define DPIOC ('dp' << 8)
#define DP_POLL (DPIOC | 1)	/* Poll on fds cached in /dev/poll */
#define DP_ISPOLLED (DPIOC | 2)	/* FD already cached? */
#define DP_REMOVE (DPIOC | 3)	/* Remove pollfds on fd closure */


/*
 * /dev/poll DP_POLL structure
 */
typedef struct dvpoll {
	struct pollfd	* dp_fds;	/* Array of pollfd structures */
	nfds_t		dp_nfds;	/* Number of pollfds at dp_fds */
	int		dp_timeout;	/* Time-out in miliseconds */
} dvpoll_t;


#ifdef __cplusplus
}
#endif

#endif /* _SYS_DEVPOLL_H */
