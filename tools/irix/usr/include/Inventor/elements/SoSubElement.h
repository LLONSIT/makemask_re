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
 |	This file defines some macros that implement things common to
 |	many subclasses of SoElement. They may be used to make SoElement
 |	subclassing easier. In all of the macros, the "className"
 |	parameter refers to the name of the element subclass.
 |
 |   Defined macros:
 |
 |	Within class header:
 |
 |		SO_ELEMENT_ABSTRACT_HEADER(className)
 |		SO_ELEMENT_HEADER(className)
 |
 |	Within class source:
 |
 |	    At file scope:
 |
 |		SO_ELEMENT_ABSTRACT_SOURCE(className)
 |		SO_ELEMENT_SOURCE(className)
 |
 |	    Class initialization (in initClass):
 |
 |		SO_ELEMENT_INIT_ABSTRACT_CLASS()
 |		SO_ELEMENT_INIT_CLASS()
 |
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_SUB_ELEMENT_
#define  _SO_SUB_ELEMENT_

#include <Inventor/elements/SoElement.h>


/////////////////////////////////////////////////////////////////////////////
//
// Macros to be called within the class definition header for a element
// subclass:
//

////////////////////////////////////////////
//
// These define type-identifier and stack index variables and methods
// that all subclasses must support.
//

//
// This one is for abstract element classes.
//
#define SO_ELEMENT_ABSTRACT_HEADER(className)				      \
  public:								      \
    static SoType	getClassTypeId()	{ return classTypeId; }	      \
    static int		getClassStackIndex()	{ return classStackIndex; }   \
  protected:								      \
    static int		classStackIndex;				      \
    className();							      \
  private:								      \
    static SoType	classTypeId

//
// This one is for non-abstract element classes.
//
#define SO_ELEMENT_HEADER(className)					      \
    SO_ELEMENT_ABSTRACT_HEADER(className);				      \
  private:								      \
    static void *createInstance()

/////////////////////////////////////////////////////////////////////////////
//
// Macros to be called within the source file for a element subclass:
//

////////////////////////////////////////////
//
// This declares the static variables defined in SO_ELEMENT_HEADER
// or SO_ELEMENT_ABSTRACT_HEADER.
//

#define SO__ELEMENT_ABSTRACT_VARS(className)				      \
SoType	className::classTypeId;						      \
int		className::classStackIndex

#define SO__ELEMENT_VARS(className)					      \
SO__ELEMENT_ABSTRACT_VARS(className)

//
// Methods on an abstract type
//
#define SO__ELEMENT_ABSTRACT_METHODS(className)				      \
									      \
className::className()							      \
{									      \
}

//
// Methods on a non-abstract type
//
#define SO__ELEMENT_METHODS(className)					      \
									      \
className::className()							      \
{									      \
    setTypeId(classTypeId);						      \
    setStackIndex(classStackIndex);					      \
}									      \
									      \
void *									      \
className::createInstance()						      \
{									      \
    return new className;						      \
}

/////////////////////////////////////////////
//
// These include all the definitions required
// at file scope
//

#define	SO_ELEMENT_ABSTRACT_SOURCE(className)				      \
    SO__ELEMENT_ABSTRACT_VARS(className);				      \
    SO__ELEMENT_ABSTRACT_METHODS(className)

#define	SO_ELEMENT_SOURCE(className)					      \
    SO__ELEMENT_VARS(className);					      \
    SO__ELEMENT_METHODS(className)

////////////////////////////////////////////
//
// This initializes the type identifer variables defined in
// SO_ELEMENT_HEADER or SO_ELEMENT_ABSTRACT_HEADER. This macro
// should be called from within initClass(). The parentClass argument
// should be the class that this subclass is derived from.
//

#define SO_ELEMENT_INIT_ABSTRACT_CLASS(className,parentClass)		      \
    do {								      \
	classTypeId = SoType::createType(parentClass::getClassTypeId(),	      \
					 SO__QUOTE(className),		      \
					 NULL);				      \
	if (parentClass::classStackIndex < 0)				      \
	    classStackIndex = createStackIndex(classTypeId);		      \
	else								      \
	    classStackIndex = parentClass::classStackIndex;		      \
    } while (0)

#define SO_ELEMENT_INIT_CLASS(className,parentClass)			      \
    do {								      \
	classTypeId = SoType::createType(parentClass::getClassTypeId(),	      \
					 SO__QUOTE(className),		      \
					 &className::createInstance);	      \
	if (parentClass::classStackIndex < 0)				      \
	    classStackIndex = createStackIndex(classTypeId);		      \
	else								      \
	    classStackIndex = parentClass::classStackIndex;		      \
    } while (0)


#endif /* _SO_SUB_ELEMENT_ */
