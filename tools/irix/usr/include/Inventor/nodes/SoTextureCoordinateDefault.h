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
 |	TextureCoordinateDefault causes there to be no texture
 |      coordinates (either explicit from a Texture2 node or implicit
 |      from a texture coordinate function node) in the state, forcing
 |      shapes to use their own, default coordinates.
 |
 |   Author(s)		: Thad Beier, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_TEXTURE_COORDINATE_DEFAULT_
#define  _SO_TEXTURE_COORDINATE_DEFAULT_

#include <Inventor/nodes/SoTextureCoordinateFunction.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTextureCoordinateDefault
//
//////////////////////////////////////////////////////////////////////////////

class SoTextureCoordinateDefault : public SoTextureCoordinateFunction {

    SO_NODE_HEADER(SoTextureCoordinateDefault);

  public:
    // No fields.

    // Constructor
    SoTextureCoordinateDefault();

  SoEXTENDER public:
    // These action methods all just call doAction.
    void		GLRender(SoGLRenderAction *action);
    void		pick(SoPickAction *action);
    void		callback(SoCallbackAction *action);
    
    // Updates the state for any action.
    void		doAction(SoAction *action);

  SoINTERNAL public:
    static void		initClass();

  protected:
    virtual ~SoTextureCoordinateDefault();
};

#endif /* _SO_TEXTURE_COORDINATE_DEFAULT_ */
