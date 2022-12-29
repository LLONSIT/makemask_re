#ifndef __WCTYPE_CORE_H
#define __WCTYPE_CORE_H
#ident "$Revision: 1.7 $"
/*	Copyright (c) 1990, 1991 UNIX System Laboratories, Inc. 	*/
/*	Copyright (c) 1984, 1986, 1987, 1988, 1989, 1990 AT&T   	*/
/*	  All Rights Reserved                                   	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF     	*/
/*	UNIX System Laboratories, Inc.   	            	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*	Copyright (c) 1990, 1991, 1992 UNIX System Laboratories, Inc.	*/
/*	Copyright (c) 1984, 1985, 1986, 1987, 1988, 1989, 1990 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF     	*/
/*	UNIX System Laboratories, Inc.                     	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/
/*	"@(#)libw:inc/wctype.h	1.1.2.4"			*/

#include <internal/sgimacros.h>
#include <sgidefs.h>
#include <standards.h>

/* 
 * Some definitions need not only to be added for Unix98 ( XOPEN_SOURCE>=500 ) ( 937772 )
 * but also for c++ and c99 
 * NOTE: _WCTYPE_CORE_EXTENSIONS_1 is local to this file
 */
#ifndef _WCTYPE_CORE_EXTENSIONS_1
#define _WCTYPE_CORE_EXTENSIONS_1 defined(__c99) || defined(__cplusplus) || (_XOPEN_SOURCE+0 >=500)
#endif

__SGI_LIBC_BEGIN_EXTERN_C

__SGI_LIBC_BEGIN_NAMESPACE_STD

/* C99: 7.25.1 types  wint_t, wctrans_t and wctype_t
               macros WEOF
*/

#ifndef _WINT_T
#   define _WINT_T
#if (_MIPS_SZLONG == 32)
	typedef long	wint_t;
#endif
#if (_MIPS_SZLONG == 64)
	typedef __int32_t wint_t;
#endif
#endif

#if (_MIPS_SIM == _ABIN32 || _MIPS_SIM == _ABI64)
#ifndef _WCTRANS_T
#   define _WCTRANS_T
#if (_MIPS_SZLONG == 32)
	typedef unsigned long	wctrans_t;
#endif
#if (_MIPS_SZLONG == 64)
	typedef __uint32_t	wctrans_t;
#endif
#endif
#endif

#ifndef _WCTYPE_T
#   define _WCTYPE_T
#if (_MIPS_SZLONG == 32)
	typedef unsigned long	wctype_t;
#endif
#if (_MIPS_SZLONG == 64)
	typedef __uint32_t	wctype_t;
#endif
#endif

#ifndef WEOF
#   define WEOF (-1)
#endif

/* C99: 7.25.2 Wide character classification utilities */

extern int	iswalnum(wint_t);
extern int	iswalpha(wint_t);
__SGI_LIBC_END_NAMESPACE_STD
#if defined(__c99)
extern int	iswblank(wint_t);
#endif /* __c99 */
extern int	__iswblank(__SGI_LIBC_NAMESPACE_QUALIFIER wint_t);
__SGI_LIBC_BEGIN_NAMESPACE_STD
extern int	iswcntrl(wint_t);
extern int	iswdigit(wint_t);
extern int	iswgraph(wint_t);
extern int	iswlower(wint_t);
extern int	iswprint(wint_t);
extern int	iswpunct(wint_t);
extern int	iswspace(wint_t);
extern int	iswupper(wint_t);
extern int	iswxdigit(wint_t);

extern int	iswctype(wint_t, wctype_t);
extern wctype_t	wctype(const char *);

/* C99: 7.25.3 Wide character case mapping utilities */

extern wint_t	towlower(wint_t);
extern wint_t	towupper(wint_t);

#if (_MIPS_SIM != _ABI32)
#ifdef _WCTRANS_T
extern wint_t	towctrans (wint_t, wctrans_t);
#if _WCTYPE_CORE_EXTENSIONS_1
extern wctrans_t wctrans(const char *);
#endif /* _WCTYPE_CORE_EXTENSIONS_1 */
#if !defined(_SGI_COMPILING_LIBC)
#pragma optional towctrans
#if _WCTYPE_CORE_EXTENSIONS_1
#pragma optional wctrans
#endif /* _WCTYPE_CORE_EXTENSIONS_1 */
#endif
#endif
#endif

__SGI_LIBC_END_NAMESPACE_STD

extern int __iswctype(__SGI_LIBC_NAMESPACE_QUALIFIER wint_t,
                      __SGI_LIBC_NAMESPACE_QUALIFIER wctype_t);
extern __SGI_LIBC_NAMESPACE_QUALIFIER wint_t
	   __trwctype(__SGI_LIBC_NAMESPACE_QUALIFIER wint_t,
                      __SGI_LIBC_NAMESPACE_QUALIFIER wctype_t);

#define	_E1	0x00000100	/* phonogram (international use) */
#define	_E2	0x00000200	/* ideogram (international use) */
#define	_E3	0x00000400	/* English (international use) */
#define	_E4	0x00000800	/* number (international use) */
#define	_E5	0x00001000	/* special (international use) */
#define	_E6	0x00002000	/* other characters (international use) */

/* Those should match with wchrtbl.c                  */
/*	_E7	0x00004000	   ISWCHAR7 = ISALPHA */
/*	_E8	0x00008000	   ISWCHAR8 = ISPRINT */
#define _E9	0x00010000	/* ISWCHAR9  */	
#define _E10	0x00020000	/* ISWCHAR10 */	
#define _E11	0x00040000	/* ISWCHAR11 */	
#define _E12	0x00080000	/* ISWCHAR12 */	
#define _E13	0x00100000	/* ISWCHAR13 */	
#define _E14	0x00200000	/* ISWCHAR14 */	
#define _E15	0x00400000	/* ISWCHAR15 */	
#define _E16	0x00800000	/* ISWCHAR16 */	
#define _E17	0x01000000	/* ISWCHAR17 */	
#define _E18	0x02000000	/* ISWCHAR18 */	
#define _E19	0x04000000	/* ISWCHAR19 */	
#define _E20	0x08000000	/* ISWCHAR20 */	
#define _E21	0x10000000	/* ISWCHAR21 */	
#define _E22	0x20000000	/* ISWCHAR22 */	

#define _ISwalpha	_ISalpha
#define	_ISwupper	_ISupper
#define	_ISwlower	_ISlower
#define	_ISwdigit	_ISdigit
#define	_ISwxdigit	_ISxdigit
#define	_ISwalnum	_ISalnum
#define	_ISwspace	_ISspace
#define _ISwblank	_ISblank
#define	_ISwpunct	_ISpunct
#define	_ISwprint	(_ISprint|_E1|_E2|_E5|_E6)
#define	_ISwgraph	(_ISgraph|_E1|_E2|_E5|_E6)
#define	_ISwcntrl	_IScntrl

#define	_ISwphonogram	_E1	/* phonogram (international use) */
#define	_ISwideogram	_E2	/* ideogram (international use) */
#define	_ISwenglish	_E3	/* English (international use) */
#define	_ISwnumber	_E4	/* number (international use) */
#define	_ISwspecial	_E5	/* special (international use) */
#define	_ISwother	_E6	/* other characters (international use) */

#if _SGIAPI
#define iscodeset0(c) ( _IS_EUC_LOCALE ? ( !((c) & ~0xff) )    : (*__libc_attr._euc_func._iscodeset)(0,c) )
#define iscodeset1(c) ( _IS_EUC_LOCALE ? ( ((c) >> 28) == 0x3) : (*__libc_attr._euc_func._iscodeset)(1,c) )
#define iscodeset2(c) ( _IS_EUC_LOCALE ? ( ((c) >> 28) == 0x1) : (*__libc_attr._euc_func._iscodeset)(2,c) )
#define iscodeset3(c) ( _IS_EUC_LOCALE ? ( ((c) >> 28) == 0x2) : (*__libc_attr._euc_func._iscodeset)(3,c) )

extern int	iswascii(__SGI_LIBC_NAMESPACE_QUALIFIER wint_t);
extern int	isphonogram(__SGI_LIBC_NAMESPACE_QUALIFIER wint_t);
extern int	isideogram(__SGI_LIBC_NAMESPACE_QUALIFIER wint_t);
extern int	isenglish(__SGI_LIBC_NAMESPACE_QUALIFIER wint_t);
extern int	isnumber(__SGI_LIBC_NAMESPACE_QUALIFIER wint_t);
extern int	isspecial(__SGI_LIBC_NAMESPACE_QUALIFIER wint_t);
#endif /* _SGIAPI */


#if _UNSAFE_WCTYPE && !defined(__cplusplus)
/*
 * Due to ANSI/XPG rules, macro arguments may be only evaluated once.
 * Standard macro definitions of iswprint et.al. require evaluation
 * of their argument twice. So, there are 3 options:
 * 1) no macros
 * 2) stick evaluated argument in a static
 * 3) provide 'unsafe' macros that evaluate the argument twice.
 *
 * Std SVR4 provides 2) - this is really bad for multi-threaded apps
 * as well as signal handlers etc..
 * We opt for 1 and 3 - for applications that explicitly need speed
 * and can guarantee that multiple evaluation is ok, the following are
 * provided.
 *
 * We don't provide macros for C++: it's forbidden by the C++ standard.
 * (section 17.4.1.2, paragraph 6)
 */
#define	iswalpha(c)	( ( _IS_EUC_LOCALE && (c) <= 255) ? isalpha(c) : __iswctype(c, _ISwalpha) )
#define	iswupper(c)	( ( _IS_EUC_LOCALE && (c) <= 255) ? isupper(c) : __iswctype(c, _ISwupper) )
#define	iswlower(c)	( ( _IS_EUC_LOCALE && (c) <= 255) ? islower(c) : __iswctype(c, _ISwlower) )
#define	iswdigit(c)	( ( _IS_EUC_LOCALE && (c) <= 255) ? isdigit(c) : __iswctype(c, _ISwdigit) )
#define	iswxdigit(c)	( ( _IS_EUC_LOCALE && (c) <= 255) ? isxdigit(c) : __iswctype(c, _ISwxdigit) )
#define	iswalnum(c)	( ( _IS_EUC_LOCALE && (c) <= 255) ? isalnum(c) : __iswctype(c, _ISwalnum) )
#define	iswspace(c)	( ( _IS_EUC_LOCALE && (c) <= 255) ? isspace(c) : __iswctype(c, _ISwspace) )
#define __iswblank(c)	( ( _IS_EUC_LOCALE && (c) <= 255) ? __isblank(c) : __iswctype(c, _ISwblank) )
#define	iswpunct(c)	( ( _IS_EUC_LOCALE && (c) <= 255) ? ispunct(c) : __iswctype(c, _ISwpunct) )
#define	iswprint(c)	( ( _IS_EUC_LOCALE && (c) <= 255) ? isprint(c) : __iswctype(c, _ISwprint) )
#define	iswgraph(c)	( ( _IS_EUC_LOCALE && (c) <= 255) ? isgraph(c) : __iswctype(c, _ISwgraph) )
#define	iswcntrl(c)	( ( _IS_EUC_LOCALE && (c) <= 255) ? iscntrl(c) : __iswctype(c, _ISwcntrl) )
#define	iswascii(c)	(!((c) & ~0177))
#define	towupper(c)	( ( _IS_EUC_LOCALE && (c) <= 255) ? toupper(c) : _trwctype(c, _L) )
#define	towlower(c)	( ( _IS_EUC_LOCALE && (c) <= 255) ? tolower(c) : _trwctype(c, _U) )

#endif /* _UNSAFE_WCTYPE */

__SGI_LIBC_END_EXTERN_C

#ifdef _WCTYPE_CORE_EXTENSIONS_1
#undef _WCTYPE_CORE_EXTENSIONS_1
#endif

#endif /* !__WCTYPE_CORE_H__ */

