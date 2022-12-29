/*
 *    Unpublished copyright (c) 2004 Silicon Graphics, Inc.
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
/*
 * brick.h -- functions for registering and finding I/O bricks and
 * router bricks within the system.
 */

#ifndef __SYS_SN_SN1_BRICK_H__
#define __SYS_SN_SN1_BRICK_H__

#include <sys/types.h>

extern int		rbrick_register(moduleid_t id);
extern moduleid_t	rbrick_lookup(int rack, int bay);
extern int		iobrick_register(moduleid_t id);
extern moduleid_t	iobrick_lookup(int rack, int bay);

#endif /* __SYS_SN_SN1_BRICK_H__ */

