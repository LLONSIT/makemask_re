/*****************************************************************************
 *
 * SGI compression library 
 *
 * cl_jpeg.h : JPEG parameters
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

#ifndef _INC_CL_JPEG_H
#define _INC_CL_JPEG_H

#ifdef __cplusplus
extern "C" {
#endif

#define CL_JPEG_QUALITY_FACTOR              	(CL_ParamID(1, 0))
#define CL_JPEG_STREAM_HEADERS                 	(CL_ParamID(1, 1))
#define CL_JPEG_QUANTIZATION_TABLES            	(CL_ParamID(1, 2))
#define CL_JPEG_NUM_PARAMS                  	11 

/*************************************************************************** 
*
* Backwards Compatibility
*
***************************************************************************/

#define CL_QUALITY_FACTOR                CL_JPEG_QUALITY_FACTOR 
#define CL_STREAM_HEADERS                CL_JPEG_STREAM_HEADERS
#define CL_NUMBER_OF_QUANTIZATION_TABLES CL_JPEG_NUMBER_OF_QUANTIZATION_TABLES
#define CL_QUANTIZATION_TABLES           CL_JPEG_QUANTIZATION_TABLES  
#define CL_CURRENT_QUANTIZATION_TABLE    CL_JPEG_CURRENT_QUANTIZATION_TABLE

#ifdef __cplusplus
}
#endif

#endif /* _INC_CL_JPEG_H */
