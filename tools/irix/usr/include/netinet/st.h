/*
 *               Copyright (C) 1997 Silicon Graphics, Inc.                
 *                                                                        
 *  These coded instructions, statements, and computer programs  contain  
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  
 *  are protected by Federal copyright law.  They  may  not be disclosed  
 *  to  third  parties  or copied or duplicated in any form, in whole or  
 *  in part, without the prior written consent of Silicon Graphics, Inc.  
 *                                                                        
 *
 *  Filename:     st.h
 *  Description:  Scheduled Transfer Protocol Headers
 */

#include <sys/endian.h>
#include <sys/types.h>

#ifndef __ST_H__
#define __ST_H__

/* Scheduled Transfer (ST) Header Definitions */

/*
 * ST Header Bit Flag Flags
 */
#define ST_FLAG_SHIFT   2
#define ST_FLAG_MASK    0x7ff

#define ST_FLAG_REJECT          0x01 
#define ST_FLAG_LAST            0x02
#define ST_FLAG_OUT_OF_ORDER    0x04
#define ST_FLAG_SEND_STATE      0x08
#define ST_FLAG_INTERRUPT       0x10
#define ST_FLAG_SILENT          0x20

#define ST_REJECT    (ST_FLAG_REJECT       << ST_FLAG_SHIFT)
#define ST_LAST      (ST_FLAG_LAST         << ST_FLAG_SHIFT)
#define ST_ORDER     (ST_FLAG_OUT_OF_ORDER << ST_FLAG_SHIFT)
#define ST_SENDSTATE (ST_FLAG_SEND_STATE   << ST_FLAG_SHIFT)
#define ST_INTERRUPT (ST_FLAG_INTERRUPT    << ST_FLAG_SHIFT)
#define ST_SILENT    (ST_FLAG_SILENT       << ST_FLAG_SHIFT)


/*
 * ST Header Bit Function Flags
 */
#define ST_FUNC_SHIFT   8

#define ST_FUNC_NOP             0
#define ST_FUNC_FETCH_INC       0x01
#define ST_FUNC_FETCH_DEC       0x02
#define ST_FUNC_FETCH_CLR       0x03
#define ST_FUNC_COMPLETE        0x07   

#define ST_FetchInc     (ST_FUNC_FETCH_INC << ST_FUNC_SHIFT)
#define ST_FetchDec     (ST_FUNC_FETCH_DEC << ST_FUNC_SHIFT)
#define ST_FetchClear   (ST_FUNC_FETCH_CLR << ST_FUNC_SHIFT)
#define ST_FetchCmplete (ST_FUNC_COMPLETE  << ST_FUNC_SHIFT)


/*
 * ST Header Opcode Flags
 */
#define	ST_OPCODE_MASK	0xf800
#define	ST_OPCODE_SHIFT	11

#define ST_OP_RCONNECT          0x01  /* request connection */
#define ST_OP_CANSWER           0x02  /* connection answer */
#define ST_OP_RDISCONNECT       0x03  /* request disconnect */
#define ST_OP_DANSWER           0x04  /* disconnect answer */
#define ST_OP_DCOMPLETE         0x05  /* disconnect complete */

#define ST_OP_NOP               0x010  /* nop */
#define ST_OP_RMR               0x013  /* request memory reg */
#define ST_OP_MRA               0x014  /* memory reg available */
#define ST_OP_GET               0x015  /* get,F&O, F&OComp */

#define ST_OP_RTS               0x016  /* request to send */
#define ST_OP_RANSWER           0x017  /* request answer */
#define ST_OP_RTR               0x018  /* request to receive */
#define ST_OP_CTS               0x01a  /* clear to send */

#define ST_OP_DATA              0x01b  /* data operation */
#define ST_OP_RS                0x01c  /* request state */
#define ST_OP_RSR               0x01d  /* request state response */
#define ST_OP_END               0x01e  /* end operation */
#define ST_OP_END_ACK           0x01f  /* end ack */ 

#define	ST_RCONNECT	(ST_OP_RCONNECT    << ST_OPCODE_SHIFT) /* request connection */
#define	ST_CANSWER	(ST_OP_CANSWER     << ST_OPCODE_SHIFT) /* connection answer */
#define	ST_RDISCONNECT	(ST_OP_RDISCONNECT << ST_OPCODE_SHIFT) /* request disconnect */
#define	ST_DANSWER	(ST_OP_DANSWER     << ST_OPCODE_SHIFT) /* disconnect answer */
#define	ST_DCOMPLETE	(ST_OP_DCOMPLETE   << ST_OPCODE_SHIFT) /* disconnect complete */

#define	ST_NOP		(ST_OP_NOP         << ST_OPCODE_SHIFT) /* nop */
#define	ST_RMR		(ST_OP_RMR         << ST_OPCODE_SHIFT) /* request memory reg */
#define	ST_MRA		(ST_OP_MRA         << ST_OPCODE_SHIFT) /* memory reg available */
#define	ST_GET		(ST_OP_GET         << ST_OPCODE_SHIFT) /* get,F&O, F&OComp */

#define	ST_RTS		(ST_OP_RTS         << ST_OPCODE_SHIFT) /* request to send */
#define	ST_RANSWER	(ST_OP_RANSWER     << ST_OPCODE_SHIFT) /* request answer */
#define	ST_RTR		(ST_OP_RTR         << ST_OPCODE_SHIFT) /* request to receive */
#define	ST_CTS		(ST_OP_CTS         << ST_OPCODE_SHIFT) /* clear to send */

#define	ST_DATA		(ST_OP_DATA        << ST_OPCODE_SHIFT) /* data operation */
#define	ST_RS		(ST_OP_RS          << ST_OPCODE_SHIFT) /* request state */
#define	ST_RSR		(ST_OP_RSR         << ST_OPCODE_SHIFT) /* request state response */
#define	ST_END		(ST_OP_END         << ST_OPCODE_SHIFT) /* end operation */
#define	ST_END_ACK	(ST_OP_END_ACK     << ST_OPCODE_SHIFT) /* end ack */

/* 
*  the "local" operations (read(), write(), timeout, pin-success/fail...
*  are also modelled as opcodes; the defs. for those are not a part of
*  ST; so, they are defined in st_var.h 
*/


/* ST_TOT_FLAGS is the minimum length of a char buffer the callers of
 * st_decode_flags() need to provide for st_decode_flags() to fill in the
 * decoded messages of ST Bit Flags. Here we assume ST_FetchInc, ST_FetchDec
 * ST_FetchClear, and ST_FetchCmplete are mutual exclusive.
 */
#define	ST_TOT_FLAGS	11

/*
 * ST parameters
 */
#define ST_MAX_VC 4



/*
 *  ST Header Structures
 * 
 *  ST Header Structure (based on opcode)     Typedef
 *  -------------------------------------------------------
 *  sth_request_connection_s	              sthdr_rc_t;
 *  sth_connection_answer_s	              sthdr_ca_t;
 *  sth_request_disconnect_s	              sthdr_rd_t;
 *  sth_disconnect_answer_s	              sthdr_da_t;
 *  sth_disconnect_complete_s	              sthdr_dc_t;
 *  sth_end_s                                 sthdr_end_t;
 *  sth_end_ack_s		              sthdr_eack_t;
 *  sth_request_to_send_s	              sthdr_rts_t;
 *  sth_request_answer_s	              sthdr_ra_t;
 *  sth_request_to_receive_s	              sthdr_rtr_t;
 *  sth_clear_to_send_s	                      sthdr_cts_t;
 *  sth_data_s		                      sthdr_data_t;
 *  sth_get_s			              sthdr_get_t;
 *  sth_request_memory_block_s                sthdr_rmb_t;
 *  sth_memory_block_available_s              sthdr_mba_t;
 *  sthdr_request_state_1_s                   sthdr_rs1_t;
 *  sthdr_request_state_response_1_s          sthdr_rsr1_t;
 *  sthdr_request_state_2_s                   sthdr_rs2_t;
 *  sthdr_request_state_response_2_s          sthdr_rsr2_t;
 *  sthdr_request_state_3_s                   sthdr_rs3_t;
 *  sthdr_request_state_response_3_s          sthdr_rsr3_t;
 *
 *
 *  ST Header Union:  sthdr_t
 */


typedef struct sthdr_request_connection_s {
	uint16_t	OpFlags;
	uint16_t	I_Slots;
	uint16_t unused_D_Port;
	uint16_t	I_Port; 
	uint32_t unused_D_Key;
	uint16_t    	Checksum;
	uint16_t	EtherType;
	uint32_t	I_Bufsize;
	uint32_t	I_Key;
	uint32_t	I_Max_Stu;
	uint32_t unused_B_num;
	uint32_t	R_UPort;
	uint32_t	I_UPort;
} sthdr_rc_t;

typedef struct sthdr_connection_answer_s {
	uint16_t	OpFlags;
	uint16_t	R_Slots;
	uint16_t	I_Port;
	uint16_t	R_Port;
	uint32_t	I_Key;
	uint16_t	Checksum;
	uint16_t unused_B_id;
	uint32_t	R_Bufsize;
	uint32_t	R_Key;
	uint32_t	R_Max_Stu;
	uint32_t unused_B_num;
	uint32_t	I_UPort;
	uint32_t	R_UPort;
} sthdr_ca_t;

typedef struct sthdr_request_disconnect_s {
	uint16_t	OpFlags;
	uint16_t unused_Param;
	uint16_t	R_Port;
	uint16_t	I_Port;
	uint32_t	R_Key;
	uint16_t	Checksum;
	uint16_t unused_B_id;
	uint32_t unused_Bufx;
	uint32_t	I_Key;
	uint32_t unused_Sync;
	uint32_t unused_B_num;
	uint32_t unused_D_id;
	uint32_t unused_S_id;
} sthdr_rd_t;

typedef struct sthdr_disconnect_answer_s {
	uint16_t	OpFlags;
	uint16_t unused_Param;
	uint16_t	I_Port;
	uint16_t	R_Port;
	uint32_t	I_Key;
	uint16_t	Checksum;
	uint16_t unused_B_id;
	uint32_t unused_Bufx;
	uint32_t	R_Key;
	uint32_t unused_Sync;
	uint32_t unused_B_num;
	uint32_t unused_D_id;
	uint32_t unused_S_id;
} sthdr_da_t;

typedef struct sthdr_disconnect_complete_s {
	uint16_t	OpFlags;
	uint16_t unused_Param;
	uint16_t	R_Port;
	uint16_t	I_Port;
	uint32_t	R_Key;
	uint16_t	Checksum;
	uint16_t unused_B_id;
	uint32_t unused_Bufx;
	uint32_t	I_Key;
	uint32_t unused_Sync;
	uint32_t unused_B_num;
	uint32_t unused_D_id;
	uint32_t unused_S_id;
} sthdr_dc_t;

typedef struct sthdr_nop {
	uint16_t	OpFlags;
	uint8_t		Opaque_A[2];
	uint16_t	R_Port;
	uint16_t	I_Port;
	uint32_t	R_Key;
	uint16_t	Checksum;
	uint8_t		Opaque_B[26];
} sthdr_nop_t;

typedef struct sthdr_end {
	uint16_t	OpFlags;
	uint16_t unused_Param;
	uint16_t	R_Port;
	uint16_t	I_Port;
	uint32_t	R_Key;
	uint16_t	Checksum;
	uint16_t unused_B_id;
	uint32_t unused_Bufx;
	uint32_t unused_Offset;
	uint32_t unused_Sync;
	uint32_t unused_B_num;
	uint32_t	R_id;
	uint32_t	I_id;
} sthdr_end_t;

typedef struct sthdr_end_ack_s {
	uint16_t	OpFlags;
	uint16_t unused_Param;
	uint16_t	I_Port;
	uint16_t	R_Port;
	uint32_t	I_Key;
	uint16_t	Checksum;
	uint16_t unused_B_id;
	uint32_t unused_Bufx;
	uint32_t unused_Offset;
	uint32_t unused_Sync;
	uint32_t unused_B_num;
	uint32_t	I_id;
	uint32_t	R_id;
} sthdr_endack_t;

typedef struct sthdr_request_to_send_s {
	uint16_t	OpFlags;
	uint16_t	CTS_req;
	uint16_t	R_Port;
	uint16_t	I_Port;
	uint32_t	R_Key;
	uint16_t	Checksum;
	uint16_t	Max_Block;
	uint32_t unused_Bufx;
	uint32_t unused_Offset;
	uint64_t	tlen;
	uint32_t	minus_one;
	uint32_t	I_id;
} sthdr_rts_t;

typedef struct sthdr_request_answer_s {
	uint16_t	OpFlags;
	uint16_t unused_Param;
	uint16_t	I_Port;
	uint16_t	R_Port;
	uint32_t	I_Key;
	uint16_t	Checksum;
	uint16_t unused_B_id;
	uint32_t unused_Bufx;
	uint32_t unused_Offset;
	uint32_t unused_Sync;
	uint32_t unused_B_num;
	uint32_t	I_id;
	uint32_t unused_S_id;
} sthdr_ra_t;

typedef struct sthdr_clear_to_send_s {
	uint16_t	OpFlags;
	uint16_t	Blocksize;
	uint16_t	I_Port;
	uint16_t	R_Port;
	uint32_t	I_Key;
	uint16_t	Checksum;
	uint16_t	R_Mx;
	uint32_t	R_Bufx;
	uint32_t	R_Offset;
	uint32_t	F_Offset;
	uint32_t	B_num;
	uint32_t	I_id;
	uint32_t	R_id;
} sthdr_cts_t;

typedef struct sthdr_data_s {
	uint16_t	OpFlags;
	uint16_t	STU_num;
	uint16_t	R_Port;
	uint16_t	I_Port;
	uint32_t	R_Key;
	uint16_t	Checksum;
	uint16_t	R_Mx;
	uint32_t	R_Bufx;
	uint32_t	R_Offset;
	uint32_t	Sync;
	uint32_t	B_num;
	uint32_t	R_id;
	uint32_t	Opaque;
} sthdr_data_t;

typedef struct sthdr_request_state_1_s {
	uint16_t	OpFlags;
	uint16_t unused_Param;
	uint16_t	R_Port;
	uint16_t	I_Port;
	uint32_t	R_Key;
	uint16_t	Checksum;
	uint16_t unused_B_id;
	uint32_t unused_Bufx;
	uint32_t unused_Offset;
	uint32_t	Sync;
	uint32_t unused_B_num;
	uint32_t	minus_one;
	uint32_t unused_S_id;
} sthdr_rs1_t;

typedef struct sthdr_request_state_response_1_s {
	uint16_t	OpFlags;
	uint16_t	R_Slots;
	uint16_t	I_Port;
	uint16_t	R_Port;
	uint32_t	I_Key;
	uint16_t	Checksum;
	uint16_t unused_B_id;
	uint32_t unused_Bufx;
	uint32_t unused_Offset;
	uint32_t	Sync;
	uint32_t unused_B_num;
	uint32_t	minus_one;
	uint32_t unused_S_id;
} sthdr_rsr1_t;

typedef struct sthdr_request_state_2_s {
	uint16_t	OpFlags;
	uint16_t unused_Param;
	uint16_t	R_Port;
	uint16_t	I_Port;
	uint32_t	R_Key;
	uint16_t	Checksum;
	uint16_t unused_B_id;
	uint32_t unused_Bufx;
	uint32_t unused_Offset;
	uint32_t	Sync;
	uint32_t	minus_one;
	uint32_t	R_id;
	uint32_t	I_id;
} sthdr_rs2_t;

typedef struct sthdr_request_state_response_2_s {
	uint16_t	OpFlags;
	uint16_t	R_Slots;
	uint16_t	I_Port;
	uint16_t	R_Port;
	uint32_t	I_Key;
	uint16_t	Checksum;
	uint16_t unused_B_id;
	uint32_t unused_Bufx;
	uint32_t	B_seq;
	uint32_t	Sync;
	uint32_t	minus_one;
	uint32_t	I_id;
	uint32_t	R_id;
} sthdr_rsr2_t;

typedef struct sthdr_request_state_3_s {
	uint16_t	OpFlags;
	uint16_t unused_Param;
	uint16_t	R_Port;
	uint16_t	I_Port;
	uint32_t	R_Key;
	uint16_t	Checksum;
	uint16_t unused_B_id;
	uint32_t unused_Bufx;
	uint32_t unused_Offset;
	uint32_t	Sync;
	uint32_t	B_num;
	uint32_t	R_id;
	uint32_t	I_id;
} sthdr_rs3_t;

typedef struct sthdr_request_state_response_3_s {
	uint16_t	OpFlags;
	uint16_t	R_Slots;
	uint16_t	I_Port;
	uint16_t	R_Port;
	uint32_t	I_Key;
	uint16_t	Checksum;
	uint16_t unused_B_id;
	uint32_t unused_Bufx;
	uint32_t	B_seq;
	uint32_t	Sync;
	uint32_t	B_num;
	uint32_t	I_id;
	uint32_t	R_id;
} sthdr_rsr3_t;

typedef struct sthdr_get_s {
	uint16_t	OpFlags;
	uint16_t	T_len;
	uint16_t	R_Port;
	uint16_t	I_Port;
	uint32_t	R_Key;
	uint16_t	Checksum;
	uint16_t	I_Mx;
	uint32_t	R_Bufx;
	uint32_t	R_Offset;
	uint32_t	I_Bufx;
	uint32_t	I_Offset;
	uint32_t	R_id;
	uint32_t	G_num;
} sthdr_get_t;

typedef struct sthdr_request_to_receive_s {
	uint16_t	OpFlags;
	uint16_t unused_Param;
	uint16_t	R_Port;
	uint16_t	I_Port;
	uint32_t	R_Key;
	uint16_t	Checksum;
	uint16_t unused_B_id;
	uint32_t unused_Bufx;
	uint32_t unused_Offset;
	uint64_t	T_len;
	uint32_t unused_D_id;
	uint32_t	I_id;
} sthdr_rtr_t;

typedef struct sthdr_request_memory_region_s {
	uint16_t	OpFlags;
	uint16_t	B_winreq;
	uint16_t	R_Port;
	uint16_t	I_Port;
	uint32_t	R_Key;
	uint16_t	Checksum;
	uint16_t unused_B_id;
	uint32_t unused_Bufx;
	uint32_t unused_Offset;
	uint64_t	T_len;
	uint32_t unused_D_id;
	uint32_t	I_id;
} sthdr_rmr_t;

typedef struct  sthdr_memory_region_available_s {
	uint16_t	OpFlags;
	uint16_t	B_win;
	uint16_t	I_Port;
	uint16_t	R_Port;
	uint32_t	I_Key;
	uint16_t	Checksum;
	uint16_t	R_Mx;
	uint32_t	R_Bufx;
	uint32_t	R_Offset;
	uint64_t	T_len;
	uint32_t	I_id;
	uint32_t	R_id;
} sthdr_mra_t;

typedef struct {
	uint16_t	OpFlags;
	uint16_t	Param;
	uint16_t	D_Port;
	uint16_t	S_Port;
	uint32_t	D_Key;
	uint16_t	Cksum;
	uint16_t	B_id;
	uint32_t	Bufx;
	uint32_t	Offset;
	uint32_t	Sync;
	uint32_t	B_num;
	uint32_t	D_id;
	uint32_t	S_id;
} sthdr_general_t;

typedef union {
	sthdr_rc_t	sth_rc; 
	sthdr_ca_t	sth_ca; 
	sthdr_rd_t	sth_rd; 
	sthdr_dc_t	sth_dc; 
	sthdr_da_t	sth_da; 
	sthdr_nop_t	sth_nop;
	sthdr_end_t	sth_end;
	sthdr_endack_t	sth_endack;

	sthdr_rts_t	sth_rts; 
	sthdr_ra_t	sth_ra;
	sthdr_rtr_t	sth_rtr;
	sthdr_cts_t	sth_cts;
	sthdr_data_t	sth_data; 
	sthdr_rs1_t	sth_rs1;
	sthdr_rsr1_t	sth_rsr1;
	sthdr_rs2_t	sth_rs2;
	sthdr_rsr2_t	sth_rsr2;
	sthdr_rs3_t	sth_rs3;
	sthdr_rsr3_t	sth_rsr3;
	sthdr_get_t	sth_get; 
	sthdr_rmr_t	sth_rmr; 
	sthdr_mra_t	sth_mra;
	sthdr_general_t	sth;
} sthdr_t;


/* For H800-FW debug only; 
*  THIS STRUCT WILL BE DELETED REAL SOON NOW!!!
*  Use at your own risk!
*
*  From rev 1.45 of the ST spec. */
typedef struct st_hdr_s {
    	uint16_t	op	: 5,
    			flags	: 11;
    	uint16_t	param;
    	uint16_t	d_port;
    	uint16_t	s_port;
    	uint32_t	d_key;
    	uint16_t	cksum;
    	uint16_t	mx;
    	uint32_t	bufx;
    	uint32_t	offset;
    	uint32_t	sync;
    	uint32_t	b_num;
    	uint32_t	d_id;
    	uint32_t	s_id;
} st_hdr_t;

typedef struct {
	uchar_t		c[32];
} stoption_t;

/* get/set operations that should be in ST */
/* kernel sockets */
#define	ST_CTS_OUTSTD		1
#define	ST_BLKSZ		2
#define	ST_BUFSZ		3
#define	ST_OUT_VCNUM		4
#define	ST_TX_SPRAY_WIDTH	5
#define	ST_RX_SPRAY_WIDTH	6
#define	ST_NUM_SLOTS		7
#define ST_MEMALLOC_POOL        10 
#define ST_STUSZ                11
#define ST_MAP_PORT_DIRECT      12
#define ST_USE_APPEND_PORT      13
#define ST_TX_CREDITS		14

/* Error values for upper layer */
#define EBADIFP     90
#define EBADBUFSIZE 91   

/* ST ULP MX errors */
#define EBADMX      101  /* An mx outside the st_ifnet, port, or bufx range */
#define EMXPOISON   102  /* A non-zero poison bit was given with the mx */
#define EMXSTUNUM   103  /* A non-zero stu-num was given with the mx */
#define EMXBADKEY   104  /* A key of 0 was given in set_mx */
#define EMXBADPORT  105  /* A port outside the st_ifp range in set_mx */
#define EMXBADBUFX  106  /* A bufx outside the st_ifp range in set_mx */

/* ST ULP PORT errors */
#define EBADPORT    110  /* A port outside of the st_ifp range was received */
#define EPORTBADBUFX 111 /* A bufx outside the st_ifp range in set_bufx */
#define EPORTBADKEY 112  /* A key of 0 was given in set_port */
#define EPORTNOMEM  113  /* Could not create descriptor Q for set_port */
#define EPORTDESSIZE 114 /* Port descriptor size is not a SHAC descriptor integral */
#define EPORTBADFLAGS 115 /* Flags specify illegal/impossible action */
#define EPORTNOTXSLOTS 116 /* Insufficient tx slots in pool for bypass job */

/* ST ULP BUFX errors */
#define EBADBUFX    120  /* A Bufx value outside the defined st_ifp range */
#define EBADSPRAY   121  /* Spray width is not legal for GSN */
#define EBUFXBADFLAGS 122 /* No flags value is supported by GSN bufx calls */

/* ST Output errors */
#define EBADVC      130  /* Invalid VC selected for message type/length */

/* OSbypass defines */

#define ST_BUFX_MAP_TX (1<<0)
#define ST_BUFX_MAP_RX (1<<1)

/*
 *  IOptional payload opcodes
 *
 *	command is defined as follows:
 *		first byte is the opcode
 *		second byte is the length includeing the first 2 bytes
 *		third through length - 2 is the payload
 *
 */
#define  ST_OPT_PAYLOAD_EOL			0x00	/* end of line */
#define  ST_OPT_PAYLOAD_NOOP			0x01	/* no-op operation */
#define  ST_OPT_PAYLOAD_LIN_ADDR_BASE		0x02	/* linear address base */
#define  ST_OPT_PAYLOAD_ULP_PARAM		0x03	/* ULP parameter */
#define  ST_OPT_PAYLOAD_ASCII_ERR_STRING	0x04	/* ascii error  string */
#define  ST_OPT_PAYLOAD_ERR_CODE		0x05	/* 2 byte error code */
#define  ST_OPT_PAYLOAD_VARBLK			0x06	/* variable block size and offset */

#define ST_OPT_PAYLOAD_EXPR_MASK		0x80	/* high bit set is "user" defined */
#define ST_OPT_PAYLOAD_IPADDRPAIR		0x90	/* IP address pair sent during CR */

/*
 *  Fixed lenght defines 
 */
#define ST_OPT__LAB_LEN				0x0a	/* length of lenear address base */
#define ST_OPT_ERR_CODE_LEN			0x04	/* length of error code  */
#define ST_OPT_VARBLK_LEN			0x10	/* length of variable block size */

#define ST_OPT_SST_LEN				0x20	/* sst optional payload length */

#define ST_OPT_MAX_LEN				0x20	/* max possible length for opt payload */
#define ST_OPT_MAX_SIZE				0x20	/* max size of opt payload space */

#endif	/* __ST_H__ */
