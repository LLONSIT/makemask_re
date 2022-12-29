/*
 * dmnet_params.h: parameters for dmnet connections
 *
 * Copyright 1997, Silicon Graphics, Inc.
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics, Inc.;
 * the contents of this file may not be disclosed to third parties, copied or
 * duplicated in any form, in whole or in part, without the prior written
 * permission of Silicon Graphics, Inc.
 *
 * RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to restrictions
 * as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data
 * and Computer Software clause at DFARS 252.227-7013, and/or in similar or
 * successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -
 * rights reserved under the Copyright Laws of the United States.
 *
 * $Revision: 1.9 $
 */
#if !defined(_DMNET_PARAMS_H_)
#define _DMNET_PARAMS_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * dmNet params definitions
 */
#define DMNET_CONNECTION_TYPE		"DMNET_CONNECTION_TYPE"
#define DMNET_PORT			"DMNET_PORT"
#define DMNET_REMOTE_SOCKADDR		"DMNET_REMOTE_SOCKADDR"
#define DMNET_LOCAL_SOCKADDR		"DMNET_LOCAL_SOCKADDR"
#define DMNET_REMOTE_HOSTNAME		"DMNET_REMOTE_HOSTNAME"
#define	DMNET_PLUGIN_NAME		"DMNET_PLUGIN_NAME"

/*
 * Types of connections.
 */
#define	DMNET_LOCAL	0
#define	DMNET_TCP	1
#define	DMNET_PLUGIN	99

/*
 * Add-on connection types
 */
#define	DMNET_STRIPED_HIPPI	100

#ifdef __cplusplus
}
#endif

#endif
