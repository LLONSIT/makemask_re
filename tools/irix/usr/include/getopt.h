#ifndef __GETOPT_H__
#define __GETOPT_H__
#ident "$Revision: 1.13 $"

/*
 * Declarations for getopt(3C).
 *
 * Copyright 1990, Silicon Graphics, Inc. 
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

#include <standards.h>
#include <internal/sgimacros.h>

__SGI_LIBC_BEGIN_EXTERN_C

extern int	getopt(int, char *const *, const char *);

extern char	*optarg;
extern int	opterr;
extern int	optind;
extern int	optopt;

/*
 * workaround for weak symbols in non-shared code
 * _PIC is not defined for non-shared code.
 * Check for optarg being #defined to  _optarg for libc builds
 */
#ifndef _PIC 
#if _MIPS_SIM !=_ABIO32
#if !defined optarg
#pragma section_non_gp (optarg)
#pragma section_non_gp (opterr)
#pragma section_non_gp (optind)
#pragma section_non_gp (optopt)
#else /* optarg */
#pragma section_non_gp (_optarg)
#pragma section_non_gp (_opterr)
#pragma section_non_gp (_optind)
#pragma section_non_gp (_optopt)
#endif /* optarg */
#endif /* _MIPS_SIM != ABIO32 */
#endif /* _PIC */


#if _SGIAPI
#define	GETOPTDONE	(-1)

/*
 * This value is returned when an option argument is found that is not
 * in the option list
 */
#define	GETOPTHUH	'?'

extern int	getsubopt(char **, char *const *, char **);
extern void	getoptreset(void);
#endif

__SGI_LIBC_END_EXTERN_C

#endif /* !__GETOPT_H__ */
