#ifndef __INC_DM_PRIVATE_H__
#define __INC_DM_PRIVATE_H__  

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

/* dm_private.h -- Declarations of private, global dmedia API */
#include <dmedia/dm_image.h>
#include <dmedia/dm_rice.h>

#ifdef __cplusplus
extern "C" {
#endif

/* This token indicates that the error is a system error to be looked
   up via oserror()
*/

#define DM_ERROR_SYSTEM (-1)

/* This token clears the error */

#define DM_ERROR_NONE (0)

void dmSetError(int errornum, const char* caller, const char* fmt, ...);
DMstatus dmRiceGetPacking(DMRiceHeader *rhp, DMimagepacking *ipk);
DMstatus dmRiceSetSamplingColorspace(DMimagepacking ipk, DMRiceHeader *rhp);

#ifdef __cplusplus
}
#endif

#endif
