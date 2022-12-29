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
 |   $Revision: 2.2 $
 |
 |   Description:
 |	This file defines the SoFaceDetail class.
 |
 |   Author(s)		: Thaddeus Beier, Dave Immel, Howard Look
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef _SO_FACE_DETAIL_
#define _SO_FACE_DETAIL_

#include <Inventor/details/SoPointDetail.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoFaceDetail
//
//  Detail information about vertex-based shapes made of faces. It
//  adds indices of various items that vary among faces and vertices.
//
//////////////////////////////////////////////////////////////////////////////

class SoFaceDetail : public SoDetail {

    SO_DETAIL_HEADER(SoFaceDetail);

  public:
    // Constructor and destructor.
    SoFaceDetail();
    virtual ~SoFaceDetail();

    // Returns the number of points in the face
    int32_t			getNumPoints() const	{ return numPoints; }

    // Returns the point detail for the indexed point of the face
    const SoPointDetail *	getPoint(int i) const	{ return &point[i]; }

    // Returns the index of the face within a shape
    int32_t			getFaceIndex() const	{ return faceIndex; }

    // Returns the index of the part within a shape
    int32_t			getPartIndex() const	{ return partIndex; }

    // Returns an instance that is a copy of this instance. The caller
    // is responsible for deleting the copy when done.
    virtual SoDetail *		copy() const;

  SoEXTENDER public:
    // Sets the number of points in the face and allocates room for the points
    void			setNumPoints(int32_t num);

    // Copies a point detail from the given detail
    void			setPoint(int32_t index, const SoPointDetail *pd);

    // Sets the face index and part index
    void			setFaceIndex(int32_t i)	{ faceIndex = i; }
    void			setPartIndex(int32_t i)	{ partIndex = i; }

    // Return a pointer to the point details.
    SoPointDetail *		getPoints()		{ return &point[0]; }

#ifndef IV_STRICT
    void    setNumPoints(long num)				// System long
		{ setNumPoints ((int32_t) num); }
    void    setPoint(long index, const SoPointDetail *pd)	// System long
		{ setPoint ((int32_t) index, pd); }
    void    setFaceIndex(long i)				// System long
		{ setFaceIndex ((int32_t) i); }
    void    setPartIndex(long i)				// System long
		{ setPartIndex ((int32_t) i); }
#endif

  SoINTERNAL public:
    static void			initClass();

  private:
    SoPointDetail		*point;
    int32_t			numPoints;
    int32_t			faceIndex, partIndex;
};

#endif /* _SO_FACE_DETAIL_ */
