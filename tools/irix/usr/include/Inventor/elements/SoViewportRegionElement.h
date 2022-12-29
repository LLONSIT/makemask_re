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
 |	This file defines the SoViewportRegionElement class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_VIEWPORT_REGION_ELEMENT
#define  _SO_VIEWPORT_REGION_ELEMENT

#include <Inventor/SbViewportRegion.h>
#include <Inventor/elements/SoSubElement.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoViewportRegionElement
//
//  Element that stores the current viewport region, which indicates
//  which part of the window is being rendered into. This information
//  is also needed during picking and bounding box computation to
//  determine sizes/locations of screen-space objects.
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoViewportRegionElement : public SoElement {

    SO_ELEMENT_HEADER(SoViewportRegionElement);

  public:
    // Initializes element
    virtual void	init(SoState *state);

    // Sets the viewport region
    static void		set(SoState *state,
			    const SbViewportRegion &vpReg);

    // Returns current viewport region from the state
    static const SbViewportRegion & get(SoState *state);

    // Returns TRUE if the viewports match
    virtual SbBool	matches(const SoElement *elt) const;

    // Create and return a copy of this element
    virtual SoElement	*copyMatchInfo() const;

    // Prints element (for debugging)
    virtual void	print(FILE *fp) const;

  SoINTERNAL public:
    // Initializes the SoViewportRegionElement class
    static void		initClass();

  protected:
    SbViewportRegion	viewportRegion;

    // Sets the region in an instance
    virtual void	setElt(const SbViewportRegion &vpReg);

    virtual ~SoViewportRegionElement();

  private:
    static SbViewportRegion *emptyViewportRegion;
};

#endif /* _SO_VIEWPORT_REGION_ELEMENT */
