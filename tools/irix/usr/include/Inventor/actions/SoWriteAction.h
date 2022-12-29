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
 |	Defines the SoWriteAction class
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_WRITE_ACTION_
#define  _SO_WRITE_ACTION_

#include <Inventor/actions/SoAction.h>
#include <Inventor/actions/SoSubAction.h>
#include <Inventor/SoOutput.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoWriteAction
//
//  For writing scene graphs to files. There are two stages in this
//  action. First it has to count references to nodes and paths, since
//  multiply-referenced nodes and paths need to have temporary names
//  defined for them. The second stage is writing the stuff out.
//
//////////////////////////////////////////////////////////////////////////////

class SoWriteAction : public SoAction {

    SO_ACTION_HEADER(SoWriteAction);

  public:
    // Constructor (default action writes to stdout)
    SoWriteAction();

    // Constructor that takes SoOutput to write to
    SoWriteAction(SoOutput *out);

    // Destructor
    virtual ~SoWriteAction();

    // Returns SoOutput
    SoOutput *		getOutput() const		{ return output; }

  SoINTERNAL public:
    static void		initClass();

    // Continues write action on a graph or path
    void		continueToApply(SoNode *node);
    void		continueToApply(SoPath *path);

  protected:
    // Initiates action on graph
    virtual void	beginTraversal(SoNode *node);

    // Override method to return FALSE, since this action applies
    // itself to each path separately, so it doesn't need the extra
    // overhead of compacting the list.
    virtual SbBool	shouldCompactPathLists() const;

  private:
    SoOutput		*output;	// Output info
    SbBool		createdOutput;	// TRUE if output created by action
    SbBool		continuing;	// TRUE only if continueToApply()
					// was used to apply action
    SbBool		doOneStage;	// TRUE if only supposed to do 1 stage
    SbPList		savedLists;	// Path lists saved for later apply

    // Performs traversal on a path list, which is a little tricker
    void		traversePathList(SoNode *node);
};

#endif /* _SO_WRITE_ACTION_ */
