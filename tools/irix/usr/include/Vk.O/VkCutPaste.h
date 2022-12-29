////////////////////////////////////////////////////////////////////////
//
// VkCutPaste.h
//
// This is the API for the Young/Wilson CutPasteDragDrop class to solve all
// your Cut & Paste needs.
//
// ---------------------------------------------------------------------
//
// Copyright 1995, Silicon Graphics, Inc.
// ALL RIGHTS RESERVED
//
// UNPUBLISHED -- Rights reserved under the copyright laws of the United
// States.   Use of a copyright notice is precautionary only and does not
// imply publication or disclosure.
//
// U.S. GOVERNMENT RESTRICTED RIGHTS LEGEND:
// Use, duplication or disclosure by the Government is subject to restrictions
// as set forth in FAR 52.227.19(c)(2) or subparagraph (c)(1)(ii) of the Rights
// in Technical Data and Computer Software clause at DFARS 252.227-7013 and/or
// in similar or successor clauses in the FAR, or the DOD or NASA FAR
// Supplement.  Contractor/manufacturer is Silicon Graphics, Inc.,
// 2011 N. Shoreline Blvd. Mountain View, CA 94039-7311.
//
// THE CONTENT OF THIS WORK CONTAINS CONFIDENTIAL AND PROPRIETARY
// INFORMATION OF SILICON GRAPHICS, INC. ANY DUPLICATION, MODIFICATION,
// DISTRIBUTION, OR DISCLOSURE IN ANY FORM, IN WHOLE, OR IN PART, IS STRICTLY
// PROHIBITED WITHOUT THE PRIOR EXPRESS WRITTEN PERMISSION OF SILICON
// GRAPHICS, INC.
//
////////////////////////////////////////////////////////////////////////

/* $Id: VkCutPaste.h,v 1.11 1996/09/10 18:27:42 blean Exp $ */

#ifndef VK_CUT_PASTE_H
#define VK_CUT_PASTE_H

#include <X11/X.h>
#include <X11/Intrinsic.h>
#include <Vk/VkCallbackObject.h>
#include <Vk/VkBase.h>


//////////////////////////////////////////////////////////////////////////
//                       Constants
//////////////////////////////////////////////////////////////////////////

#define CUTPASTE_NORMAL_TYPE   0
#define CUTPASTE_FILENAME_TYPE (1<<0)
#define CUTPASTE_HIDDEN_TYPE  (1<<1)


//////////////////////////////////////////////////////////////////////////
//                       Prototype Definitions 
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// ConvertProc:
//
// Prototype definition for conversion routines registered with
// registerConverter().
//
// These routines are called when a conversion to go from 'srcTarget' to
// 'dstTarget' is required.  Note that numSrcBytes and numDstBytes are
// in bytes, not 'format based units' (as in XtSelectionCallbackProc).
//
// The ConvertProc must set the dst and numDstBytes parameters if the
// conversion was successful.
//
// The ConvertProc must return True if the conversion was successful,
// and False otherwise.
//
//////////////////////////////////////////////////////////////////////////

typedef Boolean (*ConvertProc)(Widget w, Atom selection, void *clientData,
  Atom srcTarget, XtPointer src, unsigned long numSrcBytes, 
  Atom dstTarget, XtPointer *dst, unsigned long *numDstBytes);

////////
//
// CanConvertProc
//
////////

typedef Boolean (*CanConvertProc)(Widget w, Atom selection, void *clientData,
  Atom srcTarget, XtPointer src, unsigned long numSrcBytes, Atom dstTarget);


//////////////////////////////////////////////////////////////////////////
//
// DestroyProc:
//
// Prototype definition for providing a client side hook to cleanup
// "related data".  For example, if you make an SGI_RGBIMAGE_FILE available
// to other clients then you have created a file (let's say "/usr/tmp/foo.rgb").
// When the data is no longer needed, the destroy proc is called with the 
// filename, and you need to delete the file.  (You DO NOT free the filename in
// this DestroyProc, since that is free'ed automatically by the VkCutPaste 
// library.)
//
//////////////////////////////////////////////////////////////////////////

typedef void (*DestroyProc)(Widget w, Atom selection, Atom target, 
    XtPointer data, unsigned long numBytes, void *clientData);


//////////////////////////////////////////////////////////////////////////
//
// LoseSelectionProc
//
// Client side callback which is called when the X Windows selection
// ownership is "lost".  This means some either this client has "disowned"
// the selection (by calling clear()), or another client has obtained
// selection ownership.
//
//////////////////////////////////////////////////////////////////////////

typedef void (*LoseSelectionProc)(Widget w, Atom selection, void *clientData);


//////////////////////////////////////////////////////////////////////////
//
// DropSiteCallbackProc:
//
// Client side callback which is called when a drop operation has been
// successfully completed.
//
// target will be the first target in the list of targets (passed to
// the registerDropSite() call) which was available during the drop.
//
//////////////////////////////////////////////////////////////////////////

typedef void (*DropSiteCallbackProc)(Widget w, Atom target,
  XtPointer data, unsigned long numBytes, int x, int y, void *clientData);


//////////////////////////////////////////////////////////////////////////
//
// DragCallbackProc:
//
// Client side callback which is called when a drag occurs over the drop site
//
// target will be the target which will eventually be dropped if and when the
// user let's go of the mouse button
//
//////////////////////////////////////////////////////////////////////////

typedef void (*DragCallbackProc)(Widget w, Atom target, int reason, 
  int x, int y, void *clientData);


//////////////////////////////////////////////////////////////////////////
//
// DragAwayCallbackProc:
//
// Client side callback which is called when the drag away has been completed.
//
// The result is whether the drag was successful or not.
//
//////////////////////////////////////////////////////////////////////////

typedef void (*DragAwayCallbackProc)(Widget w, Boolean result,void *clientData);


//////////////////////////////////////////////////////////////////////////
//
// ImportCallbackProc:
//
// Client side callback which is called when a import() call has data
// to return.
//
// type will be the first target in the list of targets (passed in
// the import() call) which was available from the source client.
//
//////////////////////////////////////////////////////////////////////////

typedef void (*ImportCallbackProc)(Widget w, Atom target, XtPointer data, 
  unsigned long numBytes, void *clientData);


// extern declaration so we don't have to include _VkCutPasteMgr.h
class _VkCutPasteMgr;

class VkCutPaste : public VkCallbackObject, public VkBase
{
  public:
    VkCutPaste(Widget w);
    ~VkCutPaste();

    //////////////////////////////////////////////////////////////////////
    //////////////// Simple Cut/Paste Export API /////////////////////////
    //////////////////////////////////////////////////////////////////////

    ////////
    //
    // putReference():
    //
    //   Places a reference to the data onto the private clipboard specified
    //   by 'selection'.
    //
    //   The pointer MUST remain valid until the next 'clear()' call,
    //   or until the data is explicitly removed via 'remove()'.
    //
    ////////

    virtual Boolean putReference(Atom selection, Atom target,
				 XtPointer data, unsigned long numBytes);

    virtual Boolean putReference(Atom selection, const char *targetName,
				 XtPointer data, unsigned long numBytes);
    
    ////////
    //
    // putCopy():
    //
    //   Copies the data onto the private clipboard specified by 'selection'.
    //   The data is managed by the VkCutPaste class, and does NOT need to be
    //   explicitly removed via 'remove()'.
    //
    ////////

    virtual Boolean putCopy(Atom selection, Atom target, 
			    XtPointer data, unsigned long numBytes);
    
    virtual Boolean putCopy(Atom selection, const char *targetName, 
			    XtPointer data, unsigned long numBytes);
    
    ////////
    //
    // export():
    //
    // Exports the current contents of the private clipboard.  This
    // routine will call XtOwnSelection().
    //
    // If you pass a 'time' of 'CurrentTime', the timestamp from the last
    // X Event processed will be used.
    //
    ////////

    virtual Boolean export(Atom selection, Time time = CurrentTime);


    ////////
    //
    // clear():
    //
    // Clears the private clipboard, and the export target list.
    // Calls XtDisownSelection.
    //
    // If you pass a 'time' of 'CurrentTime', the timestamp from the last
    // X Event processed will be used.
    //
    ////////

    virtual void clear(Atom selection, Time time = CurrentTime);


    ////////
    //
    // remove():
    //
    // Removes the data specified by 'target' from the private clipboard
    // specified by 'selection', and from the export list if 'export()'
    // has been called.
    //
    // Clients must call 'remove()' on data that was placed on the
    // private clipboard when using the 'putReference()' call if the
    // data pointer becomes invalid.
    //
    ////////

    virtual Boolean remove(Atom selection, Atom target);


    //////////////////////////////////////////////////////////////////////
    //////////////// Simple Cut/Paste Import API /////////////////////////
    //////////////////////////////////////////////////////////////////////

    ////////
    //
    // importImmediate():
    //
    //   Immediately returns the first item it can successfully import from the
    //   prioritized "interestList".  It returns NULL if no valid data 
    //   is available that fits the interestList description.  Clients must
    //   free returned data with XtFree(). 
    //
    ////////

    virtual XtPointer importImmediate(Atom selection, Atom *interestList, 
				      int interestListLen, Atom *targetRet,
				      unsigned long *numBytesRet, 
				      Time theTime = CurrentTime);
    

    ////////
    //
    // import():
    //
    //   This call is exactly like "importImmediate()" above, but it uses a
    //   callback to alert the program when the data has arrived.  This is 
    //   useful if the client has a custom event loop and needs to do other 
    //   tasks while waiting for the data to arrive.
    //
    ////////

    virtual void import(Atom selection, Atom *interestList, int interestListLen,
			ImportCallbackProc proc, void *clientData = NULL, 
			Time theTime = CurrentTime);
    

    //////////////////////////////////////////////////////////////////////
    //////////////// Simple Drag/Drop API ////////////////////////////////
    //////////////////////////////////////////////////////////////////////

    ////////
    //
    // registerDropSite():
    //
    //   Registers a widget, so that if anyone drops something on this widget
    //   that is found in the prioritized "interestList", the callback is
    //   invoked.
    //
    ////////

    virtual Boolean registerDropSite(Widget w, Atom *interestList, 
				     int interestListLen,
				     DropSiteCallbackProc proc,
				     void *clientData = NULL);


    ////////
    //
    // dragAwayCopy():
    //   
    //   Call this, and a copy of the data immediately begins being "dragged".
    //   The program can free the data after this call, and this one call is 
    //   all that needs to be done for a successful drag and drop operation.
    //
    ////////

    virtual Widget dragAwayCopy(Widget w, XEvent *xev,
				Atom target, XtPointer data,
				unsigned long numBytes,
				DragAwayCallbackProc dragAwayProc = NULL,
				void *clientData = NULL);
    
    virtual Widget dragAwayCopy(Widget w, XEvent *xev,
				const char *targetName, XtPointer data,
				unsigned long numBytes,
				DragAwayCallbackProc dragAwayProc = NULL,
				void *clientData = NULL);
    

    //////////////////////////////////////////////////////////////////////
    /////////////// More advanced utility functions //////////////////////
    //////////////////////////////////////////////////////////////////////
    virtual unsigned long getVersion();
    virtual Widget getWidget();
    Atom   clipboardAtom();
    Atom   primaryAtom();

    virtual void registerDataType(Atom target, Atom type, int format, 
				  unsigned long flags = CUTPASTE_NORMAL_TYPE,
				  DestroyProc = NULL, 
				  void *clientData = NULL);
    virtual void registerDataType(const char *targetName, const char *typeName, 
				  int format,
				  unsigned long flags = CUTPASTE_NORMAL_TYPE, 
				  DestroyProc = NULL, void *clientData = NULL);
    virtual Boolean getDataTypeInfo(Atom target, Atom *type, int *format, 
				    unsigned long *flags);
    virtual void registerConverter(Atom from, Atom to, ConvertProc, 
				   CanConvertProc = NULL,
				   void *clientData = NULL);
    virtual void registerConverter(const char *fromName, const char *toName, 
				   ConvertProc, CanConvertProc = NULL,
				   void *clientData = NULL);
    virtual Boolean unregisterDropSite(Widget);
    virtual Boolean registerLoseSelection(Atom selection,
					  LoseSelectionProc loseSelProc,
					  void *clientData);
    virtual void setTransactionsTimeout(unsigned long numSeconds);
    virtual void activateHelpfulConverters();
    virtual Boolean isOwnedByMe(Atom selection);
    virtual Boolean isOwnedByLocalHost(Atom selection);
    virtual Time getXServerTime();  // invokes a round trip to X-Server
    virtual Boolean getFilenamesFromSGI_ICON(char *sgiIconData, 
					     unsigned long numBytes,
					     char ***fileNameArrayRet,
					     int *numFilesRet);
    virtual void freeFilenamesFromSGI_ICON(char **fileNameArray, int numFiles);
    
    virtual Widget dragAwayCopyExtended(Widget w, XEvent *xev,
					Atom *targetList, XtPointer *dataList,
					unsigned long *lenList,
					int numDragItems,
					DragAwayCallbackProc dragAwayProc = NULL, 
					void *clientData = NULL,
					ArgList args = NULL, int numArgs = 0);
    
    virtual Boolean registerDropSiteExtended(Widget w,
					     Atom *interestList, int interestListLen,
					     DropSiteCallbackProc proc,
					     DragCallbackProc dragProc = NULL, 
					     void *clientData = NULL,
					     Arg *args = NULL, int n = 0);


    //////////////////////////////////////////////////////////////////////
    /////////////// Local retrieval of the "clipboard contents" //////////
    /////////////// NOT X Selections based!!!                   //////////
    //////////////////////////////////////////////////////////////////////
    virtual Boolean getLocalReference(Atom, int,  Atom *, XtPointer *, 
      unsigned long *);
    virtual Boolean getLocalTypeReference(Atom, Atom, XtPointer *, 
      unsigned long *);

    //////////////////////////////////////////////////////////////////////
    //////// Advanced routines probably (?) not needed by anyone /////////
    //////////////////////////////////////////////////////////////////////
    virtual Boolean registerSite(Atom selection);
    virtual Boolean unregisterSite(Atom selection);
  
   protected:

    VkCutPaste();

    _VkCutPasteMgr *cutPasteMgr;

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkCutPaste(const VkCutPaste&);
    VkCutPaste &operator =(const VkCutPaste&);
};

#endif // VK_CUT_PASTE_H
