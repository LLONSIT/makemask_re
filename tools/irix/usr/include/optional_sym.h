#ifndef __OPTIONAL_SYM_H
#define __OPTIONAL_SYM_H

/* $Copyright:$ */

/*
 * Copyright; 1991-1997 Silicon Graphics, Inc.  ALL RIGHTS RESERVED
 * 
 * THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF SGI 
 * 
 * The copyright notice above does not evidence any actual or intended
 * publication or disclosure of this source code, which includes
 * information that is the confidential and/or proprietary, and is a
 * trade secret, of Silicon Graphics, Inc.  Any use, duplication or
 * disclosure not specifically authorized in writing by Silicon
 * Graphics is strictly prohibited. ANY DUPLICATION, MODIFICATION,
 * DISTRIBUTION, PUBLIC PERFORMANCE, OR PUBLIC DISPLAY OF THIS SOURCE
 * CODE WITHOUT THE EXPRESS WRITTEN CONSENT OF SILICON GRAPHICS, INC.
 * IS STRICTLY PROHIBITED.  THE RECEIPT OR POSSESSION OF THIS SOURCE
 * CODE AND/OR INFORMATION DOES NOT CONVEY ANY RIGHTS TO REPRODUCE,
 * DISCLOSE OR DISTRIBUTE ITS CONTENTS, OR TO MANUFACTURE, USE, OR
 * SELL ANYTHING THAT IT MAY DESCRIBE, IN WHOLE OR IN PART. 
 */

/*
 *************************************************************************
 *	Support macros for optional symbols.
 *************************************************************************
 */

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)
#ifdef __cplusplus
extern "C" {
#endif

/*
 *************************************************************************
 *	C USAGE
 *************************************************************************
 *
 *	(1) Defining an optional function in c.
 *
 *		void foo(void) 
 *		#pragma optional foo
 *		{
 *			...
 *		}
 *
 *	(2) Referencing an optional function from c.
 *
 *		#include	<optional_sym.h>
 *		...
 *		if ( _MIPS_SYMBOL_PRESENT(foo) ) {
 *			foo();
 *		} 
 *
 *************************************************************************
 */


/*
 *************************************************************************
 *	__missing_function_
 *
 *	Rld resolves all unresolved optional references to
 *	the symbol "__missing_function_", that is actually
 *	defined in libc.
 *************************************************************************
 */
#define   _MIPS_MISSING_SYMBOL_NAME "__missing_function_"
extern void __missing_function_(void);
#pragma	optional __missing_function_
#pragma	weak     __missing_function_

/*
 *************************************************************************
 *	_MIPS_MISSING_OPTIONAL_SYMBOL(_x)
 *
 *	Returns 1 if the optional symbol '_x' is not defined 
 *	in the current runtime environment.  Returns 0 otherwise.
 *
 *	NOTE:	This macro is valid only for optional symbols.
 *		For example, it will return 0 for a weak undefined
 *		symbol that is not optional symbol.
 *	NOTE:	You should not use this macro in your code, but should
 *		use _MIPS_SYMBOL_PRESENT
 *
 *************************************************************************
 */
#define _MIPS_MISSING_OPTIONAL_SYMBOL(_x) \
		((long)&(_x) == (long)(__missing_function_))


/*
 *************************************************************************
 *	_MIPS_SYMBOL_PRESENT(_x)
 *
 *	Returns 1 if the symbol '_x' is defined in the current
 *	runtime environment.  Returns 0 otherwise.
 *
 *	NOTE: This is a valid check for any and all symbol types.
 *************************************************************************
 */
#define _MIPS_SYMBOL_PRESENT(_x) \
		(((long)&(_x) != 0 ) && (!_MIPS_MISSING_OPTIONAL_SYMBOL(_x)))


#ifdef __cplusplus
}
#endif
#endif /* _LANGUAGE_C || _LANGUAGE_C_PLUS_PLUS */



/*
 *************************************************************************
 *	FORTRAN USAGE
 *************************************************************************
 *
 *	(1) Defining an optional function in Fortran 77/90.
 *
 *			subroutine foo
 *		c*$*    optional (foo)
 *			...
 *			end
 *
 *	(2) Referencing an optional function from Fortran.
 *
 *			subroutine bar
 *		#include "./optional_sym.h"
 *			external foo
 *		c*$*    optional (foo)
 *			if (_MIPS_SYMBOL_PRESENT(foo)) call foo
 *			...
 *			end
 *
 *************************************************************************
 */

/* fortran support not yet ready. */
#if 0
#if defined( _LANGUAGE_FORTRAN)
	external __missing_function
c*$*	optional (__missing_function)
c*$*	weak     (__missing_function)

#define _MIPS_MISSING_OPTIONAL_SYMBOL(_x) \
(%loc(_x).EQ.%loc(__missing_function))
#define	_MIPS_SYMBOL_PRESENT(_x) \
((%loc(_x).NE.0).AND.(%loc(_x).NE.%loc(__missing_function)))
#endif
#endif

#endif /* __OPTIONAL_SYM_H */

/*   Assembler example for optional symbol foo:
 *   .dynsym foo sto_optional
 */
