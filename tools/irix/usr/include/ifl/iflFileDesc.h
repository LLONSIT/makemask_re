#if 0
    Copyright 1995, Silicon Graphics, Inc.
    ALL RIGHTS RESERVED
 
    UNPUBLISHED -- Rights reserved under the copyright laws of the United
    States.   Use of a copyright notice is precautionary only and does not
    imply publication or disclosure.

    U.S. GOVERNMENT RESTRICTED RIGHTS LEGEND:
    Use, duplication or disclosure by the Government is subject to restrictions
    as set forth in FAR 52.227.19(c)(2) or subparagraph (c)(1)(ii) of the Rights
    in Technical Data and Computer Software clause at DFARS 252.227-7013 and/or
    in similar or successor clauses in the FAR, or the DOD or NASA FAR
    Supplement.  Contractor/manufacturer is Silicon Graphics, Inc.,
    2011 N. Shoreline Blvd. Mountain View, CA 94039-7311.
 
    THE CONTENT OF THIS WORK CONTAINS CONFIDENTIAL AND PROPRIETARY
    INFORMATION OF SILICON GRAPHICS, INC. ANY DUPLICATION, MODIFICATION,
    DISTRIBUTION, OR DISCLOSURE IN ANY FORM, IN WHOLE, OR IN PART, IS STRICTLY
    PROHIBITED WITHOUT THE PRIOR EXPRESS WRITTEN PERMISSION OF SILICON
    GRAPHICS, INC.
#endif
#ifndef _iflFileDesc_h_
#define _iflFileDesc_h_

#include <ifl/iflFormat.h>


class iflFileDesc {

public:
    // external api: begin

    // Constructing and destroying

    iflFileDesc(const char* name, iflFormat* format=NULL);
    
    // external api: name=iflFileDescPreParsed
    iflFileDesc(const char* fileName, int index, 
    	    	const char* formatName=NULL, const char* formatSpecific=NULL);
    // external api: name=iflFileDescFullyParsed
    iflFileDesc(const char* fileName, int index, 
    	    	iflFormat* format, const char* formatSpecific=NULL);

    ~iflFileDesc();

    // Attribute querying

    iflStatus getStatus() { return sts; }
    
    const char* getFileName() { return fileName; }
    
    int getFileDesc() { return fd; }
    
    int getIndex() { return index; }
    
    const char* getFormatName() { return format->getName(); }

    iflFormat* getFormat() { return format; }

    const char* getFormatSpecific() { return formatSpecific; }

    // Attribute setting

    void setFileDesc(int filedesc);
    
    // external api: end

private:
    void init(char* fileName, int index, iflFormat* format, 
    	      const char* formatSpecific);
    iflFormat* lookupFormat(const char* formatName);

    char* fileName;
    int index;
    const char* formatSpecific;
    iflFormat* format;
    int fd;
    iflStatus sts;
};

#endif
