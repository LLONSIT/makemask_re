#ifndef __GL_IMINTERP_H__
#define __GL_IMINTERP_H__
/**************************************************************************
 *									  *
 * 		 Copyright (C) 1989, Silicon Graphics, Inc.	  	  *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/

/*
 *  iminterp.h 
 *  - some pretty complex but powerful macros by Herb Kuta to generate
 *    display listable GL commands  
 *
 *  $Revision: 1.26 $
 */

#include "cppdefs.h"
#include "dlsz.h"
#include "dlpers.h"
#include "TheMacro.h"

#ifdef IGLOO 
#define DL_EXTRA_IM_SETUP()
#else
#define DL_EXTRA_IM_SETUP()	im_setup
#endif /* IGLOO */

#define	DL_GENCMD_0(intrp_sclass,name)				\
    DL_IMMED_BEGIN(visible,name,(void))				\
    { 								\
	DL_EXTRA_IM_SETUP();					\
	TOKENPASTE(im_,name)();					\
    } 								\
    DL_IMMED_END(name) 						\
    DL_CMPLR_BEGIN(visible,name,(void))				\
    { 								\
	BEGINCOMPILE(TOKENPASTE(DLSZ_,name)); 			\
	ADDINTRP(name);						\
	ENDCOMPILE(TOKENPASTE(DLSZ_,name)); 			\
    } 								\
    DL_CMPLR_END(name) 						\
    DL_INTRP_BEGIN(intrp_sclass,name) 				\
    { 								\
	TOKENPASTE(im_,name)();					\
	thread(name); 						\
    } 								\
    DL_INTRP_END(name)


#define	DL_GENCMD_1(intrp_sclass,name,type)			\
    DL_IMMED_BEGIN(visible,name,( type x))			\
    { 								\
        DL_EXTRA_IM_SETUP();					\
	TOKENPASTE(im_,name)(x); 				\
    } 								\
    DL_IMMED_END(name) 						\
    DL_CMPLR_BEGIN(visible,name,( type x))			\
    {						    		\
	BEGINCOMPILE(TOKENPASTE(DLSZ_,name)); 			\
	ADDINTRP(name);						\
	TOKENPASTE(ADD,type)(x);				\
	TOKENPASTE(ADDFILL,type)();				\
	ENDCOMPILE(TOKENPASTE(DLSZ_,name)); 			\
    } 								\
    DL_CMPLR_END(name) 						\
    DL_INTRP_BEGIN(intrp_sclass,name) 				\
	TOKENPASTE(im_,name)(TOKENPASTE(TAKE,type)(0)); 	\
	thread(name); 						\
    DL_INTRP_END(name)


#define	DL_GENCMD_1C(intrp_sclass,name,type)			\
    DL_IMMED_BEGIN(visible,name,( const type x))		\
    { 								\
	DL_EXTRA_IM_SETUP();					\
	TOKENPASTE(im_,name)(x); 				\
    } 								\
    DL_IMMED_END(name) 						\
    DL_CMPLR_BEGIN(visible,name,( const type x))		\
    {						    		\
	BEGINCOMPILE(TOKENPASTE(DLSZ_,name)); 			\
	ADDINTRP(name);						\
	TOKENPASTE(ADD,type)(x);				\
	TOKENPASTE(ADDFILL,type)();				\
	ENDCOMPILE(TOKENPASTE(DLSZ_,name)); 			\
    } 								\
    DL_CMPLR_END(name) 						\
    DL_INTRP_BEGIN(intrp_sclass,name) 				\
    { 								\
	TOKENPASTE(im_,name)(TOKENPASTE(TAKE,type)(0)); 	\
	thread(name); 						\
    } 								\
    DL_INTRP_END(name)


#define DL_GENCMD_2(intrp_sclass,name,type)			\
    DL_IMMED_BEGIN(visible,name,( type x, type y))		\
    { 								\
	DL_EXTRA_IM_SETUP();					\
	TOKENPASTE(im_,name)(x,y); 				\
    } 								\
    DL_IMMED_END(name) 						\
    DL_CMPLR_BEGIN(visible,name,( type x, type y))		\
    { 								\
	BEGINCOMPILE(TOKENPASTE(DLSZ_,name)); 			\
	ADDINTRP(name);						\
	TOKENPASTE(ADD,type)(x);				\
	TOKENPASTE(ADD,type)(y);				\
	ENDCOMPILE(TOKENPASTE(DLSZ_,name)); 			\
    } 								\
    DL_CMPLR_END(name) 						\
    DL_INTRP_BEGIN(intrp_sclass,name) 				\
    { 								\
	TOKENPASTE(im_,name)(TOKENPASTE(TAKE,type)(0),			\
		    TOKENPASTE(TAKE,type)(TOKENPASTE(DLSZ_,type)));	\
	thread(name); 						\
    } 								\
    DL_INTRP_END(name)

#define DL_GENCMD_2_TYPES(intrp_sclass,name,type1,type2)        \
    DL_IMMED_BEGIN(visible,name,( type1 x, type2 y))            \
    {                                                           \
	DL_EXTRA_IM_SETUP();					\
        TOKENPASTE(im_,name)(x,y);                              \
    }                                                           \
    DL_IMMED_END(name)                                          \
    DL_CMPLR_BEGIN(visible,name,( type1 x, type2 y))            \
    {                                                           \
        BEGINCOMPILE(TOKENPASTE(DLSZ_,name));                   \
        ADDINTRP(name);                                         \
        TOKENPASTE(ADD,type1)(x);                               \
        TOKENPASTE(ADD,type2)(y);                               \
        ENDCOMPILE(TOKENPASTE(DLSZ_,name));                     \
    }                                                           \
    DL_CMPLR_END(name)                                          \
    DL_INTRP_BEGIN(intrp_sclass,name)                           \
    {                                                           \
        TOKENPASTE(im_,name)(TOKENPASTE(TAKE,type1)(0),                  \
                    TOKENPASTE(TAKE,type1)(TOKENPASTE(DLSZ_,type1)));     \
        thread(name);                                           \
    }                                                           \
    DL_INTRP_END(name)

#define DL_SPECMD_2(intrp_sclass,name,type1,type2) 		\
    DL_IMMED_BEGIN(visible,name,( type1 x, type2 y))		\
    { 								\
	DL_EXTRA_IM_SETUP();					\
	TOKENPASTE(im_,name)(x,y); 				\
    } 								\
    DL_IMMED_END(name) 						\
    DL_CMPLR_BEGIN(visible,name,( type1 x, type2 y))		\
    { 								\
	BEGINCOMPILE(TOKENPASTE(DLSZ_,name)); 			\
	ADDINTRP(name);						\
	TOKENPASTE(ADD,type1)(x);				\
	TOKENPASTE(ADD,type2)(y);				\
	ENDCOMPILE(TOKENPASTE(DLSZ_,name)); 			\
    } 								\
    DL_CMPLR_END(name) 						\
    DL_INTRP_BEGIN(intrp_sclass,name) 				\
    { 								\
	TOKENPASTE(im_,name)(TOKENPASTE(TAKE,type1)(0),			\
		    TOKENPASTE(TAKE,type2)(TOKENPASTE(DLSZ_,type1)));	\
	thread(name); 						\
    } 								\
    DL_INTRP_END(name)

#define DL_GENCMD_3(intrp_sclass,name,type)			\
    DL_IMMED_BEGIN(visible,name,( type x, type y, type z)) 	\
    { 								\
	DL_EXTRA_IM_SETUP();					\
	TOKENPASTE(im_,name)(x,y,z); 				\
    } 								\
    DL_IMMED_END(name) 						\
    DL_CMPLR_BEGIN(visible,name,( type x, type y, type z)) 	\
    { 								\
	BEGINCOMPILE(TOKENPASTE(DLSZ_,name)); 			\
	ADDINTRP(name);						\
	TOKENPASTE(ADD,type)(x); 				\
	TOKENPASTE(ADD,type)(y); 				\
	TOKENPASTE(ADD,type)(z); 				\
	TOKENPASTE(ADDFILL,type)();				\
	ENDCOMPILE(TOKENPASTE(DLSZ_,name)); 			\
    } 								\
    DL_CMPLR_END(name) 						\
    DL_INTRP_BEGIN(intrp_sclass,name) 				\
    { 								\
	TOKENPASTE(im_,name)(TOKENPASTE(TAKE,type)(0),			\
		    TOKENPASTE(TAKE,type)(TOKENPASTE(DLSZ_,type)),	\
		    TOKENPASTE(TAKE,type)(2*TOKENPASTE(DLSZ_,type))); 	\
	thread(name); 						\
    } 								\
    DL_INTRP_END(name)

#define DL_SPECMD_3(intrp_sclass,name,type1,type2,type3)	\
    DL_IMMED_BEGIN(visible,name,( type1 x, type2 y, type3 z))	\
    { 								\
	im_setup; 						\
	TOKENPASTE(im_,name)(x,y,z); 				\
    } 								\
    DL_IMMED_END(name) 						\
    DL_CMPLR_BEGIN(visible,name,( type1 x, type2 y, type3 z))   \
    { 								\
	BEGINCOMPILE(TOKENPASTE(DLSZ_,name)); 			\
	ADDINTRP(name);						\
	TOKENPASTE(ADD,type1)(x); 				\
	TOKENPASTE(ADD,type2)(y); 				\
	TOKENPASTE(ADD,type3)(z); 				\
	ENDCOMPILE(TOKENPASTE(DLSZ_,name)); 			\
    } 								\
    DL_CMPLR_END(name) 						\
    DL_INTRP_BEGIN(intrp_sclass,name) 				\
    { 								\
	TOKENPASTE(im_,name)(TOKENPASTE(TAKE,type1)(0),		\
		    TOKENPASTE(TAKE,type2)(TOKENPASTE(DLSZ_,type1)),	\
		    TOKENPASTE(TAKE,type3)(2*TOKENPASTE(DLSZ_,type2))); 		\
	thread(name); 						\
    } 								\
    DL_INTRP_END(name)

#define DL_GENCMD_4(intrp_sclass,name,type)			\
    DL_IMMED_BEGIN(visible,name,( type x, type y, type z, type w)) \
    { 								\
	DL_EXTRA_IM_SETUP();					\
	TOKENPASTE(im_,name)(x,y,z,w); 				\
    } 								\
    DL_IMMED_END(name) 						\
    DL_CMPLR_BEGIN(visible,name,( type x, type y, type z, type w)) \
    { 								\
	BEGINCOMPILE(TOKENPASTE(DLSZ_,name)); 			\
	ADDINTRP(name);						\
	TOKENPASTE(ADD,type)(x); 				\
	TOKENPASTE(ADD,type)(y); 				\
	TOKENPASTE(ADD,type)(z); 				\
	TOKENPASTE(ADD,type)(w); 				\
	ENDCOMPILE(TOKENPASTE(DLSZ_,name)); 			\
    } 								\
    DL_CMPLR_END(name) 						\
    DL_INTRP_BEGIN(intrp_sclass,name) 				\
    { 								\
	TOKENPASTE(im_,name)(TOKENPASTE(TAKE,type)(0),		\
		    TOKENPASTE(TAKE,type)(TOKENPASTE(DLSZ_,type)),	\
		    TOKENPASTE(TAKE,type)(2*TOKENPASTE(DLSZ_,type)),	\
		    TOKENPASTE(TAKE,type)(3*TOKENPASTE(DLSZ_,type))); 	\
	thread(name); 						\
    } 								\
    DL_INTRP_END(name)

#define DL_GENCMD_5(intrp_sclass,name,type)			\
    DL_IMMED_BEGIN(visible,name,( type x, type y, type z, type w, type q)) \
    { 								\
	DL_EXTRA_IM_SETUP();					\
	TOKENPASTE(im_,name)(x,y,z,w,q);			\
    } 								\
    DL_IMMED_END(name) 						\
    DL_CMPLR_BEGIN(visible,name,( type x, type y, type z, type w, type q)) \
    { 								\
	BEGINCOMPILE(TOKENPASTE(DLSZ_,name)); 			\
	ADDINTRP(name);						\
	TOKENPASTE(ADD,type)(x); 				\
	TOKENPASTE(ADD,type)(y); 				\
	TOKENPASTE(ADD,type)(z); 				\
	TOKENPASTE(ADD,type)(w); 				\
	TOKENPASTE(ADD,type)(q); 				\
	ENDCOMPILE(TOKENPASTE(DLSZ_,name)); 			\
    } 								\
    DL_CMPLR_END(name) 						\
    DL_INTRP_BEGIN(intrp_sclass,name) 				\
    { 								\
	TOKENPASTE(im_,name)(TOKENPASTE(TAKE,type)(0),		\
		    TOKENPASTE(TAKE,type)(TOKENPASTE(DLSZ_,type)),	\
		    TOKENPASTE(TAKE,type)(2*TOKENPASTE(DLSZ_,type)),	\
		    TOKENPASTE(TAKE,type)(3*TOKENPASTE(DLSZ_,type)), 	\
		    TOKENPASTE(TAKE,type)(4*TOKENPASTE(DLSZ_,type))); 	\
	thread(name); 						\
    } 								\
    DL_INTRP_END(name)

#define DL_GENCMD_7(intrp_sclass,name,type)			\
    DL_SPECMD_7(intrp_sclass,name,type,type,type,type,type,type,type)


#define DL_SPECMD_4(intrp_sclass,name,type1,type2,type3,type4)	\
    DL_IMMED_BEGIN(visible,name,( type1 x, type2 y, type3 z, type4 w)) \
    { 								\
	DL_EXTRA_IM_SETUP();					\
	TOKENPASTE(im_,name)(x,y,z,w);				\
    } 								\
    DL_IMMED_END(name) 						\
    DL_CMPLR_BEGIN(visible,name,( type1 x, type2 y, type3 z, type4 w)) \
    { 								\
	BEGINCOMPILE(TOKENPASTE(DLSZ_,name)); 			\
	ADDINTRP(name);						\
	TOKENPASTE(ADD,type1)(x); 				\
	TOKENPASTE(ADD,type2)(y); 				\
	TOKENPASTE(ADD,type3)(z); 				\
	TOKENPASTE(ADD,type4)(w); 				\
	ENDCOMPILE(TOKENPASTE(DLSZ_,name)); 			\
    } 								\
    DL_CMPLR_END(name) 						\
    DL_INTRP_BEGIN(intrp_sclass,name) 				\
    { 								\
	TOKENPASTE(im_,name)(TOKENPASTE(TAKE,type1)(0),			\
		    TOKENPASTE(TAKE,type2)(TOKENPASTE(DLSZ_,type1)),	\
		    TOKENPASTE(TAKE,type3)(2*TOKENPASTE(DLSZ_,type2)),	\
		    TOKENPASTE(TAKE,type4)(3*TOKENPASTE(DLSZ_,type3)));	\
	thread(name); 						\
    } 								\
    DL_INTRP_END(name)

#define DL_SPECMD_6(intrp_sclass,name,type1,type2,type3,type4,type5,type6)	\
    DL_IMMED_BEGIN(visible,name,( type1 x, type2 y, type3 z, type4 w, type5 q, type6 a)) \
    { 								\
	im_setup; 						\
	TOKENPASTE(im_,name)(x,y,z,w,q,a);			\
    } 								\
    DL_IMMED_END(name) 						\
    DL_CMPLR_BEGIN(visible,name,( type1 x, type2 y, type3 z, type4 w, type5 q, type6 a)) \
    { 								\
	BEGINCOMPILE(TOKENPASTE(DLSZ_,name)); 			\
	ADDINTRP(name);						\
	TOKENPASTE(ADD,type1)(x); 				\
	TOKENPASTE(ADD,type2)(y); 				\
	TOKENPASTE(ADD,type3)(z); 				\
	TOKENPASTE(ADD,type4)(w); 				\
	TOKENPASTE(ADD,type5)(q); 				\
	TOKENPASTE(ADD,type6)(a); 				\
	ENDCOMPILE(TOKENPASTE(DLSZ_,name)); 			\
    } 								\
    DL_CMPLR_END(name) 						\
    DL_INTRP_BEGIN(intrp_sclass,name) 				\
    { 								\
	TOKENPASTE(im_,name)(TOKENPASTE(TAKE,type1)(0),			\
		    TOKENPASTE(TAKE,type2)(TOKENPASTE(DLSZ_,type1)),	\
		    TOKENPASTE(TAKE,type3)(2*TOKENPASTE(DLSZ_,type2)),	\
		    TOKENPASTE(TAKE,type4)(3*TOKENPASTE(DLSZ_,type3)), 	\
		    TOKENPASTE(TAKE,type5)(4*TOKENPASTE(DLSZ_,type4)), 	\
		    TOKENPASTE(TAKE,type6)(5*TOKENPASTE(DLSZ_,type5)));	\
	thread(name); 						\
    } 								\
    DL_INTRP_END(name)

#define DL_SPECMD_7(intrp_sclass,name,type1,type2,type3,type4,type5,type6,type7)	\
    DL_IMMED_BEGIN(visible,name,( type1 x, type2 y, type3 z, type4 w, type5 q, type6 a, type7 b)) \
    { 								\
	TOKENPASTE(im_,name)(x,y,z,w,q,a,b);			\
    } 								\
    DL_IMMED_END(name) 						\
    DL_CMPLR_BEGIN(visible,name,( type1 x, type2 y, type3 z, type4 w, type5 q, type6 a, type7 b)) \
    { 								\
	BEGINCOMPILE(TOKENPASTE(DLSZ_,name)); 			\
	ADDINTRP(name);						\
	TOKENPASTE(ADD,type1)(x); 				\
	TOKENPASTE(ADD,type2)(y); 				\
	TOKENPASTE(ADD,type3)(z); 				\
	TOKENPASTE(ADD,type4)(w); 				\
	TOKENPASTE(ADD,type5)(q); 				\
	TOKENPASTE(ADD,type6)(a); 				\
	TOKENPASTE(ADD,type7)(b); 				\
	ENDCOMPILE(TOKENPASTE(DLSZ_,name)); 			\
    } 								\
    DL_CMPLR_END(name) 						\
    DL_INTRP_BEGIN(intrp_sclass,name) 				\
    { 								\
	TOKENPASTE(im_,name)(TOKENPASTE(TAKE,type1)(0),		\
		    TOKENPASTE(TAKE,type2)(TOKENPASTE(DLSZ_,type1)),	\
		    TOKENPASTE(TAKE,type3)(2*TOKENPASTE(DLSZ_,type2)),	\
		    TOKENPASTE(TAKE,type4)(3*TOKENPASTE(DLSZ_,type3)), 	\
		    TOKENPASTE(TAKE,type5)(4*TOKENPASTE(DLSZ_,type4)), 	\
		    TOKENPASTE(TAKE,type6)(5*TOKENPASTE(DLSZ_,type5)), 	\
		    TOKENPASTE(TAKE,type7)(6*TOKENPASTE(DLSZ_,type6)));	\
	thread(name); 						\
    } 								\
    DL_INTRP_END(name)

#define DL_GENCMD_CV2(intrp_sclass,name,type)			\
    DL_IMMED_BEGIN(visible,name,( const type v[2]))		\
    { 								\
	DL_EXTRA_IM_SETUP();					\
	TOKENPASTE(im_,name)(v[0],v[1]);			\
    } 								\
    DL_IMMED_END(name) 						\
    DL_CMPLR_BEGIN(visible,name,( const type v[2]))		\
    { 								\
	BEGINCOMPILE(TOKENPASTE(DLSZ_,name)); 			\
	ADDINTRP(name);						\
	ADDV2(type,v);						\
	ENDCOMPILE(TOKENPASTE(DLSZ_,name)); 			\
    } 								\
    DL_CMPLR_END(name) 						\
    DL_INTRP_BEGIN(intrp_sclass,name) 				\
    { 								\
	TOKENPASTE(im_,name)(TOKENPASTE(TAKE,type)(0),			\
		    TOKENPASTE(TAKE,type)(TOKENPASTE(DLSZ_,type)));	\
	thread(name); 						\
    } 								\
    DL_INTRP_END(name)


#define DL_GENCMD_CV3(intrp_sclass,name,type)			\
    DL_IMMED_BEGIN(visible,name,( const type v[3]))		\
    { 								\
	DL_EXTRA_IM_SETUP();					\
	TOKENPASTE(im_,name)(v[0],v[1],v[2]);			\
    } 								\
    DL_IMMED_END(name) 						\
    DL_CMPLR_BEGIN(visible,name,( const type v[3]))		\
    { 								\
	BEGINCOMPILE(TOKENPASTE(DLSZ_,name)); 			\
	ADDINTRP(name);						\
	ADDV3(type,v);						\
	TOKENPASTE(ADDFILL,type)();				\
	ENDCOMPILE(TOKENPASTE(DLSZ_,name)); 			\
    } 								\
    DL_CMPLR_END(name) 						\
    DL_INTRP_BEGIN(intrp_sclass,name) 				\
    { 								\
	TOKENPASTE(im_,name)(TOKENPASTE(TAKE,type)(0),			\
		    TOKENPASTE(TAKE,type)(TOKENPASTE(DLSZ_,type)),	\
		    TOKENPASTE(TAKE,type)(2*TOKENPASTE(DLSZ_,type))); 	\
	thread(name); 						\
    } 								\
    DL_INTRP_END(name)

#define DL_GENCMD_CV4(intrp_sclass,name,type)			\
    DL_IMMED_BEGIN(visible,name,( const type v[4]))		\
    { 								\
	DL_EXTRA_IM_SETUP();					\
	TOKENPASTE(im_,name)(v[0],v[1],v[2],v[3]);		\
    } 								\
    DL_IMMED_END(name) 						\
    DL_CMPLR_BEGIN(visible,name,( const type v[4]))		\
    { 								\
	BEGINCOMPILE(TOKENPASTE(DLSZ_,name)); 			\
	ADDINTRP(name);						\
	ADDV4(type,v);						\
	ENDCOMPILE(TOKENPASTE(DLSZ_,name)); 			\
    } 								\
    DL_CMPLR_END(name) 						\
    DL_INTRP_BEGIN(intrp_sclass,name) 				\
    { 								\
	TOKENPASTE(im_,name)(TOKENPASTE(TAKE,type)(0),			\
		    TOKENPASTE(TAKE,type)(TOKENPASTE(DLSZ_,type)),	\
		    TOKENPASTE(TAKE,type)(2*TOKENPASTE(DLSZ_,type)),	\
		    TOKENPASTE(TAKE,type)(3*TOKENPASTE(DLSZ_,type))); 	\
	thread(name); 						\
    } 								\
    DL_INTRP_END(name)

#define DL_GENCMD_V2(intrp_sclass,name,type)			\
    DL_IMMED_BEGIN(visible,name,( type v[2]))			\
    { 								\
	DL_EXTRA_IM_SETUP();					\
	TOKENPASTE(im_,name)(v[0],v[1]);			\
    } 								\
    DL_IMMED_END(name) 						\
    DL_CMPLR_BEGIN(visible,name,( type v[2]))			\
    { 								\
	BEGINCOMPILE(TOKENPASTE(DLSZ_,name)); 			\
	ADDINTRP(name);						\
	ADDV2(type,v);						\
	ENDCOMPILE(TOKENPASTE(DLSZ_,name)); 			\
    } 								\
    DL_CMPLR_END(name) 						\
    DL_INTRP_BEGIN(intrp_sclass,aname) 				\
    { 								\
	TOKENPASTE(im_,name)(TOKENPASTE(TAKE,type)(0),		\
		    TOKENPASTE(TAKE,type)(TOKENPASTE(DLSZ_,type)));	\
	thread(name); 						\
    } 								\
    DL_INTRP_END(name)


#define DL_GENCMD_V3(intrp_sclass,name,type)			\
    DL_IMMED_BEGIN(visible,name,( type v[3]))			\
    { 								\
	DL_EXTRA_IM_SETUP();					\
	TOKENPASTE(im_,name)(v[0],v[1],v[2]);			\
    } 								\
    DL_IMMED_END(name) 						\
    DL_CMPLR_BEGIN(visible,name,( type v[3]))			\
    { 								\
	BEGINCOMPILE(TOKENPASTE(DLSZ_,name)); 			\
	ADDINTRP(name);						\
	ADDV3(type,v);						\
	TOKENPASTE(ADDFILL,type)();				\
	ENDCOMPILE(TOKENPASTE(DLSZ_,name)); 			\
    } 								\
    DL_CMPLR_END(name) 						\
    DL_INTRP_BEGIN(intrp_sclass,name) 				\
    { 								\
	TOKENPASTE(im_,name)(TOKENPASTE(TAKE,type)(0),		\
		    TOKENPASTE(TAKE,type)(TOKENPASTE(DLSZ_,type)),	\
		    TOKENPASTE(TAKE,type)(2*TOKENPASTE(DLSZ_,type))); 	\
	thread(name); 						\
    } 								\
    DL_INTRP_END(name)

#define DL_GENCMD_V4(intrp_sclass,name,type)			\
    DL_IMMED_BEGIN(visible,name,( type v[4]))			\
    { 								\
	DL_EXTRA_IM_SETUP();					\
	TOKENPASTE(im_,name)(v[0],v[1],v[2],v[3]);		\
    } 								\
    DL_IMMED_END(name) 						\
    DL_CMPLR_BEGIN(visible,name,( type v[4]))			\
    { 								\
	BEGINCOMPILE(TOKENPASTE(DLSZ_,name)); 			\
	ADDINTRP(name);						\
	ADDV4(type,v);						\
	ENDCOMPILE(TOKENPASTE(DLSZ_,name)); 			\
    } 								\
    DL_CMPLR_END(name) 						\
    DL_INTRP_BEGIN(intrp_sclass,name) 				\
    { 								\
	TOKENPASTE(im_,name)(TOKENPASTE(TAKE,type)(0),			\
		    TOKENPASTE(TAKE,type)(TOKENPASTE(DLSZ_,type)),	\
		    TOKENPASTE(TAKE,type)(2*TOKENPASTE(DLSZ_,type)),	\
		    TOKENPASTE(TAKE,type)(3*TOKENPASTE(DLSZ_,type))); 	\
	thread(name); 						\
    } 								\
    DL_INTRP_END(name)

#if defined(LIGHT)||defined(NEWPORT)
/* 
 * the following is used only by LIGHT gfx, so to be safe its ifdef'ed
 * however, it might be usefull to others also
 */
#define DL_VERTEX(name,n,type,taketype)				\
    DL_IMMED_BEGIN(visible,name,(register type v[n]))		\
    {								\
	im_setup;						\
	TOKENPASTE(im_,name)(v);				\
    }								\
    DL_IMMED_END(name)						\
    DL_CMPLR_BEGIN(visible,name,(register type v[n]))		\
    {								\
	BEGINCOMPILE(TOKENPASTE(DLSZ_,name));			\
	ADDINTRP(name);						\
	TOKENPASTE(ADDV,n)(taketype,v);				\
	ENDCOMPILE(TOKENPASTE(DLSZ_,name));			\
    }								\
    DL_CMPLR_END(name)						\
    DL_INTRP_BEGIN(visible,name)				\
    {								\
	TOKENPASTE(im_,name)(TAKEV(taketype,0));		\
	thread(name);						\
    }								\
    DL_INTRP_END(name)
#endif

#endif	/* !__GL_IMINTERP_H__ */
