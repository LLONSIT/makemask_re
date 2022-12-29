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
 |   Description:
 |	This file defines the SoGLCoordinateElement class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_GL_COORDINATE_ELEMENT
#define  _SO_GL_COORDINATE_ELEMENT

#include <Inventor/elements/SoCoordinateElement.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoGLCoordinateElement
//
//  Element that stores the current coordinates. Adds methods to
//  send the surface coordinate to GL on demand. The coordinates are
//  sent in the appropriate form, depending on whether they are stored
//  as 3-D or 4-D values.
//
//  Note that this class relies on SoCoordinateElement to store the
//  coordinates in the instance.
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoGLCoordinateElement : public SoCoordinateElement {

    SO_ELEMENT_HEADER(SoGLCoordinateElement);

  public:
    // Sends indexed coordinate to GL
    void		send(int index) const;

  SoINTERNAL public:
    // Initializes the SoGLCoordinateElement class
    static void		initClass();

  protected:
    virtual ~SoGLCoordinateElement();
};

#endif /* _SO_GL_COORDINATE_ELEMENT */
