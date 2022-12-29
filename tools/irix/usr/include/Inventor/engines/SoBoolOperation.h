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
 |	This file contains the declaration of the BoolOperation engine
 |
 |   Classes:
 |	SoBoolOperation
 |
 |   Author(s)		: Ronen Barzel
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_BOOL_OPERATION_
#define  _SO_BOOL_OPERATION_

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoMFEnum.h>
#include <Inventor/fields/SoMFBool.h>

class SoBoolOperation : public SoEngine {

    SO_ENGINE_HEADER(SoBoolOperation);
    
  public:

    enum Operation {
	    CLEAR,
	     SET,
	    A,
	NOT_A,
		 B,
		 NOT_B,
	    A_OR_B,
	NOT_A_OR_B,
	    A_OR_NOT_B,
	NOT_A_OR_NOT_B,
	    A_AND_B,
	NOT_A_AND_B,
	    A_AND_NOT_B,
	NOT_A_AND_NOT_B,
	    A_EQUALS_B,
	    A_NOT_EQUALS_B
    };

    // Inputs
    SoMFBool	a;
    SoMFBool	b;
    SoMFEnum	operation;
    
    // Output: equals a OP b
    SoEngineOutput output;	// (SoMFBool)
    SoEngineOutput inverse;	// (SoMFBool)
    
    // Constructor
    SoBoolOperation();
    
  SoINTERNAL public:

    static void initClass();

  private:

    // Destructor
    ~SoBoolOperation();

    // Evaluation method
    virtual void evaluate();
};

#endif  /* _SO_BOOL_OPERATION_ */
