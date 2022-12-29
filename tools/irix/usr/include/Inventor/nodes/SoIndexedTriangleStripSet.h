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
 |   $Revision: 2.6 $
 |
 |   Description:
 |	This file defines the SoIndexedTriangleStripSet node class.
 |
 |   Author(s)		: Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_INDEXED_TRIANGLE_SET_
#define  _SO_INDEXED_TRIANGLE_SET_

#include <Inventor/nodes/SoIndexedShape.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/nodes/SoVertexProperty.h>
class SoCoordinateElement;


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoIndexedTriangleStripSet
//
//  Indexed set of triangles strips.  Strips are separated by the
//  special index SO_END_STRIP_INDEX (-1).  The N indices in the strip
//  define N-2 triangles, which are formed by indexing into the
//  current coordinates. Depending on the current material and normal
//  binding values, the materials and normals for the triangles or
//  vertices may be accessed in order or indexed. If they are indexed,
//  the materialIndex and normalIndex fields are used.
//
//////////////////////////////////////////////////////////////////////////////

// This coordinate index indicates that the current triangle ends and the
// next triangle begins
#define SO_END_STRIP_INDEX	(-1)

class SoNormalBundle;
class SoCoordinateElement;

class SoIndexedTriangleStripSet : public SoIndexedShape {

    SO_NODE_HEADER(SoIndexedTriangleStripSet);

  public:
    // Constructor
    SoIndexedTriangleStripSet();

  SoEXTENDER public:
    // Implements actions
    virtual void	GLRender(SoGLRenderAction *action);

    // Generates default normals using the given normal bundle. 
    // Returns TRUE.
    virtual SbBool	generateDefaultNormals(SoState *state,
					       SoNormalBundle *nb);
					       
    //Typedef of pointer to method on IndexedTriangleStripSet;
    //This will be used to simplify declaration and initialization.
    typedef void (SoIndexedTriangleStripSet::*PMTSS)(SoGLRenderAction *);
					          
  SoINTERNAL public:
    static void		initClass();

    // This enum is used to indicate the current material or normal binding
    enum Binding {
	OVERALL,
	PER_STRIP,	PER_STRIP_INDEXED,
	PER_TRIANGLE,	PER_TRIANGLE_INDEXED,
	PER_VERTEX,	PER_VERTEX_INDEXED
    };
    
  protected:
    // Generates triangles representing strips
    virtual void	generatePrimitives(SoAction *action);
    

    // Overrides standard method to create an SoFaceDetail instance
    virtual SoDetail *	createTriangleDetail(SoRayPickAction *action,
					     const SoPrimitiveVertex *v1,
					     const SoPrimitiveVertex *v2,
					     const SoPrimitiveVertex *v3,
					     SoPickedPoint *pp);

    ~SoIndexedTriangleStripSet();

  private:
    // Returns current material or normal binding from action's state
    Binding		getMaterialBinding(SoAction *action);
    Binding		getNormalBinding(SoAction *action,
					 SoNormalBundle &nb);

    // Figures out normals, if necessary. Returns TRUE if normals were
    // generated
    SbBool		figureNormals(SoState *state, SoNormalBundle *nb);
    
    // Reset numVertices/numStrips when notified
    virtual void	notify(SoNotList *list);
    
    // Fill in numStrips, numTriangles and numVertices[]
    void countStripsAndTris();
    
    // Number of strips, total number of triangles, and number of
    // vertices per strip:
    int		numStrips;
    int		numTriangles;
    int *	numVertices;

    // 32 different render functions; names are formed like this:
    // Om -- overall material  Pm -- per part material
    // Fm -- per face material Vm -- per vertex material
    // On -- overall normal    Pm -- per part normal
    // Fn -- per face normal   Vm -- per vertex normal
    // T  -- per vertex texture coordinates
    void OmOn(SoGLRenderAction *); void OmOnT(SoGLRenderAction *);
    void OmPn(SoGLRenderAction *); void OmPnT(SoGLRenderAction *);
    void OmFn(SoGLRenderAction *); void OmFnT(SoGLRenderAction *);
    void OmVn(SoGLRenderAction *); void OmVnT(SoGLRenderAction *);
    void PmOn(SoGLRenderAction *); void PmOnT(SoGLRenderAction *);
    void PmPn(SoGLRenderAction *); void PmPnT(SoGLRenderAction *);
    void PmFn(SoGLRenderAction *); void PmFnT(SoGLRenderAction *);
    void PmVn(SoGLRenderAction *); void PmVnT(SoGLRenderAction *);
    void FmOn(SoGLRenderAction *); void FmOnT(SoGLRenderAction *);
    void FmPn(SoGLRenderAction *); void FmPnT(SoGLRenderAction *);
    void FmFn(SoGLRenderAction *); void FmFnT(SoGLRenderAction *);
    void FmVn(SoGLRenderAction *); void FmVnT(SoGLRenderAction *);
    void VmOn(SoGLRenderAction *); void VmOnT(SoGLRenderAction *);
    void VmPn(SoGLRenderAction *); void VmPnT(SoGLRenderAction *);
    void VmFn(SoGLRenderAction *); void VmFnT(SoGLRenderAction *);
    void VmVn(SoGLRenderAction *); void VmVnT(SoGLRenderAction *);

    // Array of function pointers to render functions:
    static PMTSS renderFunc[32];
    
    
};

#endif /* _SO_INDEXED_TRIANGLE_SET_ */
