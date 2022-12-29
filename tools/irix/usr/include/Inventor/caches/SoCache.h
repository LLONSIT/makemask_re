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
 |   $Revision: 2.6 $
 |
 |   Description:
 |	This file defines the abstract SoCache class, the base class
 |	for all caches in Inventor.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_CACHE
#define  _SO_CACHE

////////////////////////////////////////////////////////////////////////
//
//  Class SoCache:
//
//  This is the base class for all types of caches. Each cache
//  maintains the following information:
//
//      A reference count, used to allow sharing of cache instances.
//      ref() and unref() methods increment and decrement the count.
//
//      An elements-used list. This is a list of elements used in the
//      cache that are set outside it. A cache is invalidated if any
//      of these elements has changed since the cache was created.
//      There is also an elements-flag array so we can quickly tell if
//      an element type has already been added to the elements-used
//      list.
//
////////////////////////////////////////////////////////////////////////

#include <Inventor/SoLists.h>

class SoElement;
class SoState;

SoEXTENDER class SoCache {

  public:

    // Constructor. Takes the state in effect when the cache is used;
    // it is assumed that the state is pushed before the cache is
    // created. 
    SoCache(SoState *state);

    // Reference/unreference
    void		ref();
    void		unref(SoState *state = NULL);

    // Adds an element to elements-used list if not already there
    void		addElement(const SoElement *elt);

    // Adds a dependency of this instance on another cache instance.
    // The default method takes care of adding dependencies from the
    // child cache.
    virtual void	addCacheDependency(const SoState *state,
					   SoCache *cache);

    // Returns TRUE if cache is valid with respect to the given state
    virtual SbBool	isValid(const SoState *state) const;

    // Assuming isValid() returns FALSE, this will return the first
    // element that is invalid (auto-caching uses this in its
    // heuristic).  Returns NULL if the cache is not invalid because
    // of an element or if the cache is valid.
    const SoElement *	getInvalidElement(const SoState *state) const;

    // Make this cache invalid
    void		invalidate();

  protected:
    // Subclasses can use this to clean up just before they are
    // deleted.  Render caches use this to free display lists.  Note
    // that the state will be NULL if the cache is no deleted during
    // the application of an action.
    virtual void	destroy(SoState *state);

    // Destructor
    virtual ~SoCache();

  private:
    SbPList		elementsUsed;		// Elements used in cache
    unsigned char	*elementsUsedFlags;	// Which elements on list

    int			refCount;		// Reference count
    int			invalidated;		// True if invalidate called
    int			depth;			// Depth of state
};

#endif /* _SO_CACHE */
