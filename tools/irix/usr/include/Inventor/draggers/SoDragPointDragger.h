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
 |	This file defines the drag point dragger class.
 |
 | NOTE TO DEVELOPERS:
 |     For info about the structure of SoDragPointDragger:
 |     [1] compile: /usr/share/src/Inventor/samples/ivNodeKitStructure
 |     [2] type:    ivNodeKitStructure SoDragPointDragger.
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
 |  dragPointXTranslatorTranslator        - xTranslator.translator
 |  dragPointXTranslatorTranslatorActive  - xTranslator.translatorActive
 |  dragPointYTranslatorTranslator        - yTranslator.translator
 |  dragPointYTranslatorTranslatorActive  - yTranslator.translatorActive
 |  dragPointZTranslatorTranslator        - zTranslator.translator
 |  dragPointZTranslatorTranslatorActive  - zTranslator.translatorActive
 |
 |  dragPointYZTranslatorTranslator       - yzTranslator.translator
 |  dragPointYZTranslatorTranslatorActive - yzTranslator.translatorActive
 |  dragPointXZTranslatorTranslator       - xzTranslator.translator
 |  dragPointXZTranslatorTranslatorActive - xzTranslator.translatorActive
 |  dragPointXYTranslatorTranslator       - xyTranslator.translator
 |  dragPointXYTranslatorTranslatorActive - xyTranslator.translatorActive
 |
 |  dragPointXFeedback                    - xFeedback
 |  dragPointYFeedback                    - yFeedback
 |  dragPointZFeedback                    - zFeedback
 |
 |  dragPointYZFeedback                   - yzFeedback
 |  dragPointXZFeedback                   - xzFeedback
 |  dragPointXYFeedback                   - xyFeedback
 |
 |   Author(s): Paul Isaacs, Howard Look
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_DRAGPOINT_DRAGGER_
#define  _SO_DRAGPOINT_DRAGGER_

#include <Inventor/SbLinear.h>
#include <Inventor/SbBox.h>
#include <Inventor/draggers/SoDragger.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/sensors/SoSensor.h>


class SoFieldSensor;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoDragPointDragger
//
//  DragPoint dragger - allows user to move a single coordinate in
//  three dimensions.
//
//////////////////////////////////////////////////////////////////////////////

class SoDragPointDragger : public SoDragger
{
    SO_KIT_HEADER(SoDragPointDragger);

    SO_KIT_CATALOG_ENTRY_HEADER(noRotSep);
    SO_KIT_CATALOG_ENTRY_HEADER(xTranslatorSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(xTranslator);
    SO_KIT_CATALOG_ENTRY_HEADER(xyTranslatorSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(xyTranslator);

    SO_KIT_CATALOG_ENTRY_HEADER(rotXSep);
    SO_KIT_CATALOG_ENTRY_HEADER(rotX);
    SO_KIT_CATALOG_ENTRY_HEADER(xzTranslatorSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(xzTranslator);

    SO_KIT_CATALOG_ENTRY_HEADER(rotYSep);
    SO_KIT_CATALOG_ENTRY_HEADER(rotY);
    SO_KIT_CATALOG_ENTRY_HEADER(zTranslatorSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(zTranslator);
    SO_KIT_CATALOG_ENTRY_HEADER(yzTranslatorSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(yzTranslator);

    SO_KIT_CATALOG_ENTRY_HEADER(rotZSep);
    SO_KIT_CATALOG_ENTRY_HEADER(rotZ);
    SO_KIT_CATALOG_ENTRY_HEADER(yTranslatorSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(yTranslator);

    SO_KIT_CATALOG_ENTRY_HEADER(xFeedbackSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(xFeedbackSep);
    SO_KIT_CATALOG_ENTRY_HEADER(xFeedbackTranslation);
    SO_KIT_CATALOG_ENTRY_HEADER(xFeedback);

    SO_KIT_CATALOG_ENTRY_HEADER(yFeedbackSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(yFeedbackSep);
    SO_KIT_CATALOG_ENTRY_HEADER(yFeedbackTranslation);
    SO_KIT_CATALOG_ENTRY_HEADER(yFeedback);

    SO_KIT_CATALOG_ENTRY_HEADER(zFeedbackSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(zFeedbackSep);
    SO_KIT_CATALOG_ENTRY_HEADER(zFeedbackTranslation);
    SO_KIT_CATALOG_ENTRY_HEADER(zFeedback);

    SO_KIT_CATALOG_ENTRY_HEADER(planeFeedbackSep);
    SO_KIT_CATALOG_ENTRY_HEADER(planeFeedbackTranslation);
    SO_KIT_CATALOG_ENTRY_HEADER(planeFeedbackSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(yzFeedback);
    SO_KIT_CATALOG_ENTRY_HEADER(xzFeedback);
    SO_KIT_CATALOG_ENTRY_HEADER(xyFeedback);

  public:
    // Constructor
    SoDragPointDragger();

    SoSFVec3f translation;

  public:
    // Set/get the limit at which the feedback axes will jump to a new 
    // position. For example, if set to .1 (the default), the
    // feedback axes will jump when the location gets within
    // 10% of the end of the axis.
    void    setJumpLimit(float limit)	{ jumpLimit = limit; }
    float   getJumpLimit() const	{ return jumpLimit; }

    // Sets switches to show one line dragger and one plane dragger.
    // It cycles through 3 different configurations:
    // xline/yzPlane, yline/xzplane, zline/xyplane
    void showNextDraggerSet();

  SoINTERNAL public:
    static void		initClass();	// initialize the class

  protected:

    static void startCB( void *, SoDragger * );
    static void motionCB( void *, SoDragger * );
    static void finishCB( void *, SoDragger * );

    SoFieldSensor *fieldSensor;
    static void fieldSensorCB( void *, SoSensor * );
    static void valueChangedCB( void *, SoDragger * );

    static void	metaKeyChangeCB( void *, SoDragger *);

    void	dragStart();
    void	drag();
    void	dragFinish();
    
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

    virtual ~SoDragPointDragger();

  private:
    
    SoDragger *currentDragger;
    SbVec3f    startLocalHitPt;

    SbBool          shftDown;  // used to keep track of if meta key is down.

    // The box defining the area where the feedback appears.
    // This box stays still in world space whil the dragger is moved.
    // But when the dragger gets too close to the edge, it jumps over
    // to define a new box.
    SbBox3f	limitBox;
    
    // when to jump
    float	jumpLimit;

    // sets the feedback geometry based on the level of
    // constraints
    void	setFeedbackGeometry();

    // checks the limit box and extends it if necessary
    void	checkBoxLimits();

    // Sets the offsetWorkLimit box and updates the feedback geometry 
    void  updateLimitBoxAndFeedback();

    static const char geomBuffer[];

    //  Cached values to make updating feedback more efficient
    SoNode *oldXAxisNode;
    SoNode *oldYAxisNode;
    SoNode *oldZAxisNode;
};

#endif  /* _SO_DRAGPOINT_DRAGGER_ */
