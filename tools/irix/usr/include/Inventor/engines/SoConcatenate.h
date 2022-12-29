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
 |   $Revision: 2.4 $
 |
 |   Description:
 |	This file defines the "concatenation" engine that joins
 |	together several (up to 10) fields.  Its inputs are several
 |      multi-valued fields (automatic field conversion will do the
 |      right thing, so you can attach single-valued fields) of the
 |      same type, output is a multi-value field of the same type.
 |
 |      If you need to concatenate more than 10 fields together,
 |      concatenate the outputs of several of these into yet another
 |      concatenate engine.
 |
 |   Classes:
 |	SoConcatenate
 |
 |   Author(s)		: Ronen Barzel, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_CONCATENATE_
#define  _SO_CONCATENATE_

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFName.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoConcatenate
//
//  Concatenate several fields together into one big field.
//
//////////////////////////////////////////////////////////////////////////////

class SoMField;

class SoConcatenate : public SoEngine {

    SO_ENGINE_HEADER(SoConcatenate);

  public:
    // Constructor, takes a subclass of SoMField.
    SoConcatenate(SoType mfInputType);

    // Inputs; connect them like this:
    //    concatenate->input[0]->connectFrom(...)
    // The names of these inputs is input0 ... input9.
    // The default value for these fields is no values.
    SoMField *input[10];

    // Output.  Is of the same type as the inputs (note that it is a
    // pointer, unlike most engine outputs).
    SoEngineOutput *output;

  SoINTERNAL public:
    // Initializes engine class
    static void		initClass();

  protected:

    virtual SoFieldContainer *	copyThroughConnection() const;
  
  private:
    // Constructor/Destructor.  This constructor is used only when
    // reading these from file.
    SoConcatenate();
    ~SoConcatenate();

    // Concatenate engines must write out their input type before writing
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

#endif /* _SO_CONCATENATE_ */
