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
 |	This file defines the SoBoundingBoxCache class, which is used for
 |	storing caches during GL rendering.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */


#ifndef  _SO_BOUNDING_BOX_CACHE
#define  _SO_BOUNDING_BOX_CACHE

#include <Inventor/SbBox.h>
#include <Inventor/caches/SoCache.h>

////////////////////////////////////////////////////////////////////////
//
//  Class SoBoundingBoxCache:
//
//  A bounding box cache stores a bounding box and center point. It
//  also stores a flag indicating whether the box contains any line or
//  point objects, meaning that intersection tests with the box should
//  use a little extra leeway.
//
////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoBoundingBoxCache : public SoCache {

  public:
    // Constructor and destructor
    SoBoundingBoxCache(SoState *state);
    ~SoBoundingBoxCache();

    // Stores a bounding box and center point in the cache
    void		set(const SbXfBox3f &boundingBox,
			    SbBool centerSet,
			    const SbVec3f &centerPoint);

    const SbXfBox3f &	getBox() const		{ return box; }

    const SbBox3f &	getProjectedBox() const	{ return projectedBox; }

    // Returns TRUE if the center is valid.
    SbBool		isCenterSet() const	{ return centerSet; }
	

    // Returns the center (in object space)
    const SbVec3f &	getCenter() const	{ return center; }

    // Sets the hasLinesOrPoints flag to TRUE in all open bounding box
    // caches in the given state. (The flag is FALSE by default.)
    static void		setHasLinesOrPoints(SoState *state);

    // Returns the hasLinesOrPoints flag
    SbBool		hasLinesOrPoints() const	 { return hasLOrP; }

  private:
    SbXfBox3f		box;		// Bounding box
    SbBox3f		projectedBox;	// Box in local space
    SbBool		centerSet;	// If the center was set
    SbVec3f		center;		// Center point
    SbBool		hasLOrP;	// TRUE if contains lines or points
};

#endif /* _SO_BOUNDING_BOX_CACHE */
