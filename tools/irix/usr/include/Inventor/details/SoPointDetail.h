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
 |	This file defines the SoPointDetail class.
 |
 |   Author(s)		: Thaddeus Beier, Dave Immel, Howard Look
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef _SO_POINT_DETAIL_
#define _SO_POINT_DETAIL_

#include <Inventor/details/SoSubDetail.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoPointDetail
//
//  Detail information about vertex-based shapes made of points. It
//  stores indices of various items that vary from point to point.
//
//////////////////////////////////////////////////////////////////////////////

class SoPointDetail : public SoDetail {

    SO_DETAIL_HEADER(SoPointDetail);

  public:
    // Constructor and destructor
    SoPointDetail();
    virtual ~SoPointDetail();

    // Returns the index of the point in the relevant coordinate node
    int32_t	getCoordinateIndex() const	{ return coordIndex; }

    // These returns the index of the material, normal, and texture
    // coordinates for the point. Note that they may not always be
    // valid indices into nodes (e.g., if normals or texture
    // coordinates are generated automatically).
    int32_t	getMaterialIndex() const	{ return materialIndex; }
    int32_t	getNormalIndex() const		{ return normalIndex; }
    int32_t	getTextureCoordIndex() const	{ return texCoordIndex; }

    // Returns an instance that is a copy of this instance. The caller
    // is responsible for deleting the copy when done.
    virtual SoDetail *	copy() const;

  SoEXTENDER public:
    // Each of these sets one of the indices in the detail
    void	setCoordinateIndex(int32_t i)	{ coordIndex	= i; }
    void	setMaterialIndex(int32_t i)	{ materialIndex	= i; }
    void	setNormalIndex(int32_t i)		{ normalIndex	= i; }
    void	setTextureCoordIndex(int32_t i)	{ texCoordIndex	= i; }

#ifndef IV_STRICT
     void      setCoordinateIndex(long i)			// System long
			{ setCoordinateIndex ((int32_t) i); }
     void      setMaterialIndex(long i)				// System long
			{ setMaterialIndex ((int32_t) i); }
     void      setNormalIndex(long i)				// System long
			{ setNormalIndex ((int32_t) i); }
     void      setTextureCoordIndex(long i)			// System long
			{ setTextureCoordIndex ((int32_t) i); }
#endif

  SoINTERNAL public:
    static void	initClass();

  private:
    int32_t	coordIndex, materialIndex, normalIndex, texCoordIndex;
};

#endif /* _SO_POINT_DETAIL_ */
