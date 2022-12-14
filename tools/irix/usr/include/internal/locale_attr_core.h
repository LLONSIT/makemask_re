/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1997 Silicon Graphics, Inc.                *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 **************************************************************************/

#ifndef __LOCALE_ATTR_CORE_H__
#define __LOCALE_ATTR_CORE_H__

#include <sgidefs.h>
#include <internal/sgimacros.h>

#ident "$Revision: 1.2 $"

/*
 * This header file contains the definition of the __attr_t type and the
 * declaration of the global attribute object __libc_attr.
 *
 * The __attr_t structure is the first attempt to regroup into one type
 * all the information that defines a locale. This type is the foundation 
 * to the implementation of the m_* functions.
 *
 * The __libc_attr structure is a global instance that is referenced by 
 * existing functions that use locale-dependent information.
 */


/*
 * This structure defines the contents of the LC_CTYPE
 * file. The file is mapped into memory and its first
 * three fields are accessed through macros and functions.
 *
 * NOTE: The current LC_CTYPE file also holds the old ctype structure
 * which is not described here.
 */

__SGI_LIBC_BEGIN_EXTERN_C

typedef struct {

    unsigned int	_class [ 257 ];
    signed short	_lower [ 257 ];
    signed short	_upper [ 257 ];

    char		_cswidth [ 7 ];
    char		_fill [ 1 ];

    /* Beginning of the optional tables generated by wchrtbl */

} __ctype_t;

/* Type of functions used for the ISSET2 and ISSET3 macros */
typedef int	(*__isset_func_t)(int);

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
__SGI_LIBC_END_NAMESPACE_STD

/* Type of function used for the iscodeset macros */
typedef int	(*__iscodeset_func_t)(int, __SGI_LIBC_NAMESPACE_QUALIFIER wint_t);

/* Locale attribute structure */
typedef struct __attr {

    __ctype_t *		_ctype_tbl;	/* Character class information and upper-lower conversion */

    struct _csinfo {			/* EUC encoding information */
	unsigned char	_eucwidth[3];	/* Extended character set width */
	unsigned char	_scrwidth[3];	/* Extended character set screen width */
	unsigned char	_mb_cur_max;	/* Maximum bytes per character in current encoding */
    } _csinfo;

    struct _euc_func {			/* EUC related functions */
	int		_is_euc;	/* Indicates if the current locale is an EUC encoding */
	__isset_func_t	_isset2;	/* Substitions for ISSET2 macros */
	__isset_func_t	_isset3;	/* Substitions for ISSET3 macros */
	__iscodeset_func_t _iscodeset;	/* iscodeset functions */
    } _euc_func;

    struct _collate_res {		/* Resources related to LC_COLLATE category */
	unsigned char	_coll_as_cmp;	/* strcoll()/strxfrm() behave as strcmp()/strcpy() */
    } _collate_res;

    void *		_fill[15];	/* Reserves space for future use */
} __attr_t;

#define _IS_EUC_LOCALE  (__libc_attr._euc_func._is_euc)

/* The global locale attribute structure */
extern __attr_t __libc_attr;

__SGI_LIBC_END_EXTERN_C

#endif /* __LOCALE_ATTR_CORE_H__ */
