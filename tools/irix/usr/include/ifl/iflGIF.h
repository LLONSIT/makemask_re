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
#ifndef _iflGIF_h_
#define _iflGIF_h_
/*
    This file defines the getTag/setTag tag values supported by the
    GIF image file format.

    The following quasi-prototypes illustrate the use of these tag values:

	getTag(iflGIFtransparentColor, int* red, int* green, int* blue)
	
	    returns color of transparent pixel in 'red', 'green' and 'blue'
	    or ilUNSUPPORTEDBYFILE status if none specified for image
	    
	getTag(iflGIFtransparentIndex, int* index)
	
	    returns index value of transparent pixel in 'index' if any
	    or ilUNSUPPORTEDBYFILE status if none specified for image
	    
	getTag(iflGIFinterlace, int* interlaced)

	    returns TRUE in 'interlaced' if the image is interlaced

	getTag(iflGIFdelayTime, int* delayTime)

	    returns delayTime in 1/100th's of a second for current frame

	getTag(iflGIFdisposalMethod, int* method)

	    returns how the graphic is treated after being displayed in 'method'

	getTag(iflGIFuserInput, int* input)

	    returns TRUE in 'input' if user input is expected before 
	    continuing after this image

	getTag(iflGIFleftPosition, int* left)

	    returns position of left edge of this image in the logical screen
	    in 'left'

	getTag(iflGIFtopPosition, int* top)

	    returns position of top edge of this image in the logical screen
	    in 'top'

	getTag(iflGIFscreenWidth, int* width)

	    returns logical screen width for all sub-images in 'width'

	getTag(iflGIFscreenHeight, int* height)

	    returns logical screen height for all sub-images in 'height'

	getTag(iflGIFaspectRatio, float* ratio)

	    returns quotient of pixel's width over its height in 'ratio'
	    or ilUNSUPPORTEDBYFILE status if none specified for image

	getTag(iflGIFglobalMap, const iflColormap** cmap)

	    returns the global color map for the file in 'cmap' or
	    ilUNSUPPORTEDBYFILE status if none specified for image

	getTag(iflGIFbackgroundIndex, int* index)

	    returns background color index for logical screen in 'index'
	    or ilUNSUPPORTEDBYFILE status if none specified for image

	getTag(iflGIFbackgroundColor, int* red, int* green, int* blue)
	
	    returns color of background pixel in 'red', 'green' and 'blue'
	    or ilUNSUPPORTEDBYFILE status if none specified for image

	getTag(iflGIFloopCount, int* count)

	    returns the loop count for the animation sequence in 'count'
	    or ilUNSUPPORTEDBYFILE status if none specified for image


	setTag(iflGIFtransparentIndex, int index)
	
	    sets index value of transparent pixel to 'index'
	    
	setTag(iflGIFinterlace, int interlaced)

	    turns interlace mode on if 'interlaced' is TRUE, off otherwise; 
	    must be called before any data is written to the file

	setTag(iflGIFdelayTime, int delayTime)

	    sets the delayTime in 1/100th's of a second for current frame

	setTag(iflGIFdisposalMethod, int method)

	    sets how the graphic is treated after being displayed to 'method'

	setTag(iflGIFuserInput, int input)

	    indicates the user input is expected before continuing after
	    this image if 'input' is TRUE

	setTag(iflGIFleftPosition, int left)

	    sets the position of left edge of this image in the logical screen
	    to 'left'

	setTag(iflGIFtopPosition, int top)

	    sets the position of top edge of this image in the logical screen
	    to 'top'

	setTag(iflGIFscreenWidth, int width)

	    sets the logical screen width for all sub-images to 'width';
	    must be specified before any image are written

	setTag(iflGIFscreenHeight, int height)

	    sets the logical screen height for all sub-images to 'height';
	    must be specified before any images are written

	setTag(iflGIFaspectRatio, float ratio)

	    sets the quotient of pixel's width over its height to 'ratio';
	    must be specified before any images are written

	setTag(iflGIFglobalMap, const iflColormap* cmap)

	    sets the global color map for the file in 'cmap';
	    must be specified before any images are written

	setTag(iflGIFbackgroundIndex, int index)

	    sets the background color index for logical screen to 'index';
	    must be specified before any images are written

	setTag(iflGIFloopCount, int count)

	    sets the animation loop count to 'count';
	    must be specified before any images are written
*/

enum { 
    /* per sub-image tags */

    iflGIFtransparentIndex = 0,	/* transparent index */
    iflGIFtransparentColor = 1,	/* transparent color */
    iflGIFinterlace = 2, 	/* write file as interlaced data */
    iflGIFdelayTime = 3, 	/* delay time */
    iflGIFdisposalMethod = 4, 	/* delay time */
    iflGIFuserInput = 5, 	/* delay time */
    iflGIFleftPosition = 6,   	/* image left position */
    iflGIFtopPosition = 7,   	/* image top position */

    /* per file tags */

    iflGIFscreenWidth = 20,  	/* logical screen width */
    iflGIFscreenHeight = 21,  	/* logical screen height */
    iflGIFaspectRatio = 22,   	/* pixel aspect ratio */
    iflGIFglobalMap = 23,   	/* global color map */
    iflGIFbackgroundIndex = 24,	/* background color index */
    iflGIFbackgroundColor = 25,	/* background color */
    iflGIFloopCount = 26	/* number of iterations for aninmation */
};

#endif
