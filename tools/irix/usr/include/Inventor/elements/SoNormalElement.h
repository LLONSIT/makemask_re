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
 |   $Revision: 2.5 $
 |
 |   Description:
 |	This file defines the SoNormalElement class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_NORMAL_ELEMENT
#define  _SO_NORMAL_ELEMENT



#include <Inventor/SbLinear.h>
#include <Inventor/elements/SoReplacedElement.h>
#include <Inventor/errors/SoDebugError.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoNormalElement
//
//  Element that stores the current surface normals.
//
//  This class allows read-only access to the top element in the state
//  to make accessing several values in it more efficient. Individual
//  values must be accessed through this instance.
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoNormalElement : public SoReplacedElement {

    SO_ELEMENT_HEADER(SoNormalElement);

  public:
    // Initializes element
    virtual void	init(SoState *state);

    // Sets the current normals
    static void		set(SoState *state, SoNode *node,
			    int32_t numNormals, const SbVec3f *normals);

    // Returns the top (current) instance of the element in the state
    static const SoNormalElement * getInstance(SoState *state)
    	{return (const SoNormalElement *) 
	    getConstElement(state, classStackIndex);}

    // Returns the number of normal vectors in an instance
    int32_t		getNum() const		{ return numNormals; }

    // Returns the indexed normal from an element
    const SbVec3f &	get(int index) const
    	{
#ifdef DEBUG
    if (index < 0 || index >= numNormals)
	SoDebugError::post("SoNormalElement::get",
			   "Index (%d) is out of range 0 - %d",
			   index, numNormals - 1);
#endif /* DEBUG */ 
	    return normals[index];
	}

    // Prints element (for debugging)
    virtual void	print(FILE *fp) const;

  SoINTERNAL public:
    // Initializes the SoNormalElement class
    static void		initClass();

  protected:
    int32_t		numNormals;
    const SbVec3f	*normals;

    virtual ~SoNormalElement();

  private:
    // This stores a pointer to the default normal so that we can set
    // "normals" to point to it if no other normal has been set.
    static SbVec3f	*defaultNormal;
};

#endif /* _SO_NORMAL_ELEMENT */
