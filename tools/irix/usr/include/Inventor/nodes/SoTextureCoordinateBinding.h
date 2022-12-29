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
 |   $Revision $
 |
 |   Description:
 |	This file defines the SoTextureCoordinateBinding node class.
 |
 |   Author(s)		: John Rohlf
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_TEXTURE_COORDINATE_BINDING_
#define  _SO_TEXTURE_COORDINATE_BINDING_

#include <Inventor/elements/SoTextureCoordinateBindingElement.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/nodes/SoSubNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTextureCoordinateBinding
//
//  Texture coordinate binding node. This indicates how multiple texture 
//  coordinates are to be distributed over an object.
//
//  If there is a texture function defined, then neither a texture coordinate
//  nor a texture coordinate binding node is needed
//
//  Unlike normal bindings, only a few of the typical bindings make sense:
//  PER_VERTEX, and PER_VERTTEX_INDEXED
//
//////////////////////////////////////////////////////////////////////////////

class SoTextureCoordinateBinding : public SoNode {

    SO_NODE_HEADER(SoTextureCoordinateBinding);

  public:
    enum Binding {				// Binding value
	PER_VERTEX	   = SoTextureCoordinateBindingElement::PER_VERTEX,
	PER_VERTEX_INDEXED =
	    SoTextureCoordinateBindingElement::PER_VERTEX_INDEXED,

#ifndef IV_STRICT
	// Obsolete bindings:
	DEFAULT		  = PER_VERTEX_INDEXED
#endif
    };

    // Fields
    SoSFEnum		value;		// Normal binding value

    // Constructor
    SoTextureCoordinateBinding();

  SoEXTENDER public:
    virtual void	doAction(SoAction *action);
    virtual void	callback(SoCallbackAction *action);
    virtual void	GLRender(SoGLRenderAction *action);
    virtual void	pick(SoPickAction *action);

  SoINTERNAL public:
    static void		initClass();

  protected:
    virtual ~SoTextureCoordinateBinding();

    // Reads stuff into instance. Upgrades old bindings.
    virtual SbBool	readInstance(SoInput *in, unsigned short flags);
};

#endif /* _SO_TEXTURE_COORDINATE_BINDING_ */
