/*
 *    Unpublished copyright (c) 2000-2002 Silicon Graphics, Inc.
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

#ifndef __SYS_SN_SN1_BDRKHSPECREGS_NEXT_H__
#define __SYS_SN_SN1_BDRKHSPECREGS_NEXT_H__

/* HSPEC_SYNERGY0_0 (PIMM PSC) shifts and masks */

#define HS_PIMM_PSC_SHFT(subnode)	(4 * (subnode))
#define HS_PIMM_PSC_MASK(subnode)	(0xf << HS_PIMM_PSC_SHFT(subnode))
#define HS_SN10_PSC_SHFT		0
#define HS_SN10_PSC_MASK		(0xff << HS_SN10_PSC_SHFT)
#define HS_SN11_PSC_SHFT		0
#define HS_SN11_PSC_MASK		(0xf << HS_SN11_PSC_SHFT)
#define HS_IP53_PSC_SHFT		0
#define HS_IP53_PSC_MASK		(0xf << HS_IP53_PSC_SHFT)

/* HSPEC_SYNERGY0_0 shift and mask for runtime checks of
 * bedrock-based, non-C-brick hardware
 */
#define HS_NON_CBRICK_SHFT		12
#define HS_NON_CBRICK_MASK		(0xf << HS_NON_CBRICK_SHFT)

#define HS_PEBRICK_BITS			(0xc << HS_NON_CBRICK_SHFT)/*PE-brick*/
#define HS_SN10_BITS			(0x8 << HS_NON_CBRICK_SHFT)/*speedo2 */
#define HS_SN11_BITS                    (0x4 << HS_NON_CBRICK_SHFT)/*Asterix */
#define HS_IP53_BITS			(0x2 << HS_NON_CBRICK_SHFT)/*IP53    */

/*
 * LED register macros
 */

#ifdef _LANGUAGE_C

#define CPU_LED_ADDR(_nasid, _slice)					   \
	REMOTE_HSPEC_ADDR((_nasid), HSPEC_LED0 + ((_slice) << 3))

#define SET_CPU_LEDS(_nasid, _slice,  _val)				   \
	(HUB_S(CPU_LED_ADDR(_nasid, _slice), (_val)))

#define SET_MY_LEDS(_v) 						   \
	SET_CPU_LEDS(get_nasid(), get_slice(), (_v))

#endif /* _LANGUAGE_C */

#endif /* __SYS_SN_SN1_BDRKHSPECREGS_NEXT_H__ */
