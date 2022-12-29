#ifndef __INC_DM_GENERAL_H__
#define __INC_DM_GENERAL_H__  

/*****************************************************************************
*
*  Copyright 1993, Silicon Graphics, Inc.
*  All Rights Reserved.
*
*  This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics, Inc.;
*  the contents of this file may not be disclosed to third parties, copied or
*  duplicated in any form, in whole or in part, without the prior written
*  permission of Silicon Graphics, Inc.
*
*  RESTRICTED RIGHTS LEGEND:
*  Use, duplication or disclosure by the Government is subject to restrictions
*  as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data
*  and Computer Software clause at DFARS 252.227-7013, and/or in similar or
*  successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -
*  rights reserved under the Copyright Laws of the United States.
* 
*****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

/**********************************************************************
*
* Data Types
*
**********************************************************************/

/********
*
* DMboolean
*
********/

typedef int DMboolean;

#define DM_FALSE  0
#define DM_TRUE   1

/********
*
* DMfraction
*
********/

typedef struct __DMfraction {
    int numerator;
    int denominator;
} DMfraction;

/**********************************************************************
*
* Return Codes
*
**********************************************************************/

typedef enum __DMstatus
{
    DM_SUCCESS		= 0,
    DM_FAILURE		= -1
} DMstatus;

/**********************************************************************
*
* General purpose functions
*
**********************************************************************/

struct timeval;
int dmGetCurrentTime(struct timeval *);
int dmGetUST(unsigned long long *);
int dmGetUSTCurrentTimePair(unsigned long long *nanostamp, struct timeval *tv);

/**********************************************************************
*
* Error message access functions
*
**********************************************************************/

/* The maximum length of the error detail string */

#define DM_MAX_ERROR_DETAIL 1024

/* error retrieval routine;  return value is error message, errorNum is
   set to the error token value (if pointer non-null), and errorDetail
   will be filled with the error detail string.  It must be a pointer to
   a char array of size DM_MAX_ERROR_DETAIL allocated in the caller's
   memory space.  It may also be NULL if detail is not desired.
*/

/* this allows PID-specific error retrieval */

const char *dmGetErrorForPID(pid_t pid, int *errorNum, char *errorDetail);

/* this returns the error for the current PID */

const char *dmGetError(int *errorNum, char *errorDetail);

/**********************************************************************
*
* Base values for subsystem errors -- determines error token ranges
*
**********************************************************************/

#define AF_ERR_BASE             3000  /*  5000- 5999: see audiofile.h */
#define DM_BUFFER_EBASE         4000  /*  4000- 4999 */
#define DM_IC_EBASE             6000  /*  6000- 6999 */
#define DMAC_ERROR_BASE         5000  /*  5000- 5999 */
#define DMEDIA_ERROR_BASE       10000 /* 10000-10999 */
#define DMEDIA_FX_ERROR_BASE    11000 /* 11000-11999: see fx_buffer.h */
#define DMEDIA_PM_ERROR_BASE    12000 /* 12000-12999: see fx_plugin_mgr.h */

/**********************************************************************
*
* Global dmedia error tokens
*
**********************************************************************/

#define DM_DL_ERROR (DMEDIA_ERROR_BASE+1) /* dlopen(), dlsym(), etc. error */

/**********************************************************************
*
* Common params
*
**********************************************************************/

#define DM_BITRATE "DM_BITRATE"

#ifdef __cplusplus 
}
#endif

#endif /* ! __INC_DM_GENERAL_H__  */

