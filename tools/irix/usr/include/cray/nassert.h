/* USMID @(#) clibinc/cray/nassert.h	92.0	10/08/98 14:28:05 */
/*
 *	(C) COPYRIGHT CRAY RESEARCH, INC.
 *	UNPUBLISHED PROPRIETARY INFORMATION.
 *	ALL RIGHTS RESERVED.
 */

/*
 *	This header file allows assertions to be defined with assertion
 *	checking turned off by default.   To activate assertion checking,
 *	the _ASSERT_ON macro must be defined.
 */

#ifndef _ASSERT_ON
#define NDEBUG	1	/* deactivate assertion checking by default */
#endif

#include <assert.h>
