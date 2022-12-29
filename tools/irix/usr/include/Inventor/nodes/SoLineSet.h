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
 |   $Revision: 2.9 $
 |
 |   Description:
 |	This file defines the SoLineSet node class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_LINE_SET_
#define  _SO_LINE_SET_

#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/nodes/SoNonIndexedShape.h>

class SoState;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoLineSet
//
//  Set of (poly)lines. Each line consists of 2 or more vertices,
//  taken in order from the current coordinates, which are joined to
//  form segments. The startIndex field gives the starting coordinate
//  index for the first line. If materials or normals are bound to
//  vertices, they will begin at that index, as well; otherwise, they
//  will start at index 0.  The number of vertices in each polyline is
//  determined by successive entries in the numVertices field.
//
//////////////////////////////////////////////////////////////////////////////


#ifndef IV_STRICT
// Deprecated feature; specifying USE_REST_OF_VERTICES as the last
// value in the numVertices field will use all the points in the
// coordinate array.
#define SO_LINE_SET_USE_REST_OF_VERTICES	(-1)
#endif


class SoLineSet : public SoNonIndexedShape {

    SO_NODE_HEADER(SoLineSet);

  public:
    // Fields
    SoMFInt32		numVertices;	// Number of vertices per line

    // Constructor
    SoLineSet();

  SoEXTENDER public:
    // Implements actions
    virtual void	GLRender(SoGLRenderAction *action);

    // Redefine this to tell open caches that they contain lines
    virtual void	getBoundingBox(SoGetBoundingBoxAction *action);

  SoINTERNAL public:
    static void		initClass();

    // This enum is used to indicate the current material or normal binding
    enum Binding {
	OVERALL, PER_LINE, PER_SEGMENT, PER_VERTEX
    };
    
    //Typedef of pointer to method on IndexedLineSet;
    //This will be used to simplify declaration and initialization.
    typedef void (SoLineSet::*PMLS)(SoGLRenderAction *);
    
  protected:
    // Generates line segments representing line set
    virtual void	generatePrimitives(SoAction *action);

    // Computes bounding box of line set
    virtual void	computeBBox(SoAction *action, SbBox3f &box,
				    SbVec3f &center);

    // Overrides standard method to create an SoLineDetail instance
    virtual SoDetail *	createLineSegmentDetail(SoRayPickAction *action,
						const SoPrimitiveVertex *v1,
						const SoPrimitiveVertex *v2,
						SoPickedPoint *pp);

    virtual ~SoLineSet();

  private:
    // Returns current material or normal binding from action's state
    static Binding	getMaterialBinding(SoAction *action);
    static Binding	getNormalBinding(SoAction *action);

    // Returns TRUE if normal binding is AUTO and there aren't enough
    // PER_VERTEX normals, in which case we turn off lighting and draw
    // BASE_COLOR.
    SbBool	wouldGenerateNormals(SoState *state);

    // Blow vpCache when vertexProperty field changes:
    virtual void	notify(SoNotList *list);

    // This stores the total number of vertices; we use this
    // information to influence Separator's auto-caching algorithm
    // (shapes with very few triangles should be cached because
    // traversing them can be expensive, shapes with lots of triangles
    // shouldn't be cached because they'll take up too much memory).
    int				totalNumVertices;

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
    static PMLS renderFunc[32];

};

#endif /* _SO_LINE_SET_ */
