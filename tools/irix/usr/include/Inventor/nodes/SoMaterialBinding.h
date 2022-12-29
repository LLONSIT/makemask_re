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
 |	This file defines the SoMaterialBinding node class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_MATERIAL_BINDING_
#define  _SO_MATERIAL_BINDING_

#include <Inventor/elements/SoMaterialBindingElement.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/nodes/SoSubNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoMaterialBinding
//
//  Material binding node. This indicates how multiple materials are
//  to be distributed over an object.
//
//////////////////////////////////////////////////////////////////////////////

class SoMaterialBinding : public SoNode {

    SO_NODE_HEADER(SoMaterialBinding);

  public:
    enum Binding {
	// Whole object has same material
	OVERALL		  = SoMaterialBindingElement::OVERALL,
	// One material for each part of object
	PER_PART	  = SoMaterialBindingElement::PER_PART,
	// One material for each part of object, indexed
	PER_PART_INDEXED  = SoMaterialBindingElement::PER_PART_INDEXED,
	// One material for each face of object
	PER_FACE	  = SoMaterialBindingElement::PER_FACE,
	// One material for each face, indexed
	PER_FACE_INDEXED  = SoMaterialBindingElement::PER_FACE_INDEXED,
	// One material for each vertex of object
	PER_VERTEX	  = SoMaterialBindingElement::PER_VERTEX,
	// One material for each vertex, indexed
	PER_VERTEX_INDEXED= SoMaterialBindingElement::PER_VERTEX_INDEXED,

#ifndef IV_STRICT
	// Obsolete bindings:
	DEFAULT		  = OVERALL,
	NONE		  = OVERALL
#endif
    };

    // Fields
    SoSFEnum		value;		// Material binding value

    // Constructor
    SoMaterialBinding();

  SoEXTENDER public:
    virtual void	doAction(SoAction *action);
    virtual void	GLRender(SoGLRenderAction *action);
    virtual void	callback(SoCallbackAction *action);
    virtual void	pick(SoPickAction *action);

  SoINTERNAL public:
    static void		initClass();

  protected:
    virtual ~SoMaterialBinding();

    // Reads stuff into instance. Upgrades old bindings.
    virtual SbBool	readInstance(SoInput *in, unsigned short flags);
};

#endif /* _SO_MATERIAL_BINDING_ */
