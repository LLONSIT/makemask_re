#ifndef _VL_CTRL_H_
#define _VL_CTRL_H_

/*
 *  vlctrl.h - Triggered controls definitions
 *  used by apps, vl, vided, dd layers AND drivers
 *
 * Copyright 1993,1994 Silicon Graphics, Inc.
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
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <sys/types.h>
#include <sys/dmcommon.h>
#include <dmedia/dm_timecode.h>


/* Control changes occurring on specific types of triggers */
typedef uint32_t VLTriggerType;

#define VL_TRIGGER_NONE		0	/* No trigger, do it now */
#define VL_TRIGGER_MSC 		1	/* Control change at specific MSC */
#define VL_TRIGGER_GPI		2	/* Control change at a GPI */
#define VL_TRIGGER_VITC		3	/* Control change at specific VITC */
#define VL_TRIGGER_INLINE	4	/* Control change between two frames */
#define VL_TRIGGER_MINTYPE 	1
#define VL_TRIGGER_MAXTYPE 	4


/* Trigger-specific data */
typedef union {
	stamp_t msc;		/* msc trigger - MSC */
	stamp_t bufnum;		/* video buffer # - INLINE */
	uint32_t instance;	/* Which trigger - GPI */
	DMtimecode vitc;	/* vitc - VITC */
} VLTriggerVal;

#ifdef __cplusplus
}
#endif
#endif /* _VL_CTRL_H_ */
