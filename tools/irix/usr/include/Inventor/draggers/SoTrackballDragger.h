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
 |   $Revision: 2.3 $
 |
 |   Description:
 |	This file defines the trackball dragger class.
 |
 | NOTE TO DEVELOPERS:
 |     For info about the structure of SoTrackballDragger:
 |     [1] compile: /usr/share/src/Inventor/samples/ivNodeKitStructure
 |     [2] type:    ivNodeKitStructure SoTrackballDragger.
 |     [3] The program prints a diagram of the scene graph and a table with 
 |         information about each part.
 |
 |  The following parts in this dragger are created at construction time.
 |  'ResourceName' corresponds to the name of the default geometry for the
 |  part. The dragger's constructor gets the scene graph for 'ResourceName'
 |  by querying the global dictionary ( SoDB::getByName("ResourceName"); ).  
 |
 |  Resource Name:                           Part Name:
 |
 |  trackballRotator                       - rotator     
 |  trackballRotatorActive                 - rotatorActive     
 |  trackballXRotator                      - XRotator    
 |  trackballXRotatorActive                - XRotatorActive    
 |  trackballYRotator,                     - YRotator   
 |  trackballYRotatorActive,               - YRotatorActive   
 |  trackballZRotator                      - ZRotator  
 |  trackballZRotatorActive                - ZRotatorActive  
 |  trackballUserAxis                      - userAxis    
 |  trackballUserAxisActive                - userAxisActive    
 |  trackballUserRotator                   - userRotator 
 |  trackballUserRotatorActive             - userRotatorActive 
 |
 |   Author(s): Paul Isaacs, David Mott
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_TRACKBALL_DRAGGER_
#define  _SO_TRACKBALL_DRAGGER_

#include <Inventor/SbLinear.h>
#include <Inventor/SbTime.h>
#include <Inventor/sensors/SoSensor.h>
#include <Inventor/draggers/SoDragger.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFRotation.h>

class SbDict;
class SoGroup;
class SoRotation;
class SbSphereProjector;
class SbCylinderProjector;
class SoFieldSensor;
class SoTimerSensor;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTrackballDragger
//
//  Trackball dragger - allows user to rotate objects.
//
//////////////////////////////////////////////////////////////////////////////

class SoTrackballDragger : public SoDragger {

    SO_KIT_HEADER(SoTrackballDragger);

    // For making the dragger surround what lies above it.
    SO_KIT_CATALOG_ENTRY_HEADER(surroundScale);
    // For keeping the dragger even size in all 3 dimensions
    SO_KIT_CATALOG_ENTRY_HEADER(antiSquish);

    SO_KIT_CATALOG_ENTRY_HEADER(rotatorSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(rotator);
    SO_KIT_CATALOG_ENTRY_HEADER(rotatorActive);
    SO_KIT_CATALOG_ENTRY_HEADER(XRotatorSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(XRotator);
    SO_KIT_CATALOG_ENTRY_HEADER(XRotatorActive);
    SO_KIT_CATALOG_ENTRY_HEADER(YRotatorSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(YRotator);
    SO_KIT_CATALOG_ENTRY_HEADER(YRotatorActive);
    SO_KIT_CATALOG_ENTRY_HEADER(ZRotatorSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(ZRotator);
    SO_KIT_CATALOG_ENTRY_HEADER(ZRotatorActive);

    // The userAxisRotation is not a public part.
    SO_KIT_CATALOG_ENTRY_HEADER(userAxisRotation);

    SO_KIT_CATALOG_ENTRY_HEADER(userAxisSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(userAxis);
    SO_KIT_CATALOG_ENTRY_HEADER(userAxisActive);
    SO_KIT_CATALOG_ENTRY_HEADER(userRotatorSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(userRotator);
    SO_KIT_CATALOG_ENTRY_HEADER(userRotatorActive);

  public:
    // Constructor
    SoTrackballDragger();

    SoSFRotation rotation;
    SoSFVec3f scaleFactor;

    SbBool isAnimationEnabled() { return animationEnabled; }
    void setAnimationEnabled( SbBool newVal );

  SoINTERNAL public:
    static void		initClass();	// initialize the class

  protected:

    // Callbacks for drag start, motion, and finish
    static void startCB(void *, SoDragger *);
    static void motionCB(void *, SoDragger *);
    static void finishCB(void *, SoDragger *);
    
    SoFieldSensor *rotFieldSensor;
    SoFieldSensor *scaleFieldSensor;
    static void fieldSensorCB( void *, SoSensor * );
    static void valueChangedCB( void *, SoDragger * );

    // Callback for pressing and releasing the meta keys
    static void metaKeyChangeCB(void *, SoDragger *);

    // These really do the work during startCB, motionCB, and finishCB
    void	dragStart();
    void	drag();
    void	dragFinish();

    void setAllPartsActive( SbBool onOrOff );

    // detach/attach any sensors, callbacks, and/or field connections.
    // Called by:            start/end of SoBaseKit::readInstance
    // and on new copy by:   start/end of SoBaseKit::copy.
    // Classes that redefine must call setUpConnections(TRUE,TRUE) 
    // at end of constructor.
    // Returns the state of the node when this was called.
    virtual SbBool setUpConnections( SbBool onOff, SbBool doItAlways = FALSE );

    virtual void setDefaultOnNonWritingFields();

    virtual ~SoTrackballDragger();

  private:

    enum State
	{ INACTIVE, FREE_ROTATE, X_ROTATE, Y_ROTATE, Z_ROTATE,
	  SCALE, USER_AXIS_ADJUST, USER_AXIS_ROTATE, SPINNING };
    State		currentState;     

    SbVec3f             constrainedAxis;// if so, about what axis?
    SbVec3f             userAxisVec;       // For storing the user definable
					// 'special' rotation axis.

    SbSphereProjector   *sphereProj;
    SbCylinderProjector *stripeProj;

    SbVec3f             startWorldHitPt; // used during interaction
    SbBool              ctlDown, shftDown; // keep track of meta keys
    SbVec3f             prevWorldHitPt; // used during interaction by 
					 // spherical projector.
    SbMatrix            prevMotionMatrix; // used during interaction by
					   // spherical projector.

    // functions which do all the work
    void	setHighlights();

    SbBool	        rotateDrag();
    SbBool	        scaleDrag();
    SbBool	        userStripeDrag();
    
    // character strings from which the shared geometry is read
    static const char geomBuffer[];		

    // variables used for doing spinning animation
    SbBool animationEnabled;
    SbTime          prevTime;
    SbTime          spinTime;
    SbTime          scheduleRate;
    SoTimerSensor   *spinSensor;
    SbRotation      *rotBuffer;
    SbTime          *timeBuffer;
    int             firstIndex, lastIndex;
    SbVec3f         averageAxis;
    float           angleVelocity;
    SbBool          computeAverage;

    // routtines used for doing spinning animation
    static  void spinSensorCB(void *, SoSensor *);
    void    spinAnimate();
    void    resetSpinStuff();

    // We record whether ball was spinning at drag start. If so, it will 
    // call ha->setHandled() in dragFinish().  This way, it won't be 
    // considered an item selection, which is usually the case when you click 
    // on an object without moving the mouse.
    SbBool  wasSpinningAtDragStart;
};

#endif /* _SO_TRACKBALL_DRAGGER_ */
