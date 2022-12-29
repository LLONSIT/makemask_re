////////////////////////////////////////////////////////////////////////////////
///////   Copyright 1992, Silicon Graphics, Inc.  All Rights Reserved.   ///////
//                                                                            //
// This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics, Inc.;     //
// the contents of this file may not be disclosed to third parties, copied    //
// or duplicated in any form, in whole or in part, without the prior written  //
// permission of Silicon Graphics, Inc.                                       //
//                                                                            //
// RESTRICTED RIGHTS LEGEND:                                                  //
// Use,duplication or disclosure by the Government is subject to restrictions //
// as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data     //
// and Computer Software clause at DFARS 252.227-7013, and/or in similar or   //
// successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -    //
// rights reserved under the Copyright Laws of the United States.             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
#ifndef _VK_RESIZER_
#define _VK_RESIZER_

#include <Vk/VkComponent.h>

enum VkResizerReason { VR_none, VR_resizing, VR_moving, VR_resized,
			       VR_moved };

class VkResizer : public VkComponent {

  public:

    VkResizer(Boolean autoAdjust = False, Boolean liveResize = False);
    virtual ~VkResizer();

    static const char *const stateChangedCallback;

    void setIncrements(int resizeWidth, int resizeHeight,
  		       int moveX, int moveY);

    Boolean shown() { return _shown; }

    void attach(Widget w);
    void detach();

    void show();
    void hide();

    void adjustGeometry();

    void lastLocation(Position *x_return, Position *y_return,
		      Dimension *width_return, Dimension *height_return);

  protected:

    void setupCallbacks(Widget w);
    void removeCallbacks(Widget w);
    void rebuild(Widget w);
    void defineCursors();
    void buttonPress(Widget grip, XEvent *event);
    void buttonRelease(Widget grip, XEvent *event);
    void pointerMotion(XEvent *event);
    void resizeFrame(int x, int y);
    void moveFrame(int x, int y);
    void matchFrame();
    Boolean allowResize() { return (_resizeWidth || _resizeHeight); }
    Boolean allowMove() { return (_moveX || _moveY); }

    Widget _parent, _adjuster;
    Widget _frame, _area, _llGrip, _urGrip, _grab, _grabGrip;
    Boolean _autoAdjust, _liveResize, _shown;
    Boolean _resizeWidth, _resizeHeight, _moveX, _moveY;
    int _gripSize, _gripThickness, _frameThickness, _frameSpacing;
    int _frameOverhead;
    Display *_dpy;
    Pixel _bg, _fg;
    Cursor _llCursor, _urCursor, _moveCursor;
    int _grabButton, _grabX, _grabY, _originX, _originY, _sizeX, _sizeY;
    Position _startX, _startY;
    Dimension _startWidth, _startHeight;
    Boolean _pendingRebuild;

  private:
    
    static void reconfig_stub(Widget w, XtPointer client_data, XEvent *event,
			    Boolean *dispatch);
    static void button_press(Widget w, XtPointer client_data, XEvent *ev,
			   Boolean *dispatch);
    static void button_release(Widget w, XtPointer client_data, XEvent *ev,
  			     Boolean *dispatch);
    static void pointer_motion(Widget w, XtPointer client_data, XEvent *ev,
			     Boolean *dispatch);

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkResizer(const VkResizer&);
    VkResizer &operator= (const VkResizer&);
};

#endif
