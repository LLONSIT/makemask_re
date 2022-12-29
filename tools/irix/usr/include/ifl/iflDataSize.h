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
    ilDataSize returns the size of ilType in sizeof units. An
    optional argument int count can be specified and will be
    computed into the overall size. This is essential for ilBit
    type to be useful.
*/
#ifndef _iflDataSize_h_
#define _iflDataSize_h_

#include <ifl/iflTypes.h>
#include <ifl/iflSize.h>

/* flag values used with iflDataClosestType */

enum { iflDataWantSigned=0x1, iflDataAnySign=0x2, iflDataDemote=0x4 };

#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
size_t iflDataSize(iflDataType type, int count = 1);

iflDataType iflDataTypeFromRange(double minVal, double maxVal, int typeMask=-1);

iflDataType iflDataClosestType(iflDataType desired, int allowed, int flags=0);

#else
size_t iflDataSize(iflDataType type, int count);
iflDataType iflDataTypeFromRange(double minVal, double maxVal, int typeMask);
iflDataType iflDataClosestType(iflDataType desired, int allowed, int flags);
#endif
double iflDataMin(iflDataType type);

double iflDataMax(iflDataType type);

#if !defined(__cplusplus) || defined(IFL_NOINLINE_DATAFUNCS)
int iflDataIsSigned(iflDataType);
int iflDataIsIntegral(iflDataType);
#else
inline int iflDataIsSigned(iflDataType type)
    { return type & (iflChar|iflShort|iflInt|iflFloat|iflDouble); }

inline int iflDataIsIntegral(iflDataType type)
    { return type & ~(iflFloat|iflDouble); }

#endif

#ifdef __cplusplus
}
inline size_t iflDataSize(iflDataType type, const iflSize& size)
    { return iflDataSize(type, size.x*size.y*size.z*size.c); }
#endif

#endif
