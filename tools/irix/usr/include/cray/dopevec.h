/* USMID @(#) clibinc/cray/dopevec.h	92.3	06/16/99 15:48:24 */
/*
 *      (C) COPYRIGHT CRAY RESEARCH, INC.
 *      UNPUBLISHED PROPRIETARY INFORMATION.
 *      ALL RIGHTS RESERVED.
 */
#ifndef _DOPEVEC_H                      /* prevent multiple inclusions */
#define _DOPEVEC_H

/*
 * Header file describing the Fortran 90 and CF77 Dope Vector structure
 */

#include <fortran.h>

/*
 *	STRUCTURES
 */

/*
 * Word 4 contains type and length information so the libraries can perform
 * conversion when specified through FFIO.  int_len is the container bit
 * size used on a cray.  el_len and int_len fields are the same for integer,
 * real, complex, and logical.  For ASCII character, int_len is 8 to specify
 * the length of a single character.  int_len and dec_len are not used for
 * derived type entities.  F90 array intrinsics use type and int_len.
 */

typedef struct f90_type {
#if defined(__mips) || !defined(_WORD32) || defined(_LITTLE_ENDIAN)
    unsigned int		:32;     /* used for future development */
#endif

    enum typecodes {
	DVTYPE_UNUSED	   = 0,
	DVTYPE_TYPELESS    = 1,
	DVTYPE_INTEGER	   = 2,
	DVTYPE_REAL	   = 3,
	DVTYPE_COMPLEX	   = 4,
	DVTYPE_LOGICAL	   = 5,
	DVTYPE_ASCII	   = 6,
	DVTYPE_DERIVEDBYTE = 7,
	DVTYPE_DERIVEDWORD = 8
    } 	       		type    :8;	/* type code */
    unsigned int	dpflag  :1;	/* set if declared double precision
					 * or double complex */
    enum dec_codes {
	DVD_DEFAULT	= 0,		/* KIND= and *n absent, or 
					 * KIND=expression which evaluates to
					 * the default KIND, ie.:
					 *      KIND(0) for integer 
					 *      KIND(0.0) for real 
					 *      KIND((0,0)) for complex 
					 *      KIND(.TRUE.) for logical 
					 *      KIND('A') for character 
					 * across on all ANSI-conformant
					 *  implementations. */
	DVD_KIND	= 1,		/* KIND=expression which does not 
					 * qualify to be DVD_DEFAULT or 
					 * DVD_KIND_CONST or DVD_KIND_DOUBLE */
	DVD_STAR	= 2,		/* *n is specified (example: REAL*8 */
	DVD_KIND_CONST	= 3,		/* KIND=expression constant across
					 * all implementations. */
	DVD_KIND_DOUBLE	= 4		/* KIND=expression which evaluates to
					 * KIND(1.0D0) for real across all
					 * implementations.  This code may be
					 * passed for real or complex type.  */
    } kind_or_star		:3;	/* Set if KIND= or *n appears in the
                                         * variable declaration.  Values 
					 * are from enum dec_codes */
    unsigned int	int_len :12;	/* internal length in bits of iolist
                                         * entity. 8 for character data to
                                         * indicate size of each character */
    unsigned int	dec_len :8; 	/* declared length in bytes for *n
					 * or KIND value. Ignored if
					 * kind_or_star==DVD_DEFAULT */
} f90_type_t;

typedef struct DopeVector {
    union       {
		_fcd    charptr;	/* Fortran character descriptor */
		struct {
			void	       *ptr;    /* pointer to base address */
                    			        /* or shared data desc     */
			unsigned long  el_len;	/* element length in bits  */
		} a;
    }   base_addr;

    /*
     * flags and information fields within word 3 of the header
     */
    unsigned int 	assoc     :1;	/* associated flag */
    unsigned int	ptr_alloc :1;	/* set if allocated by pointer */
    enum ptrarray {
	NOT_P_OR_A	= 0,
	POINTTR		= 1,
	ALLOC_ARRY	= 2
    } 			p_or_a    :2;	/* pointer or allocatable array. Use */
					/* enum ptrarray values.  */
    unsigned int	a_contig  :1;	/* array storage contiguous flag */
    unsigned int	          :27;	/* pad for first 32 bits	*/
    unsigned int	          :29;	/* pad for second 32-bits	*/
    unsigned int	n_dim     :3;	/* number of dimensions */
    f90_type_t		type_lens;	/* data type and lengths */
    void           	*orig_base;	/* original base address */
    unsigned long 	orig_size;	/* original size */
    /*
     * Per Dimension Information
     */
#define MAXDIM 7
    struct DvDimen {
        signed long	low_bound;	/* lower bound for ith dimension */
                                        /* may be negative */
        signed long	extent;		/* number of elts for ith dimension */
        /*
         * The stride mult is not defined in constant units so that address
         * calculations do not always require a divide by 8 or 64.  For
 	 * double and complex, stride mult has a factor of 2 in it.  For
 	 * double complex, stride mult has a factor of 4 in it.
         */
        signed long 	stride_mult;    /* stride multiplier */
    }dimension[MAXDIM];
} DopeVectorType;


/*
 *	MACROS and TYPEDEFS
 */

#define	DVTYPE_NTYPES	9		/* number of data type codes	*/
typedef enum typecodes ftype_t;		/* Fortran 90 type code		*/

/*
 *	SMSCALE computes the scale of stride_mult for a non-character
 *	dopevector.  This is the number of bytes per stride_mult.  On some
 *	architectures, this always evaluates to sizeof(long).
 *
 *	Parameter:
 *		dv	- pointer to dope vector.
 *
 *	Return value:
 *		The size of one stride_mult in bytes.
 */

#if	defined(__mips) || defined(_LITTLE_ENDIAN)
#define SMSCALE(dv) \
	(((dv)->type_lens.int_len >= 8*sizeof(_f_int4)) ? 4 : \
	(((dv)->type_lens.int_len == 8*sizeof(_f_int2)) ? 2 : \
	(((dv)->type_lens.int_len == 8*sizeof(_f_int1)) ? 1 : 4)))
#elif     !defined(_WORD32) && (defined(_F_INT4) || defined(_F_REAL4))
#define SMSCALE(dv) \
	(((dv)->type_lens.int_len < 8*sizeof(long)) ? 4 : sizeof(long))
#else
#define SMSCALE(dv) (sizeof(long))
#endif

#define CPPLOG2(x) \
	(x == 1 ? 0 : \
	(x == 2 ? 1 : \
	(x == 4 ? 2 : \
	(x == 8 ? 3 : \
	(x == 16 ? 4 : \
	(x == 32 ? 5 : \
	-1))))))

#define SMSHIFT(dv) CPPLOG2(SMSCALE(dv)/sizeof(bcont))

#endif /* !_DOPEVEC_H */

