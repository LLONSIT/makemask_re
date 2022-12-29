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
/*
    This class binds image size attributes into one abstract.
*/
#ifndef _iflSize_h_
#define _iflSize_h_

#include <ifl/iflCoord.h>

#ifndef __cplusplus

typedef struct iflSize iflSize;
struct iflSize { int x, y, z, c; };

#else

class iflSize : public iflXYZC<int> {

public:
    /* Constructors */

    iflSize() {}
    iflSize(int X, int Y, int C=1) 
	{ x = X; y = Y; z = 1; c = C; }
    iflSize(int X, int Y, int Z, int C) 
	{ x = X; y = Y; z = Z; c = C; }
    iflSize(const iflSize& size) 
	{ x = size.x; y = size.y; z = size.z; c = size.c; }

    /* Operators */

    operator int() const { return x*y*z*c; }
};

#endif
#endif
