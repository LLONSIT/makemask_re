#ifndef __AUDIO_H__
#define __AUDIO_H__ 

/*****************************************************************************
 *
 * SGI audio library 
 *
 * audio.h
 *	header file for use with /usr/lib/libaudio.so
 *
 * Copyright 1991, 1992, 1993 Silicon Graphics, Inc.
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
 *
 ****************************************************************************/
#ident "$Revision: 1.103 $"

#include <sys/time.h>

#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C" {
#endif

/*
 * we define a range of values which resources cannot have.
 * in this range we place the parameters which are not also resource IDs
 * and types.
 */

#define AL_MAX_RESOURCE_ID	0x0fffffff
#define AL_PARAM_BIT		0x10000000
#define AL_TYPE_BIT		0x20000000


/*
 * audio sample numeric format:
 *  
 * the audio library represents all audio data using linear pulse
 *   code modulation (PCM) format
 * linear PCM values are represented either as signed integers (the
 *   default), or as floating-point numbers
 */
#define AL_SAMPFMT_TWOSCOMP   1
#define AL_SAMPFMT_FLOAT      32
#define AL_SAMPFMT_DOUBLE     64
#define AL_SAMPFMT_AES_CHANNEL_STATUS	(AL_PARAM_BIT | 47)
#define AL_SAMPFMT_AES_USER		(AL_PARAM_BIT | 48)
#define AL_SAMPFMT_AES_VALIDITY		(AL_PARAM_BIT | 49)
#define AL_SAMPFMT_ADAT_USER0		(AL_PARAM_BIT | 50)
#define AL_SAMPFMT_ADAT_USER1		(AL_PARAM_BIT | 51)
#define AL_SAMPFMT_ADAT_USER2		(AL_PARAM_BIT | 52)
#define AL_SAMPFMT_ADAT_USER3		(AL_PARAM_BIT | 53)


/*
 * audio sample resolution
 *    8-bit  signed integer samples are stored in signed characters
 *    16-bit signed integer samples are stored in signed shorts
 *    24-bit signed integer samples are sign extended into signed ints
 *
 * single and double precision floating-point numbers can
 *   represent more than 24-bits of dynamic range, however 24-bit resolution
 *   is the maximum supported by the audio I/O system
 */
#define AL_SAMPLE_8	 1
#define AL_SAMPLE_16	 2
#define AL_SAMPLE_24	 4

/*
 * number of channels in audio port configuration
 */
#define AL_MONO		1
#define AL_STEREO	2
#define AL_4CHANNEL	4

/*
 * global input source: the source you select (by calling ALsetparams) is
 * the source that supplies all open input ports in the system
 */
#define AL_INPUT_LINE		0
#define AL_INPUT_MIC		1
#define AL_INPUT_DIGITAL	2

/*
 * monitor control
 */
#define AL_MONITOR_OFF 0
#define AL_MONITOR_ON  1

/*
 * mute control
 */
#define AL_SPEAKER_MUTE_OFF 0
#define AL_SPEAKER_MUTE_ON  1

/*
 * port style
 */
#define AL_PORTSTYLE_SERIAL 0
#define AL_PORTSTYLE_DIRECT 1

/* error information */
#define AL_ERROR_NUMBER       0
#define AL_ERROR_TYPE         1
#define AL_ERROR_LOCATION_LSP 2
#define AL_ERROR_LOCATION_MSP 3
#define AL_ERROR_LENGTH       4

/* error types ... so far */
#define AL_ERROR_INPUT_OVERFLOW    0
#define AL_ERROR_OUTPUT_UNDERFLOW  1

typedef struct _ALconfig  *ALconfig;   /* audio port config handle */
typedef struct _ALport *ALport;        /* audio port handle        */
typedef int	ALresource;
typedef long long ALfixed;		/* AL 64-bit (32.32) fixed-point */

typedef union {
    int         i;	    /* 32-bit integer values */
    long long   ll;	    /* 64-bit integer and fixed-point values */
    void*       ptr;	    /* pointer values */
} ALvalue;

typedef struct {
    int     param;	    /* parameter */
    int	    dummy;	    /* for alignment */
    ALvalue value;	    /* value */
    short   sizeIn;	    /* size */
    short   size2In;
    short   sizeOut;	    /* size */
    short   size2Out;
} ALpv;

typedef struct {
    int resource;		/* the resource */
    int param;			/* the parameter */
    int valueType;		/* type of the whole value (scalar,vector,set...) */
    int elementType;		/* type of each element (enum, fixed, resource ...) */
    int maxElems;		/* maximum number of elements */
    int maxElems2;		/* maximum number of elements (2nd dimension) */
    char name[32];		/* name of the parameter */
    ALvalue initial;		/* initial value */
    ALvalue min;		/* minimum value (range parameters only) */
    ALvalue max;		/* maximum value (range parameters only) */
    ALvalue minDelta;		/* minimum delta between values (range parameters only) */
    ALvalue maxDelta;		/* maximum delta between values (range parameters only) */
    int specialVals;		/* special values not between min & max (range parms only) */
    int operations;		/* bitmask of supported operations (see _OP #defines) */
    int space[15];		/* extra room */
} ALparamInfo;

/*
 * audio port configuration
 * these routines allow you to:
 *   - obtain, release  a port config struct handle
 *   - initialize the configuration of an audio port before you open it
 *   - obtain configuration parameters for an open audio port
 *   - reconfigure certain parameters for an open port (see man page
 *     for ALsetconfig)
 */
extern ALconfig	    alNewConfig(void);			/* 0 for failure */
extern int	    alFreeConfig(ALconfig);		/* < 0 for failure */
extern int	    alSetConfig(ALport, ALconfig);	/* < 0 for failure */
extern ALconfig	    alGetConfig(ALport);		/* 0 for failure */
extern int	    alSetQueueSize(ALconfig, int);	/* < 0 for failure */
extern int	    alGetQueueSize(ALconfig);		/* < 0 for failure */
extern int	    alSetWidth(ALconfig, int);		/* < 0 for failure */
extern int	    alGetWidth(ALconfig);		/* < 0 for failure */
extern int	    alSetSampFmt(ALconfig, int);	/* < 0 for failure */
extern int	    alGetSampFmt(ALconfig);		/* < 0 for failure */
extern int	    alSetLimiting(ALconfig, int);	/* < 0 for failure */
extern int	    alGetLimiting(ALconfig);		/* < 0 for failure */
extern int	    alSetChannels(ALconfig, int);	/* < 0 for failure */
extern int	    alGetChannels(ALconfig);		/* < 0 for failure */

extern int	    alSetFloatMax(ALconfig, double);	/* < 0 for failure */
extern double	    alGetFloatMax(ALconfig);		/* = 0 for failure */

extern int      alSetDevice(ALconfig, int);         /* < 0 for failure */	
extern int      alGetDevice(ALconfig);              /* < 0 for failure */	

extern int	   alGetResource(ALport);		/* 0 for failure */

/*
 * audio port manipulation
 * these routines allow you to:
 *    - open, close an audio port
 *    - obtain information about the dynamic state of the sample queue for
 *      an open port
 *    - read samples from an input port / write samples to an output port
 *    - obtain a file descriptor for an audio port (for use with the 
 *      poll and select system calls)
 */
extern ALport	alOpenPort(const char* /*name*/, const char* /*direction*/, 
                                                              ALconfig);
						/* 0 for failure */
extern int	alClosePort(ALport);		/* < 0 for failure */
extern int 	alGetFD(ALport);		/* < 0 for failure */
extern int	alGetFilled(ALport);		/* < 0 for failure */
extern int	alGetFillable(ALport);		/* < 0 for failure */
extern int	alReadFrames(ALport, void* /*buf*/, int /*count*/);
						/* < 0 for failure */
extern int	alWriteFrames(ALport, void* /*buf*/, int /*count*/);
						/* < 0 for failure */
extern int	alReadBuffers(ALport, void** /*buf*/, int *, int /*count*/);
						/* < 0 for failure */
extern int	alWriteBuffers(ALport, void** /*buf*/, int *, int /*count*/);
						/* < 0 for failure */
extern int	alDiscardFrames(ALport, int /*count*/);
						/* < 0 for failure */
extern int	alZeroFrames(ALport, int /*count*/);
						/* < 0 for failure */
extern int  	alSetFillPoint(ALport, int);	/* < 0 for failure */
extern int	alGetFillPoint(ALport);		/* < 0 for failure */

extern int  	alGetFrameNumber(ALport, stamp_t *);	
extern int	alGetFrameTime(ALport, stamp_t *, stamp_t *);		

extern double	alFixedToDouble(ALfixed);
extern ALfixed	alDoubleToFixed(double);

#define	alFixedToInt(x) ((int)((x) >> 32))
#define alIntToFixed(x) (((ALfixed)(x)) << 32)

extern int	alConnect(int, int, ALpv *, int);
extern int	alDisconnect(int);

/*
 * global hardware device and system configuration
 */
#define AL_DEFAULT_DEVICE	1  /* audio I/O device */

extern int	alGetParams(int, ALpv *, int);   /* < 0 for failure */
extern int	alSetParams(int, ALpv *, int);   /* < 0 for failure */

extern int	alQueryValues(int res, int param, ALvalue *set, int setsize, 
    ALpv *quals, int qualsize);

extern int	alGetParamInfo(int res, int param, ALparamInfo *pinfo);

extern int	alGetResourceByName(int res, char *name, int type);
extern int	alIsSubtype(int type, int subtype);

/*
 * error handler: you can replace the default error handler with your
 *     own routine by calling ALseterrorhandler
 */
typedef void (*ALerrfunc)(long,const char*,...);
extern ALerrfunc alSetErrorHandler(ALerrfunc efunc);

extern char *alGetErrorString(int error);

#define AL_PRINT_ERRORS	((ALerrfunc)1)
#define AL_NO_ERRORS	((ALerrfunc)0)
#define AL_MAX_PBUFSIZE		64	/* maximum size for parameter buffer */
#define AL_MAX_STRLEN		32	/* maximum length for an AL string */

/*
 * Element types
 */
 
#define AL_NO_ELEM		0
#define AL_INT32_ELEM		0x10
#define AL_RESOURCE_ELEM	(AL_INT32_ELEM | 0x1)
#define AL_ENUM_ELEM		(AL_INT32_ELEM | 0x2)
#define AL_INT64_ELEM		0x20
#define AL_FIXED_ELEM		(AL_INT64_ELEM | 0x1)
#define AL_PTR_ELEM		0x40
#define AL_CHAR_ELEM		0x80

/*
 * Value types
 */
#define AL_NO_VAL		0
#define AL_VECTOR_VAL		1
#define AL_SCALAR_VAL		2
#define AL_SET_VAL		3
#define AL_STRING_VAL		4
#define AL_MATRIX_VAL		5


/*
 * new-style parameters. Parameters share namespace with resources, since
 * some of the parameter names can actually be used as resource IDs.
 */

#define AL_RESOURCE		(AL_PARAM_BIT | 1)
#define AL_INTERFACE		(AL_PARAM_BIT | 2)
#define AL_CLOCK_GEN		(AL_PARAM_BIT | 3)
#define AL_CHANNELS		(AL_PARAM_BIT | 4)
#define AL_PORT_COUNT		(AL_PARAM_BIT | 5)
#define AL_MAX_PORTS		(AL_PARAM_BIT | 6)
#define AL_UNUSED_PORTS		(AL_PARAM_BIT | 7)
#define AL_MAX_SETSIZE		(AL_PARAM_BIT | 8)
#define AL_DEFAULT_INPUT	9
#define AL_DEFAULT_OUTPUT	10
#define AL_SYSTEM		11
#define AL_DEVICES		(AL_PARAM_BIT | 12)
#define AL_RATE			(AL_PARAM_BIT | 13)
#define AL_RATE_FRACTION_N	(AL_PARAM_BIT | 14)
#define AL_RATE_FRACTION_D	(AL_PARAM_BIT | 15)
#define AL_JITTER		(AL_PARAM_BIT | 16)
#define AL_MASTER_CLOCK		(AL_PARAM_BIT | 17)
#define AL_TYPE			(AL_PARAM_BIT | 18)
#define AL_NAME			(AL_PARAM_BIT | 19)
#define AL_PARAMS		(AL_PARAM_BIT | 20)
#define AL_NO_OP		(AL_PARAM_BIT | 21)
#define AL_SOURCE		(AL_PARAM_BIT | 22)
#define AL_DEST			(AL_PARAM_BIT | 23)
#define AL_CONNECTIONS		(AL_PARAM_BIT | 24)
#define AL_GAIN			(AL_PARAM_BIT | 25)
#define AL_PORTS		(AL_PARAM_BIT | 26)
#define AL_GAIN_REF		(AL_PARAM_BIT | 27)
#define AL_WORDSIZE		(AL_PARAM_BIT | 28)
#define AL_MUTE			(AL_PARAM_BIT | 29)
#define AL_SUBSYSTEM		(AL_PARAM_BIT | 30)
#define AL_LABEL		(AL_PARAM_BIT | 31)
#define AL_INTERVAL		(AL_PARAM_BIT | 32)
/* values 33-35 reserved */
#define AL_SHORT_NAME		(AL_PARAM_BIT | 36)

#ifndef NO_EVENTS

#define AL_CONNECT              (AL_PARAM_BIT | 37)
#define AL_DISCONNECT           (AL_PARAM_BIT | 38)

#endif

#define AL_ASSOCIATE		(AL_PARAM_BIT | 39)
#define AL_LOCKED		(AL_PARAM_BIT | 40)
#define AL_SUBSYSTEMS		(AL_PARAM_BIT | 41)
#define AL_VIDEO_SYNC		(AL_PARAM_BIT | 42)
#define AL_VERSION		(AL_PARAM_BIT | 43)

#define AL_SUBCODE_FRAMESIZE    (AL_PARAM_BIT | 44)
#define AL_SUBCODE_FORMAT       (AL_PARAM_BIT | 45)
#define AL_SUBCODE_CHANNELS     (AL_PARAM_BIT | 46)

#define AL_AES_CHANNEL_STATUS	(AL_PARAM_BIT | 47)
#define AL_AES_USER		(AL_PARAM_BIT | 48)
#define AL_AES_VALIDITY		(AL_PARAM_BIT | 49)
#define AL_ADAT_USER0		(AL_PARAM_BIT | 50)
#define AL_ADAT_USER1		(AL_PARAM_BIT | 51)
#define AL_ADAT_USER2		(AL_PARAM_BIT | 52)
#define AL_ADAT_USER3		(AL_PARAM_BIT | 53)

/*
 * Resource types. The ordering of the types has nothing to do with which
 * are subtypes of which.
 */
#define AL_RESOURCE_TYPE	(AL_TYPE_BIT | 0)
#define AL_SYSTEM_TYPE		(AL_TYPE_BIT | 1)
#define AL_DEVICE_TYPE		(AL_TYPE_BIT | 2)
#define AL_PORT_TYPE		(AL_TYPE_BIT | 3)
#define AL_CLOCKGEN_TYPE	(AL_TYPE_BIT | 4)
#define AL_SUBSYSTEM_TYPE	(AL_TYPE_BIT | 5)
#define AL_CONNECTION_TYPE	(AL_TYPE_BIT | 6)
#define AL_INTERFACE_TYPE	(AL_TYPE_BIT | 7)
#define AL_HRB_TYPE		(AL_TYPE_BIT | 8)
#define AL_MCLK_TYPE		(AL_TYPE_BIT | 9)
#define AL_CRYSTAL_MCLK_TYPE	(AL_TYPE_BIT | 10)
#define AL_AES_MCLK_TYPE	(AL_TYPE_BIT | 11)
#define AL_ADAT_MCLK_TYPE	(AL_TYPE_BIT | 12)
#define AL_MIC_IF_TYPE		(AL_TYPE_BIT | 13)
#define AL_LINE_IF_TYPE		(AL_TYPE_BIT | 14)
#define AL_AES_IF_TYPE		(AL_TYPE_BIT | 15)
#define AL_ADAT_IF_TYPE		(AL_TYPE_BIT | 16)
#define AL_SPEAKER_IF_TYPE	(AL_TYPE_BIT | 17)
#define AL_FIXED_MCLK_TYPE	(AL_TYPE_BIT | 18)
#define AL_VARIABLE_MCLK_TYPE	(AL_TYPE_BIT | 19)
#define AL_ANALOG_IF_TYPE	(AL_TYPE_BIT | 20)
#define AL_DIGITAL_IF_TYPE	(AL_TYPE_BIT | 21)
#define AL_VIDEO_MCLK_TYPE	(AL_TYPE_BIT | 22)
#define AL_INPUT_PORT_TYPE	(AL_TYPE_BIT | 23)
#define AL_OUTPUT_PORT_TYPE	(AL_TYPE_BIT | 24)
#define AL_INPUT_HRB_TYPE	(AL_TYPE_BIT | 25)
#define AL_OUTPUT_HRB_TYPE	(AL_TYPE_BIT | 26)
#define AL_INPUT_DEVICE_TYPE	(AL_TYPE_BIT | 27)
#define AL_OUTPUT_DEVICE_TYPE	(AL_TYPE_BIT | 28)
#define AL_A2_SUBSYS_TYPE       (AL_TYPE_BIT | 29)
#define AL_RAD_SUBSYS_TYPE      (AL_TYPE_BIT | 30)
#define AL_A3_SUBSYS_TYPE       (AL_TYPE_BIT | 31)
#define AL_TEST_IF_TYPE         (AL_TYPE_BIT | 32)
#define AL_SPEAKER_PLUS_LINE_IF_TYPE	(AL_TYPE_BIT | 33)
#define AL_A1_SUBSYS_TYPE       (AL_TYPE_BIT | 34)
#define AL_DIVO_SUBSYS_TYPE	(AL_TYPE_BIT | 35)
#define AL_SMPTE272M_IF_TYPE	(AL_TYPE_BIT | 36)
#define AL_OPTICAL_IF_TYPE	(AL_TYPE_BIT | 37)
#define AL_USBAUDIO_SUBSYS_TYPE	(AL_TYPE_BIT | 38)
#define AL_MAD_SUBSYS_TYPE	(AL_TYPE_BIT | 39)

#define AL_NULL_RESOURCE	2	/* general null resource */

#define AL_ALL_INTERFACES	3	/* all interfaces */
#define AL_NULL_INTERFACE	4	/* no interface */

#define AL_GET_OP         0x1
#define AL_SET_OP         0x2
#define AL_QUERY_OP       0x4
#define AL_EVENT_OP       0x8

/*
 * error values for parameter/values
 */
#define AL_INVALID_PARAM	-1	    /* parameter unrecognized */
#define AL_INVALID_VALUE	-2	    /* value unsupported */

/*
 * Gain reference values
 */ 
#define AL_REF_NONE		0
#define AL_REF_0DBV		1

/*
 * Video sync values
 */
#define AL_VID_EXTERNAL	0
#define AL_VID_INTERNAL	1

/*
 * Special fixed-point values.
 */
#define AL_NO_CHANGE	0xffffffffffffffffLL	/* special cookie */
#define AL_NEG_INFINITY	0x8000000000000000LL	/* special "negative infinity" cookie */

/*
 * Bits in "special_values" which indicate the special values supported.
 */
#define AL_NO_CHANGE_BIT    0x1
#define AL_NEG_INFINITY_BIT 0x2
#define AL_GLOBAL_MUTE_BIT  0x4

/*
 * error codes
 */
#define AL_BAD_NOT_IMPLEMENTED	0 /* not implemented yet */
#define AL_BAD_PORT		1 /* tried to use an invalid port */
#define AL_BAD_CONFIG		2 /* tried to use an invalid configuration */
#define AL_BAD_DEVICE		3 /* tried to use an invalid device */
#define AL_BAD_RESOURCE		3 /* tried to use an invalid resource */
#define AL_BAD_DEVICE_ACCESS	4 /* unable to access the device */
#define AL_BAD_DIRECTION	5 /* illegal direction given for port */
#define AL_BAD_OUT_OF_MEM	6 /* operation has run out of memory */
#define AL_BAD_NO_PORTS		7 /* not able to allocate a port */
#define AL_BAD_WIDTH		8 /* invalid sample width given */
#define AL_BAD_ILLEGAL_STATE	9 /* an illegal state has occurred */
#define AL_BAD_QSIZE		10 /* attempt to set an invalid queue size */
#define AL_BAD_FILLPOINT	11 /* attempt to set an invalid fillpoint */
#define AL_BAD_BUFFER_NULL	12 /* null buffer pointer */
#define AL_BAD_COUNT_NEG	13 /* negative count */
#define AL_BAD_PVBUFFER		14 /* param/val buffer doesn't make sense */
#define AL_BAD_BUFFERLENGTH_NEG	15 /* negative buffer length */
#define AL_BAD_BUFFERLENGTH_ODD	16 /* odd length parameter/value buffer */
#define AL_BAD_CHANNELS		17 /* invalid channel specifier */
#define AL_BAD_PARAM		18 /* invalid parameter */
#define AL_BAD_SAMPFMT          19 /* attempt to set invalid sample format */
#define AL_BAD_RATE             20 /* invalid sample rate token */
#define AL_BAD_TRANSFER_SIZE	21 /* invalid size for sample read/write */
#define AL_BAD_FLOATMAX		22 /* invalid size for floatmax */
#define AL_BAD_PORTSTYLE	23 /* invalid port style */
#define AL_BAD_BUFFERLENGTH	24 /* bad buffer length */
#define AL_BAD_NOT_FOUND	25 /* item not found */
#define AL_BAD_PERMISSIONS	26 /* permission denied */
#define AL_MAX_ERROR		26 /* maximum error code */


/*
 * Old AL functions, provided for source compatibility
 */
 
extern ALconfig	ALnewconfig(void);		/* 0 for failure */
extern int	ALfreeconfig(ALconfig);		/* < 0 for failure */
extern int	ALsetconfig(ALport, ALconfig);	/* < 0 for failure */
extern ALconfig	ALgetconfig(ALport);		/* 0 for failure */
extern int	ALsetqueuesize(ALconfig, long);	/* < 0 for failure */
extern long	ALgetqueuesize(ALconfig);	/* < 0 for failure */
extern int	ALsetwidth(ALconfig, long);	/* < 0 for failure */
extern long	ALgetwidth(ALconfig);		/* < 0 for failure */
extern int	ALsetsampfmt(ALconfig, long);	/* < 0 for failure */
extern long	ALgetsampfmt(ALconfig);		/* < 0 for failure */
extern int	ALsetchannels(ALconfig, long);	/* < 0 for failure */
extern long	ALgetchannels(ALconfig);	/* < 0 for failure */

extern int	ALsetfloatmax(ALconfig, double);	/* < 0 for failure */
extern double	ALgetfloatmax(ALconfig);		/* = 0 for failure */
extern ALport	ALopenport(const char* /*name*/, const char* /*direction*/, 
                                                              ALconfig);
						/* 0 for failure */
extern int	ALcloseport(ALport);		/* < 0 for failure */
extern int 	ALgetfd(ALport);		/* < 0 for failure */
extern long	ALgetfilled(ALport);		/* < 0 for failure */
extern long	ALgetfillable(ALport);		/* < 0 for failure */
extern int	ALreadsamps(ALport, void* /*buf*/, long /*count*/);
						/* < 0 for failure */
extern int	ALwritesamps(ALport, void* /*buf*/, long /*count*/);
						/* < 0 for failure */
extern int  	ALsetfillpoint(ALport, long);	/* < 0 for failure */
extern long	ALgetfillpoint(ALport);		/* < 0 for failure */
extern int  	ALgetframenumber(ALport, unsigned long long *);	
extern int	ALgetframetime(ALport, unsigned long long *, 
			unsigned long long *);		

extern int	ALgetparams(long, long*, long);	/* < 0 for failure */
extern int	ALsetparams(long, long*, long);	/* < 0 for failure */
extern ALerrfunc ALseterrorhandler(ALerrfunc efunc);

extern int      ALgetstatus(ALport, long*, long);	/* < 0 for failure */
extern long	ALqueryparams(long /*device*/, long* /*PVbuffer*/, 
                                 long /*maxlength*/);
						/* < 0 for failure */
extern int	ALgetminmax(long /*device*/, long /*param*/,
				long* /*minparam*/, long* /*maxparam*/);
						/* < 0 for failure */
extern long	ALgetdefault(long /*device*/, long /*parameter*/);
						/* < 0 for failure */
extern char*	ALgetname(long /*device*/, long /*parameter*/);

/*
 * Old-style AL #defines. These are provided for backwards compatibility.
 */				

/*
 * audio port sample rates (these are the only ones supported by the library)
 */
#define AL_RATE_48000 	48000
#define AL_RATE_44100	44100
#define AL_RATE_32000	32000
#define AL_RATE_22050	22050
#define AL_RATE_16000	16000
#define AL_RATE_11025	11025
#define AL_RATE_8000	8000

/*
 * Setting the output rate to AL_RATE_INPUTRATE means that the output sample 
 * rate should track the sample rate of the currently selected input source.
 */
#define AL_RATE_INPUTRATE       (-1)

/*
 * The AES_X tokens define rates derived from the AES3 digital input
 * clock. The AES divided clock is divided by X and optionally multiplied
 * by 2/3 (if the "s" suffix is present). So AES_2 is AES/2, AES_1s is 
 * AES*2/3, etc.
 */
#define AL_RATE_AES_1           (-2)
#define AL_RATE_AES_2		(-3)
#define AL_RATE_AES_3		(-4)
#define AL_RATE_AES_4		(-5)
#define AL_RATE_AES_6		(-6)
#define AL_RATE_AES_1s		(-7)

/*
 * The following are possible return values from digital input rate queries.
 * AL_RATE_UNDEFINED means that a clock is present but its rate is
 *	not encoded in the digital audio stream;
 * AL_RATE_NO_DIGITAL_INPUT means that the AES receiver was unable
 *	to lock to the input clock, probably implying that there is no
 *	input signal;
 * AL_RATE_UNACQUIRED means that a clock is present but that the rate encoding
 * 	in the data stream has not yet been encountered. Rates are encoded
 * 	only periodically in an AES3 digital audio stream (every 192 sample
 *	frames).
 */
#define AL_RATE_UNDEFINED	(-8)
#define AL_RATE_NO_DIGITAL_INPUT	(-9)
#define AL_RATE_UNACQUIRED	(-10)
/*
 * old hardware parameters
 */
#define AL_INPUT_SOURCE		0
#define AL_LEFT_INPUT_ATTEN	1
#define AL_RIGHT_INPUT_ATTEN	2
#define AL_INPUT_RATE		3
#define AL_OUTPUT_RATE		4
#define AL_LEFT_SPEAKER_GAIN	5
#define AL_RIGHT_SPEAKER_GAIN	6
#define AL_INPUT_COUNT		7
#define AL_OUTPUT_COUNT		8
#define AL_UNUSED_COUNT		9
#define AL_SYNC_INPUT_TO_AES    10      /* Obsolete */
#define AL_SYNC_OUTPUT_TO_AES   11      /* Obsolete */
#define AL_MONITOR_CTL          12
#define AL_LEFT_MONITOR_ATTEN   13
#define AL_RIGHT_MONITOR_ATTEN  14
#define AL_CHANNEL_MODE		15
#define AL_SPEAKER_MUTE_CTL	16
#define	AL_MIC_MODE		17
#define AL_LEFT1_INPUT_ATTEN    1 	/* same as AL_LEFT_INPUT_ATTEN  */
#define AL_RIGHT1_INPUT_ATTEN   2 	/* same as AL_RIGHT_INPUT_ATTEN */
#define AL_LEFT2_INPUT_ATTEN    18
#define AL_RIGHT2_INPUT_ATTEN   19 
#define AL_DIGITAL_INPUT_RATE	20

/*
 * parameter value type
 */
#define AL_ENUM_VALUE	1	/* only certain constant values are valid */
#define AL_RANGE_VALUE	2	/* any value in a gven range is valid */


#ifndef NO_EVENTS

/*
 * some basic types
 */

typedef struct _ALeventQueue	*ALeventQueue;
typedef struct _ALevent         *ALevent;

/*
 * event functions
 */

extern ALeventQueue	alOpenEventQueue ( const char* name);
extern int	alCloseEventQueue ( ALeventQueue );
extern ALevent  alNewEvent(void);   /* 0 for failure */
extern int      alFreeEvent(ALevent);  /* < 0 for failure */
extern int      alSelectEvents(ALeventQueue, int, int *, int );
extern int      alDeselectEvents(ALeventQueue, int, int *,int);
extern int	alNextEvent ( ALeventQueue, ALevent );
extern int	alCheckEvent ( ALeventQueue, int, int, ALevent );
extern int	alPendingEvents ( ALeventQueue );
extern int	alFlushEvents ( ALeventQueue );
extern int	alGetEventQueueFD ( ALeventQueue );

/*
 *  Get functions for the event resources 
 */

extern int       alGetEventParam(ALevent);
extern int       alGetEventResource(ALevent);
extern int       alGetEventSrcResource(ALevent);
extern stamp_t   alGetEventTime(ALevent);
extern long long alGetEventUST(ALevent);
ALvalue          alGetEventValue(ALevent);
void*            alGetEventData(ALevent);

#define AL_MAX_EVENT_PARAM      64

/*
 * some event errors
 */

#define	AL_BAD_NO_EVENTQS	1024
#define	AL_BAD_INVALID_EVENTQ	1025
#define	AL_BAD_INVALID_EVENT	1026
#define AL_BAD_EVENT_NOT_FOUND  1027

/*
 * Event information structures
 */

typedef struct _ALconnectionInfo {
    int source, dest, connection;
} ALconnectionInfo;

typedef struct _ALsetChangeInfo {
    ALvalue val;    /* al value of added or deleted set element */
    int     total;  /* total number of elements in set          */
    int     pchange;/* delta in set size  +1 or -1              */
} ALsetChangeInfo;

#endif /* NO_EVENTS */

#ifdef _LANGUAGE_C_PLUS_PLUS
}
#endif

#endif /* __AUDIO_H__ */
