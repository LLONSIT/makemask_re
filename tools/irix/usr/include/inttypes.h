/* ====================================================================
 * ====================================================================
 *
 * Module: inttypes.h
 * $Revision: 1.6 $
 * $Date: 2002/09/10 02:57:20 $
 *
 * Revision history:
 *  14-Sep-92 - Original Version
 *  28-Oct-92 - Revisions from 7 October committee meeting.
 *  29-Oct-92 - Minor adjustments based on comments.
 *  26-Feb-93 - Revisions from November committee meeting.
 *  17-Aug-93 - Converted template to SGI-specific form.
 *
 * Description:
 *
 * This header defines types (via typedefs) with size attributes which
 * are independent of the definitions of the base C types provided by
 * the implementation.  It also defines facilities for manipulating
 * objects of those types, i.e. defining constants, printf/scanf
 * support, and conversions.
 *
 * The intent is that, using this header file and the facilities it
 * describes, a user can write C code with fixed-size objects which
 * is interoperable and portable among a broad range of target
 * environments, including 16-bit or 32-bit PCs as well as 32-bit or
 * 64-bit workstations.
 *
 * ====================================================================
 * ====================================================================
 */

#ifndef __INTTYPES_H__
#define __INTTYPES_H__

/* The following values encode the current revision of the template.
 * The first "official" release will be 1.0.  Subsequent releases will
 * increment the major ID for significant or incompatible changes, and
 * the minor ID for minor extensions.
 */
#define __INTTYPES_MAJOR	0
#define __INTTYPES_MINOR	1

/* ===========================  TYPES  ============================= */

/* Define the basic fixed-size integer types.  Their intended semantics
 * are to produce objects of precisely the implied size, and to cause
 * (as operands) expression evaluation of either that size or the size
 * of the underlying 'int' type if larger (the normal ANSI C promotion
 * rules).
 *
 * intmax_t and uintmax_t are integer types guaranteed to be the
 * largest supported by the implementation.  They are intended for
 * use in places where code must be able to cope with any integer
 * value.
 *
 * intptr_t and uintptr_t are integer types guaranteed to be exactly
 * the size of a pointer.
 */

#include <standards.h>
#include <sgidefs.h>
#include <internal/sgimacros.h>

#if !(defined(__c99))

#ifndef __inttypes_INCLUDED
#define __inttypes_INCLUDED
/*
 * These definitions are also in sys/types.h and need to be kept consistent
 */

typedef	signed char		int8_t;	
typedef	unsigned char		uint8_t;
typedef	signed short		int16_t;
typedef	unsigned short		uint16_t;
typedef	signed int		int32_t;
typedef	unsigned int		uint32_t;
typedef	__int64_t           	int64_t;
typedef	__uint64_t            	uint64_t;
typedef __int64_t           	intmax_t;
typedef __uint64_t            	uintmax_t;
typedef signed long int		intptr_t;
typedef unsigned long int	uintptr_t;

#endif

#if _SGIAPI
/* Define limits for the types, in the manner of limits.h: */
#define INT8_MIN	(-127-1)
#define INT8_MAX	(127)
#define UINT8_MAX	(255u)
#define INT16_MIN	(-32767-1)
#define INT16_MAX	(32767)
#define UINT16_MAX	(65535u)
#define INT32_MIN	(-2147483647-1)
#define INT32_MAX	(2147483647)
#define UINT32_MAX	(4294967295u)
#define INT64_MIN	(-9223372036854775807LL-1)
#define INT64_MAX	(9223372036854775807LL)
#define UINT64_MAX	(18446744073709551615uLL)
#define INTMAX_MIN	(-9223372036854775807LL-1)
#define INTMAX_MAX	(9223372036854775807LL)
#define UINTMAX_MAX	(18446744073709551615uLL)

/* ========================  CONSTANTS  ============================ */

/* Define macros for constants of the above types.  The intent is that:
 *
 *   -	Constants defined using these macros have a specific length and
 *	signedness.
 *
 *   -	Their extensions in contexts requiring extension (e.g.
 *	expressions of greater precision than the specified length)
 *	will be totally determined by that signedness and length.
 *	For example:
 *			INT32_C(0xffffffff)
 *	should define a 32-bit signed negative one, to be sign extended
 *	if the context requires a 64-bit value.  Observe that the
 *	identity macro in an LP64 model would yield a 32-bit unsigned
 *	4 billion something (unsigned int, because the value doesn't
 *	fit in a 32-bit int), whereas in an ILP64 model it would yield
 *	a 64-bit signed 4 billion something (signed int).
 *
 *   -	Use of such a constant will not itself force greater precision
 *	than the specified length.  For example:
 *			UINT32_C(3000000000)
 *	should define a 32-bit unsigned 3 billion, even in an LP64
 *	implementation where the simple constant 3000000000 would be
 *	treated as a signed long 3 billion, forcing the containing
 *	expression to be long.
 */

/* The __CONCAT__ macro may require redefinition for some non-ANSI
 * implementations.  It should concatenate its two arguments without
 * forcing separate tokens.
 */
#define __CONCAT__(A,B) A ## B

#define INT8_C(c)	((int8_t) c)
#define UINT8_C(c)	((uint8_t) __CONCAT__(c,u))
#define INT16_C(c)	((int16_t) c)
#define UINT16_C(c)	((uint16_t) __CONCAT__(c,u))
#define INT32_C(c)	((int32_t) c)
#define UINT32_C(c)	((uint32_t) __CONCAT__(c,u))
#define INT64_C(c)	((int64_t) __CONCAT__(c,ll))
#define UINT64_C(c)	((uint64_t) __CONCAT__(c,ull))
#define INTMAX_C(c)	((int64_t) __CONCAT__(c,ll))
#define UINTMAX_C(c)	((uint64_t) __CONCAT__(c,ull))

/* Constants are not defined for the pointer-sized integers, since the
 * size of the constant value will be known and should be adequate for
 * use in the very rare cases where pointer constants must be defined.
 */

/* ======================  FORMATTED I/O  ========================== */

/* Define extended versions of the printf/scanf libc routines.  These
 * extended routines accept an extended format syntax as follows, and
 * are otherwise identical to the corresponding libc routines.
 *
 * The size specifiers specified by the ANSI standard (i.e. 'h' 'l' and
 * 'L' preceding the conversion specifier) are extended to allow "wNN"
 * instead, indicating that the relevant object has width NN bits, or
 * "wmax" for an intmax_t object.  The valid values of NN are 16, 32,
 * and 64.  For example:
 *
 *	uint16_t u16;
 *	int32_t  s32;
 *	uint64_t u64;
 *	...
 *	i_printf ( "int16 is %w16u; int32 is %#8w32x\n", u16, s32 );
 *	i_scanf ( "%w16o%w64x", &u16, &u64 );
 *
 * The extensions are sequences with explicitly undefined semantics in
 * the ANSI standard, so create no conflicts.
 *
 * The implementation must provide these names as macros, matching the
 * prototypes below.  Therefore, they may be #undefined by a user, and
 * their addresses may NOT be taken.  (The expectation is that they
 * will ultimately be obsoleted by extensions to the underlying ANSI
 * routines' format processing.)
 *
 * The ANSI standard does not specify conversion characters for
 * char-sized integers.  Accordingly, no "w8" modifier is required.
 */
#include <stdarg.h>
#include <stdio.h>

extern int i_fprintf  ( FILE *stream, const char *format, ... );
extern int i_vfprintf ( FILE *stream, const char *format, va_list va );
extern int i_printf   ( const char *format, ... );
extern int i_vprintf  ( const char *format, va_list va );
extern int i_sprintf  ( char *s, const char *format, ... );
extern int i_vsprintf ( char *s, const char *format, va_list va );

extern int i_fscanf   ( FILE *stream, const char *format, ... );
extern int i_scanf    ( const char *format, ... );
extern int i_sscanf   ( char *s, const char *format, ... );

/* ======================  CONVERSIONS  ============================ */

/* The following routines are provided as analogues of the ANSI strtol
 * routines, with analogous semantics.  They must be provided as
 * functions, though the functions may be hidden by macro
 * implementations.  Users may therefore take their addresses, or pass
 * them as actual parameters, by first #undefining the names.
 */
extern	int8_t		strtoi8   (const char *, char **, int);
extern	int16_t		strtoi16  (const char *, char **, int);
extern	int32_t		strtoi32  (const char *, char **, int);
extern	int64_t		strtoi64  (const char *, char **, int);
extern	intmax_t	strtoimax (const char *, char **, int);
extern	uint8_t		strtou8   (const char *, char **, int);
extern	uint16_t	strtou16  (const char *, char **, int);
extern	uint32_t	strtou32  (const char *, char **, int);
extern	uint64_t	strtou64  (const char *, char **, int);
extern	uintmax_t	strtoumax (const char *, char **, int);

/* ======================  ARITHMETIC  ============================ */

/* The following routines are provided as analogues of the ANSI stdlib
 * routines, with analogous semantics.  They must be provided as
 * functions, though the functions may be hidden by macro
 * implementations.  Users may therefore take their addresses, or pass
 * them as actual parameters, by first #undefining the names.
 */
extern	int32_t 	abs_32	( int32_t );
extern	int64_t 	abs_64	( int64_t );
extern	intmax_t 	abs_max	( intmax_t );

typedef struct { int32_t quot;  int32_t rem;  } div32_t;
typedef struct { int64_t quot;  int64_t rem;  } div64_t;
typedef struct { intmax_t quot; intmax_t rem; } divmax_t;
extern	div32_t  div_32	 ( int32_t numer,  int32_t denom );
extern	div64_t  div_64	 ( int64_t numer,  int64_t denom );
extern	divmax_t div_max ( intmax_t numer, intmax_t denom );
#endif /* _SGIAPI */

#else

#include <stdint.h>
#include <wchar.h>

typedef struct {
  intmax_t quot;
  intmax_t rem;
} imaxdiv_t;

/* C99: 7.8.1 2 : Macros for format specifiers (fprintf signed integers) */

#define PRId8         "hhd"
#define PRId16        "hd"
#define PRId32        "d"
#define PRId64        "lld"

#define PRIi8         "hhi"
#define PRIi16        "hi"
#define PRIi32        "i"
#define PRIi64        "lli"

#define PRIdLEAST8    PRId8
#define PRIdLEAST16   PRId16
#define PRIdLEAST32   PRId32
#define PRIdLEAST64   PRId64

#define PRIiLEAST8    PRIi8
#define PRIiLEAST16   PRIi16
#define PRIiLEAST32   PRIi32
#define PRIiLEAST64   PRIi64

#define PRIdFAST8     PRId8
#define PRIdFAST16    PRId16
#define PRIdFAST32    PRId32
#define PRIdFAST64    PRId64

#define PRIiFAST8     PRIi8
#define PRIiFAST16    PRIi16
#define PRIiFAST32    PRIi32
#define PRIiFAST64    PRIi64

#define PRIdMAX       PRId64
#define PRIiMAX       PRIi64

#if (_MIPS_SZLONG == 32)
#define PRIdPTR       PRId32
#define PRIiPTR       PRIi32
#endif
#if (_MIPS_SZLONG == 64)
#define PRIdPTR       PRId64
#define PRIiPTR       PRIi64
#endif

/* C99: 7.8.1 3 : Macros for format specifiers (fprintf unsigned integers) */

#define PRIo8         "hho"
#define PRIo16        "ho"
#define PRIo32        "o"
#define PRIo64        "llo"

#define PRIu8         "hhu"
#define PRIu16        "hu"
#define PRIu32        "u"
#define PRIu64        "llu"

#define PRIx8         "hhx"
#define PRIx16        "hx"
#define PRIx32        "x"
#define PRIx64        "llx"

#define PRIX8         "hhX"
#define PRIX16        "hX"
#define PRIX32        "X"
#define PRIX64        "llX"

#define PRIoLEAST8    PRIo8
#define PRIoLEAST16   PRIo16
#define PRIoLEAST32   PRIo32
#define PRIoLEAST64   PRIo64

#define PRIuLEAST8    PRIu8
#define PRIuLEAST16   PRIu16
#define PRIuLEAST32   PRIu32
#define PRIuLEAST64   PRIu64

#define PRIxLEAST8    PRIx8
#define PRIxLEAST16   PRIx16
#define PRIxLEAST32   PRIx32
#define PRIxLEAST64   PRIx64

#define PRIXLEAST8    PRIX8
#define PRIXLEAST16   PRIX16
#define PRIXLEAST32   PRIX32
#define PRIXLEAST64   PRIX64

#define PRIoFAST8     PRIo8
#define PRIoFAST16    PRIo16
#define PRIoFAST32    PRIo32
#define PRIoFAST64    PRIo64

#define PRIuFAST8     PRIu8
#define PRIuFAST16    PRIu16
#define PRIuFAST32    PRIu32
#define PRIuFAST64    PRIu64

#define PRIxFAST8     PRIx8
#define PRIxFAST16    PRIx16
#define PRIxFAST32    PRIx32
#define PRIxFAST64    PRIx64

#define PRIXFAST8     PRIX8
#define PRIXFAST16    PRIX16
#define PRIXFAST32    PRIX32
#define PRIXFAST64    PRIX64

#define PRIoMAX       PRIo64
#define PRIuMAX       PRIu64
#define PRIxMAX       PRIx64
#define PRIXMAX       PRIX64

#if (_MIPS_SZLONG == 32)
#define PRIoPTR       PRIo32
#define PRIuPTR       PRIu32
#define PRIxPTR       PRIx32
#define PRIXPTR       PRIX32
#endif
#if (_MIPS_SZLONG == 64)
#define PRIoPTR       PRIo64
#define PRIuPTR       PRIu64
#define PRIxPTR       PRIx64
#define PRIXPTR       PRIX64
#endif

/* C99: 7.8.1 4 : Macros for format specifiers (fscanf signed integers) */

#define SCNd8         "hhd"
#define SCNd16        "hd"
#define SCNd32        "d"
#define SCNd64        "lld"

#define SCNi8         "hhi"
#define SCNi16        "hi"
#define SCNi32        "i"
#define SCNi64        "lli"

#define SCNdLEAST8    SCNd8
#define SCNdLEAST16   SCNd16
#define SCNdLEAST32   SCNd32
#define SCNdLEAST64   SCNd64

#define SCNiLEAST8    SCNi8
#define SCNiLEAST16   SCNi16
#define SCNiLEAST32   SCNi32
#define SCNiLEAST64   SCNi64

#define SCNdFAST8     SCNd8
#define SCNdFAST16    SCNd16
#define SCNdFAST32    SCNd32
#define SCNdFAST64    SCNd64

#define SCNiFAST8     SCNi8
#define SCNiFAST16    SCNi16
#define SCNiFAST32    SCNi32
#define SCNiFAST64    SCNi64

#define SCNdMAX       SCNd64
#define SCNiMAX       SCNi64

#if (_MIPS_SZLONG == 32)
#define SCNdPTR       SCNd32
#define SCNiPTR       SCNi32
#endif
#if (_MIPS_SZLONG == 64)
#define SCNdPTR       SCNd64
#define SCNiPTR       SCNi64
#endif

/* C99: 7.8.1 5 : Macros for format specifiers (fscanf unsigned integers) */

#define SCNo8         "hho"
#define SCNo16        "ho"
#define SCNo32        "o"
#define SCNo64        "llo"

#define SCNu8         "hhu"
#define SCNu16        "hu"
#define SCNu32        "u"
#define SCNu64        "llu"

#define SCNx8         "hhx"
#define SCNx16        "hx"
#define SCNx32        "x"
#define SCNx64        "llx"

#define SCNX8         "hhX"
#define SCNX16        "hX"
#define SCNX32        "X"
#define SCNX64        "llX"

#define SCNoLEAST8    SCNo8
#define SCNoLEAST16   SCNo16
#define SCNoLEAST32   SCNo32
#define SCNoLEAST64   SCNo64

#define SCNuLEAST8    SCNu8
#define SCNuLEAST16   SCNu16
#define SCNuLEAST32   SCNu32
#define SCNuLEAST64   SCNu64

#define SCNxLEAST8    SCNx8
#define SCNxLEAST16   SCNx16
#define SCNxLEAST32   SCNx32
#define SCNxLEAST64   SCNx64

#define SCNXLEAST8    SCNX8
#define SCNXLEAST16   SCNX16
#define SCNXLEAST32   SCNX32
#define SCNXLEAST64   SCNX64

#define SCNoFAST8     SCNo8
#define SCNoFAST16    SCNo16
#define SCNoFAST32    SCNo32
#define SCNoFAST64    SCNo64

#define SCNuFAST8     SCNu8
#define SCNuFAST16    SCNu16
#define SCNuFAST32    SCNu32
#define SCNuFAST64    SCNu64

#define SCNxFAST8     SCNx8
#define SCNxFAST16    SCNx16
#define SCNxFAST32    SCNx32
#define SCNxFAST64    SCNx64

#define SCNXFAST8     SCNX8
#define SCNXFAST16    SCNX16
#define SCNXFAST32    SCNX32
#define SCNXFAST64    SCNX64

#define SCNoMAX       SCNo64
#define SCNuMAX       SCNu64
#define SCNxMAX       SCNx64
#define SCNXMAX       SCNX64

#if (_MIPS_SZLONG == 32)
#define SCNoPTR       SCNo32
#define SCNuPTR       SCNu32
#define SCNxPTR       SCNx32
#define SCNXPTR       SCNX32
#endif
#if (_MIPS_SZLONG == 64)
#define SCNoPTR       SCNo64
#define SCNuPTR       SCNu64
#define SCNxPTR       SCNx64
#define SCNXPTR       SCNX64
#endif

/* C99: 7.8.2   : Functions for greatest-width integer types */

extern intmax_t  imaxabs(intmax_t j);
extern imaxdiv_t imaxdiv(intmax_t numer, intmax_t denom);
extern intmax_t  strtoimax(const char * __restrict nptr,
                           char ** __restrict endptr,
                           int base);
extern uintmax_t strtoumax(const char * __restrict nptr,
                           char ** __restrict endptr,
                           int base);
extern intmax_t  wcstoimax(const wchar_t * __restrict nptr,
                           wchar_t ** __restrict endptr,
                           int base);
extern uintmax_t wcstoumax(const wchar_t * __restrict nptr,
                           wchar_t ** __restrict endptr,
                           int base);

#pragma optional imaxabs
#pragma optional imaxdiv
#pragma optional strtoimax
#pragma optional strtoumax
#pragma optional wcstoimax
#pragma optional wcstoumax

#endif /* __c99 */

#endif /* __INTTYPES_H__ */
