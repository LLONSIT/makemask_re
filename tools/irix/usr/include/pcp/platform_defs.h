/*
 * Copyright (c) 1997,2004 Silicon Graphics, Inc.  All Rights Reserved.
 *
 * $Id: platform_defs.h.irix,v 1.8 2006/06/07 03:02:02 makc.longdrop.melbourne.sgi.com Exp $
 */

/*-----------------------------------------------------------------------
 * from here on down (except postscript) this is platform_defs.h
 * made by ../../configure on IRIX
 *-----------------------------------------------------------------------
 */

#ifndef _PLATFORM_DEFS_H
#define _PLATFORM_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>

/*
 * The type of timestamps in struct stat: either HAVE_STAT_TIMESPEC,
 * HAVE_STAT_TIMESTRUC or HAVE_STAT_TIME_T
 */
#define HAVE_STAT_TIMESPEC_T 1
/* #undef HAVE_STAT_TIMESTRUC */
/* #undef HAVE_STAT_TIMESPEC */
/* #undef HAVE_STAT_TIME_T */

/* HAVE_ST_MTIME if stat.st_mtime has a ``spec'' on the end */
/* #undef HAVE_ST_MTIME_WITH_SPEC */

/* HAVE_ST_MTIME if stat.st_mtime has an ``e'' on the end */
/* #undef HAVE_ST_MTIME_WITH_E */

/* if your compiler supports LL sufix on 64 bit int constants */
#define HAVE_CONST_LONGLONG 1

/*
 * HAVE_UNDERBAR_ENVIRON if extern char **_environ is defined
 * (else extern char **environ will be used)
 */
/* #undef HAVE_UNDERBAR_ENVIRON */

/*
 * If the pointer-to-function arguments to scandir()
 * are (*scanfn)(const struct dirent *dep)
 * Otherwise ``const'' will be omitted.
 */
/* #undef HAVE_CONST_DIRENT */

/*
 * If getopt() needs $POSIXLY_CORRECT set in the environment to work
 * correctly, specifically to not treat -x as an option when foo is
 * invoked with the arguments "arg -x"
 */
/* #undef HAVE_GETOPT_NEEDS_POSIXLY_CORRECT */

/* Defined if printf %p -> 0x prefix for value */
/* #undef HAVE_PRINTF_P_PFX */
#ifdef HAVE_PRINTF_P_PFX
#define PRINTF_P_PFX ""
#else
#define PRINTF_P_PFX "0x"
#endif

/* Defined if bit fields are allocated left-to-right within a word */
#define HAVE_BITFIELDS_LTOR 1

/* if compiler can cast __uint64_t to double */
#define HAVE_CAST_U64_DOUBLE 1

/* long and pointer must be either 32 bit or 64 bit */
/* #undef HAVE_64BIT_LONG */
#define HAVE_32BIT_LONG 1
#define HAVE_32BIT_PTR 1
/* #undef HAVE_64BIT_PTR */

/* Define if header file is available */
#define HAVE_FCNTL_H 1
#define HAVE_LIMITS_H 1
#define HAVE_MALLOC_H 1
#define HAVE_STRINGS_H 1
#define HAVE_SYS_TIME_H 1
#define HAVE_SYSLOG_H 1
#define HAVE_UNISTD_H 1
#define HAVE_SCHED_H 1
#define HAVE_TERMIOS_H 1
#define HAVE_DLFCN_H 1
/* #undef HAVE_DL_H */
#define HAVE_IEEEFP_H 1
/* #undef HAVE_ENDIAN_H */
#define HAVE_STANDARDS_H 1
/* #undef HAVE_SYS_BYTEORDER_H */
#define HAVE_PTHREAD_H 1
#define HAVE_GETOPT_H 1
#define HAVE_VALUES_H 1
#define HAVE_LIBGEN_H 1
#define HAVE_SGIDEFS_H 1
#define HAVE_ABI_MUTEX_H 1
#define HAVE_NDBM_H 1
#define HAVE_SYS_PARAM_H 1
#define HAVE_NETDB_H 1
#define HAVE_SYS_TERMIOS_H 1
/* #undef HAVE_STDINT_H */

#define HAVE_SYS_ENDIAN_H 1

#if defined(HAVE_MALLOC_H)
#include <malloc.h>
#else
/* #undef ptrdiff_t */
#define ptrdiff_t	long
#endif

/* HAVE_NETWORK_BYTEORDER for big endian systems (not Intel) */
#if defined(HAVE_ENDIAN_H)
#include <endian.h>
#elif defined(HAVE_SYS_ENDIAN_H)
#include <sys/endian.h>
#endif
#if defined(HAVE_ENDIAN_H) || defined(HAVE_SYS_ENDIAN_H)
#if defined(BYTE_ORDER) && BYTE_ORDER == BIG_ENDIAN
#define HAVE_NETWORK_BYTEORDER
#endif
#endif

#if defined(HAVE_SYS_BYTEORDER_H)
#include <sys/byteorder.h>
#if defined(_BIG_ENDIAN)
#define HAVE_NETWORK_BYTEORDER
#endif
#endif


/* define if libc functions are available */
#define HAVE_GETCWD 1
#define HAVE_GETHOSTNAME 1
#define HAVE_GETTIMEOFDAY 1
#define HAVE_MKTIME 1
#define HAVE_PUTENV 1
#define HAVE_SELECT 1
#define HAVE_SOCKET 1
#define HAVE_STRDUP 1
#define HAVE_STRERROR 1
#define HAVE_STRTOD 1
#define HAVE_STRTOL 1
#define HAVE_UNAME 1
#define HAVE_WAITPID 1
#define HAVE_ATEXIT 1
#define HAVE_READDIR64 1
#define HAVE_WAIT3 1
#define HAVE_SBRK 1
#define HAVE_BRK 1
/* #undef HAVE___CLONE */
#define HAVE_SPROC 1
#define HAVE_SIGNAL 1
#define HAVE_TCGETATTR 1
#define HAVE_HSTRERROR 1
#define HAVE_DLOPEN 1
/* #undef SHL_LOAD */
#define HAVE_ISNANF 1
#define HAVE_ISNAND 1
/* #undef HAVE_SHL */
#define HAVE_SGINAP 1
#define HAVE_USLEEP 1
#define HAVE_OSERROR 1
#define HAVE_SETOSERROR 1
#define HAVE_FLOG10 1
#define HAVE_SIGHOLD 1
#define HAVE_SIGRELSE 1
#define HAVE_PRCTL 1
/* #undef HAVE_REGEX */
/* #undef HAVE_REGCMP */
#define HAVE_REGEXEC 1
#define HAVE_REGCOMP 1
/* #undef HAVE_FLOCK */
/* #undef HAVE_FCNTL */
/* #undef HAVE_CFMAKERAW */
#define HAVE_DIRNAME 1
#define HAVE_BASENAME 1
/* #undef HAVE_UNSETENV */
#define HAVE_VALLOC 1
#define HAVE_MEMALIGN 1
#define HAVE_STRTOLL 1
#define HAVE_STRTOULL 1
#define HAVE_NANOSLEEP 1
#define HAVE_MKSTEMP 1

#define HAVE_SYSINFO 1

/* if termio signals are supported */
#ifdef HAVE_TERMIOS_H
#ifdef HAVE_TCGETATTR
#define HAVE_TERMIO_SIGNALS
#endif
#endif

/* if the /proc pseudo filesystem exists */
#define HAVE_PROCFS 1

/* if the /proc/pinfo/<pid> should be used (IRIX only?) */
#define HAVE_PROCFS_PINFO 1

#ifndef ULONGLONG_MAX
#define ULONGLONG_MAX (__uint64_t)18446744073709551615ULL
#endif

#ifndef LONGLONG_MAX
#define LONGLONG_MAX (__int64_t)9223372036854775807LL
#endif

/* some types only known by some compilers */
/* #undef uint_t */
/* #undef __int32_t */
/* #undef __uint32_t */
/* #undef __int64_t */
/* #undef __uint64_t */

/* Check is __psint_t is set to smth meaningful */
#define HAVE___PSINT_T 1
#ifndef HAVE___PSINT_T
#ifdef HAVE_32BIT_PTR
typedef int __psint_t;
#elif defined HAVE_64BIT_PTR
#ifdef HAVE_64BIT_LONG
typedef long __psint_t;
#else
/* This is a very strange architecture, which has 64 bit pointers but
 * not 64 bit longs. So, I'd just punt here and assume long long is Ok */
typedef long long __psint_t;
#endif
#else
#error Unknown pointer size
#endif
#endif

/*
 * socklen_t is not always defined, so use mysocklen_t as abstraction
 */
#define HAVE_SOCKLEN_T 1
#ifdef HAVE_SOCKLEN_T
#include <sys/types.h>
#include <sys/socket.h>
typedef socklen_t mysocklen_t;
#else
typedef int mysocklen_t;
#endif

/*
 * MAXNAMELEN hides in may places and may have alias names ...
 */
#ifndef MAXNAMELEN
#include <stdio.h>
#ifdef HAVE_SYS_PARAM_H
#include <sys/param.h>
#endif
#if !defined(MAXNAMELEN) && defined(FILENAME_MAX)
/* posix version of the bsd MAXNAMELEN macro */
#define MAXNAMELEN FILENAME_MAX
#endif
#endif
#ifndef MAXNAMELEN
bozo! need to find where MAXNAMELEN is defined for this platform
#endif

/*
 * MAXPATHLEN hides in may places and may have alias names ...
 */
#ifndef MAXPATHLEN
#ifdef HAVE_SYS_PARAM_H
#include <sys/param.h>
#endif
#ifdef HAVE_LIMITS_H
#include <limits.h>
#endif
#if !defined(MAXPATHLEN) && defined(PATH_MAX)
/* posix version of the bsd MAXPATHLEN macro */
#define MAXPATHLEN PATH_MAX
#endif
#endif
#ifndef MAXPATHLEN
bozo! need to find where MAXPATHLEN is defined for this platform
#endif

/*
 * MAXHOSTNAMELEN hides in may places ...
 */
#ifndef MAXHOSTNAMELEN
#ifdef HAVE_SYS_PARAM_H
#include <sys/param.h>
#endif
#endif
#ifndef MAXHOSTNAMELEN
#ifdef HAVE_LIMITS_H
#include <limits.h>
#endif
#endif
#ifndef MAXHOSTNAMELEN
#ifdef HAVE_NETDB_H
#include <netdb.h>
#endif
#endif
#ifndef MAXHOSTNAMELEN
bozo! need to find where MAXHOSTNAMELEN is defined for this platform
#endif

#ifndef CLK_TCK
#ifdef CLOCKS_PER_SEC
#define CLK_TCK CLOCKS_PER_SEC
#else
#error neither CLK_TCK or CLOCKS_PER_SEC are defined on this platform
#endif
#endif

#ifndef HAVE_SGINAP
#ifdef HAVE_USLEEP
#define sginap(x) ((long)usleep((long)((double)1000000.0 * x / CLK_TCK)),0)
#else
#define sginap(x) sleep(x/CLK_TCK)
#endif
#endif

#ifndef HAVE_OSERROR
#define oserror() errno
#endif

#ifndef HAVE_SETOSERROR
#define setoserror(e) errno = e
#endif

#ifndef HAVE_FLOG10
#if !defined(flog10)
#define flog10(x) (float)log10((double)x)
#endif
#endif

#if !defined(WORD_BIT)
#define WORD_BIT 32
#endif

#define RETSIGTYPE void
#ifndef RETSIGTYPE
#define RETSIGTYPE void
#endif

#define HAVE_SIGPF 1
#ifndef HAVE_SIGPF
/* The return type of signal() */
typedef void (*SIG_PF) (int);
#endif

#define HAVE_SA_SIGINFO 1

#define HAVE_WAIT_INCLUDES_SIGNAL 1
#ifndef HAVE_WAIT_INCLUDES_SIGNAL
#include <signal.h>
#endif

#ifndef HAVE_NDBM_H
#define DBM void
#endif

/* #undef HAVE_PR_TERMCHILD */
/* #undef HAVE_PR_SET_PDEATHSIG */

#define HAVE_PTHREAD_MUTEX_T 1

#define HAVE_FNDELAY 1
#if !defined(HAVE_FNDELAY)
/* Only Solaris is known to need this so far */
#ifndef FNDELAY
#define FNDELAY O_NDELAY
#endif
#endif

#define HAVE_ALTZONE 1
/* #undef HAVE_STRFTIME_z */

#ifndef HAVE_VALLOC
#define valloc(x) malloc(x)
#endif

/* Determine if we are on an IRIX box */
#define IS_IRIX 1
#ifdef IS_IRIX
/*
 * Parts of pmapi.h and impl.h were moved to the pmapi_mon.h and
 * impl_mon.h to facilitate OpenSource management. This macro controls
 * the inclusion of those files on irix, where they are always present.
 */
#define HAVE_SEPARATE_MONS_H 1

/*
 * still building the V1 versions of the libraries and APIs for IRIX
 * backwards compatibility
 */
#define HAVE_V1_SUPPORT 1

/*
 * do license checking for IRIX
 */
#define HAVE_LICENSE_CHECK 1
#define HAVE_FLEXLM 1

/* we have the *objectStyle functions in libpcp */
#define HAVE_OBJECT_STYLE 1

/* Location of pcplog */
#define PCPLOGDIR "/var/adm/pcplog"
#else	/* ! IS_IRIX */
/*
 * In the Open Source, stuff from libpcp_dev has been moved to libpcp
 * so this is always true
 */
#define HAVE_DEV_IN_LIBPCP 1
#endif	/* IS_IRIX */

/* Determine if we are on a Solaris box */
/* #undef IS_SOLARIS */
#ifdef IS_SOLARIS
#define FLEX_SCANNER	/* Solaris lex needs gram.tab.h */
#endif

/* Determine if we are on a Mac OS X box */
/* #undef IS_DARWIN */
#ifdef IS_DARWIN
#define DLOPEN_NO_WARN
#define st_atim st_atimespec    /* workaround */
#define st_mtim st_mtimespec    /* workaround */
#define st_ctim st_ctimespec    /* workaround */
#define isnand	isnan	/* isnan is a type-independent macro */
#define isnanf	isnan	/* isnan is a type-independent macro */
#endif

/* Determine if we are on a Cygwin box */
/* #undef IS_CYGWIN */

/*
 * Determine if we are on an Interix (aka Windows Services for Unix) box
 *
 * sometimes we have no choice other than to make platform-specific
 * choices at compile time ... sigh
 */
/* #undef IS_INTERIX */
#ifdef IS_INTERIX
/*
 * On Interix, the standard headers are incomplete ...
 */
extern int unsetenv(char *);
#endif

/* Determine if we are on an AIX box */
/* #undef IS_AIX */

#ifdef HAVE_LIBGEN_H
#include <libgen.h>
#endif

/*
 * run-time environment that is in libc for most platforms, but for some
 * we need to provide our own implementation
 */
#ifndef HAVE_DIRNAME
char *dirname(char *);
#endif
#ifndef HAVE_BASENAME
char *basename(char *);
#endif
#ifndef HAVE_ISNAND
int isnand (double);
#endif

/*-----------------------------------------------------------------------
 * postscript this is _not_ from platform_defs.h made by
 * ../../configure on IRIX
 *-----------------------------------------------------------------------
 */

/*
 * IRIX specific platform definitions and features
 */

/*
 * these ones come from the MIPS C complier, not gcc ...
 * long must be either 32 bit or 64 bit, and
 * pointer must be either 32 bit or 64 bit
 */
#undef HAVE_64BIT_LONG
#undef HAVE_32BIT_LONG
#undef HAVE_64BIT_PTR
#undef HAVE_32BIT_PTR
#if _MIPS_SZPTR == 64
#define HAVE_64BIT_LONG 1
#else
#define HAVE_32BIT_LONG 1
#endif
#if _MIPS_SZPTR == 64
#define HAVE_64BIT_PTR 1
#else
#define HAVE_32BIT_PTR 1
#endif

/* on linux, these are in src/include/builddefs.in */
#define CPP_SIMPLE "_RLD_LIST=DEFAULT /lib/cpp"
#define CPP_SIMPLE_ARGS "-Usgi -Uunix -Umips -Ulinux -I."

#ifndef __cplusplus
#define inline __inline
#endif

#ifdef __cplusplus
}
#endif

#endif /* _PLATFORM_DEFS_H */
