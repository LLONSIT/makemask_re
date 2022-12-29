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
    This class handles type conversion and reorganization between arbitrary
    rectangular data buffers.  The buffers are described with an origin and 
    size in some logical space (e.g. the image space), a data type and
    organization, and of course a pointer to the data in question.

    An existing converter can have its data and origin changed on the fly using
    setData and setOrigin. The whole reason for this class's existence is the
    deposit method which take the overlapping data (in logical space) from a 
    source converter and deposits it into itself with appropriate conversions
    if the converters have different types or orders.
*/
#ifndef _iflConverter_h_
#define _iflConverter_h_

#include <ifl/iflTypes.h>
#include <ifl/iflTile.h>
#include <ifl/iflCoord.h>
#include <ifl/iflPixel.h>

typedef enum {
    iflFillAll, iflFillSome, iflFillNone
} iflFillMode;

class iflConvIter;

class iflConverter {
public:
    iflConverter(void* dp, iflDataType dtype, iflOrder ord, int nc, 
		 const int* chans, int nx=0, int ny=0, int nz=0, 
		 int x=0, int y=0, int z=0, int c=0)
	{ init(dp, dtype, ord, nc, chans, nx, ny, nz, x, y, z, c); }
    iflConverter(const iflPixel& val, const iflTile* fillMask=NULL, 
		 const int* chans=NULL, int coff=0)
	{ init(val, fillMask, chans, coff); }
    iflConverter(const iflConverter & conv);
    iflConverter() {}
    ~iflConverter() {}

    void init(void* dp, iflDataType dtype, iflOrder ord, int nc, 
	      const int* chans, int nx=0, int ny=0, int nz=0, 
	      int x=0, int y=0, int z=0, int c=0);
    void init(const iflPixel& val, const iflTile* fillMask=NULL, 
	      const int* chans=NULL, int coff=0);

    // retarget conversion buffer
    //
    void setData(void* dp) { data = dp; }
    void setData(const iflPixel& val, const int* chans, int coff);
    void setOrigin(int x, int y, int z, int c=0) 
	{ area.x = x; area.y = y; area.z = z; cStart = c; }
    void setTile(int x, int y, int z, int nx, int ny, int nz); 
    void setClip(int x, int y, int z, int nx, int ny, int nz)
	{ clip.x = x; clip.y = y; clip.z = z; 
	  clip.nx = nx; clip.ny = ny; clip.nz = nz; 
	  clipSet = nx > 0 && ny > 0 && nz > 0; }

    // re-configure X-Y orientation
    void setFlip(iflFlip flip) {
    	flipX = (flip&iflXFlip) != 0;
	flipY = (flip&iflYFlip) != 0;
	resetStrides();
    }
    void setTransposeXY(int transXY) {
    	transposeXY = transXY;
	resetStrides();
    }

    // set the copy mask (note: only the "from" converter's mask is used)
    void setMask(const iflTile* copyMask=NULL);

    // compare a tile against the copy mask (for fill converter)
    iflFillMode checkMask(const iflTile& tile);

    // copy data between converters
    //
    void operator=(iflConverter& from);

protected:
    void* data;				// data buffer: externally managed
    iflTile area;			// area reperesented by data buffer
    iflXYZint stride;			// strides used to access data
    int cStart, cStride, cSize;		// channel dimensions
    iflTile clip;			// copied data is clipped to this area
    iflDataType type;			// data type
    iflOrder order;			// data order (determines strides)
    const int* cList;			// channel list to access (may be NULL)
    int clipSet;			// if true, then use clip area
    int flipX, flipY;			// if true, flip dimension(s)
    int transposeXY;	    	    	// if true, transpose X and Y
    iflTile mask;			// fill mask
    int fill;				// fill converter (data is one pixel)

private:
    void resetStrides();		// re-compute tile buffer strides
    void init();

    friend class iflConvIter;
};
#endif
