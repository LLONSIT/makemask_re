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
 |	This file defines the SoProfileElement class.
 |
 |   Author(s)		: Paul S. Strauss, Nick Thompson, Thad Beier,
 |                        Dave Immel, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_PROFILE_ELEMENT
#define  _SO_PROFILE_ELEMENT

#include <Inventor/SoLists.h>
#include <Inventor/SbLinear.h>
#include <Inventor/elements/SoAccumulatedElement.h>

class SoProfile;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoProfileElement
//
//  Element storing 2D profiles for nurbs and 3d text
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoProfileElement : public SoAccumulatedElement {

    SO_ELEMENT_HEADER(SoProfileElement);

  public:
    enum Profile {
	START_FIRST,
	START_NEW,
	ADD_TO_CURRENT
    };

    // Initializes element.
    virtual void	init(SoState *state);

    // Add to the current profile list
    static void		add(SoState *state, SoProfile *profile);

    // Overrides push() method to copy values from next instance in the stack
    virtual void	push(SoState *state);

    // Returns the current list of profile nodes from the state
    static const SoNodeList &	get(SoState *state);

    virtual void	print(FILE *fp) const;

  SoINTERNAL public:

    // Initializes the SoCoordinateElement class
    static void		initClass();

  protected:
    // list of profile nodes
    SoNodeList	        profiles;

    virtual ~SoProfileElement();
};

#endif /* _SO_PROFILE_ELEMENT */
