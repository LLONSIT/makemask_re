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
 |      Defines the SoShapeKit class. 
 |      Subclassed off of SoSeparatorKit, this adds all the nodes potentially
 |      used to describe a shape. Not all of these nodes are needed for any
 |      one type of shape. For example, if you set the 'shape' part to be
 |      an SoSphere node, it will not make much sense to create the part
 |      called 'profileCoordinate3' since it will be ignored in drawing the
 |      sphere.
 |
 |   Author(s)          : Paul Isaacs
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
*/

#ifndef  _SO_SHAPE_KIT_
#define  _SO_SHAPE_KIT_

#include <Inventor/nodekits/SoSeparatorKit.h>

////////////////////////////////////////////////////////////////////
//    Class: SoShapeKit
//
// NOTE TO DEVELOPERS:
//     For info about the structure of SoShapeKit:
//     [1] compile: /usr/share/src/Inventor/samples/ivNodeKitStructure
//     [2] type:    ivNodeKitStructure SoShapeKit.
//     [3] The program prints a diagram of the scene graph and a table with 
//         information about each part.
//
//    New nodes in this subclass are:
//         materialBinding, normalBinding,                 
//         and textureCoordinateBinding
//
//      A parent node that manages a collection of child nodes 
//      into a unit with the following structure:
//
//                            this
//              ----------------|
//              |        "topSeparator"
//         "callbackList"       |
//      ---------------------------------------------------------------
//      |       |           |     |         |    |   |               |
//  "pickStyle" |    "transform"  |         |    |   |               | 
//     "appearance"  "texture2Transform"    |    |   |               |
//                                          |    |  "localTransform" |
//                                          |    |                   |
//                                          |    |            "shapeSeparator"
//                                          |    |                   |
//                                          |    |                "shape"
//                                          |  "childList"
//          ---------------------------------                   
//          |        
// "materialBinding" "normalBinding"  
//  "textureCoordinateBinding" "shapeHints"
//  "coordinate3" "coordinate4" "normal"
//  "textureCoordinate2" "textureCoordinateFunction"
// "profileCoordinate2" "profileCoordinate3"
// "profileList" 
//

////////////////////////////////////////////////////////////////////
class SoShapeKit : public SoSeparatorKit {

    SO_KIT_HEADER(SoShapeKit);

    // defines fields for the new parts in the catalog
    // Binding nodes
    SO_KIT_CATALOG_ENTRY_HEADER(materialBinding);
    SO_KIT_CATALOG_ENTRY_HEADER(normalBinding);
    SO_KIT_CATALOG_ENTRY_HEADER(textureCoordinateBinding);

    // Shapehints
    SO_KIT_CATALOG_ENTRY_HEADER(shapeHints);

    // Coordinate and normal nodes
    SO_KIT_CATALOG_ENTRY_HEADER(coordinate3);
    SO_KIT_CATALOG_ENTRY_HEADER(coordinate4);
    SO_KIT_CATALOG_ENTRY_HEADER(normal);
    SO_KIT_CATALOG_ENTRY_HEADER(textureCoordinate2);
    SO_KIT_CATALOG_ENTRY_HEADER(textureCoordinateFunction);

    // Profile Stuff (for text and for nurbs)
    SO_KIT_CATALOG_ENTRY_HEADER(profileCoordinate2);
    SO_KIT_CATALOG_ENTRY_HEADER(profileCoordinate3);
    SO_KIT_CATALOG_ENTRY_HEADER(profileList);

    // Shape
    SO_KIT_CATALOG_ENTRY_HEADER(localTransform);
    SO_KIT_CATALOG_ENTRY_HEADER(shapeSeparator);
    SO_KIT_CATALOG_ENTRY_HEADER(shape);

  public:
    // constructor
    SoShapeKit();

  SoINTERNAL public:
    static void initClass();

  protected:

    // Called by the SoBaseKit::write() method. Calls setDefault(TRUE)
    // on the shapeSeparator. Note that this may be overriden later by basekit
    // if, for example, topSeparator lies on a path that is being written out.
    virtual void setDefaultOnNonWritingFields();

    virtual ~SoShapeKit();
};
#endif  /* _SO_SHAPE_KIT_ */
