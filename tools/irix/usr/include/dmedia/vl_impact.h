/*
 *  dev_impact.h -- Impact Video  definitions
 *
 * $Revision: 1.1 $
 */

#if !defined(_IMPACT_DEV_INCLUDE)
#define _IMPACT_DEV_INCLUDE

/*
 * Port definitions. The documentation associated with each node defines the
 * ports that are available on it. The following port names apply to 
 * all Impact Video nodes.
 */
#define VL_IMPACT_PORT_PIXEL_SRC_A     0x0010	/* Single-link, pixel src 0 */
#define VL_IMPACT_PORT_ALPHA_SRC_A     0x0020	/* Single-link, alpha src 0 */
#define VL_IMPACT_PORT_DUALLINK_SRC_A  0x0130	/* Dual-link, pix+alpha src 0 */
#define VL_IMPACT_PORT_PIXEL_SRC_B     0x0011	/* Single-link, pixel src 1 */
#define VL_IMPACT_PORT_ALPHA_SRC_B     0x0021	/* Single-link, alpha src 1 */
#define VL_IMPACT_PORT_DUALLINK_SRC_B  0x0131 	/* Dual-link, pix+alpha src 1 */

#define VL_IMPACT_PORT_PIXEL_DRN_A     0x1010	/* Single-link, pixel drn 0 */
#define VL_IMPACT_PORT_ALPHA_DRN_A     0x1020	/* Single-link, alpha drn 0 */
#define VL_IMPACT_PORT_DUALLINK_DRN_A  0x1130	/* Dual-link, pix+alpha drn 0 */
#define VL_IMPACT_PORT_PIXEL_DRN_B     0x1011	/* Single-link, pixel drn 1 */
#define VL_IMPACT_PORT_ALPHA_DRN_B     0x1021	/* Single-link, alpha drn 1 */
#define VL_IMPACT_PORT_DUALLINK_DRN_B  0x1131 	/* Dual-link, pix+alpha drn 1 */

/*
 * The port names are concatenated bitfields specifying the instance number,
 * link type, and data type. The following masks extract each bitfield.
 */
#define VL_IMPACT_PORT_INSTANCE_MASK 	0x000F
#define VL_IMPACT_PORT_DATATYPE_MASK 	0x00F0
#define VL_IMPACT_PORT_LINKTYPE_MASK 	0x0F00
#define VL_IMPACT_PORT_SRCDRN_MASK	0xF000

/*
 * The following definitions define the bitfields making up a port name
 */
#define VL_IMPACT_PORT_DATATYPE_PIXEL	0x0010
#define VL_IMPACT_PORT_DATATYPE_ALPHA	0x0020
#define VL_IMPACT_PORT_LINKTYPE_SINGLE	0x0000
#define VL_IMPACT_PORT_LINKTYPE_DUAL	0x0100
#define VL_IMPACT_PORT_SRCDRN_SRC	0x0000
#define VL_IMPACT_PORT_SRCDRN_DRN	0x1000

/*
 * The following are aliases are for nodes with only one port. They enforce 
 * that the port will be one of the "_A" ports.
 */
#define VL_IMPACT_PORT_PIXEL_SRC VL_IMPACT_PORT_PIXEL_SRC_A	/* Shorthand */
#define VL_IMPACT_PORT_ALPHA_SRC VL_IMPACT_PORT_ALPHA_SRC_A	/* Shorthand */
#define VL_IMPACT_PORT_DUALLINK_SRC VL_IMPACT_PORT_DUALLINK_SRC_A/* Shorthand */

#define VL_IMPACT_PORT_PIXEL_DRN VL_IMPACT_PORT_PIXEL_DRN_A	/* Shorthand */
#define VL_IMPACT_PORT_ALPHA_DRN VL_IMPACT_PORT_ALPHA_DRN_A	/* Shorthand */
#define VL_IMPACT_PORT_DUALLINK_DRN VL_IMPACT_PORT_DUALLINK_DRN_A/* Shorthand */

#endif /* _IMPACT_DEV_INCLUDE */

/* EOF dev_impact.h */
