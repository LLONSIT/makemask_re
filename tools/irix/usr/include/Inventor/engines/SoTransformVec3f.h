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
 |   $Revision: 2.0 $
 |
 |   Description:
 |	This file contains the declaration of the TransformVec3f engine
 |
 |   Classes:
 |	SoTransformVec3f
 |
 |   Author(s)		: Ronen Barzel
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_TRANSFORM_VEC3F_
#define  _SO_TRANSFORM_VEC3F_

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoMFMatrix.h>
#include <Inventor/fields/SoMFVec3f.h>

class SoTransformVec3f : public SoEngine {

    SO_ENGINE_HEADER(SoTransformVec3f);
    
  public:

    // Inputs
    SoMFVec3f	vector;
    SoMFMatrix	matrix;
    
    // Outputs
    SoEngineOutput point;	    // (SoMFVec3f) vector-matrix multiply
    SoEngineOutput direction;	    // (SoMFVec3f) direction-matrix multiply
    SoEngineOutput normalDirection; // (SoMFVec3f) direction, normalized
    
    // Constructor
    SoTransformVec3f();
    
  SoINTERNAL public:

    static void initClass();

  private:

    // Destructor
    ~SoTransformVec3f();

    // Evaluation method
    virtual void evaluate();
};

#endif  /* _SO_TRANSFORM_VEC3F_ */
