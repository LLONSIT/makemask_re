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
 |	This file defines the SoClipPlaneElement class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_CLIP_PLANE_ELEMENT
#define  _SO_CLIP_PLANE_ELEMENT

#include <Inventor/SbLinear.h>
#include <Inventor/elements/SoAccumulatedElement.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoClipPlaneElement
//
//  Element that stores the current set of clipping planes, specified
//  as SbPlanes.
//
//  When a plane is added, this element gets the current model matrix
//  from the state and stores it in the instance. This allows the
//  get() method to return the clip plane in object space (the plane
//  as originally defined) or world space (after being transformed by
//  the model matrix).
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoClipPlaneElement : public SoAccumulatedElement {

    SO_ELEMENT_HEADER(SoClipPlaneElement);

  public:
    // Initializes element
    virtual void	init(SoState *state);

    // Adds a clip plane to the current set in the state
    static void		add(SoState *state, SoNode *node,
			    const SbPlane &plane);

    // Overrides push() method to copy values from next instance in the stack
    virtual void	push(SoState *state);

    // Overrides pop() method to free up planes that were added
    virtual void	pop(SoState *state, const SoElement *prevTopElement);

    // Returns the top (current) instance of the element in the state
    static const SoClipPlaneElement * getInstance(SoState *state);

    // Returns the number of planes in an instance
    int			getNum() const;

    // Returns the indexed plane an element as an SbPlane. The plane
    // can be returned in object or world space.
    const SbPlane &	get(int index, SbBool inWorldSpace = TRUE) const;

    // Prints element (for debugging)
    virtual void	print(FILE *fp) const;

  SoINTERNAL public:
    // Initializes the SoClipPlaneElement class
    static void		initClass();

  protected:
    SbPList		planes;		// List of plane structures
    int			startIndex;	// Index of 1st plane created
					// in this instance

    // Adds the clipping plane to an instance. Takes the new plane and
    // the current model matrix
    virtual void	addToElt(const SbPlane &plane,
				 const SbMatrix &modelMatrix);

    virtual ~SoClipPlaneElement();
};

#endif /* _SO_CLIP_PLANE_ELEMENT */
