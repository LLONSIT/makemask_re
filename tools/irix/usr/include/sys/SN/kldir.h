/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1992-1997, Silicon Graphics, Inc.          *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 **************************************************************************/

#ifndef __SYS_SN_KLDIR_H__
#define __SYS_SN_KLDIR_H__

#ident "$Revision: 1.23 $"

/*
 * The kldir memory area resides at a fixed place in each node's memory and
 * provides pointers to most other SN0 memory areas.  This allows us to
 * resize and/or relocate memory areas at a later time without breaking all
 * firmware and kernels that use them.  Indices in the array are
 * permanently dedicated to areas listed below.  Some memory areas (marked
 * below) reside at a permanently fixed location, but are included in the
 * directory for completeness.
 */

#define KLDIR_MAGIC		0x434d5f53505f5357

#ifdef LANGUAGE_ASSEMBLY
#define KLDIR_OFF_MAGIC			0x00
#define KLDIR_OFF_OFFSET		0x08
#define KLDIR_OFF_POINTER		0x10
#define KLDIR_OFF_SIZE			0x18
#define KLDIR_OFF_COUNT			0x20
#define KLDIR_OFF_STRIDE		0x28
#endif /* LANGUAGE_ASSEMBLY */

#ifdef _LANGUAGE_C
typedef struct kldir_ent_s {
	__uint64_t	magic;		/* Indicates validity of entry      */
	off_t		offset;		/* Offset from start of node space  */
	__psunsigned_t	pointer;	/* Pointer to area in some cases    */
	size_t		size;		/* Size in bytes 		    */
	__uint64_t	count;		/* Repeat count if array, 1 if not  */
	size_t		stride;		/* Stride if array, 0 if not        */
	char		rsvd[16];	/* Pad entry to 0x40 bytes          */
	/* NOTE: These 16 bytes are used in the Partition KLDIR
	   entry to store partition info. Refer to klpart.h for this. */
} kldir_ent_t;
#endif /* _LANGUAGE_C */

#define KLDIR_ENT_SIZE			0x40
#define KLDIR_MAX_ENTRIES		(0x400 / 0x40)

/*
 * The actual offsets of each memory area are machine-dependent
 */
#ifdef SN0
#include <sys/SN/SN0/kldir.h>
#elif defined(SN1)
#include <sys/SN/SN1/kldir.h>
#else
#error "kldir.h is currently defined for SN0 and SN1 platforms only"
#endif

#endif /* __SYS_SN_KLDIR_H__ */
