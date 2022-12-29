#ifndef __COMPLEX_H__
#define __COMPLEX_H__

#ifndef __c99
#error This header file is to be used only for c99 mode compilations
#else

#include <sgidefs.h>
#include <standards.h>

#define complex _Complex
#define _Complex_I ((float _Complex) (__I__))
#define imaginary _Imaginary
// #define _Imaginary_I ((float _Imaginary) 1)
#define _Imaginary_I __I__
#define I _Imaginary_I

/* C99: 7.3.5.1 */
extern double complex      cacos   (double complex);
extern float complex       cacosf  (float  complex);
extern long double complex cacosl  (long double complex);
#pragma optional cacos
#pragma optional cacosf
#pragma optional cacosl

/* C99: 7.3.5.2 */
extern double complex      casin   (double complex);
extern float  complex      casinf  (float  complex);
extern long double complex casinl  (long double complex);
#pragma optional casin
#pragma optional casinf
#pragma optional casinl

/* C99: 7.3.5.3 */
extern double complex      catan   (double complex);
extern float  complex      catanf  (float  complex);
extern long double complex catanl  (long double complex);
#pragma optional catan
#pragma optional catanf
#pragma optional catanl

/* C99: 7.3.5.4 */
extern double complex      ccos    (double complex);
extern float complex       ccosf   (float complex);
extern long double complex ccosl   (long double complex);
#pragma optional ccos
#pragma optional ccosf
#pragma optional ccosl

/* C99: 7.3.5.5 */
extern double complex      csin    (double complex);
extern float complex       csinf   (float complex);
extern long double complex csinl   (long double complex);
#pragma optional csin
#pragma optional csinf
#pragma optional csinl

/* C99: 7.3.5.6 */
extern double complex      ctan    (double complex);
extern float complex       ctanf   (float complex);
extern long double complex ctanl   (long double complex);
#pragma optional ctan
#pragma optional ctanf
#pragma optional ctanl

/* C99: 7.3.6.1 */
extern double complex      cacosh  (double complex);
extern float complex       cacoshf (float  complex);
extern long double complex cacoshl (long double complex);
#pragma optional cacosh
#pragma optional cacoshf
#pragma optional cacoshl

/* C99: 7.3.6.2 */
extern double complex      casinh  (double complex);
extern float complex       casinhf (float  complex);
extern long double complex casinhl (long double complex);
#pragma optional casinh
#pragma optional casinhf
#pragma optional casinhl

/* C99: 7.3.6.3 */
extern double complex      catanh  (double complex);
extern float complex       catanhf (float  complex);
extern long double complex catanhl (long double complex);
#pragma optional catanh
#pragma optional catanhf
#pragma optional catanhl

/* C99: 7.3.6.4 */
extern double complex      ccosh   (double complex);
extern float complex       ccoshf  (float complex);
extern long double complex ccoshl  (long double complex);
#pragma optional ccosh
#pragma optional ccoshf
#pragma optional ccoshl

/* C99: 7.3.6.5 */
extern double complex      csinh   (double complex);
extern float complex       csinhf  (float complex);
extern long double complex csinhl  (long double complex);
#pragma optional csinh
#pragma optional csinhf
#pragma optional csinhl

/* C99: 7.3.6.6 */
extern double complex      ctanh   (double complex);
extern float complex       ctanhf  (float complex);
extern long double complex ctanhl  (long double complex);
#pragma optional ctanh
#pragma optional ctanhf
#pragma optional ctanhl

/* C99: 7.3.7.1 */
extern double complex      cexp    (double complex);
extern float complex       cexpf   (float complex);
extern long double complex cexpl   (long double complex);
#pragma optional cexp
#pragma optional cexpf
#pragma optional cexpl

/* C99: 7.3.7.2 */
extern double complex      clog    (double complex);
extern float complex       clogf   (float complex);
extern long double complex clogl   (long double complex);
#pragma optional clog
#pragma optional clogf
#pragma optional clogl

/* C99: 7.3.8.1 */

/* c89 also had functions cabs, cabsf and cabsl with the following
 * prototypes.
 *
 * double cabs (struct { double a,b; } z);
 * float cabsf (struct { float a,b; } z);
 * long double cabsl (struct { long double a,b; } z);
 *
 * As the passing of structs by value is different from passing
 * complex by value for the float and long double cases, the following
 * changes are being done to the C99 functions so as to maintain
 * backwards compatibility.
 * 
 * For the C99 functions we provide static definitions of these,
 * which in turn call the corresponding library functions with a __c99_
 * prefix.
 *
 * There are two drawbacks of this approach
 *
 *  1.  As each compilation will get its own copy of these functions,
 *      any program which relies on the address of these functions being
 *      unique will fail.
 *
 *  2.  If the user rolls his own version of these functions, they will
 *      never get invoked, and to get around this problem, the user
 *      should be able to disable the generation of these static functions.
 *      This is achieved by adding -D_C99_CABS_USER_DEFINED to the commandline.
 */


extern double      __c99_cabs  (double complex);
extern float       __c99_cabsf (float complex);
extern long double __c99_cabsl (long double complex);
#pragma optional   __c99_cabs
#pragma optional   __c99_cabsf
#pragma optional   __c99_cabsl

#ifdef _C99_CABS_USER_DEFINED

extern double       cabs  (double complex);
extern float        cabsf (float complex);
extern long double  cabsl (long double complex);

#else 

static inline double cabs       (double complex z)      {return __c99_cabs(z); }
static inline float  cabsf      (float complex z)       {return __c99_cabsf(z);}
static inline long double cabsl (long double complex z) {return __c99_cabsl(z);}

#endif /* _C99_CABS_USER_DEFINED */

/* C99: 7.3.8.2 */
extern double complex      cpow    (double complex, double complex);
extern float complex       cpowf   (float complex, float complex);
extern long double complex cpowl   (long double complex, long double complex);
#pragma optional cpow
#pragma optional cpowf
#pragma optional cpowl

/* C99: 7.3.8.3 */
extern double complex      csqrt   (double complex);
extern float complex       csqrtf  (float complex);
extern long double complex csqrtl  (long double complex);
#pragma optional csqrt
#pragma optional csqrtf
#pragma optional csqrtl

/* C99: 7.3.9.1 */
extern double              carg    (double complex);
extern float               cargf   (float complex);
extern long double         cargl   (long double complex);
#pragma optional carg
#pragma optional cargf
#pragma optional cargl

/* C99: 7.3.9.2 */
extern double              cimag   (double complex);
extern float               cimagf  (float complex);
extern long double         cimagl  (long double complex);
#pragma optional cimag
#pragma optional cimagf
#pragma optional cimagl

/* C99: 7.3.9.3 */
extern double complex      conj    (double complex);
extern float complex       conjf   (float complex);
extern long double complex conjl   (long double complex);
#pragma optional conj
#pragma optional conjf
#pragma optional conjl

/* C99: 7.3.9.4 */
extern double complex      cproj   (double complex);
extern float complex       cprojf  (float complex);
extern long double complex cprojl  (long double complex);
#pragma optional cproj
#pragma optional cprojf
#pragma optional cprojl

/* C99: 7.3.9.5 */
extern double              creal   (double complex);
extern float               crealf  (float complex);
extern long double         creall  (long double complex);
#pragma optional creal
#pragma optional crealf
#pragma optional creall

#if _NO_XOPEN4 && _NO_XOPEN5 && (defined(__INLINE_INTRINSICS) && \
        defined(_COMPILER_VERSION) && (_COMPILER_VERSION >= 740))
#if 0
#pragma intrinsic (cabs)
#pragma intrinsic (cabsf)
#pragma intrinsic (cabsl)
#pragma intrinsic (ccos)
#pragma intrinsic (ccosf)
#pragma intrinsic (ccosl)
#pragma intrinsic (cexp)
#pragma intrinsic (cexpf)
#pragma intrinsic (cexpl)
#endif /* 0 */
#pragma intrinsic (cimag)
#pragma intrinsic (cimagf)
#pragma intrinsic (cimagl)
#if 0
#pragma intrinsic (clog)
#pragma intrinsic (clogf)
#pragma intrinsic (clogl)
#endif /* 0 */
#pragma intrinsic (conj)
#pragma intrinsic (conjf)
#pragma intrinsic (conjl)
#pragma intrinsic (creal)
#pragma intrinsic (crealf)
#pragma intrinsic (creall)
#if 0
#pragma intrinsic (csin)
#pragma intrinsic (csinf)
#pragma intrinsic (csinl)
#pragma intrinsic (csqrt)
#pragma intrinsic (csqrtf)
#pragma intrinsic (csqrtl)
#endif /* 0 */
#ifdef __MATH_HAS_NO_SIDE_EFFECTS
#if 0
#pragma no side effects (cabs)
#pragma no side effects (cabsf)
#pragma no side effects (cabsl)
#pragma no side effects (ccos)
#pragma no side effects (ccosf)
#pragma no side effects (ccosl)
#pragma no side effects (cexp)
#pragma no side effects (cexpf)
#pragma no side effects (cexpl)
#endif /* 0 */
#pragma no side effects (cimag)
#pragma no side effects (cimagf)
#pragma no side effects (cimagl)
#if 0
#pragma no side effects (clog)
#pragma no side effects (clogf)
#pragma no side effects (clogl)
#endif /* 0 */
#pragma no side effects (conj)
#pragma no side effects (conjf)
#pragma no side effects (conjl)
#pragma no side effects (creal)
#pragma no side effects (crealf)
#pragma no side effects (creall)
#if 0
#pragma no side effects (csin)
#pragma no side effects (csinf)
#pragma no side effects (csinl)
#pragma no side effects (csqrt)
#pragma no side effects (csqrtf)
#pragma no side effects (csqrtl)
#endif /* 0 */
#endif /* __MATH_HAS_NO_SIDE_EFFECTS */
#endif /* _NO_XOPEN4 */
#endif /* __c99 */

#endif /* __COMPLEX_H__ */
