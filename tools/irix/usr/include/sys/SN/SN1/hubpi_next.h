/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1999, Silicon Graphics, Inc.               *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 **************************************************************************/

#ifndef __SYS_SN_SN1_HUBPI_NEXT_H__
#define __SYS_SN_SN1_HUBPI_NEXT_H__

/* define for remote PI_1 space. It is always half of a node_addressspace
 * from PI_0. The normal REMOTE_HUB space for PI registers access
 * the PI_0 space, unless they are qualified by PI_1.
 */
#define PI_0(x)			(x)
#define PI_1(x)			((x) + 0x200000)
#define PIREG(x,sn)		((sn) ? PI_1(x) : PI_0(x))

#define PI_MIN_STACK_SIZE 4096  /* For figuring out the size to set */
#define PI_STACK_SIZE_SHFT      12      /* 4k */

#define PI_STACKADDR_OFFSET     (PI_ERR_STACK_ADDR_B - PI_ERR_STACK_ADDR_A)
#define PI_ERRSTAT_OFFSET       (PI_ERR_STATUS0_B - PI_ERR_STATUS0_A)
#define PI_RDCLR_OFFSET         (PI_ERR_STATUS0_A_RCLR - PI_ERR_STATUS0_A)
/* these macros are correct, but fix their users to understand two PIs
   and 4 CPUs (slices) per bedrock */
#define PI_INT_MASK_OFFSET      (PI_INT_MASK0_B - PI_INT_MASK0_A)
#define PI_INT_SET_OFFSET       (PI_CC_PEND_CLR_B - PI_CC_PEND_CLR_A)
#define PI_NMI_OFFSET		(PI_NMI_B - PI_NMI_A)

#define ERR_STACK_SIZE_BYTES(_sz) \
       ((_sz) ? (PI_MIN_STACK_SIZE << ((_sz) - 1)) : 0)

#define PI_CRB_STS_P	(1 << 9) 	/* "P" (partial word read/write) bit */
#define PI_CRB_STS_V	(1 << 8)	/* "V" (valid) bit */
#define PI_CRB_STS_R	(1 << 7)	/* "R" (response data sent to CPU) */
#define PI_CRB_STS_A	(1 << 6)	/* "A" (data ack. received) bit */
#define PI_CRB_STS_W	(1 << 5)	/* "W" (waiting for write compl.) */
#define PI_CRB_STS_H	(1 << 4)	/* "H" (gathering invalidates) bit */
#define PI_CRB_STS_I	(1 << 3)	/* "I" (targ. inbound invalidate) */
#define PI_CRB_STS_T	(1 << 2)	/* "T" (targ. inbound intervention) */
#define PI_CRB_STS_E	(0x3)		/* "E" (coherent read type) */

/* When the "P" bit is set in the sk_crb_sts field of an error stack
 * entry, the "R," "A," "H," and "I" bits are actually bits 6..3 of
 * the address.  This macro extracts those address bits and shifts
 * them to their proper positions, ready to be ORed in to the rest of
 * the address (which is calculated as sk_addr << 7).
 */
#define PI_CRB_STS_ADDR_BITS(sts) \
    ((sts) & (PI_CRB_STS_I | PI_CRB_STS_H) | \
     ((sts) & (PI_CRB_STS_A | PI_CRB_STS_R)) >> 1)

#ifdef _LANGUAGE_C
/*
 * format of error stack and error status registers.
 */

struct err_stack_format {
        __uint64_t      sk_addr    : 33,   /* address */
                        sk_cmd     :  8,   /* message command */
                        sk_crb_sts : 10,   /* status from RRB or WRB */
                        sk_rw_rb   :  1,   /* RRB == 0, WRB == 1 */
                        sk_crb_num :  3,   /* WRB (0 to 7) or RRB (0 to 4) */
                        sk_t5_req  :  3,   /* RRB T5 request number */
                        sk_suppl   :  3,   /* lowest 3 bit of supplemental */
                        sk_err_type:  3;   /* error type        */
};

#define	PI_ERR_CMD_REPLY	(1<<7)


#ifdef	DEFINE_PI_ERR_CMDS_AND_TYPES

/*
 * The list of values for ib_imsg can be generated from duplonet.h
 * (in the bedrock vobs) thusly:
perl -e \
  'while(<>) { \
  next unless /define .*Type /; \
  next if /RESERVED/; \
  next unless ($n, $v) = $_ =~ /DNET_(\w+)\s+8.b ([01_]+)/; \
  $v =~ s/_//g; \
  $n .= " " x (7-length($n)); \
  printf "      \"$n\" /\* 0x%02lx *\/\n", \
	unpack("C", pack("B8", $v)); \
}' duplonet.h
 *
 */

char *pi_err_status_cmd[] = {
	"RDSH",		/* 0x00    Type Request 1 */
	"RDEX",		/* 0x01    Type Request 1 */
	"READ",		/* 0x02    Type Request 1 */
	"RSHU",		/* 0x03    Type Request 1 */
	"REXU",		/* 0x04    Type Request 1 */
	"UPGRD",	/* 0x05    Type Request 1 */
	"RLQSH",	/* 0x06    Type Request 1 */
	"UNK",		/* 0x07    Type Request X */
	"IRSHU",	/* 0x08    Type Request 2 */
	"IREXU",	/* 0x09    Type Request 2 */
	"IRDSH",	/* 0x0a    Type Request 2 */
	"IRDEX",	/* 0x0b    Type Request 2 */
	"IRMVE",	/* 0x0c    Type Request 2 */
	"UNK",		/* 0x0d    Type Request X */
	"UNK",		/* 0x0e    Type Request X */
	"INVAL",	/* 0x0f    Type Request 3 */
	"PRDH",		/* 0x10    Type Request 1 */
	"PRDI",		/* 0x11    Type Request 4 or 5 */
	"PRDM",		/* 0x12    Type Request 1 */
	"PRDU",		/* 0x13    Type Request 1 */
	"PRIHA",	/* 0x14    Type Request 4 */
	"PRIHB",	/* 0x15    Type Request 4 */
	"PRIRA",	/* 0x16    Type Request 4 */
	"PRIRB",	/* 0x17    Type Request 4 */
	"ODONE",	/* 0x18    Type Request 1 II Int */
	"UNK",		/* 0x09    Type Request X */
	"UNK",		/* 0x0a    Type Request X */
	"UNK",		/* 0x0b    Type Request X */
	"PRDB",		/* 0x1c    Type Request 1 */
	"BAR",		/* 0x1d    Type Request 1 */
	"UNK",		/* 0x1e    Type Request X */
	"UNK",		/* 0x1f    Type Request X */
	"UNK",		/* 0x20    Type Request X */
	"UNK",		/* 0x21    Type Request X */
	"UNK",		/* 0x22    Type Request X */
	"UNK",		/* 0x23    Type Request X */
	"UNK",		/* 0x24    Type Request X */
	"UNK",		/* 0x25    Type Request X */
	"UNK",		/* 0x26    Type Request X */
	"UNK",		/* 0x27    Type Request X */
	"UNK",		/* 0x28    Type Request X */
	"UNK",		/* 0x29    Type Request X */
	"UNK",		/* 0x2a    Type Request X */
	"UNK",		/* 0x2b    Type Request X */
	"UNK",		/* 0x2c    Type Request X */
	"UNK",		/* 0x2d    Type Request X */
	"UNK",		/* 0x2e    Type Request X */
	"LINVAL",	/* 0x2f    Type Request 3 Int */
	"PWRH",		/* 0x30    Type Request 1 */
	"PWRI",		/* 0x31    Type Request 4 or 5 */
	"PWRM",		/* 0x32    Type Request 1 */
	"PWRU",		/* 0x33    Type Request 1 */
	"PWIHA",	/* 0x34    Type Request 4 */
	"PWIHB",	/* 0x35    Type Request 4 */
	"PWIRA",	/* 0x36    Type Request 4 */
	"PWIRB",	/* 0x37    Type Request 4 */
	"GFXWS",	/* 0x38    Type Request 4 */
	"UNK",		/* 0x39    Type Request X */
	"UNK",		/* 0x3a    Type Request X */
	"UNK",		/* 0x3b    Type Request X */
	"PWRB",		/* 0x3c    Type Request 1 */
	"UNK",		/* 0x3d    Type Request X */
	"UNK",		/* 0x3e    Type Request X */
	"UNK",		/* 0x3f    Type Request X */
	"WB",		/* 0x40    Type Request 1 */
	"WINV",		/* 0x41    Type Request 1 */
	"UNK",		/* 0x42    Type Request X */
	"UNK",		/* 0x43    Type Request X */
	"UNK",		/* 0x44    Type Request X */
	"UNK",		/* 0x45    Type Request X */
	"UNK",		/* 0x46    Type Request X */
	"UNK",		/* 0x47    Type Request X */
	"UNK",		/* 0x48    Type Request X */
	"UNK",		/* 0x49    Type Request X */
	"UNK",		/* 0x4a    Type Request X */
	"UNK",		/* 0x4b    Type Request X */
	"UNK",		/* 0x4c    Type Request X */
	"UNK",		/* 0x4d    Type Request X */
	"UNK",		/* 0x4e    Type Request X */
	"UNK",		/* 0x4f    Type Request X */
	"GFXWL",	/* 0x50    Type Request 4 */
	"PTPWR",	/* 0x51    Type Request 4 */
	"UNK",		/* 0x52    Type Request X */
	"UNK",		/* 0x53    Type Request X */
	"UNK",		/* 0x54    Type Request X */
	"UNK",		/* 0x55    Type Request X */
	"UNK",		/* 0x56    Type Request X */
	"UNK",		/* 0x57    Type Request X */
	"UNK",		/* 0x58    Type Request X */
	"UNK",		/* 0x59    Type Request X */
	"UNK",		/* 0x5a    Type Request X */
	"UNK",		/* 0x5b    Type Request X */
	"UNK",		/* 0x5c    Type Request X */
	"UNK",		/* 0x5d    Type Request X */
	"UNK",		/* 0x5e    Type Request X */
	"UNK",		/* 0x5f    Type Request X */
	"UNK",		/* 0x60    Type Request X */
	"VRD",		/* 0x61    Type Request 6 */
	"VWR",		/* 0x62    Type Request 6 */
	"UNK",		/* 0x63    Type Request X */
	"UNK",		/* 0x64    Type Request X */
	"UNK",		/* 0x65    Type Request X */
	"UNK",		/* 0x66    Type Request X */
	"UNK",		/* 0x67    Type Request X */
	"UNK",		/* 0x68    Type Request X */
	"UNK",		/* 0x69    Type Request X */
	"UNK",		/* 0x6a    Type Request X */
	"UNK",		/* 0x6b    Type Request X */
	"UNK",		/* 0x6c    Type Request X */
	"UNK",		/* 0x6d    Type Request X */
	"UNK",		/* 0x6e    Type Request X */
	"UNK",		/* 0x6f    Type Request X */
	"UNK",		/* 0x70    Type Request X */
	"UNK",		/* 0x71    Type Request X */
	"UNK",		/* 0x72    Type Request X */
	"UNK",		/* 0x73    Type Request X */
	"UNK",		/* 0x74    Type Request X */
	"UNK",		/* 0x75    Type Request X */
	"UNK",		/* 0x76    Type Request X */
	"UNK",		/* 0x77    Type Request X */
	"UNK",		/* 0x78    Type Request X */
	"UNK",		/* 0x79    Type Request X */
	"UNK",		/* 0x7a    Type Request X */
	"UNK",		/* 0x7b    Type Request X */
	"UNK",		/* 0x7c    Type Request X */
	"UNK",		/* 0x7d    Type Request X */
	"UNK",		/* 0x7e    Type Request X */
	"UNK",		/* 0x7f    Type Request X */
	"SACK",		/* 0x80    Type Reply 1 */
	"EACK",		/* 0x81    Type Reply 1 */
	"UACK",		/* 0x82    Type Reply 1 */
	"UPC",		/* 0x83    Type Reply 1 */
	"UPACK",	/* 0x84    Type Reply 1 */
	"AERR",		/* 0x85    Type Reply 1 */
	"PERR",		/* 0x86    Type Reply 1 */
	"IVACK",	/* 0x87    Type Reply 1 */
	"WERR",		/* 0x88    Type Reply 1 */
	"WBEAK",	/* 0x89    Type Reply 1 */
	"WBBAK",	/* 0x8a    Type Reply 1 */
	"DNACK",	/* 0x8b    Type Reply 1 */
	"SXFER",	/* 0x8c    Type Reply 2 */
	"PURGE",	/* 0x8d    Type Reply 2 */
	"DNGRD",	/* 0x8e    Type Reply 2 */
	"XFER",		/* 0x8f    Type Reply 2 */
	"PACK",		/* 0x90    Type Reply 1 */
	"PACKH",	/* 0x91    Type Reply 1 */
	"PACKN",	/* 0x92    Type Reply 1 */
	"PNKRA",	/* 0x93    Type Reply 1 */
	"PNKRB",	/* 0x94    Type Reply 1 */
	"GFXCS",	/* 0x95    Type Reply 1 */
	"GFXCL",	/* 0x96    Type Reply 1 */
	"PTPCR",	/* 0x97    Type Reply 1 */
	"WIC",		/* 0x98    Type Reply 1 */
	"WACK",		/* 0x99    Type Reply 1 */
	"WSPEC",	/* 0x9a    Type Reply 1 */
	"RACK",		/* 0x9b    Type Reply 1 */
	"BRMVE",	/* 0x9c    Type Reply 1 */
	"DERR",		/* 0x9d    Type Reply 1 */
	"PRERR",	/* 0x9e    Type Reply 1 */
	"PWERR",	/* 0x9f    Type Reply 1 */
	"BINV",		/* 0xa0    Type Reply 1 */
	"UNK",		/* 0xa1    Type Reply X */
	"UNK",		/* 0xa2    Type Reply X */
	"WTERR",	/* 0xa3    Type Reply 1 PI Int */
	"RTERR",	/* 0xa4    Type Reply 1 PI Int */
	"UNK",		/* 0xa5    Type Reply X */
	"UNK",		/* 0xa6    Type Reply X */
	"SPRPLY",	/* 0xa7    Type Reply 1 PI Int */
	"ESPRPLY",	/* 0xa8    Type Reply 1 PI Int */
	"UNK",		/* 0xa9    Type Reply X */
	"UNK",		/* 0xaa    Type Reply X */
	"UNK",		/* 0xab    Type Reply X */
	"UNK",		/* 0xac    Type Reply X */
	"UNK",		/* 0xad    Type Reply X */
	"UNK",		/* 0xae    Type Reply X */
	"UNK",		/* 0xaf    Type Reply X */
	"PRPLY",	/* 0xb0    Type Reply 1 */
	"PNAKW",	/* 0xb1    Type Reply 1 */
	"PNKWA",	/* 0xb2    Type Reply 1 */
	"PNKWB",	/* 0xb3    Type Reply 1 */
	"UNK",		/* 0xb4    Type Reply X */
	"UNK",		/* 0xb5    Type Reply X */
	"UNK",		/* 0xb6    Type Reply X */
	"UNK",		/* 0xb7    Type Reply X */
	"UNK",		/* 0xb8    Type Reply X */
	"UNK",		/* 0xb9    Type Reply X */
	"UNK",		/* 0xba    Type Reply X */
	"UNK",		/* 0xbb    Type Reply X */
	"UNK",		/* 0xbc    Type Reply X */
	"UNK",		/* 0xbd    Type Reply X */
	"UNK",		/* 0xbe    Type Reply X */
	"UNK",		/* 0xbf    Type Reply X */
	"SRESP",	/* 0xc0    Type Reply 1 */
	"SRPLY",	/* 0xc1    Type Reply 1 */
	"SSPEC",	/* 0xc2    Type Reply 1 */
	"UNK",		/* 0xc3    Type Reply X */
	"ERESP",	/* 0xc4    Type Reply 1 */
	"ERPC",		/* 0xc5    Type Reply 1 */
	"ERPLY",	/* 0xc6    Type Reply 1 */
	"ESPEC",	/* 0xc7    Type Reply 1 */
	"URESP",	/* 0xc8    Type Reply 1 */
	"URPC",		/* 0xc9    Type Reply 1 */
	"URPLY",	/* 0xca    Type Reply 1 */
	"UNK",		/* 0xcb    Type Reply X */
	"SXWB",		/* 0xcc    Type Reply 2 */
	"PGWB",		/* 0xcd    Type Reply 2 */
	"SHWB",		/* 0xce    Type Reply 2 */
	"UNK",		/* 0xcf    Type Reply X */
	"UNK",		/* 0xd0    Type Reply X */
	"UNK",		/* 0xd1    Type Reply X */
	"UNK",		/* 0xd2    Type Reply X */
	"UNK",		/* 0xd3    Type Reply X */
	"UNK",		/* 0xd4    Type Reply X */
	"UNK",		/* 0xd5    Type Reply X */
	"UNK",		/* 0xd6    Type Reply X */
	"UNK",		/* 0xd7    Type Reply X */
	"BRDSH",	/* 0xd8    Type Reply 1 */
	"BRDEX",	/* 0xd9    Type Reply 1 */
	"BRSHU",	/* 0xda    Type Reply 1 */
	"BREXU",	/* 0xdb    Type Reply 1 */
	"UNK",		/* 0xdc    Type Reply X */
	"UNK",		/* 0xdd    Type Reply X */
	"UNK",		/* 0xde    Type Reply X */
	"UNK",		/* 0xdf    Type Reply X */
	"UNK",		/* 0xe0    Type Reply X */
	"UNK",		/* 0xe1    Type Reply X */
	"UNK",		/* 0xe2    Type Reply X */
	"UNK",		/* 0xe3    Type Reply X */
	"UNK",		/* 0xe4    Type Reply X */
	"UNK",		/* 0xe5    Type Reply X */
	"UNK",		/* 0xe6    Type Reply X */
	"UNK",		/* 0xe7    Type Reply X */
	"UNK",		/* 0xe8    Type Reply X */
	"VRPLY",	/* 0xe9    Type Reply 3 */
	"VWACK",	/* 0xea    Type Reply 3 */
	"UNK",		/* 0xeb    Type Reply X */
	"UNK",		/* 0xec    Type Reply X */
	"UNK",		/* 0xed    Type Reply X */
	"UNK",		/* 0xee    Type Reply X */
	"UNK",		/* 0xef    Type Reply X */
	"UNK",		/* 0xf0    Type Reply X */
	"UNK",		/* 0xf1    Type Reply X */
	"UNK",		/* 0xf2    Type Reply X */
	"UNK",		/* 0xf3    Type Reply X */
	"UNK",		/* 0xf4    Type Reply X */
	"UNK",		/* 0xf5    Type Reply X */
	"UNK",		/* 0xf6    Type Reply X */
	"UNK",		/* 0xf7    Type Reply X */
	"UNK",		/* 0xf8    Type Reply X */
	"VERRA",	/* 0xf9    Type Reply 3 */
	"VERRC",	/* 0xfa    Type Reply 3 */
	"VERRCA",	/* 0xfb    Type Reply 3 */
	"UNK",		/* 0xfc    Type Reply X */
	"UNK",		/* 0xfd    Type Reply X */
	"UNK",		/* 0xfe    Type Reply X */
	"UNK"		/* 0xff    Type Reply X */
};

char *hub_rrb_err_type[] = {
    "0 Access Error",
    "1 Uncached Partial Error",
    "2 Directory Error",
    "3 Timeout Error",
    "4 Poisoned Access Violation",
    "5 Too Many NACKs",
    "6 Response Data Error",
    "7 Packet Length Error"
};

char *hub_wrb_err_type[] = {
    "0 Access Error",
    "1 Uncached Partial Error",
    "2 (Undefined)",
    "3 Timeout Error",
    "4 (Undefined)",
    "5 (Undefined)",
    "6 Response Data Error",
    "7 Packet Length Error"
};

#endif	/* DEFINE_PI_ERR_CMDS_AND_TYPES */


typedef union pi_err_stack {
        __uint64_t      pi_stk_word;
        struct  err_stack_format pi_stk_fmt;
} pi_err_stack_t;

/* Simplified version of pi_err_status0_a_u_t (PI_ERR_STATUS0_A) */
struct err_status0_format {
	__uint64_t	s0_valid	:  1,	/* error is valid */
			s0_over_run	:  1,	/* Subsequent errors spooled */
			s0_addr		: 37,	/* Address */
			s0_cmd		:  8,	/* Incoming message command */
			s0_supplemental : 11,	/* ncoming message sup field */
			s0_proc_req_num :  3,	/* Request number for RRB only */
			s0_err_type	:  3;	/* Encoded error cause */
};

typedef union pi_err_stat0 {
	__uint64_t	pi_stat0_word;
        struct err_status0_format pi_stat0_fmt;
} pi_err_stat0_t;

/* Simplified version of pi_err_status1_a_u_t (PI_ERR_STATUS1_A) */
struct err_status1_format {
	__uint64_t	s1_src	   : 11,   /* message source */
			s1_crb_sts : 10,   /* status from RRB or WRB */
			s1_rw_rb   :  1,   /* RRB == 0, WRB == 1 */
			s1_crb_num :  3,   /* WRB (0 to 7) or RRB (0 to 4) */
			s1_inval_cnt:10,   /* signed invalidate counter RRB */
			s1_to_cnt  :  8,   /* crb timeout counter */
			s1_spl_cnt : 21;   /* number spooled to memory */
};

typedef union pi_err_stat1 {
	__uint64_t	pi_stat1_word;
	struct err_status1_format pi_stat1_fmt;
} pi_err_stat1_t;
#endif

/* Error stack types (sk_err_type) for reads:	*/
#define PI_ERR_RD_AERR		0	/* Read Access Error */
#define PI_ERR_RD_PRERR         1	/* Uncached Partial Read */
#define PI_ERR_RD_DERR          2	/* Directory Error */
#define PI_ERR_RD_TERR          3	/* Read Timeout */
#define PI_ERR_RD_PERR		4	/* Poison Access Violation */
#define PI_ERR_RD_NACK		5	/* Excessive NACKs	*/
#define PI_ERR_RD_RDE		6	/* Response Data Error	*/
#define PI_ERR_RD_PLERR		7	/* Packet Length Error */
/* Error stack types (sk_err_type) for writes:	*/
#define PI_ERR_WR_WERR          0	/* Write Access Error */
#define PI_ERR_WR_PWERR         1	/* Uncached Partial Write Error */
#define PI_ERR_WR_TERR          3	/* Write Timeout */
#define PI_ERR_WR_RDE		6	/* Response Data Error */
#define PI_ERR_WR_PLERR		7	/* Packet Length Error */


/* For backwards compatibility */
#define PI_RT_COUNT	PI_RT_COUNTER    /* Real Time Counter 		    */
#define PI_RT_EN_A	PI_RT_INT_EN_A   /* RT int for CPU A enable         */
#define PI_RT_EN_B	PI_RT_INT_EN_B   /* RT int for CPU B enable         */
#define PI_PROF_EN_A	PI_PROF_INT_EN_A /* PROF int for CPU A enable       */
#define PI_PROF_EN_B	PI_PROF_INT_EN_B /* PROF int for CPU B enable       */
#define PI_RT_PEND_A    PI_RT_INT_PEND_A /* RT interrupt pending 	    */
#define PI_RT_PEND_B    PI_RT_INT_PEND_B /* RT interrupt pending 	    */
#define PI_PROF_PEND_A  PI_PROF_INT_PEND_A /* Profiling interrupt pending   */
#define PI_PROF_PEND_B  PI_PROF_INT_PEND_B /* Profiling interrupt pending   */


/* Bits in PI_SYSAD_ERRCHK_EN */
#define PI_SYSAD_ERRCHK_ECCGEN  0x01    /* Enable ECC generation            */
#define PI_SYSAD_ERRCHK_QUALGEN 0x02    /* Enable data quality signal gen.  */
#define PI_SYSAD_ERRCHK_SADP    0x04    /* Enable SysAD parity checking     */
#define PI_SYSAD_ERRCHK_CMDP    0x08    /* Enable SysCmd parity checking    */
#define PI_SYSAD_ERRCHK_STATE   0x10    /* Enable SysState parity checking  */
#define PI_SYSAD_ERRCHK_QUAL    0x20    /* Enable data quality checking     */
#define PI_SYSAD_CHECK_ALL      0x3f    /* Generate and check all signals.  */

/* CALIAS values */
#define PI_CALIAS_SIZE_0        0
#define PI_CALIAS_SIZE_4K       1
#define PI_CALIAS_SIZE_8K       2
#define PI_CALIAS_SIZE_16K      3
#define PI_CALIAS_SIZE_32K      4
#define PI_CALIAS_SIZE_64K      5
#define PI_CALIAS_SIZE_128K     6
#define PI_CALIAS_SIZE_256K     7
#define PI_CALIAS_SIZE_512K     8
#define PI_CALIAS_SIZE_1M       9
#define PI_CALIAS_SIZE_2M       10
#define PI_CALIAS_SIZE_4M       11
#define PI_CALIAS_SIZE_8M       12
#define PI_CALIAS_SIZE_16M      13
#define PI_CALIAS_SIZE_32M      14
#define PI_CALIAS_SIZE_64M      15

/* Fields in PI_ERR_STATUS0_[AB] */
#define PI_ERR_ST0_VALID_MASK	0x8000000000000000
#define PI_ERR_ST0_VALID_SHFT	63

/* Fields in PI_SPURIOUS_HDR_0 */
#define PI_SPURIOUS_HDR_VALID_MASK	0x8000000000000000
#define PI_SPURIOUS_HDR_VALID_SHFT	63

/* Fields in PI_NACK_CNT_A/B */
#define PI_NACK_CNT_EN_SHFT	20
#define PI_NACK_CNT_EN_MASK	0x100000
#define PI_NACK_CNT_MASK	0x0fffff
#define PI_NACK_CNT_MAX		0x0fffff

/* Bits in PI_ERR_INT_PEND */
#define PI_ERR_SPOOL_CMP_B	0x000000001	/* Spool end hit high water */
#define PI_ERR_SPOOL_CMP_A	0x000000002
#define PI_ERR_SPUR_MSG_B	0x000000004	/* Spurious message intr.   */
#define PI_ERR_SPUR_MSG_A	0x000000008
#define PI_ERR_WRB_TERR_B	0x000000010	/* WRB TERR		    */
#define PI_ERR_WRB_TERR_A	0x000000020
#define PI_ERR_WRB_WERR_B	0x000000040	/* WRB WERR 		    */
#define PI_ERR_WRB_WERR_A	0x000000080
#define PI_ERR_SYSSTATE_B	0x000000100	/* SysState parity error    */
#define PI_ERR_SYSSTATE_A	0x000000200
#define PI_ERR_SYSAD_DATA_B	0x000000400	/* SysAD data parity error  */
#define PI_ERR_SYSAD_DATA_A	0x000000800
#define PI_ERR_SYSAD_ADDR_B	0x000001000	/* SysAD addr parity error  */
#define PI_ERR_SYSAD_ADDR_A	0x000002000
#define PI_ERR_SYSCMD_DATA_B	0x000004000	/* SysCmd data parity error */
#define PI_ERR_SYSCMD_DATA_A	0x000008000
#define PI_ERR_SYSCMD_ADDR_B	0x000010000	/* SysCmd addr parity error */
#define PI_ERR_SYSCMD_ADDR_A	0x000020000
#define PI_ERR_BAD_SPOOL_B	0x000040000	/* Error spooling to memory */
#define PI_ERR_BAD_SPOOL_A	0x000080000
#define PI_ERR_UNCAC_UNCORR_B	0x000100000	/* Uncached uncorrectable   */
#define PI_ERR_UNCAC_UNCORR_A	0x000200000
#define PI_ERR_SYSSTATE_TAG_B	0x000400000	/* SysState tag parity error */
#define PI_ERR_SYSSTATE_TAG_A	0x000800000
#define PI_ERR_MD_UNCORR	0x001000000	/* Must be cleared in MD    */
#define PI_ERR_SYSAD_BAD_DATA_B	0x002000000	/* SysAD Data quality bad   */
#define PI_ERR_SYSAD_BAD_DATA_A	0x004000000
#define PI_ERR_UE_CACHED_B	0x008000000	/* UE during cached load    */
#define PI_ERR_UE_CACHED_A	0x010000000
#define PI_ERR_PKT_LEN_ERR_B	0x020000000	/* Xbar data too long/short */
#define PI_ERR_PKT_LEN_ERR_A	0x040000000
#define PI_ERR_IRB_ERR_B	0x080000000	/* Protocol error           */
#define PI_ERR_IRB_ERR_A	0x100000000
#define PI_ERR_IRB_TIMEOUT_B	0x200000000	/* IRB_B got a timeout      */
#define PI_ERR_IRB_TIMEOUT_A	0x400000000

#define PI_ERR_CLEAR_ALL_A	0x554aaaaaa
#define PI_ERR_CLEAR_ALL_B	0x2aa555555


/*
 * The following five macros define all possible error int pends. 
 */

#define PI_FATAL_ERR_CPU_A	(PI_ERR_IRB_TIMEOUT_A	| \
				 PI_ERR_IRB_ERR_A	| \
				 PI_ERR_PKT_LEN_ERR_A	| \
				 PI_ERR_SYSSTATE_TAG_A 	| \
				 PI_ERR_BAD_SPOOL_A 	| \
				 PI_ERR_SYSCMD_ADDR_A 	| \
				 PI_ERR_SYSCMD_DATA_A 	| \
				 PI_ERR_SYSAD_ADDR_A 	| \
				 PI_ERR_SYSAD_DATA_A	| \
				 PI_ERR_SYSSTATE_A)

#define PI_MISC_ERR_CPU_A	(PI_ERR_UE_CACHED_A	| \
				 PI_ERR_SYSAD_BAD_DATA_A| \
				 PI_ERR_UNCAC_UNCORR_A 	| \
				 PI_ERR_WRB_WERR_A 	| \
				 PI_ERR_WRB_TERR_A 	| \
				 PI_ERR_SPUR_MSG_A 	| \
				 PI_ERR_SPOOL_CMP_A)

#define PI_FATAL_ERR_CPU_B	(PI_ERR_IRB_TIMEOUT_B	| \
				 PI_ERR_IRB_ERR_B	| \
				 PI_ERR_PKT_LEN_ERR_B	| \
				 PI_ERR_SYSSTATE_TAG_B 	| \
				 PI_ERR_BAD_SPOOL_B 	| \
				 PI_ERR_SYSCMD_ADDR_B 	| \
				 PI_ERR_SYSCMD_DATA_B 	| \
				 PI_ERR_SYSAD_ADDR_B 	| \
				 PI_ERR_SYSAD_DATA_B	| \
				 PI_ERR_SYSSTATE_B)

#define PI_MISC_ERR_CPU_B	(PI_ERR_UE_CACHED_B	| \
				 PI_ERR_SYSAD_BAD_DATA_B| \
				 PI_ERR_UNCAC_UNCORR_B 	| \
				 PI_ERR_WRB_WERR_B 	| \
				 PI_ERR_WRB_TERR_B 	| \
				 PI_ERR_SPUR_MSG_B 	| \
				 PI_ERR_SPOOL_CMP_B)

#define PI_ERR_GENERIC		(PI_ERR_MD_UNCORR)

/* Values for PI_MAX_CRB_TIMEOUT and PI_CRB_SFACTOR */
#define PMCT_MAX	0xff
#define PCS_MAX		0xffffff

/*
 * Bug #823463 WAR: set the PI CRB timeouts really long
 * so the PI doesn't time out before the II recovers.
 */
#define PCS_LONG	0xffffff
#define PCS_NORMAL      0x200000
#define PCS_SHORT       0x20000

/* pi_err_status0_a_u_t address shift */
#define ERR_STAT0_ADDR_SHFT     3

/* PI error read/write bit (RRB == 0, WRB == 1)	*/
/* pi_err_status1_a_u_t.pi_err_status1_a_fld_s.esa_wrb */
#define PI_ERR_RRB	0
#define PI_ERR_WRB	1

/* Error stack address shift, for use with pi_stk_fmt.sk_addr */
#define ERR_STK_ADDR_SHFT	7

#endif /* __SYS_SN_SN1_HUBPI_NEXT_H__ */
