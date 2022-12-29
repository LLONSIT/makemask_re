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
 |	This file defines the transform box dragger class.
 |	This dragger allows you to perform rotations,uniform scales
 |	and translations, all in one tidy box.
 |
 | NOTE TO DEVELOPERS:
 |     For info about the structure of SoTabBoxDragger:
 |     [1] compile: /usr/share/src/Inventor/samples/ivNodeKitStructure
 |     [2] type:    ivNodeKitStructure SoTabBoxDragger.
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
 |  tabBoxBoxGeom                          - boxGeom
 |
 |  tabBoxTranslator                       - tabPlane1.translator
 |  tabBoxScaleTabMaterial                 - tabPlane1.scaleTabMaterial
 |  tabBoxScaleTabHints                    - tabPlane1.scaleTabHints
 |  (ditto for tabPlane2 - tabPlane6)
 |
 |   Author(s): Paul Isaacs, Howard Look
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_TAB_BOX_DRAGGER_
#define  _SO_TAB_BOX_DRAGGER_

#include <Inventor/SbLinear.h>
#include <Inventor/draggers/SoDragger.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/sensors/SoSensor.h>

class SoFieldSensor;

class SoTabBoxDragger : public SoDragger
{
    SO_KIT_HEADER(SoTabBoxDragger);

    // For making the dragger surround what lies above it.
    SO_KIT_CATALOG_ENTRY_HEADER(surroundScale);

    SO_KIT_CATALOG_ENTRY_HEADER(tabPlane1Sep);
    SO_KIT_CATALOG_ENTRY_HEADER(tabPlane1Xf);
    SO_KIT_CATALOG_ENTRY_HEADER(tabPlane1);
    SO_KIT_CATALOG_ENTRY_HEADER(tabPlane2Sep);
    SO_KIT_CATALOG_ENTRY_HEADER(tabPlane2Xf);
    SO_KIT_CATALOG_ENTRY_HEADER(tabPlane2);
    SO_KIT_CATALOG_ENTRY_HEADER(tabPlane3Sep);
    SO_KIT_CATALOG_ENTRY_HEADER(tabPlane3Xf);
    SO_KIT_CATALOG_ENTRY_HEADER(tabPlane3);
    SO_KIT_CATALOG_ENTRY_HEADER(tabPlane4Sep);
    SO_KIT_CATALOG_ENTRY_HEADER(tabPlane4Xf);
    SO_KIT_CATALOG_ENTRY_HEADER(tabPlane4);
    SO_KIT_CATALOG_ENTRY_HEADER(tabPlane5Sep);
    SO_KIT_CATALOG_ENTRY_HEADER(tabPlane5Xf);
    SO_KIT_CATALOG_ENTRY_HEADER(tabPlane5);
    SO_KIT_CATALOG_ENTRY_HEADER(tabPlane6Sep);
    SO_KIT_CATALOG_ENTRY_HEADER(tabPlane6Xf);
    SO_KIT_CATALOG_ENTRY_HEADER(tabPlane6);

    SO_KIT_CATALOG_ENTRY_HEADER(boxGeom);

  public:
    // Constructors
    SoTabBoxDragger();

    SoSFVec3f    translation;
    SoSFVec3f    scaleFactor;

    // Cause the scale tabs size to be re-adjusted on all 6 tabPlanes. Happens 
    // automatically upon dragger finish. You may want to do this during a 
    // finishCallback for your viewer as well.
    void    adjustScaleTabSize();

  SoINTERNAL public:
    static void initClass();  // initialize the class

  protected:

    SoFieldSensor *translFieldSensor;
    SoFieldSensor *scaleFieldSensor;
    static void   fieldSensorCB( void *, SoSensor * );
    static void valueChangedCB( void *, SoDragger * );

    static void invalidateSurroundScaleCB(  void *, SoDragger * );
    static void adjustScaleTabSizeCB(  void *, SoDragger * );

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

    virtual ~SoTabBoxDragger();

  private:
    static const char geomBuffer[];
};    

#endif  /* _SO_TAB_BOX_DRAGGER_ */
