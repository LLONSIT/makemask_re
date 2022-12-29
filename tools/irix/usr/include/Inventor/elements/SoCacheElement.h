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
 |   $Revision: 2.5 $
 |
 |   Classes:
 |	SoCacheElement
 |
 |   Author(s)		: Paul S. Strauss, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_CACHE_ELEMENT_
#define  _SO_CACHE_ELEMENT_

#include <Inventor/elements/SoSubElement.h>

class SoCache;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoCacheElement
//
//  Element that stores the most recently opened cache.
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoCacheElement : public SoElement {

    SO_ELEMENT_HEADER(SoCacheElement);

  public:
    // Initializes element
    virtual void	init(SoState *state);

    // Sets cache in element accessed from state
    static void		set(SoState *state, SoCache *cache);

    // Returns the cache stored in an instance. This may be NULL.
    SoCache *		getCache() const { return cache; }

    // Returns TRUE if any cache is currently open in the state
    static SbBool	anyOpen(SoState *state);

    // Invalidate any open caches.  This is called by nodes that
    // should not be cached.
    static void		invalidate(SoState *state);

    // Overrides this method to unref cache
    virtual void	pop(SoState *state, const SoElement *prevTopElement);

    // Overrides this method to print an error message and return
    // FALSE. Cache elements should never be compared, since they
    // never appear in the elements-used list of caches!
    virtual SbBool	matches(const SoElement *elt) const;

    // Copy method prints error and returns NULL; see comment above.
    virtual SoElement	*copyMatchInfo() const;

    // Returns the next cache element in the stack
    SoCacheElement *	getNextCacheElement() const
	{ return (SoCacheElement *) getNextInStack(); }

  SoINTERNAL public:
    // Initializes the SoCacheElement class
    static void		initClass();

    // Adds the given element to the elements used lists of all
    // currently open caches in the state
    static void		addElement(SoState *state, const SoElement *elt);

    // Adds a dependency on the given cache to all currently open
    // caches in the state
    static void		addCacheDependency(SoState *state, SoCache *cache);

    // Sets invalidated bit, and returns its old value.  Used by
    // SoGLCacheList so auto-caching doesn't cache too much.
    static SbBool	setInvalid(SbBool newValue);

    // returns the current cache, from the top of the stack.  Does not
    // cause a cache dependence like getConstElement().
    static SoCache *	getCurrentCache(SoState *state)
	{return ((SoCacheElement*)(state->getElementNoPush(classStackIndex)))->cache;}

    virtual ~SoCacheElement();

  private:
    SoCache		*cache;			// Stores pointer to cache

    static SbBool	invalidated;		// invalidate() called?

friend class SoElement;
};

#endif /* _SO_CACHE_ELEMENT_ */
