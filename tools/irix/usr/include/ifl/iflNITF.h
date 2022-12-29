#if 0
    Copyright 1997, Silicon Graphics, Inc.
    ALL RIGHTS RESERVED
 
    UNPUBLISHED -- Rights reserved under the copyright laws of the United
    States.   Use of a copyright notice is precautionary only and does not
    imply publication or disclosure.

    U.S. GOVERNMENT RESTRICTED RIGHTS LEGEND:
    Use, duplication or disclosure by the Government is subject to restrictions
    as set forth in FAR 52.227.19(c)(2) or subparagraph (c)(1)(ii) of the Rights    in Technical Data and Computer Software clause at DFARS 252.227-7013 and/or
    in similar or successor clauses in the FAR, or the DOD or NASA FAR
    Supplement.  Contractor/manufacturer is Silicon Graphics, Inc.,
    2011 N. Shoreline Blvd. Mountain View, CA 94039-7311.
 
    THE CONTENT OF THIS WORK CONTAINS CONFIDENTIAL AND PROPRIETARY
    INFORMATION OF SILICON GRAPHICS, INC. ANY DUPLICATION, MODIFICATION,
    DISTRIBUTION, OR DISCLOSURE IN ANY FORM, IN WHOLE, OR IN PART, IS STRICTLY
    PROHIBITED WITHOUT THE PRIOR EXPRESS WRITTEN PERMISSION OF SILICON
    GRAPHICS, INC.
#endif
#ifndef _iflNITF_h_
#define _iflNITF_h_

#include <ifl/iflFile.h>
#include <ifl/iflFormat.h>

/*
 * iflStatus getTag(iflNITFTagSegment, iflNITFSegmentType segType,
 *		    int segNum, iflNITFSegment** seg);
 *
 * iflStatus getTag(iflNITFTagNewSegment, iflNITFSegmentType segType,
 *		    int segNum, iflNITFSegment** seg);
 */


enum iflNITFTagId {
    iflNITFTagSegment    = 0x4e490001,
    iflNITFTagNewSegment = 0x4e490002
};


enum iflNITFFieldType {
    iflNITFTypeInt32  = 1,
    iflNITFTypeInt64  = 2,
    iflNITFTypeFloat  = 3,
    iflNITFTypeByte   = 4,
    iflNITFTypeString = 5
};


enum iflNITFSegmentType {
    iflNITFSegHeader,
    iflNITFSegImage,
    iflNITFSegSymbol,
    iflNITFSegLabel,
    iflNITFSegText,
    iflNITFSegData,
    iflNITFSegReserv,
    iflNITFSegmentTypeCount
};


typedef class iflNITFField*  iflNITFFieldPtr;


class iflNITFSegment {
public:
    virtual iflNITFSegmentType getType() const=0;
    virtual int getNum() const=0;

    // Segment header accessors
    virtual iflNITFFieldPtr getField(const char* name)=0;
    virtual iflNITFFieldPtr getNextField(iflNITFFieldPtr f)=0;

    virtual iflNITFFieldType getFieldType(iflNITFFieldPtr f)=0;
    virtual size_t getFieldWidth(iflNITFFieldPtr f)=0;

    virtual iflStatus getFieldValue(iflNITFFieldPtr f, int32_t& value)=0;
    virtual iflStatus setFieldValue(iflNITFFieldPtr f, int32_t value)=0;

    virtual iflStatus getFieldValue(iflNITFFieldPtr f, int64_t& value)=0;
    virtual iflStatus setFieldValue(iflNITFFieldPtr f, int64_t value)=0;

    virtual iflStatus getFieldValue(iflNITFFieldPtr f, float& value)=0;
    virtual iflStatus setFieldValue(iflNITFFieldPtr f, float value)=0;

    virtual iflStatus getFieldValue(iflNITFFieldPtr f, const char*& value)=0;
    virtual iflStatus setFieldValue(iflNITFFieldPtr f, const char* value)=0;

    // Segment content accessors
    virtual int64_t getContentLength() const=0;
    virtual iflStatus readContent(void* buf, size_t bufLen, size_t& rdLen)=0;
    virtual iflStatus writeContent(const void* buf, size_t bufLen,
				   size_t& wrLen)=0;
    
protected:
    iflNITFSegment() { }
    virtual ~iflNITFSegment();

public:
    virtual const char* getFieldName(iflNITFFieldPtr f)=0;

    // variable length fields (currently only RESDATA and DESDATA)
    virtual iflStatus getFieldValue(iflNITFFieldPtr f, const char*& value,
				    size_t& width)=0;
    virtual iflStatus setFieldValue(iflNITFFieldPtr f, const char* value,
				    size_t width)=0;
};


#endif
