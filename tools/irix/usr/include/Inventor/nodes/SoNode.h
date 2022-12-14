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
 |   $Revision: 2.8 $
 |
 |   Description:
 |	This file defines the base SoNode class.
 |
 |   Author(s)		: Paul S. Strauss, Nick Thompson
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_NODE_
#define  _SO_NODE_

#include <Inventor/fields/SoFieldContainer.h>
#include <Inventor/SoLists.h>
#include <Inventor/SbString.h>
#include <Inventor/SoType.h>

class SoAction;
class SoCallbackAction;
class SoChildList;
class SoFieldData;
class SoGLRenderAction;
class SoGetBoundingBoxAction;
class SoGetMatrixAction;
class SoHandleEventAction;
class SoInput;
class SoOutput;
class SoPickAction;
class SoRayPickAction;
class SoSearchAction;
class SoWriteAction;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoNode
//
//  Base SoNode class (abstract).
//
//////////////////////////////////////////////////////////////////////////////


class SoNode : public SoFieldContainer {

  public:

    // Turns override flag on or off
    void		setOverride(SbBool state);

    // Returns the state of the override flag
    SbBool		isOverride() const		{ return override; }

    // Returns type identifier for SoNode class
    static SoType	getClassTypeId()	{ return classTypeId; }

    // Creates and returns an exact copy of the node. If the node is a
    // group, it copies the children as well. If the copyConnections
    // flag is TRUE (it is FALSE by default), any connections to (but
    // not from) fields of the node are copied, as well.
    SoNode *		copy(SbBool copyConnections = FALSE) const;

    // Returns TRUE if a node has an affect on the state during
    // traversal. The default method returns TRUE. Node classes (such
    // as SoSeparator) that isolate their effects from the rest of the
    // graph override this method to return FALSE.
    virtual SbBool	affectsState() const;

    // A node's name can be set using setName() (which is a method on
    // SoBase).  These methods allow nodes to be looked up by name.
    static SoNode *	getByName(const SbName &name);
    static int		getByName(const SbName &name, SoNodeList &list);

  SoEXTENDER public:

    // This method performs the "typical" operation of a node for any
    // action. The default implementation does nothing.
    virtual void	doAction(SoAction *action);

    // These virtual functions implement all of the actions for nodes,
    // Most of the default implementations do nothing.
    virtual void	GLRender(SoGLRenderAction *action);
    virtual void	callback(SoCallbackAction *action);
    virtual void	getBoundingBox(SoGetBoundingBoxAction *action);
    virtual void	getMatrix(SoGetMatrixAction *action);
    virtual void	handleEvent(SoHandleEventAction *action);
    virtual void	pick(SoPickAction *action);
    virtual void	rayPick(SoRayPickAction *action);
    virtual void	search(SoSearchAction *action);
    virtual void	write(SoWriteAction *action);

    // These methods make render traversal faster by implementing
    // different rendering paths corresponding to different action
    // path codes.  The SoNode methods just call GLRender.
    virtual void	GLRenderBelowPath(SoGLRenderAction *action);
    virtual void	GLRenderInPath(SoGLRenderAction *action);
    virtual void	GLRenderOffPath(SoGLRenderAction *action);

    // These virtual functions are called when a node gains or loses
    // status as "grabber" of events (see HandleEventAction::setGrabber()).
    // The default methods do nothing.
    virtual void	grabEventsSetup();
    virtual void	grabEventsCleanup();

  SoINTERNAL public:
    enum Stage {
	FIRST_INSTANCE,		// First real instance being constructed
	PROTO_INSTANCE,		// Prototype instance being constructed
	OTHER_INSTANCE		// Subsequent instance being constructed
    };

    // Initializes base node class
    static void		initClass();

    // Initialize ALL Inventor node classes
    static void		initClasses();

    // Initiates notification from an instance.
    virtual void	startNotify();

    // Propagates modification notification through an instance.
    virtual void	notify(SoNotList *list);

    // Returns the unique id for a node
    uint32_t		getNodeId() const	{ return uniqueId; }

    // Returns the next available unique id
    static uint32_t	getNextNodeId()	{ return nextUniqueId; }

    // Returns pointer to children, or NULL if none
    virtual SoChildList *getChildren() const;

    // Writes instance to SoOutput. (Used for either stage of writing.)
    virtual void	writeInstance(SoOutput *out);

    // Returns the index of this node in the action/method table,
    // given its type.
    static int		getActionMethodIndex(SoType t)
	    { return t.getData(); }

    // Recursively adds this node and all nodes under it to the copy
    // dictionary. Returns the copy of this node.
    virtual SoNode *	addToCopyDict() const;

    // Copies the contents of the given node into this instance. The
    // default implementation copies just field values and the name.
    virtual void	copyContents(const SoFieldContainer *fromFC,
				     SbBool copyConnections);

    // Copies an instance that is encountered through a field connection
    virtual SoFieldContainer *	copyThroughConnection() const;

  protected:
    // This is used by the field-inheritence mechanism, hidden in
    // the SoSubNode macros
    static const SoFieldData **getFieldDataPtr() { return NULL; }

    // Constructor, destructor
    SoNode();
    virtual ~SoNode();

    // Unique id for this node.
    uint32_t	uniqueId;

    // Next available unique id
    static uint32_t nextUniqueId;

    // Next index into the action method table
    static int		nextActionMethodIndex;

  private:
    static SoType	classTypeId;	// Type identifier

    SbBool		override;	// TRUE if node overrides others

    // These static methods are registered with the database - they
    // simply call the appropriate virtual function
    static void		callbackS(SoAction *, SoNode *);
    static void		GLRenderS(SoAction *, SoNode *);
    static void		getBoundingBoxS(SoAction *, SoNode *);
    static void		getMatrixS(SoAction *, SoNode *);
    static void		handleEventS(SoAction *, SoNode *);
    static void		pickS(SoAction *, SoNode *);
    static void		rayPickS(SoAction *, SoNode *);
    static void		searchS(SoAction *, SoNode *);
    static void		writeS(SoAction *, SoNode *);
};

#endif /* _SO_NODE_ */
