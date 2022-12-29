/****************************************************************************
 *
 * Copyright 1995, Silicon Graphics, Inc.
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
 ***************************************************************************/

#ifndef __SYS_VIDEOTIMING_H__
#define __SYS_VIDEOTIMING_H__

/*
 * videotiming.h - useful statistics for various standard video formats
 */

/* ====== NTSC according to ANSI/SMPTE 170M-1994 */

/*
   References:
   "Video Demystified" by Jack, p.58
   "Video Engineering" by Inglis, p.85.
   ANSI/SMPTE 170M-1994

   line frequency is exactly (4.5E6 / 286.0)
   field frequency is exactly (line frequency / (525/2))
*/

#define NTSC_LINES_PER_SEC (15734.26573426573426573426)
/*      NTSC_LINES_PER_SEC == 4500000 / 286 */

#define NTSC_SECS_PER_LINE (.00006355555555555555)
/*      NTSC_SECS_PER_LINE == 286 / 4500000 */

#define NTSC_UST_PER_LINE (63556)
/*      NTSC_UST_PER_LINE == 1000000000 * 286 / 4500000 */

#define NTSC_LINES_PER_FIELD (262.5)
/*      NTSC_LINES_PER_FIELD == 525/2 */

#define NTSC_LINES_PER_FRAME 525

#define NTSC_FIELDS_PER_SEC (59.94005994005994005994)
/*      NTSC_FIELDS_PER_SEC == 4500000 / (286 * (525/2)) */

#define NTSC_SECS_PER_FIELD (.01668333333333333333)
/*      NTSC_SECS_PER_FIELD == (286 * (525/2)) / 4500000  */

#define NTSC_UST_PER_FIELD (16683333)
/*      NTSC_UST_PER_FIELD == 1000000000 * (286 * (525/2)) / 4500000 */

#define NTSC_FRAMES_PER_SEC (29.97002997002997002997)
/*      NTSC_FRAMES_PER_SEC == 4500000 / (286 * (525)) */

#define NTSC_SECS_PER_FRAME (.03336666666666666666)
/*      NTSC_SECS_PER_FRAME == (286 * (525)) / 4500000  */

#define NTSC_UST_PER_FRAME (33366667)
/*      NTSC_UST_PER_FRAME == 1000000000 * (286 * (525)) / 4500000  */

/*
   this is SGI's standard for the meaning of UST stamps
   on NTSC video fields.  A stamp on an NTSC video frame
   is the stamp of the first field of that frame.

   line numbering schemes are shown in ANSI/SMPTE 170M-1994.

   we define "odd"  as an instance of video field 1 or 3
   we define "even" as an instance of video field 2 or 4
*/

#define NTSC_ODD_LINE_NUMBER_OF_UST_STAMP 4
#define NTSC_EVEN_LINE_NUMBER_OF_UST_STAMP (266.5)


/* ====== (B, G, H, and I) PAL, according to CCIR Report 624-1978 */

/*
   References:
   "Video Demystified" by Jack, p.74
   "Video Engineering" by Inglis, p.88.
   CCIR Report 624-1978
   line frequency is exactly 50 * (625/2)
   field frequency is exactly 50
*/

#define PAL_LINES_PER_SEC (15625.0)
/*      PAL_LINES_PER_SEC == 50 * (625/2) */

#define PAL_SECS_PER_LINE (.000064)
/*      PAL_SECS_PER_LINE == 2/(50*625) */

#define PAL_UST_PER_LINE (64000)
/*      PAL_UST_PER_LINE == 1000000000 * 2/(50*625) */

#define PAL_LINES_PER_FIELD (312.5)
/*      PAL_LINES_PER_FIELD == 625/2 */

#define PAL_LINES_PER_FIELD_PAIR (625)

#define PAL_FIELDS_PER_SEC (50)
/*      PAL_FIELDS_PER_SEC == 50 */

#define PAL_SECS_PER_FIELD (.02)
/*      PAL_SECS_PER_FIELD == 1/50 */

#define PAL_UST_PER_FIELD (20000000)
/*      PAL_UST_PER_FIELD == 1000000000 * 1/50 */

#define PAL_FRAMES_PER_SEC (25)
/*      PAL_FRAMES_PER_SEC == 50/2 */

#define PAL_SECS_PER_FRAME (.04)
/*      PAL_SECS_PER_FRAME == 1/(50/2) */

#define PAL_UST_PER_FRAME (40000000)
/*      PAL_UST_PER_FRAME == 1000000000 * 1/(50/2) */

/*
   this is SGI's standard for the meaning of UST stamps
   on PAL video fields.  A stamp on an PAL video frame
   is the stamp of the first field of that frame.

   line numbering schemes are shown in CCIR Report 624-1978

   we define "odd"  as an instance of video field I or III
   we define "even" as an instance of video field II or IV
*/

#define PAL_ODD_LINE_NUMBER_OF_UST_STAMP (1)
#define PAL_EVEN_LINE_NUMBER_OF_UST_STAMP (313.5)

#endif	/* __SYS_VIDEOTIMING_H__ */
