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
#ifndef VKMETER_H
#define VKMETER_H

#include <Vk/VkDoubleBuffer.h>

#define DONT_EDGE_START		(1 << 0)
#define DONT_EDGE_FINISH	(1 << 1)
#define DONT_EDGE_TOP		(1 << 2)
#define DONT_EDGE_BOTTOM	(1 << 3)
#define DONT_EDGE_SIDE		(1 << 4)


struct MeterInfo {
    int start;
    int end;
    int top, bottom;
    char *label;
    Pixel color;
    int flags;			/* DONT_EDGE_START, DONT_EDGE_FINISH,
				   DONT_EDGE_TOP, DONT_EDGE_BOTTOM,
				   DONT_EDGE_SIDE */
};


class VkMeter : public VkDoubleBuffer {


  public:

    VkMeter(const char *name, Widget parent);
    ~VkMeter();

    void reset(int range = -1, int units = -1);
    void update();

    void add(int value, char *color, char *label = NULL);
    void add(int value, Pixel pixel, char *label = NULL);
    void add(int value, int thickness, char *color, char *label = NULL);
    void add(int value, int thickness, Pixel pixel, char *label = NULL);

    void add(int start, int size, int sideValue, int thickness, char *color, char *label = NULL);
    void add(int start, int size, int sideValue, int thickness, Pixel color, char *label = NULL);

    void setResizePolicy( unsigned char policy ) { _resizePolicy = policy; }
    void setOrientation (unsigned char value) { _orientation = value;}
    
    void setTitle(const char *);  // Not implemented yet
    virtual const char* className();

  protected:

    virtual void afterRealizeHook();
    unsigned char _resizePolicy;

    MeterInfo *_info;
    char      *_title;
    int        _peak;
    int        _unitHeight;
    GC         _gc;
    GC         _borderGC;
    XmFontList _fontList;
    int        _numItems;
    Boolean    _drawBorder;
    Pixel      _borderColor;
    int        _factor;
    int        _lastValue;
    unsigned char _orientation;

    virtual void resize();
    void draw();
    virtual Dimension neededWidth() { return (_width); }    
    virtual Dimension neededHeight(){ return (_height); }    

  private:

    static String     _resources[];
    static XtResource _resSpec [];

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkMeter(const VkMeter&);
    VkMeter &operator= (const VkMeter&);
}; 

#endif
