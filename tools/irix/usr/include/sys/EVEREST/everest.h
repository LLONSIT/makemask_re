/**************************************************************************
 *									  *
 * 		 Copyright (C) 1992, Silicon Graphics, Inc.		  *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/

/*
 * everest.h -- bus-specific defines for everest boards
 */

#ifndef __SYS_EVEREST_H__
#define __SYS_EVEREST_H__

#ident "$Revision: 1.92 $"

/*
 * Everest system-wide definitions 
 */

#define EV_MAX_SLOTS		16	/* No more than 16 slots in Everest */
#define EV_MAX_CPUS_BOARD	4	/* No more than 4 CPUS per board */

/*
 * Everest System-wide Configuration Limitation Definitions.
 */

#define EV_MAX_IPS		13	/* Cpu boards/system */

/* LARGE_CPU_COUNT_EVEREST compilation flag is used to enable testing of
 * large cpu (>64 cpus) config changes on Everest.  We move all of the odd
 * numbered cpus to odd cpu numbers counted back from 127
 * (i.e. 1->127, 3->125, etc).  This also affects code which uses data in
 * the MPCONF area since there really aren't 128 structures there (we map
 * back to the original number when accessing that table).
 */
#if LARGE_CPU_COUNT_EVEREST
#define EV_MAX_CPUS		128
#define REAL_EV_MAX_CPUS	52
#else	/* !LARGE_CPU_COUNT */
#define EV_MAX_CPUS		52
#endif

#define EV_MAX_MC3S		8
#define EV_MAX_IO4S	     	8	/* restricted by # of windows */
#define EV_MAX_VMEADAPS		5
#define	EV_MAX_HIPADAPS		8
#define EV_MAX_EPCADAPS		3
#define EV_MAX_FCGADAPS		3	/* TBS */
#define EV_MAX_DANGADAPS        12
#define EV_MAX_S1ADAPS		16	/* TBS */

/*
 * Everest board common configuration registers.
 */
#define EV_BOARDENB		0x00	/* board enable */
#define EV_BOARDTYPE		0x01	/* board type */
#define EV_BOARDREVLVL		0x02	/* board revision level */

/* 
 * Values for various CPU board types.
 */
#define EV_IP19_BOARD		0x1	/* IP19 processor board */
#define EV_IP21_BOARD		0x2	/* IP21 processor board */
#define	EV_IP25_BOARD		0x3	/* IP25 processor board */

/*
 * Values for CPU types
 */
#define EV_CPU_R4000		0x1	/* Standard R4000 */
#define EV_CPU_TFP		0x2	/* TFP processor */
#define	EV_CPU_R10000		0x3	/* R10000 (T5) */
#define EV_CPU_NONE		(-1)	/* no cpu present in slot */

#if _LANGUAGE_C && (_KERNEL || _STANDALONE)
/*
 * load_double is still a routine in 64 bit mode on TFP because it implements
 * workarounds. It should be changed to a macro when those workarounds
 * are no longer needed.
 */

extern int load_double_lo(long long *);
extern long long load_double_nowar(long long *);
extern long long load_double_scc(long long *);

#if _MIPS_SIM == _ABI64 && !TFP
#define load_double(reg) *(volatile long long *)(reg)
#else
extern long long load_double(long long *);
#endif
#if _MIPS_SIM == _ABI64
#define store_double(reg, val)	*(volatile long long *)(reg) = (long long)(val)
#else
extern void store_double(long long *, long long);
#endif

#endif /* _LANGUAGE_C && (_KERNEL || _STANDALONE) */

/*
 * Macros to read/write Everest "local" resources.  We use a
 * macro mainly because we want to write endian-insensitive code,
 * but we're not sure that 64-bit reads/writes will be available
 * in time for Everest testing.  This gives us options.   The
 * current implementation assumes 64 bit accesses work and are
 * generated by the comipler whenever possible.
 *
 * Also may be handy for debugging.
 */

#define EV_GET_LOCAL(address) \
	((evreg_t)load_double((long long *)(address)))

#define EV_GET_LOCAL_NOWAR(address) \
	((evreg_t)load_double_nowar((long long *)(address)))

#define EV_SET_LOCAL(address,value)	\
	(store_double((long long *)(address), (long long) value))

#if IP25
#define	EV_GET_SYSCONFIG()	\
        ((evreg_t)load_double_scc((long long *)(EV_SYSCONFIG)))
#else
#define	EV_GET_SYSCONFIG()	\
        EV_GET_LOCAL(EV_SYSCONFIG)
#endif

#if _LANGUAGE_C && _KERNEL
#if	defined(MULTIPLE_CFG_WRITE_WAR) 
extern	lock_t	configLock;
#define	EV_CONFIG_LOCK(s)	s = io_splockspl(configLock, spl7)
#define	EV_CONFIG_UNLOCK(s)	io_spunlockspl(configLock, s)
#define	EV_INTR_LOCK(s)		EV_CONFIG_LOCK(s)
#define	EV_INTR_UNLOCK(s)	EV_CONFIG_UNLOCK(s)
#else 
#define	EV_CONFIG_LOCK(s)
#define	EV_CONFIG_UNLOCK(s)
#define	EV_INTR_LOCK(s)
#define	EV_INTR_UNLOCK(s)
#endif

#if	defined(MC3_CFG_READ_WAR) 
extern lock_t mc3_cfgLock;
extern cpumask_t isolate_cpumask;
extern int ignore_isolated_cpu_warning;       /* mtune/kernel */

extern void k_stop_all_cpus(void);
extern void unstop_all_cpus(void);
extern void special_doacvec(void);
extern int special_trylock(lock_t *, pl_t);
extern void special_unlock(lock_t *, int);

#define	MC3_CONFIG_TRYLOCK(s)			 \
	do {				 	 \
		s = special_trylock(&mc3_cfgLock, spl7); \
		if (s == -1) {				\
			special_doacvec();		\
		}				 \
		else {		 		 \
			break;			 \
		}				 \
	} while (1)
#define	MC3_CONFIG_UNLOCK(s)	special_unlock(&mc3_cfgLock, s)

#define MC3_CFG_LOCK_AND_STOP(ospl)	\
	MC3_CONFIG_TRYLOCK(ospl);		\
        if (isolate_cpumask && !ignore_isolated_cpu_warning)            \
		cmn_err(CE_WARN,"MC3_CFG_READ_WAR encountered isolated cpus"); \
	k_stop_all_cpus()

#define MC3_CFG_UNLOCK_AND_RESUME(ospl) \
	unstop_all_cpus();		\
	MC3_CONFIG_UNLOCK(ospl)

#else

#define	MC3_CONFIG_TRYLOCK(s)
#define	MC3_CONFIG_UNLOCK(s)
#define MC3_CFG_LOCK_AND_STOP(ospl)
#define MC3_CFG_UNLOCK_AND_RESUME(ospl)

#endif	/* MC3_CFG_READ_WAR */

#if	defined(IO4_CFG_READ_WAR) 
extern lock_t io4_cfgLock;
extern int    io4ia_war;
#define	IO4_CONFIG_LOCK(s)	\
	if (io4ia_war) s = io_splockspl(io4_cfgLock, spl7)
#define	IO4_CONFIG_UNLOCK(s)	if (io4ia_war) io_spunlockspl(io4_cfgLock, s)
#else
#define	IO4_CONFIG_LOCK(s)
#define	IO4_CONFIG_UNLOCK(s)
#endif	/* IO4_CFG_READ_WAR */

#endif /* _LANGUAGE_C && _KERNEL */

/*
 * This define lets us obtain high speed access to the RTC even on R8000
 * systems which require the CC bug workaround, since it is really only
 * needed for Configuration registers and the Sense System config register.
 * Also added macro for fast access to EV_HPIL register.
 */
#if TFP_CC_REGISTER_READ_WAR
#define	EV_GET_LOCAL_RTC	\
	((evreg_t)*(volatile long long *)(EV_RTC))
#define	EV_GET_LOCAL_HPIL	\
	((evreg_t)*(volatile long long *)(EV_HPIL))
#else	/* !TFP_CC_REGISTER_READ_WAR */
#define	EV_GET_LOCAL_RTC	EV_GET_LOCAL(EV_RTC)
#define	EV_GET_LOCAL_HPIL	EV_GET_LOCAL(EV_HPIL)
#endif	/* !TFP_CC_REGISTER_READ_WAR */

/*
 * A couple of defines concerning EBUS speed which really
 * shouldn't be hardwired.
 */
#define NSEC_PER_CYCLE		21	/* nanoseconds per bus cycle */
#define CYCLE_PER_SEC		(NSEC_PER_SEC/NSEC_PER_CYCLE)

/*
 * Shift and mask values for SYSCONFIG register.
 */
#define EV_BOARD_MAX	16
#define EV_BOARD_MASK	0x00000000ffff	/* 1 bit for each occupied slot */
#define EV_CPU_MASK	0x0000ffff0000	/* 1 bit for each CPU slot */
#define EV_MEM_MASK	0xffff00000000	/* 1 bit for each memory slot */
#define EV_BOARD_SHFT	0
#define EV_CPU_SHFT	16
#define EV_MEM_SHFT	32

/*
 * Shift and mask values for the interrupt levels in the
 * ILE and CIPL124 registers.
 */
#define EV_EBUSINT_MASK		0x1
#define EV_CMPINT_MASK		0x2
#define EV_UARTINT_MASK		0x4
#define EV_ERTOINT_MASK		0x8
#define EV_WGINT_MASK		0x10
#define EV_EBUSINT_SHFT		0
#define EV_CMPINT_SHFT		1
#define EV_UARTINT_SHFT		2
#define EV_ERTOINT_SHFT		3
#define EV_WGINT_SHFT		4
 

#if _LANGUAGE_C
/*
 * SET and GET configuration register values.  The address to write/read
 * is a function of the processor's slot #, which processor on that board
 * (0-3), and the register number to be written/read.
 */

#define EV_CONFIGADDR(slot,proc,reg) \
	((evreg_t *)(EV_CONFIGREG_BASE + ((slot)<<11) + ((reg+(0x40*(proc)))<<3)))

#define EV_SETCONFIG_REG(slot,proc,reg,value) \
	(store_double((long long *)EV_CONFIGADDR((slot),(proc),(reg)), (long long)(value)))

#define EV_GETCONFIG_REG(slot,proc,reg) \
      ((evreg_t)load_double((long long *)EV_CONFIGADDR((slot),(proc),(reg))))

#define EV_GETCONFIG_REG_NOWAR(slot,proc,reg) \
      ((evreg_t)load_double_nowar((long long *)EV_CONFIGADDR((slot),(proc),(reg))))


/*
 * Convenience versions of the above macros that refer to the currently
 * executing processor.  These can only be used after the pda is set up.
 */
#define EV_SETMYCONFIG_REG(reg,value) \
	EV_SETCONFIG_REG(cpuid_to_slot[cpuid()], cpuid_to_cpu[cpuid()]<<EV_PROCNUM_SHFT, (reg), (evreg_t)(value))

#define EV_GETMYCONFIG_REG(reg) \
	(evreg_t)EV_GETCONFIG_REG(cpuid_to_slot[cpuid()], cpuid_to_cpu[cpuid()]<<EV_PROCNUM_SHFT, (reg))

#define EV_SET_MYCMPREG(time) { \
	EV_SETMYCONFIG_REG(EV_CMPREG0, (time)); \
	EV_SETMYCONFIG_REG(EV_CMPREG1, (time)>>8); \
	EV_SETMYCONFIG_REG(EV_CMPREG2, (time)>>16); \
	EV_SETMYCONFIG_REG(EV_CMPREG3, (time)>>24); \
	}

#endif /* _LANGUAGE_C */


#if R4000 || R10000
#define CAUSE_BERRINTR	CAUSE_IP7	/* Bus error intr. */
#endif
 
#if _LANGUAGE_C
#include <sys/types.h>

typedef __uint64_t evreg_t;	/* Everest configuration register type */

#define EV_GET_REG(reg) \
	(evreg_t)load_double((long long *)(reg))

#define EV_GET_REG_NOWAR(reg) \
	(evreg_t)load_double_nowar((long long *)(reg))

#define EV_SET_REG(reg,value) \
	store_double((long long *)(reg), (long long)(value))

#if _KERNEL
extern int cpuid_to_slot[];
extern int cpuid_to_cpu[];
#endif

typedef struct scuzzy {
	volatile u_char	*d_addr;       /* address register */
	volatile u_char	*d_data;       /* data register */
	volatile u_char	*s1_base;      /* chip base address register */
	volatile u_int	*dma_write;    /* address of dma write offset reg */
	volatile u_int	*dma_read;     /* address of dma read offset reg */
	volatile u_int	*dma_xlatlo;   /* low 32 bits of addr xlations */
	volatile u_int	*dma_xlathi;   /* high 8 bits of addr xlations */
	volatile u_int	*dma_flush;    /* dma flush */
	volatile u_int	*dma_reset;    /* dma reset */
	volatile u_int	*statcmd;      /* status command register */
	volatile u_int	*ibuserr;      /* ibus error register */
	u_char		 channel;      /* host adaptor number (0, 1, or 2) */
	u_char		 errchan0;     /* error in chan 0 cleared earlier by
					  other channel's err handler */
	u_char		 dmaerror;     /* dma error detected in scsi_dmaflush */
	u_char		 d_initflags;  /* initial flags for d_flags */
	u_char		 d_clock;      /* value for clock register on WD chip */
} scuzzy_t;

#endif /* _LANGUAGE_C */

/*
 * Return value from spl routines and spinlock routines is an integer,
 * "ospl", with the following bit field encodings:
 */
#define OSPL_CEL	0x0000007f	/* Current Execution Level */
#define OSPL_TRY1	0x00000080	/* always on for return value from */
					/* ``try'' spin locks to ensure a */
					/* non-zero return value */
#define OSPL_IMASK	SR_IMASK	/* CPU interrupt mask */
#define OSPL_SPDBG	0x00080000	/* spsema* debugging aid */

/* spl return value bits describing MP networking state */
#define OSPL_IMPSPIN	0x000400000     /* got or released splimp spin lock */
#define OSPL_NETSPIN	0x000200000     /* got or released splnet spin lock */
#define OSPL_NETSET	0x000100000     /* got the lock(s) */
#define OSPL_NETBITS	(OSPL_IMPSPIN | OSPL_NETSPIN | OSPL_NETSET)

/* Temporary hack to keep all of the current Everest code from breaking. */
#ifdef IP21
#include <sys/EVEREST/IP21.h>
#elif IP25
#include <sys/EVEREST/IP25.h>
#else
#include <sys/EVEREST/IP19.h>
#endif

/*
 * Variables used to work around IO4 IA problem
 * io4ia_war: Gets set whenever kernel detects that the work around is needed.
 * io4_flush_cache:
 *	Takes a small window address, and flushes the caches in the IO4 
 *	that corresponds to this small window address.
 */
#if _LANGUAGE_C
extern int    io4ia_war;
extern int    io4_flush_cache(paddr_t);
#endif /* _LANGUAGE_C */


#endif /* __SYS_EVEREST_H__ */

