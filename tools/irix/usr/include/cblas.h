/*
 *      (C) COPYRIGHT SILICON GRAPHICS, INC.
 *      UNPUBLISHED PROPRIETARY INFORMATION.
 *      ALL RIGHTS RESERVED.
 */

#ifndef _CBLAS_H
#define _CBLAS_H

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

/* 
 * This file provides a C interface to the Fortran BLAS routines as
 * detailed by the BLAS Technical Forum (see the documents at
 * http://www.netlib.org/cgi-bin/checkout/blast/blast.pl).  A useful 
 * feature of this interface is the provision for matrices stored in 
 * row-major order; see the intro_cblas man page for details.
 *
 * For a slightly faster, more direct interface to the Fortran BLAS 
 * routines, but which also requires column-major ordering of matrices, 
 * use the scsl_blas.h header file instead; see individual BLAS man pages
 * for details.
 */

#if defined(SCSL_COMPLEX_T)
#  undef SCSL_COMPLEX_T
#endif
#if defined(SCSL_ZOMPLEX_T)
#  undef SCSL_ZOMPLEX_T
#endif
#if defined(SCSL_CMPLX_T)
#  undef SCSL_CMPLX_T
#endif
#if defined(SCSL_ZMPLX_T)
#  undef SCSL_ZMPLX_T
#endif
#if defined(SCSL_INT_T)
#  undef SCSL_INT_T
#endif

/*
 * There are several possible approaches to handling arguments of
 * complex type.  The standard for the C interface defined by the BLAS
 * technical committee  requires that all complex arguments be prototyped 
 * as void *, which is the default employed here.  This has the advantage 
 * of allowing user-defined complex types to be passed to the library 
 * routines without complaint from the compiler. The disadvantage is that 
 * the compiler will not catch type mismatches.
 *
 * To enable stronger type checking, define SCSL_NO_VOID_ARGS at compile
 * time (e.g., cc -DSCSL_NO_VOID_ARGS).  In this case, you have several
 * choices for complex types.  One possibility is to use the SCSL types
 * scsl_complex (single precision) and scsl_zomplex (double precision),
 * and prototype the library routines using pointers to these types.
 * But if the C++ STL complex types are being used, this will be
 * detected and they will be used rather than the SCSL complex
 * types. Either way, the compiler will be able to check the types of
 * complex arguments since they have been fully prototyped.  It is also
 * possible to force the use of SCSL complex types with C++ code by
 * defining SCSL_USE_SCSL_TYPES at compile type (e.g., 
 * cc -DSCSL_NO_VOID_ARGS -DSCSL_USE_SCSL_TYPES).
 *
 * The SCSL complex types defined in releases 1.3 and later are not
 * compatible with those defined in previous BLAS interfaces.  Older
 * definitions include
 *
 *      typedef struct {float real; float imag;} CBLAS_COMPLEX;
 *	typedef struct {double real; double imag;} ZBLAS_COMPLEX;
 *	typedef struct {float real; float imag;} Complex;
 *	typedef struct {float real; float imag;} Zomplex;
 *
 * To use these or other user-defined complex types, one should instead
 * define SCSL_USER_COMPLEX_T and SCSL_USER_ZOMPLEX_T at compile time to
 * be the user-defined single and double precision complex types,
 * respectively (e.g., cc -DSCSL_NO_VOID_ARGS
 * -DSCSL_USER_COMPLEX_T=my_complex _DSCSL_USER_ZOMPLEX_T=my_zomplex ...).
 *
 * The user-defined types must satisfy the following requirements:
 *   1) The real and imaginary components must be contiguous in memory.
 *   2) Sequential array elements must be contiguous in memory.
 * The SCSL complex types are not guaranteed to satisfy these requirements
 * when used with non-SGI compilers.
 */

/* SCSL-defined complex types */

typedef struct
{
  float re;
  float im;
} __scsl_complex;
  
typedef struct
{
  double re;
  double im;
} __scsl_zomplex;

#if defined(SCSL_NO_VOID_ARGS)
#  if defined(SCSL_USER_COMPLEX_T) && defined(SCSL_USER_ZOMPLEX_T)

/* Use user-supplied complex types in the prototypes. */
 
#    define SCSL_COMPLEX_T SCSL_USER_COMPLEX_T
#    define SCSL_ZOMPLEX_T SCSL_USER_ZOMPLEX_T

#  else

/*
 * C++ has it's own class/template for complex arithmetic. If it is
 * used, the function prototypes should match the C++ conventions.
 * For the cases when it is not used, the SCSL-defined complex types
 * are used (unless SCSL_USE_SCSL_TYPES is defined), but we now use
 * names that aren't likely to conflict with other attempts to define
 * complex types.
 */

#    if defined(__cplusplus) && (defined(__sgi_template_complex) || defined(__STD_COMPLEX))
#      if !defined(SCSL_USE_SCSL_TYPES)
#        define SCSL_COMPLEX_T complex<float>
#        define SCSL_ZOMPLEX_T complex<double>
#      else
         typedef __scsl_complex scsl_complex;
         typedef __scsl_zomplex scsl_zomplex;
#        define SCSL_COMPLEX_T scsl_complex
#        define SCSL_ZOMPLEX_T scsl_zomplex
#      endif
#    else
       typedef __scsl_complex scsl_complex;
       typedef __scsl_zomplex scsl_zomplex;
#      define SCSL_COMPLEX_T scsl_complex
#      define SCSL_ZOMPLEX_T scsl_zomplex
#    endif
#  endif
#  define SCSL_CMPLX_T SCSL_COMPLEX_T
#  define SCSL_ZMPLX_T SCSL_ZOMPLEX_T
#else

/* prototype the complex arguments as void * */

#  define SCSL_COMPLEX_T void
#  define SCSL_ZOMPLEX_T void

/* This is required for the functions which return
   a complex value */
#  define SCSL_CMPLX_T __scsl_complex
#  define SCSL_ZMPLX_T __scsl_zomplex
#endif

/* 
 * Integer arguments are 4 bytes in the standard version of SCSL,
 * 8 bytes in the I8 version.
 */

#if defined(SCSL_I8_INT_ARGS)
#  define SCSL_INT_T long long
#else
#  define SCSL_INT_T int
#endif

/*
 * Enumerated and derived types
 */
#define CBLAS_INDEX SCSL_INT_T

enum CBLAS_ORDER {CblasRowMajor=101, CblasColMajor=102};
enum CBLAS_TRANSPOSE {CblasNoTrans=111, CblasTrans=112, CblasConjTrans=113};
enum CBLAS_UPLO {CblasUpper=121, CblasLower=122};
enum CBLAS_DIAG {CblasNonUnit=131, CblasUnit=132};
enum CBLAS_SIDE {CblasLeft=141, CblasRight=142};

/*
 * ===========================================================================
 * Prototypes for level 1 BLAS functions (complex are recast as routines)
 * ===========================================================================
 */

static __inline float cblas_sdot(const SCSL_INT_T N,
				 const float *X,
				 const SCSL_INT_T incX,
				 const float *Y,
				 const SCSL_INT_T incY) {
  float sdot_(const SCSL_INT_T *N,
	      const float *X,
	      const SCSL_INT_T *incX,
	      const float *Y,
	      const SCSL_INT_T *incY);

  return sdot_(&N, X, &incX, Y, &incY);
}


static __inline double cblas_ddot(const SCSL_INT_T N, 
				  const double *X, 
				  const SCSL_INT_T incX,
				  const double *Y, 
				  const SCSL_INT_T incY) {
  double ddot_(const SCSL_INT_T *N, 
	       const double *X, 
	       const SCSL_INT_T *incX, 
	       const double *Y, 
	       const SCSL_INT_T *incY);

  return ddot_(&N, X, &incX, Y, &incY);
}


/*
 * Functions having prefixes Z and C only
*/

#ifdef __INTEL_COMPILER

  /* Intel compiler passes complex function return value as first argument */

  /* cblas_[cz]dotu and cblas_[cz]dotc are not part of the CBLAS standard;
     leave these routines in w/ SCSL_[CZ]OMPLEX_T for backwards compatibility */

static __inline SCSL_CMPLX_T cblas_cdotu(const SCSL_INT_T N, 
					 const SCSL_COMPLEX_T *X, 
					 const SCSL_INT_T incX,
					 const SCSL_COMPLEX_T *Y, 
					 const SCSL_INT_T incY) {
  void cdotu_(SCSL_CMPLX_T *,
	      const SCSL_INT_T *, 
	      const SCSL_COMPLEX_T *, 
	      const SCSL_INT_T *, 
	      const SCSL_COMPLEX_T *, 
	      const SCSL_INT_T *);
  SCSL_CMPLX_T result;

  cdotu_(&result, &N, X, &incX, Y, &incY);
  return result;
}


static __inline SCSL_CMPLX_T cblas_cdotc(const SCSL_INT_T N, 
					 const SCSL_COMPLEX_T *X, 
					 const SCSL_INT_T incX,
					 const SCSL_COMPLEX_T *Y, 
					 const SCSL_INT_T incY) {
  void cdotc_(SCSL_CMPLX_T *,
	      const SCSL_INT_T *, 
	      const SCSL_COMPLEX_T *, 
	      const SCSL_INT_T *, 
	      const SCSL_COMPLEX_T *, 
	      const SCSL_INT_T *);
  SCSL_CMPLX_T result;

  cdotc_(&result, &N, X, &incX, Y, &incY);
  return result;
}


static __inline SCSL_ZMPLX_T cblas_zdotu(const SCSL_INT_T N, 
					 const SCSL_ZOMPLEX_T *X, 
					 const SCSL_INT_T incX,
					 const SCSL_ZOMPLEX_T *Y, 
					 const SCSL_INT_T incY) {
  void zdotu_(SCSL_ZMPLX_T *,
	      const SCSL_INT_T *, 
	      const SCSL_ZOMPLEX_T *, 
	      const SCSL_INT_T *, 
	      const SCSL_ZOMPLEX_T *, 
	      const SCSL_INT_T *);
  SCSL_ZMPLX_T result;

  zdotu_(&result, &N, X, &incX, Y, &incY);
  return result;
}


static __inline SCSL_ZMPLX_T cblas_zdotc(const SCSL_INT_T N, 
					 const SCSL_ZOMPLEX_T *X, 
					 const SCSL_INT_T incX,
					 const SCSL_ZOMPLEX_T *Y, 
					 const SCSL_INT_T incY) {
  void zdotc_(SCSL_ZMPLX_T *,
	      const SCSL_INT_T *, 
	      const SCSL_ZOMPLEX_T *, 
	      const SCSL_INT_T *, 
	      const SCSL_ZOMPLEX_T *, 
	      const SCSL_INT_T *);
  SCSL_ZMPLX_T result;
  
  zdotc_(&result, &N, X, &incX, Y, &incY);
  return result;
}

  /* these routines are part of the standard; complex variables are passed
     as SCSL_ZOMPLEX_T * */

static __inline void cblas_cdotu_sub(const SCSL_INT_T N, 
				     const SCSL_COMPLEX_T *X, 
				     const SCSL_INT_T incX,
				     const SCSL_COMPLEX_T *Y, 
				     const SCSL_INT_T incY, 
				     SCSL_COMPLEX_T *dotu) {
  void cdotu_(SCSL_CMPLX_T *,
	      const SCSL_INT_T *, 
	      const SCSL_COMPLEX_T *, 
	      const SCSL_INT_T *, 
	      const SCSL_COMPLEX_T *, 
	      const SCSL_INT_T *);
  
  cdotu_((SCSL_CMPLX_T *) dotu, &N, X, &incX, Y, &incY);
}


static __inline void cblas_cdotc_sub(const SCSL_INT_T N, 
				     const SCSL_COMPLEX_T *X, 
				     const SCSL_INT_T incX,
				     const SCSL_COMPLEX_T *Y, 
				     const SCSL_INT_T incY, 
				     SCSL_COMPLEX_T *dotc) {
  void cdotc_(SCSL_CMPLX_T *,
	      const SCSL_INT_T *, 
	      const SCSL_COMPLEX_T *, 
	      const SCSL_INT_T *, 
	      const SCSL_COMPLEX_T *, 
	      const SCSL_INT_T *);
  
  cdotc_((SCSL_CMPLX_T *) dotc, &N, X, &incX, Y, &incY);
}


static __inline void cblas_zdotu_sub(const SCSL_INT_T N, 
				     const SCSL_ZOMPLEX_T *X, 
				     const SCSL_INT_T incX,
				     const SCSL_ZOMPLEX_T *Y, 
				     const SCSL_INT_T incY, 
				     SCSL_ZOMPLEX_T *dotu) {
  void zdotu_(SCSL_ZMPLX_T *,
	      const SCSL_INT_T *, 
	      const SCSL_ZOMPLEX_T *, 
	      const SCSL_INT_T *,
	      const SCSL_ZOMPLEX_T *,
	      const SCSL_INT_T *);

  zdotu_((SCSL_ZMPLX_T *) dotu, &N, X, &incX, Y, &incY);
}


static __inline void cblas_zdotc_sub(const SCSL_INT_T N, 
				     const SCSL_ZOMPLEX_T *X, 
				     const SCSL_INT_T incX,
				     const SCSL_ZOMPLEX_T *Y, 
				     const SCSL_INT_T incY, 
				     SCSL_ZOMPLEX_T *dotc) {
  void zdotc_(SCSL_ZMPLX_T *,
	      const SCSL_INT_T *, 
	      const SCSL_ZOMPLEX_T *, 
	      const SCSL_INT_T *, 
	      const SCSL_ZOMPLEX_T *, 
	      const SCSL_INT_T *);

  zdotc_((SCSL_ZMPLX_T *) dotc, &N, X, &incX, Y, &incY);
}

#else

  /* cblas_[cz]dotu and cblas_[cz]dotc are not part of the CBLAS standard;
     leave these routines in w/ SCSL_[CZ]OMPLEX_T for backwards compatibility */

static __inline SCSL_CMPLX_T cblas_cdotu(const SCSL_INT_T N, 
					 const SCSL_COMPLEX_T *X, 
					 const SCSL_INT_T incX,
					 const SCSL_COMPLEX_T *Y, 
					 const SCSL_INT_T incY) {
  SCSL_CMPLX_T cdotu_(const SCSL_INT_T *N, 
		      const SCSL_COMPLEX_T *X, 
		      const SCSL_INT_T *incX, 
		      const SCSL_COMPLEX_T *Y, 
		      const SCSL_INT_T *incY);

  return cdotu_(&N, X, &incX, Y, &incY);
}


static __inline SCSL_CMPLX_T cblas_cdotc(const SCSL_INT_T N, 
					 const SCSL_COMPLEX_T *X, 
					 const SCSL_INT_T incX,
					 const SCSL_COMPLEX_T *Y, 
					 const SCSL_INT_T incY) {
  SCSL_CMPLX_T cdotc_(const SCSL_INT_T *N, 
		      const SCSL_COMPLEX_T *X, 
		      const SCSL_INT_T *incX, 
		      const SCSL_COMPLEX_T *Y, 
		      const SCSL_INT_T *incY);

  return cdotc_(&N, X, &incX, Y, &incY);
}


static __inline SCSL_ZMPLX_T cblas_zdotu(const SCSL_INT_T N, 
					 const SCSL_ZOMPLEX_T *X, 
					 const SCSL_INT_T incX,
					 const SCSL_ZOMPLEX_T *Y, 
					 const SCSL_INT_T incY) {
  SCSL_ZMPLX_T zdotu_(const SCSL_INT_T *N, 
		      const SCSL_ZOMPLEX_T *X, 
		      const SCSL_INT_T *incX, 
		      const SCSL_ZOMPLEX_T *Y, 
		      const SCSL_INT_T *incY);

  return zdotu_(&N, X, &incX, Y, &incY);
}


static __inline SCSL_ZMPLX_T cblas_zdotc(const SCSL_INT_T N, 
					 const SCSL_ZOMPLEX_T *X, 
					 const SCSL_INT_T incX,
					 const SCSL_ZOMPLEX_T *Y, 
					 const SCSL_INT_T incY) {
  SCSL_ZMPLX_T zdotc_(const SCSL_INT_T *N, 
		      const SCSL_ZOMPLEX_T *X, 
		      const SCSL_INT_T *incX, 
		      const SCSL_ZOMPLEX_T *Y, 
		      const SCSL_INT_T *incY);
  
  return zdotc_(&N, X, &incX, Y, &incY);
}

  /* these routines are part of the standard; complex variables are passed
     as SCSL_ZOMPLEX_T * */

static __inline void cblas_cdotu_sub(const SCSL_INT_T N, 
				     const SCSL_COMPLEX_T *X, 
				     const SCSL_INT_T incX,
				     const SCSL_COMPLEX_T *Y, 
				     const SCSL_INT_T incY, 
				     SCSL_COMPLEX_T *dotu) {
  SCSL_CMPLX_T cdotu_(const SCSL_INT_T *N, 
		      const SCSL_COMPLEX_T *X, 
		      const SCSL_INT_T *incX, 
		      const SCSL_COMPLEX_T *Y, 
		      const SCSL_INT_T *incY);
  
  *((SCSL_CMPLX_T *) dotu) = cdotu_(&N, X, &incX, Y, &incY);
}


static __inline void cblas_cdotc_sub(const SCSL_INT_T N, 
				     const SCSL_COMPLEX_T *X, 
				     const SCSL_INT_T incX,
				     const SCSL_COMPLEX_T *Y, 
				     const SCSL_INT_T incY, 
				     SCSL_COMPLEX_T *dotc) {
  SCSL_CMPLX_T cdotc_(const SCSL_INT_T *N, 
		      const SCSL_COMPLEX_T *X, 
		      const SCSL_INT_T *incX, 
		      const SCSL_COMPLEX_T *Y, 
		      const SCSL_INT_T *incY);
  
  *((SCSL_CMPLX_T *) dotc) = cdotc_(&N, X, &incX, Y, &incY);
}


static __inline void cblas_zdotu_sub(const SCSL_INT_T N, 
				     const SCSL_ZOMPLEX_T *X, 
				     const SCSL_INT_T incX,
				     const SCSL_ZOMPLEX_T *Y, 
				     const SCSL_INT_T incY, 
				     SCSL_ZOMPLEX_T *dotu) {
  SCSL_ZMPLX_T zdotu_(const SCSL_INT_T *N, 
		      const SCSL_ZOMPLEX_T *X, 
		      const SCSL_INT_T *incX,
		      const SCSL_ZOMPLEX_T *Y,
		      const SCSL_INT_T *incY);

  *((SCSL_ZMPLX_T *) dotu) = zdotu_(&N, X, &incX, Y, &incY);
}


static __inline void cblas_zdotc_sub(const SCSL_INT_T N, 
				     const SCSL_ZOMPLEX_T *X, 
				     const SCSL_INT_T incX,
				     const SCSL_ZOMPLEX_T *Y, 
				     const SCSL_INT_T incY, 
				     SCSL_ZOMPLEX_T *dotc) {
  SCSL_ZMPLX_T zdotc_(const SCSL_INT_T *N, 
		      const SCSL_ZOMPLEX_T *X, 
		      const SCSL_INT_T *incX, 
		      const SCSL_ZOMPLEX_T *Y, 
		      const SCSL_INT_T *incY);

  *((SCSL_ZMPLX_T *) dotc) = zdotc_(&N, X, &incX, Y, &incY);
}

#endif


/*
 * Functions having prefixes S D SC DZ
 */

static __inline float cblas_snrm2(const SCSL_INT_T N, 
				  const float *X, 
				  const SCSL_INT_T incX) {
  float snrm2_(const SCSL_INT_T *N, 
	       const float  *X, 
	       const SCSL_INT_T *incX);

  return snrm2_(&N, X, &incX);
}


static __inline float cblas_sasum(const SCSL_INT_T N, 
				  const float *X, 
				  const SCSL_INT_T incX) {
  float sasum_(const SCSL_INT_T *N, 
	       const float  *X, 
	       const SCSL_INT_T *incX);

  return sasum_(&N, X, &incX);
}


static __inline float cblas_ssum(const SCSL_INT_T N, 
				 const float *X, 
				 const SCSL_INT_T incX){
  float ssum_(const SCSL_INT_T *N, 
	      const float  *X, 
	      const SCSL_INT_T *incX);

  return ssum_(&N, X, &incX);
}


static __inline double cblas_dnrm2(const SCSL_INT_T N, 
				   const double *X, 
				   const SCSL_INT_T incX) {
  double dnrm2_(const SCSL_INT_T *N, 
		const double  *X, 
		const SCSL_INT_T *incX);

  return dnrm2_(&N, X, &incX);
}


static __inline double cblas_dasum(const SCSL_INT_T N, 
				   const double  *X, 
				   const SCSL_INT_T incX) {
  double dasum_(const SCSL_INT_T *N, 
		const double  *X, 
		const SCSL_INT_T *incX);

  return dasum_(&N, X, &incX);
}


static __inline double cblas_dsum(const SCSL_INT_T N, 
				  const double  *X, 
				  const SCSL_INT_T incX) {
  double dsum_(const SCSL_INT_T *N, 
	       const double  *X, 
	       const SCSL_INT_T *incX);

  return dsum_(&N, X, &incX);
}


static __inline float cblas_scnrm2(const SCSL_INT_T N, 
				   const SCSL_COMPLEX_T *X, 
				   const SCSL_INT_T incX) {
  float scnrm2_(const SCSL_INT_T *N,
		const SCSL_COMPLEX_T *X,
		const SCSL_INT_T *incX);

  return scnrm2_(&N, X, &incX);
}


static __inline float cblas_scasum(const SCSL_INT_T N, 
				   const SCSL_COMPLEX_T *X, 
				   const SCSL_INT_T incX) {
  float scasum_(const SCSL_INT_T *N,
		const SCSL_COMPLEX_T *X,
		const SCSL_INT_T *incX);

  return scasum_(&N, X, &incX);
}


static __inline double cblas_dznrm2(const SCSL_INT_T N,
				    const SCSL_ZOMPLEX_T *X,
				    const SCSL_INT_T incX) {
  double dznrm2_(const SCSL_INT_T *N,
		 const SCSL_ZOMPLEX_T *X,
		 const SCSL_INT_T *incX);

  return dznrm2_(&N, X, &incX);
}


static __inline double cblas_dzasum(const SCSL_INT_T N,
				    const SCSL_ZOMPLEX_T *X,
				    const SCSL_INT_T incX) {
  double dzasum_(const SCSL_INT_T *N, 
		 const SCSL_ZOMPLEX_T *X,
		 const SCSL_INT_T *incX);

  return dzasum_(&N, X, &incX);
}


#ifdef __INTEL_COMPILER

  /* Intel compiler passes complex function return value as first argument */

static __inline SCSL_CMPLX_T cblas_csum(const SCSL_INT_T N, 
					const SCSL_COMPLEX_T *X, 
					const SCSL_INT_T incX) {
  void csum_(SCSL_CMPLX_T *,
	     const SCSL_INT_T *, 
	     const SCSL_COMPLEX_T *, 
	     const SCSL_INT_T *);
  SCSL_CMPLX_T result;

  csum_(&result, &N, X, &incX);
  return result;
}


static __inline void cblas_csum_sub(const SCSL_INT_T N, 
				    const SCSL_COMPLEX_T *X, 
				    const SCSL_INT_T incX,
				    SCSL_COMPLEX_T *sum) {
  void csum_(SCSL_CMPLX_T *,
	     const SCSL_INT_T *, 
	     const SCSL_COMPLEX_T *, 
	     const SCSL_INT_T *);

  csum_((SCSL_CMPLX_T *) sum, &N, X, &incX);
}


static __inline SCSL_ZMPLX_T cblas_zsum(const SCSL_INT_T N, 
					const SCSL_ZOMPLEX_T *X, 
					const SCSL_INT_T incX) {
  void zsum_(SCSL_ZMPLX_T *,
	     const SCSL_INT_T *, 
	     const SCSL_ZOMPLEX_T *, 
	     const SCSL_INT_T *);
  SCSL_ZMPLX_T result;

  zsum_(&result, &N, X, &incX);
  return result;
}


static __inline void cblas_zsum_sub(const SCSL_INT_T N, 
				    const SCSL_ZOMPLEX_T *X, 
				    const SCSL_INT_T incX,
				    SCSL_ZOMPLEX_T *sum) {
  void zsum_(SCSL_ZMPLX_T *,
	     const SCSL_INT_T *, 
	     const SCSL_ZOMPLEX_T *, 
	     const SCSL_INT_T *);

  zsum_((SCSL_ZMPLX_T *) sum, &N, X, &incX);
}

#else

static __inline SCSL_CMPLX_T cblas_csum(const SCSL_INT_T N, 
					const SCSL_COMPLEX_T *X, 
					const SCSL_INT_T incX) {
  SCSL_CMPLX_T csum_(const SCSL_INT_T *N, 
		     const SCSL_COMPLEX_T *X, 
		     const SCSL_INT_T *incX);

  return csum_(&N, X, &incX);
}


static __inline void cblas_csum_sub(const SCSL_INT_T N, 
				    const SCSL_COMPLEX_T *X, 
				    const SCSL_INT_T incX,
				    SCSL_COMPLEX_T *sum) {
  SCSL_CMPLX_T csum_(const SCSL_INT_T *N, 
		     const SCSL_COMPLEX_T *X, 
		     const SCSL_INT_T *incX);

  *((SCSL_CMPLX_T *) sum) = csum_(&N, X, &incX);
}


static __inline SCSL_ZMPLX_T cblas_zsum(const SCSL_INT_T N, 
					const SCSL_ZOMPLEX_T *X, 
					const SCSL_INT_T incX) {
  SCSL_ZMPLX_T zsum_(const SCSL_INT_T *N, 
		     const SCSL_ZOMPLEX_T *X, 
		     const SCSL_INT_T *incX);

  return zsum_(&N, X, &incX);
}


static __inline void cblas_zsum_sub(const SCSL_INT_T N, 
				    const SCSL_ZOMPLEX_T *X, 
				    const SCSL_INT_T incX,
				    SCSL_ZOMPLEX_T *sum) {
  SCSL_ZMPLX_T zsum_(const SCSL_INT_T *N, 
		     const SCSL_ZOMPLEX_T *X, 
		     const SCSL_INT_T *incX);

  *((SCSL_ZMPLX_T *) sum) = zsum_(&N, X, &incX);
}

#endif


/*
 * Functions having standard 4 prefixes (S D C Z)
 */

static __inline CBLAS_INDEX cblas_isamax(const SCSL_INT_T N,
					 const float *X, 
					 const SCSL_INT_T incX) {
  CBLAS_INDEX isamax_(const SCSL_INT_T *N,
		      const float *X, 
		      const SCSL_INT_T *incX);

  return (isamax_(&N, X, &incX) - 1);
}


static __inline CBLAS_INDEX cblas_ismax(const SCSL_INT_T N,
					const float *X, 
					const SCSL_INT_T incX) {
  CBLAS_INDEX ismax_(const SCSL_INT_T *N, 
		     const float *X, 
		     const SCSL_INT_T *incX);

  return (ismax_(&N, X, &incX) - 1);
}


static __inline CBLAS_INDEX cblas_isamin(const SCSL_INT_T N,
					 const float *X, 
					 const SCSL_INT_T incX) {
  CBLAS_INDEX isamin_(const SCSL_INT_T *N,
		      const float *X,
		      const SCSL_INT_T *incX);
  
  return (isamin_(&N, X, &incX) - 1);
}


static __inline CBLAS_INDEX cblas_ismin(const SCSL_INT_T N,
					const float *X, 
					const SCSL_INT_T incX) {
  CBLAS_INDEX ismin_(const SCSL_INT_T *N, 
		     const float *X,
		     const SCSL_INT_T *incX);

  return (ismin_(&N, X, &incX) - 1);
}


static __inline CBLAS_INDEX cblas_idamax(const SCSL_INT_T N, 
					 const double *X, 
					 const SCSL_INT_T incX) {
  CBLAS_INDEX idamax_(const SCSL_INT_T *N, 
		      const double *X,
		      const SCSL_INT_T *incX);

  return (idamax_(&N, X, &incX) - 1);
}


static __inline CBLAS_INDEX cblas_idmax(const SCSL_INT_T N, 
					const double *X, 
					const SCSL_INT_T incX) {
  CBLAS_INDEX idmax_(const SCSL_INT_T *N, 
		     const double *X,
		     const SCSL_INT_T *incX);

  return (idmax_(&N, X, &incX) - 1);
}


static __inline CBLAS_INDEX cblas_idamin(const SCSL_INT_T N, 
					 const double *X, 
					 const SCSL_INT_T incX) {
  CBLAS_INDEX idamin_(const SCSL_INT_T *N, 
		      const double *X,
		      const SCSL_INT_T *incX);

  return (idamin_(&N, X, &incX) - 1);
}


static __inline CBLAS_INDEX cblas_idmin(const SCSL_INT_T N,
					const double *X, 
					const SCSL_INT_T incX) {
  CBLAS_INDEX idmin_(const SCSL_INT_T *N, 
		     const double *X,
		     const SCSL_INT_T *incX);

  return (idmin_(&N, X, &incX) - 1);
}


static __inline CBLAS_INDEX cblas_icamax(const SCSL_INT_T N, 
					 const SCSL_COMPLEX_T *X, 
					 const SCSL_INT_T incX) {
  CBLAS_INDEX icamax_(const SCSL_INT_T *N, 
		      const SCSL_COMPLEX_T *X,
		      const SCSL_INT_T *incX);

  return (icamax_(&N, X, &incX) - 1);
}


static __inline CBLAS_INDEX cblas_izamax(const SCSL_INT_T N, 
					 const SCSL_ZOMPLEX_T *X, 
					 const SCSL_INT_T incX) {
  CBLAS_INDEX izamax_(const SCSL_INT_T *N, 
		      const SCSL_ZOMPLEX_T *X, 
		      const SCSL_INT_T *incX);

  return (izamax_(&N, X, &incX) - 1);
}

/*
 * ===========================================================================
 * Prototypes for level 1 BLAS routines
 * ===========================================================================
 */
/*
 * Routines with standard 4 prefixes (s, d, c, z)
 */

static __inline void cblas_sswap(const SCSL_INT_T N, 
				 float *X, 
				 const SCSL_INT_T incX,
				 float *Y, 
				 const SCSL_INT_T incY) {
  void sswap_(const SCSL_INT_T *N, 
	      float *X, 
	      const SCSL_INT_T *incX,
	      float *Y, 
	      const SCSL_INT_T *incY);

  sswap_(&N, X, &incX, Y, &incY);
}


static __inline void cblas_scopy(const SCSL_INT_T N, 
				 const float *X, 
				 const SCSL_INT_T incX,
				 float *Y, 
				 const SCSL_INT_T incY) {
  void scopy_(const SCSL_INT_T *N, 
	      const float *X, 
	      const SCSL_INT_T *incX,
	      float *Y, 
	      const SCSL_INT_T *incY);

  scopy_(&N, X, &incX, Y, &incY);
}


static __inline void cblas_saxpy(const SCSL_INT_T N, 
				 const float alpha, 
				 const float *X,
				 const SCSL_INT_T incX, 
				 float *Y, 
				 const SCSL_INT_T incY) {
  void saxpy_(const SCSL_INT_T *N, 
	      const float *alpha, 
	      const float *X,
	      const SCSL_INT_T *incX, 
	      float *Y, 
	      const SCSL_INT_T *incY);

  saxpy_(&N, &alpha, X, &incX, Y, &incY);
}


static __inline void cblas_saxpby(const SCSL_INT_T N, 
				  const float alpha, 
				  const float *X, 
				  const SCSL_INT_T incX, 
				  const float beta, 
				  float *Y, 
				  const SCSL_INT_T incY) {
  void saxpby_(const SCSL_INT_T *N, 
	       const float *alpha, 
	       const float *X,
	       const SCSL_INT_T *incX, 
	       const float *beta, 
	       float *Y, 
	       const SCSL_INT_T *incY);

  saxpby_(&N, &alpha, X, &incX, &beta, Y, &incY);
}


static __inline void cblas_shad(const SCSL_INT_T N, 
				const float alpha, 
				const float *X, 
				const SCSL_INT_T incX, 
				const float *Y, 
				const SCSL_INT_T incY, 
				const float beta, 
				float *Z, 
				const SCSL_INT_T incZ) {
  void shad_(const SCSL_INT_T *N, 
	     const float *alpha, 
	     const float *X,
	     const SCSL_INT_T *incX, 
	     const float *Y,
	     const SCSL_INT_T *incY, 
	     const float *beta, 
	     float *Z, 
	     const SCSL_INT_T *incZ);

  shad_(&N, &alpha, X, &incX, Y, &incY, &beta, Z, &incZ);
}


static __inline void cblas_dswap(const SCSL_INT_T N, 
				 double *X, 
				 const SCSL_INT_T incX,
				 double *Y, 
				 const SCSL_INT_T incY) {
  void dswap_(const SCSL_INT_T *N, 
	      double *X, 
	      const SCSL_INT_T *incX,
	      double *Y, 
	      const SCSL_INT_T *incY);

  dswap_(&N, X, &incX, Y, &incY);
}


static __inline void cblas_dcopy(const SCSL_INT_T N, 
				 const double *X, 
				 const SCSL_INT_T incX,
				 double *Y, 
				 const SCSL_INT_T incY) {

  void dcopy_(const SCSL_INT_T *N, 
	      const double *X,
	      const SCSL_INT_T *incX,
	      double *Y,
	      const SCSL_INT_T *incY);

  dcopy_(&N, X, &incX, Y, &incY);
}


static __inline void cblas_daxpy(const SCSL_INT_T N, 
				 const double alpha, 
				 const double *X,
				 const SCSL_INT_T incX, 
				 double *Y, 
				 const SCSL_INT_T incY) {
  void daxpy_(const SCSL_INT_T *N, 
	      const double *alpha, 
	      const double *X,
	      const SCSL_INT_T *incX, 
	      double *Y, 
	      const SCSL_INT_T *incY);

  daxpy_(&N, &alpha, X, &incX, Y, &incY);
}


static __inline void cblas_daxpby(const SCSL_INT_T N,
				  const double alpha, 
				  const double *X,
				  const SCSL_INT_T incX, 
				  const double beta, 
				  double *Y, 
				  const SCSL_INT_T incY) {
  void daxpby_(const SCSL_INT_T *N, 
	       const double *alpha, 
	       const double *X,
	       const SCSL_INT_T *incX, 
	       const double *beta, 
	       double *Y, 
	       const SCSL_INT_T *incY);

  daxpby_(&N, &alpha, X, &incX, &beta, Y, &incY);
}


static __inline void cblas_dhad(const SCSL_INT_T N, 
				const double alpha, 
				const double *X, 
				const SCSL_INT_T incX, 
				const double *Y, 
				const SCSL_INT_T incY, 
				const double beta, 
				double *Z, 
				const SCSL_INT_T incZ) {
  void dhad_(const SCSL_INT_T *N, 
	     const double *alpha, 
	     const double *X,
	     const SCSL_INT_T *incX, 
	     const double *Y,
	     const SCSL_INT_T *incY, 
	     const double *beta, 
	     double *Z, 
	     const SCSL_INT_T *incZ);

  dhad_(&N, &alpha, X, &incX, Y, &incY, &beta, Z, &incZ);
}


static __inline void cblas_cswap(const SCSL_INT_T N, 
				 SCSL_COMPLEX_T *X, 
				 const SCSL_INT_T incX,
				 SCSL_COMPLEX_T *Y, 
				 const SCSL_INT_T incY) {
  void cswap_(const SCSL_INT_T *N, 
	      SCSL_COMPLEX_T *X, 
	      const SCSL_INT_T *incX,
	      SCSL_COMPLEX_T *Y, 
	      const SCSL_INT_T *incY);

  cswap_(&N, X, &incX, Y, &incY);
}


static __inline void cblas_ccopy(const SCSL_INT_T N,
				 const SCSL_COMPLEX_T *X,
				 const SCSL_INT_T incX,
				 SCSL_COMPLEX_T *Y, 
				 const SCSL_INT_T incY) {
  void ccopy_(const SCSL_INT_T *N, 
	      const SCSL_COMPLEX_T *X, 
	      const SCSL_INT_T *incX,
	      SCSL_COMPLEX_T *Y, 
	      const SCSL_INT_T *incY);

  ccopy_(&N, X, &incX, Y, &incY);
}


static __inline void cblas_caxpy(const SCSL_INT_T N, 
				 const SCSL_COMPLEX_T *alpha, 
				 const SCSL_COMPLEX_T *X,
				 const SCSL_INT_T incX, 
				 SCSL_COMPLEX_T *Y, 
				 const SCSL_INT_T incY) {
  void caxpy_(const SCSL_INT_T *N, 
	      const SCSL_COMPLEX_T *alpha, 
	      const SCSL_COMPLEX_T *X,
	      const SCSL_INT_T *incX, 
	      SCSL_COMPLEX_T *Y, 
	      const SCSL_INT_T *incY);

  caxpy_(&N, alpha, X, &incX, Y, &incY);
}


static __inline void cblas_caxpby(const SCSL_INT_T N, 
				  const SCSL_COMPLEX_T *alpha, 
				  const SCSL_COMPLEX_T *X, 
				  const SCSL_INT_T incX, 
				  const SCSL_COMPLEX_T *beta, 
				  SCSL_COMPLEX_T *Y, 
				  const SCSL_INT_T incY) {
  void caxpby_(const SCSL_INT_T *N, 
	       const SCSL_COMPLEX_T *alpha, 
	       const SCSL_COMPLEX_T *X,
	       const SCSL_INT_T *incX, 
	       const SCSL_COMPLEX_T *beta, 
	       SCSL_COMPLEX_T *Y, 
	       const SCSL_INT_T *incY);

  caxpby_(&N, alpha, X, &incX, beta, Y, &incY);
}


static __inline void cblas_chad(const SCSL_INT_T N, 
				const SCSL_COMPLEX_T *alpha, 
				const SCSL_COMPLEX_T *X, 
				const SCSL_INT_T incX, 
				const SCSL_COMPLEX_T *Y, 
				const SCSL_INT_T incY, 
				const SCSL_COMPLEX_T *beta, 
				SCSL_COMPLEX_T *Z, 
				const SCSL_INT_T incZ) {
  void chad_(const SCSL_INT_T *N, 
	     const SCSL_COMPLEX_T *alpha, 
	     const SCSL_COMPLEX_T *X,
	     const SCSL_INT_T *incX, 
	     const SCSL_COMPLEX_T *Y,
	     const SCSL_INT_T *incY, 
	     const SCSL_COMPLEX_T *beta, 
	     SCSL_COMPLEX_T *Z, 
	     const SCSL_INT_T *incZ);

  chad_(&N, alpha, X, &incX, Y, &incY, beta, Z, &incZ);
}


static __inline void cblas_zswap(const SCSL_INT_T N, 
				 SCSL_ZOMPLEX_T *X, 
				 const SCSL_INT_T incX, 
				 SCSL_ZOMPLEX_T *Y, 
				 const SCSL_INT_T incY) {
  void zswap_(const SCSL_INT_T *N, 
	      SCSL_ZOMPLEX_T *X, 
	      const SCSL_INT_T *incX, 
	      SCSL_ZOMPLEX_T *Y,
	      const SCSL_INT_T *incY);

  zswap_(&N, X, &incX, Y, &incY);
}


static __inline void cblas_zcopy(const SCSL_INT_T N, 
				 const SCSL_ZOMPLEX_T *X, 
				 const SCSL_INT_T incX,
				 SCSL_ZOMPLEX_T *Y, 
				 const SCSL_INT_T incY) {
  void zcopy_(const SCSL_INT_T *N, 
	      const SCSL_ZOMPLEX_T *X,
	      const SCSL_INT_T *incX,
	      SCSL_ZOMPLEX_T *Y,
	      const SCSL_INT_T *incY);
  
  zcopy_(&N, X, &incX, Y, &incY);
}


static __inline void cblas_zaxpy(const SCSL_INT_T N, 
				 const SCSL_ZOMPLEX_T *alpha, 
				 const SCSL_ZOMPLEX_T *X,
				 const SCSL_INT_T incX,
				 SCSL_ZOMPLEX_T *Y, 
				 const SCSL_INT_T incY) {
  void zaxpy_(const SCSL_INT_T *N, 
	      const SCSL_ZOMPLEX_T *alpha, 
	      const SCSL_ZOMPLEX_T *X,
	      const SCSL_INT_T *incX, 
	      SCSL_ZOMPLEX_T *Y,
	      const SCSL_INT_T *incY);

  zaxpy_(&N, alpha, X, &incX, Y, &incY);
}


static __inline void cblas_zaxpby(const SCSL_INT_T N, 
				  const SCSL_ZOMPLEX_T *alpha, 
				  const SCSL_ZOMPLEX_T *X, 
				  const SCSL_INT_T incX, 
				  const SCSL_ZOMPLEX_T *beta, 
				  SCSL_ZOMPLEX_T *Y, 
				  const SCSL_INT_T incY) {
  void zaxpby_(const SCSL_INT_T *N, 
	       const SCSL_ZOMPLEX_T *alpha, 
	       const SCSL_ZOMPLEX_T *X,
	       const SCSL_INT_T *incX, 
	       const SCSL_ZOMPLEX_T *beta, 
	       SCSL_ZOMPLEX_T *Y, 
	       const SCSL_INT_T *incY);

  zaxpby_(&N, alpha, X, &incX, beta, Y, &incY);
}


static __inline void cblas_zhad(const SCSL_INT_T N, 
				const SCSL_ZOMPLEX_T *alpha, 
				const SCSL_ZOMPLEX_T *X, 
				const SCSL_INT_T incX, 
				const SCSL_ZOMPLEX_T *Y, 
				const SCSL_INT_T incY, 
				const SCSL_ZOMPLEX_T *beta, 
				SCSL_ZOMPLEX_T *Z, 
				const SCSL_INT_T incZ) {
  void zhad_(const SCSL_INT_T *N, 
	     const SCSL_ZOMPLEX_T *alpha, 
	     const SCSL_ZOMPLEX_T *X,
	     const SCSL_INT_T *incX, 
	     const SCSL_ZOMPLEX_T *Y,
	     const SCSL_INT_T *incY, 
	     const SCSL_ZOMPLEX_T *beta, 
	     SCSL_ZOMPLEX_T *Z, 
	     const SCSL_INT_T *incZ);

  zhad_(&N, alpha, X, &incX, Y, &incY,beta, Z, &incZ);
}

/*
 * Routines with S and D prefix only
 */

static __inline void cblas_srotg(float *a,
				 float *b,
				 float *c,
				 float *s) {
  void srotg_(float *a,
	      float *b,
	      float *c,
	      float *s);

  srotg_(a, b, c, s);
}


static __inline void cblas_srotmg(float *d1, 
				  float *d2, 
				  float *b1, 
				  const float b2, 
				  float *P) {
  void srotmg_(float *d1, 
	       float *d2,
	       float *b1, 
	       const float *b2, 
	       float *P);

  srotmg_(d1, d2, b1, &b2, P);
}


static __inline void cblas_srot(const SCSL_INT_T N, 
				float *X, 
				const SCSL_INT_T incX,
				float *Y, 
				const SCSL_INT_T incY, 
				const float c, 
				const float s) {
  void srot_(const SCSL_INT_T *N, 
	     float *X, 
	     const SCSL_INT_T *incX,
	     float *Y, 
	     const SCSL_INT_T *incY, 
	     const float *c, 
	     const float *s);

  srot_(&N, X, &incX, Y, &incY, &c, &s);
}


static __inline void cblas_srotm(const SCSL_INT_T N, 
				 float *X, 
				 const SCSL_INT_T incX,
				 float *Y, 
				 const SCSL_INT_T incY, 
				 const float *P) {
  void srotm_(const SCSL_INT_T *N, 
	      float *X,
	      const SCSL_INT_T *incX,
	      float *Y, 
	      const SCSL_INT_T *incY, 
	      const float *P);

  srotm_(&N, X, &incX, Y, &incY, P);
}


static __inline void cblas_drotg(double *a, 
				 double *b,
				 double *c,
				 double *s) {
  void drotg_(double *a, 
	      double *b, 
	      double *c, 
	      double *s);

  drotg_(a, b, c, s);
}


static __inline void cblas_drotmg(double *d1, 
				  double *d2, 
				  double *b1, 
				  const double b2, 
				  double *P) {
  void drotmg_(double *d1, 
	       double *d2, 
	       double *b1,
	       const double *b2, 
	       double *P);

  drotmg_(d1, d2, b1, &b2, P);
}


static __inline void cblas_drot(const SCSL_INT_T N, 
				double *X, 
				const SCSL_INT_T incX,
				double *Y, 
				const SCSL_INT_T incY, 
				const double c, 
				const double s) {
  void drot_(const SCSL_INT_T *N, 
	     double *X, 
	     const SCSL_INT_T *incX,
	     double *Y,
	     const SCSL_INT_T *incY, 
	     const double *c, 
	     const double *s);

  drot_(&N, X, &incX, Y, &incY, &c, &s);
}


static __inline void cblas_drotm(const SCSL_INT_T N, 
				 double *X, 
				 const SCSL_INT_T incX,
				 double *Y, 
				 const SCSL_INT_T incY, 
				 const double *P) {
  void drotm_ (const SCSL_INT_T *N, 
	       double *X,
	       const SCSL_INT_T *incX,
	       double *Y, 
	       const SCSL_INT_T *incY, 
	       const double *P);

  drotm_(&N, X, &incX, Y, &incY, P);
}

/*
 * Routines with S D C Z CS and ZD prefixes
 */

static __inline void cblas_crot(const SCSL_INT_T N, 
				SCSL_COMPLEX_T *X, 
				const SCSL_INT_T incX,
				SCSL_COMPLEX_T *Y, 
				const SCSL_INT_T incY, 
				const float c, 
				const SCSL_COMPLEX_T *s) {
  void crot_(const SCSL_INT_T *N, 
	     SCSL_COMPLEX_T *X, 
	     const SCSL_INT_T *incX,
	     SCSL_COMPLEX_T *Y, 
	     const SCSL_INT_T *incY, 
	     const float *c, 
	     const SCSL_COMPLEX_T *s);

  crot_(&N, X, &incX, Y, &incY, &c, s);
}


static __inline void cblas_csrot(const SCSL_INT_T N, 
				 SCSL_COMPLEX_T *X, 
				 const SCSL_INT_T incX,
				 SCSL_COMPLEX_T *Y, 
				 const SCSL_INT_T incY, 
				 const float c, 
				 const float s) {
  void csrot_(const SCSL_INT_T *N, 
	      SCSL_COMPLEX_T *X, 
	      const SCSL_INT_T *incX,
	      SCSL_COMPLEX_T *Y, 
	      const SCSL_INT_T *incY, 
	      const float *c, 
	      const float *s);

  csrot_(&N, X, &incX, Y, &incY, &c, &s);
}


static __inline void cblas_crotg(SCSL_COMPLEX_T *a,
				 SCSL_COMPLEX_T *b,
				 float *c,
				 SCSL_COMPLEX_T *s) {
  void crotg_(SCSL_COMPLEX_T *a,
	      SCSL_COMPLEX_T *b,
	      float *c,
	      SCSL_COMPLEX_T *s);

  crotg_(a, b, c, s);
}


static __inline void cblas_sscal(const SCSL_INT_T N, 
				 const float alpha, 
				 float *X, 
				 const SCSL_INT_T incX) {
  void sscal_(const SCSL_INT_T *N, 
	      const float *alpha,
	      float *X,
	      const SCSL_INT_T *incX);

  sscal_(&N, &alpha, X, &incX);
}


static __inline void cblas_dscal(const SCSL_INT_T N, 
				 const double alpha, 
				 double *X, 
				 const SCSL_INT_T incX) {
  void dscal_(const SCSL_INT_T *N, 
	      const double *alpha, 
	      double *X,
	      const SCSL_INT_T *incX);

  dscal_(&N, &alpha, X, &incX);
}


static __inline void cblas_cscal(const SCSL_INT_T N,
				 const SCSL_COMPLEX_T *alpha, 
				 SCSL_COMPLEX_T *X,
				 const SCSL_INT_T incX) {
  void cscal_(const SCSL_INT_T *N,
	      const SCSL_COMPLEX_T *alpha,
	      SCSL_COMPLEX_T *X,
	      const SCSL_INT_T *incX);

  cscal_(&N, alpha, X, &incX);
}


static __inline void cblas_zrot(const SCSL_INT_T N, 
				SCSL_ZOMPLEX_T *X, 
				const SCSL_INT_T incX,
				SCSL_ZOMPLEX_T *Y, 
				const SCSL_INT_T incY, 
				const double c, 
				const SCSL_ZOMPLEX_T *s) {
  void zrot_(const SCSL_INT_T *N, 
	     SCSL_ZOMPLEX_T *X, 
	     const SCSL_INT_T *incX,
	     SCSL_ZOMPLEX_T *Y,
	     const SCSL_INT_T *incY, 
	     const double *c, 
	     const SCSL_ZOMPLEX_T *s);

  zrot_(&N, X, &incX, Y, &incY, &c, s);
}


static __inline void cblas_zdrot(const SCSL_INT_T N, 
				 SCSL_ZOMPLEX_T *X, 
				 const SCSL_INT_T incX,
				 SCSL_ZOMPLEX_T *Y, 
				 const SCSL_INT_T incY, 
				 const double c, 
				 const double s) {
  void zdrot_(const SCSL_INT_T *N, 
	      SCSL_ZOMPLEX_T *X, 
	      const SCSL_INT_T *incX,
	      SCSL_ZOMPLEX_T *Y,
	      const SCSL_INT_T *incY, 
	      const double *c, 
	      const double *s);

  zdrot_(&N, X, &incX, Y, &incY, &c, &s);
}


static __inline void cblas_zrotg(SCSL_ZOMPLEX_T *a,
				 SCSL_ZOMPLEX_T *b,
				 double *c,
				 SCSL_ZOMPLEX_T *s) {
  void zrotg_(SCSL_ZOMPLEX_T *a,
	      SCSL_ZOMPLEX_T *b,
	      double *c,
	      SCSL_ZOMPLEX_T *s);

  zrotg_(a, b, c, s);
}


static __inline void cblas_zscal(const SCSL_INT_T N, 
				 const SCSL_ZOMPLEX_T *alpha, 
				 SCSL_ZOMPLEX_T *X,
				 const SCSL_INT_T incX) {
  void zscal_(const SCSL_INT_T *N,
	      const SCSL_ZOMPLEX_T *alpha,
	      SCSL_ZOMPLEX_T *X,
	      const SCSL_INT_T *incX);

  zscal_(&N, alpha, X, &incX);
}


static __inline void cblas_csscal(const SCSL_INT_T N,
				  const float alpha, 
				  SCSL_COMPLEX_T *X,
				  const SCSL_INT_T incX) {
  void csscal_(const SCSL_INT_T *N,
	       const float *alpha,
	       SCSL_COMPLEX_T *X, 
	       const SCSL_INT_T *incX);

  csscal_(&N, &alpha, X, &incX);
}


static __inline void cblas_zdscal(const SCSL_INT_T N, 
				  const double alpha, 
				  SCSL_ZOMPLEX_T *X, 
				  const SCSL_INT_T incX) {
  void zdscal_(const SCSL_INT_T *N, 
	       const double *alpha,
	       SCSL_ZOMPLEX_T *X, 
	       const SCSL_INT_T *incX);

  zdscal_(&N, &alpha, X, &incX);
}

/*
 * ===========================================================================
 * Prototypes for level 2 BLAS
 * ===========================================================================
 */
/*
 * Routines with standard 4 prefixes (S, D, C, Z)
 */

void cblas_sgemv(const enum CBLAS_ORDER order,
                 const enum CBLAS_TRANSPOSE TransA, const SCSL_INT_T M, const SCSL_INT_T N,
                 const float alpha, const float *A, const SCSL_INT_T lda,
                 const float *X, const SCSL_INT_T incX, const float beta,
                 float *Y, const SCSL_INT_T incY);
void cblas_strmv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const SCSL_INT_T N, const float *A, const SCSL_INT_T lda,
                 float *X, const SCSL_INT_T incX);
void cblas_strsv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const SCSL_INT_T N, const float *A, const SCSL_INT_T lda, float *X,
                 const SCSL_INT_T incX);
void cblas_sgbmv(const enum CBLAS_ORDER order, 
                 const enum CBLAS_TRANSPOSE TransA,
                 const SCSL_INT_T M, const SCSL_INT_T N, const SCSL_INT_T Kl, const SCSL_INT_T Ku,
                 const float alpha, const float *A, const SCSL_INT_T lda,
                 const float *X, const SCSL_INT_T incX, const float beta,
                 float *Y, const SCSL_INT_T incY);
void cblas_stbmv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const SCSL_INT_T N, const SCSL_INT_T K, const float *A, const SCSL_INT_T lda,
                 float *X, const SCSL_INT_T incX);
void cblas_stbsv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const SCSL_INT_T N, const SCSL_INT_T K, const float *A, const SCSL_INT_T lda,
                 float *X, const SCSL_INT_T incX);
void cblas_sspmv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const SCSL_INT_T N, const float  alpha, const float *AP,
                 const float  *X, const SCSL_INT_T incX, const float  beta, 
                 float  *Y, const SCSL_INT_T incY);
void cblas_stpsv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const SCSL_INT_T N, const float *Ap, float *X, const SCSL_INT_T incX);
void cblas_stpmv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const SCSL_INT_T N, const float *Ap, float *X, const SCSL_INT_T incX);

void cblas_dgemv(const enum CBLAS_ORDER order,
                 const enum CBLAS_TRANSPOSE TransA, const SCSL_INT_T M, const SCSL_INT_T N,
                 const double alpha, const double *A, const SCSL_INT_T lda,
                 const double *X, const SCSL_INT_T incX, const double beta,
                 double *Y, const SCSL_INT_T incY);
void cblas_dtrmv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const SCSL_INT_T N, const double *A, const SCSL_INT_T lda,
                 double *X, const SCSL_INT_T incX);
void cblas_dtrsv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const SCSL_INT_T N, const double *A, const SCSL_INT_T lda, double *X,
                 const SCSL_INT_T incX);
void cblas_dgbmv(const enum CBLAS_ORDER order, 
                 const enum CBLAS_TRANSPOSE TransA,
                 const SCSL_INT_T M, const SCSL_INT_T N, const SCSL_INT_T Kl, const SCSL_INT_T Ku,
                 const double alpha, const double *A, const SCSL_INT_T lda,
                 const double *X, const SCSL_INT_T incX, const double beta,
                 double *Y, const SCSL_INT_T incY);
void cblas_dtbmv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const SCSL_INT_T N, const SCSL_INT_T K, const double *A, const SCSL_INT_T lda,
                 double *X, const SCSL_INT_T incX);
void cblas_dtbsv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const SCSL_INT_T N, const SCSL_INT_T K, const double *A, const SCSL_INT_T lda,
                 double *X, const SCSL_INT_T incX);
void cblas_dspmv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const SCSL_INT_T N, const double  alpha, const double *AP,
                 const double  *X, const SCSL_INT_T incX, const double  beta, 
                 double  *Y, const SCSL_INT_T incY);
void cblas_dtpsv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const SCSL_INT_T N, const double *Ap, double *X, const SCSL_INT_T incX);
void cblas_dtpmv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const SCSL_INT_T N, const double *Ap, double *X, const SCSL_INT_T incX);

void cblas_cgemv(const enum CBLAS_ORDER order,
                 const enum CBLAS_TRANSPOSE TransA, const SCSL_INT_T M, const SCSL_INT_T N,
                 const SCSL_COMPLEX_T *alpha, const SCSL_COMPLEX_T *A,
                 const SCSL_INT_T lda, SCSL_COMPLEX_T *X, const SCSL_INT_T incX,
                 const SCSL_COMPLEX_T *beta, SCSL_COMPLEX_T *Y, const SCSL_INT_T incY);
void cblas_cgbmv(const enum CBLAS_ORDER order,
                 const enum CBLAS_TRANSPOSE TransA,
                 const SCSL_INT_T M, const SCSL_INT_T N, const SCSL_INT_T KL, const SCSL_INT_T KU,
                 const SCSL_COMPLEX_T *alpha, const SCSL_COMPLEX_T *A,
                 const SCSL_INT_T lda, SCSL_COMPLEX_T *X, const SCSL_INT_T incX,
                 const SCSL_COMPLEX_T *beta, SCSL_COMPLEX_T *Y, const SCSL_INT_T incY);
void cblas_ctrmv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const SCSL_INT_T N, const SCSL_COMPLEX_T *A, const SCSL_INT_T lda,
                 SCSL_COMPLEX_T *X, const SCSL_INT_T incX);
void cblas_ctbmv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const SCSL_INT_T N, const SCSL_INT_T K, const SCSL_COMPLEX_T *A,
                 const SCSL_INT_T lda, SCSL_COMPLEX_T *X, const SCSL_INT_T incX);
void cblas_cspmv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo, 
		 const SCSL_INT_T n, const SCSL_COMPLEX_T *alpha, const SCSL_COMPLEX_T *ap,
		 const SCSL_COMPLEX_T *x, const SCSL_INT_T incx, const SCSL_COMPLEX_T *beta, 
		 SCSL_COMPLEX_T *y, const SCSL_INT_T incy);
void cblas_ctpmv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const SCSL_INT_T N, const SCSL_COMPLEX_T *Ap, SCSL_COMPLEX_T *X,
                 const SCSL_INT_T incX);
void cblas_ctrsv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const SCSL_INT_T N, const SCSL_COMPLEX_T *A, const SCSL_INT_T lda,
                 SCSL_COMPLEX_T *X, const SCSL_INT_T incX);
void cblas_ctbsv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const SCSL_INT_T N, const SCSL_INT_T K, const SCSL_COMPLEX_T *A,
                 const SCSL_INT_T lda, SCSL_COMPLEX_T *X, const SCSL_INT_T incX);
void cblas_ctpsv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const SCSL_INT_T N, const SCSL_COMPLEX_T *Ap, SCSL_COMPLEX_T *X,
                 const SCSL_INT_T incX);

void cblas_zgemv(const enum CBLAS_ORDER order,
                 const enum CBLAS_TRANSPOSE TransA, const SCSL_INT_T M, const SCSL_INT_T N,
                 const SCSL_ZOMPLEX_T *alpha, const SCSL_ZOMPLEX_T *A,
                 const SCSL_INT_T lda, SCSL_ZOMPLEX_T *X, const SCSL_INT_T incX,
                 const SCSL_ZOMPLEX_T *beta, SCSL_ZOMPLEX_T *Y, const SCSL_INT_T incY);
void cblas_zgbmv(const enum CBLAS_ORDER order,
                 const enum CBLAS_TRANSPOSE TransA,
                 const SCSL_INT_T M, const SCSL_INT_T N, const SCSL_INT_T KL, const SCSL_INT_T KU,
                 const SCSL_ZOMPLEX_T *alpha, const SCSL_ZOMPLEX_T *A,
                 const SCSL_INT_T lda, SCSL_ZOMPLEX_T *X, const SCSL_INT_T incX,
                 const SCSL_ZOMPLEX_T *beta, SCSL_ZOMPLEX_T *Y, const SCSL_INT_T incY);
void cblas_ztrmv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const SCSL_INT_T N, const SCSL_ZOMPLEX_T *A, const SCSL_INT_T lda,
                 SCSL_ZOMPLEX_T *X, const SCSL_INT_T incX);
void cblas_ztbmv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const SCSL_INT_T N, const SCSL_INT_T K, const SCSL_ZOMPLEX_T *A,
                 const SCSL_INT_T lda, SCSL_ZOMPLEX_T *X, const SCSL_INT_T incX);
void cblas_zspmv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo, 
		 const SCSL_INT_T n, const SCSL_ZOMPLEX_T *alpha, const SCSL_ZOMPLEX_T *ap,
		 const SCSL_ZOMPLEX_T *x, const SCSL_INT_T incx, const SCSL_ZOMPLEX_T *beta, 
		 SCSL_ZOMPLEX_T *y, const SCSL_INT_T incy);
void cblas_ztpmv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const SCSL_INT_T N, const SCSL_ZOMPLEX_T *Ap, SCSL_ZOMPLEX_T *X,
                 const SCSL_INT_T incX);
void cblas_ztrsv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const SCSL_INT_T N, const SCSL_ZOMPLEX_T *A, const SCSL_INT_T lda,
                 SCSL_ZOMPLEX_T *X, const SCSL_INT_T incX);
void cblas_ztbsv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const SCSL_INT_T N, const SCSL_INT_T K, const SCSL_ZOMPLEX_T *A,
                 const SCSL_INT_T lda, SCSL_ZOMPLEX_T *X, const SCSL_INT_T incX);
void cblas_ztpsv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const SCSL_INT_T N, const SCSL_ZOMPLEX_T *Ap, SCSL_ZOMPLEX_T *X,
                 const SCSL_INT_T incX);

/*
 * Routines with S and D prefixes only
 */

void cblas_sger(const enum CBLAS_ORDER order, const SCSL_INT_T M, const SCSL_INT_T N,
                const float alpha, const float *X, const SCSL_INT_T incX,
                const float *Y, const SCSL_INT_T incY, float *A, const SCSL_INT_T lda);
void cblas_sgesum(const enum CBLAS_ORDER order, const enum CBLAS_TRANSPOSE TransA,
		  const SCSL_INT_T m, const SCSL_INT_T n, const float alpha,
		  const float *A, const SCSL_INT_T lda, const float beta,
		  float *B, const SCSL_INT_T ldb);
void cblas_ssymv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const SCSL_INT_T N, const float  alpha, const float  *A,
                 const SCSL_INT_T lda, const float  *X, const SCSL_INT_T incX,
                 const float  beta, float  *Y, const SCSL_INT_T incY);
void cblas_csymv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const SCSL_INT_T N, const SCSL_COMPLEX_T *alpha, const SCSL_COMPLEX_T *A,
                 const SCSL_INT_T lda, const SCSL_COMPLEX_T *X, const SCSL_INT_T incX,
                 const SCSL_COMPLEX_T *beta, SCSL_COMPLEX_T *Y, const SCSL_INT_T incY);
void cblas_ssbmv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const SCSL_INT_T N, const SCSL_INT_T K, const float  alpha,
                 const float *A, const SCSL_INT_T lda, const float  *X, 
                 const SCSL_INT_T incX, const float  beta, float  *Y, const SCSL_INT_T incY);
void cblas_ssyr(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo, 
                const SCSL_INT_T N, const float  alpha, const float  *X, 
                const SCSL_INT_T incX, float  *A, const SCSL_INT_T lda);
void cblas_csyr(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo, 
                const SCSL_INT_T N, const SCSL_COMPLEX_T *alpha, const SCSL_COMPLEX_T *X, 
                const SCSL_INT_T incX, SCSL_COMPLEX_T *A, const SCSL_INT_T lda);
void cblas_ssyr2(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo, 
                 const SCSL_INT_T N, const float alpha, const float  *X, 
                 const SCSL_INT_T incX, const float  *Y, const SCSL_INT_T incY, float  *A, 
                 const SCSL_INT_T lda);
void cblas_sspr(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo, 
                const SCSL_INT_T N, const float  alpha, const float  *X, 
                const SCSL_INT_T incX, float  *Ap);
void cblas_sspr2(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                const SCSL_INT_T N, const float  alpha, const float  *X, 
                const SCSL_INT_T incX, const float  *Y, const SCSL_INT_T incY, float  *A);
void cblas_dsymv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const SCSL_INT_T N, const double  alpha, const double  *A,
                 const SCSL_INT_T lda, const double  *X, const SCSL_INT_T incX,
                 const double  beta, double  *Y, const SCSL_INT_T incY);
void cblas_zsymv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const SCSL_INT_T N, const SCSL_ZOMPLEX_T *alpha, const SCSL_ZOMPLEX_T *A,
                 const SCSL_INT_T lda, const SCSL_ZOMPLEX_T *X, const SCSL_INT_T incX,
                 const SCSL_ZOMPLEX_T *beta, SCSL_ZOMPLEX_T *Y, const SCSL_INT_T incY);
void cblas_dger(const enum CBLAS_ORDER order, const SCSL_INT_T M, const SCSL_INT_T N,
                const double alpha, const double *X, const SCSL_INT_T incX,
                const double *Y, const SCSL_INT_T incY, double *A, const SCSL_INT_T lda);
void cblas_dgesum(const enum CBLAS_ORDER order, const enum CBLAS_TRANSPOSE TransA,
		  const SCSL_INT_T m, const SCSL_INT_T n, const double alpha,
		  const double *A, const SCSL_INT_T lda, const double beta,
		  double *B, const SCSL_INT_T ldb);
void cblas_dsbmv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const SCSL_INT_T N, const SCSL_INT_T K, const double  alpha,
                 const double *A, const SCSL_INT_T lda, const double  *X, 
                 const SCSL_INT_T incX, const double  beta, double  *Y, 
                 const SCSL_INT_T incY);
void cblas_dsyr(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo, 
                const SCSL_INT_T N, const double  alpha, const double  *X, 
                const SCSL_INT_T incX, double  *A, const SCSL_INT_T lda);
void cblas_zsyr(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo, 
                const SCSL_INT_T N, const SCSL_ZOMPLEX_T *alpha, const SCSL_ZOMPLEX_T *X, 
                const SCSL_INT_T incX, SCSL_ZOMPLEX_T *A, const SCSL_INT_T lda);
void cblas_dsyr2(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo, 
                 const SCSL_INT_T N, const double  alpha, const double  *X, 
                 const SCSL_INT_T incX, const double  *Y, const SCSL_INT_T incY, double  *A,
                 const SCSL_INT_T lda);
void cblas_dspr(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo, 
                const SCSL_INT_T N, const double  alpha, const double  *X, 
                const SCSL_INT_T incX, double  *Ap);
void cblas_dspr2(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                const SCSL_INT_T N, const double  alpha, const double  *X, 
                const SCSL_INT_T incX, const double  *Y, const SCSL_INT_T incY, double  *A);

/*
 * Routines with C and Z prefixes only
 */

void cblas_chemv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const SCSL_INT_T N, const SCSL_COMPLEX_T *alpha,
                 const SCSL_COMPLEX_T *A, const SCSL_INT_T lda, SCSL_COMPLEX_T *X,
                 const SCSL_INT_T incX, const SCSL_COMPLEX_T *beta, SCSL_COMPLEX_T *Y,
                 const SCSL_INT_T incY);
void cblas_chbmv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const SCSL_INT_T N, const SCSL_INT_T K, const SCSL_COMPLEX_T *alpha,
                 const SCSL_COMPLEX_T *A, const SCSL_INT_T lda, SCSL_COMPLEX_T *X,
                 const SCSL_INT_T incX, const SCSL_COMPLEX_T *beta, SCSL_COMPLEX_T *Y,
                 const SCSL_INT_T incY);
void cblas_chpmv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const SCSL_INT_T N, const SCSL_COMPLEX_T *alpha,
                 const SCSL_COMPLEX_T *Ap, SCSL_COMPLEX_T *X, const SCSL_INT_T incX,
                 const SCSL_COMPLEX_T *bet, SCSL_COMPLEX_T *Y, const SCSL_INT_T incY);
void cblas_cgeru(const enum CBLAS_ORDER order, const SCSL_INT_T M, const SCSL_INT_T N,
                 const SCSL_COMPLEX_T *alpha, const SCSL_COMPLEX_T *X,
                 const SCSL_INT_T incX, const SCSL_COMPLEX_T *Y, const SCSL_INT_T incY,
                 SCSL_COMPLEX_T *A, const SCSL_INT_T lda);
void cblas_cgerc(const enum CBLAS_ORDER order, const SCSL_INT_T M, const SCSL_INT_T N,
                 const SCSL_COMPLEX_T *alpha, const SCSL_COMPLEX_T *X,
                 const SCSL_INT_T incX, SCSL_COMPLEX_T *Y, const SCSL_INT_T incY,
                 SCSL_COMPLEX_T *A, const SCSL_INT_T lda);
void cblas_cgesum(const enum CBLAS_ORDER order, const enum CBLAS_TRANSPOSE TransA,
		  const SCSL_INT_T m, const SCSL_INT_T n, const SCSL_COMPLEX_T *alpha,
		  const SCSL_COMPLEX_T *A, const SCSL_INT_T lda, const SCSL_COMPLEX_T *beta,
		  SCSL_COMPLEX_T *B, const SCSL_INT_T ldb);
void cblas_cher(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                const SCSL_INT_T N, const float alpha, SCSL_COMPLEX_T *X,
                const SCSL_INT_T incX, SCSL_COMPLEX_T *A, const SCSL_INT_T lda);
void cblas_cspr(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
		const SCSL_INT_T n, const SCSL_COMPLEX_T *alpha, const SCSL_COMPLEX_T *x, 
		const SCSL_INT_T incx, SCSL_COMPLEX_T *ap);
void cblas_chpr(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                const SCSL_INT_T N, const float alpha, SCSL_COMPLEX_T *X,
                const SCSL_INT_T incX, SCSL_COMPLEX_T *Ap);
void cblas_cher2(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const SCSL_INT_T N, const SCSL_COMPLEX_T *alpha,
                 SCSL_COMPLEX_T *X, const SCSL_INT_T incX, SCSL_COMPLEX_T *Y,
                 const SCSL_INT_T incY, SCSL_COMPLEX_T *A, const SCSL_INT_T lda);
void cblas_chpr2(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const SCSL_INT_T N, const SCSL_COMPLEX_T *alpha, SCSL_COMPLEX_T *X,
                 const SCSL_INT_T incX, SCSL_COMPLEX_T *Y,
                 const SCSL_INT_T incY, SCSL_COMPLEX_T *Ap);

void cblas_zhemv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const SCSL_INT_T N, const SCSL_ZOMPLEX_T *alpha,
                 const SCSL_ZOMPLEX_T *A, const SCSL_INT_T lda, SCSL_ZOMPLEX_T *X,
                 const SCSL_INT_T incX, const SCSL_ZOMPLEX_T *beta, SCSL_ZOMPLEX_T *Y,
                 const SCSL_INT_T incY);
void cblas_zhbmv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const SCSL_INT_T N, const SCSL_INT_T K, const SCSL_ZOMPLEX_T *alpha,
                 const SCSL_ZOMPLEX_T *A, const SCSL_INT_T lda, SCSL_ZOMPLEX_T *X,
                 const SCSL_INT_T incX, const SCSL_ZOMPLEX_T *beta, SCSL_ZOMPLEX_T *Y,
                 const SCSL_INT_T incY);
void cblas_zhpmv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const SCSL_INT_T N, const SCSL_ZOMPLEX_T *alpha,
                 const SCSL_ZOMPLEX_T *Ap, SCSL_ZOMPLEX_T *X, const SCSL_INT_T incX,
                 const SCSL_ZOMPLEX_T *beta, SCSL_ZOMPLEX_T *Y, const SCSL_INT_T incY);
void cblas_zgeru(const enum CBLAS_ORDER order, const SCSL_INT_T M, const SCSL_INT_T N,
                 const SCSL_ZOMPLEX_T *alpha, const SCSL_ZOMPLEX_T *X,
                 const SCSL_INT_T incX, const SCSL_ZOMPLEX_T *Y, const SCSL_INT_T incY,
                 SCSL_ZOMPLEX_T *A, const SCSL_INT_T lda);
void cblas_zgerc(const enum CBLAS_ORDER order, const SCSL_INT_T M, const SCSL_INT_T N,
                 const SCSL_ZOMPLEX_T *alpha, const SCSL_ZOMPLEX_T *X,
                 const SCSL_INT_T incX, SCSL_ZOMPLEX_T *Y, const SCSL_INT_T incY,
                 SCSL_ZOMPLEX_T *A, const SCSL_INT_T lda);
void cblas_zgesum(const enum CBLAS_ORDER order, const enum CBLAS_TRANSPOSE TransA,
		  const SCSL_INT_T m, const SCSL_INT_T n, const SCSL_ZOMPLEX_T *alpha,
		  const SCSL_ZOMPLEX_T *A, const SCSL_INT_T lda, const SCSL_ZOMPLEX_T *beta,
		  SCSL_ZOMPLEX_T *B, const SCSL_INT_T ldb);
void cblas_zher(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                const SCSL_INT_T N, const double alpha, SCSL_ZOMPLEX_T *X,
                const SCSL_INT_T incX, SCSL_ZOMPLEX_T *A, const SCSL_INT_T lda);
void cblas_zspr(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
		const SCSL_INT_T n, const SCSL_ZOMPLEX_T *alpha, const SCSL_ZOMPLEX_T *x, 
		const SCSL_INT_T incx, SCSL_ZOMPLEX_T *ap);
void cblas_zhpr(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                const SCSL_INT_T N, const double alpha, SCSL_ZOMPLEX_T *X,
                const SCSL_INT_T incX, SCSL_ZOMPLEX_T *Ap);
void cblas_zher2(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const SCSL_INT_T N, const SCSL_ZOMPLEX_T *alpha,
                 SCSL_ZOMPLEX_T *X, const SCSL_INT_T incX, SCSL_ZOMPLEX_T *Y,
                 const SCSL_INT_T incY, SCSL_ZOMPLEX_T *A, const SCSL_INT_T lda);
void cblas_zhpr2(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const SCSL_INT_T N, const SCSL_ZOMPLEX_T *alpha, SCSL_ZOMPLEX_T *X,
                 const SCSL_INT_T incX, SCSL_ZOMPLEX_T *Y,
                 const SCSL_INT_T incY, SCSL_ZOMPLEX_T *Ap);

/*
 * ===========================================================================
 * Prototypes for level 3 BLAS
 * ===========================================================================
 */
/*
 * Routines with standard 4 prefixes (S, D, C, Z)
 */

void cblas_sgemm(const enum CBLAS_ORDER Order, 
                 const enum CBLAS_TRANSPOSE TransA,
                 const enum CBLAS_TRANSPOSE TransB, const SCSL_INT_T M, const SCSL_INT_T N,
                 const SCSL_INT_T K, const float alpha, const float *A,
                 const SCSL_INT_T lda, const float *B, const SCSL_INT_T ldb,
                 const float beta, float *C, const SCSL_INT_T ldc);
void cblas_ssymm(const enum CBLAS_ORDER Order, const enum CBLAS_SIDE Side,
                 const enum CBLAS_UPLO Uplo, const SCSL_INT_T M, const SCSL_INT_T N,
                 const float alpha, const float *A, const SCSL_INT_T lda,
                 const float *B, const SCSL_INT_T ldb, const float beta,
                 float *C, const SCSL_INT_T ldc);
void cblas_ssyrk(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE Trans, const SCSL_INT_T N, const SCSL_INT_T K,
                 const float alpha, const float *A, const SCSL_INT_T lda,
                 const float beta, float *C, const SCSL_INT_T ldc);
void cblas_ssyr2k(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                  const enum CBLAS_TRANSPOSE Trans, const SCSL_INT_T N, const SCSL_INT_T K,
                  const float alpha, const float *A, const SCSL_INT_T lda,
                  const float *B, const SCSL_INT_T ldb, const float beta,
                  float *C, const SCSL_INT_T ldc);
void cblas_strmm(const enum CBLAS_ORDER Order, const enum CBLAS_SIDE Side,
                 const enum CBLAS_UPLO Uplo, const enum CBLAS_TRANSPOSE TransA,
                 const enum CBLAS_DIAG Diag, const SCSL_INT_T M, const SCSL_INT_T N,
                 const float alpha, const float *A, const SCSL_INT_T lda,
                 float *B, const SCSL_INT_T ldb);
void cblas_strsm(const enum CBLAS_ORDER Order, const enum CBLAS_SIDE Side,
                 const enum CBLAS_UPLO Uplo, const enum CBLAS_TRANSPOSE TransA,
                 const enum CBLAS_DIAG Diag, const SCSL_INT_T M, const SCSL_INT_T N,
                 const float alpha, const float *A, const SCSL_INT_T lda,
                 float *B, const SCSL_INT_T ldb);

void cblas_dgemm(const enum CBLAS_ORDER Order, 
                 const enum CBLAS_TRANSPOSE TransA,
                 const enum CBLAS_TRANSPOSE TransB, const SCSL_INT_T M, const SCSL_INT_T N,
                 const SCSL_INT_T K, const double alpha, const double *A,
                 const SCSL_INT_T lda, const double *B, const SCSL_INT_T ldb,
                 const double beta, double *C, const SCSL_INT_T ldc);
void cblas_dgemms(const enum CBLAS_ORDER Order, 
		  const enum CBLAS_TRANSPOSE TransA,
		  const enum CBLAS_TRANSPOSE TransB, const SCSL_INT_T M, const SCSL_INT_T N,
		  const SCSL_INT_T K, const double alpha, const double *A,
		  const SCSL_INT_T lda, const double *B, const SCSL_INT_T ldb,
		  const double beta, double *C, const SCSL_INT_T ldc);
void cblas_dsymm(const enum CBLAS_ORDER Order, const enum CBLAS_SIDE Side,
                 const enum CBLAS_UPLO Uplo, const SCSL_INT_T M, const SCSL_INT_T N,
                 const double alpha, const double *A, const SCSL_INT_T lda,
                 const double *B, const SCSL_INT_T ldb, const double beta,
                 double *C, const SCSL_INT_T ldc);
void cblas_dsyrk(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE Trans, const SCSL_INT_T N, const SCSL_INT_T K,
                 const double alpha, const double *A, const SCSL_INT_T lda,
                 const double beta, double *C, const SCSL_INT_T ldc);
void cblas_dsyr2k(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                  const enum CBLAS_TRANSPOSE Trans, const SCSL_INT_T N, const SCSL_INT_T K,
                  const double alpha, const double *A, const SCSL_INT_T lda,
                  const double *B, const SCSL_INT_T ldb, const double beta,
                  double *C, const SCSL_INT_T ldc);
void cblas_dtrmm(const enum CBLAS_ORDER Order, const enum CBLAS_SIDE Side,
                 const enum CBLAS_UPLO Uplo, const enum CBLAS_TRANSPOSE TransA,
                 const enum CBLAS_DIAG Diag, const SCSL_INT_T M, const SCSL_INT_T N,
                 const double alpha, const double *A, const SCSL_INT_T lda,
                 double *B, const SCSL_INT_T ldb);
void cblas_dtrsm(const enum CBLAS_ORDER Order, const enum CBLAS_SIDE Side,
                 const enum CBLAS_UPLO Uplo, const enum CBLAS_TRANSPOSE TransA,
                 const enum CBLAS_DIAG Diag, const SCSL_INT_T M, const SCSL_INT_T N,
                 const double alpha, const double *A, const SCSL_INT_T lda,
                 double *B, const SCSL_INT_T ldb);

void cblas_cgemm(const enum CBLAS_ORDER Order, 
		 const enum CBLAS_TRANSPOSE TransA,
                 const enum CBLAS_TRANSPOSE TransB, const SCSL_INT_T M, const SCSL_INT_T N,
                 const SCSL_INT_T K, const SCSL_COMPLEX_T *alpha, 
		 const SCSL_COMPLEX_T *A,
                 const SCSL_INT_T lda, const SCSL_COMPLEX_T *B, const SCSL_INT_T ldb,
                 const SCSL_COMPLEX_T *beta, SCSL_COMPLEX_T *C, const SCSL_INT_T ldc);
void cblas_cgemm3m(const enum CBLAS_ORDER Order, 
		   const enum CBLAS_TRANSPOSE TransA,
		   const enum CBLAS_TRANSPOSE TransB, const SCSL_INT_T M, const SCSL_INT_T N,
		   const SCSL_INT_T K, const SCSL_COMPLEX_T *alpha, 
		   const SCSL_COMPLEX_T *A,
		   const SCSL_INT_T lda, const SCSL_COMPLEX_T *B, const SCSL_INT_T ldb,
		   const SCSL_COMPLEX_T *beta, SCSL_COMPLEX_T *C, const SCSL_INT_T ldc);
void cblas_csymm(const enum CBLAS_ORDER Order, const enum CBLAS_SIDE Side,
                 const enum CBLAS_UPLO Uplo, const SCSL_INT_T M, const SCSL_INT_T N,
                 const SCSL_COMPLEX_T *alpha, const SCSL_COMPLEX_T *A, 
		 const SCSL_INT_T lda, const SCSL_COMPLEX_T *B, const SCSL_INT_T ldb, 
		 const SCSL_COMPLEX_T *beta, SCSL_COMPLEX_T *C, const SCSL_INT_T ldc);
void cblas_csyrk(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE Trans, const SCSL_INT_T N, const SCSL_INT_T K,
                 const SCSL_COMPLEX_T *alpha, const SCSL_COMPLEX_T *A, 
		 const SCSL_INT_T lda,
                 const SCSL_COMPLEX_T *beta, SCSL_COMPLEX_T *C, const SCSL_INT_T ldc);
void cblas_csyr2k(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                  const enum CBLAS_TRANSPOSE Trans, const SCSL_INT_T N, const SCSL_INT_T K,
                  const SCSL_COMPLEX_T *alpha, const SCSL_COMPLEX_T *A, 
		  const SCSL_INT_T lda, const SCSL_COMPLEX_T *B, const SCSL_INT_T ldb, 
		  const SCSL_COMPLEX_T *beta, SCSL_COMPLEX_T *C, const SCSL_INT_T ldc);
void cblas_ctrmm(const enum CBLAS_ORDER Order, const enum CBLAS_SIDE Side,
                 const enum CBLAS_UPLO Uplo, const enum CBLAS_TRANSPOSE TransA,
                 const enum CBLAS_DIAG Diag, const SCSL_INT_T M, const SCSL_INT_T N,
                 const SCSL_COMPLEX_T *alpha, const SCSL_COMPLEX_T *A, 
		 const SCSL_INT_T lda, SCSL_COMPLEX_T *B, const SCSL_INT_T ldb);
void cblas_ctrsm(const enum CBLAS_ORDER Order, const enum CBLAS_SIDE Side,
                 const enum CBLAS_UPLO Uplo, const enum CBLAS_TRANSPOSE TransA,
                 const enum CBLAS_DIAG Diag, const SCSL_INT_T M, const SCSL_INT_T N,
                 const SCSL_COMPLEX_T *alpha, const SCSL_COMPLEX_T *A, 
		 const SCSL_INT_T lda, SCSL_COMPLEX_T *B, const SCSL_INT_T ldb);
void cblas_cherk(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA,
                 const SCSL_INT_T N, const SCSL_INT_T K, const float alpha,
                 const SCSL_COMPLEX_T *A, const SCSL_INT_T lda, const float beta,
                 SCSL_COMPLEX_T *C, const SCSL_INT_T ldc);
void cblas_cher2k(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA,
                 const SCSL_INT_T N, const SCSL_INT_T K, const SCSL_COMPLEX_T *alpha,
                 const SCSL_COMPLEX_T *A, const SCSL_INT_T lda, 
                 const SCSL_COMPLEX_T *B, const SCSL_INT_T ldb, const float beta,
                 SCSL_COMPLEX_T *C, const SCSL_INT_T ldc);
void cblas_chemm(const enum CBLAS_ORDER Order, const enum CBLAS_SIDE Side,
                 const enum CBLAS_UPLO Uplo, const SCSL_INT_T M, const SCSL_INT_T N,
                 const SCSL_COMPLEX_T *alpha, const SCSL_COMPLEX_T *A, 
		 const SCSL_INT_T lda, const SCSL_COMPLEX_T *B, const SCSL_INT_T ldb, 
		 const SCSL_COMPLEX_T *beta, SCSL_COMPLEX_T *C, const SCSL_INT_T ldc);

void cblas_zgemm(const enum CBLAS_ORDER Order, 
		 const enum CBLAS_TRANSPOSE TransA,
                 const enum CBLAS_TRANSPOSE TransB, const SCSL_INT_T M, const SCSL_INT_T N,
                 const SCSL_INT_T K, const SCSL_ZOMPLEX_T *alpha, 
		 const SCSL_ZOMPLEX_T *A,
                 const SCSL_INT_T lda, const SCSL_ZOMPLEX_T *B, const SCSL_INT_T ldb,
                 const SCSL_ZOMPLEX_T *beta, SCSL_ZOMPLEX_T *C, const SCSL_INT_T ldc);
void cblas_zgemm3m(const enum CBLAS_ORDER Order, 
		   const enum CBLAS_TRANSPOSE TransA,
		   const enum CBLAS_TRANSPOSE TransB, const SCSL_INT_T M, const SCSL_INT_T N,
		   const SCSL_INT_T K, const SCSL_ZOMPLEX_T *alpha, 
		   const SCSL_ZOMPLEX_T *A,
		   const SCSL_INT_T lda, const SCSL_ZOMPLEX_T *B, const SCSL_INT_T ldb,
		   const SCSL_ZOMPLEX_T *beta, SCSL_ZOMPLEX_T *C, const SCSL_INT_T ldc);
void cblas_zsymm(const enum CBLAS_ORDER Order, const enum CBLAS_SIDE Side,
                 const enum CBLAS_UPLO Uplo, const SCSL_INT_T M, const SCSL_INT_T N,
                 const SCSL_ZOMPLEX_T *alpha, const SCSL_ZOMPLEX_T *A, 
		 const SCSL_INT_T lda, const SCSL_ZOMPLEX_T *B, const SCSL_INT_T ldb, 
		 const SCSL_ZOMPLEX_T *beta, SCSL_ZOMPLEX_T *C, const SCSL_INT_T ldc);
void cblas_zsyrk(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE Trans, const SCSL_INT_T N, const SCSL_INT_T K,
                 const SCSL_ZOMPLEX_T *alpha, const SCSL_ZOMPLEX_T *A, 
		 const SCSL_INT_T lda, const SCSL_ZOMPLEX_T *beta, SCSL_ZOMPLEX_T *C, 
		 const SCSL_INT_T ldc);
void cblas_zsyr2k(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                  const enum CBLAS_TRANSPOSE Trans, const SCSL_INT_T N, const SCSL_INT_T K,
                  const SCSL_ZOMPLEX_T *alpha, const SCSL_ZOMPLEX_T *A, 
		  const SCSL_INT_T lda, const SCSL_ZOMPLEX_T *B, const SCSL_INT_T ldb, 
		  const SCSL_ZOMPLEX_T *beta, SCSL_ZOMPLEX_T *C, const SCSL_INT_T ldc);
void cblas_ztrmm(const enum CBLAS_ORDER Order, const enum CBLAS_SIDE Side,
                 const enum CBLAS_UPLO Uplo, const enum CBLAS_TRANSPOSE TransA,
                 const enum CBLAS_DIAG Diag, const SCSL_INT_T M, const SCSL_INT_T N,
                 const SCSL_ZOMPLEX_T *alpha, const SCSL_ZOMPLEX_T *A, 
		 const SCSL_INT_T lda, SCSL_ZOMPLEX_T *B, const SCSL_INT_T ldb);
void cblas_ztrsm(const enum CBLAS_ORDER Order, const enum CBLAS_SIDE Side,
                 const enum CBLAS_UPLO Uplo, const enum CBLAS_TRANSPOSE TransA,
                 const enum CBLAS_DIAG Diag, const SCSL_INT_T M, const SCSL_INT_T N,
                 const SCSL_ZOMPLEX_T *alpha, const SCSL_ZOMPLEX_T *A, 
		 const SCSL_INT_T lda, SCSL_ZOMPLEX_T *B, const SCSL_INT_T ldb);
void cblas_zhemm(const enum CBLAS_ORDER Order, const enum CBLAS_SIDE Side,
                 const enum CBLAS_UPLO Uplo, const SCSL_INT_T M, const SCSL_INT_T N,
                 const SCSL_ZOMPLEX_T *alpha, const SCSL_ZOMPLEX_T *A, 
		 const SCSL_INT_T lda, const SCSL_ZOMPLEX_T *B, const SCSL_INT_T ldb, 
		 const SCSL_ZOMPLEX_T *beta, SCSL_ZOMPLEX_T *C, const SCSL_INT_T ldc);
void cblas_zherk(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE Trans, const SCSL_INT_T N, const SCSL_INT_T K,
                 const double alpha, const SCSL_ZOMPLEX_T *A, 
		 const SCSL_INT_T lda, const double beta, SCSL_ZOMPLEX_T *C, 
		 const SCSL_INT_T ldc);
void cblas_zher2k(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                  const enum CBLAS_TRANSPOSE Trans, const SCSL_INT_T N, const SCSL_INT_T K,
                  const SCSL_ZOMPLEX_T *alpha, const SCSL_ZOMPLEX_T *A, 
		  const SCSL_INT_T lda, const SCSL_ZOMPLEX_T *B, const SCSL_INT_T ldb, 
		  const double beta, SCSL_ZOMPLEX_T *C, const SCSL_INT_T ldc);

/*
 * auxiliary functions
 */

void cblas_xerbla(SCSL_INT_T p, char *rout, char *form, ...);

#if !defined(SCSL_KEEP_TYPE_DEFS)
#  undef SCSL_INT_T
#  undef SCSL_COMPLEX_T
#  undef SCSL_ZOMPLEX_T
#  undef SCSL_CMPLX_T
#  undef SCSL_ZMPLX_T
#endif

#ifdef __cplusplus
}
#endif

#endif /* _CBLAS_H */
