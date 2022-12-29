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
 |   $Revision: 2.0 $
 |
 |   Description:
 |	This file contains the definition of SbProjector. These take
 |	a point in two dimensions and project it to a point in three
 |	dimensions. Typically, the point is the mouse position.
 |
 |	SbProjectors are typically used by manipulators to turn the
 |	mouse position into a rotation or translation.
 |
 |   Author(s)		: Howard Look, Paul Isaacs
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef _SB_PROJECTOR_
#define _SB_PROJECTOR_

#include <Inventor/SbLinear.h>

class SbProjector
{
  public:
    // Apply the projector using the given point, returning the
    // point in three dimensions that it projects to.
    // The point should be normalized from 0-1, with (0,0) at
    // the lower-left.
    virtual SbVec3f	    project(const SbVec2f &point) = 0;

    // Set/get the view volume to use for the projection.
    // This is typically gotten from SbCamera::getViewVolume.
    virtual void	    setViewVolume(const SbViewVolume &vol);

    const SbViewVolume &    getViewVolume() const	    { return viewVol; }
    
    // Set/get the transform space to work in. This matrix should transform
    // working space coords into world space.
    // The default matrix is identity, meaning that the default working
    // space is world space.
    virtual void	    setWorkingSpace(const SbMatrix &space);

    const SbMatrix &	    getWorkingSpace() const
						{ return workingToWorld ; }

    // Returns an instance that is a copy of this instance. The caller
    // is responsible for deleting the copy when done.
    virtual SbProjector *    copy() const = 0;

  protected:
    // Default constructor.
    // The default view volume is undefined.
    // The default working space is identity (world space).
    SbProjector();
    ~SbProjector(){};

    // Given this mouse point, return the line it projects to
    // in working space.
    SbLine	getWorkingLine(const SbVec2f &point) const;
  
    SbViewVolume	    viewVol;
    SbMatrix		    worldToWorking;
    SbMatrix		    workingToWorld;
};

#endif /* _SB_PROJECTOR_ */
