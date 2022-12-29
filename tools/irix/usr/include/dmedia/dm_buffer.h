/*
 * dm_buffer.h
 */

#if !defined( _DM_BUFFER_H_ )
#define _DM_BUFFER_H_

#include <sys/types.h>
#include <sys/cachectl.h>
#include <sys/dmcommon.h>
#include <dmedia/dmedia.h>
#include <dmedia/dm_params.h>
#include <dmedia/dm_image.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DM_POOL_NAME 		"DM_POOL_NAME"
#define DM_POOL_SHARE		"DM_POOL_SHARE"
#define DM_POOL_CACHEABLE 	"DM_POOL_CACHEABLE"
#define DM_POOL_MAPPED 		"DM_POOL_FAST_MAP"
#define DM_POOL_NO_ECC 		"DM_POOL_NO_ECC"
#define DM_POOL_VARIABLE	"DM_POOL_VARIABLE"
#define DM_POOL_SIZE		"DM_POOL_SIZE"
#define DM_POOL_NODE_MASK       "DM_POOL_NODE_MASK"
#define DM_POOL_NODE_DIST       "DM_POOL_NODE_DIST"
#define DM_POOL_LOW_MEM		"DM_POOL_LOW_MEM"

#define DM_BUFFER_TYPE		"DM_BUFFER_TYPE"
#define DM_BUFFER_SIZE		"DM_BUFFER_SIZE"
#define DM_BUFFER_COUNT		"DM_BUFFER_COUNT"
#define DM_BUFFER_ALIGNMENT 	"DM_BUFFER_ALIGNMENT"

#define DM_BUFFER_MAX_AUX_DATA_SIZE 	128
#define DM_BUFFER_MAX_EVENT_DATA_SIZE 	128

typedef enum {
    DM_BUFFER_TYPE_PAGE,
    DM_BUFFER_TYPE_TILE
}DMbuffertype;

typedef enum {
    DM_POOL_INTERPROCESS
}DMpoolshare;

typedef struct __DMbufferpool  	*DMbufferpool;
typedef struct __DMbuffer	*DMbuffer;

DMstatus dmBufferSetPoolDefaults( DMparams *poolParams, 
				  int bufferCount, int bufferSize,
				  DMboolean cacheable, DMboolean mapped );

DMstatus dmBufferCreatePool( const DMparams     *poolParams, 
			     DMbufferpool *returnPool );
DMstatus dmBufferDestroyPool( DMbufferpool pool );

int 	 dmBufferGetAllocSize( DMbufferpool pool);

int 	 dmBufferGetPoolFD( DMbufferpool pool );
DMstatus dmBufferSetPoolSelectSize( DMbufferpool pool, 
				    int minBytesFree );
DMstatus dmBufferGetPoolState( DMbufferpool pool, 
                               long long *bytesAvailable,
                               int *buffersAvailable );

DMstatus dmBufferAllocate( DMbufferpool pool, DMbuffer *buffer );
DMstatus dmBufferAllocateSize(DMbufferpool pool, int size, DMbuffer *buffer);
DMstatus dmBufferAttach( DMbuffer buffer );
DMstatus dmBufferFree( DMbuffer buffer );
void 	 *dmBufferMapData( DMbuffer buffer );

USTMSCpair dmBufferGetUSTMSCpair( DMbuffer buffer );
DMstatus   dmBufferSetUSTMSCpair( DMbuffer buffer, USTMSCpair ustmsc );

int	 dmBufferGetSize( DMbuffer buffer );
DMstatus dmBufferSetSize( DMbuffer buffer, int size );

DMimagetype dmBufferGetImageType( DMbuffer buffer );
DMstatus    dmBufferSetImageType( DMbuffer buffer, DMimagetype type );

DMstatus dmBufferSetUserData( DMbuffer buffer, const u_char *data, int size );
DMstatus dmBufferGetUserData( DMbuffer buffer, u_char *data, int *size );

DMstatus dmBufferGetGLPoolParams( const DMparams *imageParams,
				  DMparams *poolParams );

DMstatus _dmPoolMergeParams( DMparams *plist, int align, DMbuffertype bt,
			     int nframes, int bufsize );

/*
 * Error codes
 */

#define DM_BUFFER_INVALID_POOL_PARAMS	 DM_BUFFER_EBASE+0 	/* "Invalid Pool Params" */
#define DM_BUFFER_OUT_OF_SPACE		 DM_BUFFER_EBASE+1	/* "Pool ran out of space" */
#define DM_BUFFER_TOO_SMALL		 DM_BUFFER_EBASE+2	/* "Buffer is too small for the operation" */
#define DM_BUFFER_GL_INADEQUATE_INFO	 DM_BUFFER_EBASE+3	/* "Inadequate information to setup pool params" */
#define DM_BUFFER_GL_PARAMS_INVALID	 DM_BUFFER_EBASE+4	/* "Invalid params for setting up pool for OpenGL" */
#define DM_BUFFER_ALIGNMENT_INCOMPATIBLE DM_BUFFER_EBASE+5	/* "Buffer Alignments are Incompatible" */
#define DM_BUFFER_USER_DATA_SIZE_INVALID DM_BUFFER_EBASE+6	/* "User data size is invalid" */
#define DM_BUFFER_UNIMPLEMENTED 	 DM_BUFFER_EBASE+999	/* "Function unimplemented for current release" */

#ifdef __cplusplus 
}
#endif

#endif /* _DM_BUFFER_H_ */
