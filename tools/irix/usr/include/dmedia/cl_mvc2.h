/*****************************************************************************
 *
 * SGI compression library 
 *
 * cl_mvc2.h : MVC2 parameters
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

#ifndef _INC_CL_MVC2_H
#define _INC_CL_MVC2_H

#ifdef __cplusplus
extern "C" {
#endif

/* MVC2 Compression Specific Parameters */
#define CL_MVC2_LUMA_THRESHOLD                  (CL_ParamID (1, 0))
#define CL_MVC2_CHROMA_THRESHOLD                (CL_ParamID (1, 1))
#define CL_MVC2_EDGE_THRESHOLD                  (CL_ParamID (1, 2)) 

/* MVC2 Decompression Specific Parameters */
#define CL_MVC2_BLENDING                        (CL_ParamID (1, 3))
#define CL_MVC2_BLENDING_OFF                    0
#define CL_MVC2_BLENDING_ON                     1

/*************************************************************************** 
*
* Backwards Compatibility
*
***************************************************************************/

#define CL_LUMA_THRESHOLD                CL_MVC2_LUMA_THRESHOLD
#define CL_CHROMA_THRESHOLD              CL_MVC2_CHROMA_THRESHOLD 
#define CL_EDGE_THRESHOLD                CL_MVC2_EDGE_THRESHOLD
#define CL_BLENDING                      CL_MVC2_BLENDING
#if     !defined(ON)  || ((ON)  != CL_MVC2_BLENDING_ON)
#define ON  CL_MVC2_BLENDING_ON
#endif
#if     !defined(OFF) || ((OFF) != CL_MVC2_BLENDING_OFF)
#define OFF CL_MVC2_BLENDING_OFF
#endif

#ifdef __cplusplus
}
#endif

#endif /* _INC_CL_MVC2_H */
