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
 |   Description:
 |	This file contains basic SB library definitions.
 |
 |   Author(s)		: Paul S. Strauss, Nick Thompson
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SB_BASIC_
#define  _SB_BASIC_

//
// These symbols can be used to determine what version of Inventor
// your application is compiling against.  These symbols were first
// added with Inventor 2.1 (SO_VERSION==2, SO_VERSION_REVISION==1);
// they were undefined in previous revisions of Inventor.
//
#define SO_VERSION 		2
#define SO_VERSION_REVISION	1

#include <inttypes.h>
#include <sys/types.h>
#include <libc.h>
#include <sgidefs.h>
#include <stdio.h>

#ifndef FALSE
#   define FALSE	0
#   define TRUE		1
#endif

typedef int	SbBool;

/////////////////////////////////////////////////////////////////////////////
//
// These symbols are used in Inventor header files to distinguish
// between varying levels of use of classes and members.
//
// Types of classes are:
//
//	"class" means a public class intended for use by all users.
//	"SoEXTENDER class" indicates a class that is used only by
//		people extending the set of Inventor classes.
//	"SoINTERNAL class" means that the class is used only by
//		Inventor developers at Silicon Graphics.
//
// Types of member variables and methods are:
//
//	"public:" members are used by everybody.
//	"SoEXTENDER public:" members are used when extending Inventor.
//	"SoINTERNAL public:" members are for SGI Inventor developers only.
//
//	"protected:" members are for people extending Inventor
//		classes. (The "SoEXTENDER" is implied.)
//	"SoINTERNAL protected:" members are for SGI use only.
//
//	"private:" members are private, dammit.
//
/////////////////////////////////////////////////////////////////////////////

#define SoEXTENDER
#define SoINTERNAL

/////////////////////////////////////////////////////////////////////////////
//
// Map the single-precision math functions to the regular ones on
// machines that don't support them.
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(__sgi)

#define acosf acos
#define asinf asin
#define atanf atan
#define atan2f atan2
#define cosf cos
#define sinf sin
#define tanf tan
#define powf pow
#define sqrtf sqrt

#endif /* !defined(__sgi) */

#endif /* _SB_BASIC_ */
