#ifndef	__HDSP_H__
#define	__HDSP_H__ 
/**************************************************************************
 *									  *
 * 		 Copyright (C) 1988, Silicon Graphics, Inc.		  *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/
#ident "$Revision: 1.87 $"

#include <sys/types.h>

/**************************************************************************
 *
 *  hdsp.h - High fidelity DSP device driver programmer visible structs.
 *
 **************************************************************************/

/*
 * ring buffer header
 */
typedef struct rbheader_s 
{
    int head; 			/* index of buffer head location */   
    int tail;			/* index of buffer tail location */
    int intreq;			/* */
    int fillpt;			/* buffer fill point             */
}rbheader_t;

#define RBHEADER_SIZE (sizeof(rbheader_t)/sizeof(int))

/* 
 * ioctl cases
 */
#define HDSP_RESET		0
#define HDSP_ACTIVATE		1
#define HDSP_FIND_MINOR		2
#define HDSP_ACQUIRE_AUDIO_RB	3
#define HDSP_SET_AUDIO_PARMS	4	/* old-style set params */
#define HDSP_GET_AUDIO_PARMS	5	/* old-style get params */
#define HDSP_GET_HRBSTATUS      6
#define HDSP_SET_HRBSTATUS      7
#define HDSP_SET_RB_INFO	8
#define HDSP_GET_ALL_RB_INFO	9
#define HDSP_SET_RB_TYPE	10
#define HDSP_GET_RB_MSC		11
#define HDSP_FLUSH		12	
#define HDSP_PORTCTRL		13
#define HDSP_QUERYPARAMS	14
#define HDSP_GET_MINMAX		15
#define HDSP_GET_NAME		16
#define HDSP_GET_DEFAULT	17
#define HDSP_ACQUIRE_DIRECT_AUDIO_RB	18
#define HDSP_GET_RB_USTMSC	19
#define HDSP_GET_RESOURCE	20
#define HDSP_SET_DEVICE		21
#define HDSP_CONNECT		22
#define HDSP_DISCONNECT		23
#define HDSP_SET_PARAMS		24	/* new-style set params */
#define HDSP_GET_PARAMS		25	/* new-style get params */
#define HDSP_QUERY_VALUES	26
#define HDSP_GET_PARAM_INFO	27	/* new-style parameter info */
#define HDSP_GET_RES_BY_NAME	28
#define HDSP_SET_RB_FORMAT	29	/* for formats other than audio data */


typedef struct hdsp_srcmask_s {
    int  src;
    long long mask;
    void *event;
} hdsp_srcmask_t;

typedef struct hdsp_connection_info_s {
  int input;
  int output;
  int connection;
} hdsp_connection_info_t;


#define HDSP_MAX_EVENT_DATA  8*4

/* 
 * ioctls for events
 */

#define HDSP_EVENT_GET		101
#define HDSP_EVENT_PUT		102
#define	HDSP_EVENT_PEEK		103
#define	HDSP_EVENT_CHECK	104
#define	HDSP_EVENTQ_ALLOCATE	110
#define	HDSP_EVENTQ_DUMP	111
#define	HDSP_EVENTQ_SET_SRC_MASK 112
#define	HDSP_EVENTQ_UNSET_SRC_MASK 113
#define	HDSP_EVENTQ_FLUSH	116
#define	HDSP_EVENTQ_GET_INFO	117
#define	HDSP_EVENTQ_PENDING	118


/*
 * some ioctl return codes for events
 */

#define EVENTQ_EMPTY		-1
#define	EVENTQ_FULL		-2

#ifndef HRB_STRLEN
#define HRB_STRLEN 20		/* max length of HRB/port name */
#endif

#define HDSP_MAX_RESOURCE_DEPTH	    8
#define HDSP_LARGE_STRLEN	    80

/* 
 * arg struct for HDSP_GET_RESOURCE_BY_NAME ioctl
 */
typedef struct hdsp_getresource_s 
{
    char name[80];
    int resources[HDSP_MAX_RESOURCE_DEPTH];
    int nres;
} hdsp_getresource_t;

/* 
 * arg struct for HDSP_ACQUIRE_AUDIO_RB ioctl
 */
typedef struct hdsp_acquireaudiorb_s 
{
    int nlocs;		/* Number of locations in the user's virtual space. */
    char direction;	/* TOMIPS or FROMMIPS */
} hdsp_acquireaudiorb_t;

/* 
 * arg struct for HDSP_SET_RB_INFO ioctl
 */
typedef struct hdsp_setrbinfo_s 
{
    char name[HRB_STRLEN];	/* name of HRB/port */
    int version;		/* AL version number */
} hdsp_setrbinfo_t;

/* 
 * arg struct for HDSP_GET_RBINFO ioctl
 */
typedef struct hdsp_getrbinfo_s
{
    char name[HRB_STRLEN];	/* name of HRB/port */
    int pid;			/* pid of process associated with port */
    int type;			/* TOMIPS or FROMMIPS */
    int rbid;			/* internal id associated with RB */
    int version;		/* AL version */
    int errcnt;			/* error count for the RB */
    int nchans;			/* number of channels in RB */
    int head;			/* head of RB */
    int tail;			/* tail of RB */
    int nlocs;			/* number of locations in RB */
} hdsp_getrbinfo_t;

typedef union {
    long long ll;	        /* XXXwtw - ragnarok bug #363861 workaround */
    void *p;			/* requires biggest member first */
    int i;
} hdsp_value_t;

typedef struct hdsp_setchange_info_s {
    hdsp_value_t val;	  /* al value of added or deleted set element */
    int          total;	  /* total number of elements in set          */
    int          pchange; /* delta in set size  +1 or -1              */
} hdsp_setchange_info_t ;

typedef struct {
    int param;
    int dummy;
    hdsp_value_t value;
    short size_in;
    short size2_in;
    short size_out;
    short size2_out;
} hdsp_pv_t;

typedef long long hdsp_fixed_t;

/* 
 * arg struct for HDSP_QUERY_SET ioctl
 */
typedef struct hdsp_queryset_s
{
    hdsp_value_t set;		/* ptr to set to fill */
    int vers;			/* AL version */
    int res;			/* resource ID */
    int param;			/* parameter */
    int setsize;		/* maximum size of the set */
    int pad[8];			/* extra space for later */
} hdsp_queryset_t;

/*
 * arg struct for HDSP_GET_RBSTATUS and HDSP_SET_RBSTATUS
 */
typedef struct hdsp_rbstatus_s 
{
    int error;           /* ring buffer error count */
    int type;            /* the type of error */
    int length;          /* the length of the error (in samples) */
    int location[2];     /* location (in samples) of the beginning of */
                         /* the error. location[0] is the low 24 bits, and */
                         /* location[1] is the high 24 bits of a 48-bit count*/
} hdsp_rbstatus_t;

typedef struct hdsp_rbmsc_s
{
    /* These are taken atomically */
    unsigned long long msc;	/* MSC at kernel side of ring-buffer */
    unsigned int head, tail;	/* HRB head and tail values */
    unsigned long long ust;	/* Unadjusted System Time */
} hdsp_rbmsc_t;

typedef struct hdsp_paraminfo_s { 
    int resource;		/* the resource */
    int param;			/* the parameter */
    int value_type;		/* type of the whole value (scalar,vector,set...) */
    int element_type;		/* type of each element (enum, fixed, resource ...) */
    int max_elems;		/* maximum number of elements */
    int max_elems2;		/* maximum number of elements (2nd dimension) */
    char name[32];		/* name of the parameter */
    hdsp_value_t initial;	/* initial value */
    hdsp_value_t min;		/* maximum value (range parameters only) */
    hdsp_value_t max;		/* maximum value (range parameters only) */
    hdsp_value_t min_delta;	/* maximum delta between values (range parameters only) */
    hdsp_value_t max_delta;	/* maximum delta between values (range parameters only) */
    int special_vals;		/* special values besides those between min & max */
    int ops;			/* bitfield indicating supported operations */
    int space[15];		/* extra room */
} hdsp_paraminfo_t;

typedef struct hdsp_addrval_s   /* need for 64/32 bit interface to  */
								/* HDSP_QUERY_PARM ioctl */
{
    caddr_t     addr;		/* pointer to be passed into the kernel */
    int   		val;		/* integer data value associated w/ pointer */
} hdsp_addrval_t;

typedef struct hdsp_valaddr_s   /* need for 64/32 bit interface to */
								/* HDSP_GET_NAME ioctl */
{
    int   		val;		/* integer data value associated w/ pointer */
    caddr_t     addr;		/* pointer to be passed into the kernel */
} hdsp_valaddr_t;

#if _KERNEL
typedef struct irix5_hdsp_addrval_s
{
    app32_ptr_t    addr;	/* 32-bit pointer to be passed into kernel */
    int   		   val;		/* integer data value associated w/ pointer */
} irix5_hdsp_addrval_t;

typedef struct irix5_hdsp_valaddr_s
{
    int   		   val;		/* integer data value associated w/ pointer */
    app32_ptr_t    addr;	/* 32-bit pointer to be passed into kernel */
} irix5_hdsp_valaddr_t;
#endif /* _KERNEL */

/* 
 * ioctl parameter subcodes
 * same subcodes used for both set and get of parameters 
 * buffer looks like an array of ints: [len, subcode,value, subcode, 
 * value, ...] 
 * values are read on sets and filled in on gets 
 *
 * make sure corresponding parameters in audio.h and hdsp.h agree
 *
 * IF YOU ADD ANY PARAMETERS, YOU MAY NEED TO UPDATE MAX_AUDIO_PARMS_LEN
 * YOU MAY ALSO NEED TO UPDATE AL_MAX_PBUFSIZE, in audio.h. These two
 * parameters should be the same, and large enough to hold all the
 * parms and associated values.
 */

/*
 * old-style parameters
 */
#define HDSP_MAX_AUDIO_PARMS_LEN	64
#define HDSP_INPUT_SOURCE		0
#define HDSP_LEFT_INPUT_ATTEN		1
#define HDSP_RIGHT_INPUT_ATTEN		2
#define HDSP_LEFT1_INPUT_ATTEN		1 /* Same as HDSP_LEFT_INPUT_ATTEN */
#define HDSP_RIGHT1_INPUT_ATTEN		2 /* Same as HDSP_LEFT_INPUT_ATTEN */
#define HDSP_INPUT_RATE			3
#define HDSP_OUTPUT_RATE		4
#define HDSP_LEFT_SPEAKER_GAIN		5
#define HDSP_RIGHT_SPEAKER_GAIN		6
#define HDSP_INPUT_RBCOUNT		7
#define HDSP_OUTPUT_RBCOUNT		8
#define HDSP_UNUSED_RBCOUNT		9
#define HDSP_MONITOR_CTL                12
#define HDSP_LEFT_MONITOR_ATTEN         13
#define HDSP_RIGHT_MONITOR_ATTEN        14
#define HDSP_CHANNEL_MODE	        15
#define HDSP_SPEAKER_MUTE_CTL		16
#define HDSP_MIC_MODE			17
#define HDSP_LEFT2_INPUT_ATTEN		18
#define HDSP_RIGHT2_INPUT_ATTEN		19
#define HDSP_DIGITAL_INPUT_RATE		20
#define HDSP_LOCK_STATE			21

#define HDSP_RANGE_VALUE 2
#define HDSP_ENUM_VALUE  1

/*
 * Element types
 */
 
#define HDSP_NO_ELEM		0
#define HDSP_INT32_ELEM		0x10
#define HDSP_RESOURCE_ELEM	(HDSP_INT32_ELEM | 0x1)
#define HDSP_ENUM_ELEM		(HDSP_INT32_ELEM | 0x2)
#define HDSP_INT64_ELEM		0x20
#define HDSP_FIXED_ELEM		(HDSP_INT64_ELEM | 0x1)
#define HDSP_PTR_ELEM		0x40
#define HDSP_CHAR_ELEM		0x80

/*
 * Value types
 */
#define HDSP_NO_VAL		0
#define HDSP_VECTOR_VAL		1
#define HDSP_SCALAR_VAL		2
#define HDSP_SET_VAL		3
#define HDSP_STRING_VAL		4
#define HDSP_MATRIX_VAL		5



/*
 * we define a range of values which resources cannot have.
 * in this range we place the parameters which are not also resource IDs
 * and types.
 */

#define HDSP_MAX_RESOURCE_ID	0x0fffffff
#define HDSP_PARAM_BIT		0x10000000
#define HDSP_TYPE_BIT		0x20000000

/*
 * new-style parameters. Parameters share namespace with resources, since
 * some of the parameter names can actually be used as resource IDs.
 */

/*
 * Note on parameters.  The AL event mechanism relies on the following two 
 * characteristics for parameters:
 * 1. There lower number is unique.
 * 2. There lower number is less than 64.
 * Take that into consideration when adding new parameters, otherwise the 
 * new parameters will break events.
 */
#define HDSP_RESOURCE		(HDSP_PARAM_BIT | 1)
#define HDSP_INTERFACE		(HDSP_PARAM_BIT | 2)
#define HDSP_CLOCK_GEN		(HDSP_PARAM_BIT | 3)
#define HDSP_CHANNELS		(HDSP_PARAM_BIT | 4)
#define HDSP_PORT_COUNT		(HDSP_PARAM_BIT | 5)
#define HDSP_MAX_PORTS		(HDSP_PARAM_BIT | 6)
#define HDSP_UNUSED_PORTS	(HDSP_PARAM_BIT | 7)
#define HDSP_MAX_SETSIZE	(HDSP_PARAM_BIT | 8)
#define HDSP_DEFAULT_INPUT	9
#define HDSP_DEFAULT_OUTPUT	10
#define HDSP_SYSTEM		11
#define HDSP_DEVICES		(HDSP_PARAM_BIT | 12)
#define HDSP_RATE		(HDSP_PARAM_BIT | 13)
#define HDSP_RATE_FRACTION_N	(HDSP_PARAM_BIT | 14)
#define HDSP_RATE_FRACTION_D	(HDSP_PARAM_BIT | 15)
#define HDSP_JITTER		(HDSP_PARAM_BIT | 16)
#define HDSP_MASTER_CLOCK	(HDSP_PARAM_BIT | 17)
#define HDSP_TYPE		(HDSP_PARAM_BIT | 18)
#define HDSP_NAME		(HDSP_PARAM_BIT | 19)
#define HDSP_PARAMS		(HDSP_PARAM_BIT | 20)
#define HDSP_NO_OP		(HDSP_PARAM_BIT | 21)
#define HDSP_SOURCE		(HDSP_PARAM_BIT | 22)
#define HDSP_DEST		(HDSP_PARAM_BIT | 23)
#define HDSP_CONNECTIONS	(HDSP_PARAM_BIT | 24)
#define HDSP_GAIN		(HDSP_PARAM_BIT | 25)
#define HDSP_PORTS		(HDSP_PARAM_BIT | 26)
#define HDSP_GAIN_REF		(HDSP_PARAM_BIT | 27)
#define HDSP_WORDSIZE		(HDSP_PARAM_BIT | 28)
#define HDSP_MUTE		(HDSP_PARAM_BIT | 29)
#define HDSP_SUBSYSTEM		(HDSP_PARAM_BIT | 30)
#define HDSP_LABEL		(HDSP_PARAM_BIT | 31)
#define HDSP_INTERVAL		(HDSP_PARAM_BIT | 32) /* MSC ticks/subcode blk*/
#define HDSP_SUBCODE_MASK	(HDSP_PARAM_BIT | 33)
#define HDSP_SUBCODE_FRAME	(HDSP_PARAM_BIT | 34)
#define HDSP_CHANS_PER_SUBCODE  (HDSP_PARAM_BIT | 35) /*data chans/subcode blk*/
#define HDSP_SHORT_NAME		(HDSP_PARAM_BIT | 36)
	    /* DO NOT ADD PARAMETERS HERE */
	    
/* 
 * These two are actually different from their counterparts in
 * audio.h because the defines are already used in the ioctl.
 */
#define HDSP_CONNECT_EVENT      (HDSP_PARAM_BIT | 37)
#define HDSP_DISCONNECT_EVENT   (HDSP_PARAM_BIT | 38)

#define HDSP_ASSOCIATE   	(HDSP_PARAM_BIT | 39)
#define HDSP_LOCKED             (HDSP_PARAM_BIT | 40)
#define HDSP_SUBSYSTEMS		(HDSP_PARAM_BIT | 41)
#define HDSP_VIDEO_SYNC 	(HDSP_PARAM_BIT | 42)
#define HDSP_VERSION	 	(HDSP_PARAM_BIT | 43)
#define HDSP_SUBCODE_FRAMESIZE	(HDSP_PARAM_BIT | 44)
#define HDSP_SUBCODE_FORMAT	(HDSP_PARAM_BIT | 45)
#define HDSP_SUBCODE_CHANNELS   (HDSP_PARAM_BIT | 46)
	    /* DO NOT ADD PARAMETERS HERE */
/*
 * These #define-s are doubly defined both as parameters and 
 * sample format tokens. Note that adding a new format entails
 * adding #defines in both audio.h and hdsp.h
 */
#define HDSP_AES_CHANNEL_STATUS (HDSP_PARAM_BIT | 47)
#define HDSP_AES_USER 		(HDSP_PARAM_BIT | 48)
#define HDSP_AES_VALIDITY 	(HDSP_PARAM_BIT | 49)
#define HDSP_ADAT_USER0 	(HDSP_PARAM_BIT | 50)
#define HDSP_ADAT_USER1 	(HDSP_PARAM_BIT | 51)
#define HDSP_ADAT_USER2 	(HDSP_PARAM_BIT | 52)
#define HDSP_ADAT_USER3 	(HDSP_PARAM_BIT | 53)
	    /* ADD PARAMETERS HERE */


/*
 * Resource types. The ordering of the types has nothing to do with which
 * are subtypes of which.
 */
#define HDSP_RESOURCE_TYPE	(HDSP_TYPE_BIT | 0)
#define HDSP_SYSTEM_TYPE	(HDSP_TYPE_BIT | 1)
#define HDSP_DEVICE_TYPE	(HDSP_TYPE_BIT | 2)
#define HDSP_PORT_TYPE		(HDSP_TYPE_BIT | 3)
#define HDSP_CLOCKGEN_TYPE	(HDSP_TYPE_BIT | 4)
#define HDSP_SUBSYS_TYPE	(HDSP_TYPE_BIT | 5)
#define HDSP_CONNECTION_TYPE	(HDSP_TYPE_BIT | 6)
#define HDSP_INTERFACE_TYPE	(HDSP_TYPE_BIT | 7)
#define HDSP_HRB_TYPE		(HDSP_TYPE_BIT | 8)
#define HDSP_MCLK_TYPE		(HDSP_TYPE_BIT | 9)
#define HDSP_XTAL_MCLK_TYPE	(HDSP_TYPE_BIT | 10)
#define HDSP_AES_MCLK_TYPE	(HDSP_TYPE_BIT | 11)
#define HDSP_ADAT_MCLK_TYPE	(HDSP_TYPE_BIT | 12)
#define HDSP_MIC_IF_TYPE	(HDSP_TYPE_BIT | 13)
#define HDSP_LINE_IF_TYPE	(HDSP_TYPE_BIT | 14)
#define HDSP_AES_IF_TYPE	(HDSP_TYPE_BIT | 15)
#define HDSP_ADAT_IF_TYPE	(HDSP_TYPE_BIT | 16)
#define HDSP_SPEAKER_IF_TYPE	(HDSP_TYPE_BIT | 17)
#define HDSP_FIXED_MCLK_TYPE	(HDSP_TYPE_BIT | 18)
#define HDSP_VARIABLE_MCLK_TYPE	(HDSP_TYPE_BIT | 19)
#define HDSP_ANALOG_IF_TYPE	(HDSP_TYPE_BIT | 20)
#define HDSP_DIGITAL_IF_TYPE	(HDSP_TYPE_BIT | 21)
#define HDSP_VIDEO_MCLK_TYPE	(HDSP_TYPE_BIT | 22)
#define HDSP_INPUT_PORT_TYPE	(HDSP_TYPE_BIT | 23)
#define HDSP_OUTPUT_PORT_TYPE	(HDSP_TYPE_BIT | 24)
#define HDSP_INPUT_HRB_TYPE	(HDSP_TYPE_BIT | 25)
#define HDSP_OUTPUT_HRB_TYPE	(HDSP_TYPE_BIT | 26)
#define HDSP_INPUT_DEVICE_TYPE	(HDSP_TYPE_BIT | 27)
#define HDSP_OUTPUT_DEVICE_TYPE	(HDSP_TYPE_BIT | 28)
#define HDSP_A2_SUBSYS_TYPE	(HDSP_TYPE_BIT | 29)
#define HDSP_RAD_SUBSYS_TYPE	(HDSP_TYPE_BIT | 30)
#define HDSP_A3_SUBSYS_TYPE	(HDSP_TYPE_BIT | 31)
#define HDSP_TEST_IF_TYPE       (HDSP_TYPE_BIT | 32)
#define HDSP_SPEAKER_PLUS_LINE_IF_TYPE (HDSP_TYPE_BIT | 33)
#define HDSP_A1_SUBSYS_TYPE	(HDSP_TYPE_BIT | 34)
#define HDSP_DIVO_SUBSYS_TYPE	(HDSP_TYPE_BIT | 35)
#define HDSP_SMPTE272M_IF_TYPE	(HDSP_TYPE_BIT | 36)
#define HDSP_OPTICAL_IF_TYPE	(HDSP_TYPE_BIT | 37)

#define HDSP_NULL_RESOURCE	2	/* special token for NULL resource */

#define HDSP_ALL_INTERFACES	3	/* special token meaning "all available interfaces" */
#define HDSP_NULL_INTERFACE	4	/* special token meaning "no interface" */

/*
 * values for sample format types in connections
 * Others, such as HDSP_AES_CHANNEL_STATUS, are defined above as parameters
 */
#define HDSP_AUDIODATA_INT32  0
#define HDSP_AUDIODATA_INT32_IDX  0
#define HDSP_MAXFORMATS 8


/*
 * support for dormant ports
 */
#define HDSP_DEACTIVATE_PORT	0
#define HDSP_ACTIVATE_PORT	1

/*
 * current ring-buffer types
 */
#define HDSP_MONO		1
#define HDSP_STEREO		2
#define HDSP_4CHANNEL		4

/*
 * error values for parameter/values
 */
#define HDSP_BAD_PARAM		-1	    /* parameter unrecognized */
#define HDSP_BAD_VALUE		-2	    /* value unsupported */

/*
 * Gain reference values
 */ 
#define HDSP_REF_NONE		0
#define HDSP_REF_0DBV		1

/*
 * Video sync values
 */
#define HDSP_VID_EXTERNAL 0
#define HDSP_VID_INTERNAL 1

/*
 * Values for supported parameter operations
 */
#define HDSP_GET_OP	    0x1
#define HDSP_SET_OP	    0x2
#define HDSP_QUERY_OP	    0x4
#define HDSP_EVENT_OP	    0x8

/* ... and some convenience combinations of the above */
#define HDSP_GQE_OP	    (HDSP_GET_OP | HDSP_QUERY_OP | HDSP_EVENT_OP)
#define HDSP_GSQE_OP	    (HDSP_GET_OP | HDSP_SET_OP | HDSP_QUERY_OP | HDSP_EVENT_OP)
#define HDSP_GSE_OP	    (HDSP_GET_OP | HDSP_SET_OP | HDSP_EVENT_OP)
#define HDSP_GS_OP	    (HDSP_GET_OP | HDSP_SET_OP)
#define HDSP_GQ_OP	    (HDSP_GET_OP | HDSP_QUERY_OP)
#define HDSP_GE_OP	    (HDSP_GET_OP | HDSP_EVENT_OP)

/* 
 * old-style available rates, in Hz, 44100 == 44.1KHz, 
 * 		   5333_33 == 5.33333 KHz etc 
 * The _ALT entries are different hardware 
 *	configurations that achieve the same rate 
 * NOTE: these rates are implementation dependent 
 *	44.1, and 48 are the least likely to change 
 *	You have been warned 
 */
#define HDSP_C_RATE(x)	((x)<<1)
#define HDSP_M_RATE(x)	((x)<<2)
#define HDSP_S_RATE(x)	((x)<<4)

#define HDSP_RATE_48000		(HDSP_M_RATE(0)|HDSP_C_RATE(0)|HDSP_S_RATE(0))
#define HDSP_RATE_44100		(HDSP_M_RATE(1)|HDSP_C_RATE(0)|HDSP_S_RATE(0))
#define HDSP_RATE_32000		(HDSP_M_RATE(0)|HDSP_C_RATE(1)|HDSP_S_RATE(0))
#define HDSP_RATE_29400		(HDSP_M_RATE(1)|HDSP_C_RATE(1)|HDSP_S_RATE(0))
#define HDSP_RATE_24000		(HDSP_M_RATE(0)|HDSP_C_RATE(0)|HDSP_S_RATE(1))
#define HDSP_RATE_22050		(HDSP_M_RATE(1)|HDSP_C_RATE(0)|HDSP_S_RATE(1))
#define HDSP_RATE_16000		(HDSP_M_RATE(0)|HDSP_C_RATE(0)|HDSP_S_RATE(2))
#define HDSP_RATE_16000_ALT	(HDSP_M_RATE(0)|HDSP_C_RATE(1)|HDSP_S_RATE(1))
#define HDSP_RATE_14700		(HDSP_M_RATE(1)|HDSP_C_RATE(0)|HDSP_S_RATE(2))
#define HDSP_RATE_14700_ALT	(HDSP_M_RATE(1)|HDSP_C_RATE(1)|HDSP_S_RATE(1))
#define HDSP_RATE_12000		(HDSP_M_RATE(0)|HDSP_C_RATE(0)|HDSP_S_RATE(3))
#define HDSP_RATE_11025		(HDSP_M_RATE(1)|HDSP_C_RATE(0)|HDSP_S_RATE(3))
#define HDSP_RATE_10666_7	(HDSP_M_RATE(0)|HDSP_C_RATE(1)|HDSP_S_RATE(2))
#define HDSP_RATE_9800		(HDSP_M_RATE(1)|HDSP_C_RATE(1)|HDSP_S_RATE(2))
#define HDSP_RATE_9600		(HDSP_M_RATE(0)|HDSP_C_RATE(0)|HDSP_S_RATE(4))
#define HDSP_RATE_8820		(HDSP_M_RATE(1)|HDSP_C_RATE(0)|HDSP_S_RATE(4))
#define HDSP_RATE_8000		(HDSP_M_RATE(0)|HDSP_C_RATE(0)|HDSP_S_RATE(5))
#define HDSP_RATE_8000_ALT	(HDSP_M_RATE(0)|HDSP_C_RATE(1)|HDSP_S_RATE(3))
#define HDSP_RATE_7350		(HDSP_M_RATE(1)|HDSP_C_RATE(0)|HDSP_S_RATE(5))
#define HDSP_RATE_7350_ALT	(HDSP_M_RATE(1)|HDSP_C_RATE(1)|HDSP_S_RATE(3))
#define HDSP_RATE_6857_14	(HDSP_M_RATE(0)|HDSP_C_RATE(0)|HDSP_S_RATE(6))
#define HDSP_RATE_6400		(HDSP_M_RATE(0)|HDSP_C_RATE(1)|HDSP_S_RATE(4))
#define HDSP_RATE_6300		(HDSP_M_RATE(1)|HDSP_C_RATE(0)|HDSP_S_RATE(6))
#define HDSP_RATE_6000		(HDSP_M_RATE(0)|HDSP_C_RATE(0)|HDSP_S_RATE(7))
#define HDSP_RATE_5880		(HDSP_M_RATE(1)|HDSP_C_RATE(1)|HDSP_S_RATE(4))
#define HDSP_RATE_5512_5	(HDSP_M_RATE(1)|HDSP_C_RATE(0)|HDSP_S_RATE(7))
#define HDSP_RATE_5333_33	(HDSP_M_RATE(0)|HDSP_C_RATE(1)|HDSP_S_RATE(5))
#define HDSP_RATE_4900		(HDSP_M_RATE(1)|HDSP_C_RATE(1)|HDSP_S_RATE(5))
#define HDSP_RATE_4571_43	(HDSP_M_RATE(0)|HDSP_C_RATE(1)|HDSP_S_RATE(6))
#define HDSP_RATE_4200		(HDSP_M_RATE(1)|HDSP_C_RATE(1)|HDSP_S_RATE(6))
#define HDSP_RATE_4000		(HDSP_M_RATE(0)|HDSP_C_RATE(1)|HDSP_S_RATE(7))
#define HDSP_RATE_3675		(HDSP_M_RATE(1)|HDSP_C_RATE(1)|HDSP_S_RATE(7))
/* 
 * these set the rate to be the AES input rate divided by n, n = 1..8 
 */
#define HDSP_RATE_AES_1		(HDSP_M_RATE(3)|HDSP_C_RATE(0)|HDSP_S_RATE(0))
#define HDSP_RATE_AES_2		(HDSP_M_RATE(3)|HDSP_C_RATE(0)|HDSP_S_RATE(1))
#define HDSP_RATE_AES_3		(HDSP_M_RATE(3)|HDSP_C_RATE(0)|HDSP_S_RATE(2))
#define HDSP_RATE_AES_4		(HDSP_M_RATE(3)|HDSP_C_RATE(0)|HDSP_S_RATE(3))
#define HDSP_RATE_AES_5		(HDSP_M_RATE(3)|HDSP_C_RATE(0)|HDSP_S_RATE(4))
#define HDSP_RATE_AES_6		(HDSP_M_RATE(3)|HDSP_C_RATE(0)|HDSP_S_RATE(5))
#define HDSP_RATE_AES_7		(HDSP_M_RATE(3)|HDSP_C_RATE(0)|HDSP_S_RATE(6))
#define HDSP_RATE_AES_8		(HDSP_M_RATE(3)|HDSP_C_RATE(0)|HDSP_S_RATE(7))
/* 
 * as above with a scale factor of s == 2/3 
 */
#define HDSP_RATE_AES_1s	(HDSP_M_RATE(3)|HDSP_C_RATE(1)|HDSP_S_RATE(0))
#define HDSP_RATE_AES_2s	(HDSP_M_RATE(3)|HDSP_C_RATE(1)|HDSP_S_RATE(1))
#define HDSP_RATE_AES_3s	(HDSP_M_RATE(3)|HDSP_C_RATE(1)|HDSP_S_RATE(2))
#define HDSP_RATE_AES_4s	(HDSP_M_RATE(3)|HDSP_C_RATE(1)|HDSP_S_RATE(3))
#define HDSP_RATE_AES_5s	(HDSP_M_RATE(3)|HDSP_C_RATE(1)|HDSP_S_RATE(4))
#define HDSP_RATE_AES_6s	(HDSP_M_RATE(3)|HDSP_C_RATE(1)|HDSP_S_RATE(5))
#define HDSP_RATE_AES_7s	(HDSP_M_RATE(3)|HDSP_C_RATE(1)|HDSP_S_RATE(6))
#define HDSP_RATE_AES_8s	(HDSP_M_RATE(3)|HDSP_C_RATE(1)|HDSP_S_RATE(7))

#define HDSP_RATE_INPUTRATE	     1   /* output rate tracks input rate */
#define HDSP_RATE_UNDEFINED	   (-1)  /* rate read is not defined by spec */
#define HDSP_RATE_NO_DIGITAL_INPUT (-2)  /* AESRX PLL not yet locked.*/
#define HDSP_RATE_UNACQUIRED	   (-3)  /* PLL locked but rate not read yet */

/* 
 * These are the available input sources 
 */
#define HDSP_INPUT_LINE		0	/* Line In Jack                       */
#define HDSP_INPUT_MIC		1	/* Microphone Jack                    */
#define HDSP_INPUT_DIGITAL	2	/* Digital I/O Jack                   */

/* 
 * The following defines indicate the type of a host ring buffer. 
 */
#define HRB_TOMIPS	0		/*data transfer to mips               */
#define HRB_FROMMIPS	1		/*data transfer from mips             */
#define HRB_FOLDED	2 		/*dsp (24b,24b) pair <-> mips 32b word*/
#define HRB_UNFOLDED	0		/*dsp 24b word <-> mips 32b word      */
#define HRB_EXTEND	4		/*sign extension                      */
#define HRB_NOEXTEND	0		/*no sign extension                   */
#ifdef _KERNEL
#define HRB_USERSPACE	8		/*memory mapped to user space         */
#define HRB_KERNELSPACE	0		/*memory mapped to kernel space       */
#define HRB_SPLIT	0x10		/*rb has split header/buffer 	      */
#define HRB_NODEFER	0x20		/*don't defer update of head/tail ptr */
#define HRB_MASTER	0x40		/*ring buffer is a rate master  */
#define HRB_DIRECT	0x80		/*direct rb*/
#define HRB_SERIAL	0		/*serial access rb*/
#define HRB_DORMANT	0x100		/*dormant RB */
#define HRB_NOTALLOCED	0x200		/* RB mem not alloced by kerncreate */
#define HRB_SUBCODE	0x400		/* subcode device unseen outside kernel */
#define HRB_BIGSAMPS	0x800		/* non-standard (> 1 loc) sample sizes */
#endif /*_KERNEL*/

/*
 * Macros for dealing with fixed-point stuff
 * HDSP_NFIXED	number of places to the right of the decimal point
 */
#define HDSP_NFIXED 32
#define HDSP_FIXED_TO_INT(x)    ((x) >> HDSP_NFIXED)
#define HDSP_INT_TO_FIXED(x)    (((hdsp_fixed_t)(x)) << HDSP_NFIXED)

/*
 * Special fixed-point values.
 */
#define HDSP_DYNAMIC	0xffffffffffffffffLL	/* special cookie for dynamic intial values */
#define HDSP_NO_CHANGE	0xffffffffffffffffLL	/* special cookie */
#define HDSP_MINUS_INF	0x8000000000000000LL	/* special "minus infinity" cookie */

/*
 * Bits in "special_values" which indicate the special values supported.
 */
#define HDSP_NO_CHANGE_BIT  0x1
#define HDSP_MINUS_INF_BIT  0x2

/*
 * Subcode block sizes
 */
#define HDSP_AES_SUBCODE_BLOCKSIZE  18
#define HDSP_ADAT_SUBCODE_BLOCKSIZE 30

/*
 * maximum ring buffer length in bytes
 */
#define MAXRBLEN (4096*400)

#endif /* __HDSP_H__ */
