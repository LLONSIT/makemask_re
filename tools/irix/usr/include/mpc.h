#ifndef __MPC_H__
#define __MPC_H__

/* 
 * =============================================================
 * Copyright 1997 Silicon Graphics,  Inc.
 * ALL RIGHTS RESERVED
 * 
 * THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF SGI
 * The copyright notice above does not evidence any  actual  or
 * intended  publication of this source code and material is an
 * unpublished work by Silicon  Graphics,  Inc.  This  material
 * contains CONFIDENTIAL INFORMATION that is the property and a
 * trade secret of Silicon Graphics, Inc. Any use,  duplication
 * or  disclosure  not  specifically  authorized  in writing by
 * Silicon Graphics is  strictly  prohibited.  THE  RECEIPT  OR
 * POSSESSION  OF  THIS SOURCE CODE AND/OR INFORMATION DOES NOT
 * CONVEY ANY RIGHTS TO REPRODUCE, DISCLOSE OR  DISTRIBUTE  ITS
 * CONTENTS,  OR  TO MANUFACTURE, USE, OR SELL ANYTHING THAT IT
 * MAY DESCRIBE, IN WHOLE OR IN PART.
 * 
 * PURPOSE OF THIS FILE:
 * ---------------------
 *
 * This header file provides the prototypes for functions within 
 * the MP runtime library, and invoked by parallel C and C++ 
 * programs written using the Power C parallel directives.
 *
 * =============================================================
 */

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

unsigned mpc_my_threadnum (void);

unsigned mpc_my_threadnum (void);

unsigned mpc_numthreads (void);

unsigned mpc_maxnumthreads (void);

void mpc_set_schedtype (int);

void mpc_set_chunksize (int);

void mpc_set_numthreads (int);

void mpc_create (int);

void mpc_destroy (void);

void mpc_synchronize_memory (void);

int mpc_my_regionthreadnum (void*);

void mp_block (void);

void mp_unblock (void);

void mp_blocktime (int iters);

void mp_setup (void);

void mp_create (int num);

void mp_destroy (void);

int mp_numthreads (void);

void mp_set_numthreads (int num);

int mp_my_threadnum (void);

int mp_is_master (void);

void mp_setlock (void);

void mp_unsetlock (void);

void mp_barrier (void);

int mp_in_doacross_loop (void);

void mp_set_slave_stacksize (size_t size);

size_t mp_get_slave_stacksize (void);

#ifdef __cplusplus
}
#endif

#endif /* !__MPC_H__ */
