/* USMID @(#) clibinc/clibdefs.h	92.2	07/26/99 12:57:02 */
 
/*
*
* Copyright 1997, Silicon Graphics, Inc.
* All Rights Reserved.
*
* This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics, Inc.;
* the contents of this file may not be disclosed to third parties, copied or
* duplicated in any form, in whole or in part, without the prior written
* permission of Silicon Graphics, Inc.
*
* RESTRICTED RIGHTS LEGEND:
* Use, duplication or disclosure by the Government is subject to restrictions
* as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data
* and Computer Software clause at DFARS 252.227-7013, and/or in similar or
* successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -
* rights reserved under the Copyright Laws of the United States.
*/

/*      (C) COPYRIGHT CRAY RESEARCH, INC.
 *      UNPUBLISHED PROPRIETARY INFORMATION.
 *      ALL RIGHTS RESERVED.
 */
 
#ifndef _CLIBDEFS_H
#define _CLIBDEFS_H

/*
 * Note SV2 is part of _CRAY.
 */
#if	defined(__ia64)		/* Little Endian IEEE */
#include <sys/cdefs.h>

#ifndef _WORD32
#define	_WORD32		1		/* sizeof(int) is 4 bytes/32 bits */
#endif

#elif	_CRAY

#include <sys/cdefs.h>

#elif defined(_ABSOFT)

#ifndef _WORD32
#define _WORD32		1		/* sizeof(int) is 4 bytes/32 bits */
#endif
#ifndef _ADDR32
#define _ADDR32		1		/* sizeof(int*) is 4 bytes/32 bits */
#endif
#ifndef _CRAYIEEE
#define _CRAYIEEE	1		/* IEEE arithmetic */
#endif

#include <sys/cdefs.h>

#elif	(defined(__mips) || (defined(__linux__) && defined(__ia64__)))

#include <sys/cdefs.h>

#if 	_MIPS_SZLONG == 32
#define	_WORD32		1		/* sizeof(long) is 4 bytes/32 bits */
#endif

#else	/* Solaris assumed */

#define	_SOLARIS	1
#define	_WORD32		1		/* sizeof(int) is 4 bytes/32 bits */
#define	_ADDR32		1		/* sizeof(int*) is 4 bytes/32 bits */
#define	_CRAYIEEE	1		/* IEEE arithmetic */

#if defined(__cplusplus)
#define __BEGIN_DECLS   extern "C" {
#define __END_DECLS     };
#define _DOTDOTDOT ...
#else
#define __BEGIN_DECLS
#define __END_DECLS
#define _DOTDOTDOT
#endif

#if defined(__STDC__) || defined(__cplusplus)
#define __(_A)  _A
#else
#define __(_A)  ()
#endif

#endif	/* Solaris */

#endif	/* ! _CLIBDEFS_H */
