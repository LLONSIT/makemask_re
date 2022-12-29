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
#ifndef _VK_TEXT_IO_
#define _VK_TEXT_IO_

#include <Vk/VkComponent.h>

#include <Xm/Xm.h>

enum VkTextIOReason { TIO_input, TIO_ctrlc };

typedef struct {
  VkTextIOReason reason;
  class VkTextIO *obj;
  char *value;
} VkTextIOCallback;

class VkTextIO : public VkComponent {
public:

  static const char *const textCallback;

  VkTextIO(const char *name, Widget parent, const char *prompt = NULL);
  ~VkTextIO();

  virtual void show();

  void clearHistory();
  virtual void outputString(char *str, Boolean skipInput = True);
  void outputChar(char ch, Boolean skipInput = True);
  void disableRedisplay();
  void enableRedisplay();

  Widget textWidget() { return text; }

  Boolean activated();
  void activate();
  void deactivate();

  void changePromptString (char*);

  int buffSize();

  Boolean cursorVisible();
  void setCursorVisible(Boolean value);

protected:
  void prepTextWidget();
  void processInput(XmTextVerifyCallbackStruct *cb);
  void inputChar(char ch);
  void addInput(char ch);
  void addInputN(char *str, int length);
  void doKillLine();
  void doKillWord();
  void doDelete(int num, int start = -1);
  void newInput();
  void scrollToBottom();
  void callCallback(VkTextIOReason reason, char *value);
  void flushInput();
  int translatePos(XmTextPosition pos);
  void inputError();
  void hidePrompt();
  void restorePrompt();
  void reallyRestorePrompt();

  virtual void doCtrlC();
  virtual void doNewLine();

  static void motion_verify(Widget w, XtPointer client_data,
			    XtPointer call_data);
  static void modify_verify(Widget w, XtPointer client_data,
			    XtPointer call_data);
  static void ctrl_u(Widget w, XEvent *event, String *params,
		     Cardinal *num_params);
  static void ctrl_c(Widget w, XEvent *event, String *params,
		     Cardinal *num_params);
  static void ctrl_w(Widget w, XEvent *event, String *params,
		     Cardinal *num_params);
  static Boolean prompt_stub(XtPointer clientData);

  Widget text;
  char *prompt, *promptBuf, *buffer;
  int bufferSize;
  Boolean ignoreVerify, displayUpdated;
  Pixel normalBg, readOnlyBg;
  Boolean displayEnabled;
  Time lastTime;
  Boolean _cursorVisible;
  XtWorkProcId promptID;
  Boolean promptHidden;

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkTextIO(const VkTextIO&);
    VkTextIO &operator= (const VkTextIO&);
};

#endif
