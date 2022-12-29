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
#ifndef _iflDatabase_h_
#define _iflDatabase_h_

#include <fcntl.h>
#include <ifl/iflTypes.h>
#include <ifl/iflList.h>

class iflFormat;

class iflSuffixItem : public iflListItem {
public:
    iflSuffixItem(char* suff) { suffix = suff; }
    
    char* suffix;
};


typedef iflList<iflSuffixItem> iflSuffixList;

class iflDatabase {

public:
    // external api: begin
    // Format Lookup
    static iflDatabase* findNext(int& index);

    static iflDatabase* findByMagic(int fd);

    static iflDatabase* findByFormatName(const char* formatName);

    static iflDatabase* findByFileName(const char* fileName, 
				       int noMatchRule=TRUE);

    // Attribute queries
    const char* getName() { return name; }

    const char* getDefaultSuffix();	    // format suffix

    const char* getDescription()	    // short description
	{ return description; }

    // Capabilities of the format
    int accessModeIsSupported(int mode)
	{ return access == mode || access == O_RDWR; }

    // DSO and inst related info
    const char* getDSOName() { return dsoname; }

    const char* getInstSubSystem() { return subsystem; }

    // Conversion to iflFormat
    iflFormat* getFormat(int openDSOifNecessary = TRUE);

    // external api: end
    
private:
    iflDatabase(const char* formatName);

    char* name;		       // name of this format
    char* description;	       // description of format
    char* dsoname;	       // name of DSO for this format;
    char* subsystem;	       // name of inst subsystem
    iflSuffixList* suffixes;   // list of file name suffixes
    int access;		       // supported access modes
 
    iflFormat* format;	       // iflFormat from DSO
    
    friend class iflFormatDB;
};

#endif
