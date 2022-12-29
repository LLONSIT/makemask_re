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
 |   $Revision: 2.0 $
 |
 |   Description:
 |      Defines the SoV1NodekitParts class. An instance of this class is
 |      created for each instance of an Nodekit.
 |      Its function is to describe which 'parts' the nodekit has created
 |      from its class' SoV1NodekitCatalog.
 |      An SoV1NodekitParts contains a pointer to an SoV1NodekitCatalog and 
 |      a correlated list of nodes.
 |
 |      If a new part is asked for, this class uses the catalog as a 
 |      guide to create the part.
 |
 |   Author(s)          : Paul Isaacs, Thad Beier
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
*/

#ifndef  _SO_V1_NODEKIT_PARTS
#define  _SO_V1_NODEKIT_PARTS

#include <Inventor/misc/upgraders/SoV1NodekitCatalog.h>

class SoGroup;
class SoV1BaseKit;
class SoNode;
class SoPath;

////////////////////////////////////////////////////////////////////
//    Class: SoV1NodekitParts
////////////////////////////////////////////////////////////////////
SoEXTENDER class SoV1NodekitParts {

  SoEXTENDER public:
    // Instances of SoV1NodekitParts are created only by subclasses of SoV1BaseKit.

    // Constructor -- requires a catalog to build
    SoV1NodekitParts( SoV1BaseKit *rootOfKit, SoV1NodekitParts *partsSoFar = NULL );

    // Destructor
    ~SoV1NodekitParts();

    friend class SoV1BaseKit;

  private:
    const SoV1NodekitCatalog *catalog;   // the catalog to use in building
					  // parts
    int			    numEntries;   // must be made equal to numEntries
					  // in the catalog
    SoNode                  **nodeList;   // each 'part' is actually just
					  // a node
    SbBool makePart( const int partNum );
    SbBool replacePart( const int partNum, SoNode *newPartNode );

    SoNode *getPartFromThisCatalog( const int partNum, SbBool makeIfNeeded,
				      SbBool leafCheck, SbBool publicCheck );
    SbBool setPartFromThisCatalog( const int partNum, 
				     SoNode *newPartNode,
				     SbBool anyPart );

    // returns the part requested. If 'leafCheck' then it will only return 
    // leaves. If 'publicCheck', then it will only return public parts.
    // Otherwise it will also return interior parts.
    // Interior parts are ordinarily not obtainable through public methods.
    SoNode *getAnyPart( const SbName &nameOfPart, SbBool makeIfNeeded, 
			SbBool leafCheck, SbBool publicCheck );
    SbBool setAnyPart(  const SbName &nameOfPart, SoNode *newPartNode, 
			SbBool anyPart);

    // error check functions...
    SbBool partFoundCheck( int partNum );
    SbBool partIsLeafCheck( int partNum );
    SbBool partIsPublicCheck( int partNum );
    SbBool partIsNotListCheck( int partNum );
    SbBool verifyPartExistence( int partNum );
};

#endif  /* _SO_V1_NODEKIT_PARTS */
