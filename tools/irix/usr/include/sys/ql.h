/*
 *    Unpublished copyright (c) 1995-2003 Silicon Graphics, Inc.
 *    THIS IS UNPUBLISHED CONFIDENTIAL AND PROPRIETARY SOURCE CODE OF SGI.
 *
 *    The copyright notice above does not evidence any actual or intended
 *    publication or disclosure of this source code, which includes
 *    information that is confidential and/or proprietary, and is a
 *    trade secret, of Silicon Graphics, Inc. ANY REPRODUCTION,
 *    MODIFICATION, DISTRIBUTION, PUBLIC PERFORMANCE, OR PUBLIC DISPLAY OF
 *    OR THROUGH USE OF THIS SOURCE CODE WITHOUT THE EXPRESS WRITTEN
 *    CONSENT OF SILICON GRAPHICS, INC. IS STRICTLY PROHIBITED, AND IN
 *    VIOLATION OF APPLICABLE LAWS AND INTERNATIONAL TREATIES. THE RECEIPT
 *    OR POSSESSION OF THIS SOURCE CODE AND/OR RELATED INFORMATION DOES
 *    NOT CONVEY OR IMPLY ANY RIGHTS TO REPRODUCE, DISCLOSE OR DISTRIBUTE
 *    ITS CONTENTS, OR TO MANUFACTURE, USE, OR SELL ANYTHING THAT IT
 *    MAY DESCRIBE, IN WHOLE OR IN PART. 
 */

#ifdef linux
#define XSCSI
#define _KERNEL
#endif

/****************************************************************/
/*								*/
/*          Compile time options                                */
/*								*/
/****************************************************************/
#if defined(SN0) || defined(IP30)
#define BRIDGE_B_PREFETCH_DATACORR_WAR
#endif

#define LOAD_VIA_DMA				/* load firmware with DMA  */
#define PROBE_ALL_LUNS			1
#define USE_MUTEX

#ifdef SN
#define SLOT_ONE			0x01
#define QL_SRAM_PARITY			1      	/* enable sram parity checking */
#define BUS_RESET_ON_INIT		1
#undef  USE_IOSPACE				/* Use MEM space for mapping QL registers */
#undef  FLUSH
#endif	/* SN */

#ifdef IP30
#define QL_SRAM_PARITY			1	/* enable sram parity checking */
#define BUS_RESET_ON_INIT		0
#define USE_IOSPACE				/* Use IO space for mapping QL registers */

#if HEART_COHERENCY_WAR
#define  FLUSH
#endif
#endif  /* IP30 */

#ifdef XSCSI
#undef QL_SRAM_PARITY				/* disable sram parity check, ok since there wont be any SGI
							built 1040's under linux */
#define BUS_RESET_ON_INIT		1
#ifdef CONFIG_IA64_SGI_SN
#undef USE_IOSPACE				/* Use MEM space for mapping QL registers */
#else
#define USE_IOSPACE
#endif
#endif /* XSCSI */


#ifdef _KERNEL
#ifndef XSCSI
#include <sys/ktypes.h>
#include <sys/scsi.h>
#endif

/**********************************************************
**
**      Debug definitions
*/

#ifdef PIO_TRACE
#define	 QL_LOG_CNT	512
#endif

/**********************************************************
**
**      General Information
*/

#define IOCB_SEGS			2
#define CONTINUATION_SEGS		5

#define MAX_CONTINUATION_ENTRIES	254

#define QL_MAXTARG		16
#define QL_MAXLUN		8

#define REQUEST_QUEUE_DEPTH     256	
#define RESPONSE_QUEUE_DEPTH    256 

#define MAX_REQ_INFO            255

#define DEF_EXECUTION_THROTTLE      255


/**********************************************************
**
**      Internal Command Information
*/

#define REQ_SENSE_DATA_LENGTH       32

/*********************************************************
**
**      Host Adapter Information
*/

/***
**** Queue Entry.
**** Used only to allocate space for request and response structures.
***/
typedef struct
{
    u_char      data[64];
} queue_entry;


/***
**** DATA SEGMENT structures.
***/
typedef struct
{
    u_int     base_low_32;
    u_int     base_high_32;
    u_int     count;
} ql_data_seg;


typedef struct req_information
{
    int			timeout;
    scsi_request_t*	req;
} REQ_INFO, *pREQ_INFO;


typedef struct
{
      /* bits */
    	u_char  Not_Used0           :3; /* 0,1,2 */
    	u_char  HA_Enable           :1; /* 3 */
    	u_char  Initiator_SCSI_Id   :4; /* 4,5,6,7 */

    	u_char  Bus_Reset_Delay;
    	u_char  Tag_Age_Limit;
    	u_short Selection_Timeout;

    	struct
    	{
    		union {
        		u_char  byte;   /* access by entire byte */
        		struct {                    /*bit*/
#ifdef __LITTLE_ENDIAN
            			u_char  Renegotiate_on_Error    :1; /* 0 */
            			u_char  Stop_Queue_on_Check :1; /* 1 */
            			u_char  Auto_Request_Sense  :1; /* 2 */
            			u_char  Tagged_Queuing      :1; /* 3 */
            			u_char  Sync_Data_Transfers :1; /* 4 */
            			u_char  Wide_Data_Transfers :1; /* 5 */
            			u_char  Parity_Checking     :1; /* 6 */
            			u_char  Disconnect_Allowed  :1; /* 7 */
#else
            			u_char  Disconnect_Allowed  :1; /* 7 */
            			u_char  Parity_Checking     :1; /* 6 */
            			u_char  Wide_Data_Transfers :1; /* 5 */
            			u_char  Sync_Data_Transfers :1; /* 4 */
            			u_char  Tagged_Queuing      :1; /* 3 */
            			u_char  Auto_Request_Sense  :1; /* 2 */
            			u_char  Stop_Queue_on_Check :1; /* 1 */
            			u_char  Renegotiate_on_Error    :1; /* 0 */
#endif
       		 	} bits;

    		} Capability;

    		u_char      Throttle;
    		u_char      Sync_Period;
                            /* bits */
    		u_char      Sync_Offset     :4; /* 0,1,2,3 */
    		u_char      Wide_Allowed    :1; /* 4 */
    		u_char      Sync_Allowed    :1; /* 5 */
    		u_char      Force_Sync      :1; /* 6 */
    		u_char      Is_CDROM        :1; /* 7 */
		u_char      dt              :1;	/* able to do dual transition */
						/* should probably be a capability bit */
    	} Id[QL_MAXTARG];

} Default_Parameters;


typedef struct chip_information 
{
    	/*
    	** Base I/O Address for this card.
    	** Make sure to convert this to a usable virtual address.
    	*/
    	caddr_t		ha_base;
	scsi_pci_vhdl_t	pci_vhdl;
	struct ha_information 	*ha_info[2];	/* point back the ha information */
	
	/* pci infrastructure vertex info */
    	vertex_hdl_t	ctlr_vhdl[2];

	u_int		chip_flags;		/* general flags for the chip */	
	u_short		device_id;
	u_short		revision;		/* PCI revision ID number */
	int		bridge_revnum;		/* bridge revision number */
	u_short		clock_rate;

	u_short		*risc_code;		/* risc code firmware data */

	u_short		risc_code_length;	/* risc code data length */
	u_short		risc_code_addr;		/* risc code starting address */

	u_short		channel_count;

  	/*
         ** Request and Response pointers
         */
        u_short         request_in;             /* request in pointer */
        u_short         request_out;            /* request out pointer */
        u_short         response_out;           /* response out pointer (copy of mailbox 5 OUT) */
        u_short         response_in;            /* response in pointer (copy of mailbox 5 IN) */

    	int             queue_space;

    	queue_entry*    request_ptr;
    	queue_entry*    request_base;
    	queue_entry*    response_ptr;
    	queue_entry*    response_base;

#ifndef XSCSI
    	pciio_dmamap_t  request_dmamap;
    	pciio_dmamap_t  response_dmamap;
#endif
    	paddr_t         request_dmaptr;
    	paddr_t         response_dmaptr;

#ifndef XSCSI
	pciio_piomap_t	rmap;
    	pciio_intr_t    intr_info;
#endif

    	/* scatter gather holding place */
    	alenlist_t  alen_p;


	/* locking resources */
    	mutex_t     probemutex;		/* guards addition/removal of devices/luns */
	mutex_t     mboxmutex;		/* guarantees 1 mbox command at any time */
#ifdef USE_MUTEX
	mutex_t	    ctlrlock;
#else
	lock_t      ctlrlock;		/* guards controller state and data */
	int         ctlrlockspl;
#endif
    	sema_t      mbox_done_sema;
#ifdef XSCSI
	sema_t	    intr_sema;
#endif
    	int         mbox_timeout_info;
    	u_short     mailbox[8];

#ifdef PIO_TRACE
    	uint        *ql_log_vals;
#endif

	/* chip default parameters */
	u_char		Retry_Count;
	u_char		Retry_Delay;

	u_short		req_rotor;
	char		chip_name[MAXDEVNAME];
	struct chip_information		*next_chip;

} CHIP_INFO, *pCHIP_INFO;

typedef struct ha_information
{

    	struct chip_information 	*chip_info;

    	u_int  	     	host_flags;		/* general flags for this adapter */

	/* scsi ctlr vertex info */
    	vertex_hdl_t	ctlr_vhdl;
    	/* bus quiesce timeout id's */
    	toid_t		quiesce_in_progress_id; /* how long to wait for quiesce to   */
						/* complete			     */
    	toid_t		quiesce_id;             /* id for quiesce_time	 	     */
    	int		quiesce_time;           /* how long to keep the bus quiesced */

    	/*
    	** General flags for each device.
    	** This is used to determine if the device driver
    	** has performed a SCSI_INIT on the device AND whether the
    	** device has been enabled in the NVRAM.
    	*/

    	/*
    	** Queued requests.
    	*/
    	scsi_request_t*     req_forw;
    	scsi_request_t*     req_back;

    	/* locations to store the outstanding requests and the associated alen_l */

	int		    tcmd[QL_MAXTARG];
    	int		    reqi_cntr[QL_MAXTARG];
    	pREQ_INFO	    reqi_block[QL_MAXTARG];

    	Default_Parameters    ql_defaults;

    	int			ql_ncmd;
    	scsi_request_t*     	waitf;
    	scsi_request_t*     	waitb;

	u_short			channel_id;	/* 1240, 1280, 12160 will have 0 and 1 */
	u_short			bus_mode;	/* SE, LVD, HVD */

	char			ha_name[MAXDEVNAME];
} HA_INFO, *pHA_INFO;

/*
** DMA Configurations Register definitions 
** command channel pci address 0x80
** data0 channel pci address 0xa0
** data1 channel pci address 0xc0
*/

#define DCR_DMA_DATA_XFER_DIRECTION      0x0001
#define DCR_DMA_BURST_ENABLE             0x0002
#define DCR_DMA_INTERRUPT_ENABLE         0x0004
#define DCR_DMA_REQUEST_FROM_SCSI	 0x0008

/*
 ** dma control register definitions
*/

#define DMA_CON_CLEAR_CHAN      0x8
#define DMA_CON_CLEAR_FIFO	0x4
#define DMA_CON_RESET_INT       0x2

/*
 * chip flags 
 * 
 */
#define AFLG_CHIP_INITIALIZED            0x0001		/* isp initialized */
#define AFLG_CHIP_INTERRUPTS_ENABLED     0x0002		/* interrupts enabled */
#define AFLG_CHIP_MAIL_BOX_DONE	    	 0x0004		/* mailbox is done */
#define AFLG_CHIP_MAIL_BOX_WAITING       0x0008		/* waiting mailbox to finish thru interrupt */
#define AFLG_CHIP_DID_BDRESET            0x0010		/* did board reset */
#define AFLG_CHIP_SHUTDOWN	    	 0x0020		/* board's dead */
#define AFLG_CHIP_IN_INTR                0x0040 	/* in interrupt */
#define AFLG_CHIP_DUMPING                0x0080		/* in dumping mode */
#define AFLG_CHIP_ASYNC_RESPONSE_IN      0x0100         /* async response coming in */
#define AFLG_CHIP_DOWNLOAD_FIRMWARE      0x0200		/* downloading firmware */
#define AFLG_CHIP_SRAM_PARITY            0x0400		/* checking sram parity capability */
#define AFLG_CHIP_SRAM_PARITY_ENABLE	 0x0800		/* enable sram parity memory checking */
#define AFLG_CHIP_WATCHDOG               0x1000		/* watchdog running */
#define AFLG_CHIP_MINTR_CHK		 0x2000		/* checks for missed interrupt */
#define AFLG_CHIP_DID_SLOTRESET          0x4000		/* did slot reset */

/* the following modes are mailbox polling modes */
#define AFLG_CHIP_MBOX_POLL		(AFLG_CHIP_IN_INTR | AFLG_CHIP_DUMPING | AFLG_CHIP_WATCHDOG | AFLG_CHIP_SRAM_PARITY)

/*
 * host adapter flags 
 *
 */
#define AFLG_HA_FAST_NARROW            0x00000001		/* marker needs to be send */
#define AFLG_HA_QUIESCE_IN_PROGRESS    0x00000002		/* quiesce in progress */
#define AFLG_HA_QUIESCE_COMPLETE       0x00000004		/* quiesce completed */
#define AFLG_HA_DRAIN_IO    	       0x00000008		/* drain I/O */
#define AFLG_HA_SEND_MARKER    	       0x00000010		/* fast and narrow setup */
#define AFLG_HA_BUS_SCAN_IN_PROGRESS   0x00000020		/* bus scan in progress */
#define AFLG_HA_TIMEOUT                0x00000040               /* t/o in progress */
#define AFLG_HA_TODRAINED              0x00000080		/* t/o has completed draining */
#define AFLG_HA_BUS_RESET              0x00000100		/* need bus reset */
#define AFLG_HA_TARGS                  0x00000200		/* targets present on this bus */

#define AFLG_HA_QUEUE_PROGRESS_FLAGS		(AFLG_HA_QUIESCE_IN_PROGRESS | AFLG_HA_QUIESCE_COMPLETE | AFLG_HA_DRAIN_IO)

/*
** Device flags.
*/
#define DFLG_INITIALIZED            0x0001
#define DFLG_INIT_IN_PROGRESS       0x0002 /* LUN Init in progress -- pause LUN queue */
#define DFLG_EXCLUSIVE              0x0004
#define DFLG_CONTINGENT_ALLEGIANCE  0x0008
#define DFLG_ABORT_IN_PROGRESS      0x0010 /* LUN Abort in progress -- pause LUN queue */
#define DFLG_SEND_MARKER            0x0020 /* Send LUN marker after LUN abort */
#define DFLG_BEHAVE_QERR1           0x0100 /* QERR=1 for this device */

/*
** Device capability bits.
*/
#define CAP_RENEGOTIATE_ON_ERROR	0x01
#define CAP_STOP_QUEUE_ON_CHECK         0x02
#define CAP_AUTO_REQUEST_SENSE          0x04
#define CAP_TAGGED_QUEUING		0x08
#define CAP_SYNC_DATA_TRANSFERS         0x10
#define CAP_WIDE_DATA_TRANSFERS         0x20
#define CAP_PARITY_CHECKING		0x40
#define CAP_DISCONNECT_PRIV		0x80


#define	QLOGIC_DEV_DESC_NAME	"Qlogic SCSI"

/****************************************************************
**
**  ISP Firmware Definitions
*/

/***
**** ENTRY HEADER structure.
***/
typedef struct
{
#ifdef __LITTLE_ENDIAN
    u_char      entry_type;
    u_char      entry_cnt;
    u_char      sys_def_1;
    u_char      flags;
#else
    u_char      flags;
    u_char      sys_def_1;
    u_char      entry_cnt;
    u_char      entry_type;
#endif
} entry_header;


/*
** Entry Header Type Defintions.
*/
#define ET_COMMAND              0x9
#define ET_CONTINUATION         0xa
#define ET_STATUS               3
#define ET_MARKER               4
#define ET_EXTENDED_COMMAND     5

/*
** Entry Header Flag Definitions.
*/
#define EF_CONTINUATION             0x01
#define EF_BUSY                     0x02
#define EF_BAD_HEADER               0x04
#define EF_BAD_PAYLOAD              0x08
#define EF_ERROR_MASK   (EF_BUSY | EF_BAD_HEADER | EF_BAD_PAYLOAD)


/***
**** COMMAND ENTRY structure.
***/
typedef struct
{
    entry_header    hdr;

    u_int       handle;

#ifdef __LITTLE_ENDIAN
    u_char	target_lun;
    u_char	target_id:7,
		channel_id:1;
    u_short	cdb_length;

    u_short	control_flags;
    u_short	reserved;

    u_short	time_out;
    u_short	segment_cnt;

    u_char	cdb0;
    u_char	cdb1;
    u_char	cdb2;
    u_char	cdb3;
    u_char	cdb4;
    u_char	cdb5;
    u_char	cdb6;
    u_char	cdb7;
    u_char	cdb8;
    u_char	cdb9;
    u_char	cdb10;
    u_char	cdb11;

#else
    u_short     cdb_length;
    u_char	channel_id:1,
         	target_id:7;
    u_char      target_lun;

    u_short     reserved;
    u_short     control_flags;

    u_short     segment_cnt;
    u_short     time_out;

    u_char      cdb3;
    u_char      cdb2;
    u_char      cdb1;
    u_char      cdb0;

    u_char      cdb7;
    u_char      cdb6;
    u_char      cdb5;
    u_char      cdb4;

    u_char      cdb11;
    u_char      cdb10;
    u_char      cdb9;
    u_char      cdb8;
#endif /* __LITTLE_ENDIAN */

    u_int       reserved2;
    u_int       reserved3;
    ql_data_seg dseg[IOCB_SEGS];
} command_entry;

/*
** Command Entry Control Flag Definitions.
*/
#define CF_NO_DISCONNECTS           0x0001
#define CF_HEAD_TAG                 0x0002
#define CF_ORDERED_TAG              0x0004
#define CF_SIMPLE_TAG               0x0008
#define CF_TARGET_ROUTINE           0x0010
#define CF_READ                     0x0020
#define CF_WRITE                    0x0040
#define CF_AUTO_SENSE_DISABLE       0x0100
#define CF_FORCE_ASYNCHONOUS        0x0200
#define CF_FORCE_SYNCHONOUS         0x0400
#define CF_INITIATE_WIDE       	    0x0800
#define CF_DISABLE_DATA_PARITY      0x1000
#define CF_STOP_QUEUE       	    0x2000
#define CF_SUPPORT_EXTENDED_SENSE   0x4000
#define CF_PRIORITY_FLAG       	    0x8000


/***
**** CONTINUATION ENTRY structures.
***/
typedef struct
{
    entry_header    hdr;
    ql_data_seg     dseg[CONTINUATION_SEGS];
} continuation_entry;


/***
**** MARKER ENTRY structure.
***/

typedef struct
{
    entry_header    hdr;

    u_int       reserved0;

#ifdef __LITTLE_ENDIAN
    u_char      target_lun;
    u_char	target_id:7,
		channel_id:1;
    u_char      modifier;
    u_char      reserved1;
#else
    u_char      reserved1;
    u_char      modifier;
    u_char	channel_id:1,
    	      	target_id:7;
    u_char      target_lun;
#endif

    u_char      reserved2[52];
} marker_entry;


/*
** Marker Entry Modifier Definitions.
*/
#define MM_SYNC_DEVICE          0
#define MM_SYNC_TARGET          1
#define MM_SYNC_ALL             2


/***
**** STATUS ENTRY structure.
***/

typedef struct
{
    entry_header  hdr;

    u_int       handle;

#ifdef __LITTLE_ENDIAN
    u_short     scsi_status;
    u_short     completion_status;

    u_short     state_flags;
    u_short     status_flags;

    u_short     time;
    u_short     req_sense_length;
#else
    u_short     completion_status;
    u_short     scsi_status;

    u_short     status_flags;
    u_short     state_flags;

    u_short     req_sense_length;
    u_short     time;
#endif

    u_int       residual;

    u_char      reserved[8];

    u_char      req_sense_data[32];
} status_entry;


/*
** Status Entry Completion Status Defintions.
*/
#define SCS_COMPLETE                	0x0000
#define SCS_INCOMPLETE              	0x0001
#define SCS_DMA_ERROR               	0x0002
#define SCS_TRANSPORT_ERROR         	0x0003
#define SCS_RESET_OCCURRED          	0x0004
#define SCS_ABORTED                 	0x0005
#define SCS_TIMEOUT                 	0x0006
#define SCS_DATA_OVERRUN            	0x0007
#define SCS_COMMAND_OVERRUN         	0x0008
#define SCS_ABORT_MSG_FAILED            0x000E
#define SCS_DEVICE_RESET_MSG_FAILED     0x0012
#define SCS_UNEXPECTED_BUS_FREE         0x0014
#define SCS_DATA_UNDERRUN           	0x0015
#define SCS_CMD_UNDERRUN		0x0016
#define SCS_SCSI_PHASE_SKIPPED          0x001D
#define SCS_AUTO_SENSE_FAILED           0x001E
#define SCS_WIDE_DATA_XFER_FAILED	0x001F
#define SCS_SYNC_DATA_XFER_FAILED	0x0020
#define SCS_LVD_BUS_ERROR		0x0021
#define SCS_DATA_CRC			0x0022

/*
** Status Entry State Flag Definitions.
*/
#define SS_GOT_BUS              	0x0100
#define SS_GOT_TARGET            	0x0200
#define SS_SENT_CDB             	0x0400
#define SS_TRANSFERRED_DATA         	0x0800
#define SS_GOT_STATUS               	0x1000
#define SS_GOT_SENSE                	0x2000
#define SS_TRANSFER_COMPLETE            0x4000

/*
** Status Entry Status Flag Definitions.
*/
#define SST_DISCONNECT                  0x0001
#define SST_SYNCHRONOUS                 0x0002
#define SST_PARITY_ERROR                0x0004
#define SST_BUS_RESET                   0x0008
#define SST_DEVICE_RESET                0x0010
#define SST_ABORTED            	        0x0020
#define SST_TIMEOUT                     0x0040
#define SST_NEGOTIATION                 0x0080

/*
** Mailbox Command Definitions.
*/
#define MBOX_CMD_EXECUTE_FIRMWARE       0x0002
#define MBOX_CMD_WRITE_RAM_WORD         0x0004
#define MBOX_CMD_READ_RAM_WORD          0x0005
#define MBOX_CMD_MAILBOX_REGISTER_TEST  0x0006
#define MBOX_CMD_ABOUT_FIRMWARE         0x0008
#define MBOX_CMD_LOAD_RAM_64		0x0009

#define MBOX_CMD_ABORT_DEVICE           0x0016
#define MBOX_CMD_BUS_RESET          	0x0018

#define MBOX_CMD_GET_FIRMWARE_STATUS    	0x001F
#define MBOX_CMD_GET_INITIATOR_SCSI_ID  	0x0020
#define MBOX_CMD_GET_SELECTION_TIMEOUT  	0x0021
#define MBOX_CMD_GET_RETRY_COUNT        	0x0022
#define MBOX_CMD_GET_TAG_AGE_LIMIT      	0x0023
#define MBOX_CMD_GET_CLOCK_RATE         	0x0024
#define MBOX_CMD_GET_ACTIVE_NEGATION_STATE  	0x0025
#define MBOX_CMD_GET_ASYNC_DATA_SETUP_TIME  	0x0026
#define MBOX_CMD_GET_BUS_CONTROL_PARAMETERS 	0x0027
#define MBOX_CMD_GET_TARGET_PARAMETERS      	0x0028
#define MBOX_CMD_GET_DEVICE_QUEUE_PARAMETERS    0x0029
#define MBOX_CMD_GET_RESET_DELAY_PARAMETERS	0x002A

#define MBOX_CMD_SET_INITIATOR_SCSI_ID      	0x0030
#define MBOX_CMD_SET_SELECTION_TIMEOUT      	0x0031
#define MBOX_CMD_SET_RETRY_COUNT        	0x0032
#define MBOX_CMD_SET_TAG_AGE_LIMIT      	0x0033
#define MBOX_CMD_SET_CLOCK_RATE         	0x0034
#define MBOX_CMD_SET_ACTIVE_NEGATION_STATE  	0x0035
#define MBOX_CMD_SET_ASYNC_DATA_SETUP_TIME  	0x0036
#define MBOX_CMD_SET_BUS_CONTROL_PARAMETERS 	0x0037
#define MBOX_CMD_SET_TARGET_PARAMETERS      	0x0038
#define MBOX_CMD_SET_DEVICE_QUEUE_PARAMETERS    0x0039
#define MBOX_CMD_SET_RESET_DELAY_PARAMETERS	0x003A

#define MBOX_CMD_SET_SYSTEM_PARAMETERS		0x0045
#define MBOX_CMD_GET_SYSTEM_PARAMETERS		0x0046
#define MBOX_CMD_SET_FIRMWARE_FEATURES		0x004A
#define MBOX_CMD_GET_FIRMWARE_FEATURES		0x004B


#define MBOX_CMD_GET_TRANSFER_MODE		0x0059
#define MBOX_CMD_SET_DATA_RECOVERY_MODE    	0x005A
#define MBOX_CMD_GET_DATA_RECOVERY_MODE         0x005B

/* 64 bit operation commands */
#define MBOX_CMD_DUMP_RAM_64                0x0051
#define MBOX_CMD_INIT_REQUEST_QUEUE_64      0x0052
#define MBOX_CMD_INIT_RESPONSE_QUEUE_64     0x0053
#define MBOX_CMD_EXECUTE_IOCB_64            0x0054


/*
** Mailbox Status Definitions.
*/
#define MBOX_STS_FIRMWARE_ALIVE         	0x0000
#define MBOX_STS_CHECKSUM_ERROR         	0x0001
#define MBOX_STS_SHADOW_LOAD_ERROR      	0x0002
#define MBOX_STS_BUSY               		0x0004

#define MBOX_STS_COMMAND_COMPLETE       	0x4000
#define MBOX_STS_INVALID_COMMAND        	0x4001
#define MBOX_STS_HOST_INTERFACE_ERROR   	0x4002
#define MBOX_STS_TEST_FAILED            	0x4003
#define MBOX_STS_COMMAND_ERROR          	0x4005
#define MBOX_STS_COMMAND_PARAMETER_ERROR    	0x4006
#define MBOX_STS_BUS_CONFIG_ERROR		0x4007

#define MBOX_ASTS_SCSI_BUS_RESET        	0x8001
#define MBOX_ASTS_SYSTEM_ERROR          	0x8002
#define MBOX_ASTS_REQUEST_TRANSFER_ERROR    	0x8003
#define MBOX_ASTS_RESPONSE_TRANSFER_ERROR   	0x8004
#define MBOX_ASTS_REQUEST_QUEUE_WAKEUP      	0x8005
#define MBOX_ASTS_EXECUTION_TIMEOUT_RESET	0x8006
#define MBOX_ASTS_EXTENDED_MESSAGE_UNDERRUN	0x800A
#define MBOX_ASTS_SCSI_BUS_HANG			0x800C
#define MBOX_ASTS_SCSI_BUS_RESET_BY_ISP		0x800D
#define MBOX_ASTS_SCSI_BUS_MODE_TRANSITION	0x800E
#define MBOX_ASTS_SCSI_TARG_RATE_REDUCED	0x800F
#define MBOX_ASTS_NO_MEM			0x8010
#define MBOX_ASTS_FAST_POSTING_EVENT_CODE	0x8020
#define MBOX_ASTS_RIO_ONE_32			0x8021
#define MBOX_ASTS_RIO_TWO_32			0x8022
#define MBOX_ASTS_RIO_ONE_16			0x8031
#define MBOX_ASTS_RIO_TWO_16			0x8032
#define MBOX_ASTS_RIO_THREE_16			0x8033
#define MBOX_ASTS_RIO_FOUR_16			0x8034
#define MBOX_ASTS_RIO_FIVE_16			0x8035



/****************************************************************
**
**  ISP Register Definitions
**  These register definitions assume a 32 bit PCI interface (for PIO)
**  on a big endian machine.  For 32 bit PCI little endian, macros used
**  to access them need to XOR the address with 2.
*/

typedef volatile struct
{
    /*
    ** Bus interface registers.
    */                      /* Offsets  */


    u_short bus_id_high;        /* 0002 */
    u_short bus_id_low;         /* 0000 */

    u_short bus_config1;        /* 0006 */
    u_short bus_config0;        /* 0004 */

    u_short bus_isr;            /* 000A */
    u_short bus_icr;            /* 0008 */

    u_short NvRam_reg;		/* 000E */
    u_short bus_sema;           /* 000C */


    /*
    ** Skip over DMA Controller registers:
    **   0020-002F - Command DMA Channel
    **   0040-004F - Data DMA Channel ----- 
    **			except for the dma config and control reg
    **   0060-0063 - DMA FIFO Access Ports
    */

    u_char  not_used[0x0010];

	/* NOTE:  control_dma_* and data_dma_* are 1040 only */
    u_short control_dma_control;           /* 0022 */
    u_short control_dma_config;	           /* 0020 */
    u_short control_dma_fifo_status;       /* 0026 */
    u_short control_dma_status;	           /* 0024 */
    u_short control_dma_reserved;          /* 002a */
    u_short control_dma_counter;           /* 0028 */
    u_short control_dma_address_counter_1; /* 002e */
    u_short control_dma_address_counter_0; /* 002c */
    u_short control_dma_address_counter_3; /* 0032 */
    u_short control_dma_address_counter_2; /* 0030 */


    u_char  not_used0[0x000c];


    u_short data_dma_control;	           /* 0042 */
    u_short data_dma_config;	           /* 0040 */
    u_short data_dma_fifo_status;          /* 0046 */
    u_short data_dma_status;	           /* 0044 */
    u_short data_dma_xfer_counter_high;	   /* 004a */
    u_short data_dma_xfer_counter_low;     /* 0048 */
    u_short data_dma_address_counter_1;	   /* 004e */
    u_short data_dma_address_counter_0;	   /* 004c */
    u_short data_dma_address_counter_3;	   /* 0052 */
    u_short data_dma_address_counter_2;	   /* 0050 */


    u_char  not_used1[0x001c];

    /*
    ** Mailbox registers.
    */
    u_short mailbox1;           /* 0070     */
    u_short mailbox0;           /* 0072     */
    u_short mailbox3;           /* 0074     */
    u_short mailbox2;           /* 0076     */
    u_short mailbox5;           /* 0078     */
    u_short mailbox4;           /* 007A     */
    u_short mailbox7;           /* 007C     */
    u_short mailbox6;           /* 007E     */


    /*
    ** Note: in V3 part, RISC and SXP registers are paged.
    ** Since we don't use SXP registers, we won't define them. (only 1040 fw)
    ** - 1080/1240/1280 fw will be using this bank of register for DMA, SXP, and RISC.
    */

    /*
    ** 
    **  0080-00BF - RISC Registers.
    */

    u_short r1;			/* 82   */
    u_short accumulator;	/* 80	*/
    
    u_short r3;			/* 86   */
    u_short r2;			/* 84   */

    u_short r5;			/* 8a   */
    u_short r4;			/* 88   */

    u_short r7;			/* 8e   */
    u_short r6;			/* 8c   */

    u_short r9;			/* 92   */
    u_short r8;			/* 90   */

    u_short r11;		/* 96   */
    u_short r10;		/* 94   */

    u_short r13;		/* 9a   */
    u_short r12;		/* 98   */

    u_short r15;        	/* 9e   */
    u_short r14;		/* 9c   */


    u_short ivr;		/* a2   */
    u_short psr;		/* a0   */

    u_short rar0;		/* a6   */
    u_short pcr;		/* a4   */

    u_short lcr;		/* aa   */
    u_short rar1;		/* a8   */

    u_short mtr;		/* ae, mtr on 1040 only   */
    u_short risc_pc;    	/* ac	*/

    u_short sp;			/* b2   */
    u_short mctr;		/* b0, emb on 1040, mctr on everything else   */

    u_short b6;			/* b6   */
    u_short b4;			/* b4   */

    u_short lvdi;		/* ba, undef on 1040, lvd interrupt status on else   */
    u_short b8;			/* b8   */

    u_short hardware_revision;	/* be   */
    u_short bc;			/* bc	*/

    /*
    ** Host Configuration and Control register.
    */
    u_short c2;			/* c2   */
    u_short hccr;               /* c0     */

    u_short c6;			/* c6   */
    u_short c4;			/* c4   */

    u_short ca;			/* ca   */
    u_short c8;			/* c8   */

    u_short ce;			/* ce   */
    u_short cc;			/* cc	*/

    u_short d2;			/* d2   */
    u_short d0;			/* d0   */

    u_short d6;			/* d6   */
    u_short d4;			/* d4   */

    u_short da;			/* da   */
    u_short d8;			/* d8   */

    u_short de;			/* de   */
    u_short dc;			/* dc	*/

    u_short e2;			/* e2   */
    u_short e0;			/* e0   */

    u_short e6;			/* e6   */
    u_short e4;			/* e4   */

    u_short ea;			/* ea   */
    u_short e8;			/* e8   */

    u_short ee;			/* ee   */
    u_short ec;			/* ec	*/

    u_short f2;			/* f2   */
    u_short f0;			/* f0   */

    u_short f6;			/* f6   */
    u_short f4;			/* f4   */

    u_short fa;			/* fa   */
    u_short f8;			/* f8   */

    u_short fe;			/* fe   */
    u_short fc;			/* fc	*/


} ISP_REGS, *pISP_REGS;




/*
** Bus Configuration Register 1 Definitions.
*/
#define CONF_1_BURST_ENABLE     0x0004
#define CONF_1_1240_DMA_SEL     0x0300  /* Select DMA bank */


/* this set the high water mark to 32 bytes (16) observed */


/*
** Bus Control Register Definitions.
*/
#define ICR_SOFT_RESET		0x0001
#define ICR_ENABLE_ALL_INTS	0x0002
#define ICR_ENABLE_RISC_INT	0x0004


/*
** Bus Interrupt Status Register Defintions.
*/
#define BUS_ISR_RISC_INT	0x0004


/*
** Bus Semaphore Register Definitions.
*/
#define BUS_SEMA_LOCK           0x0001


/*
** Host Command and Control Register Definitions.
*/

        /* Command Definitions */

#define HCCR_CMD_RESET              0x1000  /* reset RISC */
#define HCCR_CMD_PAUSE              0x2000  /* pause RISC */
#define HCCR_CMD_RELEASE            0x3000  /* release paused RISC */
#define HCCR_CMD_SET_HOST_INT       0x5000  /* set host interrupt */
#define HCCR_CMD_CLEAR_RISC_INT     0x7000  /* clear RISC interrupt */
#define HCCR_SRAM_PARITY_ENABLE     0xA000  /* enable sram parity */
#define HCCR_FORCE_PARITY_ERROR     0xE000  /* force sram parity error*/



        /* Status Defintions */
#define HCCR_SRAM_PARITY_ERROR_DETECTED_1040  0x0400  /* R: parity error detected */
#define HCCR_SRAM_PARITY_BANK2  0x0400  /* R: bank two enable */
#define HCCR_SRAM_PARITY_BANK1  0x0200  /* R: bank one enable */
#define HCCR_SRAM_PARITY_BANK0  0x0100  /* R: bank zero enable */
#define HCCR_HOST_INT       	0x0080  /* R: host interrupt set */
#define HCCR_RESET          	0x0040  /* R: RISC reset in progress */
#define HCCR_PAUSE          	0x0020  /* R: RISC paused */




/****************************************************************
*/
#define INQUIRY_CMD	0x12


/********************************************************************
**
**                           Constants
*/


/* clock rates for ISP1020 and ISP1040 */

#define FAST_CLOCK_RATE 40
#define FAST20_CLOCK_RATE 60
#define FAST40_CLOCK_RATE 100		/* 1080 and 1280 only */
#define FAST80_CLOCK_RATE 80		/* 12160 */


/*
 * SCSI Bus operation modes are determined by the DIFFM and DIFFS pins.
 */
#define SCSI_BUS_MODE_SINGLE_ENDED	0x0001
#define SCSI_BUS_MODE_HVD		0x0002
#define SCSI_BUS_MODE_LVD		0x0004

/* This is for bit mask when 0x800E Asynchronous event code return and the data is mailbox1 */
#define SCSI_BUS_MODE_MASK 		0x0007


/********************************************************************
**
**                           Structures
*/

/*
** Host Adapter defaults.
*/

/* new threshold control in Config Register 1   */
/* bits		name				*/
/* 15->8	reserved                        */
/* 7->4         Extended FIFO control           */
/* 3            SXP Register Select             */
/* 2            Burst enable                    */
/* 1->0         FIFO control                    */
/*                                              */
/*                                              */
/* the original 1020 only used bits 0 and 1     */
/* but this could not occomodate 128 the btye option*/
/* Now only use the Extended FIFO control       */

/*  bits 7->4	bits 1->0	burst size	*/
/*						*/ 
/* 	6		x	512		*/
/*	5		x  	256		*/
/*   	4		x	128		*/
/*   	3		x	64		*/
/*   	2		x	32		*/
/*   	1		x	16		*/
/*   	0		3	64		*/
/*   	0		2	32		*/
/*   	0		1	16		*/
/*   	0		0	8		*/

#define BURST_512 0x60			/* for 1240 1080, and 1280 chips only */
#define BURST_256 0x50			/* for 1240 1080, and 1280 chips only */
#define BURST_128 0x40
#define BURST_64  0x30
#define BURST_32  0x20
#define BURST_16  0x10



#define HA_ENABLE             		1   /* enabled */
#if defined(XSCSI) && defined(CONFIG_IA64_DIG)
#define INITIATOR_SCSI_ID     		7	/* Need to use a default ID of 7 on the 750, system disk conflict on 0 */
#else
#define INITIATOR_SCSI_ID     		0
#endif
#define BUS_RESET_DELAY       		3   /* 3 seconds */
#define RETRY_COUNT           		0   /* no retries */
#define RETRY_DELAY           		0   /* no time between tries*/
#define ASYNC_DATA_SETUP_TIME     	8   /* was 9 clock periods, but is reserved on 12160  */
#define REQ_ACK_ACTIVE_NEGATION   	0x01   /* enabled */
#define DATA_ACTIVE_NEGATION      	0x01   /* enabled */
#define DATA_DMA_BURST_ENABLE     	0x01   /* enabled */
#define CMD_DMA_BURST_ENABLE      	0x01   /* enabled */

#define TAG_AGE_LIMIT         		8

#define SELECTION_TIMEOUT       	250 /* 250 ms */

#define MAX_QUEUE_DEPTH       		256 /* scsi target queue */

#define DELAY_AFTER_RESET      		1   /*second*/

/* special firmware features for 1240/1280/12160 */
#define QL_FIRMWARE_SGICACHE		0x200	/* enable SGI cache flush */
#define QL_FIRMWARE_FAIRNESS		0x100	/* disable reselection fairness */
#define QL_FIRMWARE_BACKOFF		0x20	/* disable synchronous backoff */

/* 12160 PPR bits */
#define QL_PPR_WIDE			0x01	/* select wide transfer */
#define QL_PPR_DUAL			0x200	/* select dual transition */
#define QL_PPR_ENABLE			0x20

/*
** Drive defaults.
*/
#define RENEGOTIATE_ON_ERROR      1   /* ON */
#define STOP_QUEUE_ON_CHECK       0   /* OFF */
#define AUTO_REQUEST_SENSE        1   /* ON  */
#define TAGGED_QUEUING       	  1   /* ON */
#define SYNC_DATA_TRANSFERS       1   /* ON */
#define WIDE_DATA_TRANSFERS       1   /* ON */
#define PARITY_CHECKING           1   
#define DISCONNECT_ALLOWED        1   
#define EXECUTION_THROTTLE        255
#define SYNC_PERIOD           	  25  /* 100 ns */
#define SYNC_PERIOD_FAST20        12  /*  50 ns */
#define SYNC_PERIOD_FAST40	  10  /* 25 ns */
#define SYNC_PERIOD_FAST40SE      12
#define SYNC_PERIOD_FAST80        9
#define SYNC_PERIOD_FAST80SE      12
#define SYNC_OFFSET               8
#define SYNC_OFFSET_12160	  0x0E
#define MAX_SYNC_OFFSET		  12
#define MAX_SYNC_OFFSET_12160     0x1c
#define DEFAULT_TIMEOUT		  10 /* default scsi timeout is 10 sec */
#define FIRMWARE_FEATURES	  0x0002


/*
 * ISP1020/ISP1040 
 * note that this is the same as 1020 
 * early part were speed graded only  
 */
#define REV_ISP1020	(ISP1040_STARTING_REV_NUM + 1)

#define REV_ISP1040     1 
#define REV_ISP1040A    2
#define REV_ISP1040AV4  3 
#define REV_ISP1040B    4
#define REV_ISP1040BV2	5 /* qlogic 1040B rev 2 */


/* the following are defines for MBOX_CMD_SET_DATA_RECOVERY_MODE */
/* we are supporting mode 2 right now 				 */
#define DATA_OVERRUN_MODE_0  0 	/* pad data until the target switches out */
				/* of data phase 		          */		
#define DATA_OVERRUN_MODE_1  1  /* hang the bus interrupt host with       */
				/* 0x800c in outgoing mailbox 0 register  */
				/* the host must reset the bus with mail  */
				/* box command				  */

#define DATA_OVERRUN_MODE_2  2  /* ISP resets the SCSI bus places 0x800D  */
				/* in outgoing mailbox 0 and returns all  */
				/* outstanding io's			  */

/**********************************************************
**
**          our PCI Information
*/

#ifndef XSCSI
/*
** PCI Bus configuration space registers.
*/
typedef struct PCI_Config_Registers
{
    u_short Device_Id;
    u_short Vendor_Id;      /* 00 */

    u_short Status;
    u_short Command;        /* 04 */

    u_char  Class_Code[3];
    u_char  Rev_Id;         /* 08 */


    u_char  Bits;
    u_char  Header_Type;
    u_char  Latency_Timer;
    u_char  Cache_Line_Size;    /* 0C */


    u_int   IO_Base_Address;    /* 10 */

    u_int   Memory_Base_Address;    /* 14 */

    u_int   Not_Used1[6];       /* 18 - 2F */

    u_int   ROM_Base_Address;   /* 30 */

    u_int   Not_Used2[2];       /* 34 - 3B */

    u_char  Interrupt_Line;     /* 3C */
    u_char  Interrupt_Pin;
    u_char  Minimum_Grant;
    u_char  Maximum_Latency;

    u_short ISP_Config_1;       /* 40 */
    u_short Not_Used3;

} PCI_REG, *pPCI_REG;
#endif


/*
** Configuration space offsets:
*/

#define     QLogic_VENDOR_ID            0x1077

#define     QLogic_1040_DEVICE_ID       0x1020
#define	    QLogic_1240_DEVICE_ID	0x1240
#define	    QLogic_1080_DEVICE_ID	0x1080
#define     QLogic_1280_DEVICE_ID	0x1280
#define	    QLogic_12160_DEVICE_ID	0x1216


/*
 * info specific to the ql lun vertex
 */

typedef struct ql_local_info {
	mutex_t			qli_openmutex;	
	u_int			qli_dev_flags;	/* lun device flags */
	int			qli_ref_count;	/* no. of references */
	int                     qli_cmd_rcnt;   /* issued command count to this LUN */
	scsi_request_t*         qli_awaitf;     /* forward pointer for commands awaiting abort completion */
	scsi_request_t*         qli_awaitb;     /* backward pointer for commands awaiting abort completion */
	scsi_request_t*         qli_iwaitf;     /* forward pointer for commands awaiting init. completion */
	scsi_request_t*         qli_iwaitb;     /* backward pointer for commands awaiting init. completion */
	scsi_target_info_t	*qli_tinfo;	/* scsi target info */
	void                   (*qli_sense_callback)(vertex_hdl_t, uint8_t *);	/* Sense callback routine */
	int			rev;		/* scsi rev of target */
						/* belongs in targ info */
#ifdef XSCSI
	spinlock_t		qli_lock;	/* short term lock for fields not fully guarded by chip_lock */
#else
	lock_t			qli_lock;	/* short term lock for fields not fully guarded by chip_lock */
#endif
} ql_local_info_t;
	
/*
 * macros associated with this structure	
 */
#define	QLI_OPENMUTEX(p)	(p->qli_openmutex)
#define QLI_TINFO(p)		(p->qli_tinfo)

/*
 * macros associated with the scsi lun info structure specific
 * to ql
 */

#define QL_OPENMUTEX(p)		QLI_OPENMUTEX(((ql_local_info_t *)p))
#define QL_TINFO(p)		QLI_TINFO(((ql_local_info_t *)p))

#define OPEN_MUTEX(p)		QL_OPENMUTEX(SLI_INFO(p))
#define TINFO(p)		QL_TINFO(SLI_INFO(p))

#define SCI_HA_INFO(p)		((pHA_INFO)(SCI_INFO(p)))
#define SLI_HA_INFO(p)		((pHA_INFO)(SCI_INFO(SLI_CTLR_INFO(p))))

#endif /* KERNEL */

/*
** Some miscellaneous configuration parameters.
*/

#define QL_RESET 	1000
#define QL_COMPUTE_PARITY_MEMORY	4000
#define WATCHDOG_TIME      10  /* for bringup set to 10 */
#define SCSI_INFO_BYTE          7
#define SCSI_CTQ_BIT            2

/*
 * Encoding of GPIO bits on channel 0 - MSCSI/A
 * [3](r)    [2](r)    [1](w)    [0](w)
 * 0 = in slot XIO1      
 * 1 = not in slot XIO1              
 *           diffsense 
 *                     0 = no internal terminator
 *                     1 = internal terminator
 *                               0 = internal bus selected
 *                               1 = external bus selected
 * 
 * Encoding of GPIO bits on channel 0 - MSCSI/B
 * [3](r)    [2](r)    [1](w)    [0](w)
 * 0 = in slot XIO1      
 * 1 = not in slot XIO1              
 *           not connected
 *                     0         0 = Internal SE selected
 *                     0         1 = External SE selected
 *                     1         0 = External DF (no termination)
 *                     1         1 = External DF (termination)
 *
 */
#define GPIO0             0x01
#define GPIO1             0x02
#define GPIO2             0x04
#define GPIO3             0x08
#define ENABLE_WRITE      (GPIO0 | GPIO1)
#define ENABLE_WRITE_SN00 0x01
#define NOT_SLOT_ZERO     GPIO3

/*
 * The IOCB handle is comprised of the following
 *        15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
 *        -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
 *                 PP UU UU UU UU TT TT TT TT TT TT TT TT
 *  where PP = port number; 0-1
 *        UU = unit number; 0-15
 *        TT = command index; 0-255
 */
#define MAX_HANDLE_NO (0x1000 | ((QL_MAXTARG - 1) * (MAX_REQ_INFO + 1)) | MAX_REQ_INFO)

#define QL_MUTEX_PRI		PRIBIO
#define QL_SEMA_PRI		PRIBIO

#define QL_INIT_MUTEX(l,n,s)	init_mutex(&(l), MUTEX_DEFAULT, n, s)

#define QL_MUTEX_LOCK(l)	mutex_lock(&(l), QL_MUTEX_PRI)
#define QL_MUTEX_UNLOCK(l)	mutex_unlock(&(l))


#ifdef USE_MUTEX
#define QL_INIT_LOCK(l,n,s)	init_mutex(l, MUTEX_DEFAULT, n, s)
#define QL_LOCK(p)		mutex_lock(&(p->ctlrlock), QL_MUTEX_PRI)
#define QL_UNLOCK(p)		mutex_unlock(&(p->ctlrlock))
#else
#define QL_INIT_LOCK(l,n,s)	init_spinlock(l, n, s)
#define QL_LOCK(p)		p->ctlrlockspl=mutex_spinlock(&p->ctlrlock)
#define QL_UNLOCK(p)		mutex_spinunlock(&p->ctlrlock, p->ctlrlockspl)
#endif

#ifdef XSCSI
#define QL_SPVAR		;
#define QL_SPLOCK(l,s)		spin_lock(&(l))
#define QL_SPUNLOCK(l,s)	spin_unlock(&(l))
#define QL_SPINIT_LOCK(l,n,s)	spin_lock_init(&l)
#define QL_SPLOCK_DESTROY(l)  	;
#else
#define QL_SPVAR		int s;
#define QL_SPLOCK(l,s)		s=mutex_spinlock(&l)
#define QL_SPUNLOCK(l,s)	mutex_spinunlock(&l,s)
#define QL_SPINIT_LOCK(l,n,s)	init_spinlock(&l, n, s)
#define QL_SPLOCK_DESTROY(l)  	spinlock_destroy(&l)
#endif

#define QL_MAXWAIT		2147483647	/* 2^31-1 */

#define QL_INITISP_LOCK		1
#define QL_INITISP_NOLOCK	0
