/**************************************************************************
 *                                                                        *
 *               Copyright (C) 2003 Silicon Graphics, Inc.                *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 **************************************************************************/

/*
 * Externs for sock_* wrapper routines.
 */

extern const char *sock_inet_ntop(struct sockaddr *, char *, socklen_t);
extern int sock_getport(struct sockaddr *, in_port_t *);
extern int sock_getlen(struct sockaddr *, socklen_t *);
extern int sock_setlen(struct sockaddr *);
extern int sock_setport(struct sockaddr *, in_port_t);
extern struct hostent *sock_getverfhostent_r(struct sockaddr *, int);

#if !defined(_SGI_COMPILING_LIBC)
#pragma optional sock_inet_ntop
#pragma optional sock_getport
#pragma optional sock_getlen
#pragma optional sock_setlen
#pragma optional sock_setport
#pragma optional sock_getverfhostent_r
#endif
