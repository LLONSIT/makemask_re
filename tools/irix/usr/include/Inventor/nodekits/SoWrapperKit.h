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
 |      Defines the SoWrapperKit class. 
 |      A group kit which has a place to attach any inventor subgraph
 |      of any unspecified structure.
 |
 |   Author(s)          : Paul Isaacs, Thad Beier
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
*/

#ifndef  _SO_WRAPPER_KIT_
#define  _SO_WRAPPER_KIT_

#include <Inventor/nodekits/SoSeparatorKit.h>


////////////////////////////////////////////////////////////
// Class: SoWrapperKit
//
// NOTE TO DEVELOPERS:
//     For info about the structure of SoWrapperKit:
//     [1] compile: /usr/share/src/Inventor/samples/ivNodeKitStructure
//     [2] type:    ivNodeKitStructure SoWrapperKit.
//     [3] The program prints a diagram of the scene graph and a table with 
//         information about each part.
//
//  A grouping in which a programmer can shove whatever
//  subgraph (s)he wants
//
//    New nodes in this subclass are:
//         contents
//
//  Adds a node before the "childList"
//  from the SoSeparatorKit class.
//
// This results in the following structure:
//
//                            this
//              ----------------|
//              |          "topSeparator"
//          "callbackList"      |
//      ----------------------------------------------------------
//      |       |           |     |          |    |              |
//  "pickStyle" |    "transform"  |          |    |              |
//     "appearance"  "texture2Transform"     |    |              |
//                                           |    |              |
//                                           |    |              |
//                                           |    |          "contents"    
//                                           |  "localTransform"
//                                           |      
//                                        "childList"
//
////////////////////////////////////////////////////////////
class SoWrapperKit : public SoSeparatorKit {

    SO_KIT_HEADER(SoWrapperKit);

    // defines fields for the new parts in the catalog
    SO_KIT_CATALOG_ENTRY_HEADER(localTransform);
    SO_KIT_CATALOG_ENTRY_HEADER(contents);

  public:
    // constructor
    SoWrapperKit();

  SoINTERNAL public:
    static void initClass();

  protected:
    virtual ~SoWrapperKit();
};

#endif  /* _SO_WRAPPER_KIT_ */
