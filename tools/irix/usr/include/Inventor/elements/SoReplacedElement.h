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
 |	This file defines the abstract SoEXTENDER SoReplacedElement class.
 |
 |   Classes:
 |	SoReplacedElement
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_REPLACED_ELEMENT
#define  _SO_REPLACED_ELEMENT

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoReplacedElement
//
//  This is the abstract base class for each state element whose value
//  is replaced whenever it is set. (Most state elements fall into
//  this category, so most are derived from this class.)
//
//  This class overrides the SoElement::getElement() method to store
//  the node-id of the node that is about to set the value in the
//  element (i.e., the node that is passed to getElement()). This
//  class also defines the SoElement::matches() method to return TRUE
//  if the node-id's of the two elements match. Subclasses can change
//  this behavior by defining matches() differently, if they wish. For
//  example, they can compare the elements' values, instead.
//
//////////////////////////////////////////////////////////////////////////////

#include <Inventor/elements/SoSubElement.h>

SoEXTENDER class SoReplacedElement : public SoElement {

    SO_ELEMENT_ABSTRACT_HEADER(SoReplacedElement);

  public:
    // Initializes node id in element
    virtual void	init(SoState *state);

    // Returns TRUE if the element matches another element, based on node-id
    virtual SbBool	matches(const SoElement *elt) const;

    // Prints element (for debugging)
    virtual void	print(FILE *fp) const;

  SoINTERNAL public:
    // Initializes the SoReplacedElement class
    static void		initClass();

    // Create and return a copy of this element.  The only operation
    // supported by the copy is matches() (the copy will be
    // unitialized except for the nodeId).
    virtual SoElement	*copyMatchInfo() const;

    // Return nodeId.  This was added so the SoTransformSeparator
    // class can figure out whether or not it contains a camera:
    uint32_t		getNodeId() const { return nodeId; }

  protected:
    uint32_t		nodeId;

    // Overrides SoElement::getElement() to set the nodeId in the
    // element instance before returning it.
    static SoElement *	getElement(SoState *state, int stackIndex,
				   SoNode *node);

    // Destructor
    virtual ~SoReplacedElement();
};

#endif /* _SO_REPLACED_ELEMENT */
