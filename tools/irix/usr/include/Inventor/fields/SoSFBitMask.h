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
 |	SoSFBitMask
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_SF_BIT_MASK_
#define  _SO_SF_BIT_MASK_

#include <Inventor/fields/SoSFEnum.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFBitMask subclass of SoSField.
//
//////////////////////////////////////////////////////////////////////////////

class SoSFBitMask : public SoSFEnum {

    // Use standard field stuff for derived class;
    // the rest is inherited from SoSFEnum
    SO_SFIELD_DERIVED_HEADER(SoSFBitMask, int, int);

    // Inherits other stuff from Enum field

  protected:
    // Looks up enum name, returns value. Returns FALSE if not found.
    virtual SbBool	findEnumValue(const SbName &name, int &val);

  SoINTERNAL public:
    static void		initClass();
};

#endif /* _SO_SF_BIT_MASK_ */
