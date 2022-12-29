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
    This class is an iterator for converters.  It is used to step to the 
    beginning of each row shared in common between two converters.
    The iterator also steps thru the channels.
*/
#ifndef _iflConvIter_h_
#define _iflConvIter_h_

#include <ifl/iflTypes.h>
#include <ifl/iflTile.h>
#include <ifl/iflConverter.h>


class iflConvIter {
private:
    iflConverter& dst;
    iflConverter& src;
    iflTile     com;	// intersection of the two converter tiles
    int baseD, baseS;	// base indexes to start of com (static)
    int ci;		// channel index counter
    int zi;		// Z dimension counter
    int yi;		// Y dimension counter
    int ziD, ziS;	// Z dimension buffer markers
    int yiD, yiS;	// Y dimension buffer markers
    int sxD, sxS;	// X strides
    int nx;		// X count
    int collapse;	// X/C loop collapse flag

    // reset iterator (after modifying dst and src converters)
    int reset();

    // finds next pair of matching channel numbers
    // returns True if a pair was found
    //	  (also re-computes ziA and ziB as side-effect if True is returned)
    int nextChan();

    // conversion functions
    void BitSwitch();
    void uCharSwitch();
    void charSwitch();
    void uShortSwitch();
    void shortSwitch();
    void uIntSwitch();
    void intSwitch();
    void floatSwitch();
    void doubleSwitch();

    // functions used by fastCopy for optimization checks
    int sameType()
    {
	return (dst.type == src.type) ||
	    ( (dst.type == iflUChar || dst.type == iflChar) && 
		(src.type == iflUChar || src.type == iflChar) ) ||
	    ( (dst.type == iflUShort || dst.type == iflShort) && 
		(src.type == iflUShort || src.type == iflShort) ) ||
	    ( (dst.type == iflUInt || dst.type == iflInt) && 
		(src.type == iflUInt || src.type == iflInt) );
    }

    int sameXdim()
	{ return src.flipX==dst.flipX && !src.transposeXY && !dst.transposeXY; }
    int sameChans();
    int sameXY()
	{ return dst.flipY == src.flipY &&
	    	 com.nx == dst.area.nx && com.nx == src.area.nx && 
		 (com.ny == dst.area.ny && com.ny == src.area.ny ||
	    	  com.nz == 1); }
    int sameZ()
	{ return com.ny == dst.area.ny && com.ny == src.area.ny &&
	    	 com.nz == dst.area.nz && com.nz == src.area.nz; }

    // fast copy functions
    int fastCopy();
    void rowCopy();
    void chanCopy();
    void wholeCopy();

public:
    iflConvIter(iflConverter& dest, iflConverter& source);

    // perform conversion on an area
    void convert(const iflTile& area);

    // return source and destination indexes
    int destIndex()   { return yiD; }
    int sourceIndex() { return yiS; }

    // steps private fields up to the next row
    int nextRow()
	{
	    return ++yi < com.ny?
			    (yiD += dst.stride.y, yiS += src.stride.y, 1) :
		(yi = 0, ++zi < com.nz? 
			    (yiD = ziD += dst.stride.z, 
			     yiS = ziS += src.stride.z, 1) :
			(zi = 0, nextChan()));
	}

};
#endif
