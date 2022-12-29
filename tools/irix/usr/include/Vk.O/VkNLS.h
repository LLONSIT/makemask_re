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
#ifndef VKNLS_H
#define VKNLS_H
#include <Xm/Xm.h>


typedef void (*NLSCallback)( void *);

class VkNLS {

  private:

    static void checkNLSCallback ( XtPointer,   XtIntervalId* );
    long   _lic_type;
    int    _check_period;
    long   _vnd_ky;
    char  *_vnd_id;
    long   lic_type;
    long   _license_id;

    int getLicense( char *, long , char *,
		    int, long ,
		    long *);


    static void loseLicenseCallback(XtPointer, XtIntervalId * );

    NLSCallback _noLicenseCallback;
    void *_clientData;
	
  public:

    VkNLS ( char *, long , int , char *,
	    NLSCallback loseLicenseCallback = NULL,
	    void *clientData = NULL);

    ~VkNLS();

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkNLS(const VkNLS&);
    VkNLS &operator= (const VkNLS&);
};


#endif
