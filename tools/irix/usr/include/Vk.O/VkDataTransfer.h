////////////////////////////////////////////////////////////////////////
//
// VkDataTransfer.h
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

#ifndef VK_DATA_TRANSFER_H
#define VK_DATA_TRANSFER_H

#include <Vk/VkCutPaste.h>

class VkNameList;


class VkDataTransfer : public VkCutPaste
{
  public:
    
    VkDataTransfer();
    ~VkDataTransfer();
    
    static const char* const dropCallback;
    static const char* const dragCallback;
    static const char* const loseSelectionCallback;
    static const char* const importCallback;
    
    Boolean exportClipboard(Time time = CurrentTime) {return export(clipboardAtom(), time); }
    Boolean exportPrimary(Time time = CurrentTime) {return export(primaryAtom(), time); }

    void clearClipboard(Time time = CurrentTime) {clear(clipboardAtom(), time); }
    void clearPrimary(Time time = CurrentTime) {clear(primaryAtom(), time); }

    Boolean remove(Atom selection, Atom target);
    Boolean remove(Atom selection, const char *target);
    
    Boolean removeClipboard(const char *target) { return remove(clipboardAtom(), target); }
    Boolean removePrimary(const char *target) { return remove(primaryAtom(), target); }

    //////////////////////////////////////////////////////////////////////
    //////////////// Simple Cut/Paste Import API /////////////////////////
    //////////////////////////////////////////////////////////////////////

    virtual XtPointer importImmediate(Atom selection, Atom *interestList, 
				      int interestListLen, Atom *targetRet,
				      unsigned long *numBytesRet, 
				      Time theTime = CurrentTime);
    
    XtPointer importImmediate(Atom selection, 
			      Atom *interestList, 
			      int interestListLen,
			      Time theTime = CurrentTime);
    
    XtPointer importImmediate(Atom selection, 
			      const char *interestList, 
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
    
    void import(Atom selection, 
		Atom *interestList, 
		int interestListLen,
		Time theTime = CurrentTime);

    void import(Atom selection, const char *interestList,
		 Time theTime = CurrentTime);    
    
    
    // ////////////////////////////////////////////////////////////////////
    // ////////////// Simple Drag/Drop API ////////////////////////////////
    // ////////////////////////////////////////////////////////////////////

   virtual Boolean registerDropSite(Widget w, Atom *interestList, 
				     int interestListLen,
				     DropSiteCallbackProc proc,
				     void *clientData = NULL);

    Boolean registerDropSite(Widget w, const char * interestList);

    Boolean registerDropSite(Widget w, 
			     const char *targets,
			     VkCallbackObject *user, 
			     VkCallbackMethod callback, 
			     void *clientData);


    void registerDragSite(Widget w);
    void registerDragSite(Widget w, 
			  VkCallbackObject *user, 
			  VkCallbackMethod callback, 
			  void *clientData);
    
    Boolean unregisterDropSite(Widget);
    void unregisterDragSite(Widget);

    // Methods for accessing imported or dropped data

    Boolean isTargetType(const char*); // Type of available data 
    Atom  getTargetType();

    void *getData();                     // data dropped or pasted
    int   getSize();                     // size of data dropped or pasted

    const char *getFile(int index = 0);  // If data is a file
    int getNumFiles();                   // How many files

    void clearData();                 // clear dropped or pasted data

    Boolean getStatus();   // Whether import or drag succeeded

    void setData(const char *target, void *data, unsigned long numBytes);
    void setData(void *data);
    void setSize(unsigned long numBytes);
    void setTarget(const char *target);

  private:

    Atom *strToAtomList(const char *, int&);
    VkNameList    *_filelist;
    void          *_data;
    unsigned long  _size;
    Atom           _targetType;
    char *         _outgoingTarget;
    Boolean        _status;

    static _VkCutPasteMgr *_theCutPasteMgr;
    static int _refs;

    static void dropSiteCallback(Widget w, Atom target,
				 XtPointer data, 
				 unsigned long numBytes, 
				 int x, int y, void *clientData);

    static void importCB(Widget w, Atom target, 
			       XtPointer data, 
			       unsigned long numBytes, 
			       void *clientData);

    static void buttonPressCallback(Widget w, 
				    XtPointer clientData, 
				    XEvent *xev, 
				    Boolean *);

    static void dragFinishCallback(Widget w, 
				   Boolean result,
				   XtPointer clientData);

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkDataTransfer(const VkDataTransfer&);
    VkDataTransfer &operator =(const VkDataTransfer&);
    
};


#define VkRegisterDragSite(w, dt, user, callback, client) \
                            ((dt)->registerDragSite(w, user, (VkCallbackMethod) callback, client))

#define VkRegisterDropSite(w, targets, dt, user, callback, client)\
                            ((dt)->registerDropSite(w, targets, user, (VkCallbackMethod) callback, client))


extern VkDataTransfer *getTheDataTransferMgr();
#define theDataTransferMgr  getTheDataTransferMgr()

#endif // VK_DATA_TRANSFER_H
