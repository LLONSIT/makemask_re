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
 |	This file defines the SoNormalBinding node class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_NORMAL_BINDING_
#define  _SO_NORMAL_BINDING_

#include <Inventor/elements/SoNormalBindingElement.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/nodes/SoSubNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoNormalBinding
//
//  Normal binding node. This indicates how multiple surface normals are
//  to be distributed over an object.
//
//////////////////////////////////////////////////////////////////////////////

class SoNormalBinding : public SoNode {

    SO_NODE_HEADER(SoNormalBinding);

  public:
    enum Binding {
	// Whole object has same normal
	OVERALL		  = SoNormalBindingElement::OVERALL,
	// One normal for each part of object
	PER_PART	  = SoNormalBindingElement::PER_PART,
	// One normal for each part of object, indexed
	PER_PART_INDEXED  = SoNormalBindingElement::PER_PART_INDEXED,
	// One normal for each face of object
	PER_FACE	  = SoNormalBindingElement::PER_FACE,
	// One normal for each face, indexed
	PER_FACE_INDEXED  = SoNormalBindingElement::PER_FACE_INDEXED,
	// One normal for each vertex of object
	PER_VERTEX	  = SoNormalBindingElement::PER_VERTEX,
	// One normal for each vertex, indexed
	PER_VERTEX_INDEXED= SoNormalBindingElement::PER_VERTEX_INDEXED,

#ifndef IV_STRICT
	// Obsolete bindings:
	DEFAULT		  = PER_VERTEX_INDEXED,
	NONE		  = PER_VERTEX_INDEXED
#endif
    };

    // Fields
    SoSFEnum		value;		// Normal binding value

    // Constructor
    SoNormalBinding();

  SoEXTENDER public:
    virtual void	doAction(SoAction *action);
    virtual void	GLRender(SoGLRenderAction *action);
    virtual void	callback(SoCallbackAction *action);
    virtual void	pick(SoPickAction *action);

  SoINTERNAL public:
    static void		initClass();

  protected:
    virtual ~SoNormalBinding();

    // Reads stuff into instance. Upgrades old bindings.
    virtual SbBool	readInstance(SoInput *in, unsigned short flags);
};

#endif /* _SO_NORMAL_BINDING_ */
