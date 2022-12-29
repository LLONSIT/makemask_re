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

#ifndef VKCOLORCHOOSERDIALOG_H
#define VKCOLORCHOOSERDIALOG_H

#include <Vk/VkDialogManager.h>
#include <Sgm/ColorC.h>

/*******************************************************
CLASS
    VkColorChooserDialog

OVERVIEW





AUTHOR
   Doug Young
******************************************************/


class VkColorChooserDialog : public VkDialogManager {

 public:


    ////////////
    //
    //
    VkColorChooserDialog( const char* name );

    ////////////
    //
    //
    virtual ~VkColorChooserDialog();


    ////////////
    //
    //
    const char* className();


    ////////////
    //
    //
    XColor *getColor();				// Returns a shifted XColor
    XColor *getXColor();			// Returns a normal XColor


    ////////////
    //
    //
    void setColor(short r, short g, short b);  // same as setCurrent + setStored
    void setXColor(unsigned short r, unsigned short g, unsigned short b);


    ////////////
    //
    //
    void setCurrentColor(short r, short g, short b);
    void setCurrentXColor(unsigned short r, unsigned short g, unsigned short b);


    ////////////
    //
    //
    void setStoredColor(short r, short g, short b);
    void setStoredXColor(unsigned short r, unsigned short g, unsigned short b);


    ////////////
    //
    //
    static const char *const valueChangedCallback;

  protected:


    ////////////
    //
    //
    virtual Widget createDialog( Widget dialogParent );

    ////////////
    //
    //
    virtual void ok(Widget, XtPointer);

    ////////////
    //
    //
    virtual void apply(Widget, XtPointer);

    ////////////
    //
    //
    virtual void cancel(Widget, XtPointer);

    ////////////
    //
    //
    virtual void drag(Widget, XtPointer);

    ////////////
    //
    //
    virtual void valueChanged(Widget, XtPointer);


    ////////////
    //
    //
    void clearValues(VkCallbackObject *, void *, void*);

  private:

    static void dragCB(Widget, XtPointer, XtPointer);
    static void valueChangedCB(Widget, XtPointer, XtPointer);
    SgColorChooserCallbackStruct *_callData;

    // _currentColor points to an XColor[2].
    //		_currentColor[0] is shifted, as expected by SgColorChooser
    //		_currentColor[1] is shifted back, and returned, when called for
    //    This means that _currentColor[1] is truly an XColor.
    XColor *_currentColor;
    XColor *_storedColor;        

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkColorChooserDialog(const VkColorChooserDialog&);
    VkColorChooserDialog &operator= (const VkColorChooserDialog&);
};

extern VkColorChooserDialog *getTheColorChooserDialog();
    
#define theColorChooserDialog getTheColorChooserDialog()


#endif // VKCOLORCHOOSERDIALOG_H
