#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include <dmedia/dmedia.h>
#include <dmedia/dm_timecode.h>

/*
 * dataudio_private.h
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


#ifdef DEBUG
#define DTDBG(x) {if (datdbg) {x;}}
#define PRINTSENSE(dsp) { \
    int i;\
    if (STATUS(dsp) == STA_CHECK) {\
        for (i = 0; i < DAT_SENSELEN; i++)\
            fprintf( stderr, "%02x ", SENSEBUF(dsp)[i] );\
        fprintf( stderr, "\n" );\
    }}
static int cddbg = 1;
#else
#define DTDBG(x)
#define PRINTSENSE(dsp)
#endif

/*
 * Defines for subcodes in main data area id bytes
 *
 * All undefined values in main-id subcode fields are reserved by the
 * DAT Conference.  Certain values as indicated are not to be used in
 * professional use particularly when recording SMPTE time code
 * (pro-rtime).
 */

/* define for fmtid field of main-id and dataid field of sub-id */
#define DAT_AUDIO_USE      0

/* defines for the emphasis field */
#define DATM_PREEMPH_OFF         0
#define DATM_PREEMPH_ON          1  /* Not recommended in professional use */

/* defines for the sampfreq field and the freq field of pro-rtime*/
#define DAT_FREQ48000            0
#define DAT_FREQ44100            1
#define DAT_FREQ32000            2

/* defines for the numchans field */
#define DAT_MAIN_NCHAN_TWO       0
#define DAT_MAIN_NCHAN_FOUR      1  /* Not permitted in professional use */

/* defines for the quantization field */
#define DAT_MAIN_QUAN_16_LINEAR  0
#define DAT_MAIN_QUAN_12_NONLIN  1  /* Not permitted in professional use */

/* defines for the trackpitch field */
#define DAT_MAIN_PITCH_NORM      0
#define DAT_MAIN_PITCH_WIDE      1  /* Not permitted in professional use */

/* defines for the copy field */
#define DAT_MAIN_COPY_PERMITTED  0
#define DAT_MAIN_COPY_PROHIBITED 2

/* Defines for subcodes in sub data area id bytes */

/* defines for the ctrl-id field */
#define DAT_SUB_TOC              1
#define DAT_SUB_SHORTENING       2
#define DAT_SUB_START            4
#define DAT_SUB_PRIORITYID       8

/* defines for interpolation flag field */
#define DAT_SUB_LEFT_IPF      0x40
#define DAT_SUB_RIGHT_IPF     0x20

/* Defines for sub data area subcode packs */

/* defines for pack id's */
#define DAT_PACK_PTIME           1
#define DAT_PACK_ATIME           2
#define DAT_PACK_RTIME           3  /* && flag = 0; */
#define DAT_PACK_TOC             4
#define DAT_PACK_DATE            5
#define DAT_PACK_CATALOG         6
#define DAT_PACK_ISRC            7
/* professional use packs */
#define DAT_PACK_PRO_RTIME       3  /* && flag = 1; */
#define DAT_PACK_PRO_BINARY      8

/*
 * Pro. DAT time code recording uses the preceding two pack items.
 * IEC time code (aka SMPTE) or Pro. DIO time code (the channel status data
 * for professional use of IEC 958) is recorded into these two pack items
 * after being converted to Pro. DAT time code format.
 */

/* defines for pro-rtime pack */
#define DAT_SP_IECTIMECODE       0
#define DAT_SP_DIOSAMPLEADDR     1
#define DAT_SP_DIOTODCODE        2

/* defines for date pack */
#define DAT_SUNDAY               1
#define DAT_MONDAY               2
#define DAT_TUESDAY              3
#define DAT_WEDNESDAY            4
#define DAT_THURSDAY             5
#define DAT_FRIDAY               6
#define DAT_SATURDAY             7

#define DAT_JANUARY           0x01
#define DAT_FEBRUARY          0x02
#define DAT_MARCH             0x03
#define DAT_APRIL             0x04
#define DAT_MAY               0x05
#define DAT_JUNE              0x06
#define DAT_JULY              0x07
#define DAT_AUGUST            0x08
#define DAT_SEPTEMBER         0x09
#define DAT_OCTOBER           0x10
#define DAT_NOVEMBER          0x11
#define DAT_DECEMBER          0x12


/*
 * Structures for accessing DAT subcodes
 *
 * All numbers are stored as BCD digits.  A value of 0xA (bit
 * pattern 1010) in any digit means the value is not currently
 * valid.
 */
#define DAT_INVALID_DIGIT        0xA
#define DAT_EOT_DIGIT            0xE
#define DAT_BOT_DIGIT            0xB

/*
 * This structure is identical to mtaudtimecode in sys/mtio.h so
 */
struct DATtimecode {
    unchar hhi:4, hlo:4;  /* hours */
    unchar mhi:4, mlo:4;  /* minutes */
    unchar shi:4, slo:4;  /* seconds */
    unchar fhi:4, flo:4;  /* frame # (finer grain than seconds) */
};

struct DATpackedbcd {unchar dhi:4, dlo:4;};

/* generic subcode pack */
typedef struct DATsubcodepack {
    unchar id:4, flag:1, pno1:3, pno2:4, pno3:4;
    unchar packdata[5];
    unchar parity;
} DATSUBCODEPACk;

/* pack for ptime, atime, rtime and pro-rtime */
struct DATtimepack {
    unchar id:4, flag:1, pno1:3, pno2:4, pno3:4;
    struct DATpackedbcd index;
    struct DATtimecode tc;
    unchar parity;
};

/* pack for pro-rtime */
struct DATprotimepack {
    unchar id:4, flag:1, fill:1, sid:2;
    unchar freq:2, xrate:3, msb:3;
    unchar lsb;
    struct DATtimecode tc;
    unchar parity;
};

/* pack for table of contents */
struct DATtocpack {
    unchar id:4, flag:1, pno1:3, pno2:4, pno3:4;
    struct DATpackedbcd point;
    struct DATtimecode atime;
    unchar parity;
};

/* pack for date */
struct DATdatepack {
    unchar id:4, dayow:4;
    struct DATpackedbcd year;
    struct DATpackedbcd month;
    struct DATpackedbcd day;
    struct DATpackedbcd hour;
    struct DATpackedbcd min;
    struct DATpackedbcd sec;
    unchar parity;
};

/* pack for catalog number */
struct DATcatalogpack {
    unchar id:4, n1:4;
    struct DATpackedbcd nrest[6];
    unchar parity;
};
    
/* pack for ISRC */
struct DATidentpack {
    unchar id:4, point:2, fill:2;
    union {
    struct {
        unchar country[2];
        unchar owner[3];
        unchar fill;
    } point0;
    struct {
        struct DATpackedbcd year;
        struct DATpackedbcd serial[3]; /* serial is 1st 5 of the 6 digits */
        unchar fill[2];
    } point1;
    } data;
    unchar parity;
};

/* pack for pro-binary */
struct DATprobinarypack {
    unchar id:4, fill:2, sid:2;
    union {
    struct bgd {
        unchar fill;
        unchar tcbits;
        struct DATpackedbcd bg[4];
    } bgd;        /* binary group data of IEC time code */
    struct csid {
        unchar csbytes[6];
    } csid;        /* channel status id of Pro DIO time code */
    struct cod {
        unchar fill[2];
        unchar cod[4];
    } cod;        /* alphanumeric origin data of Pro DIO time code */
    struct cdd {
        unchar fill[1];
        unchar flags;
        unchar cdd[4];
    } cdd;        /* alphanumeric channel destination data of Pro DIO */
    } data;
    unchar parity; 
};

/* subcodes in sub data area ID field */
struct DATsubid {
    unchar ctrlid:4, dataid:4;
    unchar pno1:4, numpacks:4;
    unchar pno2:4, pno3:4;
    unchar ipf;
};

/* subcodes in main data area ID field */
struct DATmainid {
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
typedef struct DATsubcode {
    struct DATsubcodepack packs[7];
    struct DATsubid sid;
    struct DATmainid mid;
} DATSUBCODE;

/* the complete frame structure */
typedef struct DATframe {
    char audio[DAT_DATASIZE];
    struct DATsubcode subcode;
} DATFRAME;

/*
 * private data structure representing a dat player and its state
 */
struct DATtransport {
    unsigned char        detail;      /* Addition sense and code qualifier */
    unsigned char        dattype;     /* Type of the DAT drive */
    int                  major;       /* firmware major number */
    int                  minor;       /* firmware minor number */
    DATMEDIATYPE         mediatype;   /* DAT tape formatted type */
    DATMEDIAWRITEPERMIT  mediawrp;    /* DAT tape write protection bit */
    struct dsreq        *dsp;         /* Struct for doing SCSI requests */
    int                  excl_id;     /* Exclusive use id from mediad */
    int                  state;       /* State of player */
    char                *dev;         /* name of dev scsi device */
#ifdef LATER
    DATFRAME             indatframe;  /* a template frame */
    DATFRAME             outdatframe; /* a template frame */
#endif
};

typedef struct DATseekstruct {
    unchar zero1:4, pno1:4; /* 3 BCD digits giving program number the zero */
    unchar zero2:4, pno2:4; /* fields should always be 0, or 0xA, when the */
    unchar zero3:4, pno3:4; /* pno field is also 0xA, indicating not valid */
    unchar indexhi:4, index:4;   /* index number within program; hi is the
		              most significant BCD digit, index the least. */
    struct DATtimecode ptime;    /* program time */
    struct DATtimecode atime;    /* absolute time */
    struct DATtimecode rtime;    /* running time */
    unchar seektype;             /* one of the DAT_SEEK_* values */
    unchar cfuture[11];          /* future expansion */
} DATSEEKSTRUCT;


/* internal global data structure */
extern DATFRAME indatframe, outdatframe;

/*
 * Convert a program number expressed as 3 bcd digits to a decimal
 */
extern int datPnoToDec(unchar pno1, unchar pno2, unchar pno3);

/*
 * Convert a 3 bcd digits to a decimal into program number
 */
extern void datDecToPno(int , unchar *, unchar *, unchar *);

/*
 * Increment a time code value
 */
void datIncTime(struct DATtimecode *tc);

extern void datDMtimeToTime(DMtimecode *, struct DATtimecode *);

extern void datTimeToDMtime(struct DATtimecode *, DMtimecode *);

extern void resetTimeCodes(DATTRANSPORT *);

extern DMstatus dataTranslateInfoToStruct(DATSEEKINFO *, DATSEEKSTRUCT *);

extern DMstatus dataTranslateStructToInfo(DATSEEKSTRUCT *, DATSEEKINFO *);

extern DMstatus seekToLastRead(DATTRANSPORT *, DATSEEKINFO *);

extern DMstatus datWriteRawFrame(DATTRANSPORT *, DATFRAME *);

/*
 * Return the audio tape position via reading the subcodes
 */
extern DMstatus datReadPosition(DATTRANSPORT*, DATSEEKINFO*, DMboolean, DMboolean, DATFRAME*);

/*
 * Check a timecode structure for validity.
 */
extern int datTcValid(struct DATtimecode* tc);


/***** followiing functions may be terminated later *******/
/*
 * Convert a struct timecode to a displayable ASCII string
 */
void datTimeToA(char *s, struct DATtimecode *tp);

/*
 * Convert an ASCII string to a timecode struct timecode for
 * search requests.  Returns 0 if string isn't a valid timecode.
 */
int datAToTime(struct DATtimecode *tp, const char *s);

/*
 * Fill in a datepack with the current date and time.
 */
void datSetDate(struct DATdatepack*);


/*
 * Convert an ASCII string to hmsf fields.
 * Returns 0 if string isn't a valid timecode.
 */
int datAToHmsf( const char *loc, int *h, int *m, int *s, int *f);

/*
 * Return a dtdatepack filled in with the current date and time.
 */
struct DATdatepack *datSetDatePack();

/*
 * Convert 2 bcd digits to decimal
 *
 * return 100 if either digit invalid.
 */
int datBcdToDec(int d1, int d2);



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
} DATDATATYPES;

/*
 * structure to unpack program and index numbers into and pass them
 * to callback
 */
typedef struct DATprognum {
    int value;            /* Program number converted to integer */
    struct {
    unchar d1, d2, d3;
    } bcd;            /* Original BCD digits */
} DATPROGNUM;

/*
 * structure to unpack an ISRC pack into and pass it to a callback
 */
typedef struct DATident {
    unchar country[2];
    unchar owner[3];
    unchar year[2];
    unchar serial[5];
} DATIDENT;


#ifdef __cplusplus
}
#endif
