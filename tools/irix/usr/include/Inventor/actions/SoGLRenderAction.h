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
 |   $Revision: 2.12 $
 |
 |   Description:
 |	Defines the SoGLRenderAction class
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_GL_RENDER_ACTION_
#define  _SO_GL_RENDER_ACTION_

#include <Inventor/SbViewportRegion.h>
#include <Inventor/actions/SoSubAction.h>
#include <Inventor/elements/SoShapeStyleElement.h>

class	SbBox3f;
class	SoGetBoundingBoxAction;

// Callback functions used between rendering passes should be of this type.
typedef void	SoGLRenderPassCB(void *userData);

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoGLRenderAction
//
//  GL rendering action.
//
//////////////////////////////////////////////////////////////////////////////

class SoGLRenderAction : public SoAction {

    SO_ACTION_HEADER(SoGLRenderAction);

  public:

    // Various levels of transparency rendering quality
    enum TransparencyType {
	SCREEN_DOOR,		// Use GL patterns for screen-door transparency
	ADD,			// Use additive GL alpha blending
	DELAYED_ADD,		// Use additive blending, do transp objs last
	SORTED_OBJECT_ADD,	// Use additive blending, sort objects by bbox
	BLEND,			// Use GL alpha blending
	DELAYED_BLEND,		// Use GL alpha blending, do transp objs last
	SORTED_OBJECT_BLEND	// Use GL alpha blending, sort objects by bbox
    };

    // Possible return codes from a render abort callback
    enum AbortCode {
	CONTINUE,		// Continue as usual
	ABORT,			// Stop traversing the rest of the graph
	PRUNE,			// Do not traverse this node or its children
	DELAY			// Delay rendering of this node
    };

    // Callback functions for render abort should be of this type.
    // This typedef is defined within the class, since it needs to
    // refer to the AbortCode enumerated type.
    typedef AbortCode SoGLRenderAbortCB(void *userData);

    // Constructor. The  parameter defines the viewport region
    // into which rendering will take place. 
    SoGLRenderAction(const SbViewportRegion &viewportRegion);
		

    // Destructor
    virtual ~SoGLRenderAction();

    // Sets current viewport region to use for rendering
    void		setViewportRegion(const SbViewportRegion &newRegion);

    // Returns current viewport region
    const SbViewportRegion &getViewportRegion() const	{ return vpRegion; }

    // Sets/returns current update area, which is the area of the
    // viewport region that will actually be rendered into. This can
    // be used for partial updates in applications that can manage
    // them. The update area is specified in normalized viewport
    // coordinates, where (0,0) is the lower left corner of the
    // viewport and (1,1) is the upper right corner. The area is given
    // as an origin and a size.
    void		setUpdateArea(const SbVec2f &origin,
				      const SbVec2f &size);
    void		getUpdateArea(SbVec2f &origin, SbVec2f &size) const;

    // Sets callback to call during rendering to test for abort
    // condition. The callback function should return one of the
    // AbortCode values.
    void		setAbortCallback(SoGLRenderAbortCB *func,
					 void *userData)
	{ abortCB = func; abortData = userData; }

    // Sets/returns transparency quality level to use when rendering
    void		setTransparencyType(TransparencyType type);
    TransparencyType	getTransparencyType() const	{ return transpType; }

    // Sets/returns smoothing (cheap anti-aliasing) flag
    void		setSmoothing(SbBool smooth);
    SbBool		isSmoothing() const		{ return doSmooth; }

    // Sets/returns number of rendering passes for multi-pass rendering
    void		setNumPasses(int num)		{ numPasses = num;  }
    int			getNumPasses() const		{ return numPasses; }

    // Sets/returns whether rendering is updated after each
    // anti-aliasing pass for progressive improvement (default is FALSE)
    void		setPassUpdate(SbBool flag)	{ passUpdate = flag; }
    SbBool		isPassUpdate() const		{ return passUpdate; }

    // Sets callback to invoke between passes when anti-aliasing.
    // Passing NULL (the default) will cause a color clear and a depth
    // buffer clear to be performed
    void                setPassCallback(SoGLRenderPassCB *func, void *userData)
	{ passCB = func; passData = userData; }

    // Sets/gets the GL cache context.  A cache context is just an
    // integer identifying when GL display lists can be shared between
    // render actions; for example, see the documentation on GLX
    // contexts for information on when GL display lists can be shared
    // between GLX windows.
    void		setCacheContext(uint32_t context);
    uint32_t		getCacheContext() const;

    // Sets/gets whether or not "remote" rendering is happening.
    // Inventor's auto-render-caching algorithm will choose to cache
    // more often when rendering is remote (the assumption being that
    // performance will be better with display lists stored on the
    // remote machine).  By default, it is assumed rendering is NOT
    // remote.
    void		setRenderingIsRemote(SbBool flag);
    SbBool		getRenderingIsRemote() const;

    // Invalidate the state, forcing it to be recreated at the next apply
    virtual void	invalidateState();
    
  SoEXTENDER public:
    // Returns current rendering pass number
    int			getCurPass() const		{ return curPass; }

    // Returns TRUE if render action should abort - checks user callback
    SbBool		abortNow()
	{ return (hasTerminated() || (abortCB != NULL && checkAbort())); }

    // Returns TRUE if render action handles processing of a
    // transparent object (if it is to be sorted and rendered later).
    // If this returns FALSE, the object should just go ahead and
    // render itself.
    // The optional argument isTransparent ensures that the object being
    // rendered will be taken as transparent, regardless of transparency
    // in the state.  If it is false, the state is checked for transparency.
    SbBool		handleTransparency(SbBool isTransparent = FALSE);


  SoINTERNAL public:
    static void		initClass();

    // Returns TRUE if rendering is being delayed because of
    // transparency sorting or delaying
    SbBool		isDelaying() const  { return sortObjs || delayObjs; }

    // Adds to the list of paths to render after all other stuff
    // (including delayed/sorted transparent objects) have been
    // rendered. (Used for annotation nodes.)
    void		addDelayedPath(SoPath *path);

    // Returns TRUE if currently rendering delayed paths
    SbBool		isRenderingDelayedPaths() const
	{ return renderingDelPaths; }

    int			getCullTestResults() { return cullBits; }
    void		setCullTestResults(int b) { cullBits = b; }

  protected:
    // Initiates action on graph
    virtual void	beginTraversal(SoNode *node);

  private:
    SbViewportRegion	vpRegion;	// Current viewport region
    SbVec2f		updateOrigin;	// Origin of update area
    SbVec2f		updateSize;	// Size of update area
 

    // Variables for render abort: 
    SoGLRenderAbortCB	*abortCB;	// Callback to test abort
    void		*abortData;	// User data for abort callback

    // Variables for transparency, smoothing, and multi-pass rendering:
    TransparencyType	transpType;	// Transparency quality type
    SbBool		doSmooth;	// Doing smoothing ?
    int			numPasses;	// Number of rendering passes
    int			curPass;	// Current pass
    SbBool		passUpdate;	// Whether to update after each pass
    SoGLRenderPassCB	*passCB;	// Callback between passes
    void		*passData;	// User data for pass callback

    // For SORTED_OBJECT_ADD or SORTED_OBJECT_BLEND transparency:
    SbBool		renderingTranspObjs; // TRUE when rendering transp objs
    SbBool		delayObjs;	// TRUE if transp objects are to be
					// delayed until after opaque ones
    SbBool		sortObjs;	// TRUE if objects are to be sorted
    SoPathList		transpPaths;	// Paths to transparent objects
    SoGetBoundingBoxAction *ba;		// For computing bounding boxes
    SbBox3f		*bboxes;	// Bounding boxes of objects
    int			numBBoxes;	// Number of bboxes allocated

    uint32_t		cacheContext;   // GL cache context
    SbBool		remoteRendering;// Remote rendering?

    // Stuff needed to implement rendering of delayed paths
    SoPathList		delayedPaths;	// List of paths to render
    SbBool		renderingDelPaths; // TRUE when rendering them

    // These flags determine which things have to be sent to GL when
    // the action is applied. They indicate what's changed since the
    // last time the action was applied.
    enum flags {
	TRANSPARENCY_TYPE	= 0x01,
	SMOOTHING		= 0x02,
	ALL			= 0x03	// Initial value
    };
    uint32_t		whatChanged;

    // Renders all passes starting at a node
    void		renderAllPasses(SoNode *node);

    // Renders one pass starting at a node
    void		renderPass(SoNode *node, int pass);

    // Renders objects that have been marked as transparent in same or
    // sorted order
    void		renderTransparentObjs();

    // Enables or disables GL blending
    void		enableBlending(SbBool enable);

    // Returns TRUE if render action should abort based on callback
    SbBool		checkAbort();

    // Keep track of which planes we need to view-volume cull test
    // against:
    int			cullBits;
};

#endif /* _SO_GL_RENDER_ACTION_ */
