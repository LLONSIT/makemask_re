/******************************************************************************

	    COPYRIGHT (c) 2000, 2003 by Macrovision Corporation.
	This software has been provided pursuant to a License Agreement
	containing restrictions on its use.  This software contains
	valuable trade secrets and proprietary information of 
	Macrovision Corporation and is protected by law.  It may 
	not be copied or distributed in any form or medium, disclosed 
	to third parties, reverse engineered or used in any manner not 
	provided for in said License Agreement except with the prior 
	written authorization from Macrovision Corporation.

 *****************************************************************************/
/*	
 *	Module: $Id: lm_cro.h,v 1.1 2004/05/20 19:50:24 alaffin Exp $
 *
 *	Description: 	header file required by lm_code.h
 *			Used for CRO (Counterfeit Resistant Option)
 */
#ifndef LM_CRO_H
#define LM_CRO_H

#define LM_STRENGTH_LICENSE_KEY	0	
#define LM_STRENGTH_DEFAULT	1	
#define LM_STRENGTH_113BIT	2
#define LM_STRENGTH_163BIT	3
#define LM_STRENGTH_239BIT	4
#define LM_STRENGTH_PUBKEY	LM_STRENGTH_113BIT
#define LM_STRENGTH_VERYHIGH	LM_STRENGTH_239BIT
				/* >= PUBKEY uses Public-Key */

/*
 *	Values for LM_SIGN_LEVEL
 */
#define LM_SIGN2 	2  /* SIGN2= */
#define LM_SIGN	 	1  /* SIGN= the default */
#define LM_NO_SIGN	 0  /* license key */
#endif /* LM_CRO_H */
