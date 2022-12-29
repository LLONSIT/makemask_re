/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1992-1997, Silicon Graphics, Inc.          *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 **************************************************************************/

#ifndef __SYS_SN_VECTOR_H__
#define __SYS_SN_VECTOR_H__

#define NET_VEC_NULL            ((net_vec_t)  0)
#define NET_VEC_BAD             ((net_vec_t) -1)

#ifdef RTL

#define VEC_POLLS_W		16	/* Polls before write times out */
#define VEC_POLLS_R		16	/* Polls before read times out */
#define VEC_POLLS_X		16	/* Polls before exch times out */

#define VEC_RETRIES_W		1	/* Retries before write fails */
#define VEC_RETRIES_R		1	/* Retries before read fails */
#define VEC_RETRIES_X		1	/* Retries before exch fails */

#else /* RTL */

#define VEC_POLLS_W		256	/* Polls before write times out */
#define VEC_POLLS_R		256	/* Polls before read times out */
#define VEC_POLLS_X		256	/* Polls before exch times out */

#define VEC_RETRIES_W		8	/* Retries before write fails */
#define VEC_RETRIES_R           8	/* Retries before read fails */
#define VEC_RETRIES_X		4	/* Retries before exch fails */

#endif /* RTL */

#if defined SN0
#define VECTOR_PARMS		NI_VECTOR_PARMS
#define VECTOR_ROUTE		NI_VECTOR
#define VECTOR_DATA		NI_VECTOR_DATA
#define VECTOR_STATUS		NI_VECTOR_STATUS
#define VECTOR_RETURN		NI_RETURN_VECTOR
#define VECTOR_READ_DATA	NI_VECTOR_READ_DATA
#define VECTOR_STATUS_CLEAR	NI_VECTOR_CLEAR
#define VP_PIOID_SHFT		NVP_PIOID_SHFT
#define VP_PIOID_MASK		NVP_PIOID_MASK
#define VP_WRITEID_SHFT		NVP_WRITEID_SHFT
#define VP_WRITEID_MASK		NVP_WRITEID_MASK
#define VP_ADDRESS_MASK		NVP_ADDRESS_MASK
#define VP_TYPE_TYPE		NVP_TYPE_TYPE
#define VP_TYPE_MASK		NVP_TYPE_MASK
#define VS_VALID		NVS_VALID
#define VS_OVERRUN		NVS_OVERRUN
#define VS_TARGET_SHFT		NVS_TARGET_SHFT
#define VS_TARGET_MASK		NVS_TARGET_MASK
#define VS_PIOID_SHFT		NVS_PIOID_SHFT
#define VS_PIOID_MASK		NVS_PIOID_MASK
#define VS_WRITEID_SHFT		NVS_WRITEID_SHFT
#define VS_WRITEID_MASK		NVS_WRITEID_MASK
#define VS_ADDRESS_MASK		NVS_ADDRESS_MASK
#define VS_TYPE_SHFT		NVS_TYPE_SHFT
#define VS_TYPE_MASK		NVS_TYPE_MASK
#define VS_ERROR_MASK		NVS_ERROR_MASK
#elif defined SN1
#define VECTOR_PARMS		LB_VECTOR_PARMS
#define VECTOR_ROUTE		LB_VECTOR_ROUTE
#define VECTOR_DATA		LB_VECTOR_DATA
#define VECTOR_STATUS		LB_VECTOR_STATUS
#define VECTOR_RETURN		LB_VECTOR_RETURN
#define VECTOR_READ_DATA	LB_VECTOR_READ_DATA
#define VECTOR_STATUS_CLEAR	LB_VECTOR_STATUS_CLEAR
#define VP_PIOID_SHFT		LVP_PIOID_SHFT
#define VP_PIOID_MASK		LVP_PIOID_MASK
#define VP_WRITEID_SHFT		LVP_WRITEID_SHFT
#define VP_WRITEID_MASK		LVP_WRITEID_MASK
#define VP_ADDRESS_MASK		LVP_ADDRESS_MASK
#define VP_TYPE_SHFT		LVP_TYPE_SHFT
#define VP_TYPE_MASK		LVP_TYPE_MASK
#define VS_VALID		LVS_VALID
#define VS_OVERRUN		LVS_OVERRUN
#define VS_TARGET_SHFT		LVS_TARGET_SHFT
#define VS_TARGET_MASK		LVS_TARGET_MASK
#define VS_PIOID_SHFT		LVS_PIOID_SHFT
#define VS_PIOID_MASK		LVS_PIOID_MASK
#define VS_WRITEID_SHFT		LVS_WRITEID_SHFT
#define VS_WRITEID_MASK		LVS_WRITEID_MASK
#define VS_ADDRESS_MASK		LVS_ADDRESS_MASK
#define VS_TYPE_SHFT		LVS_TYPE_SHFT
#define VS_TYPE_MASK		LVS_TYPE_MASK
#define VS_ERROR_MASK		LVS_ERROR_MASK
#endif

#define NET_ERROR_NONE          0       /* No error             */
#define NET_ERROR_HARDWARE     -1       /* Hardware error       */
#define NET_ERROR_OVERRUN      -2       /* Extra response(s)    */
#define NET_ERROR_REPLY        -3       /* Reply parms mismatch */
#define NET_ERROR_ADDRESS      -4       /* Addr error response  */
#define NET_ERROR_COMMAND      -5       /* Cmd error response   */
#define NET_ERROR_PROT         -6       /* Prot error response  */
#define NET_ERROR_TIMEOUT      -7       /* Too many retries     */
#define NET_ERROR_VECTOR       -8       /* Invalid vector/path  */
#define NET_ERROR_ROUTERLOCK   -9       /* Timeout locking rtr  */
#define NET_ERROR_INVAL	       -10	/* Invalid vector request */

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)
typedef __uint64_t              net_reg_t;
typedef __uint64_t              net_vec_t;

int             vector_write(net_vec_t dest,
                              int write_id, int address,
                              __uint64_t value);

int             vector_read(net_vec_t dest,
                             int write_id, int address,
                             __uint64_t *value);

#ifdef SN0
int             vector_exch(net_vec_t dest,
                             int write_id, int address,
                             __uint64_t *value);
#endif

int             vector_write_node(net_vec_t dest, nasid_t nasid,
                              int write_id, int address,
                              __uint64_t value);

int             vector_read_node(net_vec_t dest, nasid_t nasid,
                             int write_id, int address,
                             __uint64_t *value);

#ifdef SN0
int             vector_exch_node(net_vec_t dest, nasid_t nasid,
                             int write_id, int address,
                             __uint64_t *value);
#endif

int             vector_length(net_vec_t vec);
net_vec_t       vector_get(net_vec_t vec, int n);
net_vec_t       vector_prefix(net_vec_t vec, int n);
net_vec_t       vector_modify(net_vec_t entry, int n, int route);
net_vec_t       vector_reverse(net_vec_t vec);
net_vec_t       vector_concat(net_vec_t vec1, net_vec_t vec2);

char		*net_errmsg(int);

#ifndef _STANDALONE
int hub_vector_write(cnodeid_t cnode, net_vec_t vector, int writeid,
	int addr, net_reg_t value);
int hub_vector_read(cnodeid_t cnode, net_vec_t vector, int writeid,
	int addr, net_reg_t *value);
#endif

#endif /* _LANGUAGE_C || _LANGUAGE_C_PLUS_PLUS */

#endif /* __SYS_SN_VECTOR_H__ */

