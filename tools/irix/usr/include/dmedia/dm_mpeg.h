#ifndef __INC_DM_MPEG_H__
#define __INC_DM_MPEG_H__  

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

/*
 * Image conversion interface definitions for MPEG image converters
 * (DM_IC_ID == "MPEG")
 */

/* dmICSend "refs[]" */
#define	DM_MPEG_BUF_OUT		0		/* decoded output picture */
#define	DM_MPEG_BUF_Q		1		/* input Q matrices */
#define	DM_MPEG_BUF_FWD		2		/* forward reference frame */
#define	DM_MPEG_BUF_BWD		3		/* backward reference frame */
#define	DM_MPEG_BUF_ROUT	4		/* output reference frame, may be
						 * formatted differently than the
						 * regular output frame above */
#define	DM_MPEG_MAXBUFS		5

/*
 * dmICSend "in" buffer user data
 *
 *  these are valid for both MPEG1 and MPEG2
 *  these values cannot be reused in the
 *  MPEG1 and MPEG2 specific param lists
 *  below
 */
#define DM_MPEG_UD_HSIZE        0
#define DM_MPEG_UD_VSIZE        1
#define DM_MPEG_UD_PTYPE        2

/*
 * dmICSend "in" buffer user data
 *
 *  these are valid for MPEG1 decode, where the image
 *  type is DM_IMAGE_MPEG1
 */
#define DM_MPEG1_UD_FWD_VEC      3
#define DM_MPEG1_UD_FWD_CODE     4
#define DM_MPEG1_UD_BWD_VEC      5
#define DM_MPEG1_UD_BWD_CODE     6
#define	DM_MPEG1_UD_COUNT	 7

/*
 * dmICSend "in" buffer user data
 *
 *  these are valid for MPEG2 decode, where the image
 *  type is DM_IMAGE_MPEG2
 */
#define DM_MPEG2_UD_FWD_VEC		3
#define DM_MPEG2_UD_FWD_H_CODE		4
#define DM_MPEG2_UD_FWD_V_CODE		5
#define DM_MPEG2_UD_BWD_VEC		6
#define DM_MPEG2_UD_BWD_H_CODE		7
#define DM_MPEG2_UD_BWD_V_CODE		8
#define DM_MPEG2_UD_DEC_DCT_TYPE	9
#define DM_MPEG2_UD_DC_PREC		10
#define DM_MPEG2_UD_PIC_STRUCT		11
#define DM_MPEG2_UD_TOP_FIELD_FIRST	12
#define DM_MPEG2_UD_FRAME_PRED_DCT      13
#define DM_MPEG2_UD_CONCEAL_MV		14
#define DM_MPEG2_UD_Q_TBL_TYPE		15
#define DM_MPEG2_UD_INTRA_VLC_TBL_VER	16
#define DM_MPEG2_UD_ALT_SCAN		17
#define	DM_MPEG2_UD_COUNT		18

/* possible values for DM_MPEG_UD_PTYPE */
#define PTYPE_I 1
#define PTYPE_P 2
#define PTYPE_B 3

#ifdef __cplusplus 
}
#endif

#endif /* ! __INC_DM_MPEG_H__  */
