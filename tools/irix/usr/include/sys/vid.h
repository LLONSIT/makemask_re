#ifndef __SYS_VID_H__
#define __SYS_VID_H__

/*
 * vid.h
 *
 *	common video device driver header file
 *
 * Copyright 1993, Silicon Graphics, Inc.
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics, Inc.;
 * the contents of this file may not be disclosed to third parties, copied or
 * duplicated in any form, in whole or in part, without the prior written
 * permission of Silicon Graphics, Inc.
 *
 * RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to restrictions
 * as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data
 * and Computer Software clause at DFARS 252.227-7013, and/or in similar or
 * successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -
 * rights reserved under the Copyright Laws of the United States.
 *
 * $Revision: 1.16 $
 */

#include <sys/types.h>
#include <sys/poll.h>

#define	DEV_VIDEO	"/dev/vid"

/*
 * ioctls
 */
#define VIDIOC           ('v'<<24|'d'<<16)
#define VIDIOCTL(x)      (VIDIOC|x)
#define VIDIOCTLN(x)     (x & 0xffff)


/* These ioctls only require that an open has been done */
#define VID_GETNUM_BOARDS 		VIDIOCTL(1)
#define VID_GETBOARDINFO		VIDIOCTL(2)
#define VID_SET_DIAG_FLAG		VIDIOCTL(3)
#define VID_ATTACH_BOARD		VIDIOCTL(4)
#define	VID_IS_ATTACHED			VIDIOCTL(5)

/* These require that an attach has been done */
#define	VID_INITIALIZE			VIDIOCTL(10)
#define	VID_DETACH_BOARD		VIDIOCTL(11)

#define	VID_PRIVATE_BASE		VIDIOCTL(1000)

/* flags (struct vid_open->vx_flags) */
#define	VID_DIAG_FLAG			0x0001


/*
 * IOCTL arguments
 */

/* for VID_GETBOARDINFO */
struct vid_getboardinfo_args {
	unsigned int board;		/* board number (contiguous from 0) */
	void *buf;			/* buffer for reply */
	unsigned int len;		/* length of reply (bytes) */
};

#if _MIPS_SIM == _ABI64 && defined(_KERNEL)
struct irix5_vid_getboardinfo_args {
	unsigned int board;	/* board number (contiguous from zero) */
	app32_ptr_t  buf;	/* buffer for reply */
	unsigned int len;	/* max length, length of reply (bytes) */
};
#endif

/* for VID_ATTACH_BOARD */
struct vid_attach_board_args {
	unsigned int board;
	__psint_t vaddr;
};

#if _MIPS_SIM == _ABI64 && defined(_KERNEL)
struct irix5_vid_attach_board_args {
	unsigned int board;
	app32_ptr_t  vaddr;     /* this is a user space address */
};
#endif

/*
 * Structures
 */
struct vid_fncs;
struct vid_info;
struct vid_board;
struct vid_open;
struct vid_data;

/*
 * Is there a use for this?
 */
struct vid_data {
	int junk;
};

/*
 * Video driver structure. One of these for each open board, per process.
 */
struct vid_open {
	pid_t			vx_pid;		/* proc id */
	unsigned int		vx_flags;	/* flags */
	struct vid_board	*vx_board;	/* pointer to board structure */
	unsigned int		vx_devminor;	/* assigned devminor */
};

/*
 * Video board description.
 */
#define VID_INFO_NAME_SIZE	16

struct vid_info {
	char name[VID_INFO_NAME_SIZE];	/* unique name for this video */
	unsigned int length;		/* length of board-specific struct */
};

#if defined(_KERNEL) || defined(_KMEMUSER)
/*
 * Interface to device-dependant video board functions.
 */
struct vid_fncs {
	int (*vb_Info)(struct vid_data *, void *, unsigned int, int *);
	int (*vb_Attach)(struct vid_open *, caddr_t);
	int (*vb_Detach)(struct vid_open *);
	int (*vb_Initialize)(struct vid_open *);
	int (*vb_Private)(struct vid_open *, unsigned long, void *, int *);
	int (*vb_Poll)(struct vid_open *, short, int, struct pollhead **, unsigned int *);
};
#endif

/*
 * Video device structure. One of these for each board.
 */
struct vid_board { 
	short int	vb_index;	/* Identifies the device */
	struct vid_info	*vb_info;	/* Some info about board */
	struct vid_open	*vb_owner;	/* Exclusivity releated, may not need */
	struct vid_fncs	*vb_fncs;	/* Dev dependant fncs */
	struct vid_data	*vb_data;	/* Dev dependant bd data */
};

/*
 * Global data (defined in master.d)
 */
extern struct vid_board *VidBoards[];
extern int VidBoardLimit;
extern struct vid_open *VidDev[];
extern int VidOpenLimit;

/*
 * Board registration (called by each driver's edtinit routine)
 */
int VidRegisterBoard(struct vid_fncs *, struct vid_data *, struct vid_info *);

#endif /* _SYS_VID_H__ */
