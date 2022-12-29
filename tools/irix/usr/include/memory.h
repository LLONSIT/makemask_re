#ifndef __MEMORY_H__
#define __MEMORY_H__

#ident "$Revision: 1.10 $"
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
/*	Copyright (c) 1990, 1991 UNIX System Laboratories, Inc.	*/
/*	Copyright (c) 1988 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF     	*/
/*	UNIX System Laboratories, Inc.                     	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#include <internal/sgimacros.h>

/* from stddef.h */
#if !defined(_SIZE_T) && !defined(_SIZE_T_)
#define _SIZE_T
__SGI_LIBC_BEGIN_NAMESPACE_STD
#if (_MIPS_SZLONG == 32)
typedef unsigned int	size_t;
#endif
#if (_MIPS_SZLONG == 64)
typedef unsigned long	size_t;
#endif
__SGI_LIBC_END_NAMESPACE_STD
__SGI_LIBC_USING_FROM_STD(size_t)
#endif

__SGI_LIBC_BEGIN_NAMESPACE_STD
__SGI_LIBC_BEGIN_EXTERN_C
extern void *memccpy(void *, const void *, int, size_t);
#ifndef __SGI_LIBC_USE_STRING_OVERLOADS
extern void *memchr(const void *, int, size_t);
#endif /* __SGI_LIBC_USE_STRING_OVERLOADS */
extern void *memcpy(void *, const void *, size_t);
extern void *memset(void *, int, size_t);
extern int memcmp(const void *, const void *, size_t);
__SGI_LIBC_END_EXTERN_C
__SGI_LIBC_END_NAMESPACE_STD

#ifdef __SGI_LIBC_USE_STRING_OVERLOADS
#ifndef __sgi_cpp_memchr_defined
#define __sgi_cpp_memchr_defined

namespace __sgilib {
__SGI_LIBC_BEGIN_EXTERN_C
extern void *memchr(const void *, int, size_t);
__SGI_LIBC_END_EXTERN_C
} /* Close namespace __sgilib */

__SGI_LIBC_BEGIN_NAMESPACE_STD
inline const void* memchr(const void* s, int c, size_t n) {
  return __sgilib::memchr(s, c, n);
}

inline void* memchr(void* s, int c, size_t n) {
  return __sgilib::memchr(s, c, n);
}
__SGI_LIBC_END_NAMESPACE_STD
#endif /* __sgi_cpp_memchr_defined */
#endif /* __SGI_LIBC_USE_STRING_OVERLOADS */

__SGI_LIBC_USING_FROM_STD(memccpy)
__SGI_LIBC_USING_FROM_STD(memchr)
__SGI_LIBC_USING_FROM_STD(memcpy)
__SGI_LIBC_USING_FROM_STD(memset)
__SGI_LIBC_USING_FROM_STD(memcmp)

#endif /* !__MEMORY_H__ */
