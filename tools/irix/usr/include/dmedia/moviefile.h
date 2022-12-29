/*****************************************************************************
 *
 * SGI movie library 
 *
 * moviefile.h
 *	header file for use with /usr/lib/libmovie.a
 *      movie file I/O interface
 *
 * Copyright 1992 & 1993, Silicon Graphics, Inc.
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

#ifndef __MOVIEFILE_H__
#define __MOVIEFILE_H__

#ident "$Revision: 1.156 $"

#include <fcntl.h>		/* for O_RDONLY, O_RDWR */
#include <limits.h>             /* for LONG_MAX */
     
#include <dmedia/dmedia.h>
#include <dmedia/dm_audio.h>
#include <dmedia/dm_image.h>
#include <dmedia/dm_params.h>
#include <dmedia/dm_buffer.h>

#include <X11/Xlib.h>

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
* MVid
*
* Used to identify objects inside the movie library:
*
*   Movies
*   Tracks
*   Images (not yet supported)
*
********/

typedef void *MVid;

/*
** Special value for mvSetPrimaryAudio().  This is a value that
** is never a valid movie ID.
*/

#define MV_PRIMARY_AUDIO_NOTSET (void *)7

/********
*
* MVfileformat
*
* Defines the format of a movie file on the disk (or wherever it may
* be).  
*
********/

typedef enum __MVfileformat
{
    MV_FORMAT_SGI_1	= 0,	/* SGI format -- version 1 */
    MV_FORMAT_SGI_2	= 1,	/* SGI format -- version 2 */
    MV_FORMAT_SGI_3	= 2,	/* SGI format -- version 3 */
    MV_FORMAT_QT	= 3,	/* Apple     QuickTime */
    MV_FORMAT_OMFI	= 4,	/* Avid      OMFI (not supported) */
    MV_FORMAT_AVI	= 5,	/* Microsoft AVI */
    MV_FORMAT_MPEG1	= 6,	/* MPEG1 (ISO 11172) */
    MV_FORMAT_DIF	= 7	/* DIF format DV file */
} MVfileformat;

/********
*
* MVloopmode
*
********/

typedef enum __MVloopmode
{
    MV_LOOP_NONE	= 0,
    MV_LOOP_CONTINUOUSLY= 1,
    MV_LOOP_SWINGING	= 2
} MVloopmode;

/*
 * MVdirection
 */
typedef enum __MVdirection
{
    MV_FORWARD  = 0,
    MV_BACKWARD = 1
}MVdirection;

/*
 * MVboundary
 */
typedef enum __MVboundary
{
    MV_FRAME = 0,
    MV_KEYFRAME = 1,
    MV_TRACKDATA = 2,
    MV_EDITATOM = 3
} MVboundary;

/*
 * data type needs to be refined at some point
 * probably should assign a few bits to each type of data type
 * frame type is definitely one of them, and for now, only worry about those
 */
typedef int MVdatatype;

#define MV_FRAMETYPE_MASK	0x0003
#define MV_FRAMETYPE_BETWEEN	DM_IMAGE_TYPE_BETWEEN
#define MV_FRAMETYPE_DELTA	DM_IMAGE_TYPE_INTER
#define MV_FRAMETYPE_KEY	DM_IMAGE_TYPE_INTRA

/*
** The MV_LOOP_COUNT parameter has a special setting that means to
** loop forever (passed into mvSetLoopLimit).
*/

#define MV_LIMIT_FOREVER		0

/*
 * MV_IMAGE_STRIDE
 * - macro for RenderToImageBuffer format params
 */
#define MV_IMAGE_STRIDE "MV_IMAGE_STRIDE"

/*
 * MV_BLEND_*
 */
#define MV_BLEND_SRC 		"MV_BLEND_SRC"
#define MV_BLEND_DST 		"MV_BLEND_DST"
#define MV_BLEND_EQUATION 	"MV_BLEND_EQUATION"
#define MV_BLEND_COLOR_RED 	"MV_BLEND_COLOR_RED"
#define MV_BLEND_COLOR_GREEN 	"MV_BLEND_COLOR_GREEN"
#define MV_BLEND_COLOR_BLUE 	"MV_BLEND_COLOR_BLUE"
#define MV_BLEND_ALPHA 		"MV_BLEND_ALPHA"

/*
 * MVostype. Why this is call OSType in the QuickTime 2.0, Developer Guide
 * for Macintosh I don't know, it should be call MVreferenceTypes because it 
 * defines how one track is referenced by another.
 * If you add more types, please remember to suitably modify 
 * MV_REFERENCE_TYPES
 */
typedef enum _MVostype {
    MV_TIMECODE_REF  = 1
} MVostype;
#define MV_REFERENCE_TYPES (MV_TIMECODE_REF+1)

/*
 * MV_CUSTOM_*
 * - used for custom codec support
 */
#define MV_CUSTOM_IMAGE		"MV_CUSTOM_IMAGE"
#define MV_CUSTOM_AUDIO		"MV_CUSTOM_AUDIO"

/*
 * query attributes to be passed to the mvQuery calls
 */
/* level 1 selectors */
#define MV_QUERYTYPE_FILEFMT           500
#define MV_QUERYTYPE_COMPRESSION       501

/* level 2 selectors */
#define MV_QUERY_NAME		       600
#define MV_QUERY_ID_COUNT	       601
#define MV_QUERY_IDS		       602
#define MV_QUERY_SUPPORTED             603

/********
*
* Public Movie structures
* MVframe, MVtime, MVtimescale, MVmatrix2d, MVrect
*
********/

#define MV_MATRIX_2D_SIZE 3

typedef int 		MVframe;
typedef long long	MVtime;
typedef int		MVtimescale;
typedef float		MVmatrix2d[MV_MATRIX_2D_SIZE][MV_MATRIX_2D_SIZE];
/* we probably want 3D matrices later... */

typedef struct tagMVrect{
    int		left, bottom;
    int		right, top;
}MVrect;

/*
** Special value for MVframe and MVtime
*/

#define MV_FRAME_MAX   INT_MAX
#define MV_TIME_MAX    LONGLONG_MAX

/*
 * mode masks for opening files
 */
#define MV_OPEN_FILE_MASK	0xffff
#define MV_MPEG_PRESCAN_MASK	0x10000
#define MV_MPEG_AUDIO_BANDWIDTH_MASK	0x60000

/*
 * Prescan Mode (is prescan off?)
 */
#define MV_MPEG1_PRESCAN_OFF	0x10000

/*
 * MVaudiobandwidth Modes
 */
typedef enum {
 MV_MPEG1_AUDIO_BANDWIDTH_FULL=0x60000,
 MV_MPEG1_AUDIO_BANDWIDTH_HALF=0x40000,
 MV_MPEG1_AUDIO_BANDWIDTH_QUARTER=0x00000
 }MVaudiobandwidth;

/**********************************************************************
*
* Error Handling Functions
*
**********************************************************************/

extern int         mvGetErrno( void );
extern const char* mvGetErrorStr( int ); /* Takes an int errno value */
extern void	   mvClearErrno( void );

/**********************************************************************
*
* Movie Functions
*
* A movie is a set of tracks.  The data in the tracks is stored in a
* storage medium (such as a file).
*
* The operations that can be performed on a movie include:
*
*   1) Creating a new movie instance by either opening an existing 
*      file or by creating a new movie file.
*
*   2) Adding, Removing, and Finding tracks.
*
*   3) Getting and setting the properties (tags) of the movie.
*
*   4) Destroying a movie instance, which flush any changes made
*      out to the file.
*
*   Note : MPEG-1 movies may be opened and read, but not edited.
*
* The settable properties of a movie are:
*
*    * File format (SGI, QuickTime, etc.)
*    * Looping mode and number of loops.
*    * Title, Comment.
*
* The read-only properties of a movie are: 
* (these are computed by the library) 
*
*    * Maximum image width, height, frames-per-second.
*    * Number of image tracks.
*    * Number of audio tracks.
*
* Some aspects of opening movies may be configured.
*
*    * Prescan (scan the movie for frame info as it is opened)
*    * Audio bandwidth (bandwidth to use in opening movie)
*
**********************************************************************/

extern DMstatus  mvSetMovieDefaults	( DMparams*	params,
					  MVfileformat	format );

extern DMstatus mvQueryInt(               int           querytype,
					  int           arg1,
					  int           arg2,
					  int           arg3,
					  int           *returnValue );
extern DMstatus mvQueryDouble(            int           querytype,
					  int           arg1,
                 		          int           arg2,
					  int           arg3,
					  double        *returnValue );
extern DMstatus mvQueryPointer(           int           querytype,
					  int           arg1,
					  int           arg2,
					  int           arg3,
					  void          **returnValue );

extern int 	     mvGetTrackId	   ( MVid track );

extern DMboolean mvIsMovieFile		( const char*	filename );
extern DMstatus  mvCreateFile		( const char*	filename,
					  const DMparams*	params,
					  DMparams*	returnParamsSetOrNull,
					  MVid*		returnMovie );

extern DMstatus  mvOpenFile		( const char*	filename,
					  int		oflag,
					  MVid*		returnMovie );

extern DMboolean mvIsReadOnly		( MVid		track );

extern DMboolean mvIsAppendOnly		( MVid		track );

extern DMboolean mvIsMovieFD		( int		fd );

extern DMstatus  mvCreateFD		( int		fd, 
					  const DMparams*	params,
					  DMparams*	returnParamsSetOrNull,
					  MVid*		returnMovie );

extern DMstatus  mvOpenFD		( int		fd,
					  MVid*		returnMovie );

extern DMboolean mvIsMovieMem		( void*		pointer,
					  size_t	size );
extern DMstatus  mvCreateMem		( void*		pointer, 
					  size_t	size,
					  const DMparams*	params,
					  DMparams*	returnParamsSetOrNull,
					  MVid*		returnMovie );



extern DMstatus  mvOpenMem		( void*		pointer, 
					  size_t	size,
					  MVid*		returnMovie );

extern DMstatus  mvClose		( MVid		movie );

extern DMstatus  mvDestroyMovie		( MVid		movie );

extern DMstatus  mvWrite		( MVid		movie );

extern DMboolean mvDoesMovieNeedWrite	( MVid		movie );

extern void	 mvGetMovieUserDataListHandle( MVid	movie,
					       DMparams** userDataList );

extern void	 mvGetTrackUserDataListHandle( MVid	track,
					       DMparams** userDataList );

extern DMstatus  mvSetImageDefaults     ( DMparams      *params,
					  int           width,
					  int           height,
					  MVfileformat  format );

extern DMstatus  mvSetAudioDefaults     ( DMparams      *params,
					  int           width,
					  double        rate,
					  int           channels,
					  MVfileformat  format );

extern DMstatus  mvAddTrack		( MVid		movie,
					  DMmedium	type,
					  DMparams*	params,
					  DMparams*	returnParamsSetOrNull,
					  MVid*		returnTrack );

extern DMstatus  mvRemoveTrack		( MVid		movie,
					  MVid		track );

extern DMstatus  mvFindTrackByMedium	( MVid		movie,
					  DMmedium	type,
					  MVid*		returnTrack );

extern DMstatus mvFindTrackByIndex	( MVid		id, 
					  int		trackIndex, 
					  MVid*		returnTrack );

extern int mvGetNumTracks		( MVid		id );

extern DMstatus  mvAddUserParam		( const char*	paramName );

extern DMparams* mvGetParams		( MVid		movieOrTrack );

extern DMstatus  mvSetParams		( MVid		movieOrTrack,
					  DMparams*	params,
					  DMparams*	returnParamsSetOrNull );

extern MVtime mvGetMovieCurrentTime( MVid movie, MVtimescale timeScale );

extern DMstatus mvSetMovieCurrentTime( MVid movie, 
				       MVtime time, MVtimescale timeScale );

extern MVtime mvGetMovieGalleryTime( MVid movie, MVtimescale timeScale );

extern DMstatus mvSetMovieGalleryTime( MVid movie, 
				       MVtime time, MVtimescale timeScale );

extern DMstatus mvSetMovieSelectionTime( MVid movie, 
					 MVtime selectionTime, 
					 MVtime selectionDuration,
					 MVtimescale timeScale );

extern DMstatus mvGetMovieSelectionTime( MVid movie, 
					 MVtime *selectionTime, 
					 MVtime *selectionDuration,
					 MVtimescale timeScale );

extern DMstatus mvSetMoviePreviewTime( MVid movie, 
				       MVtime previewTime, 
				       MVtime previewDuration,
				       MVtimescale timeScale );

extern DMstatus mvGetMoviePreviewTime( MVid movie, 
				       MVtime *previewTime, 
				       MVtime *previewDuration,
				       MVtimescale timeScale );

extern MVtimescale  mvGetMovieTimeScale  ( MVid	   movie );

extern DMstatus  mvSetMovieTimeScale( MVid	   movie,
				      MVtimescale  timeScale );

extern MVtime  mvGetMovieDuration   ( MVid	   movie, 
				      MVtimescale  timeScale );

extern MVtime mvGetEstMovieDuration ( MVid         movie,
				      MVtimescale  timeScale );

extern float mvGetMoviePlayVolume( MVid movie );

extern DMstatus mvSetMoviePlayVolume( MVid movie, float volume );

extern DMstatus  mvOptimize         ( MVid         fromMovie, 
				      MVid         toMovie);

extern DMstatus mvGetMovieBoundary( MVid movie, MVtime time, MVtimescale timeScale,
				    MVdirection Direction, MVboundary Boundary,
				    int numMedia, DMmedium *medium,
				    MVtime *returnTime );

extern DMboolean mvGetMovieGLContextState( MVid movie );
extern DMstatus mvSetMovieGLContextState( MVid movie, DMboolean bGlCtxtState );

extern DMstatus mvRenderMovieToOpenGL( MVid movie, MVtime time, MVtimescale timeScale );

extern DMstatus mvRenderMovieToImageBuffer( MVid movie,
					    MVtime time,
					    MVtimescale timeScale,
					    void *buffer,
					    DMparams *formatParams );

extern size_t   mvGetAudioBufferSize(MVtime duration, MVtimescale scale, DMparams *audioParams);

extern DMstatus mvRenderMovieToAudioBuffer( MVid movie,
					    MVtime time,
					    MVtime duration,
					    MVtimescale timeScale,
					    MVdirection dir, 
                                            size_t bufsz,
                                            size_t *bufszFilled,
                                            MVframe *frames,
					    void *buffer,
					    DMparams *formatParams );

extern DMstatus mvSetMovieMatrix2dIdentity( MVid movie );
extern DMstatus mvSetMovieMatrix2d( MVid movie, MVmatrix2d matrix );
extern DMstatus mvGetMovieMatrix2d( MVid movie, MVmatrix2d matrix );
extern DMstatus mvSetMovieRect( MVid movie, MVrect rect );
extern DMstatus mvGetMovieRect( MVid movie, MVrect *rect );
extern DMstatus mvGetMovieBoundsRect( MVid movie, MVrect *rect, DMboolean enabledTracksOnly );
extern DMstatus mvGetMovieBoundingRect( MVid movie, MVrect *rect );

extern DMstatus mvScaleMovieAtTime( MVid movie, MVtime time, 
				    MVtime duration, MVtimescale timeScale,
				    float scale, DMboolean enabledTracksOnly );
extern DMstatus mvInsertMovieGapAtTime( MVid movie, MVtime time, 
				        MVtime duration, MVtimescale timeScale, 
				        DMboolean enabledTracksOnly );
extern DMstatus mvDeleteMovieAtTime( MVid movie, MVtime time,
				     MVtime duration, MVtimescale timeScale, 
				     DMboolean enabledTracksOnly );
extern DMstatus mvCopyMovieAtTime( MVid fromMovie, MVtime fromTime,
				   MVtime fromDuration, MVtimescale fromScale,
				   MVid toMovie, MVtime toTime,
				   MVtimescale toScale,
				   DMboolean byReference, DMboolean enabledTracksOnly );

/*
 * MVexportflags (mvExportFlattenedFile flags)
 */
#define MV_EXPORT_USE_GAPS_MASK    0x0001
#define MV_EXPORT_RECOMPRESS_MASK  0x0006
typedef enum {
    MV_EXPORT_USE_GAPS =           0x0001, /* use Gaps (empty edits) in QT movies. (ignored for other fmts) */
    MV_EXPORT_RECOMP_ALL=          0x0002, /* recompress all frames no matter what (slowest) */
    MV_EXPORT_RECOMP_CHANGED_Q=    0x0004, /* recompress frame if Q value does not match */
    MV_EXPORT_RECOMP_FEWEST=       0x0006  /* don't recompress even if Q value doesn't match. (fastest) */
} MVexportflags;

/*
 * MVoperation
 */
typedef enum __MVoperation
{
    MV_COPY_MOVIE_AT_TIME,
    MV_COPY_TRACK_AT_TIME,
    MV_EXPORT_FLATTENED_FILE
} MVoperation;

/*
 * MVmessage
 */
typedef enum __MVmessage
{
    MV_BEGIN,
    MV_IN_PROGRESS,
    MV_END
} MVmessage;

/*
 * progress function prototype
 */
typedef DMstatus (*MVprogressfunc)( MVid movieBeingProcessed, 
                                    MVmessage message, 
				    MVoperation, 
				    float fraction, 
				    int clientData);

extern DMstatus mvExportFlattenedFile( MVid srcMovie, 
				       const char *dstFilename,
				       DMparams *fileExportParams, 
				       DMparams *imageExportParams, 
				       DMparams *audioExportParams,
                                       unsigned int exportFlags, 
				       MVprogressfunc progressCallback,
				       int progressClientData);



/**********************************************************************
*
* Track Functions
*
* The only kind of track that we support now is an evenly spaced (in
* time) sequence of frames, where each of the frames is the same size.
* (Although the size may vary after compression.)
*
* The operations that can be performed on a track include:
*
*   1) Writing frames (either inserting or overwriting).
*
*   2) Reading frames
*
*   3) Editing operations (copying from one movie to another).  These
*      are equivalent to reading and then writing but may be
*      implemented more efficiently.)
*
* The settable properties of all tracks are:
*
*    * Compression scheme
*    * Frame rate
*    * Frame format
*    * SMPTE stuff (not supported yet)
*
* The read-only properties of all tracks are:
*
*    * Length (number of frames)
*    * Frame size (in bytes)
*    * Track type (image or audio)
*
* The settable properties of an image track are:
*
*    * Size (width and height)
*
* The settable properties of an audio track are:
*
*    * Frame size
*    * Number of channels
*
**********************************************************************/

/********
*
* Data formats
*
********/

extern DMstatus  mvMapBetweenTracks ( MVid         fromTrack,
				      MVid         toTrack,
				      MVframe      fromFrameIndex,
				      MVframe*     returnToFrameIndex );

/********
*
* Reading and Writing
*
********/

extern DMstatus  mvReadFrames       ( MVid         track,
				      MVframe      frameIndex,
				      MVframe      frameCount,
				      size_t       buffer_size,
				      void*        buffer );

extern DMstatus  mvInsertFrames     ( MVid         track,
				      MVframe      frameIndex,
				      MVframe      frameCount,
				      size_t       buffer_size,
				      void*        buffer );

extern DMstatus mvInsertFramesAtTime( MVid track, 
				      MVtime trackTime, MVtime trackDuration,
				      MVtimescale timeScale,
				      void *buffer, size_t bufferSize, 
				      DMparams *bufferParams,
				      int storedParamsIndex );

extern DMstatus  mvDeleteFrames     ( MVid         track,
				      MVframe      frameIndex,
				      MVframe      frameCount );
				     
extern DMstatus mvDeleteFramesAtTime( MVid track, MVtime trackTime, 
				      MVtime trackDuration, MVtimescale TimeScale );

extern DMstatus  mvPasteFrames      ( MVid         fromTrack,
				      MVframe      fromFrameIndex,
				      MVframe      fromFrameCount,
				      MVid         toTrack,
				      MVframe      toFrameIndex );

extern DMstatus mvInsertTrackGapAtTime( MVid track, MVtime time, 
				        MVtime duration, MVtimescale timeScale );
extern DMstatus mvScaleFramesAtTime( MVid track, MVtime time, MVtime duration, 
				     MVtimescale timeScale, float scale );
extern DMstatus mvCopyFramesAtTime( MVid srcTrack, MVtime srcTime, 
				    MVtime srcDuration, MVtimescale srcTimeScale,
				    MVid dstTrack, MVtime dstTime,
				    MVtimescale dstTimeScale,
				    DMboolean byReference );

float mvGetTrackScaleAtTime( MVid track, 
			     MVtime time, MVtimescale timeScale );

extern int mvGetTrackNumDataParams( MVid track );
extern int mvAddTrackDataParams( MVid track, DMparams *params );
extern DMstatus mvSetTrackDataParams( MVid track, 
				      int index, DMparams *params );
extern DMstatus mvGetTrackDataParams( MVid track, 
				      int index, DMparams *params );

extern DMstatus mvReadTrackData( MVid track, int dataIndex,
				 size_t bufferSize, void *buffer );

extern DMstatus mvReadTrackDataFields( MVid track, int dataIndex,
				       size_t sizeFirstBuf, void *bufFirstField,
				       size_t sizeSecondBuf, void *bufSecondField );

extern DMstatus mvInsertTrackData( MVid track, MVframe frames,
				   MVtime time, MVtime duration, MVtimescale timeScale,
				   size_t bufferSize, void *buffer, 
				   MVdatatype dataType, int paramsId );

extern DMstatus mvInsertTrackDataFields( MVid track,
					 MVtime time, MVtime duration, 
					 MVtimescale timeScale,
					 size_t sizeFirstBuf, void *bufFirstField,
					 size_t sizeSecondBuf, void *bufSecondField,
					 MVdatatype dataType, int paramsId );

extern DMstatus mvInsertTrackDataAtOffset( MVid track, MVframe frames,
					   MVtime time, MVtime duration, MVtimescale timeScale,
					   off64_t fileOffset, size_t bufferSize,
					   MVdatatype dataType, int paramsId );

extern DMstatus mvGetTrackDataOffset( MVid          track,
				      int           index,
				      off64_t       *fileOffset );

extern DMstatus mvGetTrackDataInfo( MVid track, int index,
				    size_t *returnSize, int *paramId,
				    MVdatatype *dataType, MVframe *frames );

extern DMstatus mvGetTrackDataFieldInfo( MVid track, int index,
					 size_t *firstField, 
					 off64_t *gap, 
					 size_t *secondField );

extern DMstatus mvSetTrackDataFieldInfo( MVid track, int index,
					 size_t firstField, 
					 off64_t gap, 
					 size_t secondField );

extern DMboolean mvTrackDataHasFieldInfo( MVid track, int index );

extern int mvGetTrackNumDataIndex( MVid track );
extern DMstatus mvGetTrackDataIndexAtTime( MVid track, 
					   MVtime time, MVtimescale timeScale,
					   int *index, MVframe *frameOffset);

extern size_t mvGetTrackMaxDataSize( MVid Track );
extern size_t mvGetTrackMaxFieldSize( MVid pTrack );

extern DMstatus mvSetTrackLayer( MVid track, int layer );
extern int mvGetTrackLayer( MVid track );

/********
*
* Appending
*
********/

extern DMstatus  mvAppendFrames     ( MVid         track,
				      MVframe      frameCount,
				      size_t       buffer_size,
				      void*        buffer );

/********
*
* Track References 
*
********/

extern DMstatus mvAddTrackReference(
					MVid		theTrack,
					MVid		refTrack,
					MVostype	refType,
					long*		addedIndex );
extern DMstatus mvDeleteTrackReference(
					MVid		theTrack,
					MVostype	refType,
					long		index );
extern DMstatus mvSetTrackReference(
					MVid		theTrack,
					MVid		refTrack,
					MVostype	refType,
					long		index );
extern MVid mvGetTrackReference(
					MVid		theTrack,
					MVostype	refType,
					long		index );
extern MVostype mvGetNextTrackReferenceType(
					MVid		theTrack,
					MVostype	refType );
extern long mvGetTrackReferenceCount(
					MVid		theTrack,
					MVostype	refType );

/********
*
* Direct Access to Compressed Images
*
********/

extern size_t    mvGetCompressedImageSize
                                    ( MVid         track,
				      MVframe      frameIndex );
				      
extern DMstatus  mvInsertCompressedImage
                                    ( MVid         track,
				      MVframe      frameIndex,
				      size_t       compressed_size,
				      void*        buffer );

extern DMstatus  mvReadCompressedImage
                                    ( MVid         track,
				      MVframe      frameIndex,
				      size_t       buffer_size,
				      void*        buffer );

/**********************************************************************
*
* Properties of Movies and Tracks
*
* These macros allow easy access to the parameters for a movie or
* track.  They can also be obtained by getting the parameter list
* with mvGetParams and then using the dmParamsGet functions.
*
**********************************************************************/

/********
*
* Movie Properties
*
********/

MVfileformat mvGetFileFormat       ( MVid movie );
MVloopmode   mvGetLoopMode         ( MVid movie );
int          mvGetLoopLimit        ( MVid movie );
const char*  mvGetTitle            ( MVid movie );
const char*  mvGetComment          ( MVid movie );
DMboolean    mvGetOptimized        ( MVid movie );

DMstatus     mvSetLoopMode         ( MVid movie, MVloopmode  mode    );
DMstatus     mvSetLoopLimit        ( MVid movie, int         limit   );
DMstatus     mvSetTitle            ( MVid movie, const char* title   );
DMstatus     mvSetComment          ( MVid movie, const char* comment );

/********
*
* Generic Track Properties
*
********/

MVid	      mvGetTrackMovie		( MVid track );

MVframe      mvGetTrackLength      ( MVid track );

/*
** Special value for track length
*/
#define MV_TRACK_LENGTH_UNKNOWN    -1

/*
** Special value for MPEG duration
*/
#define MV_DURATION_UNKNOWN    -1

MVframe      mvGetScannedLength    ( MVid track );
DMmedium     mvGetTrackMedium      ( MVid track );
const char*  mvGetTrackSMPTEStart  ( MVid track );
DMstatus     mvSetTrackSMPTEStart  ( MVid track, const char* timecode );

DMstatus mvSetTrackTimeScale( MVid track, MVtimescale timeScale );
MVtimescale mvGetTrackTimeScale( MVid track );

MVtime 	     mvGetTrackDuration	   ( MVid track, MVtimescale returnScale );

MVtime 	     mvGetTrackOffset	   ( MVid track, MVtimescale returnScale );
DMstatus     mvSetTrackOffset      ( MVid track, MVtime offset, MVtimescale timeScale  );

int mvGetTrackDisplayWidth( MVid track );
int mvGetTrackDisplayHeight( MVid track );

DMstatus mvSetTrackDisplayWidth( MVid track, int width );
DMstatus mvSetTrackDisplayHeight( MVid track, int height );

float    mvGetTrackPlayVolume( MVid track );
DMstatus mvSetTrackPlayVolume( MVid track, float volume );

DMstatus mvSetTrackEnable( MVid track, DMboolean enable );
DMboolean mvGetTrackEnable( MVid track );

DMstatus mvGetTrackBoundary( MVid track, MVtime time, MVtimescale timeScale,
			     MVdirection Direction, MVboundary Boundary,
			     MVtime *returnTime );

DMstatus mvRenderTrackToOpenGL( MVid track, MVtime time, MVtimescale timeScale );
DMstatus mvSetTrackMatrix2dIdentity( MVid track );
DMstatus mvSetTrackMatrix2d( MVid track, MVmatrix2d matrix );
DMstatus mvGetTrackMatrix2d( MVid track, MVmatrix2d matrix );

/********
*
* Image Track Properties
*
********/

int           mvGetImageWidth      ( MVid imageTrack );
int           mvGetImageHeight     ( MVid imageTrack );
double        mvGetImageRate       ( MVid imageTrack );
const char*   mvGetImageCompression( MVid imageTrack );
DMinterlacing mvGetImageInterlacing( MVid imageTrack );
DMpacking     mvGetImagePacking    ( MVid imageTrack );
DMorientation mvGetImageOrientation( MVid imageTrack );
double        mvGetSpatialQuality  ( MVid imageTrack );
double        mvGetTemporalQuality ( MVid imageTrack );
int           mvGetBitrate         ( MVid imageTrack );
int           mvGetKeyframeRate    ( MVid imageTrack );

DMstatus      mvSetImageRate       ( MVid imageTrack, double rate );
						    
/********
*
* Audio Track Properties
*
********/

DMaudioformat    mvGetAudioFormat     ( MVid audioTrack );
int              mvGetAudioWidth      ( MVid audioTrack );
DMaudiobyteorder mvGetAudioByteOrder  ( MVid audioTrack );
double           mvGetAudioRate       ( MVid audioTrack );
int              mvGetAudioChannels   ( MVid audioTrack );
const char*      mvGetAudioCompression( MVid audioTrack );
double           mvGetDefaultVol      ( MVid audioTrack );

#pragma optional mvGetAudioByteOrder

DMstatus         mvSetDefaultVol      ( MVid audioTrack, double vol );

/*
 * time stuff
 */
MVtime mvConvertTime( MVtime time, MVtimescale timeScale, 
                     MVtimescale newScale );

/**********************************************************************
*
* Error codes
*
* Most Movie Library calls return DM_SUCCESS on success, DM_FAILURE
* on failure. mvGetErrno() returns the last movielib error.
*
* We include our own error codes for things which will be
* caught by the regular errno.  However, they are the same
* numerical values as those assigned to the Unix system errno.
*
**********************************************************************/

#define MV_ARENA_FULL           12            /* shared arena for synchronizing movie tasks is full (ENOMEM) */
#define MV_NO_PROCESS           11            /* no more entries in process table for movie tasks (EAGAIN) */

#define MV_EBASE                2000

#define MV_BAD_ID               ( 1+MV_EBASE) /* "Bad movie or track ID" */
#define MV_NO_RGB               ( 2+MV_EBASE) /* "This machine does not support GL RGB mode. Cannot display movies" */
#define MV_BAD_FORMAT           ( 3+MV_EBASE) /* "File is not a movie file or is an unsupported format" */
#define MV_BAD_MALLOC           ( 4+MV_EBASE) /* "Unable to allocate memory" */
#define MV_BAD_GRAB_GL_NESTING  ( 5+MV_EBASE) /* "mvGrabIrisGL()/mvReleaseIrisGL() called out of order" */
#define MV_READWRITE_REQUIRED   ( 6+MV_EBASE) /* "Editing a movie requires write access to the file" */
#define MV_QT_UNSUPPORTED       ( 7+MV_EBASE) /* "Unsupported QuickTime(tm) Feature: %s" */
#define MV_INTERNAL_ERROR       ( 8+MV_EBASE) /* "Internal movie library error" */
#define MV_NO_TRACK             ( 9+MV_EBASE) /* "No track of requested type" */
#define MV_BAD_TRACK_MEDIUM     (10+MV_EBASE) /* "Only audio and image tracks are supported" */
#define MV_BAD_FRAME_NUMBER     (11+MV_EBASE) /* "Frame number is out of range for track" */
#define MV_BAD_COMP_TYPE        (12+MV_EBASE) /* "Unknown image compression scheme" */
#define MV_UNSUP_COMP_TYPE      (13+MV_EBASE) /* "Unsupported image compression scheme: %s" */
#define MV_FRAME_SIZE_MISMATCH  (14+MV_EBASE) /* "Frame sizes not the same when copying between tracks" */
#define MV_MOVIE_NOT_EMPTY      (15+MV_EBASE) /* "Destination movie in mvOptimize is not empty" */
#define MV_QT_NO_IMAGE          (16+MV_EBASE) /* "A QuickTime(tm) movie must have an image track" */
#define MV_NO_QUICKTIME         (17+MV_EBASE) /* "QuickTime(tm) codecs (libqt) not present" */
#define MV_BAD_AUDIO_PARAMS     (18+MV_EBASE) /* "Bad settings for audio track: %s" */
#define MV_BAD_IMAGE_PARAMS     (19+MV_EBASE) /* "Bad settings for image track: %s" */
#define MV_BAD_MOVIE_PARAMS     (20+MV_EBASE) /* "Bad settings for movie" */
#define MV_MEM_TOO_SMALL     	(21+MV_EBASE) /* "Space for in-memory movie is too small" */
#define MV_CL_ERROR             (22+MV_EBASE) /* "Error in compression library: %s" */
#define MV_BAD_IMAGE_FORMAT     (23+MV_EBASE) /* "Image format not supported for playback" */
#define MV_USER_PARAM_TYPE      (24+MV_EBASE) /* "Values for user parameters must be strings: %s" */
#define MV_PARAM_TYPE           (25+MV_EBASE) /* "Parameter value supplied is of the wrong type: %s" */
#define MV_MPEG1_NO_IMAGE       (26+MV_EBASE) /* "An MPEG-1 movie must have an image track" */
#define MV_MPEG1_UNSUPPORTED    (27+MV_EBASE) /* "Unsupported MPEG-1 feature: %s" */
#define MV_BAD_PARAM            (28+MV_EBASE) /* "Bad parameter passed by user: %s" */
#define MV_TIME_OUT_OF_RANGE    (29+MV_EBASE) /* "Time value is out of range" */
#define MV_UNIMPLEMENTED_FOR_IRISGL (30+MV_EBASE) /* "Function has not been implemented for IrisGL" */
#define MV_NO_VISUAL            (31+MV_EBASE) /* "No suitable visual can be found" */
#define MV_NO_PIXMAP            (32+MV_EBASE) /* "Cannot create Pixmap" */
#define MV_NO_GLPIXMAP          (33+MV_EBASE) /* "Cannot create Open GL Pixmap" */
#define MV_NO_GLXCONTEXT        (34+MV_EBASE) /* "Cannot create Open GL Rendering Context" */
#define MV_ERROR_MAKE_CURRENT   (35+MV_EBASE) /* "Error occured in making rendering context current" */
#define MV_ERROR_OPENGL         (36+MV_EBASE) /* "Error occured in OpenGL rendering" */
#define MV_TRACK_FUNCTION_UNDEFINED (37+MV_EBASE) /* "Function undefined for track object" */
#define MV_EDIT_LIST_ERROR      (38+MV_EBASE) /* "Internal Error: Edit List Corrupted" */
#define MV_UNKNOWN_BOUNDARY     (39+MV_EBASE) /* "Boundary Type Unknown Error" */
#define MV_DL_ERROR             (40+MV_EBASE) /* "Dynamic Linking Error: %s" */
#define MV_PORT_BUSY            (41+MV_EBASE) /* "Port in use" */
#define MV_SCHEDULER_DEAD       (42+MV_EBASE) /* "Scheduler thread died unexpectedly" */
#define MV_OUT_OF_CONTEXT       (43+MV_EBASE) /* "Out of context" */
#define MV_BUFFER_TOO_SMALL     (44+MV_EBASE) /* "Buffer size was not big enough to hold requested data" */
#define MV_PARAM_OUT_OF_RANGE	(45+MV_EBASE) /* "Parameter out of range" */
#define MV_AL_ERROR             (46+MV_EBASE) /* "Audio library error: %s" */
#define MV_OMFI_TOOLKIT_ERROR   (47+MV_EBASE) /* "OMFI Toolkit error: %s" */
#define MV_OMFI_UNSUPPORTED     (48+MV_EBASE) /* "Unsupported OMFI feature: %s" */
#define MV_OMFI_MULTIPLE_Q_TABLES (49+MV_EBASE) /* "Different Q tables detected between frames. Not supported in OMFI files." */
#define MV_VL_ERROR             (50+MV_EBASE) /* "Video Library Error: %s" */
#define MV_ERROR_UNSUPPORTED    (51+MV_EBASE) /* "Unsupported" */
#define MV_USER_CANCELLED_PROC  (52+MV_EBASE) /* "Process was cancelled by user" */
#define MV_NOTHING_RENDERED     (53+MV_EBASE) /* "No data was rendered" */
#define MV_CANNOT_SAVE_AS_SGI   (54+MV_EBASE) /* "Cannot Save Edited Movie as SGI format.  Please flatten to single image/audio tracks or save as another format." */
#define MV_VARIABLE_AUDIO_RATES_PER_TRACK_UNSUPPORTED (55+MV_EBASE) /* "All chunks in an audio track should have the same rate" */
#define MV_NO_LICENSE           (56+MV_EBASE) /* "No license: %s" */
#define MV_AVI_UNSUPPORTED      (57+MV_EBASE) /* "Unsupported AVI Feature: %s" */
#define MV_UNIMPLEMENTED_FOR_OPENGL (58+MV_EBASE) /* "Function not implemented for OpenGL" */
#define MV_FILE_WRITE_FAILED    (59+MV_EBASE) /* "Write to movie file failed (ran out of space)" */
#define MV_FILE_READ_FAILED     (60+MV_EBASE) /* "Read from movie file failed (corrupted file)" */
#define MV_NO_REALTIME_SCHEDULING (61+MV_EBASE) /* "Real-time scheduling disabled.  Run as root (or setuid root) to enable." */
#define MV_FRAME_REPEATED       (62+MV_EBASE) /* "Repeated frame" */
#define MV_FRAME_SKIPPED        (63+MV_EBASE) /* "Skipped frame" */
#define MV_SYNC_UNATTAINABLE    (64+MV_EBASE) /* "Sync ust is too far in the past or is too far in the future." */
#define MV_NO_HARDWARE_ACCELERATION (65+MV_EBASE) /* "No hardware acceleration is available" */
#define MV_DMEDIA_ERROR	        (66+MV_EBASE) /* "Error in the dmedia library: %s" */
#define MV_X11_ERROR            (67+MV_EBASE) /* "X11 Error: %s" */
#define MV_INFO_NOT_AVAILABLE	(68+MV_EBASE) /* "Information requested is not available" */
#define MV_INVALID_DATA_TYPE	(69+MV_EBASE) /* "Data Type of this Data is invalid for the operation" */
#define MV_NO_ALPORT            (70+MV_EBASE) /* "No audio port available" */
#define MV_MISSING_REFERENCE	(71+MV_EBASE) /* "Missing File Reference: %s" */
#define MV_BAD_TIME_SCALE       (72+MV_EBASE) /* "Invalid TimeScale" */
#define MV_ZLIB_INFLATE         (73+MV_EBASE) /* "Zlib inflation failure" */
#define MV_ZLIB_READ            (74+MV_EBASE) /* "Zlib read failure" */
#define MV_ZLIB_INIT            (75+MV_EBASE) /* "Zlib initialization failure" */
#define MV_ZLIB_END             (76+MV_EBASE) /* "Zlib end failure" */
#define MV_QT_UNSUP_HDR_COMP_TYPE (77+MV_EBASE) /* "Unsupported Quicktime(tm) header compression scheme: %s" */
		     
/**********************************************************************
*
* Parameter Name Constants
*
**********************************************************************/

/********
*
* Movie Tags
*
********/

#define MV_FILE_FORMAT          "FILE_FORMAT"
#define MV_LOOP_LIMIT           "LOOP_LIMIT"
#define MV_LOOP_MODE            "LOOP_MODE"
#define MV_TITLE                "TITLE"
#define MV_COMMENT              "COMMENT"
#define MV_OPTIMIZED            "OPTIMIZED"

/********
*
* Generic Track Tags
*
********/

#define MV_TRACK_LENGTH	        "TRACK_LENGTH"
#define MV_SCANNED_LENGTH       "SCANNED_LENGTH"
#define MV_SMPTE_START          "SMPTE_START"

/********
*
* Audio Track Tags
*
********/

#define MV_DEFAULT_VOL          "DEFAULT_VOL"


#ifdef __cplusplus
}
#endif
#endif /* !__MOVIEFILE__H__ */
