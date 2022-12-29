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
 |      Defines the SoV1AppearanceKit class. A parent node that manages 
 |      a collection of child nodes for
 |      complete description of the graphical appearance.
 |
 |   Author(s)          : Paul Isaacs, Thad Beier
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
*/

#ifndef  _SO_V1_APPEARANCE_KIT_
#define  _SO_V1_APPEARANCE_KIT_

#include <Inventor/misc/upgraders/SoV1BaseKit.h>
#include <Inventor/SoLists.h>


////////////////////////////////////////////////////////////////////
//    Class: SoV1AppearanceKit 
//
//      A parent node that manages a collection of child nodes
//      for complete description of the graphical appearance.
//
//    New nodes in this subclass are:
//         lightModel, drawStyle, material, complexity, texture2, and font
//
//    The structure of the catalog for this class is:
//
//                       this
//                         |
//   -----------------------------------------------------------------------
//   |         |           |      |        |        |             |        |
//  "label"    |    "environment" |"material" "complexity"        |     "font"
//             |                  |                    "texture2list"
//        "lightModel"     "drawStyle"        
//
//
////////////////////////////////////////////////////////////////////

SoEXTENDER class SoV1AppearanceKit : public SoV1BaseKit {

    // Define typeId and name stuff
    SO_NODE_HEADER(SoV1AppearanceKit);

    // Define catalog for children
    SO_V1_SUBKIT_CATALOG_HEADER(SoV1AppearanceKit);

  public:
    // constructor
    SoV1AppearanceKit();

    virtual SoNode *createNewNode();

    // If tryToSetPartInNewNode fails, then this routine is called.
    // It will fail if the part read from file was called "texture2List"
    // This part has been changed to a single noded part, "texture2"
    // We will use just the first child of the list and set it as the "texture2"
    // It will also print a warning.
    virtual SbBool dealWithUpgradedPart( SoBaseKit *newNode,
				  SoNode *newPart, const SbName &newPartName );
  SoINTERNAL public:
    static void initClass();

    static SoNodeList *getKitsWithUnusedTextureXfs();
    static SoNodeList *getUnusedTextureXfs();

  protected:

    // In the case where an SoV1Texture2 node has the translation rotation
    // scaleFactor or center field set, it will return a group containing
    // an SoTexture2Transform and an SoTexture2 node.
    // The SoV1AppearanceKit can not have a group part, so it pulls out the
    // SoTexture2 node and sets it as "transform."
    // Instead of just throwing away the SoTexture2Transform, it puts it in
    // this static variable so that other nodes can get at it.
    // For example, the SoV1GroupKit overloads the virtual function 
    // setUpNewNode to get this texture2Transform and copy its
    // values into its "texture2Transform" part.
    static SoNodeList *kitsWithUnusedTextureXfs;
    static SoNodeList *unusedTextureXfs;

    virtual ~SoV1AppearanceKit();
};

#endif  /* _SO_V1_APPEARANCE_KIT_ */
