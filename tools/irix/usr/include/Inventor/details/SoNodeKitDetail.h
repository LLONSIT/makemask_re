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
 |	This file defines classes for describing or extracting
 |	detail information about a node kit.
 | 
 |
 |   The details contains a pointer to the node, a pointer to the 
 |   child part within the node, and the name of the child part.
 |   
 |   Classes:
 |	SoNodeKitDetail
 |
 |   Author(s)		: Paul Isaacs
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef _SO_NODE_KIT_DETAIL_
#define _SO_NODE_KIT_DETAIL_

#include <Inventor/details/SoSubDetail.h>

class SoNode;
class SoBaseKit;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoNodeKitDetail
//
//  Base class for all detail classes.
//
//////////////////////////////////////////////////////////////////////////////

class SoNodeKitDetail : public SoDetail {
    
    SO_DETAIL_HEADER(SoNodeKitDetail);

  public:
    // Default constructor and destructor.
    SoNodeKitDetail();
    virtual ~SoNodeKitDetail();

    // Returns a pointer to the nodekit that created this detail
    SoBaseKit *getNodeKit() const { return myNodeKit; }

    // Returns a pointer to the part selected within the nodekit that 
    // created this detail.
    SoNode *getPart() const { return myPart; }

    // Returns the name of the part selected within the nodekit that
    // created this detail
    const SbName &getPartName() const { return myPartName; }

    // Returns an instance that is a copy of this instance. The caller
    // is responsible for deleting the copy when done.
    virtual SoDetail *	copy() const;

  SoEXTENDER public:

    void setNodeKit( SoBaseKit *theNodeKit );
    void setPart( SoNode *thePart );
    void setPartName( const SbName &theName )      { myPartName = theName; }

  SoINTERNAL public:
    static void		initClass();

  protected:
    SoBaseKit       *myNodeKit;
    SoNode          *myPart;
    SbName          myPartName;
};

#endif /* _SO_NODE_KIT_DETAIL_ */

