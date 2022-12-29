#ifndef _INC_DM_VLBUF_H_
#define _INC_DM_VLBUF_H_ 1

/*****************************************************************************
*
*  Copyright 1996, Silicon Graphics, Inc.
*  All Rights Reserved.
*
*  This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics, Inc.;
*  the contents of this file may not be disclosed to third parties, copied or
*  duplicated in any form, in whole or in part, without the prior written
*  permission of Silicon Graphics, Inc.
*
*  RESTRICTED RIGHTS LEGEND:
*  Use, duplication or disclosure by the Government is subject to restrictions
*  as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data
*  and Computer Software clause at DFARS 252.227-7013, and/or in similar or
*  successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -
*  rights reserved under the Copyright Laws of the United States.
* 
*****************************************************************************/

#include <sys/dms.h>
#include <sys/dmcommon.h>
#include <sys/vlbuf.h>
#include <dmedia/dm_buffer.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Routines supporting video non-dmrb buffer access.
 */
DMstatus vlBufGetValid(int, dmbufevent_t*);
int vlBufGetFree(int, int);
int vlBufGetDone(int);
DMstatus vlBufSetDone(int, int);

#ifdef __cplusplus
}
#endif

#endif
