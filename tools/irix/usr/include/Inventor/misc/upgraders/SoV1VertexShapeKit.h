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
 |   $Revision: 2.1 $
 |
 |   Description:
 |      Defines the SoV1VertexShapeKit class. 
 |      Subclassed off of SoV1ShapeKit, this class adds 3 nodes needed for all
 |      vertex-based shapes:  SoCoordinate3, SoNormal, and SoTextureCoordinate2
 |
 |   Author(s)          : Paul Isaacs
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
*/

#ifndef  _SO_V1_VERTEX_SHAPE_KIT_
#define  _SO_V1_VERTEX_SHAPE_KIT_

#include <Inventor/misc/upgraders/SoV1ShapeKit.h>

////////////////////////////////////////////////////////////////////
//    Class: SoV1VertexShapeKit
//
//    New nodes in this subclass are:
//         shapeHints, coordinate3, normal, and textureCoordinate2
//
//      A parent node that manages a collection of child nodes 
//      into a unit with the following structure:
//
//                            this
//        |---------------------|
//     "label"     |      "topSeparator"
//            "callbackList"    |
//      ---------------------------------------------------------------
//      |       |           |     |      |     |         |            |
//  "pickStyle" |    "transform"  |      |     |         |            |
//     "appearance"  "texture2Transform" |     |         |            | 
//                                       |     |         |            |
//                                       |     |         |            |
//       ---------------------------------     |         |            |
//       |         |                  |  |     |         |         "childList"
//"materialBinding"|                  |  |     |         |       
//            "normalBinding"         |  |     |         |
//       "textureCoordinateFunctionList" |     |      "shape" 
//                   "textureCoordinateBinding"|      
//                                             |
//        --------------------------------------
//        |            |               |       |
//  "shapeHints" "coordinate3"   "normal" "textureCoordinate2"
//
////////////////////////////////////////////////////////////////////

SoEXTENDER class SoV1VertexShapeKit : public SoV1ShapeKit {

    // Define typeId and name stuff
    SO_NODE_HEADER(SoV1VertexShapeKit);

    // Define catalog for children
    SO_V1_SUBKIT_CATALOG_HEADER(SoV1VertexShapeKit);

  public:
    // constructor
    SoV1VertexShapeKit();

    virtual SoNode *createNewNode();
    
    SoINTERNAL public:
    static void initClass();

  protected:
    virtual ~SoV1VertexShapeKit();
};
#endif  /* _SO_V1_VERTEX_SHAPE_KIT_ */
