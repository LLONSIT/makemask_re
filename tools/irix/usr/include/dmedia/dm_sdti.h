/*****************************************************************************
 *
 * SGI compression dmIC 
 *
 * dmic_sdti.h : SDTI/CSDI demultiplxer dmIC support
 *
 * Copyright 1996, Silicon Graphics, Inc.
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
 ****************************************************************************/

#ifndef _INC_DMIC_SDTI_H
#define _INC_DMIC_SDTI_H

#define MAX_SDTI_CHANNEL	4	/* MAX CHANNEL TO DECODE */

typedef struct __st_tt {
    char	st_info[MAX_SDTI_CHANNEL];
    char	tt_info[MAX_SDTI_CHANNEL];
} st_tt;

typedef struct __SDTIErrInfo {
    int 	errNum;
    st_tt	st_tt_info;
} SDTIErrInfo;

#define DM_IMAGE_SDTI_DV_CHANNEL_SELECT_MASK   "DM_IMAGE_SDTI_DV_CHANNEL_SELECT_MASK"	
#define DM_IMAGE_SDTI_DV_FIELD_COUNT   "DM_IMAGE_SDTI_DV_FIELD_COUNT"	
#define DM_IMAGE_SDTI_DV_RATE   "DM_IMAGE_SDTI_DV_RATE"	

#define SDTI_FIELD_PACKING 1
#define SDTI_FRAME_PACKING 2


#endif /* _INC_DMIC_SDTI_H */
