//////////////////////////////////////////////////////////////////////////////
//
// Copyright 1995, Silicon Graphics, Inc.   All Rights Reserved.
//
// This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics, Inc.;
// the contents of this file may not be disclosed to third parties, copied or
// duplicated in any form, in whole or in part, without the prior written
// permission of Silicon Graphics, Inc.
//
// RESTRICTED RIGHTS LEGEND:
// Use, duplication or disclosure by the Government is subject to restrictions
// as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data
// and Computer Software clause at DFARS 252.227-7013, and/or in similar or
// successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -
// rights reserved under the Copyright Laws of the United States.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef VKMOVIEPLAYER_H
#define VKMOVIEPLAYER_H

// VkMoviePlayer.h

#include <Vk/VkComponent.h>
#include <GL/glx.h>

class VkMoviePlayer : public VkComponent {

  public:

    static const char *const movieFinishedCallback;    

    VkMoviePlayer(const char * name,
		  Widget parent,
                  char *movieFilename = NULL);

    virtual ~VkMoviePlayer();
    virtual const char* className();

    void setMute (Boolean m=False);

    char*   movieFileName() const		{ return _movieFileName; };
    void    setMovieFileName(const char *);

    Boolean mpeg() const			{ return _mpeg;          };
    void *  movieId() const			{ return _mvid;		 };
    void *  imageTrack() const			{ return _imageTrack;    };
    void *  audioTrack() const			{ return _audioTrack;    };
    pid_t   audioPid() const                    { return _audioPid;      };

    static VkComponent *CreateVkMoviePlayer(const char *, Widget);

    virtual void play();
    virtual void play(Boolean);    
    virtual void stop();
    virtual void rewind();    
    virtual void resize(Widget, XEvent*);
    virtual void    drawFrame(int n = 0);
    virtual void    playFrame();
    virtual void    glInit(Widget);

    
  private:

    static XtTranslations _tt;
    static XtActionsRec   _actions[];
    static char           _ttDraw[];
    static String         _defaultResources[];

    Widget _form;
    Boolean      _initialized, _muted, _playing, _mpeg;
    Widget       _glDraw;
    GLXContext   _glContext;

    char         *_movieFileName;
    void *        _mvid, *_imageTrack, *_audioTrack;
    int           _mvWidth, _mvHeight;
    int           _totalFrames;
    unsigned long _frameRateMS;
    void*         _frame;
    size_t        _frameSz;
    int           _currentFrame;
    pid_t         _audioPid;
    XtIntervalId _intervalId;
    

    Boolean build();

    void startTimer();
    void stopTimer();

    // callbacks
    
    static void glInitCB(Widget, XtPointer, XtPointer);
    static void exposedCB(Widget, XtPointer, XtPointer);
    static void resizeCB(Widget, XtPointer,  XEvent*, Boolean*);    
    static void intervalCB(XtPointer, XtIntervalId*);
    static void *RegisterVkMoviePlayerInterface();        
};

#endif
