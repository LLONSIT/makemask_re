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
 |	This file defines the SoNormalBundle class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_NORMAL_BUNDLE
#define  _SO_NORMAL_BUNDLE

#include <Inventor/bundles/SoBundle.h>
#include <Inventor/elements/SoGLNormalElement.h>
#include <Inventor/misc/SoNormalGenerator.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoNormalBundle
//
//  Bundle that allows shapes to deal with normals and normal bindings
//  more easily. This class provides a fairly simple interface to
//  normal handling, including normal generation.
//
//  This class can be used during either rendering or primitive
//  generation. For primitive generation, the get() method can be used
//  to access normals. For GL rendering, the send() method can be used
//  to send normals to GL.
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoNormalBundle : public SoBundle {

  public:
    // Constructor - takes the action the bundle is used for and a
    // flag to indicate whether the bundle is being used for
    // rendering. If this is TRUE, the bundle can be used to send
    // normals to GL. 
    SoNormalBundle(SoAction *action, SbBool forRendering);

    // Destructor
    ~SoNormalBundle();

    // Returns TRUE if normals need to be generated.
    SbBool		shouldGenerate(int numNeeded);

    // Initializes generation in the case where shouldGenerate() is
    // not called. (shouldGenerate() does this automatically).
    void		initGenerator(int initialNum = 100);

    //////////////////////
    //
    // If shouldGenerate() returns TRUE, these methods can be used by
    // shapes to specify the geometry to generate normals for. They
    // are front-ends to methods on the SoNormalGenerator class:
    //

    // Send a polygon's worth of vertices. Begin a polygon, send as
    // many vertices as you want, and then end the polygon.
    void		beginPolygon()
	{ generator->beginPolygon(); }
    void		polygonVertex(const SbVec3f &point)
	{ generator->polygonVertex(point); }
    void		endPolygon()
	{ generator->endPolygon(); }

    // Send a triangle
    void		triangle(const SbVec3f &p1,
				 const SbVec3f &p2,
				 const SbVec3f &p3)
	{ generator->triangle(p1, p2, p3); }

    // Calculates the normals once all vertices have been sent. The
    // normals are stored by the bundle so the caller does not have to
    // deal with them directly.  The startIndex argument specifies the
    // index at which the generated normals will begin-- it can be
    // used by shapes that allow the coordinates and normals to be
    // offset (non-indexed shapes).  If addToState is TRUE, the
    // state will be pushed, the normals will be added to the
    // state; otherwise, you can just use
    // getGeneratedNormals/getNumGeneratedNormals to get the generated
    // normals.
    //
    // The normal bundle DOES NOT FREE the generated normals!  It is
    // expected that normals will be added to a normal cache, and the
    // normal cache will free the normals.
    //
    void		generate(int startIndex = 0,
				 SbBool addToState=TRUE);

    // Returns the generated normals.
    const SbVec3f *	getGeneratedNormals() const
	{ return generator->getNormals(); }
    int			getNumGeneratedNormals() const
	{ return generator->getNumNormals(); }


    // This allows shapes that generate their own normals (for
    // efficiency) to store the resulting normals in the state. The
    // bundle takes care of pushing/popping the state.
    // Note:  This method only adds the normals to the state, it does
    // NOT store a pointer to them (so you cannot call the
    // getGenerated() routines)
    void		set(int32_t numNormals, const SbVec3f *normals);

    // Returns indexed normal. This can be used for primitive
    // generation or during rendering
    const SbVec3f &	get(int index) const	{ return normElt->get(index); }

    // Sends indexed normal to the GL, for use only during GL rendering
    void		send(int index) const	{ GLNormElt->send(index); }

  SoINTERNAL public:
    SoNormalGenerator	*generator;	// Normal generator

  private:
    // Normal elements:
    const SoNormalElement	*normElt;
    const SoGLNormalElement	*GLNormElt;

    SbBool		isRendering;	// Bundle being used for rendering
    SbBool		pushedState;	// We pushed state to set normals
    SoNode		*currentNode;	// Node that created the bundle
};

#endif /* _SO_NORMAL_BUNDLE */

