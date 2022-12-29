#ident "$Id: tscomm.h,v 1.9 2002/08/08 14:10:02 kfr Exp $"

/**************************************************************************
 *                                                                        *
 *  Copyright (C) 2000 Silicon Graphics, Inc.                             *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 **************************************************************************/


/*
 *   tscomm.h
 *
 *   Define the interface between the personality daemon and the TS driver
 *   and the configuration definition used to identify TS supported devices
 *   in the master.d/scsi file.
 *
 */

#ifndef __SYS_TSCOMM_H_
#define	__SYS_TSCOMM_H_

#include <sys/mtio.h>

#define	TS_DEV_DAEMON		"tsdaem"	/* TS daemon device	      */
#define	TS_DEV_REQUEST		"tsreq"		/* TS request device	      */
#define	TS_DIR_ALIAS		"/hw/tape"	/* Tape aliases		      */

/*
 *   ts_types provides a definition of the table found in master.d/scsi
 *   which lists the devices supported by the Tape Support Driver.
 */
#define	TS_MAX_VENDOR	8
#define	TS_MAX_PRODUCT	16
#define	TS_MAX_DENSITY	8

typedef	struct	ts_types {
	u_char	ts_hinv;
	u_char	ts_vendor[TS_MAX_VENDOR];
	u_char	ts_product[TS_MAX_PRODUCT];
	uint	ts_compress : 1;
	uint	ts_speed    : 1;
	uint	ts_variable : 1;
	uint_t	ts_numdens;
	char	**ts_dens_hwg;
	char	**ts_dens_alias;
	u_char	ts_dens_code[TS_MAX_DENSITY];
} ts_types_t;

extern  ts_types_t  ts_types[];
extern  int     ts_numtypes;
extern	int	tsdebug;


#define	TS_VERSION	1


/*
 *   Ioctl requests
 *
 */
#define	TSIOC_ABORT	1
#define	TSIOC_BLKINFO	2
#define	TSIOC_COPYIN	3
#define	TSIOC_COPYOUT	4
#define	TSIOC_INIT	5
#define	TSIOC_QUERY	6
#define	TSIOC_READY	7
#define	TSIOC_RESUME	8
#define	TSIOC_SEND	9
#define	TSIOC_STOP	10
#define	TSIOC_STATUS	11
#define	TSIOC_STRAT	12
#define	TSIOC_TRACE	13
#define	TSIOC_TABLE	14
#define	TSIOC_LICENSE	15


/*
 *   TSIOC_BLKINFO
 *
 *   Provide the minimum, maximum, and fixed block size during I/O
 *   verification and upon completion of a block size setting on an
 *   I/O request.  They are required by the TS driver to perform I/O
 *   processing.
 *
 */
typedef	struct	tsblkinfo {
	uint_t		ts_minsize;
	uint_t		ts_maxsize;
	uint_t		ts_blksize;
} tsblkinfo_t;


/*
 *   TSIOC_INIT
 *
 *   Provide initial device information to the driver.  This ioctl
 *   will identify the Tape Support System version used by the personality
 *   daemon, provide information which will allow I/O requests to be
 *   performed in the driver, specify a sense buffer location and length
 *   for sense data following an I/O error, and will describe the ioctls
 *   supported and the requirements for support.
 *
 */
typedef	struct	ioclist	{
	uint		ts_cmd;
	u_char		ts_root   : 1,
			ts_kern	  : 1,
			ts_input  : 1,
			ts_output : 1;
	uint_t		ts_argsize;
} ioclist_t;
	

typedef	struct	tsinit {
	ushort		ts_version;
	caddr_t		ts_sense;
	uint_t		ts_senselen;
	uint_t		ts_io_divisor;
	uint_t		ts_min_timeo;
	uint_t		ts_attr;
	uint_t		ts_iocnum;
	ioclist_t	ts_ioclist[1];
} tsinit_t;

/*
 *   No ts_attr flags at this time.
 */
#define	TSA_ALL		0x00000000



/*
 *   TSIOC_LICENSE (Personality Daemon)
 *
 *   Check if this license's MAXDRIVES limit has been reached.
 *
 */

#define	L_MAX_LIC_FEATURE	64
#define	L_MAX_LIC_VERSION	64

typedef	struct	{
	char	ts_feature[L_MAX_LIC_FEATURE];
	char	ts_version[L_MAX_LIC_VERSION];
	int	ts_liccnt;
} ts_license_t;



/*
 *   TSIOC_QUERY (Personality Daemon)
 *
 *   Issued, after receiving a SIGUSR1 signal, to obtain a request from
 *   the TS driver.  The driver signals the personality daemon on system
 *   calls which require device specific processing, when an error is
 *   detected on an I/O request, if the driver requires a status update,
 *   and if the first write must be flushed to tape.
 *
 */
typedef	struct	tscomm {
	short		ts_reqt;	/* Driver request		     */
	uint_t		ts_prop;	/* Device properties		     */
	pid_t		ts_pid;		/* ID of process issuing request     */
	uint_t		ts_cmd;		/* Ioctl request		     */
	int64_t		ts_arg;		/* Ioctl argument		     */
	uchar_t		ts_density;	/* Density command code		     */
	int		ts_openflags;	/* Flags specified on non-stat open  */
	int		ts_errno;	/* errno to return to the user	     */
	uint_t		ts_state;	/* Processing state		     */
	uint_t		ts_curblksz;	/* Current block size		     */
	uint64_t	ts_cblknum;	/* Current calculated block number   */
	uint_t		ts_sensesent;	/* Amount of sense data returned     */
	int		ts_reqcnt;	/* I/O request byte count	     */
	int		ts_resid;	/* Number of bytes not transferred   */
	uint		ts_errha;	/* Host adaptor error code	     */
	uchar_t		ts_errscsi;	/* SCSI error code	 	     */
	uint64_t	ts_readcnt;	/* Number of read commands sent	     */
	uint64_t	ts_writecnt;	/* Number of write commands sent     */
	uint64_t	ts_ioctlcnt;	/* Number of ioctl requests	     */
	uint64_t	ts_bytesread;	/* Number of bytes read	since load   */
	uint64_t	ts_byteswrt;	/* Number of bytes written since load*/
	cap_value_t	ts_cap_effective; /* effective capability	     */
} tscomm_t;

/*
 *   ts_reqt flags.
 *
 *   Specifies the reason for signalling the personality daemon.
 *
 */
#define	TSRQ_OPEN	0x00000001
#define	TSRQ_CLOSE	0x00000002
#define	TSRQ_IOCTL	0x00000004
#define	TSRQ_IOERR	0x00000008
#define	TSRQ_READ	0x00000010
#define	TSRQ_WRITE	0x00000020
#define	TSRQ_WRTPROT	0x00000040

/*
 *   ts_state flags.
 */
#define	TSST_EOD	0x00000001
#define	TSST_EOF	0x00000002
#define	TSST_EOM	0x00000004
#define	TSST_IO		0x00000008
#define	TSST_READ	0x00000010
#define	TSST_WRITE	0x00000020
#define	TSST_RETRY	0x00000040
#define	TSST_SIGNAL	0x00000080
#define	TSST_WRTPROT	0x00000100
#define	TSST_ANSI	0x00000200

/*
 *   ts_prop flags.
 *
 *   Identifies the device properties of the device for which
 *   personality daemon processing is required.
 *
 */
#define	TSPR_STAT	0x00000001	/* Stat device			      */
#define	TSPR_COMPRESS	0x00000002	/* Compression device		      */
#define	TSPR_VARIABLE	0x00000004	/* Variable block device	      */
#define	TSPR_NOREWIND	0x00000008	/* No rewind on close device	      */
#define	TSPR_SILI	0x00000010	/* Suppress illegal length errors     */
#define	TSPR_MIXED_IO	0x00000020	/* Device allows reads after writes   */
					/*   and writes after reads	      */


/*
 *   TSIOC_QUERY (Tape Support Daemon)
 *
 *   On an open request, if a personality daemon does not exist, the TS
 *   daemon will be signalled instead.  The TS daemon will use this ioctl
 *   to get information about the device requiring personality daemon
 *   intervention in order to create the appropriate personality daemon
 *   to process the request.
 *
 */
#define	TS_MAX_DEVNAME	1024
#define	L_MAX_VENDOR	TS_MAX_VENDOR+1
#define	L_MAX_PRODUCT	TS_MAX_PRODUCT+1
#define	L_MAX_DEVNAME	TS_MAX_DEVNAME+1

typedef	struct	tsdmncom {
	dev_t		ts_dev;			    /* Vertex handle of device*/
	char		ts_vendor[L_MAX_VENDOR];   /* Vendor ID of device     */
	char		ts_product[L_MAX_PRODUCT]; /* Product ID of device    */
	char		ts_devfile[L_MAX_DEVNAME]; /* Device request file     */
} tsdmncom_t;


/*
 *   TSIOC_RESUME (Tape Support Daemon)
 *
 *   Resume the user of device 'ts_dev' with the specified errno.
 *
 */
typedef	struct	tsdmnres {
	dev_t		ts_dev;
	int		ts_errno;
} tsdmnres_t;


/*
 *   TSIOC_SEND
 *
 *   Send a device request.
 *
 */
typedef struct	tsreq {
	uint    	ts_flags;	/* Request flags; see below 	  */
	uint     	ts_time; 	/* Timeout in milliseconds   	  */

	/*	scsi request	  				          */
	caddr_t  	ts_cmdbuf;	/* Command buffer 		  */
	uchar_t    	ts_cmdlen;	/* Command buffer length 	  */
	caddr_t		ts_databuf;	/* Data buffer  		  */
	uint		ts_datalen;	/* Data buffer length 		  */
	caddr_t		ts_sensebuf;	/* Sense buffer			  */
	uint		ts_senselen;	/* Sense buffer length 		  */

	/*	return portion 					 	  */
	uint		ts_errha;	/* Host adaptor error code	  */
	uchar_t		ts_errscsi;	/* SCSI error code	 	  */
	uint		ts_datasent;	/* Actual length user data 	  */
	uchar_t		ts_sensesent;	/* Actual length sense data 	  */
} tsreq_t;

/*
 *   ts_flags
 */
#define	TSF_READ	0x00000001	/* Input data from the SCSI bus	  */
#define	TSF_WRITE	0x00000002	/* Output data to the SCSI bus	  */
#define	TSF_IMM		0x00000004	/* Immediate mode command 	  */


/*
 *   TSIOC_STATUS (request device)
 *
 *   Return the status of all or one device.
 *
 */
typedef	struct	tsstat {
	short		ts_all;
	dev_t		ts_dev;
	int		ts_len;
	int		ts_num;
	caddr_t		ts_addr;
} tsstat_t;

typedef	struct	tsstatdev {
	pid_t		ts_pid;			/* Personality daemon PID     */
	short		ts_reqt;		/* Driver request	      */
	char		ts_devfile[L_MAX_DEVNAME]; /* Device default file     */
	mtgetext_t	ts_sts;
} tsstatdev_t;


/*
 *   TSIOC_STOP
 *
 *   Stop all activity on a device and terminate the corresponding personality
 *   daemon or stop the activity on all devices and terminate all personality
 *   daemons and the Tape Support daemon.
 */
typedef	struct	tsstop {
	short	ts_all;
	dev_t	ts_dev;
} tsstop_t;

#endif		/* __SYS_TSCOMM_H_ */
