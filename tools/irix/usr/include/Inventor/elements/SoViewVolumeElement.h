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
 |   $Revision: 2.3 $
 |
 |   Description:
 |	This file defines the SoViewVolumeElement class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_VIEW_VOLUME_ELEMENT
#define  _SO_VIEW_VOLUME_ELEMENT

#include <Inventor/SbLinear.h>
#include <Inventor/elements/SoReplacedElement.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoViewVolumeElement
//
//  Element that stores the current viewing volume.
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoViewVolumeElement : public SoReplacedElement {

    SO_ELEMENT_HEADER(SoViewVolumeElement);

  public:
    // Initializes element
    virtual void	init(SoState *state);

    // Sets the view volume in the state
    static void		set(SoState *state, SoNode *node,
			    const SbViewVolume &viewVolume);

    // Returns the current view volume from the state
    static const SbViewVolume &	get(SoState *state);

    // Prints element (for debugging)
    virtual void	print(FILE *fp) const;

  SoINTERNAL public:
    // Initializes the SoViewVolumeElement class
    static void		initClass();

  protected:
    SbBool		volumeWasSet;  // COMPAT 2.0 ???
    SbViewVolume	viewVolume;

    virtual ~SoViewVolumeElement();
};

#endif /* _SO_VIEW_VOLUME_ELEMENT */
