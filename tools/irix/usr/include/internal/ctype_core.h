#ifndef __CTYPE_CORE_H__
#define __CTYPE_CORE_H__
#ident "$Revision: 1.4 $"
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

/*
 * Note - this is an ANSI and XPG4 header file - In ANSI mode only
 * ANSI symbols are permitted!
 */

#include <internal/sgimacros.h>
#include <standards.h>

#define	_U	0x00000001	/* Upper case */
#define	_L	0x00000002	/* Lower case */
#define	_N	0x00000004	/* Numeral (digit) */
#define	_S	0x00000008	/* Spacing character */
#define	_P	0x00000010	/* Punctuation */
#define	_C	0x00000020	/* Control character */
#define	_B	0x00000040	/* Obsolete: was to designate the space character only */
#define	_X	0x00000080	/* heXadecimal digit */

#define _A	0x00004000	/* Alphabetical characters only */
#define _PR	0x00008000	/* Printable characters only */
#define _G	0x40000000	/* Graphic characters only */
#define _BL	0x80000000	/* The blank character class */

#define _ISalpha	(_U | _L | _A)
#define	_ISupper	(_U)
#define	_ISlower	(_L)
#define	_ISdigit	(_N)
#define	_ISxdigit	(_X)
#define	_ISalnum	(_U | _L | _A | _N)
#define	_ISspace	(_S | _BL)
#define _ISblank	(_BL)
#define	_ISpunct	(_P)
#define	_ISprint	(_P | _U | _L | _N | _A | _X | _PR)
#define	_ISgraph	(_P | _U | _L | _N | _A | _X | _G)
#define	_IScntrl	(_C)

__SGI_LIBC_BEGIN_EXTERN_C

__SGI_LIBC_BEGIN_NAMESPACE_STD
extern int isalnum(int);
extern int isalpha(int);
__SGI_LIBC_END_NAMESPACE_STD
#if defined(__c99) || defined(_SGI_COMPILING_LIBC)
extern int isblank(int);
#if !defined(_SGI_COMPILING_LIBC)
#pragma optional isblank
#endif
#endif /* __c99 */
extern int __isblank(int);
__SGI_LIBC_BEGIN_NAMESPACE_STD
extern int iscntrl(int);
extern int isdigit(int);
extern int isgraph(int);
extern int islower(int);
extern int isprint(int);
extern int ispunct(int);
extern int isspace(int);
extern int isupper(int);
extern int isxdigit(int);
extern int tolower(int);
extern int toupper(int);
__SGI_LIBC_END_NAMESPACE_STD

/* ANSI permits anything that starts with a 'is' or 'to' */
extern int isascii(int);        
extern int toascii(int);        
#if (_XOPEN4 || _XOPEN5) && _NO_ANSIMODE
extern int _tolower(int);
extern int _toupper(int);
#endif

__SGI_LIBC_END_EXTERN_C

#ifndef _KERNEL

#include <internal/locale_attr_core.h>

#ifndef _LINT

#define	isalnum(c)	((__libc_attr._ctype_tbl->_class+1)[c] & _ISalnum)
#define	isalpha(c)	((__libc_attr._ctype_tbl->_class+1)[c] & _ISalpha)
#if defined(__c99) || defined(_SGI_COMPILING_LIBC)
#define isblank(c)	((__libc_attr._ctype_tbl->_class+1)[c] & _ISblank)
#endif /* __c99 */
#define __isblank(c)	((__libc_attr._ctype_tbl->_class+1)[c] & _ISblank)
#define	iscntrl(c)	((__libc_attr._ctype_tbl->_class+1)[c] & _IScntrl)
#define	isdigit(c)	((__libc_attr._ctype_tbl->_class+1)[c] & _ISdigit)
#define	isgraph(c)	((__libc_attr._ctype_tbl->_class+1)[c] & _ISgraph)
#define	islower(c)	((__libc_attr._ctype_tbl->_class+1)[c] & _ISlower)
#define	isprint(c)	((__libc_attr._ctype_tbl->_class+1)[c] & _ISprint)
#define	ispunct(c)	((__libc_attr._ctype_tbl->_class+1)[c] & _ISpunct)
#define	isspace(c)	((__libc_attr._ctype_tbl->_class+1)[c] & _ISspace)
#define	isupper(c)	((__libc_attr._ctype_tbl->_class+1)[c] & _ISupper)
#define	isxdigit(c)	((__libc_attr._ctype_tbl->_class+1)[c] & _ISxdigit)

#define	isascii(c)	(!((c) & ~0177))
#define	toascii(c)	((c) & 0177)
#if (_XOPEN4 || _XOPEN5) && _NO_ANSIMODE
#define	_toupper(c)     ((__libc_attr._ctype_tbl->_upper+1)[c])
#define	_tolower(c)	((__libc_attr._ctype_tbl->_lower+1)[c])
#endif

#endif	/* lint */

#else	/* _KERNEL */

extern unsigned char __ctype[];

#ifndef _LINT

#define	isalnum(c)	((__ctype +1)[c] & _ISalnum)
#define	isalpha(c)	((__ctype +1)[c] & _ISalpha)
#if defined(__c99) || defined(_SGI_COMPILING_LIBC)
#define isblank(c)	((__ctype +1)[c] & _ISblank)
#endif /* __c99 */
#define __isblank(c)	((__ctype +1)[c] & _ISblank)
#define	iscntrl(c)	((__ctype +1)[c] & _IScntrl)
#define	isdigit(c)	((__ctype +1)[c] & _ISdigit)
#define	isgraph(c)	((__ctype +1)[c] & _ISgraph)
#define	islower(c)	((__ctype +1)[c] & _ISlower)
#define	isprint(c)	((__ctype +1)[c] & (_ISprint | _B))
#define	ispunct(c)	((__ctype +1)[c] & _ISpunct)
#define	isspace(c)	((__ctype +1)[c] & _ISspace)
#define	isupper(c)	((__ctype +1)[c] & _ISupper)
#define	isxdigit(c)	((__ctype +1)[c] & _ISxdigit)

#define	isascii(c)	(!((c) & ~0177))
#define	toascii(c)	((c) & 0177)
#if (_XOPEN4 || _XOPEN5) && _NO_ANSIMODE
#define	_toupper(c)     ((__ctype + 258)[c])
#define	_tolower(c)	((__ctype + 258)[c])
#endif

#endif	/* lint */

#endif  /* _KERNEL */

#ifdef __cplusplus
/* Masking macros are forbidden by the C++ standard.  See section
   17.4.2.1, paragraph 6, of the standard, especially footnote 159. */

#undef isalnum
#undef isalpha
#if defined(__c99) || defined(_SGI_COMPILING_LIBC)
#undef isblank
#endif /* __c99 */
#undef __isblank
#undef iscntrl
#undef isdigit
#undef isgraph
#undef islower
#undef isprint
#undef ispunct
#undef isspace
#undef isupper
#undef isxdigit
#undef _toupper
#undef _tolower
#undef tolower
#undef toupper

#endif /* __cplusplus */

#endif /* !__CTYPE_CORE_H__ */
