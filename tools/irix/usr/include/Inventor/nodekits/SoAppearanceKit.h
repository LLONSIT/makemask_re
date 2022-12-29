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
 |      Defines the SoAppearanceKit class. A parent node that manages 
 |      a collection of child nodes for
 |      complete description of the graphical appearance.
 |
 |   Author(s)          : Paul Isaacs, Thad Beier
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
*/

#ifndef  _SO_APPEARANCE_KIT_
#define  _SO_APPEARANCE_KIT_

#include <Inventor/nodekits/SoBaseKit.h>


////////////////////////////////////////////////////////////////////
//    Class: SoAppearanceKit 
//
//      A parent node that manages a collection of child nodes
//      for complete description of the graphical appearance.
//
// NOTE TO DEVELOPERS:
//     For info about the structure of SoAppearanceKit:
//     [1] compile: /usr/share/src/Inventor/samples/ivNodeKitStructure
//     [2] type:    ivNodeKitStructure SoAppearanceKit.
//     [3] The program prints a diagram of the scene graph and a table with 
//         information about each part.
//
//    The structure of the catalog for this class is:
//
//                       this
//                         |
//   -----------------------------------------------------------------------
//   |            |             |      |        |        |             |
//  "callbackList"|"environment"|"material" "complexity" |           "font"
//                |             |                      "texture2" 
//        "lightModel"     "drawStyle"                            
//
////////////////////////////////////////////////////////////////////

class SoAppearanceKit : public SoBaseKit {

    SO_KIT_HEADER(SoAppearanceKit);

    // defines fields for the new parts in the catalog
    SO_KIT_CATALOG_ENTRY_HEADER(lightModel);
    SO_KIT_CATALOG_ENTRY_HEADER(environment);
    SO_KIT_CATALOG_ENTRY_HEADER(drawStyle);
    SO_KIT_CATALOG_ENTRY_HEADER(material);
    SO_KIT_CATALOG_ENTRY_HEADER(complexity);
    SO_KIT_CATALOG_ENTRY_HEADER(texture2);
    SO_KIT_CATALOG_ENTRY_HEADER(font);

  public:
    // constructor
    SoAppearanceKit();

  SoINTERNAL public:
    static void initClass();

  protected:
    virtual ~SoAppearanceKit();
};

#endif  /* _SO_APPEARANCE_KIT_ */
