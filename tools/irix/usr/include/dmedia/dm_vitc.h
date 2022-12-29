/***************************************************************************
 * SGI Digital Media Library: VITC Utility Routines
 *
 * <dmedia/dm_audioutil.h>
 *    header file for use with /usr/lib/libdmedia.so
 *
 * This file contains definitions used with by the VITC support routines
 * in libdmedia.  VITC stands for Vertical Interval Time Code which is a
 * method for encoding SMPTE time code in the vertical blanking portion of
 * a video signal.
 ***************************************************************************
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

#ifndef __DM_VITC_H__
#define __DM_VITC_H__

#include <sys/dmcommon.h>

#ifdef __cplusplus
extern "C" {
#endif

		/* NOTE : Moved the DMVITCcode structure to dmcommon.h */

typedef struct _DMVITCdecoder *DMVITCdecoder;

extern DMstatus		dmVITCDecoderCreate(DMVITCdecoder *decoder,
						int timecodeType);

extern DMstatus 	dmVITCDecoderDestroy(DMVITCdecoder decoder);

extern DMstatus		dmVITCDecoderSetStride(DMVITCdecoder decoder,
					int bytesperpixel,
					int offsetintopixel);

extern DMstatus		dmVITCDecode(DMVITCdecoder decoder, 
					void *videoPixels,
					int lineWidth,
					int numLines, 
					DMVITCcode *vitcCodeword);

extern DMstatus         dmVITCDecoderSetPixelTiming(DMVITCdecoder context, 
                                                    int vl_timing);


#ifdef __cplusplus
}
#endif

#endif /* __DM_VITC_H__ */
