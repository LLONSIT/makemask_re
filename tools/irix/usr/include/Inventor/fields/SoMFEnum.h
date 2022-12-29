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
 |   Classes:
 |	SoMFEnum
 |
 |   Macros:
 |
 |	SO_NODE_SET_MF_ENUM_TYPE(fieldName, enumType)
 |	SO_ENGINE_SET_MF_ENUM_TYPE(fieldName, enumType)
 |		These assign a specific type of enum to an MFEnum field.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_MF_ENUM_
#define  _SO_MF_ENUM_

#include <Inventor/SbString.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/fields/SoSubField.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoMFEnum subclass of SoMField. This field holds enumerated types.
//  Each instance of the field must define enumeration mnemonics and
//  character strings. This stores the enumeration values as integers
//  (as allowed by C++).
//
//////////////////////////////////////////////////////////////////////////////

class SoMFEnum : public SoMField {

    // Use standard field stuff
    SO_MFIELD_HEADER(SoMFEnum, int, int);

  public:
    //
    // Some convenience functions:
    //

    // Set value from SbName or character string
    void		setValue(const SbName &name);

    // Set indexed value from SbName or character string
    void		set1Value(int index, const SbName &name);

  SoEXTENDER public:
    // Sets up value/name correspondances
    void		setEnums(int num, int *vals, SbName *names);

  SoINTERNAL public:
    static void		initClass();

  protected:
    SbBool		legalValuesSet; // TRUE if setEnums called
    int			numEnums;	// Number of enumeration values
    int			*enumValues;	// Enumeration values
    SbName		*enumNames;	// Mnemonic names of values

    // Looks up enum name, returns value. Returns FALSE if not found.
    virtual SbBool	findEnumValue(const SbName &name, int &val);

    // Looks up enum value, returns ptr to name. Returns FALSE if not found.
    virtual SbBool	findEnumName(int val, const SbName *&name) const;
};


////////////////////////////////////////////
//
//  Debugging macros (used by other macros in this file)
//  The container must have a field 'firstInstance'.
//
#ifdef DEBUG
#define SO__MF_ENUM_CHECK_DATA(vals, typeName, fieldName, containerMacroName) \
    do {								      \
	if (vals == NULL && firstInstance)				      \
	    SoDebugError::post("SO_SET_MF_ENUM_TYPE",			      \
			       "Field %s (%s, line %d): Did you forget to"    \
			       " use SO_%s_DEFINE_ENUM_VALUE(%s, ...)?",      \
			       fieldName, __FILE__, __LINE__,		      \
			       containerMacroName, typeName);		      \
    } while(0)
#else
#define SO__MF_ENUM_CHECK_DATA(vals, typeName, fieldName, containerMacroName)	while(0)
#endif
	

////////////////////////////////////////////
//
// This defines the specific type of enum expected by a particular
// SoMFEnum field.
//

#define	SO__MF_ENUM_SET_TYPE(fieldName, enumType, contMacroName, contData)    \
    do {								      \
	int _so_mf_enum_num;						      \
	int *_so_mf_enum_vals;						      \
	SbName *_so_mf_enum_names;					      \
	contData->getEnumData(SO__QUOTE(enumType),			      \
				_so_mf_enum_num,			      \
				_so_mf_enum_vals,			      \
				_so_mf_enum_names);			      \
	SO__MF_ENUM_CHECK_DATA(_so_mf_enum_vals,			      \
			       SO__QUOTE(enumType),			      \
			       SO__QUOTE(fieldName),			      \
			       contMacroName);				      \
	fieldName.setEnums(_so_mf_enum_num,				      \
			   _so_mf_enum_vals,				      \
			   _so_mf_enum_names);				      \
    } while (0)

#define SO_NODE_SET_MF_ENUM_TYPE(fieldName, enumType)			      \
    SO__MF_ENUM_SET_TYPE(fieldName,enumType,"NODE",fieldData)

#define SO_ENGINE_SET_MF_ENUM_TYPE(fieldName, enumType)			      \
    SO__MF_ENUM_SET_TYPE(fieldName,enumType,"ENGINE",inputData)

//
// End of macros
//
/////////////////////////////////////////////////////////////////////////////


#endif /* _SO_MF_ENUM_ */
