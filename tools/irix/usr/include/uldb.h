#ifndef __ULDB_H_
#define __ULDB_H_
#ifdef __cplusplus
extern "C" {
#endif
#ident "$Revision: 1.9 $"
/*
*
* Copyright 1992, Silicon Graphics, Inc.
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
*/
/*
 * NOTE: Best viewed if TABS are set to 4
 */

#include <sys/types.h>
#include <sys/resource.h>

#define LOCALBUFLEN     4096
#define LOCALFILE       "/etc/jlimits.m"
#define LISTMAP         "jlimits"
#define KEY_SEP         "#"     /* key separator */
#define LIMIT_SEP       ":"     /* limit separator */
#define VAL_SEP         "="     /* value separator */

/*
 * Magic key for entry that contains all domain names
 */
#define ALL_DOMAINS_KEY	"ALL_DOMAINS"

/*
 * Multiplier Values
 */
#define KILO            1024LLU            /* kilobyte conversion */
#define K_KILO          "k"
#define MEGA            1048576LLU         /* megabyte conversion */
#define M_MEGA          "m"
#define GIGA            1073741824LLU      /* gigabyte conversion */
#define G_GIGA          "g"
#define TERA            1099511627776LLU   /* terabyte conversion */
#define T_TERA          "t"
#define HOURS           3600LLU            /* Hours conversion */
#define H_HOURS         "H"
#define MINUTES         60LLU              /* Minutes conversion */
#define M_MINUTES       "M"

/*
 * Types
 */

/*
 * Binary limit values are held as unsigned 64-bit values
 */
typedef rlim_t 	uldb_limit_t;

typedef struct uldb_namelist_s {
		int			uldb_nitems;	/* number of names in the list */
		char		**uldb_names;	/* list of name pointers */
} uldb_namelist_t;

typedef struct uldb_limitlist_s {
		int				uldb_nitems;	/* number of limit values in the list */
		uldb_limit_t	*uldb_limits;	/* listof limit pointers */
} uldb_limitlist_t;

/*
 * Prototypes
 */

extern uldb_limitlist_t *uldb_get_limit_values(char *, char *, 
	uldb_namelist_t *);
extern uldb_limitlist_t *uldb_get_value_units(char *, char *,
	uldb_namelist_t *);
extern uldb_namelist_t *uldb_get_limit_names(char *);
extern uldb_namelist_t *uldb_get_domain_names(void);
extern void	uldb_free_namelist (uldb_namelist_t *);
extern void	uldb_free_limit_list (uldb_limitlist_t *);

#if !defined(_SGI_COMPILING_LIBC)
#pragma optional uldb_get_limit_values
#pragma optional uldb_get_value_units
#pragma optional uldb_get_limit_names
#pragma optional uldb_get_domain_names
#pragma optional uldb_free_namelist 
#pragma optional uldb_free_limit_list 
#endif

#endif /* !__ULDB_H_ */
