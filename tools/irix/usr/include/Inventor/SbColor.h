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
 |   Description:
 |	This file contains the SbColor class definition.
 |
 |   Author(s)	: Alain Dumesny
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SB_COLOR_H_
#define  _SB_COLOR_H_

#include <Inventor/SbLinear.h>


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbColor
//
//  3D vector used to represent an RGB color. Each component of the vector is 
// a floating-point number between 0.0 and 1.0 .
//
//////////////////////////////////////////////////////////////////////////////

class SbColor;


// C-api.h: struct SbColor {
// C-api.h: 	float rgb[3];
// C-api.h: };


class SbColor : public SbVec3f {
  public:
    // Default constructor
    SbColor();

    // Constructor given an SbVec3f
    SbColor(const SbVec3f vec3f) { setValue(vec3f.getValue()); }

    // Constructor given an array of 3 components
    SbColor(const float rgb[3])				{ setValue(rgb); }

    // Constructor given 3 individual components
    SbColor(float r, float g, float b)			{ setValue(r, g, b); }

    //
    // HSV routines. Those are 3 floats containing the Hue, Saturation and
    // Value (same as brightness) of the color.
    //

    // Sets value of color vector from 3 hsv components
    SbColor &	setHSVValue(float h, float s, float v);

    // Sets value of color vector from array of 3 hsv components
    SbColor &	setHSVValue(const float hsv[3])
			{ return setHSVValue(hsv[0], hsv[1], hsv[2]); }

    // Returns 3 individual hsv components
    void	getHSVValue(float &h, float &s, float &v) const;

    // Returns an array of 3 hsv components
    void	getHSVValue(float hsv[3]) const
 			{ getHSVValue(hsv[0], hsv[1], hsv[2]); }
    
    //
    // RGBA Packed integer color routines. The color format expressed in 
    // hexadecimal is 0xrrggbbaa, where
    //	    aa 	is the alpha value
    //	    bb 	is the blue value
    //	    gg 	is the green value
    //	    rr 	is the red value
    // RGBA component values range from 0 to 0xFF (255).
    //
    
    // Sets value from ordered RGBA packed color. Alpha value is used for
    // transparency.
    SbColor &	setPackedValue(uint32_t orderedRGBA, float& transparency);

    // Returns ordered RGBA packed color. Alpha is 1 - transparency, scaled
    // between 0 and 255 = 0xFF.
    uint32_t   getPackedValue(float transparency = 0.0) const;

// NOTE: These Macros are stolen from SbVec3f because the C-api
// generator does NOT generate macros for macros defined by a parent
// class. Thus they must be done `by hand'.  Yes, this does suck.

// C-api.h: #define SbColGetRGB(_dest, _src)				      \
// C-api.h:     (((_dest)[0] = (_src).rgb[0]), ((_dest)[1] = (_src).rgb[1]),  \
// C-api.h:      ((_dest)[2] = (_src).rgb[2]))

// C-api.h: #define SbColGetR_G_B(_r, _g, _b, _src)			      \
// C-api.h:     (((_r) = (_src).rgb[0]), ((_g) = (_src).rgb[1]),	      \
// C-api.h:	 ((_b) = (_src).rgb[2]))

// C-api.h: #define SbColSetRGB(_dest, _src)				      \
// C-api.h:     (((_dest).rgb[0] = (_src)[0]), ((_dest).rgb[1] = (_src)[1]),  \
// C-api.h:      ((_dest).rgb[2] = (_src)[2]))

// C-api.h: #define SbColSetR_G_B(_dest, _r, _g, _b)			      \
// C-api.h:     (((_dest).rgb[0] = (_r)), ((_dest).rgb[1] = (_g)),	      \
// C-api.h:      ((_dest).rgb[2] = (_b)))

// C-api.h: #define SbColMult(_v, _s)					      \
// C-api.h:     (((_v).rgb[0] *= (_s)), ((_v).rgb[1] *= (_s)), ((_v).rgb[2] *= (_s)))

// C-api.h: #define SbColDiv(_v, _s)					      \
// C-api.h:     (((_v).rgb[0] /= (_s)), ((_v).rgb[1] /= (_s)), ((_v).rgb[2] /= (_s)))

// C-api.h: #define SbColAdd(_dest, _src1, _src2)			      \
// C-api.h:     (((_dest).rgb[0] = (_src1).rgb[0] + (_src2).rgb[0]),	      \
// C-api.h:      ((_dest).rgb[1] = (_src1).rgb[1] + (_src2).rgb[1]),	      \
// C-api.h:      ((_dest).rgb[2] = (_src1).rgb[2] + (_src2).rgb[2]))

// C-api.h: #define SbColSub(_dest, _src1, _src2)			      \
// C-api.h:     (((_dest).rgb[0] = (_src1).rgb[0] - (_src2).rgb[0]),	      \
// C-api.h:      ((_dest).rgb[1] = (_src1).rgb[1] - (_src2).rgb[1]),	      \
// C-api.h:      ((_dest).rgb[2] = (_src1).rgb[2] - (_src2).rgb[2]))

};

#endif /* _SB_COLOR_H_ */

