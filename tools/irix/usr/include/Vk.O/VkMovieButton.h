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

#ifndef VKMOVIEBUTTON_H
#define VKMOVIEBUTTON_H

// VkMovieButton.h

#include <Vk/VkComponent.h>



class VkMovieButton : public VkComponent {

  public:

    static const char *const activateCallback;
    static const char *const movieFinishedCallback;    

    VkMovieButton(const char * name,
		  Widget parent,
                  char *movieFilename = NULL,
		  char *label=NULL);

    virtual ~VkMovieButton();
    virtual const char* className();

    void setLabel(char* label=NULL);
    void setAlignment(unsigned char);    
    void setMute (Boolean m=False);

    char*   getMovieFileName() const;
    void    setMovieFileName(const char *);

    static VkComponent *CreateVkMovieButton(const char *, Widget);

    void play();
    void stop();
    void rewind();    

  private:

    void *_screen;
    
    static XtTranslations _tt;
    static XtActionsRec   _actions[];
    static char           _ttDraw[];
    static String         _defaultResources[];

    Pixel     _locate;
    Pixel     _bg;    
    Widget    _form, _lbl;

    void lh(Boolean);    
    virtual void resize(Widget, XEvent*);        

    void finished(VkCallbackObject *, void *, void *);
    
    // callbacks
    
    static void resizeCB(Widget, XtPointer,  XEvent*, Boolean*);    
    static void ActivateSingleClick(Widget,XButtonPressedEvent*,
				    String*,Cardinal*);
    static void ActivateDblClick(Widget,XButtonPressedEvent*,
			         String*,Cardinal*);
    static void ButtonDown(Widget w, XButtonReleasedEvent*,
			   String*, Cardinal*);
    static void lhCB(Widget, XtPointer clientData, XEvent *event, Boolean*);
    static void *RegisterVkMovieButtonInterface();        
};

#endif
