#ident "$Revision: 1.9 $"

#ifndef __PRIVATE_MOVIEFILE_H__
#define __PRIVATE_MOVIEFILE_H__

/*****************************************************************************
 *
 * SGI movie library
 *
 * moviefile.h
 *	Public include file for Silicon Graphics movie file format,
 *	for use with /usr/lib/libmovie.a
 *
 * Copyright 1992, Silicon Graphics, Inc.
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
 *
 ****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*
 * SGI movie file structures.
 */

typedef struct _MVheader {
    int movie_id;
    int version;
    int unused1;
    int unused2;
    int numTags;
    int unused3;		
} MVheader;

typedef struct _MVtrackheader {
    int         unused1;
    int         numTags;
    int         unused2;
} MVtrackheader;

typedef struct _MVdirectoryentry {
    size_t      location;
    size_t      size;
    int         numTags;
    int         unused;
} MVdirectoryentry;

typedef struct __MVtag {
    char        tag[16];
    int         datalength;
} MVtag;

#define MOVIE_ID		'MOVI' 
#define MOVIE_ID_OLD		0x00010400	
#define MOVIE_VERSION_1		1
#define MOVIE_VERSION_2		2
#define MOVIE_VERSION_3		3
#define MOVIE           	1   /* For MovieHeader.showType */ 
#define SLIDE_SHOW      	2   /* For MovieHeader.showType */
#define SOUND           	1   /* For MovieHeader.movieType */
#define SILENT          	2   /* For MovieHeader.movieType */
#define IMAGE_FORMAT_MVC1	1   /* CL_MVC1 compressed image data */
#define IMAGE_FORMAT_FIT	2   /* Uncompressed image data */
#define IMAGE_FORMAT_RLE	3   /* CL_RLE compressed image data */
#define IMAGE_FORMAT_MPEG	4   /* MPEG compressed movie. */
#define IMAGE_FORMAT_8RGB       5   /* Indigo 8 bit RGB image data. */
#define IMAGE_FORMAT_QTRPZA     6   /* Quicktime compressed movie. */
#define IMAGE_FORMAT_QTRLE      7   /* Quicktime compressed movie. */
#define IMAGE_FORMAT_QTRAW      8   /* Quicktime compressed movie. */
#define IMAGE_FORMAT_QTJPEG     9   /* Quicktime compressed movie. */
#define IMAGE_FORMAT_JPEG	4   /* CL_JPEG compressed image data. */

#define LOOP_NONE		0   /* For MovieHeader.loop_mode */
#define LOOP_CONTINUOUSLY	1   /* For MovieHeader.loop_mode */
#define LOOP_SWINGING		2   /* For MovieHeader.loop_mode */

#define FRAME_FLAG_ISKEY	1

extern DMstatus  mvSetFrameParams   ( MVid         track,
                                      MVframe      frameIndex,
                                      DMparams*    params,
                                      DMparams*    paramsSetOrNull );

extern DMparams* mvGetFrameParams   ( MVid         id,
                                      MVframe      frame );

#ifdef __cplusplus
}
#endif
#endif /* __PRIVATE_MOVIEFILE_H__ */
