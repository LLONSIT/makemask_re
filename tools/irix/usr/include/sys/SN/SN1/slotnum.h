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

#ifndef __SYS_SN_SN1_SLOTNUM_H__
#define __SYS_SN_SN1_SLOTNUM_H__

#define SLOTNUM_MAXLENGTH	16

/*
 * This file defines IO widget to slot/device assignments for SN-MIPS
 * systems.
 */

#include <sys/slotnum.h>

/* This determines module to pnode mapping. */

#define NODESLOTS_PER_MODULE		1
#define NODESLOTS_PER_MODULE_SHFT	1

#if _KERNEL
#include <sys/xtalk/xtalk.h>

extern void get_slotname(slotid_t, char *);
extern slotid_t get_widget_slotnum(int xbow, int widget, char bt);
extern void get_widget_slotname(int, int, char, char *);

/* IO_SLOT_NUM is widget ID in SN1 */
#define MAX_IO_SLOT_NUM		15

#endif /* _KERNEL */

#endif /* __SYS_SN_SN1_SLOTNUM_H__ */

