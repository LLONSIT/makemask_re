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
 |   $Revision: 2.1 $
 |
 |   Description:
 |	This file defines the base SoError class.
 |
 |   Classes:
 |	SoError
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_ERROR
#define  _SO_ERROR

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoError
//
//  This is the base class for all error classes, which provide error
//  handling for applications.
//
//  There are two facets to errors: posting and handling. An error is
//  posted when some bad condition occurs. Posting is done primarily
//  by the Inventor library itself, but extenders can post their own
//  errors. Posting an error creates an instance of the appropriate
//  error class (or subclass) and then passes it to the active error
//  handler. The default handler just prints an appropriate message to
//  stderr. Applications can override this behavior by supplying a
//  different handler (by specifying a callback function).
//
//  Each subclass of SoError supports the setHandlerCallback() method,
//  which is used to set the callback function to handle errors. The
//  callback for the most derived class of a specific error instance
//  is used to handle an event.
//
//  The error instance passed to a callback is deleted immediately
//  after the callback is called; an application that wishes to save
//  info from the instance has to copy it out first.
//
//  Each error class contains a run-time class type id (SoType) that
//  can be used to determine the type of an instance. The base class
//  defines a character string that represents a detailed error
//  message that is printed by the default handler.
//
//  All handlers are called by the SoError::handleError() method. When
//  debugging, you can set a breakpoint on this method to stop right
//  before an error is handled.
//
//////////////////////////////////////////////////////////////////////////////

#include <Inventor/SbString.h>
#include <Inventor/SoType.h>

class SoError;		// Forward reference

class SoBase;
class SoEngine;
class SoNode;
class SoPath;

// Error handling callbacks are of this type:
typedef void	SoErrorCB(const SoError *error, void *data);

class SoError {

  public:
    // Sets/returns handler callback for SoError class
    static void		setHandlerCallback(SoErrorCB *cb, void *data)
	{ handlerCB = cb; cbData = data; }
    static SoErrorCB *	getHandlerCallback()	{ return handlerCB; }
    static void *	getHandlerData()	{ return cbData; }

    // Returns debug string containing full error info from instance
    const SbString &	getDebugString() const { return debugString; }

    // Returns type identifier for SoError class
    static SoType	getClassTypeId()	{ return classTypeId; }

    // Returns type identifier for error instance
    virtual SoType	getTypeId() const;

    // Returns TRUE if instance is of given type or is derived from it
    SbBool		isOfType(SoType type) const;

  SoEXTENDER public:
    // Posts an error. The debugString will be created from the given
    // arguments, which are in printf() format
    static void		post(const char *formatString ...);

    // These are convenience functions that return a printable string
    // representing the given object. For example, a node is
    // represented by name (if it has one) and by address; the
    // returned string will be something like:
    //    node named "squid" at address 0x1004dcba
    static SbString	getString(const SoNode *node);
    static SbString	getString(const SoPath *path);
    static SbString	getString(const SoEngine *engine);

  SoINTERNAL public:
    // Initializes SoError class
    static void		initClass();

    // Initialize ALL Inventor error classes
    static void		initClasses();

  protected:
    // The default error handler callback - it just prints to stderr
    static void		defaultHandlerCB(const SoError *error, void *data);

    // Returns handler callback (and data) to use for a given instance
    virtual SoErrorCB *	getHandler(void *&data) const;

    // Sets/appends to the debug string
    void		setDebugString(const char *string)
	{ debugString = string; }
    void		appendToDebugString(const char *string)
	{ debugString += string; }

    // Calls appropriate handler for an error instance. Application
    // writers can set breakpoints at this when debugging.
    void		handleError();

  private:
    static SoType	classTypeId;	// Type id of SoError class
    static SoErrorCB	*handlerCB;	// Handler callback for SoError class
    static void		*cbData;	// User data for callback
    static SbBool	wasInitted;	// TRUE if error class initialized
    SbString		debugString;	// Detailed error message string

    // The getString() methods use this one
    static SbString	getBaseString(const SoBase *base, const char *what);
};

#endif /* _SO_ERROR */
