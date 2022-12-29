/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1992-1997, Silicon Graphics, Inc.          *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 **************************************************************************/

#ifndef __SYS_SN_SN0_SN0DRV_H__
#define __SYS_SN_SN0_SN0DRV_H__

#include <sys/SN/sndrv.h>

#define SN0DRV_GET_ROUTERINFO		SNDRV_GET_ROUTERINFO
#define SN0DRV_GET_INFOSIZE		SNDRV_GET_INFOSIZE
#define SN0DRV_GET_HUBINFO		SNDRV_GET_HUBINFO
#define SN0DRV_GET_FLASHLOGSIZE		SNDRV_GET_FLASHLOGSIZE
#define SN0DRV_SET_FLASHSYNC		SNDRV_SET_FLASHSYNC
#define SN0DRV_GET_FLASHLOGDATA		SNDRV_GET_FLASHLOGDATA
#define SN0DRV_GET_FLASHLOGALL		SNDRV_GET_FLASHLOGALL

#define SN0DRV_MDPERF_ENABLE		8
#define SN0DRV_MDPERF_DISABLE		9
#define SN0DRV_MDPERF_GET_COUNT		10
#define SN0DRV_MDPERF_GET_CTRL		11

#define SN0DRV_GET_SBEINFO		12

#define SN0DRV_ELSC_NVRAM		13
#define SN0DRV_SET_HISTOGRAM_TYPE	SNDRV_SET_HISTOGRAM_TYPE
#define SN0DRV_ROU_FENCE_OP          	15
#define SN0DRV_ROU_PORT_MAP             16
#define SN0DRV_ROU_PORT_NIC_GET         17
#define SN0DRV_ROU_NIC_GET         	18
#define SN0DRV_ELSC_COMMAND		SNDRV_ELSC_COMMAND

#define	SN0DRV_CLEAR_LOG		SNDRV_CLEAR_LOG
#define	SN0DRV_INIT_LOG			SNDRV_INIT_LOG
#define	SN0DRV_GET_PIMM_PSC		SNDRV_GET_PIMM_PSC

#define SN0DRV_UKNOWN_DEVICE		SNDRV_UKNOWN_DEVICE
#define SN0DRV_ROUTER_DEVICE		SNDRV_ROUTER_DEVICE
#define SN0DRV_HUB_DEVICE		SNDRV_HUB_DEVICE
#define SN0DRV_ELSC_NVRAM_DEVICE	SNDRV_ELSC_NVRAM_DEVICE
#define SN0DRV_ELSC_CONTROLLER_DEVICE	SNDRV_ELSC_CONTROLLER_DEVICE

#define SN0DRV_NVOP_READ		0x01
#define SN0DRV_NVOP_WRITE		0x02

#define SN0DRV_CMD_BUF_LEN		96	/* equals ELSC_PACKET_MAX */

typedef struct sn0drv_nvop_s {
	int		flags;
	int		addr;
	char		data;
} sn0drv_nvop_t;

typedef struct rou_regop_s {
        short           op ;
#define FENCE_IGNORE     	1       /* Ignore op on this reg        */
#define FENCE_READ       	2       /* Read value in reg            */
#define FENCE_DWRITE     	4       /* Destructive WRITE            */
#define FENCE_AND_WRITE    	8       /* And mask			*/
#define FENCE_OR_WRITE    	10      /* Or mask 			*/
        router_reg_t    reg ;
} rou_regop_t ;

typedef struct sn0drv_fence_s {
        rou_regop_t     local_blk ;
        rou_regop_t     ports[MAX_ROUTER_PORTS] ;
} sn0drv_fence_t ;

typedef struct sn0drv_router_map_s {
	char 	type[MAX_ROUTER_PORTS] ;
} sn0drv_router_map_t ;

#endif /* __SYS_SN_SN0_SN0DRV_H__ */
