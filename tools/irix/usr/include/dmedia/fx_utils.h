/***********************************************************************
**
** fx_utils.h
**	
**	General stuff for libfxplugutils.
**
** Copyright 1995, Silicon Graphics, Inc.
** ALL RIGHTS RESERVED
**
** UNPUBLISHED -- Rights reserved under the copyright laws of the United
** States.   Use of a copyright notice is precautionary only and does not
** imply publication or disclosure.
**
** U.S. GOVERNMENT RESTRICTED RIGHTS LEGEND:
** Use, duplication or disclosure by the Government is subject to restrictions
** as set forth in FAR 52.227.19(c)(2) or subparagraph (c)(1)(ii) of the Rights
** in Technical Data and Computer Software clause at DFARS 252.227-7013 and*or
** in similar or successor clauses in the FAR, or the DOD or NASA FAR
** Supplement.  Contractor*manufacturer is Silicon Graphics, Inc.,
** 2011 N. Shoreline Blvd. Mountain View, CA 94039-7311.
**
** THE CONTENT OF THIS WORK CONTAINS CONFIDENTIAL AND PROPRIETARY
** INFORMATION OF SILICON GRAPHICS, INC. ANY DUPLICATION, MODIFICATION,
** DISTRIBUTION, OR DISCLOSURE IN ANY FORM, IN WHOLE, OR IN PART, IS STRICTLY
** PROHIBITED WITHOUT THE PRIOR EXPRESS WRITTEN PERMISSION OF SILICON
** GRAPHICS, INC.
**
***********************************************************************/

#ifndef _FX_UTILS_H
#define _FX_UTILS_H

#include <dmedia/dm_params.h>	/* DMparams */
#include <dmedia/moviefile.h>	/* MVtimescale, MVtime */
#include "PremiereXAPI.h"	/* PRX_ScanlineBuffer */

/**********************************************************************
*
* Error codes for fx functions.
*
**********************************************************************/

#define FX_ERROR_INTERNAL		(DMEDIA_FX_ERROR_BASE + 1)
#define FX_ERROR_NO_BUFFERS		(DMEDIA_FX_ERROR_BASE + 2)
#define FX_ERROR_LIBMOVIE		(DMEDIA_FX_ERROR_BASE + 3)
#define FX_ERROR_BAD_USAGE_BITS		(DMEDIA_FX_ERROR_BASE + 3)
#define FX_ERROR_NO_MEMORY		(DMEDIA_FX_ERROR_BASE + 4)
#define FX_ERROR_CONV_KERNEL_SIZE	(DMEDIA_FX_ERROR_BASE + 5)
#define FX_ERROR_X_DISPLAY		(DMEDIA_FX_ERROR_BASE + 6)
#define FX_ERROR_NO_PBUFFER		(DMEDIA_FX_ERROR_BASE + 7)
#define FX_ERROR_NO_PIXMAP		(DMEDIA_FX_ERROR_BASE + 8)
#define FX_ERROR_NO_WINDOW		(DMEDIA_FX_ERROR_BASE + 9)
#define FX_ERROR_NO_DMBUFFER		(DMEDIA_FX_ERROR_BASE + 10)
#define FX_ERROR_GLX			(DMEDIA_FX_ERROR_BASE + 11)
#define FX_ERROR_SETUP_ORDER		(DMEDIA_FX_ERROR_BASE + 12)
#define FX_ERROR_BAD_FORMAT		(DMEDIA_FX_ERROR_BASE + 13)
#define FX_ERROR_BAD_PARAMETER		(DMEDIA_FX_ERROR_BASE + 14)
    
/**********************************************************************
*
* Macros for use with PremiereXAPI.h
*
**********************************************************************/

/********
*
* DM_FX_4_CHARS_TO_INT - Used for constructing plug-in names.
*
********/

#define DM_FX_4_CHARS_TO_INT(a,b,c,d) \
    ((((unsigned int) (a) & 0xff) << 24) | \
     (((unsigned int) (b) & 0xff) << 16) | \
     (((unsigned int) (c) & 0xff) <<  8) | \
     (((unsigned int) (d) & 0xff) <<  0))


#ifdef __cplusplus
extern "C" {
#endif
 
/* Load and merge X resources from the specified file
 *   Note- filename should be the name of the resource file only - do not
 *   give a full directory path - the directories to search for your
 *   specified file is locale-dependent and determined at run-time
 */
DMstatus dmFXMergeResources(
    const char* filename     /* X resouce file */
    );

#ifdef __cplusplus
}
#endif

#endif /* _FX_UTILS_H */
