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
 |	SoMFColor
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_MF_COLOR_
#define  _SO_MF_COLOR_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbColor.h>
#include <Inventor/fields/SoMFVec3f.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoMFColor subclass of SoMField.
//
//////////////////////////////////////////////////////////////////////////////

class SoMFColor : public SoMField {
    // Use standard field stuff
    SO_MFIELD_HEADER(SoMFColor, SbColor, const SbColor &);

  public:
    //
    // Additional convenience functions
    //

    // Set RGB/HSV values from array of arrays of 3 floats
    void		setValues(int start, int num, const float rgb[][3]);
    void		setHSVValues(int start, int num, const float hsv[][3]);

    // Set to one RGB color from SbVec3f, 3 floats, or array of 3 floats
    void		setValue(const SbVec3f &vec);
    void		setValue(float r, float g, float b);
    void		setValue(const float rgb[3]);

    // Set to one HSV color from 3 floats or array of 3 floats
    void		setHSVValue(float h, float s, float v);
    void		setHSVValue(const float hsv[3]);

    // Set one of N RGB colors from SbVec3f, 3 floats, or array of 3 floats
    void		set1Value(int index, const SbVec3f &vec);
    void		set1Value(int index, float r, float g, float b);
    void		set1Value(int index, const float rgb[3]);

    // Set1 one of N HSV colors from 3 floats or array of 3 floats
    void		set1HSVValue(int index, float h, float s, float v);
    void		set1HSVValue(int index, const float hsv[3]);

  SoINTERNAL public:
    static void		initClass();

  private:
    virtual void	writeBinaryValues(SoOutput *out) const;
    virtual SbBool	readBinaryValues(SoInput *in, int numToRead);
};

#endif /* _SO_MF_COLOR_ */
