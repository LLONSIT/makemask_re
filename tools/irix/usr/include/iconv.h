#ifndef _ICONV_H
#define _ICONV_H
#ident "$Revision: 1.7 $"
/*
*
* Copyright 1995, Silicon Graphics, Inc.
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

#include <sys/types.h>
#include <internal/sgimacros.h>

__SGI_LIBC_BEGIN_EXTERN_C

typedef void	*iconv_t;

extern iconv_t	iconv_open(const char *, const char *);
extern size_t	iconv(iconv_t, char **, size_t *, char **, size_t *);
extern int	iconv_close(iconv_t);

__SGI_LIBC_END_EXTERN_C

#endif /*_ICONV_H*/
