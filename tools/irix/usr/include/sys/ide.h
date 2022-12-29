#ifndef __IDE_H_
#define __IDE_H_

#ifdef XSCSI

#include <linux/config.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/wait.h>
#include <linux/errno.h>
#include <linux/module.h>
#include <linux/pci.h>
#include <linux/fs.h>
#include <linux/timer.h>
#include <linux/poll.h>
#include <linux/smp_lock.h>
#include <asm/byteorder.h>
#include <linux/spinlock.h>
#include <asm/atomic.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm/semaphore.h>
#include <asm/delay.h>
#include <asm/unistd.h>
#include <linux/kdb.h>
#include <linux/smp_lock.h>
#include <linux/init.h>
#include <linux/blk.h>
#include <linux/xscsi/xscsi.h>
#include <linux/xscsi/osdep_linux.h>
#include <linux/xscsi/alenlist.h>
#include <linux/xscsi/xfailover.h>
#include <linux/devfs_fs_kernel.h>

#else
#include "sys/types.h"
#include "sys/ksynch.h"
#include "sys/poll.h"
#include "sys/ddi.h"
#include "sys/param.h"
#include "sys/systm.h"
#include "sys/edt.h"
#include "sys/sysmacros.h"
#include "sys/cmn_err.h"
#include "sys/debug.h"
#include "sys/kmem.h"
#include "sys/mman.h"
#include "ksys/ddmap.h"
#include "sys/errno.h"
#include "sys/immu.h"
#include "sys/invent.h"
#include "sys/kopt.h"
#include "sys/mbuf.h"
#include "sys/sbd.h"
#include "sys/socket.h"
#include "sys/cpu.h"
#include "sys/conf.h"
#include "sys/ddi.h"
#include "sys/mload.h"
#include "sys/cred.h"
#include "sys/pci_intf.h"
#include "sys/PCI/pciio.h"
#include "sys/PCI/PCI_defs.h"
#include "sys/ktime.h"
#include "sys/sema.h"
#include "sys/scsi.h"
#include  "sys/iograph.h"
#include  "ksys/xthread.h"
#include  "sys/pfdat.h"
#include  "sys/var.h"
#include  "sys/failover.h"
#include  "sys/invent.h"
#include  "sys/PCI/pcibr.h"
#include "sys/alenlist.h"

#endif

// Starting Linux - specific declarations 

#define CMD_DEV_ID			0x649
#define CMD_VENDOR_ID			0x1095
#define PCI_VENDOR_ID_PROMISE           0x105a
#define PCI_DEVICE_ID_PROMISE_20265     0x0d30
#define PCI_DEVICE_ID_PROMISE_20267     0x4d30
#define PCI_DEVICE_ID_PROMISE_20246     0x4d33
#define PCI_DEVICE_ID_PROMISE_20262     0x4d38
#define PCI_DEVICE_ID_PROMISE_20268     0x4d68
#define PCI_DEVICE_ID_PROMISE_20268R    0x6268
#define PCI_DEVICE_ID_PROMISE_5300      0x5300

#ifdef XSCSI
typedef devfs_handle_t	xscsi_vhdl_t;
typedef struct pci_dev  *pci_hdl_t;
#define PCIIO_WRITE_GATHER      0x0

#define SCSI_HWG_UNLOCK()	up_write(&scsi_hwgraph_lock)
typedef enum pciio_endian_e {
    PCIDMA_ENDIAN_BIG,
    PCIDMA_ENDIAN_LITTLE
} pciio_endian_t;

#else
typedef vertex_hdl_t xscsi_vhdl_t;
typedef xscsi_vhdl_t  pci_hdl_t;
#endif

#define LABEL_LENGTH_MAX	256
#define	ATA_MAX_BLOCKS		256
#define	ATA_BLOCK_SIZE		512
#define IDE_64KB_LIMIT		0xFFFF
#define IDE_CMD_DEBUG		1


// Ending linux-specific declarations

#define READCAPACITY        0x25
#define WRITE_EXTENDED      0x2A

#define READ_6		    0x08
#define WRITE_6		    0x0A
#define READ_EXTENDED       0x28
#define MODESELECT_6        0x15
#define MODESELECT_10       0x55
#define MODESENSE_6         0x1A
#define MODESENSE_10        0x5A
#define INQUIRY             0x12
#define TESTUNITREADY       0x00
#define REQUEST_SENSE       0x03

#define ATA_CMD_SEND        0x01
#define ATA_CMD_FAKE        0x02
#define ATA_CMD_UNSUPPORTED 0x04
#define	ATA_SPECIAL_CMD		0x10
#define ATA_SPECIAL_CMD_COMPLETE	0x20
#define LBA_SET             0x40

/*
 * Used to keep track of last N commands issued.
 */
#ifdef IDE_CMD_DEBUG
typedef struct xide_cmd_dbg_s {
  void   *request;
  u_char  command[12];
  int     datalength;
  u_short action;
  u_short code;
  timespec_t Time;
} xide_cmd_dbg_t;

#define IDE_CDBG_RCVD		0
#define IDE_CDBG_ADD		1
#define IDE_CDBG_RM		2
#define IDE_CDBG_FINISH		3
#define IDE_CDBG_DONE		4
#define IDE_CMD_BRANCH		5
#define IDE_CMD_SUCCESS		6
#define IDE_CMD_ERROR		7
#define IDE_CMD_WATCH		8
#define IDE_CMD_SENT		9
/*
static char *xide_cdbg_actions[] =
{
 "Received ScsiReq   ",		// 0
 "Add to ScsiReq     ",		// 1
 "Remove from ScsiReq",		// 2
 "Put in FinishQ      ",	// 3
 "sr_notify() Called",		// 4
 "Branched",			// 5
 "ScsiReq successful",		// 6
 "ScsiReq ERROR",		// 7
 "ScsiReq ret. by Watchdog()",	// 8
 "ScsiReq Sent to Device",	// 9
};
*/
#define IDE_CMD_IDX_SZ 256 /* 32  Cmd Debug Queue */
#endif

#define WATCHDOG_TIME (HZ*20)

/* return codes */
#define  IDE_FAIL          1
#define  IDE_OK            0

#define  IDE_ABORT        -1
#define  IDE_NO_START      0
#define  IDE_STARTED       1
#define  IDE_NEED_WAIT     2

/* fix size of some entries */
#define  IDE_MAPSIZE       128    /* min number of page table entrys for cmd */
#define  IDE_CMD_OBJS      1    /* W75_4-0 : max number of commands outstanding - 1 */

/* IOC4 Specific Definitions */
#define IOC4_CMD_OFFSET		0x100
//#define IOC4_CTRL_OFFSET	0x118
#define IOC4_CTRL_OFFSET	0x120
#define IOC4_DMA_OFFSET		0x140
#define IOC4_INTR_OFFSET	0x0

#define IOC4_TIMING		0x00
#define IOC4_DMA_PTR_L		0x01
#define IOC4_DMA_PTR_H		0x02
#define IOC4_DMA_ADDR_L		0x03
#define IOC4_DMA_ADDR_H		0x04
#define IOC4_BC_DEV		0x05
#define IOC4_BC_MEM		0x06
#define	IOC4_DMA_CTRL		0x07
#define	IOC4_DMA_END_ADDR	0x08

// Bits in the IOC4 Control/Status Register
#define	IOC4_S_DMA_START	0x01
#define	IOC4_S_DMA_STOP		0x02
#define	IOC4_S_DMA_DIR		0x04
#define	IOC4_S_DMA_ACTIVE	0x08
#define	IOC4_S_DMA_ERROR	0x10
#define	IOC4_ATA_MEMERR		0x02

// Read/ Write Directions
#define	IOC4_DMA_WRITE		0x04
#define	IOC4_DMA_READ		0x00

typedef struct xide_std_PageTblEntry {
#ifdef USE_LE32_ORDERING
  uint64_t 	EOT_Resv_Len:32;
  uint64_t	Adr:32;
#else	
  uint64_t	Adr:32;
  uint64_t 	EOT_Resv_Len:32;
#endif 
} xide_std_PageTblEntry_t;		

typedef struct xide_ioc4_PageTblEntry {
	uint64_t	Adr;
	uint64_t	EOT_Resv_Len;
} xide_ioc4_PageTblEntry_t;	

typedef union xide_PageTblEntry {
		xide_std_PageTblEntry_t 	xide_32b;
		xide_ioc4_PageTblEntry_t sgi_ioc4;
} xide_PageTblEntry_t;		
/*
typedef struct xide_PageTblEntry {
  uint64_t	Adr:32;
  uint64_t 	EOT_Resv_Len:32;
} xide_PageTblEntry_t;		
*/
typedef struct xide_LunInfo_s	xide_LunInfo_t;
typedef struct xide_CmdObj_s	xide_CmdObj_t;

typedef volatile struct {
	uint8_t	count_h;
	uint8_t	sector_h;
	uint8_t	cyl_lsb_h;
	uint8_t	cyl_msb_h;
} cmd48_regs_t;	

typedef volatile struct {
	uint8_t	data;		/* Data Register : Offset 0 */
	uint8_t	err_feature;	/* (R) Error/ (W)Features Register : Offset 1 */
	uint8_t	count;		/* (W) sector count : Offset 2 */
	uint8_t	sector;		/* sector # : Offset 3  : LBA Low*/
	uint8_t	cyl_lsb;	/* cylinder# LSB : Offset 4 : LBA Mid */
	uint8_t	cyl_msb;	/* cylinder# MSB :  Offset 5  : LBA High*/
	uint8_t	drive;		/* Sector/Drive/Head/Device register : Offset 6 */
	uint8_t	command;	/* Command/status register : Offset 7 */
} command_regs_t;

struct xide_CmdObj_s {
  /* For putting In queue */
  xide_CmdObj_t		*Next;	
  xide_CmdObj_t		*Prev;	
	/* DMA Stuff */
  uint8_t               NoPte;	
  uint8_t               UseBigmap;	
  xide_PageTblEntry_t    *Pte;		
//  void			*Pte;		
  uint64_t	   	PtePciAddr;
//  uint64_t		DataPciAddr;
  alenlist_t            AlenList;      /* phys adr of data */
  alenlist_t            PciAlenList;   /* pci adr of data  */
 
	/* pre-allocated map of size = IDE_MAPSIZE */
  xide_PageTblEntry_t    *ReservedPte;
//  void			*ReservedPte;
  iopaddr_t             ReservedPtePciAddr;

  /* The following PTE map variables are only needed if
   * the map is > IDE_MAPSIZE and BigMap is not available
   */
  uint32_t              AllocMapSize; /* for pte map */
  pciio_dmamap_t        PteDMAMap;
  iopaddr_t             PteDMAMapBaseaddr;
  int                   NumPtes;

  /* only has non NULL value if sr_buflen > 0 */
  pciio_dmamap_t        DataDMAMap;
  iopaddr_t             DataDMAMapBaseaddr;

  /* Scsi requests linked to it */
  scsi_request_t	*TempReqForFix;
  scsi_request_t	*HoldReq;
  scsi_request_t	*OrigReq;
  scsi_request_t	*SentReq;

  scsi_request_t	*ReqSense;

  /* fix up information for device blksz != media blksize */
  u_char		FixMap4BlkSz;
  int			MapStartLen;
  int			MapEndLen;

  /* timeout information */
  int                   TimeOut;
  int                   StartTime;
  int                   TimeOutTime;		

  uint8_t               State;
  u_char		CmdBlk[12]; /* Command bytes of PKT Command to be sent */	
  cmd48_regs_t		cmdblk48;
  command_regs_t	ide_cmdblk;
  int8_t		Tag;	/* Tag value of the scsi_request */	
  
  xide_LunInfo_t         *li;		/* Lun to which command is sent */
  uint8_t		request_stage;
  uint8_t		transfer_type;

/* New Fields to get over the 128K (256 Block) barrier */
  int					offset;
  xide_PageTblEntry_t	*start_Pte;	  
  xide_PageTblEntry_t	*saved_Pte;	  
  uint64_t				start_PtePciAddr;
  uint8_t				Offset_Flag;
  uint32_t				Prev_Num_Blocks;
};

typedef struct xide_mode_sense_6_hdr_s {
	u_char	SenseLen;
	u_char	MediaType;
	u_char	DevSpecific;
	u_char	BlkDescLen;
        union {
	  struct {
	    u_char  NumOfBlks[4];
	    u_char  BlkLength[4];
	  } Desc;
	  u_char  DataNoBD[8];
	} Data;
        u_char  DataIfBD;
} xide_mode_sense_6_hdr_t;

typedef struct xide_mode_sense_10_hdr_s {
	u_char	SenseLen[2];
	u_char	MediaType;
	u_char	DevSpecific;
        u_char  Reserved[2];
	u_char	BlkDescLen[2];
        union {
	  struct {
	    u_char  NumOfBlks[4];
	    u_char  BlkLength[4];
	  } Desc;
	  u_char  DataNoBD[8];
	} Data;
        u_char  DataIfBD;
} xide_mode_sense_10_hdr_t;

#define	IDE_DATA		0
#define	IDE_ERR_FEATURE		1
#define	IDE_COUNT		2
#define	IDE_SECTOR		3
#define	IDE_CYL_LSB		4
#define	IDE_CYL_MSB		5
#define	IDE_DRIVE		6
#define	IDE_COMMAND		7


#define	IDE_ALT_STATUS		2
//#define	IDE_ALT_STATUS		1

typedef volatile struct {
	uint8_t	resvd0;
	uint8_t	resvd1;
	uint8_t	alt_status;	 /* alternate registers offset */
	uint8_t	resvd3;
} ctrl_regs_t;	

#define IDE_BMIDECR0	0
#define	IDE_MRDMODE	1
#define	IDE_BMIDESR0	2
#define	IDE_UDIDETCR0	3
#define	IDE_DTPR0	4
#define	IDE_BMIDECR1	8
#define	IDE_BMIDECSR	9
#define	IDE_BMIDESR1	0x0A
#define	IDE_UDIDETCR1	0x0B
#define	IDE_DTPR1	0x0C
#define	IDE_UDMA3_4_CTRL 0x11	
#define	IDE_SUB_SYSID	0x12
#define	IDE_FLASH	0x14
#define	IDE_MASTER_CTL0	0x1A
#define	IDE_MASTER_CTL1	0x1B
#define	IDE_SYS_CTL	0x1C
#define	IDE_ATAPI_CH1	0x20
#define	IDE_ATAPI_CH2	0x24

typedef	volatile struct {
	uint8_t		bmxidecr0; /* 0x70 : Bus Master Cmd Reg. for Primary Channel */
	uint8_t		mrdmode;  /* 0x71 : Intr Enable, Status Reg, 
				Master Read Select Ctrl Reg. for both channels */	
	uint8_t		bmxidesr0; /* 0x72 : Bus Master Status Reg. for Primary Chnl */
	uint8_t		udxidetcr0;/* 0x73 : Ultra DMA Timing Ctrl Reg. for Prim. Chnl */
	uint32_t	dtpr0;	  /* 0x74-77: Descriptor Table Ptr Reg. for Prim. Chnl */
	uint8_t		bmxidecr1; /* 0x78 : Bus Master Cmd Reg. for 2ndry Channel */
	uint8_t		bmxidecsr; /* 0x79 : Bus Master Ctrl Status Reg */	
	uint8_t		bmxidesr1; /* 0x0A : Bus Master IDE/ATA Status Reg. for Ch. 2 */
	uint8_t		udxidetcr1;/* 0x0B : Ultra DMA Timing Ctrl Reg. for Ch. 2 */
	uint32_t	dtpr1;	  /* 0x0C-0F :  Descriptor Table Ptr Reg. for Ch. 2 */		
	uint8_t		resv_10;  /* Reserved */		
	uint8_t		udma3_4_ctrl; /* 0x11 : Ultra DMA Mode 3,4 Ctrl : Promise */
	uint8_t		sub_sysID;/* 0x12 : Sub System ID modification Ctrl : Promise */
	uint8_t		resv_13;  /* Reserved */
	uint32_t	flash;	  /* 0x14-17: Flash Memory Write port : Promise */
	uint16_t	resv18_19;/* Reserved */
	uint8_t		master_ctl0;/* 0x1A : Master Mode Ctrl for Ch. 1 : Promise */
	uint8_t		master_ctl1;/* 0x1B : Master Mode Ctrl for Ch. 2 : Promise */
	uint32_t	sys_ctl;  /* 0x1C-1F : System Ctrl Reg. Promise */
	uint32_t	atapi_Ch1;/* 0x20-23 : Ch. 1 ATAPI DMA port */ 
	uint32_t	atapi_Ch2;/* 0x24-27 : Ch. 2 ATAPI DMA port */ 
} pdc20262_dma_regs_t;	

typedef	volatile struct {
	uint8_t		bmxidecr0; /* 0x70 : Bus Master Cmd Reg. for Primary Channel */
	uint8_t		mrdmode;  /* 0x71 : Intr Enable, Status Reg, 
				Master Read Select Ctrl Reg. for both channels */	
	uint8_t		bmxidesr0; /* 0x72 : Bus Master Status Reg. for Primary Chnl */
	uint8_t		udxidetcr0;/* 0x73 : Ultra DMA Timing Ctrl Reg. for Prim. Chnl */
	uint32_t	dtpr0;	  /* 0x74-77: Descriptor Table Ptr Reg. for Prim. Chnl */
	uint8_t		bmxidecr1; /* 0x78 : Bus Master Cmd Reg. for 2ndry Channel */
	uint8_t		bmxidecsr; /* 0x79 : Bus Master Ctrl Status Reg */	
	uint8_t		bmxidesr1; /* 0x0A : Bus Master IDE/ATA Status Reg. for Ch. 2 */
	uint8_t		udxidetcr1;/* 0x0B : Ultra DMA Timing Ctrl Reg. for Ch. 2 */
	uint32_t	dtpr1;	  /* 0x0C-0F :  Descriptor Table Ptr Reg. for Ch. 2 */		
} cmd649_dma_regs_t;

typedef volatile struct {
	uint32_t	timing_reg0;
	uint32_t	timing_reg1;
	uint32_t	low_mem_ptr;
	uint32_t	high_mem_ptr;
	uint32_t	low_mem_addr;
	uint32_t	high_mem_addr;
	uint32_t	dev_byte_count;
	uint32_t	mem_byte_count;
	uint32_t	status;
} ioc4_dma_regs_t;	

typedef volatile struct {
	uint32_t	low_err;
	uint32_t	high_err;
	uint32_t	serial_intr;
	uint32_t	ata_intr; // Other Interrupt Reg.
	uint32_t	serial_set;
	uint32_t	ata_intr_set;
	uint32_t	serial_clear;
	uint32_t	ata_intr_clear;
} ioc4_intr_regs_t;

#define 	IOC4_INTR_REG	0x03
#define		IOC4_INTR_SET	0x05
#define		IOC4_INTR_CLEAR	0x07


typedef struct	xide_ProtoInfo_s	xide_ProtoInfo_t; 
typedef struct	xide_TargInfo_s	xide_TargInfo_t;
typedef struct	xide_dev_s	xide_dev_t;

struct xide_ProtoInfo_s {
	vertex_hdl_t		ProtoVhdl;
#ifndef XSCSI	
	vertex_hdl_t		PciVhdl;
#else	
	struct pci_dev		*PciVhdl;
#endif	
	uint			Flags;
	char			HwgName[LABEL_LENGTH_MAX];
#ifdef XSCSI	
	sema_t			intr_q;
	sema_t			intr_watch_q;
#endif
	uint8_t			intr_set;
	uint8_t			intr_seen;
	uint8_t			prevent_intr;
	uint8_t			pci_dma_error;
	/* For Multiple IDE Controllers */
	xide_ProtoInfo_t		*Next;
	int				Number;
	uint16_t			devid;
	uint16_t			vendorid;
	uint16_t				revID;
	uint32_t			pciio_byte_stream;
	uint8_t			xide_alt_status;

	/* For Fairness in sending commands */
	int					LastTargServed; /* 0 or 1 only */	

	/* List of free CmdObjs */
	xide_CmdObj_t		*FreeCmdObjTail; 
	xide_CmdObj_t		*FreeCmdObjHead; 
	
	/* DMA Stuff */
	xide_PageTblEntry_t	*Bigmap;/* for transaction > IDE_MAPSIZE pages */
	iopaddr_t			BigMapPciAddr;
	int					BigmapInUse;
	int					BigMapMaxCount;
	caddr_t				XferScratch;
	iopaddr_t			XferScratchPci;	/* PCI address of above */	
	pciio_dmamap_t  	PteMap;
	iopaddr_t           PteMapBaseaddr;
	pciio_dmamap_t  	DmaEndMap;
	iopaddr_t			DmaEndAddr;
	caddr_t				DmaEndPtr;
	/* Locking Stuff */
	#if  IDE_SPINLOCKS
	lock_t				GraphLock;     /* add/rm to ti/liList or hwgraph */
	int              	GraphLockSpl;
	lock_t              CommandLock;     /* Commmand Sent to Device */
	int              	CommandLockSpl;
	lock_t              ResourceLock;  /* todo lists, maps, objs */
	int                 ResourceLockSpl;
	lock_t              FinishedQLock;
	int                 FinishedQSpl;
	lock_t              IntrLock;
	int                 IntrLockSpl;
	#else
	mutex_t            	GraphLock;
	mutex_t           	CommandLock;
	mutex_t				ResourceLock;
	mutex_t				FinishedQLock;
	mutex_t				IntrLock;
	#endif

	/* Channel Mapping Regs */
//	command_regs_t		*cmdblk;
//	ctrl_regs_t		*ctrlblk;
//	dma_regs_t		*dmablk;
	
	caddr_t				cmdblk;
	caddr_t				ctrlblk;
	caddr_t				dmablk;
	caddr_t				intrblk;	
	// Interrupt register block for IOC4
	
	/* Target Info */
	int 			device_conf[2]; 
		/* 11-8 : 0 -> not added to hwgraph | 1 -> added */
		/* 7-4 : 0 -> not found | 1 -> ATA | 2 -> ATAPI */
		/* 3-0 : 0 -> not found | 1 -> found */
	
	xide_TargInfo_t		*PtrToTarg[2];
	uint8_t				State;
	
	/* Finished Q of requests */
	scsi_request_t		*FinishedQHead;
	scsi_request_t		*FinishedQTail;
} ;

struct xide_TargInfo_s {
	vertex_hdl_t		TargetVhdl;
	vertex_hdl_t		ProtoVhdl;
	xide_ProtoInfo_t		*ProtoInfo;
	int			Number;
	char			HwgName[LABEL_LENGTH_MAX];
	xide_LunInfo_t		*PtrToLun[2];
};		

#ifdef XSCSI
typedef void   (*SenseCallback_t)(vertex_hdl_t, uint8_t *);
#endif

struct xide_LunInfo_s {
	vertex_hdl_t		LunVhdl;
	vertex_hdl_t		TargetVhdl;
	vertex_hdl_t		ProtoVhdl;
	xide_TargInfo_t		*TargInfo;
	xide_ProtoInfo_t		*ProtoInfo;
	int			Number;	

	/* HwGraph Stuff */
	scsi_target_info_t	tinfo;

	/* Identify (Packet) Device Info */
	xide_dev_t		*xidentifyDev; 
	uint8_t			address_48;
	
	/* Get Capacity Command Info */
	uint32_t		CapNumOfBlocks;
	uint32_t		CapBlockSize;
	int				CapDataValid;
  	uint32_t		NumOfBlocks; /* Set by Mselect 6 */
	uint32_t		BlockSize; /* Set by Mselect 6 */
		

	/* Block Size Stuff */
	u_char			AddSenseBD;/* add/rm block desc for mode cmds */
	u_char			FixSenseBD;/* fix block desc for m-select cmd */
	u_char			NoMode6Cmd; /* M-sense/sel. 6 byte cmds (y=1) */
	u_char			NoMode10Cmd; /* M-sense/sel. 6 byte cmds (y=1) */
	u_char			BlockSizeValid; /* Is current block_size valid? */
	
	/* Process accessing LUN stuff */
	int			RefCount;
	u_char			Exclusive;
	u_char			ContAlleg;     /* contingent allegiance */
	
	/* Queueing Stuff */
	xide_CmdObj_t		*CmdObjHead; /* CmdObjs sent to device : Head */
	xide_CmdObj_t		*CmdObjTail; /* CmdObjs sent to device  : Tail*/
	scsi_request_t		*ScsiReqQHead;/* Scsi Reqs by dksc/ds : Head */
	scsi_request_t		*ScsiReqQTail;/* Scsi Reqs by dksc/ds : Tail */
			 
	/* CallBack Func */
#ifndef XSCSI	
	void			(*SenseCallback)();
#else
	SenseCallback_t          SenseCallback;
#endif	

	/* Locking Stuff */
	mutex_t			OpenLock;
	#ifdef  IDE_SPINLOCKS
	lock_t			LunLock;
	int				LunSpl;
	#else
	mutex_t			LunLock;
	#endif

	uint8_t			WeAreCD;
	uint32_t		Tag_Used;

};	


/*
#define IDE_PCI_OUTB(x,y)	PCI_OUTB(((uintptr_t)(x)^3),y)
#define IDE_PCI_INB(x)		PCI_INB(((uintptr_t)(x)^3))
#define IDE_PCI_INW(x)		PCI_INH(((uintptr_t)(x)^2))
#define IDE_PCI_OUTW(x,y)	PCI_OUTH(((uintptr_t)(x)^2),y)
#define IDE_PCI_OUTDW(x,y)	PCI_OUTW((uintptr_t)(x),y)
#define IDE_PCI_INDW(x)		PCI_INW((uintptr_t)(x))
*/

#define PCI_VENDOR_SGI		0x10A9			
#define	IOC4_PCI_ID		0x100A
void 		xide_putb(xide_ProtoInfo_t *pi, caddr_t addr, uint8_t	offset, uint8_t	value); 
void 		xide_putw(xide_ProtoInfo_t *pi, caddr_t addr, uint8_t offset, uint16_t value);
void		xide_putdw(xide_ProtoInfo_t *pi, caddr_t addr, uint8_t offset, uint32_t value);
uint8_t		xide_getb(xide_ProtoInfo_t *pi, caddr_t addr, uint8_t	offset); 
uint16_t	xide_getw(xide_ProtoInfo_t *pi, caddr_t addr, uint8_t offset);
uint32_t	xide_getdw(xide_ProtoInfo_t *pi, caddr_t addr, uint8_t offset);


#define IDE_OUTB(pi,addr,offset,value)	xide_putb(pi,addr,offset,value)
#define IDE_OUTW(pi,addr,offset,value)	xide_putw(pi,addr,offset,value)
#define IDE_OUTDW(pi,addr,offset,value)	xide_putdw(pi,addr,offset,value)

#define IDE_INB(pi,addr,offset)		xide_getb(pi,addr,offset)
#define IDE_INW(pi,addr,offset)		xide_getw(pi,addr,offset)
#define IDE_INDW(pi,addr,offset)	xide_getdw(pi,addr,offset)

#define IDE_DELAY(x)		delay(x)

#define ATAPI_MAGIC_LSB		0x14
#define ATAPI_MAGIC_MSB		0xeb
#define INV_IDE_IOC4	29
#define INV_IDE			30
#define SCI_SCSI_TYPE_IDE	0x31

#define	IDE_S_BUSY		0x80
#define IDE_S_DRQ		0x08
#define IDE_C_REL		0x04
#define IDE_S_SERV		0x10

#define	IDE_E_ERR		0x01
#define IDE_E_ABORT		0x04

#define	DEV_PRESENT		0x01
#define	DEV_ABSENT		0x00
#define ATA_DEV_PRESENT		0x40
#define ATAPI_DEV_PRESENT	0x20
#define DEV_IN_GRAPH		0x0100
#define TARGET_IN_GRAPH		0x0200

typedef struct xide_pciconfig_s  xide_pciconfig_t;

struct xide_pciconfig_s
{
	u_int16_t	PCI_devID,PCI_vendID;
	u_int16_t	PCI_status,PCI_command;
	u_int8_t	PCI_class_code[3], PCI_revID;
	u_int8_t	rsvd1, PCI_header_type,
			PCI_latency_timer, PCI_cache_line;
	u_int32_t	PCI_base0;
	u_int32_t	PCI_base1;
	u_int32_t	PCI_base2;
	u_int32_t	PCI_base3;
	u_int32_t	PCI_base4;
	u_int32_t	PCI_base5;
	u_int32_t	unused1;
	u_int32_t	unused2;
	u_int32_t	PCI_rombase;
	u_int32_t	unused3;
	u_int32_t	unused4;
	u_int8_t	PCI_max_latency, PCI_min_grant,
			PCI_intr_pin, PCI_intr_line;
	u_int8_t	PCI_errorgen, PCI_intlinsel1,
			PCI_devstatus0, PCI_devconfig;
};

/* CDROM Specific Structure only */
struct xide_dev_s {
	uint16_t		atapi_dev:2, /* 0_16-15 => atapi */
#define IDE_DEVICE	0x2
				resv_1 : 1,		
				dev_type : 3,				
#define IDE_DIRECT	0x0
#define IDE_TAPE	0x1
#define IDE_CDROM	0x5
#define IDE_OPTICAL	0x7
				removable : 1,
				drq_time : 2,
#define IDE_DRQ_MPROC	0x0
#define IDE_DRQ_INTR	0x1
#define IDE_DRQ_ACCL	0x2
				resv_2 : 2,
				incomplete : 1,
				pkt_len : 2;
#define IDE_PKT_12	0x0
#define IDE_PKT_16	0x1
	uint16_t		cylinder;	/* 1: Unused */
	uint16_t		w2_resv;	/* Word 2 : reserved */
	uint16_t		heads;		/* 3: Unused */
	uint16_t		unfbytes_track;	/* 4: Unused */
	uint16_t		unfbytes_sector;/* 5: Unused */
	uint16_t		sectors;	/* 6: Unused */
	uint16_t		w7_9resv[3];	/* 7-9 : resv */
	uint8_t			serial_no[20];	/* 10-19 */
	uint16_t		w20_21resv[2];	/* 20-21 reserved */	 	
	uint16_t		ecc_bytes;	/* 22: unused */
	uint8_t			firmware_rev[8];/* 23-26 : firmware revision */
	uint8_t			model_no[40];	/* 27-46 : Model no. */			
	uint16_t		nsecperint;	/* 47 : Unused */
	uint16_t		w48_resv;	/* 48 : resv */
	uint16_t		dma_interleave : 1,/* 49_15 : Interleaved DMA */
				cmd_queue : 1,	/* 49_14 : Command Queueing */
				overlap : 1,	/* 49_13 : Overlap operation supported */
				softreset :1,	/* 49_12 : Obsolete */
				iordy_yes : 1,	/* 49_11 : IORDY supported */
				iordy_no :1,	/* 49_10 : IORDY may be disabled */
				lba : 1,	/* 49_9  : LBA supported */
				dma : 1,		/* 49_8	 : DMA supported */
				w49_vendor : 8;	/* 49_7-0: Vendor Specific */		
	uint16_t		capvalidate;	/* 50 */
	uint16_t		old_pio;	/* 51 : PIO modes 0-2 : Obsolete */	
	uint16_t		old_dma;	/* 52 :	Old DMA modes,not IDE-3:Obsolete */
	uint16_t		w53_resv : 13,	/* 53_15-3 : reserved */
				valid_w88 : 1,	/* 53_2 : Fields in Word 88 valid */
				valid_w64_70 :1,/* 53_1 : Fields in W 64 - 70 valid */
				valid_w54_58 :1;/* 53_0 : Fields in W 54 - 58 valid */
	uint16_t		curr_cyl;	/* 54 : Unused */
	uint16_t		curr_heads; 	/* 55 : Unused */
	uint16_t		curr_sect;	/* 56 : Unused */
	uint16_t		curr_cap[2];	/* 57-58 : Unused */		
	uint16_t		w59_resv;	/* 59 : reserved */
	uint16_t		usr_sect[2];	/* 60-61 : Unused */
	uint16_t		singleword_dma;	/* 62 : Single Word DMA modes */
	uint16_t		w63_resv : 3,	/* 63_15-11 : Reserved */
				multidma_2: 1, 	/* 63_10 : Multiword DMA mode 2 selected */
				multidma_1: 1,	/* 63_9  : Multiword DMA mode 1 selected */
				multidma_0: 1,	/* 63_8  : Multiword DMA mode 0 selected */
				w63_resv2 : 3,	/* 63_7-3 : Reserved */
				multidma_2supp : 1, /* 63_2 : Multiword DMA modes <= 2 supported */
				multidma_1supp : 1, /* 63_1 : Multiword DMA modes <= 1 supported */
				multidma_0supp : 1; /* 63_0 : Multiword DMA mode 0 supported */	
	uint16_t		w64_resv :8,	/* 64_15-8 : reserved */
				pio_modes : 8;	/* 64_7-0  : PIO modes supported */
	uint16_t		mwdma_min;	/* 65 : Minimum Multiword DMA time (in nanosecs) */
	uint16_t		mwdma_rec; 	/* 66 : Manufac. Multiword DMA time (in nanosecs) */
	uint16_t		pio_noflow;	/* 67 : Min. PIO time & No flowcontrol (nanosecs) */
	uint16_t		pio_iordy;	/* 68 : Min. PIO time with IORDY */
	uint16_t		w69_70resv[2];	/* 69-70 : reserved */	
	uint16_t		rls_ovrlap;	/* 71 : Time(ns) for bus-release after PACKET cmd */
	uint16_t		rls_service;	/* 72 : Time(ns) for bus-release after SERVICE cmd*/
	uint16_t		w73_74resv[2];	/* 73-74 : Reserved */
	uint16_t		w75_resv : 11,	/* 75_15-5 : Reserved */
				queue_depth:5;	/* 75_4-0  : Max. Queue Depth - 1*/
	uint16_t		w76_79resv[4];	/* 76-79 : Reserved */
	uint16_t		w80_resv :9,	/* 80_15-7 : Reserved for IDE 14-7 */
				ver6_supp :1,	/* 80_6 : IDE 6 support */
				ver5_supp :1,	/* 80_5	: IDE 5 support */  
				ver4_supp :1,	/* 80_4 : IDE 4 support */
				ver3_supp :1,	/* 80_3 : IDE   3 support */
				w80_resv1 :3;	/* 80_2-0 : reserved */
	uint16_t		ver_minor;	/* 81 : Minor version number */
	uint16_t		w82_resv :1;	/* 82_15 : reserved */
	uint16_t		cmd_nop  :1;	/* 82_14 : NOP cmd */
	uint16_t		cmd_readbuf :1; /* 82_13 : Read Buffer Cmd */
	uint16_t		cmd_writebuf :1;/* 82_12 : Write Buf */
	uint16_t		w82_resv2 :1 ;	/* 82_11 : Obsolete */
	uint16_t		cmd_hpaset :1;	/* 82_10 : Host Prot. Area feature set */
	uint16_t		cmd_devreset :1;/* 82_9  : Device Reset Cmd Support */		
	uint16_t		cmd_service :1; /* 82_8  : Service Interrupt Support */
	uint16_t		cmd_release :1; /* 82_7	 : Release Interrupt Support */
	uint16_t		cmd_lookahead :1; /* 82_6: Look Ahead Support */
	uint16_t		cmd_writecache :1;/* 82_5: Write Cache support */ 
	uint16_t		cmd_packet :1;	/* 82_4 : Support for Packet Commands */
	uint16_t		cmd_pwrmgmt :1;	/* 82_3	: Support for Pwr Mgmt */
	uint16_t		cmd_media :1;	/* 82_2 : Support for Removable Media */
	uint16_t		cmd_security:1;	/* 82_1 : Security Mode supported */
	uint16_t		cmd_smart:1;	/* 82_0 : SMART feature support */
	uint16_t		w83_resv :2;	/* 83_15-14 : Should be 0x01 */
	uint16_t		w83_resv2 :1;	/* 83_13 : Reserved */
	uint16_t		cmd_flushcache:1;/* 83_12: Flush Cache Cmd */
	uint16_t		cmd_devconf:1;	/* 83_11 : Dev. Conf Overlay Set */
	uint16_t		w83_48bitaddress : 1;	/* 83_10 : 48 Bit Addresses Supported */
	uint16_t		w83_acoustic :1;	/* 83_9 : Auto Acoustic Mgmt */
	uint16_t		cmd_setmax :1;	/* 83_8  : SET MAX cmd */
	uint16_t		w83_resv4 :1;	/* 83_7	 : reserved */
	uint16_t		cmd_setfeatures:1; /* 83_6 : Set Features Cmd */
	uint16_t		cmd_pwrup :1;	/* 83_5 : Power Up in Standby feature set */
	uint16_t		cmd_notifymedia :1; /* 83_4 : Rem. Media Set Notification supp*/
	uint16_t		w83_resv5 :3;	/* 83_3-1 : reserved */
	uint16_t		cmd_microcode :1;	/* 83_0 : Download MicroCode support */
	uint16_t		w84_resv :2;	/* 84_15-14 : Shallbe set to 0x01 */
	uint16_t		w84_resv2:14;	/* 84_13-0 : resv */
	uint16_t		w85_resv :1;	/* 85_15 : reserved */
	uint16_t		enb_nop  :1;	/* 85_14 : NOP cmd Enable */
	uint16_t		enb_readbuf :1; /* 85_13 : Read Buffer Cmd  Enable*/
	uint16_t		enb_writebuf :1;/* 85_12 : Write Buf Enable */
	uint16_t		w85_resv2 :1 ;	/* 85_11 : Obsolete */
	uint16_t		enb_hpaset :1;	/* 85_10 : Host Prot. Area feature set */
	uint16_t		enb_devreset :1;/* 85_9  : Device Reset Cmd Enable */		
	uint16_t		enb_service :1; /* 85_8  : Service Interrupt Enable */
	uint16_t		enb_release :1; /* 85_7	 : Release Interrupt Enable */
	uint16_t		enb_lookahead :1; /* 85_6: Look Ahead Enable */
	uint16_t		enb_writecache :1;/* 85_5: Write Cache Enable */
	uint16_t		enb_packet :1;	/* 85_4 : Enable Packet Commands */
	uint16_t		enb_pwrmgmt :1;	/* 85_3	: Enable Pwr Mgmt */
	uint16_t		enb_media :1;	/* 85_2 : Enable Removable Media */
	uint16_t		enb_security:1;	/* 85_1 : Security Mode enabled */
	uint16_t		enb_smart:1;	/* 85_0 : SMART feature enabled */
	uint16_t		w86_resv :2;	/* 86_15-14 : Should be 0x01 */
	uint16_t		w86_resv2 :1;	/* 86_13 : Reserved */
	uint16_t		sup_flushcache:1;/* 86_12: Flush Cache Cmd */
	uint16_t		sup_devconf:1;	/* 86_11 : Dev. Conf Overlay Set */
	uint16_t		w86_resv3 : 2;	/* 86_10-9 : resv */
	uint16_t		enb_setmax :1;	/* 86_8  : SET MAX cmd */
	uint16_t		w86_resv4 :1;	/* 86_7	 : reserved */
	uint16_t		sup_setfeatures:1; /* 86_6 : Set Features Cmd */
	uint16_t		enb_pwrup :1;	/* 86_5 : Power Up in Standby feature set */
	uint16_t		enb_notifymedia :1; /* 86_4 : Rem. Media Set Notification supp*/
	uint16_t		w86_resv5 :3;	/* 86_3-1 : reserved */
	uint16_t		enb_microcode:1;	/* 86_0 : Download MicroCode enabled */
	uint16_t		w87_resv :2;	/* 87_15-14 : set to 0,1 */
	uint16_t		w87_resv2:14;	/* resv */
	uint16_t		w88_resv:2;	/* 88_15-14 : resv */
	uint16_t		udma5_sel:1;	/* 88_13 : Ultra DMA mode 5 selected */
	uint16_t		udma4_sel:1;	/* 88_12 : Ultra DMA mode 4 selected */
	uint16_t		udma3_sel:1;	/* 88_11 : Ultra DMA mode 3 selected */
	uint16_t		udma2_sel:1;	/* 88_10 : Ultra DMA mode 2 selected */
	uint16_t		udma1_sel:1;	/* 88_9  : Ultra DMA mode 1 selected */
	uint16_t		udma0_sel:1;	/* 88_8  : Ultra DMA mode 0 selected */
	uint16_t		w88_resv2 :2;	/* 88_7-6: resv */
	uint16_t		udma5_sup:1;	/* 88_5 : Ultra DMA mode<=5 support */
	uint16_t		udma4_sup:1;	/* 88_4 : Ultra DMA mode<=4 support */
	uint16_t		udma3_sup:1;	/* 88_3 : Ultra DMA mode<=3 support */
	uint16_t		udma2_sup:1;	/* 88_2 : Ultra DMA mode<=2 support */
	uint16_t		udma1_sup:1;	/* 88_1 : Ultra DMA mode<=1 support */
	uint16_t		udma0_sup:1;	/* 88_0 : Ultra DMA mode<=0 support */
	uint16_t		w89_92resv[4];	/* 89-92: reserved */
	uint16_t		w93_resv:2;	/* 93_15-14 : resv */
	uint16_t		cblid:1;	/* 93_13: CBLID level */
	uint16_t		dev1_reset:5;	/* 93_12-8 : Dev 1 Hardware reset result */
	uint16_t		dev0_reset:8;	/* 93_7-0  : Dev 0 Hardware reset result */	
	uint16_t		w94_125resv[32];/* 94-125 reserved */	
	uint16_t		byte_count;	/* 126 : Set to 0x0 */
	uint16_t		w127_resv:14;	/* 127_15-2: Reserved */
	uint16_t		rmv_status:2;	/* 127_1-0 : Rem. Media Status Notify support */
	uint16_t		security_status;/* 128 : Security Status */
	uint16_t		w129_159resv[31];/* 129-159 : Vendor specific */		
	uint16_t		w160_175resv[16];/* 160_175 : CFA reserved */
	uint16_t		w176_254resv[79];/* 176_254 : CFA reserved */
	uint16_t		checksum :8,	/* 255_15-8 : Checksum */
				signature:8;	/* 255_7-0  : Signature*/
};	

/*
 * Spinlocks and mutexes both supported as compile time options
 */
#if IDE_SPINLOCKS
#define INITLOCK(l,n,s) init_spinlock(l, n, s)
#define IOLOCK(l,s)     s = io_splock(l)
#define IOUNLOCK(l,s)   io_spinlockspl(l, s)
#define IOTRYLOCK(l,s)  mutex_spintrylock_spl(l, s)
#define FREELOCK(l)     spinlock_destroy(l)
#else
#define INITLOCK(l,n,s) init_mutex(l, MUTEX_DEFAULT, n, s)
#define IOLOCK(l,s)     mutex_lock(&(l), PRIBIO)
#define IOUNLOCK(l,s)   mutex_unlock(&(l))
#define IOTRYLOCK(l,s)  mutex_trylock(&(l))
#define FREELOCK(l)     mutex_destroy(l)
#endif

//#if defined(IP35)
#if defined(IP32)
#define USE_DIRECT_PCI_TRANSLATION
#else
#define USE_MAPPED_PCI_TRANSLATION
#endif /* IP32 */

#define IDE_CLR_CACHE(req, adr, len)                      \
  if ((req->sr_flags & SRF_FLUSH) == SRF_FLUSH) {         \
    if ((req->sr_flags & SRF_DIR_IN) == SRF_DIR_IN)       \
      dki_dcache_inval(adr, len);                         \
    else                                                  \
      dki_dcache_wbinval(adr, len);                       \
  } 

#if IDE_KMEM_DEBUG
#define IDE_KMEM_ALLOC(k,s,f)                              \
   k = kmem_alloc(s,f);                                    \
   printf("xide alloc:  %x, size: %x\n", k, s);       

#define IDE_KMEM_ZALLOC(k,s,f)                             \
       k = kmem_zalloc(s, f);                              \
       printf("xide zalloc: %x, size: %x\n", k, s);

#define IDE_KMEM_FREE(a,s)                                 \
       kmem_free(a, s);                                    \
       printf("xide free:   %x, size: %x\n", a, s);
#else
#define IDE_KMEM_ALLOC(k,s,f) k = kmem_alloc(s,f);
#define IDE_KMEM_ZALLOC(k,s,f) k = kmem_zalloc(s,f);
#define IDE_KMEM_FREE(a,s) kmem_free(a,s);
#endif

#if IDE_CMD_DEBUG
extern 	xide_cmd_dbg_t   xide_cmd_list[IDE_CMD_IDX_SZ];
extern	int	 	xide_cmd_wrap;
extern 	int 		xide_cmd_index;
#endif

/*
 * Allows IDE_ASSERT to put us into the debugger
 */
#ifdef XSCSI
#if defined(CONFIG_XSCSI_IDE_KDB)
#define IDE_ASSERT(EX) if(!(EX)){printk("IDE_ASSERT FAIL "); printk("\n"); KDB_ENTER();}
#else
#define IDE_ASSERT(EX)
#endif
#else
#if defined(DEBUG)
#define IDE_ASSERT(EX) if(!(EX)){printf("IDE_ASSERT FAIL "); printf(#EX"\n"); debug("ring");}
#else
#define IDE_ASSERT(EX)
#endif
#endif

#ifdef SN
#define TIMEOUT_SPL     plbase
#else /* !SN */
#define TIMEOUT_SPL     plhi
#endif /* !SN */

#define MODE_SENSE6_CMD   0x1A
#define MODE_SENSE10_CMD  0x5A
#define MODE_SELECT6_CMD  0x15
#define MODE_SELECT10_CMD 0x55
#define READ_CAPACITY_CMD 0x25
#define READ10_CMD        0x28
#define WRITE10_CMD       0x2A
#define TEST_UNIT_READY   0x00

#define	UDMA		0x40
#define UDMA_5		0x45
#define UDMA_4		0x44
#define UDMA_3		0x43
#define UDMA_2		0x42
#define UDMA_1		0x41
#define UDMA_0		0x40
#define	PIO		0x08

#define MDMA 		0x20
#define MULTIDMA_2 	0x22
#define MULTIDMA_1 	0x21
#define MULTIDMA_0 	0x20

#define IDE_DMA_START	0x01
#define IDE_DMA_STOP	0x0
#define IDE_DMA_READ	0x00
#define IDE_DMA_WRITE	0x08

#define DMA_S_ACTIVE	0x01
#define DMA_S_ERROR	0x02
#define DMA_S_INTR	0x04
#define DMA_S_MASTER	0x20
#define DMA_S_SLAVE	0x40

#define IDE_CO_ACTIVE	0x01
#define IDE_CO_FREE	0x02

#define	IDE_START_TRANSFER 0x01
#define	IDE_MIDDLE_TRANSFER 0x02
#define	IDE_END_TRANSFER 0x04
#define	IDE_SPLIT_TRANSFER	0x10

#define	PIO_NONDATA	0x10
#define PIO_DATA_IN	0x20
#define PIO_DATA_OUT	0x20

#define CMD_OVERLAP 	0x02
#define CMD_NON_OVERLAP	0x01
#define CMD_DMA		0x40
#define CMD_PACKET	0x100
#define CMD_ATA_DMA	0x011400

#define HHR 			0x01 /* HardWare reset */
#define HIO 			0x10 

#define DEVICE_PROBE_OVER 	0x08 /* Device Probe Over */
#define OVERLAP			0x02 /* Overlapped Commands */	
#define NON_OVERLAP		0x04 /* No Overlapping Commands */
#define PACKET			0xA0 /* PKT Command Passed */				

#define	DMA			0x01
#define PKT_CMD_IN		0x10
#define PKT_BYTES_SENT		0x20
#define	PKT_DATA_TRANSFER	0x30
#define	PKT_DMA_START		0x40
#define	PKT_DMA_COMPLETE	0x50
#define CMD_COMPLETE		0x60
#define BUS_RELEASE		0x70

#define IDE_HOLD 0x03
#define IDE_NIEN 0x02
#define IDE_QUEUE_EMPTY 0x0
#define IDE_BUSY 	0x1

extern int	xide_devflag;
extern int	xidedebug;
extern 		xide_ProtoInfo_t *xide_proto_list;
extern int      xide_proto_num;

extern mutex_t	xide_connect_sema;


/**************************
   external declaration
**************************/

/* in irix/kern/mtune/kernel file */
extern int default_intr_pri;

/* in master.d file */
extern int            xide_print_sense;
extern int            xide_print_cmd;

/* in scsi.c */
extern char *scsi_adaperrs_tab[];

#ifndef XSCSI
void 			xide_init(void);
int			xide_attach(vertex_hdl_t vhdl);
#else
int __init 		xide_detect(void);
int __devinit		xide_attach(struct pci_dev *vhdl, const struct pci_device_id *pci_id);
#endif
void			xide_intr(xide_ProtoInfo_t  *pi);
void			xide_WatchdogTimer(xide_ProtoInfo_t *pi);
int			xide_ioctl(vertex_hdl_t proto_vhdl, uint cmd, struct scsi_ha_op *op);
int 			xide_dump(vertex_hdl_t proto_vhdl);
//void 			xide_free(vertex_hdl_t lun_vhdl, void (*cb)());
void			xide_free(vertex_hdl_t lun_vhdl, void (*cb)(vertex_hdl_t, uint8_t *));
//int			xide_alloc(vertex_hdl_t lun_vhdl, int opt, void (*cb)()); 
int			xide_alloc(vertex_hdl_t lun_vhdl, int opt, void (*cb)(vertex_hdl_t, uint8_t *)) ;
void 			xide_command(scsi_request_t *req);

#ifdef XSCSI
#undef PCI_OUTW // Syntax error in osdep_linux.h so this hack -> 6/10/02
#define PCI_OUTW(port,val)     outl(val, (unsigned long) (port)) 
struct scsi_atapi_args
{
   vertex_hdl_t  lun_vhdl;
   uint          read;          /* if 1 get blksize, if 0, set it to blksize */
   uint          blksize;
};
typedef struct scsi_atapi_args scsi_atapi_args_t;
#endif

#endif
