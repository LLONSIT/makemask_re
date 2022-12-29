#if 0
    Copyright 1997, Silicon Graphics, Inc.
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
#ifndef _iflBMP_h_
#define _iflBMP_h_
/*
    This file defines the getTag/setTag tag values supported by the
    BMP image file format.

    The following quasi-prototypes illustrate the use of these tag values:

	getTag(iflBMPHorizResolution, unsigned int* resolution);

	    returns the horizontal resolution of the pixels in the image
	    in pixels per meter

	getTag(iflBMPVertResolution, unsigned int* resolution);

	    returns the vertical resolution of the pixels in the image
	    in pixels per meter

	getTag(iflBMPSignificantColors, unsigned int* colorCount);

	    returns the number of significant colors in the colormap

	setTag(iflBMPHorizResolution, unsigned int resolution);

	    sets the horizontal resolution of the pixels in the image
	    in pixels per meter

	setTag(iflBMPVertResolution, unsigned int resolution);

	    sets the vertical resolution of the pixels in the image
	    in pixels per meter

	setTag(iflBMPSignificantColors, unsigned int colorCount);

	    sets the number of significant colors in the colormap
*/

enum {
    iflBMPHorizResolution   = 1,
    iflBMPVertResolution    = 2,
    iflBMPSignificantColors = 3
};

#endif
