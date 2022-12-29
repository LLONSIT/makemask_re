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
#ifndef _iflMinMax_h_
#define _iflMinMax_h_



    // Getting the minimum value

template<class T> inline T iflMin(T a, T b) { return a < b ? a : b; }
template<class T> inline T iflMin(T a, T b, T c)
    { return iflMin(iflMin(a,b),c); }
template<class T> inline T iflMin(T a, T b, T c, T d)
    { return iflMin(iflMin(a,b,c),d); }

    // Getting the maximum value

template<class T> inline T iflMax(T a, T b) { return a > b ? a : b; }
template<class T> inline T iflMax(T a, T b, T c)
    { return iflMax(iflMax(a,b),c); }
template<class T> inline T iflMax(T a, T b, T c, T d)
    { return iflMax(iflMax(a,b,c),d); }

#endif
