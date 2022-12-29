/*
 *    Unpublished copyright (c) 2000 Silicon Graphics, Inc.
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

#ifndef __SYS_SN_SN1_HUBXB_NEXT_H__
#define __SYS_SN_SN1_HUBXB_NEXT_H__

/* XB_FIRST_ERROR fe_source field encoding */
#define XVE_SOURCE_POQ0 0xf	/* 1111 */
#define XVE_SOURCE_PIQ0 0xe	/* 1110 */
#define XVE_SOURCE_POQ1 0xd	/* 1101 */
#define XVE_SOURCE_PIQ1 0xc	/* 1100 */
#define XVE_SOURCE_MP0  0xb	/* 1011 */
#define XVE_SOURCE_MP1  0xa	/* 1010 */
#define XVE_SOURCE_MMQ  0x9	/* 1001 */
#define XVE_SOURCE_MIQ  0x8	/* 1000 */
#define XVE_SOURCE_NOQ  0x7	/* 0111 */
#define XVE_SOURCE_NIQ  0x6	/* 0110 */
#define XVE_SOURCE_IOQ  0x5	/* 0101 */
#define XVE_SOURCE_IIQ  0x4	/* 0100 */
#define XVE_SOURCE_LOQ  0x3	/* 0011 */
#define XVE_SOURCE_LIQ  0x2	/* 0010 */

/* XB_PARMS fields */
#define XBP_RESET_DEFAULTS	0x0008000080000021LL
#define XBP_ACTIVE_DEFAULTS	0x00080000fffff021LL

#endif /* __SYS_SN_SN1_HUBXB_NEXT_H__ */
