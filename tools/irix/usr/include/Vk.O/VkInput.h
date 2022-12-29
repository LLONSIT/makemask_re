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
#ifndef VKINPUT_H
#define VKINPUT_H

#include <X11/Intrinsic.h>
#include <Vk/VkCallbackObject.h>

/*
 * VkInput is a base class intended to encapsulate the
 * mechanism for setting up object-oriented callbacks on file descriptors.
 */


class VkInput : public VkCallbackObject {

    public:

	VkInput();
        virtual ~VkInput();

	void	attach(int fd, XtInputMask mask);
	void	remove();

	int	fd()		{ return _fd; }
	XtInputId id()		{ return _id; }

        static const char * const inputCallback;        

    protected:

	XtInputId  _id;
	int	   _fd;

    private:

       static void inputXtCallback(XtPointer   clientData, 
				   int        *source, 
				   XtInputId  *idptr);

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkInput(const VkInput&);
    VkInput &operator= (const VkInput&);
};

#endif
