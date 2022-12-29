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
 |      Defines the SoNodekitParts class. An instance of this class is
 |      created for each instance of an Nodekit.
 |      Its function is to describe which 'parts' the nodekit has created
 |      from its class' SoNodekitCatalog.
 |      An SoNodekitParts contains a pointer to an SoNodekitCatalog and 
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

#ifndef  _SO_NODEKIT_PARTS
#define  _SO_NODEKIT_PARTS

#include <Inventor/nodekits/SoNodekitCatalog.h>

class SoNodeKitListPart;
class SoBaseKit;
class SoNode;
class SoFullPath;
class SoSFNode;

////////////////////////////////////////////////////////////////////
//    Class: SoNodekitParts
////////////////////////////////////////////////////////////////////
SoEXTENDER class SoNodekitParts {

  SoEXTENDER public:
    // Instances of SoNodekitParts are created only by subclasses of SoBaseKit.

    // Constructor -- requires a catalog to build
    SoNodekitParts( SoBaseKit *rootOfKit );

    // Destructor
    ~SoNodekitParts();

    friend class SoBaseKit;

  private:
    const SoNodekitCatalog *catalog;   // the catalog to use in building
					  // parts
    int			    numEntries;   // must be made equal to numEntries
					  // in the catalog
    SoBaseKit               *rootPointer; // Pointer to the part 'this'
    SoSFNode                **fieldList;  // each 'part' is actually just
					  // a node, stored in a field

    SbBool makePart( const int partNum );
    SbBool replacePart( const int partNum, SoNode *newPartNode );
    void   unregisterDescendants( const int partNum );

    SoNode *getPartFromThisCatalog( const int partNum, SbBool makeIfNeeded,
				      SbBool leafCheck, SbBool publicCheck, 
				      SbBool &existedBefore );
    SoFullPath *createPathToPartFromThisCatalog( const int partNum, 
		    SbBool makeIfNeeded, SbBool leafCheck, 
		    SbBool publicCheck,  SbBool &existedBefore );
    SbBool setPartFromThisCatalog( const int partNum, 
				     SoNode *newPartNode,
				     SbBool anyPart );

    SoNode *getSingleNamePart( const SbName &nameOfPart, SbBool makeIfNeeded,
				SbBool leafCheck, SbBool publicCheck, 
				SbBool &existedBefore );
    SoFullPath *getSingleNamePathToPart( const SbName &nameOfPart, 
				 SbBool makeIfNeeded, SbBool leafCheck, 
				 SbBool publicCheck, SbBool &existedBefore );
    SbBool setSingleNamePart( const SbName &nameOfPart, SoNode *newPartNode,
				SbBool anyPart );

    // returns the part requested. If 'leafCheck' then it will only return 
    // leaves. If 'publicCheck', then it will only return public parts.
    // Otherwise it will also return interior parts.
    // Interior parts are ordinarily not obtainable through public methods.
    SoNode *getAnyPart( const SbName &nameOfPart, SbBool makeIfNeeded, 
			SbBool leafCheck, SbBool publicCheck );
    SoNode *getAnyPart( const SbName &nameOfPart, SbBool makeIfNeeded, 
			SbBool leafCheck, SbBool publicCheck, 
			SbBool &existedBefore);
    SoFullPath *createPathToAnyPart( const SbName &nameOfPart, 
		    SbBool makeIfNeeded, SbBool leafCheck, SbBool publicCheck );
    SoFullPath *createPathToAnyPart( const SbName &nameOfPart, 
		    SbBool makeIfNeeded, SbBool leafCheck, 
		    SbBool publicCheck,  SbBool &existedBefore );
    SbBool setAnyPart(  const SbName &nameOfPart, SoNode *newPartNode, 
			SbBool anyPart);

    // parse a string like 'nameOfList[elementNum]' into two parts...
    // Destructive to parseString, so give it a copy if you care.
    // Replaces the '[' with an end-of-string and reads elementNum 
    // into the integer given
    SbBool parseListItem( char *parseString, int &index );

    // help to delete unneeded parts...
    SbBool partIsNonLeafAndMayBeDeleted( int partNum );

    // error check functions...
    SbBool partFoundCheck( int partNum );
    SbBool partIsLeafCheck( int partNum );
    SbBool partIsPublicCheck( int partNum );
    SbBool verifyPartExistence( int partNum );

    // builds a path from the entry 'this' down to the entry given
    // by 'nameOfPart'. Assumes that 'theNode' matches 'nameOfPart'
    SoFullPath *createPathDownTo( const SbName &nameOfPart, SoNode *theNode );

    // appends pathB after pathA and returns result.
    // result is NULL if either path is NULL or if pathA->tail != pathB->head
    SoFullPath *addPaths( const SoFullPath *pathA, 
			    const SoFullPath *pathB ) const;
};

#endif  /* _SO_NODEKIT_PARTS */
