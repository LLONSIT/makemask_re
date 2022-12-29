////////////////////////////////////////////////////////////////////////////////
/////// Copyright 1992-1997, Silicon Graphics, Inc.  All Rights Reserved.///////
//                                                                            //
// This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics, Inc.;     //
// the contents of this file may not be disclosed to third parties, copied    //
// or duplicated in any form, in whole or in part, without the prior written  //
// permission of Silicon Graphics, Inc.                                       //
//                                                                            //
// RESTRICTED RIGHTS LEGEND:                                                  //
// Use,duplication or disclosure by the Government is subject to restrictions //
// as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data     //
// and Computer Software clause at DFARS 252.227-7013, and/or in similar or   //
// successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -    //
// rights reserved under the Copyright Laws of the United States.             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
#ifndef VKHELPAPI_H
#define VKHELPAPI_H

#include <X11/Xlib.h>

extern "C" {

extern int SGIHelpInit(Display *in_dsp, char *in_client, char *in_sep);
extern int SGIHelpMsg(char *in_key, char *in_book, char *user_data);
extern int SGIHelpIndexMsg(char *in_key, char *in_book);

extern int _VkSGIHelpInit(Display *in_dsp, char *in_client, char *in_sep);
extern int _VkSGIHelpMsg(char *in_key, char *in_book, char *user_data);
extern int _VkSGIHelpIndexMsg(char *in_key, char *in_book);

}

#endif
