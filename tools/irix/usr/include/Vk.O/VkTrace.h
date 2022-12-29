/*
 * ==========================================================================
 * Copyright 1992, 1993, Silicon Graphics, Inc.
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics, Inc.;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior written
 * permission of Silicon Graphics, Inc.
 *
 * RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to restrictions 
 * as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data
 * and Computer Software clause at DFARS 252.227-7013, and/or in similar or 
 * successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished - 
 * rights reserved under the Copyright Laws of the United States.
 *
 * ==========================================================================
 * Module   : VkTrace.h -- prototypes for tracing utility functions
 *
 */
#ifndef _VKTRACE_H
#define _VKTRACE_H

#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <Vk/VkMsg.h>


/* External globals controlling the tracing */

extern	FILE	*theVkTraceFile;
extern	int	vkTraceEnable;
extern	int	vkTraceDetailEnable;
extern	int	vkTraceMessageEnable;
extern	int	vkTraceMessageArgsEnable;

extern	char	vkTraceBuf[1024];

#ifdef __cplusplus
extern "C" { 
#endif

char	*VkCvtime (time_t *ttime);
char	*VkCvDeltaTime (struct timeval tempus);

/* Enable tracing, open log file */
void	VkTraceOpen(char *_name);

/* Trace an event */
void	VkTrace(char *event);
void	VkTrace2(char *event, char *param);
void	VkTracev(char *event, char *param, ...);

/* Add detail to an event */
void	VkTraceDetail(char *event);
void	VkTraceDetail2(char *event, char *param);
void	VkTraceDetailv(char *event, char *param, ...);

/* Mark an event in the trace */
void	VkTraceMark(char *event);
void	VkTraceMark2(char *event, char *param);
void	VkTraceMarkv(char *event, char *param, ...);

/* Trace a Message, with header and args */
void	VkTraceMessage(char *event, VkMsgMessage);

/* Trace message args */
void	VkTraceMsgArgs(int, VkMsgArg *);

#ifdef __cplusplus
}
#endif

#endif
