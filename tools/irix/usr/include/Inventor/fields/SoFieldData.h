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
 |   $Revision: 2.3 $
 |
 |   Description:
 |	Definition of the SoFieldData class, which is used by all objects
 |	that have fields.
 |
 |   Author(s)		: Paul S. Strauss, Nick Thompson, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */


#ifndef  _SO_FIELD_DATA_
#define  _SO_FIELD_DATA_

#include <Inventor/misc/SoBasic.h>
#include <Inventor/SbPList.h>
#include <Inventor/SbString.h>

class SoField;
class SoInput;
class SoFieldContainer;
class SoOutput;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoFieldData
//
//  The SoFieldData class holds data about fields of an object: the
//  number of fields the object has, the names of the fields, and a
//  pointer to a prototype instance of the field. (Typically, this
//  prototype field is contained within a prototype instance of the
//  node or engine.)
//
//  All objects of a given class share the same field data. Therefore,
//  to get information about a particular field in a particular object
//  instance, it is necessary to pass that instance to the appropriate
//  method.
//
//////////////////////////////////////////////////////////////////////////////

SoINTERNAL class SoFieldData {
  public:
    // Constructor
    SoFieldData() {}

    // Copy constructors
    SoFieldData(const SoFieldData &);
    SoFieldData(const SoFieldData *);

    // Constructor that takes number of fields as a hint
    SoFieldData(int numFields) : fields(numFields) {}

    // Destructor
    ~SoFieldData();

    // Adds a field to current data, given default value object, name of
    // field and pointer to field within default value object. This is
    // used to define fields of a FieldContainer (node or engine) class.
    void		addField(SoFieldContainer *defObject,
				 const char *fieldName,
				 const SoField *field);

    // Copy values and flags of fields from one object to another (of
    // the same type). If copyConnections is TRUE, any connections to
    // the fields are copied as well
    void		overlay(SoFieldContainer *to,
				const SoFieldContainer *from,
				SbBool copyConnections) const;

    // Returns number of fields
    int			getNumFields() const	{ return fields.getLength(); }

    // Returns name of field with given index
    const SbName &	getFieldName(int index) const;

    // Returns pointer to field with given index within given object instance
    SoField *		getField(const SoFieldContainer *object,
				 int index) const;

    // Returns index of field, given the field and the instance it is in
    int			getIndex(const SoFieldContainer *fc,
				 const SoField *field) const;

    // Enum name/value mechanism
    void		addEnumValue(const char *typeName,
				     const char *valName, int val);
    void		getEnumData(char *typeName, int &num,
				    int *&vals, SbName *&names);

  SoINTERNAL public:

    // Reads into fields according to SoInput. The third
    // parameter indicates whether an unknown field should be reported
    // as an error; this can be FALSE for nodes that have children.
    // The last argument will be set to TRUE if a description of the
    // fields (using the "inputs" or "fields" keywords) was read.
    SbBool		read(SoInput *in, SoFieldContainer *object,
			     SbBool errorOnUnknownField,
			     SbBool &notBuiltIn) const;

    // This function is used when the field name has already been
    // read, and just the value needs to be read in.  It is used by
    // the above read() method and to read in GlobalFields.  It
    // returns TRUE if there were no problems reading, and will return
    // FALSE in 'foundName' if the given name is not the name of one
    // of the fields in the fieldData.
    SbBool		read(SoInput *in, SoFieldContainer *object,
			     const SbName &fieldName,
			     SbBool &foundName) const;

    // Writes all fields of object according to SoOutput
    void		write(SoOutput *out,
			      const SoFieldContainer *object) const;

    // Copies all fields from given field data into this one, creating
    // new fields for them
    void		copy(const SoFieldData *from);

    // Returns TRUE if the values in the fields of one container are
    // the same as those in another (of the same type)
    SbBool		isSame(const SoFieldContainer *c1,
			       const SoFieldContainer *c2) const;

    // Read field type information
    SbBool		readFieldDescriptions(
				SoInput *in, SoFieldContainer *object,
				int numDescriptionsExpected) const;

    // Write field type information
    void		writeFieldDescriptions(
				SoOutput *out,
				const SoFieldContainer *object) const;

  private:
    // Used by binary reading to read in all the fields:
    SbBool		readFields(
				SoInput *in, SoFieldContainer *object,
				int numFieldsWritten) const;

    SbPList		fields;		// List of fields (SoFieldEntry)
    SbPList		enums;		// List of enums (SoEnumEntry)
};    

#endif /* _SO_FIELD_DATA_ */
