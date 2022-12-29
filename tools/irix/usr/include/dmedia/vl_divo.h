/***** This is a Generated File! Edit vl_divo.pl to make changes *****/

/*
 *  device-dependant header file for DIVO video
 *
 * Copyright 1997 Silicon Graphics, Inc.
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics, Inc.;
 * the contents of this file may not be disclosed to third parties, copied or
 * duplicated in any form, in whole or in part, without the prior written
 * permission of Silicon Graphics, Inc.
 *
 * RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to restrictions
 * as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data
 * and Computer Software clause at DFARS 252.227-7013, and/or in similar or
 * successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -
 * rights reserved under the Copyright Laws of the United States.
 */


#ifndef __VL_DIVO_H
#define __VL_DIVO_H



		/*  VL_DEFAULT_SOURCE defines  */

#define VL_DIVO_SRC_DIGITAL_VIDEO         0

		/*  DIVO Device Dependent Controls  */
#define VL_DIVO_DEV_BASE         (('D'<<24)|('I'<<16)|('V'<<8)|'O')



		/*  Sync Source Selection  */

#define VL_DIVO_SYNC_HOUSE                0
#define VL_DIVO_SYNC_DIGITAL_INPUT_LINK_A    1
#define VL_DIVO_SYNC_DIGITAL_INPUT_LINK_B    2
#define VL_DIVO_SYNC_DBOARD               3

		/*  Raster mode support  */

#define VL_DIVO_RASTER_MODE       ( VL_DIVO_DEV_BASE + 1 )
#define VL_DIVO_RASTER_VIDEO              0
#define VL_DIVO_RASTER_DATA               1

		/*  Loopback mode, for IO device  */

#define VL_DIVO_LOOPBACK          ( VL_DIVO_DEV_BASE + 2 )
#define VL_DIVO_LOOPBACK_ON               0
#define VL_DIVO_LOOPBACK_OFF              1

		/*  Line offset for VITC  */

#define VL_DIVO_VITC_LINE_OFFSET  ( VL_DIVO_DEV_BASE + 3 )

		/*  Digital interface precision in bits  */

#define VL_DIVO_INTERFACE_PRECISION ( VL_DIVO_DEV_BASE + 4 )
#define VL_DIVO_INTERFACE_PRECISION_8     0
#define VL_DIVO_INTERFACE_PRECISION_10    1

		/*  Active bits on digital input  */

#define VL_DIVO_INPUT_ACTIVE_BITS ( VL_DIVO_DEV_BASE + 5 )
#define VL_DIVO_INPUT_ACTIVE_BITS_UNKNOWN    0
#define VL_DIVO_INPUT_ACTIVE_BITS_8       1
#define VL_DIVO_INPUT_ACTIVE_BITS_10      2

		/*  Field display mode, for DIVO-DVC device  */

#define VL_DIVO_FIELD_DISPLAY     ( VL_DIVO_DEV_BASE + 6 )
#define VL_DIVO_FIELD_DISPLAY_F1F2        0
#define VL_DIVO_FIELD_DISPLAY_F2F1        1
#define VL_DIVO_FIELD_DISPLAY_F1F1        2
#define VL_DIVO_FIELD_DISPLAY_F2F2        3

		/*  Closed Caption mode, for DIVO-DVC device  */

#define VL_DIVO_CLOSED_CAPTION    ( VL_DIVO_DEV_BASE + 7 )
#define VL_DIVO_CLOSED_CAPTION_OFF        0
#define VL_DIVO_CLOSED_CAPTION_ON         1

		/*  Compatibility with earlier DIVO 1.0 tokens  */
		/*  which lacked VL_ prefix.  */
		/*  Please do not use these; use the VL_ ones  */
#define DIVO_SRC_DIGITAL_VIDEO          VL_DIVO_SRC_DIGITAL_VIDEO
#define DIVO_SYNC_HOUSE                 VL_DIVO_SYNC_HOUSE
#define DIVO_SYNC_DIGITAL_INPUT_LINK_A  VL_DIVO_SYNC_DIGITAL_INPUT_LINK_A
#define DIVO_SYNC_DIGITAL_INPUT_LINK_B  VL_DIVO_SYNC_DIGITAL_INPUT_LINK_B
#define DIVO_SYNC_DBOARD                VL_DIVO_SYNC_DBOARD


		/*  SDTI Header  */
typedef struct {
  u_char did;            /* data id identifier */
  u_char sdid;           /* sec. data id identifier */
  u_char dc;             /* data word count */
  u_char lnum[2];        /* linenumber0 and linenumber1 */
  u_char lnumcrc[2];     /* linenumber0 and linenumber1 crc */
  u_char aai_code;       /* appl identified and code */
  u_char dst_addr[16];   /* destination address */
  u_char src_addr[16];   /* source address */
  u_char btype;          /* block type */
  u_char crcflag;        /* payload crc flag */
  u_char dextflag;       /* data extension flag */
  u_char reserved[4];    /* reserved words */
} sdti_hdr_t;


typedef struct sdti_dv_signal_s {
  unsigned char freq:1;         /* field/frame frequency, 1=50, 0=59.97 */
  unsigned char dif_structure:3;/* 011 : 25Mbps, 101 : 50Mbps */
  unsigned char reserved:2;
  unsigned char fsnf:1;         /* 0=valid, 1=invalid */
  unsigned char trf:1;          /* 0=valid, 1=invalid */
} sdti_dv_signal_t;


typedef struct sdti_dv_transmission_s {
  unsigned char fsn:4;          /* frame sequence number */
  unsigned char trans_rate:4;   /* transmission rate */
} sdti_dv_transmission_t;


#define DIVO_SDTI_BLOCK_TYPE_FIXED      0x33
#define DIVO_SDTI_BLOCK_TYPE_VARIABLE   0xC1


#define DIVO_SDTI_DV_DATA_TYPE_DVCPRO1  0x21 /* 25Mbps */
#define DIVO_SDTI_DV_DATA_TYPE_DVCPRO2  0x22 /* 50Mbps */


#define DIVO_SDTI_DV_PACKETS_PER_LINE      8
#define DIVO_SDTI_DV_525_CHAN_HEIGHT      94
#define DIVO_SDTI_DV_625_CHAN_HEIGHT     113


#define DIVO_SDTI_VP_525_FIELD_HEIGHT    248
#define DIVO_SDTI_VP_625_FIELD_HEIGHT    294


#define DIVO_SDTI_DV_DIF_25             0x03
#define DIVO_SDTI_DV_DIF_50             0x05


#define DIVO_SDTI_DV_RATE_1X            0x00
#define DIVO_SDTI_DV_RATE_2X            0x01
#define DIVO_SDTI_DV_RATE_3X            0x02
#define DIVO_SDTI_DV_RATE_4X            0x03


#define DIVO_SDTI_DV_FREQ_525           0x00
#define DIVO_SDTI_DV_FREQ_625           0x01


#define DIVO_525_DIF_FRAME_SIZE       120000
#define DIVO_625_DIF_FRAME_SIZE       144000


		/*  flags for SDTI errors and status  */
#define DIVO_VIDINFO_SDTI_ERROR_LINK_A                  (1 << 0x0)
#define DIVO_VIDINFO_SDTI_ERROR_LINK_B                  (1 << 0x1)
#define DIVO_VIDINFO_SDTI_ERROR_PARITY                  (1 << 0x2)
#define DIVO_VIDINFO_SDTI_ERROR_LINE0                   (1 << 0x3)
#define DIVO_VIDINFO_SDTI_ERROR_LINE1                   (1 << 0x4)
#define DIVO_VIDINFO_SDTI_ERROR_LINE_CRC0               (1 << 0x5)
#define DIVO_VIDINFO_SDTI_ERROR_LINE_CRC1               (1 << 0x6)
#define DIVO_VIDINFO_SDTI_ERROR_HEADER_CRC0             (1 << 0x7)
#define DIVO_VIDINFO_SDTI_ERROR_HEADER_CRC1             (1 << 0x8)
#define DIVO_VIDINFO_SDTI_ERROR_HEADER_CHECKSUM         (1 << 0x9)
#define DIVO_VIDINFO_SDTI_ERROR_PAYLOAD_CRC0            (1 << 0xA)
#define DIVO_VIDINFO_SDTI_ERROR_PAYLOAD_CRC1            (1 << 0xB)
#define DIVO_VIDINFO_SDTI_ERROR_ADF                     (1 << 0xC)
#define DIVO_VIDINFO_SDTI_ERROR_DID                     (1 << 0xD)
#define DIVO_VIDINFO_SDTI_ERROR_SDID                    (1 << 0xE)
#define DIVO_VIDINFO_SDTI_ERROR_DATA_COUNT              (1 << 0xF)
#define DIVO_VIDINFO_SDTI_INFO_VARIABLE	               (1 << 0x10)


#endif  /* __VL_DIVO_H */
