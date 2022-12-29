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
 |   $Revision: 2.3 $
 |
 |   Classes:
 |	SoMFLong
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_MF_LONG_
#define  _SO_MF_LONG_

#ifndef IV_STRICT
#include <Inventor/fields/SoMFInt32.h>
typedef SoMFInt32  SoMFLong;

#else

Error.  SoMFLong invalid with -DIV_STRICT.   See <Inventor/fields/SoMFLong.h>
------
Inventor now provides So*Int32 types in place of So*Long types to simplify
porting to other architectures and operating systems.  

You should use SoMFInt32 in place of SoMFLong and also change longs in your
code to the appropriate sized typedef from <inttypes.h>.   The perl script  
/usr/sbin/longToInt32  can assist you making this transition.  Note that not 
all longs should be changed as some are determined by other system include 
files.
_____________________________________________________________________________
#endif /* IV_STRICT */

#endif /* _SO_MF_LONG_ */
