/**************************************************************************
 *									  *
 * Copyright (C) 1993 Silicon Graphics, Inc.   			          *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/
#ifndef __MD_H__
#define __MD_H__

#include <sgidefs.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/midi.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct __MDport *MDport;

typedef struct midistatusinfo MDstatusinfo;

typedef void (*mdErrfunc)(long,const char*,...);
extern mdErrfunc mdSeterrorhandler(mdErrfunc efunc);

char  *mdRegister      (const char *name);
int    mdUnRegister    (const char *name);
MDport mdOpenInPort    (const char *name); /* open an input port */
MDport mdOpenOutPort   (const char *name); /* open an output port */
int    mdClosePort     (MDport);           /* close down any port */
int    mdGetFd         (MDport);	   /* retrieve a file descriptor */
int    mdInit          (void);             /* initialize midi system */

char *mdGetName        (int);              /* get name of a lower device */
char *mdGetDefault     (int);	           /* get name of the default device */
void  mdCallFree       (void*);	           /* Indirect call of mdFree for dloading */
void *mdCallMalloc     (size_t);	   /* Indirect call of mdMalloc for dloading */

/* defines for mdGetDefault */
#define MD_GET_OUTPUT 0		   
#define MD_GET_INPUT  1

int  mdSetStampMode   (MDport, int);    	/* set time stamp mode */
int  mdGetStampMode   (MDport);    		/* get time stamp mode */
int  mdSetOrigin      (MDport, long long); 	/* set the timing base */

/* New way to set up a time line.  Sets both the origin time and origin tick */

int  mdSetStartPoint  (MDport port, long long time, long long stamp);

void mdSetRelativeTick(MDport, long long); 	/* Set the initial tick value */
long long mdGetOrigin(MDport); 	/* set the timing base */

/* these routines deal with MIDI time.  They have no effect
 * unless MD_DELTATICKS or MD_RELATIVETICKS have been set in 
 * mdSetStampMode 
 */
int mdGetDivision(MDport);          /* sets the divisions per beat */
int mdSetDivision(MDport, int);     /* aka ppq */

int mdGetTempo(MDport);             /* {g,s}et tempo, in usec per beat */
int mdSetTempo(MDport, int);        

int mdSetTemposcale(MDport, double); /* set a tempo scalar */

int mdCountReaders   (MDport);		/* Return count of readers from port */
int mdCountWriters   (MDport);		/* Return count of writers to port */

int   mdMakeClock (MDport, char *, int); /* make this port a clock source */
int   mdInitClocks(void);	         /* get the number of available clocks */
char *mdGetClock  (int);		 /* get the name of available clocks */
int   mdSetClock  (MDport, char *);	 /* slave this port to specified clock */

/* conversions from nanosecond times to ticks based on 
 * division and tempo for the MDport in question 
 */
long long mdTicksToNanos(MDport, long long);
long long mdNanosToTicks(MDport, long long);

/* timing modes */
#define MD_NOSTAMP           1
#define MD_DELTASTAMP        2
#define MD_RELATIVESTAMP     3
#define MD_DELTATICKS        4	    /* delta ticks, as in SMF 1.0 */
#define MD_RELATIVETICKS     5	    /* relative ticks */

#define MD_STAMPING_MASK     0xf

/* debugging and statistics */
#define DBSTAMPS             0x1

extern int __mdmsglengths [];

#define mdMsgLen(x) ((__mdmsglengths[(x & 0x7f) >> 4]))

typedef struct __mdevent {
	char msg[4];
	char *sysexmsg;
	long long stamp;   	    /* time stamp in ns */
	int msglen;                 /* length of data, sysex only */
} MDevent;

/* basic I/O routines */
int mdReceive(MDport, MDevent *, int);
int mdSend   (MDport, MDevent *, int);
int mdGetWaitingEvents(MDport);

long long mdPause(MDport);
long long mdTell (MDport);
long long mdTellNow (MDport);
int mdPanic(MDport);

int mdPrintEvent(char *, MDevent *, int);

typedef void *(*mdMalloc_t)(size_t);
typedef void  (*mdFree_t)(void *);

void mdSetAllocator(mdMalloc_t, mdFree_t, void *);
extern mdMalloc_t mdMalloc;
extern mdFree_t mdFree;

/* routines for dealing with midi messages */
int mdGetStatus (char *msg);
int mdGetChannel(char *msg);
int mdGetByte1  (char *msg);
int mdGetByte2  (char *msg);

void mdSetStatus (char *msg, int x);
void mdSetChannel(char *msg, int x);
void mdSetByte1  (char *msg, int x);
void mdSetByte2  (char *msg, int x);

#define MD_CHANNELMASK	 	    0x0F
#define MD_STATUSMASK	 	    0xF0

#define MD_CHANNELVOICE		    0x80
#define MD_NOTEOFF		    0x80
#define MD_NOTEON		    0x90    /* note-off is also note-on w/velocity=0 */
#define MD_POLYKEYPRESSURE	    0xA0    /* polyphonic key pressure or aftertouch */
#define MD_CONTROLCHANGE	    0xB0
#define MD_CHANNELMODESELECT	    0xB0
#define MD_PROGRAMCHANGE	    0xC0
#define MD_CHANNELPRESSURE	    0xD0    /* aftertouch is the Yamaha term */ 
#define MD_PITCHBENDCHANGE	    0xE0

#ifdef MD_SYSEX
#undef MD_SYSEX
#endif
#define MD_SYSEX		    0xF0	/* System Exclusive */

#define MD_SYSTEMCOMMON		    0xF1
#define MD_TIMECODEQUARTERFRAME	    0xF1
#define MD_SONGPOSITIONPOINTER	    0xF2
#define MD_SONGSELECT		    0xF3
#define MD_UNDEFINED1		    0xF4
#define MD_UNDEFINED2		    0xF5
#define MD_CABLE		    0xF5	/* Proposed extension */
#define MD_TUNEREQUEST		    0xF6
#define MD_EOX			    0xF7	/* End of System Exclusive */

#define MD_SYSTEMREALTIME	    0xF8
#define MD_TIMINGCLOCK		    0xF8
#define MD_UNDEFINED3		    0xF9
#define MD_START		    0xFA
#define MD_CONTINUE		    0xFB
#define MD_STOP			    0xFC
#define MD_UNDEFINED4		    0xFD
#define MD_ACTIVESENSING	    0xFE
#define MD_SYSTEMRESET		    0xFF
#define MD_META			    0xFF	/* MIDI Files only */

#define MD_BANKSELECT		    0x00
#define MD_MODULATIONWHEEL	    0x01
#define MD_BREATHCONTROLLER	    0x02
#define MD_FOOTCONTROLLER	    0x04
#define MD_PORTAMENTOTIME	    0x05
#define MD_DATAENTRYMSB		    0x06
#define MD_MAINVOLUME		    0x07	/* renamed to Channel Volume */
#define MD_CHANNELVOLUME	    MD_MAINVOLUME
#define MD_BALANCE		    0x08
#define MD_PAN			    0x0A
#define MD_EXPRESSIONCONTROLLER	    0x0B
#define MD_EFFECTCONTROL1	    0x0C
#define MD_EFFECTCONTROL2	    0x0D
#define MD_GENERALPURPOSE1	    0x10
#define MD_GENERALPURPOSE2	    0x11
#define MD_GENERALPURPOSE3	    0x12
#define MD_GENERALPURPOSE4	    0x13

#define MD_LSBFOR00		    0x20
#define MD_LSBFOR1F		    0x3F

#define MD_BANKSELECT_LSB	        (MD_BANKSELECT|0x20) 
#define MD_MODULATIONWHEEL_LSB	    (MD_MODULATIONWHEEL|0x20)
#define MD_BREATHCONTROLLER_LSB	    (MD_BREATHCONTROLLER|0x20)
#define MD_FOOTCONTROLLER_LSB	    (MD_FOOTCONTROLLER|0x20)
#define MD_PORTAMENTOTIME_LSB	    (MD_PORTAMENTOTIME|0x20)
#define MD_DATAENTRYMSB_LSB	        (MD_DATAENTRYMSB|0x20)
#define MD_CHANNELVOLUME_LSB	    (MD_CHANNELVOLUME|0x20)
#define MD_BALANCE_LSB		        (MD_BALANCE|0x20)
#define MD_PAN_LSB		            (MD_PAN|0x20)
#define MD_EXPRESSIONCONTROLLER_LSB (MD_EXPRESSIONCONTROLLER|0x20)
#define MD_EFFECTCONTROL1_LSB	    (MD_EFFECTCONTROL1|0x20)
#define MD_EFFECTCONTROL2_LSB	    (MD_EFFECTCONTROL2|0x20)
#define MD_GENERALPURPOSE1_LSB	    (MD_GENERALPURPOSE1|0x20)
#define MD_GENERALPURPOSE2_LSB	    (MD_GENERALPURPOSE2|0x20)
#define MD_GENERALPURPOSE3_LSB	    (MD_GENERALPURPOSE3|0x20)
#define MD_GENERALPURPOSE4_LSB	    (MD_GENERALPURPOSE4|0x20)

#define MD_DAMPERPEDAL		    0x40	/* sustain pedal */
#define MD_PORTAMENTO		    0x41
#define MD_SOSTENUTO		    0x42
#define MD_SOFTPEDAL		    0x43
#define MD_LEGATOFOOTSWITCH         0x44
#define MD_HOLD2		    0x45

#define MD_SOUNDCONTROLLER1         0x46	/* default: Sound Variation           */
#define MD_SOUNDCONTROLLER2         0x47	/* default: Timbre/Harmonic Intensity */
#define MD_SOUNDCONTROLLER3         0x48	/* default: Release Time              */
#define MD_SOUNDCONTROLLER4         0x49	/* default: Attack  Time              */
#define MD_SOUNDCONTROLLER5         0x4A	/* default: Brightness                */
#define MD_SOUNDCONTROLLER6         0x4B	/* 6-10: no defaults                  */
#define MD_SOUNDCONTROLLER7         0x4C
#define MD_SOUNDCONTROLLER8         0x4D
#define MD_SOUNDCONTROLLER9         0x4E
#define MD_SOUNDCONTROLLER10        0x4F

#define MD_GENERALPURPOSE5	    0x50
#define MD_GENERALPURPOSE6	    0x51
#define MD_GENERALPURPOSE7	    0x52
#define MD_GENERALPURPOSE8	    0x53
#define MD_PORTAMENTOCONTROL	    0x54
    /* 0x55-5A undefined */

#define MD_EFFECTS1DEPTH            0x5B	/* formerly External Effects Depth */
#define MD_EFFECTS2DEPTH            0x5C	/* formerly Tremolo Depth          */
#define MD_EFFECTS3DEPTH            0x5D	/* formerly Chorus  Depth          */	
#define MD_EFFECTS4DEPTH            0x5E	/* formerly Celeste (Detune) Depth */
#define MD_EFFECTS5DEPTH            0x5F	/* formerly Phaser  Depth          */

#define MD_EXTERNALEFFECTSDEPTH	    MD_EFFECTS1DEPTH
#define MD_TREMELODEPTH		    MD_EFFECTS2DEPTH
#define MD_CHORUSDEPTH		    MD_EFFECTS3DEPTH
#define MD_CELESTEDEPTH		    MD_EFFECTS4DEPTH
#define MD_PHASERDEPTH		    MD_EFFECTS5DEPTH

#define MD_DATAINCREMENT	    0x60
#define MD_DATADECREMENT	    0x61
#define MD_NRPN_LSB		    0x62	/* Non Registered Parameter Number */
#define MD_NRPN_MSB		    0x63
#define MD_RPN_LSB		    0x64	/* Registered Parameter Number */
#define MD_RPN_MSB		    0x65

#define MD_ALLSOUNDOFF		    0x78
#define MD_CHANNELMODEMESSAGES	    0x79
#define MD_RESETALLCONTROLLERS	    0x79
#define MD_LOCALCONTROL		    0x7A    /* 0=off, 127=on */
#define MD_ALLNOTESOFF		    0x7B
#define MD_OMNIMODEOFF		    0x7C    /* + All Notes Off */
#define MD_OMNIMODEON		    0x7D    /* + All Notes Off */
#define MD_MONOMODEON		    0x7E    /* + All Notes Off */
#define MD_POLYMODEON		    0x7F    /* Mono=Off + All Notes Off */

#ifdef __cplusplus
}
#endif

#endif /* !__MD_H__ */
