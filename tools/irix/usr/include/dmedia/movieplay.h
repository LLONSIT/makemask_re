/*****************************************************************************
 *
 * SGI movie library 
 *
 * movieplay.h
 *	header file for use with libmovieplay.so
 *      movie playback interface
 *
 * Copyright 1992, 1993, & 1996, Silicon Graphics, Inc.
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

#ifndef __MOVIEPLAY_H__
#define __MOVIEPLAY_H__

#ident "$Revision: 1.39 $"

#include <X11/Xlib.h>		/* for Display, Window */
#include <GL/glx.h>		/* for GLXContext */

#include <dmedia/dmedia.h>
#include <dmedia/dm_audio.h>
#include <dmedia/dm_image.h>
#include <dmedia/dm_timecode.h>
#include <dmedia/dm_params.h>
#include <dmedia/moviefile.h>
#include <dmedia/audio.h>
#include <GL/glx.h>
#include <X11/Xlib.h>
#include <dmedia/vl.h>

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************************
*
* Type Definitions
*
**********************************************************************/

/********
*
* MVport - opaque handle
*
********/

typedef void * MVport;

/* Port names and data structures */

#define MV_PORT_GFX      "mvgfx"
#define MV_PORT_AUDIO    "mvaudio"
#define MV_PORT_VIDEO    "mvvideo"

/* Data for MV_PORT_GFX */
typedef struct
{
    Display *     dpy;
    Window        win;
    GLXContext    ctxt;           /* If NULL, assume IrisGL compatibility mode */
    XVisualInfo * vInfo;          /* optional */
    DMboolean     onscreenRender; /* obsolete */
} MVgfxPortData;

/* Data for MV_PORT_AUDIO */
typedef struct
{
    ALconfig      config;     /* in: config info for an ALport */
    int           ownsRate;   /* in: true if the port can set the AL's rate */
    double        sampleRate; /* in: sample RATE to use, if 0 use hardware RATE */
} MVaudioPortData;

/* Data for MV_PORT_VIDEO */
typedef struct
{
    Display *     dpy;  /* If NULL, only show on video-out */
    Window        win;  /* If None, only show on video-out */
    GLXContext    ctxt; /* optional */
    XVisualInfo * vInfo;/* optional */
    DMboolean     flickerFilter; /* currently unused */
    VLServer      svr;  /* currently unused */
    VLPath        path; /* currently unused */
    VLNode        src;  /* currently unused */
    VLNode        drn;  /* currently unused */
} MVvideoPortData;

/********
*
* MVsyncInfo - synchronization information
*
********/

typedef struct
{
    long long    ust;
    MVtime       movieTime;
    MVtimescale  timeScale;
    MVdirection  direction; /* unused */
    double       speed;     /* unused */
} MVsyncInfo;

/********
*
* MVeventmask (for mvSetSelectEvents())
*
********/

typedef __uint32_t MVeventmask;

#define MV_EVENT_MASK_FRAME		(1<<1)
#define MV_EVENT_MASK_STOP		(1<<2)
#define MV_EVENT_MASK_ERROR		(1<<3)
#define MV_EVENT_MASK_SLOW_PLAY		(1<<4)
#define MV_EVENT_MASK_SYNC     		(1<<5)
#define MV_EVENT_MASK_WARNING		(1<<6)
#define MV_EVENT_MASK_SCHED  		(1<<7)

/********
*
* MVeventtype
*
********/

typedef enum __MVeventtype
{
    MV_EVENT_FRAME		= 1,
    MV_EVENT_STOP		= 2,
    MV_EVENT_ERROR		= 3,
    MV_EVENT_SLOW_PLAY		= 4,
    MV_EVENT_SYNC     		= 5,
    MV_EVENT_WARNING   		= 6,
    MV_EVENT_SCHED              = 7
} MVeventtype;

/********
*
* Playback Events
*
********/

typedef struct __mvFrameEvent {	/* a frame just played */
    MVeventtype		type;	/* event type */
    MVtime 		time;	/* same as X timestamp, in milliseconds */
    MVid 		id;	/* movie instance which produced the event */
    MVframe 		frame;	/* current frame for the movie instance */
} MVframeevent;

typedef struct __mvStopEvent {	/* the movie stopped at the end */
    MVeventtype 	type;
    MVtime 		time;
    MVid 		id;
    MVframe 		frame;
} MVstopevent;

typedef struct __mvErrorEvent {	/* error condition halting playback */
    MVeventtype 	type;
    MVtime 		time;
    MVid 		id;
    MVframe 		frame;
    int 		errcode;
    pid_t               pid;
} MVerrorevent;

/* Do not use, obsolete */
typedef struct __mvSlowPlayEvent { /* cannot acheive desired frame rate */
    MVeventtype 	type;
    MVtime 		time;
    MVid 		id;
    MVframe 		frame;
    int 		reason;
} MVslowplayevent;

typedef struct __mvSyncEvent { /* sync information */
    MVeventtype         type;
    MVtime              obsolete;
    MVid                id;
    MVport              port;
    MVsyncInfo          syncInfo;
} MVsyncevent;

typedef struct __mvWarningEvent { /* warning condition */
    MVeventtype         type;
    MVtime              obsolete;
    MVid                id;
    MVtime              movieTime; 
    MVtime              duration;
    MVtimescale         scale;  
    int                 errcode;
    pid_t               pid;
} MVwarningevent;

typedef struct __mvSchedEvent { /* scheduling event */
    MVeventtype         type;
    MVtime              obsolete;
    MVid                id;
    DMboolean           realTime;
} MVschedevent;

typedef struct __mvGenericEvent { /* common to all events */
    MVeventtype         type;
    MVtime              time;
    MVid                id;
} MVgenericevent;

typedef union __mvEvent {
    MVeventtype		type;	    
    MVframeevent 	mvframe;
    MVstopevent 	mvstop;
    MVerrorevent 	mverror;
    MVslowplayevent 	mvslowplay; /* obsolete */
    MVsyncevent         mvsync;
    MVwarningevent      mvwarning;
    MVschedevent        mvsched;
    MVgenericevent 	mvgeneric; /* all events may be safely cast to this */
} MVevent;

/**********************************************************************
*
* Playback parameters
*
**********************************************************************/

/* How to correct when fields are dropped */

#define MV_FIELD_CORRECTION "MV_FIELD_CORRECTION"

typedef enum 
{
    MV_FIELD_CORRECT_SPATIALLY,
    MV_FIELD_CORRECT_TEMPORALLY
} MVfieldcorrection;

/* How to display odd-sized movies on video devices */

#define MV_VIDEO_DISPLAY "MV_VIDEO_DISPLAY"
typedef enum
{
    MV_VIDEO_DISPLAY_UPPER_LEFT = 0,
    MV_VIDEO_DISPLAY_CENTER = 1,
    MV_VIDEO_DISPLAY_SCALE_TO_FIT = 2
} MVvideoDisplay;

/**********************************************************************
*
* Playback Functions
*
**********************************************************************/

extern DMstatus	 mvSetNumMoviesHint ( int          numMovies );
extern int       mvGetNumMoviesHint ( void );

extern DMstatus  mvBindOpenGLWindow ( MVid         movieid, 
				      Display*     dpy,
				      Window       win,
				      GLXContext   ctxt );
extern DMstatus  mvUnbindOpenGLWindow( MVid        movie );

extern void      mvSetCurrentFrame  ( MVid         movieid, 
				      MVframe      newframe );
extern MVframe   mvGetCurrentFrame  ( MVid         movieid );
extern DMstatus  mvSetCurrentTime   ( MVid         movieid, 
                                      MVtime       time, 
                                      MVtimescale  timeScale );
extern MVtime    mvGetCurrentTime   ( MVid         movieid, 
                                      MVtimescale  timeScale );

extern void      mvScrubCurrentFrame( MVid         movieid, 
				      MVframe      newframe );

extern void      mvStop             ( MVid         movieid );
extern void      mvPlay             ( MVid         movieid );
extern DMboolean mvIsMovieStopped   ( MVid         movieid );

extern void	 mvSetStartFrame    ( MVid	   movieid, 
				      MVframe	   startframe );
extern MVframe	 mvGetStartFrame    ( MVid	   movieid );
extern void	 mvSetEndFrame	    ( MVid	   movieid, 
				      MVframe	   endframe );
extern MVframe	 mvGetEndFrame	    ( MVid	   movieid );
extern DMstatus  mvSetStartTime     ( MVid         movie, 
                                      MVtime       time, 
                                      MVtimescale  scale );
extern MVtime    mvGetStartTime     ( MVid         movie, 
                                      MVtimescale scale );
extern DMstatus  mvSetEndTime       ( MVid         movie, 
                                      MVtime       time, 
                                      MVtimescale  scale );
extern MVtime    mvGetEndTime       ( MVid         movie, 
                                      MVtimescale  scale );

extern void      mvSetEnableAudio   ( MVid         movieid, 
				      DMboolean    onoff );
extern DMboolean mvGetEnableAudio   ( MVid         movieid );
extern void      mvSetPrimaryAudio  ( MVid         movieid );
extern MVid      mvGetPrimaryAudio  ( void );
extern void      mvSetEnableVideo   ( MVid         movieid, 
                                      DMboolean    onoff );
extern DMboolean mvGetEnableVideo   ( MVid         movieid );

extern void      mvSetVideoDisplay  ( MVid         movieid,
                                      MVvideoDisplay 
                                                   mode );
extern MVvideoDisplay      
                 mvGetVideoDisplay  ( MVid         movieid );

extern void      mvSetVideoStillFrame
                                    ( MVid         movieid,
                                      DMboolean    still ); 
extern DMboolean mvGetVideoStillFrame
                                    ( MVid         movieid );

extern void      mvSetPlayLoopMode  ( MVid         movieid, 
				      MVloopmode   newloopmode );
extern MVloopmode
                 mvGetPlayLoopMode  ( MVid         movieid );
extern void      mvSetPlayLoopLimit ( MVid         movieid, 
				      MVframe      newlooplimit );
extern MVframe   mvGetPlayLoopLimit ( MVid         movieid );
extern void      mvSetPlayLoopCount ( MVid         movieid, 
				      MVframe      newloopcount );
extern MVframe   mvGetPlayLoopCount ( MVid         movieid );

extern void      mvSetViewOffset    ( MVid         movieid, 
				      int          offsetx, 
				      int          offsety,
				      DMboolean    glcoordsystem ); 
extern void      mvGetViewOffset    ( MVid         movieid,
				      int*         offsetxreturn,
				      int*         offsetyreturn,
				      DMboolean    glcoordsystem ); 
extern void      mvQueryViewOffset  ( MVid         movieid, 
				      int          offsetx, 
				      int          offsety,
				      int*         offsetxreturn, 
				      int*         offsetyreturn,
				      DMboolean    glcoordsystem );  
extern void      mvSetViewSize      ( MVid         movieid, 
				      int          newwidth, 
				      int          newheight,
				      DMboolean    keepAspect ); 
extern void      mvGetViewSize      ( MVid         movieid, 
				      int*         widthreturn,
				      int*         heightreturn );
extern DMboolean mvGetViewKeepAspect( MVid         movieid );
extern void      mvQueryViewSize    ( MVid         movieid, 
				      int          width, 
				      int          height,
				      DMboolean    obsolete, 
				      int*         widthreturn,
				      int*         heightreturn );  
extern DMstatus  mvSetViewOffsetAndSize(
                                      MVid         movie, 
                                      int          x, 
                                      int          y, 
                                      int          w, 
                                      int          h, 
                                      DMboolean          glcoordsystem);
extern void      mvSetViewBackground( MVid         movieid,
				      unsigned short red,
				      unsigned short green,
				      unsigned short blue );
extern void      mvGetViewBackground( MVid         movieid, 
				      unsigned short* redreturn,
				      unsigned short* greenreturn,
				      unsigned short* bluereturn ); 

/* Event routines (for all movies) */
extern DMstatus	   mvGetEventFD       ( int *fdreturn );
extern void        mvSetSelectEvents  ( MVeventmask eventmask );
extern MVeventmask mvGetSelectEvents  ( void );
extern void        mvNextEvent        ( MVevent* eventreturn );
extern void        mvPeekEvent        ( MVevent* eventreturn );
extern int         mvPendingEvents    ( void );

/* "Per movie" event routines */
extern DMstatus    mvGetMovieEventFD      ( MVid        movieid, 
                                            int *       fdreturn );
extern void        mvSetMovieSelectEvents ( MVid        movieid, 
                                            MVeventmask eventmask );
extern MVeventmask mvGetMovieSelectEvents ( MVid        movieid );
extern void        mvNextMovieEvent       ( MVid        movieid, 
                                            MVevent *   eventreturn );
extern void        mvPeekMovieEvent       ( MVid        movieid, 
                                            MVevent *   eventreturn );
extern int         mvPendingMovieEvents   ( MVid        movieid );

extern DMstatus	   mvGetActualFrameRate ( MVid     movieid, 
                                          double * ratereturn );

extern void        mvSetPlaySpeed       ( MVid     movieid, 
                                          double   newplayspeed );
extern double      mvGetPlaySpeed       ( MVid     movieid );
extern MVdirection mvGetCurrentDirection( MVid     movie );

extern void      mvSetPlayEveryFrame( MVid         movieid, 
                                      DMboolean    sync );
extern DMboolean mvGetPlayEveryFrame( MVid         movieid );

extern void      mvShowCurrentFrame ( MVid         movieid );
extern void      mvShowCurrentTime  ( MVid         movieid );

extern void      mvResizeOpenGLWindow ( Display*     dpy, 
				      Window       win,
				      GLXContext   ctxt );

extern void      mvGrabOpenGL       ( void );
extern void      mvReleaseOpenGL    ( void );

/* Playback port routines */

extern MVport      mvOpenPort             ( const char *name, 
                                            void *      portdata );
extern void        mvClosePort            ( MVport port );
extern DMstatus    mvBindMovieToPorts     ( MVid        movieid, 
                                            MVport *    port, 
                                            int         numports, 
                                            int *       numboundports );
extern void        mvUnbindPortsFromMovie ( MVport *    ports, 
                                            int         numports );
extern void        mvUnbindMovieFromPorts ( MVid        movieid );
extern MVid        mvGetPortMovie         ( MVport      port );
extern int         mvGetMoviePorts        ( MVid        movieid, 
                                            MVport **   portlist );
extern MVport      mvGetMovieMasterPort   ( MVid        movieid );
extern void        mvGrabPort             ( MVport      port );
extern void        mvReleasePort          ( MVport      port );
extern void        mvResizePort           ( MVport      port );
extern DMstatus    mvSetPortEnabled       ( MVport      port, 
                                            DMboolean   onoff );
extern DMboolean   mvGetPortEnabled       ( MVport      port );

/* Playback hardware acceleration hint for mvBindOpenGLWindow() */

extern DMstatus   mvGetMovieHwAcceleration ( MVid        movieid, 
                                             DMboolean * hasHw );
extern DMstatus   mvSetMovieHwAcceleration ( MVid        movieid, 
                                             DMboolean   useHw );

/* External synchronization */

/* 10 secs worth of nanos */
#define MV_MIN_SYNC_DISTANCE_NANOS     (10LL*1000000000LL)

/* 20 ms worth of nanos */
#define MV_MIN_PREROLL_NANOS           (20LL*1000000LL)

extern DMstatus  mvPlayAt            ( MVid movieid, MVsyncInfo *syncInfo );
extern DMstatus  mvGetMovieSyncInfo  ( MVid movieid, MVsyncInfo *syncInfo );
extern DMstatus  mvSetMovieSyncInfo  ( MVid movieid, MVsyncInfo *syncInfo );

extern const char *mvGetPlayErrorStr(int errno, pid_t pid);

/**********************************************************************
*
* Obsolete calls
*
**********************************************************************/

/* Replaced by mvBindOpenGLWindow()/mvUnbindOpenGLWindow()/mvResizeOpenGLWindow() */
/* Also see port calls */
extern DMstatus  mvBindWindow       ( MVid         movieid, 
				      Display*     dpy,
				      Window       win );
extern DMstatus  mvUnbindWindow     ( MVid         movie );
extern void      mvResizeWindow     ( Display*     dpy, 
				      Window       win );

/* Replaced by mvGrabOpenGL()/mvReleaseOpenGL()/mvGrabPort() */
extern void      mvGrabIrisGL       ( void );
extern void      mvReleaseIrisGL    ( void );

/* Replaced by mvSetEnableVideo(), mvGetEnableVideo() */
extern void      mvSetFrameDisplay  ( DMboolean    showframes );
extern DMboolean mvGetFrameDisplay  ( void );

/* MV_EVENT_SLOW_PLAY events are no longer sent */
/* Use FRAME_SKIPPED or FRAME_REPEATED warning events instead */
extern void      mvSetSlowThreshold ( double slowthresh );
extern double    mvGetSlowThreshold ( void );

#ifdef __cplusplus
}
#endif
#endif /* !__MOVIEPLAY_H__ */
