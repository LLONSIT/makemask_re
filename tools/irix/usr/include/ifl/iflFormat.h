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
#ifndef _iflFormat_h_
#define _iflFormat_h_

#include <fcntl.h>
#include <ifl/iflTypes.h>
#include <ifl/iflError.h>
#include <ifl/iflList.h>
#include <ifl/iflSize.h>
#include <ifl/iflDatabase.h>
#include <ifl/iflFileConfig.h>
#include <ifl/iflTag.h>

class iflFile;
struct iflTagDescription;


class iflFormat : private iflListItem {

public:
    // external api: begin

    // Format lookup

    static iflFormat* findNext(int& index, int openDSOifNecessary = TRUE);

    static iflFormat* findByMagic(int fd, int openDSOifNecessary = TRUE);

    static iflFormat* findByFormatName(const char* formatName, 
				       int openDSOifNecessary = TRUE);

    static iflFormat* findByFileName(const char* fileName,
				     int noMatchRule = FALSE, 
				     int openDSOifNecessary = TRUE);

    // Attribute queries

    const char* getName() { return name; }	    // format name

    const char* getDefaultSuffix()		    // format suffix
	{ return db? db->getDefaultSuffix() : NULL; }

    const char* getDescription()		    // short description
	{ return db? db->getDescription() : NULL; }

    // Attribute support queries

    int accessModeIsSupported(int mode)
	{ return db? db->accessModeIsSupported(mode) : FALSE; }

    virtual int typeIsSupported(iflDataType type) = 0;

    virtual int orderIsSupported(iflOrder order) = 0;

    virtual int orientationIsSupported(iflOrientation orientation) = 0;

    virtual int colorModelIsSupported(iflColorModel colormodel) = 0;

    virtual int compressionIsSupported(iflCompression compression) = 0;

    virtual int sizeIsSupported(int width, int height, int z, int c, 
				iflOrientation orientation) = 0;

    virtual int pagingIsSupported() = 0;

    virtual int pageSizeIsSupported(int iWidth, int iHeight, int iz, int ic,
				    int pWidth, int pHeight, int pz, int pc, 
				    iflOrientation orientation) = 0;

    virtual int randomAccessReadIsSupported() = 0;

    virtual int randomAccessWriteIsSupported() = 0;

    // Attribute preference queries

    virtual iflDataType getPreferredType() = 0;

    virtual iflOrder getPreferredOrder() = 0;

    virtual iflOrientation getPreferredOrientation() = 0;

    virtual iflColorModel getPreferredColorModel(int nc=0) = 0;

    virtual iflCompression getPreferredCompression() = 0;

    virtual void getPreferredPageSize(int iWidth, int iHeight, int iz, int ic,
				      int& pWidth, int& pHeight, int& pz, 
				      int& pc, iflOrientation orientation) = 0;

    // XXX We probably need a way to obtain a list of all
    // the compression types (and descriptions) that the format
    // supports, since there is no way IL can predict
    // the types and descriptions of format-specific compressions.

    // Inheriting attributes

    iflStatus applyDefaults(iflFile* source, iflFileConfig& config);
    // external api: name=applyDefaultsConfig
    iflStatus applyDefaults(iflFileConfig* source, iflFileConfig& config);

    // GUI support

    iflTagDescription* getTagDescriptions(int& count);

    // Version query

    int haveDSOVersion(int major, int minor);

    // external api: end

protected:
    // Constructing

    iflFormat(const char* formatName);

    virtual iflFile* newfileobj();

private:
    friend class iflFile;   // so iflFile::open() can access newfileobj()

    // So that iflFormat objects can put themselves in a list...
    friend class iflMultiList<iflFormat,iflListItem>;
    friend class iflMultiListIter<iflFormat,iflListItem>;
    
    char* name;
    iflDatabase* db;
    
// new virtual added here to maintain backward binary compatibility XXX

protected:
    // Implementing GUI support

    virtual iflTagDescription* _getTagDescriptions(int& count);
};


class iflReadOnlyFormat : public iflFormat {
public:
    iflReadOnlyFormat(const char* formatName) : iflFormat(formatName) {}
    
    // default implementations: nothing is supported/preferred
    virtual int typeIsSupported(iflDataType);
    virtual int orderIsSupported(iflOrder);
    virtual int orientationIsSupported(iflOrientation);
    virtual int colorModelIsSupported(iflColorModel);
    virtual int compressionIsSupported(iflCompression);
    virtual int sizeIsSupported(int,int,int,int, iflOrientation);
    virtual int pagingIsSupported();
    virtual int pageSizeIsSupported(int,int,int,int, int,int,int,int, 
				    iflOrientation);
    virtual int randomAccessReadIsSupported();
    virtual int randomAccessWriteIsSupported();
    virtual iflDataType getPreferredType();
    virtual iflOrder getPreferredOrder();
    virtual iflOrientation getPreferredOrientation();
    virtual iflColorModel getPreferredColorModel(int=0);
    virtual iflCompression getPreferredCompression();
    virtual void getPreferredPageSize(int,int,int,int, int&,int&,int&,int&, 
				      iflOrientation);
};

#endif
