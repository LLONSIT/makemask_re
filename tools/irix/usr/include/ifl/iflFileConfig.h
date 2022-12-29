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
#ifndef _iflFileConfig_h_
#define _iflFileConfig_h_
/*
    iflFileConfig describes the configuration of an iflFile;
    it is used with the iflFile::create() calls and to query file 
    configurations.
*/

#include <ifl/iflTypes.h>
#include <ifl/iflSize.h>
#include <ifl/iflOrientation.h>

class iflFile;

class iflFileConfig {

public:
    // external api: begin

    // Constructing and initializing

    iflFileConfig(const iflSize* imagedims=NULL, 
	          iflDataType datatype = iflDataType(0),
	          iflOrder dimensionorder = iflOrder(0), 
	          iflColorModel colormodel = iflColorModel(0),
	          iflOrientation orientation = iflOrientation(0),
	          iflCompression compression = iflCompression(0), 
	          const iflSize* pagedims = NULL);

    // external api: name=iflFileConfigFile
    iflFileConfig(iflFile* file); 

    void reset();

    // Setting attributes

    void setDimensions(const iflSize& imagedims) { imageDims = imagedims; }

    void setDataType(iflDataType datatype) { dtype = datatype; }

    void setOrder(iflOrder dimensionorder) { order = dimensionorder; }

    void setColorModel(iflColorModel colormodel) { cm = colormodel; }

    void setOrientation(iflOrientation orientation) { orient = orientation; }

    void setCompression(iflCompression compression) { compress = compression; }

    void setPageDimensions(const iflSize& pagedims) { pageDims = pagedims; }

    // Getting current attributes

    void getDimensions(iflSize& imagedims) { imagedims = imageDims; }

    // external api: name=getDimensionsPtr
    const iflSize& getDimensions() { return imageDims; }

    void getSize(iflSize& imagesize) 
    { 
	if (iflOrientationIsTrans[orient])
	    { imagesize.x = imageDims.y; imagesize.y = imageDims.x;}
	else
	    { imagesize.x = imageDims.x; imagesize.y = imageDims.y;}
	imagesize.z = imageDims.z;
	imagesize.c = imageDims.c;
    }

    iflDataType getDataType() { return dtype; }

    iflOrder getOrder() { return order; }

    iflColorModel getColorModel() { return cm; }

    iflOrientation getOrientation() { return orient; }

    iflCompression getCompression() { return compress; }

    void getPageDimensions(iflSize& pagedims) { pagedims = pageDims; }
    // external api: name=getPageDimensionsPtr
    const iflSize& getPageDimensions() { return pageDims; }

    void getPageSize(iflSize& pagesize) 
    { 
	if (iflOrientationIsTrans[orient])
	    { pagesize.x = pageDims.y; pagesize.y = pageDims.x;}
	else
	    { pagesize.x = pageDims.x; pagesize.y = pageDims.y;}
	pagesize.z = pageDims.z;
	pagesize.c = pageDims.c;
    }

    
    // Querying which attributes were defaulted
    int areDimensionsDefaulted() 
	{ return imageDims.x == 0 || imageDims.y == 0 ||
		 imageDims.z == 0 || imageDims.c == 0; }

    int isDataTypeDefaulted() { return dtype == iflDataType(0); }

    int isOrderDefaulted() { return order == iflOrder(0); }

    int isColorModelDefaulted() { return cm == iflColorModel(0); }

    int isOrientationDefaulted() { return orient == iflOrientation(0); }

    int isCompressionDefaulted() { return compress == iflCompression(0); }

    int arePageDimensionsDefaulted()
	{ return pageDims.x == 0 || pageDims.y == 0 ||
		 pageDims.z == 0 || pageDims.c == 0; }
    
    // external api: end

private:
    iflSize imageDims;
    iflDataType dtype;
    iflOrder order;
    iflColorModel cm;
    iflOrientation orient;
    iflCompression compress;
    iflSize pageDims;
    int specified;		// mask of specified attributes
};

#endif
