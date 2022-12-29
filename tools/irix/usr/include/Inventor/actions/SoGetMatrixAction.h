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
 |	Defines the SoGetMatrixAction class
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_GET_MATRIX_ACTION_
#define  _SO_GET_MATRIX_ACTION_

#include <Inventor/SbLinear.h>
#include <Inventor/actions/SoSubAction.h>
#include <Inventor/SbViewportRegion.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoGetMatrixAction
//
//  For computing a cumulative transformation matrix and its inverse,
//  along with a cumulative texture transformation matrix and its inverse.
//
//  This action is unlike most others in that it does not traverse
//  downwards. When called on a node, it computes the matrix for just
//  that node. (This makes sense for transformation nodes, but not for
//  others, really.) When called on a path, it gathers the
//  transformation info for all nodes in the path and those that
//  affect nodes in the path, but it stops when it hits the last node
//  in the path; it does not traverse downwards from it as other
//  actions (such as rendering) do. This behavior makes the most sense
//  for this action.
//
//  EXTENDERS:  The model and texture matrix elements are not enabled
//  for this action.  Your transformation nodes must use the
//  getMatrix/getInverse calls and directly modify the matrices stored
//  in the action.
//
//////////////////////////////////////////////////////////////////////////////

class SoGetMatrixAction : public SoAction {

    SO_ACTION_HEADER(SoGetMatrixAction);

  public:
    // Constructor
    SoGetMatrixAction(const SbViewportRegion &newRegion);

    // Destructor
    virtual ~SoGetMatrixAction();

    // Sets current viewport region to use for action
    void		setViewportRegion(const SbViewportRegion &newRegion);

    // Returns current viewport region
    const SbViewportRegion &getViewportRegion() const	{ return vpRegion; }

    // Returns cumulative transformation matrix and inverse matrix
    // Extenders:  your transformation nodes should get these and
    // directly modify them.  Users:  you should treat these as
    // constants.
    SbMatrix &		getMatrix() 		{ return ctm; }
    SbMatrix &		getInverse()		{ return inv; }

    // Returns cumulative texture transformation matrix and inverse matrix
    // Extenders:  your textureTransformation nodes should get these
    // and directly modify them.  Users:  you should treat these as
    // constants.
    SbMatrix &		getTextureMatrix() 	{ return texCtm; }
    SbMatrix &		getTextureInverse()	{ return texInv; }

  SoINTERNAL public:
    static void		initClass();

  protected:
    // Initiates action on graph
    virtual void	beginTraversal(SoNode *node);

  private:
    SbMatrix		ctm;		// Cumulative transformation matrix
    SbMatrix		inv;		// Inverse transformation matrix
    SbMatrix		texCtm;		// Cumulative texture transf matrix
    SbMatrix		texInv;		// Inverse texture transf matrix
    SbViewportRegion	vpRegion;	// Current viewport region
};

#endif /* _SO_GET_MATRIX_ACTION_ */
