#if 0 

    Copyright (c) 1991 SGI   All Rights Reserved
    THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF SGI
    The copyright notice above does not evidence any
    actual or intended publication of such source code,
    and is an unpublished work by Silicon Graphics, Inc.
    This material contains CONFIDENTIAL INFORMATION that
    is the property of Silicon Graphics, Inc. Any use,
    duplication or disclosure not specifically authorized
    by Silicon Graphics is strictly prohibited.
    
    RESTRICTED RIGHTS LEGEND:
    
    Use, duplication or disclosure by the Government is
    subject to restrictions as set forth in subdivision
    (c)(1)(ii) of the Rights in Technical Data and Computer
    Software clause at DFARS 52.227-7013, and/or in similar
    or successor clauses in the FAR, DOD or NASA FAR
    Supplement.  Unpublished- rights reserved under the
    Copyright Laws of the United States.  Contractor is
    SILICON GRAPHICS, INC., 2011 N. Shoreline Blvd.,
    Mountain View, CA 94039-7311

#endif
/*
    This structure defines the configuration of the user's buffer on getTile 
    and setTile calls.
*/
#ifndef _iflConfig_h_
#define _iflConfig_h_

#include <ifl/iflTypes.h>
#include <ifl/iflCoord.h>


class iflConfig {

public:
    iflDataType dtype;

    iflOrder order;

    iflOrientation orientation;

    int nchans;

    int choff;

    int* channels;

    // Creating and destroying

    iflConfig() {}
    
    // external api: begin
    iflConfig(iflDataType type, iflOrder ord=iflInterleaved, 
    	      int nchan=0, int* chanList=NULL, int chanOff=0, 
    	      iflOrientation ori=iflOrientation(0));

    ~iflConfig() {}

    // external api: end
    
    // Channel list manipulations

    void invert(int nc, int* chanList) const;

    int isInvertable() const;

    void compose(int nc, int* in, int* out) const;
    

    int mapChan(int idx) const
	{ return (idx<0||idx>=nchans)? -1:
	    (channels!=NULL? channels[idx+choff]:idx+choff); }

    int operator[](int idx) const
	{ return mapChan(idx); }
};
#endif
