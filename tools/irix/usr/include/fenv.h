#ifndef __FENV_H__
#define __FENV_H__

#ifndef __c99
#error This header file is to be used only for c99 mode compilations
#else

/* C99: 7.6 3/4 : Floating-point environment data types */

/* WARNING: do not change fenv_t.
 * If yo do need to change you also need to modify math/fenv.c
 * as mentioned in bug 862409.
 */

typedef int fenv_t;
typedef int fexcept_t;

/* C99: 7.6 5/6 : Floating-point environment exception flags */

#define FE_INEXACT    0x00000004
#define FE_UNDERFLOW  0x00000008
#define FE_OVERFLOW   0x00000010
#define FE_DIVBYZERO  0x00000020
#define FE_INVALID    0x00000040
#define FE_ALL_EXCEPT (FE_INEXACT | FE_UNDERFLOW | FE_OVERFLOW | \
                       FE_DIVBYZERO | FE_INVALID)

/* C99: 7.6 7   : Floating-point environment rounding direction modes */

#define FE_TONEAREST  0
#define FE_TOWARDZERO 1
#define FE_UPWARD     2
#define FE_DOWNWARD   3

/* C99: 7.6 8   : Default floating point environment */

const fenv_t *get_fpc_csr_init_state();
#pragma optional get_fpc_csr_init_state
#define FE_DFL_ENV (get_fpc_csr_init_state())

/* C99: 7.6.2   : Floating-point exceptions */

extern void feclearexcept(int excepts);
extern void fegetexceptflag(fexcept_t *flagp, int excepts);
extern void feraiseexcept(int excepts);
extern void fesetexceptflag(const fexcept_t *flagp, int excepts);
extern int  fetestexcept(int excepts);
#pragma optional feclearexcept
#pragma optional fegetexceptflag
#pragma optional feraiseexcept
#pragma optional fesetexceptflag
#pragma optional fetestexcept

/* C99: 7.6.3   : Rounding */

extern int  fegetround(void);
extern int  fesetround(int round);
#pragma optional fegetround
#pragma optional fesetround

/* C99: 7.6.4   : Environment */

extern void fegetenv(fenv_t *envp);
extern int  feholdexcept(fenv_t *envp);
extern void fesetenv(const fenv_t *envp);
extern void feupdateenv(const fenv_t *envp);
#pragma optional fegetenv
#pragma optional feholdexcept
#pragma optional fesetenv
#pragma optional feupdateenv

#endif /* __c99 */

#endif /* __FENV_H__ */
