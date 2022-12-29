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
 |   $Revision: 2.3 $
 |
 |   Description:
 |	This file defines the SoCallback node class.
 |
 |   Author(s)		: Paul S. Strauss, Nick Thompson, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_CALLBACK_
#define  _SO_CALLBACK_

#include <Inventor/SbLinear.h>
#include <Inventor/nodes/SoSubNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoCallback
//
//  The SoCallback node is a general mechanism that allows
//  applications to insert callback functions into a scene graph. The
//  callback function registered with the node is called each time
//  that node is traversed to perform any scene graph action. When the
//  callback function is called, it is passed a pointer to the action
//  being traversed and a user-data pointer that is registered with
//  the callback function. A NULL callback function pointer means that
//  no function will be called.
//
//////////////////////////////////////////////////////////////////////////////

// Callback functions registered with this node should be of this type.
typedef void SoCallbackCB(void *userData, SoAction *action);

class SoCallback : public SoNode {

    SO_NODE_HEADER(SoCallback);

  public:
    // Constructor
    SoCallback();

    // Sets pointer to callback function and user data
    void	setCallback(SoCallbackCB *func, void *userData = NULL)
	{ callbackFunc = func; callbackData = userData; }

  SoEXTENDER public:
    // Traversal methods for all the actions:
    virtual void	doAction(SoAction *action);
    virtual void	callback(SoCallbackAction *action);
    virtual void	GLRender(SoGLRenderAction *action);
    virtual void	getBoundingBox(SoGetBoundingBoxAction *action);
    virtual void	getMatrix(SoGetMatrixAction *action);
    virtual void	handleEvent(SoHandleEventAction *action);
    virtual void	pick(SoPickAction *action);
    virtual void	search(SoSearchAction *action);
    virtual void	write(SoWriteAction *action);

  SoINTERNAL public:
    static void		initClass();

  protected:
    virtual ~SoCallback();

    // Copies the contents of the given node into this instance
    virtual void	copyContents(const SoFieldContainer *fromFC,
				     SbBool copyConnections);

  private:
    SoCallbackCB	*callbackFunc;		// Function to call
    void		*callbackData;		// User data to pass it
};

#endif /* _SO_CALLBACK_ */
