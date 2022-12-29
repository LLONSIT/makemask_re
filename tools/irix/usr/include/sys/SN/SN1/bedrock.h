/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1992-1998, Silicon Graphics, Inc.          *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 **************************************************************************/

#ifndef __SYS_SN_SN1_BEDROCK_H__
#define __SYS_SN_SN1_BEDROCK_H__

/* The secret password; used to release protection */
#define HUB_PASSWORD		0x53474972756c6573ull

#define CHIPID_HUB		0x3012
#define CHIPID_ROUTER		0x3017

#define BEDROCK_REV_1_0		1
#define BEDROCK_REV_1_1		2

#define MAX_HUB_PATH		80

#if defined(IP35)
#include <sys/SN/arch.h>
#include <sys/SN/SN1/addrs.h>
#include <sys/SN/SN1/hubpi.h>
#include <sys/SN/SN1/hubmd.h>
#include <sys/SN/SN1/hubio.h>
#include <sys/SN/SN1/hubni.h>
#include <sys/SN/SN1/hublb.h>
#include <sys/SN/SN1/hubxb.h>
#include <sys/SN/SN1/hubpi_next.h>
#include <sys/SN/SN1/hubmd_next.h>
#include <sys/SN/SN1/hubio_next.h>
#include <sys/SN/SN1/hubni_next.h>
#include <sys/SN/SN1/hublb_next.h>
#include <sys/SN/SN1/hubxb_next.h>
#include <sys/SN/SN1/bdrkhspecregs.h>
#include <sys/SN/SN1/bdrkhspecregs_next.h>

#if defined(SABLE) || defined(DIRECT_L1_CONSOLE)
#define IP27_NO_HUBUART_INT	1
#endif

#else /* ! IP35 */

<< BOMB! SN1 is only defined for IP35 >>

#endif /* defined(IP35) */

/* Translation of uncached attributes */
#define	UATTR_HSPEC	0
#define	UATTR_IO	1
#define	UATTR_MSPEC	2
#define	UATTR_UNCAC	3

#if _LANGUAGE_ASSEMBLY

/*
 * Get nasid into register, r (uses at)
 */
#define GET_NASID_ASM(r)				\
	dli	r, LOCAL_HUB_ADDR(LB_REV_ID);	\
	ld	r, (r);					\
	and	r, LRI_NODEID_MASK;			\
	dsrl	r, LRI_NODEID_SHFT

#endif /* _LANGUAGE_ASSEMBLY */

#if _LANGUAGE_C

#include <sys/xtalk/xwidget.h>
#include <sys/sema.h>

/* hub-as-widget iograph info, labelled by INFO_LBL_XWIDGET */
typedef struct v_hub_s *v_hub_t;
typedef __uint64_t      rtc_time_t;

struct nodepda_s;
int hub_check_pci_equiv(void *addra, void *addrb);
void capture_hub_stats(cnodeid_t, struct nodepda_s *);
void init_hub_stats(cnodeid_t, struct nodepda_s *);

/*
 * The kernel flags register is used to pass kernel state information
 * when the kernel is running. This register should not overlap anything
 * that another partition may need during it's boot sequence.
 * For SN1 the MD_BIST_DATA register is not used after the local
 * partition has finished booting.
 */
 
#define LB_KERNEL_FLAGS		MD_BIST_DATA

#define LB_KFLAGS_PANIC_SHFT	0	/* set when the system is panic'ing */
#define LB_KFLAGS_PANIC		1<<LB_KFLAGS_PANIC_SHFT

#endif /* _LANGUAGE_C */

#endif /* __SYS_SN_SN1_BEDROCK_H__ */
