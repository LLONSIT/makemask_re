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
 |	SoSFTrigger
 |
 |   Author(s)		: Ronen Barzel
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_SF_TRIGGER_
#define  _SO_SF_TRIGGER_

#include <Inventor/fields/SoSubField.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFTrigger subclass of SoSField.
//
//////////////////////////////////////////////////////////////////////////////

class SoSFTrigger : public SoSField {

    // Use standard field stuff
    SO_SFIELD_REQUIRED_HEADER(SoSFTrigger);
    SO_SFIELD_CONSTRUCTOR_HEADER(SoSFTrigger);

  public:
    // equivalent to SoField::touch().  Kept for consistency
    void                setValue()		{ touch(); }

    // getValue is a no-op:
    void                getValue() const	{ }

    // Start notification.
    virtual void	touch();

    // Equality/inequality tests. Since there are no values, trigger
    // fields are all the same
    int			operator ==(const SoSFTrigger &t) const;
    int			operator !=(const SoSFTrigger &t) const;

  SoINTERNAL public:
    static void		initClass();

    // Notification can flow through a trigger, but can't start at a
    // trigger.  The only way to start notification at a trigger is to
    // call touch().
    virtual void	startNotify();

    // Override notify to always evaluate (after passing on
    // notification) to clear upstream dirty bits
    virtual void	notify(SoNotList *list);

  private:
    // Reading and writing. These are no-ops.
    virtual SbBool	readValue(SoInput *in);
    virtual void	writeValue(SoOutput *out) const;
};

#endif /* _SO_SF_TRIGGER_ */
