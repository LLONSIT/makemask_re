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
 |	This file defines the tab plane dragger class.
 |	This dragger allows you to perform scales
 |	and translations, all in one tidy plane.
 |
 | NOTE TO DEVELOPERS:
 |     For info about the structure of SoTabPlaneDragger:
 |     [1] compile: /usr/share/src/Inventor/samples/ivNodeKitStructure
 |     [2] type:    ivNodeKitStructure SoTabPlaneDragger.
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
 |  tabPlaneTranslator                     - translator
 |  tabPlaneScaleTabMaterial               - scaleTabMaterial
 |  tabPlaneScaleTabHints                  - scaleTabHints
 |
 |
 |   Author(s): Paul Isaacs
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_TAB_PLANE_DRAGGER_
#define  _SO_TAB_PLANE_DRAGGER_

#include <Inventor/SbLinear.h>
#include <Inventor/sensors/SoSensor.h>
#include <Inventor/projectors/SbLineProjector.h>
#include <Inventor/projectors/SbPlaneProjector.h>
#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/draggers/SoDragger.h>

class SoNode;
class SoCoordinate3;
class SoGLRenderAction;
class SoRayPickAction;
class SoFieldSensor;

class SoTabPlaneDragger : public SoDragger
{
    // Define typeId and name stuff
    SO_KIT_HEADER(SoTabPlaneDragger);

    SO_KIT_CATALOG_ENTRY_HEADER(planeSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(translator);
    SO_KIT_CATALOG_ENTRY_HEADER(scaleTabs);
    SO_KIT_CATALOG_ENTRY_HEADER(scaleTabMaterial);
    SO_KIT_CATALOG_ENTRY_HEADER(scaleTabHints);
    SO_KIT_CATALOG_ENTRY_HEADER(scaleTabMaterialBinding);
    SO_KIT_CATALOG_ENTRY_HEADER(scaleTabNormalBinding);
    SO_KIT_CATALOG_ENTRY_HEADER(scaleTabNormal);
    SO_KIT_CATALOG_ENTRY_HEADER(edgeScaleCoords);
    SO_KIT_CATALOG_ENTRY_HEADER(edgeScaleTab0);
    SO_KIT_CATALOG_ENTRY_HEADER(edgeScaleTab1);
    SO_KIT_CATALOG_ENTRY_HEADER(edgeScaleTab2);
    SO_KIT_CATALOG_ENTRY_HEADER(edgeScaleTab3);
    SO_KIT_CATALOG_ENTRY_HEADER(cornerScaleCoords);
    SO_KIT_CATALOG_ENTRY_HEADER(cornerScaleTab0);
    SO_KIT_CATALOG_ENTRY_HEADER(cornerScaleTab1);
    SO_KIT_CATALOG_ENTRY_HEADER(cornerScaleTab2);
    SO_KIT_CATALOG_ENTRY_HEADER(cornerScaleTab3);

  public:
    // Constructor
    SoTabPlaneDragger();

    SoSFVec3f    translation;
    SoSFVec3f    scaleFactor;

    // Cause the scale tabs size to be re-adjusted. Happens automatically
    // upon dragger finish. You may want to do it upon viewer finish as 
    // well.
    void    adjustScaleTabSize();

  SoINTERNAL public:
    static void initClass();  // initialize the class

  protected:

    static void startCB( void *, SoDragger *);
    static void motionCB( void *, SoDragger *);
    static void finishCB( void *, SoDragger *);
    static void	metaKeyChangeCB( void *, SoDragger *);

    SbLineProjector	*lineProj;
    SbPlaneProjector	*planeProj;

    SoFieldSensor *translFieldSensor;
    SoFieldSensor *scaleFieldSensor;
    static void   fieldSensorCB( void *, SoSensor * );
    static void valueChangedCB( void *, SoDragger * );

    virtual void    GLRender( SoGLRenderAction *action );

    void 	dragStart();
    void 	drag();
    void 	dragFinish();

    void 	translateStart();
    void 	translateDrag();
    
    void 	edgeScaleStart();
    void 	edgeScaleDrag();
    
    void 	cornerScaleStart();
    void 	cornerScaleDrag();
    
    void 	scaleUniformStart();
    void 	scaleUniformDrag();

    SbVec3f           worldRestartPt;
    int		      currentScalePatch;

    enum State {
	    INACTIVE, TRANSLATING, EDGE_SCALING, CORNER_SCALING, UNIFORM_SCALING
    };
    SbBool              shftDown;

    State		currentState;
    State		restartState;
    int			translateDir;

    SbVec3f             scaleCenter;

    SbBool		needScaleTabAdjustment;
    void		reallyAdjustScaleTabSize(SoGLRenderAction *action);

    void getXYScreenLengths( SbVec2f &lengths, const SbMatrix &localToScreen, 
				const SbVec2s &winSize);

    // detach/attach any sensors, callbacks, and/or field connections.
    // Called by:            start/end of SoBaseKit::readInstance
    // and on new copy by:   start/end of SoBaseKit::copy.
    // Classes that redefine must call setUpConnections(TRUE,TRUE) 
    // at end of constructor.
    // Returns the state of the node when this was called.
    virtual SbBool setUpConnections( SbBool onOff, SbBool doItAlways = FALSE );

    virtual void setDefaultOnNonWritingFields();

    virtual ~SoTabPlaneDragger();

  private:
    static const char geomBuffer[];
};    

#endif  /* _SO_TAB_PLANE_DRAGGER_ */
