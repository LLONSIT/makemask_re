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
 |	The TextureCoordinatePlane.  This texture coordinate function
 |      maps object space coordinates (xyz) to texture space (st)
 |      coordinates by projecting the object space coordinates onto
 |      a plane.
 |
 |   Author(s)		: Thad Beier, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_TEXTURE_COORDINATE_PLANE_
#define  _SO_TEXTURE_COORDINATE_PLANE_

#include <Inventor/nodes/SoTextureCoordinateFunction.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFRotation.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTextureCoordinatePlane
//
//////////////////////////////////////////////////////////////////////////////

class SoTextureCoordinatePlane : public SoTextureCoordinateFunction {

    SO_NODE_HEADER(SoTextureCoordinatePlane);

  public:
    // Fields
    SoSFVec3f		directionS; // S coordinates projection direction
    SoSFVec3f		directionT; // T coordinates projection direction

    // Constructor
    SoTextureCoordinatePlane();

  SoEXTENDER public:
    void		GLRender(SoGLRenderAction *action);
    void		pick(SoPickAction *action);
    void		callback(SoCallbackAction *action);
    
    void		doAction(SoAction *action);

  SoINTERNAL public:
    static void		initClass();

  protected:
    virtual ~SoTextureCoordinatePlane();

  private:
    // Callback used internally to project a point:
    static const SbVec4f &valueCallback(void *instance,
	const SbVec3f &position, const SbVec3f &);

    // Callback used internally to send GL texgen commands:
    static void doTexgen(void *);
};

#endif /* _SO_TEXTURE_COORDINATE_PLANE_ */
