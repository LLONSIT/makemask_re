/*
 * Copyright (C) 2000 SGI 
 */

#ifndef _IMPL_MON_H
#define _IMPL_MON_H

#ifndef _IMPL_H
#error "This file does not meant to be included on its own"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * time control internal API
 */
#define PM_TCTL_PROTO_VERSION	1	/* protocol version number */

/* internal commands */
#define PM_TCTL_ACK		16	/* used by pmTimeSendAck */
#define PM_TCTL_INITIALIZE	17	/* used by pmTimeConnect */

#define PM_TCTL_MASTER_PATH	"/usr/pcp/bin/pmtime"

/* time control client */
typedef struct {
    int			toClient;	/* server sends socket */
    int			fromClient;	/* server receive socket */
    int			wantAck;	/* nonzero => ACK expected */
    int			version;	/* protocol version used by the client */
    pmTime		data;		/* client state data */
} __pmTimeClient;


/* time control state */
typedef struct {
    int			mode;		/* mode bitmap */
    int			control;	/* control port (socket) */
    char		*port;		/* NULL if standalone */
    pmTime		data;		/* synchronized state */
    int			numclients;	/* number of clients */
    __pmTimeClient	*clients;	/* array of clients */
    int			numtz;		/* number of timezones */
    pmTimeZone		*tz;		/* array of time zones */
} __pmTimeState;

/* pdu structure for PM_TCTL_INITIALIZE */
typedef struct {
    int			version;	/* version number */
    pmTime		params;		/* user's parameters */
} __pmTimeInitPDU;

/*
 * Create control port on the given named pipe, then bind and listen.
 * This is for use by X11 widgets and the pmTimeMaster main program.
 */
extern int __pmTimeInit(const char *, pmTime *); /* port, initState */

/* close control port, close and free all clients, free internal state */
extern int __pmTimeClose(void);

/* get pointer to internal time control state (static in timecontrol.c) */
extern int __pmTimeGetState(__pmTimeState **);

/* accept a new client, return err */
extern int __pmTimeAcceptClient(int *, int *, pmTime *); /* toClient*, fromClient*, initparams */

/* register XTB data for the client */
extern void __pmTimeRegisterClient(int, pmTime *);

/* initialize a new time control client on given sockets|pipe */
extern int __pmTimeAddClient(int, int); /* toClient, fromClient */

/* find a client (keyed by it's send file descriptor) */
extern __pmTimeClient *__pmTimeFindClient(int); /* fd */

/* add a new time control timezone */
extern int __pmTimeAddTimezone(const char *, const char *); /* label, tz */

/* find a previously added timezone by it's label, return it's handle */
extern int __pmTimeGetTimezone(const char *);

/* delete and free a time control client (on given sndFd) */
extern int __pmTimeDelClient(int);

/* send a time control command to all clients, return err or 0 */
extern int __pmTimeBroadcast(int, pmTime *); /* cmd, data */

/*
 * return the number of clients with pending ACKS.
 * If timeout is non-NULL and there are acks pending,
 * block in select until any client is ready.
 */
extern int __pmTimeAcksPending(struct timeval *); /* timeout */
extern void __pmTimeSetHungClients(void);

/* low level time control PDU transmit */
extern int __pmTimeSendPDU(int, int, pmTime *); /* fd, cmd, state */

/* low level time control PDU receive, returns recv'ed command */
extern int __pmTimeRecvPDU(int, pmTime *); /* fd, state */

/* debug routines */
extern const char *__pmTimeCmdStr(int);
extern const char *__pmTimeStateStr(int);
extern const char *__pmTimeStr(const pmTime *);

/*
 * object style checks
 */

#define PM_STYLE_O32		0
#define PM_STYLE_N32		1
#define PM_STYLE_64		2
#define PM_STYLE_IA32		3
#define PM_STYLE_UNKNOWN	-1

/*
 * Check caller's object style matches the object style of the running kernel.
 * Return 0 if OK else PM_ERR_OBJSTYLE
 */
extern int __pmCheckObjectStyle(void);

/*
 * Get the object style of the caller and of the running kernel.
 * Returns 0 on success or negative errno
 */
extern int __pmGetObjectStyle(int *, int *); /* &user, &kernel */

/*
 * Get the name of specified object style, e.g. "mips_o32".
 * Return pointer to static buffer, or NULL if unknown
 */
extern const char *__pmNameObjectStyle(int); /* PM_STYLE_* */

/*
 * "fetchgroup" api
 * (currently not documented)
 */

/* add a metric to the fetch group lists, returns req cookie */
extern int __pmFetchGroupAdd(int /*contextMode*/, char * /*hostOrArchive*/,
    pmDesc * /*desc*/, int /*instance*/, double * /*current*/,
    double * /*previous*/, struct timeval * /*currentTime*/,
    struct timeval * /*previousTime*/, int * /*currentFetchErr*/,
    int * /*previousFetchErr*/);

/* reset the pointers to hold the results for a req cookie */
extern void __pmFetchGroupPointers(int /*reqnum*/, double * /*current*/,
    double * /*previous*/, struct timeval * /*currentTime*/,
    struct timeval * /*previousTime*/, int * /*currentFetchErr*/,
    int * /*previousFetchErr*/);

/* delete a req cookie */
extern int __pmFetchGroupDel(int /*reqNumber*/);

/* fetch all req cookies */
extern int __pmFetchGroupFetch(void);

/* set archive mode for all archives currently open */
extern void __pmFetchGroupArchiveMode(int /*mode*/, 
				      const struct timeval * /*when*/,
				      int /*interval*/);

/* get archive bounds for all archives currently open */
extern int __pmFetchGroupArchiveBounds(struct timeval * /*start*/,
    struct timeval * /*finish*/);

/* print fetch group stats */
extern void __pmFetchGroupStats(void);

#ifdef HAVE_DEV_IN_LIBPCP
/*
 * Must be called by authorised clients in order that communication
 * with either a licensed or an unlicensed pmcd can take place.
 */
extern void __pmSetAuthClient(void);

/*
 * nodelock license check
 */
#define GET_LICENSE_SILENT	0x00
#define GET_LICENSE_SHOW_EXP	0x01
#define GET_LICENSE_SHOW_NOLIC	0x02
#define GET_LICENSE_SHOW_ALL	0x7f
#define GET_LICENSE_DIE		0x80

#endif /* HAVE_DEV_IN_LIBPCP */

#ifdef __cplusplus
}
#endif

#endif /* _IMPL_MON_H */
