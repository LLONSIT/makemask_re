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
 |	This file defines the SoTextDetail class.
 |
 |   Author(s)		: Thaddeus Beier, Dave Immel, Howard Look
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef _SO_TEXT_DETAIL_
#define _SO_TEXT_DETAIL_

#include <Inventor/SbBox.h>
#include <Inventor/details/SoSubDetail.h>
#include <Inventor/nodes/SoText3.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTextDetail
//
//  Detail about a shape representing text.
//
//////////////////////////////////////////////////////////////////////////////

class SoTextDetail : public SoDetail {

    SO_DETAIL_HEADER(SoTextDetail);

  public:
    // Constructor and destructor
    SoTextDetail();
    virtual ~SoTextDetail();

    // Returns the index of the string within a multiple-value string
    // fields of a text node
    int32_t		getStringIndex() const		{ return stringIndex; }

    // Returns the index of the character within the string. For
    // example, if the character of detail was the "u" within
    // "Splurmph", the character index would be 3. 
    int32_t		getCharacterIndex() const	{ return charIndex; }

    // For Text3, this returns which part was picked:
    SoText3::Part	getPart() const		{ return part; }

    // Returns an instance that is a copy of this instance. The caller
    // is responsible for deleting the copy when done.
    virtual SoDetail *	copy() const;

  SoEXTENDER public:
    // For Text3, this sets which part is picked:
    void		setPart(SoText3::Part p)	{ part = p; }

    // These set the string and character indices:
    void		setStringIndex(int32_t i)		{ stringIndex = i; }
    void		setCharacterIndex(int32_t i)	{ charIndex = i; }

#ifndef IV_STRICT
    void    setStringIndex(long i)				// System long
		{ setStringIndex((int32_t) i); }
    void    setCharacterIndex(long i)				// System long
		{ setCharacterIndex((int32_t) i); }
#endif

  SoINTERNAL public:
    static void		initClass();

  private:
    int32_t		stringIndex, charIndex;
    SoText3::Part	part;
};

#endif /* _SO_TEXT_DETAIL_ */
