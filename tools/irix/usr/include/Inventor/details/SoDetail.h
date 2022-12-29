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
 |	This file defines the (abstract) base SoDetail class.
 |
 |   Author(s)		: Dave Immel, Howard Look, Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef _SO_DETAIL_
#define _SO_DETAIL_

#include <Inventor/SoType.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoDetail
//
//  Base class for all detail classes. A detail represents extra
//  information about a point on a surface, such as an intersection
//  returned from picking along a ray (SoPickedPoint) or as a vertex
//  of a generated primitive (SoPrimitiveVertex).
//
//  The base class does not contain any useful information. It is here
//  only as an abstract class. Subclasses can add useful detail
//  information, such as a part index or nearest vertex.
//
//////////////////////////////////////////////////////////////////////////////

class SoDetail {
  public:
    // Destructor
    virtual ~SoDetail();

    // Returns type identifier for SoDetail class
    static SoType	getClassTypeId() { return classTypeId; }

    // Returns type identifier for detail
    virtual SoType	getTypeId() const = 0;

    // Returns TRUE if detail is of given type or is derived from it
    SbBool		isOfType(SoType type) const;

    // Returns an instance that is a copy of this instance. The caller
    // is responsible for deleting the copy when done.
    virtual SoDetail *	copy() const = 0;

  SoINTERNAL public:
    static void		initClass();

    // Initialize ALL Inventor detail classes
    static void		initClasses();

  protected:
    // Constructor is protected since this is an abstract class
    SoDetail();

  private:
    static SoType	classTypeId;		// Type identifier
};

#endif /* _SO_DETAIL_ */

