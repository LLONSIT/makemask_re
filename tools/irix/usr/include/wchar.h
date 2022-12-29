#ifndef _WCHAR_H
#define _WCHAR_H

#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <locale_attr.h>
#if _NO_XOPEN5
#include <wctype.h>
#endif
#include <internal/wchar_core.h>

__SGI_LIBC_USING_FROM_STD(size_t)
__SGI_LIBC_USING_FROM_STD(wint_t)
__SGI_LIBC_USING_FROM_STD(mbstate_t)
__SGI_LIBC_USING_FROM_STD(wctype_t)
__SGI_LIBC_USING_FROM_STD(iswalnum)
__SGI_LIBC_USING_FROM_STD(iswalpha)
__SGI_LIBC_USING_FROM_STD(iswcntrl)
__SGI_LIBC_USING_FROM_STD(iswdigit)
__SGI_LIBC_USING_FROM_STD(iswgraph)
__SGI_LIBC_USING_FROM_STD(iswlower)
__SGI_LIBC_USING_FROM_STD(iswprint)
__SGI_LIBC_USING_FROM_STD(iswpunct)
__SGI_LIBC_USING_FROM_STD(iswspace)
__SGI_LIBC_USING_FROM_STD(iswupper)
__SGI_LIBC_USING_FROM_STD(iswxdigit)
__SGI_LIBC_USING_FROM_STD(iswctype)
__SGI_LIBC_USING_FROM_STD(wctype)
__SGI_LIBC_USING_FROM_STD(towlower)
__SGI_LIBC_USING_FROM_STD(towupper)

__SGI_LIBC_USING_FROM_STD(fwprintf)
__SGI_LIBC_USING_FROM_STD(fwscanf)
__SGI_LIBC_USING_FROM_STD(swprintf)
__SGI_LIBC_USING_FROM_STD(swscanf)
__SGI_LIBC_USING_FROM_STD(vfwprintf)
#if defined(__c99)
__SGI_LIBC_USING_FROM_STD(vfwscanf)
#endif /* __c99 */
__SGI_LIBC_USING_FROM_STD(vswprintf)
#if defined(__c99)
__SGI_LIBC_USING_FROM_STD(vswscanf)
#endif /* __c99 */
__SGI_LIBC_USING_FROM_STD(vwprintf)
#if defined(__c99)
__SGI_LIBC_USING_FROM_STD(vwscanf)
#endif /* __c99 */
__SGI_LIBC_USING_FROM_STD(wprintf)
__SGI_LIBC_USING_FROM_STD(wscanf)

__SGI_LIBC_USING_FROM_STD(fgetwc)
__SGI_LIBC_USING_FROM_STD(fgetws)
__SGI_LIBC_USING_FROM_STD(fputwc)
__SGI_LIBC_USING_FROM_STD(fputws)
__SGI_LIBC_USING_FROM_STD(fwide)
__SGI_LIBC_USING_FROM_STD(getwc)
__SGI_LIBC_USING_FROM_STD(getwchar)
__SGI_LIBC_USING_FROM_STD(putwc)
__SGI_LIBC_USING_FROM_STD(putwchar)
__SGI_LIBC_USING_FROM_STD(ungetwc)

__SGI_LIBC_USING_FROM_STD(wcstod)
#if defined(__c99)
__SGI_LIBC_USING_FROM_STD(wcstof)
__SGI_LIBC_USING_FROM_STD(wcstold)
#endif /* __c99 */

__SGI_LIBC_USING_FROM_STD(wcstol)
#if defined(_c99) || _ABIAPI || _SGIAPI
__SGI_LIBC_USING_FROM_STD(wcstoll)
#endif /* defined(_c99) || _ABIAPI || _SGIAPI */
__SGI_LIBC_USING_FROM_STD(wcstoul)
#if defined(_c99) || _ABIAPI || _SGIAPI
__SGI_LIBC_USING_FROM_STD(wcstoull)
#endif /* defined(_c99) || _ABIAPI || _SGIAPI */

__SGI_LIBC_USING_FROM_STD(wcscpy)
__SGI_LIBC_USING_FROM_STD(wcsncpy)
__SGI_LIBC_USING_FROM_STD(wmemcpy)
__SGI_LIBC_USING_FROM_STD(wmemmove)

__SGI_LIBC_USING_FROM_STD(wcscat)
__SGI_LIBC_USING_FROM_STD(wcsncat)

__SGI_LIBC_USING_FROM_STD(wcscmp)
__SGI_LIBC_USING_FROM_STD(wcscoll)
__SGI_LIBC_USING_FROM_STD(wcsncmp)
__SGI_LIBC_USING_FROM_STD(wcsxfrm)
__SGI_LIBC_USING_FROM_STD(wmemcmp)

__SGI_LIBC_USING_FROM_STD(wcschr)
__SGI_LIBC_USING_FROM_STD(wcscspn)
__SGI_LIBC_USING_FROM_STD(wcspbrk)
__SGI_LIBC_USING_FROM_STD(wcsrchr)
__SGI_LIBC_USING_FROM_STD(wcsspn)
__SGI_LIBC_USING_FROM_STD(wcsstr)
__SGI_LIBC_USING_FROM_STD(wcstok)
__SGI_LIBC_USING_FROM_STD(wmemchr)
__SGI_LIBC_USING_FROM_STD(wcslen)
__SGI_LIBC_USING_FROM_STD(wmemset)

__SGI_LIBC_USING_FROM_STD(wcsftime)

#if (_MIPS_SIM == _ABIN32 || _MIPS_SIM == _ABI64)
__SGI_LIBC_USING_FROM_STD(btowc)
__SGI_LIBC_USING_FROM_STD(wctob)
#endif

#if (_MIPS_SIM == _ABIN32 || _MIPS_SIM == _ABI64)
__SGI_LIBC_USING_FROM_STD(mbsinit)
#endif

#if (_MIPS_SIM == _ABIN32 || _MIPS_SIM == _ABI64)
__SGI_LIBC_USING_FROM_STD(mbrlen)
__SGI_LIBC_USING_FROM_STD(mbrtowc)
__SGI_LIBC_USING_FROM_STD(wcrtomb)
#endif

#if (_MIPS_SIM == _ABIN32 || _MIPS_SIM == _ABI64)
__SGI_LIBC_USING_FROM_STD(mbsrtowcs)
__SGI_LIBC_USING_FROM_STD(wcsrtombs)
#endif

__SGI_LIBC_USING_FROM_STD(wcwidth)
__SGI_LIBC_USING_FROM_STD(wcswidth)
__SGI_LIBC_USING_FROM_STD(wcswcs)

#endif /* _WCHAR_H */
