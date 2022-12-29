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
 |	This file defines the SoCylinderDetail class.
 |
 |   Author(s)		: Thaddeus Beier, Dave Immel, Howard Look
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef _SO_CYLINDER_DETAIL_
#define _SO_CYLINDER_DETAIL_

#include <Inventor/details/SoSubDetail.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoCylinderDetail
//
//  Detail about an SoCylinder node. It contains a bitmask indicating
//  the part of the cylinder.
//
//////////////////////////////////////////////////////////////////////////////

class SoCylinderDetail : public SoDetail {

    SO_DETAIL_HEADER(SoCylinderDetail);

  public:
    // Constructor and destructor
    SoCylinderDetail();
    virtual ~SoCylinderDetail();

    // Returns the part of detail for this shape, as one of the part masks
    // of SoCylinder.
    int			getPart() const			{ return part; }

    // Returns an instance that is a copy of this instance. The caller
    // is responsible for deleting the copy when done.
    virtual SoDetail *	copy() const;

  SoEXTENDER public:
    // Sets the part of detail for the shape
    void		setPart(int _part)		{ part = _part; }

  SoINTERNAL public:
    static void		initClass();
    
  protected:
    int part;
};

#endif /* _SO_CYLINDER_DETAIL_ */
