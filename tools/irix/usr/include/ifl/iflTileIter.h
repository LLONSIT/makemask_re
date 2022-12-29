#if 0 

    Copyright (c) 1991-1995 SGI   All Rights Reserved
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
#ifndef _iflTileIter_h_
#define _iflTileIter_h_

#include <ifl/iflTile.h>
#include <ifl/iflConfig.h>
#include <ifl/iflSize.h>

class iflTileIter : public iflTile3D<int> {

public:
    // Constructors

    iflTileIter(const iflTile3Dint& parent, const iflSize& pageSize, 
	        int cSize, const iflConfig* config=NULL, int tileAligned=FALSE);

    iflTileIter(const iflTile3Dint& parent, int cSize, 
		const iflConfig* config=NULL, int tileAligned=FALSE);

    // Iteration

    int more();
    
    int getCount() { if (altered) reset(); return pageCount; }

    // Initialization

    void setPageSize(const iflSize& pageSize);
    
    void setTile(const iflTile3Dint& parent, int cSize, 
	         const iflConfig* cfg=NULL, int tileAligned=0);
		 
    void setPageBorder(const iflXYZint& border, int includeBorder=FALSE);

    int c;
    int nc;

protected:
    iflTileIter() {}

private:
    // finds (possibly) indirected channel
    int moreChans();
    
    // sets up for iteration, called by more() or getCount() if any of
    // the iterators parameters have been altered
    void reset();
    
    int ox, oy, oz, oc;	// parent tile origin
    int sx, sy, sz, sc;	// starting x,y,z,c location
    int ex, ey, ez, ec;	// ending x,y,z,c location
    int* chanList;	// channel indirection list
    int cLen;		// length of channel list
    int dx, dy, dz;	// page deltas (different from nx if page border > 0)
    int bx, by, bz;	// page borders
    
    int incBorder;	// if TRUE, include pages with only border data
    int talign;		// if TRUE, align iteration to parent tile origin
    int altered;	// if TRUE, reset() needs to be called 
    int pageCount;	// number of pages that will be iterated

};
#endif
