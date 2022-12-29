#ifndef __INC_DM_PARAMS_H__
#define __INC_DM_PARAMS_H__  
    
/*****************************************************************************
*
*  Copyright 1993, Silicon Graphics, Inc.
*  All Rights Reserved.
*
*  This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics, Inc.;
*  the contents of this file may not be disclosed to third parties, copied or
*  duplicated in any form, in whole or in part, without the prior written
*  permission of Silicon Graphics, Inc.
*
*  RESTRICTED RIGHTS LEGEND:
*  Use, duplication or disclosure by the Government is subject to restrictions
*  as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data
*  and Computer Software clause at DFARS 252.227-7013, and/or in similar or
*  successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -
*  rights reserved under the Copyright Laws of the United States.
* 
*****************************************************************************/

#include <dmedia/dmedia.h>
#include <stdlib.h>		/* for size_t */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef PARAM_REGISTRY
#define DM_ENUM_DEF(paramName,const,value,name,full_name) const = value
#define DM_TYPE_DEF(paramName,type) /*nothing*/
#else
#define DM_ENUM_DEF(paramName,const,value,name,full_name) register_enum const value name full_name
#define DM_TYPE_DEF(paramName,type) \
register_type paramName type \

#endif

/**********************************************************************
*
* Data Types
*
**********************************************************************/

typedef enum __DMparamtype
{
    DM_TYPE_ENUM		= 100,
    DM_TYPE_INT			= 101,
    DM_TYPE_STRING		= 102,
    DM_TYPE_FLOAT		= 103,
    DM_TYPE_FRACTION		= 104,
    DM_TYPE_PARAMS		= 105,
    DM_TYPE_TOC_ENTRY		= 106,
    DM_TYPE_LONG_LONG		= 107,
    DM_TYPE_BINARY		= 108,
    
    DM_TYPE_ENUM_ARRAY		= 110,
    DM_TYPE_INT_ARRAY		= 111,
    DM_TYPE_STRING_ARRAY	= 112,
    DM_TYPE_FLOAT_ARRAY		= 113,
    DM_TYPE_FRACTION_ARRAY	= 114,

    DM_TYPE_INT_RANGE		= 121,
    DM_TYPE_FLOAT_RANGE		= 123,
    DM_TYPE_FRACTION_RANGE	= 124
} DMparamtype;

typedef struct __DMparams DMparams;

/**********************************************************************
*
* Structure definitions for the various data types.
*
**********************************************************************/

/********
*
* DMenumarray
*
********/

typedef struct DMenumarray
{
    int		elemCount;
    int		capacity;
    int*	elems;
} DMenumarray;

/********
*
* DMintarray
*
********/

typedef struct DMintarray
{
    int		elemCount;
    int		capacity;
    int*	elems;
} DMintarray;

/********
*
* DMstringarray
*
********/

typedef struct DMstringarray
{
    int		elemCount;
    int		capacity;
    char**	elems;
} DMstringarray;

/********
*
* DMfloatarray
*
********/

typedef struct DMfloatarray
{
    int		elemCount;
    int		capacity;
    double*	elems;
} DMfloatarray;

/********
*
* DMfractionarray
*
********/

typedef struct DMfractionarray
{
    int		elemCount;
    int		capacity;
    DMfraction*	elems;
} DMfractionarray;

/********
*
* DMintrange
*
********/

typedef struct DMintrange
{
    int		low;
    int		high;
} DMintrange;

/********
*
* DMfloatrange
*
********/

typedef struct DMfloatrange
{
    float	low;
    float	high;
} DMfloatrange;

/********
*
* DMfractionrange
*
********/

typedef struct DMfractionrange
{
    DMfraction	low;
    DMfraction	high;
} DMfractionrange;

/**********************************************************************
*
* Parameter lists
*
* Parameter lists are used to set and adjust the parameters of
* digital media objects such as audio ports, compression functions,
* video devices, and movie tracks.  They allow you to create a
* configuration (e.g., audio rate, width, etc.) and use it to
* set up an audio part and a movie.
*
* A general rule is followed by these parameter list functions: 
* ownership of data is *not* passed during procedure calls, except
* in the create and destroy functions.  The functions that take
* strings will copy the strings if they want to keep them.  Functions
* that return strings or other structures retain ownership and the
* called must not free them.
*
**********************************************************************/

/**********************************************************************
*
* Function Declarations
*
* These are the functions used to manipulate parameter lists.  
* Typical usage scenarios are as follows:
*
* 1) When opening a port or initializing an object, a parameter list
*    is passed in to configure it.
*
*	DMparams* params;
*       dmParamsCreate( &params );
*       mvSetMovieDefaults( params, ... );
*       ...
*       mvCreateFile( ..., params );
*       dmParamsDestroy( params );
*
* 2) When changing the settings on a port or object, a parameter list
*    is passed in that holds all of the parameters to change.
*
*	DMparams* params;
*       dmParamsCreate( &params );
*	dmParamsSetFloat( params, DM_IMAGE_RATE, 15.0 );
*       mvSetParams( imageTrack, params, NULL );
*       dmParamsDestroy( params );
*
*    Libraries will usually provide convenience functions that allow
*    parameters to be changed mare conveniently:
*
*	mvSetImageRate( imageTrack, 15.0 );
*
* All functions that can possibly fail return an error code indicating 
* success or failure.  The only reason for failure in these routines
* is a lack of memory.
*
**********************************************************************/

/********
*
* Creating and destroying parameter lists.
*
* The creation function can fail because of lack of memory, so 
* it returns an error code.  The destructor can never fail.
*
* These are the only functions that ever allocate and free
* parameter lists.  Other libraries should *not* provide wrapper
* functions to create parameter lists and return them to the user.
*
* A program is correctly written if every dmParamsCreate
* is balanced by a dmParamsDestroy.
*
********/

extern DMstatus     dmParamsCreate   (DMparams** returnNewList);

extern void         dmParamsDestroy  (DMparams*  params);
				       
/********
*
* Functions for getting values from a param list.
*
********/

extern int                    dmParamsGetEnum        (const DMparams*    params,
					              const char*        paramName);
extern int                    dmParamsGetInt         (const DMparams*    params,
					              const char*        paramName );
extern long long              dmParamsGetLongLong    (const DMparams*    params,
					              const char*        paramName);
extern const char*            dmParamsGetString      (const DMparams*    params,
					              const char*        paramName);
extern const void*            dmParamsGetBinary      (const DMparams*    params,
					              const char*        paramName,
					                    size_t*	 dataSize);
extern double                 dmParamsGetFloat       (const DMparams*    params,
					              const char*        paramName );
extern DMfraction             dmParamsGetFract       (const DMparams*    params,
					              const char*        paramName);
extern const DMparams*        dmParamsGetParams      (const DMparams*    params,
					              const char*        paramName);
extern const DMenumarray*     dmParamsGetEnumArray   (const DMparams*    params,
					              const char*        paramName);
extern const DMintarray*      dmParamsGetIntArray    (const DMparams*    params,
					              const char*        paramName);
extern const DMstringarray*   dmParamsGetStringArray (const DMparams*    params,
					              const char*        paramName);
extern const DMfloatarray*    dmParamsGetFloatArray  (const DMparams*    params,
					              const char*        paramName);
extern const DMfractionarray* dmParamsGetFractArray  (const DMparams*    params,
					              const char*        paramName);
extern const DMintrange*      dmParamsGetIntRange    (const DMparams*    params,
					              const char*        paramName);
extern const DMfloatrange*    dmParamsGetFloatRange  (const DMparams*    params,
					              const char*        paramName);
extern const DMfractionrange* dmParamsGetFractRange  (const DMparams*    params,
					              const char*        paramName);

/********
*
* Functions for setting values in a param list.
*
* For strings, parameter lists, toc entries, arrays, and ranges, the
* data are copied so that the caller retains ownership of the memory.
*
********/


extern DMstatus  dmParamsSetEnum              (DMparams*       params,
				         const char*           paramName,
				         const int             value);
extern DMstatus  dmParamsSetLongLong         (DMparams*        params,
				        const char*            paramName,
				        const long long        value);
extern DMstatus  dmParamsSetInt              (DMparams*        params,
				        const char*            paramName,
				        const int              value);
extern DMstatus  dmParamsSetString           (DMparams*        params,
				        const char*            paramName,
				        const char*            value);
extern DMstatus  dmParamsSetBinary           (DMparams*        params,
					const char*            paramName,
					const size_t	       dataSize,
					const void*	       data);
extern DMstatus  dmParamsSetFloat            (DMparams*        params,
				        const char*            paramName,
				        const double           value);
extern DMstatus  dmParamsSetFract            (DMparams*        params,
				        const char*            paramName,
				        const DMfraction       value);
extern DMstatus  dmParamsSetParams           (DMparams*        params,
				        const char*            paramName,
				        const DMparams*        value);
extern DMstatus  dmParamsSetEnumArray        (DMparams*        params,
					const char*            paramName,
					const DMenumarray*     value);
extern DMstatus  dmParamsSetIntArray         (DMparams*        params,
					const char*            paramName,
					const DMintarray*      value);
extern DMstatus  dmParamsSetStringArray      (DMparams*        params,
					const char*            paramName,
					const DMstringarray*   value);
extern DMstatus  dmParamsSetFloatArray       (DMparams*        params,
					const char*            paramName,
					const DMfloatarray*    value);
extern DMstatus  dmParamsSetFractArray       (DMparams*        params,
					const char*            paramName,
					const DMfractionarray* value);
extern DMstatus  dmParamsSetIntRange         (DMparams*        params,
					const char*            paramName,
					const DMintrange*      value);
extern DMstatus  dmParamsSetFloatRange       (DMparams*        params,
					const char*            paramName,
					const DMfloatrange*    value);
extern DMstatus  dmParamsSetFractRange       (DMparams*        params,
					const char*            paramName,
					const DMfractionrange* value);

/********
*
* Manipulating the elements of a list.
*
********/

extern void         dmParamsRemoveElem         (DMparams*    params,
				          const char*        paramName);

extern int          dmParamsGetNumElems  (const DMparams*    params);

extern const char*  dmParamsGetElem      (const DMparams*    params,
				          const int          index);

extern DMparamtype  dmParamsGetElemType  (const DMparams*    params,
				          const int          index);

extern DMparamtype  dmParamsGetType  	 (const DMparams*    params,
				          const char*        paramName);

extern DMboolean    dmParamsIsPresent    (const DMparams*    params,
				          const char*        paramName);

extern DMstatus     dmParamsCopyElem     (const DMparams*    fromParams,
					  const char*        paramName,
					        DMparams*    toParams);

extern DMboolean    dmParamsAreEqual     (const DMparams     *params1, 
					  const DMparams     *params2);

extern DMstatus     dmParamsCopyAllElems (const DMparams*     fromParams,
					        DMparams*     toParams);

extern DMstatus     dmParamsScan	 (const DMparams*     params,
					        DMstatus    (*scanFunc)(
					  		      const DMparams*  params,
					                      const char*      paramName,
						                    void*      scanArg, 
						                    DMboolean* stopScan),
					        void*	      scanArg);

/**********************************************************************
*
* Flattening parameter lists for storage in files.
*
**********************************************************************/

extern size_t	dmParamsFlatten	   (const DMparams* params,
				    const char*     paramName,
				    const size_t    bufferSize,
				          void*     buffer);

extern DMstatus	dmParamsUnflatten  (const size_t    bufferSize,
				    const void*     buffer,
				          DMparams* destination);

/**********************************************************************
*
* Parameter Registry
*
**********************************************************************/

/* XXX Need man pages for these. */
					   
DMstatus dmGetParamType		(const char*        paramName,
				       DMparamtype* returnType);


DMstatus dmGetEnumName		(const char*  paramName,
				 const int    enumValue,
				 const char** returnShortName,
				 const char** returnFullName);

DMstatus dmGetEnumValue		(const char*  paramName,
				 const char*  shortName,
				       int*   returnValue);
				 
/**********************************************************************
*
* Media
*
* Every set of parameters that describes a format includes the
* parameter DM_MEDIUM to indicate what kind of data is being
* described.
*
**********************************************************************/

#define DM_MEDIUM	"DM_MEDIUM"

DM_TYPE_DEF( DM_MEDIUM, ENUM )

typedef enum __DMmedium
{
DM_ENUM_DEF( DM_MEDIUM, DM_IMAGE, 200, "image", "Image" ),
DM_ENUM_DEF( DM_MEDIUM, DM_AUDIO, 201, "audio", "Audio" ),
DM_ENUM_DEF( DM_MEDIUM, DM_TIMECODE, 202, "timecode", "Timecode" ),
DM_ENUM_DEF( DM_MEDIUM, DM_TEXT, 203, "text", "Text" )
} DMmedium;


/**********************************************************************
*
* CodecType
*
* Describes the type of codec; sync or async:
*
* Async Codec:
*            _______________  
*           |               |
*  raw_in-->|  Compressor   |-->comp_out   
*           |_______________|
*
*            _______________
*           |               |
* comp_in-->|  Decompressor |-->raw_out
*           |_______________|
*
*
* Sync Codec:
*            _______________
*           |               |
*  raw_in-->|  Compressor   |-->comp_out
*           |---------------|
* comp_in-->|  Decompressor |-->raw_out
*           |_______________|
*  
*  
*  While the compressor and decompressor are independent in the async codec,
*  in the case of the sync codec, no output is produced until the
*  appropriate data is fed to both inputs.
*
**********************************************************************/

#define DM_CODEC_TYPE	"DM_CODEC_TYPE"

DM_TYPE_DEF( CODEC_TYPE, ENUM )

typedef enum __DMcodecType
{
DM_ENUM_DEF( DM_CODEC_TYPE, DM_SYNC_CODEC,  210, "sync_codec", "Sync_codec" ),
DM_ENUM_DEF( DM_CODEC_TYPE, DM_ASYNC_CODEC, 211, "sync_codec", "Async_codec" )
} DMcodecType;

#ifdef __cplusplus 
}
#endif

#endif /* ! __INC_DM_PARAMS_H__  */
