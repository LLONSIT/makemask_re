/*
 * Copyright 1991-1996, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED
 *
 * UNPUBLISHED -- Rights reserved under the copyright laws of the United
 * States.   Use of a copyright notice is precautionary only and does not
 * imply publication or disclosure.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to restrictions
 * as set forth in FAR 52.227.19(c)(2) or subparagraph (c)(1)(ii) of the Rights
 * in Technical Data and Computer Software clause at DFARS 252.227-7013 and/or
 * in similar or successor clauses in the FAR, or the DOD or NASA FAR
 * Supplement.  Contractor/manufacturer is Silicon Graphics, Inc.,
 * 2011 N. Shoreline Blvd. Mountain View, CA 94039-7311.
 *
 * THE CONTENT OF THIS WORK CONTAINS CONFIDENTIAL AND PROPRIETARY
 * INFORMATION OF SILICON GRAPHICS, INC. ANY DUPLICATION, MODIFICATION,
 * DISTRIBUTION, OR DISCLOSURE IN ANY FORM, IN WHOLE, OR IN PART, IS STRICTLY
 * PROHIBITED WITHOUT THE PRIOR EXPRESS WRITTEN PERMISSION OF SILICON
 * GRAPHICS, INC.
 */
//  -*- C++ -*-

/*
 *
 _______________________________________________________________________
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 |
 |   $Revision: 2.0 $
 |
 |   Description:
 |	Callback list - a list of callback functions and associated data,
 |   with member functions to add, remove, and invoke callbacks.
 |	
 |   Classes:	SoCallbackList
 |
 |   Author(s):	David Mott
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_CALLBACK_LIST_
#define  _SO_CALLBACK_LIST_

#include <Inventor/SbPList.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoCallbackList
//
//////////////////////////////////////////////////////////////////////////////

// Callback functions that are registered with this class should
// be cast to this type.
typedef void SoCallbackListCB(void *userData, void *callbackData);

class SoCallbackList {
    
  public:

    SoCallbackList();
    ~SoCallbackList();
    
    //
    // Managing callback functions
    // At callback time, f will be called with userData as the first
    // parameter, and callback specific data as the second parameter.
    // e.g. (*f)(userData, callbackData);

    void    addCallback(SoCallbackListCB *f, void *userData = NULL);
    void    removeCallback(SoCallbackListCB *f, void *userData = NULL);
    
    void    clearCallbacks()			    { list.truncate(0); }
    int	    getNumCallbacks() const		    { return list.getLength(); }

    void    invokeCallbacks(void *callbackData);

  private:
  
    // callbackList holds a list of functions and user data
    SbPList 	list;
};

#endif  /* _SO_CALLBACK_LIST_ */
