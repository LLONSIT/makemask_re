#ifndef EmgrEvent_h_
#define EmgrEvent_h_

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#ifdef linux
#include <stdint.h>
#elif sgi
#include <inttypes.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*=================================================*/
/*=============      Common data      =============*/
/*=================================================*/

struct GeneralBlock;   
   
/*
 * Structure: EmgrEventHeader
 *
 *      The EmgrEventHeader structure contains all "FIXED" data pertaining
 *      to an event. 
 */
typedef struct EmgrEventHeader {

      int32_t	evClass;     /* Event Class number (application specific) */
      int32_t	evType;	     /* Event Type number (application specific) */
      int16_t   flags;       /* Event flags */
      int16_t	version;     /* Event Version (application specific) */
      int32_t	placeHolder; /* Attribute to support correct aliment  */
      int64_t	timestamp;   /* Event Time (GMT) */
      int32_t   uid;         /* User ID of a process which sends an event */
      uint32_t  evid;        /* Event id  <16 bit sq number><16 bit random> */
      int32_t	header_size; /* size of fixed and variable parts of header */
      int32_t   total_size;  /* size of entire event including header  */

} EmgrEventHeader_t;

#define EMGR_EVENT_FORWARD_FLAG (0x01)
#define EMGR_EVENT_RESPRQ_FLAG  (0x02)
#define EMGR_EVENT_BATCHRQ_FLAG (0x04)
   
/*
 * Structure: EmgrEvent
 *
 *      The EmgrEvent structure contains all public data pertaining to a
 *      managed event. All fixed length data (class, type, etc.) is stored
 *      in an EmgrEventHeader struct located at the start of the EmgrEvent
 *      struct. Pointers to various bits of variable length data (source,
 *      appname, and origin) are contained in the EmgrEvent struct as well.
 *      All private data, required by the API control layer, is located in a
 *      private event control structure which contains an EmgrEvent
 *      struct as its first element. It is for this reason that memory for
 *      an EmgrEvent structure should never be allocated directly. Instead,
 *      use the EMGR API function, emgrAllocEvent(), when allocating event
 *      resources. 
 */
typedef struct EmgrEvent {
	
	/* Fixed portion of public event data 
	 */
	EmgrEventHeader_t header;
      
	/* Variable portion of public event data 
	 */	
	char *source;          /* fully qualified local hostname */
	char *appname;         /* Name of application that owns this event */
	char *origin;          /* Name of application that logged this event */

	/* Private API data is appended here 
	 *
         * Note: Never allocate memory for an EmgrEvent struct directly.
         * Instead, always use the emgrAllocEvent() function when allocating 
	 * an event control structure. 
	 */

} EmgrEvent_t;


/*
 * Function: emgrAllocEvent()
 *
 *     The emgrAllocEvent() function allocates an EmgrEvent structure
 *     and initializes key fields in the event header.
 *
 * Parameters:
 *
 *     <appname>    Pointer to character string containing the name of
 *                  the application that "owns" the event (has domain over
 *                  event Class and Type). Note that <appname> is a required 
 *                  parameter.
 *
 *     <evClass>    Application specific Event Class Number, or zero (0) 
 *                  if this is to be a "classless" event.
 *
 *     <evType>     Application specific Event Type Number. Note that
 *                  Type number cannot be equal to zero (0) or -1.
 *
 *     <version>    Application specific Event Version Number (for
 *                  exclusive use by consumer and producer applications).
 *
 *     <origin>     Pointer to character string containing the name of
 *                  the application logging the event. If the application
 *                  logging the event is the same one that owns the events,
 *                  then <origin> can be the same as <appname>, or it can an
 *                  empty string or a NULL char pointer.
 *
 * Return Value:
 *
 *     The emgrAllocEvent() function returns a pointer to an initialized 
 *     EmgrEvent struct on success and a NULL EmgrEvent pointer on
 *     failure.
 */
EmgrEvent_t *emgrAllocEvent (const char *appname, int evClass, int evType, 
			     int version, const char *origin);
 
EmgrEvent_t *emgrCloneEvent (const EmgrEvent_t* pEvent);

/*
 * Function: emgrFreeEvent()
 *
 *     The emgrFreeEvent() function frees up all memory resources
 *     associated with an event.
 *
 * Parameters:
 *
 *     <pEvent>     Pointer to EmgrEvent struct
 *
 * Return Value:
 *
 *     The emgrFreeEvent() function returns zero (0) on success and -1 
 *     on failure. 
 */
int emgrFreeEvent(EmgrEvent_t *pEvent);

   
/*
 * Function: emgrAddItemToEvent()
 *
 *     The emgrAddItemToEvent() function adds an item (named value) to 
 *     an event. 
 *
 * Parameters:
 *
 *     <evType>     Application specific Event Type Number. Note that
 *
 *     <name>       Pointer to character string containing the item name
 *
 *     <vlaue>      Pointer to character string containing the item value
 *
 * Return Value:
 *
 *     The emgrAddItemToEvent() function returns zero (0) on success and
 *     -1 on failure. 
 *
 */
int
emgrAddItemToEvent(EmgrEvent_t *pEvent, const char *name, const char *value);


/*
 * Same as above but takes long integer, convers it to string and does
 * emgrAddItemToEvent()
 */   
int emgrAddIntItemToEvent(EmgrEvent_t* pEvent,
			  const char* name, long value);
   
/*
 * Function: emgrAddTaggedDataToEvent()
 *
 *     The emgrAddTaggedDataToEvent() function adds an arbitrary sized 
 *     block of data to an event. The data block added to the event is 
 *     identified by a tag (character string) that acts as the item 
 *     name.
 *
 * Parameters:
 *
 *     <pEvent>     Pointer to EmgrEvent struct 
 *
 *     <tag>        Pointer to character string containing the data tag
 *
 *     <pBuffer>    Pointer to buffer containing the data. The pointer has to
 *                  valid till the end of use of an event. The library
 *                  is not going to free or modify content of the data
 *
 *     <size>       Number of bytes of data in buffer
 *
 * Return Value:
 *
 *     The emgrAddTaggedDataToEvent() function returns zero (0) on
 *     success and -1 on failure. 
 */
int emgrAddTaggedDataToEvent(EmgrEvent_t *pEvent, const char *tag,
			     const void *pBuffer, size_t size);


/*
 * Function: emgrAddDataToEvent()
 *
 *     The emgrAddDataToEvent() function adds an arbitrary sized block 
 *     of data to an event. The data block added to the event using this 
 *     function does not have any tag or item name associated to it.
 *
 * Parameters:
 *
 *     <pEvent>     Pointer to EmgrEvent struct 
 *
 *     <pBuffer>    Pointer to buffer containing the data. The pointer has to
 *                  valid till the end of use of an event. The library
 *                  is not going to free or modify content of the data
 *
 *     <size>       Number of bytes of data in buffer
 *
 * Return Value:
 *
 *     The emgrAddDataToEvent() function returns zero (0) on success 
 *     and -1 on failure. 
 */
int emgrAddDataToEvent(EmgrEvent_t *pEvent, const void *pBuffer, size_t size);
   

/*
 * Function: emgrAddTaggedFileToEvent()
 *
 *     The emgrAddTaggedFileToEvent() function copies the contents of 
 *     a file to a buffer and attaches it to an event. The data block 
 *     containing the file is identified by a tag (character string) 
 *     that acts as the item name.
 *
 * Parameters:
 *
 *     <pEvent>     Pointer to EmgrEvent struct 
 *
 *     <tag>        Pointer to character string containing file tag
 *
 *     <path>       Pointer to character string containing path name of
 *                  file.
 *
 * Return Value:
 *
 *     The emgrAddTaggedFileToEvent() function returns zero (0) on
 *     success and -1 on failure. 
 */
int
emgrAddTaggedFileToEvent(EmgrEvent_t *pEvent,
			 const char *tag, const char *path);


/*
 * Function: emgrAddFileToEvent()
 *
 *     The emgrAddFileToEvent() function copies the contents of a file 
 *     to a buffer and attaches it to an event. The data block added to 
 *     an event using this function does not have any tag or item name 
 *     associated to it.
 *
 * Parameters:
 *
 *     <pEvent>     Pointer to EmgrEvent struct 
 *
 *     <path>       Pointer to character string containing path name of
 *                  file 
 *
 * Return Value:
 *
 *     The emgrAddFileToEvent() function returns zero (0) on success 
 *     and -1 on failure. 
 */
int emgrAddFileToEvent(EmgrEvent_t *pEvent, const char *path);


/*
 * Function: emgrAddGbToEvent()
 *
 *     The emgrAddGbToEvent() function adds a GeneralBlock to an event.
 *
 * Parameters:
 *
 *     <pEvent>     Pointer to EmgrEvent struct 
 *
 *     <pNewGb>     Pointer to the GeneralBlock struct to add to the
 *                  event
 *
 * Return Value:
 *
 *     The emgrAddGbToEvent() function returns zero (0) on success 
 *     and -1 on failure. 
 */
int emgrAddGbToEvent(EmgrEvent_t *pEvent, struct GeneralBlock *pGb);


/*
 * Function: emgrCheckEvent()
 *
 *     The emgrCheckEvent() function performs a sanity check to ensure
 *     that an event structure is valid.
 *
 * Parameters:
 *
 *     <pEvent>     Pointer to EmgrEvent struct 
 *
 * Return Value:
 *
 *     The emgrCheckEvent() function returns FALSE (0) if the event is
 *     NOT vlid and TRUE (1) if it is valid.
 */
int emgrCheckEvent(const EmgrEvent_t *pEvent);
   

/*==================================================*/
/*=========== Consumer Related Functions ===========*/
/*==================================================*/


/*
 * Function: emgrGetEventItem()
 *
 *     The emgrGetEventItem() function locates a named item attached to 
 *     an EmgrEvent struct.
 *
 * Parameters:
 *
 *     <pEvent>     Pointer to EmgrEvent struct 
 *
 *     <name>       Pointer to character string containing item name
 *
 *     <pType>      Pointer to location where item type is to be stored
 *
 *     <pLength>    Pointer to location where item's length is to be stored
 *
 *     Length will represent sting length for the Character String Value,
 *     length of a blob of data for Binary data or file length for 
 *     a file data
 *
 * Return Value:
 *
 *     The emgrGetEventItem() function returns zero a pointer to an item
 *     on success or a NULL pointer on failure.
 */
const void* emgrGetEventItem(const EmgrEvent_t *pEvent, const char *name,
			     int *pType, int* pLength);


/*
 * Function: emgrGetFirstEventItem()
 *
 *     The emgrGetFirstEventItem() returns the first item attached to an 
 *     event.
 *
 * Parameters:
 *
 *     <pEvent>     Pointer to EmgrEvent struct 
 *
 *     <pName>      Pointer to location where item name pointer is to 
 *                  be stored
 *
 *     <pValue>     Pointer to location where item value pointer is to
 *                  be stored
 *
 *     <pType>      Pointer to location where item type is to be stored
 *
 *     <pLength>    Pointer to location where item's length is to be stored
 *
 *     Length will represent sting length for the Character String Value,
 *     length of a blob of data for Binary data or file length for 
 *     a file data
 * Return Value:
 *
 *     The emgrGetFirstEventItem() function returns zero (0) on success 
 *     and -1 on failure. 
 */
int emgrGetFirstEventItem(EmgrEvent_t* pEvent, 
                          const char **pName, const void **pValue,
			  int *pType, int* pLength);

/*
 * Function: emgrGetNextEventItem()
 *
 *     The emgrGetNextEventItem() function returns the next item attached 
 *     to an event.
 *
 * Parameters:
 *
 *     <pEvent>     Pointer to EmgrEvent struct 
 *
 *     <pName>      Pointer to location where item name pointer is
 *                  stored 
 *
 *     <pValue>     Pointer to location where item value pointer is
 *                  stored
 *
 *     <pType>      Pointer to location where item type is stored
 *
 *     <pLength>    Pointer to location where item's length is to be stored
 *
 *     Length will represent sting length for the Character String Value,
 *     length of a blob of data for Binary data or file length for 
 *     a file data
 * Return Value:
 *
 *     The emgrGetNextEventItem() function returns zero (0) on success 
 *     and -1 on failure. 
 */
int emgrGetNextEventItem (EmgrEvent_t *pEvent,
                          const char **pName, const void **pValue,
			  int* pType, int* pLength);


/*
 * Function: emgrGetFirstEventGb()
 *
 *     The emgrGetFirstEventGb() function returns the first GeneralBlock 
 *     attached to an event.
 *
 * Parameters:
 *
 *     <pEvent>     Pointer to EmgrEvent struct 
 *
 * Return Value:
 *
 *     The emgrGetFirstEventGb() function returns a pointer to a
 *     GeneralBlock struct on success and a NULL pointer on failure.
 */
const struct GeneralBlock *emgrGetFirstEventGb(EmgrEvent_t *pEvent);


/*
 * Function: emgrGetNextEventGb()
 *
 *     The emgrGetNextEventGb() function returns the next GeneralBlock
 *     in sequence attached to an event.
 *
 * Parameters:
 *
 *     <pEvent>     Pointer to EmgrEvent struct 
 *
 * Return Value:
 *
 *     The emgrGetNextEventGb() function returns a pointer to a
 *     GeneralBlock struct on success and a NULL pointer on failure.
 */
const struct GeneralBlock *emgrGetNextEventGb (EmgrEvent_t *pEvent);


/*
 * Function: emgrSearchGb()
 *
 *     The emgrSearchGb() function locates the GeneralBlock attached to 
 *     an event with having a specified tag (item name).
 *
 * Parameters:
 *
 *     <pEvent>     Pointer to EmgrEvent struct 
 *
 *        <tag>     Pointer to character string containing GeneralBlock
 *                  tag
 *
 * Return Value:
 *
 *     The emgrSearchGb() function returns a pointer to a GeneralBlock
 *     struct on success and a NULL pointer on failure.
 */
const struct GeneralBlock *emgrSearchGb(const EmgrEvent_t *pEvent,
					const char *tag);


/*
 * Function: emgrBuildQSearch()
 *
 *     builds event's internal bsearch table to be able to perform bsearch
 *     operation
 *
 * Parameters:
 *
 *     <pEvent>     Pointer to EmgrEvent struct 
 *
 * Return Value:
 *
 *     The emgrBuildQSearch() function returns zero (0) on success and -1 
 *     on failure.
 */
int emgrBuildQSearch(EmgrEvent_t *pEvent);
   

   
/*
 * Function: emgrSetToForward()
 *
 *     sets certain attributes to the event so that event will be forwarded
 *     by emgr to another emgr(s) using specified forwarding path
 *
 * Parameters:
 *
 *     <pEvent>     Pointer to EmgrEvent struct 
 *
 *     <forwardPath> Character string representing forwarding path
 *                   in format "(<host name>[:port]>)+".
 *                   Example "host1>host2:5553>host3"
 * Return Value:
 *
 *     The emgrSetToForward() function returns zero (0) on success and -1 
 *     if forwarding path has an invalid format.
 */
int emgrSetToForward(EmgrEvent_t *pEven, const char* forwardPath );
   
/*
 * Function: emgrForwardEvent()
 *
 *     sets certain attributes to the event so that event will be forwarded
 *     by emgr to another emgr(s) using specified forwarding path. Then
 *     it uses emgrSendEvent() to send an event to the first address
 *     in forwarding path.
 *
 * Parameters:
 *
 *     <pEvent>     Pointer to EmgrEvent struct 
 *
 *     <forwardPath> Character string representing forwarding path
 *                   in format "(<host name>[:port]\>)+".
 *                   Example "host1>host2:5553>host3" would specify
 *                   forwarding path to host1 then host2 port 5558 then
 *                   host3
 * Return Value:
 *
 *     The emgrSendEvent() function returns zero (0) on success and -1 
 *     if forwarding path has an invalid format or a communication error
 *     with a first host occurred.
 */
int emgrForwardEvent(EmgrEvent_t *pEven, const char* forwardPath );

   
/*
 * Function: emgrPrintEvent()
 *
 *     Prints en event content in to the out FILE stream
 *     
 *
 * Parameters:
 *
 *     <pEvent>     Pointer to EmgrEvent struct 
 *     <FILE>       Pointer to FILE stream 
 * Return Value:
 *
 *     Non
 *     
 */
void emgrPrintEvent(const EmgrEvent_t *pEvent, FILE* out);


void emgrEventUpdateEvTimeStamp(EmgrEvent_t* pEvent);
int  emgrEventUpdateSource(EmgrEvent_t* pEvent, const char* source);
   
#ifdef __cplusplus
}
#endif

#endif
