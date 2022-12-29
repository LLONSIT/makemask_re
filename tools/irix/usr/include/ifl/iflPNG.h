#if 0
    Copyright 1995, Silicon Graphics, Inc.
    ALL RIGHTS RESERVED
 
    UNPUBLISHED -- Rights reserved under the copyright laws of the United
    States.   Use of a copyright notice is precautionary only and does not
    imply publication or disclosure.

    U.S. GOVERNMENT RESTRICTED RIGHTS LEGEND:
    Use, duplication or disclosure by the Government is subject to restrictions
    as set forth in FAR 52.227.19(c)(2) or subparagraph (c)(1)(ii) of the Rights    in Technical Data and Computer Software clause at DFARS 252.227-7013 and/or
    in similar or successor clauses in the FAR, or the DOD or NASA FAR
    Supplement.  Contractor/manufacturer is Silicon Graphics, Inc.,
    2011 N. Shoreline Blvd. Mountain View, CA 94039-7311.
 
    THE CONTENT OF THIS WORK CONTAINS CONFIDENTIAL AND PROPRIETARY
    INFORMATION OF SILICON GRAPHICS, INC. ANY DUPLICATION, MODIFICATION,
    DISTRIBUTION, OR DISCLOSURE IN ANY FORM, IN WHOLE, OR IN PART, IS STRICTLY
    PROHIBITED WITHOUT THE PRIOR EXPRESS WRITTEN PERMISSION OF SILICON
    GRAPHICS, INC.
#endif
#ifndef _iflPNG_h_
#define _iflPNG_h_

/*
 * iflPNGFile only allows O_RDONLY or O_WRONLY file access modes.  setTag()
 * is not allowed on images open for O_RDONLY.  Note that all setTag()
 * calls must occur before the setPage() call.
 */
enum {
    /*
     * Get PNG handles:
     *
     *     getTag(iflPNGhandles, png_struct **png, png_info **info);
     *
     * NOTE: the iflPNGFile* may become corrupted if the returned handles
     * are used to set arbitrary PNG state.
     */
    iflPNGhandles = 1,

    /*
     * Get/set number of bits per channel sample:
     *
     *     getTag(iflPNGbitspersample, int *bitspersample);
     *     setTag(iflPNGbitspersample, int bitspersample);
     *
     * Only legal setTag() is to set bitspersample to 2 or 4 when data type
     * is iflUChar.
     */
    iflPNGbitspersample = 2,

    /*
     * Get/set progressively interlace flag
     *
     *     getTag(iflPNGinterlace, int *interlace);
     *     setTag(iflPNGinterlace, int interlace);
     *
     * Interlace is 1 for progressively interlaced images, 0 otherwise
     */
    iflPNGinterlace = 3,

    /*
     * Get/set background color:
     *
     *     getTag(iflPNGbackground, int *valid, iflPixel *background);
     *     setTag(iflPNGbackground, iflPixel *background);
     *
     * The number of channels in backgroundColor must match the number of
     * channels in the PNG image (minus the alpha channel if present).
     * valid == 1 if a background color is present, 0 otherwise.
     */
    iflPNGbackground = 4,

    /*
     * Get/set device-independent color specification:
     *
     *     getTag(iflPNGchromaticity, int *valid, iflPNGchromaticity_t *chromaticity);
     *     setTag(iflPNGchromaticity, iflPNGchromaticity_t *chromaticity);
     *
     * valid == 1 if chromaticity is present, 0 otherwise.
     */
    iflPNGchromaticity = 5,

    /*
     * Get/set image gamma correction:
     *
     *     getTag(iflPNGgamma, int *valid, float *gamma);
     *     setTag(iflPNGgamma, float gamma);
     *
     * valid == 1 if gamma correction value is present, 0 otherwise.
     */
    iflPNGgamma = 6,		/* image gamma correction */

    /*
     * Get/set histogram for color palette images:
     *
     *     getTag(iflPNGhistogram, int *valid, png_uint_16 **histogram);
     *     setTag(iflPNGhistogram, png_uint_16 *histogram);
     *
     * Only usable on color palette images.  Returned histogram is an array
     * getColormap()->getLength() long.  The bins indicate the *approximate*
     * proportional use of the associated color indecies; though a 0
     * litterally means that the associated color index is not used at all.
     * For a getTag() the returned histogram pointer is only valid as long
     * as the underlaying iflPNGFile is valid and the histogram is not
     * changed.  For a setTag(), the passed histogram pointer should point
     * to malloc()'ed store; this store will be freed automatically when the
     * iflPNGFile is destroyed (or another histogram is set).  valid == 1
     * if histogram is pressent, 0 otherwise.
     */
    iflPNGhistogram = 7,

    /*
     * Get/set physical dimensions of pixels:
     *
     *     getTag(iflPNGpixeldimensions, int *valid, iflPNGpixeldimensions_t *pdims);
     *     setTag(iflPNGpixeldimensions, iflPNGpixeldimensions_t *pdims);
     *
     * If pdims->units == 1, pdims->xPixelsPerUnit and pdims->yPixelsPerUnit
     * contain the number of physical pixels per meter in X (width) and
     * Y (height), respectively.  If pdims->units is 0, the X and Y values
     * define the pixel aspect ratio only.  valid == 1 if physical pixel
     * dimensions are present, 0 otherwise.
     */
    iflPNGpixeldimensions = 8,

    /*
     * Get/set number of significant bits in original image:
     *
     *     getTag(iflPNGsignificantbits, int *valid, png_color_8 *sbits);
     *     setTag(iflPNGsignificantbits, png_color_8 *sbits);
     *
     * The number of significant bits in each ``color'' in the original image.
     * When setting this, each value must be less than the number of bits per
     * channel.  For each color model supported by PNG, the following fields
     * in sbits are used:
     *
     *     Color Model        Valid sbits fields
     *     ---------------------------------------------------------
     *     iflLuminance       gray
     *     iflLuminanceAlpha  gray alpha
     *     iflRGB             red green blue
     *     iflRGBA            red green blue alpha
     *     iflRGBPalette      red green blue (sig bits in palette colors)
     *
     * valid == 1 if significant bits information is present, 0 otherwise.
     */
    iflPNGsignificantbits = 9,

    /*
     * Get/set last modification time of image:
     *
     *     getTag(iflPNGtime, int *valid, struct tm *modtime);
     *     getTag(iflPNGtime, struct tm *modtime);
     *
     * The function mktime() may be called to convert the struct tm into a
     * time_t if desired.  valid == 1 if last modification time is present,
     * 0 otherwise.
     */
    iflPNGtime = 10,

    /*
     * Get/set RGB/luminance transparent color:
     *
     *     getTag(iflPNGtransparency, int *valid, iflPixel *transparent);
     *     setTag(iflPNGtransparency, iflPixel *transparent);
     *
     * This must only be used with iflRGB and iflLuminance images.  The
     * transparent color is used to mark pixels that should be considered
     * fully transparent (alpha value = 0).  All other pixels are considered
     * to be fully opaque (alpha = 1).  valid == 1 if a transparent color
     * is present, 0 otherwise.
     */
    iflPNGtransparency = 11,

    /*
     * Get/set palette transparencies:
     *
     *   getTag(iflPNGpaletteTransparency, int *valid,
     *           int *nAlphas, png_byte **paletteAlphas);
     *   setTag(iflPNGpaletteTransparency,
     *           int nAlphas, png_byte *paletteAlphas);
     *
     * This must only be used with iflRGBPalette images.  The paletteAlphas
     * array is nAlphas long and contains an array of alpha values ranging
     * from 0 to 255 corresponding to to the palette index values 0 ..
     * nAlphas-1.  Note that nAlphas may be smaller than the domain of the
     * palette image.  All palette indecies >= nAlpha are considered to have
     * alpha values of 255.  For a getTag() the returned paletteAlphas
     * pointer is only valid as long as the underlaying iflPNGFile is valid
     * and the palette transparencies are not changed.  For a setTag(), the
     * passed paletteAlphas pointer should point to malloc()'ed store; this
     * store will be freed automatically when the iflPNGFile is destroyed
     * (or another palette transparency is set).  valid == 1 is palette alphas
     * are present, 0 otherwise.
     */
    iflPNGpaletteTransparency = 12
};

/* used for iflPNGchromaticity get/setTag() calls */
typedef struct { /* cHRM chunk values */
    float	xWhite;
    float	yWhite;
    float	xRed;
    float	yRed;
    float	xGreen;
    float	yGreen;
    float	xBlue;
    float	yBlue;
} iflPNGchromaticity_t;

/* used for iflPNGpixeldimensions get/setTag() calls */
typedef struct { /* pHYs chunk values */
    uint32_t	xPixelsPerUnit;
    uint32_t	yPixelsPerUnit;
    int		units;		/* 0: unit is unknown; 1: unit is meter */
} iflPNGpixeldimensions_t;

#endif /* _iflPNG_h_ */
