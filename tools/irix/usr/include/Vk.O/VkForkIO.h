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
#ifndef _VK_FORK_IO_
#define _VK_FORK_IO_

#include <Vk/VkTextIO.h>
#include <Vk/VkProgram.h>
#include <Vk/VkSubProcess.h>
#include <Vk/VkInput.h>


enum VkForkIOReason { FIO_exited, FIO_destroyed, FIO_ctrlc, FIO_ctrld };

class VkForkIO : public VkTextIO {

public:

  VkForkIO(const char *name, Widget parent, const char *prompt = NULL);
  ~VkForkIO();

  void execCommand(char *cmd);

  Boolean running() { return _running; }

  void inputString(char *str);

  static const char *const exitCallback;
  static const char *const inputCallback;

protected:

  void cmdOutput(VkCallbackObject*, void *, void *);

  void cmdExit(VkCallbackObject*, void *, void *);

  void killProcess();

  int readAndOutput(VkInput *input);

  virtual void doCtrlC();
  virtual void doCtrlD();
  virtual void doNewLine();

  Boolean _running;

  VkInput stdoutCB;
  VkInput stderrCB;

  VkSubProcess process;

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkForkIO(const VkForkIO&);
    VkForkIO &operator= (const VkForkIO&);
};

#endif
