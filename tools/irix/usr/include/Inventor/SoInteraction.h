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
 |   $Revision: 2.0 $
 |
 |   Description:
 |	This class is used in conjunction with any Inventor interaction.
 |   The init() method must be called in order for interaction to work
 |   properly (e.g. manipulators, selection, etc.)
 |
 |   Author(s)	: David Mott
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_INTERACTION_
#define  _SO_INTERACTION_


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoInteraction
//
//  Class with one static function to initialize all interaction node classes.
//  SoInteraction::init MUST be called in order for interaction classes to
//  function. SoInteraction::init() calls SoDB::init().
//
//////////////////////////////////////////////////////////////////////////////

#include <Inventor/SbBasic.h>

class SoInteraction {
  public:
    static void		init();		// init all interaction classes
  private:
    static SbBool	initialized;	// has interaction been initialized
};

#endif /* _SO_INTERACTION_ */
