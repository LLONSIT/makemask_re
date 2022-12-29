#ifndef __INC_PLUG_IN_MGR_H__
#define __INC_PLUG_IN_MGR_H__  
    
/*****************************************************************************
*
*  Copyright 1996, Silicon Graphics, Inc.
*  All Rights Reserved.
*
*  This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics, Inc.;
*  the contents of this file may not be disclosed to third parties, copied or
*  duplicated in any form, in whole or in part, without the prior written
*  permission of Silicon Graphics, Inc.
*
*  RESTRICTED RIGHTS LEGEND:
*  Use, duplication or disclosure by the Government is subject to restrictions
*  as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data
*  and Computer Software clause at DFARS 252.227-7013, and/or in similar or
*  successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -
*  rights reserved under the Copyright Laws of the United States.
* 
*****************************************************************************/

#include <dmedia/fx_buffer.h>		/* DMfxbuffer */

#include <Xm/Xm.h>
#include <dmedia/dm_params.h>
#include <dmedia/moviefile.h>		/* MVid, MVtime, MVtimescale */

#ifdef __cplusplus
extern "C" {
#endif

#define DM_IMAGE_ROWBYTES   "DM_IMAGE_ROWBYTES"

typedef struct __DMplugmgr  DMplugmgr;	/* 1 only */
typedef struct __DMeffect   DMeffect;	/* 1 per "filtered" clip */
typedef struct __DMplugin   DMplugin;	/* 1 per dso on system */

/* plug-in type (used as a bitmask also) */
typedef enum {
    DM_VIDEO_FILTER	= 1,
    DM_VIDEO_TRANSITION	= 2,
    DM_AUDIO_FILTER	= 4,
    DM_ALL_PLUGIN_TYPES	= 0xFFFFF   /* Can't use -1, enums are unsigned */
} DMplugintype;

typedef enum {
    DM_TRACK_A	= 1,
    DM_TRACK_B	= 2
} DMplugintrack;

/*
 * Applications must supply a callback method that will fill in the data
 * and size for the entire source clip.
 */
				 
typedef DMstatus (*DMaudiocallback)	(
    void *clientData, 
    int firstByte, 
    int size, 
    unsigned char *samples);

typedef DMstatus (*DMvideocallback)	(
    void *clientData, 
    int frame,
    DMplugintrack track,    /*	DM_TRACK_A for filters, 
				DM_TRACK_A or DM_TRACK_B for transitions */
    int width, 
    int height, 
    int rowBytes, 
    unsigned char *data);

/*
** During processing an image clip or loading in a directory of plugins, 
** a callback function is invoked periodically for two purposes:
**
**  (1) It can give feedback to the UI on how far things have
**      progressed, and 
**
**  (2) It can indicate that the processing should be cancelled.  If
**      it is cancelled, the destination track is restored to its
**      original state.
**
** If the function returns DM_TRUE, that means to continue processing.
*/

typedef DMboolean (DMprogresscallback)(
    float fractionComplete,		/* in the range 0.0 to 1.0 */
    void* clientData);

/*
 * dmPMCreateManager returns an plugin of the plugin manager.
 * Should be able to pass in NULL for appShellWidget, when you
 * don't need a UI (mvfilter).  Will return NULL if it fails.
 * If you pass in NULL, then dmPMCreateManager will create an
 * app shell widget for you.
 */
DMplugmgr *dmPMCreateManager(
    Widget appShellWidget);
    
void dmPMDestroyManager(
    DMplugmgr *	pim);

/*
 * dmPMGetAppShell() returns the appShellWidget used by the plugin manager.
 *
 * If an application passes dmPMCreateManager() a non-null widget,
 * that appShellWidget is returned.
 * If an application passes in NULL to dmPMCreateManager(), then
 * the "constructed" appShellWidget is returned.
 */
Widget dmPMGetAppShell(
    DMplugmgr *	pim);

/*
 * dmPMInitDirectory returns the number of plug-ins loaded.
 * You can call dmPMInitDirectory as many times as necessary.  
 * If you pass in NULL, should it check some default directories?
 * 
 * Need some set default directory (or set of default directories) 
 * where the plugins are stored, so applications know where to look.
 *
 * Should there be some policy and/or higher-level components for
 * adding new directories of plugins.
 *
 */
DMplugin **dmPMInitDirectory(
    DMplugmgr *	    pim, 
    const char *    dirName, 
    unsigned int    typemask);
    
DMplugin **dmPMInitDirectoryWithProgress(
    DMplugmgr *		    pim, 
    const char *	    dirName, 
    unsigned int	    typemask, 
    DMprogresscallback *    progressCallback,
    void *		    progressClientData);
    
/*
 * dmPMInitPlugin is another way of initializing a plugin, it returns a
 * pointer to the plugin.
 * dmPMUnLoadPluginDso can be used after a dmPMInitDirectory call as well.
 */ 
DMplugin *dmPMInitPlugin(
    DMplugmgr *, 
    const char *);
    
DMstatus dmPMFreePlugin(
    DMplugmgr *, 
    DMplugin *);

DMstatus dmPMFreeAllPlugins(
    DMplugmgr *);

/*
 * dmPMGetPluginCount returns the number of plug-ins initialized.
 */
int dmPMGetPluginCount(
    DMplugmgr *);
    
/*
 * dmPMGetPlugin gets the nth plugin.
 * dmPMGetPluginByName gets the plugin with this name and prefix.
 * If prefix is NULL, it returns the first plugin with that name.
 */
DMplugin *dmPMGetPlugin(
    DMplugmgr *, 
    int n);

DMplugin *dmPMGetPluginFromEffect(
    DMeffect *);

DMplugin *dmPMGetPluginByName(
    DMplugmgr *, 
    const char *name, 
    const char *prefix);

DMplugin *dmPMGetPluginByPathname(
    DMplugmgr *, 
    const char *pathname);

/*
 * dmPMGetDefaultPluginPathForType:
 * - On success, returns the default path for plugins of type pluginType.
 *   The return value is allocated via "malloc", and should be freed (free()).
 * - On failure, returns NULL, and sets the dm error code (see dmGetError).
 *
 * pluginType must be exactly one of DM_VIDEO_FILTER, DM_VIDEO_TRANSITION, or
 * DM_AUDIO_FILTER.  Note that this usage of pluginType does NOT allow
 * a bit mask of types.  You can only specify one type at a time.
 *
 * On success, the return value should be "freed" (see free()).
 */
char *dmPMGetDefaultPluginPathForType(
    unsigned int pluginType);

/*
 * dmPMSortByName: sorts the list of plugins by the name field.  Typically
 * used after a call to loadDirectory(), but can be used at anytime.
 *
 * dmPMSortByPrefix: sorts the list of plugins by a concatenation of
 * the prefix and name of the plugin.
 */
void dmPMSortByName(
    DMplugmgr *);
    
void dmPMSortByPrefix(
    DMplugmgr *);

/*
 * dmPMGetName returns the name of the plugin.
 * dmPMGetLocalName returns the localized name (french, japanese, etc)
 *                  for use in the user interface.
 * dmPMGetPrefix returns the prefix (vendor name) of the plugin.
 * dmPMGetPathname returns the pathname of the plugin on disk.
 * dmPMGetType returns the plugin type (i.e. DM_AudioFilter).
 */
const char *dmPMGetName(
    DMplugin *plugin);
    
const char *dmPMGetLocalName(
    DMplugin *plugin);
    
const char *dmPMGetPrefix(
    DMplugin *plugin);
    
const char *dmPMGetPathname(
    DMplugin *plugin);
    
DMplugintype dmPMGetType(
    DMplugin *plugin);

/*
 * dmPMGetSourceAUsage returns a bitmask of the following values:
 *  DM_BUF_INPUT_DIRECT	    - reads from void *data
 *  DM_BUF_INPUT_TEXTURE    - uses OpenGL texturing
 *  DM_BUF_INPUT_DRAWPIXELS - uses OpenGL pixel drawing
 *  DM_BUF_INPUT_MOVIE	    - used only by application
 *  DM_BUF_INPUT_ALL	    - may use any kind of input
 */
int dmPMGetSourceAUsage(
    DMplugin *plugin);
 
/*
 * dmPMGetSourceBUsage returns a bitmask of the following values:
 *  DM_BUF_INPUT_DIRECT	    - reads from void *data
 *  DM_BUF_INPUT_TEXTURE    - uses OpenGL texturing
 *  DM_BUF_INPUT_DRAWPIXELS - uses OpenGL pixel drawing
 *  DM_BUF_INPUT_MOVIE	    - used only by application
 *  DM_BUF_INPUT_ALL	    - may use any kind of input
 */
int dmPMGetSourceBUsage(
    DMplugin *plugin);
 
/*
 * dmPMGetDestUsage returns a bitmask of the following values:
 *  DM_BUF_OUTPUT_DIRECT    - writes to void *data
 *  DM_BUF_OUTPUT_OPENGL    - renders with OpenGL
 *  DM_BUF_OUTPUT_MOVIE	    - used only by application
 */
int dmPMGetDestUsage(
    DMplugin *plugin);

/*
 * dmPMGetProperty tries to retrieve the value of the property
 * that is passed in. It returns DM_FALSE if the property was not
 * found or if an error occured.
 */
DMboolean dmPMGetProperty(
    DMplugin *plugin, 
    int property, 
    void **value);
    
/*
 * dmPMHasDialog returns True if the plugin's setup routine launches
 * a dialog.
 */
DMboolean dmPMHasDialog(
    DMplugin *);

/*
 * dmPMCreateEffect and dmPMCreateEffectByName return a plugin instance.
 */
DMeffect *dmPMCreateEffect(
    DMplugmgr *, 
    DMplugin *);

/*
 * dmPMCreateEffectByName creates an effect of the plugin with name
 * and prefix.  prefix can be NULL.
 */
DMeffect *dmPMCreateEffectByName(
    DMplugmgr *, 
    const char *name, 
    const char *prefix);

/*
 * dmPMDestroyEffect frees any memory that the DMeffect occupied
 */
DMstatus dmPMDestroyEffect(
    DMeffect *);

/*
 * dmPMSetAudioCallback sets the callback and clientData
 * for audio filters only
 */
DMstatus dmPMSetAudioCallback(
    DMeffect *, 
    DMaudiocallback, 
    void *clientData);

/*
 * dmPMSetVideoCallback sets the callback and clientData
 * for video filters and transitions
 */
DMstatus dmPMSetVideoCallback(
    DMeffect *, 
    DMvideocallback, 
    void *clientData);

/*
 * DMrestoreFromByteStream is generally called after reading from a 
 * file.  It is used instead of dmPMCreateEffect.
 * Question:  Can we call this w/o calling dmPMInitDirectory first?
 * If so,  would this call a dmPMInitPlugin then?  yes, yes (probably).
 */
DMeffect *dmPMCreateFromByteStream(
    DMplugmgr *, 
    void *data, 
    size_t numBytes);

/*
 * dmPMConvertToByteStream is generally called before writing to a file.
 * Caller is responsible for freeing the data.
 */
DMstatus dmPMConvertToByteStream(
    DMeffect *, 
    void **data, 
    size_t *numBytes);

/******************************************************************************
 * 
 *  SETUP calls - may provide a blocking dialog
 * 
 ******************************************************************************/

DMstatus dmPMSetupVideoFilter(	
    DMeffect *effect, 
    void *src, 
    DMparams *srcParams, 
    unsigned int part, 
    unsigned int total);

DMstatus dmPMSetupVideoTransition(
    DMeffect *effect, 
    void *srcA, 
    DMparams *srcAParams, 
    void *srcB, 
    DMparams *srcBParams, 
    unsigned int part, 
    unsigned int total);

/*
 * audio srcParams should include samples per second (DM_AUDIO_RATE)
 */
DMstatus dmPMSetupAudioFilter(	
    DMeffect *effect, 
    unsigned char *src, 
    DMparams *srcParams, 
    int firstByte,	    /* first sample byte offset */
    int size,		    /* size of source in bytes */
    int total);		    /* total bytes of audio in clip */


DMstatus dmPMBufferSetupVideoFilter(
    DMeffect *effect, 
    DMfxbuffer *srcBuffer, 
    DMparams *srcParams, 
    unsigned int part, 
    unsigned int total);

DMstatus dmPMBufferSetupVideoTransition(
    DMeffect *effect, 
    DMfxbuffer *srcABuffer,
    DMparams *srcAParams, 
    DMfxbuffer *srcBBuffer, 
    DMparams *srcBParams, 
    unsigned int part, 
    unsigned int total);

/******************************************************************************
 * 
 *  EXECUTE calls
 * 
 ******************************************************************************/

DMstatus dmPMExecuteVideoFilter(	
    DMeffect *effect,
    void *src, 
    DMparams *srcParams, 
    void *dst, 
    DMparams *dstParams, 
    unsigned int part, 
    unsigned int total);

DMstatus dmPMExecuteVideoTransition(  
    DMeffect *effect,
    void *srcA, 
    DMparams *srcAParams, 
    void *srcB, 
    DMparams *srcBParams, 
    void *dst, 
    DMparams *dstParams, 
    unsigned int part, 
    unsigned int total);
				    
DMstatus dmPMExecuteAudioFilter(	
    DMeffect *effect, 
    unsigned char *src, 
    DMparams *srcParams, 
    unsigned char *dst, 
    DMparams *dstParams, 
    int firstByte,	    /* first sample byte offset */
    int size,		    /* size of source in bytes */
    int total);		    /* total bytes of audio in clip */

DMstatus dmPMBufferExecuteVideoFilter(
    DMeffect *effect, 
    DMfxbuffer *srcBuffer,
    DMparams *srcParams, 
    DMfxbuffer *dstBuffer,
    DMparams *dstParams, 
    unsigned int part, 
    unsigned int total);

DMstatus dmPMBufferExecuteVideoTransition(
    DMeffect *effect, 
    DMfxbuffer *srcABuffer,
    DMparams *srcAParams, 
    DMfxbuffer *srcBBuffer,
    DMparams *srcBParams, 
    DMfxbuffer *dstBuffer,
    DMparams *dstParams, 
    unsigned int part, 
    unsigned int total);

DMstatus dmPMBufferExecuteVideoFilterOnField(
    DMeffect *effect, 
    DMboolean isEvenField,
    DMfxbuffer *srcBuffer,
    DMparams *srcParams, 
    DMfxbuffer *dstBuffer,
    DMparams *dstParams, 
    unsigned int part, 
    unsigned int total);

DMstatus dmPMBufferExecuteVideoTransitionOnField(
    DMeffect *effect,
    DMboolean isEvenField,
    DMfxbuffer *srcABuffer,
    DMparams *srcAParams, 
    DMfxbuffer *srcBBuffer,
    DMparams *srcBParams, 
    DMfxbuffer *dstBuffer,
    DMparams *dstParams, 
    unsigned int part, 
    unsigned int total);

/******************************************************************************
 * 
 *  CLEANUP calls
 * 
 ******************************************************************************/

DMstatus dmPMCleanupVideoFilter(
    DMeffect *);
    
DMstatus dmPMCleanupVideoTransition(
    DMeffect *);
    
DMstatus dmPMCleanupAudioFilter(
    DMeffect *);

/***********************************************************************
**
** Movie processing functions
**
***********************************************************************/

/*
** These operation types tell dmPMProcessImageClip what to do.  They are
** treated as postfix operations on a stack machine (like PostScript).
*/

typedef enum 
{
    DM_MOVIE,		/* Use a movie as a source clip (push). */
    DM_TRACK,		/* Use one track of a movie as a source clip (push). */
    DM_FILTER,		/* Apply a filter. (replace top of stack) */
    DM_TRANSITION	/* Apply a transition. (replace top two with one) */
} DMoptype;

typedef struct __DMprocessop
{
    DMoptype		type;
    
    MVid		movie;		/* movies */
    MVid		track;		/* tracks */
    MVtime		startTime;	/* movies and tracks */

    DMeffect*		effect;		/* filters and transitions */
    int			totalFrames;	/* # of frames f/t is applied to */
    int			startFrame;	/* first frame processed */
} DMprocessop;

extern DMstatus dmPMProcessImageClip(
    DMprocessop*	arrayOfOperations,
    int			numberOfOperations,
    DMboolean		callSetup, 
    MVtimescale		timescale,
    MVtime		frameDuration,
    MVtime		movieDuration,
    MVid		destinationTrack,
    MVtime		destinationStartTime
    );

extern DMstatus dmPMProcessImageClipWithProgress(
    DMprocessop*	arrayOfOperations,
    int			numberOfOperations,
    DMboolean		callSetup, 
    MVtimescale		timescale,
    MVtime		frameDuration,
    MVtime		movieDuration,
    MVid		destinationTrack,
    MVtime		destinationStartTime,
    DMprogresscallback*	progressCallback,
    void*		progressClientData
    );


#ifdef __cplusplus
}
#endif

/**********************************************************************
*
* Plugin Manager Error Codes
*
* These are obtained from dmGetErrno().
*
**********************************************************************/

#define DM_ERROR_INTERNAL		(DMEDIA_PM_ERROR_BASE + 1)
#define DM_ERROR_BAD_PROCESS_OP		(DMEDIA_PM_ERROR_BASE + 2)
#define DM_ERROR_PROCESS_STOPPED	(DMEDIA_PM_ERROR_BASE + 3)
#define DM_ERROR_NO_MEMORY		(DMEDIA_PM_ERROR_BASE + 4)
#define DM_ERROR_NO_MANAGER		(DMEDIA_PM_ERROR_BASE + 5)
#define DM_ERROR_NO_PLUGIN		(DMEDIA_PM_ERROR_BASE + 6)
#define DM_ERROR_NO_EFFECT		(DMEDIA_PM_ERROR_BASE + 7)
#define DM_ERROR_NO_BUFFER		(DMEDIA_PM_ERROR_BASE + 8)
#define DM_ERROR_OTHER			(DMEDIA_PM_ERROR_BASE + 9)
#define DM_ERROR_BAD_PART_TOTAL		(DMEDIA_PM_ERROR_BASE + 10)
#define DM_ERROR_MISSING_PARAMS		(DMEDIA_PM_ERROR_BASE + 11)
#define DM_ERROR_BAD_PARAMS 		(DMEDIA_PM_ERROR_BASE + 12)
#define DM_ERROR_BAD_TYPE		(DMEDIA_PM_ERROR_BASE + 13)

/**********************************************************************
 *
 * Plugin Properties
 *
 **********************************************************************/

#define DM_PLUGIN_DEBUGGING	    1100    /* Bool: show warning messages + */
#define DM_PLUGIN_DESCRIPTION	    1200    /* char *: Long description text ! */
#define DM_PLUGIN_IS_VARIABLE	    1500    /* Bool: Varies with time, space, etc. + */
#define DM_PLUGIN_VERSION	    2000    /* major.minor: Plugin version */
#define DM_PLUGIN_IMAGE_FORMATS     3003    /* uint: Buffer Format */
#define DM_PLUGIN_INTRODUCES_ALPHA  4000    /* Bool: the plugin introduces alpha + */

/***********************************************************************
 * 
 * Usage bits
 * 
 ***********************************************************************/

/* Buffer Input Usage */
#define DM_BUF_INPUT_DIRECT	    0x0001  /* reads from void *data */
#define DM_BUF_INPUT_TEXTURE	    0x0002  /* uses OpenGL texturing */
#define DM_BUF_INPUT_DRAWPIXELS	    0x0004  /* uses OpenGL pixel drawing */
#define DM_BUF_INPUT_MOVIE	    0x0008  /* used only by application */
#define DM_BUF_INPUT_ALL	    0xFFFF  /* may use any kind of input */

/* Buffer Output Usage */
#define DM_BUF_OUTPUT_DIRECT	    0x0001  /* writes to void *data */
#define DM_BUF_OUTPUT_OPENGL	    0x0002  /* renders with OpenGL */
#define DM_BUF_OUTPUT_MOVIE	    0x0004  /* used only by application */

#endif /* ! __INC_PLUG_IN_MGR_H__  */
