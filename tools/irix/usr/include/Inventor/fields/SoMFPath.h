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
 |   $Revision: 2.2 $
 |
 |   Classes:
 |	SoMFPath
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_MF_PATH_
#define  _SO_MF_PATH_

#include <Inventor/fields/SoSubField.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoMFPath subclass of SoMField. Each field value is a pointer to an
//  SoPath. The field automatically maintains references to the paths
//  it points to and propagates notification from the paths.
//
//////////////////////////////////////////////////////////////////////////////

class SoMFPath : public SoMField {

    // Use standard field stuff
    SO_MFIELD_HEADER(SoMFPath, SoPath *, SoPath *);

  SoINTERNAL public:
    static void		initClass();

    // Propagates notification through field
    virtual void	notify(SoNotList *list);

    // Update a copied field to use node copies if the head nodes have
    // been copied
    virtual void	fixCopy(SbBool copyConnections);

    // Override this to also check the heads of the stored paths
    virtual SbBool	referencesCopy() const;

  private:
    SoNode		**heads;	// Head nodes of paths (needed
					// to track notification)

    // Override this to maintain write-references in paths
    virtual void	countWriteRefs(SoOutput *out) const;

    // Changes value in field without doing other notification stuff.
    // Keeps track of references and auditors.
    void		setVal(int index, SoPath *newValue);
};

#endif /* _SO_MF_PATH_ */
