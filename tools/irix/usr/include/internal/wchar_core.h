#ifndef _WCHAR_CORE_H
#define _WCHAR_CORE_H
#ident "$Revision: 1.13 $"
/*
*
* Copyright 1995, Silicon Graphics, Inc.
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
#include <sgidefs.h>
#include <standards.h>
#include <internal/sgimacros.h>

/*
 * This is an XPG4 header
 * and modified for XPG5
 */

/* 
 * Some definitions need not only to be added for Unix98 ( XOPEN_SOURCE>=500 ) ( 937772 )
 * but also for c++ and c99 
 * NOTE: _WCHAR_CORE_EXTENSIONS_1 is local to this file
 */
#ifndef _WCHAR_CORE_EXTENSIONS_1
#define _WCHAR_CORE_EXTENSIONS_1 defined(__c99) || defined(__cplusplus) || (_XOPEN_SOURCE+0 >=500)
#endif

__SGI_LIBC_BEGIN_EXTERN_C

__SGI_LIBC_BEGIN_NAMESPACE_STD

/* C99: 7.24.1 types  wchar_t, wctype_t, size_t, mbstate_t and wint_t
                      struct tm is not being declared here
                      as wchar.h includes time.h, and
                         cwchar  includes ctime.
               macros NULL, WCHAR_MIN, WCHAR_MAX and WEOF.
*/

#if !defined(_SIZE_T) && !defined(_SIZE_T_)
#define _SIZE_T
#if (_MIPS_SZLONG == 32)
typedef unsigned int	size_t;
#endif
#if (_MIPS_SZLONG == 64)
typedef unsigned long	size_t;
#endif
#endif

#ifndef _WCHAR_T
#define _WCHAR_T
#if (_MIPS_SZLONG == 32)
typedef long wchar_t;
#endif
#if (_MIPS_SZLONG == 64)
typedef __int32_t wchar_t;
#endif
#endif

__SGI_LIBC_END_NAMESPACE_STD

/* wuchar_t isn't part of the C++ standard */

#ifndef _WUCHAR_T
#   define _WUCHAR_T
#if (_MIPS_SZLONG == 32)
	typedef unsigned long	wuchar_t;
#endif
#if (_MIPS_SZLONG == 64)
	typedef __uint32_t	wuchar_t;
#endif
#endif

__SGI_LIBC_BEGIN_NAMESPACE_STD

#ifndef _WINT_T
#   define _WINT_T
#if (_MIPS_SZLONG == 32)
	typedef long	wint_t;
#endif
#if (_MIPS_SZLONG == 64)
	typedef __int32_t wint_t;
#endif
#endif

#ifndef _WCTYPE_T
#   define _WCTYPE_T
#if (_MIPS_SZLONG == 32)
	typedef unsigned long   wctype_t;
#endif
#if (_MIPS_SZLONG == 64)
	typedef __uint32_t      wctype_t;
#endif
#endif

#ifndef _MBSTATE_T
#   define _MBSTATE_T
	typedef char	mbstate_t;
#endif

#ifndef NULL
#   define NULL	0L
#endif

#if _WCHAR_CORE_EXTENSIONS_1
#if (_MIPS_SIM == _ABIN32 || _MIPS_SIM == _ABI64)
#ifndef WCHAR_MAX
#define WCHAR_MAX 2147483647
#endif
#ifndef WCHAR_MIN
#define WCHAR_MIN (-2147483647-1)
#endif
#endif
#endif /* _WCHAR_CORE_EXTENSIONS_1 */

#ifndef WEOF
#   define WEOF	(-1)
#endif

/* C99: 7.25.2 Wide character classification utilities */

extern int	iswalnum(wint_t);
extern int	iswalpha(wint_t);
__SGI_LIBC_END_NAMESPACE_STD
#if defined(__c99)
extern int	iswblank(wint_t);
#if !defined(_SGI_COMPILING_LIBC)
#pragma optional iswblank
#endif
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

/* C99: 7.24.2 Formatted wide character input/output functions */

#if (_MIPS_SIM == _ABIN32 || _MIPS_SIM == _ABI64)
#if _WCHAR_CORE_EXTENSIONS_1
extern int fwprintf(FILE * __restrict, const wchar_t * __restrict, ...);
extern int fwscanf(FILE * __restrict, const wchar_t * __restrict, ...);
extern int swprintf(wchar_t * __restrict, size_t, const wchar_t * __restrict, ...);
extern int swscanf(const wchar_t * __restrict, const wchar_t * __restrict, ...);
extern int vfwprintf(FILE * __restrict, const wchar_t * __restrict, va_list);

extern int vswprintf(wchar_t * __restrict, size_t, const wchar_t * __restrict, va_list);
extern int vwprintf(const wchar_t * __restrict, va_list);
extern int wprintf(const wchar_t * __restrict, ...);
extern int wscanf(const wchar_t * __restrict, ...);

#if !defined(_SGI_COMPILING_LIBC)
#pragma optional fwprintf
#pragma optional fwscanf
#pragma optional swprintf
#pragma optional swscanf
#pragma optional vfwprintf
#pragma optional vswprintf
#pragma optional vwprintf
#pragma optional wprintf
#pragma optional wscanf
#endif
#endif /* _WCHAR_CORE_EXTENSIONS_1 */

#if defined(__c99)
extern int vfwscanf(FILE * __restrict, const wchar_t * __restrict, va_list);
extern int vswscanf(const wchar_t * __restrict, const wchar_t * __restrict, va_list);
extern int vwscanf(const wchar_t * __restrict, va_list);
#if !defined(_SGI_COMPILING_LIBC)
#pragma optional vfwscanf
#pragma optional vswscanf
#pragma optional vwscanf
#endif
#endif /* __c99 */
#endif /* _MIPS_SIM == _ABIN32 || _MIPS_SIM == ABI64 */


/* C99: 7.24.3 Wide character input output functions */

extern wint_t	fgetwc(FILE *);
extern wchar_t	*fgetws(wchar_t * __restrict, int, FILE * __restrict);
extern wint_t	fputwc(wint_t, FILE *);
extern int	fputws(const wchar_t * __restrict, FILE * __restrict);
#if _WCHAR_CORE_EXTENSIONS_1
extern int      fwide(FILE *, int);
#endif /* _WCHAR_CORE_EXTENSIONS_1 */
extern wint_t	getwc(FILE *);
extern wint_t	getwchar(void);
extern wint_t	putwc(wint_t, FILE *);
extern wint_t	putwchar(wint_t);
extern wint_t	ungetwc(wint_t, FILE *);
#if (_SGIAPI && _NO_ANSIMODE)
extern wchar_t	*getws(wchar_t *);
extern int	putws(wchar_t *);
#endif /* _SGIAPI && _NO_ANSIMODE */
#ifndef __cplusplus
#define getwchar()	getwc(stdin)
#define putwchar(x)	putwc((x), stdout)
#endif /* __cplusplus */

/* C99: 7.24.4 General wide string utilities */

/* C99: 7.24.4.1 Wide string numeric conversion functions */

extern double	wcstod(const wchar_t * __restrict, wchar_t ** __restrict);
#if (_MIPS_SIM != _ABI32)
#if defined(__c99)
extern float    wcstof(const wchar_t * __restrict, wchar_t ** __restrict);
extern long double wcstold(const wchar_t * __restrict, wchar_t ** __restrict);
#if !defined(_SGI_COMPILING_LIBC)
#pragma optional wcstof 
#pragma optional wcstold 
#endif
#endif /* __c99 */
#endif

extern long	wcstol(const wchar_t * __restrict, wchar_t ** __restrict, int);
#if defined(__c99) || _ABIAPI || _SGIAPI
extern long long wcstoll(const wchar_t * __restrict, wchar_t ** __restrict, int);
#endif
extern unsigned long	wcstoul(const wchar_t * __restrict, wchar_t ** __restrict, int);
#if defined(__c99) || _ABIAPI || _SGIAPI
extern unsigned long long wcstoull(const wchar_t * __restrict, wchar_t ** __restrict, int);
#endif

/* C99: 7.24.4.2 Wide string copying functions */

extern wchar_t	*wcscpy(wchar_t * __restrict, const wchar_t * __restrict);
extern wchar_t	*wcsncpy(wchar_t * __restrict, const wchar_t * __restrict, size_t);
#if _WCHAR_CORE_EXTENSIONS_1
#if (_MIPS_SIM == _ABIN32 || _MIPS_SIM == _ABI64)
extern wchar_t  *wmemcpy(wchar_t * __restrict, const wchar_t * __restrict, size_t);
extern wchar_t  *wmemmove(wchar_t *, const wchar_t *, size_t);
#if !defined(_SGI_COMPILING_LIBC)
#pragma optional wmemcpy
#pragma optional wmemmove
#endif
#endif
#endif /* _WCHAR_CORE_EXTENSIONS_1 */

/* C99: 7.24.4.3 Wide string concatenation functions */

extern wchar_t	*wcscat(wchar_t * __restrict, const wchar_t * __restrict);
extern wchar_t	*wcsncat(wchar_t * __restrict, const wchar_t * __restrict, size_t);

/* C99: 7.24.4.4 Wide string comparison functions */

extern int	wcscmp(const wchar_t *, const wchar_t *);
extern int	wcscoll(const wchar_t *, const wchar_t *);
extern int	wcsncmp(const wchar_t *, const wchar_t *, size_t);
extern size_t	wcsxfrm(wchar_t * __restrict, const wchar_t * __restrict, size_t);
#if _WCHAR_CORE_EXTENSIONS_1
#if (_MIPS_SIM == _ABIN32 || _MIPS_SIM == _ABI64)
extern int      wmemcmp(const wchar_t *, const wchar_t *, size_t);
#if !defined(_SGI_COMPILING_LIBC)
#pragma optional wmemcmp
#endif
#endif
#endif /* _WCHAR_CORE_EXTENSIONS_1 */

/* C99: 7.24.4.5 Wide string search functions */

#ifndef __SGI_LIBC_USE_STRING_OVERLOADS
extern wchar_t	*wcschr(const wchar_t *, wint_t);
#endif /* __SGI_LIBC_USE_STRING_OVERLOADS */
extern size_t	wcscspn(const wchar_t *, const wchar_t *);
extern wchar_t	*wcspbrk(const wchar_t *, const wchar_t *);
#ifndef __SGI_LIBC_USE_STRING_OVERLOADS
extern wchar_t	*wcsrchr(const wchar_t *, wchar_t);
#endif /* __SGI_LIBC_USE_STRING_OVERLOADS */
extern size_t	wcsspn(const wchar_t *, const wchar_t *);
#ifndef __SGI_LIBC_USE_STRING_OVERLOADS
extern wchar_t	*wcsstr(const wchar_t *, const wchar_t *);
#endif /* __SGI_LIBC_USE_STRING_OVERLOADS */

#if !defined(_SGI_COMPILING_LIBC)
#if (_MIPS_SIM == _ABIN32 || _MIPS_SIM == _ABI64)
#if _NO_XOPEN5
extern wchar_t  *      wcstok(wchar_t *, const wchar_t *);
extern wchar_t  *_xpg4_wcstok(wchar_t *, const wchar_t *);
#pragma optional _xpg4_wcstok
#else
extern wchar_t  *_xpg5_wcstok(wchar_t * __restrict, const wchar_t * __restrict, wchar_t ** __restrict);
#ifdef _XPG5_WCSTOK_USER_DEFINED
/*
 * If you need to define your own wcstok function, use the
 * -D_XPG5_WCSTOK_USER_DEFINED option at compile time. A user defined
 * wcstok function must be defined with the function prototype below.
 * The wcstok function in libc will not work correctly with this prototype.
 */
extern wchar_t  *      wcstok(wchar_t * __restrict, const wchar_t * __restrict, wchar_t ** __restrict);
#else
/*
 * Since the static function is defined in each source file that 
 * includes this header file, these static functions will have 
 * different addresses in any cases that inline expansion is not
 * performed. This may cause problems if the address of the 
 * function is examined in programs.
 */
/*REFERENCED*/
static __inline wchar_t  *wcstok(wchar_t * __restrict _ws1, const wchar_t * __restrict _ws2, wchar_t ** __restrict _pws)
{
	return(_xpg5_wcstok(_ws1, _ws2, _pws)); 
}
#endif
#pragma optional _xpg5_wcstok
#endif
#else
extern wchar_t  *wcstok(wchar_t *, const wchar_t *);
#endif
#else /* _SGI_COMPILING_LIBC */
#if (_MIPS_SIM == _ABIN32 || _MIPS_SIM == _ABI64)
extern wchar_t  *wcstok(wchar_t *, const wchar_t *, wchar_t **);
extern wchar_t  *_xpg4_wcstok(wchar_t *,            const wchar_t *);
extern wchar_t	*_xpg5_wcstok(wchar_t * __restrict, const wchar_t * __restrict, wchar_t ** __restrict);
#else
extern wchar_t  *wcstok(wchar_t *, const wchar_t *);
#endif
#endif /* !defined(_SGI_COMPILING_LIBC) */

#if _WCHAR_CORE_EXTENSIONS_1
#if (_MIPS_SIM == _ABIN32 || _MIPS_SIM == _ABI64)
extern wchar_t  *wmemchr(const wchar_t *, wchar_t, size_t);
#if !defined(_SGI_COMPILING_LIBC)
#pragma optional wmemchr
#endif
#endif
#endif /* _WCHAR_CORE_EXTENSIONS_1 */

/* C99: 7.24.4.6 Miscellaneous functions */

extern size_t	wcslen(const wchar_t *);
#if _WCHAR_CORE_EXTENSIONS_1
#if (_MIPS_SIM == _ABIN32 || _MIPS_SIM == _ABI64)
extern wchar_t  *wmemset(wchar_t *, wchar_t, size_t);
#if !defined(_SGI_COMPILING_LIBC)
#pragma optional wmemset
#endif
#endif
#endif /* _WCHAR_CORE_EXTENSIONS_1 */

/* C99: 7.24.5 Wide character time conversion functions */

#if !defined(_SGI_COMPILING_LIBC)
#if (_MIPS_SIM == _ABIN32 || _MIPS_SIM == _ABI64)
#if _NO_XOPEN5
extern size_t          wcsftime(wchar_t *, __SGI_LIBC_NAMESPACE_QUALIFIER size_t, const char *, const struct tm *);
extern size_t    _xpg4_wcsftime(wchar_t *, __SGI_LIBC_NAMESPACE_QUALIFIER size_t, const char *, const struct tm *);
#pragma optional _xpg4_wcsftime
#else
extern size_t    _xpg5_wcsftime(wchar_t * __restrict, __SGI_LIBC_NAMESPACE_QUALIFIER size_t, const wchar_t * __restrict, const struct tm * __restrict);
#ifdef _XPG5_WCSFTIME_USER_DEFINED
/*
 * If you need to define your own wcsftime function, use the 
 * -D_XPG5_WCSFTIME_USER_DEFINED option at compile time. A user defined 
 * wcsftime function must be defined with the function prototype below. 
 * The wcsftime function in libc will not work correctly with this prototype. 
 */
extern size_t          wcsftime(wchar_t * __restrict, __SGI_LIBC_NAMESPACE_QUALIFIER size_t, const wchar_t * __restrict, const struct tm * __restrict);
#else
/*
 * Since the static function is defined in each source file that 
 * includes this header file, these static functions will have 
 * different addresses in any cases that inline expansion is not 
 * performed. This may cause problems if the address of the 
 * function is examined in programs.
 */
/*REFERENCED*/
static __inline size_t wcsftime(wchar_t * __restrict _wcs, __SGI_LIBC_NAMESPACE_QUALIFIER size_t _maxsize, const wchar_t * __restrict _format, const struct tm * __restrict _timptr)
{
	return(_xpg5_wcsftime(_wcs, _maxsize, _format, _timptr));
}
#endif
#pragma optional _xpg5_wcsftime
#endif /* _NO_XOPEN5 */
#else
extern size_t   wcsftime(wchar_t *, size_t, const char *, const struct tm *);
#endif
#else /* _SGI_COMPILING_LIBC */
#if (_MIPS_SIM == _ABIN32 || _MIPS_SIM == _ABI64)
extern size_t   wcsftime(wchar_t *, size_t, const char *, const struct tm *);
extern size_t   _xpg4_wcsftime(wchar_t *,            size_t, const char *,               const struct tm *);
extern size_t	_xpg5_wcsftime(wchar_t * __restrict, size_t, const wchar_t * __restrict, const struct tm * __restrict);
#else
extern size_t   wcsftime(wchar_t *, size_t, const char *, const struct tm *);
#endif
#endif /* !defined(_SGI_COMPILING_LIBC) */

/* C99: 7.24.6 Extended multibyte/wide character conversion utilities */

/* C99: 7.24.6.1 Single-byte/wide character conversion functions */

#if _WCHAR_CORE_EXTENSIONS_1 || defined(_SGI_COMPILING_LIBC)
#if (_MIPS_SIM == _ABIN32 || _MIPS_SIM == _ABI64)
extern wint_t   btowc(int);
extern int      wctob(wint_t);
#if !defined(_SGI_COMPILING_LIBC)
#pragma optional btowc
#pragma optional wctob
#endif
#endif

/* C99: 7.24.6.2 Conversion state functions */

#if (_MIPS_SIM == _ABIN32 || _MIPS_SIM == _ABI64)
extern int      mbsinit(const mbstate_t *);
#if !defined(_SGI_COMPILING_LIBC)
#pragma optional mbsinit
#endif
#endif

/* C99: 7.24.6.3 Restartable multibyte/wide character conversion functions */

#if (_MIPS_SIM == _ABIN32 || _MIPS_SIM == _ABI64)
extern size_t   mbrlen(const char * __restrict, size_t, mbstate_t * __restrict);
extern size_t   mbrtowc(wchar_t * __restrict, const char * __restrict, size_t, mbstate_t * __restrict);
extern size_t   wcrtomb(char * __restrict, wchar_t, mbstate_t * __restrict);
#if !defined(_SGI_COMPILING_LIBC)
#pragma optional mbrlen
#pragma optional mbrtowc
#pragma optional wcrtomb
#endif
#endif

/* C99: 7.24.6.4 Restartable multibyte/wide string conversion functions */

#if (_MIPS_SIM == _ABIN32 || _MIPS_SIM == _ABI64)
extern size_t   mbsrtowcs(wchar_t * __restrict, const char ** __restrict, size_t, mbstate_t * __restrict);
extern size_t   wcsrtombs(char * __restrict, const wchar_t ** __restrict, size_t, mbstate_t * __restrict);
#if !defined(_SGI_COMPILING_LIBC)
#pragma optional mbsrtowcs
#pragma optional wcsrtombs
#endif
#endif
#endif /* _WCHAR_CORE_EXTENSIONS_1 || defined(_SGI_COMPILING_LIBC) */

/* functions not specified in C99 */

extern int	wcwidth(wchar_t);
extern int	wcswidth(const wchar_t *, size_t);
extern wchar_t	*wcswcs(const wchar_t *, const wchar_t *);

#ifndef _SGI_COMPILING_LIBC
#if _WCHAR_CORE_EXTENSIONS_1
#pragma optional fwide
#endif /* _WCHAR_CORE_EXTENSIONS_1 */
#endif /* _SGI_COMPILING_LIBC */

__SGI_LIBC_END_NAMESPACE_STD

#if _SGIAPI
extern wchar_t  *wcstok_r(wchar_t *, const wchar_t *, wchar_t **);
#endif /* _SGIAPI */

__SGI_LIBC_END_EXTERN_C

#ifdef __SGI_LIBC_USE_STRING_OVERLOADS

/*
 * In C++, five of the functions from the C wide string library are replaced
 * by overloaded pairs.  (Overloaded on const.)  In each case, there is
 * no semantic difference between the C function and the C++ functions.
 * We handle this by declaring the C version in an internal namespace;
 * each C++ version just turns around and calls the C version, performing
 * whatever const manipulations are necessary.  Note that this trick only
 * works because a namespace doesn't appear in the mangled name of an
 * extern "C" function.  Extern "C" names aren't mangled.
 */

namespace __sgilib {
__SGI_LIBC_BEGIN_EXTERN_C
extern wchar_t	*wcschr(const wchar_t *, __SGI_LIBC_NAMESPACE_QUALIFIER wint_t);
extern wchar_t	*wcspbrk(const wchar_t *, const wchar_t *);
extern wchar_t	*wcsrchr(const wchar_t *, wchar_t);
extern wchar_t	*wcsstr(const wchar_t *, const wchar_t *);
__SGI_LIBC_END_EXTERN_C
} /* Close namespace __sgilib. */

__SGI_LIBC_BEGIN_NAMESPACE_STD

inline const wchar_t* wcschr(const wchar_t* s, wint_t c) {
  return __sgilib::wcschr(s, c);
}

inline wchar_t* wcschr(wchar_t* s, wint_t c) {
  return __sgilib::wcschr(s, c);
}

inline const wchar_t* wcspbrk(const wchar_t* s1, const wchar_t* s2) {
  return __sgilib::wcspbrk(s1, s2);
}

inline wchar_t* wcspbrk(wchar_t* s1, const wchar_t* s2) {
  return __sgilib::wcspbrk(s1, s2);
}

inline const wchar_t* wcsrchr(const wchar_t* s, wchar_t c) {
  return __sgilib::wcsrchr(s, c);
}

inline wchar_t* wcsrchr(wchar_t* s, wchar_t c) {
  return __sgilib::wcsrchr(s, c);
}

inline const wchar_t* wcsstr(const wchar_t* s1, const wchar_t* s2) {
  return __sgilib::wcsstr(s1, s2);
}

inline wchar_t* wcsstr(wchar_t* s1, const wchar_t* s2) {
  return __sgilib::wcsstr(s1, s2);
}

__SGI_LIBC_END_NAMESPACE_STD

#endif /* __SGI_LIBC_USE_STRING_OVERLOADS */

#ifdef _WCHAR_CORE_EXTENSIONS_1
#undef _WCHAR_CORE_EXTENSIONS_1
#endif

#endif /*_WCHAR_H*/
