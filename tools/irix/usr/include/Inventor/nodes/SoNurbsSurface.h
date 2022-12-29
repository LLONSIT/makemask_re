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
 |   $Revision: 2.6 $
 |
 |   Description:
 |	This file defines the SoNurbsSurface node class.
 |
 |   Author(s)		: Dave Immel
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_NURBS_SURFACE_
#define  _SO_NURBS_SURFACE_

#include <Inventor/SbLinear.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/nodes/SoShape.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoNurbsSurface
//
//  NURBS surface. The surface consists of two knot vectors and orders for
//  the U and V parametric directions.  The control points for the surface
//  are obtained from the current coordinates.  There are also orders and
//  knot vectors for the S and T (texture) coordinates
//
//////////////////////////////////////////////////////////////////////////////

class SoState;
class SoPrimitiveVertex;
class _SoNurbsNurbsTessellator;

class SoNurbsSurface : public SoShape {

    SO_NODE_HEADER(SoNurbsSurface);

  public:
    // Fields
    SoSFInt32		numUControlPoints; // Number of control points in
    SoSFInt32		numVControlPoints; // the U and V directions.
    SoSFInt32		numSControlPoints; // Number of control points in
    SoSFInt32		numTControlPoints; // the S and T directions
    SoMFFloat		uKnotVector;       // The knot vectors in the U and
    SoMFFloat		vKnotVector;       // V directions.
    SoMFFloat		sKnotVector;       // The knot vectors in the S and
    SoMFFloat		tKnotVector;       // T directions.

    // Constructor
    SoNurbsSurface();

  SoEXTENDER public:
    virtual void	GLRender(SoGLRenderAction *action);
    virtual void	rayPick(SoRayPickAction *action);

  SoINTERNAL public:
    static void		initClass();

    void                sendPrimitive(SoAction *, SoPrimitiveVertex *);

  protected:
    // Generates triangles representing a surface
    virtual void	generatePrimitives(SoAction *action);

    // Computes bounding box of surface
    virtual void	computeBBox(SoAction *action, SbBox3f &box,
				    SbVec3f &center);

    ~SoNurbsSurface();

  private:
    // Renders the surface
    void                drawNURBS(_SoNurbsNurbsTessellator *render, SoState *state,
				  SbBool doTextures);

    // Matrix operations for level of detail and culling
    void                calcTotalMatrix( SoState *state, SbMatrix &totalMat );
    void                multMatrix4d( SbMatrix &n, SbMatrix left, 
				      SbMatrix right );

    // This callback gets details from the NURBS library
    static void         primCB(SoAction *, SoPrimitiveVertex *, void *);
};

#endif /* _SO_NURBS_SURFACE_ */
