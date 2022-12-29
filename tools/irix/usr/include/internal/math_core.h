#ifndef __MATH_CORE_H__
#define __MATH_CORE_H__

#include <sgidefs.h>
#include <standards.h>
#include <internal/sgimacros.h>

/* Copyright (C) 1989 Silicon Graphics, Inc. All rights reserved.  */
/* ------------------------------------------------------------------ */
/* | Copyright Unpublished, MIPS Computer Systems, Inc.  All Rights | */
/* | Reserved.  This software contains proprietary and confidential | */
/* | information of MIPS and its suppliers.  Use, disclosure or     | */
/* | reproduction is prohibited without the prior express written   | */
/* | consent of MIPS.                                               | */
/* ------------------------------------------------------------------ */

/* #ident "$Revision: 7.68 $" */

/* ANSI C Notes:
 *
 * - THE IDENTIFIERS APPEARING OUTSIDE OF #ifdef __EXTENSIONS__ IN THIS
 *   standard header ARE SPECIFIED BY ANSI!  CONFORMANCE WILL BE ALTERED
 *   IF ANY NEW IDENTIFIERS ARE ADDED TO THIS AREA UNLESS THEY ARE IN ANSI's
 *   RESERVED NAMESPACE. (i.e., unless they are prefixed by __[a-z] or
 *   _[A-Z].  For external objects, identifiers with the prefix _[a-z] 
 *   are also reserved.)
 *
 *  - Names created by appending either the suffix 'l' or 'f'
 *    to one of the reserved function names are reserved for the corresponding
 *    single- or extended- precision version of the function.
 */

/* Power C Notes:
 *
 *  - Power C assumes that all external functions (unless otherwise marked)
 *    might modify global data and therefore calls to such functions can
 *    not be safely concurrentized.
 *
 *  - The pragma "no side effects" indicates that the named function is
 *    free from such side effects and calls to it can be concurrentized.
 *
 *  - This pragma has been added below for each function in the math library
 *    which is "safe".
 *
 *  - The pragma is properly passed on by 'cpp' & 'c++' and ignored by
 *    'ccom'.  It only has meaning to 'pca'.
 */
/*
 * XPG4/POSIX Notes:
 *	This header is also specified by POSIX/XOPEN..
 *	Although the standards say nothing - we assume that the ANSI
 *	'guideline' that all std ANSI names with an 'l' or 'f' are reserved.
 */

/*
 * ANSI definitions
 */

__SGI_LIBC_BEGIN_EXTERN_C

__SGI_LIBC_BEGIN_NAMESPACE_STD

/* size_t is not part of math.h but is left here for backewards compatibility */

#if !defined(_SIZE_T) && !defined(_SIZE_T_)
#define _SIZE_T
#if (_MIPS_SZLONG == 32)
typedef unsigned int    size_t;
#endif
#if (_MIPS_SZLONG == 64)
typedef unsigned long   size_t;
#endif
#endif

__SGI_LIBC_END_NAMESPACE_STD

/* float_t and double_t, described by 7.12, paragraph 2, of the C99
 * standard.  The definitions here correspond to FP_EVAL_METHOD equal
 * to 0.  These typedefs are not supposed to be defined for C90 or
 * C++, but we have defined them in the past and we'll retain them for
 * backward compatibility.  
 */

typedef float  float_t;
typedef double double_t;

/* HUGE_VAL */

#ifndef HUGE_VAL	/* Also in limits.h */
#if _SGIAPI || _ABIAPI
#ifndef __TYPEDEF_H_VAL
#define __TYPEDEF_H_VAL
typedef union _h_val {
#if (_MIPS_SZLONG == 32)
        unsigned long i[2];
#endif
#if (_MIPS_SZLONG == 64)
        __uint32_t i[2];
#endif
        double d;
} _h_val;
#endif /* __TYPEDEF_H_VAL */

extern const _h_val __huge_val;
#define HUGE_VAL __huge_val.d
#else /* _SGIAPI || _ABIAPI */

/* __infinity is a double-precision variable in libc set to infinity */

extern const double __infinity;
#define HUGE_VAL __infinity	
#endif /* _SGIAPI || _ABIAPI */
#endif /* !HUGE_VAL */

#ifdef __c99

extern const float       __infinityf;
extern const long double __infinityl;

#define HUGE_VALF __infinityf
#define HUGE_VALL __infinityl
#define INFINITY  __infinityf

/* C99: 7.12 5 float value representing a quiet NAN */

extern const float _nanf_val;
#define NAN        _nanf_val

/* C99: 7.12 6 defines for floating point classification */

#define   FP_ZERO          1
#define   FP_SUBNORMAL     2
#define   FP_NORMAL        4
#define   FP_INFINITE      8
#define   FP_NAN           16

/* C99: 7.12 7 defines for floating point multiply add */

#if 0
#define   FP_FAST_FMA
#define   FP_FAST_FMAF
#define   FP_FAST_FMAL
#endif

/* C99: 7.12 7 defines for ilogb */

/* INT_MIN is defined in limits.h, but including it causes
 * problems for UNIX98 
 */
#ifndef INT_MIN
#define INT_MIN         (-2147483647-1) /* min value of an "int" */
#endif /* INT_MIN */

#define   FP_ILOGB0        INT_MIN
#define   FP_ILOGBNAN      INT_MIN

/* C99: 7.12 8 defines for math error handling */
/* How math errors are reported.  MATH_ERRNO means they're reported
 * through errno, MATH_ERREXCEPT means they're reported through
 * exceptions.  math_errhandling must be equal to MATH_ERRNO,
 * MATH_ERREXCEPT, or MATH_ERRNO|MATH_ERREXCEPT. */

#define   MATH_ERRNO       1
#define   MATH_ERREXCEPT   2
#define   math_errhandling MATH_ERRNO

/* C99: 7.12.3 floating-point classification functions. */

/* The following 18 entry points are defined in c99's libc. __generic is a builtin
 * defined in the c99 front end. */

extern int _fpclassify(double);
extern int _fpclassifyf(float);
extern int _fpclassifyl(long double);
extern int _isfinite(double);
extern int _isfinitef(float);
extern int _isfinitel(long double);
extern int _isinf(double);
extern int _isinff(float);
extern int _isinfl(long double);
extern int _isnan(double);
extern int _isnanf(float);
extern int _isnanl(long double);
extern int _isnormal(double);
extern int _isnormalf(float);
extern int _isnormall(long double);
extern int _signbit(double);
extern int _signbitf(float);
extern int _signbitl(long double);

#define fpclassify(x) __generic(x,,, _fpclassify, _fpclassifyf, _fpclassifyl,,,)(x)
#define isfinite(x)   __generic(x,,, _isfinite,   _isfinitef,   _isfinitel,,,)(x)
#define isinf(x)      __generic(x,,, _isinf,      _isinff,      _isinfl,,,)(x)
#define isnan(x)      __generic(x,,, _isnan,      _isnanf,      _isnanl,,,)(x)
#define isnormal(x)   __generic(x,,, _isnormal,   _isnormalf,   _isnormall,,,)(x)
#define signbit(x)    __generic(x,,, _signbit,    _signbitf,    _signbitl,,,)(x)

#pragma optional _fpclassify
#pragma optional _fpclassifyf
#pragma optional _fpclassifyl
#pragma optional _isfinite
#pragma optional _isfinitef
#pragma optional _isfinitel
#pragma optional _isinf
#pragma optional _isinff
#pragma optional _isinfl
#pragma optional _isnan
#pragma optional _isnanf
#pragma optional _isnanl
#pragma optional _isnormal
#pragma optional _isnormalf
#pragma optional _isnormall
#pragma optional _signbit
#pragma optional _signbitf
#pragma optional _signbitl

#endif /* __c99 */

__SGI_LIBC_BEGIN_NAMESPACE_STD

/* 
 *  C90 ANSI-standard functions.  Each is listed with 
 *  its single-precision counterpart, if it exists.
 *  Note that the C90 standard allows (but does not require)
 *  the float and long double versions.  The C99 standard
 *  requires both.
 */

#if (_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64)
#define __SGI_LIBC_LONG_DOUBLE_OVERLOADS 1
#endif /* N32 or 64 */

/* Trignometric functions */
/* C99: 7.12.4 */
/* C89: 4.5.2 */

extern double	   acos(double);
extern float	   acosf(float);
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
extern long double acosl( long double );
#endif /* c99 or N32 or 64 */

extern double	   asin(double);
extern float	   asinf(float);
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
extern long double asinl( long double );
#endif /* c99 or N32 or 64 */

extern double	   atan(double);
extern float	   atanf(float);
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
extern long double atanl( long double );
#endif /* c99 or N32 or 64 */

extern double	   atan2(double, double);
extern float	   atan2f(float, float);
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
extern long double atan2l( long double, long double );
#endif /* c99 or N32 or 64 */

extern double	   cos(double);
extern float	   cosf(float);
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
extern long double cosl( long double );
#endif /* c99 or N32 or 64 */

extern double	   sin(double);
extern float	   sinf(float);
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
extern long double sinl( long double );
#endif /* c99 or N32 or 64 */

extern double	   tan(double);
extern float	   tanf(float);
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
extern long double tanl( long double );
#endif /* c99 or N32 or 64 */

#ifdef __MATH_HAS_NO_SIDE_EFFECTS

#pragma no side effects (acos)
#pragma no side effects (acosf)
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
#pragma no side effects (acosl)
#endif /* c99 or N32 or 64 */

#pragma no side effects (asin)
#pragma no side effects (asinf)
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
#pragma no side effects (asinl)
#endif /* c99 or N32 or 64 */

#pragma no side effects (atan)
#pragma no side effects (atanf)
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
#pragma no side effects (atanl)
#endif /* c99 or N32 or 64 */

#pragma no side effects (atan2)
#pragma no side effects (atan2f)
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
#pragma no side effects (atan2l)
#endif /* c99 or N32 or 64 */

#pragma no side effects (cos)
#pragma no side effects (cosf)
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
#pragma no side effects (cosl)
#endif /* c99 or N32 or 64 */

#pragma no side effects (sin)
#pragma no side effects (sinf)
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
#pragma no side effects (sinl)
#endif /* c99 or N32 or 64 */

#pragma no side effects (tan)
#pragma no side effects (tanf)
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
#pragma no side effects (tanl)
#endif /* c99 or N32 or 64 */

#endif /* __MATH_HAS_NO_SIDE_EFFECTS */

#if _NO_XOPEN4 && _NO_XOPEN5 && (defined(__INLINE_INTRINSICS) && \
        defined(_COMPILER_VERSION) && (_COMPILER_VERSION >= 710))

#pragma intrinsic (acos)
#pragma intrinsic (acosf)
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
#pragma intrinsic (acosl)
#endif /* c99 or N32 or 64 */

#pragma intrinsic (asin)
#pragma intrinsic (asinf)
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
#pragma intrinsic (asinl)
#endif /* c99 or N32 or 64 */

#pragma intrinsic (atan)
#pragma intrinsic (atanf)
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
#pragma intrinsic (atanl)
#endif /* c99 or N32 or 64 */

#pragma intrinsic (cos)
#pragma intrinsic (cosf)
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
#pragma intrinsic (cosl)
#endif /* c99 or N32 or 64 */

#pragma intrinsic (sin)
#pragma intrinsic (sinf)
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
#pragma intrinsic (sinl)
#endif /* c99 or N32 or 64 */

#pragma intrinsic (tan)
#pragma intrinsic (tanf)
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
#pragma intrinsic (tanl)
#endif /* c99 or N32 or 64 */

#endif /* _NO_XOPEN4 && _NO_XOPEN5 && (defined(__INLINE_INTRINSICS) .. */

/* Hyperbolic functions */
/* C99: 7.12.5 */
/* C89: 4.5.3 */

__SGI_LIBC_END_NAMESPACE_STD

#if defined(__c99) || ((_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE)
extern double      acosh(double);
#endif /* defined(__c99) || ((_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE) */
#if defined(__c99)
extern float       acoshf(float);
extern long double acoshl(long double);

#pragma optional   acoshf
#pragma optional   acoshl
#endif /* __c99 */

#if defined(__c99) || ((_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE)
extern double      asinh(double);
#endif /* defined(__c99) || ((_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE) */
#if defined(__c99)
extern float       asinhf(float);
extern long double asinhl(long double);

#pragma optional   asinhf
#pragma optional   asinhl
#endif /* __c99 */

#if defined(__c99) || ((_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE)
extern double      atanh(double);
#endif /* defined(__c99) || ((_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE) */
#if defined(__c99)
extern float       atanhf(float);
extern long double atanhl(long double);

#pragma optional   atanhf
#pragma optional   atanhl
#endif /* __c99 */

__SGI_LIBC_BEGIN_NAMESPACE_STD

extern double	   cosh(double);
extern float	   coshf(float);
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
extern long double coshl( long double );
#endif /* c99 or N32 or 64 */

extern double	   sinh(double);
extern float	   sinhf(float);
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
extern long double sinhl( long double );
#endif /* c99 or N32 or 64 */

extern double	   tanh(double);
extern float	   tanhf(float);
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
extern long double tanhl( long double );
#endif /* c99 or N32 or 64 */

#ifdef __MATH_HAS_NO_SIDE_EFFECTS

__SGI_LIBC_END_NAMESPACE_STD

#if defined(__c99) || ((_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE)
#pragma no side effects (acosh)
#pragma no side effects (asinh)
#pragma no side effects (atanh)
#endif /* defined(__c99) || ((_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE) */

__SGI_LIBC_BEGIN_NAMESPACE_STD

#pragma no side effects (cosh)
#pragma no side effects (coshf)
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
#pragma no side effects (coshl)
#endif /* c99 or N32 or 64 */

#pragma no side effects (sinh)
#pragma no side effects (sinhf)
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
#pragma no side effects (sinhl)
#endif /* c99 or N32 or 64 */

#pragma no side effects (tanh)
#pragma no side effects (tanhf)
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
#pragma no side effects (tanhl)
#endif /* c99 or N32 or 64 */

#endif /* __MATH_HAS_NO_SIDE_EFFECTS */

/* Exponential and logarithmic functions */
/* C99: 7.12.6 */
/* C89: 4.5.4 */

extern double	   exp(double);
extern float	   expf(float);
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
extern long double expl( long double );
#endif /* c99 or N32 or 64 */

__SGI_LIBC_END_NAMESPACE_STD

#if defined(__c99)
extern double      exp2(double);
extern float       exp2f(float);
extern long double exp2l(long double);

#pragma optional   exp2
#pragma optional   exp2f
#pragma optional   exp2l
#endif /* __c99 */

#if defined(__c99) || ((_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE)
extern double      expm1(double);
#endif /* defined(__c99) || ((_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE) */
#if defined(__c99) || _SGIAPI
extern float       expm1f(float);
#endif /* __c99 */
#if defined(__c99)
extern long double expm1l(long double);
#pragma optional   expm1l
#endif /* __c99 */

__SGI_LIBC_BEGIN_NAMESPACE_STD

extern double	   frexp(double, int *);
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
extern float	   frexpf(float, int *);
#pragma optional   frexpf
#endif /* __c99 */
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
extern long double frexpl( long double, int *);
#endif /* c99 or N32 or 64 */

__SGI_LIBC_END_NAMESPACE_STD

#if defined(__c99) || ((_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE)
extern int         ilogb(double);
#endif /* defined(__c99) || ((_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE) */
#if defined(__c99)
extern int         ilogbf(float);
extern int         ilogbl(long double);

#pragma optional   ilogbf
#pragma optional   ilogbl
#endif /* __c99 */

__SGI_LIBC_BEGIN_NAMESPACE_STD

extern double	   ldexp(double, int);
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
extern float	   ldexpf(float, int);
#pragma optional   ldexpf
#endif /* __c99 */
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
extern long double ldexpl( long double, int );
#endif /* c99 or N32 or 64 */

extern double	   log(double);
extern float	   logf(float);
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
extern long double logl( long double );
#endif /* c99 or N32 or 64 */

extern double	   log10(double);
extern float	   log10f(float);
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
extern long double log10l( long double );
#endif /* c99 or N32 or 64 */

__SGI_LIBC_END_NAMESPACE_STD

#if defined(__c99) || ((_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE)
extern double      log1p(double);
#endif /* defined(__c99) || ((_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE) */
#if defined(__c99) || _SGIAPI
extern float       log1pf(float);
#endif /* __c99 */
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
extern long double log1pl(long double);
#endif /* __c99 */

#if defined(__c99)
extern double      log2(double);
extern float       log2f(float);
extern long double log2l(long double);

#pragma optional   log2
#pragma optional   log2f
#pragma optional   log2l
#endif /* __c99 */

#if defined(__c99) || ((_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE)
extern double      logb(double);
#endif /* defined(__c99) || ((_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE) */
#if defined(__c99)
extern float       logbf(float);
#pragma optional   logbf
#endif /* __c99 */
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
extern long double logbl(long double);
#endif /* __c99 */

__SGI_LIBC_BEGIN_NAMESPACE_STD

extern double	   modf(double, double *);
extern float	   modff(float, float *); 
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
extern long double modfl( long double, long double *);
#endif /* c99 or N32 or 64 */

__SGI_LIBC_END_NAMESPACE_STD

#if defined(__c99)

extern double      scalbn(double, int);
extern float       scalbnf(float, int);
extern long double scalbnl(long double, int);

extern double      scalbln(double, long int);
extern float       scalblnf(float, long int);
extern long double scalblnl(long double, long int);

#pragma optional   scalbn
#pragma optional   scalbnf
#pragma optional   scalbnl
#pragma optional   scalbln
#pragma optional   scalblnf
#pragma optional   scalblnl

#endif /* __c99 */

__SGI_LIBC_BEGIN_NAMESPACE_STD

#ifdef __MATH_HAS_NO_SIDE_EFFECTS

#pragma no side effects (exp)
#pragma no side effects (expf)
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
#pragma no side effects (expl)
#endif /* c99 or N32 or 64 */

__SGI_LIBC_END_NAMESPACE_STD

#if defined(__c99) || ((_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE)
#pragma no side effects (expm1)
#endif /* defined(__c99) || ((_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE) */
#if defined(__c99) || _SGIAPI
#pragma no side effects (expm1f)
#endif /* __c99 */

#if defined(__c99) || ((_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE)
#pragma no side effects (ilogb)
#endif /* defined(__c99) || ((_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE) */

__SGI_LIBC_BEGIN_NAMESPACE_STD

#pragma no side effects (log)
#pragma no side effects (logf)
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
#pragma no side effects (logl)
#endif /* c99 or N32 or 64 */

#pragma no side effects (log10)
#pragma no side effects (log10f)
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
#pragma no side effects (log10l)
#endif /* c99 or N32 or 64 */

__SGI_LIBC_END_NAMESPACE_STD

#if defined(__c99) || ((_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE)
#pragma no side effects (log1p)
#endif /* defined(__c99) || ((_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE) */
#if defined(__c99) || _SGIAPI
#pragma no side effects (log1pf)
#endif /* __c99 */

#if defined(__c99) || ((_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE)
#pragma no side effects (logb)
#endif /* defined(__c99) || ((_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE) */
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
#pragma no side effects (logbl)
#endif /* __c99 */

__SGI_LIBC_BEGIN_NAMESPACE_STD

#endif /* __MATH_HAS_NO_SIDE_EFFECTS */

#if _NO_XOPEN4 && _NO_XOPEN5 && (defined(__INLINE_INTRINSICS) && \
        defined(_COMPILER_VERSION) && (_COMPILER_VERSION >= 710))

#pragma intrinsic (exp)
#pragma intrinsic (expf)
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
#pragma intrinsic (expl)
#endif /* c99 or N32 or 64 */

#pragma intrinsic (log)
#pragma intrinsic (logf)
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
#pragma intrinsic (logl)
#endif /* c99 or N32 or 64 */

#pragma intrinsic (log10)
#pragma intrinsic (log10f)
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
#pragma intrinsic (log10l)
#endif /* c99 or N32 or 64 */

#endif /* _NO_XOPEN4 && _NO_XOPEN5 && (defined(__INLINE_INTRINSICS) ... */

/* Power and absolute-value functions */
/* C99: 7.12.7 */
/* C89: 4.5.5 */

__SGI_LIBC_END_NAMESPACE_STD

#if defined(__c99) || ((_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE)
extern double      cbrt(double);
#endif /* defined(__c99) || ((_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE) */
#if defined(__c99)
extern float       cbrtf(float);
extern long double cbrtl(long double);

#pragma optional   cbrtf
#pragma optional   cbrtl
#endif /* __c99 */

__SGI_LIBC_BEGIN_NAMESPACE_STD

extern double	   fabs(double);
extern float	   fabsf(float);
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
extern long double fabsl( long double );
#endif /* c99 or N32 or 64 */

__SGI_LIBC_END_NAMESPACE_STD

#if defined(__c99) || ((_XOPEN4 || _XOPEN5) && _NO_ANSIMODE)
extern double      hypot(double, double);
#endif /* defined(__c99) || ((_XOPEN4 || _XOPEN5) && _NO_ANSIMODE) */
#if defined(__c99) || _SGIAPI
extern float       hypotf(float, float);
#endif /* __c99 */
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
extern long double hypotl(long double, long double);
#endif /* __c99 */

__SGI_LIBC_BEGIN_NAMESPACE_STD

extern double	   pow(double, double);
extern float	   powf(float, float);
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
extern long double powl( long double, long double );
#endif /* c99 or N32 or 64 */

extern double	   sqrt(double);
extern float	   sqrtf(float);
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
extern long double sqrtl( long double );
#endif /* c99 or N32 or 64 */

#ifdef __MATH_HAS_NO_SIDE_EFFECTS

__SGI_LIBC_END_NAMESPACE_STD

#if defined(__c99) || ((_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE)
#pragma no side effects (cbrt)
#endif /* defined(__c99) || ((_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE) */

__SGI_LIBC_BEGIN_NAMESPACE_STD

#pragma no side effects (fabs)
#pragma no side effects (fabsf)
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
#pragma no side effects (fabsl)
#endif /* c99 or N32 or 64 */

__SGI_LIBC_END_NAMESPACE_STD

#if defined(__c99) || ((_XOPEN4 || _XOPEN5) && _NO_ANSIMODE)
#pragma no side effects (hypot)
#endif /* defined(__c99) || ((_XOPEN4 || _XOPEN5) && _NO_ANSIMODE) */
#if defined(__c99) || _SGIAPI
#pragma no side effects (hypotf)
#endif /* __c99 */
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
#pragma no side effects (hypotl)
#endif /* __c99 */

__SGI_LIBC_BEGIN_NAMESPACE_STD

#pragma no side effects (pow)
#pragma no side effects (powf)
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
#pragma no side effects (powl)
#endif /* c99 or N32 or 64 */

#pragma no side effects (sqrt)
#pragma no side effects (sqrtf)
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
#pragma no side effects (sqrtl)
#endif /* c99 or N32 or 64 */

#endif /* __MATH_HAS_NO_SIDE_EFFECTS */

/* Error and gamma functions */
/* C99: 7.12.8 */

__SGI_LIBC_END_NAMESPACE_STD

#if defined(__c99) || ((_XOPEN4 || _XOPEN5) && _NO_ANSIMODE)
extern double      erf(double);
#endif /* defined(__c99) || ((_XOPEN4 || _XOPEN5) && _NO_ANSIMODE) */
#if defined(__c99)
extern float       erff(float);
#pragma optional   erff
#endif /* __c99 */
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
extern long double erfl(long double);
#endif /* __c99 */

#if defined(__c99) || ((_XOPEN4 || _XOPEN5) && _NO_ANSIMODE)
extern double      erfc(double);
#endif /* defined(__c99) || ((_XOPEN4 || _XOPEN5) && _NO_ANSIMODE) */
#if defined(__c99)
extern float       erfcf(float);
#pragma optional   erfcf
#endif /* __c99 */
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
extern long double erfcl(long double);
#endif /* __c99 */

#if defined(__c99) || ((_XOPEN4 || _XOPEN5) && _NO_ANSIMODE)
extern double      lgamma(double);
#endif /* defined(__c99) || ((_XOPEN4 || _XOPEN5) && _NO_ANSIMODE) */
#if defined(__c99)
extern float       lgammaf(float);
#pragma optional   lgammaf
#endif /* __c99 */
#if defined(__c99) || (((_XOPEN4 || _XOPEN5) && _NO_ANSIMODE) && ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI))
extern long double lgammal(long double);
#endif /* __c99 */

#if defined(__c99)
extern double      tgamma(double);
extern float       tgammaf(float);
extern long double tgammal(long double);

#pragma optional   tgamma
#pragma optional   tgammaf
#pragma optional   tgammal
#endif /* __c99 */

#ifdef __MATH_HAS_NO_SIDE_EFFECTS

#if defined(__c99) || ((_XOPEN4 || _XOPEN5) && _NO_ANSIMODE)
#pragma no side effects (erf)
#endif /* defined(__c99) || ((_XOPEN4 || _XOPEN5) && _NO_ANSIMODE) */
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
#pragma no side effects (erfl)
#endif /* __c99 */

#if defined(__c99) || ((_XOPEN4 || _XOPEN5) && _NO_ANSIMODE)
#pragma no side effects (erfc)
#endif /* __c99 */
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
#pragma no side effects (erfcl)
#endif /* __c99 */

#endif /* __MATH_HAS_NO_SIDE_EFFECTS */

__SGI_LIBC_BEGIN_NAMESPACE_STD

/* Nearest integer functions */
/* C99: 7.12.9 */
/* C89: 4.5.6 */

extern double	   ceil(double);
extern float	   ceilf(float);
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
extern long double ceill( long double );
#endif /* c99 or N32 or 64 */

extern double	   floor(double);
extern float	   floorf(float);
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
extern long double floorl( long double );
#endif /* c99 or N32 or 64 */

__SGI_LIBC_END_NAMESPACE_STD

#if defined(__c99)
extern double      nearbyint(double);
extern float       nearbyintf(float);
extern long double nearbyintl(long double);

#pragma optional   nearbyint
#pragma optional   nearbyintf
#pragma optional   nearbyintl
#endif /* __c99 */

#if defined(__c99) || ((_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE)
extern double      rint(double);
#endif /* defined(__c99) || ((_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE) */
#if defined(__c99)
extern float       rintf(float);
#pragma optional   rintf
#endif /* __c99 */
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
extern long double rintl(long double);
#endif /* __c99 */

#if defined(__c99)
extern long int    lrint(double);
extern long int    lrintf(float);
extern long int    lrintl(long double);

#pragma optional   lrint
#pragma optional   lrintf
#pragma optional   lrintl
#endif /* __c99 */

#if defined(__c99)
extern long long int llrint(double);
extern long long int llrintf(float);
extern long long int llrintl(long double);

#pragma optional     llrint
#pragma optional     llrintf
#pragma optional     llrintl
#endif /* __c99 */

#if defined(__c99)
extern double      round(double);
extern float       roundf(float);
extern long double roundl(long double);

#pragma optional   round
#pragma optional   roundf
#pragma optional   roundl
#endif /* __c99 */

#if defined(__c99)
extern long int    lround(double);
extern long int    lroundf(float);
extern long int    lroundl(long double);

#pragma optional   lround
#pragma optional   lroundf
#pragma optional   lroundl
#endif /* __c99 */

#if defined(__c99)
extern long long int llround(double);
extern long long int llroundf(float);
extern long long int llroundl(long double);

#pragma optional     llround
#pragma optional     llroundf
#pragma optional     llroundl
#endif /* __c99 */

#if defined(__c99) || _SGIAPI
extern double      trunc(double);
extern float       truncf(float);
#endif /* __c99 */
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
extern long double truncl(long double);
#endif /* __c99 */

__SGI_LIBC_BEGIN_NAMESPACE_STD

#ifdef __MATH_HAS_NO_SIDE_EFFECTS

#pragma no side effects (ceil)
#pragma no side effects (ceilf)
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
#pragma no side effects (ceill)
#endif /* c99 or N32 or 64 */

#pragma no side effects (floor)
#pragma no side effects (floorf)
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
#pragma no side effects (floorl)
#endif /* c99 or N32 or 64 */

__SGI_LIBC_END_NAMESPACE_STD

#if defined(__c99) || ((_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE)
#pragma no side effects (rint)
#endif /* defined(__c99) || ((_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE) */
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
#pragma no side effects (rintl)
#endif /* __c99 */

#if defined(__c99) || _SGIAPI
#pragma no side effects (trunc)
#pragma no side effects (truncf)
#endif /* __c99 */
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
#pragma no side effects (truncl)
#endif /* __c99 */

__SGI_LIBC_BEGIN_NAMESPACE_STD

#endif /* __MATH_HAS_NO_SIDE_EFFECTS */

/* Remainder functions */
/* C99: 7.12.10 */

extern double	   fmod(double, double);
extern float	   fmodf(float, float);
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
extern long double fmodl( long double, long double );
#endif /* c99 or N32 or 64 */

__SGI_LIBC_END_NAMESPACE_STD

#if defined(__c99) || ((_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE)
extern double        remainder(double, double);
#endif /* defined(__c99) || ((_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE) */
#if defined(__c99)
extern float         remainderf(float, float);
extern long double   remainderl(long double, long double);

#pragma optional     remainderf
#pragma optional     remainderl
#endif /* __c99 */

#if defined(__c99)
extern double        remquo(double, double, int *);
extern float         remquof(float, float, int *);
extern long double   remquol(long double, long double, int *);

#pragma optional     remquo
#pragma optional     remquof
#pragma optional     remquol
#endif /* __c99 */

__SGI_LIBC_BEGIN_NAMESPACE_STD

#ifdef __MATH_HAS_NO_SIDE_EFFECTS

#pragma no side effects (fmod)
#pragma no side effects (fmodf)
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
#pragma no side effects (fmodl)
#endif /* c99 or N32 or 64 */

__SGI_LIBC_END_NAMESPACE_STD

#if defined(__c99) || ((_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE)
#pragma no side effects (remainder)
#endif /* defined(__c99) || ((_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE) */

__SGI_LIBC_BEGIN_NAMESPACE_STD

#endif /* __MATH_HAS_NO_SIDE_EFFECTS */

/* Manipulation functions */
/* C99: 7.12.11 */

__SGI_LIBC_END_NAMESPACE_STD

#if defined(__c99) || _SGIAPI
extern double        copysign(double, double);
#endif /* defined(__c99) || _SGIAPI */
#if defined(__c99)
extern float         copysignf(float, float);
#pragma optional     copysignf
#endif /* __c99 */
#if defined(__c99) || _SGIAPI
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
extern long double   copysignl(long double, long double);
#endif /* c99 or N32 or 64 */
#endif /* defined(__c99) || _SGIAPI */

#if defined(__c99)
extern double        nan(const char *);
extern float         nanf(const char *);
extern long double   nanl(const char *);

#pragma optional     nan
#pragma optional     nanf
#pragma optional     nanl
#endif /* __c99 */

#if defined(__c99) || ((_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE)
extern double        nextafter(double, double);
#endif /* defined(__c99) || ((_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE) */
#if defined(__c99)
extern float         nextafterf(float, float);
#pragma optional     nextafterf
#endif /* __c99 */
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
extern long double   nextafterl(long double, long double);
#endif /* __c99 */

#if defined(__c99)
extern double        nexttoward(double, long double);
extern float         nexttowardf(float, long double);
extern long double   nexttowardl(long double, long double);

#pragma optional     nexttoward
#pragma optional     nexttowardf
#pragma optional     nexttowardl
#endif /* __c99 */

#ifdef __MATH_HAS_NO_SIDE_EFFECTS

#if defined(__c99) || _SGIAPI
#pragma no side effects (copysign)
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
#pragma no side effects (copysignl)
#endif /* c99 or N32 or 64 */
#endif /* defined(__c99) || _SGIAPI */

#if defined(__c99) || ((_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE)
#pragma no side effects (nextafter)
#endif /* defined(__c99) || ((_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE) */
#if defined(__c99) || ((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI)
#pragma no side effects (nextafterl)
#endif /* __c99 */

#endif /* __MATH_HAS_NO_SIDE_EFFECTS */

__SGI_LIBC_BEGIN_NAMESPACE_STD

/* Maximum, minimum, and positive difference functions */
/* C99: 7.12.12 */

__SGI_LIBC_END_NAMESPACE_STD

#if defined(__c99)
extern double        fdim(double, double);
extern float         fdimf(float, float);
extern long double   fdiml(long double, long double);

#pragma optional     fdim
#pragma optional     fdimf
#pragma optional     fdiml
#endif /* __c99 */

#if defined(__c99)
extern double        fmax(double, double);
extern float         fmaxf(float, float);
extern long double   fmaxl(long double, long double);

#pragma optional     fmax
#pragma optional     fmaxf
#pragma optional     fmaxl
#endif /* __c99 */

#if defined(__c99)
extern double        fmin(double, double);
extern float         fminf(float, float);
extern long double   fminl(long double, long double);

#pragma optional     fmin
#pragma optional     fminf
#pragma optional     fminl
#endif /* __c99 */

#ifdef __MATH_HAS_NO_SIDE_EFFECTS

#endif /* __MATH_HAS_NO_SIDE_EFFECTS */

__SGI_LIBC_BEGIN_NAMESPACE_STD

/* Floating multiply-add */
/* C99: 7.12.13 */

__SGI_LIBC_END_NAMESPACE_STD

#if defined(__c99)
extern double        fma(double, double, double);
extern float         fmaf(float, float, float);
extern long double   fmal(long double, long double, long double);

#pragma optional     fma
#pragma optional     fmaf
#pragma optional     fmal
#endif /* __c99 */

__SGI_LIBC_BEGIN_NAMESPACE_STD

/* Comparison Macros */
/* C99: 7.12.14 */

__SGI_LIBC_END_NAMESPACE_STD

#if defined(__c99)

extern int _isgreater(double, double);
extern int _isgreaterf(float, float);
extern int _isgreaterl(long double, long double);
extern int _isgreaterequal(double, double);
extern int _isgreaterequalf(float, float);
extern int _isgreaterequall(long double, long double);
extern int _isless(double, double);
extern int _islessf(float, float);
extern int _islessl(long double, long double);
extern int _islessequal(double, double);
extern int _islessequalf(float, float);
extern int _islessequall(long double, long double);
extern int _islessgreater(double, double);
extern int _islessgreaterf(float, float);
extern int _islessgreaterl(long double, long double);
extern int _isunordered(double, double);
extern int _isunorderedf(float, float);
extern int _isunorderedl(long double, long double);

#define isgreater(x,y)      __generic(x,y,, _isgreater, _isgreaterf, _isgreaterl,,,)(x,y)
#define isgreaterequal(x,y) __generic(x,y,, _isgreaterequal, _isgreaterequalf, _isgreaterequall,,,)(x,y)
#define isless(x,y)         __generic(x,y,, _isless, _islessf, _islessl,,,)(x,y)
#define islessequal(x,y)    __generic(x,y,, _islessequal, _islessequalf, _islessequall,,,)(x,y)
#define islessgreater(x,y)  __generic(x,y,, _islessgreater, _islessgreaterf, _islessgreaterl,,,)(x,y)
#define isunordered(x,y)    __generic(x,y,, _isunordered, _isunorderedf, _isunorderedl,,,)(x,y)

#pragma optional _isgreater
#pragma optional _isgreaterf
#pragma optional _isgreaterl
#pragma optional _isgreaterequal
#pragma optional _isgreaterequalf
#pragma optional _isgreaterequall
#pragma optional _isless
#pragma optional _islessf
#pragma optional _islessl
#pragma optional _islessequal
#pragma optional _islessequalf
#pragma optional _islessequall
#pragma optional _islessgreater
#pragma optional _islessgreaterf
#pragma optional _islessgreaterl
#pragma optional _isunordered
#pragma optional _isunorderedf
#pragma optional _isunorderedl

#endif /* __c99 */

__SGI_LIBC_BEGIN_NAMESPACE_STD

__SGI_LIBC_END_NAMESPACE_STD

#if (_XOPEN4 || _XOPEN5)  && _NO_ANSIMODE
/*
 * XPG4 extensions
 */
/* Some useful constants */
#define M_E		2.7182818284590452354
#define M_LOG2E		1.4426950408889634074
#define M_LOG10E	0.43429448190325182765
#define M_LN2		0.69314718055994530942
#define M_LN10		2.30258509299404568402
#define M_PI		3.14159265358979323846
#define M_PI_2		1.57079632679489661923
#define M_PI_4		0.78539816339744830962
#define M_1_PI		0.31830988618379067154
#define M_2_PI		0.63661977236758134308
#define M_2_SQRTPI	1.12837916709551257390
#define M_SQRT2		1.41421356237309504880
#define M_SQRT1_2	0.70710678118654752440

extern int signgam;

extern double	gamma(double);

#if !defined(__c99)
extern int	isnan(double);
#ifdef __MATH_HAS_NO_SIDE_EFFECTS
#pragma no side effects (isnan)
#endif /* __MATH_HAS_NO_SIDE_EFFECTS */
#endif /* !c99 */

#if _ABIAPI
extern int	isnand(double);
#ifdef __MATH_HAS_NO_SIDE_EFFECTS
#pragma no side effects (isnand)
#endif /* __MATH_HAS_NO_SIDE_EFFECTS */
#endif /* _ABIAPI */

extern double	j0(double);
#ifdef __MATH_HAS_NO_SIDE_EFFECTS
#pragma no side effects (j0)
#endif /* __MATH_HAS_NO_SIDE_EFFECTS */

extern double	j1(double);
#ifdef __MATH_HAS_NO_SIDE_EFFECTS
#pragma no side effects (j1)
#endif /* __MATH_HAS_NO_SIDE_EFFECTS */

extern double	jn(int, double);
#ifdef __MATH_HAS_NO_SIDE_EFFECTS
#pragma no side effects (jn)
#endif /* __MATH_HAS_NO_SIDE_EFFECTS */

extern double	y0(double);
#ifdef __MATH_HAS_NO_SIDE_EFFECTS
#pragma no side effects (y0)
#endif /* __MATH_HAS_NO_SIDE_EFFECTS */

extern double	y1(double);
#ifdef __MATH_HAS_NO_SIDE_EFFECTS
#pragma no side effects (y1)
#endif /* __MATH_HAS_NO_SIDE_EFFECTS */

extern double	yn(int, double);
#ifdef __MATH_HAS_NO_SIDE_EFFECTS
#pragma no side effects (yn)
#endif /* __MATH_HAS_NO_SIDE_EFFECTS */


#ifndef _MAXFLOAT
#define _MAXFLOAT
#define MAXFLOAT	((float)3.40282346638528860e+38)
#endif  /* _MAXFLOAT */

#endif /* (_XOPEN4 || _XOPEN5) && _NO_ANSIMODE */

#if (_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE
/*
 * XPG4 Unix Extensions
 */

extern double	scalb(double, double);
#ifdef __MATH_HAS_NO_SIDE_EFFECTS
#pragma no side effects (scalb)
#endif /* __MATH_HAS_NO_SIDE_EFFECTS */

#endif /* (_XOPEN4UX || _XOPEN5) && _NO_ANSIMODE */

#if (_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI

/* long double precision routines. */

#if !defined(__c99)
struct __cabsl_s { long double a,b; };

extern long double cabsl( struct __cabsl_s );
#endif

extern int  finitel( long double );
extern long double j0l( long double );
extern long double j1l( long double );
extern long double jnl( int, long double );
extern long double y0l( long double );
extern long double y1l( long double );
extern long double ynl( int, long double );

#ifdef __MATH_HAS_NO_SIDE_EFFECTS

#if !defined(__c99)
#pragma no side effects (cabsl)
#endif
#pragma no side effects (finitel)
#pragma no side effects (j0l)
#pragma no side effects (j1l)
#pragma no side effects (jnl)
#pragma no side effects (y0l)
#pragma no side effects (y1l)
#pragma no side effects (ynl)
#endif /* __MATH_HAS_NO_SIDE_EFFECTS */

extern	int	signgaml;

#endif /* (n32 or 64) && _SGIAPI */

#if _SGIAPI
/*
 * SGI/SVR4 Additions
 */

enum version { c_issue_4, ansi_1, strict_ansi };
extern const enum version _lib_version;
#if !defined(__c99)
struct __cabs_s { double a,b; };

extern double	cabs(struct __cabs_s);
#ifdef __MATH_HAS_NO_SIDE_EFFECTS
#pragma no side effects (cabs)
#endif /* __MATH_HAS_NO_SIDE_EFFECTS */
#endif

extern double	drem(double, double);
#ifdef __MATH_HAS_NO_SIDE_EFFECTS
#pragma no side effects (drem)
#endif /* __MATH_HAS_NO_SIDE_EFFECTS */

extern int	finite(double);
#ifdef __MATH_HAS_NO_SIDE_EFFECTS
#pragma no side effects (finite)
#endif /* __MATH_HAS_NO_SIDE_EFFECTS */


#if (_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI

/* long double precision routines */

/* libc routines */

extern int isnanl( long double );

extern long double scalbl( long double, long double );

extern long double dreml (long double, long double);

#ifdef __MATH_HAS_NO_SIDE_EFFECTS

#pragma no side effects (isnanl)
#pragma no side effects (scalbl)
#pragma no side effects (dreml)

#endif /* __MATH_HAS_NO_SIDE_EFFECTS */

#endif

__SGI_LIBC_BEGIN_NAMESPACE_STD
extern double	atof(const char *);

extern double   strtod(const char * __restrict, char ** __restrict);

extern int	rand(void);
extern void	srand(unsigned);
__SGI_LIBC_END_NAMESPACE_STD

extern long	random(void);
extern void	srandom(unsigned);
extern char *	initstate(unsigned int, char *, __SGI_LIBC_NAMESPACE_QUALIFIER size_t);
extern char *	setstate(const char *);

extern double	drand48(void);
extern double	erand48(unsigned short [3]);
extern long	lrand48(void);
extern long	nrand48(unsigned short [3]);
extern long	mrand48(void);
extern long	jrand48(unsigned short [3]);
extern void	srand48(long);
extern unsigned short * seed48(unsigned short int [3]);
extern void	lcong48(unsigned short int [7]);

/* Map old MIPS names of single-precision forms to ANSI names.*/

#define facos	acosf
#define fasin	asinf
#define fatan	atanf
#define fatan2	atan2f
#define fcos	cosf
#define fsin	sinf
#define ftan	tanf
#define fcosh	coshf
#define fsinh	sinhf
#define ftanh	tanhf
#define fexp	expf
#define flog	logf
#define flog10	log10f
#define fsqrt	sqrtf
#define fceil	ceilf
#define ffloor	floorf


#if (_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI

/* map long double precision forms to the ANSI names */

#define	isnanq	isnanl

#define	qabs	fabsl
#define	qacos	acosl
#define	qasin	asinl
#define	qatan	atanl
#define	qatan2	atan2l

#if defined(__c99)
#define qcbrt	cbrtl
#define qexmp1	expm1l
#define qdrem	dreml
#endif /* __c99 */

#if !defined(__c99)
#define __qcabs_s __cabsl_s

#define	qcabs	cabsl
#endif
#define	qceil	ceill
#define	qcopysign copysignl
#define	qcos	cosl
#define	qcosh	coshl
#define	qerf	erfl
#define	qerfc	erfcl
#define	qexp	expl
#define	qfinite	finitel
#define	qfloor	floorl
#define	qfrexp	frexpl
#define	qhypot	hypotl
#define	qj0	j0l
#define	qj1	j1l
#define	qjn	jnl
#define	qldexp	ldexpl
#define	qlog	logl
#define	qlog1p	log1pl
#define	qlog10	log10l
#define	qlogb	logbl
#define	qmod	fmodl
#define	qmodf	modfl
#define	qnextafter nextafterl
#define	qpow	powl
#define	qrint	rintl
#define	qscalb	scalbl
#define	qsin	sinl
#define	qsinh	sinhl
#define	qsqrt	sqrtl
#define	qtan	tanl
#define	qtanh	tanhl
#define	qtrunc	truncl
#define	qy0	y0l
#define	qy1	y1l
#define	qyn	ynl

#if (_XOPEN4 || _XOPEN5) && _NO_ANSIMODE
#define	qgamma	gammal
#define	qlgamma	lgammal
#define	qsigngam signgaml

extern long double gammal( long double );

#endif

#endif

/* similar mapping of old MIPS names to ANSI-like names */

#undef flog1p
#define flog1p 	log1pf
#define ftrunc	truncf

/* additional single-percision forms */
extern float	fhypot(float, float);
#ifdef __MATH_HAS_NO_SIDE_EFFECTS
#pragma no side effects (fhypot)
#endif /* __MATH_HAS_NO_SIDE_EFFECTS */

#if !defined(__c99)
struct __fcabs_s { float a,b; };

extern float	fcabs(struct __fcabs_s);
#ifdef __MATH_HAS_NO_SIDE_EFFECTS
#pragma no side effects (fcabs)
#endif /* __MATH_HAS_NO_SIDE_EFFECTS */
#endif

extern float	fexpm1(float);
#ifdef __MATH_HAS_NO_SIDE_EFFECTS
#pragma no side effects (fexpm1)
#endif /* __MATH_HAS_NO_SIDE_EFFECTS */

#if _NO_XOPEN4 && _NO_XOPEN5 && (defined(__INLINE_INTRINSICS) && \
	((_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI))
#if _MIPS_ISA != _MIPS_ISA_MIPS1
#pragma intrinsic (hypotf)
#pragma intrinsic (fhypot)
#endif
#endif

#ifndef HUGE
#ifdef  MAXFLOAT
#define HUGE		MAXFLOAT
#else
#define HUGE	((float)3.40282346638528860e+38) /* value of MAXFLOAT */
#endif /* MAXFLOAT */
#endif /* !HUGE */

#define _ABS(x)	((x) < 0 ? -(x) : (x))
#define _REDUCE(TYPE, X, XN, C1, C2)	{ \
	double x1 = (double)(TYPE)X, x2 = X - x1; \
	X = x1 - (XN) * (C1); X += x2; X -= (XN) * (C2); }
#define _POLY1(x, c)	((c)[0] * (x) + (c)[1])
#define _POLY2(x, c)	(_POLY1((x), (c)) * (x) + (c)[2])
#define _POLY3(x, c)	(_POLY2((x), (c)) * (x) + (c)[3])
#define _POLY4(x, c)	(_POLY3((x), (c)) * (x) + (c)[4])
#define _POLY5(x, c)	(_POLY4((x), (c)) * (x) + (c)[5])
#define _POLY6(x, c)	(_POLY5((x), (c)) * (x) + (c)[6])
#define _POLY7(x, c)	(_POLY6((x), (c)) * (x) + (c)[7])
#define _POLY8(x, c)	(_POLY7((x), (c)) * (x) + (c)[8])
#define _POLY9(x, c)	(_POLY8((x), (c)) * (x) + (c)[9])

#if defined(__cplusplus)  && \
    defined(_MIPS_SIM) && _MIPS_SIM != _MIPS_SIM_ABI32 && \
    !defined(__OLD_MATHERR_NAMES)
#define __MATH_EXCEPTION math_exception
#else
#define __MATH_EXCEPTION exception
#endif

struct __MATH_EXCEPTION {
	int type;
	char *name;
	double arg1;
	double arg2;
	double retval;
};

extern int matherr(struct __MATH_EXCEPTION *p);

#undef __MATH_EXCEPTION

__SGI_LIBC_END_EXTERN_C

#include <svr4_math.h>

__SGI_LIBC_BEGIN_EXTERN_C

#endif /* _SGIAPI */

#if defined(__INLINE_INTRINSICS) && _NO_XOPEN4 && _NO_XOPEN5

/* The functions made intrinsic here can be activated by the driver
** passing -D__INLINE_INTRINSICS to cfe, but cfe should ensure that
** this has no effect unless the hardware architecture directly
** supports these basic operations.
*/

__SGI_LIBC_BEGIN_NAMESPACE_STD

#if _MIPS_ISA != _MIPS_ISA_MIPS1
#pragma intrinsic (sqrt)
#pragma intrinsic (sqrtf)
#if (_MIPS_SIM==_MIPS_SIM_NABI32 || _MIPS_SIM==_MIPS_SIM_ABI64) && _SGIAPI
#pragma intrinsic (pow)
#pragma intrinsic (powf)
#endif
#endif
#pragma intrinsic (fabs)
#pragma intrinsic (fabsf)

__SGI_LIBC_END_NAMESPACE_STD

#endif /* defined(__INLINE_INTRINSICS) && _NO_XOPEN4  && _NO_XOPEN5 */

__SGI_LIBC_END_EXTERN_C

/* Overloads of abs for integral types.  The C++ standard says they shouldn't
 * be here, only in stdlib.h.  Since we're defining abs(int) in this file,
 * though, it would be dangerous not to put in long and long long too.
 */

__SGI_LIBC_BEGIN_NAMESPACE_STD

#ifdef __cplusplus
#ifndef _ABS_
#define _ABS_
#define _ABS_INLINE_
inline int abs(int x) {return x > 0 ? x : -x;}
#endif
#endif

#if defined(__cplusplus) && \
     defined(_MIPS_SIM) && _MIPS_SIM != _MIPS_SIM_ABI32 && \
     defined(_COMPILER_VERSION) && (_COMPILER_VERSION >= 720) && \
     defined(__LIBC_MATH_OVERLOAD__) && __LIBC_MATH_OVERLOAD__

#ifndef __sgi_cpp_abs_long_defined
#define __sgi_cpp_abs_long_defined
inline long abs(long x) {return x > 0 ? x : -x;}
#ifdef _LONGLONG
inline long long abs(long long x) {return x > 0 ? x : -x;}
#endif /* _LONGLONG */
#endif /* __sgi_cpp_abs_long_defined */

#endif /* __cplusplus && n32 && version >= 7.2 && __LIBC_MATH_OVERLOAD__ */

#if defined(__cplusplus) && \
     defined(_MIPS_SIM) && _MIPS_SIM != _MIPS_SIM_ABI32 && \
     defined(_COMPILER_VERSION) && (_COMPILER_VERSION >= 720) && \
     defined(__LIBC_MATH_OVERLOAD__) && __LIBC_MATH_OVERLOAD__

#if !_SGIAPI

/* These functions are declared here to maintain compatibility
 * with the behavior prior to 7.4.
 */

__SGI_LIBC_BEGIN_EXTERN_C

extern long double fabsl( long double );
extern long double ceill( long double );
extern long double floorl( long double );
extern long double fmodl( long double, long double );
extern long double frexpl( long double, int *);
extern long double ldexpl( long double, int );
extern long double modfl( long double, long double *);
extern long double sqrtl( long double );
extern long double expl( long double );
extern long double logl( long double );
extern long double log10l( long double );
extern long double powl( long double, long double );
extern long double sinl( long double );
extern long double cosl( long double );
extern long double tanl( long double );
extern long double asinl( long double );
extern long double acosl( long double );
extern long double atanl( long double );
extern long double atan2l( long double, long double );
extern long double sinhl( long double );
extern long double coshl( long double );
extern long double tanhl( long double );

extern float	   frexpf(float, int *);
#pragma optional   frexpf
extern float	   ldexpf(float, int);
#pragma optional   ldexpf

__SGI_LIBC_END_EXTERN_C

#endif /* _SGIAPI */

inline float abs(float x) { return fabsf(x); }
inline double abs(double x) { return fabs(x); }
inline long double abs(long double x) { return __SGI_LIBC_NAMESPACE::fabsl(x); }

inline float fabs(float x) { return fabsf(x); }
inline long double fabs(long double x) { return __SGI_LIBC_NAMESPACE::fabsl(x); }

inline float ceil(float x) { return ceilf(x); }
inline long double ceil(long double x) { return __SGI_LIBC_NAMESPACE::ceill(x); }

inline float floor(float x) { return floorf(x); }
inline long double floor(long double x) { return __SGI_LIBC_NAMESPACE::floorl(x); }

inline float fmod(float x, float y) { return fmodf(x, y); }
inline long double fmod(long double x, long double y) {
  return __SGI_LIBC_NAMESPACE::fmodl(x, y); 
}

inline float frexp(float x, int* y) { return frexpf(x, y); }
inline long double frexp(long double x, int* y) {
  return __SGI_LIBC_NAMESPACE::frexpl(x, y);
}

inline float ldexp(float x, int y) { return ldexpf(x, y); }
inline long double ldexp(long double x, int y) {
  return __SGI_LIBC_NAMESPACE::ldexpl(x, y);
}

inline float modf(float x, float* y) { return modff(x, y); }
inline long double modf(long double x, long double* y) {
  return __SGI_LIBC_NAMESPACE::modfl(x, y);
}

inline float sqrt(float x) { return sqrtf(x); }
inline long double sqrt(long double x) { return __SGI_LIBC_NAMESPACE::sqrtl(x); }

inline float exp(float x) { return expf(x); }
inline long double exp(long double x) { return __SGI_LIBC_NAMESPACE::expl(x); }

inline float log(float x) { return logf(x); }
inline long double log(long double x) { return __SGI_LIBC_NAMESPACE::logl(x); }

inline float log10(float x) { return log10f(x); }
inline long double log10(long double x) { return __SGI_LIBC_NAMESPACE::log10l(x); }

inline float pow(float x, float y) { return powf(x, y); }
inline long double pow(long double x, long double y) {
  return __SGI_LIBC_NAMESPACE::powl(x, y);
}

inline float pow(float x, int n) {
  float tmp;
  switch(n) {
  case 2:
    return x * x;
  case 3:
    return x * x * x;
  case 4:
    return tmp = x * x, tmp * tmp;
  default:
    return pow(x, (float) n);
  }
}

inline double pow(double x, int n) {
  double tmp;
  switch(n) {
  case 2:
    return x * x;
  case 3:
    return x * x * x;
  case 4:
    return tmp = x * x, tmp * tmp;
  default:
    return pow(x, (double) n);
  }
}

inline long double pow(long double x, int n) {
  long double tmp;
  switch(n) {
  case 2:
    return x * x;
  case 3:
    return x * x * x;
  case 4:
    return tmp = x * x, tmp * tmp;
  default:
    return pow(x, (long double) n);
  }
}

inline float sin(float x) { return sinf(x); }
inline long double sin(long double x) { return __SGI_LIBC_NAMESPACE::sinl(x); }

inline float cos(float x) { return cosf(x); }
inline long double cos(long double x) { return __SGI_LIBC_NAMESPACE::cosl(x); }

inline float tan(float x) { return tanf(x); }
inline long double tan(long double x) { return __SGI_LIBC_NAMESPACE::tanl(x); }

inline float asin(float x) { return asinf(x); }
inline long double asin(long double x) { return __SGI_LIBC_NAMESPACE::asinl(x); }

inline float acos(float x) { return acosf(x); }
inline long double acos(long double x) { return __SGI_LIBC_NAMESPACE::acosl(x); }

inline float atan(float x) { return atanf(x); }
inline long double atan(long double x) { return __SGI_LIBC_NAMESPACE::atanl(x); }

inline float atan2(float x, float y) { return atan2f(x, y); }
inline long double atan2(long double x, long double y) {
  return __SGI_LIBC_NAMESPACE::atan2l(x, y);
}

inline float sinh(float x) { return sinhf(x); }
inline long double sinh(long double x) { return __SGI_LIBC_NAMESPACE::sinhl(x); }

inline float cosh(float x) { return coshf(x); }
inline long double cosh(long double x) { return __SGI_LIBC_NAMESPACE::coshl(x); }

inline float tanh(float x) { return tanhf(x); }
inline long double tanh(long double x) { return __SGI_LIBC_NAMESPACE::tanhl(x); }

#endif /* __cplusplus && n32 && version >= 7.2 && __LIBC_MATH_OVERLOAD__ */

__SGI_LIBC_END_NAMESPACE_STD

#endif /* !__MATH_CORE_H__ */

