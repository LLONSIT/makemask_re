/******************************************************************************

	    COPYRIGHT (c) 1990, 2002 by Macrovision Corporation.
	This software has been provided pursuant to a License Agreement
	containing restrictions on its use.  This software contains
	valuable trade secrets and proprietary information of 
	Macrovision Corporation and is protected by law.  It may 
	not be copied or distributed in any form or medium, disclosed 
	to third parties, reverse engineered or used in any manner not 
	provided for in said License Agreement except with the prior 
	written authorization from Macrovision Corporation.

 *****************************************************************************/
/*	
 *	Module: $Id: lm_attr.h,v 1.1 2004/05/20 19:50:24 alaffin Exp $
 *
 *	Description: 	Attribute tags for FLEXlm setup parameters.
 *
 *	M. Christiano
 *	5/3/90
 *
 *	Last changed:  11/12/98
 *
 */

#define LM_A_DECRYPT_FLAG	1	/* (short) */
#define LM_A_DISABLE_ENV	2	/* (short) */
#define LM_A_LICENSE_FILE	3	/* (char *) -- obsolete in v5 */
#define LM_A_CRYPT_CASE_SENSITIVE 4	/* (short) */
#define LM_A_GOT_LICENSE_FILE	5	/* (short) */
#define LM_A_CHECK_INTERVAL	6	/* (int) */
#define LM_A_RETRY_INTERVAL	7	/* (int) */
#define LM_A_TIMER_TYPE		8	/* (int) */
#define LM_A_RETRY_COUNT	9	/* (int) */
#define	LM_A_CONN_TIMEOUT	10	/* (int) */
#define	LM_A_NORMAL_HOSTID	11	/* (short) */
#define LM_A_USER_EXITCALL	12	/* PTR to func returning int */
#define	LM_A_USER_RECONNECT	13	/* PTR to func returning int */
#define LM_A_USER_RECONNECT_DONE 14	/* PTR to func returning int */
#define LM_A_USER_CRYPT		15	/* PTR to func returning (char *) */
#define	LM_A_USER_OVERRIDE	16	/* (char *) */
#define LM_A_HOST_OVERRIDE	17	/* (char *) */
#define LM_A_PERIODIC_CALL	18	/* PTR to func returning int */
#define LM_A_PERIODIC_COUNT	19	/* (int) */
#define LM_A_NO_TRAFFIC_ENCRYPT	21	/* (short) */
#define LM_A_USE_START_DATE	22	/* (short) */
#define LM_A_MAX_TIMEDIFF	23	/* (int) */
#define LM_A_DISPLAY_OVERRIDE	24	/* (char *) */
#define LM_A_ETHERNET_BOARDS	25	/* (char **) */
#define LM_A_LINGER		27	/* (long) */
/* 
 *	#28 RESERVED -- it used to be LM_A_CUR_JOB, and if a 
 *	user uses that number, we want it to error out
 *	#define LM_A_CUR_JOB		28	 (LM_HANDLE *) 
 */

#define LM_A_SETITIMER		29	/* PTR to func returning void, eg PFV */
#define LM_A_SIGNAL		30	/* PTR to func returning PTR to */
					/*    function returning void, eg:
					      PFV (*foo)(); 	*/
#define LM_A_TRY_COMM		31	/* (short) Try old comm versions */
#define LM_A_VERSION		32	/* (short) FLEXlm version */
#define LM_A_REVISION		33	/* (short) FLEXlm revision */
#define LM_A_COMM_TRANSPORT	34	/* (short) Communications transport */
					/*	  to use (LM_TCP/LM_UDP) */
#define LM_A_CHECKOUT_DATA	35	/* (char *) Vendor-defined checkout  */
					/*				data */
#define LM_A_PROCESS_UPGRADE	36	/* (short) Process UPGRADE lines? */
#define LM_A_DIAGS_ENABLED	37	/* (short) Allow FLEXlm diag output */
#define LM_A_REDIRECT_VERIFY	38	/* Verification routine for hostid */
					/* redirect (NULL -> NO redirection) */
					/* PTR to func returning (char *) */
#define LM_A_HOSTID_PARSE	39	/* Vendor-defined hostid parsing */
					/* routine: PTR to func returning int */
#define LM_A_VENDOR_GETHOSTID	40	/* Return Vendor-defined hostid */
					/* PTR to func returning (HOSTID *) */
#define LM_A_VENDOR_PRINTHOSTID	41	/* Print Vendor-defined hostid */
					/* PTR to func returning (char *) */
#define LM_A_VENDOR_CHECKID	42	/* Compare 2 Vendor-defined hostids */
					/* PTR to func returning int */
#define LM_A_UDP_TIMEOUT	43	/* (int) If UDP client doesn't send */
					/* heartbeart, then it is timed out */
					/* default = 3 minutes, although */
					/* actual timeout can take two minutes*/
					/* longer */
#define LM_A_ALLOW_SET_TRANSPORT 44 /* (int) If this is true, users */
					/* can reset COMM_TRANSPORT. */
					/* default = true: With default, */
					/* users can reset COMM_TRANSPORT via */
					/* COMM_TRANSPORT line in license */
					/* file or FLEXLM_COMM_TRANSPORT */
					/* environment variable. */
#define LM_A_CHECKOUTFILTER	45	/* Vendor-defined checkout filter */
					/* PTR to func returning int */
#define LM_A_LICENSE_FILE_PTR	46	/* (char *) - for lm_get_attr use  */
					/* char *s; lm_get_attr(..,&s);  */
					/* -- obsolete in v5 */
#define LM_A_ALT_ENCRYPTION	47	/* (VENDORCODE *) - for alternate */
					/* encryption codes */
#define LM_A_VD_GENERIC_INFO	48	/* PTR to LM_VD_GENERIC_INFO struct */
					/* struct type set to: */
					/* LM_VD_GENINFO_HANDLE_TYPE, */
					/* struct feat set to (CONFIG *) */
					/* returned from lm_next_conf() */
					/* after lh_get_attr, values returned */
					/* in struct (see lm_client.h) */
#define LM_A_VD_FEATURE_INFO	49	/* PTR to LM_VD_FEATURE_INFO struct */
					/* struct type set to: */
					/* LM_VD_FEATINFO_HANDLE_TYPE, */
					/* struct feat set to (CONFIG *) */
					/* returned from lm_next_conf() */
					/* after lh_get_attr, values returned */
					/* in struct (see lm_client.h) */
#if 0 /* discontinued in v5 */
#define LM_A_MASTER		50	/* (char *),lm_get_attr only, returns */
					/* name of master node for red. servs */
#endif
#define LM_A_LF_LIST		51	/* (char ***) -- returns null- */
					/* terminated list of filenames */
#define	LM_A_PLATFORM_OVERRIDE	52	/* (char *) */
#ifdef LM_INTERNAL
#define LM_A_PORT_HOST_PLUS   53        /* Internal Use Only */
#endif
#define LM_A_LICENSE_DEFAULT	56	/* (char *) -- use this instead of */
					/* LM_A_LICENSE_FILE or  */
					/* LM_A_LICENSE_FILE_PTR */
#define LM_A_CAPACITY		57	/* (short) */
#define LM_A_VENDOR_ID_DECLARE  58	/* set: PTR to LM_VENDOR_HOSTID struct*/
					/* get: PTR to LM_VENDOR_HOSTID_PTR */
#define LM_A_GENERIC_SERVER_OK	59	/* defaults to NOT-OK (0) */
#define LM_A_USING_GENERIC_SERVER 60	/* true if flexlmd is server 
					   get_attr ONLY */
#define LM_A_RETRY_CHECKOUT 	61	/* (int) default: 1 (true). 
					   Retry checkout if failure is due 
					   to communications error */
#define LM_A_SUPPORT_HP_IDMODULE 62	/* (int) default: 0 (false)
					   Not recommended, since it can
					   impact performance, and requires
					   use of SIGALRM */
#define LM_A_TCP_TIMEOUT	63	/* (int) If TCP client doesn't send */
					/* heartbeart, then it is timed out */
					/* default = 2 hours */
#define LM_A_CHECK_BADDATE	64	/* default = false */
#define LM_A_BEHAVIOR_VER	65	/* (char *) LM_BEHAVIOR_V6, etc. 
					   (ptr to char *) in lc_get_attr */
#define LM_A_LKEY_START_DATE	66	/* (int) default false-sdate in lkey */
#define LM_A_LKEY_LONG		67	/* (int) default false - 64-bit lkey*/
#define LM_A_LONG_ERRMSG	68	/* (int) error messages fmt */
#define LM_A_LICENSE_CASE_SENSITIVE 69	/* (int) default false */
#define LM_A_LICENSE_FMT_VER	70	/* (char *) LM_BEHAVIOR_V6, etc. 
					 * default LM_BEHAVIOR_CURRENT
					 */

#define LM_A_PC_PROMPT_FOR_FILE	71	/* (int) default true */
#define LM_A_PROMPT_FOR_FILE	LM_A_PC_PROMPT_FOR_FILE	 /* alias */
#define LM_A_MAX_LICENSE_LEN	72	/* (int) default true */
#define LM_A_INTERNAL1		73	/* for internal use only */
#define LM_A_USER_CRYPT_FILTER	74	/* PTR to func taking job, int, int, 
								int */
#define LM_A_USER_CRYPT_FILTER_GEN 75	/* PTR to func taking job, int, int */
#define LM_A_CKOUT_INSTALL_LIC 76	/* (int) true if BEH_V7+, else false */
#define LM_A_PERROR_MSGBOX 78	        /* (int/default true) If false, 
                                           perror doesn't put up a MSGBOX, but 
                                           prints to stderr, for batch apps
                                        */
#define LM_A_BORROW_OK 79               /* (int) default false, if true,
                                         * linger-borrowing enabled 
                                         */
#define LM_A_RELEASE_PATCH 80            /* (ptr to char *, lc_get_attr only)
                                          * The patch string for this release
                                          */
#define LM_A_WINDOWS_MODULE_HANDLE 81    /* (long) return value from
                                          * GetModuleHandle() 
                                          */
#define LM_A_LCM                82    /* (int) default is true (windows only) */
#define LM_A_FLEXLOCK           83    /* (int) default is false (windows only)*/
#define LM_A_LCM_URL            84    /* (char *) Internet URL for LCM 
                                       * support. Default is 
                                       * www.macrovision.com
                                       */
#define LM_A_FLEXLOCK_INSTALL_ID 85   /* (long) lc_get_attr() only.  See
                                       * Flexlock documentation.
                                       */
#define LM_A_JAVA_LIC_FMT 	86   /* (int, default: false) if set, 
				      * licenses are printed in java-
				      *	compatible format  
				      */

/* 
 *	The following is a programmatic API that can
 *	be used to override the setting in lm_code.h
 */
#define LM_A_SIGN_LEVEL 	87    	/* SIGN=, default is 1, set to 0 to
					   turn off and use license-key */
#define LM_A_KEY_LEVEL 	LM_A_SIGN_LEVEL    	
			/* for backward compatibility with v7.2 */
#define LM_A_PHASE2_APP		88	/* PTR to func taking job, int, int, int
					 * Implies LM_A_KEY_TYPE is 
					 * KEY_TYPE_PHASE2 */
#define LM_A_PHASE2_GEN		89	/* PTR to func taking job, int, int */
#define LM_A_PUBKEY		90	/* VENDORCODE * with pubkey info 
					   Rare--Use only if directed by 
					   Macrovision */
#define LM_A_INTERNAL2		91	/* Internal use only */
#define LM_A_STRENGTH_OVERRIDE	92	/* override value for individual app/
					   license-generator */
#define LM_A_BORROW_EXPIRE 	93	/* char *: date and optional time
					 * when license expires in 
					 * dd-mmm-yyyy[:hh:mm] format and 
					 * time in
					 * 24-hour hh:mm  format. */
#define LM_A_BORROW_STRING 	94	/* For custom borrow security 
					 * Usage:  char x[MAX_CONFIG_LEN * 2];
					 * set_attr(...,(LM_A_VAL_TYPE)x);
					 * See manual for further information
					 */
#define LM_A_MT_HEARTBEAT 	95	/* Default true:  Multi-threaded
					 * heartbeat is unsupported on some
					 * Unix platforms where multi-threading
					 * support is weak.  If your app
					 * has multi-threading conflicts, use
					 * this attr to disable 
					 */
#define LM_A_BORROW_STAT	96	/* Obtain information about locally
					 * borrowed features -- 
					 * Only valid for lc_get_attr.
					 * Takes pointer to LM_BORROW_STAT:
					 * Use 
					 * LM_BORROW_STAT s;
					 *	lc_get_attr(job, 
					 *		LM_A_BORROW_STAT,
					 *		&s);
					 * See lmclient.h for LM_BORROW_STAT.
					 */ 
#define LM_A_NO_MT_CONNECT	97	/* For backwards compatibility */
#define LM_A_MT_CONNECT		98	/* On Windows only:  default: true 
					 * If false, multi-threaded connect
					 * on Windows not used 
					 */

#define LM_A_USER_EXITCALL_EX			101
#define LM_A_USER_RECONNECT_EX			102
#define LM_A_USER_RECONNECT_DONE_EX		103
#define LM_A_CHECKOUTFILTER_EX			104
#define LM_A_VENDOR_CALLBACK_DATA			105
#define LM_A_CHECKOUTFILTERLAST_EX			106

