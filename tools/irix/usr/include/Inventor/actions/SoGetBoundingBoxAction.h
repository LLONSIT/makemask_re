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
 |	Defines the SoGetBoundingBoxAction class
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_GET_BOUNDING_BOX_ACTION_
#define  _SO_GET_BOUNDING_BOX_ACTION_

#include <Inventor/SbBox.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/actions/SoSubAction.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoGetBoundingBoxAction
//
//  For computing a bounding box enclosing objects defined by a scene
//  graph. The box is a rectangular prism whose sides are aligned with
//  the coordinate axes, and is represented as an SbBox3f. It also
//  computes the center point, which is defined differently for
//  different objects.
//
//////////////////////////////////////////////////////////////////////////////

class SoGetBoundingBoxAction : public SoAction {

    SO_ACTION_HEADER(SoGetBoundingBoxAction);

  public:
    // Constructor takes viewport region to use for picking. Even
    // though the bounding box computation may not involve a window
    // per se, some nodes need this information to determine their
    // size and placement.
    SoGetBoundingBoxAction(const SbViewportRegion &viewportRegion);

    // Destructor
    virtual ~SoGetBoundingBoxAction();

    // Sets current viewport region to use for action
    void		setViewportRegion(const SbViewportRegion &newRegion);

    // Returns current viewport region
    const SbViewportRegion &getViewportRegion() const	{ return vpRegion; }

    // Returns computed bounding box
    SbBox3f		getBoundingBox() const	{ return box.project(); }

    // Returns bounding box before transform
    SbXfBox3f &		getXfBoundingBox()	{ return box; }

    // Returns computed center point
    const SbVec3f &	getCenter() const;

    // Set to TRUE if you want the returned bounding box to be in the
    // space of whatever camera is in the graph. Camera space is
    // defined to have the viewpoint at the origin, with the direction
    // of view along the negative z axis. This space can be used to
    // determine distances of objects from the camera.
    void		setInCameraSpace(SbBool flag)	{ cameraSpace = flag; }

    // Returns camera space flag
    SbBool		isInCameraSpace() const		{ return cameraSpace; }

    // set a path to do a resetTransform/resetBoundingBox on. The default
    // is to do the reset right before the given path.
    enum ResetType {    // Which things get reset:
	TRANSFORM      = 0x01,	    // Transformation
	BBOX           = 0x02,	    // Bounding Box
	ALL            = 0x03       // Both Transform and Bounding Box
    };
    void		setResetPath(const SoPath *path,
				     SbBool resetBefore = TRUE,
				     ResetType what = ALL);
    const SoPath *	getResetPath() const	{ return resetPath; }
    SbBool		isResetPath() const	{ return( resetPath != NULL); }
    SbBool		isResetBefore() const	{ return resetBefore; }
    SoGetBoundingBoxAction::ResetType getWhatReset() const { return resetWhat;}

  SoEXTENDER public:

    // Call these methods at beginning and end (respectively) of
    // the getBoundingBox action for each node. (SoNode calls these in
    // its static method for this action.)
    void		checkResetBefore();
    void		checkResetAfter();

    // Extends the current bounding box by the given bounding box,
    // after transforming it by the current value of the
    // SoLocalBBoxMatrixElement
    void		extendBy(const SbBox3f &box);
    void		extendBy(const SbXfBox3f &box);

    // Sets the center of the bounding box to the given point, which,
    // if transformCenter is TRUE, is first transformed by the current
    // value of the SoLocalBBoxMatrixElement. After this is called,
    // isCenterSet will return TRUE, unless resetCenter is called.
    // Shapes should setCenter() to whatever is appropriate (e.g.
    // left-justified text might set the center to be the start of the
    // string) with transformCenter set to TRUE.  Groups are
    // responsible for averaging the centers if more than one shape
    // sets the center; when setting the center to the average of
    // transformed centers, pass FALSE for transformCenter.
    void		setCenter(const SbVec3f &center,
				  SbBool transformCenter);
    SbBool		isCenterSet() const;
    void		resetCenter();

  SoINTERNAL public:
    static void		initClass();

  protected:
    // Initiates action on graph
    virtual void	beginTraversal(SoNode *node);

  private:
    SbXfBox3f		box;		// Bounding box
    SbVec3f		center;		// Center point
    SbBool		cameraSpace;	// Bounding box in camera space?
    const SoPath	*resetPath;	// path to reset transform
    SbBool		resetBefore;	// reset before or after?
    ResetType 	  	resetWhat;      // which things get reset?
    SbViewportRegion	vpRegion;	// Current viewport region
    SbBool		centerSet;	// setCenter() called?

    // check to see if the reset parameters are met, if so, do the
    // reset transform and reset bbox
    void		checkReset(SbBool resetBefore);
};

#endif /* _SO_GET_BOUNDING_BOX_ACTION_ */
