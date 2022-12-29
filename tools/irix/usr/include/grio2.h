/**************************************************************************
 *									  *
 *               Copyright (C) 2003, Silicon Graphics, Inc.               *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 **************************************************************************/

#ifndef _GRIO2_H_
#define _GRIO2_H_

/*
 * SGI Guaranteed Rate IO Version 2
 * Public userspace API
 * usr/include/grio2.h
 *
 */

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * GRIOv2 parameter indicies
 */
 
#define GR_PARAM_GRIO_INSTALLED	   0 /* param points to an int, 0 = not installed */

/*
 * GRIOv2 types
 */

typedef struct {
    unsigned char	__gr_bits[16];
} grio_uuid_t;

typedef grio_uuid_t	grio_stream_id_t;	/* cluster unique stream id   */
typedef grio_uuid_t	grio_fs_id_t;		/* filesystem id	      */
typedef cell_t		grio_cell_t;		/* client cell id	      */
typedef uint64_t	grio_ticket_t;		/* opaque request ticket      */
typedef int		grio_descriptor_t;	/* userspace file descriptor  */
typedef int32_t		grio_counter_t;		/* counters/histogram buckets */
typedef off_t		grio_off_t;		/* bytes		      */
typedef uint64_t	grio_msecs_t;		/* milliseconds		      */
typedef uint64_t	grio_usecs_t;		/* microseconds		      */
typedef off_t		grio_bandwidth_t;	/* bytes/second		      */
typedef time_t		grio_time_t;		/* seconds since epoch	      */
typedef size_t		grio_size_t;		/* size_t bytes		      */
typedef dev_t		grio_dev_t;		/* grio managed devices	      */
typedef pid_t		grio_pid_t;		/* process id		      */

/*
 * Integer type primitives. These are just aliases for whatever is
 * the most natural, native definition on the current platform.
 */
typedef int16_t		grio_int16_t;
typedef uint16_t	grio_uint16_t;
typedef int32_t		grio_int32_t;
typedef uint32_t	grio_uint32_t;
typedef int64_t		grio_int64_t;
typedef uint64_t	grio_uint64_t;

/*
 * Before retrieving histograms of a given class from the kernel
 * (eg. gr_service_time) an application should first query the kernel
 * for the properties of the class using grio_qos_get_hist_desc().
 *
 * This call returns the histogram size and range, and allows an
 * application to pre-allocate a buffer of the correct length.
 *
 * The properties of a particular class of histograms remain constant
 * after boot. Applications need only query this information once for
 * each distinct class of histogram they wish to retrieve.
 *
 * The histogram and info structures are defined below.
 * They are interpreted as follows:
 *
 * gr_buckets:  +--+--+--+--+--+--   --+--+--+--+--+--+
 *              |  |  |  |  |  |  ...  |  |  |  |  |  |
 *              +--+--+--+--+--+--   --+--+--+--+--+--+
 * underflow ---^  ^-- gr_lo_val       gr_hi_val --^  ^-- overflow
 * bucket                                                 bucket
 *              <------------- gr_nbkts -------------->
 *
 * gr_buckets[0] and gr_buckets[gr_nbkts-1] are used as overflow
 * buckets that count samples lying outside the histogram range
 * [gr_lo_val, gr_hi_val]. Actual histogram data is stored in the
 * remainder of the array: gr_buckets[1..gr_nbkts-2].
 *
 */

#define GRIO_STREAM_ID_ALL NULL

typedef enum {
    gr_service_time = 1
} grio_qos_hist_type_t;

typedef struct grio_qos_hist_desc {
    grio_int32_t	gr_nbkts;	/* number of buckets		      */
    grio_int64_t	gr_lo_val;	/* lowest counted value		      */
    grio_int64_t	gr_hi_val;	/* highest counted value	      */
} grio_qos_hist_desc_t;

typedef struct grio_qos_hist {
    grio_stream_id_t	gr_stream_id;	/* stream_id			      */
    grio_counter_t	gr_buckets[1];	/* histogram buckets		      */
} grio_qos_hist_t;

typedef struct grio_qos_metrics {
    grio_int64_t	av;		/* current (moving) average	      */
    grio_int64_t	min;		/* min observed			      */
    grio_int64_t	max;		/* max observed			      */
} grio_qos_metrics_t;

/*
 * GRIOv2 QoS Monitoring: in-kernel bandwidth/service time
 * moving-averages
 *
 * GRIOv2 maintains in-kernel, per-stream moving averages for
 * delivered bandwidth and io service time over a number of different
 * timescales.
 *
 * Moving averages are retrieved from the kernel using
 * grio_qos_get_interval_stats() which returns an array of
 * grio_qos_interval_t structures defined below.
 *
 * The structure is interpreted as follows. The interval over which
 * the moving average is computed is specified as either a count or a
 * time: if specified as a count the GR_QOS_COUNTED flag is set and
 * gr_count stores the number of samples; if it is specificied as a
 * time the GR_QOS_TIMED flag is set and gr_msecs contains the length
 * of the interval in milliseconds. One of these two flags is always
 * set.
 *
 * The GR_QOS_ACTIVE flag idicates that the current moving averages
 * (gr_bw.av and gr_io.av) are valid. Otherwise, if the metrics could
 * not be updated for the last IO the flag is cleared and the
 * gr_inactive counter is incremented. gr_inactive counts the number
 * of samples since the QoS monitoring was activated that the metrics
 * could not be computed. Note that even if the current moving average
 * was not valid at the last sample, the min/max values are always
 * valid.
 */
#define GR_QOS_COUNTED	0x01	
#define GR_QOS_TIMED	0x02
#define GR_QOS_ACTIVE	0x04

typedef struct grio_qos_interval {
    grio_int32_t	gr_flags;	/* interval type/other flags	      */
    grio_uint32_t	gr_count;	/* qos monitoring interval as a count */
    grio_msecs_t	gr_msecs;	/* qos monitoring interval as a time  */
    grio_int32_t	gr_inactive;	/* num ios qos metrics were inactive  */
    grio_qos_metrics_t	gr_bw;		/* bandwidth			      */
    grio_qos_metrics_t	gr_io;		/* io service time		      */
} grio_qos_interval_t;

/* get_streams */
#define GR_WAIT         0x01		/* wait for streams to change	      */

/* grio_reserve[_fd] */
#define GR_STATIC       0x02		/* make a static bandwidth allocation */

#define grio_errno	errno

#define GRIO_ID_LEN	(36+1)          /* the length including terminating '\0' 
                                           for a uuid in string form */

#ifndef GRIO2_RTL

/* 
 * Interfaces for implicit linking to grio2 (app links with grio2).
 */

extern int grio_query_param(int index, void *param);

/*
 * stream manipulation
 */

extern int grio_avail(const char *fs, grio_off_t *bytes, grio_msecs_t *msecs);
extern int grio_reserve(const char *path,
		grio_off_t *bytes, grio_msecs_t *msecs, int flags,
		grio_stream_id_t *stream_id);
extern int grio_reserve_fd(grio_descriptor_t fd,
		grio_off_t *bytes, grio_msecs_t *msecs, int flags,
		grio_stream_id_t *stream_id);
extern int grio_bind(grio_descriptor_t fd, grio_stream_id_t *stream_id);
extern int grio_unbind(grio_descriptor_t fd);
extern int grio_modify(grio_stream_id_t *stream_id,
		grio_off_t *bytes, grio_msecs_t *msecs, int flags);
extern int grio_release(grio_stream_id_t *stream_id);


/*
 * monitoring and quality-of-service
 */
extern int grio_get_stream(grio_descriptor_t fd, grio_stream_id_t *stream_id);
extern int grio_get_streams(grio_stream_id_t *stream_ids, int nelements,
		int flags, int *num);
extern int grio_qos_get_hist_desc(grio_qos_hist_type_t type,
		grio_qos_hist_desc_t *desc);
extern int grio_qos_get_hist(grio_stream_id_t *stream_id,
		grio_qos_hist_type_t type,
		void *buf, grio_size_t len, int *num);
extern int grio_qos_get_interval_stats(grio_stream_id_t *stream_id,
		grio_qos_interval_t *stats,
		int nelements, int *num);
extern int grio_qos_reset(grio_stream_id_t *stream_id);
extern int grio_qos_reinit(grio_stream_id_t *stream_id,
		const char *interval_spec);

/*
 * UUID manipulation
 */
extern int grio_id_from_string(const char *str_uuid, grio_uuid_t *uuid);
extern int grio_id_to_string(grio_uuid_t *id, char str_uuid[GRIO_ID_LEN]);
extern int grio_id_is_equal(const grio_uuid_t *uuid1, const grio_uuid_t *uuid2);

#else /* GRIO2_RTL */

/* 
 * Define GRIO2_RTL if using the grio2rtl support library for 
 * explicit runtime loading and linking the real grio2 library -
 * if it is installed.
 *
 */

typedef int (*__grio_errno_fptr_t)(void);

typedef int (*grio_query_param_fptr_t)(int index, void *param);
typedef int (*grio_avail_fptr_t)(const char *fs, 
		grio_off_t *bytes, grio_msecs_t *msecs);
typedef int (*grio_reserve_fptr_t)(const char *path, 
		grio_off_t *bytes, grio_msecs_t *msecs, 
		int flags, grio_stream_id_t *stream_id);
typedef int (*grio_reserve_fd_fptr_t)(grio_descriptor_t fd,
		grio_off_t *bytes, grio_msecs_t *msecs, int flags,
		grio_stream_id_t *stream_id);
typedef int (*grio_bind_fptr_t)(grio_descriptor_t fd, 
	    	grio_stream_id_t *stream_id);
typedef int (*grio_unbind_fptr_t)(grio_descriptor_t fd);
typedef int (*grio_modify_fptr_t)(grio_stream_id_t *stream_id,
	    	grio_off_t *bytes, grio_msecs_t *msecs, int flags);
typedef int (*grio_release_fptr_t)(grio_stream_id_t *stream_id);

typedef int (*grio_get_stream_fptr_t)(grio_descriptor_t fd,
		grio_stream_id_t *stream_id);
typedef int (*grio_get_streams_fptr_t)(
		grio_stream_id_t *stream_ids, int nelements,
		int flags, int *num);
typedef int (*grio_qos_get_hist_desc_fptr_t)(grio_qos_hist_type_t type,
		grio_qos_hist_desc_t *desc);
typedef int (*grio_qos_get_hist_fptr_t)(grio_stream_id_t *stream_id,
		grio_qos_hist_type_t type,
		void *buf, grio_size_t len, int *num);
typedef int (*grio_qos_get_interval_stats_fptr_t)(
		grio_stream_id_t *stream_id, grio_qos_interval_t *stats,
		int nelements, int *num);
typedef int (*grio_qos_reset_fptr_t)(grio_stream_id_t *stream_id);
typedef int (*grio_qos_reinit_fptr_t)(grio_stream_id_t *stream_id,
		const char *interval_spec);
typedef int (*grio_id_from_string_fptr_t)(const char *str_uuid, 
                grio_uuid_t *uuid);
typedef int (*grio_id_to_string_fptr_t)(grio_uuid_t *id, 
                char str_uuid[GRIO_ID_LEN]);
typedef int (*grio_id_is_equal_fptr_t)(const grio_uuid_t *uuid1, 
                const grio_uuid_t *uuid2);

extern __grio_errno_fptr_t		__grio_errno;

extern grio_query_param_fptr_t		grio_query_param;
extern grio_avail_fptr_t		grio_avail;
extern grio_reserve_fptr_t		grio_reserve;
extern grio_reserve_fd_fptr_t		grio_reserve_fd;
extern grio_bind_fptr_t			grio_bind;
extern grio_unbind_fptr_t		grio_unbind;
extern grio_modify_fptr_t		grio_modify;
extern grio_release_fptr_t		grio_release;

extern grio_get_stream_fptr_t		grio_get_stream;
extern grio_get_streams_fptr_t		grio_get_streams;
extern grio_qos_get_hist_desc_fptr_t	grio_qos_get_hist_desc;
extern grio_qos_get_hist_fptr_t		grio_qos_get_hist;
extern grio_qos_get_interval_stats_fptr_t grio_qos_get_interval_stats;
extern grio_qos_reset_fptr_t		grio_qos_reset;
extern grio_qos_reinit_fptr_t		grio_qos_reinit;
extern grio_id_from_string_fptr_t	grio_id_from_string;
extern grio_id_to_string_fptr_t		grio_id_to_string;
extern grio_id_is_equal_fptr_t		grio_id_is_equal;
	
#endif /* GRIO2_RTL */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _GRIO2_H_ */
