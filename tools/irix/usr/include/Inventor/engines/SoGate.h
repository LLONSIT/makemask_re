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
 |	This file defines the SoGate class.
 |
 |   Author(s)		: Ronen Barzel, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_GATE_
#define  _SO_GATE_

#include <Inventor/SoDB.h>
#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFName.h>
#include <Inventor/fields/SoSFTrigger.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoGate
//
//  Gate engine class. A gate engine copies its input to its output,
//  when the "enable" field is true.  It will also do a one-time copy
//  when the trigger field is touched.
//
//////////////////////////////////////////////////////////////////////////////


class SoGate : public SoEngine {

    SO_ENGINE_HEADER(SoGate);

  public:
    // Constructor takes a subclass of SoMField.
    SoGate(SoType mfInputType);

    SoSFBool		enable;		// enable continuous flow-through
    SoSFTrigger		trigger;	// copy a single value

    // Note that unlike most engines the input field is a pointer.
    // The default value for this field is no values.
    SoMField		*input;

    // Note that unlike most engines the output is a pointer.  The
    // type of the output is the same as the input.
    SoEngineOutput	*output;

  SoINTERNAL public:
    static void		initClass();

  protected:

    virtual void	inputChanged(SoField *whichInput);

    virtual SoFieldContainer *	copyThroughConnection() const;
  
  private:
    SoGate();
    ~SoGate();

    // gate engines must write out their input type before writing
    // their fields, so these are overridden:
    virtual SbBool	readInstance(SoInput *in, unsigned short flags);
    virtual void	writeInstance(SoOutput *out);

    void		setup(SoType);

    virtual void	evaluate();

    int conversionCase;

    SoFieldData *myInputData;
    SoEngineOutputData *myOutputData;

    SoSFName typeField; // Used when reading/writing
};

#endif /* _SO_GATE_ */
