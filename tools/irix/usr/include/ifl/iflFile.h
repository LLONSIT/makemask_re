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
#ifndef _iflFile_h_
#define _iflFile_h_

#include <ifl/iflTypes.h>
#include <ifl/iflError.h>
#include <ifl/iflSize.h>
#include <ifl/iflConfig.h>
#include <ifl/iflColormap.h>
#include <ifl/iflOrientation.h>
#include <ifl/iflFileConfig.h>
#include <ifl/iflFileDesc.h>
#include <ifl/iflClassList.h>
#include <fcntl.h>
#include <stdarg.h>

class iflFormat;

// Flags to iflFile::close()

#define IFL_CLOSE_DISCARD (1<<0)

struct iflParameterDesc {   // used with parseArguments()
    char* name;	    // filled in with pointer to name of parameter
    char* value;    // filled in with value of paramter (or NULL if none)
};

struct iflNameDesc {   // used with lookupName()
    char* name;	    // parameter/value name 
    int id;	    // id associated with that name
};


class iflFile {

public:
    iflClassListDeclare

    // external api: begin
    
    // Open/create/close methods

    // external api: name=openPreParsed
    static iflFile* open(iflFileDesc& fileDesc, int mode = O_RDONLY,
			 iflStatus* status=NULL);
    // external api: name=openByDescriptor
    static iflFile* open(int fd, const char* filename, int mode=O_RDONLY, 
			 iflFormat* format=NULL, iflStatus* status=NULL); 
    static iflFile* open(const char* filename, int mode = O_RDONLY,
			 iflStatus* status=NULL)
	{ return iflFile::open(-1, filename, mode, NULL, status); }

    static iflFile* create(const char* filename,  
			   iflFile* source, const iflFileConfig* cfg=NULL, 
			   iflFormat* format=NULL, iflStatus* status=NULL)
	{ return iflFile::create(-1, filename, source, cfg, format, status); }
    // external api: name=createByDescriptor
    static iflFile* create(int fd, const char* filename,  
			   iflFile* source, const iflFileConfig* cfg=NULL, 
			   iflFormat* format=NULL, iflStatus* status=NULL);
    // external api: name=createPreParsed
    static iflFile* create(iflFileDesc& fileDesc, iflFile* source, 
			   const iflFileConfig* cfg=NULL, 
			   iflStatus* status=NULL);

    iflStatus close(int flags = 0);	// destructs the object

    virtual iflStatus flush();

    static char* parseFileName(const char* fullname, char** formatName=NULL, 
			       int* index=NULL, char** formatArgs=NULL);

    // Image data access

    iflStatus getTile(int x, int y, int z, int nx, int ny, int nz,
		      void* data, const iflConfig* config=NULL);

    iflStatus setTile(int x, int y, int z, int nx, int ny, int nz,
		      const void *data, const iflConfig* config=NULL);

    virtual iflStatus getPage(void* data, int x, int y, int z, int c,
			      int nx, int ny, int nz, int nc);

    virtual iflStatus setPage(const void* data, int x, int y, int z, int c, 
			      int nx, int ny, int nz, int nc);

    // external api: end
    virtual iflStatus getCompressedPage(...);
    virtual iflStatus decompressPage(...);
    virtual iflStatus compressPage(...);
    virtual iflStatus setCompressedPage(...);
    // external api: begin

    // Manipulating the current image index

    virtual int getNumImgs();

    virtual int getCurrentImg();

    virtual iflStatus setCurrentImg(int idx);

    // Adding images

    virtual iflStatus appendImg(iflFile* source, iflFileConfig* fc=NULL);

    // Attribute query and set

    const char* getFileName()		{ return filename; }

    int getFileDesc()			{ return fd; }

    int getFileMode()			{ return accessmode; }

    iflFormat* getFormat()		{ return format; }

    iflColorModel getColorModel()	{ return cm; }

    int* getChannelPermutation()    	{ return channelPermutation; }

    void getDimensions(iflSize& dimensions)
	{ getSize(dimensions, iflLowerLeftOrigin); }

    void getSize(iflSize& sz, iflOrientation toOrientation) // no default
	{ sz = size; iflMapSize(orientation, sz, toOrientation); }

    int getZsize() { return size.z; }

    int getCsize() { return size.c; }

    iflDataType getDataType()		{ return dtype; }

    iflOrder getOrder()			{ return order; }

    void getPageDimensions(iflSize& pageDims) 
	{ getPageSize(pageDims, iflLowerLeftOrigin); }

    void getPageSize(iflSize& sz, iflOrientation toOrientation) // no default
	{ sz = pageSize; iflMapSize(orientation, sz, toOrientation); }

    iflOrientation getOrientation()	{ return orientation; }

    iflCompression getCompression()	{ return compression; }

    virtual iflStatus getColormap(const iflColormap*& cmap);

    virtual iflStatus getStatMinMax(double& min, double& max);

    virtual iflStatus getScaleMinMax(double& min, double& max);

    virtual iflStatus setColormap(const iflColormap* cmap);

    virtual iflStatus setStatMinMax(double min, double max);

    virtual iflStatus setScaleMinMax(double min, double max);

    // Format specific attributes

    // external api: end
    iflStatus getTag(int tag, ...);

    // external api: begin
    iflStatus getTagV(int tag, va_list ap)
    	{ return getItem(tag, ap); }

    // external api: end
    iflStatus setTag(int tag, ...);

    // external api: begin
    iflStatus setTagV(int tag, va_list ap)
    	{ return setItem(tag, ap); }

    int haveAttributesChanged();

    // <subsubsection Deprecated versions>

    // external api: end
    iflStatus getItem(int tag, ...);	// deprecated

    // external api: begin
    // external api: name=getItemV
    virtual iflStatus getItem(int tag, va_list ap);

    // external api: end
    iflStatus setItem(int tag, ...);	// deprecated

    // external api: begin
    // external api: name=setItemV
    virtual iflStatus setItem(int tag, va_list ap);

    // ICC profile access

    iflStatus getICCProfile(int& size, void*& profile);

    iflStatus freeICCProfile(void* profile);

    iflStatus setICCProfile(int size, const void* profile);

    // Direct I/O support

    iflStatus enableDirectIO(int enable=TRUE);

    iflStatus getDirectIOMemAlignment(size_t& memAlign);

    // external api: end

    // Multiprocessing support

    void setBeginFileIO_CB(iflStatus (*cb)(void*), void* arg)
	{ beginFileIO_CB = cb; beginFileIO_arg = arg; }

    void setEndFileIO_CB(iflStatus (*cb)(void*), void* arg)
	{ endFileIO_CB = cb; endFileIO_arg = arg; }


protected:
    // Creating and destroying

    iflFile();

    virtual ~iflFile();	

    void markAttributesChanged()
	{ attrChanged = TRUE; }

    // File argument parsing

    int parseArguments(iflParameterDesc* params, int maxParams);

    static int lookupName(const char* name, const iflNameDesc* names);

    // Multiprocessing support

    iflStatus beginFileIO()
	{ return beginFileIO_CB != NULL ? beginFileIO_CB(beginFileIO_arg)
					: (iflStatus)iflOKAY; }

    iflStatus endFileIO()
	{ return endFileIO_CB != NULL ? endFileIO_CB(endFileIO_arg)
				      : (iflStatus)iflOKAY; }

    // Implementing opening, closing and creating
    
    virtual iflStatus openFile() = 0;

    virtual iflStatus createFile();

    virtual iflStatus closeFile() = 0;

    // ICC methods added here to maintain backward binary compatibility XXX

    // Implementing ICC public methods

    virtual iflStatus _getICCProfile(int& size, void*& profile);

    virtual iflStatus _freeICCProfile(void* profile);

    virtual iflStatus _setICCProfile(int size, const void* profile);

    // Direct I/O methods added here to maintain backward binary compat XXX

    // Implementing direct I/O public methods

    virtual iflStatus _enableDirectIO(int enable=TRUE);

    virtual iflStatus _getDirectIOMemAlignment(size_t& memAlign);

    // Attributes that never change after open or create

    char* filename;

    int fd;

    int accessmode;

    iflFormat* format;

    char* formatArgs;

    // Attributes that may change when sub-image changes
    // Attributes that should be considered read-only
    // to all methods except openFile(), setCurrentImg(), appendImg(),
    // and setTag() (and setTag() needs to report whether it changes them).
    // The remaining methods would be declared const, except that they must
    // be allowed to modify the subclass's members.
    iflSize size;

    iflDataType dtype;

    iflOrder order;

    iflSize pageSize;

    iflColorModel cm;

    iflOrientation orientation;

    iflCompression compression;

private:

    int* channelPermutation; // subclass need not worry about this
    
    int attrChanged;	// TRUE if attrs change since last call to
			// haveAttributesChanged()
    
    iflStatus (*beginFileIO_CB)(void*);
    void* beginFileIO_arg;
    iflStatus (*endFileIO_CB)(void*);
    void* endFileIO_arg;
};

#endif
