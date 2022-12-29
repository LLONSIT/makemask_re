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
#ifndef _iflFIT_h_
#define _iflFIT_h_
/*
    This file defines the getTag/setTag tag values supported by the
    FIT image file format.

    The following quasi-prototypes illustrate the use of these tag values:

	getTag(iflFITextensionSize, int* extSize)
	
	    returns size of extension in bytes in 'extSize'
	    
	getTag(iflFITextensionData, void* extData, int length)

	    reads 'length' bytes of extension data into 'extData'

	setTag(iflFITextensionSize, int extSize)

	    sets size of extension in bytes to 'extSize', must be called
	    before any data is written to the file
	    
	setTag(iflFITextensionData, void* extData, int length)

	    writes 'length' bytes of extension data into 'extData'
*/

enum { 
    iflFITextensionSize = 1,	/* size of user extension */
    iflFITextensionData = 2	/* user extension data */
};

#endif
