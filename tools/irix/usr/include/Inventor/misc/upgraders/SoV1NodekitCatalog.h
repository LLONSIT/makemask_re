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
 |      Defines the SoV1NodekitCatalog class. This class is used to 
 |      describe the subgraphs that make up different classes of 
 |      nodekit.	
 |
 |   Author(s)          : Paul Isaacs, Thad Beier
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
*/

#ifndef  _SO_V1_NODEKIT_CATALOG
#define  _SO_V1_NODEKIT_CATALOG

#include <Inventor/SbString.h>
#include <Inventor/SbPList.h>
#include <Inventor/SoType.h>

#define SO_V1_CATALOG_NAME_NOT_FOUND -1

////////////////////////////////////////////////////////////////////
//
//    Class: SoV1NodekitCatalogEntry
//
//    an internal class that should be accessed only by an SoV1NodekitCatalog
//
//
////////////////////////////////////////////////////////////////////
SoINTERNAL class SoV1NodekitCatalogEntry {
    private:
	SbName     name;		// Reference name of this entry 
	SoType     type;		// Type of node allowable for setting
					// this entry. 'type' may be an 
					// abstract node type
	SoType     defaultType;		// Type of node to create if the nodekit
					// is asked to build this part itself.
					// May not be an abstract node type.
	SbBool     leafPart;            // Is this entry a leaf node in the 
					// nodekit's structure?
	SbName     parentName;		// Reference name of this entry's parent
	SbName     rightSiblingName;    // Name of right sibling of the entry
	SbBool     listPart;            // Is this entry a list of nodes?
	SbPList    listItemTypes;       // If so, what types of nodes may
					// it contain?
	SbBool     publicPart;          // Can a user be given a pointer to
					// this part?
    SoINTERNAL public:
	// constructor
	SoV1NodekitCatalogEntry(const SbName &theName, 
	      const SoType &theType,       const SoType &theDefaultType, 
	      const SbName &theParentName, const SbName &theRightSiblingName, 
		    SbBool theListPart,    const SbPList &theListItemTypes,
		    SbBool thePublicPart );

	// clone exactly, or make a clone with a given type...
	SoV1NodekitCatalogEntry *clone() const;           
	SoV1NodekitCatalogEntry *clone( const SoType &newType,
				      const SoType &newDefaultType ) const; 

	// inquiry functions:
	const SbName  &getName() const { return name; }
	const SoType  &getType() const { return type; }
	const SoType  &getDefaultType() const { return defaultType; }
	SbBool        isLeaf() const { return leafPart; }
	const SbName  &getParentName() const { return parentName; }
	const SbName  &getRightSiblingName() const { return rightSiblingName; }
	SbBool        isList() const { return listPart; }
	const SbPList &getListItemTypes() const { return listItemTypes; }
	SbBool        isPublic() const { return publicPart; }

	// For adding to the set of node types allowed beneath a list...
	void addListItemType( const SoType &typeToAdd );

	// these should only by used by catalogs when an entry
	// is given a new child or left sibling...
	void setLeaf( SbBool newLeafPart ) { leafPart = newLeafPart; }
	void setRightSiblingName( const SbName &newN ) { rightSiblingName = newN; }
	// This should only by used by catalogs when an entry is changing
	// type and/or defaultType
	void setTypes( const SoType &newType, const SoType &newDefaultType )
			    { type = newType; defaultType = newDefaultType; }

	// recursively search this entry for 'name to find' in the 
	// templates of this entry and its descendants
	SbBool recursiveSearch( const SbName &nameToFind, 
				SbPList *typesChecked) const;

	void printCheck() const; // prints the contents of this entry
};

////////////////////////////////////////////////////////////////////
//    Class: SoV1NodekitCatalog
////////////////////////////////////////////////////////////////////
SoEXTENDER class SoV1NodekitCatalog {

  public:

    // initializes static variables. 
    static void initClass();

    // How many entries in this catalog?
    int        getNumEntries() const { return numEntries; }

    // inquiry routines, to find out about entries in the catalog,
    // Questions may be asked based on name or partNumber.
    int		     getPartNumber(      const SbName &theName ) const;
    const SbName     &getName(		 int    thePartNumber ) const;
    const SoType     &getType(		 int    thePartNumber ) const;
    const SoType     &getType(		 const SbName &theName ) const;
    const SoType     &getDefaultType(	 int    thePartNumber ) const;
    const SoType     &getDefaultType(	 const SbName &theName ) const;
    SbBool           isLeaf(		 int    thePartNumber ) const;
    SbBool           isLeaf(		 const SbName &theName ) const;
    const SbName     &getParentName(	 int    thePartNumber ) const;
    const SbName     &getParentName(	 const SbName &theName ) const;
    int              getParentPartNumber(int    thePartNumber ) const;
    int              getParentPartNumber(const SbName &theName ) const;
    const SbName     &getRightSiblingName(int    thePartNumber ) const;
    const SbName     &getRightSiblingName(const SbName &theName ) const;
    int              getRightSiblingPartNumber(int thePartNumber ) const;
    int              getRightSiblingPartNumber(const SbName &theName ) const;
    SbBool           isList(		 int    thePartNumber ) const;
    SbBool           isList(		 const SbName &theName ) const;
    const SbPList    &getListItemTypes( int    thePartNumber ) const;
    const SbPList    &getListItemTypes( const SbName &theName ) const;
    SbBool           isPublic(		 int    thePartNumber ) const;
    SbBool           isPublic(		 const SbName &theName ) const;

  SoEXTENDER public:
    // Catalogs are only constructed, destructed, cloned or added to  
    // by subclasses of SoV1BaseKit.
    // This should be accomplished using the macros provided in SoSubKit.h

    // Constructor
    SoV1NodekitCatalog();

    // Destructor
    ~SoV1NodekitCatalog();

    // Make a new identical copy, but you must give the node type for 'this' 
    // (where 'this' is the top level node in the template )
    SoV1NodekitCatalog *clone( const SoType &typeOfThis ) const;

    // Adding entries
    SbBool addEntry(const SbName &theName, 
		    const SoType &theType, const SoType &theDefaultType,
		    const SbName &theParentName, 
	            const SbName &theRightSiblingName, SbBool theListPart, 
	            const SoType &theListItemType,
			  SbBool thePublicPart);

    // For adding to the set of node types allowed beneath a list...
    void addListItemType(int    thePartNumber,const SoType &typeToAdd);
    void addListItemType(const SbName &theName,     const SoType &typeToAdd);

    // For changing the type and defaultType of an entry.
    // The new types must be subclasses of the types already existing in the
    // entry.  
    // For example, in SoV1ShapeKit, the part "shape" has type SoShape and
    // default type SoSphere.  Any shape node is acceptable, but be default a 
    // sphere will be built.
    // Well, when creating the SoV1VertexShapeKit class, a call of:
    //    narrowTypes( "shape", SoVertexShape::getClassTypeId(), 
    //			        SoFaceSet::getClassTypeId())
    // might be used.  This would reflect the fact that:
    // Only vertext shapes may be put in the "shape"  part, not just any shape.
    // And also, by default, a faceSet will be built, not a sphere.
    void narrowTypes( const SbName &theName, const SoType &newType, 
		      const SoType &newDefaultType );

  SoINTERNAL public:
    // used by SoV1NodekitParts to search through catalogs.
    // recursively search a given part for 'name to find' in the 
    // templates of that entry and its descendants
    SbBool recursiveSearch( int partNumber, const SbName &nameToFind, 
			    SbPList *typesChecked) const;

    void printCheck() const; // prints the contents of this catalog

  private:

    static const SbName  *emptyName;
    static const SbPList *emptyList;
    static SoType  *badType;

    int 		  numEntries;   // how many entries?
    SoV1NodekitCatalogEntry **entries;    // the array of entries
    SbDict                partNameDict; // For fast lookup of part numbers

    // Used for testing various aspects of new entries into a catalog
    SbBool    checkName( const SbName &theName );
    SbBool    checkNewName( const SbName &theName );
    SbBool    checkNewTypes( const SoType &theType, 
			     const SoType &theDefaultType );
    SbBool    checkAndGetParent(    const SbName &theName, 
    				    const SbName &theParentName, 
				    SoV1NodekitCatalogEntry *& parentEntry );
    SbBool    checkAndGetSiblings(  const SbName &theParentName, 
				    const SbName &theRightSiblingName, 
				    SoV1NodekitCatalogEntry *& leftEntry,
				    SoV1NodekitCatalogEntry *& rightEntry );
    SbBool    checkCanTypesBeList(  const SoType &theType,
    				    const SoType &theDefaultType );

};

#endif  /* _SO_V1_NODEKIT_CATALOG */
