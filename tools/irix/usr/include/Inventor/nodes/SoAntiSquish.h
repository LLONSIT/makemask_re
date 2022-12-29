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
 |	This file defines the SoAntiSquish node class.
 |
 |   Author(s)		: Paul Isaacs
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_ANTI_SQUISH_
#define  _SO_ANTI_SQUISH_

#include <Inventor/fields/SoFieldData.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/nodes/SoTransformation.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFEnum.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoAntiSquish
//
//  undoes any uneven scales in the current transformation matrix.
//  during traversal
//
//////////////////////////////////////////////////////////////////////////////

class SoAntiSquish : public SoTransformation {

    SO_NODE_HEADER(SoAntiSquish);

  public:

    // Constructor
    SoAntiSquish();

    enum Sizing {
	X,
	Y,
	Z,
	AVERAGE_DIMENSION,
	BIGGEST_DIMENSION,
	SMALLEST_DIMENSION,
	LONGEST_DIAGONAL
    };

    // Fields
        SoSFEnum		sizing;
	// If TRUE, recalculates every time the ctm changes.
	// If FALSE, recalculates only after the recalc() method is called.
	// Default is TRUE
        SoSFBool		recalcAlways;

    // If recalcAlways field is FALSE, call this method to force a new matrix
    // to be calculated.
    void recalc();

  SoEXTENDER public:
    // Called by actions that need to change the state with a new matrix.
    void		doAction(SoAction *action);

  SoINTERNAL public:
    static void		initClass();

  protected:
    virtual void	callback(SoCallbackAction *action);
    virtual void	GLRender(SoGLRenderAction *action);
    virtual void	getBoundingBox(SoGetBoundingBoxAction *action);
    virtual void	getMatrix(SoGetMatrixAction *action);
    virtual void	pick(SoPickAction *action);

    virtual ~SoAntiSquish();

    SbMatrix getUnsquishingMatrix( SbMatrix squishedMatrix, SbBool doInverse,
				   SbMatrix &inverseAnswer );

  private:
    SbMatrix savedAnswer, savedInverseAnswer;

    SbBool recalcNextTime;
};

#endif /* _SO_ANTI_SQUISH_ */
