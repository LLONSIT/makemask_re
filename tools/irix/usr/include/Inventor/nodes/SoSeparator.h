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
 |   Description:
 |	This file defines the SoSeparator node class.
 |
 |   Author(s)		: Paul S. Strauss, Nick Thompson
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_SEPARATOR_
#define  _SO_SEPARATOR_

#include <Inventor/nodes/SoGroup.h>
#include <Inventor/fields/SoSFEnum.h>

class SoBoundingBoxCache;
class SoGLCacheList;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoSeparator
//
//  Separator group node: state is saved before traversing children
//  and restored afterwards.
//
//////////////////////////////////////////////////////////////////////////////

#include <Inventor/fields/SoSFBitMask.h>

class SoSeparator : public SoGroup {

    SO_NODE_HEADER(SoSeparator);

  public:

    enum CacheEnabled {		// Possible values for caching
	OFF,			// Never build or use a cache
	ON,			// Always try to build a cache
	AUTO			// Decide based on some heuristic
    };

    // Fields
    SoSFEnum renderCaching;	// OFF/ON/AUTO
    SoSFEnum boundingBoxCaching;// OFF/ON/AUTO
    SoSFEnum renderCulling;	// OFF/ON/AUTO
    SoSFEnum pickCulling;	// OFF/ON/AUTO

    // Constructor
    SoSeparator();

    // Constructor that takes approximate number of children
    SoSeparator(int nChildren);

    // Overrides default method on SoNode
    virtual SbBool	affectsState() const;

    // Set/get the number of render caches each separator will have
    // (2, by default).  The more render caches each separator is
    // allowed to have, the more memory used.  setNumRenderCaches only
    // affects separators that are created after it is called, not
    // separators that were created before.  Setting zero render
    // caches globally turns off render caching.
    static void		setNumRenderCaches(int howMany);
    static int		getNumRenderCaches();

  SoEXTENDER public:
    // Implement actions
    virtual void	doAction(SoAction *action);
    virtual void	callback(SoCallbackAction *action);
    virtual void	getBoundingBox(SoGetBoundingBoxAction *action);
    virtual void	getMatrix(SoGetMatrixAction *action);
    virtual void	GLRender(SoGLRenderAction *action);
    virtual void	handleEvent(SoHandleEventAction *action);
    virtual void	rayPick(SoRayPickAction *action);
    virtual void	search(SoSearchAction *action);

    // These methods make render traversal faster by implementing
    // different rendering paths corresponding to different action
    // path codes.
    virtual void	GLRenderBelowPath(SoGLRenderAction *action);
    virtual void	GLRenderInPath(SoGLRenderAction *action);
    virtual void	GLRenderOffPath(SoGLRenderAction *action);

  SoINTERNAL public:
    static void		initClass();

    virtual void	notify(SoNotList *list);

  protected:
    // Returns TRUE if this separator can be culled because it is
    // outside the cull volume.  The cullResults flags come from the
    // GLRenderAction->getCullTestResults() method, and track the
    // results of previous cull tests to save work when we know we're
    // completely inside the view volume.
    virtual SbBool	cullTest(SoGLRenderAction *action, int &cullResults);

    virtual SbBool	readInstance(SoInput *in, unsigned short flags);

    virtual ~SoSeparator();

  private:
    // Each separator that is created will contain up to this many
    // render caches.
    static int		numRenderCaches;

    SoBoundingBoxCache	*bboxCache;	// Cache for bounding boxes
    SoGLCacheList	*cacheList;	// Caches for GL rendering
};

#endif /* _SO_SEPARATOR_ */
