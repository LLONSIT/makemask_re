#if 0 

    Copyright (c) 1991 SGI   All Rights Reserved
    THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF SGI
    The copyright notice above does not evidence any
    actual or intended publication of such source code,
    and is an unpublished work by Silicon Graphics, Inc.
    This material contains CONFIDENTIAL INFORMATION that
    is the property of Silicon Graphics, Inc. Any use,
    duplication or disclosure not specifically authorized
    by Silicon Graphics is strictly prohibited.
    
    RESTRICTED RIGHTS LEGEND:
    
    Use, duplication or disclosure by the Government is
    subject to restrictions as set forth in subdivision
    (c)(1)(ii) of the Rights in Technical Data and Computer
    Software clause at DFARS 52.227-7013, and/or in similar
    or successor clauses in the FAR, DOD or NASA FAR
    Supplement.  Unpublished- rights reserved under the
    Copyright Laws of the United States.  Contractor is
    SILICON GRAPHICS, INC., 2011 N. Shoreline Blvd.,
    Mountain View, CA 94039-7311

#endif
#ifndef _iflOrientation_h_
#define _iflOrientation_h_

#include <ifl/iflTypes.h>
#include <ifl/iflTile.h>
#include <ifl/iflSize.h>


extern char iflOrientationIsLow[];
extern char iflOrientationIsLeft[];
extern char iflOrientationIsTrans[];

iflOrientation
iflMapOrientation(iflOrientation orientation, 
		  int flipX, int flipY, int transXY);

void
iflMapFlipTrans(iflOrientation fromOrientation, iflFlip& flip, int& transXY, 
		iflOrientation toOrientation);

void
iflMapTile(iflOrientation fromOrientation, iflTile2D<float>& tile, 
	   iflOrientation toOrientation, const iflSize& size);
void
iflMapTile(iflOrientation fromOrientation, iflTile2D<int>& tile,
    	   iflFlip& flip, int& transXY, iflOrientation toOrientation, 
	   const iflSize& size);
void
iflMapTile(iflOrientation fromOrientation, iflTile2D<int>& tile, 
	   iflOrientation toOrientation, const iflSize& size);

void
iflMapXY(iflOrientation fromOrientation, int& x, int& y, 
	 iflOrientation toOrientation, const iflSize& size);
void
iflMapXY(iflOrientation fromOrientation, float& x, float& y, 
	 iflOrientation toOrientation, const iflSize& size);
void
iflMapXYSign(iflOrientation fromOrientation, float& x, float& y,
	     iflOrientation toOrientation);

int
iflOrientationIsMirror(iflOrientation fromOrientation,
		       iflOrientation toOrientation);

void
iflMapSize(iflOrientation fromOrientation, iflSize &size, 
	   iflOrientation toOrientation);
void
iflMapSize(iflOrientation fromOrientation, int& sx, int& sy, 
	   iflOrientation toOrientation);
#endif
