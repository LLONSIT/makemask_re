/* USMID @(#) clibinc/cray/clibinc_config.h	92.1	11/12/98 10:48:54 */
/*
 *	(C) COPYRIGHT CRAY RESEARCH, INC.
 *	UNPUBLISHED PROPRIETARY INFORMATION.
 *	ALL RIGHTS RESERVED.
 *
 *	** This header is for CRI internal use only. **
 *
 *	This header file contains the definition for the _CRAYLIBS_RELEASE 
 *	macro which tells the version of the CrayLibs release package.   
 *	An attempt is made to ensure that this version number reflects the 
 *	true CrayLibs release number.  However, there may be times when the 
 *	release level defined here is slightly out of date.   Normally, the 
 *	major and minor release level (first two) digits will be correct.  
 *	The revision and update level (last two) digits are more apt to 
 *	occasionally be out of date.
 *
 *	Other macros might be added in this header file to help coordinate
 *	the migration of a header file between two release packages.  For 
 *	example, if "complex.h" is to migrate out of UNICOS and into
 *	the CrayLibs package a macro definition might be added here to
 *	indicate that a complex.h exists in the CrayLibs package.
 */

#define _CRAYLIBS_RELEASE	3200	/* CrayLibs 3.2.0.0 */
