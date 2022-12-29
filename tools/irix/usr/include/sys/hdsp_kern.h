/**************************************************************************
 *									  *
 * 		 Copyright (C) 1988, Silicon Graphics, Inc.		  *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/
#ident "$Header: /hosts/bonnie.engr.sgi.com/proj/irix6.5/isms/dmedia/devices/audio/kern.new/sys/RCS/hdsp_kern.h,v 1.18 1997/08/07 18:23:54 cook Exp $"

/***************************************************************************
 *
 *  hdsp_kern.h - Hollywood DSP device driver internal structs.
 *  (programmer visible hdsp structs are in hdsp.h).
 *
 ****************************************************************************/

#ifndef KDSP	/* this header file is used both for HDSP and KDSP.
		   for KDSP we ignore some of the definitions */

/* 
 * The following struct describes what the hdsp driver knows about a host ring
 * buffer.  
 */
typedef struct hrb_s {
    ulong *vheader;	 /* Virtual address of the header part of the hrb     */
    caddr_t pheader;	 /* Physical address of the header part of the hrb    */
    void *vdata;	 /* Virtual address of the data part of the hrb       */
    caddr_t pdata;	 /* Physical address of the data part of the hrb      */
    caddr_t vaddr;	 /* Virtual address of the data in user's addr space  */
    int nlocs;		 /* Number of locations in the data part of the hrb   */
    int nbytes;		 /* Number of bytes in the hrb, including the header  */
    int minordev;	 /* Minor device number associated with this hrb.     */
    void (*hrb_isr)();	 /* Pointer to the interrupt service routine.         */
    struct hrb_s *next;  /* Pointer to the next free or allocated hrb struct  */
    char type;		 /* Type of hrb (TOMIPS, FROMMIPS, FOLDED, etc.)      */
    struct pollhead pq; /* Poll head (for select, poll)                     */
    char state;		 /* State of the hrb.                                 */
    char rbnum;		 /* Ring Buffer Number                                */
    char dspnotified;	 /* True if the DSP has been notified of the hrb      */
    int maplen;		 /* Length of the mmaped region                       */
} hrb_t;

#endif

/* 
 * The following defines indicate the state of a host ring buffer.  
 */
#define HRB_WAITING 1

/* 
 * The following flags controll the behavior of kernel writes to the dsp 
 *	-- needed by streams drivers to prevent sleeping 
 */
#define HDSPSLEEPOK 0
#define HDSPNOSLEEP 1

/* 
 * The following macros are convenient ways to query the type of a host ring
 * buffer. 
 */
#define HRB_ISFOLDED(x)		(((x)&HRB_FOLDED)!=0)
#define HRB_ISFROMMIPS(x)	(((x)&HRB_FROMMIPS)!=0)
#define HRB_ISEXTEND(x)		(((x)&HRB_EXTEND)!=0)
#define HRB_ISUSERSPACE(x)	(((x)&HRB_USERSPACE)!=0)

#define HRB_ISUNFOLDED(x)	(((x)&HRB_FOLDED)==0)
#define HRB_ISTOMIPS(x)		(((x)&HRB_FROMMIPS)==0)
#define HRB_ISNOEXTEND(x)	(((x)&HRB_EXTEND)==0)
#define HRB_ISKERNELSPACE(x)	(((x)&HRB_USERSPACE)==0)

/* 
 * limits 
 */
#define HDSPMEMORYHI	65536	/* In DSP Words.           */
#define HDSPMEMORYLOW	32768	/* In DSP Words.           */
#define MAXHRB          30      /* maximum number of hrb's */

/* 
 * The following struct describes a Hollywood DSP on a HPC1 controller.  
 */
typedef struct hdsp_s {
	volatile unsigned int   state;       /* DSP state:for sleep/wakeup*/
	volatile unsigned long *dmawdcount;  /* DMA transfer size (16)    */
	volatile unsigned long *gioaddl;     /* GIO-bus address LSB (16)  */
	volatile unsigned long *gioaddm;     /* GIO-bus address MSB (16)  */
	volatile unsigned long *pbusadd;     /* Pbus address (16)         */
	volatile unsigned long *dmactl;      /* DMA control (2)           */
	volatile unsigned long *handtx;      /* handshake tx (16)         */
	volatile unsigned long *handrx;      /* handshake rx (16)         */
	volatile unsigned long *cintstat;    /* CPU interrupt status (3)  */
	volatile unsigned long *cintmask;    /* CPU interrupt masks (3)   */
	volatile unsigned long *miscsr;      /* misc control,status (8)   */
	volatile unsigned long *burstctl;    /* ballistics register (16)  */
	volatile unsigned long *memory;      /* DSP memory                */
	hrb_t *cmdin;	                     /* Commands from the DSP     */
	hrb_t *cmdout;                       /* Commands to the DSP       */
	int input_source;                    /* audio parameter           */
	int left_input_atten;                /* audio parameter           */
	int right_input_atten;               /* audio parameter           */
	int left2_input_atten;               /* audio parameter           */
	int right2_input_atten;              /* audio parameter           */
	int input_rate;                      /* audio parameter           */
	int output_rate;                     /* audio parameter           */
	int left_speaker_gain;               /* audio parameter           */
	int right_speaker_gain;              /* audio parameter           */
	int speaker_mute;                    /* audio parameter           */
	int inputrbcount;     /* Count of input (to mips) ring buffers    */
	int outputrbcount;    /* Count of output (from mips) ring buffers */
} hdsp_t;

/*
 * offsets into shared DSP memory
 */
#define HDSP_MEM_MONITOR_FLAG     24  /* passthru enable/disable */
#define HDSP_MEM_AUDIORB_ERROR    28  /* base addr for audio rb error flags */
#define HDSP_MEM_AUDIO0_ERROR     28  /* audio 0 error flag */
#define HDSP_MEM_AUDIORB_TYPE     32  /* error types */
#define HDSP_MEM_AUDIORB_LENGTH   36  /* length of errors */
#define HDSP_MEM_AUDIORB_LOC_ADDR 40  /* locations of errors */

#define HDSP_MEM_LEFT_MONITOR_ATTEN    48   /* left channel atten factor */
#define HDSP_MEM_RIGHT_MONITOR_ATTEN   49   /* right channel atten factor */

/* 
 * The following defines indicate the state of the hdsp 
 */
#define HDSP_RESET 0		/* reset and ucode not loaded */
#define HDSP_INITIALIZING 1	/* ucode loading */
#define HDSP_RUNNING 2		/* ucode loaded and running */

/* 
 * XXX BOGUS 
 * The following procedures place and remove data to/from host ring buffers 
 /
void hrb_dsptomipsfolded_isr(hrb_t*);
void hrb_dsptomipsunfolded_isr(hrb_t*);
void hrb_mipstodspfolded_isr(hrb_t*);
void hrb_mipstodspunfolded_isr(hrb_t*);

void hrb_user_dsptomipsfolded_isr(hrb_t*);
void hrb_user_dsptomipsunfolded_isr(hrb_t*);
void hrb_user_mipstodspfolded_isr(hrb_t*);
void hrb_user_mipstodspunfolded_isr(hrb_t*);
 */
/* 
 * Hollywood DSP commands. 
 */
#define DSPCMD_CREATEHRB		1
#define DSPCMD_ACQUIRE_SAMPLERB		4
#define DSPCMD_FREE_SAMPLERB		5
#define DSPCMD_CHANGE_SAMPLE_RB		6
#define DSPCMD_CHANGE_AUDIO_PARMS	7

/*
 * Client locks state 
 */
#define HDSP_CLIENT_UNOPENED	(-2)
#define HDSP_CLIENT_OPENED	(-1)

/* 
 * Priority that the DSP blocks interrupts at. 
 */
#define splhdsp()	splhi()

/* 
 * HPC1 CINTMASK interrupt mask register bits 
 *    1 => enable interrupt source, 0 => disable
 */
#define HDSP_CINTMASK_DMA       1   /* end of DMA             */
#define HDSP_CINTMASK_HANDTX    2   /* DSP writes to HANDTX   */
#define HDSP_CINTMASK_HANDRX    4   /* DSP reads from HANDRX  */

/* 
 * Configuration constants 
 */
#define CMDBUFSIZE   300
#define REPLYBUFSIZE 20
#define MAXHDSPCLIENTS	12
#define HDSPSPRI (PZERO-1)
