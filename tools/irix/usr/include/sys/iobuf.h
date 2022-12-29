/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*#ident	"@(#)kern-port:sys/iobuf.h	10.2"*/
#ident	"$Revision: 3.10 $"
/*
 * The iobuf if used by drivers to keep track of certain statistics
 * and to maintain a list of requests in a queue.
 */
typedef struct iobuf
{
	struct buf	*prio_head;	/* head of Priority I/O queue */
	struct buf	*prio_tail;	/* tail of Priority I/O queue */
	struct buf	*io_head;	/* head of I/O queue */
	struct buf	*io_tail;	/* tail of I/O queue */
	union
	{
		char	active;		/* busy flag */
		long	prevblk;	/* block # of previous command */
	} io_state;
	int		seq_count;	/* count of sequential requests */
	daddr_t		seq_next;	/* next sequential request */
} iobuf_t;

typedef struct diskqueue
{
	struct buf	*prio_head;	/* head of Priority I/O queue */
	struct buf	*prio_tail;	/* tail of Priority I/O queue */
	struct buf	*io_head;	/* head of I/O queue */
	struct buf	*io_tail;	/* tail of I/O queue */
	daddr_t		 io_prev;	/* block # of previous command */
	daddr_t		 seq_next;	/* next sequential request */
	int		 seq_count;	/* count of sequential requests */
	int		 io_qsize;	/* # of requests on i/o queue */
	struct buf	*io_overflow_head; /* head of i/o overflow */
	struct buf	*io_overflow_tail; /* tail of i/o overflow */
	int		 delwri_holdoff; /* delwri fairness variable */
	struct buf	*delwri_head;	/* head of delwri queue */
	struct buf	*delwri_tail;	/* tail of delwri queue */
	daddr_t		 delwri_prev;	/* block # of previous command */
	int		 delwri_qsize;	/* # of requests on delwri queue */
	struct buf	*delwri_overflow_head; /* head of delwri overflow */
	struct buf	*delwri_overflow_tail; /* tail of delwri overflow */
} diskqueue_t;


extern void		macsisort(struct diskqueue *, struct buf *);
extern void		nosort(struct diskqueue *, struct buf *);
extern struct buf *	fair_disk_dequeue(struct diskqueue *);
