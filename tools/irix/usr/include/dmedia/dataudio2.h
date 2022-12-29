#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include <dmedia/dmedia.h>
#include <dmedia/dm_timecode.h>

/*
 * dataudio.h
 *
 * Definitions for handling audio data from the DAT drive
 *
 *
 * Copyright 1991, 1992, 1993, 1994, 1995 Silicon Graphics, Inc.
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics, Inc.;
 * the contents of this file may not be disclosed to third parties, copied or
 * duplicated in any form, in whole or in part, without the prior written
 * permission of Silicon Graphics, Inc.
 *
 * RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to restrictions
 * as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data
 * and Computer Software clause at DFARS 252.227-7013, and/or in similar or
 * successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -
 * rights reserved under the Copyright Laws of the United States.
 */

/* DAT defines */

#define DAT_DATASIZE       5760
#define DAT_SUBCODESIZE    (sizeof(struct DATsubcode))
#define DAT_BLOCKSIZE      (DAT_DATASIZE + DAT_SUBCODESIZE)
#define DAT_DATASIZE48K    DAT_DATASIZE
#define DAT_DATASIZE44K    5292
#define DAT_DATASIZE32K    3840
#define DAT_PADSIZE44K     (DAT_DATASIZE - DAT_DATASIZE44K)
#define DAT_PADSIZE32K     (DAT_DATASIZE - DAT_DATASIZE32K)
#define DAT_NUMSAMPS48K    (DAT_DATASIZE48K/2)
#define DAT_NUMSAMPS44K    (DAT_DATASIZE44K/2)
#define DAT_NUMSAMPS32K    (DAT_DATASIZE32K/2)

#define DAT_XR_30                0
#define DAT_XR_2997NDF           1
#define DAT_XR_2997DF            2
#define DAT_XR_25                3
#define DAT_XR_24                4


/* following definitions should sync with 
       #define MTAUDPOSN_PROG  0
       #define MTAUDPOSN_ABS   1
       #define MTAUDPOSN_RUN   2
       #define MTAUDPOSN_PTIME 3
   which were defined under <sys/mtio.h>  */
#define DAT_SEEK_PROG  0       /* seek to program number */
#define DAT_SEEK_ABS   1       /* seek to absolute time */
#define DAT_SEEK_RUN   2       /* seek to running time */
#define DAT_SEEK_PTIME 3       /* seek to program time (within program) */


/*
 * DAT status code
 */
#define DAT_READY         0  /* ready to accept next command */
#define DAT_BUSYSTATE     1  /* device is executing a previous command */
#define DAT_ERROR         2  /* not identified error */
#define DAT_UNDEFINE      3  /* undefined status, could be a problem */
#define DAT_NOSENSE       4  /* no sense */
#define DAT_NOTREADY      5  /* not ready, no tape or ... */
#define DAT_MEDERR        6  /* unrecoverable data error encountered */
#define DAT_HWERR         7  /* hardware failure */
#define DAT_ILLREQ        8  /* the CDB contains an invalid bit */
#define DAT_UATTEN        9  /* tape was changed prior to sending command */
#define DAT_WPROT        10  /* write protected */
#define DAT_BUSY         11  /* an immediate command is in progress */
#define DAT_BLNKCHK      12  /* no data condition or wrong data format */
#define DAT_VLOFLOW      13  /* write complete with data in te buffer */

/*** Additional detail information ***/
/* Detailed information for DAT_NOSENSE */
#define DAT_A_NOSENSE    14  /* no additioal information availabel */
#define DAT_A_FILEMRK    15  /* file mark detected */
#define DAT_A_EOT        16  /* end of tape */
#define DAT_A_BOT        17  /* beginning of tape */

/* Detailed information for DAT_NOTREADY */
#define DAT_A_PROCESS    18  /* in process of becoming ready */
#define DAT_A_INMEDIA    19  /* incompatable media */
#define DAT_A_CLNTAPE    20  /* cleaning cassette installed */
#define DAT_A_NOTAPE     21  /* casette not present */

/* Detailed information for DAT_MEDERR */
#define DAT_A_EXCWRITE   22  /* excessive write */
#define DAT_A_URECREAD   23  /* unrecovered read error */
#define DAT_A_RERR_UF    24  /* can't read tape, unknown format */
#define DAT_A_RERR_INF   25  /* can't read tape, incompatable format */
#define DAT_A_FMRCRUP    26  /* tape format corrupted */
#define DAT_A_SEQPOSERR  27  /* sequential positioning error */
#define DAT_A_LOSTPOS    28  /* lost tape position */

/* Detailed information for DAT_UATTEN */
#define DAT_A_NOTTRAN    29  /* not ready to ready transition */
#define DAT_A_RESET      30  /* power on or reset */
#define DAT_A_TAPECHANGE 31  /* cassette was changed */

/* Detailed information for DAT_BLNKCHK */
#define DAT_A_EOD        32  /* end of data detected */
#define DAT_A_UKNWFMT    33  /* can't read tape, unknown format */


/* These are somewhat confusing.  The actual DAT spec encoding on the tape is
 * 0xBB, 0xEE and 0xAA.  But they are encoded in BCD so any program number detecting code 
 * needs to look at the individual BCD digits.  Just converting them to an int will 
 * get you a valid program number.  The values below are mnemonically similar
 * to their dat encoded counterparts, but not the actual markers.
 */
#define DAT_BOT_PROGNUM     0xBBB
#define DAT_EOT_PROGNUM     0xEEE
#define DAT_INVALID_PROGNUM  0xAAA

/*
 * Handle for playing audio on a DAT drive
 */
typedef struct DATtransport DATTRANSPORT;


typedef enum DATmediaType{
    DATmediaUnknown,
    DATmediaNotTape,
    DATmediaData,
    DATmediaAudio
} DATMEDIATYPE;

typedef enum DATmediaWritePermit {
    DATmediaWriteProtect,
    DATmediaWriteAllow,
    DATmediaWriteUnknown
} DATMEDIAWRITEPERMIT;


typedef struct DATseekinfo {
    int  prognum;
    DMtimecode ptime;    /* program time */
    DMtimecode atime;    /* absolute time */
    DMtimecode rtime;    /* running time */
    unchar seektype;     /* one of the DAT_SEEK_* values */
} DATSEEKINFO;

typedef struct DATaudiodata {
    char audio[DAT_DATASIZE];
} DATAUDIODATA;


/********************************************************************/

/*
 * Open a devscsi device corresponding to a DAT drive.
 * Specifying NULL for devscsi causes the hardware inventory
 * to be consulted for a DAT drive.
 *
 * direction specifies way the device is to be used "r", "w", or "rw".
 */
extern DATTRANSPORT *datOpen(char const *devscsi, char const *direction);

/* Release the opened devscsi DAT drive */
extern void datClose(DATTRANSPORT *);

/*
 * Setup DAT device as an audio device,
 * query the media type, then rewind the tape back to BOT.
 *
 */
extern DMstatus datInit(DATTRANSPORT *);

/* Enable/Disable the eject button */
extern DMstatus datAllowRemoval(DATTRANSPORT *);
extern DMstatus datPreventRemoval(DATTRANSPORT *);

/* Test device unit */
extern DMstatus datTestReady(DATTRANSPORT *);

/* Rewind back to beginning of tape */
extern DMstatus datSeekBOT(DATTRANSPORT *, DMboolean waitForCompletion);

/* Read from tape */
extern int datRead(DATTRANSPORT *, unsigned char *, ulong);

/* Write into tape */
extern int datWrite(DATTRANSPORT *, unsigned char *, ulong);

/* Search the audio tape position */
extern DMstatus datSeekPosition(DATTRANSPORT *, DATSEEKINFO *,
				DMboolean waitForCompletion);

/* Return the audio tape position via firmware query*/
DMstatus datQueryPosition(DATTRANSPORT *, DATSEEKINFO *);

/* Query the audio tape position */
extern DATMEDIATYPE datQueryMediaType(DATTRANSPORT *);
extern DMboolean datQueryMediaWProtected(DATTRANSPORT *);

/* Device operation mode handlers */
extern DMstatus datForceInAudioMode(DATTRANSPORT *);
extern DMstatus datForceInDataMode(DATTRANSPORT *);
extern DMstatus datSaveOrgMode(DATTRANSPORT *);
extern DMstatus datRestoreOrgMode(DATTRANSPORT *);

/* Do eject tape */
extern DMstatus datDoEject(DATTRANSPORT *);

/* Ask device to abort command */
extern DMstatus datAbort(DATTRANSPORT *);

/* Return the error report */
extern DMstatus datWaitForCompletion(DATTRANSPORT *);

extern DMstatus datWriteBOT(DATTRANSPORT *);
extern DMstatus datWriteEOT(DATTRANSPORT *);
extern DMstatus datWriteSilence(DATTRANSPORT *, int);
extern DMstatus datWriteFrame(DATTRANSPORT *, DATAUDIODATA *, int, DMboolean);

extern void datSetIndex(DATTRANSPORT *, int);
extern void datSetProgram(DATTRANSPORT *, int);
extern void datSetTime(DATTRANSPORT *, DATSEEKINFO *);

extern void datIncrIndex(DATTRANSPORT *);
extern void datIncrProgram(DATTRANSPORT *);
extern void datIncTimeCode(DATTRANSPORT *);

extern int  datGetSampleRate(DATTRANSPORT *);
extern void datSetSampleRate(DATTRANSPORT *, int);
extern int  datGetSamplesPerFrame(DATTRANSPORT *);
extern void datSetCopyProhibited(DATTRANSPORT *, DMboolean);
extern DMboolean datGetCopyProhibited(DATTRANSPORT *, DMboolean);
extern void datGetFirmwareRevision(DATTRANSPORT *, int *, int *);

extern void datFixParity(DATTRANSPORT *);

/*
 * Utility functions
 */

/*
 * Convert a frame number to struct DMtimecode
 */
extern void datFrameToTc(unsigned long, DMtimecode *);

/*
 * Convert a struct DMtimecode into the corresonding DAT frame number.
 */
extern unsigned long datTcToFrame(DMtimecode *);

#ifdef __cplusplus
}
#endif
