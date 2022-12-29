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
 |	This file contains the definition of the internal
 |	SoAuditorList class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef _SO_AUDITOR_LIST_
#define _SO_AUDITOR_LIST_

#include <Inventor/SbPList.h>
#include <Inventor/misc/SoNotification.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoAuditorList
//
//  SoAuditorList class. This class maintains a list of instances that
//  audit (receive notification from) an SoBase or SoField. Each entry
//  in the list consists of a pointer to the auditor (base or field)
//  instance and a type code of type SoNotRec::Type.
//
//  The type of the auditor object pointer depends on the type code,
//  as follows:
//
//	Type code:	Auditor object pointer:
//
//	CONTAINER	The SoFieldContainer containing the field
//	PARENT		The parent node
//	SENSOR		The SoDataSensor instance
//	FIELD		The destination field instance
//	ENGINE		The destination field instance
//
//  Since there are two entries in the underlying SbPList for each
//  auditor, some of these methods have to do some fancy footwork.
//
//////////////////////////////////////////////////////////////////////////////

#if _COMPILER_VERSION>=710
#  pragma set woff 1375
#endif

SoINTERNAL class SoAuditorList : private SbPList {
  public:

    // Constructor and destructor.
    SoAuditorList();
    ~SoAuditorList();

    // Adds an auditor of the given type to the list
    void		append(void *auditor, SoNotRec::Type type);

    // Sets auditor and type for given index
    void		set(int index, void *auditor, SoNotRec::Type type);

    // Finds an auditor in the list, returning the index or -1 if not found
    int			find(void *auditor, SoNotRec::Type type) const;

    // Returns object or type for given index
    void *		getObject(int index) const;
    SoNotRec::Type	getType(int index) const;

    // Removes an auditor from the list
    void		remove(int index);
    void		remove(void *auditor, SoNotRec::Type type)
	{ remove(find(auditor, type)); }

    // Returns number of auditors in list
    int			getLength() const;

    // Propagates notification to all auditors in list
    void		notify(SoNotList *list);

  private:
    // Propagates notification to indexed auditor
    void		notify1(SoNotList *list, int index);
};

#if _COMPILER_VERSION>=710
#  pragma reset woff 1375
#endif

#endif /* _SO_AUDITOR_LIST_ */
