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
 |	This file contains the declaration of the Calculator engine
 |
 |   Classes:
 |	SoCalculator
 |
 |   Author(s)		: Ronen Barzel
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_CALCULATOR_
#define  _SO_CALCULATOR_

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoMFVec3f.h>

class SoCalcParser;

class SoCalculator : public SoEngine {

    SO_ENGINE_HEADER(SoCalculator);
    
  public:

    // Inputs
    SoMFFloat	a,b,c,d,e,f,g,h;
    SoMFVec3f	A,B,C,D,E,F,G,H;
    SoMFString	expression;
    
    // Outputs
    SoEngineOutput oa,ob,oc,od;	// (SoMFfloat)
    SoEngineOutput oA,oB,oC,oD;	// (SoMFVec3f)
    
    // Constructor
    SoCalculator();

  SoINTERNAL public:

    static void initClass();

  protected:
    virtual void	inputChanged(SoField *whichInput);

  private:
    // Destructor
    ~SoCalculator();

    // Evaluation method
    virtual void evaluate();

    SoCalcParser	*parser;
    SbBool		reparse;

    // working storage for the evaluation
    float	va, vb, vc, vd, ve, vf, vg, vh, ova, ovb, ovc, ovd;
    float	ta, tb, tc, td, te, tf, tg, th;
    SbVec3f	vA, vB, vC, vD, vE, vF, vG, vH, ovA, ovB, ovC, ovD;
    SbVec3f	tA, tB, tC, tD, tE, tF, tG, tH;
    static float *lookupFloat(void *, const char *);
    static SbVec3f *lookupVec3f(void *, const char *);
};

#endif  /* _SO_CALCULATOR_ */
