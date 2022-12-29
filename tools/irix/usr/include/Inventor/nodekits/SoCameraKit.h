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
 |      Defines the SoCameraKit class. 
 |      Subclassed off of SoBaseKit, it is the base class for all camera kits.
 |
 |   Author(s)          : Paul Isaacs
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
*/

#ifndef  _SO_CAMERA_KIT_
#define  _SO_CAMERA_KIT_

#include <Inventor/nodekits/SoBaseKit.h>

////////////////////////////////////////////////////////////////////
//    Class: SoCameraKit
//
// NOTE TO DEVELOPERS:
//     For info about the structure of SoCameraKit:
//     [1] compile: /usr/share/src/Inventor/samples/ivNodeKitStructure
//     [2] type:    ivNodeKitStructure SoCameraKit.
//     [3] The program prints a diagram of the scene graph and a table with 
//         information about each part.
//
//      A parent node that manages a collection of child nodes 
//      into a unit with the following structure:
//
//                            this
//                              |
//        ------------------------
//        |                      |               
//     "callbackList"       "transformGroup"
//                               |
//                      ----------------
//                      |              |
//                    "transform" "camera"
//                                           
////////////////////////////////////////////////////////////////////

class SoCameraKit : public SoBaseKit {

    SO_KIT_HEADER(SoCameraKit);

    // defines fields for the new parts in the catalog
    SO_KIT_CATALOG_ENTRY_HEADER(transformGroup);
    SO_KIT_CATALOG_ENTRY_HEADER(transform);
    SO_KIT_CATALOG_ENTRY_HEADER(camera);

  public:
    // constructor
    SoCameraKit();

  SoINTERNAL public:
    static void initClass();

  protected:
    virtual ~SoCameraKit();
};
#endif  /* _SO_CAMERA_KIT_ */
