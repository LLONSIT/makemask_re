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
 |   $Revision: 2.1 $
 |
 |   Description:
 |	This file defines the SoAnnotation node class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_ANNOTATION_
#define  _SO_ANNOTATION_

#include <Inventor/nodes/SoSeparator.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoAnnotation
//
//  Annotation group node: delays rendering its children until all
//  other nodes have been traversed, turning off depth buffer
//  comparisons first. The result is that the shapes under the
//  annotation node are rendered on top of the rest of the scene.
//
//  Note that if more than one annotation node is present in a graph,
//  the order in which they are traversed determines the stacking
//  order - later nodes are rendered on top of earlier ones. Also note
//  that since depth buffer comparisons are disabled, complex 3D
//  objects may not be rendered correctly when used under annotation
//  nodes.
//
//  All non-rendering actions are inherited as is from SoSeparator.
//
//////////////////////////////////////////////////////////////////////////////
class SoAnnotation : public SoSeparator {

    SO_NODE_HEADER(SoAnnotation);

  public:

    // No fields

    // Constructor
    SoAnnotation();

  SoEXTENDER public:
    // Implement actions
    virtual void	GLRender(SoGLRenderAction *action);

  SoINTERNAL public:
    static void		initClass();

  protected:
    // Destructor
    virtual ~SoAnnotation();
};

#endif /* _SO_ANNOTATION_ */
