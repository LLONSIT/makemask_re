/*
 * Copyright 1991-1996, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED
 *
 * UNPUBLISHED -- Rights reserved under the copyright laws of the United
 * States.   Use of a copyright notice is precautionary only and does not
 * imply publication or disclosure.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to restrictions
 * as set forth in FAR 52.227.19(c)(2) or subparagraph (c)(1)(ii) of the Rights
 * in Technical Data and Computer Software clause at DFARS 252.227-7013 and/or
 * in similar or successor clauses in the FAR, or the DOD or NASA FAR
 * Supplement.  Contractor/manufacturer is Silicon Graphics, Inc.,
 * 2011 N. Shoreline Blvd. Mountain View, CA 94039-7311.
 *
 * THE CONTENT OF THIS WORK CONTAINS CONFIDENTIAL AND PROPRIETARY
 * INFORMATION OF SILICON GRAPHICS, INC. ANY DUPLICATION, MODIFICATION,
 * DISTRIBUTION, OR DISCLOSURE IN ANY FORM, IN WHOLE, OR IN PART, IS STRICTLY
 * PROHIBITED WITHOUT THE PRIOR EXPRESS WRITTEN PERMISSION OF SILICON
 * GRAPHICS, INC.
 */
//  -*- C++ -*-

/*
 *
 _______________________________________________________________________
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 |
 |   $Revision: 2.2 $
 |
 |   Description:
 |	This file defines the SoByteStream class.
 |
 |   Author(s): David Mott
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_BYTE_STREAM_
#define  _SO_BYTE_STREAM_

#include <Inventor/SbBasic.h>

class SoNode;
class SoPath;
class SoPathList;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoByteStream
//
//  This class creates a byte stream representation of a scene graph,
//  using the SoWriteAction to write to an in memory buffer. Byte streams
//  are commonly used to transfer data, for instance during copy and paste.
//
//////////////////////////////////////////////////////////////////////////////

class SoByteStream {
  public:
    SoByteStream();
   ~SoByteStream();

    // Convert the passed node, path, or path list into a byte stream.
    // Caller may specify whether the byte stream is written in binary
    // (TRUE) or ascii (FALSE) format. The converted data can be accessed
    // through getData() and getNumBytes().
    
    void	        convert(SoNode *node, SbBool binaryFormat = TRUE);
    
    void	        convert(SoPath *path, SbBool binaryFormat = TRUE);
    
    void	        convert(SoPathList *pathList, SbBool binaryFormat = TRUE);

    // Access the byte stream data
    void *    	    	getData()   	{ return data; }
    uint32_t   		getNumBytes()	{ return numBytes; }
    
    // Unconvert a byte stream back to a path list.
    // This static routine performs an SoDB::read on the data,
    // and returns a path list of the paths read in.
    
    static SoPathList *	unconvert(SoByteStream *byteStream);
    
    static SoPathList *	unconvert(void *data, uint32_t numBytes);
  
  SoEXTENDER public:
    // This allows apps to store raw data here without converting 
    // an Inventor node, path, or path list. This sets isRaw to TRUE,
    // and that data cannot be unconverted.
    void		copy(void *d, size_t len);
    SbBool		isRawData() const { return isRaw; }
     
  private:
    void		*data;
    uint32_t		numBytes;
    SbBool		isRaw;
};

#endif // _SO_BYTE_STREAM_
