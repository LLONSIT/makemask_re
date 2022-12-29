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
 |   Classes:
 |	SoSFColor
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_SF_COLOR_
#define  _SO_SF_COLOR_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbColor.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFColor subclass of SoSField.
//
//////////////////////////////////////////////////////////////////////////////

class SoSFColor : public SoSField {

    // Use standard field stuff
    SO_SFIELD_HEADER(SoSFColor, SbColor, const SbColor &);

  public:

    //
    // Some additional convenience functions
    //

    // Set RGB color from SbVec3f
    void		setValue(const SbVec3f &vec);

    // Set RGB/HSV value from 3 floats
    void		setValue(float r, float g, float b);

    void		setHSVValue(float h, float s, float v);

    // Set RGB/HSV value from array of 3 floats
    void		setValue(const float rgb[3]);

    void		setHSVValue(const float hsv[3]);

  SoINTERNAL public:
    static void		initClass();
};

#endif /* _SO_SF_COLOR_ */
