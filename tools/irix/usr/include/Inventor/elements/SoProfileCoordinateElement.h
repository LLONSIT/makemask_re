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
 |   $Revision $
 |
 |   Description:
 |	This file defines the SoProfileCoordinateElement class.
 |
 |   Author(s)		: Paul S. Strauss, Nick Thompson, Thad Beier
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_PROFILE_COORDINATE_ELEMENT
#define  _SO_PROFILE_COORDINATE_ELEMENT

#include <Inventor/SbLinear.h>
#include <Inventor/elements/SoReplacedElement.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoProfileCoordinateElement
//
//  Element storing the current profile coordinates, as either 2-D or
//  3-D points.
//
//  This class allows read-only access to the top element in the state
//  to make accessing several values in it more efficient. Individual
//  values must be accessed through this instance.
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoProfileCoordinateElement : public SoReplacedElement {

    SO_ELEMENT_HEADER(SoProfileCoordinateElement);

  public:
    // Initializes element.
    virtual void	init(SoState *state);

    // Sets the current profile coordinates
    static void		set2(SoState *state, SoNode *node,
			     int32_t numCoords, const SbVec2f *coords);
    static void		set3(SoState *state, SoNode *node,
			     int32_t numCoords, const SbVec3f *coords);

    // Returns the top (current) instance of the element in the state
    static const SoProfileCoordinateElement * getInstance(SoState *state);

    // Returns the number of coordinate points in an instance
    int32_t		getNum() const		{ return numCoords; }

    // Returns the indexed coordinate from an element as a 2- or
    // 3-vector, converting if necessary.
    const SbVec2f &	get2(int index) const;
    const SbVec3f &	get3(int index) const;

    // TRUE if set2() was called.
    SbBool		is2D() const  {	return coordsAre2D; }

    // Returns the default profile coordinate
    static SbVec2f	getDefault2() { return SbVec2f(0.0, 0.0); }
    static SbVec3f	getDefault3() { return SbVec3f(0.0, 0.0, 1.0); }

    virtual void	print(FILE *fp) const;

  SoINTERNAL public:
    // Initializes the SoCoordinateElement class
    static void		initClass();

  protected:
    int32_t 		numCoords;
    const SbVec2f	*coords2;
    const SbVec3f	*coords3;
    SbBool		coordsAre2D;

    virtual ~SoProfileCoordinateElement();

  private:
    static SbVec2f	*defaultCoord2;

    SbVec2f		convert2;	// To convert from 3-D to 2-D
    SbVec3f		convert3;	// To convert from 2-D to 3-D
};

#endif /* _SO_PROFILE_COORDINATE_ELEMENT */
