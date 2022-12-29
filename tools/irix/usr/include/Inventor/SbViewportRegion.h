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
 |	This file contains the SbViewportRegion class definition.
 |
 |   Author(s)	: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SB_VIEWPORT_REGION_
#define  _SB_VIEWPORT_REGION_

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbViewportRegion
//
//  Class that represents the active viewport region in a display
//  window. It contains the screen-space size of the window as well as
//  the origin and size of the viewport within the window. By default,
//  the viewport is the same as the full window. Methods allow the
//  viewport to be set either in terms of screen space pixels or as
//  normalized coordinates, where (0,0) is the lower-left corner of
//  the window and (1,1) is the upper-right corner.
//
//////////////////////////////////////////////////////////////////////////////

#include <Inventor/SbLinear.h>

class SbViewportRegion {
  public:
    // Default constructor. Sets window size to default 100x100
    SbViewportRegion();

    // Constructor that takes window size as width and height in pixels
    SbViewportRegion(short width, short height);

    // Constructor that takes window size as width and height in
    // pixels as SbVec2s
    SbViewportRegion(SbVec2s winSize);

    // Constructor that takes an SbViewportRegion to copy from
    SbViewportRegion(const SbViewportRegion &vpReg);

    // Changes window size to given width and height in pixels
    void		setWindowSize(short width, short height)
	{ setWindowSize(SbVec2s(width, height)); }

    // Changes window size to given width and height in pixels, given
    // as SbVec2s
    void		setWindowSize(SbVec2s winSize);

    // Sets viewport to given region, specified as normalized window
    // coordinates: (0,0) is the lower-left corner, (1,1) is the upper-right.
    void		setViewport(float left, float bottom,
				    float width, float height)
	{ setViewport(SbVec2f(left, bottom), SbVec2f(width, height)); }

    // Sets viewport to region with given origin (lower-left corner)
    // and size, given as normalized coordinate vectors.
    void		setViewport(SbVec2f origin, SbVec2f size);

    // Sets viewport to given region, specified as pixel coordinates
    // in window: (0,0) is the lower-left corner
    void		setViewportPixels(short left, short bottom,
					  short width, short height)
	{ setViewportPixels(SbVec2s(left, bottom), SbVec2s(width, height)); }

    // Sets viewport to region with given origin (lower-left corner)
    // and size, given as pixel coordinates.
    void		setViewportPixels(SbVec2s origin, SbVec2s size);

    // Returns window size in pixels
    const SbVec2s &	getWindowSize() const		{ return windowSize; }

    // Returns viewport origin in normalized coordinates
    const SbVec2f &	getViewportOrigin() const	{ return vpOrigin; }

    // Returns viewport origin in pixels
    const SbVec2s &	getViewportOriginPixels() const	{ return vpOriginPix; }

    // Returns viewport size in normalized coordinates
    const SbVec2f &	getViewportSize() const		{ return vpSize; }

    // Returns viewport size in pixels
    const SbVec2s &	getViewportSizePixels() const	{ return vpSizePix;}

    // Returns aspect ratio (width/height) of viewport
    float		getViewportAspectRatio() const
	{ return (vpSizePix[1] == 0 ? 1.0 :
		  (float) vpSizePix[0] / (float) vpSizePix[1]); }

    // Scales viewport within window to be the given ratio of its
    // current width or height, leaving the resulting viewport
    // centered about the same point as the current one.
    void		scaleWidth(float ratio);
    void		scaleHeight(float ratio);

    // Sets/returns the pixel-per-inch ratio for the display device
    // the viewport is part of. The default value is 72 (1 pixel per
    // printer's point).
    void		setPixelsPerInch(float ppi)   { pixelsPerInch = ppi;  }
    float		getPixelsPerInch() const      { return pixelsPerInch; }

    // Convenience function that returns number of pixels per printer's point
    float		getPixelsPerPoint() const
	{ return pixelsPerInch / 72.0; }

    // Equality comparison operator
    friend int		operator ==(const SbViewportRegion &reg1,
				    const SbViewportRegion &reg2);

  private:
    SbVec2s		windowSize;	// Window size in pixels
    SbVec2f		vpOrigin;	// Viewport origin, normalized
    SbVec2s		vpOriginPix;	// Viewport origin in pixels
    SbVec2f		vpSize;		// Viewport size, normalized
    SbVec2s		vpSizePix;	// Viewport size in pixels
    SbBool		vpSet;		// TRUE if viewport was set explicitly
    float		pixelsPerInch;	// Number of pixels per inch

    // Sets viewport to be full window
    void		setFullViewport();

    // Adjusts viewport pixel size based on new window size or new viewport
    void		adjustViewport();
};

#endif /* _SB_VIEWPORT_REGION_ */
