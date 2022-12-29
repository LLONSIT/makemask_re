#ifndef __LOCALE_CORE_H__
#define __LOCALE_CORE_H__
#ident "$Revision: 1.2 $"
/*
*
* Copyright 1992, Silicon Graphics, Inc.
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
/*	Copyright (c) 1988 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <internal/sgimacros.h>

/* It is deliberate that we are defining struct lconv in the global
   namespace rather than in namespace std.  That's because of binary
   compatibility.  We want to make sure that the mangling of functions
   like f(struct lconv*) doesn't change.
*/

struct 	lconv 	{
	char *decimal_point;
	char *thousands_sep;
	char *grouping;
	char *int_curr_symbol;
	char *currency_symbol;
	char *mon_decimal_point;
	char *mon_thousands_sep;
	char *mon_grouping;
	char *positive_sign;
	char *negative_sign;
	char int_frac_digits;
	char frac_digits;
	char p_cs_precedes;
	char p_sep_by_space;
	char n_cs_precedes;
	char n_sep_by_space;
	char p_sign_posn;
	char n_sign_posn;
#if 0
	char int_p_cs_precedes;
	char int_n_cs_precedes;
	char int_p_sep_by_space;
	char int_n_sep_by_space;
	char int_p_sign_posn;
	char int_n_sign_posn;
#endif
};

#define LC_CTYPE	0
#define LC_NUMERIC	1
#define LC_TIME		2
#define LC_COLLATE	3
#define LC_MONETARY	4
#define LC_MESSAGES	5
#define LC_ALL		6

#ifndef NULL
#define NULL	0L
#endif

__SGI_LIBC_BEGIN_EXTERN_C
__SGI_LIBC_BEGIN_NAMESPACE_STD

extern char *setlocale(int, const char *);
extern struct lconv *localeconv(void);

__SGI_LIBC_END_NAMESPACE_STD
__SGI_LIBC_END_EXTERN_C

#endif /* !__LOCALE_CORE_H__ */
