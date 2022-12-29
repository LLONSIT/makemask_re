#ifndef _VL_H_
#define _VL_H_

/*
 *  vl.h -- Main header file for the IRIS Video Library.
 *
 * Copyright 1993,1994 Silicon Graphics, Inc.
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

#define VLSpecificationRelease 2

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <ulocks.h>
#include <sys/types.h>
#include <sys/dmcommon.h>
#include <dmedia/dm_buffer.h>
#include <dmedia/dm_timecode.h>
#include <dmedia/dm_vitc.h>
#include <dmedia/vlctrl.h>

#define VL_PROTOCOL     1               /* current protocol version */
#define VL_PROTOCOL_REVISION 3          /* current minor version */


/* Basic VL data types for controls, etc. */

typedef int VLBoolean;

typedef struct {
    int x, y;
} VLXY;

typedef struct {
    int base;
    int increment;
    int limit;
    int type;		/* one of the following values: */
#define VL_LINEAR	1
#define VL_GEOMETRIC	2
} VLRange;

typedef struct {
    VLRange numerator;
    VLRange denominator;
} VLFractionRange;

typedef struct {
    int numerator;
    int denominator;
} VLFraction;

	/* used to setup transfer trigger */

typedef struct {
  int triggerType;  /* VL_TRIGGER_NONE, VL_TRIGGER_GPI,
                       VL_TRIGGER_VITC, VL_TRIGGER_MSC */
  VLTriggerVal value;
} VLTrigger;

typedef struct {
 int condition;  /* start, stop */
 int instance;
 int state;		/* on, off, pulse, nothing */
} VLGPIOutMode;

typedef struct {
 int gpi;  		/* gpi input or output */
 int instance;  /* which line */
 int state;		/* on, off, pulse, nothing */
} VLGPIState;

/*
 * Definitions for VL nodes:
 */

/*
 * Definitions of node types and kinds. Used as arguments for vlGetNode(),
 * returned in VLNodeInfo.
 */

/* Node type */
#define VL_SRC		1		/* Sources of data */
#define VL_DRN		2		/* Drains for data */
#define VL_DEVICE	3		/* The device node */
#define VL_INTERNAL	4		/* Filters & such */

/* Node kind */
#define VL_VIDEO        1
#define VL_GFX          2		/* Sirius only */
#define VL_MEM          3
#define VL_SCREEN       4
#define VL_TEXTURE      5		/* Sirius and Impact only */
#define VL_NETWORK      6
#define VL_BLENDER	7
#define VL_KEYGEN       8               /* Key Generator */
/* RESERVED NODE KIND   9 */
#define VL_CSC		10		/* Color space converter node */
#define VL_FB		11		/* Frame buffer node */
#define VL_CODEC	12		/* Compression/Decompression node*/
/* also VL_ANY */


/*
 * The following may be returned by vlGetConnection to indicate that the
 * node/port are not representd on the client's path.
 */
#define VLUnknownNode -1
#define VLUnknownPort -1

typedef int VLNode;
typedef int VLPort;

typedef struct __vlNodePortPair {
    VLNode node;
    VLPort port;
} VLNodePortPair;

#define VL_NAME_SIZE 32

typedef struct __vlNodeInfo {
    int id;
    char name[VL_NAME_SIZE];	/* name of node */
    int type;			/* see list above */
    int number;			/* number of this node */
    int kind;			/* see list above */
} VLNodeInfo;

typedef int VLPath;		/* handle for a path  */

typedef int VLDev;		/* handle for a device  */

typedef struct __vlDevice {
    VLDev dev;
    char name[VL_NAME_SIZE];	/* name of device */
    int numNodes;		/* number of nodes on this device */
    VLNodeInfo *nodes;		/* list of nodes */
    void *priv;
} VLDevice;

typedef struct __vlDevList {
    int numDevices;		/* number of devices */
    VLDevice *devices;		/* list of devices */
} VLDevList;



/*
 * VL server access routines:
 */

typedef struct _VLServer *VLServer;

extern VLServer vlOpenVideo(
    const char *	/* Server Name */
);

extern int vlCloseVideo(
    VLServer		/* Server Handle */
);

extern int vlGetDeviceList(
    VLServer,		/* Server Handle */
    VLDevList *		/* Device List   */
);

/* Define vlGetFD as an alias for vlConnectionNumber */ 
#define vlGetFD vlConnectionNumber

extern int vlConnectionNumber(VLServer svr);
extern int vlServerProtocolVersion(VLServer svr);
extern int vlServerProtocolRevision(VLServer svr);
extern int vlServerVendorRelease(VLServer svr);
extern char * vlServerString(VLServer svr);



/*
 * Routines to manipulate paths and nodes:
 */

extern VLDev vlGetDevice(
    VLServer,           /* Server Handle */
    VLPath		/* Path Handle */
);

extern VLPath vlCreatePath(
    VLServer,		/* Server Handle */
    VLDev,		/* Device Handle */
    VLNode,		/* Source */
    VLNode		/* Drain */
);

extern VLNode vlGetNode(
    VLServer,		/* Server Handle */
    int,		/* node type */
    int,		/* node kind */
    int			/* node number */
);

extern int vlDestroyPath(
    VLServer,		/* Server Handle */
    VLPath		/* Path Handle */
);

extern int vlAddNode(
    VLServer,		/* Server Handle */
    VLPath,		/* Path Handle */
    VLNode		/* Node */
);

extern int vlRemoveNode(
    VLServer,		/* Server Handle */
    VLPath,		/* Path Handle */
    VLNode		/* Node */
);

/*
 *----------------------------------------------------------------------
 *
 * Controls
 */

typedef int VLControlType;	/* see the following #defines */

/*
 * Configuration controls:
 *
 * VL_DEFAULT_SOURCE(int)	the default input video source for a path
 * VL_TIMING(int)		the timing for video (on video node or device)
 */
#define VL_DEFAULT_SOURCE	0
#define VL_TIMING		1 /* one of the following values */
    /*
     * 525 lines total -> active plus blanking;
     * 625 lines total -> active plus blanking;
     *
     * Betacam/MII/composite tape formats use square pixel analog timings;
     * D1 tape formats use CCIR601 timings;
     * D2 tape formats use the 4 times subcarrier timings.
     */
#define  VL_TIMING_525_SQ_PIX	0 /*analog (525 lines) 12.27 MHz; 646x486 */
#define  VL_TIMING_625_SQ_PIX	1 /*analog (625 lines) 14.75 MHz; 768x576 */
#define  VL_TIMING_525_CCIR601	2 /*digital component  13.50 MHz; 720x486 */
#define  VL_TIMING_625_CCIR601	3 /*digital component  13.50 MHz; 720x576 */
#define  VL_TIMING_525_4FSC	4 /*4x ntsc subcarrier 14.32 MHz; 768x486 */
#define  VL_TIMING_625_4FSC	5 /*4x pal subcarrier  17.72 MHz; 948x576 */

     /*
      * SMPTE 274M formats: 1125 total lines, 1920x1080 active picture,
      * square pixels, 16:9 picture aspect ratio.
      * 'p' suffix means progressive scanning, 'i' means 2:1 interlaced.
      */
#define  VL_TIMING_1125_1920x1080_60p	6  /* 148.5 MHz */
#define  VL_TIMING_1125_1920x1080_5994p	7  /* 148.5/1.001 MHz */
#define  VL_TIMING_1125_1920x1080_50p	8  /* 148.5 MHz */
#define  VL_TIMING_1125_1920x1080_60i	9  /* 74.25 MHz */
#define  VL_TIMING_1125_1920x1080_5994i	10 /* 74.25/1.001 MHz */
#define  VL_TIMING_1125_1920x1080_50i	11 /* 74.25 MHz */
#define  VL_TIMING_1125_1920x1080_30p	12 /* 74.25 MHz */
#define  VL_TIMING_1125_1920x1080_2997p	13 /* 74.25/1.001 MHz */
#define  VL_TIMING_1125_1920x1080_25p	14 /* 74.25 MHz */
#define  VL_TIMING_1125_1920x1080_24p	15 /* 74.25 MHz */
#define  VL_TIMING_1125_1920x1080_2398p	16 /* 74.25/1.001 MHz */

     /*
      * other "high-definition" formats
      */
#define  VL_TIMING_1250_1920x1080_50p	17 /* SMPTE 295M 148.5 MHz */
#define  VL_TIMING_1250_1920x1080_50i	18 /* SMPTE 295M 74.25 MHz */
#define  VL_TIMING_1125_1920x1035_60i	19 /* SMPTE 260M/240M 74.25 MHz */
#define  VL_TIMING_1125_1920x1035_5994i	20 /* SMPTE 260M/240M 74.25/1.001 MHz*/
#define  VL_TIMING_750_1280x720_60p	21 /* SMPTE 296M 74.25 MHz */
#define  VL_TIMING_750_1280x720_5994p	22 /* SMPTE 296M 74.25/1.001 MHz */
#define  VL_TIMING_525_720x483_5994p	23 /* SMPTE 293M 27.0 MHz */

      /*
       * new SMPTE 274M formats
       *
       *  The timings are obsolete 
       */	
#define  VL_TIMING_1125_1920x1080_48sf        24 /* Sony proposed 274M 74.25 MHz */
#define  VL_TIMING_1125_1920x1080_4795sf      25 /* Sony proposed 274M 74.25/1.001 MHz */


      /*
       * newer SMPTE 274M formats per SMPTE recommended practice
       */
#define  VL_TIMING_1125_1920x1080_24PsF         VL_TIMING_1125_1920x1080_48sf     /* Sony proposed 274M 74.25 MHz */
#define  VL_TIMING_1125_1920x1080_2398PsF       VL_TIMING_1125_1920x1080_4795sf   /* Sony proposed 274M 74.25/1.001 MHz */
#define  VL_TIMING_1125_1920x1080_30PsF         26 /* Sony proposed 274M 74.25 MHz */
#define  VL_TIMING_1125_1920x1080_2997PsF       27 /* Sony proposed 274M 74.25/1.001 MHz */
#define  VL_TIMING_1125_1920x1080_25PsF         28 /* Sony proposed 274M 74.25 MHz */

/*
 * Size/Position Controls:
 *
 * These controls are used to set up the size and position of the video
 * stream. The API specification is as follows:
 *
 * On VL_VIDEO nodes:
 *	VL_SIZE(xy)		size of video
 *	VL_OFFSET(xy)		offset to active region of video
 *
 * On all other nodes:
 *	VL_ZOOM(fract)		the zoom factor for the video stream
 *	VL_OFFSET(xy)		the offset within the video (after zoom)
 *	VL_SIZE(xy)		the clipped size of the video
 *	VL_ORIGIN(xy)		the offset within the node
 *	VL_RATE(fract)		frame rate
 *
 * VL_OFFSET, VL_SIZE are measured in pixels against the
 *      extents of the base unit of VL_CAP_TYPE, ie. frames or fields.
 * 
 * VL_RATE is measured in either frames/second or fields/second depending
 *      on the  unit of VL_CAP_TYPE.
 */
#define VL_ORIGIN		2 
#define VL_OFFSET		3		/* pixels per frames or field */
#define VL_SIZE			4		/* pixels per frames or field */
#define VL_RATE			5		/* frames or fields per second */
#define VL_ZOOM			44		/* nominal, 1.0 is passthough */

/*
 * Data type controls:
 *
 * On any node other than video:
 *	VL_CAP_TYPE(int)	what fields/interleaving for the transfer
 *	VL_PACKING(int)		what pixel packing to use
 */
#define VL_CAP_TYPE		6
#define     VL_CAPTURE_NONINTERLEAVED	0	/* fields */
#define     VL_CAPTURE_INTERLEAVED	1	/* frames */
#define     VL_CAPTURE_EVEN_FIELDS	2	/* fields */
#define     VL_CAPTURE_ODD_FIELDS	3	/* fields */
#define     VL_CAPTURE_FIELDS		4	/* fields */
#define VL_PACKING		7
#define     VL_PACKING_RGB_332_P	0
#define     VL_PACKING_RGBA_8		1	/* really ABGR_8 */
#define     VL_PACKING_RGB_8		2	/* really BGR_8 */
#define     VL_PACKING_RBG_323		3
#define     VL_PACKING_VUY_411_SV	4
#define     VL_PACKING_YVYU_422_8	5
#define     VL_PACKING_Y_8_P		6
#define     VL_PACKING_RGB_332		7
#define     VL_PACKING_BGR_332		8
#define     VL_PACKING_RGB_332_IP	9
#define     VL_PACKING_BGR_332_P	10
#define     VL_PACKING_BGR_332_IP	11
#define     VL_PACKING_RGB_565		12
#define     VL_PACKING_RGB_565_P	13
#define     VL_PACKING_RGB_565_IP	14
#define     VL_PACKING_RGB_8_P		15
#define     VL_PACKING_RGB_10		16
#define     VL_PACKING_Y_8_IP		17
#define     VL_PACKING_YUV_444_8	18
#define     VL_PACKING_YUVA_4444_8	19
#define     VL_PACKING_YUV_444_10	20
#define     VL_PACKING_YUVA_4444_10	21	
#define     VL_PACKING_ABGR_8		22	/* really RGBA_8 (OpenGL) */
#define     VL_PACKING_AUYV_4444_8	23
#define     VL_PACKING_A_2_BGR_10	24
#define     VL_PACKING_A_2_UYV_10	25
#define     VL_PACKING_AYU_AYV_10	26	/* two transfers */ 
#define     VL_PACKING_YVYU_422_10	27
#define     VL_PACKING_AUYV_4444_10	28
#define     VL_PACKING_RGBA_10		29	/* really ABGR_10 */
#define     VL_PACKING_ABGR_10		30	/* really RBGA_10 */
#define     VL_PACKING_ARGB_1555	31	/* 16 bit ARGB (really ARGB :)*/
#define	    VL_PACKING_BGR_8_P		32	/* 444_8 OpenGL packed to 24bit */
#define     VL_PACKING_UYV_8_P		33	/* 444_8 UYV packed into 24 bits */
#define     VL_PACKING_AUYV_8		VL_PACKING_AUYV_4444_8

        			/* new packing list  for the VL1.1 definitions */
#define VL_PACKING_444_332          51    /* packed 332, 1 byte/pixel.  */
#define VL_PACKING_R444_332         52    /* packed 332, 1 byte/pixel.  */
#define VL_PACKING_0444_8           53    /* RGB-8bit  4bytes/pixel.    */
#define VL_PACKING_R0444_8          54    /* RGB-8bit  4bytes/pixel.    */
#define VL_PACKING_444_8            55    /* RGB-8bit  packed 3bytes/pixel.  */
#define VL_PACKING_R444_8           56    /* RGB-8bit  packed 3bytes/pixel.  */
#define VL_PACKING_4444_8           57    /* RGBA-8bit  4bytes/pixel.   */
#define VL_PACKING_R4444_8          58    /* RGBA-8bit  4bytes/pixel.   */
#define VL_PACKING_242_8            60    /* 422-8bit, makes sense only in CCIR, 2bytes/pixel.  */
#define VL_PACKING_R242_8           61    /* 422-8bit, makes sense only in CCIR, 2bytes/pixel.  */
#define VL_PACKING_4_8              62    /* 8bit, luminance only in yuv.  1byte/pixel   */
#define VL_PACKING_4_4				63	  /* 4bit, luminance only in yuv */	
#define VL_PACKING_4444_10_10_10_2   64   /* packed RGBA, 10bits for RGB 2bits for  */
#define VL_PACKING_R4444_10_10_10_2  65   /* packed ABGR, 10bits for RGB 2bits for  */
#define VL_PACKING_2424_10_10_10_2Z  66   /* 4224_10bit per component,  */
#define VL_PACKING_R2424_10_10_10_2Z  67  /* 4224_10bit per component,  */
#define VL_PACKING_242_10_in_16_L     68  /* 422 YUV 16bits with 10 valid bits per  */
#define VL_PACKING_242_10_in_16_R     69  /* 422 YUV 16bits with 10 valid bits per  */
#define VL_PACKING_4444_10_in_16_L    70  /* 4444 16bits with 10 valid bits per component.  */
#define VL_PACKING_4444_10_in_16_R    71  /* 4444 16bits with 10 valid bits per component.  */
#define VL_PACKING_R4444_10_in_16_L   72  /* Reversed 4444, makes sense only for ABGR.  */
#define VL_PACKING_R4444_10_in_16_R   73  /* Reversed 4444, makes sense only for ABGR.  */
#define VL_PACKING_R4440_10_in_16_L   74  /* Reversed 444 paded to 16bits/pixel */
#define VL_PACKING_R4440_10_in_16_R   75  /* Reversed 444 paded to 16bits/pixel */
#define VL_PACKING_4444_13_in_16_L    76  /* 16bits with 13 valid bits per */
#define VL_PACKING_4444_13_in_16_R    77  /* 16bits with 13 valid bits per */
#define VL_PACKING_4444_12_in_16_L    78  /* 16bits with 12 valid bits per */
#define VL_PACKING_4444_12_in_16_R    79  /* 16bits with 12 valid bits per */
#define VL_PACKING_X4444_5551         80  /* 16bits per pixel, with 5bits for R,G,B */
#define VL_PACKING_X444_332           81  /* 8bits per pixel, with 332 for R,G,B.   */
#define VL_PACKING_4444_12            82  /* packed 12bits/comp(RGBA/CrYCbA).   */
#define VL_PACKING_444_12             83  /* packed 12bits/comp(RGBA/CrYCbA).   */
#define VL_PACKING_4444_6             84  /* packed 6bits/comp(RGBA).  3bytes/pixel. */
#define VL_PACKING_444_5_6_5          85  /* packed RGB, 2bytes/pixel.  */
#define VL_PACKING_242_10            86    /* 422-10 bit packed  */
#define VL_PACKING_444_10_in_16_L    87  /* 444 16bits with 10 valid bits per component.  */
#define VL_PACKING_R242_10_in_16_L   88
#define VL_PACKING_R242_10_in_16_R   89
#define VL_PACKING_R242_10           90  /*Reversed 422-10 bit packed  */
#define VL_PACKING_CUSTOM 	     91  /* used to load a device specific packing format */

#define VL_PACKING_DV                92  /* packed lower 8bits/comp Y only */
#define VL_PACKING_SDTI_DV           93  /* packed 8bits/comp */
#define VL_PACKING_444_10_in_16_R    94  /* 444 16bits with 10 valid bits per component. */
#define VL_PACKING_444_12_in_16_L    95  /* 444 16bits with 12 valid bits per component. */
#define VL_PACKING_444_12_in_16_R    96  /* 444 16bits with 12 valid bits per component. */
#define VL_PACKING_2424_8            97  /* 422-8bit, makes sense only in CCIR, 3bytes/pixel.  */
#define VL_PACKING_R2424_8           98  /* 422-8bit, makes sense only in CCIR, 3bytes/pixel.  */
#define VL_PACKING_R242_12_in_16_L   99
#define VL_PACKING_R242_12_in_16_R   100
#define VL_PACKING_R2424_12_in_16_L  101
#define VL_PACKING_R2424_12_in_16_R  102
#define VL_PACKING_242_12_in_16_L    103
#define VL_PACKING_242_12_in_16_R    104
#define VL_PACKING_2424_12_in_16_L   105
#define VL_PACKING_2424_12_in_16_R   106
#define VL_PACKING_R444_10_in_16_R   107
#define VL_PACKING_R444_10_in_16_L   108
#define VL_PACKING_R444_12_in_16_R   109
#define VL_PACKING_R444_12_in_16_L   110
#define VL_PACKING_444_13_in_16_R    111
#define VL_PACKING_444_13_in_16_L    112
#define VL_PACKING_R444_13_in_16_R   113
#define VL_PACKING_R444_13_in_16_L   114

/*
 * XXX VL_PACKING_MAX is used inconsistently in the VL; some places,
 * it is used as total number of packings.  In other places, it
 * is used as the maximum packing *value*.  They are not the same.
 * We keep it the same as it has been, which is the total number
 * of packings, mainly because some arrays are sized as [VL_PACKING_MAX].
 */
#define VL_PACKING_MAX		     115

/*
 * Screen-specific controls:
 *	VL_WINDOW(int)		what window the video should appear in
 */
#define VL_WINDOW		8

/*
 * Video attribute controls:
 */
#define VL_BRIGHTNESS		9
#define VL_CONTRAST		10
#define VL_H_PHASE		11
#define VL_HUE			12
#define VL_SATURATION		56
#define VL_RED_SETUP		13		/* boolean */
#define VL_GREEN_SETUP		14		/* boolean */
#define VL_GRN_SETUP		14
#define VL_BLUE_SETUP		15		/* boolean */
#define VL_BLU_SETUP		15
#define VL_ALPHA_SETUP		57		/* boolean */
#define VL_V_PHASE		16		/* in lines, nominal 0 */
#define VL_SIGNAL		17
#define     VL_SIGNAL_NOTHING		0
#define     VL_SIGNAL_BLACK		1
#define     VL_SIGNAL_REAL_IMAGE	2
#define     VL_SIGNAL_COLOR_BARS	3
#define VL_FREEZE		18
#define VL_DEFAULT_DRAIN	19
#define VL_MUXSWITCH		20
#define VL_FORMAT		21
#define     VL_FORMAT_COMPOSITE				0
#define     VL_FORMAT_SVIDEO		 		1
#define     VL_FORMAT_RGB		 		2 /* full range */
#define     VL_FORMAT_BETACAM		 		3
#define     VL_FORMAT_MII		 		4
#define     VL_FORMAT_SMPTE_YUV		 		5
#define     VL_FORMAT_DIGITAL_COMPOSITE	 		6
#define     VL_FORMAT_DIGITAL_COMPONENT	 		7 /* parallel */
#define     VL_FORMAT_DIGITAL_COMPONENT_SERIAL	 	8
#define     VL_FORMAT_DIGITAL_COMPONENT_DUAL	 	9 /* 4:4:4:4  */
#define     VL_FORMAT_DIGITAL_COMPONENT_DUAL_SERIAL	10 /* 4:4:4:4 serial */
#define     VL_FORMAT_DIGITAL_INDYCAM			11
#define     VL_FORMAT_DIGITAL_CAMERA			11 /* onboard camera */
						   /* ... replaces "INDYCAM" */
#define     VL_FORMAT_DIGITAL_COMPONENT_RGB		12 /* 4:4:4:4 rgb */
#define     VL_FORMAT_DIGITAL_COMPONENT_RGB_SERIAL	13 /* 4:4:4:4 rgb */
#define     VL_FORMAT_RAW_DATA				14 /* Arbitrary data */
#define VL_SYNC			22
#define     VL_SYNC_INTERNAL		0
#define     VL_SYNC_GENLOCK		2
#define VL_SYNC_SOURCE		58		/* input for VL_SYNC_GENLOCK */


/* Blend functions: not all products support all fcns */
#define VL_BLEND_A_FCN		34
#define VL_BLEND_B_FCN		59
#define     VL_BLDFCN_ZERO              0  /*  0 */
#define     VL_BLDFCN_ONE               1  /*  1 */
#define     VL_BLDFCN_A_ALPHA		2  /*  (A alpha)*/
#define     VL_BLDFCN_B_ALPHA		3  /*  (B alpha)  */
#define     VL_BLDFCN_MINUS_A_ALPHA	4  /*  1 - (A alpha) */
#define     VL_BLDFCN_MINUS_B_ALPHA	5  /*  1 - (B alpha) */
#define VL_BLEND_A		35 /* A source node */
#define VL_BLEND_B		36 /* B source node */
#define VL_BLEND_A_ALPHA	37 /* A alpha node */
#define VL_BLEND_B_ALPHA	38 /* B alpha node */
#define VL_BLEND_A_NORMALIZE	39 /* A follows porter-duff model, boolean */
#define VL_BLEND_B_NORMALIZE	60 /* B follows porter-duff model, boolean */
#define VL_BLEND_OUT_NORMALIZE	61 /* OUT follows porter-duff model, boolean */

/* Advisory controls */
#define VL_SUPERVISORY_PATH	62 /* Is this path supervisory? */

/*
 * VL_ASPECT complements VL_ZOOM;
 *   the resulting zoom values after VL_ASPECT
 *   is applied are:
 *
 *     X Zoom = VL_ZOOM * VL_ASPECT
 *     Y Zoom = VL_ZOOM
 *
 *   common values are:
 *    1:1 no change to VL_ZOOM
 *    1:2 X (width) half the Y (height)
 *   (this compensates for the difference in aspect
 *    when capturing fields only.)
 */
#define	VL_ASPECT		63	/* Aspect Ratio (1:2 means 1/2 X) */

/* signal processing filters */
#define	VL_FLICKER_FILTER	64	/* input control - flicker filter */
#define	VL_DITHER_FILTER	65	/* input control - dither filter */
#define	VL_NOTCH_FILTER		66	/* output control - notch filter */

#define VL_LAYOUT		67	/* memory layout */
#define     VL_LAYOUT_LINEAR		0	/* images */
#define     VL_LAYOUT_GRAPHICS		1	/* pbuffers and textures */
#define     VL_LAYOUT_MIPMAP		2	/* mipmaps */


#define VL_FIELD_DOMINANCE 68 /* Field dominance controls */
#define VL_F1_IS_DOMINANT 0
#define VL_F2_IS_DOMINANT 1

#define VL_COLORSPACE  69		/* Colorspace control */
#define     VL_COLORSPACE_NONE    0	/* raw data */
#define     VL_COLORSPACE_RGB     1	/* full-range RGB (ITU-R BT.601-5) */
#define     VL_COLORSPACE_CCIR601 2	/* YCrCb (ITU-R BT.601-5) */
#define     VL_COLORSPACE_RP175   3	/* headroom-range RGB (SMPTE RP175) */
#define     VL_COLORSPACE_YUV     4	/* full-range YUV */

#define     VL_COLORSPACE_REC601_YCRCB    VL_COLORSPACE_CCIR601
#define     VL_COLORSPACE_REC601_YUV      VL_COLORSPACE_YUV
#define	    VL_COLORSPACE_REC601_RGB_H    VL_COLORSPACE_RP175
#define	    VL_COLORSPACE_REC601_RGB_F	  VL_COLORSPACE_RGB

#define     VL_COLORSPACE_240M_YCRCB      5	/* YCrCb (SMPTE 240M) */
#define     VL_COLORSPACE_240M_YUV        6	/* full-range YUV (SMPTE 240M) */
#define     VL_COLORSPACE_240M_RGB_H      7	/* headroom-range RGB (SMPTE 240M) */
#define     VL_COLORSPACE_240M_RGB_F      8	/* full-range RGB (SMPTE 240M) */

#define     VL_COLORSPACE_REC709_YCRCB    9	/* YCrCb (ITU-R BT.709-2 60Hz) */
#define     VL_COLORSPACE_REC709_YUV      10	/* full-range YUV (ITU-R BT.709-2 60Hz) */
#define     VL_COLORSPACE_REC709_RGB_H    11	/* headroom-range RGB (ITU-R BT.709-2 60Hz) */
#define     VL_COLORSPACE_REC709_RGB_F    12	/* full-range RGB (ITU-R BT.709-2 60Hz) */


#define VL_COMPRESSION  70		/* compression control, memory nodes only */
#define VL_COMPRESSION_NONE   0
#define VL_COMPRESSION_RICE   1
#define VL_COMPRESSION_JPEG   2
#define VL_COMPRESSION_MPEG2  3
#define VL_COMPRESSION_DVCPRO 4
#define VL_COMPRESSION_DV     5
#define VL_COMPRESSION_DVCPRO50 6 


#define VL_RICE_COMP_PRECISION 71  /* precision for rice data */
#define VL_RICE_COMP_PRECISION_8             0
#define VL_RICE_COMP_PRECISION_10            1
#define VL_RICE_COMP_PRECISION_12            2
#define VL_RICE_COMP_PRECISION_13            3

#define VL_RICE_COMP_SAMPLING  72  		/* sampling */
#define VL_RICE_COMP_SAMPLING_422           0
#define VL_RICE_COMP_SAMPLING_4224          1
#define VL_RICE_COMP_SAMPLING_444           2
#define VL_RICE_COMP_SAMPLING_4444          3

#define VL_RICE_COMP_DITHER       73   /* turn on/off */
#define VL_RICE_COMP_DITHER_OFF   0
#define VL_RICE_COMP_DITHER_ON    1

#define VL_TRANSFER_TRIGGER  	74   /* xfer trig setup */

#define VL_GPI_OUT_MODE		    75	/* setup to assert gpi out */
									/* condition */
#define VL_GPI_OUT_XFER_START 1
#define VL_GPI_OUT_XFER_STOP  2

			/* set the state to one of these */

#define VL_GPI_CLEAR			0 /* clear any pending GPI triggers */
#define VL_GPI_ON			1
#define VL_GPI_OFF			2
#define VL_GPI_PULSE			3  /* transition state for 1 field time */

#define VL_GPI_STATE			76	/* set or get GPI state */
#define VL_GPI_IN			1
#define VL_GPI_OUT			2


#define VL_SDTI_MODE                    77 /* set or get SDTI state */
#define VL_SDTI_MODE_OFF                0
#define VL_SDTI_MODE_ON                 1  /* fixed sized DV packets */
#define VL_SDTI_MODE_VARIABLE_ON        2  /* variable sized packets */

#define VL_SDTI_HEADER                  78

/*
 * Control classes:
 */

typedef unsigned int VLControlClass; /* one of the following values: */

#define VL_CLASS_NO_UI		0
#define VL_CLASS_SLIDER         1
#define VL_CLASS_KNOB           2
#define VL_CLASS_BUTTON         3
#define VL_CLASS_TOGGLE         4
#define VL_CLASS_DETENT_KNOB    5
#define VL_CLASS_LIST		6

#define VL_CLASS_RDONLY		0x8000	/* control is read-only */
#define VL_CLASS_WRONLY		0x4000	/* control is write-only */
#define VL_CLASS_NO_DEFAULT     0x2000  /* don't save in default files */
#define VL_CLASS_NORMALIZE	0x10000	/* normalize value */
#define VL_CLASS_VALIDATE	0x20000	/* validate value */

#define VL_IS_CTL_RDONLY(x)	((x)->ctlClass & VL_CLASS_RDONLY)
#define VL_IS_CTL_WRONLY(x)	((x)->ctlClass & VL_CLASS_WRONLY)
#define VL_IS_CTL_RW(x)		(!(VL_IS_CTL_RDONLY(x) || VL_IS_CTL_WRONLY(x)))

#define VL_CLASS_MASK		0xfff


typedef unsigned int VLControlGroup;  /* one of the following values: */

#define VL_CTL_GROUP_BLENDING			0
#define VL_CTL_GROUP_VISUALQUALITY		1
#define VL_CTL_GROUP_SIGNAL			2
#define VL_CTL_GROUP_CODING			3
#define VL_CTL_GROUP_SYNC			4
#define VL_CTL_GROUP_ORIENTATION		5
#define VL_CTL_GROUP_SIZING			6
#define VL_CTL_GROUP_RATES			7
#define VL_CTL_GROUP_WS				 8	/* Window System */
#define VL_CTL_GROUP_PATH			 9	/* Path Controls */
#define VL_CTL_GROUP_SIGNAL_ALL			10	/* comp & component */
#define VL_CTL_GROUP_SIGNAL_COMPOSITE		11	/* Controls composite */
#define VL_CTL_GROUP_SIGNAL_COMPONENT		12	/* Controls component */
#define VL_CTL_GROUP_SIGNAL_CLUT_COMPOSITE	13	/* CLUT composite */
#define VL_CTL_GROUP_SIGNAL_CLUT_COMPONENT	14	/* CLUT component */
#define VL_CTL_GROUP_KEYING			15

#define VL_CTL_GROUP_PRO		0x8000	/* control is a Pro Control */

#define VL_IS_CTL_PRO(x)	((x)->group & VL_CTL_GROUP_PRO)
#define VL_IS_CTL_COMMON(x)	(!((x)->group & VL_CTL_GROUP_PRO))

#define VL_CTL_GROUP_MASK		0xfff


typedef int VLControlValueType;	/* one of the following values: */

#define VL_CT_FRACT	1
#define VL_CT_BOOL	2
#define VL_CT_INT	3
#define VL_CT_UINT	4
#define VL_CT_XY	5
#define VL_CT_EXT	6
#define VL_CT_STRING	7
#define VL_CT_MATRIX	8
#define VL_CT_XFER_TRIG 9
#define VL_CT_GPI_OUT_MODE  10
#define VL_CT_GPI_STATE 11


typedef struct {
    char name[VL_NAME_SIZE];
    int value;
} VLControlItem;

typedef struct __vlControlInfo {
    char name[VL_NAME_SIZE]; /* name of control */
    VLControlType type;      /* e.g. WINDOW, HUE, BRIGHTNESS */
    VLControlClass ctlClass; /* SLIDER, DETENT, KNOB, BUTTON */
    VLControlGroup group;    /* BLEND, VISUAL QUALITY, SIGNAL, SYNC */
    VLNode node;             /* associated node */
    VLControlValueType valueType;	/* what kind of data do we have */
    int valueCount;		/* how many data items do we have */
    int numFractRanges;     /* number of ranges to describe control */
    VLFractionRange *ranges; /* range of values of control */

    int numItems;		/* number of enumerated items */
    VLControlItem *itemList;	/* the actual enumerations */
} VLControlInfo;

/* These are the associated types for VLExtendedValues */
enum VLDataType {VL_LUT_BYPASS = 1, VL_LUT_GAMMA, VL_LUT_DIRECT, VL_LUT_LINEAR};

typedef struct {
    int  dataType;	/* one of the above enums... must be set */
    int  dataSize;	/* size in bytes */
    void *dataPointer;	
} VLExtendedValue;

/* Structure used by the VL to store the size of the different controls: */
typedef union {
    VLFraction	fractVal;
    VLBoolean	boolVal;
    int		intVal;
    VLXY	xyVal;
    char	stringVal[96];  /* beware of trailing NULLs! */
    float	matrixVal[3][3];	
    uint	pad[24];	/* reserved */
	VLTrigger xfer_trigger;  /* for transfers */
	VLGPIOutMode gpi_out;	/* gpi output triggers */
	VLGPIState   gpi_state; /* gpi state set or get */
    VLExtendedValue extVal;/* for large data values */
} VLControlValue;

typedef struct {
    int numControls;
    VLControlInfo *controls;
} VLControlList;

/* Trigger-specific definitions */

typedef union {
	VLNode refnode;	/* trigger defined re this node - MSC */
} VLTriggerParam;
	
/* Trigger-specific data */
typedef struct {
	VLTriggerParam param;
	VLTriggerVal val;
} VLTriggerData;

extern int           vlGetControl(
    VLServer,		/* Server Handle */
    VLPath,		/* Path Handle */
    VLNode,		/* node */
    VLControlType,	/* Type, from list above */
    VLControlValue *	/* the value to be returned */
);

extern VLControlInfo *vlGetControlInfo(
    VLServer,		/* Server Handle */
    VLPath,		/* Path Handle */
    VLNode,		/* Source/Drain */
    VLControlType	/* Type, from list above */
);

extern int vlFreeControlInfo(
    VLServer,		/* Server Handle */
    VLControlInfo *	/* Pointer from vlGetControlInfo */
);

extern VLControlList *vlGetControlList(
    VLServer,		/* Server Handle */
    VLPath		/* Path Handle */
);

extern int vlFreeControlList(
    VLServer,		/* Server Handle */
    VLControlList *	/* Pointer from vlGetControlList */
);

extern int vlSetControl(
    VLServer,		/* Server Handle */
    VLPath,		/* Path Handle */
    VLNode,		/* node */
    VLControlType,	/* Type, from list above */
    VLControlValue *	/* the value to be set */
);

extern int vlSetControlTrigger(
    VLServer,		/* Server Handle */
    VLPath,		/* Path Handle */
    VLNode,		/* node */
    VLTriggerType,	/* type of trigger */
    VLTriggerData *,	/* Trigger-specific info */
    VLControlType,	/* Type, from list above */
    VLControlValue *	/* the value to be set */
);

extern int vlSetControlInLine(
    VLServer,		/* Server Handle */
    VLPath,		/* Path Handle */
    VLNode,		/* target node */
    VLNode,		/* reference node */
    VLControlType,	/* Type, from list above */
    VLControlValue *	/* the value to be set */
);


/*----------------------------------------------------------------------*/

/*
 * Path usage:
 */

typedef VLPath *VLPathList;

typedef short VLUsageType;

#define VL_DONE_USING	0x0000
#define VL_READ_ONLY	0x0001
#define VL_SHARE	0x0002
#define VL_LOCK	0x0003
#define VL_MAX_USAGE	0x0004

extern int vlSetupPaths(
    VLServer,		/* Server Handle */
    VLPathList,         /* list of Path Handles */
    int,                /* Number of PathHandles */
    VLUsageType,        /* CtrlUsage */
    VLUsageType         /* StreamUsage */
);

extern int vlSetConnection(
    VLServer,		/* Server Handle */
    VLPath,		/* Path Handle */
    VLNode,		/* Source node */
    VLPort,		/* Source port */
    VLNode, 		/* Target node */
    VLPort,		/* Target port */
    VLBoolean		/* Pre-emp */
);

extern int vlGetConnection(
    VLServer,		/* Server Handle */
    VLPath,		/* Path Handle */
    VLNode,		/* Source node */
    VLPort,		/* Source port */
    VLNode *,		/* Array of connected node(s) */
    VLPort *,		/* Array of connected port(s) */
    int *n		/* nodes allocated/nodes returned */
);

typedef uint VLEventMask;

/*
 * Transfer modes:
 */

#define VL_TRANSFER_MODE_CONTINUOUS	101
#define VL_TRANSFER_MODE_DISCRETE	102
#define VL_TRANSFER_MODE_AUTOTRIGGER	103

#define VLTriggerImmediate	VLNoEventsMask

typedef struct VLTransferDescriptor {
    int mode;
    VLEventMask trigger;
    short delay;
    short count;
    int sequence;
    unsigned long long ustime;
} VLTransferDescriptor;

extern int vlBeginTransfer(
    VLServer,		/* Server Handle */
    VLPath,		/* Path Handle */
    int,		/* Count of descriptors */
    VLTransferDescriptor *	/* array of transfer descriptors */
);

extern int vlEndTransfer(
    VLServer,		/* Server Handle */
    VLPath		/* Path Handle */
);

/*
 * Events
 */

typedef void (*VLEventHandler)(uint, void *);
typedef int  (*VLPendingFunc)(void *);

/* Start with 2 since 0 and 1 are reserved for daemon */
#define	VLFIRSTEvent		2
#define	VLStreamBusy		2	/* Stream is locked */
#define	VLStreamPreempted	3	/* Stream was grabbed */
#define	VLAdvanceMissed		4	/* Already reached time */
#define	VLStreamAvailable	5	/* Stream has been released */
#define	VLSyncLost		6	/* Sync isn't being detected */
#define	VLStreamStarted		7	/* Stream started delivery */
#define	VLStreamStopped		8	/* Stream stopped delivery */
#define	VLSequenceLost		9	/* A Field/Frame dropped */
#define	VLControlChanged	10	/* A Control has changed */
#define	VLTransferComplete	11	/* A Transfer has completed */
#define	VLTransferFailed	12	/* A Transfer has failed */
#define	VLEvenVerticalRetrace	13	/* A Vertical Retrace event */
#define	VLOddVerticalRetrace	14	/* A Vertical Retrace event */
#define	VLFrameVerticalRetrace	15	/* A Vertical Retrace event */
#define	VLDeviceEvent		16	/* A Vertical Retrace event */
#define	VLDefaultSource		17	/* Default Source Changed */
#define VLControlRangeChanged	18
#define VLControlPreempted	19
#define VLControlAvailable	20
#define	VLDefaultDrain		21	/* Default Drain Changed */
#define	VLStreamChanged		22	/* Path connectivity changed */
#define	VLTransferError		23	/* A Single Transfer errored */
#define	VLInvalidControl	24	/* Frame-accurate ctrl chg was late */

#define	VLEventToMask(event)		(1<<((event)-VLFIRSTEvent))
#define VLStreamBusyMask		VLEventToMask(VLStreamBusy)
#define VLStreamPreemptedMask		VLEventToMask(VLStreamPreempted)
#define VLAdvanceMissedMask		VLEventToMask(VLAdvanceMissed)
#define VLStreamAvailableMask		VLEventToMask(VLStreamAvailable)
#define VLSyncLostMask			VLEventToMask(VLSyncLost)
#define VLStreamStartedMask		VLEventToMask(VLStreamStarted)
#define VLStreamStoppedMask		VLEventToMask(VLStreamStopped)
#define VLSequenceLostMask		VLEventToMask(VLSequenceLost)
#define VLControlChangedMask		VLEventToMask(VLControlChanged)
#define VLTransferCompleteMask		VLEventToMask(VLTransferComplete)
#define VLTransferFailedMask		VLEventToMask(VLTransferFailed)
#define VLEvenVerticalRetraceMask	VLEventToMask(VLEvenVerticalRetrace)
#define VLOddVerticalRetraceMask	VLEventToMask(VLOddVerticalRetrace)
#define VLFrameVerticalRetraceMask	VLEventToMask(VLFrameVerticalRetrace)
#define VLDeviceEventMask		VLEventToMask(VLDeviceEvent)
#define VLDefaultSourceMask		VLEventToMask(VLDefaultSource)
#define VLControlRangeChangedMask	VLEventToMask(VLControlRangeChanged)
#define VLControlPreemptedMask		VLEventToMask(VLControlPreempted)
#define VLControlAvailableMask		VLEventToMask(VLControlAvailable)
#define VLDefaultDrainMask		VLEventToMask(VLDefaultDrain)
#define VLStreamChangedMask		VLEventToMask(VLStreamChanged)
#define VLTransferErrorMask		VLEventToMask(VLTransferError)
#define VLInvalidControlMask		VLEventToMask(VLInvalidControl)

#define VLLASTEvent		(128) /* must be bigger than any event # */

#define VLAllEventsMask		(~0)
#define VLNoEventsMask		0

typedef struct __vlAnyEvent {
    int reason;
    VLServer server;
    VLDev device;
    VLPath path;
    uint time;
    uint serial;
} VLAnyEvent;

typedef VLAnyEvent VLStreamBusyEvent;
typedef VLAnyEvent VLStreamPreemptedEvent;
typedef VLAnyEvent VLAdvanceMissedEvent;
typedef VLAnyEvent VLStreamAvailableEvent;
typedef VLAnyEvent VLSyncLostEvent;
typedef VLAnyEvent VLStreamStartedEvent;
typedef VLAnyEvent VLStreamStoppedEvent;
typedef VLAnyEvent VLOddVerticalRetraceEvent;
typedef VLAnyEvent VLEvenVerticalRetraceEvent;
typedef VLAnyEvent VLFrameVerticalRetraceEvent;
typedef VLAnyEvent VLTransferFailedEvent;


typedef struct __vlTransferCompleteEvent {
    int reason;
    VLServer server;
    VLDev device;
    VLPath path;
    uint time;
    uint serial;
	uint msc;
} VLTransferCompleteEvent;

typedef struct __vlSequenceLostEvent {
    int reason;
    VLServer server;
    VLDev device;
    VLPath path;
    uint time;
    int serial;

    VLBoolean field;	/* TRUE == field, FALSE == frame */
    int number;		/* sequence number of dropped field or frame */
    int count;		/* number of dropped fields or frames */
} VLSequenceLostEvent;

typedef struct __vlControlChangedEvent {
    int reason;
    VLServer server;
    VLDev device;
    VLPath path;
    uint time;
    int serial;
    VLNode node;
    VLControlType type;
    VLControlValue value;
} VLControlChangedEvent;

typedef struct __vlControlRangeChangedEvent {
    int reason;
    VLServer server;
    VLDev device;
    VLPath path;
    uint time;
    int serial;
    VLNode node;
    VLControlType type;
} VLControlRangeChangedEvent;

typedef VLControlRangeChangedEvent VLControlPreemptedEvent;
typedef VLControlRangeChangedEvent VLControlAvailableEvent;

typedef struct __vlDeviceEventEvent {
    int reason;
    VLServer server;
    VLDev device;
    VLPath path;
    uint time;
    int serial;
    int value;		/* device-specific info */
} VLDeviceEventEvent;

typedef struct __vlDefaultNodeEvent {
    int reason;
    VLServer server;
    VLDev device;
    VLPath path;
    uint time;
    int serial;
    VLNode node;
} VLDefaultNodeEvent;

typedef VLDefaultNodeEvent VLDefaultSourceEvent;
typedef VLDefaultNodeEvent VLDefaultDrainEvent;

typedef struct __vlErrorEvent {
    int reason;
    VLServer server;
    VLDev device;
    VLPath path;
    uint time;
    int serial;

    int errorCode;
    int resourceId;
    int majorCode;
    int minorCode;
} VLErrorEvent;

typedef struct __vlStreamChangedEvent {
    int reason;
    VLServer server;
    VLDev device;
    VLPath path;
    uint time;
    int serial;
    VLNode srcnode;
    VLPort srcport;
    VLNode drnnode;
    VLPort drnport;
} VLStreamChangedEvent;

/* errTypes */
#define VLTranferErrorEDH  0

/* flags for EDH error */

#define VL_EDH_LINK_A    		(0 << 0x0 )
#define VL_EDH_LINK_B	   		(1 << 0x1 )
#define VL_EDH_EDA_FullFld 		(1 << 0x2 )
#define VL_EDH_EDH_FullFld		(1 << 0x3 )
#define VL_EDH_UES				(1 << 0x4 )
#define VL_EDH_EDH_ActiveFld 	(1 << 0x5 )
#define VL_EDH_EDA_AncillaryFld (1 << 0x6 )
#define VL_EDH_EDH_AncillaryFld	(1 << 0x7 )
#define VL_EDH_IDA				(1 << 0x8 )
#define VL_EDH_IDH  			(1 << 0x9 )

typedef struct __vlTransferErrorEvent {
    int reason;
    VLServer server;
    VLDev device;
    VLPath path;
    uint time;
    uint serial;
    uint msc; 	/* msc of the field/frame that has the error. */
    uint errType; /* EDH etc... */
    uint flags;
	uint count;
} VLTransferErrorEvent;
typedef struct __vlInvalidControlEvent {
    int reason;
    VLServer server;
    VLDev device;
    VLPath path;
    uint time;
    uint serial;
    VLNode node;
    VLControlType type;
    VLControlValue value;
} VLInvalidControlEvent;

typedef union __vlEvent {
    int reason;
    VLAnyEvent vlany;
    VLStreamBusyEvent vlstreambusy;
    VLStreamPreemptedEvent vlstreampreempted;
    VLAdvanceMissedEvent vladvancemissed;
    VLStreamAvailableEvent vlstreamavailable;
    VLSyncLostEvent vlsynclost;
    VLStreamStartedEvent vlstreamstarted;
    VLStreamStoppedEvent vlstreamstopped;
    VLSequenceLostEvent vlsequencelost;
    VLControlChangedEvent vlcontrolchanged;
    VLControlRangeChangedEvent vlcontrolrangechanged;
    VLControlPreemptedEvent vlcontrolpreempted;
    VLControlAvailableEvent vlcontrolavailable;
    VLTransferCompleteEvent vltransfercomplete;
    VLTransferFailedEvent vltransferfailed;
    VLEvenVerticalRetraceEvent vlevenverticalretrace;
    VLOddVerticalRetraceEvent vloddverticalretrace;
    VLFrameVerticalRetraceEvent vlframeverticalretrace;
    VLDeviceEventEvent vldeviceevent;
    VLDefaultSourceEvent vldefaultsource;
    VLDefaultDrainEvent vldefaultdrain;
    VLErrorEvent vlerror;
    VLStreamChangedEvent vlstreamchanged;
    VLTransferErrorEvent vltransfererror;
    VLInvalidControlEvent vlinvalidcontrolevent;
} VLEvent;

extern int vlPending(
    VLServer		/* Server */
);

extern int vlSelectEvents(
    VLServer,		/* Server Handle */
    VLPath,		/* Path Handle */
    VLEventMask		/* Events of Interest */
);

extern int vlRegisterHandler(
    VLServer,		/* Server */
    int,		/* fd */
    VLEventHandler,	/* Event Handler */
    VLPendingFunc,	/* pending check if there is one */
    void *		/* user data */
);

extern int vlRemoveHandler(
    VLServer,		/* Server */
    int			/* fd */
);

extern void vlMainLoop(
    void
);

extern char *vlEventToName(
    int		/* Event Type */
);

extern int vlNextEvent(
    VLServer,		/* Server */
    VLEvent *		/* Event Return Value */
);

extern int vlPeekEvent(
    VLServer,		/* Server */
    VLEvent *		/* Event Return Value */
);

extern int vlCheckEvent(
    VLServer,		/* Server */
    VLEventMask,	/* mask */
    VLEvent *		/* Event Return Value */
);

typedef void (*VLCallbackProc)(
    VLServer,		/* Server Handle */
    VLEvent *,		/* Event Structure Pointer */
    void *		/* Client Data */
);

extern int vlAddCallback(
    VLServer,		/* Server Handle */
    VLPath,		/* Path Handle */
    VLEventMask,	/* Events on which to invoke callbacks */
    VLCallbackProc,	/* Callback Procedure */
    void *		/* Client Data */
);

extern int vlRemoveCallback(
    VLServer,		/* Server Handle */
    VLPath,		/* Path Handle */
    VLEventMask,	/* Events from which to remove callbacks */
    VLCallbackProc,	/* Callback Procedure */
    void *		/* Client Data */
);

extern int vlRemoveAllCallbacks(
    VLServer,		/* Server Handle */
    VLPath,		/* Path Handle */
    VLEventMask		/* Events on which to invoke callbacks */
);

extern int vlCallCallbacks(
    VLServer,		/* Server Handle */
    VLEvent *		/* event for call backs */
);

/*
 * Convenience routines
 */

typedef struct _DMRingBuffer *VLBuffer;
typedef char * VLInfoPtr;

extern int vlGetTransferSize(
    VLServer,		/* Server Handle */
    VLPath		/* Path Handle */
);

int vlRegisterBuffer(
    VLServer,		/* Server Handle */
    VLPath,		/* Path Handle */
    VLNode,		/* Memory node id */
    VLBuffer		/* ring buffer handle from dmRBCreate */
);

int vlDeregisterBuffer(
    VLServer,		/* Server Handle */
    VLPath,		/* Path Handle */
    VLNode,		/* Memory node id */
    VLBuffer		/* the ring buffer handle */
);

VLBuffer vlCreateBuffer(
    VLServer,		/* The Server Handle */
    VLPath,		/* The Path Handle */
    VLNode,		/* the Node Handle */
    int			/* number of frames in the buffer */
);

int vlBufferAdvise(
    VLBuffer,		/* the ring buffer handle */
    int			/* Advisory type */
);

#define VL_CA_TAG_GAMMA  1	/* parm is a double * */
#define VL_CA_TAG_MATRIX 2      /* parm is a 3x4 matrix of coefficients */
#define VL_CA_TAG_FLAG	 3	/* parm is a random flag */

int vlConversionAdviseGamma(
    VLServer svr,
    VLPath   path,	       
    int      sourcePacking,
    int      destPacking,
    double   gamma
);		       

int vlConversionAdviseMatrix(
    VLServer svr,
    VLPath   path,	       
    int      sourcePacking,
    int      destPacking,
    double   *matrix
);		       

int vlConversionAdviseFlag(
    VLServer svr,
    VLPath   path,	       
    int      sourcePacking,
    int      destPacking,
    int      flag
);		       

#define VL_BUFFER_ADVISE_NOACCESS 1 /* Contents of buffer are not accessed */
#define VL_BUFFER_ADVISE_ACCESS   2 /* Contents of buffer will be accessed */

int vlBufferGetFd(
    VLBuffer		/* Buffer handle */
);

int vlGetFilled(
    VLServer,           /* Server Handle */
    VLPath,             /* Path Handle   */
    VLBuffer            /* Buffer Handle */
);

VLInfoPtr vlGetNextValid(
    VLServer,		/* Server Handle */
    VLBuffer		/* Buffer Handle */
);

VLInfoPtr vlGetLatestValid(
    VLServer,		/* Server Handle */
    VLBuffer		/* Buffer Handle */
);

VLInfoPtr vlGetNextFree(
    VLServer,		/* Server Handle */
    VLBuffer,		/* Buffer Handle */
    int			/* size of the buffer */
);

void * vlGetActiveRegion(
    VLServer,		/* Server Handle */
    VLBuffer,		/* Buffer Handle */
    VLInfoPtr info	/* info handle */
);

DMediaInfo * vlGetDMediaInfo(
    VLServer,		/* Server Handle */
    VLBuffer,		/* Buffer Handle */
    VLInfoPtr		/* Info Handle */
);

DMImageInfo * vlGetImageInfo(
    VLServer,		/* Server Handle */
    VLBuffer,		/* Buffer Handle */
    VLInfoPtr		/* Info Handle */
);

int vlPutFree(
    VLServer,		/* Server Handle */
    VLBuffer		/* Buffer handle */
);

int vlPutValid(
    VLServer,		/* Server Handle */
    VLBuffer		/* Buffer handle */
);

int vlBufferDone(
    VLBuffer		/* Buffer Handle */
);

int vlBufferReset(
    VLServer,		/* Server Handle */
    VLBuffer		/* Buffer Handle */
);

int vlDestroyBuffer(
    VLServer,		/* Server Handle */
    VLBuffer		/* Buffer Handle */
);

extern uint vlInitDevice(
    VLServer,		/* Server Handle */
    VLDev,		/* Device Handle */
    const char *	/* path name to defaults file, or NULL */
);

/*
 * VL 1.1 routines incorporating DMbuffer interfaces.
 */
int vlDMGetParams(
    VLServer, 		/* Server Handle */
    VLPath, 		/* Path Handle */
    VLNode,		/* Node Handle */
    DMparams*		/* Params Handle */
);

int vlDMPoolRegister(
    VLServer,		/* Server Handle */
    VLPath,		/* Path Handle */
    VLNode,		/* Node Handle */
    DMbufferpool	/* DMbufferpool Handle */
);

int vlDMPoolDeregister(
    VLServer, 		/* Server Handle */
    VLPath,		/* Path Handle */
    VLNode,		/* Node Handle */
    DMbufferpool	/* DMbufferpool Handle */
);

int vlDMBufferPutValid(
    VLServer, 		/* Server Handle */
    VLPath,		/* Path Handle */
    VLNode,		/* Node Handle */
    DMbuffer		/* DMbuffer Handle */
);

int vlDMBufferGetValid(
    VLServer, 		/* Server Handle */
    VLPath,		/* Path Handle */
    VLNode,		/* Node Handle */
    DMbuffer*		/* Pointer to DMbuffer */
);

int vlNodeGetFd(
    VLServer, 		/* Server Handle */
    VLPath,		/* Path Handle */
    VLNode		/* Node Handle */
);

int vlDMBufferGetFilledByNode(
    VLServer,           /* Server Handle */
    VLPath,             /* Path Handle   */
    VLNode              /* Node Handle */
);

int vlDMBufferResetNode(
    VLServer, 		/* Server Handle */
    VLPath,		/* Path Handle */
    VLNode		/* Node Handle */
);

int vlDMBufferSetOutputFillpoint(
    VLServer, 		/* Server Handle */
    VLPath,		/* Path Handle */
    VLNode,		/* Node Handle */
    int			/* fill point */
);

int vlDMBufferSetInputFillpoint(
    VLServer, 		/* Server Handle */
    VLPath,		/* Path Handle */
    VLNode,		/* Node Handle */
    int			/* fill point */
);

int vlDMBufferGetVideoInfo(
    DMbuffer,		/* DMbuffer handle */
    DMBufferVideoInfo*	/* Destination Video info pointer */
);

int vlDMBufferSetVideoInfo(
    DMbuffer,		/* DMbuffer handle */
    DMBufferVideoInfo*	/* Source Video info pointer */
);

/*
 * libdvl routine. These are non-portable and supported on the
 * O2 platform only.
 */
int vlGetFilledByNode(
    VLServer, 		/* Server Handle */
    VLPath,		/* Path Handle */
    VLNode		/* Node Handle */
);

int vlDMBufferSend(
    VLServer, 		/* Server Handle */
    VLPath,		/* Path Handle */
    DMbuffer		/* DMbuffer Handle */
);

int vlEventRecv(
    VLServer, 		/* Server Handle */
    VLPath,		/* Path Handle */
    VLEvent *		/* Event */
);

int vlEventToDMBuffer(
    VLEvent *,		/* Event to translate */
    DMbuffer *		/* return DMbuffer */
);

int vlPathGetFD(
    VLServer, 		/* Server Handle */
    VLPath,		/* Path Handle */
    int *		/* Return FD */
);

int vlDMPoolGetParams(
    VLServer, 		/* Server Handle */
    VLPath, 		/* Path Handle */
    VLNode,		/* Node Handle */
    DMparams*		/* Params Handle */
);

/*
 * UST/MSC support;
 */

extern stamp_t vlGetFrontierMSC(
    VLServer,           /* Server Handle */
    VLPath,             /* Path Handle   */
    VLNode              /* Mem Node Handle */
);

extern int vlGetUSTMSCPair(
    VLServer,           /* Server Handle */
    VLPath,             /* Path Handle   */
    VLNode,             /* VL_VIDEO or VL_SCREEN Node (the jack) */		   
    VLPort,             /* Port on that Node (picks out a jack) */
    VLNode,             /* Memory Node */
    USTMSCpair *        /* returned ust/msc pair */
);

extern double vlGetUSTPerMSC(
    VLServer,		/* Server Handle   */ 
    VLPath,		/* Path Handle     */
    VLNode		/* Mem Node Handle */		     
);


extern stamp_t vlGetPathDelay(
    VLServer,           /* Server Handle */
    VLPath,             /* Path Handle   */
    VLNode,             /* jack1 node */
    VLPort,             /* VL_ANY for default jack */
    VLNode,             /* jack2 node */
    VLPort              /* VL_ANY for default jack */
);		      

/*
 * Default management routines
 */

extern int vlSaveSystemDefaults(
    VLServer		/* Server */
);

extern int vlRestoreSystemDefaults(
    VLServer		/* Server */
);

extern int vlRestoreFactoryDefaults(
    VLServer		/* Server */
);

/* 
 * Extension Support
 */

typedef enum {
    VL_EXTENSIONS
} VLenum;

const char *vlGetString(
    VLServer,		/* Server */
    VLDev dev,		/* in: device handle */
    VLenum name		/* in: resource to query */
);

/*
 * Fraction Utility Routines
 */

VLBoolean vlMatchFloat (
    double given,             /* in: the floating point value to compare */
    VLFractionRange *ranges,  /* in: the range list to compare with */
    int nranges,              /* in: the number of ranges in the list */
    VLFraction *lower,        /* out: the closest lower fraction */
    VLFraction *higher        /* out: the closest higher fraction */
);

VLBoolean vlMatchFraction (
    VLFraction *given,        /* in: the fraction to compare */
    VLFractionRange *ranges,  /* in: the range list to compare with */
    int nranges,              /* in: the number of ranges in the list */
    VLFraction *lower,        /* out: the closest lower fraction */
    VLFraction *higher        /* out: the closest higher fraction */
);

int vlFractionCount (
    VLFractionRange *ranges,
    int nranges
);

VLBoolean vlMatchFractionInList (
    VLFraction *fraction,     /* in: the fraction to find */
    VLFraction *list,         /* in: the list to search */
    int count,                /* in: length of list */
    VLFraction *lower,        /* out: nearest lower fraction */
    VLFraction *higher,       /* out: nearest higher fraction */
    int *index_return         /* out: index of lower */
);

VLFraction * vlFractionList(
    VLFractionRange *range,
    int nranges,
    int *length_return
);

void vlChooseClosestFraction(
    VLFraction *lower,
    VLFraction *higher,
    VLFraction *user
);



/*
 * The following are the error code definitions for the VL.
 * The error code will be stored in vlErrno on an error return.
 */

/*
 * Do not use vlErrno, as it is here only for backwards compatibility.
 * instead use the call vlGetErrno
 */
#define DDSTRSIZE 128
extern int vlErrno;
extern char vlddErrStr[DDSTRSIZE];

#define VLSuccess            0    /* everything's okay */
#define VLBadRequest         1    /* bad request code */
#define VLBadValue           2    /* int parameter out of range */
#define VLBadPath            3    /* parameter not a path */
#define VLBadNode            4    /* parameter not a node */
#define VLBadAtom            5    /* parameter not an atom */
#define VLBadDevice          6    /* parameter not a device */
#define VLBadControl         7    /* parameter not a control */
#define VLBadMatch           8    /* parameter mismatch */
#define VLBadAccess         10    /* depending on context */
#define VLBadAlloc          11    /* insufficient resources */
#define VLBadIDChoice       14    /* choice not in range or already used */
#define VLBadName           15    /* font or color name doesn't exist */
#define VLBadLength         16    /* Request length incorrect */
#define VLBadIoctl          17	  /* ioctl failed in the server */
#define VLBadImplementation 18    /* server is broken */
#define VLPathInUse	    19	  /* Path is in exclusive use */
#define VLBadServer	    20	  /* Server parameter is invalid */
#define VLBadBuffer	    21    /* Buffer invalid */
#define VLBadSize	    22	  /* Buffer size invalid */
#define VLNotEnoughResident 23	  /* we don't have enough resident memory */
#define VLBufferTooSmall    24	  /* the buffer allocated is too small */
#define VLValueOutOfRange   25	  /* the value is out of range (for controls)*/
#define VLSetupFailed       26    /* SetupPath of failed  */
#define VLBadWinAlloc       27    /* Insufficient hardware screen space */
#define VLInputsNotLocked   28    /* Video input sources cannot be locked */
#define VLNoRoute	    29	  /* No route could be found */
#define VLNotSupported	    30	  /* VlSetConnection/GetConnection */
#define VLBadPort	    31	  /* parameter not a valid port */
#define VLNotEnoughSpace    32	  /* need more space in GetConnection */
#define VLAPIConflict       33	  /* A mix of new and old API calls were made */
#define VLAgain		    34	  /* Resource temporarily unavailable */
#define VLDDError 		35	  /* used to send dd specific error messages */
#define VLWarning		36	  /* used to send warning messages to client */

#define VLMaxError	    37	  /* Must be larger than the largest error */
				  /* Subject to change in future releases */

extern int vlGetErrno(
    void
);

extern const char *vlStrError(
    int 		/* error value */
);

extern void vlPerror(
    const char *	/* string prefixed before error message */
);

typedef int (*VLErrorHandler) (
    VLServer,		/* Server Handle */
    VLEvent*		/* Error event */
);

extern VLErrorHandler vlSetErrorHandler (
    VLErrorHandler	/* Handler */
);

typedef int (*VLIOErrorHandler) (
    VLServer             /* Server Handle */
);

extern VLIOErrorHandler vlSetIOErrorHandler (
    VLIOErrorHandler    /* handler */
);


/*
 * Reserved resource and constant definitions:
 */

#define VL_ANY		0x10000000	/* also used by other VL routines
					 * to represent an unknown value. */
#define VL_IRISGLWINDOW	0x10000010

#define VLNone               0L /* universal null resource or null atom */

#define VLAllTemporary       0L /* special Resource ID passed to KillClient */

#define VLCurrentTime        0L /* special Time */

#ifndef TRUE
#define TRUE	(1)
#endif

#ifndef FALSE
#define FALSE	(0)
#endif

#ifdef __cplusplus
}
#endif
#endif /* _VL_H_ */
