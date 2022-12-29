/*
 * Copyright (c) 1997,2004 Silicon Graphics, Inc.  All Rights Reserved.
 */

/* $Id: pmapi.h,v 2.82 2006/06/07 03:02:02 makc.longdrop.melbourne.sgi.com Exp $ */

#ifndef _PMAPI_H
#define _PMAPI_H

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/time.h>

/*
 * Platform and environment customization
 */
#include "platform_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PMAPI_VERSION_1	1
#define PMAPI_VERSION_2	2
#define PMAPI_VERSION	PMAPI_VERSION_2

/*
 * -------- Naming Services --------
 */
typedef unsigned int	pmID;		/* Metric Identifier */
#define PM_ID_NULL	0xffffffff

typedef unsigned int	pmInDom;	/* Instance-Domain */
#define PM_INDOM_NULL	0xffffffff
#define PM_IN_NULL	0xffffffff

#define PM_NS_DEFAULT	NULL	/* default name */

/*
 * Encoding for the units (dimensions Time and Space) and scale
 * for Performance Metric Values
 *
 * For example, a pmUnits struct of
 *	{ 1, -1, 0, PM_SPACE_MBYTE, PM_TIME_SEC, 0 }
 * represents Mbytes/sec, while 
 *	{ 0, 1, -1, 0, PM_TIME_HOUR, 6 }
 * represents hours/million-events
 */
typedef struct {
#ifdef HAVE_BITFIELDS_LTOR
    int	dimSpace : 4;	/* space dimension */
    int	dimTime : 4;	/* time dimension */
    int	dimCount : 4;	/* event dimension */
    int	scaleSpace : 4;	/* one of PM_SPACE_* below */
    int	scaleTime : 4;	/* one of PM_TIME_* below */
    int	scaleCount : 4;	/* one of PM_COUNT_* below */
    int pad : 8;
#else
    int pad : 8;
    int	scaleCount : 4;	/* one of PM_COUNT_* below */
    int	scaleTime : 4;	/* one of PM_TIME_* below */
    int	scaleSpace : 4;	/* one of PM_SPACE_* below */
    int	dimCount : 4;	/* event dimension */
    int	dimTime : 4;	/* time dimension */
    int	dimSpace : 4;	/* space dimension */
#endif
} pmUnits;			/* dimensional units and scale of value */

/* pmUnits.scaleSpace */
#define PM_SPACE_BYTE	0	/* bytes */
#define PM_SPACE_KBYTE	1	/* Kilobytes (1024) */
#define PM_SPACE_MBYTE	2	/* Megabytes (1024^2) */
#define PM_SPACE_GBYTE	3	/* Gigabytes (1024^3) */
#define PM_SPACE_TBYTE	4	/* Terabytes (1024^4) */
#define PM_SPACE_PBYTE	5	/* Petabytes (1024^5) */
#define PM_SPACE_EBYTE	6	/* Exabytes  (1024^6) */
/* pmUnits.scaleTime */
#define PM_TIME_NSEC	0	/* nanoseconds */
#define PM_TIME_USEC	1	/* microseconds */
#define PM_TIME_MSEC	2	/* milliseconds */
#define PM_TIME_SEC	3	/* seconds */
#define PM_TIME_MIN	4	/* minutes */
#define PM_TIME_HOUR	5	/* hours */
/*
 * pmUnits.scaleCount (e.g. count events, syscalls, interrupts, etc.)
 * -- these are simply powers of 10, and not enumerated here,
 *    e.g. 6 for 10^6, or -3 for 10^-3
 */
#define PM_COUNT_ONE	0	/* 1 */

/* Performance Metric Descriptor */
typedef struct {
    pmID	pmid;		/* unique identifier */
    int		type;		/* base data type (see below) */
    pmInDom	indom;		/* instance domain */
    int		sem;		/* semantics of value (see below) */
    pmUnits	units;		/* dimension and units */
} pmDesc;

/* pmDesc.type -- data type of metric values */
#define PM_TYPE_NOSUPPORT	-1	/* not implemented in this version */
#define PM_TYPE_32		0	/* 32-bit signed integer */
#define PM_TYPE_U32		1	/* 32-bit unsigned integer */
#define PM_TYPE_64		2	/* 64-bit signed integer */
#define PM_TYPE_U64		3	/* 64-bit unsigned integer */
#define PM_TYPE_FLOAT		4	/* 32-bit floating point */
#define PM_TYPE_DOUBLE		5	/* 64-bit floating point */
#define PM_TYPE_STRING		6	/* array of char */
#define PM_TYPE_AGGREGATE	7	/* arbitrary binary data (aggregate) */
#define PM_TYPE_AGGREGATE_STATIC 8	/* static pointer to aggregate */
#define PM_TYPE_UNKNOWN		255	/* used in pmValueBlock, not pmDesc */

/* pmDesc.sem -- semantics/interpretation of metric values */
#define PM_SEM_COUNTER	1	/* cumulative counter (monotonic increasing) */
				/* was PM_SEM_RATE, no longer used now */
#define PM_SEM_INSTANT	3	/* instantaneous value, continuous domain */
#define PM_SEM_DISCRETE	4	/* instantaneous value, discrete domain */

/* Generic Union for Value-Type conversions */
typedef union {
    __int32_t	l;	/* 32-bit signed */
    __uint32_t	ul;	/* 32-bit unsigned */
    __int64_t	ll;	/* 64-bit signed */
    __uint64_t	ull;	/* 64-bit unsigned */
    float	f;	/* 32-bit floating point */
    double	d;	/* 64-bit floating point */
    char	*cp;	/* char ptr */
    void	*vp;	/* void ptr */
} pmAtomValue;


/*
 * for PCP 1.x PMDAs and PMCDs, need to map errors unconditionally sometimes
 * otherwise mapping is conditional upon value being in range
 */

#define PM_ERR_BASE1 1000
#define PM_ERR_BASE2 12345
#define PM_ERR_BASE  PM_ERR_BASE2

#define PM_ERR_V1(e) (e)+PM_ERR_BASE2-PM_ERR_BASE1

#define XLATE_ERR_1TO2(e) \
	((e) <= -PM_ERR_BASE1 ? (e)+PM_ERR_BASE1-PM_ERR_BASE2 : (e))
#define XLATE_ERR_2TO1(e) \
	((e) <= -PM_ERR_BASE2 ? PM_ERR_V1(e) : (e))

/* PMAPI Error Conditions */

#define PM_ERR_GENERIC		(-PM_ERR_BASE-0)    /* Generic error, already reported above */
#define PM_ERR_PMNS		(-PM_ERR_BASE-1)    /* Problems parsing PMNS definitions */
#define PM_ERR_NOPMNS		(-PM_ERR_BASE-2)    /* PMNS not accessible */
#define PM_ERR_DUPPMNS		(-PM_ERR_BASE-3)    /* Attempt to reload the PMNS */
#define PM_ERR_TEXT		(-PM_ERR_BASE-4)    /* Oneline or help text is not available */
#define PM_ERR_APPVERSION	(-PM_ERR_BASE-5)    /* Metric not supported by this version of monitored application */
#define PM_ERR_VALUE		(-PM_ERR_BASE-6)    /* Missing metric value(s) */
#define PM_ERR_LICENSE		(-PM_ERR_BASE-7)    /* Current PCP license does not permit this operation */
#define PM_ERR_TIMEOUT		(-PM_ERR_BASE-8)    /* Timeout waiting for a response from PMCD */
#define PM_ERR_NODATA		(-PM_ERR_BASE-9)    /* Empty archive log file */
#define PM_ERR_RESET		(-PM_ERR_BASE-10)   /* pmcd reset or configuration changed */
#define PM_ERR_FILE		(-PM_ERR_BASE-11)   /* Cannot locate a file */
#define PM_ERR_NAME		(-PM_ERR_BASE-12)   /* Unknown metric name */
#define PM_ERR_PMID		(-PM_ERR_BASE-13)   /* Unknown or illegal metric identifier */
#define PM_ERR_INDOM		(-PM_ERR_BASE-14)   /* Unknown or illegal instance domain identifier */
#define PM_ERR_INST		(-PM_ERR_BASE-15)   /* Unknown or illegal instance identifier */
#define PM_ERR_UNIT		(-PM_ERR_BASE-16)   /* Illegal pmUnits specification */
#define PM_ERR_CONV		(-PM_ERR_BASE-17)   /* Impossible value or scale conversion */
#define PM_ERR_TRUNC		(-PM_ERR_BASE-18)   /* Truncation in value conversion */
#define PM_ERR_SIGN		(-PM_ERR_BASE-19)   /* Negative value in conversion to unsigned */
#define PM_ERR_PROFILE		(-PM_ERR_BASE-20)   /* Explicit instance identifier(s) required */
#define PM_ERR_IPC		(-PM_ERR_BASE-21)   /* IPC protocol failure */
#define PM_ERR_NOASCII		(-PM_ERR_BASE-22)   /* ASCII format not supported for this PDU */
#define PM_ERR_EOF		(-PM_ERR_BASE-23)   /* IPC channel closed */
#define PM_ERR_NOTHOST		(-PM_ERR_BASE-24)   /* Operation requires context with host source of metrics */
#define PM_ERR_EOL		(-PM_ERR_BASE-25)   /* End of PCP archive log */
#define PM_ERR_MODE		(-PM_ERR_BASE-26)   /* Illegal mode specification */
#define PM_ERR_LABEL		(-PM_ERR_BASE-27)   /* Illegal label record at start of a PCP archive log file */
#define PM_ERR_LOGREC		(-PM_ERR_BASE-28)   /* Corrupted record in a PCP archive log */
#define PM_ERR_NOTARCHIVE	(-PM_ERR_BASE-29)   /* Operation requires context with archive source of metrics */
#define PM_ERR_LOGFILE          (-PM_ERR_BASE-30)   /* Missing archive file */
#define PM_ERR_NOCONTEXT	(-PM_ERR_BASE-31)   /* Attempt to use an illegal context */
#define PM_ERR_PROFILESPEC	(-PM_ERR_BASE-32)   /* NULL pmInDom with non-NULL instlist */
#define PM_ERR_PMID_LOG		(-PM_ERR_BASE-33)   /* Metric not defined in the PCP archive log */
#define PM_ERR_INDOM_LOG	(-PM_ERR_BASE-34)   /* Instance domain identifier not defined in the PCP archive log */
#define PM_ERR_INST_LOG		(-PM_ERR_BASE-35)   /* Instance identifier not defined in the PCP archive log */
#define PM_ERR_NOPROFILE	(-PM_ERR_BASE-36)   /* Missing profile - protocol botch */
#define	PM_ERR_NOAGENT		(-PM_ERR_BASE-41)   /* No pmcd agent for domain of request */
#define PM_ERR_PERMISSION	(-PM_ERR_BASE-42)   /* No permission to perform requested operation */
#define PM_ERR_CONNLIMIT	(-PM_ERR_BASE-43)   /* PMCD connection limit for this host exceeded */
#define PM_ERR_AGAIN		(-PM_ERR_BASE-44)   /* try again. Info not currently available */

#define PM_ERR_ISCONN		(-PM_ERR_BASE-45)   /* already connected */
#define PM_ERR_NOTCONN		(-PM_ERR_BASE-46)   /* not connected */
#define PM_ERR_NEEDPORT		(-PM_ERR_BASE-47)   /* port name required */
#define PM_ERR_WANTACK		(-PM_ERR_BASE-48)   /* can not send due to pending acks */
#define PM_ERR_NONLEAF		(-PM_ERR_BASE-49)   /* PMNS node is not a leaf node */
#define PM_ERR_OBJSTYLE		(-PM_ERR_BASE-50)   /* user/kernel object style mismatch */
#define PM_ERR_PMCDLICENSE	(-PM_ERR_BASE-51)   /* PMCD is not licensed to accept connections */

#define PM_ERR_CTXBUSY		(-PM_ERR_BASE-97)   /* Context is busy */
#define PM_ERR_TOOSMALL		(-PM_ERR_BASE-98)   /* Insufficient elements in list */
#define PM_ERR_TOOBIG		(-PM_ERR_BASE-99)   /* Result size exceeded */

#define PM_ERR_PMDAREADY	(-PM_ERR_BASE-1048) /* now ready to respond */
#define PM_ERR_PMDANOTREADY	(-PM_ERR_BASE-1049) /* not yet ready to respond */
#define PM_ERR_NYI		(-PM_ERR_BASE-8999) /* Functionality not yet implemented */

/*
 * Report PMAPI errors messages
 */
extern const char *pmErrStr(int);

/*
 * Load a Performance Metrics Name Space
 */
extern int pmLoadNameSpace(const char *);
extern int pmLoadASCIINameSpace(const char *, int);
extern void pmUnloadNameSpace(void);

/*
 * Where is PMNS located - added for distributed PMNS.
 */
extern int pmGetPMNSLocation(void);
#define PMNS_LOCAL   1
#define PMNS_REMOTE  2
#define PMNS_ARCHIVE 3

/*
 * Trim a name space with respect to the current context
 * (usually from an archive, or after processing an archive)
 */
extern int pmTrimNameSpace(void);

/*
 * Expand a list of names to a list of metrics ids
 */
extern int pmLookupName(int, char **, pmID *);

/*
 * Find the names of descendent nodes in the PMNS
 * and in the latter case get the status of each child.
 */
extern int pmGetChildren(const char *, char ***);
extern int pmGetChildrenStatus(const char *, char ***, int **);
#define PMNS_LEAF_STATUS     0	/* leaf node in PMNS tree */
#define PMNS_NONLEAF_STATUS  1	/* non-terminal node in PMNS tree */

/*
 * Reverse Lookup: find name(s) given a metric id
 */
extern int pmNameID(pmID, char **);		/* one */
extern int pmNameAll(pmID, char ***);		/* all */

/*
 * Handy recursive descent of the PMNS
 */
extern int pmTraversePMNS(const char *, void(*)(const char *));

/*
 * Given a metric, find it's descriptor (caller supplies buffer for desc),
 * from the current context.
 */
extern int pmLookupDesc(pmID, pmDesc *);

/*
 * Return the internal instance identifier, from the current context,
 * given an instance domain and the external instance name.
 * Archive variant scans the union of the indom entries in the archive
 * log.
 */
extern int pmLookupInDom(pmInDom, const char *);
extern int pmLookupInDomArchive(pmInDom, const char *);

/*
 * Return the external instance name, from the current context,
 * given an instance domain and the internal instance identifier.
 * Archive variant scans the union of the indom entries in the archive
 * log.
 */
extern int pmNameInDom(pmInDom, int, char **);
extern int pmNameInDomArchive(pmInDom, int, char **);

/*
 * Return all of the internal instance identifiers (instlist) and external
 * instance names (namelist) for the given instance domain in the current
 * context.
 * Archive variant returns the union of the indom entries in the archive
 * log.
 */
extern int pmGetInDom(pmInDom, int **, char ***);
extern int pmGetInDomArchive(pmInDom, int **, char ***);

/*
 * Given context ID, return a host name, associated with the id
 * or empty string if no name can be found
 * Note: in IRIX6.5, this is an optional symbol
 */
extern const char *pmGetContextHostName(int);

/*
 * return the handle of the current context
 */
extern int pmWhichContext(void);

/*
 * destroy a context and close it's connection
 */
extern int pmDestroyContext(int);

/*
 * Establish a new context (source of performance data + instance profile)
 * for the named host
 */
extern int pmNewContext(int, const char *);
#define PM_CONTEXT_HOST		1	/* context types */
#define PM_CONTEXT_ARCHIVE	2
#define PM_CONTEXT_LOCAL	3	/* local host, no pmcd connection */
#define PM_CONTEXT_TYPEMASK	0xff	/* Mask to separate types from flags */

#define PM_CTXFLAG_SHALLOW	(1<<8)  /* Shallow host context - don't connect */
#define PM_CTXFLAG_EXCLUSIVE	(1<<9)  /* Exclusive host context - don't share socket */

/*
 * Duplicate current context -- returns handle to new one for pmUseContext()
 */
extern int pmDupContext(void);

/*
 * Restore (previously established or duplicated) context
 */
extern int pmUseContext(int);

/*
 * Reconnect an existing context (when pmcd dies, etc). All existing context
 * settings are preserved and the previous context settings are restored.
 */
extern int pmReconnectContext(int);

extern int pmGetContextFD(int);
extern int pmGetContextTimeout(int, int*);
extern int pmContextConnectTo(int, const struct sockaddr *);
extern int pmContextConnectChangeState(int);
extern void pmContextUndef (void);

/*
 * Add to instance profile.
 * If pmInDom == PM_INDOM_NULL, then all instance domains are selected.
 * If no inst parameters are given, then all instances are selected.
 * e.g. to select all available instances in all domains,
 * then use pmAddProfile(PM_INDOM_NULL, 0, NULL).
 */
extern int pmAddProfile(pmInDom, int, int *);

/*
 * Delete from instance profile.
 * Similar (but negated) functional semantics to pmProfileAdd.
 * E.g. to disable all instances in all domains then use
 * pmDelProfile(PM_INDOM_NULL, 0, NULL).
 */
extern int pmDelProfile(pmInDom, int, int *);

/* 
 * ---------- Collection services ---------- 
 *
 * Result from pmFetch is encoded as a timestamp and vector of pointers
 * to pmValueSet instances (one per PMID in the result).
 * Each pmValueSet has a PMID, a value count, a value format, and a vector of
 * instance-value pairs.  Aggregate, string and non-int values are returned
 * via one further level of indirection using pmValueBlocks.
 *
 * timeStamp
 * ->pmID
 *   value format
 *     instance, value
 *     instance, value
 *     ... etc
 *
 * ->pmID
 *   value format
 *     instance, value
 *     ... etc
 *
 *
 * Notes on pmValueBlock
 *   0. may be used for arbitrary binary data
 *   1. only ever allocated dynamically, and vbuf expands to accommodate
 *	an arbitrary value (don't believe the [1] size!)
 *   2. len is the length of the len field + the real size of vbuf
 *	(which includes the null-byte terminator if there is one)
 */
typedef struct {
#ifdef HAVE_BITFIELDS_LTOR
    unsigned int	vtype : 8;	/* value type */
    unsigned int	vlen : 24;	/* bytes for vtype/vlen + vbuf */
#else
    unsigned int	vlen : 24;	/* bytes for vtype/vlen + vbuf */
    unsigned int	vtype : 8;	/* value type */
#endif
    char		vbuf[1];	/* the value */
} pmValueBlock;

#define PM_VAL_HDR_SIZE	4		/* bytes for the vtype/vlen header */
#define PM_VAL_VLEN_MAX	0x00ffffff	/* maximum vbuf[] size */

typedef struct {
    int		inst;		/* instance identifier */
    union {
	pmValueBlock	*pval;	/* pointer to value-block */
	int		lval;	/* integer value insitu (lval 'cuz it WAS a long) */
    } value;
} pmValue;

typedef struct {
    pmID	pmid;		/* metric identifier */
    int		numval;		/* number of values */
    int		valfmt;		/* value style */
    pmValue	vlist[1];	/* set of instances/values */
} pmValueSet;

/* values for valfmt */
#define PM_VAL_INSITU	0	/* value.lval is it */
#define PM_VAL_DPTR	1	/* value.pval->vbuf is it, and dynamic alloc */
#define PM_VAL_SPTR	2	/* value.pval->vbuf is it, and static alloc */


/* Result returned by pmFetch() */
typedef struct {
    struct timeval	timestamp;	/* time stamped by collector */
    int		numpmid;		/* number of PMIDs */
    pmValueSet	*vset[1];		/* set of value sets, one per PMID */
} pmResult;


/*
 * Fetch metrics. Value/instances returned depends on current instance profile.
 * By default, all available instances for each requested metric id are
 * returned. The metrics argument is terminated with PM_NULL_ID
 *
 * The value sets returned are in the same order as the metrics argument,
 * and the number of value sets returned is guaranteed to be the same as
 * the number of metrics in the agument.  
 */
extern int pmFetch(int, pmID *, pmResult **);

/*
 * PMCD state changes returned as pmFetch function result for PM_CONTEXT_HOST
 * contexts, i.e. when communicating with PMCD
 */
#define PMCD_NO_CHANGE		0
#define PMCD_ADD_AGENT		1
#define PMCD_RESTART_AGENT	2
#define PMCD_DROP_AGENT		4

/*
 * variant that is used to return a pmResult from an archive
 */
extern int pmFetchArchive(pmResult **);

/*
 * Label Record at the start of every log file - as exported above
 * the PMAPI ...
 * NOTE MAXHOSTNAMELEN is a bad choice here for ll_hostname[], as
 *	it may vary on different hosts ... we use PM_LOG_MAXHOSTLEN instead, and
 *	size this to be the same as MAXHOSTNAMELEN in IRIX 5.3
 * NOTE	that the struct timeval means we have another struct (__pmLogLabel32)
 *	for internal use that has a timeval_32 in place of the struct timeval.
 */
#define PM_TZ_MAXLEN	40
#define PM_LOG_MAXHOSTLEN		64
#define PM_LOG_MAGIC	0x50052600
#define PM_LOG_VERS01	0x1
#define PM_LOG_VERS02	0x2
#define PM_LOG_VOL_TI	-2	/* temporal index */
#define PM_LOG_VOL_META	-1	/* meta data */
typedef struct {
    int		ll_magic;	/* PM_LOG_MAGIC | log format version no. */
    pid_t	ll_pid;				/* PID of logger */
    struct timeval	ll_start;		/* start of this log */
    char	ll_hostname[PM_LOG_MAXHOSTLEN];	/* name of collection host */
    char	ll_tz[PM_TZ_MAXLEN];		/* $TZ at collection host */
} pmLogLabel;

/*
 * get the label record from the current archive context, and discover
 * when the archive ends
 */
extern int pmGetArchiveLabel(pmLogLabel *);
extern int pmGetArchiveEnd(struct timeval *);

/* Free result buffer */
extern void pmFreeResult(pmResult *);

/* Value extract from pmValue and type conversion */
extern int pmExtractValue(int, const pmValue *, int, pmAtomValue *, int);

/* Print single pmValue */
extern void pmPrintValue(FILE *, int, int, const pmValue *, int);

/* Scale conversion, based on value format, value type and scale */
extern int pmConvScale(int, const pmAtomValue *, const pmUnits *, pmAtomValue *, 
		       pmUnits *);

/* Sort instances for each metric within a pmResult */
extern void pmSortInstances(pmResult *);

/* Adjust collection time and/or mode for pmFetch */
extern int pmSetMode(int, const struct timeval *, int);
#define PM_MODE_LIVE	0
#define PM_MODE_INTERP	1
#define PM_MODE_FORW	2
#define PM_MODE_BACK	3

/* Modify the value of one or more metrics */
extern int pmStore(const pmResult *);

/* Get help and descriptive text */
extern int pmLookupText(pmID, int, char **);
extern int pmLookupInDomText(pmInDom, int, char **);
#define PM_TEXT_ONELINE	1
#define PM_TEXT_HELP	2

/*
 * some handy formatting routines for messages, and other output
 */
extern const char *pmIDStr(pmID);
extern const char *pmInDomStr(pmInDom);
extern const char *pmTypeStr(int);
extern const char *pmUnitsStr(const pmUnits *);
extern const char *pmAtomStr(const pmAtomValue *, int);
extern const char *pmNumberStr(double);

/* Extended time base definitions and macros */
#define PM_XTB_FLAG	0x1000000

#define PM_XTB_SET(type) (PM_XTB_FLAG | (type << 16))
#define PM_XTB_GET(x) ( (x & PM_XTB_FLAG) ? ( (x & 0xff0000) >> 16) : -1)

/* parse -t, -S, -T, -A and -O options */
extern int pmParseInterval(const char *, struct timeval *, char **);
extern int pmParseTimeWindow(
      const char *, const char *, const char *, const char *,
      const struct timeval *, const struct timeval *,
      struct timeval *, struct timeval *, struct timeval *, char **);

/* reporting timezone */
extern int pmUseZone(const int);
extern int pmNewZone(const char *);
extern int pmNewContextZone(void);
extern int pmWhichZone(char **);
extern char *pmCtime(const time_t *, char *);
extern struct tm *pmLocaltime(const time_t *, struct tm *);

/* Parse host:metric[instances] or archive/metric[instances] */
typedef struct {
    int         isarch;         /* source type: 0 -> live host, 1 -> archive */
    char        *source;        /* name of source host or archive */
    char        *metric;        /* name of metric */
    int         ninst;          /* number of instances, 0 -> all */
    char        *inst[1];       /* array of instance names */
} pmMetricSpec;

/* parsing of host:metric[instances] or archive/metric[instances] */
extern int pmParseMetricSpec(const char *, int, char *, pmMetricSpec **,
			     char **);
#define pmFreeMetricSpec(p) free(p)

/*
 * configurable error reporting
 */
extern int pmprintf(const char *, ...);
extern int pmflush(void);

/*
 * Wrapper for config/environment variables. Warning: this will exit() with
 * a FATAL error if /etc/pcp.conf does not exist and $PCP_CONF is not set.
 * Return values point to strings in the environment.
 * Note: in IRIX6.5, this is an optional symbol
 */
extern char *pmGetConfig(const char *);

/*
 * Mainloop implementation.
 */
struct rusage;

int pmLoopRegisterInput(int, int, int (*)(int, int, void *), void *, int);
int pmLoopRegisterSignal(int, int (*)(int, void *), void *);
int pmLoopRegisterTimeout(int, int (*)(void *), void *);
int pmLoopRegisterChild(pid_t, int (*)(pid_t, int, const struct rusage *, void *), void *);
int pmLoopRegisterIdle(int (*)(void *), void *);

void pmLoopUnregisterInput(int);
void pmLoopUnregisterSignal(int);
void pmLoopUnregisterTimeout(int);
void pmLoopUnregisterChild(int);
void pmLoopUnregisterIdle(int);

void pmLoopStop(void);
int pmLoopMain(void);

extern int pmLoopDebug;

/*
 * Asynchronous versions of main pmapi client routines - each one
 * either sends or receives a PDU.
 */ 
extern int pmReceiveDesc(int, pmDesc *);
extern int pmReceiveFetch(int, pmResult **);
extern int pmReceiveInDom (int,  int **, char ***);
extern int pmReceiveInDomInst (int);
extern int pmReceiveInDomName (int, char **);
extern int pmReceiveNameID (int, char **);
extern int pmReceiveNames (int, int, pmID []);
extern int pmReceiveNamesAll (int, char ***);
extern int pmReceiveNamesOfChildren (int, char ***, int **);
extern int pmReceiveStore (int);
extern int pmReceiveText (int, char **);
extern int pmReceiveTraversePMNS (int, void (*)(const char *));
extern int pmRequestDesc (int, pmID );
extern int pmRequestFetch(int, int, pmID *);
extern int pmRequestInDom (int, pmInDom);
extern int pmRequestInDomInst (int, pmInDom, const char *);
extern int pmRequestInDomName (int, pmInDom, int);
extern int pmRequestInDomText (int, pmID, int);
extern int pmRequestNameID (int, pmID);
extern int pmRequestNames (int, int, char *[]);
extern int pmRequestNamesOfChildern (int, const char *, int );
extern int pmRequestStore (int, const pmResult *);
extern int pmRequestText (int, pmID, int);
extern int pmRequestTraversePMNS (int, const char *);

#ifdef __sgi
#ifndef _SGI_COMPILING_LIBPCP
#pragma optional pmLoopRegisterInput
#pragma optional pmLoopRegisterSignal
#pragma optional pmLoopRegisterTimeout
#pragma optional pmLoopRegisterChild
#pragma optional pmLoopRegisterIdle
#pragma optional pmLoopUnregisterInput
#pragma optional pmLoopUnregisterSignal
#pragma optional pmLoopUnregisterTimeout
#pragma optional pmLoopUnregisterChild
#pragma optional pmLoopUnregisterIdle
#pragma optional pmLoopStop
#pragma optional pmLoopMain

#pragma optional pmGetContextFD
#pragma optional pmGetContextTimeout
#pragma optional pmContextConnectTo
#pragma optional pmContextConnectChangeState
#pragma optional pmContextUndef

#pragma optional pmReceiveDesc
#pragma optional pmReceiveFetch
#pragma optional pmReceiveInDom
#pragma optional pmReceiveInDomInst
#pragma optional pmReceiveInDomName
#pragma optional pmReceiveNameID
#pragma optional pmReceiveNames
#pragma optional pmReceiveNamesAll
#pragma optional pmReceiveNamesOfChildren
#pragma optional pmReceiveStore
#pragma optional pmReceiveTraversePMNS
#pragma optional pmReceiveText
#pragma optional pmRequestDesc
#pragma optional pmRequestFetch
#pragma optional pmRequestInDom
#pragma optional pmRequestInDomInst
#pragma optional pmRequestInDomName
#pragma optional pmRequestInDomText
#pragma optional pmRequestNameID
#pragma optional pmRequestNames
#pragma optional pmRequestNamesOfChildern
#pragma optional pmRequestStore
#pragma optional pmRequestText
#pragma optional pmRequestTraversePMNS

#endif
#endif


#ifdef HAVE_SEPARATE_MONS_H
#include "pmapi_mon.h"
#endif

#ifdef MALLOC_AUDIT
#include "malloc-audit.h"
#endif

#ifdef __cplusplus
}
#endif

#endif /* _PMAPI_H */
