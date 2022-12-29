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
 |	This file defines the abstract SoInterpolate class and
 |	macros used to derive classes from it, as well as the
 |	derived classes themselves.
 |
 |   Macros:
 |	SO_INTERPOLATE_HEADER
 |	SO_INTERPOLATE_SOURCE
 |	SO_INTERPOLATE_INITCLASS
 |
 |   Classes:
 |	
 |      SoInterpolate	(abstract base class)
 |      SoInterpolateFloat
 |      SoInterpolateRotation
 |      SoInterpolateVec2f
 |      SoInterpolateVec3f
 |      SoInterpolateVec4f
 |
 |   Author(s)		: Ronen Barzel
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_INTERPOLATE_
#define  _SO_INTERPOLATE_

#include <Inventor/SoDB.h>
#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoMFRotation.h>
#include <Inventor/fields/SoMFVec2f.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoMFVec4f.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoInterpolate
//
//  Abstract base class for all interpolater engines. An interpolater
//  engine interpolates linearly between two values, based on "alpha"
//  between 0 and 1.
//
//////////////////////////////////////////////////////////////////////////////

class SoInterpolate : public SoEngine {

    SO_ENGINE_ABSTRACT_HEADER(SoInterpolate);

  public:
    // derived classes will define "input0" and "input1" fields
    SoSFFloat		alpha;
    SoEngineOutput	output;

  SoINTERNAL public:
    static void		initClass();
    static void		initClasses();	// init all builtin derived classes

  protected:
    SoInterpolate();
    static int max(int a, int b) { return (a > b) ? a : b; }
    static int clamp(int i, int n) { return (i < n) ? i : n-1; }

    ~SoInterpolate();
};

/////////////////////////////////////////////////////////////////////////////
//
// These macros can be used to easily define interpolater engine
// headers and source.
//
/////////////////////////////////////////////////////////////////////////////

//
// This macro is to be used within the class definition header. It
// declares variables and methods that all interpolaters support
//

#define SO_INTERPOLATE_HEADER(className)		      		\
									\
    SO_ENGINE_HEADER(className);					\
									\
  private:								\
    ~className();							\
    virtual void	evaluate();					\
									\
  SoINTERNAL public:							\
    static void		initClass();					\
									\
  public:								\
    className()

//
// This macro is to be used within the class source. It defines the
// variables and methods declared in SO_INTERPOLATE_HEADER().
// The "interpVal" argument should be an expression that returns
// the interpolation between local variables "v0" and "v1" of type
// "valType", based on local variable "a" which is a float.
//

#define SO_INTERPOLATE_SOURCE(className, type,		 		\
			valType, defaultVal0, defaultVal1, interpVal)	\
									\
SO_ENGINE_SOURCE(className);						\
									\
className::className()							\
{									\
    SO_ENGINE_CONSTRUCTOR(className);					\
    SO_ENGINE_ADD_INPUT(alpha, (0.0));			      		\
    SO_ENGINE_ADD_INPUT(input0, defaultVal0);				\
    SO_ENGINE_ADD_INPUT(input1, defaultVal1);				\
    SO_ENGINE_ADD_OUTPUT(output, type);			      		\
    isBuiltIn = TRUE;							\
}									\
									\
className::~className()							\
{									\
}									\
									\
void									\
className::evaluate()							\
{									\
    int n0 = input0.getNum();						\
    int n1 = input1.getNum();						\
    float a = alpha.getValue();						\
    for (int i=max(n0,n1)-1; i>=0; i--) {				\
	valType v0 = input0[clamp(i,n0)];				\
	valType v1 = input1[clamp(i,n1)];				\
	SO_ENGINE_OUTPUT(output, type, set1Value(i, interpVal));	\
    }									\
}

/////////////////////////////////////////////////////////////////////////////
//
// This macro defines the initClass method for Interpolators.  It is
// separate from the _SOURCE macro so that we can put all of the
// engine's initClass methods near each other to reduce the number of
// pages touched on startup (decreasing startup time and the amount of
// memory used).
//

#define SO_INTERPOLATE_INITCLASS(className, classPrintName)		\
									\
void									\
className::initClass()							\
{									\
    SO__ENGINE_INIT_CLASS(className, classPrintName, SoInterpolate);	\
}
/////////////////////////////////////////////////////////////////////////////
//
// Interpolaters for the builtin field types.
//
/////////////////////////////////////////////////////////////////////////////

class SoInterpolateFloat : public SoInterpolate {
    SO_INTERPOLATE_HEADER(SoInterpolateFloat);
    SoMFFloat		input0;
    SoMFFloat		input1;
};

class SoInterpolateRotation : public SoInterpolate {
    SO_INTERPOLATE_HEADER(SoInterpolateRotation);
    SoMFRotation	input0;
    SoMFRotation	input1;
};

class SoInterpolateVec2f : public SoInterpolate {
    SO_INTERPOLATE_HEADER(SoInterpolateVec2f);
    SoMFVec2f		input0;
    SoMFVec2f		input1;
};

class SoInterpolateVec3f : public SoInterpolate {
    SO_INTERPOLATE_HEADER(SoInterpolateVec3f);
    SoMFVec3f		input0;
    SoMFVec3f		input1;
};

class SoInterpolateVec4f : public SoInterpolate {
    SO_INTERPOLATE_HEADER(SoInterpolateVec4f);
    SoMFVec4f		input0;
    SoMFVec4f		input1;
};

#endif /* _SO_INTERPOLATE_ */
