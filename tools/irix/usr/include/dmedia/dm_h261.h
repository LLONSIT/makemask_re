#ifndef __INC_DM_H261_H__
#define __INC_DM_H261_H__  

/*****************************************************************************
 *
 * Copyright 1995, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED
 *
 * UNPUBLISHED -- Rights reserved under the copyright laws of the United
 * States.   Use of a copyright notice is precautionary only and does not
 * imply publication or disclosure.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to restrictions
 * as set forth in FAR 52.227.19(c)(2) or subparagraph (c)(1)(ii) of the Rights
 * in Technical Data and Computer Software clause at DFARS 252.227-7013 and/or
 * in similar or successor clauses in the FAR, or the DOD or NASA FAR
 * Supplement.  Contractor/manufacturer is Silicon Graphics, Inc.,
 * 2011 N. Shoreline Blvd. Mountain View, CA 94039-7311.
 *
 * THE CONTENT OF THIS WORK CONTAINS CONFIDENTIAL AND PROPRIETARY
 * INFORMATION OF SILICON GRAPHICS, INC. ANY DUPLICATION, MODIFICATION,
 * DISTRIBUTION, OR DISCLOSURE IN ANY FORM, IN WHOLE, OR IN PART, IS STRICTLY
 * PROHIBITED WITHOUT THE PRIOR EXPRESS WRITTEN PERMISSION OF SILICON
 * GRAPHICS, INC.
 *
 ****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#define DM_IC_H261_MINFO        "DM_IC_H261_MINFO"
#define DM_IC_H261_FLOATCOMP    "DM_IC_H261_FLOATCOMP"
#define DM_IC_H261_AGE          "DM_IC_H261_AGE"
#define DM_IC_H261_MODE         "DM_IC_H261_MODE"
#define DM_IC_H261_MAXQUANT     31

typedef enum {
    DM_IC_H261_MODE_INTRA,
    DM_IC_H261_MODE_INTER,
    DM_IC_H261_MODE_ALL
} DMicH261mode;

typedef struct __H261Hdr {
    int sbit;
    int ebit;
} H261hdr, *PH261hdr;


#ifdef __cplusplus 
}
#endif

#endif /* ! __INC_DM_H261_H__  */

