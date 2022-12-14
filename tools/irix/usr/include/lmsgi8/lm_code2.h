/******************************************************************************

	    COPYRIGHT (c) 2002, 2003 by Macrovision Corporation.
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
 *	Module: $Id: lm_code2.h,v 1.1 2004/05/20 19:50:24 alaffin Exp $
 *
 *	Description: 	2nd header file required by lm_code.h
 */
#ifndef LM_CODE2_H
#define LM_CODE2_H
#ifdef V8_1_COMMENT
Migration issues:

	We have the following migration paths:

	From			To
				v8.1 CRO	non-CRO
				--------	-------
	pre-v7.2 license-key	1		2 (no change)
	pre-v8.1 non-cro sign=	3		4 (no change)
	v7.2 CRO		5		6 (not possible)
	New			7		8
	v7.2 license-key	9		10

	Notes:
	Case 1:		license-key, SIGN= no SEED3/4.  use absence of seeds
			3 and 4 as signal that this is case 1.
	Case 2:		No change.  LM_STRENGTH is LM_STRENGTH_LICENSE_KEY
			LM_SIGN_LEVEL is 0
			Handshake seeds automatically generated.
	Case 3:		We probably will not handle these now.  These are 
			companies that had the opportunity to buy CRO when
			they first purchased, and chose not to.  We actually
			did not have a migration path for these in v7.2 or
			v8.0 either.
	Case 4:		No Change.  LM_STRENGTH is LM_STRENGTH_DEFAULT
			LM_SIGN_LEVEL is 1
	Case 5:		Migration:  SIGN and SIGN2.  Signal is that there
			are seeds 1-4 and LM_SIGN_LEVEL is 2.
	Case 6:		Not possible.  Cannot go from CRO to non-CRO.
	Case 7:		New CRO customer.  LM_SIGN_LEVEL is 1.  
			Signal is no ENCRYPTION_SEEDS
	case 8:		LM_STRENGTH_DEFAULT.  LM_SIGN_LEVEL is 1.
			Signal is no ENCRYPTION_SEEDS
	case 9:		There is no automatic signal for this -- it is ambiguous
			with case 5.  The ISV will have to set LM_SIGN_LEVEL to
			LM_SIGN (1).
	case 10:	No change.  LM_STRENGTH is LM_STRENGTH_LICENSE_KEY.
#endif /* V8_1_COMMENT */

#ifndef LM_SIGN_LEVEL 
#if (LM_STRENGTH >= LM_STRENGTH_113BIT) && !defined(ENCRYPTION_SEED3)
	/*
	 *	Case 1: Upgrade from pre-v7.2 license-key to CRO
	 *		Both license-key and SIGN= supported
	 *		Sign= generated using v8.1 method
	 */
#define LM_SIGN_LEVEL LM_SIGN
#endif 	/* Case 1 */

#if (LM_STRENGTH == LM_STRENGTH_LICENSE_KEY) && !defined(ENCRYPTION_SEED3)
	/*
	 *	Case 2: Upgrade from pre-v7.2 license-key -- no change 
	 *		Handshake seeds automatically generated
	 */
#define LM_SIGN_LEVEL LM_NO_SIGN  	
#endif 	/* Case 2 */

#if (LM_STRENGTH == LM_STRENGTH_DEFAULT) && defined(ENCRYPTION_SEED3)
	/*
	 *	Case 4: Upgrade from v7.2 non-CRO SIGN= -- no change 
	 */
#define LM_SIGN_LEVEL LM_SIGN  	
#endif 	/* Case 4 */

#if (LM_STRENGTH >= LM_STRENGTH_113BIT) && defined(ENCRYPTION_SEED3)
	/*
	 *	Case 5: Upgrade from v7.2 CRO 
	 *		SIGN= and SIGN2= required
	 */
#define LM_SIGN_LEVEL LM_SIGN2
#endif 	/* Case 5 */

#ifndef ENCRYPTION_SEED1 
	/*
	 *	Cases 7 and 8: new customer
	 */

#define LM_SIGN_LEVEL LM_SIGN
#endif 	/* Cases 7 and 8 */

#if (LM_STRENGTH == LM_STRENGTH_LICENSE_KEY) && defined(ENCRYPTION_SEED3)
	/* 
	 *	Case 10:  Used v7.2 and still using LICENSE_KEY
	 */
#define LM_SIGN_LEVEL LM_NO_SIGN
#endif /* Case 10 */

#else
	/*
	 *	Else for LM_SIGN_LEVEL.  There should be only one case here:
	 *	case 9
	 */
#if (LM_SIGN_LEVEL == LM_SIGN) && (LM_STRENGTH >= LM_STRENGTH_113BIT) \
	&& defined(ENCRYPTION_SEED3)
	/*
	 *	Case 9: Upgrade from v7.2 license-key to CRO, but didn't use
	 *		CRO in v7.2
	 *		SIGN= only 
	 *	No action -- LM_SIGN_LEVEL already explictly set by ISV.
	 */
#endif /* Case 9 */

#endif  /* LM_SIGN_LEVEL */

#ifndef LM_SIGN_LEVEL
#define LM_SIGN_LEVEL 9999 /* Error */ 
#endif /* Errors */

#ifndef ENCRYPTION_SEED1 /* New v8.1+ ISV */
#define ENCRYPTION_SEED1 0
#define ENCRYPTION_SEED2 0
#endif /* ENCRYPTION_SEED1 */
#ifndef ENCRYPTION_SEED3 /* Didn't use v7.2 */
#define ENCRYPTION_SEED3 0
#define ENCRYPTION_SEED4 0
#endif /* ENCRYPTION_SEED3 */

/*
 *	Behavior
 */
#ifndef LM_VER_BEHAVIOR
#define LM_VER_BEHAVIOR LM_BEHAVIOR_V8 
/* 			
 *				Upgrading customers may want to set 
 * 				behavior defaults to previous version, 
 *				though this is usually discouraged.  
 *				Behaviors can be changed individually using 
 *				LM_A_xxx in the flexible API. Valid settings 
 *				include: LM_BEHAVIOR_V2, _V3, _V4, _V5, 
 *				_V5_1, _V6, _V7, _V7_1
 */
#endif /* LM_VER_BEHAVIOR */
#ifndef LM_BORROW_OK
/* 
 *	Borrow:			Set this to 0 if borrowing is unsupported   
 *				Not recommended, since borrowing must
 *				also be enabled in the license
 */
#define LM_BORROW_OK	1
#endif /* LM_BORROW_OK */

#endif /* LM_CODE2_H */

