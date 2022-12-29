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
 |	This file defines the SoNurbsProfile node class.
 |
 |   Author(s)		: Thad Beier, Dave Immel, Paul Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_NURBS_PROFILE_
#define  _SO_NURBS_PROFILE_

#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/nodes/SoProfile.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoNurbsProfile
//
//
//////////////////////////////////////////////////////////////////////////////

class SoNurbsProfile : public SoProfile{

    SO_NODE_HEADER(SoNurbsProfile);

  public:
    // Fields (in addition to those inherited from parent class)
    SoMFFloat		knotVector;

    // Constructor
    SoNurbsProfile();

  SoEXTENDER public:
    // Returns a profile as a trim curve. floatsPerVec will be either
    // 2 or 3 depending on whether the curve is non-rational or
    // rational.
    virtual void	getTrimCurve(SoState *state, int32_t &numPoints,
				     float *&points, int &floatsPerVec,
				     int32_t &numKnots, float *&knotVector);

    // Returns vertices approximating the profile
    virtual void	getVertices(SoState *state, int32_t &nVertices,
				    SbVec2f *&vertices);

  SoINTERNAL public:
    static void		initClass();

  protected:
    virtual ~SoNurbsProfile();
};

#endif /* _SO_NURBS_PROFILE_ */
