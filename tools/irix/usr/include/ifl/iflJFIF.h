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
#ifndef _iflJFIF_h_
#define _iflJFIF_h_
/*
    This file defines the getTag/setTag tag values supported by the
    JFIF image file format.

    The following quasi-prototypes illustrate the use of these tag values:

	getTag(iflJFIFcompressionQuality, int* val)

	    This function returns the value of the quality factor used in
	    encoding or creating the JFIF image file. The "quality
	    factor" is the amount by which quantization tables are scaled
	    to adjust image quality.

	getTag(iflJFIFenableOptHuffTab, int* on)

	    This function returns TRUE in 'on' if optimization of entropy
	    encoding parameters is enabled; FALSE otherwise.

	getTag(iflJFIFrestartInterval, int* val)

	    This function returns the value of the restart interval
	    used in encoding or creating the JFIF image file. This is
	    the interval at which a JPEG restart marker is emitted.
	    This interval is either in number of MCU rows or blocks.

	getTag(iflJFIFsmoothingFactor, int* val)

	    This function returns the value of the smoothing factor, used
	    to eliminate dithering noise while encoding or creating the
	    JFIF image file.  The value ranging from 0 to 100, indicates
	    the strength of smoothing.  0 means no smoothing.

	getTag(iflJFIFqTable, char** qtablefile)

	    This function returns the filename from which the custom
	    quantization tables were read. These are tables used in
	    encoding or creating the JFIF image file. If default tables
	    were used, NULL is returned.

	getTag(iflJFIFsamplingFactors, int* horiz, int* vert, int ch)

	    The horizontal and vertical sampling factors used (in encoding
	    or creating the JFIF image file) for channel 'ch' are returned
	    in 'horiz' and 'vert'.

	getTag(iflJFIFgrayScaleEncoding, int* on)

	    This function returns TRUE in 'on' if grayscale encoding is
	    enabled i.e. a monochrome JFIF file is created from a color
	    input; FALSE otherwise.

	getTag(iflJFIFgrayScaleDecoding, int* on)

	    This function returns TRUE in 'on' if grayscale decoding is
	    enabled i.e. a color file is read as a monochrome image;
	    FALSE otherwise.

	getTag(iflJFIFblockSmoothing, int* on)

	    This function returns TRUE in 'on' if cross-block smoothing 
	    (a decoding parameter) is enabled; FALSE otherwise.

	setTag(iflJFIFcompressionQuality, int val)

	    This function sets the quality factor used in encoding or
	    creating a JFIF image file to 'val'. val can range from 0
	    (worst) to 100 (best), default is 75.  The quality factor lets
	    you trade off compressed file size against quality of the
	    reconstructed image: the higher the quality setting, the larger
	    the JPEG file, and the closer the output image will be to the
	    original input.  Normally you want to use the lowest quality
	    setting (smallest file) that decompresses into something
	    visually indistinguishable from the original image.  For this
	    purpose the quality setting should be between 50 and 95; the
	    default of 75 is often about right.  If you see defects at 75,
	    then go up 5 or 10 counts at a time until you are happy with
	    the output image.  (The optimal setting will vary from one
	    image to another.)

	setTag(iflJFIFenableOptHuffTab, int on)

	    This method can be used to enable optimization of entropy
	    encoding parameters, used while encoding or creating a JFIF
	    image file, by setting 'on' = TRUE.  By default this
	    optimization is not enabled and default encoding parameters are
	    used.  Enabling the optimization usually makes the JPEG file a
	    little smaller, but the compression runs somewhat slower and
	    needs much more memory.  Image quality and speed of
	    decompression are unaffected by enabling optimization.

	setTag(iflJFIFrestartInterval, int val, int inRows)

	    This function is used to set the restart interval used in
	    encoding or creating the JFIF image file. If 'inRows' = TRUE then
	    a JPEG restart marker is emitted every 'val' MCU rows; else if
	    inRows = FALSE, a JPEG restart marker is emitted every val MCU
	    blocks. The restart option inserts extra markers that allow a
	    JPEG decoder to

	setTag(iflJFIFsmoothingFactor, int val)

	    This function sets the smoothing factor, useful in eliminating
	    dithering noise, to 'val'. This is used while encoding or
	    creating a JFIF image file.  val can range from 0 to 100,
	    indicating the strength of smooting; 0, the default means no
	    smoothing. This smoothing option filters the input to eliminate
	    fine-scale noise.  This is often useful when converting GIF
	    files to JPEG: a moderate smoothing factor of 10 to 50 gets rid
	    of dithering patterns in the input file, resulting in a smaller
	    JPEG file and a better-looking image.  Too large a smoothing
	    factor will visibly blur the image, however. This functionality
	    is meant for advanced users with some knowledge of JPEG.

	setTag(iflJFIFqTable, char* qtablefile)

	    This function can be used to set the quantization tables to be
	    used in the encoding process to those in the file 'qtablefile'.
	    The file should contain one to four tables (64 values each) as
	    plain text.  Comments preceded by '#' may be included in the
	    file.  The tables are implicitly numbered 0,1,etc. If a
	    non-zero quality factor is also specified, the values in the
	    file are scaled according to a quality scaling curve. If
	    qtablefile = NULL, default tables are used. This function is
	    meant for wizards with indepth knowledge of JPEG.

	setTag(iflJFIFsamplingFactors, int horiz, int vert, int ch)

	    This function can be used to set the JPEG sampling factors used
	    in creating a JFIF image file. The horizontal and vertical
	    sampling for channel 'ch' are set to 'horiz' and 'vert'. This
	    function is meant for wizards with indepth knowledge of JPEG.

	setTag(iflJFIFgrayScaleEncoding, int on)

	    This method can be used to enable creation of a monochrome JFIF
	    image file from a color (ilRGB) input, by setting 'on' = TRUE. By
	    default this functionality is disabled and a color input
	    produces a color output. This functionality is meant for
	    advanced users with some knowledge of JPEG.

	setTag(iflJFIFgrayScaleDecoding, int on)

	    This function can be used to force a JFIF color file to be read
	    as a monochrome image (i.e. iflRGB color space is converted to
	    iflLuminance), by setting 'on' = TRUE.

	setTag(iflJFIFblockSmoothing, int on)

	    This function can be used to enable cross-block smoothing while
	    decoding or reading a JFIF image file, by setting 'on' = TRUE.
	    This is quite memory-intensive and only seems to improve the
	    image at very low quality settings (compression quality of 10
	    to 20 or so).  At normal quality settings it may make things
	    worse. By default cross-block smoothing is disabled, on =
	    FALSE. This functionality is meant for advanced users with some
	    knowledge of JPEG.
*/

enum { 
    iflJFIFcompressionQuality = 1,  /* quality factor using in encoding */
    iflJFIFenableOptHuffTab = 2,    /* optimization of entropy encoding */
    iflJFIFrestartInterval = 3,     /* interval between JPEG restart markers */
    iflJFIFsmoothingFactor = 4,     /* smoothing factor for dithering noise */
    iflJFIFqTable = 5, 		    /* quantization table file name */
    iflJFIFsamplingFactors = 6,     /* JPEG horiz/verical sampling factors */
    iflJFIFgrayScaleEncoding = 7,   /* greyscale encoding enable */
    iflJFIFgrayScaleDecoding = 8,   /* greyscale decoding enable */
    iflJFIFblockSmoothing = 9	    /* cross-block smoothing on decoding */
};

#endif
