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
 |	SoSFImage
 |
 |   Author(s)		: Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_SF_IMAGE_
#define  _SO_SF_IMAGE_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbLinear.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFImage subclass of SoSField.
//
//////////////////////////////////////////////////////////////////////////////

class SoSFImage : public SoSField {
    // Uses only some of the standard field stuff (because there is no
    // SbImage type):
    SO_SFIELD_REQUIRED_HEADER(SoSFImage);
    SO_SFIELD_CONSTRUCTOR_HEADER(SoSFImage);

  public:
    // getValue returns the size, number of components and a constant
    // pointer to the image.
    const unsigned char *	getValue(SbVec2s &size, int &nc) const;

    // setValue copies the image given to it into internal storage.
    // See startEditing() for a way of avoiding the copy if you are
    // doing a getValue() followed immediately by a setValue().
    void			setValue(const SbVec2s &size, int nc,
					 const unsigned char *bytes);
    
    // Equality/inequality tests
    int				operator ==(const SoSFImage &f) const;
    int				operator !=(const SoSFImage &f) const
	{ return ! ((*this) == f); }

    // Avoid copying the values in/out, if you are just changing the
    // bytes and not changing the dimensions of the image.  This is
    // equivalent to getValue, but returns a pointer you can change.
    unsigned char *		startEditing(SbVec2s &size, int &nc);
    void			finishEditing();

  SoINTERNAL public:
    static void		initClass();

  private:
    SbVec2s		size;		// Width and height of image
    int			numComponents;	// Number of components per pixel
    unsigned char *	bytes;		// Array of pixels

    // Reading and writing
    virtual SbBool	readValue(SoInput *in);
    virtual void	writeValue(SoOutput *out) const;
};

#endif /* _SO_SF_IMAGE_ */
