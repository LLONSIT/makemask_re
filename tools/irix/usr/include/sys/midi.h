/**************************************************************************
 *									  *
 *		Copyright ( C ) 1990-1995, Silicon Graphics, Inc.	  *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/
/*
 * Internals for the MIDI streams mulitplexor
 */
#ident "$Revision: 1.35 $"

#ifndef	__MIDI_H_
#define	__MIDI_H_

#include <sys/ioctl.h>
#include <sys/time.h>

/*
 * This is the format of PROTO messages sent by libmd
 */
struct midistamp {
	int prim_type;
	int lowerdev;			/* lower device message came from */
	int port;			/* port on lower device */
	long long tv;	        	/* delta time or ticks */
};

/* prim_types for new style messages */
#define MD_NOMSG        0
#define MD_MESSAGE      1
#define MD_SYS          2  
#define MD_TIMECODE     3
#define MD_QFRAME       4
#define MD_COMMON       5
#define MD_REALTIME     6
#define MD_TEMPO        7	        /* tempo change meta event */

/* size of sysex buffer */
#define SYSBUFSZ     1024

/*
 * These are used by libmidi (old library)
 */
struct midistamps {
	int prim_type;			/* always MIDI_STAMPED */
	struct timeval tv[1];		/* 1 or more stamps */
};

struct midisysex {
	int prim_type;			/* always MIDI_SYSEX */
	int dev_id;			/* equivalent to midimessage.dev_id */
	struct timeval tv;
};

struct midistampi {
	int prim_type;			/* MIDI_STAMPI or MIDI_SYSEXI */
	int data_len;			/* # midimessages in data portion */
	struct timeval tv;		/* timestamp for data portion */
};

union midiprims {
	int prim_type;
	struct midisysex sysex;
	struct midistamps stamps;
	struct midistampi stampi;
};

struct midimessage {			/* for 1-3 byte messages, !sysex */
	u_int len:2;			/* msg len [0..3] */
	u_int dev_id:6;			/* getmsg src / putmsg dest */
	u_char bytes[3];		/* bytes[1]=status */
};

/* prim_types for old style messages */
#define	MIDI_STAMPED	1		/* delta-stamped 1-3 byte messages */
#define MIDI_SYSEX	2		/* delta-stamped sysex message */
#define	MIDI_STAMPI	3		/* delta-stamped input messages */
#define	MIDI_SYSEXI	4		/* delta-stamped input sysex */

/*
 * MIOC_GETDEVINFO
 *
 * The devinfo structure is returned by the GETDEVINFO ioctl. It
 * contains various bits of interesting information about the 
 * upper-level application which has the requested port open.
 * NOTE: This call is only for use by the MIDI library; user-level
 * applications should not rely on this interface!
 */
#define APPNMSZ   32		/* max name of upper-level app */
struct mididevinfo {
	dev_t	minor;		/* Minor number of midi dev to query */
	pid_t	pid;		/* Process ID of upper-level process */
	char	name[APPNMSZ];	/* Name of midi dev */
	int	flags;		/* Device flags */
	int	lower;		/* Lower device index */
	int	ready;		/* Indicates whether the ready flag is set */
};

/* mididevinfo flag values */
#define	MIDI_STAMP_INPUT	0x01	/* 1 = delaystamp input */
#define MIDI_PAUSED		0x02	/* 1 = timer is paused */
#define MIDI_WRONLY             0x04    /* 1 = write only stream */
#define MIDI_RDONLY             0x08    /* 1 = read only stream */
#define MIDI_FAST               0x10    /* 1 = fast output mode (no timer) */
#define MIDI_FLOW               0x20    /* 1 = use time flow control */
#define MIDI_TICKMODE           0x40    /* 1 = use ticks for time stamps */
#define MIDI_NOTIFY		0x80	/* This stream wants notify events */
#define MIDI_SQUELCH		0x100	/* Squelch all non-notify events */
#define MIDI_READY		0x200	/* The dev is ready to xmit or recv */

/*
 * MIOC_SETNOTIFY
 *
 * The midistatusinfo structure is used by the MIDI driver to pass
 * events of interest up to user-level applications.  This interface
 * is primarily intended for use by SGI's MIDI daemons and status 
 * monitors; it is subject to change without notice.
 */
struct midistatusinfo {
	char event_hdr[8];		/* ASCII event name */
	unsigned type;			/* Type of status message */
	int id;				/* Minor number of multiplexor id */
	char name[APPNMSZ];		/* App or Link name (if known) */
	pid_t pid;			/* Process ID (may not be applicable) */
	int args[4];			/* Argument space */
};

/*
 * midistatusinfo type bits
 */
#define MNOTE_MDOPEN	0x1		/* Application opens a port */
#define MNOTE_MDCLOSE	0x2		/* Application closed a port */
#define MNOTE_LINK	0x4		/* A new MIDI device was added */
#define MNOTE_UNLINK	0x8		/* A MIDI device was removed */
#define MNOTE_SETLOWER	0x10		/* A device was (re)named */
#define MNOTE_SETNAME	0x20		/* A port was (re)named */
/* #define MNOTE_RESCAN	0x40 */		/* OBSOLETE */
#define MNOTE_SETDEFAULT 0x80		/* Set the default port */
#define MNOTE_PRIVATE	0x1000		/* Only provide information for events
					 * pertaining to my link */
#define MNOTE_GLOBAL	0x0		/* Get all events (default) */
#define MNOTE_ALLEVENTS 0xff		/* Interested in all events */

/*
 * MIO_{GET,SET}NAME
 */
#define LINKNAMESZ  32		        /* max link name size */
typedef struct midi_name_s {
	int lowerlink;			/* Streams I_LINK id for SET,
					 * interface index for GET
					 */
	char name[LINKNAMESZ];
} midi_name_t;

/*
 * MIOC_GETSTATS
 */
struct midi_stats {
	long long higherror;   /* highest variance from ideal time */
	long long lowerror;    /* lowest variance */
	long long totalerr;    /* total error */
	int nerrors;           /* number of events later than acceptable */
	int nmessages;         /* number of messages gone through */
};

#define MIDI_PORT_RESERVED 32	

/* ioctl cmds */
#define MIOC_STAMPI	_IOW('M',1,int)		/* 1 = delaystamp input */
#define MIOC_TIMELEFT   _IOR('M',2,long long)
					/* time left before queu drains */
#define MIOC_CHMOD      _IOW('M',3,int)	        /* make stream read only */
#define MIOC_ACTIVE	_IOW('M',4,int)	        /* ignore active sense */
#define MIOC_TIMERRST   _IOW('M',5,long long)   /* reset delta time */
#define MIOC_INTERNAL   _IOW('M',6,int)	        /* internal synth interface */
#define MIOC_FASTOUTPUT _IOW('M',7,int)         /* enable fast mode (no time stamp) */
#define MIOC_VERSION    _IOW('M',8,int)	        /* set the version number */
#define MIOC_SETLOWER   _IOW('M',9,int)         /* set the lower device used */
#if _MIPS_SIM == _ABI64	/* 32-bit user pointers */
#define MIOC_SETNAME    _IOR('M',11,int)        /* name a port */
#define MIOC_GETNAME    _IOW('M',12,int)        /* get the name of a port */
#else
#define MIOC_SETNAME    _IOR('M',11,midi_name_t *) /* name a port */
#define MIOC_GETNAME    _IOW('M',12,midi_name_t *) /* get the name of a port */
#endif /* _MIPS_SIM == _ABI64 */

#define MIOC_GETLOWERS  _IOR('M',13,int)        /* get highest index of a lower device */
#define MIOC_FLOW       _IOW('M',14,int)        /* set flow control */
#define MIOC_SETTICKS   _IOW('M',15,int)        /* set tick mode 0=off, non-zero = division */
#define MIOC_SETTEMPO   _IOW('M',16,int)   /* set usecs per beat in tick mode */
#define MIOC_TELL       _IOR('M',17,long long)
                                      /* get last message that was sent out */
#define MIOC_STOP       _IOR('M',18,long long)        
                               /* stop MIDI output and return the last tick */
#define MIOC_SETSCALAR  _IOW('M',19,long long) /* set tempo scale */
#define MIOC_PANIC      _IOW('M',20,int)        /* send all notes off & reset all controllers */

#if _MIPS_SIM == _ABI64	/* 32-bit user pointers */
#define MIOC_SET_DEFAULT _IOW('M',21,int) /* set the default device */
#else
#define MIOC_SET_DEFAULT _IOW('M',21,midi_name_t *) /* set the default device */
#endif

#define MIOC_GETSTATS   _IOR('M',22,struct midi_stats) /* get the timing stats */
#define MIOC_DELTA      _IOW('M',23,long long) 
#define MIOC_MINOR      _IOR('M',23,int) 

#define MIOC_GETNUMDEVS	_IOR('M',24, int)
#define MIOC_GETDEVINFO  _IOR('M',26, struct mididevinfo)

#define MIOC_SETSQUELCH	_IOW('M',27, int)
#define MIOC_SETNOTIFY	_IOW('M',28, int)
#define MIOC_SETREADY   _IOW('M',29, int)
/* MTP stuff */
#define MIOC_SETFAST    _IOW('M',30, int)       /* this is a fast device */
#define MIOC_SETMTPN    _IOW('M',31, int)       /* it belongs to mtp #{1,2} */

#define MIOC_SETID 	_IOW('M', 32, int)	/* Set autofeedback filter 
						 * value. */
#define MIOC_TELLNOW    _IOR('M',33,long long)
						/* get current tick */
                        

#define STRID_MIDI 0xbad

#ifdef MIDI_NOSTREAMS
#include <sys/nsmidi.h>
#else
#ifdef _KERNEL

/* Chain for "I_LINK"'ed lower streams */
struct midilink {
	queue_t *lwq;			/* top write queue of lower stream */
	queue_t *lrq;			/* top read queue of lower stream */
	int l_index;			/* system ID from struct linkblk */
	int mli;			/* lower device */
	unsigned int l_flags;		/* flags specific to this device */
	char name[LINKNAMESZ];	        /* name of this link */
};

/* struct midilink flag values */
#define MIDI_INTERNAL           0x01    /* link is internal */

struct midiport {
	/* Streams stuff */
	queue_t *rq;			/* bottom read queue of upper stream */
	queue_t *wq;			/* wrte queue of upper stream */

	dev_t mdi;		        /* index into midi_ports[] */
	int mli;			/* index into midi_links[] */

	int version;		        /* version of library  */
	int filter_id;			/* anti-feedback filtration value */ 
	unsigned int flags;		/* see flag values below */
	char app_name[APPNMSZ];		/* The name of the upper-level app */
	pid_t app_pid;			/* App's process ID */
	unsigned int notify_flags;	/* Notification flags */
	struct midi_stats stats;	/* Error statistics */
	
	/* I/O timing */
	toid_t tid;			/* timeout id, or zero */
	long long lastwrite;		/* last time of write */
	long long lastread;		/* last time of read */
	long long totalsent;		/* last tick sent out */

	/* Temporal buffering */
	long long timeleft;    		/* time remaining 'til queue empties */

	/* Tickmode and tempo scaling parameters */
	long long tempo;       		/* micro seconds per beat */
	long long division;    		/* pulses per tick, def=24 */
	long long scale;       		/* tempo scale in millionths*/
	long long npb;	       		/* scaled tempo: nanos per beat */
	long long tnrem;       		/* remainder of nanos per tick: n/div */
	long long ntrem;       		/* remainder of ticks per nano: n/div */
};

/* Stuff from master.d/midi */

/* Upper streams: */
extern int midi_cnt;			/* Actual number */
extern struct midiport *midi_ports[];	/* Actual active instantiations */

/* Lower streams: */
extern int midilink_cnt;		/* Actual number */
extern struct midilink *midi_links[];	/* Actual lower links */

#endif /* MIDI_NOSTREAMS */
#endif /* _KERNEL */
#endif  /* __MIDI_H__ */
