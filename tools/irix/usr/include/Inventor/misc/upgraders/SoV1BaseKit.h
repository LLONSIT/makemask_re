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
 |      Defines the SoV1BaseKit class. A pure virtual class for all
 |      of the SoV1NodeKit classes
 |
 |   Author(s)          : Paul Isaacs, Thad Beier, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
*/

#ifndef  _SO_V1_BASE_KIT_
#define  _SO_V1_BASE_KIT_

#include <Inventor/misc/upgraders/SoV1CustomNode.h>
#include <Inventor/misc/upgraders/SoV1NodekitParts.h>
#include <Inventor/misc/upgraders/SoV1SubKit.h>

class SoSeparator;
class SbBox3f;
class SoBaseKit;

////////////////////////////////////////////////////////////////////
//    Class: SoV1BaseKit -- pure virtual class 
//
//  This is the base class for all node kits.
//
//  It contains only 'this' and a label node beneath it.
//  It's catalog is made to describe the following structure:
//
//                            this
//                              |
//                            "label"
//
////////////////////////////////////////////////////////////////////

SoEXTENDER class SoV1BaseKit : public SoV1CustomNode {

    //
    // DEFINE TYPEID AND NAME STUFF
    //
    SO_NODE_HEADER(SoV1BaseKit);

    //
    // DEFINE CATALOG OF CHILDREN
    //
    // Instead of calling SO_V1_SUBKIT_CATALOG_HEADER(className) here,
    // which is the norm for all nodekits, explicitly write the contents
    // of that macro, so as to expose the base class virtual function
    // getNodekitCatalog...
    //
  private:
    static SoV1NodekitCatalog *nodekitCatalog; /* design of this class */
  protected:
    static SoV1NodekitCatalog *getClassNodekitCatalog();

    /* Returns an SoV1NodekitCatalog for the node */
    virtual const SoV1NodekitCatalog *getNodekitCatalog() const;
    // ...end of contents of SO_V1_SUBKIT_CATALOG_HEADER

  public:

    //
    // CONSTRUCTOR
    //
    SoV1BaseKit();

    //
    // GETTING PARTS
    //
    // If no node is present, NULL will be returned, unless makeIfNeeded = TRUE
    // If makeIfNeeded = TRUE,
    // -- creates the node 
    // -- looks in the catalog to see if any extra nodes are needed to
    //    connect the node up the nodekit to 'this'
    // When 'makeIfNeeded' is TRUE, and the node is one that accumulates an
    // inherited state, this inherited state is calculated along the given path.
    //
    SoNode *getPart( const SbName &partName, const SoType &partType, 
		     SbBool makeIfNeeded, SoPath *inheritancePath = NULL);

    virtual SoNode *createNewNode();
    virtual void setUpNewNode(SoNode *newNode);
		     
  SoINTERNAL public:
    static void initClass();

    friend class SoV1NodekitCatalogEntry;
    friend class SoV1NodekitParts;

  protected:

    // Used during file reading by setUpNewNode. It goes through the
    // parts list of the upgrader and tries to pass each part to the
    // node created by createNewNode.
    SbBool tryToSetPartInNewNode( SoBaseKit *newNode,
				  SoNode *newPart, const SbName &newPartName );

    // If tryToSetPartInNewNode fails, then this routine is called.
    // (setUpNewNode will take care of the following two cases, but other
    // cases are handled by a subclass implementing dealWithUpgradedPart:
    // [1] if the partName is "label", then newNode->setName() is called 
    //     with the label's field value.
    // [2] if the part is a list-part, then it will be converted into an
    //     SoV1NodeKitListPart and its children will be added accordingly,
    //     assuming they are of permissable types.)
    virtual SbBool dealWithUpgradedPart( SoBaseKit *newNode,
				  SoNode *newPart, const SbName &newPartName );

    SbBool childOkInList(const SoNode *child,
			 const SbPList &listToCheck ) const;

    // like getPart, but it is allowed to get non-leaf parts.
    SoNode *getAnyPart( const SbName &partName, const SoType &partType, 
			SbBool makeIfNeeded, SbBool leafCheck, 
			SbBool publicCheck, SoPath *inheritancePath = NULL );
    SbBool setAnyPart( const SbName &partName, SoNode *from, SbBool anyPart );


    // parts list.
    SoV1NodekitParts	*nodekitPartsList;

    // called during construction to create parts list
    void createNodekitPartsList();

    // Return the node's partsList
    const SoV1NodekitParts *getNodekitPartsList() const 
			    { return nodekitPartsList; };

    virtual ~SoV1BaseKit();

  private:

    // All nodekits are subclassed from SoV1BaseKit, which is in turn derived 
    // from SoV1CustomNode.  When SoV1CustomNode reads the 
    // 'customData' field, it gives each derived class a chance to read 
    // a string (by calling the virtual function interpretCustomData).  
    // For SoV1BaseKit, this string is a list 
    // of parts that actually have been built by the nodekit.  Note that this
    // is a subset of all parts listed in the nodekitCatalog. The list 
    // written out has one name for each non-null entry in 
    // nodekitPartsList->nodeList
    virtual void                interpretCustomData(SoV1CustomNode *inst,
						    int index) const;
};

#endif  /* _SO_V1_BASE_KIT_ */
