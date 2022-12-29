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
 |   Classes:
 |	SoMFString
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_MF_STRING_
#define  _SO_MF_STRING_

#include <Inventor/fields/SoSubField.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoMFString subclass of SoMField.
//
//////////////////////////////////////////////////////////////////////////////

class SoMFString : public SoMField {
    // Use standard field stuff
    SO_MFIELD_HEADER(SoMFString, SbString, const SbString &);

  public:
    //
    // Some additional convenience functions:
    //

    // Set values from array of character strings
    void	setValues(int start, int num, const char *strings[]);

    // Set one value from character string
    void	setValue(const char *string);

    // Convenience function to delete text from consecutive strings.
    // All text from the given character of one line (fromChar in
    // fromLine) to the given character of another line (toChar in
    // toLine), inclusive, is deleted. Any leftover text on fromLine
    // and toLine is merged into one line.
    void	deleteText(int fromLine, int fromChar, int toLine, int toChar);


  SoINTERNAL public:
    static void		initClass();
};

#endif /* _SO_MF_STRING_ */
