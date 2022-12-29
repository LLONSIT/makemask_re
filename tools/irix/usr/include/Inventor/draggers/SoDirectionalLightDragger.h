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
 |	This is the include file for the SoDirectionalLightDragger.
 |
 |   This is a composite dragger which allows independent rotation,
 |   and translation for dragging a directional light.
 |   When applied to a directional light, the translation will only serve
 |   to move the dragger. This translation will have no effect on
 |   the directional light being dragged.
 |
 |  It is composed of an SoRotateSphericalDragger (for rotation), 
 |  and an SoDragPointDragger (for translation).
 |
 | NOTE TO DEVELOPERS:
 |     For info about the structure of SoDirectionalLightDragger:
 |     [1] compile: /usr/share/src/Inventor/samples/ivNodeKitStructure
 |     [2] type:    ivNodeKitStructure SoDirectionalLightDragger.
 |     [3] The program prints a diagram of the scene graph and a table with 
 |         information about each part.
 |
 |  The following parts in this dragger are created at construction time.
 |  'ResourceName' corresponds to the name of the default geometry for the
 |  part. The dragger's constructor gets the scene graph for 'ResourceName'
 |  by querying the global dictionary ( SoDB::getByName("ResourceName"); ).  
 |
 |  Resource Name:                             Part Name:
 |
 |  directionalLightOverallMaterial          - material
 |
 |  directionalLightTranslatorLineTranslator - 
 |				      - translator.xTranslator.translator
 |				      - translator.yTranslator.translator
 |				      - translator.zTranslator.translator
 |  directionalLightTranslatorLineTranslatorActive  - 
 |				      - translator.xTranslator.translatorActive
 |				      - translator.yTranslator.translatorActive
 |				      - translator.zTranslator.translatorActive
 |
 |  directionalLightTranslatorPlaneTranslator        - 
 |				      - translator.yzTranslator.translator
 |				      - translator.xzTranslator.translator
 |				      - translator.xyTranslator.translator
 |  directionalLightTranslatorPlaneTranslatorActive  - 
 |				      - translator.yzTranslator.translatorActive
 |				      - translator.xzTranslator.translatorActive
 |				      - translator.xyTranslator.translatorActive
 |
 |  directionalLightRotatorRotator        - rotator.rotator
 |  directionalLightRotatorRotatorActive  - rotator.rotatorActive
 |  directionalLightRotatorFeedback       - rotator.feedback
 |  directionalLightRotatorFeedbackActive - rotator.feedbackActive
 |
 |   Author(s): Paul Isaacs, David Mott
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_DIRECTIONAL_LIGHT_DRAGGER_
#define  _SO_DIRECTIONAL_LIGHT_DRAGGER_

#include <Inventor/SbLinear.h>
#include <Inventor/draggers/SoDragger.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFRotation.h>
#include <Inventor/sensors/SoSensor.h>

class SoFieldSensor;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoDirectionalLightDragger
//
//  This changes the direction of directional lights.
//
//////////////////////////////////////////////////////////////////////////////

class SoDirectionalLightDragger : public SoDragger {

    SO_KIT_HEADER(SoDirectionalLightDragger);

    // This gives the dragger an overall material.  It is edited by lightManips
    // to make its dragger match the color of the light.  Any materials within 
    // other parts will override this one. 
    SO_KIT_CATALOG_ENTRY_HEADER(material);

    // The translator is kept under a separator along with a
    // rotation that is maintained as the inverse to the rotation of the
    // light. This means that using the rotator does not rotate the
    // coordinate system that we translate the base of the dragger in.
    SO_KIT_CATALOG_ENTRY_HEADER(translatorSep);
    SO_KIT_CATALOG_ENTRY_HEADER(translatorRotInv);
    SO_KIT_CATALOG_ENTRY_HEADER(translator);
    SO_KIT_CATALOG_ENTRY_HEADER(rotator);

  public:
    SoDirectionalLightDragger();

    SoSFRotation rotation;
    SoSFVec3f    translation;

  SoINTERNAL public:
    static void		initClass();	// initialize the class

  protected:

    SoFieldSensor *translFieldSensor;
    SoFieldSensor *rotFieldSensor;
    static void   fieldSensorCB( void *, SoSensor * );
    static void valueChangedCB( void *, SoDragger * );

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

    ~SoDirectionalLightDragger();

  private:
    static const char		geomBuffer[];
};

#endif /* _SO_DIRECTIONAL_LIGHT_DRAGGER_ */
