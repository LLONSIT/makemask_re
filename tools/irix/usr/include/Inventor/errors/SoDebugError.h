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
 |	This file defines the SoDebugError class.
 |
 |   Classes:
 |	SoDebugError
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_DEBUG_ERROR
#define  _SO_DEBUG_ERROR

#include <Inventor/errors/SoError.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoDebugError
//
//  This class is used for all errors reported from the debugging
//  version of the Inventor library. These errors are typically
//  programmer errors, such as passing a NULL pointer or an
//  out-of-range index. The post() method takes the name of the
//  Inventor method that detected the error, to aid the programmer in
//  debugging.
//
//////////////////////////////////////////////////////////////////////////////


#if _COMPILER_VERSION>=710
#  pragma set woff 1375
#endif

class SoDebugError : public SoError {

  public:
    enum Severity {
	ERROR,		// Error
	WARNING,	// Just a warning
	INFO		// No error, just information
    };

    // Sets/returns handler callback for SoDebugError class
    static void		setHandlerCallback(SoErrorCB *cb, void *data)
	{ handlerCB = cb; cbData = data; }
    static SoErrorCB *	getHandlerCallback()	{ return handlerCB; }
    static void *	getHandlerData()	{ return cbData; }

    // Returns type identifier for SoDebugError class
    static SoType	getClassTypeId()	{ return classTypeId; }

    // Returns type identifier for error instance
    virtual SoType	getTypeId() const;

    // Returns severity of error (for use by handlers)
    SoDebugError::Severity getSeverity() const	{ return severity; }

  SoEXTENDER public:
    // Posts an error
    static void		post(const char *methodName,
			     const char *formatString ...);

    // Posts a warning
    static void		postWarning(const char *methodName,
				    const char *formatString ...);

    // Posts an informational (non-error) message
    static void		postInfo(const char *methodName,
				 const char *formatString ...);

  SoINTERNAL public:
    // Initializes SoDebugError class
    static void		initClass();

  protected:
    // Returns handler callback (and data) to use for a given instance
    virtual SoErrorCB *	getHandler(void *&data) const;

  private:
    static SoType	classTypeId;	// Type id of SoDebugError class
    static SoErrorCB	*handlerCB;	// Handler callback for class
    static void		*cbData;	// User data for callback

    Severity		severity;	// Severity of error
};

#if _COMPILER_VERSION>=710
#  pragma reset woff 1375
#endif

#endif /* _SO_DEBUG_ERROR */
