#ifndef __IFLSOFTIMAGEFILE_H__
#define __IFLSOFTIMAGEFILE_H__

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
 * Desc   : IFL SOFTIMAGE file format                                       *
 *                                                                          *
 * Author : Will McGovern ( willmc@asd.sgi.com )                            *
 *                                                                          *
 * Notes  :                                                                 *
 *--------------------------------------------------------------------------*/

/* This entry must be added to the users ifl_database file for this format

format SOFTIMAGE 
    match               ulong(0) == 0x5380f634 && ulong(88) == 0x50494354
    description         "SOFTIMAGE image"
    dso                 libiflSOFTIMAGE.so
    subsystem           "custom"
    suffixes            .pic
*/

/* Supported tags for getTag() and setTag() */

enum {
  iflSOFTIMAGEsubregion      = 1,     // set/get subregion and frame dimensions
  iflSOFTIMAGEpadSubregion   = 2,     // *** NOT IMPLEMENTED YET ***
  iflSOFTIMAGEresetSubregion = 3      // *** NOT IMPLEMENTED YET ***
};

#endif
