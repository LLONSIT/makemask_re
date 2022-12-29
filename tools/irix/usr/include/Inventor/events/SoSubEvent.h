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
 |	many subclasses of SoEvent. They may be used to make SoEvent
 |	subclassing easier. In all of the macros, the "className"
 |	parameter refers to the name of the event subclass.
 |
 |   Defined macros:
 |
 |	Within class header:
 |
 |		SO_EVENT_HEADER(className)
 |
 |	Within class source:
 |
 |	    At file scope:
 |
 |		SO_EVENT_SOURCE(className)
 |
 |	    Class initialization (initClass):
 |
 |		SO_EVENT_INIT_CLASS()
 |
 |
 |   Author(s)		: David Mott
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_SUB_EVENT_
#define  _SO_SUB_EVENT_

#include <Inventor/events/SoEvent.h>


//  *** note: many of the macros use the "do { ... } while(0)"
//  ***       hack to define multiline blocks as a single statement
//  ***       of code that can be used anywhere and ended with a semicolon

/////////////////////////////////////////////////////////////////////////////
//
// Macros to be called within the class definition header for an event
// subclass:
//

////////////////////////////////////////////
//
// These defines type-identifier and naming variables and methods that
// all subclasses and abstract subclasses must support.
//

#define SO_EVENT_HEADER()						      \
  public:								      \
    static SoType	getClassTypeId()	/* Returns class type id */   \
				    { return classTypeId; }		      \
    virtual SoType	getTypeId() const;	/* Returns type id	*/    \
  private:								      \
    static SoType	classTypeId		/* Type id		*/


/////////////////////////////////////////////////////////////////////////////
//
// Macros to be called within the source file for an event subclass:
//

////////////////////////////////////////////
//
// This declares the static variables defined in SO_EVENT_HEADER
//

#define SO__EVENT_VARS(className)					      \
    SoType		className::classTypeId


////////////////////////////////////////////
//
// Methods on the type
//

#define SO__EVENT_METHODS(className)				              \
									      \
    SoType								      \
    className::getTypeId() const					      \
    {									      \
	return classTypeId;						      \
    }


/////////////////////////////////////////////
//
// These include all the definitions required
// at file scope
//

#define	SO_EVENT_SOURCE(className)					      \
    SO__EVENT_VARS(className);						      \
    SO__EVENT_METHODS(className)


////////////////////////////////////////////
//
// This initializes the type identifer variables defined in
// SO_EVENT_HEADER . This macro should be called from within initClass().
// The parentClass argument should be the class that this subclass is
// derived from.
//

#define SO_EVENT_INIT_CLASS(className,parentClass)			      \
    classTypeId =							      \
        SoType::createType(parentClass::getClassTypeId(),		      \
		   SO__QUOTE(className))




#endif /* _SO_SUB_EVENT_ */

