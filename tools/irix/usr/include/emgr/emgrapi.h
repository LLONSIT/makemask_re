#ifndef EMGRAPI_H
#define EMGRAPI_H

#include <stdlib.h>
#include <sys/time.h>
#ifdef linux
#include <stdint.h>
#elif sgi
#include <inttypes.h>
#endif

#include "EmgrEvent.h"
#include "emgrSubscrApi.h"
#include "emgrGb.h"

#ifdef __cplusplus
extern "C" {
#endif


/* 
 * Function: emgrIsDaemonInstalled()
 *         
 *     The emgrIsDaemonInstalled() function checks to see if the Event 
 *     Manager is installed on the local system.
 *
 * Parameters: 
 *
 *     None
 *
 * Return Value:       
 *
 *     The emgrIsDaemonInstalled() function returns one (1) if the Event
 *     Manager is installed on the local system and zero (0) if the Event 
 *     Manager is not installed.
 */
int emgrIsDaemonInstalled();

/* 
 * Function: emgrIsDaemonStarted()
 *
 *     The emgrIsDaemonStarted() function checks to see if the Event
 *     Manager server is running on a specified system.
 *
 * Parameters:
 *
 *     <server>     Name of host to check
 *
 * Return Value:    
 *
 *     The emgrIsDaemonStarted() function returns one (1) if the Event
 *     Manager is running on the local system and zero (0) if the Event 
 *     Manager is not running.
 */
int emgrIsDaemonStarted(const char *server);

/* 
 * Function: getConfigValue()
 *
 *     The getConfigValue() function locates the config value having
 *     the given key.
 *
 * Parameters:
 *
 *     <key>        Pointer to character string containing search key.
 *
 *     <value>      Pointer to location where result string pointer is to 
 *                  be stored.
 * 
 *     <from>       Token that lets getConfigValue() know where to begin 
 *                  its search. <from> is NULL the first time getConfigValue()
 *                  is called. The return value from previous calls is passed
 *                  with the next call so that getConfigValue() is able to
 *                  continue its search from the place where it left off.
 *
 * Return Value: 
 *
 *     The getConfigValue() function returns a token indicating where to
 *     begin the search the next time getConfigValue() is called.
 */
typedef void*   SearchMarker_t;
SearchMarker_t getConfigValue  (const char *key, 
				const char **value, SearchMarker_t from);


/*====================================================================*/
/*=============      Producer functions description      =============*/
/*====================================================================*/


/* 
 * Function: emgrSendEvent()
 *
 *     The emgrSendEvent() function is used to send an event to the
 *     Event Manager on the specified host.
 *
 * Parameters:
 *
 *    <pEvent>      Pointer to EmgrEvent struct
 *
 *    <host>        The name of the host event is to be sent to. If <host> 
 *                  is NULL or the empty string, then the default server 
 *                  for the local node will be used.
 *
 * Return Value: 
 *
 *     The emgrSendEvent() function returns zero (0) on success and
 *     errno on failure.
 */
int emgrSendEvent(EmgrEvent_t *pEvent, const char *host);


/* 
 * Function: emgrShmInitEvent()
 *
 *     The emgrShmInitEvent() function is used on consumer side to
 *     initialize an Event from a shared memory allocated from an emgr.
 *     
 *
 * Parameters:
 *
 *    <shmId>      Shared Memory ID which is passed as a command
 *                 line parameter to a consumer process
 *
 *    <pError>     Pointer to integer error status.
 *
 * Return Value: 
 *
 *     The emgrShmInitEvent() if success - return pointer to initialized
 *     EmgrEvent_t. If failure it returns NULL and *pError should contain
 *     error code.
 */
EmgrEvent_t* emgrShmInitEvent(int shmId, int* pError);

EmgrEvent_t* emgrShmCliInitEvent(int argc, const char* argv[], int* pError);

   
   
/*====================================================================*/
/*=============      Consumer functions description      =============*/
/*====================================================================*/


/* 
 * Function: ConsumerEntry()
 *
 *     ConsumerEntry() is a typedef that maps to the entry point function
 *     in each consumer that is called from the EMGR server.
 *
 * Parameters:
 *
 *     <event>      Pointer to incomming EmgrEvent event struct.
 *
 *     <argc>       The number of arguments being passed, including the
 *                  name of the called function.
 *
 *     <argv>       Argument list.
 *
 * Return Value: 
 *
 *     The ConsumerEntry() function returns zero (0) on success and
 *     an error code on failure.
 */
typedef int ConsumerEntry_t(EmgrEvent_t *event, int argc, const char *argv[]);

   
/*=================================================*/
/*=============      Error codes      =============*/
/*=================================================*/

enum EmgrErrCodes {

	emgrNoErrors               = 0,
	emgrErrFrwdPathMissing,//     = 1,
	emgrErrConsumerMissing,//     = 2,
	emgrErrInvalidConsumerDef ,// = 3,
	emgrErrInvalidEvent   ,//     = 4,
	emgrErrInvalidFormat  ,//     = 5,
	emgrErrInvalidDso     ,//     = 6,
	emgrErrInvalidFuncName,//     = 7,
	emgrErrWrongValue     ,//     = 8,
	emgrSystemError       ,//     = 9,
	emgrNetworkError      ,//     = A-10,
        emgrMemAllocationFailure,//   = B-11,
	emgrDuplicateSubscription,//  = C-12,
	emgrNoSuchSubscription   ,//  = D-13,
	emgrAddressResolutionError,// = E-14,
	emgrEventTranslationError ,// = F-15,
	emgrOperationTimeOut      ,// = G-16,
	emgrNoSuchFile            ,// = H-17
	emgrNoAdmPemissions       ,// = I-18
	/*...*/
	emgrMaxError,
	/* insert here... */
	emgrOtherError             = 99
};

   /*
	emgrERR_No_memory_in_event_pool,
	emgrERR_Too_much_errors,
	emgrErr_File_Not_found,
	emgrErr_File_open_failed,
	emgrErr_read_err,
   */     
   
/* Network err codes */
 
#define EMGRERR_SOCKOPEN	1     /* socket open failed */
#define EMGRERR_HOSTNOTFOUND	2     /* gethostbyname failed */
#define EMGRERR_CONNREFUSED	3     /* No one listening on remote address */
#define EMGRERR_CONNTIMEOUT	4     /* Timeout while attempting connection */
#define EMGRERR_NETUNREACH	5     /* Network is unreachable. */
#define EMGRERR_CONNECTOTHER	6     /* Other connect error */
#define EMGRERR_SEND		7     /* send err */
#define EMGRERR_RESPONSE	9     /* Response err */

const char* emgrGetLocalHostname(void);
uint32_t emgrGetHostaddr(const char* host);
uint32_t emgrGetLocalHostaddr(void);
   

#ifdef __cplusplus
}
#endif

#endif
