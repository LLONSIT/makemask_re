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
 |	This file defines the SoGLCacheList class, which can be used
 |      is used by nodes like Separator to maintain a list of render
 |      caches that might be used.  It also implements an auto caching
 |      scheme that tries to be smart about only building caches when
 |      things are not changing.
 |
 |   Typical use:
 |      In a node's GLRender method:
 |         if (cacheList->call(state)) return;
 |         cacheList->open(state, TRUE);
 |         ... do normal children stuff...
 |         cacheList->close();
 |
 |     In a node's notify method:
 |         cacheList->invalidateAll();
 |
 |   Author(s)		: Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */


#ifndef  _SO_GL_CACHE_LIST
#define  _SO_GL_CACHE_LIST

#include <Inventor/SbBasic.h>


struct SoGLCacheListEntry;
class SoGLRenderAction;
class SoState;
class SoElement;

SoEXTENDER class SoGLCacheList {
    
  public:
    // Constructor.  Takes the maximum number of caches to build.
    SoGLCacheList(int numCaches = 2);

    // Destructor.
    ~SoGLCacheList();
    
    // Given an SoGLRenderAction, try to use one of the caches we've
    // built.  If none of the caches can be used, this returns FALSE.
    // If this returns TRUE, then a cache has been called and all the
    // GL commands in it have already been done.
    SbBool call(SoGLRenderAction *);
    
    // Open a new cache, maybe.  If the autoCache flag is TRUE, a
    // heuristic will be used to figure out whether or not caching
    // should be done (based on when caches were built, when they were
    // used, etc).  If the flag is FALSE, always try to open a cache
    // (and possibly delete an old cache).
    void open(SoGLRenderAction *, SbBool autoCache = TRUE);

    // Close an open cache, if any.  If open() didn't open a cache,
    // this routine does nothing.
    void close(SoGLRenderAction *);
    
    // Mark all caches as invalid.  This should be called when a node
    // is notified of changes in its children or fields.
    void invalidateAll();
    
  private:
    SoGLCacheListEntry *getLRU();
    void setMRU(SoGLCacheListEntry *e);
    void setLRU(SoGLCacheListEntry *e);
    void blow(SoState *, SoGLCacheListEntry *);

    // MRU is the head of a looped list of caches.  Every time
    // a cache is used, it is added to the front of the list.  When we
    // decide to replace a cache, the end cache on the list is used.
    SoGLCacheListEntry *MRU;
    int maxCaches, numCaches;
    SoGLCacheListEntry *openCache;
    int threshold;	// Number of frames to wait before trying to
			// build a cache.  This is increased when caches
			// are found to be invalid, and decreased when a
			// cache is successfully used.
    int mightBeUsed;	// When we can't use a cache, this counts the
			// number of times open() is called and we
			// think we might have been able to use a cache, if
    			// there was one built.  The bigger this gets,
			// the more likely we are to use a cache.
    SoElement *invalidElement;
			// This is the element that caused the most
			// recently used cache to be considered
			// invalid.  If it doesn't change, a cache
			// will be built (if it does continue to
			// change, we'll avoid building a cache).
    SbBool saveInvalid;	// Used to remember whether or not a node
			// called SoCacheElement::invalidate() between
			// open() and close().  This scheme assumes
			// that nodes won't apply() another action
			// that uses the CacheElement during
			// rendering (that would screw up caching
			// anyway, so that is a good assumption).
    int saveACacheBits;	// At cache->open() time we get these from the
			// SoGLCacheContextElement, clear them before
			// traversing children, and reset them at
			// cache->close() time.

};


#endif /* _SO_GL_CACHE_LIST */
