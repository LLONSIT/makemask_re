#if 0 

    Copyright (c) 1991 SGI   All Rights Reserved
    THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF SGI
    The copyright notice above does not evidence any
    actual or intended publication of such source code,
    and is an unpublished work by Silicon Graphics, Inc.
    This material contains CONFIDENTIAL INFORMATION that
    is the property of Silicon Graphics, Inc. Any use,
    duplication or disclosure not specifically authorized
    by Silicon Graphics is strictly prohibited.
    
    RESTRICTED RIGHTS LEGEND:
    
    Use, duplication or disclosure by the Government is
    subject to restrictions as set forth in subdivision
    (c)(1)(ii) of the Rights in Technical Data and Computer
    Software clause at DFARS 52.227-7013, and/or in similar
    or successor clauses in the FAR, DOD or NASA FAR
    Supplement.  Unpublished- rights reserved under the
    Copyright Laws of the United States.  Contractor is
    SILICON GRAPHICS, INC., 2011 N. Shoreline Blvd.,
    Mountain View, CA 94039-7311

#endif
/*
    This is the base class for lookup tables 
*/

#include <ifl/iflTypes.h>
#include <ifl/iflError.h>

#ifndef _iflLut_h_
#define _iflLut_h_

class iflLut {

public:
    // Creating and destroying

    iflLut()
	{ init(NULL, 0, iflDataType(0), 0, 0); }
    // external api: begin
    iflLut(int numChan, iflDataType dtype, double min, double max, int length=0)
	{ init(NULL, numChan, dtype, min, max, length); }
    // external api: name=iflLutNoAlloc
    iflLut(void* table, int numChan, iflDataType dtype, 
	   double min, double max, int length=0) 
	{ init(table, numChan, dtype, min, max, length); }
    // external api: name=iflLutCopy
    iflLut(const iflLut& other)
    	{ init(other.data, other.numChannels, other.type,
    	       other.domainMin, other.domainMax, other.tabLength); }

    virtual ~iflLut();
    
    // Basic attributes

    int getNumChans() const { return numChannels; }

    iflDataType getDataType() const { return type; }

    int getLength() const { return tabLength; }

    // Entry access

    double getVal(double domainIdx, int chan=0) const;

    iflStatus setVal(double val, double domainIdx, int chan=0);

    // Direct table access

    void* getOrigin(int chan) const;

    void* getChan(int chan) const;

    void* getData() const { return data; }

    void setData(void* data); 

    // Domain and range control

    void getDomain(double& min, double& max) const
	{ min = domainMin; max = domainMax; }

    double getDomainMin() const
	{ return domainMin; }

    double getDomainMax() const
	{ return domainMax; }

    double getDomainStep() const
	{ return 1/scale; }

    void getRange(double& min, double& max) const;

    iflStatus setDomain(double min, double max);

    // Comparison

    int isDiff(const iflLut& from) const;
    
    // external api: end

    // Copying

    void operator=(const iflLut& from);

protected:
    // Initialization

    void init(void* table, int tabChannels, iflDataType tabType, 
	      double min, double max, int length=0); 
	      
private:
    // set basic lut attributes
    void setType(iflDataType lutType);
    void setNumChans(int numChans) { numChannels = numChans; }
    
    // used to clamp a double value to int (to prevent overflow)
    double clampToInt(double val);

    void* data;		// actual data for lookup tables 	
    void* allocFlg;	// indicates who allocated the table	
    iflDataType type;	// data type of the lookup table        
    int	numChannels;	// number of channels in lookup table	
    size_t tabWidth;	// number of bytes in each table entry		
    int tabLength;	// Length of table
    double domainMin;	// lut domain lower bound
    double domainMax;	// lut domain upper bound
    double scale;	// scale and bias mapping domain to lut entries
    double bias;
};


#endif
