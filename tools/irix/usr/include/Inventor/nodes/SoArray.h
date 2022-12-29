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
 |	This file defines the SoArray node class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_ARRAY_
#define  _SO_ARRAY_

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/nodes/SoGroup.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoArray
//
//  Array group node: creates an IxJxK array. Each element in the
//  array is drawn by traversing all of the children of this node,
//  saving and restoring state before and after each element. I, J,
//  and K are given by the numElements1, numElements2, and
//  numElements3 fields. The 3D vector separating the centers of
//  adjacent elements in each of the three directions is given by
//  separation1, separation2, and separation3. The origin field
//  indicates whether the array is positioned with the current
//  object-space origin at the center of the first element, the last
//  element, or at the center of all elements.
//
//////////////////////////////////////////////////////////////////////////////

class SoArray : public SoGroup {

    SO_NODE_HEADER(SoArray);

  public:

    // Fields
    SoSFShort		numElements1;	// Number of elements in 1st direction
    SoSFShort		numElements2;	// Number of elements in 2nd direction
    SoSFShort		numElements3;	// Number of elements in 3rd direction

    SoSFVec3f		separation1;	// Separation vector in 1st direction
    SoSFVec3f		separation2;	// Separation vector in 2nd direction
    SoSFVec3f		separation3;	// Separation vector in 3rd direction

    enum Origin {		// Array origin:
	FIRST,				// Origin at first element
	CENTER,				// Origin at center of elements
	LAST				// Origin at last element
    };

    SoSFEnum		origin;		// Base point

    // Constructor and destructor
    SoArray();

    // Overrides default method on SoNode to return FALSE since arrays
    // are effectively separators
    virtual SbBool	affectsState() const;

  SoEXTENDER public:
    // Implement actions
    virtual void	doAction(SoAction *action);
    virtual void	callback(SoCallbackAction *action);
    virtual void	GLRender(SoGLRenderAction *action);
    virtual void	pick(SoPickAction *action);
    virtual void	getBoundingBox(SoGetBoundingBoxAction *action);
    virtual void	handleEvent(SoHandleEventAction *action);
    virtual void	getMatrix(SoGetMatrixAction *action);
    virtual void	search(SoSearchAction *action);

  SoINTERNAL public:
    static void		initClass();

  protected:
    virtual ~SoArray();
};

#endif /* _SO_ARRAY_ */
