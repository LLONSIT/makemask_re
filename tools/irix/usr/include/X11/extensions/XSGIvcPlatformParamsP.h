
#ifndef __XSGIVC_PLATFORM_PARAMS_P_H__
#define __XSGIVC_PLATFORM_PARAMS_P_H__

/*
 * XSGIvcPlatformParamsP.h
 *
 *      defines and data structures that are private to sgi
 *
 *
 * Copyright 1994, Silicon Graphics, Inc.
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
 * $Revision: 1.3 $
 */

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)

/* these platform params currently only work on an InfiniteReality, but are not necessarily InfiniteReality specific */

#define XSGIVC_PlatformParamBindChannelToXWid     -100
#define XSGIVC_PlatformParamQueryChannelRectInfo  -101
typedef struct {
        int     rect_x;
        int     rect_y;
        int     rect_dx;
        int     rect_dy;
        int     rect_w;
        int     rect_h;
        int     rect_dw;
        int     rect_dh;
        int     border_x;
        int     border_y;
        int     border_w;
        int     border_h;
        int     independent;
} XSGIvcPlatformParamQueryChannelRectInfo;

#define XSGIVC_PlatformParamSetFieldDominance     -102
/* dominance setting */
#define XSGIVC_PlatformParamSetFieldDominance_EvenDominance 0
#define XSGIVC_PlatformParamSetFieldDominance_OddDominance 1

#endif /* C || C++ */

#endif /* !__XSGIVC_PLATFORM_PARAMS_P_H__ */
