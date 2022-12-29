
#ifndef __OMP_H__
#define __OMP_H__

#ident "$Revision: 1.2 $"

/*
*
* Copyright 1998 Silicon Graphics, Inc.
* All Rights Reserved.
*
* This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics, Inc.;
* the contents of this file may not be disclosed to third parties, copied or
* duplicated in any form, in whole or in part, without the prior written
* permission of Silicon Graphics, Inc.
*
* RESTRICTED RIGHTS LEGEND:
* Use, duplication or disclosure by the Government is subject to restrictions
* as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data
* and Computer Software clause at DFARS 252.227-7013, and/or in similar or
* successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -
* rights reserved under the Copyright Laws of the United States.
*/

#ifdef __cplusplus
extern "C" {
#endif

typedef int *omp_lock_t;
typedef int *omp_nest_lock_t;

void    omp_set_num_threads (int _Num_Threads);
int     omp_get_num_threads (void);
int     omp_get_max_threads (void);
int     omp_get_thread_num  (void);
int     omp_get_num_procs   (void);
int     omp_in_parallel     (void);
void    omp_set_dynamic     (int _Dynamic_Threads);
int     omp_get_dynamic     (void);
void    omp_set_nested      (int _Nested);
int     omp_get_nested      (void);

void    omp_init_lock       (omp_lock_t *_Lock);
void    omp_destroy_lock    (omp_lock_t *_Lock);
void    omp_set_lock        (omp_lock_t *_Lock);
void    omp_unset_lock      (omp_lock_t *_Lock);
int     omp_test_lock       (omp_lock_t *_Lock);

#pragma intrinsic (omp_set_lock, omp_unset_lock, omp_test_lock)

void    omp_init_nest_lock      (omp_nest_lock_t *_Lock);
void    omp_destroy_nest_lock   (omp_nest_lock_t *_Lock);
void    omp_set_nest_lock       (omp_nest_lock_t *_Lock);
void    omp_unset_nest_lock     (omp_nest_lock_t *_Lock);
int     omp_test_nest_lock      (omp_nest_lock_t *_Lock);

#pragma intrinsic (omp_set_nest_lock, omp_unset_nest_lock, omp_test_nest_lock)

double  omp_get_wtime   (void);
double  omp_get_wtick   (void);

#ifdef __cplusplus
}
#endif
#endif /* __OMP_H__ */
