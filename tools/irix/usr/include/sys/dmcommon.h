#ifndef _SYS_DMCOMMON_H_
#define _SYS_DMCOMMON_H_
/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1990, Silicon Graphics, Inc.               *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 **************************************************************************/
/*
 * dmcommon.h
 *
 * $Revision$
 *
 * Header information for the ringbuffers that may be required in the
 * kernel.
 */

#include <sys/types.h>
#include <sys/time.h>

/* stamp_t also defined in sys/time.h.  retain for a bit to ease transition */

/* stamp_t: SGI-specific type for USTs and MSCs */
/* there is no "ust_t": use stamp_t ; there is no "msc_t": check library */
#ifndef _STAMP_T
#define _STAMP_T
typedef signed long long stamp_t; /* used for USTs and often MSCs */
typedef struct USTMSCpair
{
  stamp_t ust; /* a UST value at which an MSC hit an input or output jack */
  stamp_t msc; /* the MSC which is being described */
} USTMSCpair;
#endif /* !_STAMP_T */

/*
 * following are general dmedia header structures and the tags that
 * should be associated with them.
 */

#define DM_RB_DMEDIA_INFO	0x100001
#define DM_RB_DMEDIA_TAG_NAME	"DMediaInfoStructure"

#define DM_RB_TYPE_IMAGE	1001	/* image data is in this buffer */
#define DM_RB_TYPE_AUDIO	1002	/* audio data is in this buffer */
#define DM_RB_TYPE_VIDEO	1003	/* both audio and video are here */

typedef struct {
   int hour;
   int minute;
   int second;
   int frame;
   int tc_type;                      /* FPS and drop type */
} DMtimecode;

/* tc_type definition */
   
#define DM_TC_DROP_MASK    0x00010000
#define DM_TC_FORMAT_MASK  0x0000FF00
#define DM_TC_RATE_MASK    0x000000FF

/* Formats */
#define DM_TC_FORMAT_NTSC  0x00000100
#define DM_TC_FORMAT_PAL   0x00000200
#define DM_TC_FORMAT_FILM  0x00000300
#define DM_TC_FORMAT_HDTV  0x00000400

/* Rates */
#define DM_TC_RATE_2997    0x00000001   /* NTSC, Brazilian PAL, dropframe  */
#define DM_TC_RATE_30      0x00000002   /* NTSC, Brazilian PAL, non-dropframe */
#define DM_TC_RATE_24      0x00000003   /* film                            */
#define DM_TC_RATE_25      0x00000004   /* PAL                             */
#define DM_TC_RATE_60      0x00000005   /* HDTV */
#define DM_TC_RATE_5994    0x00000006   /* HDTV */

/* Dropframe flag */
#define DM_TC_NODROP       0x00000000
#define DM_TC_DROPFRAME    0x00010000


typedef struct _DMLTCcode {
    DMtimecode      tc;     /* Timecode */
    unsigned int    dropFrame :1;   /* NTSC drop frame mode on */
    unsigned int    colorLock :1;   /* Count locked to color framing */
    char        userType;   /* Binary Group flags for user data */
    char        userData[4];    /* User Group bytes */
} DMLTCcode;

typedef struct {
    DMtimecode      tc;     /* Timecode */
    unsigned int    dropFrame :1;   /* NTSC drop frame mode on */
    unsigned int    colorLock :1;   /* Count locked to color framing */
    unsigned int    evenField :1;   /* True if came from an even field */
    char        userType;   /* Binary Group flags for user data */
    char        userData[4];    /* User Group bytes */
} DMVITCcode;

#if _MIPS_SIM == _ABI64

typedef struct DMediaInfo
{
    int                  type;      /* should be enum? */
    struct irix5_timeval time;      /* the system time */
    struct irix5_timeval duration;  /* the duration of this buffer */
    int                  sequence;  /* field sequence number */
    stamp_t              ustime;    /* unadjusted system time in nanoseconds */
    DMVITCcode           vitc;
    unsigned int         sdti;
} DMediaInfo;
 
#else

typedef struct DMediaInfo
{
    int 	   type;        /* should be enum? */
    struct timeval time;	/* the system time */
    struct timeval duration;	/* the duration of this buffer */
    int 	   sequence;	/* field sequence number */
    stamp_t 	   ustime;	/* unadjusted system time in nanoseconds */
    DMVITCcode	   vitc;
    unsigned int   sdti;

} DMediaInfo;
#endif
#define DM_RB_IMAGE_INFO	0x100002
#define DM_RB_IMAGE_TAG_NAME	"DMImageInfoStructure"

typedef struct DMImageInfo
{
    int offset;			/* offset to start of data */
    int width, height;		/* the size of the image */
    int packing;		/* the pixel packing format */
    int compression;		/* how the data is compressed */
} DMImageInfo;

#define DM_RB_AUDIO_INFO	0x100003
#define DM_RB_AUDIO_TAG_NAME	"DMAudioInfoStructure"

typedef struct DMAudioInfo
{
    int offset;			/* offset to start of data */
    int width;			/* the sample width */
    int format;			/* the sample format */
    double rate;		/* the sampling rate */
    int compression;		/* the compression format */
} DMAudioInfo;

#define DMImageAudio DMAudioInfo	/* oops, a typo got into vl_1.0, */
					/* keep reference for compatibility */

/*
 * Type definitions for DMBufferInlineInfo structure.
 * The type specifies the structure used in inlineinfo union field
 * as well as other structures to be added in the future.
 */
#define	DM_INLINEINFO_DMRB	0x0	/* 0 for backwards compatability */
#define	DM_INLINEINFO_VIDEO	0x1
#define	DM_INLINEINFO_DMNET	0x2
#define	DM_INLINEINFO_UNDEFINED	0x8

/*
 * Defined in dms.h
 */
#ifndef DMBUF_EVENT_SYSTEM_INLINE
#define DMBUF_EVENT_SYSTEM_INLINE	128
#endif

/*
 * Per-image information passed to application by video drivers.
 * Used as inline info structure for dmRB VL calls.
 * Defined as vidinfo_t in dmcommon.h for backwards compatability.
 */
typedef struct DMBufferDMRBInfo_s {
    DMediaInfo  dmedia_info;
    DMImageInfo	image_info;
} DMBufferDMRBInfo;

/*
 * Per-image information passed between applications and video drivers.
 * Used as inline info structure for dmbuffer VL calls.
 *
 * As the DMBufferVideoInfo structure is copied between driver and
 * application, its size should remain fixed.  For the same reason,
 * the type field should remain at a known and fixed offset.
 * The size of DMBufferVideoInfo is fixed by DMBUF_VIDINFO_SIZE.
 * If fields are added to the structure, DMBUF_VIDINFO_PAD must be
 * updated to reflect actual amount used.
 */
#define DMBUF_VIDINFO_SIZE	96  /* size in bytes of DMBufferVideoInfo */

#define DMBUF_VIDINFO_PAD  ((DMBUF_VIDINFO_SIZE) - 2*sizeof(DMVITCcode) -\
	2*sizeof(unsigned int))

#define	DMBUF_VIDINFO_VALID_VITC1 0x1
#define	DMBUF_VIDINFO_VALID_VITC2 0x2
#define DMBUF_VIDINFO_VALID_SDTI  0x4


typedef struct DMBufferVideoInfo_s {
    DMVITCcode vitc[2];
    unsigned int validinfo;
    unsigned int sdti;
    char pad[DMBUF_VIDINFO_PAD];
} DMBufferVideoInfo;

typedef struct DMBufferDMnetInfo_s {
    unsigned int serial;
    size_t dataSize;
    struct timeval tv;
    unsigned int nanos;
} DMBufferDMnetInfo;

/*
 * General info structure supplied by a kernel driver or
 * user application passed inline with dmBuffer.
 */
typedef struct DMBufferInlineInfo {
    union inlineinfo_u {
	DMBufferDMRBInfo udmRBInfo;	/* first for backward compatability */
	DMBufferVideoInfo uvideoInfo;
    } inlineinfo_u;

    unsigned int type;	/* must be at known offset in structure */

    DMBufferDMnetInfo dmNetInfo;

} DMBufferInlineInfo;

#define	dmRBInfo inlineinfo_u.udmRBInfo
#define	videoInfo inlineinfo_u.uvideoInfo

#ifndef __INC_DM_RICE_H__
#define __INC_DM_RICE_H__


/*
 * RICE compression definitions
 */
#define DM_RICE_MAGIC ('R'<<8|'I')
#define DM_RICE_VERSION_DIVO_1		1 /* first RICE version used by DIVO */

typedef struct {
  uint16_t rmagic;
  uint16_t rversion;
  uint16_t xsize;  
  uint16_t ysize;
  uint16_t precision;		/* component width */
  uint16_t sampling;		/* component sampling */
  uint16_t colorspace;
  uint16_t blocksize;
  uint32_t size;		/* compressed size of field in bytes */
  uint16_t padded;		/* was extra word added for 64 bit alignment */
  uint16_t reserved[5];
} DMRiceHeader;

/* RICE component precision */
#define DM_RICE_PRECISION_8		0
#define DM_RICE_PRECISION_10		1
#define DM_RICE_PRECISION_12		2
#define DM_RICE_PRECISION_13		3

/* RICE component sampling */
#define DM_RICE_SAMPLING_422		0
#define DM_RICE_SAMPLING_4224		1
#define DM_RICE_SAMPLING_444		2
#define DM_RICE_SAMPLING_4444		3

/* RICE colorspace of data */
#define DM_RICE_COLORSPACE_RGB		1
#define DM_RICE_COLORSPACE_CCIR601	2
#define DM_RICE_COLORSPACE_RP175	3
#define DM_RICE_COLORSPACE_YUV		4 

/* RICE blocksize */
#define DM_RICE_BLOCKSIZE_15		0
#define DM_RICE_BLOCKSIZE_16		1

#endif /* __INC_DM_RICE_H__ */
#endif /* _SYS_DMCOMMON_H */
