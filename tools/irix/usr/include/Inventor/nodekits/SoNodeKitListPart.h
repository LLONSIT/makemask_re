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
 |   $Revision: 2.4 $
 |
 |   Description:
 |      Defines the SoNodeKitListPart class. 
 |      It behaves sort of like a group to the outsider, but it only allows
 |      certain types of nodes to be put beneath it.
 | 
 |      It contains hidden children, and is not derived from SoGroup.
 |      The addChild(), insertChild(), etc. methods all check that the
 |      new node is allowable beneath it.
 |
 |      The container node sits beteen the SoNodeKitListPart and the children.
 |      It's type is taken in the constructor, and must be derived from 
 |      SoGroup. By making the container an SoSeparator, SoSwitch, etc.,
 |      the SoNodeKitList can be made to encase its set of children in
 |      the appropriate behavior.
 |
 |   Author(s)          : Paul Isaacs
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
*/

#ifndef  _SO_NODE_KIT_LIST_PART_
#define  _SO_NODE_KIT_LIST_PART_

#include <Inventor/misc/SoChildList.h>
#include <Inventor/fields/SoSFName.h>
#include <Inventor/fields/SoMFName.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodekits/SoNodekitParts.h>
#include <Inventor/nodekits/SoBaseKit.h>

class SoGroup;

class SoGetMatrixAction;
class SoGLRenderAction;
class SoGetBoundingBoxAction;
class SoHandleEventAction;
class SoSearchAction;
class SoSearchAction;
class SoCallbackAction;

////////////////////////////////////////////////////////////////////
//    Class: SoNodeKitListPart
//
////////////////////////////////////////////////////////////////////

class SoNodeKitListPart : public SoNode {

    SO_NODE_HEADER(SoNodeKitListPart);

  public:

    // Constructor
    SoNodeKitListPart();

    // Returns the type of the contaner node. Default containerType is SoGroup.
    SoType	   getContainerType() const;
    void           setContainerType( SoType newContainerType );

    // By default, any type of node is allowed to be a child.
    // Once addChildType() is called, all children must belong to 
    // at least one of the types in the list.
    const SoTypeList &getChildTypes() const;
    void             addChildType( SoType typeToAdd );

    SbBool        isTypePermitted( SoType typeToCheck ) const;
    SbBool        isChildPermitted( const SoNode *child ) const;

    // Sends a string to the 'set' method on the container node.
    // This is how you can set the value of a switch node if the container
    // node is an SoSwitch, for example.
    void containerSet( const char *fieldDataString );


    // After this method is called, the types are locked in place.
    // Once called, the methods setContainerType() and addChildType()
    // will have no effect.
    // The types can not be unlocked. This gives the original creator of the
    // node a chance to "set it and forget it"
    void   lockTypes(); 
    SbBool isTypeLocked() const { return areTypesLocked; }


    // Child operations 
    void		addChild(SoNode *child);
    void		insertChild(SoNode *child, int childIndex);
    SoNode		*getChild(int index) const;
    int			findChild(SoNode *child) const;
    int			getNumChildren() const;
    void		removeChild(int index);
    void		removeChild(SoNode *child)
		{ removeChild( findChild(child));	}
    void		replaceChild(int index, SoNode *newChild);
    void		replaceChild( SoNode *oldChild, SoNode *newChild)
		{ replaceChild(findChild(oldChild), newChild); }

    // Depending on the type of the container, this may
    // or may not affect the state.
    virtual SbBool affectsState() const;


  SoEXTENDER public:

    // These functions implement all actions for nodekits.
    virtual void doAction( SoAction *action );
    virtual void callback( SoCallbackAction *action );
    virtual void GLRender( SoGLRenderAction *action );
    virtual void getBoundingBox( SoGetBoundingBoxAction *action );
    virtual void getMatrix(SoGetMatrixAction *action );
    virtual void handleEvent( SoHandleEventAction *action );
    virtual void pick( SoPickAction *action );
    virtual void search( SoSearchAction *action );

  SoINTERNAL public:
    static void initClass();

    // Returns pointer to children
    virtual SoChildList *getChildren() const;

  protected:

    SoGroup *getContainerNode();

    // Reads in from file. Takes care of setting parts and stuff.
    virtual SbBool readInstance(SoInput *in, unsigned short flags);

    SoChildList *children;

    // Copies the contents of the given nodekit into this instance
    virtual void	copyContents(const SoFieldContainer *fromFC,
				     SbBool copyConnections);

  protected:
    virtual ~SoNodeKitListPart();

  private:
    SoSFName containerTypeName;
    SoMFName childTypeNames;
    SoSFNode containerNode;

    SoTypeList childTypes;

    SbBool  areTypesLocked;

    friend class SoBaseKit;
};

#endif  /* _SO_NODE_KIT_LIST_PART_ */
