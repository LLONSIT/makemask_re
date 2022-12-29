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
 |	This file defines the SoPickRayElement class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_PICK_RAY_ELEMENT
#define  _SO_PICK_RAY_ELEMENT

#include <Inventor/SbLinear.h>
#include <Inventor/elements/SoSubElement.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoPickRayElement
//
//  Element that stores the current ray to use for picking. It
//  contains the world space ray information in terms of an
//  SbViewVolume. The projection point and view direction of the
//  volume represent the ray itself. The width (which equals the
//  height) represents the diameter of the picking circle in the near
//  plane. The near and far planes represent the distances to the near
//  and far planes between which valid intersections must lie.
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoPickRayElement : public SoElement {

    SO_ELEMENT_HEADER(SoPickRayElement);

  public:
    // Initializes element
    virtual void	init(SoState *state);

    // Always returns FALSE, since this element should never be a
    // criterion for cache invalidation.
    virtual SbBool	matches(const SoElement *elt) const;

    // Create and return a copy of this element
    virtual SoElement	*copyMatchInfo() const;

    // Sets the picking ray
    static void		set(SoState *state, const SbViewVolume &volume);

    // Returns the current picking ray view volume from the state
    static const SbViewVolume &	get(SoState *state);

    // Prints element (for debugging)
    virtual void	print(FILE *fp) const;

  SoINTERNAL public:
    // Initializes the SoPickRayElement class
    static void		initClass();

  protected:
    SbViewVolume	volume;		// Ray as view volume

    virtual ~SoPickRayElement();
};

#endif /* _SO_PICK_RAY_ELEMENT */
