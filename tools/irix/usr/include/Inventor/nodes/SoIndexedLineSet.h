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
 |	This file defines the SoIndexedLineSet node class.
 |
 |   Author(s)		: Paul S. Strauss, Nick Thompson
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_INDEXED_LINE_SET_
#define  _SO_INDEXED_LINE_SET_

#include <Inventor/nodes/SoIndexedShape.h>

class SoState;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoIndexedLineSet
//
//  Indexed set of (poly)lines. Each line consists of 2 or more
//  vertices, each of which is denoted by an integer index (from the
//  coordIndex field) into the current coordinates. Depending on the
//  current material and normal binding values, the materials and
//  normals for the lines or vertices may be accessed in order or
//  indexed. If they are indexed, the materialIndex and normalIndex
//  fields are used. Texture coordinates may also be indexed, using
//  the textureCoordIndex field.
//
//////////////////////////////////////////////////////////////////////////////

// This coordinate index indicates that the current line ends and the
// next line begins
#define SO_END_LINE_INDEX	(-1)

class SoIndexedLineSet : public SoIndexedShape {

    SO_NODE_HEADER(SoIndexedLineSet);

  public:
    // Inherits all fields

    // Constructor
    SoIndexedLineSet();

  SoEXTENDER public:
    // Implements actions
    virtual void	GLRender(SoGLRenderAction *action);

    // Redefine this to tell open caches that they contain lines
    virtual void	getBoundingBox(SoGetBoundingBoxAction *action);
					       
    //Typedef of pointer to method on IndexedLineSet;
    //This will be used to simplify declaration and initialization.
    typedef void (SoIndexedLineSet::*PMILS)(SoGLRenderAction *);
					          
  SoINTERNAL public:
    static void		initClass();

    // This enum is used to indicate the current material or normal binding
    enum Binding {
	OVERALL,
	PER_SEGMENT,	PER_SEGMENT_INDEXED,
	PER_LINE,	PER_LINE_INDEXED,
	PER_VERTEX,	PER_VERTEX_INDEXED
    };

  protected:
    // Generates line segments representing line set
    virtual void	generatePrimitives(SoAction *action);

    // Overrides standard method to create an SoLineDetail instance
    virtual SoDetail *	createLineSegmentDetail(SoRayPickAction *action,
						const SoPrimitiveVertex *v1,
						const SoPrimitiveVertex *v2,
						SoPickedPoint *pp);
    virtual ~SoIndexedLineSet();

  private:
    // Returns current material or normal binding from action's state
    static Binding	getMaterialBinding(SoAction *action);
    static Binding	getNormalBinding(SoAction *action);

    // Reset numVertices/numSegments/numPolylines when notified
    virtual void	notify(SoNotList *list);
    
    // Fill in numPolylines, numSegments 
    void countPolylinesAndSegments();
    
    // Number of polylines, number of line segments, and vertices per polyline

    int		numSegments;
    int		numPolylines;
    int *	numVertices;
        
    // Returns TRUE if normal binding is AUTO and there aren't enough
    // PER_VERTEX normals, in which case we turn off lighting and draw
    // BASE_COLOR.
    SbBool	wouldGenerateNormals(SoState *state);

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
    static PMILS renderFunc[32];
    
};

#endif /* _SO_INDEXED_LINE_SET_ */
    
