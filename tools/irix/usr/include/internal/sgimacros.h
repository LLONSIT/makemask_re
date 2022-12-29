/*
 * Copyright 2002, Silicon Graphics, Inc.
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

#ifndef __SGIMACROS_H__
#define __SGIMACROS_H__

/* 
 *
 * Defines the following macros: 
 *
 *   __restrict
 *       For C99 it maps to the restrict keyword
 *       Does nothing otherwise.
 *
 *   __SGI_LIBC_BEGIN_EXTERN_C
 *       Begin an extern "C" block.  Does nothing if this is C.
 *
 *   __SGI_LIBC_END_EXTERN_C
 *       End an extern "C" block.  Does nothing if this is C.
 *
 *   __SGI_LIBC_NAMESPACE
 *       The namespace that the C library is defined in.  Expands to
 *       either std or nothing.
 *
 *   __SGI_LIBC_NAMESPACE_QUALIFIER
 *       The namespace that the C library is defined in.  Expands to
 *       either std:: or nothing.
 *
 *   __SGI_LIBC_BEGIN_NAMESPACE_STD
 *       Begin namespace std. Does nothing unless this is C++ and we're
 *       putting the C library into std.
 *
 *   __SGI_LIBC_END_NAMESPACE_STD
 *       Begin namespace std. Does nothing unless this is C++ and we're
 *       putting the C library into std.
 *
 *   __SGI_LIBC_USING_FROM_STD
 *       Used within global namespace.  Imports a name from namespace std.
 *       Does nothing unless we're this is C++ and we're putting the C
 *       library into std.
 *
 *   __SGI_LIBC_USING_FROM_GLOBAL
 *       Used within namespace std.  Imports a name from the global namespace.
 *       Does nothing unless we're this is C++ and we're putting the C
 *       library into std.
 *
 *   __SGI_LIBC_USE_STRING_OVERLOADS
 *       Defined to indicate that certain string functions from the
 *       C library should be replaced by two overloads, as required
 *       (for const correctness) by the C++ standard.  See, for example,
 *       string_core.h.
 *
 */

#ifdef __c99
#  define __restrict restrict
#else
#  define __restrict
#endif /* __c99 */

#ifdef __cplusplus
#  define __SGI_LIBC_BEGIN_EXTERN_C extern "C" {
#  define __SGI_LIBC_END_EXTERN_C }
#else /* __cplusplus */
#  define __SGI_LIBC_BEGIN_EXTERN_C
#  define __SGI_LIBC_END_EXTERN_C
#endif /* __cplusplus */

#if defined(__cplusplus) && defined(_LIBC_IN_NAMESPACE_STD_)
#  define  __SGI_LIBC_NAMESPACE std
#  define  __SGI_LIBC_NAMESPACE_QUALIFIER std::
#  define  __SGI_LIBC_BEGIN_NAMESPACE_STD namespace std {
#  define  __SGI_LIBC_END_NAMESPACE_STD }
#  define  __SGI_LIBC_USING_FROM_STD(__FN) using std::__FN;
#  define  __SGI_LIBC_USING_FROM_GLOBAL(__FN) using ::__FN;
#else /* defined(__cplusplus) && defined(_LIBC_IN_NAMESPACE_STD_) */
#  define  __SGI_LIBC_NAMESPACE
#  define  __SGI_LIBC_NAMESPACE_QUALIFIER
#  define  __SGI_LIBC_BEGIN_NAMESPACE_STD
#  define  __SGI_LIBC_END_NAMESPACE_STD
#  define  __SGI_LIBC_USING_FROM_STD(__FN)
#  define  __SGI_LIBC_USING_FROM_GLOBAL(__FN)
#endif /* defined(__cplusplus) && defined(_LIBC_IN_NAMESPACE_STD_) */

#if defined(__cplusplus) && \
     defined(_MIPS_SIM) && _MIPS_SIM != _MIPS_SIM_ABI32 && \
     defined(_COMPILER_VERSION) && (_COMPILER_VERSION >= 720) && \
     defined(__LIBC_OVERLOAD__) && __LIBC_OVERLOAD__
#define __SGI_LIBC_USE_STRING_OVERLOADS
#else
#undef __SGI_LIBC_USE_STRING_OVERLOADS
#endif

#endif /* __SGIMACROS_H__ */
