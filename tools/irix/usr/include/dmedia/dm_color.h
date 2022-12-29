/*
 * dm_color.h
 *
 *	Man pages for the Color Space Library
 *        can be obtained by: man dmColor
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
 */

/*
 *
 * The Color Space Library supports the following tokens defined in dm_image.h:
 *
 * DM_IMAGE_WIDTH
 * DM_IMAGE_HEIGHT
 * DM_IMAGE_PACKING:     DM_IMAGE_PACKING_RGB
 *                       DM_IMAGE_PACKING_BGR
 *                       DM_IMAGE_PACKING_RGBX
 *                       DM_IMAGE_PACKING_RGBA
 *                       DM_IMAGE_PACKING_XRGB
 *                       DM_IMAGE_PACKING_ARGB
 *                       DM_IMAGE_PACKING_XBGR
 *                       DM_IMAGE_PACKING_ABGR
 *                       DM_IMAGE_PACKING_XRGB1555
 *                       DM_IMAGE_PACKING_RGBA5551
 *                       DM_IMAGE_PACKING_CbYCr
 *                       DM_IMAGE_PACKING_CbYCrA
 *                       DM_IMAGE_PACKING_CbYCrY
 *                       DM_IMAGE_PACKING_CbYCrYYY
 *                       DM_IMAGE_PACKING_LUMINANCE
 *                       DM_IMAGE_PACKING_LUMINANCE_ALPHA
 * DM_IMAGE_DATATYPE:    DM_IMAGE_DATATYPE_BIT
 *                       DM_IMAGE_DATATYPE_CHAR
 *                       DM_IMAGE_DATATYPE_SHORT10L
 *                       DM_IMAGE_DATATYPE_SHORT10R
 *                       DM_IMAGE_DATATYPE_SHORT12L
 *                       DM_IMAGE_DATATYPE_SHORT12R
 * DM_IMAGE_ORDER:       DM_IMAGE_ORDER_INTERLEAVED
 *                       DM_IMAGE_ORDER_SEQUENTIAL
 *                       DM_IMAGE_ORDER_SEPARATE
 * DM_IMAGE_ORIENTATION: DM_IMAGE_TOP_TO_BOTTOM
 *                       DM_IMAGE_BOTTOM_TO_TOP
 * DM_IMAGE_MIRROR:      DM_IMAGE_LEFT_TO_RIGHT
 *                       DM_IMAGE_RIGHT_TO_LEFT
 * DM_IMAGE_COMPONENT_1
 * DM_IMAGE_COMPONENT_2
 * DM_IMAGE_COMPONENT_3
 * DM_IMAGE_COMPONENT_ALPHA
 * DM_IMAGE_COMPONENT_ALL
 * DM_IMAGE_BIAS
 * DM_IMAGE_SCALE
 * DM_IMAGE_MIN
 * DM_IMAGE_MAX
 * DM_IMAGE_GAMMA
 * DM_IMAGE_GAMMA_TB
 * DM_IMAGE_GAMMA_TS
 * DM_IMAGE_GAMMA_A
 * DM_IMAGE_GAMMA_B
 * DM_IMAGE_GAMMA_C
 * DM_IMAGE_GAMMA_TABLE
 *
 */

#ifndef __DM_COLOR_H__
#define __DM_COLOR_H__

#ifdef __cplusplus
extern "C" {
#endif

#ident "$Revision: 1.20 $"

#include <dmedia/dmedia.h>
#include <dmedia/dm_image.h>
#include <dmedia/dm_params.h>


typedef struct _DMcolorconverter* DMcolorconverter;


/*************
*
* dmColor set/get source/destination/conversion parameters
*
*************/
extern DMstatus dmColorSetSrcParams  (const DMcolorconverter converter,
                                            DMparams        *srcParams);
extern DMstatus dmColorSetDstParams  (const DMcolorconverter converter,
                                            DMparams        *dstParams);
extern DMstatus dmColorGetSrcParams  (const DMcolorconverter converter,
                                            DMparams        *srcParams);
extern DMstatus dmColorGetDstParams  (const DMcolorconverter converter,
                                            DMparams        *dstParams);
extern DMstatus dmColorSetConvParams (const DMcolorconverter converter,
                                            DMparams        *convParams);
extern DMstatus dmColorGetConvParams (const DMcolorconverter converter,
                                            DMparams        *convParams);


/*************
*
* dmColor set/get conversion parameters
*
*************/
extern DMstatus dmColorSetContrast          (const DMcolorconverter converter,
                                             const float            contrast);
extern DMstatus dmColorSetBrightness        (const DMcolorconverter converter, 
                                             const float            brightness);
extern DMstatus dmColorSetSaturation        (const DMcolorconverter converter,
                                             const float            saturation);
extern DMstatus dmColorSetHue               (const DMcolorconverter converter,
                                             const float            hue);
extern DMstatus dmColorSetDefaultAlpha      (const DMcolorconverter converter, 
                                             const float            defaultAlpha);
extern DMstatus dmColorSetSubsamplingFilter (const DMcolorconverter converter,
                                             const int              subsamplingFilter);

extern DMstatus dmColorGetContrast          (const DMcolorconverter converter,
                                                   float           *contrast);
extern DMstatus dmColorGetBrightness        (const DMcolorconverter converter,
                                                   float           *brightness);
extern DMstatus dmColorGetSaturation        (const DMcolorconverter converter,
                                                   float           *saturation);
extern DMstatus dmColorGetHue               (const DMcolorconverter converter,
                                                   float           *hue);
extern DMstatus dmColorGetDefaultAlpha      (const DMcolorconverter converter,
                                                   float           *defaultAlpha);
extern DMstatus dmColorGetSubsamplingFilter (const DMcolorconverter converter,
                                                   int             *subsamplingFilter);


/*************
*
* dmColor get information routines
*
*************/
extern DMstatus dmColorGetSrcSize         (const DMcolorconverter converter,
                                                 int             *size);
extern DMstatus dmColorGetDstSize         (const DMcolorconverter converter,
                                                 int             *size);


/*************
*
* dmColor manager routines
*
*************/
extern DMstatus dmColorCreate            (DMcolorconverter *converter);
extern DMstatus dmColorDestroy     (const DMcolorconverter  converter);
extern DMstatus dmColorPrecompute  (const DMcolorconverter  converter);
extern DMstatus dmColorConvert     (const DMcolorconverter  converter,
                                          void             *srcImage,
                                          void             *dstImage);

/*************
*
* dmColor error handling routines
*
*************/
extern DMstatus    dmColorGetError       (const DMcolorconverter converter,
                                                int             *error);
extern const char *dmColorGetErrorString (const int              error);


/**************
*
* dmColor conversion params
*
**************/
#define DM_COLOR_CONV_CONTRAST		 "DM_COLOR_CONV_CONTRAST"
#define DM_COLOR_CONV_BRIGHTNESS	 "DM_COLOR_CONV_BRIGHTNESS"
#define DM_COLOR_CONV_SATURATION	 "DM_COLOR_CONV_SATURATION"
#define DM_COLOR_CONV_HUE		 "DM_COLOR_CONV_HUE"
#define DM_COLOR_CONV_DEFAULT_ALPHA	 "DM_COLOR_CONV_DEFAULT_ALPHA"
#define DM_COLOR_CONV_SUBSAMPLING_FILTER "DM_COLOR_CONV_SUBSAMPLING_FILTER"
#define DM_COLOR_CONV_RED_BIAS		 "DM_COLOR_CONV_RED_BIAS"
#define DM_COLOR_CONV_RED_SCALE		 "DM_COLOR_CONV_RED_SCALE"
#define DM_COLOR_CONV_GREEN_BIAS	 "DM_COLOR_CONV_GREEN_BIAS"
#define DM_COLOR_CONV_GREEN_SCALE	 "DM_COLOR_CONV_GREEN_SCALE"
#define DM_COLOR_CONV_BLUE_BIAS		 "DM_COLOR_CONV_BLUE_BIAS"
#define DM_COLOR_CONV_BLUE_SCALE	 "DM_COLOR_CONV_BLUE_SCALE"
#define DM_COLOR_CONV_TRANSFORM_MATRIX	 "DM_COLOR_CONV_TRANSFORM_MATRIX"


/*************
*
* dmColor subsampling filter types
*
*************/
#define DM_COLOR_SUBSAMPLINGFILTER_TYPE0  10001  /* Replication/elimination of chroma.  */
#define DM_COLOR_SUBSAMPLINGFILTER_TYPE1  10002  /* Linear interpolation/extrapolation. */
#define DM_COLOR_SUBSAMPLINGFILTER_TYPE2  10003  /* Recommended CCIR filters.           */


/*************
*
* dmColor errors
*
*************/
#define DM_COLOR_ERROR_NONE                1001  /* "No error."                         */
#define DM_COLOR_ERROR_OUT_OF_MEMORY       1002  /* "Out of memory!"                    */
#define DM_COLOR_ERROR_INVALID_CONVERTER   1003  /* "Invalid converter!"                */
#define DM_COLOR_ERROR_INVALID_SRC         1004  /* "Invalid source pointer!"           */
#define DM_COLOR_ERROR_INVALID_DST         1005  /* "Invalid destination pointer!"      */
#define DM_COLOR_ERROR_INVALID_TOKEN       1006  /* "Invalid token!"                    */
#define DM_COLOR_ERROR_INVALID_VALUE       1007  /* "Invalid value!"                    */
#define DM_COLOR_ERROR_INVALID_DIMENSION   1008  /* "Invalid dimension!"                */
#define DM_COLOR_ERROR_INVALID_TRANSFORM   1009  /* "Invalid transform!"                */



#ifdef __cplusplus
}
#endif

#endif /* !__DM_COLOR_H__ */
