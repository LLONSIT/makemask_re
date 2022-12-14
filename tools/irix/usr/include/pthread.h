#ifndef _PTHREAD_H_
#define _PTHREAD_H_


/**************************************************************************
 *									  *
 * 		 Copyright (C) 1996 Silicon Graphics, Inc.		  *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/

/*
 * POSIX 1C Threads header file
 */
#include <standards.h>
#ifndef	_POSIX1C
#define _POSIX1C	1
#endif

#ifndef	_SGI_MP_SOURCE
#define _SGI_MP_SOURCE
#endif

#include <sys/types.h>
#include <time.h>
#include <sched.h>
#include <sys/pthread.h>
#include <internal/sgimacros.h>

__SGI_LIBC_BEGIN_EXTERN_C

#if _SGIAPI && !defined(errno)
#define errno	(*__oserror())		/* use threadsafe definition */
extern int	*__oserror(void);
#endif


#define PTHREAD_PROCESS_SHARED	0
#define PTHREAD_PROCESS_PRIVATE	1


/*
 * Threads
 */

/* Thread creation attributes
 */
#define _POSIX_THREAD_ATTR_STACKSIZE	1
#define _POSIX_THREAD_ATTR_STACKADDR	1
int pthread_attr_init(pthread_attr_t *);
int pthread_attr_destroy(pthread_attr_t *);
int pthread_attr_setstacksize(pthread_attr_t *, size_t);
int pthread_attr_getstacksize(const pthread_attr_t *, size_t *);
int pthread_attr_setstackaddr(pthread_attr_t *, void *);
int pthread_attr_getstackaddr(const pthread_attr_t *, void **);
int pthread_attr_setguardsize(pthread_attr_t *, size_t);
int pthread_attr_getguardsize(const pthread_attr_t *, size_t *);
int pthread_attr_setdetachstate(pthread_attr_t *, int);
int pthread_attr_getdetachstate(const pthread_attr_t *, int *);

#define PTHREAD_CREATE_JOINABLE	0
#define PTHREAD_CREATE_DETACHED	1

/* Thread scheduling attributes
 */
#define _POSIX_THREAD_PRIORITY_SCHEDULING	1
int pthread_attr_setscope(pthread_attr_t *, int);
int pthread_attr_getscope(const pthread_attr_t *, int *);
int pthread_attr_setinheritsched(pthread_attr_t *, int);
int pthread_attr_getinheritsched(const pthread_attr_t *, int *);
int pthread_attr_setschedpolicy(pthread_attr_t *, int);
int pthread_attr_getschedpolicy(const pthread_attr_t *, int *);
int pthread_attr_setschedparam(pthread_attr_t *, const struct sched_param *);
int pthread_attr_getschedparam(const pthread_attr_t *, struct sched_param *);

#define PTHREAD_SCOPE_PROCESS	0
#define PTHREAD_SCOPE_SYSTEM	1
#define PTHREAD_SCOPE_BOUND_NP	2

#define PTHREAD_EXPLICIT_SCHED	0
#define PTHREAD_INHERIT_SCHED	1

/* Thread creation and control
 */
int pthread_create(pthread_t *, const pthread_attr_t *, void *(*)(void *), void *);
int pthread_join(pthread_t, void **);
int pthread_detach(pthread_t);
void pthread_exit(void *);
pthread_t pthread_self(void);
int pthread_equal(pthread_t, pthread_t);
#define pthread_equal(t1, t2) ((t1) == (t2))

int pthread_once(pthread_once_t *, void (*)(void));
#define PTHREAD_ONCE_INIT	0

/* Thread scheduling control
 */
int pthread_getschedparam(pthread_t, int *, struct sched_param *);
int pthread_setschedparam(pthread_t, int, const struct sched_param *);
int pthread_getconcurrency(void);
int pthread_setconcurrency(int);
int pthread_getrunon_np(int *);
int pthread_setrunon_np(int);

/* Thread cancellation
 */
int pthread_cancel(pthread_t);
int pthread_setcancelstate(int, int *);
int pthread_setcanceltype(int, int *);
void pthread_testcancel(void);

struct __pthread_cncl_hdlr	**__pthread_cancel_list(void);
struct __pthread_cncl_hdlr {
	struct __pthread_cncl_hdlr	*__ptch_next;
	void				(*__ptch_func)(void *);
	void				*__ptch_arg;
};

#define pthread_cleanup_push(func, arg)			\
{	/* start of cleanup scope */			\
	struct __pthread_cncl_hdlr __ptch;		\
	struct __pthread_cncl_hdlr **__ptch_list;	\
	__ptch.__ptch_func = func;			\
	__ptch.__ptch_arg = arg;			\
	__ptch_list = __pthread_cancel_list();		\
	__ptch.__ptch_next = *__ptch_list;		\
	*__ptch_list = &__ptch

#define pthread_cleanup_pop(exec)				\
	*__ptch_list = __ptch.__ptch_next;			\
	if (exec) {						\
		(*__ptch.__ptch_func)(__ptch.__ptch_arg);	\
	}							\
}	/* end of cleanup scope */

#define PTHREAD_CANCELED		((void *)(1L))

#define PTHREAD_CANCEL_DISABLE		0
#define PTHREAD_CANCEL_ENABLE		1
#define PTHREAD_CANCEL_ASYNCHRONOUS	0
#define PTHREAD_CANCEL_DEFERRED		1


/*
 * Mutexes
 */

/* Mutex initialisation attributes
 */
int pthread_mutexattr_init(pthread_mutexattr_t *);
int pthread_mutexattr_destroy(pthread_mutexattr_t *);
int pthread_mutexattr_getpshared(const pthread_mutexattr_t *, int *);
int pthread_mutexattr_setpshared(pthread_mutexattr_t *, int);

/* Mutex scheduling attributes
 */
int pthread_mutexattr_setprotocol(pthread_mutexattr_t *, int);
int pthread_mutexattr_getprotocol(const pthread_mutexattr_t *, int *);
int pthread_mutexattr_setprioceiling(pthread_mutexattr_t *, int);
int pthread_mutexattr_getprioceiling(const pthread_mutexattr_t *, int *);

#define _POSIX_THREAD_PRIO_INHERIT	1
#define _POSIX_THREAD_PRIO_PROTECT	1
#define PTHREAD_PRIO_NONE	0	/* priority unaffected */
#define PTHREAD_PRIO_INHERIT	1	/* priority inheritance */
#define PTHREAD_PRIO_PROTECT	2	/* priority ceiling */
#define PTHREAD_PRIO_THREAD_NP	3	/* thread non-preemptible */
#define PTHREAD_PRIO_SYSTEM_NP	4	/* system non-preemptible */

/* Mutex type attributes
 */
int pthread_mutexattr_settype(pthread_mutexattr_t *, int);
int pthread_mutexattr_gettype(const pthread_mutexattr_t *, int *);

#define PTHREAD_MUTEX_NORMAL            0
#define PTHREAD_MUTEX_ERRORCHECK        1
#define PTHREAD_MUTEX_RECURSIVE         2
#define PTHREAD_MUTEX_DEFAULT           3
#define PTHREAD_MUTEX_SPINBLOCK_NP	4

/* Mutex creation and control
 */
int pthread_mutex_init(pthread_mutex_t *, const pthread_mutexattr_t *);
int pthread_mutex_destroy(pthread_mutex_t *);

int pthread_mutex_lock(pthread_mutex_t *);
int pthread_mutex_trylock(pthread_mutex_t *);
int pthread_mutex_unlock(pthread_mutex_t *);

#define PTHREAD_MUTEX_INITIALIZER	{ 0 }

/* Mutex scheduling control
 */
int pthread_mutex_setprioceiling(pthread_mutex_t *, int, int *);
int pthread_mutex_getprioceiling(const pthread_mutex_t *, int *);


/*
 * Condition Variables
 */

/* Condition variable initialization attributes
 */
int pthread_condattr_init(pthread_condattr_t *);
int pthread_condattr_destroy(pthread_condattr_t *);
int pthread_condattr_getpshared(const pthread_condattr_t *, int *);
int pthread_condattr_setpshared(pthread_condattr_t *, int);

/* Condition variable operations
 */
int pthread_cond_init(pthread_cond_t *, const pthread_condattr_t *);
int pthread_cond_destroy(pthread_cond_t *);

int pthread_cond_signal(pthread_cond_t *);
int pthread_cond_broadcast(pthread_cond_t *);
int pthread_cond_wait(pthread_cond_t *, pthread_mutex_t *);
int pthread_cond_timedwait(pthread_cond_t *, pthread_mutex_t *,
			   const struct timespec *);

#define PTHREAD_COND_INITIALIZER	{ 0 }


/*
 * Read-write locks
 */

/* Read-write lock initialization attributes
 */
int pthread_rwlockattr_init(pthread_rwlockattr_t *);
int pthread_rwlockattr_destroy(pthread_rwlockattr_t *);
int pthread_rwlockattr_getpshared(const pthread_rwlockattr_t *, int *);
int pthread_rwlockattr_setpshared(pthread_rwlockattr_t *, int);

/* Read-write lock creation and control
 */
int pthread_rwlock_init(pthread_rwlock_t *, const pthread_rwlockattr_t *);
int pthread_rwlock_destroy(pthread_rwlock_t *);

int pthread_rwlock_rdlock(pthread_rwlock_t *);
int pthread_rwlock_tryrdlock(pthread_rwlock_t *);
int pthread_rwlock_wrlock(pthread_rwlock_t *);
int pthread_rwlock_trywrlock(pthread_rwlock_t *);
int pthread_rwlock_unlock(pthread_rwlock_t *);

#define PTHREAD_RWLOCK_INITIALIZER	{ 0 }


/*
 * Thread-specific data
 */

int pthread_key_create(pthread_key_t *, void (*)(void *));
int pthread_setspecific(pthread_key_t, const void *);
void *pthread_getspecific(pthread_key_t);
int pthread_key_delete(pthread_key_t);


/*
 * Barriers
 */
#define PTHREAD_BARRIER_SERIAL_THREAD (-1) /* Arbitrary non-errno # */

int pthread_barrierattr_destroy(pthread_barrierattr_t *);
int pthread_barrierattr_init(pthread_barrierattr_t *);
int pthread_barrierattr_setpshared(pthread_barrierattr_t *, int);
int pthread_barrierattr_getpshared(pthread_barrierattr_t *, int *);
int pthread_barrier_init(pthread_barrier_t *,
			    const pthread_barrierattr_t *, unsigned int);
int pthread_barrier_wait(pthread_barrier_t *);
int pthread_barrier_destroy(pthread_barrier_t *);

#pragma optional pthread_barrierattr_destroy
#pragma optional pthread_barrierattr_init
#pragma optional pthread_barrierattr_setpshared
#pragma optional pthread_barrierattr_getpshared
#pragma optional pthread_barrier_init
#pragma optional pthread_barrier_wait
#pragma optional pthread_barrier_destroy

/*
 * Spin locks
 */
int pthread_spin_destroy(pthread_spinlock_t *);
int pthread_spin_init(pthread_spinlock_t *, int);
int pthread_spin_lock(pthread_spinlock_t *);
int pthread_spin_trylock(pthread_spinlock_t *);
int pthread_spin_unlock(pthread_spinlock_t *);

#pragma optional pthread_spin_destroy
#pragma optional pthread_spin_init
#pragma optional pthread_spin_lock
#pragma optional pthread_spin_trylock
#pragma optional pthread_spin_unlock

/*
 * Miscellaneous
 */



__SGI_LIBC_END_EXTERN_C

#endif /* !_PTHREAD_H_ */
