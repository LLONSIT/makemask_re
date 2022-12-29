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

#ifndef VKPIE_H
#define VKPIE_H

#include <Vk/VkMeter.h>

class VkPie : public VkMeter {

  public:
    
    VkPie(const char * name, Widget);
    virtual ~VkPie();
    void setRadius(int radius);
    void setLeftTextPosition(int percent) { _leftTextPosition = percent; }

    Dimension neededWidth() { computeBounds(); return _desiredWidth; }
    Dimension neededHeight(){ computeBounds(); return _desiredHeight; }
    
    virtual const char* className();

    static VkComponent *CreateVkPie(const char *name, Widget parent);
    
  protected:

    double degreesToRadians(int angle);

    void computePixelPosition(int x, int y, int width, int height, int angle,
			    int *x_return, int *y_return);

    void drawPieEdges(XPoint *points, GC gc, int flags);

    void drawPieCrust(int x, int y, int width, int height);

    void drawPieQuadrantSlice(int x, int y, int width, int height,
			      Pixel bg, int start, int end,
			      int bottom, int top, int flags);

    void drawPieSlices ( int x, int y, int width, int height,
			 MeterInfo *info, int num );
       
    void draw();
  
    int _radius;

    int _leftTextPosition;

    virtual void computeBounds();

    Dimension _desiredWidth;
    Dimension _desiredHeight;

private:

   static String _resources[];
   static XtResource _resSpec [];

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkPie(const VkPie&);
    VkPie &operator= (const VkPie&);
    
}; 

#endif
