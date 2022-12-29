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
 |	This file defines some macros that implement things common to
 |	many subclasses of SoAction. They may be used to make SoAction
 |	subclassing easier. In all of the macros, the "className"
 |	parameter refers to the name of the action subclass.
 |
 |   Defined macros:
 |
 |	Within class header:
 |		SO_ACTION_HEADER
 |
 |	Within class source:
 |		SO_ACTION_SOURCE
 |		SO_ACTION_INIT_CLASS
 |		SO_ACTION_CONSTRUCTOR
 |		SO_ACTION_ADD_METHOD
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_SUB_ACTION_
#define  _SO_SUB_ACTION_

#include <Inventor/actions/SoAction.h>
#include <Inventor/SbString.h>

/////////////////////////////////////////////////////////////////////////////
//
// Macros to be called within the class definition header for an action
// subclass:
//

////////////////////////////////////////////
//
// This defines type-identifier variables and methods that all
// subclasses must support. 
//

#define SO_ACTION_HEADER(className)					      \
  public:								      \
    virtual SoType		getTypeId() const;			      \
    static SoType		getClassTypeId()			      \
				    { return classTypeId; }		      \
  SoEXTENDER public:							      \
    static void 		addMethod(SoType t, SoActionMethod method)    \
				    { methods->addMethod(t, method); }	      \
    static void 		enableElement(SoType t, int stkIndex)	      \
				    { enabledElements->enable(t, stkIndex);}  \
  protected:								      \
    virtual const SoEnabledElementsList & getEnabledElements() const;	      \
    static SoEnabledElementsList *enabledElements;			      \
    static SoActionMethodList	*methods;				      \
  private:								      \
    static SoType		classTypeId

/////////////////////////////////////////////////////////////////////////////
//
// Macros to be called within the source file for a action subclass:
//

////////////////////////////////////////////
//
// This declares the static variables defined in SO_ACTION_HEADER.
//

#define SO__ACTION_VARS(className)					      \
    SoEnabledElementsList	*className::enabledElements;		      \
    SoActionMethodList		*className::methods;			      \
    SoType			className::classTypeId

////////////////////////////////////////////
//
// This implements the methods defined in SO_ACTION_HEADER.
//

#define SO__ACTION_METHODS(className)					      \
									      \
SoType									      \
className::getTypeId() const						      \
{									      \
    return classTypeId;							      \
}									      \
									      \
const SoEnabledElementsList &						      \
className::getEnabledElements() const					      \
{									      \
    return *enabledElements;						      \
}

////////////////////////////////////////////
//
// This contains the definitions necessary at file scope
//
#define SO_ACTION_SOURCE(className)					      \
    SO__ACTION_VARS(className);						      \
    SO__ACTION_METHODS(className)

////////////////////////////////////////////
//
// This initializes the type identifer variables defined in
// SO_ACTION_HEADER. This macro should be called from within
// initClass().
//

#define SO_ACTION_INIT_CLASS(className, parentClass)			      \
    enabledElements = new SoEnabledElementsList(parentClass::enabledElements);\
    methods = new SoActionMethodList(parentClass::methods);		      \
    classTypeId    = SoType::createType(parentClass::getClassTypeId(),	      \
					SO__QUOTE(className), NULL)

///////////////////////////////////////////////
//
// This is included at the beginning of
// a constructor, to do required initializations
//

#define SO_ACTION_CONSTRUCTOR(className)				      \
    traversalMethods = methods

////////////////////////////////////////////
//
// This macro can be used by action subclasses within initClass() to
// register a method to call for a specific node class. It is passed
// the name of the node class and the method to call.
//

#define SO_ACTION_ADD_METHOD(nodeClass, method)				      \
    addMethod(nodeClass::getClassTypeId(), method)

#endif /* _SO_SUB_ACTION_ */
