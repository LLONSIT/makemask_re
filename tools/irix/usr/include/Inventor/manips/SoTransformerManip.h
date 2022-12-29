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
 |   Description:
 |	This file defines the SoTransformerManip class.
 |      It uses a SoTransformerDragger to edit the fields of a hideableTransformManip
 |
 |   Author(s): Paul Isaacs
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_TRANSFORMER_MANIP_
#define  _SO_TRANSFORMER_MANIP_

#include <Inventor/manips/SoTransformManip.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTransformerManip
//
//  - allows user to transform objects.
//
//////////////////////////////////////////////////////////////////////////////

class SoTransformerManip : public SoTransformManip {

    SO_NODE_HEADER(SoTransformerManip);

  public:
    // Constructor
    SoTransformerManip();

    // Tells the dragger to unsquish its rotation and scale knobs during 
    // the next traversal.
    void unsquishKnobs();

    // Controls whether or not locate highlighting is used.
    SbBool isLocateHighlighting();
    void setLocateHighlighting( SbBool onOff );

  SoINTERNAL public:
    static void		initClass();	// initialize the class

  protected:
    virtual ~SoTransformerManip();
};

#endif /* _SO_TRANSFORMER_MANIP_ */
