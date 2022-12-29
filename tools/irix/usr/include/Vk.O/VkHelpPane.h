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

#ifndef VKHELPPANE_H
#define VKHELPPANE_H

#include <Vk/VkSubMenu.h>

class VkSimpleWindow;
class VkHelpPane;
class VkMenu;

/*******************************************************
CLASS
    VkHelpPane

OVERVIEW





******************************************************/

typedef struct {
  VkHelpPane *obj;
  int index;
} VkHelpIndexCallback;

typedef struct {
  Boolean valid;
  char *book;
  char *label;
  int belongsTo;
  char *id;
  VkHelpIndexCallback *cb;
} VkHelpTaskInfo;

class VkHelpPane : public VkSubMenu {

  public:


    ////////////
    //
    //
    VkHelpPane(const char *name, 
	       VkMenuDesc *desc = NULL, 
	       XtPointer defaultClientData = NULL);

    ////////////
    //
    //
    VkHelpPane(Widget parent,
	       const char *name, 
	       VkMenuDesc *desc = NULL, 
	       XtPointer defaultClientData = NULL);


    ////////////
    //
    //
    virtual ~VkHelpPane();    


    ////////////
    //
    //
    virtual const char* className(); 


    ////////////
    //
    //
    void setItemSensitivities(Boolean context, Boolean overview, Boolean
			      index, Boolean keys, Boolean tutorial);


    ////////////
    //
    //
    Boolean useOldMenuArrangement() { return _useOldMenuArrangement; }


  protected:

    Boolean  _bContext, _bOverview, _bKeys, _bTutorial, _bIndex;
    VkHelpTaskInfo *_info;
    int _numInfo, _sizeInfo;
    Boolean _useOldMenuArrangement;
    Boolean _useWebMenuArrangement;
    char *_windowName;


    ////////////
    //
    //
    void create();

    ////////////
    //
    //
    void setSensitivities();

    ////////////
    //
    //
    void processWebHelpTopics(VkMenu *menu, const char *topicResName);


    ////////////
    //
    //
    void readTasks();

    ////////////
    //
    //
    void processOneLine(char *str);

    ////////////
    //
    //
    VkHelpTaskInfo *addTask(char *book, char *label, char *belongsTo,
			    char *id);

    ////////////
    //
    //
    void addTaskActions();

    ////////////
    //
    //
    int addTaskSubAction(VkMenu *parent, int index);


    ////////////
    //
    //
    virtual void build(Widget);
    

  private:
    static  void overviewCallback(Widget, XtPointer, XtPointer);
    static  void onItemCallback(Widget,   XtPointer, XtPointer);
    static  void indexCallback(Widget,    XtPointer, XtPointer);
    static  void versionCallback(Widget,    XtPointer, XtPointer);
    static  void keysCallback(Widget,     XtPointer, XtPointer);
    static  void tutorialCallback(Widget, XtPointer, XtPointer);
    static  void taskCallback(Widget, XtPointer, XtPointer);
    static  void webTaskCallback(Widget, XtPointer, XtPointer);

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkHelpPane(const VkHelpPane&);
    VkHelpPane &operator= (const VkHelpPane&);
    
};

#endif
