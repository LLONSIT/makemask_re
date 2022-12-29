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
 |   $Revision: 1.1 $
 |
 |   Description:
 |	This file defines the SoNormalCache class, which is used for
 |	storing generated normals.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */


#ifndef  _SO_NORMAL_CACHE
#define  _SO_NORMAL_CACHE

#include <Inventor/SbLinear.h>
#include <Inventor/caches/SoCache.h>

////////////////////////////////////////////////////////////////////////
//
//  Class SoNormalCache:
//
//  A normal cache stores a list of normals.
//
////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoNormalCache : public SoCache {

  public:
    // Constructor and destructor
    SoNormalCache(SoState *state);
    ~SoNormalCache();

    // Stores a list of normals in the cache
    void		set(int numNormals, const SbVec3f *normals);

    // Returns the number of normals and list of normals
    int			getNum() const		{ return numNormals; }
    const SbVec3f *	getNormals() const	{ return normals;    }

  private:
    int			numNormals;		// Number of normals
    const SbVec3f	*normals;		// Array of normals
};

#endif /* _SO_NORMAL_CACHE */
