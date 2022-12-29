/* Copyright (c) 2000, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED
 *
 * UNPUBLISHED -- Rights reserved under the copyright laws of the United
 * States.   Use of a copyright notice is precautionary only and does not
 * imply publication or disclosure.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to
 * restrictions as set forth in FAR 52.227.19(c)(2) or subparagraph
 * (c)(1)(ii) of the Rights in Technical Data and Computer Software clause
 * at DFARS 252.227-7013 and/or in similar or successor clauses in the FAR,
 * or the DOD or NASA FAR Supplement.  Contractor/manufacturer is
 * Silicon Graphics, Inc., 2011 N. Shoreline Blvd. Mountain View,
 * CA 94039-7311.
 *
 * THE CONTENT OF THIS WORK CONTAINS CONFIDENTIAL AND PROPRIETARY
 * INFORMATION OF SILICON GRAPHICS, INC. ANY DUPLICATION, MODIFICATION,
 * DISTRIBUTION, OR DISCLOSURE IN ANY FORM, IN WHOLE, OR IN PART, IS
 * STRICTLY PROHIBITED WITHOUT THE PRIOR EXPRESS WRITTEN PERMISSION OF
 * SILICON GRAPHICS, INC.
 *
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Portions of code used herein are governed by the following license(s).
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 2000 Marc Alexander Lehmann <pcg@goof.com>
 * 
 * Redistribution and use in source and binary forms, with or without modifica-
 * tion, are permitted provided that the following conditions are met:
 * 
 *   1.  Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 * 
 *   2.  Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 * 
 *   3.  The name of the author may not be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MER-
 * CHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO
 * EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPE-
 * CIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTH-
 * ERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _COMPRESSION_H
#define _COMPRESSION_H

#include <sys/types.h>

/*
 * This number should be incremented if additional drivers are added.
 */

#define CL_VERSION		1

/*
 * The following compression/uncompression drivers are available.
 * They are specified as an argument to the compress()/uncompress()
 * calls.
 */

#define CL_NUM_TYPES		5

#define CL_TYPE_RLE1		0
#define CL_TYPE_RLE4		1
#define CL_TYPE_RLE8		2
#define CL_TYPE_LZF		3
#define CL_TYPE_ZP		4

/*
 * These are the public entry points to the compression library.
 */

/*
 * int compression_init(void **cptr, void *scratch, size_t len, uint_t cookie)
 *
 * Arguments:
 *   cptr      Pointer to memory to receive pointer to library cookie.
 *             Allocated by library if memory contents are NULL, otherwise
 *             memory should point to CL_COOKIE_SIZE area to receive
 *             cookie contents.
 *   scratch   Pointer to memory area used as scratch space. If NULL,
 *             scratch is allocated by library. The caller should be
 *             able to sleep if scratch is not supplied.
 *   len       Size of the scratch area (if supplied). Must be at least
 *             CL_MIN_SCRATCH.
 *   cookie    Optional tracking ID used by caller. Can be retrieved by
 *             compression_get_cookie().
 * 
 * Returns -errno on failure.
 */

int compression_init(void **, void *, size_t, uint_t);

/*
 * int compression_end(void *cptr)
 *
 * Arguments:
 *   cptr       Pointer to cookie created with compression_init(). The
 *              cookie and scratch area are not freed if they were
 *              supplied by the caller to compression_init().
 *
 * Returns -errno on failure.
 */

int compression_end(void *);

/*
 * ssize_t compress(void *cptr, int type, void *in, void *out, size_t len)
 *
 * Arguments:
 *   cptr        Pointer to cookie created with compression_init().
 *   type        Type of compression to use. See above.
 *   in          Pointer to buffer to compress.
 *   out         Pointer to buffer to receive compressed data.
 *   len         Length of buffers. They are assumed to be equal in size.
 *
 * Returns size of compressed data, -errno on failure. -ENOSPC returned
 * if compressed length exceeds buffer size.
 */

ssize_t compress(void *, int, void *, void *, size_t);

/*
 * int uncompress(void *cptr, int type, void *in, void *out,
 *                size_t ilen, size_t *olen)
 *
 * Arguments:
 *   cptr        Pointer to cookie created with compression_init().
 *   type        Type of compression used. See above.
 *   in          Pointer to buffer containing compressed data.
 *   out         Pointer to buffer to receive uncompressed output.
 *   ilen        Size of compressed data.
 *   olen        Pointer to size of out buffer. Returns decompressed size.
 *
 * Returns -errno on failure. -EIO returned if compressed data corrupted.
 */

int uncompress(void *, int, void *, void *, size_t, size_t *);

/*
 * uint_t compression_get_cookie(void *cptr)
 *
 * Arguments:
 *   cptr         Pointer to cookie created with compression_init().
 *
 * Returns the cookie value passed to compression_init().
 */

uint_t compression_get_cookie(void *);

/*
 * The cookie is used internally in the compression library to track
 * the required information. Normally it is allocated by
 * compression_init() and is handled by users of the library as a
 * void *. It is provided here however for those cases that
 * it's preallocated by the user of the library and should not
 * be allocated by the library.
 */

typedef struct {
	uint_t  cl_cookie;
	void   *cl_scratch;
	int     cl_flags;
} cl_cookie_t;

#define CL_COOKIE_SIZE		(sizeof(cl_cookie_t))
#define CL_MIN_SCRATCH_SHFT	(12)
#define CL_MIN_SCRATCH		((1 << CL_MIN_SCRATCH_SHFT)*sizeof(void *))

#endif /* _COMPRESSION_H */
