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
 |      Defines the SoV1GroupKit class. 
 |      Organizes an appearance, a transform, a local transform and a 
 |      group of child kits
 |
 |   Author(s)          : Paul Isaacs, Thad Beier
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
*/

#ifndef  _SO_V1_GROUP_KIT_
#define  _SO_V1_GROUP_KIT_

#include <Inventor/misc/upgraders/SoV1BaseKit.h>
#include <Inventor/misc/upgraders/SoV1AppearanceKit.h>

////////////////////////////////////////////////////////////////////
//    Class: SoV1GroupKit
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
//        |---------------------|
//     "label"     |      "topSeparator"
//            "callbackList"    |
//      ---------------------------------------------------------------
//      |       |           |     |                                   |
//  "pickStyle" |    "transform"  |                                   |
//     "appearance"  "texture2Transform"                              |
//                                                                    |
//                                                                    | 
//                                                              "childList"
//
////////////////////////////////////////////////////////////////////
SoEXTENDER class SoV1GroupKit : public SoV1BaseKit {

    // Define typeId and name stuff
    SO_NODE_HEADER(SoV1GroupKit);

    // Define catalog for children
    SO_V1_SUBKIT_CATALOG_HEADER(SoV1GroupKit);

  public:
    // constructor
    SoV1GroupKit();

    virtual SoNode *createNewNode();

    // Overload this function. After SoV1BaseKit is done, see if there
    // is information we need in the nodelist:
    // SoV1AppearanceKit::unusedTextureXfs.
    // If so, move this into our "texture2Transform" part.
    // Need to do this because Inventor 1.0 texture had fields for 
    // texture transforms, but new one does not. So SoV1AppearanceKit just
    // stores this info. We retrieve it and make use of it.
    virtual void setUpNewNode(SoNode *newNode);
    
    SoINTERNAL public:
    static void initClass();

  protected:
    virtual ~SoV1GroupKit();
};
#endif  /* _SO_V1_GROUP_KIT_ */
