#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include <sys/mtio.h>

/*
 * dataudio.h
 *
 * Definitions for handling audio data from the DAT drive
 *
 *
 * Copyright 1991, Silicon Graphics, Inc.
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

#define DTDA_DATASIZE		5760
#define DTDA_SUBCODESIZE	(sizeof(struct dtsubcode))
#define DTDA_BLOCKSIZE		(DTDA_DATASIZE + DTDA_SUBCODESIZE)
#define DTDA_DATASIZE48K	DTDA_DATASIZE
#define DTDA_DATASIZE44K 	5292
#define DTDA_DATASIZE32K	3840
#define DTDA_PADSIZE44K		(DTDA_DATASIZE - DTDA_DATASIZE44K)
#define DTDA_PADSIZE32K		(DTDA_DATASIZE - DTDA_DATASIZE32K)
#define DTDA_NUMSAMPS48K	(DTDA_DATASIZE48K/2)
#define DTDA_NUMSAMPS44K	(DTDA_DATASIZE44K/2)
#define DTDA_NUMSAMPS32K	(DTDA_DATASIZE32K/2)

/*
 * Defines for subcodes in main data area id bytes
 *
 * All undefined values in main-id subcode fields are reserved by the
 * DAT Conference.  Certain values as indicated are not to be used in
 * professional use particularly when recording SMPTE time code
 * (pro-rtime).
 */

/* define for fmtid field of main-id and dataid field of sub-id */
#define DT_AUDIO_USE	0

/* defines for the emphasis field */
#define DTM_PREEMPH_OFF	0
#define DTM_PREEMPH_ON	1	/* Not recommended in professional use */

/* defines for the sampfreq field and the freq field of pro-rtime*/
#define DT_FREQ48000	0
#define DT_FREQ44100	1
#define DT_FREQ32000	2

/* defines for the numchans field */
#define DTM_NCHAN_TWO	0
#define DTM_NCHAN_FOUR	1	/* Not permitted in professional use */

/* defines for the quantization field */
#define DTM_QUAN_16_LINEAR	0
#define DTM_QUAN_12_NONLIN	1	/* Not permitted in professional use */

/* defines for the trackpitch field */
#define DTM_PITCH_NORM	0
#define DTM_PITCH_WIDE	1	/* Not permitted in professional use */

/* defines for the copy field */
#define DTM_COPY_PERMITTED	0
#define DTM_COPY_PROHIBITED	2

/* Defines for subcodes in sub data area id bytes */

/* defines for the ctrl-id field */
#define DTS_TOC		1
#define DTS_SHORTENING	2
#define DTS_START	4
#define DTS_PRIORITYID	8

/* defines for interpolation flag field */
#define DTS_LEFT_IPF	0x40
#define DTS_RIGHT_IPF	0x20

/* Defines for sub data area subcode packs */

/* defines for pack id's */
#define	DTP_PTIME	1
#define DTP_ATIME	2
#define DTP_RTIME	3	/* && flag = 0; */
#define DTP_TOC		4
#define DTP_DATE	5
#define DTP_CATALOG	6
#define DTP_ISRC	7
/* professional use packs */
#define DTP_PRO_RTIME	3	/* && flag = 1; */
#define DTP_PRO_BINARY	8

/*
 * Pro. DAT time code recording uses the preceding two pack items.
 * IEC time code (aka SMPTE) or Pro. DIO time code (the channel status data
 * for professional use of IEC 958) is recorded into these two pack items
 * after being converted to Pro. DAT time code format.
 */

/* defines for pro-rtime pack */
#define DT_SP_IECTIMECODE	0
#define DT_SP_DIOSAMPLEADDR	1
#define DT_SP_DIOTODCODE	2

#define DT_XR_30	0
#define DT_XR_2997NDF	1
#define DT_XR_2997DF	2
#define DT_XR_25	3
#define DT_XR_24	4

/* defines for date pack */
#define DT_SUNDAY	1
#define DT_MONDAY	2
#define DT_TUESDAY	3
#define DT_WEDNESDAY	4
#define DT_THURSDAY	5
#define DT_FRIDAY	6
#define DT_SATURDAY	7

#define DT_JANUARY	0x01
#define DT_FEBRUARY	0x02
#define DT_MARCH	0x03
#define DT_APRIL	0x04
#define DT_MAY		0x05
#define DT_JUNE		0x06
#define DT_JULY		0x07
#define DT_AUGUST	0x08
#define DT_SEPTEMBER	0x09
#define DT_OCTOBER	0x10
#define DT_NOVEMBER	0x11
#define DT_DECEMBER	0x12

/*
 * Structures for accessing DAT subcodes
 *
 * All numbers are stored as BCD digits.  A value of 0xA (bit
 * pattern 1010) in any digit means the value is not currently
 * valid.
 */

#define DT_INVALID 0xA

/*
 * The timecode structure looks like this:
 *
 *	struct dttimecode {
 *	    unchar hhi:4, hlo:4;
 *	    unchar mhi:4, mlo:4;
 *	    unchar shi:4, slo:4;
 *	    unchar fhi:4, flo:4;
 *	};
 *
 * This structure is identical to mtaudtimecode in sys/mtio.h so
 */
#define dttimecode mtaudtimecode

struct dtpackedbcd {unchar dhi:4, dlo:4;};

/* generic subcode pack */
struct dtsubcodepack {
    unchar id:4, flag:1, pno1:3, pno2:4, pno3:4;
    unchar packdata[5];
    unchar parity;
};

/* pack for ptime, atime, rtime and pro-rtime */
struct dttimepack {
    unchar id:4, flag:1, pno1:3, pno2:4, pno3:4;
    struct dtpackedbcd index;
    struct dttimecode tc;
    unchar parity;
};

/* pack for pro-rtime */
struct dtprotimepack {
    unchar id:4, flag:1, fill:1, sid:2;
    unchar freq:2, xrate:3, msb:3;
    unchar lsb;
    struct dttimecode tc;
    unchar parity;
};

/* pack for table of contents */
struct dttocpack {
    unchar id:4, flag:1, pno1:3, pno2:4, pno3:4;
    struct dtpackedbcd point;
    struct dttimecode atime;
    unchar parity;
};

/* pack for date */
struct dtdatepack {
    unchar id:4, dayow:4;
    struct dtpackedbcd year;
    struct dtpackedbcd month;
    struct dtpackedbcd day;
    struct dtpackedbcd hour;
    struct dtpackedbcd min;
    struct dtpackedbcd sec;
    unchar parity;
};

/* pack for catalog number */
struct dtcatalogpack {
    unchar id:4, n1:4;
    struct dtpackedbcd nrest[6];
    unchar parity;
};
    
/* pack for ISRC */
struct dtidentpack {
    unchar id:4, point:2, fill:2;
    union {
	struct {
	    unchar country[2];
	    unchar owner[3];
	    unchar fill;
	} point0;
	struct {
	    struct dtpackedbcd year;
	    struct dtpackedbcd serial[3]; /* serial is 1st 5 of the 6 digits */
	    unchar fill[2];
	} point1;
    } data;
    unchar parity;
};

/* pack for pro-binary */
struct dtprobinarypack {
    unchar id:4, fill:2, sid:2;
    union {
	struct bgd {
	    unchar fill;
	    unchar tcbits;
	    struct dtpackedbcd bg[4];
	} bgd;		/* binary group data of IEC time code */
	struct csid {
	    unchar csbytes[6];
	} csid;		/* channel status id of Pro DIO time code */
	struct cod {
	    unchar fill[2];
	    unchar cod[4];
	} cod;		/* alphanumeric origin data of Pro DIO time code */
	struct cdd {
	    unchar fill[1];
	    unchar flags;
	    unchar cdd[4];
	} cdd;		/* alphanumeric channel destination data of Pro DIO */
    } data;
    unchar parity; 
};

/* subcodes in sub data area ID field */
struct dtsubid {
    unchar ctrlid:4, dataid:4;
    unchar pno1:4, numpacks:4;
    unchar pno2:4, pno3:4;
    unchar ipf;
};

/* subcodes in main data area ID field */
struct dtmainid {
    unchar fmtid:2;
    unchar emphasis:2;
    unchar sampfreq:2;
    unchar numchans:2;
    unchar quantization:2;
    unchar trackpitch:2;
    unchar copy:2;
    unchar pack:2;
};

/* subcode data structure */
typedef struct dtsubcode {
    struct dtsubcodepack packs[7];
    struct dtsubid sid;
    struct dtmainid mid;
} DTSUBCODE;

/* and, finally, the complete frame */
typedef struct dtframe {
    char audio[DTDA_DATASIZE];
    struct dtsubcode subcode;
} DTFRAME;

/********************************************************************/

/*
 * Utility functions
 *
 * These functions aid in handling the digital audio data and
 * subcodes from the DAT drive.
 *
 */

/*
 * Convert a frame number to struct timecode
 */

void DTframetotc(unsigned long frame, struct dttimecode *tc);

/*
 * Convert a frame number to mins/secs/frames
 */

void DTframetohmsf(unsigned long frame, int *h,int *m, int *s, int *f);

/*
 * Convert a struct timecode to a displayable ASCII string
 */
void DTtimetoa(char *s, struct dttimecode *tp);

/*
 * Convert an ASCII string to a timecode struct timecode for
 * search requests.  Returns 0 if string isn't a valid timecode.
 */
int DTatotime(struct dttimecode *tp, const char *s);

/*
 * Convert an ASCII string to hmsf fields.
 * Returns 0 if string isn't a valid timecode.
 */
int DTatohmsf( const char *loc, int *h, int *m, int *s, int *f);

/*
 * Increment a time code value
 */
void DTinctime(struct dttimecode *tc);

/*
 * Convert an array of 6-bit values to an ASCII string.
 * This function returns the number of characters converted.
 */
int DTsbtoa( char *s, const unchar *sixbit, int count );

/*
 * Convert an hours, minutes, seconds and frames quadruple into
 * the corresponding DAT frame number.
 */
unsigned long DThmsftoframe(int h, int m, int s, int f);

/*
 * Convert a struct dttimecode into the corresonding DAT frame number.
 */
unsigned long DTtctoframe(struct dttimecode* tc);

/*
 * Fill in a datepack with the current date and time.
 */
void DTsetdate(struct dtdatepack*);

/*
 * Return a dtdatepack filled in with the current date and time.
 */
struct dtdatepack *DTsetdatepack();

/*
 * Check a timecode structure for validity.
 */
int DTtcvalid(struct dttimecode* tc);

/*
 * Convert a program number expressed as 3 bcd digits to a decimal
 */
int DTpnotodec(unchar pno1, unchar pno2, unchar pno3);

/*
 * Convert 2 bcd digits to decimal
 *
 * return 100 if either digit invalid. 
 */
int DTbcdtodec(int d1, int d2);	

/*
 * Digital Audio Tape Data Parser Functions
 *
 * These functions aid in parsing the digital audio data that is
 * read from a DAT
 *
 */

/*
 * Identifiers for the different types of callbacks from the
 * parser.
 */
typedef enum dtdatatypes {
    dt_audio, dt_pnum, dt_index, dt_ptime, dt_atime, dt_rtime,
    dt_prortime, dt_mainid, dt_sampfreq, dt_toc, dt_date, dt_catalog,
    dt_ident, dt_probinary
} DTDATATYPES;

/*
 * structure to unpack program and index numbers into and pass them
 * to callback
 */
typedef struct dtprognum {
    int value;			/* Program number converted to integer */
    struct {
	unchar d1, d2, d3;
    } bcd;			/* Original BCD digits */
} DTPROGNUM;

/*
 * structure to unpack an ISRC pack into and pass it to a callback
 */
typedef struct dtident {
    unchar country[2];
    unchar owner[3];
    unchar year[2];
    unchar serial[5];
} DTIDENT;

/*
 * Handle for a dtparser structure
 */
typedef struct dtparser DTPARSER;

typedef void (*DTCALLBACKFUNC)(void*, enum dtdatatypes, void*);

/*
 * Make a new parser
 */
DTPARSER *DTcreateparser();

/*
 * Delete a parser and free the memory
 */
void DTdeleteparser(DTPARSER *);

/*
 * Reset only the position fields of the parser.  
 * This should be called anytime the tape is repositioned.
 */
void DTresetparserpos(DTPARSER *);

/*
 * Reset a parser.  This should be called after a disc has been ejected and
 * a new one loaded.
 */
void DTresetparser(DTPARSER *);

/*
 * Add or remove a callback from the parser for one of the data items from
 * the enumerated list of dtdatatypes.
 */
#define DTsetcallback	DTaddcallback	/* remove 2 releases after 4.1 */
void DTaddcallback(DTPARSER *dtp, DTDATATYPES type,
                   DTCALLBACKFUNC func, void *arg);
void DTremovecallback(DTPARSER *dtp, DTDATATYPES type);

/*
 * Parse a frame of digital audio data.  DTparseframe calls each established
 * callback passing it the data item it is expecting.
 */
int DTparseframe(DTPARSER *dtp, DTFRAME *dtfp);

#ifdef __cplusplus
}
#endif
