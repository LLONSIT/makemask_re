/* $Xorg: dpms.h,v 1.3 2000/08/18 04:05:45 coskrey Exp $ */
/*****************************************************************

Copyright (c) 1996 Digital Equipment Corporation, Maynard, Massachusetts.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software.

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
DIGITAL EQUIPMENT CORPORATION BE LIABLE FOR ANY CLAIM, DAMAGES, INCLUDING, 
BUT NOT LIMITED TO CONSEQUENTIAL OR INCIDENTAL DAMAGES, OR OTHER LIABILITY, 
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR 
IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of Digital Equipment Corporation 
shall not be used in advertising or otherwise to promote the sale, use or other
dealings in this Software without prior written authorization from Digital 
Equipment Corporation.

******************************************************************/

/*
 * HISTORY
 */
/*
 * @(#)$RCSfile: dpms.h,v $ $Revision: 1.2 $ (DEC) $Date: 2002/01/18 10:57:20 $
 */


#define DPMSModeOn	0
#define DPMSModeStandby	1
#define DPMSModeSuspend	2
#define DPMSModeOff	3

#ifndef DPMS_SERVER
#include <X11/Xlib.h>
#include <X11/Xmd.h>

extern Bool DPMSQueryExtension(Display *, int *, int *);
#pragma optional DPMSQueryExtension
extern Status DPMSGetVersion(Display *, int *, int *);
#pragma optional DPMSGetVersion
extern Bool DPMSCapable(Display *);
#pragma optional DPMSCapable
extern Status DPMSSetTimeouts(Display *, CARD16, CARD16, CARD16);
#pragma optional DPMSSetTimeouts
extern Bool DPMSGetTimeouts(Display *, CARD16 *, CARD16 *, CARD16 *);
#pragma optional DPMSGetTimeouts
extern Status DPMSEnable(Display *);
#pragma optional DPMSEnable
extern Status DPMSDisable(Display *);
#pragma optional DPMSDisable
extern Status DPMSForceLevel(Display *, CARD16);
#pragma optional DPMSForceLevel
extern Status DPMSInfo(Display *, CARD16 *, BOOL *);
#pragma optional DPMSInfo
#endif



