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
 |	many subclasses of SoDetail. They may be used to make SoDetail
 |	subclassing easier. In all of the macros, the "className"
 |	parameter refers to the name of the detail subclass.
 |
 |   Defined macros:
 |
 |	Within class header:
 |		SO_DETAIL_HEADER
 |
 |	Within class source:
 |		SO_DETAIL_SOURCE
 |		SO_DETAIL_INIT_CLASS
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_SUB_DETAIL_
#define  _SO_SUB_DETAIL_

#include <Inventor/details/SoDetail.h>

/////////////////////////////////////////////////////////////////////////////
//
// Macros to be called within the class definition header for a detail
// subclass:
//

////////////////////////////////////////////
//
// This defines type-identifier variables and methods that all
// subclasses must support. 
//

#define SO_DETAIL_HEADER(className)					      \
  public:								      \
    virtual SoType		getTypeId() const;			      \
    static SoType		getClassTypeId() { return classTypeId; }      \
  private:								      \
    static SoType		classTypeId

/////////////////////////////////////////////////////////////////////////////
//
// Macros to be called within the source file for a detail subclass:
//

////////////////////////////////////////////
//
// This declares the static variables defined in SO_DETAIL_HEADER.
//

#define SO__DETAIL_ID_VARS(className)					      \
    SoType			className::classTypeId

////////////////////////////////////////////
//
// This implements the methods defined in SO_DETAIL_HEADER.
//

#define SO__DETAIL_ID_METHODS(className)				      \
									      \
SoType									      \
className::getTypeId() const						      \
{									      \
    return classTypeId;							      \
}

////////////////////////////////////////////
//
// This contains the definitions necessary at file scope
//
#define SO_DETAIL_SOURCE(className)					      \
    SO__DETAIL_ID_VARS(className);					      \
    SO__DETAIL_ID_METHODS(className)

////////////////////////////////////////////
//
// This initializes the type identifer variables defined in
// SO_DETAIL_HEADER. This macro should be called from within
// initClass().
//

#define SO_DETAIL_INIT_CLASS(className, parentClass)			      \
    classTypeId = SoType::createType(parentClass::getClassTypeId(),	      \
				     SO__QUOTE(className), NULL)


#endif /* _SO_SUB_DETAIL_ */
