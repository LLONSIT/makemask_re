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
 |	This file defines the SoIndexedFaceSet node class.
 |
 |   Author(s)		: Paul S. Strauss, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_INDEXED_FACE_SET_
#define  _SO_INDEXED_FACE_SET_

#include <Inventor/nodes/SoIndexedShape.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoIndexedFaceSet
//
//  Indexed set of faces. Each face consists of 3 or more vertices,
//  each of which is denoted by an integer index (from the coordIndex
//  field) into the current coordinates. Depending on the current
//  material and normal binding values, the materials and normals for
//  the faces or vertices may be accessed in order or indexed. If they
//  are indexed, the materialIndex and normalIndex fields are used.
//
//////////////////////////////////////////////////////////////////////////////

// This coordinate index indicates that the current face ends and the
// next face begins
#define SO_END_FACE_INDEX	(-1)

class SoNormalBundle;
class SoCoordinateElement;
class SoShapeStyleElement;

class SoIndexedFaceSet : public SoIndexedShape {

    SO_NODE_HEADER(SoIndexedFaceSet);

  public:
    // Inherits fields

    // Constructor
    SoIndexedFaceSet();

  SoEXTENDER public:
    // Implements actions
    virtual void	GLRender(SoGLRenderAction *action);

    // Generates default normals using the given normal bundle. 
    // Returns TRUE.
    virtual SbBool	generateDefaultNormals(SoState *state,
					       SoNormalBundle *nb);

    // Typedef of pointer to method on IndexedFaceSet;
    // This will be used to simplify declaration and initialization.
    typedef void (SoIndexedFaceSet::*PMFS)(SoGLRenderAction *);
					          
  SoINTERNAL public:
    static void		initClass();

    // This enum is used to indicate the current material or normal binding
    enum Binding {
	OVERALL, PER_FACE, PER_FACE_INDEXED, PER_VERTEX,
	    PER_VERTEX_INDEXED
    };

  protected:
    // Generates triangles representing faces
    virtual void	generatePrimitives(SoAction *action);

    // Overrides standard method to create an SoFaceDetail instance
    virtual SoDetail *	createTriangleDetail(SoRayPickAction *action,
					     const SoPrimitiveVertex *v1,
					     const SoPrimitiveVertex *v2,
					     const SoPrimitiveVertex *v3,
					     SoPickedPoint *pp);
    ~SoIndexedFaceSet();

  private:
    // Saves normal binding when generating primitives for picking
    Binding		savedNormalBinding;

    // Returns current material or normal binding from action's state
    Binding		getMaterialBinding(SoAction *action);
    Binding		getNormalBinding(SoAction *action,
					 SoNormalBundle *nb);

    // Figures out normals, if necessary. Returns TRUE if normals were
    // generated
    SbBool		figureNormals(SoState *state, SoNormalBundle *nb);

    // set numTris/Quads/Faces to -1 when notified
    virtual void	notify(SoNotList *list);
    
    // Set number of triangles/quads/faces, based on coordIndex array.
    void setupNumTrisQuadsFaces();
    
    // Number of triangles, quads, (n>4)-vertex faces
    int	    numTris, numQuads, numFaces;

    // 18*3ferent render functions; names are formed like this:
    // Om -- overall material
    // Fm -- per face material Vm -- per vertex material
    // On -- overall normal
    // Fn -- per face normal   Vm -- per vertex normal
    // T  -- per vertex texture coordinates
    void TriOmOn(SoGLRenderAction *); void TriOmOnT(SoGLRenderAction *);
    void TriOmFn(SoGLRenderAction *); void TriOmFnT(SoGLRenderAction *);
    void TriOmVn(SoGLRenderAction *); void TriOmVnT(SoGLRenderAction *);
    void TriFmOn(SoGLRenderAction *); void TriFmOnT(SoGLRenderAction *);
    void TriFmFn(SoGLRenderAction *); void TriFmFnT(SoGLRenderAction *);
    void TriFmVn(SoGLRenderAction *); void TriFmVnT(SoGLRenderAction *);
    void TriVmOn(SoGLRenderAction *); void TriVmOnT(SoGLRenderAction *);
    void TriVmFn(SoGLRenderAction *); void TriVmFnT(SoGLRenderAction *);
    void TriVmVn(SoGLRenderAction *); void TriVmVnT(SoGLRenderAction *);
    void QuadOmOn(SoGLRenderAction *); void QuadOmOnT(SoGLRenderAction *);
    void QuadOmFn(SoGLRenderAction *); void QuadOmFnT(SoGLRenderAction *);
    void QuadOmVn(SoGLRenderAction *); void QuadOmVnT(SoGLRenderAction *);
    void QuadFmOn(SoGLRenderAction *); void QuadFmOnT(SoGLRenderAction *);
    void QuadFmFn(SoGLRenderAction *); void QuadFmFnT(SoGLRenderAction *);
    void QuadFmVn(SoGLRenderAction *); void QuadFmVnT(SoGLRenderAction *);
    void QuadVmOn(SoGLRenderAction *); void QuadVmOnT(SoGLRenderAction *);
    void QuadVmFn(SoGLRenderAction *); void QuadVmFnT(SoGLRenderAction *);
    void QuadVmVn(SoGLRenderAction *); void QuadVmVnT(SoGLRenderAction *);
    void GenOmOn(SoGLRenderAction *); void GenOmOnT(SoGLRenderAction *);
    void GenOmFn(SoGLRenderAction *); void GenOmFnT(SoGLRenderAction *);
    void GenOmVn(SoGLRenderAction *); void GenOmVnT(SoGLRenderAction *);
    void GenFmOn(SoGLRenderAction *); void GenFmOnT(SoGLRenderAction *);
    void GenFmFn(SoGLRenderAction *); void GenFmFnT(SoGLRenderAction *);
    void GenFmVn(SoGLRenderAction *); void GenFmVnT(SoGLRenderAction *);
    void GenVmOn(SoGLRenderAction *); void GenVmOnT(SoGLRenderAction *);
    void GenVmFn(SoGLRenderAction *); void GenVmFnT(SoGLRenderAction *);
    void GenVmVn(SoGLRenderAction *); void GenVmVnT(SoGLRenderAction *);

    // Array of function pointers to render functions:
    static PMFS TriRenderFunc[32];
    static PMFS QuadRenderFunc[32];
    static PMFS GenRenderFunc[32];
};

#endif /* _SO_INDEXED_FACE_SET_ */
