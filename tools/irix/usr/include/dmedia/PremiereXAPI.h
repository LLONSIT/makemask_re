/*
    Premiere -- UNIX Plugin Interface
	API Version 1.0
    
    Copyright (c) 1995, 1996, 1997 Adobe Systems Incorporated
    All Rights Reserved.
*/

#ifndef _PREMIEREXAPI_H
#define _PREMIEREXAPI_H 1

#ifdef __cplusplus
extern "C" {
#endif

/*
================
	INCLUDES
================
*/

#ifdef UX_IS_PREM
#define Cursor XCursor	// avoid XWindows's conflict with QuickDraw's definition
#define Region XRegion
#define EventMask XEventMask
#define Screen XScreen /* X already has an XScreen */
#else
#include <X11/Intrinsic.h>
#endif
#include <sys/dmcommon.h>	/* for stamp_t */
#include <GL/gl.h>
#include <GL/glx.h>
#ifdef UX_IS_PREM
#undef Screen
#endif
/*
================
	CONSTANTS
================
*/

/*--- QUAD ASCII Constants ---*/

/* These 32-bit constants are used to identify types of information,
   and to tag property values.  They can be conveniently defined
   as 4 ASCII characters packed into a 32-bit word in big-endian
   order.  Some compilers support the "long character constant"
   construct, such as:
   		long int foo = 'AFlt';  // same as kAFlt
   which you can use, assuming the native order is big-endian.  Otherwise
   you can use these constants, which are defined as a shorthand.
   They always start with the letter 'k', followed by the 4 ASCII
   characters.  Leading or trailing spaces are indicated with the 
   underbar (_) character. */ 

#define kAFlt			0x41466C74
#define kDISS			0x44495353
#define kDevC			0x44657643
#define kDraw			0x44726177
#define kExpD			0x45787044
#define kExpM			0x4578704D
#define kPRXa			0x50525861
#define kPRXi			0x50525869
#define kPRXm			0x5052586D
#define kPRXs			0x50525873
#define kSPFX			0x53504658
#define kTAKE			0x54414B45
#define kVFlt			0x56466C74
#define kWI00			0x57493030
#define kWI01			0x57493031
#define kWI02			0x57493032
#define kWI03			0x57493033
#define kWI04			0x57493034
#define kWI05			0x57493035
#define kWI06			0x57493036
#define kWI07			0x57493037
#define kWI08			0x57493038
#define kWI09			0x57493039
#define kWI10			0x57493130
#define kWI11			0x57493131
#define kWI12			0x57493132
#define kWI13			0x57493133
#define kWI14			0x57493134
#define kWI15			0x57493135
#define kWI16			0x57493136

#ifndef UX_IS_PREM

/**************** CONSTANTS COMMON TO ALL PLATFORMS ****************/

/*=== BIT MASKS ==================================*/

/*--- Audio Data Export Bit Masks ---*/
enum {
	aflag8KHz			= 0x0001,
	aflag11KHz			= 0x0002,
	aflag22KHz			= 0x0004,
	aflag44KHz			= 0x0008,
	aflag48KHz			= 0x0010,
	aflagSpecial		= 0x0040,
	aflagStereo			= 0x0100,
	aflag16Bit			= 0x0200,
	aflagDropFrame		= 0x0400,
	aflagTwosComp		= 0x1000
};

/*--- Audio Flag Bit Masks ---*/
enum {
	gaStereo			= 0x0100,
	ga16Bit				= 0x0200,
	gaTwosComp			= 0x1000
};

/*--- Device Control Feature Bits ---*/
enum {
	fCanInsertEdit      = 0x10000000,   /* Unix: supports InsertEdit command */
	fDrvrQuiet          = 0x00040000,   /* From 4.2: support Quiet command */
	fHasJogMode         = 0x00020000,   /* From 4.2: can jog with mode */
	fCanEject           = 0x00010000,	/* From 4.2: can eject media */
	fStepFwd			= 0x00008000,	/* can step forward */
	fStepBack			= 0x00004000,	/* can step back */
	fRecord				= 0x00002000,	/* can record */
	fPositionInfo		= 0x00001000,	/* returns position info */
	fGoto				= 0x00000800,	/* can seek to a specific frame
									   	   (fPositionInfo must also be set) */
	f1_5				= 0x00000400,	/* can play at 1/5 speed */
	f1_10				= 0x00000200,	/* can play at 1/10 speed */
	fBasic				= 0x00000100,	/* supports
										   Stop,Play,Pause,FastFwd,Rewind */
	fHasOptions			= 0x00000080,	/* plugin puts up an options dialog */
	fReversePlay		= 0x00000040,	/* supports reverse play */
	fCanLocate			= 0x00000020,	/* can locate a specific time code */
	fStillFrame			= 0x00000010,	/* device is frame addressable,
										   like a laser disc */
	fCanShuttle			= 0x00000008,	/* supports the Shuttle command */
	fCanJog				= 0x00000004	/* supports the JogTo command */
};


/*--- Transition Corner Bit Masks ---*/
enum {
	bitTop				= 0x01,
	bitRight			= 0x02,
	bitBottom			= 0x04,
	bitLeft				= 0x08,
	bitUpperRight		= 0x10,
	bitLowerRight		= 0x20,
	bitLowerLeft		= 0x40,
	bitUpperLeft		= 0x80
};

/*--- Transition Option Bit Masks ---*/
enum {
	optInPairs			= 0x01,	/* options operate in pairs */
	optHasCustom		= 0x02,	/* has custom dialog */
	optNoTimeVariance	= 0x04,	/* does not vary over time */
	optNoFirstSetup		= 0x08,	/* does not get setup call 1st time */
	optDirectCompData	= 0x10,	/* can handle compressed data */
	optSetupUsesSource	= 0x20,	/* Set if setup wants access to source */
	optExclusiveDialog	= 0x40	/* Set if never wants Transition dialog */
};

/*--- Video Flag Bit Masks ---*/
enum {
	gvFieldsOdd			= 0x0200,
	gvFieldsEven		= 0x0100
};

/*=== SELECTORS ==================================*/

/*--- Data Conversion Selectors ---*/
enum {
	Draw_GetInfo		= 0,
	Draw_GetVideo		= 1,
	Draw_GetAudio		= 2,
	Draw_Open			= 3,
	Draw_Close			= 4,
	Draw_Quiet			= 5,
	
	Draw_CheckType		= 1000
};

/*--- Data Export Selectors ---*/
enum {
	edCleanup			= -1,
	edExecute			= 0
};

/*--- Device Control Selectors ---*/
enum {
	dsInit				= 0,	/* init data, mode, user settings? */
	dsSetup				= 1,	/* get user settings */
	dsExecute			= 2,	/* perform command */
	dsCleanup			= 3,	/* disconnect, dispose data */
	dsRestart			= 4,	/* dsInit, but use exiting data */
	dsQuiet				= 5		/* From 4.2: disconnect, maintain data */
};

/*--- EDL Export Selectors ---*/
enum {
	exCleanup			= -1,
	exExecute			= 0,
	exTrue30fps			= 1
};

/*--- Filter Selectors ---*/
enum {
	fsCleanup			= -1,
	fsExecute			= 0,
	fsSetup				= 1,
	fsDisposeData		= 2		/* From 4.2: ignore this selector */
};

/*--- Transition Selectors ---*/
enum {
	esCleanup			= -1,
	esExecute			= 0,
	esSetup				= 1
};

/*=== OTHER CONSTANTS ============================*/

/*--- Device Control Commands ---*/
enum {
	cmdGetFeatures		= 0,	/* return feature bits */
	cmdStatus			= 1,	/* fill in current mode and time code,
								   gets called repeatedly */
	cmdNewMode			= 2,	/* change to the mode in 'mode' */
	cmdGoto				= 3,	/* goto to 'timeCode' */
	cmdLocate			= 4,	/* find 'timeCode' and then return
								   (with deck in play mode) */
	cmdShuttle			= 5,	/* shuttle at rate specified in 'mode',
								   from -100 to +100 */
	cmdJogTo			= 6,	/* position at 'timeCode' quickly,
								   from the current location */
	cmdJog				= 7,	/* From 4.2: jog at rate specified in
								   'mode', from -25 to +25 */
	cmdEject			= 8,	/* From 4.2: eject media */
	cmdInsertEdit		= 9		/* Unix-only: perform "insert-edit" record */
};

/*--- Device Control Modes ---*/
enum {
	modeStop			= 0,
	modePlay			= 1,
	modePlay1_5			= 2,
	modePlay1_10		= 3,
	modePause			= 4,
	modeFastFwd			= 5,
	modeRewind			= 6,
	modeRecord			= 7,
	modeGoto			= 8,
	modeStepFwd			= 9,
	modeStepBack		= 10,
	modePlayRev			= 11,
	modePlayRev1_5		= 12,
	modePlayRev1_10		= 13
};

/*--- EDL Export Block Codes ---*/
enum {
	 bBLOK = 0x424C4F4B,	/* See documentation for details */

	 bTRKB = 0x54524B42,
	 bTRAK = 0x5452414B,
	 bFVID = 0x46564944,
	 bFSUP = 0x46535550,
	 bFAUD = 0x46415544,
	 bAMAP = 0x414D4150,
	 bFF_X = 0x46465F58,
	 bTREC = 0x54524543,
	 bRBND = 0x52424E44,
	 bRPNT = 0x52504E54,
	 bFXOP = 0x46584F50,
	 bFXDF = 0x46584446,
	 bEDGE = 0x45444745,
	 bMPNT = 0x4D504E54,
	 bSPNT = 0x53504E54,
	 bEPNT = 0x45504E54,
	 bOVER = 0x4F564552,
	 bCOLR = 0x434F4C52,
	 bSIMI = 0x53494D49,
	 bBLND = 0x424C4E44,
	 bTHRS = 0x54485253,
	 bCUTO = 0x4355544F,
	 bALIA = 0x414C4941,
	 bSHAD = 0x53484144,
	 bRVRS = 0x52565253,
	 bGARB = 0x47415242,
	 bPONT = 0x504F4E54,
	 bMATI = 0x4D415449,
	 bVFLT = 0x56464C54,
	 bAFLT = 0x41464C54,
	 bFILT = 0x46494C54,
	 bMOTN = 0x4D4F544E,
	 bSMTH = 0x534D5448,
	 bMREC = 0x4D524543,
	 bDATA = 0x44415441,

	 bCLPB = 0x434C5042,
	 bCLIP = 0x434C4950,
	 bMARK = 0x4D41524B,
	 bLOCK = 0x4C4F434B,
	 bRATE = 0x52415445,

	 bFILB = 0x46494C42,
	 bFILE = 0x46494C45,
	 bMACS = 0x4D414353,
	 bMACP = 0x4D414350,
	 bFRMS = 0x46524D53,
	 bVIDI = 0x56494449,
	 bAUDI = 0x41554449,
	 bTIMC = 0x54494D43,
	 bTIMB = 0x54494D42,
	 bREEL = 0x5245454C
};

/*--- Return Codes For Plugin Calls ---*/
enum {
	dcNoErr				= 0,
	dcTooBig			= 1,
	dcUnsupported		= 2,
	dcBadFile			= 3,
	dcMemErr			= 4,
	dcOtherErr			= 5,
	dcNoContent			= 6,
	dcBadRate			= 7,
	dcBadCompression	= 8,
	dcBadCodec			= 9,	/* From 4.2 */
	
	dcTwosComp 			= -1
};

/*--- Transition Wipe Codes ---*/
enum {
	fDISS = kDISS,			/* cross dissolve */
	fTAKE = kTAKE,			/* 'take' or cut */
	fWI00 = kWI00,			/* vertical wipe from the left edge */
	fWI01 = kWI01,			/* horizontal wipe from the top edge */
	fWI02 = kWI02,			/* vertical wipe from the right edge */
	fWI03 = kWI03,			/* horizontal wipe from the bottom edge */
	fWI04 = kWI04,			/* diagonal wipe from upper left corner */
	fWI05 = kWI05,			/* diagonal wipe from upper right corner */
	fWI06 = kWI06,			/* diagonal wipe from lower right corner */
	fWI07 = kWI07,			/* diagonal wipe from lower left corner */
	fWI08 = kWI08,			/* vertical split wipe */
	fWI09 = kWI09,			/* horizontal split wipe */
	fWI10 = kWI10,			/* horizontal/vertical split wipe */
	fWI11 = kWI11,			/* box wipe out from the center */
	fWI12 = kWI12,			/* circular wipe from the center */
	fWI13 = kWI13,			/* inset wipe from upper left */
	fWI14 = kWI14,			/* inset wipe from upper right */
	fWI15 = kWI15,			/* inset wipe from lower right */
	fWI16 = kWI16			/* inset wipe from lower left */
};

#endif /* UX_IS_PREM */

/**************** CONSTANTS FOR UNIX PLATFORMS ONLY ****************/

/*=== BIT MASKS ==================================*/

/*--- Contents Flag Bit Masks ---*/
enum {					/* see contains field of PRX_DataConverterRec */
	hasVideo			= 0x0001,
	hasAudio			= 0x0002,
	hasReserved1		= 0x0004,
	hasReserved2		= 0x0008
};

/*--- Data Export Flag Bit Masks ---*/
enum {
	bitCanDoVideo		= 0x8000,
	bitCanDoAudio		= 0x4000
};

/*--- Operational Flag Bit Masks ---*/
enum {
	flagInSequence      = 0x0001,
	flagStartSequence   = 0x0002
};


/*--- Buffer Usage Bit Masks ---*/

enum { /* Buffer Input Usage */
	bufInputDirect      = 0x0001,  /* reads from void *data */
	bufInputTexture     = 0x0002,  /* uses OpenGL texturing */
	bufInputDrawPixels  = 0x0004,  /* uses OpenGL pixel drawing */
	bufInputMovie       = 0x0008,  /* used only by application */
	bufInputAll			= 0xFFFF   /* may use any kind of input */
};

enum { /* Buffer Output Usage */
	bufOutputDirect     = 0x0001,  /* writes to void *data */
	bufOutputOpenGL     = 0x0002,  /* renders with OpenGL */
	bufOutputMovie      = 0x0004,  /* used only by application */
	bufOutputOpenGLDepth= 0x0008	/* OpenGL rendering requires Z bfr */
};

/*--- Buffer Format Bit Masks ---*/
enum {
	formatRGBA8   = 0x0001,
	formatABGR8   = 0x0002,
	formatAny8    = 0x000F,  /* any 4-component, 8-bit format */
	formatRGBA16  = 0x0010,
	formatAny16   = 0x00F0
};


/*=== OTHER ENUMS ================================*/

/*--- Plugin Data Utilities Error Codes ---*/
enum {							/* see PRX_GetData, etc. */
	pdNoErr				= 0,
	pdWrongState		= 1,
	pdNoData			= 2,
	pdUnknownType		= 3,
	pdUnknownID			= 4,
	pdNotScalar			= 5,
	pdMemErr			= 6,
	pdOther				= 7
};

/*--- Plugin Data Item Types ---*/
enum {							/* see PRX_ItemRec */
	tBool				= 0,	/* 0 = false, true otherwise */
	tInt				= 1,	/* 32-bit integer */
	tUnsigned			= 2,	/* 32-bit unsigned integer */
	tFloat				= 3,	/* 32-bit IEEE float */
	tString				= 4,	/* null terminated string, arrayLen ignored */
	tTmpPtr				= 5,	/* void *, NOT SAVED IN FILE */
	tByte				= 6		/* 8-bit unsigned quantity, arrayLen heeded */
};
#define PRX_PI_LAST_TYPE	tByte		/* DON'T FORGET TO UPDATE THIS! */

/*--- Plugin Data States ---*/
typedef enum {
	stError				= -1,
	stNew				= 0,
	stReadFromFile		= 1,
	stModified			= 2,
	stNoInit			= 3
} PRX_PluginDataState;

/*=== PROPERTY LISTS =============================*/

/*--- Property List Keys ---*/

/*
	All values are required, unless marked as follows in the comment:
	+ = optional
	! = required by one or more types, optional or N/A for others
*/

enum _t_PRX_PKeys {
	PK_EndOfList 		=    0,	/* int: end of list marker */
	PK_APIVersion		= 1000,	/* major.minor: API version number */
	PK_Debugging		= 1100, /* Bool: show warning messages + */
	PK_Description		= 1200,	/* char *: Long description text ! */
	PK_DispatchSym		= 1300,	/* char *: Main dispatch procedure */
	PK_ExpCanDo			= 1400, /* uint: Data export flags-ExpD ! */
	PK_IsVariable		= 1500, /* Bool: Varies with time, space, etc. + */
	PK_HasDialog        = 1550, /* Bool: has a dialog for adjusting params + */
	PK_MacFileType		= 1600, /* PRX_Tag: MacOS file type-Draw + */
	PK_MediaType		= 1700, /* PRX_Tag: type of media-Draw ! */
	PK_Name				= 1800,	/* char *: Plugin name for UI */
	PK_PluginType		= 1900, /* PRX_Tag: Plugin type */
	PK_PluginVersion	= 2000,	/* major.minor: Plugin version */
	PK_SPFXOptions		= 2100, /* PRX_SPFXOptionsRec *: SPFX options ! */
	PK_UniquePrefix     = 2200, /* char *: For unique ID for plugin */
	PK_WasCopiedProc	= 2300,	/* void (*)(): Free property list + */
	PK_WipeCodes		= 2400, /* PRX_Tag *: Standard wipe codes-SPFX ! */
	PK_WipeCodes_Dir	= 2410, /* char *: PK_WipeCodes directions-SPFX ! */
	PK_WipeCodes_Len 	= 2420, /* uint: PK_WipeCodes array length-SPFX ! */
	PK_SourceAUsage     = 3000, /* uint: Buffer Input Usage */
	PK_SourceBUsage     = 3001, /* uint: Buffer Input Usage */
	PK_DestUsage        = 3002, /* uint: Buffer Output Usage */
	PK_ImageFormats     = 3003, /* uint: Buffer Format */
	PK_IntroducesAlpha  = 4000, /* Bool: the plugin introduces alpha + */
	PK_ZLastKey       = 100000	/* int: placeholder + */
};

/*
DETAILS ON A FEW OF THE PROPERTY KEYS

PK_IntroducesAlpha:
OPTIONAL.  If this property is True, then the plugin is declaring that it
produces alpha in such a way that the if the source alpha is 0xff, the
destination alpha might be something other than 0xff.

A plugin would set alpha:
if sourceAAlpha == 0xff && sourceBAlpha == 0xff && destAlpha != 0xff then
  PK_IntroducesAlpha = True
else
  PK_IntroducesAlpha = False

PK_HasDialog:
OPTIONAL.  If a plugin has a dialog for adjusting its parameters,
it may set this property to true.  The application may then
choose to relay this information to the user, for example, by
appending ellipsis (...) to the name of the plugin.  The application
is free to ignore this property.

PK_Debugging:
OPTIONAL.  While you are developing your plugin, you may benefit
from the warning messages that the application can print to stderr
about inconsistencies with your plugin.  Set this property to true
to see the messages.  Make sure you omit this property when you ship
your plugin.  The application may provide a user setting to suppress
warnings, even if you specify True for PK_Debugging.

PK_IsVariable:
OPTIONAL.  If specified, indicates that the plugin's user settings
will vary over time, or position, or both, etc.  In most cases,
the plugin interpolates between a set of start settings and a set
of end settings, both of which are stored in the plugin's private data.
This flag is a hint to the UI of the application that the user may
control the way the plugin varies.  If omitted, the default value
assumed by the application depends on the plugin type:
	Filters (AFlt, VFlt):	FALSE
	Transitions (SPFX):		!(PRX_SPFXOptionsRec.flag & optNoTimeVariance)
	Other plugin types:		N/A

PK_MacFileType:
OPTIONAL FOR DATA CONVERSION (Draw), N/A OTHERWISE.  If you know the
registered MacOS file type for your type of data, specify it here.
This type will be written into a resource fork for your data files,
which will make file opening and type checking more efficient.  If
you do not know the registered MacOS file type, a temporary type will
be assigned by the application, which will NOT be written to a resource
fork for your file.

PK_MediaType:
REQUIRED FOR DATA CONVERSION (Draw), N/A OTHERWISE.  Specifies the
type of media the data represents:
	PRX_MEDIA_TYPE_AUDIO		Any sound media
	PRX_MEDIA_TYPE_MOVIE		Any time sequenced media that resembles a movie
	PRX_MEDIA_TYPE_SEQUENCE		Any sequence of images with no time base
	PRX_MEDIA_TYPE_STILL		Any still image media
The UI presented to the user when this data is shown is derived
from the PK_MediaType.  For example, a PRX_MEDIA_TYPE_MOVIE might
display in a window that has VCR control buttons, while a
PRX_MEDIA_TYPE_STILL might display in a window with no VCR control
buttons, but with scaling and cropping controls.  Use
PRX_MEDIA_TYPE_SEQUENCE for image sequences which never have audio,
and which have no natural time base or rate of playback (for
example, the Photoshop Filmstrip format, or a digital slide show
format.)

PK_Name:
REQUIRED.  Name of the plugin as displayed to the user
in command menus, splash screen, dialog boxes, and errors.  Also
used as the unique name for the plugin, which may be stored in
files.  Use special encoding?  (c) becomes copyright symbol, (tm)
trademark, (r) registered?  Reference a standard encoding?

Any ISO-8859 character (8-bit ASCII) character is legal.

PK_UniquePrefix:
REQUIRED.  A registered prefix for all the plugins you create,
using the printable 7-bit subset of ISO-8859: 0x20 (space) thru
0x7E (~), inclusive.  A unique identifier, suitable for storing
in files, is constructed by concatanating the following strings
(the notation <keyname> indicates the value of the named property,
converted to a string as needed):

	<PK_UniquePrefix> "\012" <PK_Name> "\012" <PK_PluginVersion>

For example, if the following properties were defined:

	{ PK_UniquePrefix,		(void *) "Adobe" },
	{ PK_Name,				(void *) "Super Cool" },
	{ PK_PluginVersion, 	(void *) PRX_MAJOR_MINOR(1,0) }

The unique ID for this plugin would be:

	"Adobe\012Super Cool\0121.0"

For PK_UniquePrefix, we recommend that you use the X Consortium Registry
service, and use your registered ORGANIZATION name.  See the "registry" file
in the lastest X release, or send mail to xregistry@x.org.

PK_WasCopiedProc:
OPTIONAL:  If the plugin had to create the
property list dynamically, it can include this callback proc to
free the property list after the application has copied it
*/

/*=== DEFINED CONSTANTS ==========================*/

#define PRX_CLICKS					600

#define PRX_ENTRY_SYM				"PRX_PluginProperties"

#define PRX_TYPE_AUDIO_FILTER		kAFlt
#define PRX_TYPE_DATA_CONVERTER		kDraw
#define PRX_TYPE_DATA_EXPORTER		kExpD
#define PRX_TYPE_DEVICE_CONTROLLER	kDevC
#define PRX_TYPE_EDL_EXPORTER		kExpM
#define PRX_TYPE_TRANSITION			kSPFX
#define PRX_TYPE_VIDEO_FILTER		kVFlt

#define PRX_MEDIA_TYPE_AUDIO		kPRXa
#define PRX_MEDIA_TYPE_MOVIE		kPRXm
#define PRX_MEDIA_TYPE_SEQUENCE		kPRXs
#define PRX_MEDIA_TYPE_STILL		kPRXi

/*
================
	TYPEDEFS
================
*/

#ifndef UX_IS_PREM
typedef Window PRX_Window;
#else
typedef unsigned PRX_Window;
#endif

typedef char PRX_Bool;

typedef enum _t_PRX_PKeys PRX_PKeys;

typedef struct _t_PRX_PropertyList {
	PRX_PKeys key;
	void *value;
} PRX_KeyValueRec, *PRX_PropertyList;

typedef PRX_PropertyList (*PRX_PluginPropertiesProc)(unsigned apiVersion);

				/* Typedef for properties proc prototype */

typedef void *PRX_RefCon[8];

				/* Typedef for private reference constant */

typedef struct {
	unsigned char *data;			/* pointer to pixel data */
	unsigned rowBytes;				/* size of 1 scanline in bytes */
	XRectangle bounds;				/* bounding rectangle for pixels */

	Display*  glDpy;                /* app's X display (connection) */
	GLXDrawable glDrawable;         /* current drawable for OpenGL rendering */
	GLXContext  glContext;          /* current context for OpenGL rendering */

	void*  appBufferInfo;           /* private buffer information, ignore */
	PRX_RefCon appPrivate;			/* private reference constants, ignore */
} PRX_ScanlineBufferRec, *PRX_ScanlineBuffer;

				/* This structure defines a buffer of one or more
				   scanlines of pixel data.  Scanlines are organized
				   from top to bottom, and scanned from left to right.
				   The number of scanlines can be derived from bounds:
				   		nScanlines = bounds.height;
				   The width of a scanline in pixels is:
				   		nWidth = bounds.width;
				   Pixels are always in the most efficient native
				   format, which means that your code will have to
				   use PRX_GetPixelFormat at runtime
				   to handle different formats.  Ignore the
				   appPrivate and appBufferInfo fields; do not save
				   or change their values.  See PRX_NewScanlineBuffer
				   and PRX_FreeScanlineBuffer. */


typedef int PRX_Tag;				/* 32-bits treated as 4 ASCII characters */

/*--- Plugin Data Items ---*/

typedef struct {
	int id;							/* plugin specified id for item */
	int type;						/* item type */
	unsigned arrayLen;				/* 0 if single, >0 for array */
	void *data;						/* item value, or array */
} PRX_ItemRec, *PRX_ItemArray;

				/* This structure defines an item of plugin private
				   data, or a user setting, for a plugin instance.
				   The id is a plugin specified number which uniquely
				   identifies this particular data item.  The type
				   indicates what scalar type is contained in
				   the data field.  See the enum above (tInt, tBool,
				   etc.).  If the arrayLen is 0, there is only one
				   value in the data field.  Otherwise, the data
				   field should be treated as a pointer to an array
				   of length arrayLen elements, each element being
				   of the type indicated in the type field. */

/*--- Audio Filter Data Types ---*/

/* An audio filter plugin entry point (dispatch symbol) is defined as follows:

		int YourAudioFilter(int selector, PRX_AudioFilter theData)

   You can use any name you want for the procedure, which you define with
   the PK_DispatchSym property */

typedef struct {
	void *appPrivData;				/* utility function data, passed back */
	unsigned char *src;				/* source samples */
	unsigned char *dst;				/* destination for filtered samples */
	int firstByte;					/* first sample byte offset */
	int size;						/* size of src, in bytes */
	int total;						/* total bytes of audio in clip */
	int fps;						/* frames per second rate */ 
	short sampleFormat;				/* format flags */
	short flags;                    /* operational flag bits */
	double rate;					/* sample rate */
} PRX_AudioFilterRec, *PRX_AudioFilter;

				/* Runtime data passed to a video filter plugin */

/*--- Data Conversion Data Types ---*/

/* A data conversion plugin entry point (dispatch symbol) is defined
   as follows:

		int YourDataConverter(int selector, PRX_DataConverter theData)

   You can use any name you want for the procedure, which you define with
   the PK_DispatchSym property */

typedef enum {
	trackA = 0,
	trackB = 1
} PRX_TrackID;

typedef struct {
	void *appPrivData;				/* utility function data, passed back */
	
	/*** Draw_GetVideo Info ***/
	PRX_ScanlineBuffer vidDst;		/* SPECIFIES video data destination */
	XRectangle vidRect;				/* SPECIFIES sub-rectangle of vidDst */
	unsigned vidFlags;				/* SPECIFIES per Draw_GetVideo flags */
	unsigned frame;					/* SPECIFIES frame to put in vidDst */
	int inPoint;					/* SPECIFIES user specified In point */
	int outPoint;					/* SPECIFIES user specified Out point */
	
	/*** Draw_GetAudio Info ***/
	unsigned char *audDst;			/* SPECIFIES audio data destination */
	int firstByte;					/* SPECIFIES first sample byte offset */
	int size;						/* SPECIFIES bytes to put in audDst */
	
	/*** File Information ***/
	char *filePath;					/* SPECIFIES pathname of file */
	void *fileRef;					/* reference to opened file, NULL
									   if file is not open yet */
	PRX_Bool isSingleFrame;			/* set for still images */
	PRX_Bool mustBuffer;			/* set if converted frames must be
									   buffered offscreen (no direct to
									   screen conversion) */
	PRX_Bool isDifferenced;			/* set for files whose converted
									   frames require other frames
									   to compute */
	PRX_Bool isNotFile;				/* set if data to be converted comes
									   from someplace other than the file
									   specified in filePath */ 
	PRX_Bool is1fps;				/* set if data to be converted is
									   a series of still images that
									   can be shown at a rate of 1 fps
									   (numbered sequences of image files) */
	PRX_Bool mustNotCache;			/* set if data should not be cached */
	PRX_Bool spare1;				/* spare flag 1 */
	PRX_Bool spare2;				/* spare flag 2 */
	
	/*** Format Information ***/
	XRectangle bounds;				/* largest bounding rectangle for video
									   images in data */
	int numFrames;					/* total number of frames of video */
	PRX_Bool isAlphaUseful;			/* set if the alpha channel byte in
									   the 32-bit pixel data is useful */
	PRX_Bool spare3;				/* spare flag 3 */
	short contains;					/* bit masks for video, audio */
	int audFlags;					/* audio flags (gaStereo, etc.) */
	double audRate;					/* audio rate */
} PRX_DataConverterRec, *PRX_DataConverter;

				/* Runtime data passed to a data conversion plugin.
				   The word SPECIFIES in the field comment indicates
				   that this data is passed in by the application,
				   which the plugin should treat as readonly.  All
				   other fields are for the plugin to fill in and
				   return, usually during the Draw_GetInfo call. */


/*--- Data Export Data Types ---*/

/* A data export plugin entry point (dispatch symbol) is defined
   as follows:

		int YourDataExport(int selector, PRX_DataExporter theData);

   You can use any name you want for the procedure, which you define with
   the PK_DispatchSym property */

typedef struct {
	void *appPrivData;				/* utility function data, passed back */
	int inPoint;					/* user specified In point */
	int outPoint;					/* user specified Out point */
	int numFrames;					/* number of frames in the clip */
	int frameRate;					/* frames/second rate of clip */
	XRectangle bounds;				/* bounding rectangle for pixels */
	short contains;					/* bit masks for video, audio */
	short audFlags;					/* audio flags (gaStereo, etc.) */
	double audRate;					/* audio rate */
} PRX_DataExporterRec, *PRX_DataExporter;

				/* Runtime data passed to a data export plugin.
				   See Utility Routines defined below for additional
				   information. */

/*--- Device Control Data Types ---*/

/* A device control plugin entry point (dispatch symbol) is defined
   as follows:

		int YourDevController(int selector, PRX_DevController theData);

   You can use any name you want for the procedure, which you define with
   the PK_DispatchSym property */

typedef struct {
	void *appPrivData;				/* utility function data, passed back */
	short command;					/* command to perform */
	short mode;						/* mode command and status */
	int timeCode;					/* time code command and status:
									   -1 = N/A, -2 = blank */
	short timeFormat;				/* 0=non-drop, 1=drop-frame */
	short timeRate;					/* fps for the time code above */
	int features;					/* cmdGetFeatures return value */
	short error;					/* error code from any command */
	short preroll;					/* pre-roll time (seconds) */
	stamp_t ust;					/* Unadjusted System Time for sync'ing */
	stamp_t msc;					/* Media Stream Counter for sync'ing */
	int count;						/* number of frames */
} PRX_DevControllerRec, *PRX_DevController;

/*--- EDL Export Data Types ---*/

typedef struct {
	long size;						/* total size of this block,
									   including static data and sub-blocks */
	long dataSize;					/* the static data size for this block */
	long type;						/* block type (PRX_Tag) */
	long theID;						/* the block ID, for blocks which do not
									   need an ID, 0 is used */
} PRX_BlockRec;

				/* Block header. Additional "static" data follows header,
				   if dataSize > 0. */

/* A device control plugin entry point (dispatch symbol) is defined
   as follows:

		int YourEDLExporter(int selector, PRX_EDLExporter theData);

   You can use any name you want for the procedure, which you define with
   the PK_DispatchSym property */

typedef struct {
	void *appPrivData;				/* utility function data, passed back */
	PRX_BlockRec *project;			/* pointer to first block in project */
	unsigned size;				    /* total size of the project, in bytes */
	int timeBase;					/* current default timebase */
	char *projectName;				/* current project name */
} PRX_EDLExporterRec, *PRX_EDLExporter;

/* The following structures are for the block types that have structured
   "static" data. */

typedef struct {					/* See PRX_EDLXFromPoint(...) */
	short v;
	short h;
} PRX_Point;

typedef struct {					/* See PRX_EDLXFromRect(...) */
	short top;
	short left;
	short bottom;
	short right;
} PRX_Rect;

typedef struct {
	long start;						/* starting position for the work area */
	long end;						/* ending position for the work area */
} PRX_BLOK;

typedef struct {
	short fileID;					/* the dependent file ID */
	long in;						/* IN point within the source clip */
	long out;						/* OUT point within the source clip-1 */
} PRX_CLIP;

typedef struct {
	unsigned char corners;			/* the 'corner' flags, one bit each,
									   from the user settings for the effect */
	char direction;					/* the direction flag, 0= A-->B, 1=B-->A */
	short startPercent;				/* starting percentage times 100 */
	short endPercent;				/* ending percentage times 100 */
} PRX_FXOP;

typedef struct {					/* See PRX_EDLFileNameFromMACS(...) */
	short vRefNum;
	long parID;
	unsigned char name[64];
} PRX_MACS;

typedef struct {
	short zoom;						/* zoom factor 1 to 400, 100 is normal */
	short time;						/* time location 1 to 1000 */
	short rotation;					/* rotation -360 to 360, 0 is normal */
	short delay;					/* delay factor 0 to 100, 0 is normal */
	PRX_Point spot;					/* center for the image at this point */
} PRX_MREC;

typedef struct {
	long h;							/* horizontal */
	short v;						/* vertical */
} PRX_RPNT;

typedef struct {
	long frames;					/* binary frame count */
	char dropframe;					/* true = DF, false = NDF */
	char format;					/* 1 = NTSC(30), 0 = PAL(25), 2=Film(24) */
} PRX_TIMB;

typedef struct {
	short clipID;					/* the dependent clip ID */
	long start;						/* the clip starting position */
	long end;						/* the clip ending position */
} PRX_TREC;

typedef struct {
	PRX_Rect frame;					/* bounding frame for video data */
	short depth;					/* bit depth for video data */
} PRX_VIDI;

/*--- Transition Data Types ---*/

/* A transition plugin entry point (dispatch symbol) is defined
   as follows:

		int YourTransition(int selector, PRX_Transition theData)

   You can use any name you want for the procedure, which you define with
   the PK_DispatchSym property */

typedef struct {
	void *appPrivData;				/* utility function data, passed back */
	PRX_ScanlineBuffer srcA;		/* source A pixels */
	PRX_ScanlineBuffer srcB;		/* source B pixels */
	PRX_ScanlineBuffer dst;			/* destination for filtered pixels */
	int part;						/* part/total = % complete */
	int total;						/* total number of buffers to filter */
	char arrowFlags;				/* for direction arrows */
	char reverse;					/* Boolean: run in reverse? */
	char source;					/* Boolean: are sources swapped? */
	char spare;					/* unused */
	XPoint start;					/* Spatial starting point */
	XPoint end;						/* Spatial ending point */
	XPoint center;					/* Spatial center point */
	short scanlineFormat;			/* format flags */
	short flags;                    /* operational flag bits */
	int fps;						/* frames per second rate */ 
} PRX_TransitionRec, *PRX_Transition;

				/* Runtime data passed to a transition plugin */

typedef struct {
	unsigned char enable;			/* which corners are enabled? */
	unsigned char state;			/* which corners are currently on? */
	unsigned char flags;			/* bit flags: custom, pairs, invariant */
	char exclusive;					/* are the edge indicators exclusive? */
	char hasReverse;				/* transition reversible? */
	char hasEdges;					/* edges? */
	char hasStart;					/* controlled open point? */
	char hasEnd;					/* controlled close point? */
} PRX_SPFXOptionsRec;

				/* This structure defines the options for a transition.
				   It is used in conjunction with the PK_SPFXOptions
				   property. */


/*--- Video Filter Data Types ---*/

/* A video filter plugin entry point (dispatch symbol) is defined
   as follows:

		int YourVideoFilter(int selector, PRX_VideoFilter theData)

   You can use any name you want for the procedure, which you define with
   the PK_DispatchSym property */

typedef struct {
	void *appPrivData;				/* utility function data, passed back */
	PRX_ScanlineBuffer src;			/* source pixels */
	PRX_ScanlineBuffer dst;			/* destination for filtered pixels */
	int part;						/* part/total = % complete */
	int total;						/* total number of buffers to filter */
	short scanlineFormat;			/* format flags */
	short flags;                    /* operational flag bits */
	int fps;						/* frames per second rate */ 
} PRX_VideoFilterRec, *PRX_VideoFilter;

				/* Runtime data passed to a video filter plugin */

/*
================
	MACROS
================
*/

#define PRX_MAJOR_MINOR(major, minor) \
	(((major) << 16) | ((minor) & 0x0FFFF))

#define PRX_SET_VERSION(v, major, minor) \
	(v) = PRX_MAJOR_MINOR(major, minor)

#define PRX_GET_VERSION(v, major, minor) \
	(major) = ((unsigned)(v)) >> 16; \
	(minor) = ((unsigned)(v)) & 0xFFFF


/*
==================
	PROTOTYPES
==================
*/

/*--- Mandatory Entry Point ---*/

/* This prototype represents the mandatory entry point into the plugin
   code and must be exported by the plugin. */

PRX_PropertyList PRX_PluginProperties(unsigned apiVersion);

				/* apiVersion SPECIFIES the latest version of the
				   plugin API understood by the host application.
				   RETURNS a property list.  The property list may
				   either by the address of a statically allocated
				   and initialized array, or a dynamically allocated
				   array, in which case the host application will 
				   expect the PK_FreePropsProc property to be defined.
				   The plugin owns the memory for the property list:
				   if items are to be retained by the host application,
				   they will be copied. */


/**** UTILITY FUNCTIONS ***************************/

/* These prototypes represent utilities and services provided by
   the host application to plugins.  Global data and context
   specification information can be obtained through these
   functions.  Global data should be accessed once, during the
   plugin's setup phase, or during creation of its private data,
   and stored in the private data that is passed back to the plugin,
   for greater efficiency. */

/*=== PLUGIN SPECIFIC "CALLBACKS" ================*/

int PRX_DCOpenFile(PRX_DataConverter theData);

				/* FOR DATA CONVERTER PLUGINS ONLY.
				   If your plug-in is in a selector that
				   expects to find the file already open,
				   but the PRX_DataConverter->fileRef field
				   is NULL, use this utility to call your
				   plugin with the Draw_Open selector.  Do not
				   call your Draw_Open code branch directly,
				   Premiere needs to do additional bookkeeping
				   on opened files.  Returns zero on success,
				   or a "dc" error on failure. */

PRX_Bool PRX_DevCheckAbort(PRX_DevController theData);

				/* FOR DEVICE CONTROL PLUGINS ONLY.
				   Call during dsExecute/cmdLocate to determine
				   if the user is attempting to abort the locate
				   operation. A non-zero result indicates that the
				   user has attempted to terminate the locate operation. */

void PRX_DevResume(PRX_DevController theData);

				/* FOR DEVICE CONTROL PLUGINS ONLY.
				   Call to resume capture operations after a suspend.
				   See PRX_DevSuspend.  Every PRX_DevSuspend must
				   be followed by a PRX_DevResume. */

void PRX_DevSuspend(PRX_DevController theData);

				/* FOR DEVICE CONTROL PLUGINS ONLY.
				   Call to temporarily suspend any capture operations
				   in a device-controlled window.  Normally, you
				   would call this routine before putting up an error
				   alert, for example:
				   
				   		PRX_DevSuspend(theData);
						// ... put up your modal dialog, wait for user ...
						PRX_DevResume(theData);
					
				   IMPORTANT! If you don't call PRX_DevSuspend
				   before putting up an error alert (or any other kind
				   of window), video may be played over your window. */

short PRX_EDLClipFromFile(PRX_EDLExporter theData, short fileID);

				/* FOR EDL EXPORT PLUGINS ONLY.
				   Return the clipID for a fileID.  Returns -1
				   if the fileID is not a clip file. */

int PRX_EDLCountBlocks(PRX_EDLExporter theData, PRX_Tag type,
	PRX_BlockRec *srcBlock);

				/* FOR EDL EXPORT PLUGINS ONLY.
				   Return the number of blocks of a given type,
				   starting from srcBlock. Set type to -1 to
				   get the total number of blocks after srcBlock. */

unsigned PRX_EDLCopyData(PRX_EDLExporter theData, PRX_BlockRec *srcBlock,
	void *dst, unsigned maxLen);

				/* FOR EDL EXPORT PLUGINS ONLY.
				   This routine copies the data from srcBlock (not
				   including the PRX_BlockRec header) to the
				   buffer dst, up to maxLen bytes.  The actual
				   number of bytes copied is returned.  The dst
				   pointer must be large enough to hold maxLen
				   bytes. */

int PRX_EDLEditWipeCodes(PRX_EDLExporter theData);

				/* FOR EDL EXPORT PLUGINS ONLY.
				   Show a standard wipe code definition dialog box.
				   The dialog is modal.  This routine will not return
				   until the user closes the dialog box. */

int PRX_EDLFileNameFromMACS(PRX_EDLExporter theData, PRX_MACS *block,
	char *path);

				/* FOR EDL EXPORT PLUGINS ONLY.
				   Convert a PRX_MACS block to a path name.
				   Copies the file path to path (caller
				   should allocate to PATH_MAX).
				   Returns non-zero if no such file. */

PRX_BlockRec *PRX_EDLFindBlock(PRX_EDLExporter theData, PRX_Tag type,
	long theID, long index, PRX_BlockRec *srcBlock);

				/* FOR EDL EXPORT PLUGINS ONLY.
				   Find a particular block.  A -1 for type means
				   any type.  A -1 for theID means any ID.
				   A -1 for index means an exact match for
				   theID and type. */

int PRX_EDLGetWipeCodes(PRX_EDLExporter theData, int *codes);

				/* FOR EDL EXPORT PLUGINS ONLY.
				   Return the current set of user defined wipe
				   code identifiers. */

PRX_BlockRec *PRX_EDLNextBlock(PRX_EDLExporter theData,
	PRX_BlockRec *srcBlock);

				/* FOR EDL EXPORT PLUGINS ONLY.
				   Return the pointer to the block after srcBlock.
				   Returns NULL if there are no more blocks. */ 
				   
void PRX_EDLXFromPoint(PRX_EDLExporter theData, PRX_Point *point,
	XPoint *xPoint);

				/* FOR EDL EXPORT PLUGINS ONLY.
				   Convert a PRX_Point to an XPoint. */

void PRX_EDLXFromRect(PRX_EDLExporter theData, PRX_Rect *rect,
	XRectangle *xRect);

				/* FOR EDL EXPORT PLUGINS ONLY.
				   Convert a PRX_Rect to an XRectangle. */

int PRX_ExportAudioFromClip(PRX_DataExporter theData, unsigned second,
	short formatFlags, double audRate, unsigned char *samples);

				/* FOR DATA EXPORT PLUGINS ONLY.
				   Get past or future audio samples from
				   the source clip (derived from 
				   theData->appPrivData).  The second parameter
				   is the desired starting time, from
				   0 to [PRX_DataExporterRec fields] numFrames*frameRate
				   inclusive, although your plugin should abide by
				   the user specified inPoint and outPoint.
				   Exactly one second's worth of audio samples are returned
				   into samples.  The samples parameter must be non-NULL, and
				   must be large enough for the application to write all the
				   requested samples into (see PRX_AllocAudioBuffer). 
				   If formatFlags is set to aflagSpecial, audRate is
				   used as the requested audio rate, with the application
				   doing any resampling or downsampling necessary. */

int PRX_ExportFPS(PRX_DataExporter theData);

				/* FOR DATA EXPORT PLUGINS ONLY.
				   Get the frames per second rate of the clip
				   being exported. */

int PRX_ExportVideoFromClip(PRX_DataExporter theData, int frame,
	PRX_ScanlineBuffer scanbuf, XRectangle *bounds);

				/* FOR DATA EXPORT PLUGINS ONLY.
				   Get a past or future scanline buffer from
		   		   the source clip (derived from theData->appPrivData).
		   		   The frame parameter is the desired buffer, from
		  		   0 to PRX_DataExporterRec.numFrames inclusive, although
				   your plugin should abide by the user specified
				   PRX_DataExporterRec.inPoint and outPoint.  The
		   		   scanbuf pointer must be non-NULL, and scanbuf->data
				   must be large enough for the application to write
				   the requested scanlines into.  The bounds parameter is
		   		   the destination rectangle in scanbuf. */

int PRX_GetAudioFromClip(PRX_AudioFilter theData, int firstByte, int size,
	unsigned char *samples);

				/* FOR AUDIO FILTERS ONLY.
				   Get past or future audio samples from
				   the source clip (derived from 
				   theData->appPrivData).  The firstByte parameter
				   is the desired starting sample byte, from
				   0 to PRX_AudioFilterRec.total-1 inclusive.
				   The size parameter specifies the number of
				   bytes you want to retrieve.  The samples
				   parameter must be non-NULL, and must be large
				   enough for the application to write all the
				   requested samples into (see PRX_AllocAudioBuffer) */
				   

int PRX_GetVideoFromClip(PRX_VideoFilter theData, int frame,
	PRX_ScanlineBuffer scanbuf, XRectangle *bounds);

				/* FOR VIDEO FILTERS ONLY.
				   Get a past or future scanline buffer from
		   		   the source clip (derived from theData->appPrivData).
		   		   The frame parameter is the desired buffer, from
		  		   0 to PRX_VideoFilterRec.total inclusive.  The
		   		   scanbuf pointer must be non-NULL, and scanbuf->data
				   must be large enough for the application to write
				   the requested scanlines into.  The bounds parameter is
		   		   the destination rectangle in scanbuf.  */

int PRX_GetVideoFromTrack(PRX_Transition theData, int frame,
	PRX_TrackID track, PRX_ScanlineBuffer scanbuf, XRectangle *bounds);

				/* FOR TRANSITIONS ONLY.
				   Get a past or future scanline buffer from
		   		   the clip in the specified track (specified
				   in appPrivData).  The frame parameter is the
				   desired buffer, from 0 to PRX_TransitionRec.total
				   inclusive.  The scanbuf pointer must be non-NULL,
				   and scanbuf->data must be large enough for the
				   application to write the requested scanlines
				   into.  The bounds parameter is the destination
				   rectangle in scanbuf. */

/*=== CLIP FUNCTIONS =============================*/

PRX_Bool PRX_ClipAspect(short clipID);

PRX_Bool PRX_ClipBackwards(short clipID);

int PRX_ClipCountMarkers(short clipID);

int PRX_ClipFindMarker(short clipID, int frame, int fps);

int PRX_ClipGetMarker(short clipID, int marker, int fps);

int PRX_ClipNextMarker(short clipID, int frame, int fps);

int PRX_ClipPrevMarker(short clipID, int frame, int fps);

int PRX_ClipSize(short clipID, int fps);

int PRX_ClipSpeed(short clipID);

int PRX_ClipStart(short clipID, int fps);

void PRX_ClipTitle(short clipID, char *title, PRX_Bool *alias);

int PRX_ClipWidth(short clipID, int fps);

short PRX_GetClipID(void *theData);

/*=== PLUGIN DATA UTILITIES ======================*/

/* The following routines return zero on success, or a non-zero
   error code (pdUnknownID, pdWrongState, pdNoData, etc.)  The
   first parameter of each of these functions is theData,
   which is the same as the parameter passed to your
   plugin entry point, regardless of the type of plugin.
   For example, for an Audio Fiter, you would specify the
   PRX_AudioFilter pointer passed to your Audio Filter entry
   point procedure. */

int PRX_CheckData(void *theData, PRX_Tag *signature, unsigned *version,
	unsigned *numItems, unsigned *size);

				/* Gets the signature and version you specified when
				   your plugin data was initialized.  When the
				   PRX_PluginDataState is stReadFromFile, you can
				   use the signature and version to determine if the
				   data read from the application storage file
				   was written by an earlier version of your plugin.
				   You can then take steps to upgrade the data.
				   You also get the number of items stored
				   in the numItems parameter, and the total number
				   of bytes of storage used in the size parameter.
				   Returns pdWrongState if the PRX_PluginDataState is
				   stNew. Pass NULL for parameters you don't care
				   about. */

int PRX_GetData(void *theData, int itemID, int *type, unsigned *arrayLen,
	void **data);

				/* Retrieves an item of your plugin data. The itemID
				   specifies which item you want. The type of the
				   item is returned in type, and the value is returned
				   in *data. If *data is an array, the length of the
				   array is returned in arrayLen.  If arrayLen is 0,
				   *data is the actual data value, not a pointer to
				   the data. Returns pdWrongState for stNew. */

PRX_PluginDataState PRX_GetState(void *theData);

				/* Get the current data state. */

int PRX_InitData(void *theData, PRX_Tag signature, unsigned version,
	PRX_ItemArray items, unsigned numItems);

				/* Can be used to initialize new user settings
				   and plugin data (when PRX_PluginDataState is stNew),
				   or to erase old settings and replace them with
				   new ones.  The signature and version parameters
				   help your plugin support old data files: see
				   PRX_CheckData for details.  The version 
				   parameter is a 32-bit version number.  The
				   items array contains your data, which is
				   numItems in length. If the PRX_PluginDataState
				   is stNoInit, this function returns pdWrongState
				   and does nothing. */

int PRX_NextData(void *theData, PRX_ItemRec **item);

				/* Retrieves the next data item with a stateless
				   enumerator.  The order that
				   items are stored in is undefined, but you can
				   use PRX_NextData to access each of the data items
				   one at a time.  All data items are guaranteed to
				   be returned by the time PRX_NextData stores NULL
				   into *item (indicating that there is no more
				   data).  This is useful for determining which
				   itemID's are actually used in this instance, if some
				   are optional. Specify *item as NULL to get the first
				   available item.  You must pass the previously returned
				   item in order to insure that you get the
				   next item, and all items in turn.  For example, the
				   following loop traverses all data items:
				   
				   PRX_ItemRec *item = NULL; // Start at the first item
				   do {
				   		PRX_NextData(theData, &item);
						// Process item ... continue until done
						// Make sure you leave item and id as the
						// values returned by the last call to
						// PRX_NextData
				   } while (item);
				   
				   Returns pdWrongState for stNew.
				   */

int PRX_RemoveData(void *theData, int itemID);

				/* Remove the designated item, freeing memory the
				   application allocated for the copy of the data
				   item. Returns pdWrongState if stNew. */

int PRX_SetData(void *theData, int itemID, int type, unsigned arrayLen,
	void *data);

				/* Stores an item of your plugin data, creating a new
				   item if this itemID has not be set before. The itemID
				   specifies which item you are storing.  The type
				   specifies the data type.  The arrayLen indicates
				   that the data is an array of values of type. If
				   arrayLen is 0, data is not an array, but the
				   actual value.  Returns pdWrongState if stNew. */

/*=== MISCELLANEOUS UTILITIES ====================*/

int PRX_FreeScanlineBuffer(PRX_ScanlineBuffer scanbuf);

				/* Free a PRX_ScanlineBuffer allocated with
				   PRX_NewScanlineBuffer.  Set's the structure
				   pointed to by scanbuf to all zeroes. */

unsigned PRX_GetAudioSize(unsigned secs, short formatFlags,
	double audRate);

				/* The size of an audio sample buffer depends
				   on the format and the rate.  This utility
				   computes the size in bytes for you.  Pass
				   the returned result to your memory allocation
				   routine to create an appropriately sized buffer.
				   Use secs to specify the duration of the audio
				   sample in seconds.  Specify the format using
				   formatFlags (e.g., aflag11KHz+aflag16Bit).  If
				   formatFlags has the aflagSpecial bit set,
				   audRate is used as the audio rate. */

int PRX_GetPixelFormat(void);

				/* Return the native pixel format supported by
				   the application. See the values formatRGBA8,
				   formatABGR8, etc. */

int PRX_NewScanlineBuffer(XRectangle *bounds, PRX_ScanlineBuffer scanbuf);

				/* Allocate a new PRX_ScanlineBuffer with bounds.
				   Fill in the structure pointed to by scanbuf.
				   The associated dmfx buffer is initially setup
				   for direct output.
				   Return a non-zero error code if failure. */

int PRX_SetupOutputScanlineBuffer(int outputUsage, PRX_ScanlineBuffer scanbuf);
				/* Sets up scanbuf's dmfx buffer for the type of
				   output indicated by outputUsage, which is one
				   of bufOutputDirect, bufOutputOpenGL, etc.  The
				   buffer is given an anticipated inputUsage of
				   bufInputAll.  The scanline buffer tracks its
				   current setup state, and manages any input or
				   output cleanup that might be necessary.
				   Return a non-zero error code if failure. */

int PRX_SetupInputScanlineBuffer(int inputUsage, PRX_ScanlineBuffer scanbuf);
				/* Sets up scanbuf's dmfx buffer for the type of
				   input indicated by inputUsage, which is a
				   logical OR of bufInputDirect, bufInputDrawPixels,
				   etc.  The scanline buffer tracks its current
				   setup state, and manages any input or output
				   cleanup that might be necessary.
				   Return a non-zero error code if failure. */

void PRX_UpdateAllWindows(void);

				/* When your plugin has moved, resized, or closed
				   a plugin window or dialog box, your
				   plugin should call PRX_UpdateAllWindows to allow
				   the application a chance to refresh any application
				   windows that were underneath. */

#ifndef UX_IS_PREM

Display *PRX_GetDisplay(void);

				/* Return the X Display that the host app is
				   displaying on. */

Widget PRX_GetAppShell(void);

				/* Return the application shell widget */

Widget PRX_GetDialogParent(void);

				/* Return the appropriate shell to parent
				 * a dialog */

void PRX_SetPremiereTransient(Widget);

				/* Tell Premiere a window is transient */

void PRX_BusyCursor(Boolean);

				/* Set cursor windows, including transients */

int PRX_DispatchEvent(XEvent *event);

				/* While implementing a modal dialog, use this
				   function to dispatch events you acquire with
				   XtAppNextEvent.  The event argument should actually
				   be */

#endif

#ifdef __cplusplus
}
#endif

#endif /* _PREMIERE_XAPI_H */
