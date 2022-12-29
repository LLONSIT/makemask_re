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
 |	This file contains the definition of the SbLineProjector
 |	class. This projects the mouse onto a line. 
 |	  
 |   Author(s)		: Howard Look, Paul Isaacs
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef _SB_LINE_PROJECTOR_
#define _SB_LINE_PROJECTOR_

#include <Inventor/projectors/SbProjector.h>

class SbLineProjector : public SbProjector
{
  public:
    // Constructor
    // The default line passes through the origin and is
    // oriented toward the Y axis.
    SbLineProjector();

    // Destructor
    ~SbLineProjector(){};
    
    // Returns an instance that is a copy of this instance. The caller
    // is responsible for deleting the copy when done.
    virtual SbProjector *    copy() const;

    // Apply the projector using the given point, returning the
    // point in three dimensions that it projects to.
    // The point should be normalized from 0-1, with (0,0) at the lower-left.
    virtual SbVec3f	project(const SbVec2f &point);

    // Set/get the line to use.
    void		setLine(const SbLine &line);
    const SbLine &	getLine() const		  { return line; }

    // Get a vector on this line given two normalized mouse points.
    virtual SbVec3f	getVector(const SbVec2f &mousePosition1,
				  const SbVec2f &mousePosition2);
					    
    // Get a vector given the current mouse point.
    // Uses the last point on this projector from the previous
    // call to getVector or setStartPostion. Do not use this
    // if the working space transform is changing since
    // the new point will be in a different space than
    // the old one.
    virtual SbVec3f	getVector(const SbVec2f &mousePosition);
					    
    // Set the initialial from a mouse position.
    void		setStartPosition(const SbVec2f &mousePosition)
				{ lastPoint = project(mousePosition); }

    // Set the initialial position from a point on the projector.
    void		setStartPosition(const SbVec3f &point)
						{ lastPoint = point; }
  protected:

    SbLine	line;
    SbVec3f	lastPoint;
};

#endif /* _SB_LINE_PROJECTOR_ */
