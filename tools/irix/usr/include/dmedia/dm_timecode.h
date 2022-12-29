/*
 *  dm_timecode.h -- Header file for libdmedia timecode manipulation
 *     routines and structure definitions. 
 * Also contains DMparam defintions for use by the movie library
 *
 * Copyright 1995 Silicon Graphics, Inc.
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

#ifndef _DM_TIMECODE_H_
#define _DM_TIMECODE_H_

#include <sys/dmcommon.h>
#include <dmedia/dmedia.h>      /* for DMstatus, DMboolean, etc */

#ifdef __cplusplus
extern "C" {
#endif

		/* NOTE : Moved the timecode structure to dmcommon.h */

/* common (fully specified) timecode types */
#define DM_TC_BAD          0
#define DM_TC_24_ND \
   DM_TC_NODROP | DM_TC_FORMAT_FILM | DM_TC_RATE_24
#define DM_TC_25_ND \
   DM_TC_NODROP | DM_TC_FORMAT_PAL | DM_TC_RATE_25
#define DM_TC_30_ND \
   DM_TC_NODROP | DM_TC_FORMAT_NTSC | DM_TC_RATE_30
#define DM_TC_60_ND \
   DM_TC_NODROP | DM_TC_FORMAT_HDTV | DM_TC_RATE_60

/* Note that 29.97 4-field drop is what is used in NTSC */
/* 29.97 8-field drop is used in M-PAL (Brazil) */
#define DM_TC_2997_4FIELD_DROP \
   DM_TC_DROPFRAME | DM_TC_FORMAT_NTSC | DM_TC_RATE_2997
#define DM_TC_2997_8FIELD_DROP \
   DM_TC_DROPFRAME | DM_TC_FORMAT_PAL | DM_TC_RATE_2997
#define DM_TC_5994_8FIELD_DROP \
   DM_TC_DROPFRAME | DM_TC_FORMAT_HDTV | DM_TC_RATE_5994


/* Function Prototypes */

extern DMstatus dmTCToString( char * string, const DMtimecode *smpteTimecode );

extern DMstatus dmTCFromString( DMtimecode * result, const char * string,
                                  int tc_type );

extern DMstatus dmTCFromSeconds( DMtimecode * result, const int tc_type,
                               const double seconds );

extern DMstatus dmTCToSeconds( const DMtimecode * a, double * seconds );

extern int  dmTCFramesPerDay( const int tc_type );

extern DMstatus dmTCAddTC(  DMtimecode * result, const DMtimecode *a,
                              const DMtimecode *b, int *overflow );

extern DMstatus dmTCAddFrames( DMtimecode * result, const DMtimecode * a, 
                                 int  b, int * overflowunderflow );

extern DMstatus dmTCFramesBetween( int  * result, const DMtimecode * a, 
                              const DMtimecode * b );

/* DMparams for timecodes */
#define DM_TIMECODE_FLAGS		"DM_TIMECODE_FLAGS"
#define DM_TIMECODE_FTIMESCALE		"DM_TIMECODE_FTIMESCALE"
#define DM_TIMECODE_FRAME_DURATION	"DM_TIMECODE_FRAME_DURATION"
#define DM_TIMECODE_NUM_FRAMES		"DM_TIMECODE_NUM_FRAMES"
#define DM_TIMECODE_SRC_REF		"DM_TIMECODE_SRC_REF"

#ifdef __cplusplus
}
#endif
#endif /* _DM_TIMECODE_H_ */
