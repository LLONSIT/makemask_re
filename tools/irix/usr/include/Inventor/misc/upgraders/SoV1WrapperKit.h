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
 |      Defines the SoV1WrapperKit class. 
 |      A group kit which has a place to attach any inventor subgraph
 |      of any unspecified structure.
 |
 |   Author(s)          : Paul Isaacs, Thad Beier
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
*/

#ifndef  _SO_V1_WRAPPER_KIT_
#define  _SO_V1_WRAPPER_KIT_

#include <Inventor/misc/upgraders/SoV1GroupKit.h>


////////////////////////////////////////////////////////////
// Class: Wrapper
//
//  A grouping in which a programmer can shove whatever
//  subgraph (s)he wants
//
//    New nodes in this subclass are:
//         contents
//
//  Adds a node before the "childList"
//  from the SoV1GroupKit class.
//
// This results in the following structure:
//
//                            this
//        |---------------------|
//     "label"     |      "topSeparator"
//            "callbackList"    |
//      ----------------------------------------------------------
//      |       |           |     |                         |    |
//  "pickStyle" |    "transform"  |                         |    |
//     "appearance"  "texture2Transform"                    |    |
//                                                          |    |
//                                                          |    |
//                                                          |    |
//                                                          |  "childList"
//                                                          |      
//                                                       "contents"
//
////////////////////////////////////////////////////////////
SoEXTENDER class SoV1WrapperKit : public SoV1GroupKit {

    // Define typeId and name stuff
    SO_NODE_HEADER(SoV1WrapperKit);

    // Define catalog for children
    SO_V1_SUBKIT_CATALOG_HEADER(SoV1WrapperKit);

  public:
    // constructor
    SoV1WrapperKit();

    virtual SoNode *createNewNode();
    
    SoINTERNAL public:
    static void initClass();

  protected:
    virtual ~SoV1WrapperKit();
};

#endif  /* _SO_V1_WRAPPER_KIT_ */
