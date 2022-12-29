#ifndef __IFLYUVFILE_H__
#define __IFLYUVFILE_H__

/****************************************************************************
 *                                                                          *
 *                Copyright (C) 1995, Silicon Graphics, Inc.                *
 *                           All Rights Reserved.                           *
 *                                                                          *
 *  UNPUBLISHED -- Rights reserved under the copyright laws of the United   *
 *  States.  Use of a copyright notice is precautionary only and does not   *
 *  imply publication or disclosure.                                        *
 *                                                                          *
 *  THIS  SOFTWARE  CONTAINS  CONFIDENTIAL AND PROPRIETARY INFORMATION OF   *
 *  SILICON GRAPHICS, INC.  ANY DUPLICATION, MODIFICATION,  DISTRIBUTION,   *
 *  OR  DISCLOSURE  IS  STRICTLY  PROHIBITED  WITHOUT  THE  PRIOR EXPRESS   *
 *  WRITTEN PERMISSION OF SILICON GRAPHICS, INC.                            *
 *                                                                          *
 *   U.S. GOVERNMENT RESTRICTED RIGHTS LEGEND                               *
 *   Use, duplication or disclosure by the Government is                    *
 *   subject to restrictions as set forth in FAR 52.227.19(c)(2) or         *
 *   subparagraph (c)(1)(ii) of the Rights in Technical Data and Computer   *
 *   Software clause at DFARS 252.227-7013 and/or in similar or successor   *
 *   clauses in the FAR, or the DOD or NASA FAR Supplement.                 *
 *   Unpublished-- rights reserved under the copyright laws of the          *
 *   United States. Contractor/manufacturer is Silicon Graphics, Inc.,      *
 *   2011 N. Shoreline Blvd., Mountain View, CA 94039-7311.                 *
 *                                                                          *
 ****************************************************************************/

/*--------------------------------------------------------------------------*
 * Desc   : IFL 8-bit YUV ( CCIR-601 ) file format ( Sirius, Abekas etc. )  *
 *                                                                          *
 * Author : Will McGovern ( willmc@asd.sgi.com )                            *
 *                                                                          *
 * Notes  : Supports 8-bit CCIR-601 NSTC/PAL YUV format in fields/frames.   *
 *          The CCIR-601 active video sizes supported are :                 *
 *                                                                          *
 *              NTSC = 720 pixels x 486 lines ( frame format )              *
 *                   = 720 pixels x 243 lines ( field format )              *
 *                                                                          *
 *              PAL  = 720 pixels x 576 lines ( frame format )              *
 *                   = 720 pixels x 288 lines ( field format )              *
 *                                                                          *
 *          The IFL tags specific to this format are as follows :           *
 *                                                                          *
 *          getTag( iflYUVstandard, int* val )                              *
 *          setTag( iflYUVstandard, int val )                               *
 *                                                                          *
 *              val may be either YUV_STANDARD_NTSC or YUV_STANDARD_PAL.    *
 *              This value determines the allowable size of the image.      *
 *              See above for the PAL and NTSC sizes.                       *
 *                                                                          *
 *          getTag( iflYUVformat, int* val )                                *
 *          setTag( iflYUVformat, int val )                                 *
 *                                                                          *
 *              Returns either YUV_FORMAT_FIELD or YUV_FORMAT_FRAME.        *
 *              This value determines whether the image size is a full      *
 *              frame ( 2 interleaved fields ) or single field.             *
 *              See above for the PAL and NTSC field and frame sizes.       *
 *                                                                          *
 *          Format specified filename arguments :                           *
 *                                                                          *
 *              "standard" = "PAL" or "NTSC"      ( see above )             *
 *              "format"   = "FIELD" or "FRAME"   ( see above )             *
 *                                                                          *
 *              eg.  filename.yuv#yuv%standard=PAL%format=FRAME             *
 *                                                                          *
 *--------------------------------------------------------------------------*/

/* This entry must be added to the users ifl_database file for this format

format YUV 
    description         "YUV image"
    dso                 libiflYUV.so
    subsystem           "custom"
    suffixes            .yuv
*/

/* Supported tags for getTag() and setTag() */

enum {
  iflYUVstandard = 1,     // Encoding standard ( PAL or NTSC )
  iflYUVformat   = 2      // Format of data ( FIELD or FRAME )
};

/* Supported values for iflYUVstandard tag */

enum {
  YUV_STANDARD_NTSC = 1,  // CCIR-601 NTSC ( 720x486 or 720x243 )
  YUV_STANDARD_PAL  = 2   // CCIR-601 PAL  ( 720x576 or 720x288 )
};

/* Supported values for iflYUVformat tag */

enum {
  YUV_FORMAT_FIELD = 1,   // Fields ( NTSC=243 lines, PAL=288 lines )
  YUV_FORMAT_FRAME = 2    // Frames ( NTSC=486 lines, PAL=576 lines )
};

#endif
