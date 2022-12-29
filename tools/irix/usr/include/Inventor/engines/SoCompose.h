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
 |	This file contains the implementation of the
 |      various composition and decomposition engines
 |
 |   Classes:
 |       SoComposeVec2f 
 |       SoComposeVec3f 
 |       SoComposeVec4f 
 |       SoComposeRotation 
 |       SoComposeRotationFromTo
 |       SoDecomposeVec2f 
 |       SoDecomposeVec3f 
 |       SoDecomposeVec4f 
 |       SoDecomposeRotation 
 |
 |   Author(s)		: Ronen Barzel
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_COMPOSE_
#define  _SO_COMPOSE_

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoMFMatrix.h>
#include <Inventor/fields/SoMFRotation.h>
#include <Inventor/fields/SoMFVec2f.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoMFVec4f.h>

// This internal macro defines the standard methods for the composition
// engines.  These are just basic engine declarations, nothing fancy. 
// The macro leaves the class header in "public:" state so it can be
// followed immediately with the composition input and output declarations.
#define SO_COMPOSE__HEADER(Name)		\
	    SO_ENGINE_HEADER(Name);		\
	  private:				\
	    ~Name();				\
	    virtual void evaluate();		\
	  public:				\
	    Name();				\
	    static void initClass()				

///////////////////////////////////////////////////////////
// 
//  Vector composition engines
// 
class SoComposeVec2f : public SoEngine {
    SO_COMPOSE__HEADER(SoComposeVec2f);
    SoMFFloat		x;	// Input
    SoMFFloat		y;	// Input
    SoEngineOutput	vector;	// Output (SoMFVec2f)
};
class SoComposeVec3f : public SoEngine {
    SO_COMPOSE__HEADER(SoComposeVec3f);
    SoMFFloat		x;	// Input
    SoMFFloat		y;	// Input
    SoMFFloat		z;	// Input
    SoEngineOutput	vector;	// Output (SoMFVec3f)
};
class SoComposeVec4f : public SoEngine {
    SO_COMPOSE__HEADER(SoComposeVec4f);
    SoMFFloat		x;	// Input
    SoMFFloat		y;	// Input
    SoMFFloat		z;	// Input
    SoMFFloat		w;	// Input
    SoEngineOutput	vector;	// Output (SoMFVec4f)
};

///////////////////////////////////////////////////////////
// 
//  Vector decomposition engines
// 
class SoDecomposeVec2f : public SoEngine {
    SO_COMPOSE__HEADER(SoDecomposeVec2f);
    SoMFVec2f		vector;	// Input
    SoEngineOutput	x;	// Output (SoMFFloat)
    SoEngineOutput	y;	// Output (SoMFFloat)
};
class SoDecomposeVec3f : public SoEngine {
    SO_COMPOSE__HEADER(SoDecomposeVec3f);
    SoMFVec3f		vector;	// Input
    SoEngineOutput	x;	// Output (SoMFFloat)
    SoEngineOutput	y;	// Output (SoMFFloat)
    SoEngineOutput	z;	// Output (SoMFFloat)
};
class SoDecomposeVec4f : public SoEngine {
    SO_COMPOSE__HEADER(SoDecomposeVec4f);
    SoMFVec4f		vector;	// Input
    SoEngineOutput	x;	// Output (SoMFFloat)
    SoEngineOutput	y;	// Output (SoMFFloat)
    SoEngineOutput	z;	// Output (SoMFFloat)
    SoEngineOutput	w;	// Output (SoMFFloat)
};

///////////////////////////////////////////////////////////
// 
//  Rotation composition engines
// 
class SoComposeRotation : public SoEngine {
    SO_COMPOSE__HEADER(SoComposeRotation);
    SoMFVec3f		axis;		// Input
    SoMFFloat		angle;		// Input
    SoEngineOutput	rotation;	// Output (SoMFRotation)
};
class SoComposeRotationFromTo : public SoEngine {
    SO_COMPOSE__HEADER(SoComposeRotationFromTo);
    SoMFVec3f		from;		// Input
    SoMFVec3f		to;		// Input
    SoEngineOutput	rotation;	// Output (SoMFRotation)
};


///////////////////////////////////////////////////////////
// 
//  Rotation decomposition engine
// 
class SoDecomposeRotation : public SoEngine {
    SO_COMPOSE__HEADER(SoDecomposeRotation);
    SoMFRotation	rotation;	// Input
    SoEngineOutput	axis;		// Output (SoMFVec3f)
    SoEngineOutput	angle;		// Output (SoMFFloat)
};


///////////////////////////////////////////////////////////
// 
//  Matrix composition engine
// 
class SoComposeMatrix : public SoEngine {
    SO_COMPOSE__HEADER(SoComposeMatrix);
    SoMFVec3f		translation;	// Input
    SoMFRotation	rotation;	// Input
    SoMFVec3f		scaleFactor;	// Input
    SoMFRotation	scaleOrientation;//Input
    SoMFVec3f		center;		// Input
    SoEngineOutput	matrix;		// Output (SoMFMatrix)
};


///////////////////////////////////////////////////////////
// 
//  Matrix decomposition engine
//
//  Note: a matrix decomposition depends on the choice of
//  center. So a "center" input is provided (with default 
//  value 0,0,0) and there is no "center" output.
// 
class SoDecomposeMatrix : public SoEngine {
    SO_COMPOSE__HEADER(SoDecomposeMatrix);
    SoMFMatrix		matrix;		// Input
    SoMFVec3f		center;		// Input
    SoEngineOutput	translation;	// Output (SoMFVec3f)
    SoEngineOutput	rotation;	// Output (SoMFRotation)
    SoEngineOutput	scaleFactor;	// Output (SoMFVec3f)
    SoEngineOutput	scaleOrientation;//Output (SoMFRotation)
};

#endif  /* _SO_COMPOSE_ */
