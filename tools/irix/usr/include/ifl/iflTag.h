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
#ifndef _iflTag_h_
#define _iflTag_h_
/*
    Type defintitions used with iflFormat::getTagDescriptions()
*/

#include <ifl/iflTypes.h>
#include <ifl/iflError.h>


struct iflTagDescription {
    int tag;   	    	    /* tag value used with getTag/setTag */
    u_int flags;    	    /* flags encoding type, count... (iflTagFlags) */
    char* description;	    /* description of tag suitable for quick help */
    char* name;     	    /* name of tag suitable for GUI label */
    char* defaultValue;     /* default value (e.g. "1.4", "true", "enumval") */
    	    	    	    /*     may be NULL if no default */
    void* spec;     	    /* type specific: iflEnumSpec, iflIntRangeSpec, */
    	    	    	    /* iflFloatRangeSpec, iflDoubleRangeSpec, or NULL */
};
#ifndef __cplusplus
typedef struct iflTagDescription iflTagDescription;
#endif


#ifdef __cplusplus

enum iflTagFlags {
    /* number of paramters for this tag */
    iflTagParamCountMask = 0xf,
    iflTagNoParams = 0,    	/* zero paramter values with this tag */
    iflTagOneParam = 1,    	/* one parameter value... */
    iflTagTwoParams = 2,
    iflTagThreeParams = 3,
    iflTagFourParams = 4,
    iflTagFiveParams = 5,  	/* more than five paramters not allowed */
    
    /* type of parameters */
    iflTagTypeMask = 0xf0,
    iflTagShort = 0x00,	    	/* short */
    iflTagInt = 0x10,	    	/* integer */
    iflTagFloat = 0x20,    	/* float */
    iflTagString = 0x30,   	/* char*, null terminated */
    iflTagBoolean = 0x40,  	/* integer: 0 or 1 */
    iflTagShortEnum = 0x50, 	/* enums, uses iflEnumSpec* for 'spec' */
    iflTagEnum = 0x60,
    iflTagIntRange = 0x70, 	/* integer, uses iflIntRangeSpec* for 'spec' */
    iflTagFloatRange = 0x80,	/* float, uses iflFloatRangeSpec* for 'spec' */
    iflTagDouble = 0x90,	/* double */
    iflTagDoubleRange = 0xa0,	/* double, uses iflDoubleRangeSpec* for 'spec' */
    
    /* is tag supported for get/set */
    iflTagGet = 0x100,    	/* supported for getTag */
    iflTagSet = 0x200,  	/* supported for setTag  */
    
    /* is tag relevant to open and/or create */
    iflTagOpen = 0x1000,    	/* tag makes sense for open */
    iflTagCreate = 0x2000,  	/* tag makes sense for create */
    iflTagInfo = 0x4000,  	/* tag makes sense for info display */
    
    /* should tag be excluded from GUI presentations */
    iflTagHide = 0x10000    	/* don't present tag in a GUI */
};

#endif

struct iflEnumSpec {	    /* used for 'spec' with iflTagEnum */
    char* name;
    int value;
};
#ifndef __cplusplus
typedef struct iflEnumSpec iflEnumSpec;
#endif


struct iflIntRangeSpec {    /* used for 'spec' with iflTagIntRange */
    int min;
    int max;
};
#ifndef __cplusplus
typedef struct iflIntRangeSpec iflIntRangeSpec;
#endif


struct iflFloatRangeSpec {    /* used for 'spec' with iflTagFloatRange */
    float min;
    float max;
    float step;
};
#ifndef __cplusplus
typedef struct iflFloatRangeSpec iflFloatRangeSpec;
#endif

struct iflDoubleRangeSpec {    /* used for 'spec' with iflTagDoubleRange */
    double min;
    double max;
    double step;
};
#ifndef __cplusplus
typedef struct iflDoubleRangeSpec iflDoubleRangeSpec;
#endif

#ifdef __cplusplus

class iflFile;

class iflTag {
public:
    iflTag();	// use with init() for arrays
    // external api: begin
    // external api: name=iflTagFromDesc
    iflTag(iflTagDescription* desc);
    ~iflTag();
    
    void init(iflTagDescription* desc);

    void* getValue() { return value; }
    int getType() { return desc->flags&iflTagTypeMask; }
    int getCount() { return desc->flags&iflTagParamCountMask; }

    iflStatus read(iflFile* file);
    iflStatus write(iflFile* file);

    iflStatus encode(char* str);
    iflStatus decode(const char* str);
    // external api: end

protected:
    iflTagDescription* desc;
    void* value;

private:
    void freeStrings();
    int strAllocated;
};

#endif

#endif
