#ifndef __TGMATH_H__
#define __TGMATH_H__

#ifndef __c99
#error This header file is to be used only for c99 mode compilations
#else

/* 7.22 */

#include <math.h>
#include <complex.h>

/* functions appearing in both math.h and complex.h */

#define acos(x)         __generic(x,,,     acos, acosf, acosl, cacos, cacosf, cacosl)(x)
#define asin(x)         __generic(x,,,     asin, asinf, asinl, casin, casinf, casinl)(x)
#define atan(x)         __generic(x,,,     atan, atanf, atanl, catan, catanf, catanl)(x)
#define acosh(x)        __generic(x,,,     acosh, acoshf, acoshl, cacosh, cacoshf, cacoshl)(x)
#define asinh(x)        __generic(x,,,     asinh, asinhf, asinhl, casinh, casinhf, casinhl)(x)
#define atanh(x)        __generic(x,,,     atanh, atanhf, atanhl, catanh, catanhf, catanhl)(x)
#define cos(x)          __generic(x,,,     cos, cosf, cosl, ccos, ccosf, ccosl)(x)
#define sin(x)          __generic(x,,,     sin, sinf, sinl, csin, csinf, csinl)(x)
#define tan(x)          __generic(x,,,     tan, tanf, tanl, ctan, ctanf, ctanl)(x)
#define cosh(x)         __generic(x,,,     cosh, coshf, coshl, ccosh, ccoshf, ccoshl)(x)
#define sinh(x)         __generic(x,,,     sinh, sinhf, sinhl, csinh, csinhf, csinhl)(x)
#define tanh(x)         __generic(x,,,     tanh, tanhf, tanhl, ctanh, ctanhf, ctanhl)(x)
#define exp(x)          __generic(x,,,     exp, expf, expl, cexp, cexpf, cexpl)(x)
#define log(x)          __generic(x,,,     log, logf, logl, clog, clogf, clogl)(x)
#define pow(x)          __generic(x, y,,   pow, powf, powl, cpow, cpowf, cpowl)(x, y)
#define sqrt(x)         __generic(x,,,     sqrt, sqrtf, sqrtl, csqrt, csqrtf, csqrtl)(x)
#define fabs(x)         __generic(x,,,     fabs, fabsf, fabsl, cabs, cabsf, cabsl)(x)

/* functions appearing in math.h and not in complex.h */

#define atan2(x,y)      __generic(x, y,,   atan2, atan2f, atan2l,,,)(x, y)
#define cbrt(x)         __generic(x,,,     cbrt, cbrtf, cbrtl,,,)(x)
#define ceil(x)         __generic(x,,,     ceil, ceilf, ceill,,,)(x)
#define copysign(x)     __generic(x, y,,   copysign, copysignf, copysignl,,,)(x, y)
#define erf(x)          __generic(x,,,     erf, erff, erfl,,,)(x)
#define erfc(x)         __generic(x,,,     erfc, erfcf, erfcl,,,)(x)
#define exp2(x)         __generic(x,,,     exp2, exp2f, exp2l,,,)(x)
#define expm1(x)        __generic(x,,,     expm1, expm1f, expm1l,,,)(x)
#define fdim(x,y)       __generic(x, y,,   fdim, fdimf, fdiml,,,)(x, y)
#define floor(x)        __generic(x,,,     floor, floorf, floorl,,,)(x)
#define fma(x)          __generic(x,,,     fma, fmaf, fmal,,,)(x)
#define fmax(x,y)       __generic(x, y,,   fmax, fmaxf, fmaxl,,,)(x, y)
#define fmin(x,y)       __generic(x, y,,   fmin, fminf, fminl,,,)(x, y)
#define fmod(x,y)       __generic(x, y,,   fmod, fmodf, fmodl,,,)(x, y)
#define frexp(x,y)      __generic(x, y,,   frexp, frexpf, frexpl,,,)(x, y)
#define hypot(x,y)      __generic(x, y,,   hypot, hypotf, hypotl,,,)(x, y)
#define ilogb(x)        __generic(x,,,     ilogb, ilogbf, ilogbl,,,)(x)
#define ldexp(x,y)      __generic(x, y,,   ldexp, ldexpf, ldexpl,,,)(x, y)
#define lgamma(x)       __generic(x,,,     lgamma, lgammaf, lgammal,,,)(x)
#define llrint(x)       __generic(x,,,     llrint, llrintf, llrintl,,,)(x)
#define llround(x)      __generic(x,,,     llround, llroundf, llroundl,,,)(x)
#define log10(x)        __generic(x,,,     log10, log10f, log10l,,,)(x)
#define log1p(x)        __generic(x,,,     log1p, log1pf, log1pl,,,)(x)
#define log2(x)         __generic(x,,,     log2, log2f, log2l,,,)(x)
#define logb(x)         __generic(x,,,     logb, logbf, logbl,,,)(x)
#define lrint(x)        __generic(x,,,     lrint, lrintf, lrintl,,,)(x)
#define lround(x)       __generic(x,,,     lround, lroundf, lroundl,,,)(x)
#define nearbyint(x)    __generic(x,,,     nearbyint, nearbyintf, nearbyintl,,,)(x)
#define nextafter(x,y)  __generic(x, y,,   nextafter, nextafterf, nextafterl,,,)(x, y)
#define nexttoward(x,y) __generic(x, y,,   nexttoward, nexttowardf, nexttowardl,,,)(x, y)
#define remainder(x,y)  __generic(x, y,,   remainder, remainderf, remainderl,,,)(x, y)
#define remquo(x,y,z)   __generic(x, y, z, remquo, remquof, remquol,,,)(x, y, z)
#define rint(x)         __generic(x,,,     rint, rintf, rintl,,,)(x)
#define round(x)        __generic(x,,,     round, roundf, roundl,,,)(x)
#define scalbn(x,y)     __generic(x, y,,   scalbn, scalbnf, scalbnl,,,)(x, y)
#define scalbln(x,y)    __generic(x, y,,   scalbln, scalblnf, scalblnl,,,)(x, y)
#define tgamma(x)       __generic(x,,,     tgamma, tgammaf, tgammal,,,)(x)
#define trunc(x)        __generic(x,,,     trunc, truncf, truncl,,,)(x)

/* functions appearing in complex.h and not in math.h */

#define carg(x)         __generic(x,,,   ,,, carg, cargf, cargl)(x)
#define cimag(x)        __generic(x,,,   ,,, cimag, cimagf, cimagl)(x)
#define conj(x)         __generic(x,,,   ,,, conj, conjf, conjl)(x)
#define cproj(x)        __generic(x,,,   ,,, cproj, cprojf, cprojl)(x)
#define creal(x)        __generic(x,,,   ,,, creal, crealf, creall)(x)

#endif /* __c99 */

#endif /* __TGMATH_H__ */
