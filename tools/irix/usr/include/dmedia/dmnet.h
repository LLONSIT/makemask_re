/*
 * dmnet.h: dmNet user API
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
 * $Revision: 1.13 $
 */
#if !defined(_DMNET_H_)
#define _DMNET_H_

#include <sys/dmcommon.h>
#include <dmedia/dmedia.h>
#include <dmedia/dm_buffer.h>
#include <dmedia/dmnet_params.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct dmnetconnection_s	*DMnetconnection;

extern DMstatus dmNetOpen(DMnetconnection*);
extern DMstatus dmNetClose(DMnetconnection);

extern DMstatus dmNetConnect(DMnetconnection, DMparams*);
extern DMstatus dmNetListen(DMnetconnection, DMparams*);
extern DMstatus dmNetAccept(DMnetconnection, DMparams*);

extern DMstatus dmNetRegisterPool(DMnetconnection, DMbufferpool);
extern DMstatus dmNetRegisterBuffer(DMnetconnection);

extern DMstatus dmNetGetParams(DMnetconnection, DMparams*);

extern DMstatus dmNetRecv(DMnetconnection, DMbuffer*);
extern DMstatus dmNetSend(DMnetconnection, DMbuffer);

extern int dmNetControlFd(DMnetconnection);
extern int dmNetDataFd(DMnetconnection);

extern DMstatus dmNetQueryHardware(DMnetconnection, char***, int*);
extern DMstatus dmNetQueryProtocol(DMnetconnection, char*, char***, int*);
extern DMstatus dmNetSelectProtocol(DMnetconnection, char*, char*, DMparams*);

#ifdef __cplusplus
}
#endif

#endif
