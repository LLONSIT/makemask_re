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
/**************************************************************************
 * 		 Copyright (C) 1991-94, Silicon Graphics, Inc.		  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 **************************************************************************/

//  -*- C++ -*-

/*
 *
 _______________________________________________________________________
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 |
 |   $Revision: 1.7 $
 |
 |   Description:
 |	This file defines the SoAsciiText node class.
 |
 |   Author(s)		: Chris Marrin,  Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_ASCIITEXT_
#define  _SO_ASCIITEXT_

#include <Inventor/SbBox.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFBitMask.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/nodes/SoShape.h>

#include <GL/gl.h>   // For GLenum declaration

//  GLU Library version dependency.   Introduced with Iris 6.2.
#ifndef gluTESSELATOR
#if defined(__glu_h__) && (GLU_VERSION_1_2)
#define gluTESSELATOR  GLUtesselator
#else
#define gluTESSELATOR  GLUtriangulatorObj
extern "C" struct GLUtriangulatorObj;
#endif
#endif


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoAsciiText
//
//  Specify 3D text for Vrml.
//
//////////////////////////////////////////////////////////////////////////////

class MyOutlineFontCache;
class SoPrimitiveVertex;
class SoTextureCoordinateElement;

class SoAsciiText : public SoShape {

    SO_NODE_HEADER(SoAsciiText);

  public:
    enum Justification {		// Justification types
	LEFT	= 0x01,
	RIGHT	= 0x02,
	CENTER	= 0x03
    };

    // Fields
    SoMFString		string;		// the strings to display
    SoSFFloat		spacing;	// interval between strings
    SoSFEnum		justification;
    SoMFFloat		width;		// width of each string

    // Constructor
    SoAsciiText();

  SoEXTENDER public:

    virtual void	GLRender(SoGLRenderAction *action);
    virtual void	rayPick(SoRayPickAction *action);

  SoINTERNAL public:
    static void		initClass();

  protected:
    // Computes bounding box of text
    virtual void	computeBBox(SoAction *action, SbBox3f &box,
				    SbVec3f &center);

    // Generates primitives
    virtual void	generatePrimitives(SoAction *);
    
    virtual ~SoAsciiText();

  private:
    // Setup the internal font cache
    SbBool setupFontCache(SoState *state, SbBool forRender = FALSE);

    // Return bounding box of the fronts of all characters.
    void getFrontBBox(SbBox2f &result);

    // Extend a 

    // Figure out how much each line of text is offset (based on width
    // of characters and justification)
    SbVec2f getStringOffset(int line, float width);
    
    // Render the fronts of the characters
    void renderFront(SoGLRenderAction *action, const SbString &string,
		     float width, GLUtriangulatorObj *tobj);
    
    // Creates a text detail when picking:
    SoDetail * createTriangleDetail(SoRayPickAction *,
				    const SoPrimitiveVertex *,
				    const SoPrimitiveVertex *,
				    const SoPrimitiveVertex *,
				    SoPickedPoint *);

    // Generates the fronts of the characters, by getting the outlines
    // and calling the glu tesselation code:
    void generateFront(const SbString &string, float width);
    
    // Static callbacks invoked by the glu tesselation code:
    static void beginCB(GLenum primType);
    static void endCB();
    static void vtxCB(void *vertex);
    
    // Private data:
    // MyOutlineFontCache is an internal, opaque class used to
    // maintain gl display lists and other information for each
    // character in a font.
    MyOutlineFontCache *myFont;

    // All this stuff is used while generating primitives:
    static SoAsciiText *currentGeneratingNode;
    static SoPrimitiveVertex *genPrimVerts[3];
    static SbVec3f genTranslate;
    static int genWhichVertex;
    static uint32_t genPrimType;
    static SoAction *genAction;
    static SbBool genBack;
    static SbBool genTexCoord;
    static const SoTextureCoordinateElement *tce;
};

#endif /* _SO_ASCIITEXT_ */
