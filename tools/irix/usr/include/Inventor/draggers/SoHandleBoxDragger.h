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
 |	This file defines the handle box dragger class.
 |
 | NOTE TO DEVELOPERS:
 |     For info about the structure of SoHandleBoxDragger:
 |     [1] compile: /usr/share/src/Inventor/samples/ivNodeKitStructure
 |     [2] type:    ivNodeKitStructure SoHandleBoxDragger.
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
 |  NOTE: for the translators and extruders, 
 |        numbering refers to a cube-face:
 |        1=top,2=bot,3=lft,4=rit,5=fnt,6=bak
 |
 |	handleBoxTranslator1               - translator1
 |	handleBoxTranslator1Active         - translator1Active
 |      (ditto for translator2-translator6)
 |
 |      handleBoxExtruder1                 - extruder1
 |      handleBoxExtruder1Active           - extruder1Active
 |      (ditto for extruder2-extruder6)
 |
 |  
 |  NOTE: for the uniform scalers, 
 |        numbers refer to a corner: 
 |        1=+x+y+z,  2=+x+y-z, 3=+x-y+z, 
 |        4=+x-y-z,  5=-x+y+z,  6=-x+y-z, 
 |        7=-x-y+z, 8=-x-y-z
 |      handleBoxUniform1		   - uniform1
 |      handleBoxUniform1Active            - uniform1Active
 |      (ditto for uniform2-uniform8)
 |
 |  NOTE: for the arrows, numbering refers
 |        to cube-face they point out from:
 |        1=top,2=bot,3=lft,4=rit,5=fnt,6=bak
 |  
 |      handleBoxArrow1                    - arrow1
 |      (ditto for arrow2-arrow6)
 |
 |   Author(s): Paul Isaacs, David Mott
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_HANDLEBOX_DRAGGER_
#define  _SO_HANDLEBOX_DRAGGER_

#include <Inventor/draggers/SoDragger.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/sensors/SoSensor.h>

class SbDict;
class SoDrawStyle;
class SbPlaneProjector;
class SbLineProjector;
class SoFieldSensor;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoHandleBoxDragger
//
//  HandleBox dragger - allows user to transform objects.
//
//////////////////////////////////////////////////////////////////////////////

class SoHandleBoxDragger : public SoDragger {

    SO_KIT_HEADER(SoHandleBoxDragger);

    SO_KIT_CATALOG_ENTRY_HEADER(drawStyle);

    // For making the dragger surround what lies above it.
    SO_KIT_CATALOG_ENTRY_HEADER(surroundScale);

    SO_KIT_CATALOG_ENTRY_HEADER(translator1Switch);
    SO_KIT_CATALOG_ENTRY_HEADER(translator1);
    SO_KIT_CATALOG_ENTRY_HEADER(translator1Active);
    SO_KIT_CATALOG_ENTRY_HEADER(translator2Switch);
    SO_KIT_CATALOG_ENTRY_HEADER(translator2);
    SO_KIT_CATALOG_ENTRY_HEADER(translator2Active);
    SO_KIT_CATALOG_ENTRY_HEADER(translator3Switch);
    SO_KIT_CATALOG_ENTRY_HEADER(translator3);
    SO_KIT_CATALOG_ENTRY_HEADER(translator3Active);
    SO_KIT_CATALOG_ENTRY_HEADER(translator4Switch);
    SO_KIT_CATALOG_ENTRY_HEADER(translator4);
    SO_KIT_CATALOG_ENTRY_HEADER(translator4Active);
    SO_KIT_CATALOG_ENTRY_HEADER(translator5Switch);
    SO_KIT_CATALOG_ENTRY_HEADER(translator5);
    SO_KIT_CATALOG_ENTRY_HEADER(translator5Active);
    SO_KIT_CATALOG_ENTRY_HEADER(translator6Switch);
    SO_KIT_CATALOG_ENTRY_HEADER(translator6);
    SO_KIT_CATALOG_ENTRY_HEADER(translator6Active);


    SO_KIT_CATALOG_ENTRY_HEADER(extruder1Switch);
    SO_KIT_CATALOG_ENTRY_HEADER(extruder1);
    SO_KIT_CATALOG_ENTRY_HEADER(extruder1Active);
    SO_KIT_CATALOG_ENTRY_HEADER(extruder2Switch);
    SO_KIT_CATALOG_ENTRY_HEADER(extruder2);
    SO_KIT_CATALOG_ENTRY_HEADER(extruder2Active);
    SO_KIT_CATALOG_ENTRY_HEADER(extruder3Switch);
    SO_KIT_CATALOG_ENTRY_HEADER(extruder3);
    SO_KIT_CATALOG_ENTRY_HEADER(extruder3Active);
    SO_KIT_CATALOG_ENTRY_HEADER(extruder4Switch);
    SO_KIT_CATALOG_ENTRY_HEADER(extruder4);
    SO_KIT_CATALOG_ENTRY_HEADER(extruder4Active);
    SO_KIT_CATALOG_ENTRY_HEADER(extruder5Switch);
    SO_KIT_CATALOG_ENTRY_HEADER(extruder5);
    SO_KIT_CATALOG_ENTRY_HEADER(extruder5Active);
    SO_KIT_CATALOG_ENTRY_HEADER(extruder6Switch);
    SO_KIT_CATALOG_ENTRY_HEADER(extruder6);
    SO_KIT_CATALOG_ENTRY_HEADER(extruder6Active);

    SO_KIT_CATALOG_ENTRY_HEADER(uniform1Switch);
    SO_KIT_CATALOG_ENTRY_HEADER(uniform1);
    SO_KIT_CATALOG_ENTRY_HEADER(uniform1Active);
    SO_KIT_CATALOG_ENTRY_HEADER(uniform2Switch);
    SO_KIT_CATALOG_ENTRY_HEADER(uniform2);
    SO_KIT_CATALOG_ENTRY_HEADER(uniform2Active);
    SO_KIT_CATALOG_ENTRY_HEADER(uniform3Switch);
    SO_KIT_CATALOG_ENTRY_HEADER(uniform3);
    SO_KIT_CATALOG_ENTRY_HEADER(uniform3Active);
    SO_KIT_CATALOG_ENTRY_HEADER(uniform4Switch);
    SO_KIT_CATALOG_ENTRY_HEADER(uniform4);
    SO_KIT_CATALOG_ENTRY_HEADER(uniform4Active);
    SO_KIT_CATALOG_ENTRY_HEADER(uniform5Switch);
    SO_KIT_CATALOG_ENTRY_HEADER(uniform5);
    SO_KIT_CATALOG_ENTRY_HEADER(uniform5Active);
    SO_KIT_CATALOG_ENTRY_HEADER(uniform6Switch);
    SO_KIT_CATALOG_ENTRY_HEADER(uniform6);
    SO_KIT_CATALOG_ENTRY_HEADER(uniform6Active);
    SO_KIT_CATALOG_ENTRY_HEADER(uniform7Switch);
    SO_KIT_CATALOG_ENTRY_HEADER(uniform7);
    SO_KIT_CATALOG_ENTRY_HEADER(uniform7Active);
    SO_KIT_CATALOG_ENTRY_HEADER(uniform8Switch);
    SO_KIT_CATALOG_ENTRY_HEADER(uniform8);
    SO_KIT_CATALOG_ENTRY_HEADER(uniform8Active);

    SO_KIT_CATALOG_ENTRY_HEADER(arrowTranslation);

    SO_KIT_CATALOG_ENTRY_HEADER(arrow1Switch);
    SO_KIT_CATALOG_ENTRY_HEADER(arrow1);
    SO_KIT_CATALOG_ENTRY_HEADER(arrow2Switch);
    SO_KIT_CATALOG_ENTRY_HEADER(arrow2);
    SO_KIT_CATALOG_ENTRY_HEADER(arrow3Switch);
    SO_KIT_CATALOG_ENTRY_HEADER(arrow3);
    SO_KIT_CATALOG_ENTRY_HEADER(arrow4Switch);
    SO_KIT_CATALOG_ENTRY_HEADER(arrow4);
    SO_KIT_CATALOG_ENTRY_HEADER(arrow5Switch);
    SO_KIT_CATALOG_ENTRY_HEADER(arrow5);
    SO_KIT_CATALOG_ENTRY_HEADER(arrow6Switch);
    SO_KIT_CATALOG_ENTRY_HEADER(arrow6);

  public:
    // Constructor
    SoHandleBoxDragger();
    
    SoSFVec3f    translation;
    SoSFVec3f    scaleFactor;

  SoINTERNAL public:
    static void		initClass();	// initialize the class

  protected:

    // Callbacks for drag start, motion, and finish
    static void startCB( void *, SoDragger * );
    static void motionCB( void *, SoDragger * );
    static void finishCB( void *, SoDragger * );
    
    SoFieldSensor *translFieldSensor;
    SoFieldSensor *scaleFieldSensor;
    static void   fieldSensorCB( void *, SoSensor * );
    static void valueChangedCB( void *, SoDragger * );

    // Callbacks for pressing and releasing the meta keys
    static void	metaKeyChangeCB( void *, SoDragger *);

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

    virtual ~SoHandleBoxDragger();

  private:

    enum WhichAxis 
        { POSX, POSY, POSZ, NEGX, NEGY, NEGZ };
    void   highlightAxisForScale( WhichAxis axis );

    enum State
	{ INACTIVE, 
	  SCALE_GEOM_ONLY,
	   RIT_X_SCALE,  TOP_Y_SCALE,  FNT_Z_SCALE, 
	   LFT_X_SCALE,  BOT_Y_SCALE,  BAK_Z_SCALE, 

	  PX_PY_PZ_3D_SCALE, PX_PY_NZ_3D_SCALE, PX_NY_PZ_3D_SCALE, 
	  PX_NY_NZ_3D_SCALE, NX_PY_PZ_3D_SCALE, NX_PY_NZ_3D_SCALE, 
	  NX_NY_PZ_3D_SCALE, NX_NY_NZ_3D_SCALE, 

	  RIT_TRANSLATE,  TOP_TRANSLATE,  FNT_TRANSLATE,
	  LFT_TRANSLATE,  BOT_TRANSLATE,  BAK_TRANSLATE };

    State		currentState;     
    int                 translateDir;   // Used for 1-D translation,
				        // this variable records the current
				        // axis being used.

    SbPlaneProjector    *motionPlaneProj;
    SbLineProjector     *motionLineProj;

    State	    restartState;     // used by meta callback. 
    SbVec3f         worldRestartPt; // used during interaction

    SbBool          altDown, ctlDown, shftDown;  // used to keep track of
						 // which meta keys were down.

    // functions which do all the work
    void	setHighlights();
    void	setFeedbackArrows();

    SbBool		translateInit();
    SbBool		faceScaleInit();
    SbBool		uniformScaleInit();
    SbBool		scaleGeomSizeOnlyInit();

    SbBool		translateDrag();
    SbBool		scaleDrag();
    SbBool		scaleGeomSizeOnlyDrag();

    // character strings from which the shared geometry is read
    static const char geomBuffer[];		
};

#endif /* _SO_HANDLEBOX_DRAGGER_ */
