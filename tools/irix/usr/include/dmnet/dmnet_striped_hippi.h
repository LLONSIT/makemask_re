/*
 * dmnet_striped_hippi.h: parameters for striped hippi connections
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
 * $Revision: 1.3 $
 */
#if !defined(_DMNET_STR_HIPPI_H_)
#define _DMNET_STR_HIPPI_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * params definitions
 */

#define	DMNET_HIPPI_NDEV	"DMNET_HIPPI_NDEV"
#define	DMNET_HIPPI_DEV		"DMNET_HIPPI_DEV%d"
#define	DMNET_HIPPI_IFIELD	"DMNET_HIPPI_IFIELD%d"
#define	DMNET_HIPPI_ULP		"DMNET_HIPPI_ULP"
#define	DMNET_HIPPI_STRIPE	"DMNET_HIPPI_STRIPE"

#ifdef __cplusplus
}
#endif

#endif
