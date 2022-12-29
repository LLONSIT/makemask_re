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
 |      Defines the SoSceneKit class. 
 |      Organizes four lists into a scene:
 |         cameraList       -- a list of SoCameraKits and its subclasses.
 |         lightList        -- a list of SoLightKits and its subclasses.
 |         childList        -- a list of SoSeparatorKit and its subclasses
 |
 |   Author(s)          : Paul Isaacs
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
*/

#ifndef  _SO_SCENE_KIT_
#define  _SO_SCENE_KIT_

#include <Inventor/nodekits/SoBaseKit.h>

////////////////////////////////////////////////////////////////////
//    Class: SoSceneKit
//
// NOTE TO DEVELOPERS:
//     For info about the structure of SoSceneKit:
//     [1] compile: /usr/share/src/Inventor/samples/ivNodeKitStructure
//     [2] type:    ivNodeKitStructure SoSceneKit.
//     [3] The program prints a diagram of the scene graph and a table with 
//         information about each part.
//
//    New nodes in this subclass are:
//         cameraList, lightList, and childList
//
//      A parent node that manages a collection of child nodes 
//      into a unit with the following structure:
//
//                            this
//                              |
//              -----------------
//              |               |
//           "callbackList" "topSeparator"
//                              |
//           --------------------------------
//           |               |              |        
//      "cameraList"    "lightList"   "childList"     
//
////////////////////////////////////////////////////////////////////
class SoSceneKit : public SoBaseKit {

    SO_KIT_HEADER(SoSceneKit);

    // defines fields for the new parts in the catalog
    SO_KIT_CATALOG_ENTRY_HEADER(topSeparator);
    SO_KIT_CATALOG_ENTRY_HEADER(cameraList);
    SO_KIT_CATALOG_ENTRY_HEADER(lightList);
    SO_KIT_CATALOG_ENTRY_HEADER(childList);

  public:
    // constructor
    SoSceneKit();

    // sets the switch node in 'cameraList' to be the number given
    int  getCameraNumber();
    void setCameraNumber(int camNum );

    // Overrides default method on SoNode
    virtual SbBool affectsState() const;

  SoINTERNAL public:
    static void initClass();

  protected:
    virtual ~SoSceneKit();
};
#endif  /* _SO_SCENE_KIT_ */
