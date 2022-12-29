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
 |   $Revision: 2.11 $
 |
 |   Description:
 |	This file defines the SoGLRenderCache class, which is used for
 |	storing caches during GL rendering.
 |
 |   Author(s)		: Paul S. Strauss, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */


#ifndef  _SO_GL_RENDER_CACHE
#define  _SO_GL_RENDER_CACHE

#include <GL/gl.h>
#include <Inventor/caches/SoCache.h>
#include <Inventor/elements/SoGLLazyElement.h>

////////////////////////////////////////////////////////////////////////
//
//  Class SoGLRenderCache:
//
//  A render cache stores a GL display list containing commands that
//  draw a representation of the shape(s) represented by the cache.
//  The display list id is stored in the cache instance.
//
//  Each instance has a list of all nested display lists
//  that it calls. This list maintains reference counts on the
//  instances within it.
//  
//  This version has a copy of SoGLLazyElement, which is handled differently
//  than other elements.
//
////////////////////////////////////////////////////////////////////////

class SoGLDisplayList;

SoEXTENDER class SoGLRenderCache : public SoCache {

  public:
    // Constructor and destructor
    SoGLRenderCache(SoState *state);
    ~SoGLRenderCache();

    // Maintain list of cache dependencies.  If one cache calls
    // another inside of it, we have to make sure that the inner cache
    // isn't deleted before the outer one.
    virtual void	addNestedCache(SoGLDisplayList *child);

    // Opens/closes the cache. All GL commands made between an open()
    // and a close() will be part of the the display list cache.
    // Calling open automatically sets SoCacheElement.
    void		open(SoState *state);
    void		close();

    // Calls the cache. The display list will be sent to GL.  This
    // automatically calls addCacheDependency on any open cache.
    void		call(SoState *state);

    // Returns TRUE if cache is valid with respect to the given state
    // The GL version tests for GL Enable flags, first.
    virtual SbBool      isValid(const SoState *state) const;
 
    // method for the lazy element to set flags:
    void setLazyBits(uint32_t ivFlag, uint32_t glFlag, uint32_t sendFlag)
	{checkGLFlag |= glFlag;
	checkIVFlag |= ivFlag;
	doSendFlag |= sendFlag;}
	
    SoGLLazyElement* getLazyElt() 
	{return GLCacheLazyElement;}

  protected:
    // Free display lists before deletion, if possible (if not, they
    // are added to a list to be deleted later by the
    // CacheContextElement).
    virtual void	destroy(SoState *state);

  private:
    SoGLDisplayList	*list;		// Display list structure
    SbBool		listOpen;	// Whether display list is open
    SbPList		nestedCaches;	// List of nested caches

    // Save state that opened a cache, to use when it is closed:
    SoState *		saveState;

    // Keep a copy of SoGLLazyElement for comparison
    SoGLLazyElement *	GLCacheLazyElement;
    
    // Keep a copy of the GL state for copying back after cache call:
    SoGLLazyElement::GLLazyState    cachedGLState;

    // BitFlags for maintaining Lazy Element:
    // indicates that GL must match for cache to be valid
    uint32_t		checkGLFlag;

    // indicates that IV must match for cache to be valid
    uint32_t		checkIVFlag;

    // indicates that a send must be issued prior to calling cache.
    uint32_t		doSendFlag;
    
};

#endif /* _SO_GL_RENDER_CACHE */
