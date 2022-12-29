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
 |	This file defines the SoVertexShape node class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_VERTEX_SHAPE_
#define  _SO_VERTEX_SHAPE_

#include <Inventor/nodes/SoShape.h>
#include <Inventor/nodes/SoVertexProperty.h>
#include <Inventor/fields/SoSFNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVertexShape
//
//  Abstract vertex-based shape node class. All nodes derived from
//  this class are shapes that are constructed from vertices at some
//  or all of the current coordinates.  They all have vertexProperty nodes,
//  and vpCaches.
//
//////////////////////////////////////////////////////////////////////////////

class SoNormalBundle;
class SoNormalCache;
class SoState;


class SoVertexShape : public SoShape {

    SO_NODE_ABSTRACT_HEADER(SoVertexShape);
    
  public:
      SoSFNode		vertexProperty;

  SoEXTENDER public:
    // Subclasses may define this method to generate normals to use
    // when the normal binding is DEFAULT and there aren't enough
    // normals in the state. This should use the given SoNormalBundle
    // to generate the normals. Returns TRUE if normals were generated.
    virtual SbBool	generateDefaultNormals(SoState *state,
					       SoNormalBundle *nb);

  SoINTERNAL public:
    static void		initClass();

    // Redefines this to invalidate normal cache
    virtual void	notify(SoNotList *list);

  protected:
    // Constructor - makes this abstract
    SoVertexShape();

    virtual ~SoVertexShape();
    
    // Returns TRUE if the shape should be rendered. 
    // Checks for transparency in vertexProperty node before invoking
    // render action.
    virtual SbBool	shouldGLRender(SoGLRenderAction *action);
    
    // vpCache stores information from one render to the next about
    // what information needs to be grabbed from the state, etc.
    SoVertexPropertyCache	vpCache;

    // Sets up a cache to hold normals. This assumes the cache depends
    // on only the current coordinates, shape hints, and crease angle.
    void		setNormalCache(SoState *state,
				       int numNormals, const SbVec3f *normals);

    // Returns the current normal cache, or NULL if there is none
    SoNormalCache	*getNormalCache() const { return normalCache; }

  private:
    // This allows instances to cache normals that have been generated
    SoNormalCache	*normalCache;
};

#endif /* _SO_VERTEX_SHAPE_ */
