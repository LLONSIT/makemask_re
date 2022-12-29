/*****************************************************************************
 *
 * SGI compression library 
 *
 * cl_mvc3.h : MVC3 parameters
 *
 * Copyright 1992, 1993 & 1994, Silicon Graphics, Inc.
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

#ifndef _INC_CL_MVC3_H
#define _INC_CL_MVC3_H

#ifdef __cplusplus
extern "C" {
#endif

#define CL_MVC3_QUALITY_LEVEL                    (CL_ParamID(1, 0))
  
/*************************************************************************** 
*
* Backwards Compatibility
*
***************************************************************************/

#define CL_QUALITY_LEVEL                 CL_MVC3_QUALITY_LEVEL
#define CL_RTR_QUALITY_LEVEL             CL_MVC3_QUALITY_LEVEL

#ifdef __cplusplus
}
#endif

#endif /* _INC_CL_MVC3_H */
