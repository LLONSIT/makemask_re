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
 |	This file defines the abstract SoEXTENDER SoAccumulatedElement
 |	class.
 |
 |   Classes:
 |	SoAccumulatedElement
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_ACCUMULATED_ELEMENT
#define  _SO_ACCUMULATED_ELEMENT

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoAccumulatedElement
//
//  This is the abstract base class for each state element whose value
//  may be accumulated when it is set. (This is rare.) Examples are
//  transformations and profiles.
//
//  Subclasses may need to override the push() method to copy values
//  from the next instance in the stack (using getNextInStack() ),
//  if the new one has to accumulate values on top of the old ones.
//
//  This class defines the matches() method to compare lists of
//  node-id's. The node-id's represent the states of all nodes that
//  changed the value of the element. SoAccumulatedElement provides
//  methods that maintain lists of node-id's of all nodes that affect
//  an instance. Subclasses must call these methods to make sure the
//  id's are up to date, if they plan to use the standard matches()
//  method. Otherwise, they can define matches() differently, if they
//  wish.
//
//////////////////////////////////////////////////////////////////////////////

#include <Inventor/elements/SoSubElement.h>

SoEXTENDER class SoAccumulatedElement : public SoElement {

    SO_ELEMENT_ABSTRACT_HEADER(SoAccumulatedElement);

  public:
    // Returns TRUE if the element matches another element, based on node-id's
    virtual SbBool	matches(const SoElement *elt) const;

    // Prints element (for debugging)
    virtual void	print(FILE *fp) const;

  SoINTERNAL public:
    // Initializes the SoAccumulatedElement class
    static void		initClass();

  protected:
    // Clears out the list of node id's
    void		clearNodeIds();

    // Adds the id of the given node to the current list
    void		addNodeId(const SoNode *node);

    // Sets the node id list to JUST the id of the given node
    void		setNodeId(const SoNode *node);

    // Create and return a copy of this element; this will copy the
    // nodeId list properly.
    virtual SoElement	*copyMatchInfo() const;

    // Override normal capture method to capture elements at other
    // depths that we are accumulating with.
    virtual void	captureThis(SoState *state) const;

    // Destructor
    virtual ~SoAccumulatedElement();

    // This stores the list of node id's as pointers, since they
    // should be the same length as int32_ts. The id's are sorted by
    // increasing value, to make comparisons easier.
    SbPList		nodeIds;
  private:

    SbBool		accumulatesWithParentFlag;
};

#endif /* _SO_ACCUMULATED_ELEMENT */
