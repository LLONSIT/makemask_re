#if 0
    Copyright 1997 Noran Instruments Inc.
    All Rights Reserved

    Noran Instruments Inc.
    2551 W. Beltline Highway
    Middleton WI 53562

    Developer: Stephen M. Leo

    --

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
#ifndef _iflMT_h_
#define _iflMT_h_
/*
    These tag values are used with the getTag() and setTag() methods for
    images of either SGI movie file or QuickTime file format.

    See the iflMT(3) man page for details.
*/

enum {
    iflMTgetFrameTaggedParam,
    iflMTgetFrameAllParams,
    iflMTgetMovieHeaderTaggedParam,
    iflMTgetMovieHeaderAllParams,
    iflMTgetTrackHeaderTaggedParam,
    iflMTgetTrackHeaderAllParams,
    iflMTappendImageTrack,
    iflMTappendAudioTrack,
    iflMTremoveCurrentTrack,
    iflMTsetCurrentTrack,
    iflMTinsertFrame,
    iflMTremoveFrame,
    iflMTsetItemTagged,
    iflMTsetFrameTaggedParam,
    iflMTsetFrameAllParams,
    iflMTsetMovieHeaderTaggedParam,
    iflMTsetMovieHeaderAllParams,
    iflMTsetTrackHeaderTaggedParam,
    iflMTsetTrackHeaderAllParams,
    iflMTaddDataTags,
    iflMTgetNumberOfTracks,
    iflMTgetNumberOfFramesInTrack,
    iflMTgetFrameHeight,
    iflMTgetFrameWidth,
    iflMTsetImageTrack,
    iflMTsetAudioTrack,
    iflMTgetNumberOfImageTracks,
    iflMTgetNumberOfAudioTracks,
    iflMTgetTrackMedium,
    iflMToptimizeMovie
};



#endif

