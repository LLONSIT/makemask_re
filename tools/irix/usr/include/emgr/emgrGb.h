#ifndef emgrGb_h_
#define emgrGb_h_

#include <stdlib.h>
#include <sys/uio.h>

#ifdef linux
#include <stdint.h>
#elif sgi
#include <inttypes.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct List;
   
typedef enum {
   GbFile        = 1, /* File on a local file system */
   GbBinData     = 2, /* raw array of uninterpreted data */
   GbCharString  = 3, /* character '\0' terminated string */
   GbBinData2    = 4, /* raw array of uninterpreted data,
			 but data will be copied in to private mem */
   GbMaxType     = 5
} GbType_t;

typedef struct GeneralBlock {
      
      int32_t type;
      int32_t length;
      
      void*   pValue;

      char    tag[1];
} GeneralBlock_t;

typedef struct GbFileValue {
      int32_t  size; /* size of the static attributes (size and mod time) +
                        the length of the path and file */
      char     modTime[24];
      char*    path;
      int8_t*  pContent;
} GbFileValue_t;

/* General GB allocation routine */   
GeneralBlock_t* NewGb(GbType_t t, const char* tag);
GeneralBlock_t* CloneGb(const GeneralBlock_t* pGb);

#ifdef linux
inline
#endif
const char* gbGetTag(const GeneralBlock_t* pGb);

#ifdef linux
inline
#endif
GbType_t gbGetType(const GeneralBlock_t* pGb);
   
#ifdef linux
inline
#endif
const char* gbGetStrValue(const GeneralBlock_t* pGb);

#ifdef linux
inline
#endif
const void* gbGetDataValue(const GeneralBlock_t* pGb);

#ifdef linux
inline
#endif
const GbFileValue_t* gbGetFileValue(const GeneralBlock_t* pGb);

/* Returns length of the file in GB (GbFileValue_t.pContent) */
int getGbFileLength( const GbFileValue_t* pFile);

/* Returns length of binary data at GB.pValue */   
int getGbBinDataLength( const GeneralBlock_t* pGb);


/* Returns the length of the type value assosiated with thte given GB */   
int getGbValueLength(const GeneralBlock_t* pGb);

/* Saves the file, if newFileName == NULL uses filename from pFile */   
int SaveGbFile( const GbFileValue_t* pFile, const char* newFileName );
   
   
/* Type specific GB allocations*/
GeneralBlock_t* NewGbFile(const char* tag, const char* filePath, int* pError);

/* For the binary data General block will simply store the pointer and won't
 * free it at the end. In case if there is a need to free the data -
 * the FreeGbBinData() should be called
 */   
GeneralBlock_t* NewGbBinData(const char* tag, int l, const void* pData);

/* or you can use this one, it will free the data */   
   GeneralBlock_t* NewGbBinData2(const char* tag, int l, const void* pData);
   
/* Free the BinData pointer */   
void FreeGbBinData(GeneralBlock_t* pGb);

/* A routine to duplicate the data in to dynamically allocated memory.
 * Returns new data pointer. If allocation fails - returns NULL.
 */   
const void* DupGbBinData(GeneralBlock_t* pGb);

/* The method to create String GB. It will make a private copy of the  
 * string value and free in on destruction step.
 */   
GeneralBlock_t* NewGbCharString(const char* tag, const char* pString);
   
   
/* Interface to perform type specific operations and used internally 
 * by Gb Handling routines  
 */
   
/* To serialize */   
int GetGbSerializedBlocks(GeneralBlock_t* pGb, struct List* pList);

/* And to DeSerialize */   
GeneralBlock_t* DeSerializeGB(const int8_t* pBuffer, int* pRead, int n2h);

/* Just checks if GB has a valid type */   
int CheckGb (const GeneralBlock_t* pGb);


   
/* The routine of this type should free any internal specific memmory
 * allocation, but should NOT free the parameter pointer.
 */
typedef enum {
   DynamicFree, /* assume all mem allocations were dynamic */
   StaticFree   /* assume some pointers were assigned without
		 * mem. allocation for performance reasons
		 */
} GbFreeType_t;


/* To free type specific GB*/   
void FreeGb(GeneralBlock_t* pGb, GbFreeType_t t);

   
typedef void (FreeFunc_t)(GeneralBlock_t* pGb, GbFreeType_t t);

typedef struct SerializedBlock {
      int baseNeedsToBeFreed; /* The flag shows wheather the ioVec.iov_base
                               * needs to be freed after use  
                               */
      struct iovec ioVec;
} SerializedBlock_t;

/* This func suppose to allocate and define as many SerializedBlock_t
 * entries as it needs to be able to send content of the GB over the net
 * and put those blocks in to the list. Return value shows exact number
 * of bytes need to be sent in all blocks together.
 *
 * Those blocks of data has to be organized the way that if it read
 * sequentially - the deserializing routine would be able to
 * restore content of the GB
 */
typedef int (SerializeFunc_t)(GeneralBlock_t* pGb, struct List* pList);

/* Here is the serialization routine which would need to deserialize
 * the buffer   in to appropriate structure. The trick is to avoid
 * copying of data, sa major internal pointers should not be allocated.
 * To avoid freeing it - later on the GB structture will not be submitted
 * to a free function, but the GB itself will be freed. 
 */
typedef GeneralBlock_t* (DeSerializeFunc_t)(const int8_t* pBuffer,
					    int* pRead, int n2h);

   
#ifdef __cplusplus
}
#endif


#endif
