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
 |   $Revision: 2.3 $
 |
 |   Description:
 |	This file defines the SoLinearProfile node class.
 |
 |   Author(s)		: Thad Beier, Dave Immel, Paul Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_LINEAR_PROFILE_
#define  _SO_LINEAR_PROFILE_

#include <Inventor/nodes/SoProfile.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoLinearProfile
//
//  Piecwise linear 2D profile. The profile is defined as line
//  segments between the current profile coordinates.
//
//////////////////////////////////////////////////////////////////////////////

// This value, when used as the last value of the index field, 
// the coordinates, starting from the last index+1 (zero if there is
// only one value in the index field).
#define SO_LINEAR_PROFILE_USE_REST_OF_VERTICES	(-1)

class SoLinearProfile : public SoProfile{

    SO_NODE_HEADER(SoLinearProfile);

  public:
    // Inherits all fields from parent class

    // Constructor
    SoLinearProfile();

  SoEXTENDER public:
    // Returns a profile as a trim curve.  numKnots will be zero.
    // floatsPerVec will be either 2 or 3 depending on whether the
    // curve is non-rational or rational.
    virtual void	getTrimCurve(SoState *state, int32_t &numPoints,
				     float *&points, int &floatsPerVec,
				     int32_t &numKnots, float *&knotVector);

    // Returns vertices defining the profile
    virtual void	getVertices(SoState *state, int32_t &nVertices,
				    SbVec2f *&vertices);

  SoINTERNAL public:
    static void		initClass();

  protected:
    virtual ~SoLinearProfile();
};

#endif /* _SO_LINEAR_PROFILE_ */
