/************************************************************

Copyright (c) 1989  X Consortium

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
X CONSORTIUM BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of the X Consortium shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from the X Consortium.

********************************************************/

/* $XConsortium: sgicap.h,v 1.17 94/04/17 20:11:23 rws Exp $ */

#ifndef _SGICAP_H_
#define _SGICAP_H_

#include <X11/Xfuncproto.h>

#define X_SGICapQueryVersion		0
#define X_SGICapRegisterInterest	1
#define X_SGICapStart			2
#define X_SGICapQueryAndReset		3
#define X_SGICapStop			4
#define X_SGICapWithdrawInterest	5
#define X_SGICapQueryCopyAndReset	6

#define SGICapNumberEvents		0
#define SGICapNumberErrors		0

typedef XID SGICapInterestType;

#ifndef _SGICAP_SERVER_

_XFUNCPROTOBEGIN

extern Bool SGICapQueryExtension (
#if NeedFunctionPrototypes
    Display*	/* display */,
    int*	/* event_base */,
    int*	/* error_base */
#endif
);

extern Status SGICapQueryVersion (
#if NeedFunctionPrototypes
    Display*	/* display */,
    int*	/* major_version */,
    int*	/* minor_version */
#endif
);

extern SGICapInterestType SGICapRegisterInterest (
#if NeedFunctionPrototypes
    Display*	/* display */,
    Drawable	/* dest */,
    int		/* x */,
    int		/* y */,
    unsigned int/* width */,
    unsigned int/* height */
#endif
);

extern void SGICapStart (
#if NeedFunctionPrototypes
    Display*	/* display */,
    SGICapInterestType	/* SGICapInterest */
#endif
);

extern XRectangle* SGICapQueryAndReset (
#if NeedFunctionPrototypes
    Display*	/* display */,
    SGICapInterestType	/* SGICapInterest */,
    Time*	/* time_return */,
    int*	/* count_return */,
    int*	/* ordering_return */
#endif
);

extern void SGICapStop (
#if NeedFunctionPrototypes
    Display*	/* display */,
    SGICapInterestType	/* SGICapInterest */
#endif
);

extern void SGICapWithdrawInterest (
#if NeedFunctionPrototypes
    Display*	/* display */,
    SGICapInterestType	/* SGICapInterest */
#endif
);

extern XRectangle* SGICapQueryCopyAndReset (
#if NeedFunctionPrototypes
    Display*	/* display */,
    SGICapInterestType	/* SGICapInterest */,
    Time*	/* time_return */,
    int*	/* count_return */,
    int*	/* ordering_return */,
    ShmReadDisplayBuf* /* shmbuf */
#endif
);

_XFUNCPROTOEND

#endif /* _SGICAP_SERVER_ */

#endif /* _SGICAP_H_ */
