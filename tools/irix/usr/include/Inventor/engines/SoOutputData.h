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
 |	Definition of the SoEngineOutputData class, which is used by
 |	engines to store information about their outputs.  Based on
 |	SoFieldData.
 |
 |   Author(s)		: Paul S. Strauss, Nick Thompson, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */


#ifndef  _SO_OUTPUT_DATA_
#define  _SO_OUTPUT_DATA_

#include <Inventor/misc/SoBasic.h>
#include <Inventor/SbPList.h>
#include <Inventor/SbString.h>
#include <Inventor/SoType.h>

class SoEngine;
class SoFieldContainer;
class SoInput;
class SoOutput;
class SoEngineOutput;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoEngineOutputData
//
//  The SoEngineOutputData class holds data about engine outputs: the
//  number of outputs the engine has, the names of the outputs.
//
//  All engines of a given class share the same output data. Therefore,
//  to get information about a particular output in a particular engine
//  instance, it is necessary to pass that instance to the appropriate
//  method.
//
//////////////////////////////////////////////////////////////////////////////

SoINTERNAL class SoEngineOutputData {
  public:
    // Default constructor
    SoEngineOutputData() { }

    SoEngineOutputData(const SoEngineOutputData *);

    // Constructor that takes number of fields as a hint
    SoEngineOutputData(int numOutputs) : outputs(numOutputs)
	{ }

    // Destructor
    ~SoEngineOutputData();

    // Adds an output to current data, given name of output,
    // a pointer to field within the engine, and the type of output.
    void		addOutput(const SoEngine *defEngine,
				  const char *outputName,
				  const SoEngineOutput *output,
				  SoType type);

    // Returns number of outputs
    int			getNumOutputs() const	{ return outputs.getLength(); }

    // Returns name of output with given index
    const SbName &	getOutputName(int index) const;

    // Returns pointer to output with given index within given object instance
    SoEngineOutput *	getOutput(const SoEngine *engine,
				  int index) const;

    // Returns index of output, given the output and the engine it
    // is in.
    int			getIndex(const SoEngine *engine,
				 const SoEngineOutput *output) const;

    // Returns type of output with given index
    const SoType &	getType(int index) const;

    // Methods to read and write the output descriptions
    SbBool		readDescriptions(SoInput *in,
					 SoEngine *engine) const;
    void		writeDescriptions(SoOutput *out,
					 SoEngine *engine) const;
  private:
    SbPList		outputs;	// List of outputs (SoOutputEntry)
};    

#endif /* _SO_OUTPUT_DATA_ */
