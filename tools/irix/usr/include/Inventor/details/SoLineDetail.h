/*
 * Copyright 1991-1996, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED
 *
 * UNPUBLISHED -- Rights reserved under the copyright laws of the United
 * States.   Use of a copyright notice is precautionary only and does not
 * imply publication or disclosure.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to restrictions
 * as set forth in FAR 52.227.19(c)(2) or subparagraph (c)(1)(ii) of the Rights
 * in Technical Data and Computer Software clause at DFARS 252.227-7013 and/or
 * in similar or successor clauses in the FAR, or the DOD or NASA FAR
 * Supplement.  Contractor/manufacturer is Silicon Graphics, Inc.,
 * 2011 N. Shoreline Blvd. Mountain View, CA 94039-7311.
 *
 * THE CONTENT OF THIS WORK CONTAINS CONFIDENTIAL AND PROPRIETARY
 * INFORMATION OF SILICON GRAPHICS, INC. ANY DUPLICATION, MODIFICATION,
 * DISTRIBUTION, OR DISCLOSURE IN ANY FORM, IN WHOLE, OR IN PART, IS STRICTLY
 * PROHIBITED WITHOUT THE PRIOR EXPRESS WRITTEN PERMISSION OF SILICON
 * GRAPHICS, INC.
 */
//  -*- C++ -*-

/*
 *
 _______________________________________________________________________
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 |
 |   $Revision: 2.1 $
 |
 |   Description:
 |	This file defines the SoLineDetail class.
 |
 |   Author(s)		: Thaddeus Beier, Dave Immel, Howard Look
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef _SO_LINE_DETAIL_
#define _SO_LINE_DETAIL_

#include <Inventor/details/SoPointDetail.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoLineDetail
//
//  Detail information about vertex-based shapes made of line
//  segments. It adds indices of various items that vary among lines,
//  segments, and vertices.
//
//////////////////////////////////////////////////////////////////////////////

class SoLineDetail : public SoDetail {

    SO_DETAIL_HEADER(SoLineDetail);

  public:
    // Constructor and destructor.
    SoLineDetail();
    virtual ~SoLineDetail();

    // These return the point details for the two ends of the line segment
    const SoPointDetail *	getPoint0() const	{ return &point[0]; }
    const SoPointDetail *	getPoint1() const	{ return &point[1]; }

    // Returns the index of the line the segment is part of within a
    // shape (e.g., the third line within an SoLineSet)
    int32_t			getLineIndex() const	{ return lineIndex; }

    // Returns the index of the part (usually part = segment) within a
    // shape (e.g., the fifth segment overall within an SoLineSet)
    int32_t			getPartIndex() const	{ return partIndex; }

    // Returns an instance that is a copy of this instance. The caller
    // is responsible for deleting the copy when done.
    virtual SoDetail *		copy() const;

  SoEXTENDER public:
    // Copies a point detail from the given detail
    void			setPoint0(const SoPointDetail *pd);
    void			setPoint1(const SoPointDetail *pd);

    // Sets the line index and part index
    void			setLineIndex(int32_t i)	{ lineIndex = i; }
    void			setPartIndex(int32_t i)	{ partIndex = i; }

#ifndef IV_STRICT
    void    setLineIndex(long i)				// System long
		{ setLineIndex ((int32_t) i); }
    void    setPartIndex(long i)				// System long
		{ setPartIndex ((int32_t) i); }
#endif

  SoINTERNAL public:
    static void			initClass();

  private:
    SoPointDetail		point[2];
    int32_t			lineIndex, partIndex;
};

#endif /* _SO_LINE_DETAIL_ */
