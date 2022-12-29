/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1992-2000, Silicon Graphics, Inc.          *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 **************************************************************************/

#ifndef __SYS_SN_SNDRV_H__
#define __SYS_SN_SNDRV_H__

#if defined _KERNEL && !defined _STANDALONE
extern int sndrv_ioctl_common(dev_t, int cmd, void *arg,
				int flag, struct cred *, int *rvalp);
#endif

/* ioctl commands */
#define SNDRV_GET_ROUTERINFO		1
#define SNDRV_GET_INFOSIZE		2
#define SNDRV_GET_HUBINFO		3
#define SNDRV_GET_FLASHLOGSIZE		4
#define SNDRV_SET_FLASHSYNC		5
#define SNDRV_GET_FLASHLOGDATA		6
#define SNDRV_GET_FLASHLOGALL		7

#define SNDRV_SET_HISTOGRAM_TYPE	14

#define SNDRV_ELSC_COMMAND		19
#define	SNDRV_CLEAR_LOG			20
#define	SNDRV_INIT_LOG			21
#define	SNDRV_GET_PIMM_PSC		22
#define SNDRV_SET_PARTITION		23
#define SNDRV_GET_PARTITION		24
#define SNDRV_GET_ELSC_VERSION		25
#define SNDRV_ACQUIRE_ROUTERINFO	26
#define SNDRV_GET_SYSTEM_CONFIG_INFO	27

/* Devices */
#define SNDRV_UKNOWN_DEVICE		-1
#define SNDRV_ROUTER_DEVICE		1
#define SNDRV_HUB_DEVICE		2
#define SNDRV_ELSC_NVRAM_DEVICE		3
#define SNDRV_ELSC_CONTROLLER_DEVICE	4
#define SNDRV_SYSCTL_SUBCH		5

#if SN0
#include <sys/SN/SN0/sn0drv.h>
#endif

#endif /* __SYS_SN_SNDRV_H__ */
