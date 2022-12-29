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

#ifndef __iflError_h__
#define __iflError_h__

/*
    Error codes, error handling and assertion macros used by the IFL library.

    

    
*/


#include <pfmt.h>	/* for definitions of MM_HALT, etc. */

#ifdef __cplusplus

/* Error Reporting */

void iflError(int flags, const char* msg, ...);

void iflErrorV(int flags, const char* msg, va_list);

void _iflDebug(const char* msg, ...);

#endif /* __cplusplus */

#ifdef __cplusplus
extern "C" {
#endif

typedef void (iflErrorHandlerFunc)(void* arg,/* closure arg */
				   int flags,/* includes severity, see pfmt(3)*/
				   const char* msg, va_list args);
typedef iflErrorHandlerFunc* iflErrorHandlerType;

/* Standard Error Handlers */

extern iflErrorHandlerFunc iflNaiveErrorHandler; /* this is the default */

extern iflErrorHandlerFunc iflRobustErrorHandler;
    

extern iflErrorHandlerFunc iflSilentErrorHandler;

/* Handling Errors */

void iflGetErrorHandler(iflErrorHandlerType* handler, void** arg);

void iflSetErrorHandler(iflErrorHandlerType newhandler, void* newarg);

#ifdef __cplusplus
}
#endif

/*
 * Assertion macros:
 *    iflAssert() -- logically impossible conditions, elided from shipped code
 *    iflAlwaysAssert() -- logically impossible conditions,
 *			   kept (but less verbose) in shipped code
 */
extern void __iflAssert(const char *, const char *, int);

#ifdef NDEBUG
#define iflAssert(EX) ((void)0)
#define iflAlwaysAssert(EX) ((EX)?((void)0):__iflAssert(0,__FILE__,__LINE__))
#define iflDebug(args) ((void)0)
#else /* !NDEBUG */
#define iflAssert(EX)       ((EX)?((void)0):__iflAssert( # EX ,__FILE__,__LINE__))
#define iflAlwaysAssert(EX) ((EX)?((void)0):__iflAssert( # EX ,__FILE__,__LINE__))
#define iflDebug(args) _iflDebug args
#endif /* !NDEBUG */


/* iflStatus encodes status return values and object states.  There are
 * three components of an iflStatus code:
 *
 *     unsigned int mainstatus:12 -- ifl status code
 *     unsigned int subDomain:4   -- domain of subStatus
 *     unsigned int subStatus:16  -- subdomain status code
 *
 * mainstatus encodes a main status code; subStatus encodes an elaboration of
 * the main status code from another domain.  For example: status might
 * be iflOPENFAILED and subStatus might be ENOFILE to indicate why ifl
 * returned iflOPENFAILED.  In order to determine what subStatus means
 * one must examine subdomain to see whether subStatus contains UNIX errno's,
 * etc.
 *
 * The completely 0 status code, iflOKAY, is reserved.  This makes it
 * easier for most cases in which the caller does not care
 * about the specific value, but only wants to compare with iflOKAY.
 *
 * Note: this file is included by C code so general comments must use
 *       the C commenting convention.
 */

enum iflStatus {
    iflOKAY = 0
    /* Other values are really composed of fields as described above... */
};
#ifndef __cplusplus
typedef enum iflStatus iflStatus;
#endif

/*
 * Possible values for mainstatus field of an iflStatus...
 */
enum iflMainStatus {
    iflREADONLY                 = 1,
    iflWRITEONLY                = 2,
    iflBADPARAMS                = 3,
    iflUNSUPPORTEDBYLIBRARY     = 4,
    iflUNSUPPORTEDBYFORMAT      = 5,
    iflBADMAGIC                 = 6,
    iflBADIMGFMT                = 7,
    iflBADFIELDSET              = 8,
    iflBADFIELDGET              = 9,
    iflSYSTEM_CONFIGURATION_ERROR = 10,
    iflFILEINDEXOOB             = 11,

    iflMALLOCFAILED		= 12,
    iflOPENFAILED		= 13,
    iflCLOSEFAILED		= 14,
    iflREADFAILED		= 15,
    iflWRITEFAILED		= 16,
    iflSEEKFAILED		= 17,
    iflSTATFAILED		= 18,

    iflDBOPENFAILED		= 19,

    iflSCRIPTFAILED		= 20,

    iflPREMATUREEOF		= 21,
    iflCORRUPTED		= 22,
    iflUNSUPPORTEDBYFILE	= 23
    /* if values are added here, they must be added to iflMainStatusToString */
};
#ifndef __cplusplus
typedef enum iflMainStatus iflMainStatus;
#endif

/*
 * 
 */
enum iflSubDomain {
    iflSubDomainNONE     = 0, /* no subdomain; subStatus not meaningful */
    iflSubDomainUNIX     = 1, /* subStatus encodes UNIX errno */
    iflLastSubDomain     = 1
};
#ifndef __cplusplus
typedef enum iflSubDomain iflSubDomain;
#endif

/* iflStatus encoding functions (only C++ is supported).
 */
#ifdef __cplusplus

/* Translating Error Status Codes */

inline iflStatus
iflStatusEncode(unsigned int mainstatus,
		unsigned int subDomain = iflSubDomainNONE,
		unsigned int subStatus = 0)
    {
	return (iflStatus) (((mainstatus&0x0fff) << 0)
			       | ((subDomain &0x000f) << 12)
			       | ((subStatus &0xffff) << 16));
    }
#endif

/* iflStatus decoding functions
 */
#define iflGetMainStatus(iflstatus) ((iflMainStatus)(((iflstatus)>>0) & 0x0fff))
#define iflGetSubDomain(iflstatus)  ((iflSubDomain)(((iflstatus)>>12) & 0x000f))
#define iflGetSubStatus(iflstatus)  ((unsigned int)(((iflstatus)>>16) & 0xffff))

#ifdef __cplusplus
extern "C" {
#endif


char* iflStatusToString(iflStatus status, char buf[], int bufsize);

const char* iflMainStatusToString(iflMainStatus status);


#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

// Convenience class for automatically saving and restoring
// the ifl Error handler.
// Usage:
//	{
//	    iflSetLocalErrorHandler(my_error_handler, my_arg);
//	    ... calls to IFL that should use my_error_handler ...
//	} // original error handler is restored when object goes out of scope

class iflSetLocalErrorHandler {
public:
    iflSetLocalErrorHandler(iflErrorHandlerType handler, void *arg)
    {
	iflGetErrorHandler(&old_handler, &old_arg);
	iflSetErrorHandler(handler, arg);
    }
    /* non-virtual, since always on stack */
    ~iflSetLocalErrorHandler()
    {
	iflSetErrorHandler(old_handler, old_arg);
    }
protected:
    iflErrorHandlerType old_handler;
    void *old_arg;
};

#endif

#endif /* __iflError_h__ */
