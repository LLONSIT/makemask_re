/*
 *    Unpublished copyright (c) 1996-2002 Silicon Graphics, Inc.
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

#ifndef _FAILOVER_H_
#define _FAILOVER_H_

#include <sys/scsi.h>

/* 
 * Structure definitions for failover specific syssgi routines
 * Usage: 
 *    To force a failover switch:
 *      vertex_hdl_t p_vhdl, s_vhdl;
 *      syssgi(SGI_FO_SWITCH, p_vhdl, &s_vhdl);
 *    To get failover instance information:
 *      struct user_fo_instance *buf;
 *      int                      len;
 *      syssgi(SGI_FO_DUMP, buf, &len);
 */
struct user_fo_instance {
  int                      foi_primary;
  vertex_hdl_t             foi_path_vhdl[];
};

/*
 * Structure definitions for DIOCFOUPDATE ioctl
 */
typedef struct user_fo_generic_info {
	int		fgi_revision;
	char		fgi_instance_name[32];	/* cast to scsi_name_t */
	struct user_fo_generic_lun_data {
		vertex_hdl_t	fgi_lun_vhdl;
		u_char		fgi_inq_data[SCSI_INQUIRY_LEN];
	}fgi_lun_data[];
} user_fo_generic_info_t;

#if _KERNEL
extern int fo_max_paths;
typedef void *scsi_name_t;

#define FOI_PATHSTAT_INVALID  0 
#define FOI_PATHSTAT_VALID    1
#define FOI_PATHSTAT_FAILED   2	/* Failed but maybe still usable */
#define FOI_PATHSTAT_UNCLUN   3

#define FOI_NO_PRIMARY		(-1)

struct scsi_fo_instance {
  struct scsi_fo_instance *foi_next;
  struct scsi_candidate   *foi_foc;
  scsi_name_t              foi_grp_name;
  int                      foi_primary;
  char			   foi_restrict;
  char			   foi_avt;
  struct foi_path_info {
    vertex_hdl_t           foi_path_vhdl;
    u_char                 foi_path_status;
  } foi_path[];
};
typedef struct scsi_fo_instance  scsi_fo_instance_struct_t;
typedef struct scsi_candidate   *scsi_fo_instance_t;

#define FO_NAMECMP_FAIL          0
#define FO_NAMECMP_SUCCESS       1
#define FO_NAMECMP_REPLACE       2

#define FO_VH_COH_POLICY_INVALID 0
#define FO_VH_COH_POLICY_LAZY    1
#define FO_VH_COH_POLICY_EAGER   2

struct scsi_candidate {
  char                    *scsi_match_str1;	/* First string used for matching */
  char                    *scsi_match_str2;	/* Second string used for matching */
  u_char                   scsi_match_off1;	/* Offset of 1st string in inventory */
  u_char                   scsi_match_off2;	/* Offset of 2nd string in inventory */
  int                    (*scsi_validlun_func)(u_char *, vertex_hdl_t);
  int                    (*scsi_getname_func)(vertex_hdl_t, scsi_name_t *, u_char *);
  int                    (*scsi_cmpname_func)(scsi_name_t, scsi_name_t);
  int                    (*scsi_avt_func)(vertex_hdl_t);
  char                  *(*scsi_sprintf_func)(scsi_name_t);
  int                    (*scsi_switch_func)(vertex_hdl_t, vertex_hdl_t);
  int			 (*scsi_primary_func)(struct scsi_candidate *,
					      struct user_fo_generic_info *);
  int                    (*scsi_reportwarnings_func)(vertex_hdl_t);
  int                      scsi_vh_coherency_policy;
  sema_t                  *scsi_foi_sema4;
  struct scsi_fo_instance *scsi_foi;
};
typedef struct scsi_candidate  scsi_candidate_struct_t;
typedef struct scsi_candidate *scsi_candidate_t;

extern struct scsi_candidate fo_candidates[];

/*
 * Primary entry points to FAILOVER module
 */
void fo_scsi_device_update(u_char *inv, vertex_hdl_t lun_vhdl);
void fo_scsi_lun_remove(vertex_hdl_t lun_vhdl);
int  fo_scsi_device_switch(vertex_hdl_t p_vhdl, vertex_hdl_t *s_vhdl);
int  fo_scsi_device_switch_new(vertex_hdl_t, vertex_hdl_t *, int);
int  fo_scsi_device_pathcount(vertex_hdl_t vhdl);
int  fo_is_failover_candidate(u_char *inv, vertex_hdl_t lun_vhdl);
int  fo_scsi_device_update_generic (user_fo_generic_info_t *fgi);
int  fo_scsi_device_path_state (vertex_hdl_t p_vhdl);
int  fo_scsi_device_is_avt (vertex_hdl_t vhdl);

#define FO_SWITCH_SUCCESS         0
#define FO_SWITCH_INVALID_PATH    1
#define FO_SWITCH_NOPATH          2 /* degenerate case - no longer a possible return code */
#define FO_SWITCH_ONEPATHONLY     3
#define FO_SWITCH_PATHS_EXHAUSTED 4
#define FO_SWITCH_FAIL            -1

/*
** Values returned to caller via fo_scsi_device_path_state().
*/
#define FO_PRIMARY_PATH         5
#define FO_ALTERNATE_PATH       6
#define FO_UNKNOWN_DEVICE       7
#define FO_INVALID_PATH         FO_SWITCH_INVALID_PATH


#define FO_PATHCOUNT_FAIL         -1

/*
 * IDBG routines
 */
void idbg_foi(vertex_hdl_t lun_vhdl);

#endif /* _KERNEL */

#endif
