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
 |	This file defines the abstract SoFieldConverter base class.
 |
 |   Author(s)		: Paul S. Strauss, Ronen Barzel
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_FIELD_CONVERTER_
#define  _SO_FIELD_CONVERTER_

#include <Inventor/SoDB.h>
#include <Inventor/engines/SoSubEngine.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoFieldConverter
//
//  Abstract base class for all field converter engines. A field
//  converter engine is used to convert the value of a field of one
//  type to another. These engines are registered with the global
//  database so connections between fields of different types can be
//  made by automatically inserting a converter instance.
//  A single class of converter engine may be registered for several
//  different conversions.
//  Field converters are never written to file
//  (SoField::writeConnection takes care of that).
//
//////////////////////////////////////////////////////////////////////////////


SoEXTENDER class SoFieldConverter : public SoEngine {

    SO_ENGINE_ABSTRACT_HEADER(SoFieldConverter);

  public:
    // These must be defined in each subclass. They return the input
    // and output connections of the given types.
    virtual SoField *		getInput(SoType type)  = 0;
    virtual SoEngineOutput *	getOutput(SoType type) = 0;

    // Returns the input that is connected.  By default, this searches
    // through the field data for the field that is connected;
    // you can redefine to make more efficient.
    virtual SoField *		getConnectedInput();

  SoINTERNAL public:
    static void		initClass();
    static void		initClasses();	// init all builtin converters

    // Adds all fields connected from the output of the converter to
    // the given list
    int			getForwardConnections(SoFieldList &list) const;

  protected:
    SoFieldConverter();

    ~SoFieldConverter();
};

#endif /* _SO_FIELD_CONVERTER_ */
