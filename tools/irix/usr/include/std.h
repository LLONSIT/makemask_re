#ifndef __STD_H__
#define __STD_H__
/*
 * std.h
 *
 *
 * Copyright 1991, Silicon Graphics, Inc.
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

#ident "$Revision: 1.4 $"

/*
 *	@(#) std.h 1.1 88/03/30 inccmd:std.h
 */
#define	SYSBSIZE	BSIZE		/* system block size */
#define	SYSBSHIFT	BSHIFT

#define	EFFBSIZE	SYSBSIZE	/* efficient block size */
#define	EFFBSHIFT	SYSBSHIFT

#define	MULWSIZE	2		/* multiplier 'word' */
#define	MULWSHIFT	1
#define	MULLSIZE	4		/* multiplier 'long' */
#define	MULLSHIFT	2
#define	MULBSIZE	512		/* multiplier 'block' */
#define	MULBSHIFT	9
#define	MULKSIZE	1024		/* multiplier 'k' */
#define	MULKSHIFT	10

#define	SYSTOMUL(sysblk)	((sysblk) * (SYSBSIZE / MULBSIZE))
#endif /* !__STD_H__ */
