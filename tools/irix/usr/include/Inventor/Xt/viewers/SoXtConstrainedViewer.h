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
 |   Classes	: SoXtConstrainedViewer
 |
 |   Author(s)	: Alain Dumesny
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_XT_CONSTRAINED_VIEWER_
#define  _SO_XT_CONSTRAINED_VIEWER_

#include <Inventor/Xt/viewers/SoXtFullViewer.h>
#include <Inventor/SbBox.h>


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoXtConstrainedViewer
//
//////////////////////////////////////////////////////////////////////////////

class SoXtConstrainedViewer : public SoXtFullViewer {
 public:
    
    // 
    // Specifies the upward direction of the viewer. This up direction is
    // used by the viewers to constrain the camera when tilting up/down, and
    // also used when rotating the camera right/left.
    // The default is the +Y (0,1,0) direction.
    //
    void	    setUpDirection(const SbVec3f &newUpDirection);
    SbVec3f	    getUpDirection()		    { return upDirection; }
    
    //
    // redefine these to add constrained viewer functionality
    //
    virtual void    setCamera(SoCamera *newCam);
    virtual void    saveHomePosition();
    virtual void    resetToHomePosition();
    virtual void    recomputeSceneSize();
    
 protected:
    SoXtConstrainedViewer(
	Widget parent,
	const char *name, 
	SbBool buildInsideParent, 
	SoXtFullViewer::BuildFlag flag, 
	SoXtViewer::Type type, 
	SbBool buildNow);
    ~SoXtConstrainedViewer();
    
    SbVec3f	    upDirection;
    float	    sceneHeight;
    
    // Tilts the camera, restraining it to 180 degree rotation from the
    // up direction. A positive angle tilts the camera up.
    virtual void	tiltCamera(float deltaAngle);
    
    // Redefine these to do constrained viewing tasks.
    // The bottom wheel rotates the camera around the up direction, the
    // left wheel tilts the camera up/down constraning to 180 degree from
    // the up direction. 
    virtual void    	bottomWheelMotion(float newVal);
    virtual void    	leftWheelMotion(float newVal);
    
    // This is called during a paste.
    // We redefine this to keep the right vector of the camera
    // in a parallel plane.
    virtual void	changeCameraValues(SoCamera *newCamera);
    
    // this routine is called by subclasses to find and set the new
    // up direction given the current mouse position. If something is
    // picked, the normal to the object picked will be used to specify
    // the new up direction.
    void		findUpDirection(const SbVec2s &mouseLocation);
    
    // this routine checks the camera orientation and makes sure that the
    // current right vector and the ideal right vector (cross between the
    // view vector and world up direction) are the same (i.e. no unwanted
    // roll), else it fixes it. This keeps the up direction valid.
    void		checkForCameraUpConstrain();
    
    // Redefine this to keep the up vector when seeking
    virtual void	computeSeekFinalOrientation();
    
 private:
    SbVec3f	    origUpDirection; // used to save/reset
};

#endif  /* _SO_XT_CONSTRAINED_VIEWER_ */
