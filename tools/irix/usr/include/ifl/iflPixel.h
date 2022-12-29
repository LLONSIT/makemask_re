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
   This class is used to represent a single pixel.
*/
#ifndef _iflPixel_h_
#define _iflPixel_h_


#include <ifl/iflTypes.h>

class iflPixel {

public:
    // external api: begin

    // Constructing and destroying

    iflPixel(iflDataType type=iflDataType(0), int nc=0, const void* data=NULL);
    // external api: name=iflPixelPixCreate
    iflPixel(const iflPixel& pix);

    ~iflPixel() { if (data != NULL) delete [] data; }

    // Initializing

    void set(iflDataType type, int nc=0, const void* data = NULL);

    void convert(const iflPixel& pix, iflDataType toType, int nc=0, 
		 int* chanList=NULL);

    // external api: end
    void operator=(const iflPixel& pix);
    // external api: begin

    // Member access

    double getElem(int index) const;

    void setElem(double val, int index=0);
    
    double min() const;

    double max() const;

    int getNumChans() const { return nchans; }

    iflDataType getDataType() const { return dtype; }

    void* getData() const { return data; }

    // external api: end

    // Convenience operators

    double operator[](int index) const { return getElem(index); }

    int operator==(const iflPixel& pix);

    int operator!=(const iflPixel& pix);

private:
    void init();
    iflDataType dtype;	// for now all channels have the same data type
    int nchans;		// number of components/elements
    void* data;		// actual pixel data

};
#endif
