/*
 * Copyright (C) 1995-2000 Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED.
 *
 * $Id: pmapi_mon.h,v 1.3 2003/11/10 04:22:17 kenmcd.longdrop.melbourne.sgi.com Exp $
 */

#ifndef _PMAPI_MON_H
#define _PMAPI_MON_H

#ifndef _PMAPI_H
#error "This file does not meant to be included on its own"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* time control client commands, returned by pmTimeRecv() */
#define PM_TCTL_SET		0	/* goto new position, set delta */
#define PM_TCTL_STEP		1	/* update (i.e. fetch), ACK required */
#define PM_TCTL_SKIP		2	/* step (but don't fetch, live only) */
#define PM_TCTL_VCRMODE		3	/* change vcr modes */
#define PM_TCTL_TZ		4	/* use a new timezone (tzlabel and tz)*/
#define PM_TCTL_SHOWDIALOG	5	/* show/hide time controls dialog */
#define PM_TCTL_BOUNDS		6	/* use new archive bounds */

/* time control vcr mode indicators */
#define PM_TCTL_VCRMODE_STOP	0	/* expect long pause */
#define PM_TCTL_VCRMODE_PLAY	1	/* expect slow seq of PM_TCTL_STEP */
#define PM_TCTL_VCRMODE_FAST	2	/* expect rapid seq of PM_TCTL_STEP */
#define PM_TCTL_VCRMODE_DRAG	3	/* expect rapid seq of PM_TCTL_SET */

/* time control connection modes (bitmap) */
#define PM_TCTL_MODE_STANDALONE	1	/* stand-alone mode, single client */
#define PM_TCTL_MODE_MASTER	2	/* use an existing master controller */
#define PM_TCTL_MODE_NEWMASTER	4	/* create new master controller */

#define PM_TCTL_MODE_HOST	8	/* live mode (stop/step available only) */
#define PM_TCTL_MODE_ARCHIVE	16	/* archive mode (full VCR controls) */

/* time control state data */
typedef struct {
    int			showdialog;	/* non-zero => time control dialog is visible */
    struct timeval	position;	/* current time / archive position */
    int			delta;		/* update interval +-milliseconds */
    char		tzlabel[PM_TZ_MAXLEN];	
                                        /* name of current time zone */
    char		tz[PM_TZ_MAXLEN];		
					/* current time zone */
    struct timeval	start;		/* controller's current starting time */
    struct timeval	finish;		/* controller's current finish time */
    int			vcrmode;	/* PM_TCTL_VCRMODE_STOP .. PM_TCTL_VCRMODE_DRAG */
} pmTime;

/*
 * Connect to time controller in given mode, returns read fd (or err < 0).
 * If standalone or new master then use given initial state.
 */
extern int pmTimeConnect(int, const char *, pmTime *); /* mode, port, initState */

/* disconnect from time control master or standalone, free internal state. */
extern int pmTimeDisconnect(void);

/* return port name (in static buffer), or NULL if standalone */
extern const char *pmTimeGetPort(void);

/* receive a time control command (may block), returns command (or err < 0) */
extern int pmTimeRecv(pmTime *);	/* commandBuffer */

/* send ack that PM_TCTL_STEP has been processed */
extern int pmTimeSendAck(const struct timeval *);	/* actualFetchTime */

/* send earliest and latest archive bounds */
extern int pmTimeSendBounds(const struct timeval *, const struct timeval *);

/* send a label and a timezone string */
extern int pmTimeSendTimezone(const char *, const char *);

/* show/hide the master time control dialog */
extern int pmTimeShowDialog(int);	/* 0==hide else show */

/* send new position and delta (note: delta is signed) */
extern int pmTimeSendPosition(const struct timeval *, int);

/* send new VCR mode */
extern int pmTimeSendMode(int); /* PM_TCTL_VCRMODE_STOP, etc */

/* return a char pixmap representing vcrmode (0..3) dir (-1, 0, 1), live (0, 1), record (0, 1) */
extern const char **pmTimeGetStatePixmap(int, int, int, int); /* vcrmode, dir, live, record */

/*
 * record session support
 */
#define PM_REC_ON	40
#define PM_REC_OFF	41
#define PM_REC_DETACH	43
#define PM_REC_STATUS	44
#define PM_REC_SETARG	45

typedef struct {
    FILE	*f_config;	/* caller writes pmlogger configuration here */
    int		fd_ipc;		/* IPC channel to pmlogger */
    char	*logfile;	/* full pathname for pmlogger error logfile */
    pid_t	pid;		/* process id for pmlogger */
    int		status;		/* exit status, -1 if unknown */
} pmRecordHost;

extern FILE *pmRecordSetup(const char *, const char *, int);
extern int pmRecordAddHost(const char *, int, pmRecordHost **);
extern int pmRecordControl(pmRecordHost *, int, const char *);


/*
 * Must be called by authorised clients in order that communication
 * with either a licensed or an unlicensed pmcd can take place.
 */
extern void __pmSetAuthClient(void);

#ifdef __cplusplus
}
#endif

#endif /* _PMAPI_MON_H */
