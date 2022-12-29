#ifndef __STDINT_H__
#define __STDINT_H__

#ifndef __c99
#error This header file is to be used only for c99 mode compilations
#else

/*
 * inttypes.h  and types.h also defines these.
 * Avoid compiler errors if either inttypes.h
 * or types.h is also included.
 */

#ifndef __inttypes_INCLUDED
#define __inttypes_INCLUDED

/* C99: 7.18.1.1 : Exact-width integer types */

typedef signed char             int8_t;
typedef unsigned char           uint8_t;
typedef signed short            int16_t;
typedef unsigned short          uint16_t;
typedef signed int              int32_t;
typedef unsigned int            uint32_t;
typedef signed long long        int64_t;
typedef unsigned long long      uint64_t;

/* C99: 7.18.1.4 : Integer types capable of holding object pointers */

typedef signed long int         intptr_t;
typedef unsigned long int       uintptr_t;

/* C99: 7.18.1.5 : Greatest-width integer types */

typedef signed long long        intmax_t;
typedef unsigned long long      uintmax_t;

#endif /* !__inttypes_INCLUDED */

/* C99: 7.18.1.2 : Minimum-width integer types */

typedef signed char             int_least8_t;
typedef unsigned char           uint_least8_t;
typedef signed short            int_least16_t;
typedef unsigned short          uint_least16_t;
typedef signed int              int_least32_t;
typedef unsigned int            uint_least32_t;
typedef signed long long        int_least64_t;
typedef unsigned long long      uint_least64_t;

/* C99: 7.18.1.3 : Fastest minimum-width integer types */

typedef signed char             int_fast8_t;
typedef unsigned char           uint_fast8_t;
typedef signed short            int_fast16_t;
typedef unsigned short          uint_fast16_t;
typedef signed int              int_fast32_t;
typedef unsigned int            uint_fast32_t;
typedef signed long long        int_fast64_t;
typedef unsigned long long      uint_fast64_t;

/* C99: 7.18.2.1 : Limits of exact-width integer types */

#define INT8_MIN                (-0x7f - 1)
#define INT16_MIN               (-0x7fff - 1)
#define INT32_MIN               (-0x7fffffff - 1)
#define INT64_MIN               (-0x7fffffffffffffff - 1)

#define INT8_MAX                0x7f
#define INT16_MAX               0x7fff
#define INT32_MAX               0x7fffffff
#define INT64_MAX               0x7fffffffffffffff

#define UINT8_MAX               0xff
#define UINT16_MAX              0xffff
#define UINT32_MAX              0xffffffff
#define UINT64_MAX              0xffffffffffffffff

/* C99: 7.18.2.2 : Limits of minimum-width integer types */

#define INT_LEAST8_MIN          INT8_MIN
#define INT_LEAST16_MIN         INT16_MIN
#define INT_LEAST32_MIN         INT32_MIN
#define INT_LEAST64_MIN         INT64_MIN

#define INT_LEAST8_MAX          INT8_MAX
#define INT_LEAST16_MAX         INT16_MAX
#define INT_LEAST32_MAX         INT32_MAX
#define INT_LEAST64_MAX         INT64_MAX

#define UINT_LEAST8_MAX         UINT8_MAX
#define UINT_LEAST16_MAX        UINT16_MAX
#define UINT_LEAST32_MAX        UINT32_MAX
#define UINT_LEAST64_MAX        UINT64_MAX

/* C99: 7.18.2.3 : Limits of fastest minimum-width integer types */

#define INT_FAST8_MIN           INT8_MIN
#define INT_FAST16_MIN          INT16_MIN
#define INT_FAST32_MIN          INT32_MIN
#define INT_FAST64_MIN          INT64_MIN

#define INT_FAST8_MAX           INT8_MAX
#define INT_FAST16_MAX          INT16_MAX
#define INT_FAST32_MAX          INT32_MAX
#define INT_FAST64_MAX          INT64_MAX

#define UINT_FAST8_MAX          UINT8_MAX
#define UINT_FAST16_MAX         UINT16_MAX
#define UINT_FAST32_MAX         UINT32_MAX
#define UINT_FAST64_MAX         UINT64_MAX

/* C99: 7.18.2.4 : Limits of integer types capable of holding object pointers */

#if (_MIPS_SZLONG == 32)
#define INTPTR_MIN              INT32_MIN
#define INTPTR_MAX              INT32_MAX
#define UINTPTR_MAX             UINT32_MAX
#endif
#if (_MIPS_SZLONG == 64)
#define INTPTR_MIN              INT64_MIN
#define INTPTR_MAX              INT64_MAX
#define UINTPTR_MAX             UINT64_MAX
#endif

/* C99: 7.18.2.5 : Limits of greatest-width integer types */

#define INTMAX_MIN              INT64_MIN
#define INTMAX_MAX              INT64_MAX
#define UINTMAX_MAX             UINT64_MAX

/* C99: 7.18.3   : Limits of other integer types */

#if (_MIPS_SZLONG == 32)
#define PTRDIFF_MIN             INT32_MIN
#define PTRDIFF_MAX             INT32_MAX
#endif
#if (_MIPS_SZLONG == 64)
#define PTRDIFF_MIN             INT64_MIN
#define PTRDIFF_MAX             INT64_MAX
#endif

#define SIG_ATOMIC_MIN          INT32_MIN
#define SIG_ATOMIC_MAX          INT32_MAX

#if (_MIPS_SZLONG == 32)
#define SIZE_MAX                UINT32_MAX
#endif
#if (_MIPS_SZLONG == 64)
#define SIZE_MAX                UINT64_MAX
#endif

#define WCHAR_MIN               INT32_MIN
#define WCHAR_MAX               INT32_MAX

#define WINT_MIN                INT32_MIN
#define WINT_MAX                INT32_MAX

/* C99: 7.18.4.1 : Macros for minimum-width integer constants */

#define INT8_C(x)               (int_least8_t)(x)
#define INT16_C(x)              (int_least16_t)(x)
#define INT32_C(x)              (int_least32_t)(x)
#define INT64_C(x)              (int_least64_t)(x)

#define UINT8_C(x)              (uint_least8_t)(x)
#define UINT16_C(x)             (uint_least16_t)(x)
#define UINT32_C(x)             (uint_least32_t)(x)
#define UINT64_C(x)             (uint_least64_t)(x)

/* C99: 7.18.4.2 : Macros for greatest-width integer constants */

#define INTMAX_C(x)             (intmax_t)(x)
#define UINTMAX_C(x)            (uintmax_t)(x)

#endif /* __c99 */

#endif /* __STDINT_H__ */
