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
 |   $Revision $
 |
 |   Description:
 |	This file defines the SoProfile node class.
 |
 |   Author(s)		: Thad Beier, Dave Immel, Paul Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_PROFILE_
#define  _SO_PROFILE_

#include <Inventor/SbLinear.h>
#include <Inventor/elements/SoProfileElement.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/nodes/SoSubNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoProfile
//
//  Abstract base class of 2D profiles.  These profiles are used as trim
//  curves for nurbs and bevels for 3D text.  The two (so far) subclasses
//  are SoLinearProfile and SoNurbsProfile
//
//////////////////////////////////////////////////////////////////////////////

class SoProfile : public SoNode{

    SO_NODE_ABSTRACT_HEADER(SoProfile);

  public:
    enum Profile {
	START_FIRST    = SoProfileElement::START_FIRST,
	START_NEW      = SoProfileElement::START_NEW,
	ADD_TO_CURRENT = SoProfileElement::ADD_TO_CURRENT
    };

    // Fields
    SoMFInt32		index;	      // Number of vertices per profile
    SoSFEnum		linkage;      // connectivity of this curve and others

  SoEXTENDER public:
    // These action methods are implemented for profiles. Each of them
    // just adds the profile to the current state.
    virtual void	doAction(SoAction *action);
    virtual void	callback(SoCallbackAction *action);
    virtual void	GLRender(SoGLRenderAction *action);
    virtual void	getBoundingBox(SoGetBoundingBoxAction *action);
    virtual void	pick(SoPickAction *action);

    // Returns a profile as a trim curve.  numKnots is zero if the
    // curve is linear. floatsPerVec will be either 2 or 3 depending
    // on whether the curve is non-rational or rational.
    virtual void	getTrimCurve(SoState *state, int32_t &numPoints,
				     float *&points, int &floatsPerVec,
				     int32_t &numKnots, float *&knotVector) = 0;

    // Returns vertices approximating the profile
    virtual void	getVertices(SoState *state, int32_t &nVertices,
				    SbVec2f *&vertices) = 0;

  SoINTERNAL public:
    static void		initClass();

  protected:
    SoProfile();

    virtual ~SoProfile();
};

#endif /* _SO_PROFILE_ */
