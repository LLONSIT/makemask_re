#ifndef emgrSubscrApi_h_
#define emgrSubscrApi_h_

#include "EmgrEvent.h"


/*
 * Function: emgrNewSubscribe()
 *
 *     The emgrNewSubscribe() is a wrapper to the emgrAllocEvent()
 *     function that allocates an EmgrEvent structure and initializes 
 *     the event eader for subscription using the data provided.
 *
 * Parameters:
 *
 *     <appname>    Pointer to character string containing the name of
 *                  the application that "owns" the event (has domain over
 *                  the event Class and Type). This string can be NULL
 *                  which means events from any application
 *
 *     <evClass>    Event Class to subscribe for, or -1 for all classes.
 *
 *     <evType>     Event Type to subscribe for, or -1 for all types.
 *
 *     <source>     Pointer to character string containing the name of
 *                  the host or hosts to subscribe matching events from.
 *                  If the <source> string contains multiple host names, 
 *                  they must be separated by spaces and/or commas. If 
 *                  <source> is an empty string or a NULL char pointer, 
 *                  then events will be subscribed from the localhost.
 *
 *     <origin>     Pointer to character string containing the name of
 *                  the application that will be used to log an event. 
 *                  Note that, if the application sending the events is 
 *                  the same one that owns the events, then make <origin> 
 *                  and <appname> the same (or pass an empty string or 
 *                  NULL char pointer in the <origin> parameter).
 *
 *
 * Return Value:
 *
 *     The emgrNewSubscribe() function returns a pointer to a EmgrEvent
 *     struct on success and a NULL pointer on failure.
 */
EmgrEvent_t* emgrNewSubscribe(const char* appname, int evClass, int evType, 
			      const char* source,
			      const char* origin
			      );


/*
 * Function: emgrAddSubscribe()
 *
 *     The emgrAddSubscribe() adds next subscribsion specification
 *     to already allocated with emgrNewSubscribe() function
 *     subscribtion event and sets specific information for batch event
 *     processing.
 *
 * Parameters:
 *
 *     <appname>    Pointer to character string containing the name of
 *                  the application that "owns" the event (has domain over
 *                  the event Class and Type). This string can be NULL
 *                  which means events from any application
 *
 *     <evClass>    Event Class to subscribe for, or -1 for all classes.
 *
 *     <evType>     Event Type to subscribe for, or -1 for all types.
 *
 *     <source>     Pointer to character string containing the name of
 *                  the host or hosts to subscribe matching events from.
 *                  If the <source> string contains multiple host names, 
 *                  they must be separated by spaces and/or commas. If 
 *                  <source> is an empty string or a NULL char pointer, 
 *                  then events will be subscribed from the localhost.
 *
 *     <origin>     Pointer to character string containing the name of
 *                  the application that will be used to log an event. 
 *                  Note that, if the application sending the events is 
 *                  the same one that owns the events, then make <origin> 
 *                  and <appname> the same (or pass an empty string or 
 *                  NULL char pointer in the <origin> parameter).
 *
 *
 * Return Value:
 *
 *     The emgrAddSubscribe() function returns a pointer to a EmgrEvent
 *     struct on success and a NULL pointer on failure.
 */
EmgrEvent_t* emgrAddSubscribe(EmgrEvent_t* pEvent,
			      const char* appname, int evClass, int evType, 
			      const char* source,
			      const char* origin
			      );

/* This one simply adds subscription attributes to an event */
EmgrEvent_t* emgrSpecSubscribe(EmgrEvent_t* pEvent,
			       const char* appname, int evClass, int evType, 
			       const char* source,
			       const char* origin
			       );

/* emgrRunSubscribe() and emgrRunUnsubscribe() can be used instead of
 * emgrSendEvent() in case if operation completion status is needed.
 *
 * <timeout> - is a value in second to wait for return from emgr 
 */
int
emgrRunSubscribe(EmgrEvent_t* pSubscrEvent,
		 const char* host, int timeout, char** pRetEventMask );

int
emgrRunUnSubscribe(EmgrEvent_t* pSubscrEvent,
		   const char* host, int timeout, char** pRetEventMask);


/*
 * Function: emgrSubscribeSpecPriority()
 *
 *     The emgrSubscribeSpecPriority() is a wrapper to the
 *     emgrAddItemToEvent() function that adds tagged item to a
 *     subscription or unsubscription event to specify optional event
 *     priority filter for subscription matching. 
 *
 *
 * Parameters:
 *
 *      <pri>   priority same as it is used in syslog
 *
 * Return Value:
 *     0 - OK
 *    -1 - memory allocation failure
 */
int emgrSubscribeSpecPriority(EmgrEvent_t* pEvent, int pri);

/*
 * Function: emgrSubscribeSpecFacility()
 *
 *     The emgrSubscribeSpecFacility() is a wrapper to the
 *     emgrAddItemToEvent() function that adds tagged item to a
 *     subscription or unsubscription event to specify optional event
 *     facility filter for subscription matching. 
 *
 *
 * Parameters:
 *
 *      <facility>   facility id same as it is used in syslog
 *
 * Return Value:
 *     0 - OK
 *    -1 - memory allocation failure
 */
int emgrSubscribeSpecFacility(EmgrEvent_t* pEvent, int facility);

/*
 * Function: emgrNewUnSubscribe()
 *
 *     The emgrNewUnSubscribe() is a wrapper to the emgrAllocEvent() function
 *     that allocates an EmgrEvent structure and initializes the event header
 *     for unsubscription using the data provided.
 *
 * Parameters:
 *
 *     <appname>    Pointer to character string containing the name of the
 *                  application that "owns" the event (has domain over the
 *                  event Class and Type). Note that, when unsubscribing
 *                  events, <appname> cannot be an empty string or a NULL char
 *                  pointer.
 *
 *     <type>       Event Type to unsubscribe, or -1 for all types.
 *
 *     <evClass>    Event Class to unsubscribe, or -1 for all classes.
 *
 *     <source>     Pointer to character string containing the name of the
 *                  host or hosts to unsubscribe matching events from. If
 *                  the <source> string contains multiple host names,
 *                  they must be seperated by spaces and/or commas. If
 *                  <source> is an empty string or a NULL char pointer,
 *                  then matching events will be unsubscribed for all hosts.
 *
 *     <origin>     Pointer to character string containing the name of the
 *                  application generating the event (if it is something other
 *                  than Appname).
 *
 *
 * Return Value:
 *
 *     The emgrNewUnSubscribe() function returns a pointer to a EmgrEvent
 *     struct on success and a NULL pointer on failure.
 */
EmgrEvent_t *emgrNewUnSubscribe(const char *appname, int evClass, int evType, 
				const char *source, const char *origin);

EmgrEvent_t *emgrAddUnSubscribe(EmgrEvent_t * pEvent,
				const char *appname, int evClass, int evType, 
				const char *source, const char *origin);

/*
 * Function: emgrNewQuery()
 *
 *     The emgrNewQuery() is a wrapper to the emgrAllocEvent() function
 *     that allocates an EmgrEvent structure and initializes the event header
 *     for conducting a query of events currently subscribed for.
 *
 * Parameters:
 *
 *     <appname>    Pointer to character string containing the name of the
 *                  application that "owns" the event (has domain over the
 *                  event Class and Type). 
 *
 *     <evClass>    Event Class to match in query, or -1 for all classes.
 *
 *     <evType>     Event Type to match in query, or -1 for all types.
 *
 *     <source>     Pointer to character string containing the name of the
 *                  host or hosts to matching events from in query. If
 *                  <source> contains multiple host names, they must be 
 *                  seperated by spaces and/or commas. If <source> is an 
 *                  empty string or a NULL char pointer, then only events 
 *                  logged from the local system will match in the query.
 *
 *     <origin>     Pointer to character string containing the name of the
 *                  application generating the event (if it is something other
 *                  than Appname).
 *
 * Return Value:
 *
 *     The emgrNewQuery() function returns a pointer to a EmgrEvent
 *     struct on success and a NULL pointer on failure.
 */
EmgrEvent_t *emgrNewQuery(const char *appname, int evClass, int evType, 
			  const char *source, const char *origin);


/*
 * Function: emgrNewQuery()
 *
 *     The emgrRunQuery() is a routine to execute subscription query
 *     
 *
 * Parameters:
 *     <pQueryEvent> created by emgrNewQuery() query event
 *     <host>        emgr host and, optionally, port number
 *     <ppRetEvents> array of pointers to events which comply with a query
 *     <pEvCount>    amount of returned events
 *
 *                   returned events and array of pointers will have to be
 *                   freed from a calling program 
 * Return Value:
 * returns 0 on success and ppRetEvents and pEvCount set to values. Otherwise
 * returns -1    
 */
int emgrRunQuery(EmgrEvent_t* pQueryEvent, const char* host,
		 EmgrEvent_t*** ppRetEvents, int* pEvCount,
		 int timeout );

/*
 * Function: emgrSubscribeSpecRegexpMap()
 *
 *     The emgrSubscribeSpecRegexpMap() is a wrapper to the
 *     emgrAddItemToEvent() function that adds tagged item to a
 *     subscription event to specify optional untagged event's class
 *     and type mapping before forwarding it to a subscribed consumer. 
 *
 *
 * Parameters:
 *
 *      <regExp>   Regular expression to match agains an event's message body
 *      <evMapClass> class id which needs to be put in to an event
 *      <evMapType>  class id which needs to be put in to an event
 *
 * Return Value:
 *     0 - OK
 *    -1 - memory allocation failure
 */
int emgrSubscribeSpecRegexpMap(EmgrEvent_t* pEvent, const char* regExp,
			       int evMapClass, int evMapType 
			       );


/*
 * Function: emgrSubscribeSpecTimeFreq()
 *
 *     The emgrSubscribeSpecTimeFreq() is a wrapper to the
 *     emgrAddItemToEvent() function that adds tagged item to a
 *     subscription event to specify how often (ev/sec) a matching event
 *     has to be sent to a matching subscriber. 
 *
 *
 * Parameters:
 *
 *     <freq>  
 * Return Value:
 *     0 - OK
 *    -1 - memory allocation failure
 */
int emgrSubscribeSpecTimeFreq(EmgrEvent_t* pEvent, int freq);

/*
 * Function: emgrSubscribeSpecCntFreq()
 *
 *     The emgrSubscribeSpecCntFreq() is a wrapper to the
 *     emgrAddItemToEvent() function that adds tagged item to a
 *     subscription event to specify how often (1/n) a matching event
 *     has to be sent to a matching subscriber. 
 *
 *
 * Parameters:
 *
 *     <freq>  
 * Return Value:
 *     0 - OK
 *    -1 - memory allocation failure
 */
int emgrSubscribeSpecCntFreq(EmgrEvent_t* pEvent, int freq);


/*
 * Set of routines to specify a subscription consumer 
 */

/* 
 * Function: emgrSubscribeSpecDsoConsumer()
 *
 *     The emgrSubscribeSpecDsoConsumer() is used when subscribing for
 *     events where the consumer is implemented in the form of a DSO library
 *     containing a specific set of functions that are called from the
 *     Event Manager Server.
 *
 * Parameters:
 *
 *     <pEvent>     Pointer to EmgrEvent struct
 *
 *     <dsoPath>    Pointer to character string containing the pathname
 *                  for the consumer DSO library.
 *
 *     <callName>   Pointer to character string containing the name of the
 *                  main consumer function to call.
 *
 *     <prmSpec>    ???
 *
 * Return Value:
 *
 *     The emgrSubscribeSpecDsoConsumer() function returns zero (0) on success
 *     and -1 on failure.
 */
int emgrSubscribeSpecDsoConsumer(EmgrEvent_t *pEvent,
				 const char *dsoPath, 
				 const char *callName,
				 const char *prmSpec);

/* 
 * Function: emgrSubscribeSpecExecConsumer()
 *
 *     The emgrSubscribeSpecExecConsumer() is used when subscribing for
 *     events where the consumer is an application that is launched via
 *     fork()/exec(). Event parameters are passed to the consumer on the
 *     command line.
 *
 * Parameters:
 *
 *     <pEvent>     Pointer to EmgrEvent struct
 *
 *     <execPath>   Pointer to character string containing the pathname
 *                  for the consumer application to launch.
 *
 *     <prmSpec>    parameters string to executable
 *
 * Return Value:
 *
 *     The emgrSubscribeSpecExecConsumer() function returns zero (0) on success
 *     and -1 on failure.
 */
int emgrSubscribeSpecExecConsumer(EmgrEvent_t *pEvent, 
				  const char *execPath, const char *prmSpec);

/* 
 * Function: emgrSubscribeSpecExecShMemConsumer()
 *
 *     The emgrSubscribeSpecExecShMemConsumer() is used when subscribing for
 *     events where the consumer is an application that is launched via
 *     fork() and exec(). Event parameters are passed to the consumer via a
 *     shared memory handoff handled by the API layer.
 *
 * Parameters:
 *
 *     <pEvent>     Pointer to EmgrEvent struct
 *
 *     <execPath>   Pointer to character string containing the pathname
 *                  for the consumer application to launch.
 *
 *     <prmSpec>    parameters string to executable
 *
 * Return Value:
 *
 *     The emgrSubscribeSpecExecShMemConsumer() function returns zero (0)
 *     on success and -1 on failure.
 */
int emgrSubscribeSpecExecShMemConsumer(EmgrEvent_t *pEvent,
				       const char *execPath,
				       const char *prmSpec);


int emgrSubscribeSpecForwardConsumer(EmgrEvent_t *pEvent,
				     const char *forwardPath);

int emgrSpecForwardConsumerAuthProc(EmgrEvent_t *pEvent,
				    const char *dsoPath, 
				    const char *callName,
				    const char *callPrms);


typedef int ForwardAuthFunc_t(EmgrEvent_t *event,  const char *prms);

int emgrSubscribeSpecMap(EmgrEvent_t* pEvent, int mClass, int mType );

#endif /* emgrSubscrApi_h_ */
