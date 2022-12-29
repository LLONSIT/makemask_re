/**************************************************************************
 *									  *
 * 		 Copyright (C) 1995  Silicon Graphics, Inc.		  *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/
#ident "$Revision: 1.112 $"

/***************************************************************************
 *
 *  kdsp_kern.h - Private header file for the KDSP audio driver.
 *  Only device-independent structs should be here.
 *  (application programmer visible kdsp structs are in hdsp.h).
 *  (device-dependent structs go in header files for the device).
 *
 ****************************************************************************/
#include <sys/poll.h>

#ifdef MIN
#undef MIN
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#endif

#ifdef MAX
#undef MAX
#define MAX(a,b) (((a) > (b)) ? (a) : (b))
#endif

#define HRB_DEFAULT	    ((hrb_t *)-2L) /* -2 in conn indicates default RB */
#define HRB_WILDCARD	    ((hrb_t *)-1L) /* -1 arg to connlist_delete is wildcard */
#define HRB_END		    0	/* 0 is list terminator */

#define HDSPMASTER    0
#define HDSPCONTROL   1
#define HDSPCLIENTLOW 2  /* lowest kdsp client minor device number */

typedef struct kdsp_old_param_info_s {
    int param;		    /* the parameter in question */
    int kind;		    /* type of value accepted */
    int min;		    /* minimum value */
    int max;		    /* maximum value */
    int initial;	    /* initial value */
    char *name;		    /* name of the parameter */
} kdsp_old_param_info_t;

typedef struct kdsp_range_info_s {
    hdsp_value_t min;	    /* minimum value */
    hdsp_value_t max;	    /* maximum value */
    hdsp_value_t min_delta; /* minimum delta between two values */
    hdsp_value_t max_delta; /* maximum delta between two values */
    int	special_vals;	    /* special values not in range */
    hdsp_fixed_t steps_per_db;    /* Conversion constant max_step/(max-min), 
			     	   * or 0 if max=min. used for old AL atten compat 
				   * value should be rounded. Only needed on 
				   * input gain ranges.
				   */

    /*
     * dbs_per_step has different interpretations on input & output
     * interfaces. It is a conversion constant for old AL compatibility.
     * On input interfaces, it means "dbs per old AL (AL_*_INPUT_ATTEN) 
     * increment". On output interfaces, it means "dbs per log step,"
     * i.e. it's a multiplier for kdsp_log_table. For a device which
     * behaves exactly as an old-AL MDAC, it should be exactly 20.0.
     */
    hdsp_fixed_t dbs_per_step;	    
    int max_step;	    /* step value corresponding to max atten. Only
			       needed on input interfaces */
    hdsp_value_t del_recip; /* 1/min_delta. Used in dB -> regval conversion */
    hdsp_value_t hw_adj;    /* Addative constant for extra hw gain stages
			     * Used in dB -> regval conversion */
} kdsp_range_info_t;

typedef struct kdsp_param_info_s {
    int param;		    /* the parameter in question */
    char *res_name;	    /* the name of the resource to which this parameter
			       applies, if it applies to only one resource */
    int res_type;	    /* the type of resource to which this parameter applies: this allows one
			       parameter to appear multiple times in a given array, with different resources
			       using different entries */
    short val_type;	    /* the aggregate type of the whole value */
    short elem_type;	    /* the type of each element of the value */
    short max_elems;	    /* the maximum number of elements, for a non-scalar */
    short max_elems2;	    /* the maximum number of elements, for a non-scalar (2nd dim) */
    hdsp_value_t initial;   /* initial value */
    kdsp_range_info_t *range;	/* information on range parameters */
    char *name;		    /* name of the parameter */
    
    /*
     * the following members allow a resource to specify what values
     * are allowed for parameters which take enum & resource types. These
     * are used by the alQuerySet function. get_vlist is an optional pointer
     * to a function which fills in the current set of accepted values for
     * a parameter. This is ideal for parameters whose accepted sets of values vary
     * dynamically. If get_vlist is 0, a default function is called,  which
     * returns the current contents of the "vlist" list. This is the preferred
     * method for parameters whose sets of values are static or mostly static.
     */
    int (*get_vlist)(void *, struct kdsp_param_info_s *, hdsp_value_t *, int);
    hdsp_value_t *vlist;    /* list of accepted values, if enum or resource type */
    int vals;		    /* number of entries in vlist */
    int ops;		    /* supported operations */
} kdsp_param_info_t;


/*
 * Resource
 */
 
typedef int kdsp_resid_t;	/* in case we want to change the resource ID type */

#define HDSPEVENTLOW  256	/* lowest client minor device number for events */

/* 
 * eve_t definition must match that of ALEvent in audio.h 
 * (XXX - need to maintain this in a better way?)
 */

typedef struct eve_s {
    kdsp_resid_t	src;		/* event src */
    kdsp_resid_t	res;		/* registered resource */
    int 		param;	        /* event parameter */
    unsigned long long 	ust;		/* UST */
    hdsp_value_t	value;	        /* event data */
    char                buffer[HDSP_MAX_EVENT_DATA]; /* event data */
} eve_t;

/*
 * Linked list of resources that have a particular evq_t attached to
 * to them.
 */

typedef struct evq_res_s {    
    kdsp_resid_t           res;   
    struct evq_res_s       *next;
} evq_res_t;
      
/* 
 * driver private event que structs
 */

typedef struct evq_s {
    int 		valid;
    int			minordev;
    int                 id;
    int                 nevents;
    evq_res_t           *reslist;       /* linked list to resources */
    long long           mask;           /* paramater mask  */
    int 		qsize;		/* size of the que */
    eve_t		*pevbuf;	/* ptr to the event buffer */
    int 		ip;		/* insertion point */
    int 		rp;		/* removal point */
    int			wakeup_cnt;	/* how many clients waiting in poll */
    struct pollhead 	*php;		/* needed for poll/select */
    sema_t		qlock;		/* lock to protect the que */
} evq_t;

typedef struct kdsp_evqlist_s { 
    long long              mask;       /* parameter mask                   */
    evq_t                  *eventq;    /* event queue attached to resource */
    struct kdsp_evqlist_s  *next;      /* next pointer in the linked list  */
} kdsp_evqlist_t;

#define KDSP_NAMELEN	 32

/*
 * a resource pointer. This establishes a user/subresource relationship between two
 * resources. This is linked into two lists, one maintaining a list
 * of users for the subresource, and one maintaining a list of subresources
 * the user is using.
 */
typedef struct kdsp_rp_s {
    void *parent;
    void *sub;
    struct kdsp_rp_s *next_parent;
    struct kdsp_rp_s *next_sub;
} kdsp_rp_t;

#define KDSP_MAX_SUBS    24  /* arbitrary limit on # potential subresources per res */

typedef struct kdsp_resource_s {
    struct kdsp_resource_s *superclass;	/* pointer to superclass if necessary */

    /*
     * parameter interfaces
     */
    int (*set_params)(struct kdsp_resource_s *,hdsp_pv_t *, int);
    int (*get_params)(struct kdsp_resource_s *,hdsp_pv_t *, int);
    void (*commit_params)(struct kdsp_resource_s *);
    kdsp_param_info_t *params;  /* buffer full of parameter information */
    
    int               evqstatus;
    kdsp_evqlist_t    *evqlist; /* Attached event queues linked list    */
    kdsp_evqlist_t    *defevqlist; /* Attached event queue linked list for defaults */
    unsigned long long param_mask; /* parameter mask for fast event traversal */

    /*
     * subs & parents list which resources this resource is currently
     * using (subs), and which resources are currently using this 
     * resource (parents).
     */
    kdsp_rp_t *subs;		/* resources we're using, if any */
    kdsp_rp_t *parents;		/* our users, if any */
    
    /*
     * avail_subs lists the resources which this resource can potentially
     * use.
     */
    struct kdsp_resource_s *avail_subs[KDSP_MAX_SUBS];
    
    void *subsys;		/* if non-zero, subsystem that owns this
				   resource. really a (kdsp_subsys_t *) */
    int nparams;		/* # entries in parameter buffer */
    kdsp_resid_t id;		/* resource ID */
    int type;			/* type */
    char name[KDSP_NAMELEN];	/* name */
    char label[KDSP_NAMELEN];		/* text label or user alias */
    char default_label[KDSP_NAMELEN];	/* default label -- when the user
					   hasn't specified a label, use this */
    int label_not_unique;	/* 1 if the label is not unique */
    int def_label_not_unique;	/* 1 if the default label is not unique */
} kdsp_resource_t;

/*
 * The following structs are for servicing events generated from the
 * interrupt routine.  
 */
typedef struct kdsp_evqinfo_s {
    kdsp_resource_t   *resource;
    kdsp_param_info_t  pinfo;
    hdsp_pv_t          pv;
}kdsp_evqinfo_t;

typedef struct kdsp_intevq_s {
    int             valid;       /* Indicates if event queue is valid  */
    int             qsize;       /* Size of queue buffer               */
    int             nevents;     /* Number of event requests queued up */
    kdsp_evqinfo_t *bevqinfo;    /* Pointer to event request buffer    */
    int             ip;          /* Insertion point                    */
    int             rp;          /* Removal Point                      */
} kdsp_intevq_t;

/*
 * Resource Map Entry
 * The resource map is a hash table with a linked list of entries for each bucket.
 * It is used for mapping resource IDs to the actual resources.
 * Each linked list is sorted by resource ID.
 */
typedef struct kdsp_resmap_s {
    kdsp_resource_t *res;      	    /* ptr to associated resource */
    struct kdsp_resmap_s *next;	    /* next entry in this hash bucket */
    kdsp_resid_t id;		    /* resource ID */
} kdsp_resmap_t ;

#define KDSP_VERSION_NUMBER 	  6
#define KDSP_MAX_RESOURCES	  256
#define KDSP_RESOURCE_MAP_SIZE    64
#define KDSP_RESOURCE_MAP_MASK    63
#define KDSP_RESOURCE_HASH(x)	  ((x) & KDSP_RESOURCE_MAP_MASK)

/* 
 * The following struct describes what the kdsp driver knows about a ring
 * buffer. We sort the fields by decreasing element size to minimize 
 * the size of the structure; no padding will be required to meet
 * element alignment restrictions.
 */
typedef struct hrb_s {
    kdsp_resource_t res; /* resource information */
    
    /* long longs */
    long long errloc;	 /* location of current error on port */
    long long sampoffset;   /* sample offset of this HRB from reference */
    unsigned long long   msc; /* hardware MSC (@ current DMA pointer) (64 bits) */
    unsigned long long   ust; /* ust at which elapsed changed (64 bits) */
   
    /* longs & pointers */
    rbheader_t *vheader; /* Virtual address of the header part of the hrb   */
    rbheader_t *pheader; /* Physical address of the header part of the hrb  */
    void *vdata;	 /* Virtual address of the data part of the hrb     */
    caddr_t pdata;	 /* Physical address of the data part of the hrb   */
    caddr_t vaddr;	 /* Virtual address of data in user's addr space  */
    void *pend;	 	 /* physical address of end of rb */
    struct hrb_s *master;/* If we are a slave this is our master */
    void *clockgen;	 /* pointer to clock generator for this RB */
    void *clist;	 /* connection list for this HRB */
    int (*pre_connect)(struct hrb_s *, struct hrb_s *);
    int (*post_connect)(struct hrb_s *, struct hrb_s *);
    void (*cg_update_hrb)(struct hrb_s *);  /* called by cg on rate-change */
    void (*get_rb_mscust)(struct hrb_s *, unsigned long long *, unsigned long long *);
    
    /* ints */
    int nlocs;		 /* Number of locations in data part of the hrb   */
    int extra;		 /* Number of extra locations in hrb */
    int nbytes;		 /* Number of bytes in the hrb, including header  */
    int newhdtl;	 /* new head/tail value for this RB after curr intr */
    int refcnt;	    	 /* reference count: # conns into/out of RB */
    int state;		 /* State of the hrb.                             */
    int nchans;	    	 /* Number of interleaved channels in this RB */
    int	frameshift;	 /* shift to convert between samples, frames */
    int drop_samps;	 /* number of samples to drop off head */
    int maplen;		 /* Length of the mmaped region                       */
    int uniqid;		 /* unique sequence number to identify port	      */
    u_int errcnt;	 /* total number of errors on port */
    u_int errtype;	 /* type of error that last occurred on port */
    u_int errlength;	 /* length of current error */
    int dma_latency; 	 /* DMA latency if needs_dma */
    int frames_per_dma;	 /* size of DMA chunk size, in frames */
    int ccomp; 	 	 /* connected component number */
    int frames_to_move;	 /* # frames to move this interrupt */
    int type;		 /* Type of hrb (TOMIPS, FROMMIPS, etc.)   */
    int formatidx;	 /* Data format of hrb */
    int locs_per_frame;	 /* Locations (uints) per frame */
    
    /* chars */
    char dma_active;	 /* True if RB is currently being DMAd from/to */
    char needs_dma;	 /* This hrb requires DMA to service it */
    char errstate;	 /* error state: 1 = error, 0 = no error */
} hrb_t;
    
/*
 *  Moved these pointers here, because kdsp_events.c needs access 
 *  to these pointers.
 */
extern hrb_t *kdsp_default_in ;
extern hrb_t *kdsp_default_out;

typedef struct kdsp_port_s {
    hrb_t hrb;		 /* Port is a subclass of RB */
    pid_t pid;		 /* pid of application using port	     */
    uid_t uid;		 /* real uid of application using port	      */
    struct pollhead pq;  /* Poll queue (for select, poll)                 */
    struct kdsp_port_s *next;  /* Pointer to the next free or allocated hrb struct  */
    int minordev;	 /* Minor device number associated with this hrb. */
    int alversion;	 /* AL version number for this HRB */
    char wakeup;	 /* True if this RB needs a reader/writer woken    */
    kdsp_resid_t connto; /* Connect to this resource upon open */
} kdsp_port_t;

/* 
 * The following defines indicate the state of a host ring buffer.  
 */
#define HRB_WAITING 1

/* 
 * The following macros are convenient ways to query the type of a host ring
 * buffer. 
 */
#define HRB_ISSPLIT(x)		(((x)&HRB_SPLIT)!=0)
#define HRB_ISFROMMIPS(x)	(((x)&HRB_FROMMIPS)!=0)
#define HRB_ISUSERSPACE(x)	(((x)&HRB_USERSPACE)!=0)
#define HRB_ISDIRECT(x)		(((x)&HRB_DIRECT)!=0)
#define HRB_ISMASTER(x)		(((x)&HRB_MASTER)!=0)

#define HRB_ISTOMIPS(x)		(((x)&HRB_FROMMIPS)==0) 
#define HRB_ISKERNELSPACE(x)	(((x)&HRB_USERSPACE)==0)
#define HRB_ISCONTIGUOUS(x)	(((x)&HRB_SPLIT)==0)
#define HRB_ISSERIAL(x)		(((x)&HRB_DIRECT)==0)
#define HRB_ISSLAVE(x)		(((x)&HRB_MASTER)==0)

#define HRB_ISSOURCE(x)		((HRB_ISUSERSPACE(x) && HRB_ISFROMMIPS(x)) | \
				 (HRB_ISKERNELSPACE(x) && HRB_ISTOMIPS(x)))
#define HRB_ISDEST(x)		((HRB_ISUSERSPACE(x) && HRB_ISTOMIPS(x)) | \
				 (HRB_ISKERNELSPACE(x) && HRB_ISFROMMIPS(x)))
#define HRB_ISSUBCODE(x)	(((x)&HRB_SUBCODE)!=0)
#define HRB_ISDATA(x)		(((x)&HRB_SUBCODE)==0)
#define HRB_ISBIGSAMPS(x)	(((x)&HRB_BIGSAMPS)!=0)
#define HRB_ISREGSAMPS(x)	(((x)&HRB_BIGSAMPS)==0)

/*
 * These macros apply to the RB state
 */
#define HRB_ISDORMANT(x)	(((x)&HRB_DORMANT)!=0)
#define HRB_ISACTIVE(x)		(((x)&HRB_DORMANT)==0)

/* 
 * limits 
 */
#define KDSP_MAX_USER_RBS	16	/* maximum number of user HRBs (ports) */
#define KDSP_MAX_CONN		32	/* maximum number of connections */

#define KDSP_MAX_UNIQID	32767	/* max value for a port unique ID */
#define KDSP_MAX_RATES	7	/* number of entries in rate table */

#define KDSP_MAX_DEVICES	64	/* maximum number of devices */
#define KDSP_MAX_FRAMESIZE	16	/* maximum number of channels 
					   per stream */
#define KDSP_MAX_PARAMS		64	/* maximum number of parameters in the system */

/*
 * 404 samples is the absolute minimum for 4-channel operation.
 * The maximum number of frames per 2 ms is 100, frame size is 4,
 * and there needs to be one extra sample frame in the ring buffer.
 */
#define AUDIOKERNBUFSIZE 404	
#define HDSPSPRI (PZERO-1)

#define KDSP_CLOCK_SYNC		0
#define KDSP_RBDRAIN_SYNC	1
#define KDSP_RBFILL_SYNC	2
#define KDSP_DELETED		-1

typedef void (*kdsp_tfunc_t)();

/*
 * Master Clock
 */
typedef struct kdsp_mclk_s {
    kdsp_resource_t res;
    hdsp_fixed_t rate;		    /* master clock rate, in Hz */
    void (*update)(struct kdsp_mclk_s *);   /* cause mclk to update its state */
    char unlocked;		    /* non-zero if PLL unlocked */
} kdsp_mclk_t;
 
/*
 * The following struct describes a clock generator.
 * Functions must be provided for device specific operations.
 */

typedef struct kdsp_clockgen_s {
    kdsp_resource_t res;
    void (*mclk_update_cg)(struct kdsp_clockgen_s *, int); /* called by mclk on state-change */
    hdsp_fixed_t rate;		    /* sample rate for this entry, if known in Hz */
    hdsp_fixed_t old_rate;	    /* Used for mantaining state information for events */
    int rate_frac_n;		    /* rate-fraction numerator */
    int old_rate_frac_n; 	    /* Used for mantaining state information for events */
    int rate_frac_d;		    /* rate-fraction denominator */
    int old_rate_frac_d;	    /* Used for mantaining state information for events */
    hrb_t *syncsource;		    /* synced to what RB? (if synced to RB) */
    kdsp_mclk_t *mclk;		    /* master clock currently in use */
    kdsp_mclk_t *old_mclk;	    /* Used for mantaining state information for events */
    int	servoframes;		    /* # frames to keep buffered on an output synced to this */
    int	inuse;			    /* is this rate in use? */
    int	synctype;		    /* synced to RB or unix clock? */
    struct kdsp_clockgen_s *next;
} kdsp_clockgen_t;

/*
 * The following struct defines the information required for a single
 * HRB->HRB connection. Note that a connection goes "from" an output
 * port (input device) "to" an input port (output device).
 * A connection belongs to three lists: the connection list, which 
 * contains all active connections; a list of connections out of the
 * output port to which this is connected; and a list of connections 
 * out of the input port to which this is connected.
 */
typedef struct kdsp_connection_s {
    kdsp_resource_t res;		/* connection is a resource */
    hrb_t *in;				/* input port */
    hrb_t *out;				/* output port */
    kdsp_tfunc_t t_func;		/* transfer func: e.g. copy or mix? */
    struct kdsp_connection_s *next;	/* next free or used conn */
    struct kdsp_connection_s *prev;	/* previous free or used conn */
    struct kdsp_connection_s *next_i;	/* next conn @ input port */
    struct kdsp_connection_s *prev_i;	/* prev conn @ input port */
    struct kdsp_connection_s *next_o;	/* next conn @ output port */
    struct kdsp_connection_s *prev_o;	/* prev conn @ output port */
    kdsp_resource_t *associated_with;	/* if this connection is scheduled to go away
					   when associated_with goes away */
    unsigned int flags;			/* various flags (see below for defs) */
    int isolate;
    int formatidx;			/* data format of connection */
} kdsp_connection_t;

/*
 * values for connection flags
 */

#define KDSP_MIX       		0x1	/* conn should mix */
#define KDSP_COPY       	0x0	/* conn should copy */
#define KDSP_CLIP		0x2	/* conn should clip */
#define KDSP_MONO_LEFT		0x4	/* conn is mono, left channel only */
#define KDSP_WDEFAULT		0x100	/* writer is default */
#define KDSP_RDEFAULT		0x200	/* reader is default */
#define KDSP_REFUSED		0x400	/* connection refused */

/*
 * The following struct defines a "list-of-connections" type.
 */
typedef struct kdsp_connlist_s {
    kdsp_connection_t conns[KDSP_MAX_CONN];	/* array of conns */
    kdsp_connection_t *firstused;		/* first used conn */
    kdsp_connection_t *firstfree;		/* first free conn */
    int numconns;				/* number of conns */
} kdsp_connlist_t;

/* 
 * The following struct describes an audio subsystem (e.g. a 
 * particular board),  which can support multiple devices. 
 * Typically a subsystem corresponds with a particular device-dependent
 * driver.
 */
typedef struct kdsp_subsys_s {
    kdsp_resource_t res;			    /* resource */
    int  (*probe)(void);			    /* probe for existence of subsys */
    int (*init)(struct kdsp_subsys_s *);	    /* initialize subsys */
    void (*shutdown)(struct kdsp_subsys_s *);	    /* shut down & remove resources */
    void (*pre_trans_ops)(struct kdsp_subsys_s *);  /* per-interrupt update */
    void (*halt_intr_ops)(struct kdsp_subsys_s *);
    void (*reset)(struct kdsp_subsys_s *);	    /* for old-style subsys compat */
    int (*activate)(struct kdsp_subsys_s *);	    /* for old-style subsys compat */
    void (*set_ust_offset)(struct kdsp_subsys_s *, unsigned long long);    /* set offset from "master" UST  */
    void (*enable_ust)(struct kdsp_subsys_s *);	    /* UST providers enable output  */
    void (*disable_ust)(struct kdsp_subsys_s *);	    /* UST providers disable output */
    void (*reset_ust)(struct kdsp_subsys_s *);	    /* UST listeners reset UST & listen */
    hdsp_value_t (*initial_val)(kdsp_resource_t *, kdsp_param_info_t *);    /* For proper pinfo.initial reporting */
    void *default_in;				    /* default input for this subsystem */
    void *default_out;				    /* default output for this subsystem */
    struct kdsp_subsys_s *next;
    int needs_intr;                 /* non-0 if non-clist interrupts are needed */
    int default_pri;				    /* priority of this subsystem. Lower number
						       means more likely to become the system default */
} kdsp_subsys_t;

/* 
 * The following struct describes a physical audio device.  
 * Functions must be provided for device specific operations.
 */

typedef struct kdsp_device_s {
    hrb_t hrb;						/* Device is a subclass of RB */
    
    void (*pre_trans_ops)(struct kdsp_device_s *);
    void (*post_trans_ops)(struct kdsp_device_s *);
    int  (*start_dma)(struct kdsp_device_s *);
    void (*stop_dma)(struct kdsp_device_s *);
    
    /*
     * some devices need a fixed amount of extra buffering 
     * beyond the (sample-rate-dependent) number of frames
     * required to absorb interrupt latency. If extra_buf_samps
     * is non-zero, it's the number of extra samples this 
     * device requires.
     */
    int extra_buf_samps;
    int does_limiting;					/* true if output device limits 
							   audio to 24 bits */
    
    kdsp_subsys_t *subsys;				/* subsystem used by this device */
    struct kdsp_device_s *next;				/* next device in global list */
    
    /*
     * interface stuff
     */
    void *interface;					/* i/f in use */
    void *subcode;					/* first subcode struct in list */
} kdsp_device_t;

/* 
 * The following struct describes a physical interface resource.
 * A physical interface represents the section of a device which
 * gets the signal to the outside world. Since a device can have 
 * multiple of these, and in some cases,  they can be shared between
 * devices, it's a separate resource.
 */
typedef struct kdsp_interface_s {
    kdsp_resource_t res;	   /* Interface is a subclass of resource */
    kdsp_device_t *device;	   /* Device to which the interface belongs */
    int wordsize;		   /* Wordsize, in bits */
} kdsp_interface_t;

/*
 * typedef for kdsp timing statistics information block.
 */
typedef struct kdsp_stats_s {
    int max_time;
    int breadcrumbs;	    	    /* not currently used */
    int max_delta;
    int sum_delta;
    int num_delta;
    int sum_time;
    int num_time;
    int lateintr;
    int maxmax;			    /* not currently used */
    int misc[8];
} kdsp_stats_t;

#define KDSP_BREADCRUMBS_IN_TIMERCALLBACK 	(1 << 31)
#define KDSP_BREADCRUMBS_IN_TIMEPOKE 		(1 << 30)
#define KDSP_BREADCRUMBS_IN_IOCTL 		(1 << 29)

typedef struct kdsp_subcode_s {
    kdsp_device_t *subcode_dev;         /* unmapped device handling subcode rb*/
    kdsp_device_t *data_dev;		/* device subcode belongs to */
    unsigned char *default_sc;		/* default in/out subcode frame */
    unsigned char *olddefault_sc;	/* default in/out subcode frame */
    unsigned char *intr_default;        /* ptr to 1 of the above for intr proc*/
    unsigned char *user_default;        /* ptr to 1 of the above for user proc*/
    void *next;				/* Next subcode struct in list */
    int formattype;			/* Subcode format */
    int interval;			/* MSC ticks per block */
    int chansize;			/* # of bytes per subcode channel */
    int nbytes;                         /* # of bytes for 1 full subcode frame*/
    sema_t sema;			/* special user/intr sema4 on sc read */
    int wakeflag;			/* special user/intr flag for sc read */
    unsigned int flags;			/* general purpose flags */
    char needs_data_on;			/* 1 if data dma needs to be on too */
} kdsp_subcode_t;


extern unsigned char kdsp_byte_flip[];
#define KDSP_FLIP8(res,word)   (res) = kdsp_byte_flip[(word)]
#define KDSP_FLIP32(res,word)  \
        ((char *)&(res))[3] = kdsp_byte_flip[((char *)&(word))[0]]; \
        ((char *)&(res))[2] = kdsp_byte_flip[((char *)&(word))[1]]; \
        ((char *)&(res))[1] = kdsp_byte_flip[((char *)&(word))[2]]; \
        ((char *)&(res))[0] = kdsp_byte_flip[((char *)&(word))[3]]


/* Flags specific to subcode */
#define HDSP_SUBCODE_NEW_DEFAULT_FRAME 		(1<<0)
#define HDSP_SUBCODE_XFER_IN_PROGRESS  		(1<<1)
#define HDSP_SUBCODE_NEW_AES_RATE		(1<<2)
#define HDSP_SUBCODE_AES_RATE_XFER_IN_PROGRESS  (1<<3)
#define HDSP_SUBCODE_UNLOCKED                   (1<<4)


/* Subcode defines */
#define KDSP_ADAT_FRAMESIZE 1
#define KDSP_AES_FRAMESIZE 6
#define MULTBY6(x)  (((x) << 1) + ((x) << 2))

/*
 * If these #defined values change then a bug might be created in
 * what /var/sysgen/mtune/kdsp expects for its kdsp_pro_audio_subcode
 * valid values.
 */
#define KDSP_MTUNE_SUBCODE_HW_DEFAULT	2
#define KDSP_MTUNE_SUBCODE_PRO	1
#define KDSP_MTUNE_SUBCODE_CONS	0

/* mtune-able kernel variables */
extern int kdsp_pro_audio_subcode;

/* Flags representing reasons to turn interrupts on */
#define HDSP_INTR_AES_PASSTHRU			(1<<0)
#define HDSP_INTR_GET_SUBCODE			(1<<1)
#define HDSP_INTR_SET_SUBCODE			(1<<2)


/*
 * Client locks state 
 */
#define HDSP_CLIENT_NOT		(-3)	/* not a valid client */
#define HDSP_CLIENT_UNOPENED	(-2)	/* not opened */
#define HDSP_CLIENT_OPENED	(-1)	/* opened but unmapped */
#define HDSP_CLIENT_MAPPED	(0)	/* mapped */

/*
 * transfer functions.
 * all of these take a source, a target, and a number of frames to
 * transfer, except fastclip, which takes a target and a number of samples
 * to clip. 
 */

extern void fastcopy(void*, void*, int, int, int);

extern void fastcopyl22(void*, void*, int);
extern void fastmix22(void*, void*, int);
extern void fastmixl22(void*, void*, int);
extern void fastmixclip22(void*, void*, int);
extern void fastmixclipl22(void*, void*, int);
extern void fastcopyclip22(void*, void*, int);

extern void fastclip(void *, int);

extern void fastcopyl44(void*, void*, int);
extern void fastmix44(void*, void*, int);
extern void fastmixl44(void*, void*, int);
extern void fastmixclip44(void*, void*, int);
extern void fastcopyclip44(void*, void*, int);
extern void fastmixclipl44(void*, void*, int);

extern void fastcopy24(void*, void*, int);
extern void fastmix24(void*, void*, int);
extern void fastcopyl24(void*, void*, int);
extern void fastmixclip24(void*, void*, int);
extern void fastcopyclip24(void*, void*, int);

extern void fastcopy42(void*, void*, int);
extern void fastcopyl42(void*, void*, int);
extern void fastmix42(void*, void*, int);
extern void fastmixclip42(void*, void*, int);
extern void fastcopyclip42(void*, void*, int);

extern void fastcopy84(void*, void*, int);
extern void fastcopy82(void*, void*, int);
extern void fastmix88(void*, void*, int);
extern void fastmix84(void*, void*, int);
extern void fastmix82(void*, void*, int);

extern void fastcopy28(void*, void*, int);
extern void fastcopy48(void*, void*, int);
extern void fastmix28(void*, void*, int);
extern void fastmix48(void*, void*, int);

extern void fastcopyclip88(void*, void*, int);
extern void fastmixclip88(void*, void*, int);

extern void fastcopy2_16(void*, void*, int);
extern void fastmix2_16(void*, void*, int);
extern void fastcopy4_16(void*, void*, int);
extern void fastmix4_16(void*, void*, int);
extern void fastcopy8_16(void*, void*, int);
extern void fastmix8_16(void*, void*, int);
extern void fastcopyclip8_16(void*, void*, int);
extern void fastmixclip8_16(void*, void*, int);
extern void fastcopy16_2(void*, void*, int);
extern void fastmix16_2(void*, void*, int);
extern void fastcopy16_4(void*, void*, int);
extern void fastmix16_4(void*, void*, int);
extern void fastcopy16_8(void*, void*, int);
extern void fastmix16_8(void*, void*, int);
extern void fastcopyclip16_8(void*, void*, int);
extern void fastmixclip16_8(void*, void*, int);
extern void fastmix16_16(void*, void*, int);
extern void fastcopyclip16_16(void*, void*, int);
extern void fastmixclip16_16(void*, void*, int);

/*
 * ADAT subcode transfer functions
 */
extern void adatcopy(void*, void*, int, int, int);

/*
 * AES subcode tranfer functions
 */
extern void aescopy(void*, void*, int, int, int);

extern void aescopy1_2(void*, void*, int);
extern void aescopy1_4(void*, void*, int);
extern void aescopy1_8(void*, void*, int);
extern void aescopy1_16(void*, void*, int);
extern void aescopy2_1(void*, void*, int);
extern void aescopy2_4(void*, void*, int);
extern void aescopy2_8(void*, void*, int);
extern void aescopy2_16(void*, void*, int);
extern void aescopy4_1(void*, void*, int);
extern void aescopy4_2(void*, void*, int);
extern void aescopy4_8(void*, void*, int);
extern void aescopy4_16(void*, void*, int);
extern void aescopy8_1(void*, void*, int);
extern void aescopy8_2(void*, void*, int);
extern void aescopy8_4(void*, void*, int);
extern void aescopy8_16(void*, void*, int);
extern void aescopy16_1(void*, void*, int);
extern void aescopy16_2(void*, void*, int);
extern void aescopy16_4(void*, void*, int);
extern void aescopy16_8(void*, void*, int);

void kdsp_timercallback(void);

/*
 * Functions available to DI & DD routines both
 */

void  kdsp_set_param_info(kdsp_resource_t *);

void hrb_usercreate(int nlocs, int type, int minordev);
int  kdsp_destroy_port(int);

int kdsp_create_device(kdsp_device_t *dev, int nlocs,int type,int dcache,void *split,int nchans, int formattype);
void kdsp_destroy_device(kdsp_device_t *dev);
kdsp_connection_t *kdsp_connect(hrb_t *, hrb_t *, int, int, int);

int  connlist_delete(hrb_t *, hrb_t *);
int  connlist_reconnect(hrb_t *, hrb_t *, hrb_t *, hrb_t *);
int  connlist_reconfig(hrb_t *, hrb_t *, int, int);
void connlist_init(void);

void kdsp_set_default_input(hrb_t *dev);
void kdsp_set_default_output(hrb_t *dev);

int kdsp_map_resource(kdsp_resource_t *ptr, int force_id);
int kdsp_unmap_resource(kdsp_resid_t id);
void kdsp_change_resource(int id, kdsp_resource_t *res);
void kdsp_init_resource(kdsp_resource_t *res, int type, char *name, char *label, void *subsys, void *template, int nbytes);
kdsp_resource_t *kdsp_find_resource(kdsp_resid_t id);
kdsp_resource_t *kdsp_find_resource_in_list(kdsp_resid_t id, kdsp_resource_t **l, int nres);
int kdsp_is_subtype(int ta, int tb);

void kdsp_add_subsys(kdsp_subsys_t *, int);
void kdsp_set_default_subsys_pri(kdsp_subsys_t *,  int);
void kdsp_add_device(kdsp_subsys_t *, kdsp_device_t *);

void kdsp_select_interface(kdsp_device_t *, kdsp_interface_t *);
void kdsp_select_clockgen(hrb_t *, kdsp_clockgen_t *);
void kdsp_select_mclk(kdsp_clockgen_t *, kdsp_mclk_t *);
int kdsp_add_subresource(kdsp_resource_t *, kdsp_resource_t *);
int kdsp_delete_subresource(kdsp_resource_t *, kdsp_resource_t *);

int kdsp_reduce_frac(long long n, long long d, int *num, int *den, int limit);
hdsp_fixed_t kdsp_aes_cs_to_hz(unsigned char *csbytes);
void kdsp_hz_to_aes_cs(hdsp_fixed_t r, unsigned char *csbytes);

void kdsp_update_cg_users(kdsp_clockgen_t *);
void kdsp_update_mclk_users(kdsp_mclk_t *mclk);
void kdsp_mclk_update_cg(kdsp_clockgen_t *, int);

void kdsp_writeback_rb(kdsp_device_t *dev);

int kdsp_set_channels(hrb_t *, int);

int kdsp_list_avail_subs(void *v, kdsp_param_info_t *pi, hdsp_value_t *params, int i);

void kdsp_create_subcode(kdsp_subcode_t *sc, kdsp_device_t *datadev, kdsp_device_t *scdev, int fmt);
void kdsp_destroy_subcode(kdsp_subcode_t *sc);
void kdsp_set_aes_rate_bits(kdsp_subcode_t *sc, hdsp_fixed_t rate);
void kdsp_set_default_subcode(kdsp_subcode_t *sc, hdsp_pv_t *p, int userspace);
void kdsp_get_default_subcode(kdsp_subcode_t *sc, hdsp_pv_t *p, int userspace);
int  kdsp_update_default_subcode(kdsp_subcode_t *sc);
int kdsp_db_gain_to_regval(hdsp_fixed_t gain, kdsp_interface_t *itf, int loudlow);
hdsp_fixed_t kdsp_regval_to_db_gain(int regval, kdsp_interface_t *itf, int loudlow);



int kdsp_compare_values(kdsp_resource_t *, hdsp_pv_t *, hdsp_pv_t *, 
			       kdsp_param_info_t **);
int kdsp_pv_list_op(kdsp_resource_t *res, hdsp_pv_t *pbp, int nparms, int cmd, int userspace);
int kdsp_pv_op(kdsp_resource_t *res, int cmd, hdsp_pv_t *pbp, int userspace, kdsp_resource_t *res_list[], int nres); 
kdsp_param_info_t *kdsp_find_param_info(kdsp_resource_t *res, int param);
hdsp_value_t kdsp_initial_val(kdsp_resource_t *res, kdsp_param_info_t *pinfo);

/*
 * old-to-new and new-to-old gain conversion routines.
 * These are exposed mainly for indigo_dd, which internally uses
 * the old-style ones since they are just register values for that platform.
 */
int kdsp_db_gain_to_old_atten(kdsp_resource_t *itf,hdsp_fixed_t gain);
hdsp_fixed_t kdsp_old_atten_to_db_gain(kdsp_resource_t *itf,int atten);
int kdsp_db_gain_to_old_gain(kdsp_resource_t *itf, hdsp_fixed_t gain);
hdsp_fixed_t kdsp_old_gain_to_db_gain(kdsp_resource_t *itf,int gain);

/*
 * Macro for excluding OUR interrupt routine
 * We use sleeping locks when the ONEms timeout is an xthread.
 * Where that is not supported, we use spl's.
 */
#ifdef AUDIO_TIMEOUT_IS_THREADED
/*  Global lock used by di and dd layers. Declared in kdsp_di.c */
extern mutex_t kdsp_lock;     
#   define BLOCK_INTR  mutex_lock(&kdsp_lock, PLTWAIT);
#   define ENABLE_INTR mutex_unlock(&kdsp_lock);
#else
#   define BLOCK_INTR s=splprof()
#   define ENABLE_INTR splx(s)
#endif

/*
 * Macro for excluding ALL interrupts. 
 * This is used where you REALLY want to block interrupts on
 * the cpu you are running on for making timing measurments
 * and such. It is not used (and won't work) to lock kdsp data
 * structures during modification. Use sparingly please.
 */
#define BLOCK_INTRS s=splprof()
#define ENABLE_INTRS splx(s)

/*
 * functions for fetching and putting external values, potentially from
 * userspace.
 */
void *kdsp_fetch_external(hdsp_pv_t *pv, void *local, int maxsize, int unitsize, int userspace);
int kdsp_put_external(hdsp_pv_t *pv, void *source, int maxsize, int unitsize, int userspace);
void *kdsp_fetch_external_string(hdsp_pv_t *pv, char *string, int maxsize, int userspace);
int kdsp_put_external_string(hdsp_pv_t *pv, char *string, int userspace);

hdsp_fixed_t kdsp_fixedmult(hdsp_fixed_t a, hdsp_fixed_t b);

#ifdef EVEREST
#define KVTOPHYS(xxx) kdsp_evkvtophys(xxx)
void *kdsp_evkvtophys(void *kv);
#else
#define KVTOPHYS(xxx) kvtophys(xxx)
#endif

#if defined(EVEREST) || defined(SN0) || defined(IP30)	/* really if has cache-coherent DMA */
#define CACHE_WB_INVAL(addr, len)
#define CACHE_WB(addr, len)
#define CACHE_INVAL(addr, len)
#define WB_DMADES(hs)
#elif defined(IP32)
#define CACHE_WB(addr, len) 		dki_dcache_wb((addr), (len))
#define CACHE_INVAL(addr, len)		dki_dcache_inval((addr), (len))
#define CACHE_WB_INVAL(addr, len)	dki_dcache_wbinval((addr), (len))
#define WB_DMADES(hs) dki_dcache_wb((hs)->dmades_start, HAL2_DMADES_BLOCKSIZE)
#else
/*
 * macros and declarations for cache operations
 */
#ifndef IP32
extern void __dcache_wb_inval(void *, int);
extern void __dcache_inval(void *, int);
extern void __dcache_wb(void *, int);
#endif

#define CACHE_WB_INVAL(addr, len) __dcache_wb_inval((addr), (len))
#define CACHE_WB(addr, len) __dcache_wb((addr), (len))
#define CACHE_INVAL(addr, len)	__dcache_inval((addr), (len))
#define WB_DMADES(hs) __dcache_wb((hs)->dmades_start, HAL2_DMADES_BLOCKSIZE)
#endif



