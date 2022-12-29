/*_____________________________________________________________________________
 *
 * File:    MovieController.h
 * By:      Ashmeet Sidana
 * Contact: as@sgi.com
 * Date:    3/1/93
 * Purpose: Public include file for movie widget.
 *          Implements a complete viewkit component (i.e. maintains
 *	    same interface as a component but is not dependent on
 *          the viewkit in any way).
 *
 * $Id: MovieController.h,v 1.39 1995/08/04 01:03:56 mad Exp $
 *_____________________________________________________________________________
 */

#ifndef MOVIECONTROLLER_H_INCLUDED
#define MOVIECONTROLLER_H_INCLUDED

#include <X11/Xatom.h>
#include <Xm/Xm.h>

#ifdef MOVIECONTROLLER_OPENGL
#include <GL/glx.h>
#define __MV_OPEN_GL__ 1
#else
#include <gl/glws.h>
#endif

#include <dmedia/moviefile.h>
#include <dmedia/movieplay.h>

#define MOVIECONTROLLER_NUM_MOVIES 25 /*maximum number of simultaneous movies
  				       *currently supported. Can be safely 
                                       *increased and code recompiled.
				       */

#define TRIANGLE_SIZE   25


/*_____________________________________________________________________________
 *
 * class MovieController
 *_____________________________________________________________________________
 */

class MovieController {
  public:
    MovieController ( Widget parent, char *widgetName, char *movieFileName,
		      int zoom, Boolean doDoubleBuffer = False);
    MovieController ( Widget parent, char *widgetName, MVid movieID, char *movieFileName,
		      int zoom, Boolean doDoubleBuffer = False);
    ~MovieController();

    virtual void show ();
    virtual void error(char *msg);
    Widget  baseWidget()			{ return _baseWidget; } ;

    void play   ();
    void stop   ();
    void playEveryFrame();
    void mute   ();
    void rewind ();
    void frmBack();
    void frmFwd ();
    void forwardPlay();
    void reversePlay();
    void reset  ();
    void gotoFrame(MVframe dest);

    MVid getMvid(){return mvid; };

    void setFrameCB   (void (*theFunc)(MVframe)) { frameCBFunc    = theFunc; };
    void setgInitCB   (void (*theFunc)())        { gInitCBFunc    = theFunc; };
    void setZoomUpCB  (void (*theFunc)())        { zoomUpCBFunc   = theFunc; };
    void setZoomDownCB(void (*theFunc)())        { zoomDownCBFunc = theFunc; };
    void setExposeCB  (void (*theFunc)())        { exposeCBFunc   = theFunc; };
    void setStopCB    (void (*theFunc)())        { stopCBFunc     = theFunc; };
    
    int getMvWidth()				{ return (mvWidth); };
    int getMvHeight()				{ return (mvHeight); };


    //
    // this gross hack sets the desired speed that the "play" and
    // "reverse" functions will use.  Use only a positive number;
    // the reverse logic will handle the movie library properly.
    //
    virtual void setPlayRevSpeed(double newPlayRevSpeed);
    
    //
    // X selection mechanism (i.e. cut and paste) support.
    //
    // The MovieController component posts targets for:
    //	    - highlighted region of sound track, for audio applications
    //	    - highlighted region of the movie, for movie applications
    //	    - current image frame at the time copyXXX() invoked, for
    //	      imaging applications.
    //
    // By default, the MovieController component asserts the PRIMARY
    // selection when the user highlights a region using Shift plus
    // left mouse drag.  It also asserts the CLIPBOARD selection for
    // the highlighted region when the user types Control-C.
    //
    // setSelectedRegion() allows the application to highlight the
    // region of sound and movie information to transfer.  Units are
    // in frames of the movie's image track.
    //
    // The MovieController component does not support Paste, as it
    // does not support movie editing.
    //
    virtual void setSelectedRegion( MVframe start, MVframe length );
    virtual void getSelectedRegion( MVframe& start,  MVframe& length );
    virtual void copyPrimary( Time timestamp );
    virtual void copyClipboard( Time timestamp );

    //
    // Allows app to deliberately disown the PRIMARY or CLIPBOARD
    // selections.  The highlighted region remains unaffected.
    //
    // In the case of the PRIMARY selection, the highlighted region
    // remains visible on screen.  An application may call
    // copyPrimary() to restore the PRIMARY selection for the
    // highlighted region.
    //
    // giveUpPrimary() causes the primaryLostCB() (see below)
    // to be invoked.
    //
    virtual void giveUpPrimary( Time timestamp );
    virtual void giveUpClipboard( Time timestamp );
    
    //
    // Applications which wish to know when the PRIMARY selection
    // has been gained or lost by the MovieController can set
    // callbacks to obtain this information.  Applications can
    // find out if the controller still has a highlighted region, but
    // not the PRIMARY selection, by checking the return values
    // of getSelectedRegion().
    // 
    void setPrimaryGainedCB(void (*theFunc)())
	    { primaryGainedCBFunc = theFunc; };
    void setPrimaryLostCB(void (*theFunc)())
	    { primaryLostCBFunc = theFunc; };

  private:
    void newMovieController(Widget parent, char *widgetName,
				    int zoom, Boolean doDoubleBuffer);

    void (*frameCBFunc)    (MVframe);
    void (*gInitCBFunc)    (void);
    void (*zoomUpCBFunc)   (void);
    void (*zoomDownCBFunc) (void);
    void (*exposeCBFunc)   (void);
    void (*stopCBFunc)	   (void);
/*
 * UI state variables
 */
    int  initialized;
    Boolean doubleBuffer;	    // are we double-buffering?
    double playRevSpeed;
    int  playing;
    int  dragging1;
    int  button1Down;
    int  atEnd;
    int  drag_start_x;
    Boolean isLocated;

    int  button2Down;
    int  drag_start_y;

    int frameUpdateHack;


/* 
 * window related instance variables.
 */

    Widget          _baseWidget,glDraw,shell;
    Widget          popup,curVolLbl,rewindW,stopW,playW;
    Widget          volShell,volSB;
    int             inputId;
    Display         *dpy;
#ifdef MOVIECONTROLLER_OPENGL
    GLXContext	    glContext;
#else
    GLXconfig*      retconfig;
#endif
    int             maxScrollWidth;
    int curVolume;

/*
 * movie related instance variables
 */
    char         *movieFileName;
    MVid         mvid;
    int          mvWidth,mvHeight;
    int          moviefd;
    DMboolean	 audioPresent;
    long         audioRate;
    MVid	 imageTrack;
    MVid	 audioTrack;
    static DMboolean playingEveryFrame;

/*
 * audio related instance variables
 */
    
    static char  curVol[10];
    static long  saveVolLeft,saveVolRight;
    static short muted;

/*
 * object reference counting for handling
 * movie events.
 */

    static int   curMaxObjOffset;
    int          objOffset;

/*
 *event handlers
 */
    static void  handleMovieEvents(XtPointer, int*, XtInputId* );
    static void  postIt           (Widget w,Widget popup,XButtonEvent *event);
    static void  makeVolume       (Widget w,XtPointer, XEvent *);
    static void  focusLeftWindow  ( Widget w, XtPointer, XEvent *, Boolean* );

/*
 *callbacks
 */

    static void gInitCB   (Widget, XtPointer, XtPointer);
    static void exposed   (Widget, XtPointer, XtPointer);
    static void resizedCB (Widget, XtPointer, XtPointer);
    static void playCB    (Widget, XtPointer, XtPointer);
    static void stopCB    (Widget, XtPointer, XtPointer);
    static void resetCB   (Widget, XtPointer, XtPointer);
    static void volUpCB   (Widget, XtPointer, XtPointer); 
    static void volDownCB (Widget, XtPointer, XtPointer);
#if DEBUG
    // stub functions for the moment - keep them out of shipping code
    static void playEveryFrameCB    
			  (Widget, XtPointer, XtPointer); 
    static void muteCB    (Widget, XtPointer, XtPointer);
#endif


/*
 *translations
 */
    static void ActivateButton1Down(Widget,XButtonPressedEvent*,
				   String*,Cardinal*);
    static void ActivateMouseMoved(Widget,XPointerMovedEvent*,
				   String*,Cardinal*);
    static void ActivateButton1Up  (Widget,XButtonReleasedEvent*,
				   String*,Cardinal*);
    static void ActivateButton2Down(Widget,XButtonPressedEvent*,
				   String*,Cardinal*);
    static void ActivateButton2Up  (Widget,XButtonPressedEvent*,
				   String*,Cardinal*);
    static void ActivateLeft    (Widget,XEvent*,String*,Cardinal*);
    static void ActivateRight   (Widget,XEvent*,String*,Cardinal*);
    static void ActivateM       (Widget,XEvent*,String*,Cardinal*);
    static void ActivateP       (Widget,XEvent*,String*,Cardinal*);
    static void ActivateS       (Widget,XEvent*,String*,Cardinal*);
    static void ActivateR       (Widget,XEvent*,String*,Cardinal*);
    static void ActivateZoomUp  (Widget,XEvent*,String*,Cardinal*);
    static void ActivateZoomDown(Widget,XEvent*,String*,Cardinal*);
    static void ActivateCopy	(Widget,XEvent*,String*,Cardinal*);

/*
 * internal utility functions
 */
    MVframe  pixelToFrame( int xPos );
    int  frameToPixel( MVframe frameNum );
    void moveToMouse( int mouseX );
    int getTotalFrames();


    char *getCurVol();
    void setCurVolume(int);
    int  getCurVolume();
    
    //
    // Stuff for drawing in the display window.
    //

    void drawCurrentImage();
    void setTriangleActive( DMboolean triangleIsVisible );
    void setTrianglePos( int newPos );
    int  getTrianglePos();
    
    void putTriangleUp();
    void takeTriangleDown();
    unsigned long pixelsUnderTriangle[(TRIANGLE_SIZE+1) * (TRIANGLE_SIZE+1)];
    Boolean checkTriangleLocated(XPointerMovedEvent *event);
    void doLocateHighlight(XPointerMovedEvent *);

    int       _curTrianglePos;
    DMboolean _triangleVisible;
    
    
    void resetIfAtEnd();
    void wrapIfAtBeginning();
    
    
    //
    // X selection mechanism support
    //
    static MovieController*	primarySelectionOwner;
    static MovieController*	clipboardSelectionOwner;
    static Atom			xa_SGI_RGB_IMAGE_FILENAME;
    static Atom			xa_SGI_AUDIO_FILENAME;
    static Atom			xa_SGI_MOVIE_FILENAME;
    static Atom			xa_PRIMARY;
    static Atom			xa_CLIPBOARD;
    static Atom			xa_TARGETS;
    static Atom			xa_ATOM;
    static Atom			xa_INTEGER;

    //
    // used to save what frame was showing at the time Copy
    // called or PRIMARY selection marked.
    //
    MVframe			primarySelectionFrame;
    MVframe			clipboardSelectionFrame;
    
    //
    // used to save start and duration of selection region on a
    // per-controller basis.   also whether a particular controller
    // should be showing the selected region.
    //
    // Both the primary and the clipboard selections refer to the
    // same selected region.
    //
    MVframe			regionStart;
    MVframe			regionLength;
    Boolean			showSelection;
    
    //
    // callback functions for when the PRIMARY selection is
    // gained and lost.
    //
    void (*primaryGainedCBFunc)   (void);
    void (*primaryLostCBFunc)	  (void);

    //
    // helper functions for shift-selecting a region.
    //
    void handleSelectionDown( XButtonPressedEvent* ev );
    void handleSelectionDrag( int dragX, int startX );
    void handleSelectionUp( XButtonReleasedEvent* ev);
    void drawSelectedRegion();
    
    void initSelections();
    static Boolean  SelectionRequestCB ( Widget w,
		Atom* selection, Atom* target, Atom* type, XtPointer* value,
		unsigned long* length, int* format );
    static void	    LostOwnershipCB( Widget w, Atom *selection );
    char *	    extractImageFile( Atom selection );
    char *	    extractAudioFile();
    char *	    extractMovieFile();
};

#endif /*MOVIECONTROLLER_H_INCLUDED*/
