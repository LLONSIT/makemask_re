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
 |	This file defines the SoCoordinateElement class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_COORDINATE_ELEMENT
#define  _SO_COORDINATE_ELEMENT

#include <Inventor/SbLinear.h>
#include <Inventor/elements/SoReplacedElement.h>


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoCoordinateElement
//
//  Element that stores the current coordinates. Coordinates may be
//  specified as 3-D or 4-D vectors. This element remembers the last
//  type of value stored.
//
//  This class allows read-only access to the top element in the state
//  to make accessing several values in it more efficient. Individual
//  values must be accessed through this instance.
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoCoordinateElement : public SoReplacedElement {

    SO_ELEMENT_HEADER(SoCoordinateElement);

  public:
    // Initializes element
    virtual void	init(SoState *state);

    // Sets the current coordinates in the state as 3-vectors or 4-vectors
    static void		set3(SoState *state, SoNode *node,
			     int32_t numCoords, const SbVec3f *coords);
    static void		set4(SoState *state, SoNode *node,
			     int32_t numCoords, const SbVec4f *coords);

    // Returns the top (current) instance of the element in the state
    static const SoCoordinateElement * getInstance(SoState *state)
        {return (const SoCoordinateElement *)
	    getConstElement(state, classStackIndex);}

    // Returns the number of coordinate points in an instance
    int32_t		getNum() const		{ return numCoords; }

    // Returns TRUE if the coordinates were specified as 3-vectors,
    // FALSE if 4-vectors
    SbBool		is3D() const		{ return coordsAre3D; }

    // Returns the indexed coordinate from an element as a 3- or
    // 4-vector, converting if necessary. A returned reference may be
    // invalid after the next call to either of these methods.
    const SbVec3f &	get3(int index) const;
    const SbVec4f &	get4(int index) const;

    // Returns the default 3-D or 4-D coordinate
    static SbVec3f getDefault3()		{ return SbVec3f(0, 0, 0); }
    static SbVec4f getDefault4()		{ return SbVec4f(0, 0, 0, 1); }

    // Prints element (for debugging)
    virtual void	print(FILE *fp) const;

  SoINTERNAL public:
    // Initializes the SoCoordinateElement class
    static void		initClass();

  protected:
    int32_t		numCoords;
    const SbVec3f	*coords3;
    const SbVec4f	*coords4;
    SbBool		coordsAre3D;

    virtual ~SoCoordinateElement();

  private:
    // This stores a pointer to the default coordinates so that we can
    // set "coords3" to point to them if no other values have been set.
    static SbVec3f	*defaultCoord3;

    SbVec3f		convert3;	// To convert from 4-D to 3-D
    SbVec4f		convert4;	// To convert from 3-D to 4-D
};

#endif /* _SO_COORDINATE_ELEMENT */
