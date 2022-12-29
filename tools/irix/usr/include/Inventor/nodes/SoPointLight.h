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
 |   $Revision: 2.2 $
 |
 |   Description:
 |	This file defines the SoPointLight node class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_POINT_LIGHT_
#define  _SO_POINT_LIGHT_

#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/nodes/SoLight.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoPointLight
//
//  Point light source node. A point light illuminates in all
//  directions from a given point in space.
//
//////////////////////////////////////////////////////////////////////////////

class SoPointLight : public SoLight {

    SO_NODE_HEADER(SoPointLight);

  public:
    // Fields (in addition to those in SoLight):
    SoSFVec3f		location;	// Source location

    // Constructor
    SoPointLight();

  SoEXTENDER public:
    // Creates a light source during rendering
    virtual void	GLRender(SoGLRenderAction *action);

  SoINTERNAL public:
    static void		initClass();

  protected:
    virtual ~SoPointLight();
};

#endif /* _SO_POINT_LIGHT_ */
