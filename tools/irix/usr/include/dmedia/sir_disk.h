/*
 * sir_disk.h - Contains disk header structure for reading/writing
 *              raw video files.  Used by sir_vidtodisk, sir_disktovid,
 *              and orion.
 *
 * Copyright 1994, Silicon Graphics, Inc.
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

#ident "$Revision: 1.2 $"

#ifndef __SIR_DISK_H__
#define __SIR_DISK_H__

#define	SUCCESS	0
#define	FAILURE	1

#define SIR_DISK_VERSION      4
#define SIR_DISK_MAGIC        (('V'<<24)|('I'<<16)|('D'<<8)|'1')

/*
 * Disk Header Structure
 */
struct disk_hdr {
    int magic;
    int version;

    /* video section */

    int video_width;	       /* image width in pixels; typically 720 */
    int video_height;	       /* image height in pixels; typically 243 */
    int video_packing;	       /* VL packing type; e.g. VL_PACKING_RGBA_8 */
    int video_format;	       /* VL format type; e.g. VL_FORMAT_RGB */
    int video_timing;	       /* VL timing; e.g. VL_TIMING_525_CCIR601 */
    int video_capture_type;    /* VL capture; e.g. VL_CAPTURE_NONINTERLEAVED */
    int video_field_dominance; /* field 1 or field 2 dominant (0 if frames) */
    int video_origin;	       /* this allows us to determine how to draw to
				* the graphics screen */

    int block_size;	       /* size of disk block */
    int blocks_per_image;      /* disk blocks per field/frame */
    int video_start_block;     /* where the real video data starts */
    int video_n_blocks;        /* total number of video data blocks */

    /* audio section */

    int audio_sample_rate;     /* AL sample rate; e.g. AL_RATE_48000 */
    int audio_sample_format;   /* AL numeric format; e.g. AL_SAMPFMT_FLOAT */
    int audio_sample_resolution; /* AL sample resolution; e.g. AL_SAMPLE_16 */
    int audio_n_channels;      /* AL number of channels; e.g. AL_STEREO */

    int audio_start_block;
    int audio_n_blocks;

    /* misc. other info */

    /* the block size is now a configurable parameter, so we can't pad */
    /* desc out to the end of a block here.  This can be done externally */
    /* anyway */
    char desc[64];
};

#endif /* __SIR_DISK_H__ */

