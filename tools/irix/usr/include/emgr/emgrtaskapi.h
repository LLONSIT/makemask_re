/* -                             EMGRTASKAPI.H                              -*/
/* ------------------------------------------------------------------------- */
/*                                                                           */
/* Copyright 1992-2002 Silicon Graphics, Inc.                                */
/* All Rights Reserved.                                                      */
/*                                                                           */
/* This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics, Inc.;    */
/* the contents of this file may not be disclosed to third parties, copied o */
/* duplicated in any form, in whole or in part, without the prior written    */
/* permission of Silicon Graphics, Inc.                                      */
/*                                                                           */
/* RESTRICTED RIGHTS LEGEND:                                                 */
/* Use,duplication or disclosure by the Government is subject to restrictions*/
/* as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data    */
/* and Computer Software clause at DFARS 252.227-7013, and/or in similar or  */
/* successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -   */
/* rights reserved under the Copyright Laws of the United States.            */
/*                                                                           */
/* ------------------------------------------------------------------------- */
/* emgrtaskapi.h have set of function prototypes for tasks. Tasks will use   */
/* this file. This file is for PUBLIC					     */
/* --------------------------------------------------------------------------*/

/* !!!!!!!!!!!!!!!!!!!!! Write more comments for functions return types*/

#ifndef EMGRTASKAPI_H
#define EMGRTASKAPI_H

#include <stdlib.h>

/* Event manager commands exit return codes */
/*internal error codes*/
#define EMGRCMD_SOCKETOPEN_FAILED		1	/* socket open failed*/
#define EMGRCMD_BIND_FAILED			2	/* bind failed*/
#define EMGRCMD_SENDTO_FAILED			3	/* Send to failed*/
#define EMGRCMD_RECV_FAILED			4	/* recvfrom failed*/
#define EMGRCMD_USAGE_ERR			5	/* usage err*/
#define	EMGRCMD_MEMORY_ERR			6	/*internal memory err*/

/* External erro codes*/
#define EMGRCMD_DSO_PATH_NOT_FOUND		7	/*dso path not fouand*/
#define EMGRCMD_DSO_NOT_LOADED			8	/* dso not loaded*/
#define EMGRCMD_DSO_SYMBOL_NOT_FOUND		9	/*dso symbol not found*/
#define	EMGRCMD_INFO_CMD_ERR			10	/*Info command error*/
#define EMGRCMD_CMD_CMD_FAILED			11	/* command func failed*/
#define	EMGRCMD_MSG_CMD_FAILED			12	/* Msg cmd failed*/
#define EMGRCMD_TASK_ALREADY_LOADED		13	/*task already loaded*/ 
#define EMGRCMD_TASK_ALREADY_STARTED		14	/*task already started*/ 
			/* Rcv/Snd buffer size for info socket (bytes) */
#define RCVINFOREQ_MAXSIZE 1024
#undef	RCVINFOREQ_MAXSIZE
#if	RCVINFOREQ_MAXSIZE < BUFSIZ
#define	RCVINFOREQ_MAXSIZE   BUFSIZ
#endif
#define TSKNAMELEN	256
#define	TSKARGSLEN	126
#define	TSKRETBUFLEN	126


/* Return Values of TSKEXIT function*/
#define UNLOAD_DSO		1
#define DO_NOT_UNLOAD_DSO	2
#define NEVER_UNLOAD_DSO	3

#ifdef __cplusplus
extern "C" {
#endif

typedef int   (*DTaskInit_t)(const char*);
typedef int   (*DTaskStart_t)(const char*);
typedef int   (*DTaskStop_t)(const char*);
typedef int   (*DTaskExit_t)(const char*);
typedef int   (*DTaskInfo_t)(const char*, char** pRes);
typedef int   (*DTaskMessage_t)(const char*);
typedef int   (*DTaskCommand_t)(const char*);

typedef struct DTaskCtlBlock {
      DTaskInit_t    initFunc;
      DTaskStart_t   startFunc;
      DTaskStop_t    stopFunc;
      DTaskExit_t    exitFunc;
      DTaskInfo_t    infoFunc;
      DTaskMessage_t msgFunc;
      DTaskCommand_t cmdFunc;
} DTaskCtlBlock_t;

   
#ifdef __cplusplus
}
#endif

#endif
