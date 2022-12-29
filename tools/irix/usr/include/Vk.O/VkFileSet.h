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
#ifndef VKFILESET_H
#define VKFILESET_H

// WARNING: VkFileSet should not be used.  It is obsolete, core dumps, and
// WARNING: and has assorted other bugs.  It is not supported, and this
// WARNING: header file should probably be removed from the release.

#include <Vk/VkComponent.h>

class VkNameList;

class VkFileSet : public VkComponent
{

   public:

     VkFileSet(Widget, char *);
     ~VkFileSet();

     static const char* const dismissCallback;

     void setWorkingDirectory(char *);

    void add(char * file);
    void add(VkNameList * list);
    void clear();

     char * workingDirectory() { return _workingDirectory;}
     VkNameList *fileset();

     void setBrowsedDirectory(char * );

   protected:
  
     virtual void ok();
    
   private:

     static String _resources[];
 
     VkNameList *_fileset;

     char * _browsedDirectory;    // The directory displayed in the fileset editor's file browser 
     char * _workingDirectory;    // The current directory  of this program, which the fileset is realtive to
     
     Boolean  _literalInput;
     Boolean  _recursiveDirs;

     Widget	_helpButton;
     Widget	_cancelButton;
     Widget	_okButton;
     Widget	_separator;
     Widget	_scrolledWindow;
     Widget	_fileSetList;
     Widget	_scrolledWindow1;
     Widget	_directoryList;
     Widget	_filesList;
     Widget	_currentDirectoryWidget;
     Widget	_workingDirectoryWidget;
     Widget	_currentDirectoryLabel;
     Widget	_moveFilesButton;
     Widget	_moveDirsButton;
     Widget	_recursiveButton;
     Widget	_fileTextWidget;
     Widget	_dirCountLabel;
     Widget	_label1;
     Widget	_showButton;
     Widget	_literalButton;
     Widget	_fileSetLabel;
     Widget	_fileSetName;
     Widget	_removeButton;
     Widget	_includeCButton;
     Widget	_includeCPlusButton;
     Widget	_includeFortranButton;
     Widget	_includeAllButton;
     Widget	_fileRadioBox;
     Widget	_filesetFileBrowser;

     void addFileDirect();
     void addFiles();
     void addDirs();
     void removeFile(char *);

     static void setBrowsedDirectoryCallback(Widget, XtPointer, XtPointer);
     static void browseDirectoryCallback(Widget, XtPointer, XtPointer);
     static void addFileDirectCallback(Widget, XtPointer, XtPointer);
     static void addFilesCallback(Widget, XtPointer, XtPointer);
     static void addDirsCallback(Widget, XtPointer, XtPointer);
     static void removeFileCallback(Widget, XtPointer, XtPointer);
     static void okCallback(Widget, XtPointer, XtPointer);
     static void setRecursiveCallback(Widget, XtPointer, XtPointer);
     static void cancelCallback(Widget, XtPointer, XtPointer);
     static void setLiteralCallback(Widget, XtPointer, XtPointer);

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkFileSet(const VkFileSet&);
    VkFileSet &operator= (const VkFileSet&);
};


#endif 
