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
 |      Defines the SoSeparatorKit class. 
 |      Organizes an appearance, a transform, a local transform and a 
 |      group of child kits
 |
 |   Author(s)          : Paul Isaacs, Thad Beier
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
*/

#ifndef  _SO_SEPARATOR_KIT_
#define  _SO_SEPARATOR_KIT_

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodekits/SoBaseKit.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/sensors/SoFieldSensor.h>

////////////////////////////////////////////////////////////////////
//    Class: SoSeparatorKit
//
// NOTE TO DEVELOPERS:
//     For info about the structure of SoSeparatorKit:
//     [1] compile: /usr/share/src/Inventor/samples/ivNodeKitStructure
//     [2] type:    ivNodeKitStructure SoSeparatorKit.
//     [3] The program prints a diagram of the scene graph and a table with 
//         information about each part.
//
//    New nodes in this subclass are:
//         callbackList, topSeparator, pickStyle, appearance,                 
//          transform, texture2Transform, 
//          childList
//
//      A parent node that manages a collection of child nodes 
//      into a unit with the following structure:
//
//                            this
//            ------------------|
//            |          "topSeparator"
//         "callbackList"       |
//      ---------------------------------------------------------------
//      |       |       |           |     |                           |
//  "pickStyle" |    "units" "transform"  |                           |
//     "appearance"  "texture2Transform"                              |
//                                                                    |
//                                                                    | 
//                                                              "childList"
//
////////////////////////////////////////////////////////////////////

class SoSeparatorKit : public SoBaseKit {

    SO_KIT_HEADER(SoSeparatorKit);

    // defines fields for the new parts in the catalog
    SO_KIT_CATALOG_ENTRY_HEADER(topSeparator);
    SO_KIT_CATALOG_ENTRY_HEADER(pickStyle);
    SO_KIT_CATALOG_ENTRY_HEADER(appearance);
    SO_KIT_CATALOG_ENTRY_HEADER(units);
    SO_KIT_CATALOG_ENTRY_HEADER(transform);
    SO_KIT_CATALOG_ENTRY_HEADER(texture2Transform);
    SO_KIT_CATALOG_ENTRY_HEADER(childList);

  public:

    enum CacheEnabled {         // Possible values for caching
	OFF,                    // Never build or use a cache
	ON,                     // Always try to build a cache
	AUTO                    // Decide based on some heuristic
    };

    // Fields
    SoSFEnum renderCaching;     // OFF/ON/AUTO (see above)
    SoSFEnum boundingBoxCaching;// OFF/ON/AUTO (see above)
    SoSFEnum renderCulling;     // OFF/ON/AUTO (see above)
    SoSFEnum pickCulling;       // OFF/ON/AUTO (see above)

    // constructor
    SoSeparatorKit();

    // Overrides default method on SoNode
    virtual SbBool affectsState() const;

  SoINTERNAL public:
    static void initClass();

  protected:

    // detach/attach any sensors, callbacks, and/or field connections.
    // Called by:            start/end of SoBaseKit::readInstance
    // and on new copy by:   start/end of SoBaseKit::copy.
    // Classes that redefine must call setUpConnections(TRUE,TRUE) 
    // at end of constructor.
    // Returns the state of the node when this was called.
    virtual SbBool setUpConnections( SbBool onOff, SbBool doItAlways = FALSE );

    // Called by the SoBaseKit::write() method. Calls setDefault(TRUE)
    // on the topSeparator. Note that this may be overriden later by basekit
    // if, for example, topSeparator lies on a path that is being written out.
    virtual void setDefaultOnNonWritingFields();

    // This sensor will watch the topSeparator part.  If the part changes to a 
    // new node,  then the fields of the old part will be disconnected and
    // the fields of the new part will be connected.
    // Connections are made from/to the renderCaching, boundingBoxCaching,
    // renderCulling and pickCulling fields. This way, the SoSeparatorKit
    // can be treated from the outside just like a regular SoSeparator node.
    // Setting the fields will affect caching and culling, even though the
    // topSeparator takes care of it.
    // oldTopSep keeps track of the part for comparison.
    SoFieldSensor *fieldSensor;
    static void fieldSensorCB( void *, SoSensor *);
    SoSeparator *oldTopSep;

    void connectSeparatorFields( SoSeparator *dest, SbBool onOff );

  protected:
    virtual ~SoSeparatorKit();

};
#endif  /* _SO_SEPARATOR_KIT_ */
