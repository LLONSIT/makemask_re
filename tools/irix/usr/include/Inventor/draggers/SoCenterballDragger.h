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
 |	This file defines a trackball-like dragger which allows the
 |      user to drag the center of rotation to a new location.
 |
 | NOTE TO DEVELOPERS:
 |     For info about the structure of SoCenterballDragger:
 |     [1] compile: /usr/share/src/Inventor/samples/ivNodeKitStructure
 |     [2] type:    ivNodeKitStructure SoCenterballDragger.
 |     [3] The program prints a diagram of the scene graph and a table with 
 |         information about each part.
 |
 |
 |  The following parts in this dragger are created at construction time.
 |  'ResourceName' corresponds to the name of the default geometry for the
 |  part. The dragger's constructor gets the scene graph for 'ResourceName'
 |  by querying the global dictionary ( SoDB::getByName("ResourceName"); ).  
 |
 |  Resource Name:                           Part Name:
 |
 |       centerballRotator                     - rotator.rotator
 |       centerballRotatorActive               - rotator.rotatorActive
 |
 |       centerballStripe                    - XRotator.rotator
 |       centerballStripeActive              - XRotator.rotatorActive
 |       centerballStripe                    - YRotator.rotator
 |       centerballStripeActive              - YRotator.rotatorActive
 |       centerballStripe                    - ZRotator.rotator
 |       centerballStripeActive              - ZRotator.rotatorActive
 |
 |       centerballCenterChanger              - XCenterChanger.translator
 |       centerballCenterChangerActive        - XCenterChanger.translatorActive
 |       centerballCenterXAxisFeedback        - XCenterChanger.xAxisFeedback
 |       centerballCenterYAxisFeedback        - XCenterChanger.yAxisFeedback
 |
 |       centerballCenterChanger              - YCenterChanger.translator
 |       centerballCenterChangerActive        - YCenterChanger.translatorActive
 |       centerballCenterXAxisFeedback        - YCenterChanger.xAxisFeedback
 |       centerballCenterYAxisFeedback        - YCenterChanger.yAxisFeedback
 |
 |       centerballCenterChanger              - ZCenterChanger.translator
 |       centerballCenterChangerActive        - ZCenterChanger.translatorActive
 |       centerballCenterXAxisFeedback        - ZCenterChanger.xAxisFeedback
 |       centerballCenterYAxisFeedback        - ZCenterChanger.yAxisFeedback
 |
 |       centerballXAxis              	       - XAxis
 |       centerballYAxis              	       - YAxis
 |       centerballZAxis              	       - ZAxis
 |
 |   Author(s): Paul Isaacs, Howard Look
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_CENTERBALL_DRAGGER_
#define  _SO_CENTERBALL_DRAGGER_

#include <Inventor/SbLinear.h>
#include <Inventor/sensors/SoSensor.h>
#include <Inventor/draggers/SoDragger.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFRotation.h>

class SoFieldSensor;
class SoInput;
class SoGetBoundingBoxAction;
class SoGetMatrixAction;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoCenterballDragger
//
//  CenterballDragger - allows user to rotate objects.
//
//////////////////////////////////////////////////////////////////////////////

class SoCenterballDragger : public SoDragger {

    SO_KIT_HEADER(SoCenterballDragger);

    // For making the dragger surround what lies above it.
    SO_KIT_CATALOG_ENTRY_HEADER(surroundScale);
    // For keeping the dragger even size in all 3 directions
    SO_KIT_CATALOG_ENTRY_HEADER(antiSquish);

    // Translates whole dragger to location of center.
    SO_KIT_CATALOG_ENTRY_HEADER(translateToCenter);

    SO_KIT_CATALOG_ENTRY_HEADER(lightModel);

    SO_KIT_CATALOG_ENTRY_HEADER(rotator);

    SO_KIT_CATALOG_ENTRY_HEADER(YRotator);
    SO_KIT_CATALOG_ENTRY_HEADER(ZCenterChanger);
    SO_KIT_CATALOG_ENTRY_HEADER(ZAxisSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(ZAxis);

    SO_KIT_CATALOG_ENTRY_HEADER(rotX90);

    SO_KIT_CATALOG_ENTRY_HEADER(ZRotator);
    SO_KIT_CATALOG_ENTRY_HEADER(YCenterChanger);
    SO_KIT_CATALOG_ENTRY_HEADER(YAxisSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(YAxis);

    SO_KIT_CATALOG_ENTRY_HEADER(rotY90);

    SO_KIT_CATALOG_ENTRY_HEADER(XRotator);

    SO_KIT_CATALOG_ENTRY_HEADER(rot2X90);

    SO_KIT_CATALOG_ENTRY_HEADER(XCenterChanger);
    SO_KIT_CATALOG_ENTRY_HEADER(XAxisSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(XAxis);

  public:
    SoCenterballDragger();

    SoSFRotation rotation;
    SoSFVec3f    center;

  SoEXTENDER public:
    // Saves the matrix that moves the center relative to the motionMatrix
    // after it calls the default SoDragger method.
    virtual void saveStartParameters();

  SoINTERNAL public:
    static void		initClass();	// initialize the class

  protected:
    
    SoFieldSensor *rotFieldSensor;
    SoFieldSensor *centerFieldSensor;
    static void fieldSensorCB( void *, SoSensor *);
    static void valueChangedCB( void *, SoDragger *);

    void transferCenterDraggerMotion(SoDragger *childDragger);

    // Differs from SoDragger as follows: If it has a surroundScale node with 
    // 'ignoreInBbox' set to TRUE, this means surroundScale is calculating its 
    // bbox for sizing. So we also need to ignore the 'translateToCenter' 
    // matrix. Take care of this by disabling notification of 
    // 'translateToCenter', changing it to identity, running action, 
    // and then putting everything back.
    virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
    virtual void	getMatrix(SoGetMatrixAction *action);

    static void kidStartCB(  void *, SoDragger * );
    static void kidFinishCB( void *, SoDragger * );

    void setSwitches( SoDragger *activeChild );

    // detach/attach any sensors, callbacks, and/or field connections.
    // Also set geometry of childDraggers to be our default instead of their
    // regular default, using our resources.
    // Called by:            start/end of SoBaseKit::readInstance
    // and on new copy by:   start/end of SoBaseKit::copy.
    // Classes that redefine must call setUpConnections(TRUE,TRUE) 
    // at end of constructor.
    // Returns the state of the node when this was called.
    virtual SbBool setUpConnections( SbBool onOff, SbBool doItAlways = FALSE );

    virtual void setDefaultOnNonWritingFields();

    ~SoCenterballDragger();

  private:

    // Used by centerball to save initial matrix of the 'translateToCenter'
    // part when the child begins to move.
    SbMatrix startCenterMatrix;

    // character string from which the shared geometry is read
    static const char geomBuffer[];
};

#endif /* _SO_CENTERBALL_DRAGGER_ */
