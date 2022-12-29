/*
 *    Unpublished copyright (c) 1987-1997,1999-2002 Silicon Graphics, Inc.
 *    THIS IS UNPUBLISHED CONFIDENTIAL AND PROPRIETARY SOURCE CODE OF SGI.
 *
 *    The copyright notice above does not evidence any actual or intended
 *    publication or disclosure of this source code, which includes
 *    information that is confidential and/or proprietary, and is a
 *    trade secret, of Silicon Graphics, Inc. ANY REPRODUCTION,
 *    MODIFICATION, DISTRIBUTION, PUBLIC PERFORMANCE, OR PUBLIC DISPLAY OF
 *    OR THROUGH USE OF THIS SOURCE CODE WITHOUT THE EXPRESS WRITTEN
 *    CONSENT OF SILICON GRAPHICS, INC. IS STRICTLY PROHIBITED, AND IN
 *    VIOLATION OF APPLICABLE LAWS AND INTERNATIONAL TREATIES. THE RECEIPT
 *    OR POSSESSION OF THIS SOURCE CODE AND/OR RELATED INFORMATION DOES
 *    NOT CONVEY OR IMPLY ANY RIGHTS TO REPRODUCE, DISCLOSE OR DISTRIBUTE
 *    ITS CONTENTS, OR TO MANUFACTURE, USE, OR SELL ANYTHING THAT IT
 *    MAY DESCRIBE, IN WHOLE OR IN PART. 
 */

#ifndef _HBALIB_
#define _HBALIB_

/*
** sys/hba_api.h - common hba api
**
** HBA API VERSION 1.92
**
** From Methodologies for Interconnects Rev 1.92, December 4, 2001:
**
**	The Common HBA API provides a consistent low-level HBA standard
**	interface for accessing information in a Fibre Channel Storage
**	Area Network that would be implemented across vendors as a standard
**	'C' API supported by vendor specific library instances.
**
** Functions implemented in support of this interface
**
**	HBA_GetVersion()			- via library
**
**	HBA_GetNumberOfAdapters()		- via syssgi
**	HBA_GetAdapterName()			- via syssgi
**
**	HBA_OpenAdapter()			- via scsiha
**	HBA_CloseAdapter()			- via scsiha
**
**	HBA_GetAdapterAttributes()		- via scsiha / driver ioctl
**	HBA_GetAdapterPortAttributes()		- via scsiha / driver ioctl
**	HBA_GetPortStatistics()			- via scsiha / driver ioctl
**	HBA_GetDiscoveredPortAttributes()	- via scsiha / driver ioctl
**	HBA_RefreshInformation()		- via scsiha / driver ioctl
**	HBA_GetFcpTargetMapping()		- via scsiha / driver ioctl
**
**	int qlfc_get_controller_count(void);	- called by syssgi
**	char *qlfc_adapter_name(int)		- called by syssgi
**
*/

typedef uint8_t  HBA_UINT8;
typedef uint16_t HBA_UINT16;
typedef uint32_t HBA_UINT32;
typedef uint64_t HBA_UINT64;

typedef int64_t HBA_INT64;

typedef HBA_UINT32 HBA_HANDLE;
typedef HBA_UINT32 HBA_STATUS;
#define HBA_STATUS_OK 			0
#define HBA_STATUS_ERROR 		1 	/* Error */
#define HBA_STATUS_ERROR_NOT_SUPPORTED 	2 	/* Function not supported.*/
#define HBA_STATUS_ERROR_INVALID_HANDLE	3 	/* invalid handle */
#define HBA_STATUS_ERROR_ARG 		4 	/* Bad argument */ 
#define HBA_STATUS_ERROR_ILLEGAL_WWN 	5 	/* WWN not recognized */
#define HBA_STATUS_ERROR_ILLEGAL_INDEX 	6 	/* Index not recognized */ 
#define HBA_STATUS_ERROR_MORE_DATA 	7 	/* Larger buffer required */
#define HBA_STATUS_ERROR_STALE_DATA 	8 	/* Information has changed since the last call to HBA_RefreshInformation */
#define HBA_STATUS_SCSI_CHECK_CONDITION 9 	/* SCSI Check Condition reported*/
#define HBA_STATUS_ERROR_BUSY 		10 	/* Adapter busy or reserved, retry may be  effective*/
#define HBA_STATUS_ERROR_TRY_AGAIN 	11 	/* Request timed out, retry may be  effective */
#define HBA_STATUS_ERROR_UNAVAILABLE 	12 	/* Referenced HBA has been removed or  deactivated */

typedef HBA_UINT32 HBA_PORTTYPE;

#define HBA_PORTTYPE_UNKNOWN 		1 	/* Unknown */
#define HBA_PORTTYPE_OTHER 		2 	/* Other */ 
#define HBA_PORTTYPE_NOTPRESENT 	3 	/* Not present */
#define HBA_PORTTYPE_NPORT 		5 	/* Fabric */ 
#define HBA_PORTTYPE_NLPORT 		6 	/* Public Loop */
#define HBA_PORTTYPE_FLPORT 		7 
#define HBA_PORTTYPE_FPORT 		8 	/* Fabric Port */ 
#define HBA_PORTTYPE_EPORT 		9 	/* Fabric expansion port */
#define HBA_PORTTYPE_GPORT 		10 	/* Generic Fabric Port */

#define HBA_PORTTYPE_LPORT 		20 	/* Private Loop */
#define HBA_PORTTYPE_PTP 		21 	/* Point to Point */

typedef HBA_UINT32 HBA_PORTSTATE;

#define HBA_PORTSTATE_UNKNOWN 		1 	/* Unknown */ 
#define HBA_PORTSTATE_ONLINE 		2 	/* Operational */
#define HBA_PORTSTATE_OFFLINE 		3 	/* User Offline */
#define HBA_PORTSTATE_BYPASSED 		4 	/* Bypassed */ 
#define HBA_PORTSTATE_DIAGNOSTICS 	5 	/* In diagnostics mode */
#define HBA_PORTSTATE_LINKDOWN 		6 	/* Link Down */
#define HBA_PORTSTATE_ERROR 		7 	/* Port Error */
#define HBA_PORTSTATE_LOOPBACK 		8 	/* Loopback */

typedef HBA_UINT32 HBA_PORTSPEED;

#define HBA_PORTSPEED_UNKNOWN 		0 	/* Unknown - transceiver incapable of reporting*/
#define HBA_PORTSPEED_1GBIT 		1 	/* 1 GBit/sec */
#define HBA_PORTSPEED_2GBIT 		2 	/* 2 GBit/sec */
#define HBA_PORTSPEED_10GBIT 		4 	/* 10 GBit/sec */
#define HBA_PORTSPEED_4GBIT 		8 	/* 4 GBit / sec */
#define HBA_PORTSPEED_NOT_NEGOTIATED 	(1<<15)	/* Speed not established*/

typedef HBA_UINT32 HBA_COS;


typedef struct HBA_fc4types {
	HBA_UINT8 		bits[32]; 			/* 32 bytes of FC-4 per GS-2 */
} HBA_FC4TYPES, *PHBA_FC4TYPES;

typedef struct HBA_wwn {
	HBA_UINT8 wwn[8];
} HBA_WWN, *PHBA_WWN;

typedef struct HBA_AdapterAttributes {
	char 			Manufacturer[64]; 		/*Emulex */
	char 			SerialNumber[64]; 		/* A12345 */
	char 			Model[256]; 			/* QLA2200 */
	char 			ModelDescription[256]; 		/* Agilent TachLite */
	HBA_WWN 		NodeWWN;
	char 			NodeSymbolicName[256]; 		/* From GS-2 */
	char 			HardwareVersion[256]; 		/* Vendor use */
	char 			DriverVersion[256]; 		/* Vendor use */
	char 			OptionROMVersion[256]; 		/* Vendor use - i.e. hardware boot ROM*/
	char 			FirmwareVersion[256]; 		/* Vendor use */
	HBA_UINT32 		VendorSpecificID; 		/* Vendor specific */
	HBA_UINT32 		NumberOfPorts;
	char 			DriverName[256]; 		/* Binary path and/or name of driver file. */
} HBA_ADAPTERATTRIBUTES, *PHBA_ADAPTERATTRIBUTES;

typedef struct HBA_PortAttributes {
	HBA_WWN 		NodeWWN;
	HBA_WWN 		PortWWN;
	HBA_UINT32 		PortFcId;
	HBA_PORTTYPE 		PortType; 			/*PTP, Fabric, etc. */
	HBA_PORTSTATE 		PortState;
	HBA_COS 		PortSupportedClassofService;
	HBA_FC4TYPES		PortSupportedFc4Types;
	HBA_FC4TYPES		PortActiveFc4Types;
	char 			PortSymbolicName[256]; 
	char 			OSDeviceName[256]; 		/* \device\ScsiPort3 */
	HBA_PORTSPEED		PortSupportedSpeed;
	HBA_PORTSPEED		PortSpeed;
	HBA_UINT32 		PortMaxFrameSize;
	HBA_WWN 		FabricName;
	HBA_UINT32 		NumberofDiscoveredPorts;
} HBA_PORTATTRIBUTES, *PHBA_PORTATTRIBUTES;

typedef struct HBA_PortStatistics {
	HBA_INT64 		SecondsSinceLastReset;
	HBA_INT64 		TxFrames;
	HBA_INT64 		TxWords;
	HBA_INT64 		RxFrames;
	HBA_INT64 		RxWords;
	HBA_INT64 		LIPCount;
	HBA_INT64 		NOSCount;
	HBA_INT64 		ErrorFrames;
	HBA_INT64 		DumpedFrames;
	HBA_INT64 		LinkFailureCount;
	HBA_INT64 		LossOfSyncCount;
	HBA_INT64 		LossOfSignalCount;
	HBA_INT64 		PrimitiveSeqProtocolErrCount;
	HBA_INT64 		InvalidTxWordCount;
	HBA_INT64 		InvalidCRCCount;
} HBA_PORTSTATISTICS, *PHBA_PORTSTATISTICS;

typedef enum HBA_fcpbindingtype {
	TO_D_ID, 
	TO_WWN
} HBA_FCPBINDINGTYPE; 

typedef struct HBA_ScsiId { 
	char 			OSDeviceName[256]; 	/* \device\ScsiPort3 */ 
	HBA_UINT32 		ScsiBusNumber; 		/* Bus on the HBA */ 
	HBA_UINT32 		ScsiTargetNumber; 	/* SCSI Target ID to OS */ 
	HBA_UINT32 		ScsiOSLun;
} HBA_SCSIID, *PHBA_SCSIID; 

typedef struct HBA_FcpId { 
	HBA_UINT32 		FcId; 
	HBA_WWN 		NodeWWN; 
	HBA_WWN 		PortWWN;
	HBA_UINT64 		FcpLun;
} HBA_FCPID, *PHBA_FCPID;

typedef struct HBA_FcpScsiEntry { 
	HBA_SCSIID 		ScsiId; 
	HBA_FCPID 		FcpId; 
} HBA_FCPSCSIENTRY, *PHBA_FCPSCSIENTRY; 

typedef struct HBA_FCPTargetMapping { 
	HBA_UINT32 		NumberOfEntries; 
	HBA_FCPSCSIENTRY 	entry[1]; 		/* Variable length array containing mappings*/ 
} HBA_FCPTARGETMAPPING, *PHBA_FCPTARGETMAPPING; 

typedef struct HBA_FCPBindingEntry { 
	HBA_FCPBINDINGTYPE 	type; 
	HBA_SCSIID 		ScsiId; 
	HBA_FCPID 		FcpId; 
	HBA_UINT32 		FcId; 
} HBA_FCPBINDINGENTRY, *PHBA_FCPBINDINGENTRY; 

typedef struct HBA_FCPBinding { 
	HBA_UINT32 		NumberOfEntries; 
	HBA_FCPBINDINGENTRY 	entry[1]; 		/* Variable length array */
} HBA_FCPBINDING, *PHBA_FCPBINDING; 

typedef enum HBA_wwntype { 
	NODE_WWN, 
	PORT_WWN
} HBA_WWNTYPE; 

/* Although the HBA_MgmtInfo structure closely resembles */ 
/* the ACC to an RNID, it is different. */ 
/* It includes only 8 bytes for WWN */ 

typedef struct HBA_MgmtInfo { 
	HBA_WWN 		wwn; 
	HBA_UINT32 		unittype; 
	HBA_UINT32 		PortId; 
	HBA_UINT32 		NumberOfAttachedNodes; 
	HBA_UINT16 		IPVersion; 
	HBA_UINT16 		UDPPort; 
	HBA_UINT8 		IPAddress[16]; 
	HBA_UINT16 		reserved; 
	HBA_UINT16 		TopologyDiscoveryFlags; 
} HBA_MGMTINFO, *PHBA_MGMTINFO; 

#define HBA_EVENT_LIP_OCCURRED 		1 
#define HBA_EVENT_LINK_UP 		2 
#define HBA_EVENT_LINK_DOWN 		3 
#define HBA_EVENT_LIP_RESET_OCCURRED	4 
#define HBA_EVENT_RSCN			5 
#define HBA_EVENT_PROPRIETARY		0xFFFF 

typedef struct HBA_Link_EventInfo { 
	HBA_UINT32 		PortFcId; 			/* Nx_Port which this event occurred */ 
	HBA_UINT32 		Reserved[3];
} HBA_LINK_EVENTINFO, *PHBA_LINK_EVENTINFO; 

typedef struct HBA_RSCN_EventInfo { 
	HBA_UINT32 		PortFcId; 			/* Nx_Port which this event occurred */
	HBA_UINT32 		NPortPage; 			/* Reference FC-FS for RSCN ELS  Affected Port_ID 
Pages */ 
	HBA_UINT32 		Reserved[2]; 
} HBA_RSCN_EVENTINFO, *PHBA_RSCN_EVENTINFO; 

typedef struct HBA_Pty_EventInfo { 
	HBA_UINT32 		PtyData[4]; 			/* Proprietary data */ 
} HBA_PTY_EVENTINFO, *PHBA_PTY_EVENTINFO;

typedef struct HBA_EventInfo { 
	HBA_UINT32 		EventCode; 
	union { 
		HBA_LINK_EVENTINFO	Link_EventInfo; 
		HBA_RSCN_EVENTINFO	RSCN_EventInfo; 
		HBA_PTY_EVENTINFO	Pty_EventInfo; 
	} Event; 
} HBA_EVENTINFO, *PHBA_EVENTINFO; 

typedef HBA_UINT32 (* HBAGetVersionFunc)(); 
typedef HBA_STATUS (* HBALoadLibraryFunc)(); 
typedef HBA_STATUS (* HBAFreeLibraryFunc)(); 
typedef HBA_UINT32 (* HBAGetNumberOfAdaptersFunc)(); 
typedef HBA_STATUS (* HBAGetAdapterNameFunc)(HBA_UINT32, char*); 
typedef HBA_HANDLE (* HBAOpenAdapterFunc)(char*); 
typedef void (* HBACloseAdapterFunc)(HBA_HANDLE); 
typedef HBA_STATUS (* HBAGetAdapterAttributesFunc)(HBA_HANDLE, PHBA_ADAPTERATTRIBUTES); 
typedef HBA_STATUS (* HBAGetAdapterPortAttributesFunc)(HBA_HANDLE, HBA_UINT32, PHBA_PORTATTRIBUTES); 
typedef HBA_STATUS (* HBAGetPortStatisticsFunc)(HBA_HANDLE, HBA_UINT32, PHBA_PORTSTATISTICS); 
typedef HBA_STATUS (* HBAGetDiscoveredPortAttributesFunc)(HBA_HANDLE, HBA_UINT32, HBA_UINT32, PHBA_PORTATTRIBUTES); 
typedef HBA_STATUS (* HBAGetPortAttributesByWWNFunc)(HBA_HANDLE, HBA_WWN, PHBA_PORTATTRIBUTES); 
typedef HBA_STATUS (* HBASendCTPassThruFunc)(HBA_HANDLE, void *, HBA_UINT32, void *, HBA_UINT32); 
typedef void (* HBARefreshInformationFunc)(HBA_HANDLE); 
typedef void (* HBAResetStatisticsFunc)(HBA_HANDLE, HBA_UINT32); 
typedef HBA_STATUS (* HBAGetFcpTargetMappingFunc) (HBA_HANDLE, PHBA_FCPTARGETMAPPING); 
typedef HBA_STATUS (* HBAGetFcpPersistentBindingFunc) (HBA_HANDLE, PHBA_FCPBINDING); 
typedef HBA_STATUS (* HBAGetEventBufferFunc)(HBA_HANDLE, PHBA_EVENTINFO, HBA_UINT32 *); 
typedef HBA_STATUS (* HBASetRNIDMgmtInfoFunc) (HBA_HANDLE, PHBA_MGMTINFO); 
typedef HBA_STATUS (* HBAGetRNIDMgmtInfoFunc)(HBA_HANDLE, PHBA_MGMTINFO); 
typedef HBA_STATUS (* HBASendRNIDFunc) (HBA_HANDLE, HBA_WWN, HBA_WWNTYPE, void *, HBA_UINT32 *); 
typedef HBA_STATUS (* HBASendScsiInquiryFunc) (HBA_HANDLE, HBA_WWN, HBA_UINT64, HBA_UINT8, HBA_UINT32, void *, HBA_UINT32, void *,HBA_UINT32); 
typedef HBA_STATUS (* HBASendReportLUNsFunc) (HBA_HANDLE, HBA_WWN, void *, HBA_UINT32,void *,HBA_UINT32); 
typedef HBA_STATUS (* HBASendReadCapacityFunc) (HBA_HANDLE, HBA_WWN,HBA_UINT64, 
void *, HBA_UINT32, void *, HBA_UINT32); 

typedef struct HBA_EntryPoints { 
	HBAGetVersionFunc 			GetVersionHandler; 
	HBALoadLibraryFunc 			LoadLibraryHandler; 
	HBAFreeLibraryFunc 			FreeLibraryHandler; 
	HBAGetNumberOfAdaptersFunc 		GetNumberOfAdaptersHandler; 
	HBAGetAdapterNameFunc 			GetAdapterNameHandler; 
	HBAOpenAdapterFunc 			OpenAdapterHandler; 
	HBACloseAdapterFunc 			CloseAdapterHandler; 
	HBAGetAdapterAttributesFunc 		GetAdapterAttributesHandler; 
	HBAGetAdapterPortAttributesFunc 	GetAdapterPortAttributesHandler; 
	HBAGetPortStatisticsFunc 		GetPortStatisticsHandler; 
	HBAGetDiscoveredPortAttributesFunc 	GetDiscoveredPortAttributesHandler; 
	HBAGetPortAttributesByWWNFunc 		GetPortAttributesByWWNHandler; 
	HBASendCTPassThruFunc 			SendCTPassThruHandler; 
	HBARefreshInformationFunc 		RefreshInformationHandler; 
	HBAResetStatisticsFunc 			ResetStatisticsHandler; 
	HBAGetFcpTargetMappingFunc 		GetFcpTargetMappingHandler; 
	HBAGetFcpPersistentBindingFunc 		GetFcpPersistentBindingHandler; 
	HBAGetEventBufferFunc 			GetEventBufferHandler; 
	HBASetRNIDMgmtInfoFunc 			SetRNIDMgmtInfoHandler; 
	HBAGetRNIDMgmtInfoFunc 			GetRNIDMgmtInfoHandler; 
	HBASendRNIDFunc 			SendRNIDHandler; 
	HBASendScsiInquiryFunc 			ScsiInquiryHandler; 
	HBASendReportLUNsFunc 			ReportLUNsHandler; 
	HBASendReadCapacityFunc 		ReadCapacityHandler; 
} HBA_ENTRYPOINTS, *PHBA_ENTRYPOINTS;

HBA_UINT32	HBA_GetVersion(void);
HBA_UINT32	HBA_GetNumberOfAdapters(void);
HBA_HANDLE	HBA_OpenAdapter(char *);
void		HBA_CloseAdapter(HBA_HANDLE);
void		HBA_RefreshInformation(HBA_HANDLE);
HBA_STATUS	HBA_GetAdapterName(HBA_UINT32, char *);
HBA_STATUS	HBA_GetAdapterAttributes(HBA_HANDLE, HBA_ADAPTERATTRIBUTES *);
HBA_STATUS	HBA_GetAdapterPortAttributes(HBA_HANDLE, HBA_UINT32, HBA_PORTATTRIBUTES *);
HBA_STATUS	HBA_GetPortStatistics(HBA_HANDLE, HBA_UINT32, HBA_PORTSTATISTICS *);
HBA_STATUS	HBA_GetDiscoveredPortAttributes(HBA_HANDLE, HBA_UINT32, HBA_UINT32, HBA_PORTATTRIBUTES *);
HBA_STATUS	HBA_GetFcpTargetMapping(HBA_HANDLE, HBA_FCPTARGETMAPPING *);


#endif
