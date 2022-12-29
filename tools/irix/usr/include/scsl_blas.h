/*
 *      (C) COPYRIGHT SILICON GRAPHICS, INC.
 *      UNPUBLISHED PROPRIETARY INFORMATION.
 *      ALL RIGHTS RESERVED.
 */

#ifndef _SCSL_BLAS_H
#define _SCSL_BLAS_H

#ifdef __cplusplus
extern "C"
{
#endif

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
 * complex type. Our default is to define our own complex types,
 * scsl_complex and scsl_zomplex, and prototype the library routines
 * using pointers to these types.  But if the C++ STL complex types 
 * are being used, this will be detected and they will be used rather
 * than the SCSL complex types. Either way, the compiler will be able 
 * to check the types of complex arguments since they have been fully
 * prototyped.
 *
 * An alternative approach is to just prototype using void pointers,
 * which is enabled by defining SCSL_VOID_ARGS at compile time (e.g.,
 * cc -DSCSL_VOID_ARGS ...). This has the advantage of allowing
 * user-defined complex types to be passed to the library routines
 * without complaint from the compiler. The disadvantage is that the
 * compiler will not catch type mismatches.
 *
 * To permit strong type checking for user-defined complex types, one
 * should instead define SCSL_USER_COMPLEX_T and SCSL_USER_ZOMPLEX_T
 * at compile time to be the user-defined single and double precision
 * complex types, respectively (e.g., cc -DSCSL_USER_COMPLEX_T=my_complex
 * -DSCSL_USER_ZOMPLEX_T=my_zomplex ...).
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

#if defined(SCSL_VOID_ARGS)

/* Omit type checking; just prototype the complex arguments as void *.
 */
#  define SCSL_COMPLEX_T void
#  define SCSL_ZOMPLEX_T void

/* This is required for the functions which return
   a complex value */
#  define SCSL_CMPLX_T __scsl_complex
#  define SCSL_ZMPLX_T __scsl_zomplex

#else
#  if defined(SCSL_USER_COMPLEX_T) && defined(SCSL_USER_ZOMPLEX_T)

/* Use user-supplied complex types in the prototypes.
 */
#    define SCSL_COMPLEX_T SCSL_USER_COMPLEX_T
#    define SCSL_ZOMPLEX_T SCSL_USER_ZOMPLEX_T

#  else

/* C++ has it's own class/template for complex arithmetic. If it is
 * used, the function prototypes should match the C++ conventions.
 * For the cases when it is not used, the SCSL-defined complex types
 * are used, but we now use names that aren't likely to conflict with
 * other attempts to define complex types. SCSL 1.0--1.2 used the
 * names complex and zomplex, so to prevent breaking old code, the
 * old names are preserved, but can be disbaled bt defining
 * SCSL_DONT_USE_OLD_TYPES (e.g., cc -DSCSL_DONT_USE_OLD_TYPES ...).
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
#endif

/* Integer arguments are 4 bytes in the standard version of SCSL,
 * 8 bytes in the I* version.
 */
#if defined(SCSL_I8_INT_ARGS)
#  define SCSL_INT_T long long
#else
#  define SCSL_INT_T int
#endif

/*
 * ===========================================================================
 * Prototypes for level 1 BLAS functions
 * ===========================================================================
 */

static __inline float sdot(SCSL_INT_T N,
			   float *X,
			   SCSL_INT_T incX,
			   float *Y, 
			   SCSL_INT_T incY) {
  float sdot_(SCSL_INT_T *N,  
	      float *X,  
	      SCSL_INT_T *incX,
	      float  *Y,  
	      SCSL_INT_T *incY);

  return sdot_(&N, X, &incX, Y, &incY);
}


static __inline double ddot(SCSL_INT_T N, 
			    double *X, 
			    SCSL_INT_T incX,
			    double *Y, 
			    SCSL_INT_T incY) {
  double ddot_(SCSL_INT_T *N, 
	       double *X, 
	       SCSL_INT_T *incX,
	       double *Y, 
	       SCSL_INT_T *incY);

  return ddot_(&N, X, &incX, Y, &incY);
}


#ifdef __INTEL_COMPILER

  /* Intel compiler passes complex function return value as first argument */

  /* With the exception of the following 4 routines, complex values
     and arrays are passed as void * in order to allow the greatest
     flexibility in the choice of complex data type */
  
  static __inline SCSL_CMPLX_T cdotu(SCSL_INT_T N,
				     SCSL_COMPLEX_T *X, 
				     SCSL_INT_T incX, 
				     SCSL_COMPLEX_T *Y,
				     SCSL_INT_T incY) {
  void cdotu_(SCSL_CMPLX_T *,
	      SCSL_INT_T *, 
	      SCSL_COMPLEX_T *,
	      SCSL_INT_T *, 
	      SCSL_COMPLEX_T *, 
	      SCSL_INT_T *);
  SCSL_CMPLX_T result;

  cdotu_(&result, &N, X, &incX, Y, &incY);
  return result;
}

  
static __inline SCSL_CMPLX_T cdotc(SCSL_INT_T N,
				   SCSL_COMPLEX_T *X, 
				   SCSL_INT_T incX, 
				   SCSL_COMPLEX_T *Y,
				   SCSL_INT_T incY) {
  void cdotc_(SCSL_CMPLX_T *,
	      SCSL_INT_T *,
	      SCSL_COMPLEX_T *,
	      SCSL_INT_T *,
	      SCSL_COMPLEX_T *,
	      SCSL_INT_T *);
  SCSL_CMPLX_T result;

  cdotc_(&result, &N, X, &incX, Y, &incY);
  return result;
}


static __inline SCSL_ZMPLX_T zdotu(SCSL_INT_T N, 
				   SCSL_ZOMPLEX_T *X, 
				   SCSL_INT_T incX, 
				   SCSL_ZOMPLEX_T *Y,
				     SCSL_INT_T incY) {
  void zdotu_(SCSL_ZMPLX_T *,
	      SCSL_INT_T *, 
	      SCSL_ZOMPLEX_T *,
	      SCSL_INT_T *, 
	      SCSL_ZOMPLEX_T *,
	      SCSL_INT_T *);
  SCSL_ZMPLX_T result;

  zdotu_(&result, &N, X, &incX, Y, &incY);
  return result;
}


static __inline SCSL_ZMPLX_T zdotc(SCSL_INT_T N,
				   SCSL_ZOMPLEX_T *X, 
				   SCSL_INT_T incX,
				   SCSL_ZOMPLEX_T *Y,
				   SCSL_INT_T incY) {
  void zdotc_(SCSL_ZMPLX_T *,
	      SCSL_INT_T *, 
	      SCSL_ZOMPLEX_T *,
	      SCSL_INT_T *, 
	      SCSL_ZOMPLEX_T *, 
	      SCSL_INT_T *);
  SCSL_ZMPLX_T result;

  zdotc_(&result, &N, X, &incX, Y, &incY);
  return result;
}

  /* These routines are provided for those not using SCSL or C++ complex
     data types */

static __inline void cdotu_sub(SCSL_INT_T N, 
			       SCSL_COMPLEX_T *X, 
			       SCSL_INT_T incX,
			       SCSL_COMPLEX_T *Y, 
			       SCSL_INT_T incY, 
			       SCSL_COMPLEX_T *dotu) {
  void cdotu_(SCSL_CMPLX_T *,
	      SCSL_INT_T *, 
	      SCSL_COMPLEX_T *, 
	      SCSL_INT_T *,
	      SCSL_COMPLEX_T *, 
	      SCSL_INT_T *);

  cdotu_((SCSL_CMPLX_T *) dotu, &N, X, &incX, Y, &incY);
}


static __inline void cdotc_sub(SCSL_INT_T N, 
			       SCSL_COMPLEX_T *X, 
			       SCSL_INT_T incX,
			       SCSL_COMPLEX_T *Y, 
			       SCSL_INT_T incY, 
			       SCSL_COMPLEX_T *dotc) {
  void cdotc_(SCSL_CMPLX_T *,
	      SCSL_INT_T *, 
	      SCSL_COMPLEX_T *, 
	      SCSL_INT_T *,
	      SCSL_COMPLEX_T *, 
	      SCSL_INT_T *);

  cdotc_((SCSL_CMPLX_T *) dotc, &N, X, &incX, Y, &incY);
}


static __inline void zdotu_sub(SCSL_INT_T N, 
			       SCSL_ZOMPLEX_T *X, 
			       SCSL_INT_T incX,
			       SCSL_ZOMPLEX_T *Y, 
			       SCSL_INT_T incY, 
			       SCSL_ZOMPLEX_T *dotu) {
  void zdotu_(SCSL_ZMPLX_T *,
	      SCSL_INT_T *, 
	      SCSL_ZOMPLEX_T *, 
	      SCSL_INT_T *,
	      SCSL_ZOMPLEX_T *, 
	      SCSL_INT_T *);

  zdotu_((SCSL_ZMPLX_T *) dotu, &N, X, &incX, Y, &incY);
}


static __inline void zdotc_sub(SCSL_INT_T N, 
			       SCSL_ZOMPLEX_T *X, 
			       SCSL_INT_T incX,
			       SCSL_ZOMPLEX_T *Y, 
			       SCSL_INT_T incY, 
			       SCSL_ZOMPLEX_T *dotc) {
  void zdotc_(SCSL_ZMPLX_T *,
	      SCSL_INT_T *, 
	      SCSL_ZOMPLEX_T *, 
	      SCSL_INT_T *,
	      SCSL_ZOMPLEX_T *, 
	      SCSL_INT_T *);

  zdotc_((SCSL_ZMPLX_T *) dotc, &N, X, &incX, Y, &incY);
}

#else

  /* With the exception of the following 4 routines, complex values
     and arrays are passed as void * in order to allow the greatest
     flexibility in the choice of complex data type */
  
  static __inline SCSL_CMPLX_T cdotu(SCSL_INT_T N,
				     SCSL_COMPLEX_T *X, 
				     SCSL_INT_T incX, 
				     SCSL_COMPLEX_T *Y,
				     SCSL_INT_T incY) {
  SCSL_CMPLX_T cdotu_(SCSL_INT_T *N, 
		      SCSL_COMPLEX_T *X,
		      SCSL_INT_T *incX, 
		      SCSL_COMPLEX_T *Y, 
		      SCSL_INT_T *incY);

  return cdotu_(&N, X, &incX, Y, &incY);
}

  
static __inline SCSL_CMPLX_T cdotc(SCSL_INT_T N,
				   SCSL_COMPLEX_T *X, 
				   SCSL_INT_T incX, 
				   SCSL_COMPLEX_T *Y,
				   SCSL_INT_T incY) {
  SCSL_CMPLX_T cdotc_(SCSL_INT_T *N,
		      SCSL_COMPLEX_T *X,
		      SCSL_INT_T *incX,
		      SCSL_COMPLEX_T *Y,
		      SCSL_INT_T *incY);

  return cdotc_(&N, X, &incX, Y, &incY);
}


static __inline SCSL_ZMPLX_T zdotu(SCSL_INT_T N, 
				   SCSL_ZOMPLEX_T *X, 
				   SCSL_INT_T incX, 
				   SCSL_ZOMPLEX_T *Y,
				     SCSL_INT_T incY) {
  SCSL_ZMPLX_T zdotu_(SCSL_INT_T *N, 
		      SCSL_ZOMPLEX_T *X,
		      SCSL_INT_T *incX, 
		      SCSL_ZOMPLEX_T *Y,
		      SCSL_INT_T *incY);

  return zdotu_(&N, X, &incX, Y, &incY);
}


static __inline SCSL_ZMPLX_T zdotc(SCSL_INT_T N,
				   SCSL_ZOMPLEX_T *X, 
				   SCSL_INT_T incX,
				   SCSL_ZOMPLEX_T *Y,
				   SCSL_INT_T incY) {
  SCSL_ZMPLX_T zdotc_(SCSL_INT_T *N, 
		      SCSL_ZOMPLEX_T *X,
		      SCSL_INT_T *incX, 
		      SCSL_ZOMPLEX_T *Y, 
		      SCSL_INT_T *incY);

  return zdotc_(&N, X, &incX, Y, &incY);
}

  /* These routines are provided for those not using SCSL or C++ complex
     data types */

static __inline void cdotu_sub(SCSL_INT_T N, 
			       SCSL_COMPLEX_T *X, 
			       SCSL_INT_T incX,
			       SCSL_COMPLEX_T *Y, 
			       SCSL_INT_T incY, 
			       SCSL_COMPLEX_T *dotu) {
  SCSL_CMPLX_T cdotu_(SCSL_INT_T *N, 
		      SCSL_COMPLEX_T *X, 
		      SCSL_INT_T *incX,
		      SCSL_COMPLEX_T *Y, 
		      SCSL_INT_T *incY);

  *((SCSL_CMPLX_T *) dotu) = cdotu_(&N, X, &incX, Y, &incY);
}


static __inline void cdotc_sub(SCSL_INT_T N, 
			       SCSL_COMPLEX_T *X, 
			       SCSL_INT_T incX,
			       SCSL_COMPLEX_T *Y, 
			       SCSL_INT_T incY, 
			       SCSL_COMPLEX_T *dotc) {
  SCSL_CMPLX_T cdotc_(SCSL_INT_T *N, 
		      SCSL_COMPLEX_T *X, 
		      SCSL_INT_T *incX,
		      SCSL_COMPLEX_T *Y, 
		      SCSL_INT_T *incY);

  *((SCSL_CMPLX_T *) dotc) = cdotc_(&N, X, &incX, Y, &incY);
}


static __inline void zdotu_sub(SCSL_INT_T N, 
			       SCSL_ZOMPLEX_T *X, 
			       SCSL_INT_T incX,
			       SCSL_ZOMPLEX_T *Y, 
			       SCSL_INT_T incY, 
			       SCSL_ZOMPLEX_T *dotu) {
  SCSL_ZMPLX_T zdotu_(SCSL_INT_T *N, 
		      SCSL_ZOMPLEX_T *X, 
		      SCSL_INT_T *incX,
		      SCSL_ZOMPLEX_T *Y, 
		      SCSL_INT_T *incY);

  *((SCSL_ZMPLX_T *) dotu) = zdotu_(&N, X, &incX, Y, &incY);
}


static __inline void zdotc_sub(SCSL_INT_T N, 
			       SCSL_ZOMPLEX_T *X, 
			       SCSL_INT_T incX,
			       SCSL_ZOMPLEX_T *Y, 
			       SCSL_INT_T incY, 
			       SCSL_ZOMPLEX_T *dotc) {
  SCSL_ZMPLX_T zdotc_(SCSL_INT_T *N, 
		      SCSL_ZOMPLEX_T *X, 
		      SCSL_INT_T *incX,
		      SCSL_ZOMPLEX_T *Y, 
		      SCSL_INT_T *incY);

  *((SCSL_ZMPLX_T *) dotc) = zdotc_(&N, X, &incX, Y, &incY);
}

#endif


static __inline float snrm2(SCSL_INT_T N, 
			    float *X,
			    SCSL_INT_T incX) {
  float snrm2_(SCSL_INT_T *N, 
	       float *X, 
	       SCSL_INT_T *incX);

  return snrm2_(&N, X, &incX);
}


static __inline float sasum(SCSL_INT_T N, 
			    float *X, 
			    SCSL_INT_T incX) {
  float sasum_(SCSL_INT_T *N, 
	       float *X, 
	       SCSL_INT_T *incX);

  return sasum_(&N, X, &incX);
}


static __inline float ssum(SCSL_INT_T N, 
			   float *X,
			   SCSL_INT_T incX) {
  float ssum_(SCSL_INT_T *N, 
	      float *X, 
	      SCSL_INT_T *incX);

  return ssum_(&N, X, &incX);
}


static __inline double dnrm2(SCSL_INT_T N,
			     double *X,
			     SCSL_INT_T incX) {
  double dnrm2_(SCSL_INT_T *N,
		double *X, 
		SCSL_INT_T *incX);
  return dnrm2_(&N, X, &incX);
}


static __inline double dasum(SCSL_INT_T N,
			     double *X, 
			     SCSL_INT_T incX) {
  double dasum_(SCSL_INT_T *N, 
		double *X, 
		SCSL_INT_T *incX);

  return dasum_(&N, X, &incX);
}


static __inline double dsum(SCSL_INT_T N, 
			    double *X,
			    SCSL_INT_T incX) {
  double dsum_(SCSL_INT_T *N, 
	       double *X, 
	       SCSL_INT_T *incX);

  return dsum_(&N, X, &incX);
}


static __inline float scnrm2(SCSL_INT_T N, 
			     SCSL_COMPLEX_T *X, 
			     SCSL_INT_T incX) {
  float scnrm2_(SCSL_INT_T *N, 
		SCSL_COMPLEX_T *X, 
		SCSL_INT_T *incX);

  return scnrm2_(&N, X, &incX);
}


static __inline float scasum(SCSL_INT_T N, 
			     SCSL_COMPLEX_T *X, 
			     SCSL_INT_T incX) {
  float scasum_(SCSL_INT_T *N, 
		SCSL_COMPLEX_T *X,
		SCSL_INT_T *incX);

  return scasum_(&N, X, &incX);
}


static __inline double dznrm2(SCSL_INT_T N,
			      SCSL_ZOMPLEX_T *X,
			      SCSL_INT_T incX) {
  double dznrm2_(SCSL_INT_T *N, 
		 SCSL_ZOMPLEX_T *X,
		 SCSL_INT_T *incX);

  return dznrm2_(&N, X, &incX);
}


static __inline double dzasum(SCSL_INT_T N, 
			      SCSL_ZOMPLEX_T *X, 
			      SCSL_INT_T incX) {
  double dzasum_(SCSL_INT_T *N, 
		 SCSL_ZOMPLEX_T *X, 
		 SCSL_INT_T *incX);

  return dzasum_(&N, X, &incX);
}


#ifdef __INTEL_COMPILER

  /* Intel compiler passes complex function return value as first argument */

static __inline SCSL_CMPLX_T csum(SCSL_INT_T N, 
				  SCSL_COMPLEX_T *X, 
				  SCSL_INT_T incX) {
  void csum_(SCSL_CMPLX_T *,
	     SCSL_INT_T *, 
	     SCSL_COMPLEX_T *, 
	     SCSL_INT_T *);
  SCSL_CMPLX_T result;

  csum_(&result, &N, X, &incX);
  return result;
}


static __inline void csum_sub(SCSL_INT_T N, 
			      SCSL_COMPLEX_T *X, 
			      SCSL_INT_T incX,
			      SCSL_COMPLEX_T *sum) {
  void csum_(SCSL_CMPLX_T *,
	     SCSL_INT_T *, 
	     SCSL_COMPLEX_T *, 
	     SCSL_INT_T *);

  csum_((SCSL_CMPLX_T *) sum, &N, X, &incX);
}


static __inline SCSL_ZMPLX_T zsum(SCSL_INT_T N, 
				  SCSL_ZOMPLEX_T *X, 
				  SCSL_INT_T incX) {
  void zsum_(SCSL_ZMPLX_T *,
	     SCSL_INT_T *, 
	     SCSL_ZOMPLEX_T *, 
	     SCSL_INT_T *);
  SCSL_ZMPLX_T result;

  zsum_(&result, &N, X, &incX);
  return result;
}


static __inline void zsum_sub(SCSL_INT_T N, 
			      SCSL_ZOMPLEX_T *X, 
			      SCSL_INT_T incX,
			      SCSL_ZOMPLEX_T *sum) {
  void zsum_(SCSL_ZMPLX_T *,
	     SCSL_INT_T *, 
	     SCSL_ZOMPLEX_T *, 
	     SCSL_INT_T *);

  zsum_((SCSL_ZMPLX_T *) sum, &N, X, &incX);
}

#else

static __inline SCSL_CMPLX_T csum(SCSL_INT_T N, 
				  SCSL_COMPLEX_T *X, 
				  SCSL_INT_T incX) {
  SCSL_CMPLX_T csum_(SCSL_INT_T *N, 
		     SCSL_COMPLEX_T *X, 
		     SCSL_INT_T *incX);

  return csum_(&N, X, &incX);
}


static __inline void csum_sub(SCSL_INT_T N, 
			      SCSL_COMPLEX_T *X, 
			      SCSL_INT_T incX,
			      SCSL_COMPLEX_T *sum) {
  SCSL_CMPLX_T csum_(SCSL_INT_T *N, 
		     SCSL_COMPLEX_T *X, 
		     SCSL_INT_T *incX);

  *((SCSL_CMPLX_T *) sum) = csum_(&N, X, &incX);
}


static __inline SCSL_ZMPLX_T zsum(SCSL_INT_T N, 
				  SCSL_ZOMPLEX_T *X, 
				  SCSL_INT_T incX) {
  SCSL_ZMPLX_T zsum_(SCSL_INT_T *N, 
		     SCSL_ZOMPLEX_T *X, 
		     SCSL_INT_T *incX);

  return zsum_(&N, X, &incX);
}


static __inline void zsum_sub(SCSL_INT_T N, 
			      SCSL_ZOMPLEX_T *X, 
			      SCSL_INT_T incX,
			      SCSL_ZOMPLEX_T *sum) {
  SCSL_ZMPLX_T zsum_(SCSL_INT_T *N, 
		     SCSL_ZOMPLEX_T *X, 
		     SCSL_INT_T *incX);

  *((SCSL_ZMPLX_T *) sum) = zsum_(&N, X, &incX);
}

#endif


static __inline SCSL_INT_T isamax(SCSL_INT_T N, 
				  float *X, 
				  SCSL_INT_T incX) {
  SCSL_INT_T isamax_(SCSL_INT_T *N, 
		     float *X,
		     SCSL_INT_T *incX);

  return (isamax_(&N, X, &incX) - 1);
}


static __inline SCSL_INT_T ismax(SCSL_INT_T N,
				 float *X, 
				 SCSL_INT_T incX) {
  SCSL_INT_T ismax_(SCSL_INT_T *N,
		    float *X, 
		    SCSL_INT_T *incX);

  return (ismax_(&N, X, &incX) - 1);
}


static __inline SCSL_INT_T isamin(SCSL_INT_T N,
				  float *X, 
				  SCSL_INT_T incX) {
  SCSL_INT_T isamin_(SCSL_INT_T *N, 
		     float *X,
		     SCSL_INT_T *incX);

  return (isamin_(&N, X, &incX) - 1);
}


static __inline SCSL_INT_T ismin(SCSL_INT_T N, 
				 float *X, 
				 SCSL_INT_T incX) {
  SCSL_INT_T ismin_(SCSL_INT_T *N, 
		    float *X,
		    SCSL_INT_T *incX);

  return (ismin_(&N, X, &incX) - 1);
}


static __inline SCSL_INT_T idamax(SCSL_INT_T N,
				  double *X, 
				  SCSL_INT_T incX) {
  SCSL_INT_T idamax_(SCSL_INT_T *N, 
		     double *X,
		     SCSL_INT_T *incX);

  return (idamax_(&N, X, &incX) - 1);
}


static __inline SCSL_INT_T idmax(SCSL_INT_T N, 
				 double *X, 
				 SCSL_INT_T incX) {
  SCSL_INT_T idmax_(SCSL_INT_T *N, 
		    double *X,
		    SCSL_INT_T *incX);

  return (idmax_(&N, X, &incX) - 1);
}


static __inline SCSL_INT_T idamin(SCSL_INT_T N, 
				  double *X, 
				  SCSL_INT_T incX) {
  SCSL_INT_T idamin_(SCSL_INT_T *N, 
		     double *X,
		     SCSL_INT_T *incX);

  return (idamin_(&N, X, &incX) - 1);
}


static __inline SCSL_INT_T idmin(SCSL_INT_T N, 
				 double *X, 
				 SCSL_INT_T incX) {
  SCSL_INT_T idmin_(SCSL_INT_T *N,
		    double *X, 
		    SCSL_INT_T *incX);

  return (idmin_(&N, X, &incX) - 1);
}


static __inline SCSL_INT_T icamax(SCSL_INT_T N, 
				  SCSL_COMPLEX_T *X, 
				  SCSL_INT_T incX) {
  SCSL_INT_T icamax_(SCSL_INT_T *N, 
		     SCSL_COMPLEX_T *X,
		     SCSL_INT_T *incX);
  return (icamax_(&N, X, &incX) - 1);
}


static __inline SCSL_INT_T izamax(SCSL_INT_T N, 
				  SCSL_ZOMPLEX_T *X, 
				  SCSL_INT_T incX) {
  SCSL_INT_T izamax_(SCSL_INT_T *N, 
		     SCSL_ZOMPLEX_T *X,
		     SCSL_INT_T *incX);

  return (izamax_(&N, X, &incX) - 1);
}


static __inline void sswap(SCSL_INT_T N, 
			   float *X, 
			   SCSL_INT_T incX,
			   float *Y, 
			   SCSL_INT_T incY) {
  void sswap_(SCSL_INT_T *N, 
	      float *X, 
	      SCSL_INT_T *incX,
	      float *Y,
	      SCSL_INT_T *incY);

  sswap_(&N, X, &incX, Y, &incY);
}


static __inline void scopy(SCSL_INT_T N, 
			   float *X, 
			   SCSL_INT_T incX,
			   float *Y, 
			   SCSL_INT_T incY) {
  void scopy_(SCSL_INT_T *N, 
	      float *X, 
	      SCSL_INT_T *incX,
	      float *Y, 
	      SCSL_INT_T *incY);

  scopy_(&N, X, &incX, Y, &incY);
}


static __inline void saxpy(SCSL_INT_T N, 
			   float alpha, 
			   float *X,
			   SCSL_INT_T incX,
			   float *Y,
			   SCSL_INT_T incY) {
  void saxpy_(SCSL_INT_T *N,
	      float *alpha, 
	      float *X,
	      SCSL_INT_T *incX, 
	      float *Y, 
	      SCSL_INT_T *incY);

  saxpy_(&N, &alpha, X, &incX, Y, &incY);
}


static __inline void saxpby(SCSL_INT_T N, 
			    float alpha,
			    float *X,
			    SCSL_INT_T incX,
			    float beta,
			    float *Y, 
			    SCSL_INT_T incY) {
  void saxpby_(SCSL_INT_T *N, 
	       float *alpha,
	       float *X,
	       SCSL_INT_T *incX,
	       float *beta, 
	       float *Y,
	       SCSL_INT_T *incY);

  saxpby_(&N, &alpha, X, &incX, &beta, Y, &incY);
}


static __inline void shad(SCSL_INT_T N, 
			  float alpha, 
			  float *X, 
			  SCSL_INT_T incX, 
			  float *Y, 
			  SCSL_INT_T incY, 
			  float beta, 
			  float *Z, 
			  SCSL_INT_T incZ) {
  void shad_(SCSL_INT_T *N, 
	     float *alpha, 
	     float *X,
	     SCSL_INT_T *incX, 
	     float *Y,
	     SCSL_INT_T *incY, 
	     float *beta, 
	     float *Z, 
	     SCSL_INT_T *incZ);

  shad_(&N, &alpha, X, &incX, Y, &incY, &beta, Z, &incZ);
}


static __inline void dswap(SCSL_INT_T N, 
			   double *X, 
			   SCSL_INT_T incX,
			   double *Y, 
			   SCSL_INT_T incY) {
  void dswap_(SCSL_INT_T *N, 
	      double *X, 
	      SCSL_INT_T *incX,
	      double *Y, 
	      SCSL_INT_T *incY);

  dswap_(&N, X, &incX, Y, &incY);
}


static __inline void dcopy(SCSL_INT_T N,
			   double *X,
			   SCSL_INT_T incX,
			   double *Y, 
			   SCSL_INT_T incY) {
  void dcopy_(SCSL_INT_T *N,
	      double *X, 
	      SCSL_INT_T *incX,
	      double *Y, 
	      SCSL_INT_T *incY);

  dcopy_(&N, X, &incX, Y, &incY);
}


static __inline void daxpy(SCSL_INT_T N,
			   double alpha,
			   double *X,
			   SCSL_INT_T incX,
			   double *Y, 
			   SCSL_INT_T incY) {
  void daxpy_(SCSL_INT_T *N,
	      double *alpha,
	      double *X,
	      SCSL_INT_T *incX,
	      double *Y, 
	      SCSL_INT_T *incY);

  daxpy_(&N, &alpha, X, &incX, Y, &incY);
}


static __inline void daxpby(SCSL_INT_T N, 
			    double alpha, 
			    double *X,
			    SCSL_INT_T incX,
			    double beta,
			    double *Y,
			    SCSL_INT_T incY) {
  void daxpby_(SCSL_INT_T *N, 
	       double *alpha,
	       double *X,
	       SCSL_INT_T *incX,
	       double *beta,
	       double *Y, 
	       SCSL_INT_T *incY);

  daxpby_(&N, &alpha, X, &incX, &beta, Y, &incY);
}


static __inline void dhad(SCSL_INT_T N, 
			  double alpha, 
			  double *X, 
			  SCSL_INT_T incX, 
			  double *Y, 
			  SCSL_INT_T incY, 
			  double beta, 
			  double *Z, 
			  SCSL_INT_T incZ) {
  void dhad_(SCSL_INT_T *N, 
	     double *alpha, 
	     double *X,
	     SCSL_INT_T *incX, 
	     double *Y,
	     SCSL_INT_T *incY, 
	     double *beta, 
	     double *Z, 
	     SCSL_INT_T *incZ);

  dhad_(&N, &alpha, X, &incX, Y, &incY, &beta, Z, &incZ );
}


static __inline void cswap(SCSL_INT_T N, 
			   SCSL_COMPLEX_T *X,
			   SCSL_INT_T incX,
			   SCSL_COMPLEX_T *Y,
			   SCSL_INT_T incY) {
  void cswap_(SCSL_INT_T *N, 
	      SCSL_COMPLEX_T *X, 
	      SCSL_INT_T *incX,
	      SCSL_COMPLEX_T *Y, 
	      SCSL_INT_T *incY);

  cswap_(&N, X, &incX, Y, &incY);
}


static __inline void ccopy(SCSL_INT_T N, 
			   SCSL_COMPLEX_T *X, 
			   SCSL_INT_T incX,
			   SCSL_COMPLEX_T *Y, 
			   SCSL_INT_T incY) {
  void ccopy_(SCSL_INT_T *N,
	      SCSL_COMPLEX_T *X, 
	      SCSL_INT_T *incX,
	      SCSL_COMPLEX_T *Y, 
	      SCSL_INT_T *incY);

  ccopy_(&N, X, &incX, Y, &incY);
}


static __inline void caxpy(SCSL_INT_T N,
			   SCSL_COMPLEX_T *alpha,
			   SCSL_COMPLEX_T *X,
			   SCSL_INT_T incX,
			   SCSL_COMPLEX_T *Y, 
			   SCSL_INT_T incY) {
  void caxpy_(SCSL_INT_T *N, 
	      SCSL_COMPLEX_T *alpha, 
	      SCSL_COMPLEX_T *X,
	      SCSL_INT_T *incX, 
	      SCSL_COMPLEX_T *Y, 
	      SCSL_INT_T *incY);
  
  caxpy_(&N, alpha, X, &incX, Y, &incY);
}



static __inline void caxpby(SCSL_INT_T N, 
			    SCSL_COMPLEX_T *alpha, 
			    SCSL_COMPLEX_T *X, 
			    SCSL_INT_T incX, 
			    SCSL_COMPLEX_T *beta, 
			    SCSL_COMPLEX_T *Y, 
			    SCSL_INT_T incY) {
  void caxpby_(SCSL_INT_T *N, 
	       SCSL_COMPLEX_T *alpha, 
	       SCSL_COMPLEX_T *X,
	       SCSL_INT_T *incX, 
	       SCSL_COMPLEX_T *beta, 
	       SCSL_COMPLEX_T *Y, 
	       SCSL_INT_T *incY);

  caxpby_(&N, alpha, X, &incX, beta, Y, &incY);
}


static __inline void chad(SCSL_INT_T N, 
			  SCSL_COMPLEX_T *alpha, 
			  SCSL_COMPLEX_T *X, 
			  SCSL_INT_T incX, 
			  SCSL_COMPLEX_T *Y, 
			  SCSL_INT_T incY, 
			  SCSL_COMPLEX_T *beta, 
			  SCSL_COMPLEX_T *Z, 
			  SCSL_INT_T incZ) {
  void chad_(SCSL_INT_T *N, 
	     SCSL_COMPLEX_T *alpha, 
	     SCSL_COMPLEX_T *X,
	     SCSL_INT_T *incX, 
	     SCSL_COMPLEX_T *Y,
	     SCSL_INT_T *incY, 
	     SCSL_COMPLEX_T *beta, 
	     SCSL_COMPLEX_T *Z, 
	     SCSL_INT_T *incZ);

  chad_(&N, alpha, X, &incX, Y, &incY, beta, Z, &incZ);
}


static __inline void zswap(SCSL_INT_T N, 
			   SCSL_ZOMPLEX_T *X, 
			   SCSL_INT_T incX, 
			   SCSL_ZOMPLEX_T *Y, 
			   SCSL_INT_T incY) {
  void zswap_(SCSL_INT_T *N, 
	      SCSL_ZOMPLEX_T *X, 
	      SCSL_INT_T *incX, 
	      SCSL_ZOMPLEX_T *Y, 
	      SCSL_INT_T *incY);

  zswap_(&N, X, &incX, Y, &incY);
}


static __inline void zcopy(SCSL_INT_T N, 
			   SCSL_ZOMPLEX_T *X, 
			   SCSL_INT_T incX,
			   SCSL_ZOMPLEX_T *Y, 
			   SCSL_INT_T incY) {
  void zcopy_(SCSL_INT_T *N, 
	      SCSL_ZOMPLEX_T *X, 
	      SCSL_INT_T *incX,
	      SCSL_ZOMPLEX_T *Y, 
	      SCSL_INT_T *incY);

  zcopy_(&N, X, &incX, Y, &incY);
}


static __inline void zaxpy(SCSL_INT_T N,
			   SCSL_ZOMPLEX_T *alpha,
			   SCSL_ZOMPLEX_T *X,
			   SCSL_INT_T incX, 
			   SCSL_ZOMPLEX_T *Y, 
			   SCSL_INT_T incY) {
  void zaxpy_(SCSL_INT_T *N, 
	      SCSL_ZOMPLEX_T *alpha, 
	      SCSL_ZOMPLEX_T *X,
	      SCSL_INT_T *incX, 
	      SCSL_ZOMPLEX_T *Y,
	      SCSL_INT_T *incY);

  zaxpy_(&N, alpha, X, &incX, Y, &incY);
}


static __inline void zaxpby(SCSL_INT_T N, 
			    SCSL_ZOMPLEX_T *alpha, 
			    SCSL_ZOMPLEX_T *X, 
			    SCSL_INT_T incX, 
			    SCSL_ZOMPLEX_T *beta, 
			    SCSL_ZOMPLEX_T *Y, 
			    SCSL_INT_T incY) {
  void zaxpby_(SCSL_INT_T *N, 
	       SCSL_ZOMPLEX_T *alpha, 
	       SCSL_ZOMPLEX_T *X,
	       SCSL_INT_T *incX, 
	       SCSL_ZOMPLEX_T *beta, 
	       SCSL_ZOMPLEX_T *Y, 
	       SCSL_INT_T *incY);

  zaxpby_(&N, alpha, X, &incX, beta, Y, &incY );
}


static __inline void zhad(SCSL_INT_T N, 
			  SCSL_ZOMPLEX_T *alpha, 
			  SCSL_ZOMPLEX_T *X, 
			  SCSL_INT_T incX, 
			  SCSL_ZOMPLEX_T *Y, 
			  SCSL_INT_T incY, 
			  SCSL_ZOMPLEX_T *beta, 
			  SCSL_ZOMPLEX_T *Z, 
			  SCSL_INT_T incZ) {
  void zhad_(SCSL_INT_T *N, 
	     SCSL_ZOMPLEX_T *alpha, 
	     SCSL_ZOMPLEX_T *X,
	     SCSL_INT_T *incX, 
	     SCSL_ZOMPLEX_T *Y,
	     SCSL_INT_T *incY, 
	     SCSL_ZOMPLEX_T *beta, 
	     SCSL_ZOMPLEX_T *Z, 
	     SCSL_INT_T *incZ);

  zhad_(&N, alpha, X, &incX, Y, &incY, beta, Z, &incZ );
}


static __inline void srotg(float *a, 
			   float *b,
			   float *c,
			   float *s) {
  void srotg_(float *a,
	      float *b, 
	      float *c, 
	      float *s);

  srotg_(a, b, c, s);
}


static __inline void srotmg(float *d1, 
			    float *d2,
			    float *b1, 
			    float b2, 
			    float *P) {
  void srotmg_ (float *d1,
		float *d2,
		float *b1, 
		float *b2,
		float *P);

  srotmg_(d1, d2, b1, &b2, P);
}


static __inline void srot(SCSL_INT_T N, 
			  float *X, 
			  SCSL_INT_T incX,
			  float *Y, 
			  SCSL_INT_T incY, 
			  float c, 
			  float s) {
  void srot_(SCSL_INT_T *N, 
	     float *X, 
	     SCSL_INT_T *incX,
	     float *Y, 
	     SCSL_INT_T *incY, 
	     float *c, 
	     float *s);

  srot_(&N, X, &incX, Y, &incY, &c, &s);
}


static __inline void srotm(SCSL_INT_T N,
			   float *X, 
			   SCSL_INT_T incX,
			   float *Y, 
			   SCSL_INT_T incY,
			   float *P) {
  void srotm_(SCSL_INT_T *N, 
	      float *X, 
	      SCSL_INT_T *incX,
	      float *Y, 
	      SCSL_INT_T *incY,
	      float *P);

  srotm_(&N, X, &incX, Y, &incY, P);
}


static __inline void drotg(double *a,
			   double *b, 
			   double *c, 
			   double *s) {
  void drotg_(double *a,
	      double *b,
	      double *c,
	      double *s);

  drotg_(a, b, c, s);
}


static __inline void drotmg(double *d1,
			    double *d2, 
			    double *b1, 
			    double b2,
			    double *P) {
  void drotmg_(double *d1, 
	       double *d2,
	       double *b1,
	       double *b2,
	       double *P);

  drotmg_(d1, d2, b1, &b2, P);
}


static __inline void drot(SCSL_INT_T N, 
			  double *X,
			  SCSL_INT_T incX,
			  double *Y, 
			  SCSL_INT_T incY, 
			  double c, 
			  double s) {
  void drot_(SCSL_INT_T *N, 
	     double *X,
	     SCSL_INT_T *incX,
	     double *Y,
	     SCSL_INT_T *incY, 
	     double *c,
	     double *s);

  drot_(&N, X, &incX, Y, &incY, &c, &s);
}


static __inline void drotm(SCSL_INT_T N,
			   double *X,
			   SCSL_INT_T incX,
			   double *Y,
			   SCSL_INT_T incY,
			   double *P) {
  void drotm_ (SCSL_INT_T *N,
	       double *X,
	       SCSL_INT_T *incX,
	       double *Y, 
	       SCSL_INT_T *incY, 
	       double *P);

  drotm_(&N, X, &incX, Y, &incY, P);
}


static __inline void crot(SCSL_INT_T N, 
			  SCSL_COMPLEX_T *X, 
			  SCSL_INT_T incX,
			  SCSL_COMPLEX_T *Y, 
			  SCSL_INT_T incY, 
			  float c, 
			  SCSL_COMPLEX_T *s) {
  void crot_(SCSL_INT_T *N, 
	     SCSL_COMPLEX_T *X, 
	     SCSL_INT_T *incX,
	     SCSL_COMPLEX_T *Y, 
	     SCSL_INT_T *incY, 
	     float *c, 
	     SCSL_COMPLEX_T *s);

  crot_(&N, X, &incX, Y, &incY, &c, s);
}


static __inline void csrot(SCSL_INT_T N, 
			   SCSL_COMPLEX_T *X, 
			   SCSL_INT_T incX,
			   SCSL_COMPLEX_T *Y, 
			   SCSL_INT_T incY, 
			   float c, 
			   float s) {
  void csrot_(SCSL_INT_T *N, 
	      SCSL_COMPLEX_T *X, 
	      SCSL_INT_T *incX,
	      SCSL_COMPLEX_T *Y, 
	      SCSL_INT_T *incY, 
	      float *c, 
	      float *s);

  csrot_(&N, X, &incX, Y, &incY, &c, &s);
}


static __inline void crotg(SCSL_COMPLEX_T *a,
			   SCSL_COMPLEX_T *b,
			   float *c,
			   SCSL_COMPLEX_T *s) {
  void crotg_(SCSL_COMPLEX_T *a,
	      SCSL_COMPLEX_T *b,
	      float *c,
	      SCSL_COMPLEX_T *s);

  crotg_(a, b, c, s);
}


static __inline void sscal(SCSL_INT_T N,
			   float alpha,
			   float *X, 
			   SCSL_INT_T incX) {
  void sscal_(SCSL_INT_T *N,
	      float *alpha,
	      float *X,
	      SCSL_INT_T *incX);

  sscal_(&N, &alpha, X, &incX);
}


static __inline void dscal(SCSL_INT_T N,
			   double alpha, 
			   double *X, 
			   SCSL_INT_T incX) {
  void dscal_(SCSL_INT_T *N, 
	      double *alpha, 
	      double *X,
	      SCSL_INT_T *incX);

  dscal_(&N, &alpha, X, &incX);
}


static __inline void cscal(SCSL_INT_T N,
			   SCSL_COMPLEX_T *alpha, 
			   SCSL_COMPLEX_T *X,
			   SCSL_INT_T incX) {
  void cscal_(SCSL_INT_T *N, 
	      SCSL_COMPLEX_T *alpha,
	      SCSL_COMPLEX_T *X,
	      SCSL_INT_T *incX);

  cscal_(&N, alpha, X, &incX);
}


static __inline void zrot(SCSL_INT_T N, 
			  SCSL_ZOMPLEX_T *X, 
			  SCSL_INT_T incX,
			  SCSL_ZOMPLEX_T *Y, 
			  SCSL_INT_T incY, 
			  double c, 
			  SCSL_ZOMPLEX_T *s) {
  void zrot_(SCSL_INT_T *N, 
	     SCSL_ZOMPLEX_T *X, 
	     SCSL_INT_T *incX,
	     SCSL_ZOMPLEX_T *Y,
	     SCSL_INT_T *incY, 
	     double *c, 
	     SCSL_ZOMPLEX_T *s);

  zrot_(&N, X, &incX, Y, &incY, &c, s);
}


static __inline void zdrot(SCSL_INT_T N, 
			   SCSL_ZOMPLEX_T *X, 
			   SCSL_INT_T incX,
			   SCSL_ZOMPLEX_T *Y, 
			   SCSL_INT_T incY, 
			   double c, 
			   double s) {
  void zdrot_(SCSL_INT_T *N, 
	      SCSL_ZOMPLEX_T *X, 
	      SCSL_INT_T *incX,
	      SCSL_ZOMPLEX_T *Y,
	      SCSL_INT_T *incY, 
	      double *c, 
	      double *s);

  zdrot_(&N, X, &incX, Y, &incY, &c, &s);
}


static __inline void zrotg(SCSL_ZOMPLEX_T *a,
			   SCSL_ZOMPLEX_T *b,
			   double *c,
			   SCSL_ZOMPLEX_T *s) {
  void zrotg_(SCSL_ZOMPLEX_T *a,
	      SCSL_ZOMPLEX_T *b,
	      double *c,
	      SCSL_ZOMPLEX_T *s);

  zrotg_(a, b, c, s);
}


static __inline void zscal(SCSL_INT_T N,
			   SCSL_ZOMPLEX_T *alpha, 
			   SCSL_ZOMPLEX_T *X, 
			   SCSL_INT_T incX) {
  void zscal_(SCSL_INT_T *N, 
	      SCSL_ZOMPLEX_T *alpha,
	      SCSL_ZOMPLEX_T *X, 
	      SCSL_INT_T *incX);

  zscal_(&N, alpha, X, &incX);
}


static __inline void csscal(SCSL_INT_T N, 
			    float alpha, 
			    SCSL_COMPLEX_T *X, 
			    SCSL_INT_T incX) {
  void csscal_(SCSL_INT_T *N,
	       float *alpha,
	       SCSL_COMPLEX_T *X, 
	       SCSL_INT_T *incX);

  csscal_(&N, &alpha, X, &incX);
}


static __inline void zdscal(SCSL_INT_T N, 
			    double alpha, 
			    SCSL_ZOMPLEX_T *X,
			    SCSL_INT_T incX) {
  void zdscal_(SCSL_INT_T *N, 
	       double *alpha,
	       SCSL_ZOMPLEX_T *X, 
	       SCSL_INT_T *incX);

  zdscal_(&N, &alpha, X, &incX);
}

/*
 * ===========================================================================
 * Prototypes for level 2 BLAS
 * ===========================================================================
 */

static __inline void sgemv(char *TransA, 
			   SCSL_INT_T m, 
			   SCSL_INT_T n,
			   float alpha, 
			   float *a, 
			   SCSL_INT_T lda, 
			   float *x, 
			   SCSL_INT_T incx,  
			   float beta, 
			   float *y, 
			   SCSL_INT_T incy) {
  void sgemv_(char *, 
	      SCSL_INT_T *, 
	      SCSL_INT_T *, 
	      float *, 
	      float *, 
	      SCSL_INT_T *, 
	      float *, 
	      SCSL_INT_T *,  
	      float *, 
	      float *, 
	      SCSL_INT_T *);

  sgemv_(TransA, &m, &n, &alpha, a, &lda, x, &incx, &beta, y, &incy);
}


static __inline void sger(SCSL_INT_T m,
			  SCSL_INT_T n,
			  float alpha, 
			  float *x,
			  SCSL_INT_T incx, 
			  float *y, 
			  SCSL_INT_T incy,
			  float *a,
			  SCSL_INT_T lda) {
  void sger_(SCSL_INT_T *, 
	     SCSL_INT_T *, 
	     float *, 
	     float *,
	     SCSL_INT_T *, 
	     float *, 
	     SCSL_INT_T *,
	     float *,
	     SCSL_INT_T *);

  sger_(&m, &n, &alpha, x, &incx, y, &incy, a, &lda);
}


static __inline void sgesum(char *TransA,
			    SCSL_INT_T m, 
			    SCSL_INT_T n,
			    float alpha,
			    float *A, 
			    SCSL_INT_T lda, 
			    float beta,
			    float *B, 
			    SCSL_INT_T ldb) {
  void sgesum_(char *, 
	       SCSL_INT_T *, 
	       SCSL_INT_T *, 
	       float *,
	       float *, 
	       SCSL_INT_T *, 
	       float *, 
	       float *,
	       SCSL_INT_T *);

  sgesum_(TransA, &m, &n, &alpha, A, &lda, &beta, B, &ldb);
}


static __inline void strmv(char *Uplo, 
			   char *TransA,
			   char *Diag,
			   SCSL_INT_T n,
			   float *a,
			   SCSL_INT_T lda,
			   float *x,
			   SCSL_INT_T incx) {
  void strmv_(char *,
	      char *,
	      char *,
	      SCSL_INT_T *,
	      float *,
	      SCSL_INT_T *,
	      float *, 
	      SCSL_INT_T *);

  strmv_(Uplo, TransA, Diag, &n, a, &lda, x, &incx );
}


static __inline void strsv(char *Uplo,
			   char *TransA,
			   char *Diag,
			   SCSL_INT_T n,
			   float *a, 
			   SCSL_INT_T lda,
			   float *x, 
			   SCSL_INT_T incx) {
  void strsv_(char *, 
	      char *, 
	      char *, 
	      SCSL_INT_T *,
	      float *,
	      SCSL_INT_T *,
	      float *, 
	      SCSL_INT_T *);

  strsv_(Uplo, TransA, Diag, &n, a, &lda, x, &incx );
}


static __inline void ssymv(char *Uplo, 
			   SCSL_INT_T n,
			   float alpha, 
			   float *a, 
			   SCSL_INT_T lda, 
			   float *x,
			   SCSL_INT_T incx,
			   float beta,
			   float *y, 
			   SCSL_INT_T incy) {
  void ssymv_(char *, 
	      SCSL_INT_T *,
	      float *, 
	      float *,
	      SCSL_INT_T *,
	      float *, 
	      SCSL_INT_T *,
	      float *,
	      float *, 
	      SCSL_INT_T *);

  ssymv_(Uplo, &n, &alpha, a, &lda, x, &incx, &beta, y, &incy );
}


static __inline void csymv(char *Uplo, 
			   SCSL_INT_T n,
			   SCSL_COMPLEX_T *alpha, 
			   SCSL_COMPLEX_T *a, 
			   SCSL_INT_T lda, 
			   SCSL_COMPLEX_T *x,
			   SCSL_INT_T incx,
			   SCSL_COMPLEX_T *beta,
			   SCSL_COMPLEX_T *y, 
			   SCSL_INT_T incy) {
  void csymv_(char *, 
	      SCSL_INT_T *,
	      SCSL_COMPLEX_T *, 
	      SCSL_COMPLEX_T *,
	      SCSL_INT_T *,
	      SCSL_COMPLEX_T *, 
	      SCSL_INT_T *,
	      SCSL_COMPLEX_T *,
	      SCSL_COMPLEX_T *, 
	      SCSL_INT_T *);

  csymv_(Uplo, &n, alpha, a, &lda, x, &incx, beta, y, &incy );
}


static __inline void ssyr(char *Uplo, 
			  SCSL_INT_T n, 
			  float alpha, 
			  float *x,
			  SCSL_INT_T incx, 
			  float *a, 
			  SCSL_INT_T lda) {
  void ssyr_(char *,
	     SCSL_INT_T *,
	     float *, 
	     float *,
	     SCSL_INT_T *, 
	     float *, 
	     SCSL_INT_T *);

  ssyr_(Uplo, &n, &alpha, x, &incx, a, &lda);
}


static __inline void csyr(char *Uplo, 
			  SCSL_INT_T n, 
			  SCSL_COMPLEX_T *alpha, 
			  SCSL_COMPLEX_T *x,
			  SCSL_INT_T incx, 
			  SCSL_COMPLEX_T *a, 
			  SCSL_INT_T lda) {
  void csyr_(char *,
	     SCSL_INT_T *,
	     SCSL_COMPLEX_T *, 
	     SCSL_COMPLEX_T *,
	     SCSL_INT_T *, 
	     SCSL_COMPLEX_T *, 
	     SCSL_INT_T *);

  csyr_(Uplo, &n, alpha, x, &incx, a, &lda);
}


static __inline void ssyr2(char *Uplo, 
			   SCSL_INT_T n, 
			   float alpha, 
			   float *x,
			   SCSL_INT_T incx,
			   float *y, 
			   SCSL_INT_T incy,
			   float *a, 
			   SCSL_INT_T lda) {
  void ssyr2_(char *, 
	      SCSL_INT_T *,
	      float *,
	      float *,
	      SCSL_INT_T *, 
	      float *, 
	      SCSL_INT_T *, 
	      float *,
	      SCSL_INT_T *);

  ssyr2_(Uplo, &n, &alpha, x, &incx, y, &incy, a, &lda);
}


static __inline void sgbmv(char *TransA, 
			   SCSL_INT_T m, 
			   SCSL_INT_T n,
			   SCSL_INT_T kl,
			   SCSL_INT_T ku,
			   float alpha,
			   float *a, 
			   SCSL_INT_T lda, 
			   float *x,
			   SCSL_INT_T incx,  
			   float beta, 
			   float *y,
			   SCSL_INT_T incy ) {
  void sgbmv_(char *,
	      SCSL_INT_T *,
	      SCSL_INT_T *,
	      SCSL_INT_T *,
	      SCSL_INT_T *,
	      float *, 
	      float *, 
	      SCSL_INT_T *,
	      float *, 
	      SCSL_INT_T *,
	      float *, 
	      float *,
	      SCSL_INT_T *);

  sgbmv_(TransA, &m, &n, &kl, &ku, &alpha, a, &lda, x,
	 &incx, &beta, y, &incy );
}


static __inline void stbmv(char *Uplo,
			   char *TransA, 
			   char *Diag,
			   SCSL_INT_T n,
			   SCSL_INT_T k,
			   float *a,
			   SCSL_INT_T lda,
			   float *x,
			   SCSL_INT_T incx) {
  void stbmv_(char *,
	      char *, 
	      char *, 
	      SCSL_INT_T *,
	      SCSL_INT_T *,
	      float *,
	      SCSL_INT_T *,
	      float *,
	      SCSL_INT_T *);

  stbmv_(Uplo, TransA, Diag, &n, &k, a, &lda, x, &incx );
}


static __inline void stbsv(char *Uplo, 
			   char *TransA, 
			   char *Diag,
			   SCSL_INT_T n,
			   SCSL_INT_T k, 
			   float *a, 
			   SCSL_INT_T lda,
			   float *x, 
			   SCSL_INT_T incx) {
  void stbsv_(char *, 
	      char *, 
	      char *, 
	      SCSL_INT_T *,
	      SCSL_INT_T *, 
	      float *, 
	      SCSL_INT_T *, 
	      float *,
	      SCSL_INT_T *);

  stbsv_(Uplo, TransA, Diag, &n, &k, a, &lda, x, &incx );
}


static __inline void ssbmv(char *Uplo, 
			   SCSL_INT_T n,
			   SCSL_INT_T k, 
			   float alpha, 
			   float *a,
			   SCSL_INT_T lda,
			   float *x,
			   SCSL_INT_T incx,
			   float beta,
			   float *y, 
			   SCSL_INT_T incy) {
  void ssbmv_(char *, 
	      SCSL_INT_T *,
	      SCSL_INT_T *,
	      float *,
	      float *,
	      SCSL_INT_T *,
	      float *, 
	      SCSL_INT_T *,
	      float *,
	      float *,
	      SCSL_INT_T *);

  ssbmv_(Uplo, &n, &k, &alpha, a, &lda, x, &incx, &beta, y, &incy );
}


static __inline void sspmv(char *Uplo, 
			   SCSL_INT_T n,
			   float alpha, 
			   float *ap,
			   float *x,
			   SCSL_INT_T incx, 
			   float beta, 
			   float *y,
			   SCSL_INT_T incy) {
  void sspmv_(char *, 
	      SCSL_INT_T *, 
	      float *, 
	      float *, 
	      float *,
	      SCSL_INT_T *, 
	      float *, 
	      float *, 
	      SCSL_INT_T *);

  sspmv_(Uplo, &n, &alpha, ap, x, &incx, &beta, y, &incy );
}


static __inline void stpmv(char *Uplo, 
			   char *TransA, 
			   char *Diag,
			   SCSL_INT_T n,
			   float *ap,
			   float *x,
			   SCSL_INT_T incx) {
  void stpmv_(char *, 
	      char *, 
	      char *, 
	      SCSL_INT_T *,
	      float *, 
	      float *, 
	      SCSL_INT_T *);

  stpmv_(Uplo, TransA, Diag, &n, ap, x, &incx);
}


static __inline void stpsv(char *Uplo, 
			   char *TransA, 
			   char *Diag,
			   SCSL_INT_T n, 
			   float *ap,
			   float *x, 
			   SCSL_INT_T incx) {
  void stpsv_(char *, 
	      char *, 
	      char *, 
	      SCSL_INT_T *,
	      float *,
	      float *,
	      SCSL_INT_T *);

  stpsv_(Uplo, TransA, Diag, &n, ap, x, &incx);
}


static __inline void sspr(char *Uplo, 
			  SCSL_INT_T n,
			  float alpha,
			  float *x,
			  SCSL_INT_T incx,
			  float *ap) {
  void sspr_(char *, 
	     SCSL_INT_T *,
	     float *, 
	     float *,
	     SCSL_INT_T *,
	     float *);

  sspr_(Uplo, &n, &alpha, x, &incx, ap);
}


static __inline void sspr2(char *Uplo,
			   SCSL_INT_T n,
			   float alpha,
			   float *x,
			   SCSL_INT_T incx,
			   float *y, 
			   SCSL_INT_T incy,
			   float *ap) {
  void sspr2_(char *, 
	      SCSL_INT_T *,
	      float *, 
	      float *,
	      SCSL_INT_T *,
	      float *,
	      SCSL_INT_T *,
	      float *);
  sspr2_(Uplo, &n, &alpha, x, &incx, y, &incy, ap);
}


static __inline void dgemv( char *TransA, 
			    SCSL_INT_T m, 
			    SCSL_INT_T n, 
			    double alpha, 
			    double *a, 
			    SCSL_INT_T lda, 
			    double *x, 
			    SCSL_INT_T incx, 
			    double beta, 
			    double *y, 
			    SCSL_INT_T incy) {
  void dgemv_(char *, 
	      SCSL_INT_T *, 
	      SCSL_INT_T *, 
	      double *,
	      double *, 
	      SCSL_INT_T *, 
	      double *, 
	      SCSL_INT_T *,
	      double *, 
	      double *, 
	      SCSL_INT_T *);

  dgemv_(TransA, &m, &n, &alpha, a, &lda, x, &incx, &beta, y, &incy);
}


static __inline void dger(SCSL_INT_T m, 
			  SCSL_INT_T n, 
			  double alpha,
			  double *x, 
			  SCSL_INT_T incx, 
			  double *y,
			  SCSL_INT_T incy, 
			  double *a, 
			  SCSL_INT_T lda) {
  void dger_(SCSL_INT_T *,
	     SCSL_INT_T *,
	     double *,
	     double *,
	     SCSL_INT_T *, 
	     double *,
	     SCSL_INT_T *, 
	     double *,
	     SCSL_INT_T *);

  dger_(&m, &n, &alpha, x, &incx, y, &incy, a, &lda);
}


static __inline void dgesum(char *TransA,
			    SCSL_INT_T m, 
			    SCSL_INT_T n,
			    double alpha,
			    double *A, 
			    SCSL_INT_T lda, 
			    double beta,
			    double *B, 
			    SCSL_INT_T ldb) {
  void dgesum_(char *, 
	       SCSL_INT_T *, 
	       SCSL_INT_T *, 
	       double *,
	       double *, 
	       SCSL_INT_T *, 
	       double *, 
	       double *,
	       SCSL_INT_T *);

  dgesum_(TransA, &m, &n, &alpha, A, &lda, &beta, B, &ldb);
}


static __inline void dtrmv(char *Uplo, 
			   char *TransA, 
			   char *Diag,
			   SCSL_INT_T n, 
			   double *a, 
			   SCSL_INT_T lda,
			   double *x, 
			   SCSL_INT_T incx) {
  void dtrmv_(char *, 
	      char *, 
	      char *, 
	      SCSL_INT_T *,
	      double *,
	      SCSL_INT_T *, 
	      double *, 
	      SCSL_INT_T *);

  dtrmv_(Uplo, TransA, Diag, &n, a, &lda, x, &incx);
}


static __inline void dtrsv(char *Uplo, 
			   char *TransA, 
			   char *Diag,
			   SCSL_INT_T n,
			   double *a, 
			   SCSL_INT_T lda,
			   double *x,
			   SCSL_INT_T incx) {
  void dtrsv_(char *, 
	      char *, 
	      char *,
	      SCSL_INT_T *,
	      double *,
	      SCSL_INT_T *,
	      double *,
	      SCSL_INT_T *);

  dtrsv_(Uplo, TransA, Diag, &n, a, &lda, x, &incx);
}


static __inline void dsymv(char *Uplo,
			   SCSL_INT_T n,
			   double alpha,
			   double *a, 
			   SCSL_INT_T lda,
			   double *x, 
			   SCSL_INT_T incx,
			   double beta, 
			   double *y, 
			   SCSL_INT_T incy) {
  void dsymv_(char *, 
	      SCSL_INT_T *, 
	      double *, 
	      double *,
	      SCSL_INT_T *,
	      double *, 
	      SCSL_INT_T *,
	      double *,
	      double *,
	      SCSL_INT_T *);

  dsymv_(Uplo, &n, &alpha, a, &lda, x, &incx, &beta, y, &incy);
}


static __inline void zsymv(char *Uplo, 
			   SCSL_INT_T n,
			   SCSL_ZOMPLEX_T *alpha, 
			   SCSL_ZOMPLEX_T *a, 
			   SCSL_INT_T lda, 
			   SCSL_ZOMPLEX_T *x,
			   SCSL_INT_T incx,
			   SCSL_ZOMPLEX_T *beta,
			   SCSL_ZOMPLEX_T *y, 
			   SCSL_INT_T incy) {
  void zsymv_(char *, 
	      SCSL_INT_T *,
	      SCSL_ZOMPLEX_T *, 
	      SCSL_ZOMPLEX_T *,
	      SCSL_INT_T *,
	      SCSL_ZOMPLEX_T *, 
	      SCSL_INT_T *,
	      SCSL_ZOMPLEX_T *,
	      SCSL_ZOMPLEX_T *, 
	      SCSL_INT_T *);

  zsymv_(Uplo, &n, alpha, a, &lda, x, &incx, beta, y, &incy );
}


static __inline void dsyr(char *Uplo, 
			  SCSL_INT_T n, 
			  double alpha, 
			  double *x,
			  SCSL_INT_T incx,
			  double *a, 
			  SCSL_INT_T lda) {
  void dsyr_(char *,
	     SCSL_INT_T *,
	     double *,
	     double *,
	     SCSL_INT_T *,
	     double *, 
	     SCSL_INT_T *);

  dsyr_(Uplo, &n, &alpha, x, &incx, a, &lda);
}


static __inline void zsyr(char *Uplo, 
			  SCSL_INT_T n, 
			  SCSL_ZOMPLEX_T *alpha, 
			  SCSL_ZOMPLEX_T *x,
			  SCSL_INT_T incx, 
			  SCSL_ZOMPLEX_T *a, 
			  SCSL_INT_T lda) {
  void zsyr_(char *,
	     SCSL_INT_T *,
	     SCSL_ZOMPLEX_T *, 
	     SCSL_ZOMPLEX_T *,
	     SCSL_INT_T *, 
	     SCSL_ZOMPLEX_T *, 
	     SCSL_INT_T *);

  zsyr_(Uplo, &n, alpha, x, &incx, a, &lda);
}


static __inline void dsyr2(char *Uplo,
			   SCSL_INT_T n,
			   double alpha,
			   double *x,
			   SCSL_INT_T incx,
			   double *y, 
			   SCSL_INT_T incy,
			   double *a,
			   SCSL_INT_T lda) {
  void dsyr2_(char *,
	      SCSL_INT_T *, 
	      double *, 
	      double *, 
	      SCSL_INT_T *,
	      double *, 
	      SCSL_INT_T *, 
	      double *,
	      SCSL_INT_T *);

  dsyr2_(Uplo, &n, &alpha, x, &incx, y, &incy, a, &lda);
}


static __inline void dgbmv(char *TransA, 
			   SCSL_INT_T m, 
			   SCSL_INT_T n, 
			   SCSL_INT_T kl,
			   SCSL_INT_T ku, 
			   double alpha,
			   double *a, 
			   SCSL_INT_T lda, 
			   double *x, 
			   SCSL_INT_T incx, 
			   double beta, 
			   double *y, 
			   SCSL_INT_T incy) {
  void dgbmv_(char *, 
	      SCSL_INT_T *,
	      SCSL_INT_T *, 
	      SCSL_INT_T *,
	      SCSL_INT_T *, 
	      double *,
	      double *, 
	      SCSL_INT_T *,
	      double *, 
	      SCSL_INT_T *, 
	      double *,
	      double *,
	      SCSL_INT_T *);

  dgbmv_(TransA, &m, &n, &kl, &ku, &alpha, a, &lda, x, &incx, &beta, y, &incy);
}


static __inline void dtbmv(char *Uplo,
			   char *TransA,
			   char *Diag, 
			   SCSL_INT_T n,
			   SCSL_INT_T k, 
			   double *a,
			   SCSL_INT_T lda,
			   double *x, 
			   SCSL_INT_T incx) {
  void dtbmv_(char *, 
	      char *, 
	      char *,
	      SCSL_INT_T *,
	      SCSL_INT_T *, 
	      double *, 
	      SCSL_INT_T *, 
	      double *, 
	      SCSL_INT_T *);

  dtbmv_(Uplo, TransA, Diag, &n, &k, a, &lda, x, &incx);
}


static __inline void dtbsv(char *Uplo,
			   char *TransA, 
			   char *Diag,
			   SCSL_INT_T n,
			   SCSL_INT_T k, 
			   double *a, 
			   SCSL_INT_T lda,
			   double *x,
			   SCSL_INT_T incx) {
  void dtbsv_(char *, 
	      char *, 
	      char *, 
	      SCSL_INT_T *,
	      SCSL_INT_T *,
	      double *, 
	      SCSL_INT_T *, 
	      double *,
	      SCSL_INT_T *);

  dtbsv_(Uplo, TransA, Diag, &n, &k, a, &lda, x, &incx);
}


static __inline void dsbmv(char *Uplo,
			   SCSL_INT_T n,
			   SCSL_INT_T k,
			   double alpha, 
			   double *a,
			   SCSL_INT_T lda,
			   double *x, 
			   SCSL_INT_T incx,
			   double beta,
			   double *y,
			   SCSL_INT_T incy) {
  void dsbmv_(char *,
	      SCSL_INT_T *, 
	      SCSL_INT_T *, 
	      double *,
	      double *, 
	      SCSL_INT_T *,
	      double *,
	      SCSL_INT_T *,
	      double *,
	      double *,
	      SCSL_INT_T *);

  dsbmv_(Uplo, &n, &k, &alpha, a, &lda, x, &incx, &beta, y, &incy);
}


static __inline void dspmv(char *Uplo, 
			   SCSL_INT_T n, 
			   double alpha,
			   double *ap,
			   double *x,
			   SCSL_INT_T incx,
			   double beta, 
			   double *y,
			   SCSL_INT_T incy) {
  void dspmv_(char *, 
	      SCSL_INT_T *,
	      double *,
	      double *,
	      double *, 
	      SCSL_INT_T *,
	      double *, 
	      double *,
	      SCSL_INT_T *);

  dspmv_(Uplo, &n, &alpha, ap, x, &incx, &beta, y, &incy);
}


static __inline void dtpmv(char *Uplo, 
			   char *TransA,
			   char *Diag,
			   SCSL_INT_T n, 
			   double *ap, 
			   double *x, 
			   SCSL_INT_T incx) {
  void dtpmv_(char *, 
	      char *, 
	      char *, 
	      SCSL_INT_T *,
	      double *, 
	      double *,
	      SCSL_INT_T *);

  dtpmv_(Uplo, TransA, Diag, &n, ap, x, &incx);
}


static __inline void dtpsv(char *Uplo, 
			   char *TransA,
			   char *Diag,
			   SCSL_INT_T n, 
			   double *ap, 
			   double *x,
			   SCSL_INT_T incx) {
  void dtpsv_(char *,
	      char *,
	      char *, 
	      SCSL_INT_T *,
	      double *,
	      double *,
	      SCSL_INT_T *);
  dtpsv_(Uplo, TransA, Diag, &n, ap, x, &incx);
}


static __inline void dspr(char *Uplo, 
			  SCSL_INT_T n,
			  double alpha, 
			  double *x,
			  SCSL_INT_T incx,
			  double *ap) {
  void dspr_(char *, 
	     SCSL_INT_T *, 
	     double *, 
	     double *,
	     SCSL_INT_T *, 
	     double *);

  dspr_(Uplo, &n, &alpha, x, &incx, ap);
}


static __inline void dspr2(char *Uplo, 
			   SCSL_INT_T n,
			   double alpha,
			   double *x,
			   SCSL_INT_T incx,
			   double *y,
			   SCSL_INT_T incy,
			   double *ap){
  void dspr2_(char *,
	      SCSL_INT_T *, 
	      double *, 
	      double *,
	      SCSL_INT_T *,
	      double *,
	      SCSL_INT_T *, 
	      double *);

  dspr2_(Uplo, &n, &alpha, x, &incx, y, &incy, ap);
}


static __inline void cgemv(char *TransA, 
			   SCSL_INT_T m, 
			   SCSL_INT_T n, 
			   SCSL_COMPLEX_T *alpha, 
			   SCSL_COMPLEX_T *a, 
			   SCSL_INT_T lda, 
			   SCSL_COMPLEX_T *x, 
			   SCSL_INT_T incx,
			   SCSL_COMPLEX_T *beta, 
			   SCSL_COMPLEX_T *y, 
			   SCSL_INT_T incy) {
  void cgemv_(char *, 
	      SCSL_INT_T *, 
	      SCSL_INT_T *, 
	      SCSL_COMPLEX_T *,
	      SCSL_COMPLEX_T *, 
	      SCSL_INT_T *, 
	      SCSL_COMPLEX_T *, 
	      SCSL_INT_T *,
	      SCSL_COMPLEX_T *, 
	      SCSL_COMPLEX_T *, 
	      SCSL_INT_T *);

  cgemv_(TransA, &m, &n, alpha, a, &lda, x, &incx, beta, y, &incy);
}


static __inline void cgbmv(char *TransA, 
			   SCSL_INT_T m, 
			   SCSL_INT_T n, 
			   SCSL_INT_T kl,
			   SCSL_INT_T ku,
			   SCSL_COMPLEX_T *alpha, 
			   SCSL_COMPLEX_T *a, 
			   SCSL_INT_T lda, 
			   SCSL_COMPLEX_T *x,
			   SCSL_INT_T incx,  
			   SCSL_COMPLEX_T *beta, 
			   SCSL_COMPLEX_T *y,
			   SCSL_INT_T incy) {
  void cgbmv_(char *,
	      SCSL_INT_T *,
	      SCSL_INT_T *,
	      SCSL_INT_T *,
	      SCSL_INT_T *,
	      SCSL_COMPLEX_T *, 
	      SCSL_COMPLEX_T *,
	      SCSL_INT_T *,
	      SCSL_COMPLEX_T *, 
	      SCSL_INT_T *,
	      SCSL_COMPLEX_T *, 
	      SCSL_COMPLEX_T *,
	      SCSL_INT_T *);

  cgbmv_(TransA, &m, &n, &kl, &ku, alpha, a, &lda, x, &incx, beta, y, &incy);
}


static __inline void cgeru(SCSL_INT_T m,
			   SCSL_INT_T n,
			   SCSL_COMPLEX_T *alpha,
			   SCSL_COMPLEX_T *x,
			   SCSL_INT_T incx, 
			   SCSL_COMPLEX_T *y,
			   SCSL_INT_T incy,
			   SCSL_COMPLEX_T *a,
			   SCSL_INT_T lda) {
  void cgeru_(SCSL_INT_T *, 
	      SCSL_INT_T *,
	      SCSL_COMPLEX_T *, 
	      SCSL_COMPLEX_T *,
	      SCSL_INT_T *,
	      SCSL_COMPLEX_T *, 
	      SCSL_INT_T *, 
	      SCSL_COMPLEX_T *,
	      SCSL_INT_T *);

  cgeru_(&m, &n, alpha, x, &incx, y, &incy, a, &lda);
}


static __inline void cgerc(SCSL_INT_T m,
			   SCSL_INT_T n, 
			   SCSL_COMPLEX_T *alpha,
			   SCSL_COMPLEX_T *x,
			   SCSL_INT_T incx,
			   SCSL_COMPLEX_T *y,
			   SCSL_INT_T incy,
			   SCSL_COMPLEX_T *a,
			   SCSL_INT_T lda) {
  void cgerc_(SCSL_INT_T *, 
	      SCSL_INT_T *,
	      SCSL_COMPLEX_T *,
	      SCSL_COMPLEX_T *,
	      SCSL_INT_T *,
	      SCSL_COMPLEX_T *,
	      SCSL_INT_T *, 
	      SCSL_COMPLEX_T *,
	      SCSL_INT_T *);

  cgerc_(&m, &n, alpha, x, &incx, y, &incy, a, &lda);
}


static __inline void cgesum(char *TransA,
			    SCSL_INT_T m, 
			    SCSL_INT_T n,
			    SCSL_COMPLEX_T *alpha,
			    SCSL_COMPLEX_T *A, 
			    SCSL_INT_T lda, 
			    SCSL_COMPLEX_T *beta,
			    SCSL_COMPLEX_T *B, 
			    SCSL_INT_T ldb) {
  void cgesum_(char *, 
	       SCSL_INT_T *, 
	       SCSL_INT_T *, 
	       SCSL_COMPLEX_T *,
	       SCSL_COMPLEX_T *, 
	       SCSL_INT_T *, 
	       SCSL_COMPLEX_T *, 
	       SCSL_COMPLEX_T *,
	       SCSL_INT_T *);

  cgesum_(TransA, &m, &n, alpha, A, &lda, beta, B, &ldb);
}


static __inline void chemv(char *Uplo,
			   SCSL_INT_T n, 
			   SCSL_COMPLEX_T *alpha, 
			   SCSL_COMPLEX_T *a,
			   SCSL_INT_T lda,
			   SCSL_COMPLEX_T *x, 
			   SCSL_INT_T incx, 
			   SCSL_COMPLEX_T *beta, 
			   SCSL_COMPLEX_T *y, 
			   SCSL_INT_T incy) {
  void chemv_(char *, 
	      SCSL_INT_T *,
	      SCSL_COMPLEX_T *, 
	      SCSL_COMPLEX_T *,
	      SCSL_INT_T *, 
	      SCSL_COMPLEX_T *, 
	      SCSL_INT_T *, 
	      SCSL_COMPLEX_T *,
	      SCSL_COMPLEX_T *, 
	      SCSL_INT_T *);

  chemv_(Uplo, &n, alpha, a, &lda, x, &incx, beta, y, &incy);
}


static __inline void chbmv(char *Uplo,
			   SCSL_INT_T n,
			   SCSL_INT_T k,
			   SCSL_COMPLEX_T *alpha, 
			   SCSL_COMPLEX_T *a,
			   SCSL_INT_T lda, 
			   SCSL_COMPLEX_T *x, 
			   SCSL_INT_T incx,
			   SCSL_COMPLEX_T *beta,
			   SCSL_COMPLEX_T *y, 
			   SCSL_INT_T incy) {
  void chbmv_(char *,
	      SCSL_INT_T *, 
	      SCSL_INT_T *,
	      SCSL_COMPLEX_T *,
	      SCSL_COMPLEX_T *, 
	      SCSL_INT_T *,
	      SCSL_COMPLEX_T *, 
	      SCSL_INT_T *,
	      SCSL_COMPLEX_T *,
	      SCSL_COMPLEX_T *,
	      SCSL_INT_T *);

  chbmv_(Uplo, &n, &k, alpha, a, &lda, x, &incx, beta, y, &incy);
}


static __inline void chpmv(char *Uplo,
			   SCSL_INT_T n,
			   SCSL_COMPLEX_T *alpha, 
			   SCSL_COMPLEX_T *ap, 
			   SCSL_COMPLEX_T *x, 
			   SCSL_INT_T incx, 
			   SCSL_COMPLEX_T *beta,
			   SCSL_COMPLEX_T *y, 
			   SCSL_INT_T incy) {
  void chpmv_(char *,
	      SCSL_INT_T *,
	      SCSL_COMPLEX_T *, 
	      SCSL_COMPLEX_T *,
	      SCSL_COMPLEX_T *, 
	      SCSL_INT_T *, 
	      SCSL_COMPLEX_T *,
	      SCSL_COMPLEX_T *,
	      SCSL_INT_T *);

  chpmv_(Uplo, &n, alpha, ap, x, &incx, beta, y, &incy);
}


static __inline void ctbmv(char *Uplo,
			   char *TransA,
			   char *Diag,
			   SCSL_INT_T n,
			   SCSL_INT_T k, 
			   SCSL_COMPLEX_T *a, 
			   SCSL_INT_T lda, 
			   SCSL_COMPLEX_T *x,
			   SCSL_INT_T incx) {
  void ctbmv_(char *,
	      char *,
	      char *,
	      SCSL_INT_T *,
	      SCSL_INT_T *,
	      SCSL_COMPLEX_T *, 
	      SCSL_INT_T *, 
	      SCSL_COMPLEX_T *, 
	      SCSL_INT_T *);

  ctbmv_(Uplo, TransA, Diag, &n, &k, a, &lda, x, &incx);
}


static __inline void ctbsv(char *Uplo,
			   char *TransA,
			   char *Diag,
			   SCSL_INT_T n,
			   SCSL_INT_T k, 
			   SCSL_COMPLEX_T *a, 
			   SCSL_INT_T lda,
			   SCSL_COMPLEX_T *x, 
			   SCSL_INT_T incx) {
  void ctbsv_(char *,
	      char *, 
	      char *, 
	      SCSL_INT_T *,
	      SCSL_INT_T *, 
	      SCSL_COMPLEX_T *,
	      SCSL_INT_T *,
	      SCSL_COMPLEX_T *,
	      SCSL_INT_T *);

  ctbsv_(Uplo, TransA, Diag, &n, &k, a, &lda, x, &incx);
}


static __inline void ctrmv(char *Uplo, 
			   char *TransA, 
			   char *Diag,
			   SCSL_INT_T n, 
			   SCSL_COMPLEX_T *a, 
			   SCSL_INT_T lda,
			   SCSL_COMPLEX_T *x,
			   SCSL_INT_T incx) {
  void ctrmv_(char *,
	      char *, 
	      char *, 
	      SCSL_INT_T *,
	      SCSL_COMPLEX_T *, 
	      SCSL_INT_T *,
	      SCSL_COMPLEX_T *, 
	      SCSL_INT_T *);

  ctrmv_(Uplo, TransA, Diag, &n, a, &lda, x, &incx);
}


static __inline void ctrsv(char *Uplo, 
			   char *TransA, 
			   char *Diag,
			   SCSL_INT_T n, 
			   SCSL_COMPLEX_T *a, 
			   SCSL_INT_T lda,
			   SCSL_COMPLEX_T *x, 
			   SCSL_INT_T incx) {
  void ctrsv_(char *, 
	      char *, 
	      char *, 
	      SCSL_INT_T *,
	      SCSL_COMPLEX_T *, 
	      SCSL_INT_T *, 
	      SCSL_COMPLEX_T *,
	      SCSL_INT_T *);

  ctrsv_(Uplo, TransA, Diag, &n, a, &lda, x, &incx);
}


static __inline void cspmv(char *Uplo, 
			   SCSL_INT_T n,
			   SCSL_COMPLEX_T *alpha, 
			   SCSL_COMPLEX_T *ap,
			   SCSL_COMPLEX_T *x,
			   SCSL_INT_T incx, 
			   SCSL_COMPLEX_T *beta, 
			   SCSL_COMPLEX_T *y,
			   SCSL_INT_T incy) {
  void cspmv_(char *, 
	      SCSL_INT_T *, 
	      SCSL_COMPLEX_T *, 
	      SCSL_COMPLEX_T *, 
	      SCSL_COMPLEX_T *,
	      SCSL_INT_T *, 
	      SCSL_COMPLEX_T *, 
	      SCSL_COMPLEX_T *, 
	      SCSL_INT_T *);

  cspmv_(Uplo, &n, alpha, ap, x, &incx, beta, y, &incy );
}


static __inline void ctpmv(char *Uplo, 
			   char *TransA, 
			   char *Diag,
			   SCSL_INT_T n,
			   SCSL_COMPLEX_T *ap,
			   SCSL_COMPLEX_T *x, 
			   SCSL_INT_T incx) {
  void ctpmv_(char *, 
	      char *, 
	      char *, 
	      SCSL_INT_T *,
	      SCSL_COMPLEX_T *, 
	      SCSL_COMPLEX_T *, 
	      SCSL_INT_T *);

  ctpmv_(Uplo, TransA, Diag, &n, ap, x, &incx);
}


static __inline void ctpsv(char *Uplo,
			   char *TransA,
			   char *Diag,
			   SCSL_INT_T n,
			   SCSL_COMPLEX_T *ap,
			   SCSL_COMPLEX_T *x, 
			   SCSL_INT_T incx) {
  void ctpsv_(char *, 
	      char *, 
	      char *, 
	      SCSL_INT_T *,
	      SCSL_COMPLEX_T *, 
	      SCSL_COMPLEX_T *, 
	      SCSL_INT_T *);

  ctpsv_(Uplo, TransA, Diag, &n, ap, x, &incx);
}


static __inline void cspr(char *Uplo, 
			  SCSL_INT_T n,
			  SCSL_COMPLEX_T *alpha,
			  SCSL_COMPLEX_T *x,
			  SCSL_INT_T incx,
			  SCSL_COMPLEX_T *ap) {
  void cspr_(char *, 
	     SCSL_INT_T *,
	     SCSL_COMPLEX_T *, 
	     SCSL_COMPLEX_T *,
	     SCSL_INT_T *,
	     SCSL_COMPLEX_T *);

  cspr_(Uplo, &n, alpha, x, &incx, ap);
}


static __inline void chpr(char *Uplo, 
			  SCSL_INT_T n, 
			  float alpha, 
			  SCSL_COMPLEX_T *x, 
			  SCSL_INT_T incx,
			  SCSL_COMPLEX_T *ap) {
  void chpr_(char *,
	     SCSL_INT_T *,
	     float *,
	     SCSL_COMPLEX_T *,
	     SCSL_INT_T *, 
	     SCSL_COMPLEX_T *);

  chpr_(Uplo, &n, &alpha, x, &incx, ap);
}


static __inline void chpr2(char *Uplo, 
			   SCSL_INT_T n,
			   SCSL_COMPLEX_T *alpha, 
			   SCSL_COMPLEX_T *x,
			   SCSL_INT_T incx, 
			   SCSL_COMPLEX_T *y, 
			   SCSL_INT_T incy,
			   SCSL_COMPLEX_T *ap) {
  void chpr2_(char *, 
	      SCSL_INT_T *, 
	      SCSL_COMPLEX_T *, 
	      SCSL_COMPLEX_T *,
	      SCSL_INT_T *, 
	      SCSL_COMPLEX_T *, 
	      SCSL_INT_T *,
	      SCSL_COMPLEX_T *);

  chpr2_(Uplo, &n, alpha, x, &incx, y, &incy, ap);
}


static __inline void cher(char *Uplo,
			  SCSL_INT_T n,
			  float alpha,
			  SCSL_COMPLEX_T *x,
			  SCSL_INT_T incx, 
			  SCSL_COMPLEX_T *a,
			  SCSL_INT_T lda) {
  void cher_(char *,
	     SCSL_INT_T *,
	     float *, 
	     SCSL_COMPLEX_T *,
	     SCSL_INT_T *, 
	     SCSL_COMPLEX_T *,
	     SCSL_INT_T *);

  cher_(Uplo, &n, &alpha, x, &incx, a, &lda);
}


static __inline void cher2(char *Uplo, 
			   SCSL_INT_T n, 
			   SCSL_COMPLEX_T *alpha,
			   SCSL_COMPLEX_T *x,
			   SCSL_INT_T incx, 
			   SCSL_COMPLEX_T *y, 
			   SCSL_INT_T incy,
			   SCSL_COMPLEX_T *a,
			   SCSL_INT_T lda) {
  void cher2_(char *,
	      SCSL_INT_T *,
	      SCSL_COMPLEX_T *, 
	      SCSL_COMPLEX_T *,
	      SCSL_INT_T *, 
	      SCSL_COMPLEX_T *,
	      SCSL_INT_T *,
	      SCSL_COMPLEX_T *,
	      SCSL_INT_T *);

  cher2_(Uplo, &n, alpha, x, &incx, y, &incy, a, &lda);
}


static __inline void zgemv(char *TransA,
			   SCSL_INT_T m,
			   SCSL_INT_T n,
			   SCSL_ZOMPLEX_T *alpha, 
			   SCSL_ZOMPLEX_T *a,
			   SCSL_INT_T lda, 
			   SCSL_ZOMPLEX_T *x, 
			   SCSL_INT_T incx,
			   SCSL_ZOMPLEX_T *beta,
			   SCSL_ZOMPLEX_T *y, 
			   SCSL_INT_T incy) {
  void zgemv_(char *,
	      SCSL_INT_T *,
	      SCSL_INT_T *,
	      SCSL_ZOMPLEX_T *,
	      SCSL_ZOMPLEX_T *, 
	      SCSL_INT_T *,
	      SCSL_ZOMPLEX_T *,
	      SCSL_INT_T *,
	      SCSL_ZOMPLEX_T *, 
	      SCSL_ZOMPLEX_T *,
	      SCSL_INT_T *);

  zgemv_(TransA, &m, &n, alpha, a, &lda, x, &incx, beta, y, &incy);
}


static __inline void zgbmv(char *TransA,
			   SCSL_INT_T m,
			   SCSL_INT_T n,
			   SCSL_INT_T kl,
			   SCSL_INT_T ku,
			   SCSL_ZOMPLEX_T *alpha, 
			   SCSL_ZOMPLEX_T *a, 
			   SCSL_INT_T lda, 
			   SCSL_ZOMPLEX_T *x, 
			   SCSL_INT_T incx,  
			   SCSL_ZOMPLEX_T *beta, 
			   SCSL_ZOMPLEX_T *y, 
			   SCSL_INT_T incy) {
  void zgbmv_(char *,
	      SCSL_INT_T *,
	      SCSL_INT_T *,
	      SCSL_INT_T *,
	      SCSL_INT_T *,
	      SCSL_ZOMPLEX_T *, 
	      SCSL_ZOMPLEX_T *, 
	      SCSL_INT_T *,
	      SCSL_ZOMPLEX_T *, 
	      SCSL_INT_T *, 
	      SCSL_ZOMPLEX_T *,
	      SCSL_ZOMPLEX_T *,
	      SCSL_INT_T *);

  zgbmv_(TransA, &m, &n, &kl, &ku, alpha, a, &lda, x, &incx, beta, y, &incy);
}


static __inline void zgeru(SCSL_INT_T m, 
			   SCSL_INT_T n, 
			   SCSL_ZOMPLEX_T *alpha,
			   SCSL_ZOMPLEX_T *x,
			   SCSL_INT_T incx,
			   SCSL_ZOMPLEX_T *y,
			   SCSL_INT_T incy,
			   SCSL_ZOMPLEX_T *a,
			   SCSL_INT_T lda) {
  void zgeru_(SCSL_INT_T *,
	      SCSL_INT_T *,
	      SCSL_ZOMPLEX_T *, 
	      SCSL_ZOMPLEX_T *,
	      SCSL_INT_T *, 
	      SCSL_ZOMPLEX_T *, 
	      SCSL_INT_T *,
	      SCSL_ZOMPLEX_T *,
	      SCSL_INT_T *);

  zgeru_(&m, &n, alpha, x, &incx, y, &incy, a, &lda);
}


static __inline void zgerc(SCSL_INT_T m,
			   SCSL_INT_T n,
			   SCSL_ZOMPLEX_T *alpha, 
			   SCSL_ZOMPLEX_T *x,
			   SCSL_INT_T incx,
			   SCSL_ZOMPLEX_T *y, 
			   SCSL_INT_T incy,
			   SCSL_ZOMPLEX_T *a, 
			   SCSL_INT_T lda) {

  void zgerc_(SCSL_INT_T *,
	      SCSL_INT_T *,
	      SCSL_ZOMPLEX_T *, 
	      SCSL_ZOMPLEX_T *,
	      SCSL_INT_T *,
	      SCSL_ZOMPLEX_T *, 
	      SCSL_INT_T *, 
	      SCSL_ZOMPLEX_T *,
	      SCSL_INT_T *);

  zgerc_(&m, &n, alpha, x, &incx, y, &incy, a, &lda);
}


static __inline void zgesum(char *TransA,
			    SCSL_INT_T m, 
			    SCSL_INT_T n,
			    SCSL_ZOMPLEX_T *alpha,
			    SCSL_ZOMPLEX_T *A, 
			    SCSL_INT_T lda, 
			    SCSL_ZOMPLEX_T *beta,
			    SCSL_ZOMPLEX_T *B, 
			    SCSL_INT_T ldb) {
  void zgesum_(char *, 
	       SCSL_INT_T *, 
	       SCSL_INT_T *, 
	       SCSL_ZOMPLEX_T *,
	       SCSL_ZOMPLEX_T *, 
	       SCSL_INT_T *, 
	       SCSL_ZOMPLEX_T *, 
	       SCSL_ZOMPLEX_T *,
	       SCSL_INT_T *);

  zgesum_(TransA, &m, &n, alpha, A, &lda, beta, B, &ldb);
}


static __inline void zhemv(char *Uplo,
			   SCSL_INT_T n,
			   SCSL_ZOMPLEX_T *alpha, 
			   SCSL_ZOMPLEX_T *a,
			   SCSL_INT_T lda, 
			   SCSL_ZOMPLEX_T *x,
			   SCSL_INT_T incx, 
			   SCSL_ZOMPLEX_T *beta,
			   SCSL_ZOMPLEX_T *y,
			   SCSL_INT_T incy) {
  void zhemv_(char *, 
	      SCSL_INT_T *,
	      SCSL_ZOMPLEX_T *,
	      SCSL_ZOMPLEX_T *,
	      SCSL_INT_T *,
	      SCSL_ZOMPLEX_T *,
	      SCSL_INT_T *,
	      SCSL_ZOMPLEX_T *,
	      SCSL_ZOMPLEX_T *,
	      SCSL_INT_T *);

  zhemv_(Uplo, &n, alpha, a, &lda, x, &incx, beta, y, &incy);
}


static __inline void zhbmv(char *Uplo, 
			   SCSL_INT_T n, 
			   SCSL_INT_T k,
			   SCSL_ZOMPLEX_T *alpha, 
			   SCSL_ZOMPLEX_T *a, 
			   SCSL_INT_T lda,
			   SCSL_ZOMPLEX_T *x, 
			   SCSL_INT_T incx,
			   SCSL_ZOMPLEX_T *beta, 
			   SCSL_ZOMPLEX_T *y, 
			   SCSL_INT_T incy) {
  void zhbmv_(char *,
	      SCSL_INT_T *,
	      SCSL_INT_T *,
	      SCSL_ZOMPLEX_T *,
	      SCSL_ZOMPLEX_T *, 
	      SCSL_INT_T *, 
	      SCSL_ZOMPLEX_T *, 
	      SCSL_INT_T *,
	      SCSL_ZOMPLEX_T *, 
	      SCSL_ZOMPLEX_T *, 
	      SCSL_INT_T *);

  zhbmv_(Uplo, &n, &k, alpha, a, &lda, x, &incx, beta, y, &incy);
}


static __inline void zhpmv(char *Uplo, 
			   SCSL_INT_T n,
			   SCSL_ZOMPLEX_T *alpha, 
			   SCSL_ZOMPLEX_T *ap,
			   SCSL_ZOMPLEX_T *x, 
			   SCSL_INT_T incx, 
			   SCSL_ZOMPLEX_T *beta, 
			   SCSL_ZOMPLEX_T *y,
			   SCSL_INT_T incy) {
  void zhpmv_(char *, 
	      SCSL_INT_T *, 
	      SCSL_ZOMPLEX_T *,
	      SCSL_ZOMPLEX_T *,
	      SCSL_ZOMPLEX_T *, 
	      SCSL_INT_T *,
	      SCSL_ZOMPLEX_T *, 
	      SCSL_ZOMPLEX_T *,
	      SCSL_INT_T *);

  zhpmv_(Uplo, &n, alpha, ap, x, &incx, beta, y, &incy);
}


static __inline void ztbmv(char *Uplo,
			   char *TransA, 
			   char *Diag,
			   SCSL_INT_T n, 
			   SCSL_INT_T k, 
			   SCSL_ZOMPLEX_T *a, 
			   SCSL_INT_T lda, 
			   SCSL_ZOMPLEX_T *x, 
			   SCSL_INT_T incx) {
  void ztbmv_(char *, 
	      char *,
	      char *,
	      SCSL_INT_T *,
	      SCSL_INT_T *, 
	      SCSL_ZOMPLEX_T *,
	      SCSL_INT_T *,
	      SCSL_ZOMPLEX_T *, 
	      SCSL_INT_T *);

  ztbmv_(Uplo, TransA, Diag, &n, &k, a, &lda, x, &incx);
}


static __inline void ztbsv(char *Uplo,
			   char *TransA,
			   char *Diag,
			   SCSL_INT_T n,
			   SCSL_INT_T k,
			   SCSL_ZOMPLEX_T *a, 
			   SCSL_INT_T lda,
			   SCSL_ZOMPLEX_T *x, 
			   SCSL_INT_T incx) {
  void ztbsv_(char *,
	      char *,
	      char *,
	      SCSL_INT_T *,
	      SCSL_INT_T *, 
	      SCSL_ZOMPLEX_T *, 
	      SCSL_INT_T *,
	      SCSL_ZOMPLEX_T *,
	      SCSL_INT_T *);
  
  ztbsv_(Uplo, TransA, Diag, &n, &k, a, &lda, x, &incx);
}


static __inline void ztrmv(char *Uplo,
			   char *TransA,
			   char *Diag,
			   SCSL_INT_T n,
			   SCSL_ZOMPLEX_T *a, 
			   SCSL_INT_T lda,
			   SCSL_ZOMPLEX_T *x,
			   SCSL_INT_T incx) {
  void ztrmv_(char *,
	      char *, 
	      char *, 
	      SCSL_INT_T *,
	      SCSL_ZOMPLEX_T *, 
	      SCSL_INT_T *, 
	      SCSL_ZOMPLEX_T *, 
	      SCSL_INT_T *);

  ztrmv_(Uplo, TransA, Diag, &n, a, &lda, x, &incx);
}


static __inline void ztrsv(char *Uplo, 
			   char *TransA,
			   char *Diag,
			   SCSL_INT_T n, 
			   SCSL_ZOMPLEX_T *a,
			   SCSL_INT_T lda,
			   SCSL_ZOMPLEX_T *x,
			   SCSL_INT_T incx) {
  void ztrsv_(char *,
	      char *, 
	      char *, 
	      SCSL_INT_T *,
	      SCSL_ZOMPLEX_T *,
	      SCSL_INT_T *,
	      SCSL_ZOMPLEX_T *, 
	      SCSL_INT_T *);

  ztrsv_(Uplo, TransA, Diag, &n, a, &lda, x, &incx);
}


static __inline void zspmv(char *Uplo, 
			   SCSL_INT_T n,
			   SCSL_ZOMPLEX_T *alpha, 
			   SCSL_ZOMPLEX_T *ap,
			   SCSL_ZOMPLEX_T *x,
			   SCSL_INT_T incx, 
			   SCSL_ZOMPLEX_T *beta, 
			   SCSL_ZOMPLEX_T *y,
			   SCSL_INT_T incy) {
  void zspmv_(char *, 
	      SCSL_INT_T *, 
	      SCSL_ZOMPLEX_T *, 
	      SCSL_ZOMPLEX_T *, 
	      SCSL_ZOMPLEX_T *,
	      SCSL_INT_T *, 
	      SCSL_ZOMPLEX_T *, 
	      SCSL_ZOMPLEX_T *, 
	      SCSL_INT_T *);

  zspmv_(Uplo, &n, alpha, ap, x, &incx, beta, y, &incy );
}


static __inline void ztpmv(char *Uplo, 
			   char *TransA, 
			   char *Diag,
			   SCSL_INT_T n,
			   SCSL_ZOMPLEX_T *ap, 
			   SCSL_ZOMPLEX_T *x, 
			   SCSL_INT_T incx) {
  void ztpmv_(char *, 
	      char *, 
	      char *, 
	      SCSL_INT_T *,
	      SCSL_ZOMPLEX_T *,
	      SCSL_ZOMPLEX_T *, 
	      SCSL_INT_T *);

  ztpmv_(Uplo, TransA, Diag, &n, ap, x, &incx);
}


static __inline void ztpsv(char *Uplo,
			   char *TransA, 
			   char *Diag,
			   SCSL_INT_T n,
			   SCSL_ZOMPLEX_T *ap, 
			   SCSL_ZOMPLEX_T *x, 
			   SCSL_INT_T incx) {
  void ztpsv_(char *,
	      char *, 
	      char *, 
	      SCSL_INT_T *,
	      SCSL_ZOMPLEX_T *,
	      SCSL_ZOMPLEX_T *,
	      SCSL_INT_T *);

  ztpsv_(Uplo, TransA, Diag, &n, ap, x, &incx);
}


static __inline void zspr(char *Uplo, 
			  SCSL_INT_T n,
			  SCSL_ZOMPLEX_T *alpha,
			  SCSL_ZOMPLEX_T *x,
			  SCSL_INT_T incx,
			  SCSL_ZOMPLEX_T *ap) {
  void zspr_(char *, 
	     SCSL_INT_T *,
	     SCSL_ZOMPLEX_T *, 
	     SCSL_ZOMPLEX_T *,
	     SCSL_INT_T *,
	     SCSL_ZOMPLEX_T *);

  zspr_(Uplo, &n, alpha, x, &incx, ap);
}


static __inline void zhpr(char *Uplo, 
			  SCSL_INT_T n, 
			  double alpha,
			  SCSL_ZOMPLEX_T *x,
			  SCSL_INT_T incx,
			  SCSL_ZOMPLEX_T *ap) {
  void zhpr_(char *, 
	     SCSL_INT_T *, 
	     double *,
	     SCSL_ZOMPLEX_T *,
	     SCSL_INT_T *, 
	     SCSL_ZOMPLEX_T *);

  zhpr_(Uplo, &n, &alpha, x, &incx, ap);
}


static __inline void zhpr2(char *Uplo, 
			   SCSL_INT_T n, 
			   SCSL_ZOMPLEX_T *alpha,
			   SCSL_ZOMPLEX_T *x,
			   SCSL_INT_T incx, 
			   SCSL_ZOMPLEX_T *y, 
			   SCSL_INT_T incy,
			   SCSL_ZOMPLEX_T *ap) {
  void zhpr2_(char *, 
	      SCSL_INT_T *,
	      SCSL_ZOMPLEX_T *,
	      SCSL_ZOMPLEX_T *,
	      SCSL_INT_T *, 
	      SCSL_ZOMPLEX_T *,
	      SCSL_INT_T *,
	      SCSL_ZOMPLEX_T *);

  zhpr2_(Uplo, &n, alpha, x, &incx, y, &incy, ap);
}


static __inline void zher(char *Uplo, 
			  SCSL_INT_T n, 
			  double alpha,
			  SCSL_ZOMPLEX_T *x,
			  SCSL_INT_T incx, 
			  SCSL_ZOMPLEX_T *a, 
			  SCSL_INT_T lda) {
  void zher_(char *, 
	     SCSL_INT_T *,
	     double *, 
	     SCSL_ZOMPLEX_T *,
	     SCSL_INT_T *,
	     SCSL_ZOMPLEX_T *, 
	     SCSL_INT_T *);

  zher_(Uplo, &n, &alpha, x, &incx, a, &lda);
}


static __inline void zher2(char *Uplo,
			   SCSL_INT_T n, 
			   SCSL_ZOMPLEX_T *alpha, 
			   SCSL_ZOMPLEX_T *x,
			   SCSL_INT_T incx,
			   SCSL_ZOMPLEX_T *y, 
			   SCSL_INT_T incy,
			   SCSL_ZOMPLEX_T *a,
			   SCSL_INT_T lda) {
  void zher2_(char *, 
	      SCSL_INT_T *,
	      SCSL_ZOMPLEX_T *,
	      SCSL_ZOMPLEX_T *,
	      SCSL_INT_T *,
	      SCSL_ZOMPLEX_T *, 
	      SCSL_INT_T *,
	      SCSL_ZOMPLEX_T *,
	      SCSL_INT_T *);

  zher2_(Uplo, &n, alpha, x, &incx, y, &incy, a, &lda);
}

/*
 * ===========================================================================
 * Prototypes for level 3 BLAS
 * ===========================================================================
 */

static __inline void sgemm(char *TransA, 
			   char *TransB, 
			   SCSL_INT_T m, 
			   SCSL_INT_T n, 
			   SCSL_INT_T k, 
			   float alpha, 
			   float *a,
			   SCSL_INT_T lda,
			   float *b, 
			   SCSL_INT_T ldb,
			   float beta, 
			   float *c, 
			   SCSL_INT_T ldc) {
  void sgemm_(char *, 
	      char *,
	      SCSL_INT_T *,
	      SCSL_INT_T *,
	      SCSL_INT_T *,
	      float *, 
	      float *, 
	      SCSL_INT_T *,
	      float *, 
	      SCSL_INT_T *,
	      float *,
	      float *,
	      SCSL_INT_T *);

  sgemm_(TransA, TransB, &m, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); 
}


static __inline void ssymm(char *Side,
			   char *Uplo,
			   SCSL_INT_T m, 
			   SCSL_INT_T n,
			   float alpha,
			   float *a,
			   SCSL_INT_T lda,
			   float *b, 
			   SCSL_INT_T ldb,
			   float beta,
			   float *c, 
			   SCSL_INT_T ldc) {
  void ssymm_(char *,
	      char *,
	      SCSL_INT_T *,
	      SCSL_INT_T *,
	      float *,
	      float *,
	      SCSL_INT_T *, 
	      float *,
	      SCSL_INT_T *,
	      float *, 
	      float *, 
	      SCSL_INT_T *);

  ssymm_(Side, Uplo, &m, &n, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); 
}


static __inline void ssyrk(char *Uplo, 
			   char *Trans,
			   SCSL_INT_T n, 
			   SCSL_INT_T k,
			   float alpha,
			   float *a, 
			   SCSL_INT_T lda, 
			   float beta,
			   float *c,
			   SCSL_INT_T ldc) {
  void ssyrk_(char *, 
	      char *, 
	      SCSL_INT_T *, 
	      SCSL_INT_T *,
	      float *,
	      float *,
	      SCSL_INT_T *,
	      float *,
	      float *,
	      SCSL_INT_T *);

  ssyrk_(Uplo, Trans, &n, &k, &alpha, a, &lda, &beta, c, &ldc); 
}


static __inline void ssyr2k(char *Uplo,
			    char *Trans, 
			    SCSL_INT_T n, 
			    SCSL_INT_T k,
			    float alpha, 
			    float *a, 
			    SCSL_INT_T lda,
			    float *b,
			    SCSL_INT_T ldb, 
			    float beta, 
			    float *c, 
			    SCSL_INT_T ldc) {
  void ssyr2k_(char *, 
	       char *,
	       SCSL_INT_T *, 
	       SCSL_INT_T *,
	       float *, 
	       float *, 
	       SCSL_INT_T *, 
	       float *,
	       SCSL_INT_T *, 
	       float *, 
	       float *, 
	       SCSL_INT_T *);

  ssyr2k_(Uplo, Trans, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); 
}


static __inline void strmm(char *Side,
			   char *Uplo, 
			   char *Trans,
			   char *Diag,
			   SCSL_INT_T m, 
			   SCSL_INT_T n,
			   float alpha,
			   float *a, 
			   SCSL_INT_T lda,
			   float *b, 
			   SCSL_INT_T ldb) {
  void strmm_(char *, 
	      char *,
	      char *, 
	      char *,
	      SCSL_INT_T *, 
	      SCSL_INT_T *, 
	      float *, 
	      float *,
	      SCSL_INT_T *, 
	      float *, 
	      SCSL_INT_T *);

  strmm_(Side, Uplo, Trans, Diag, &m, &n, &alpha, a, &lda, b, &ldb);
}


static __inline void strsm(char *Side, 
			   char *Uplo,
			   char *Trans, 
			   char *Diag,
			   SCSL_INT_T m, 
			   SCSL_INT_T n,
			   float alpha, 
			   float *a, 
			   SCSL_INT_T lda, 
			   float *b, 
			   SCSL_INT_T ldb){
  void strsm_(char *, 
	      char *, 
	      char *, 
	      char *,
	      SCSL_INT_T *, 
	      SCSL_INT_T *,
	      float *,
	      float *,
	      SCSL_INT_T *,
	      float *, 
	      SCSL_INT_T *);
  
  strsm_(Side, Uplo, Trans, Diag, &m, &n, &alpha, a, &lda, b, &ldb);
}


static __inline void dgemm(char *TransA, 
			   char *TransB, 
			   SCSL_INT_T m,
			   SCSL_INT_T n,
			   SCSL_INT_T k,
			   double alpha,
			   double *a,
			   SCSL_INT_T lda,
			   double *b,
			   SCSL_INT_T ldb,
			   double beta, 
			   double *c, 
			   SCSL_INT_T ldc) {
  void dgemm_(char *,
	      char *,
	      SCSL_INT_T *,
	      SCSL_INT_T *,
	      SCSL_INT_T *,
	      double *,
	      double *,
	      SCSL_INT_T *,
	      double *,
	      SCSL_INT_T *, 
	      double *,
	      double *,
	      SCSL_INT_T *);

  dgemm_(TransA, TransB, &m, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); 
}


static __inline void dgemms(char *TransA, 
			    char *TransB, 
			    SCSL_INT_T m,
			    SCSL_INT_T n,
			    SCSL_INT_T k,
			    double alpha,
			    double *a,
			    SCSL_INT_T lda,
			    double *b,
			    SCSL_INT_T ldb,
			    double beta, 
			    double *c, 
			    SCSL_INT_T ldc) {
  void dgemms_(char *,
	      char *,
	      SCSL_INT_T *,
	      SCSL_INT_T *,
	      SCSL_INT_T *,
	      double *,
	      double *,
	      SCSL_INT_T *,
	      double *,
	      SCSL_INT_T *, 
	      double *,
	      double *,
	      SCSL_INT_T *);

  dgemms_(TransA, TransB, &m, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); 
}


static __inline void dsymm(char *Side,
			   char *Uplo,
			   SCSL_INT_T m,
			   SCSL_INT_T n,
			   double alpha,
			   double *a, 
			   SCSL_INT_T lda,
			   double *b, 
			   SCSL_INT_T ldb,
			   double beta,
			   double *c, 
			   SCSL_INT_T ldc) {
  void dsymm_(char *,
	      char *, 
	      SCSL_INT_T *, 
	      SCSL_INT_T *,
	      double *, 
	      double *,
	      SCSL_INT_T *,
	      double *,
	      SCSL_INT_T *,
	      double *,
	      double *,
	      SCSL_INT_T *);

  dsymm_(Side, Uplo, &m, &n, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); 
}


static __inline void dsyrk(char *Uplo, 
			   char *Trans, 
			   SCSL_INT_T n,
			   SCSL_INT_T k,
			   double alpha,
			   double *a,
			   SCSL_INT_T lda,
			   double beta,
			   double *c,
			   SCSL_INT_T ldc) {
  void dsyrk_(char *,
	      char *, 
	      SCSL_INT_T *,
	      SCSL_INT_T *,
	      double *, 
	      double *,
	      SCSL_INT_T *,
	      double *, 
	      double *,
	      SCSL_INT_T *);

  dsyrk_(Uplo, Trans, &n, &k, &alpha, a, &lda, &beta, c, &ldc); 
}


static __inline void dsyr2k(char *Uplo,
			    char *Trans, 
			    SCSL_INT_T n, 
			    SCSL_INT_T k,
			    double alpha,
			    double *a,
			    SCSL_INT_T lda,
			    double *b,
			    SCSL_INT_T ldb,
			    double beta, 
			    double *c,
			    SCSL_INT_T ldc) {
  void dsyr2k_(char *, 
	       char *, 
	       SCSL_INT_T *,
	       SCSL_INT_T *,
	       double *, 
	       double *,
	       SCSL_INT_T *,
	       double *,
	       SCSL_INT_T *, 
	       double *, 
	       double *, 
	       SCSL_INT_T *);

  dsyr2k_(Uplo, Trans, &n, &k, &alpha, a, &lda, b, &ldb, &beta, c, &ldc); 
}


static __inline void dtrmm(char *Side, 
			   char *Uplo, 
			   char *Trans,
			   char *Diag, 
			   SCSL_INT_T m, 
			   SCSL_INT_T n,
			   double alpha, 
			   double *a, 
			   SCSL_INT_T lda,
			   double *b,
			   SCSL_INT_T ldb) {
  void dtrmm_(char *,
	      char *,
	      char *,
	      char *,
	      SCSL_INT_T *,
	      SCSL_INT_T *,
	      double *,
	      double *,
	      SCSL_INT_T *, 
	      double *,
	      SCSL_INT_T *);

  dtrmm_(Side, Uplo, Trans, Diag, &m, &n, &alpha, a, &lda, b, &ldb);
}


static __inline void dtrsm(char *Side, 
			   char *Uplo,
			   char *Trans,
			   char *Diag,
			   SCSL_INT_T m,
			   SCSL_INT_T n,
			   double alpha, 
			   double *a,
			   SCSL_INT_T lda,
			   double *b, 
			   SCSL_INT_T ldb){
  void dtrsm_(char *,
	      char *,
	      char *,
	      char *,
	      SCSL_INT_T *,
	      SCSL_INT_T *,
	      double *, 
	      double *,
	      SCSL_INT_T *, 
	      double *,
	      SCSL_INT_T *);

  dtrsm_(Side, Uplo, Trans, Diag, &m, &n, &alpha, a, &lda, b, &ldb);
}


static __inline void cgemm(char *TransA, 
			   char *TransB, 
			   SCSL_INT_T m,
			   SCSL_INT_T n, 
			   SCSL_INT_T k, 
			   SCSL_COMPLEX_T *alpha,
			   SCSL_COMPLEX_T *a, 
			   SCSL_INT_T lda, 
			   SCSL_COMPLEX_T *b,
			   SCSL_INT_T ldb, 
			   SCSL_COMPLEX_T *beta, 
			   SCSL_COMPLEX_T *c, 
			   SCSL_INT_T ldc) {
  void cgemm_(char *, 
	      char *, 
	      SCSL_INT_T *,
	      SCSL_INT_T *,
	      SCSL_INT_T *,
	      SCSL_COMPLEX_T *, 
	      SCSL_COMPLEX_T *, 
	      SCSL_INT_T *, 
	      SCSL_COMPLEX_T *, 
	      SCSL_INT_T *,
	      SCSL_COMPLEX_T *, 
	      SCSL_COMPLEX_T *, 
	      SCSL_INT_T *);

  cgemm_(TransA, TransB, &m, &n, &k, alpha, a, &lda, b, &ldb, beta, c, &ldc); 
}


static __inline void cgemm3m(char *TransA, 
			     char *TransB, 
			     SCSL_INT_T m,
			     SCSL_INT_T n, 
			     SCSL_INT_T k, 
			     SCSL_COMPLEX_T *alpha,
			     SCSL_COMPLEX_T *a, 
			     SCSL_INT_T lda, 
			     SCSL_COMPLEX_T *b,
			     SCSL_INT_T ldb, 
			     SCSL_COMPLEX_T *beta, 
			     SCSL_COMPLEX_T *c, 
			     SCSL_INT_T ldc) {
  void cgemm3m_(char *, 
		char *, 
		SCSL_INT_T *,
		SCSL_INT_T *,
		SCSL_INT_T *,
		SCSL_COMPLEX_T *, 
		SCSL_COMPLEX_T *, 
		SCSL_INT_T *, 
		SCSL_COMPLEX_T *, 
		SCSL_INT_T *,
		SCSL_COMPLEX_T *, 
		SCSL_COMPLEX_T *, 
		SCSL_INT_T *);

  cgemm3m_(TransA, TransB, &m, &n, &k, alpha, a, &lda, b, &ldb, beta, c, &ldc); 
}


static __inline void csymm(char *Side, 
			   char *Uplo, 
			   SCSL_INT_T m,
			   SCSL_INT_T n,
			   SCSL_COMPLEX_T *alpha,
			   SCSL_COMPLEX_T *a, 
			   SCSL_INT_T lda,
			   SCSL_COMPLEX_T *b,
			   SCSL_INT_T ldb,
			   SCSL_COMPLEX_T *beta,
			   SCSL_COMPLEX_T *c,
			   SCSL_INT_T ldc) {
  void csymm_(char *, 
	      char *, 
	      SCSL_INT_T *,
	      SCSL_INT_T *,
	      SCSL_COMPLEX_T *, 
	      SCSL_COMPLEX_T *,
	      SCSL_INT_T *,
	      SCSL_COMPLEX_T *,
	      SCSL_INT_T *,
	      SCSL_COMPLEX_T *, 
	      SCSL_COMPLEX_T *,
	      SCSL_INT_T *);

  csymm_(Side, Uplo, &m, &n, alpha, a, &lda, b, &ldb, beta, c, &ldc); 
}


static __inline void csyrk(char *Uplo,
			   char *Trans,
			   SCSL_INT_T n,
			   SCSL_INT_T k,
			   SCSL_COMPLEX_T *alpha, 
			   SCSL_COMPLEX_T *a,
			   SCSL_INT_T lda,
			   SCSL_COMPLEX_T *beta,
			   SCSL_COMPLEX_T *c,
			   SCSL_INT_T ldc) {
  void csyrk_(char *, 
	      char *, 
	      SCSL_INT_T *, 
	      SCSL_INT_T *,
	      SCSL_COMPLEX_T *, 
	      SCSL_COMPLEX_T *, 
	      SCSL_INT_T *, 
	      SCSL_COMPLEX_T *,
	      SCSL_COMPLEX_T *, 
	      SCSL_INT_T *);

  csyrk_(Uplo, Trans, &n, &k, alpha, a, &lda, beta, c, &ldc); 
}


static __inline void csyr2k(char *Uplo, 
			    char *Trans,
			    SCSL_INT_T n,
			    SCSL_INT_T k,
			    SCSL_COMPLEX_T *alpha, 
			    SCSL_COMPLEX_T *a,
			    SCSL_INT_T lda, 
			    SCSL_COMPLEX_T *b,
			    SCSL_INT_T ldb,
			    SCSL_COMPLEX_T *beta, 
			    SCSL_COMPLEX_T *c, 
			    SCSL_INT_T ldc) {
  void csyr2k_(char *, 
	       char *, 
	       SCSL_INT_T *,
	       SCSL_INT_T *,
	       SCSL_COMPLEX_T *,
	       SCSL_COMPLEX_T *, 
	       SCSL_INT_T *, 
	       SCSL_COMPLEX_T *,
	       SCSL_INT_T *,
	       SCSL_COMPLEX_T *, 
	       SCSL_COMPLEX_T *, 
	       SCSL_INT_T *);

  csyr2k_(Uplo, Trans, &n, &k, alpha, a, &lda, b, &ldb, beta, c, &ldc); 
}


static __inline void chemm(char *Side, 
			   char *Uplo,
			   SCSL_INT_T m,
			   SCSL_INT_T n,
			   SCSL_COMPLEX_T *alpha, 
			   SCSL_COMPLEX_T *a, 
			   SCSL_INT_T lda, 
			   SCSL_COMPLEX_T *b, 
			   SCSL_INT_T ldb,
			   SCSL_COMPLEX_T *beta,
			   SCSL_COMPLEX_T *c, 
			   SCSL_INT_T ldc) { 
  void chemm_(char *,
	      char *,
	      SCSL_INT_T *,
	      SCSL_INT_T *,
	      SCSL_COMPLEX_T *, 
	      SCSL_COMPLEX_T *, 
	      SCSL_INT_T *,
	      SCSL_COMPLEX_T *,
	      SCSL_INT_T *,
	      SCSL_COMPLEX_T *,
	      SCSL_COMPLEX_T *,
	      SCSL_INT_T *);

  chemm_(Side, Uplo, &m, &n, alpha, a, &lda, b, &ldb, beta, c, &ldc); 
}


static __inline void cherk(char *Uplo, 
			   char *Trans,
			   SCSL_INT_T n,
			   SCSL_INT_T k,
			   float alpha,
			   SCSL_COMPLEX_T *a,
			   SCSL_INT_T lda, 
			   float beta,
			   SCSL_COMPLEX_T *c,
			   SCSL_INT_T ldc) {
  void cherk_(char *, 
	      char *, 
	      SCSL_INT_T *,
	      SCSL_INT_T *,
	      float *, 
	      SCSL_COMPLEX_T *, 
	      SCSL_INT_T *, 
	      float *,
	      SCSL_COMPLEX_T *, 
	      SCSL_INT_T *);

  cherk_(Uplo, Trans, &n, &k, &alpha, a, &lda, &beta, c, &ldc); 
}


static __inline void cher2k(char *Uplo,
			    char *Trans,
			    SCSL_INT_T n, 
			    SCSL_INT_T k,
			    SCSL_COMPLEX_T *alpha,
			    SCSL_COMPLEX_T *a, 
			    SCSL_INT_T lda, 
			    SCSL_COMPLEX_T *b,
			    SCSL_INT_T ldb,
			    float beta, 
			    SCSL_COMPLEX_T *c,
			    SCSL_INT_T ldc) {

  void cher2k_(char *,
	       char *,
	       SCSL_INT_T *,
	       SCSL_INT_T *,
	       SCSL_COMPLEX_T *, 
	       SCSL_COMPLEX_T *, 
	       SCSL_INT_T *,
	       SCSL_COMPLEX_T *,
	       SCSL_INT_T *, 
	       float *, 
	       SCSL_COMPLEX_T *,
	       SCSL_INT_T *);

  cher2k_(Uplo, Trans, &n, &k, alpha, a, &lda, b, &ldb, &beta, c, &ldc); 
}


static __inline void ctrmm(char *Side,
			   char *Uplo,
			   char *Trans, 
			   char *Diag,
			   SCSL_INT_T m,
			   SCSL_INT_T n, 
			   SCSL_COMPLEX_T *alpha, 
			   SCSL_COMPLEX_T *a, 
			   SCSL_INT_T lda, 
			   SCSL_COMPLEX_T *b, 
			   SCSL_INT_T ldb) {
  void ctrmm_(char *,
	      char *,
	      char *,
	      char *,
	      SCSL_INT_T *,
	      SCSL_INT_T *, 
	      SCSL_COMPLEX_T *,
	      SCSL_COMPLEX_T *,
	      SCSL_INT_T *, 
	      SCSL_COMPLEX_T *, 
	      SCSL_INT_T *);

  ctrmm_(Side, Uplo, Trans, Diag, &m, &n, alpha, a, &lda, b, &ldb);
}


static __inline void ctrsm(char *Side, 
			   char *Uplo, 
			   char *Trans, 
			   char *Diag,
			   SCSL_INT_T m,
			   SCSL_INT_T n, 
			   SCSL_COMPLEX_T *alpha,
			   SCSL_COMPLEX_T *a,
			   SCSL_INT_T lda,
			   SCSL_COMPLEX_T *b, 
			   SCSL_INT_T ldb) {
  void ctrsm_(char *, 
	      char *, 
	      char *, 
	      char *,
	      SCSL_INT_T *, 
	      SCSL_INT_T *,
	      SCSL_COMPLEX_T *, 
	      SCSL_COMPLEX_T *,
	      SCSL_INT_T *,
	      SCSL_COMPLEX_T *, 
	      SCSL_INT_T *);

  ctrsm_(Side, Uplo, Trans, Diag, &m, &n, alpha, a, &lda, b, &ldb);
}


static __inline void zgemm(char *TransA, 
			   char *TransB, 
			   SCSL_INT_T m,
			   SCSL_INT_T n, 
			   SCSL_INT_T k,
			   SCSL_ZOMPLEX_T *alpha, 
			   SCSL_ZOMPLEX_T *a, 
			   SCSL_INT_T lda, 
			   SCSL_ZOMPLEX_T *b, 
			   SCSL_INT_T ldb, 
			   SCSL_ZOMPLEX_T *beta, 
			   SCSL_ZOMPLEX_T *c, 
			   SCSL_INT_T ldc) {
  void zgemm_(char *, 
	      char *, 
	      SCSL_INT_T *, 
	      SCSL_INT_T *,
	      SCSL_INT_T *, 
	      SCSL_ZOMPLEX_T *, 
	      SCSL_ZOMPLEX_T *, 
	      SCSL_INT_T *,
	      SCSL_ZOMPLEX_T *, 
	      SCSL_INT_T *, 
	      SCSL_ZOMPLEX_T *, 
	      SCSL_ZOMPLEX_T *,
	      SCSL_INT_T *);

  zgemm_(TransA, TransB, &m, &n, &k, alpha, a, &lda, b, &ldb, beta, c, &ldc); 
}


static __inline void zgemm3m(char *TransA, 
			     char *TransB, 
			     SCSL_INT_T m,
			     SCSL_INT_T n, 
			     SCSL_INT_T k,
			     SCSL_ZOMPLEX_T *alpha, 
			     SCSL_ZOMPLEX_T *a, 
			     SCSL_INT_T lda, 
			     SCSL_ZOMPLEX_T *b, 
			     SCSL_INT_T ldb, 
			     SCSL_ZOMPLEX_T *beta, 
			     SCSL_ZOMPLEX_T *c, 
			     SCSL_INT_T ldc) {
  void zgemm3m_(char *, 
		char *, 
		SCSL_INT_T *, 
		SCSL_INT_T *,
		SCSL_INT_T *, 
		SCSL_ZOMPLEX_T *, 
		SCSL_ZOMPLEX_T *, 
		SCSL_INT_T *,
		SCSL_ZOMPLEX_T *, 
		SCSL_INT_T *, 
		SCSL_ZOMPLEX_T *, 
		SCSL_ZOMPLEX_T *,
		SCSL_INT_T *);

  zgemm3m_(TransA, TransB, &m, &n, &k, alpha, a, &lda, b, &ldb, beta, c, &ldc); 
}


static __inline void zsymm(char *Side, 
			   char *Uplo, 
			   SCSL_INT_T m,
			   SCSL_INT_T n,
			   SCSL_ZOMPLEX_T *alpha, 
			   SCSL_ZOMPLEX_T *a, 
			   SCSL_INT_T lda,
			   SCSL_ZOMPLEX_T *b,
			   SCSL_INT_T ldb,
			   SCSL_ZOMPLEX_T *beta, 
			   SCSL_ZOMPLEX_T *c, 
			   SCSL_INT_T ldc) {
  void zsymm_(char *,
	      char *, 
	      SCSL_INT_T *, 
	      SCSL_INT_T *,
	      SCSL_ZOMPLEX_T *, 
	      SCSL_ZOMPLEX_T *, 
	      SCSL_INT_T *, 
	      SCSL_ZOMPLEX_T *,
	      SCSL_INT_T *, 
	      SCSL_ZOMPLEX_T *, 
	      SCSL_ZOMPLEX_T *, 
	      SCSL_INT_T *);

  zsymm_(Side, Uplo, &m, &n, alpha, a, &lda, b, &ldb, beta, c, &ldc); 
}


static __inline void zsyrk(char *Uplo, 
			   char *Trans,
			   SCSL_INT_T n,
			   SCSL_INT_T k,
			   SCSL_ZOMPLEX_T *alpha,
			   SCSL_ZOMPLEX_T *a, 
			   SCSL_INT_T lda,
			   SCSL_ZOMPLEX_T *beta,
			   SCSL_ZOMPLEX_T *c,
			   SCSL_INT_T ldc) {
  void zsyrk_(char *, 
	      char *,
	      SCSL_INT_T *,
	      SCSL_INT_T *,
	      SCSL_ZOMPLEX_T *,
	      SCSL_ZOMPLEX_T *,
	      SCSL_INT_T *,
	      SCSL_ZOMPLEX_T *,
	      SCSL_ZOMPLEX_T *,
	      SCSL_INT_T *);

  zsyrk_(Uplo, Trans, &n, &k, alpha, a, &lda, beta, c, &ldc); 
}


static __inline void zsyr2k(char *Uplo, 
			    char *Trans, 
			    SCSL_INT_T n, 
			    SCSL_INT_T k,
			    SCSL_ZOMPLEX_T *alpha, 
			    SCSL_ZOMPLEX_T *a,
			    SCSL_INT_T lda,
			    SCSL_ZOMPLEX_T *b,
			    SCSL_INT_T ldb,
			    SCSL_ZOMPLEX_T *beta,
			    SCSL_ZOMPLEX_T *c, 
			    SCSL_INT_T ldc) {
  void zsyr2k_(char *, 
	       char *, 
	       SCSL_INT_T *,
	       SCSL_INT_T *,
	       SCSL_ZOMPLEX_T *,
	       SCSL_ZOMPLEX_T *,
	       SCSL_INT_T *, 
	       SCSL_ZOMPLEX_T *,
	       SCSL_INT_T *,
	       SCSL_ZOMPLEX_T *,
	       SCSL_ZOMPLEX_T *, 
	       SCSL_INT_T *);

  zsyr2k_(Uplo, Trans, &n, &k, alpha, a, &lda, b, &ldb, beta, c, &ldc); 
}


static __inline void zhemm(char *Side, 
			   char *Uplo, 
			   SCSL_INT_T m, 
			   SCSL_INT_T n,
			   SCSL_ZOMPLEX_T *alpha, 
			   SCSL_ZOMPLEX_T *a, 
			   SCSL_INT_T lda, 
			   SCSL_ZOMPLEX_T *b, 
			   SCSL_INT_T ldb,
			   SCSL_ZOMPLEX_T *beta, 
			   SCSL_ZOMPLEX_T *c, 
			   SCSL_INT_T ldc) {
  void zhemm_(char *, 
	      char *, 
	      SCSL_INT_T *, 
	      SCSL_INT_T *,
	      SCSL_ZOMPLEX_T *, 
	      SCSL_ZOMPLEX_T *, 
	      SCSL_INT_T *, 
	      SCSL_ZOMPLEX_T *,
	      SCSL_INT_T *, 
	      SCSL_ZOMPLEX_T *, 
	      SCSL_ZOMPLEX_T *, 
	      SCSL_INT_T *);

  zhemm_(Side, Uplo, &m, &n, alpha, a, &lda, b, &ldb, beta, c, &ldc); 
}


static __inline void zherk(char *Uplo, 
			   char *Trans, 
			   SCSL_INT_T n, 
			   SCSL_INT_T k,
			   double alpha, 
			   SCSL_ZOMPLEX_T *a, 
			   SCSL_INT_T lda, 
			   double beta,
			   SCSL_ZOMPLEX_T *c, 
			   SCSL_INT_T ldc) {
  void zherk_(char *,
	      char *, 
	      SCSL_INT_T *, 
	      SCSL_INT_T *,
	      double *, 
	      SCSL_ZOMPLEX_T *,
	      SCSL_INT_T *,
	      double *, 
	      SCSL_ZOMPLEX_T *, 
	      SCSL_INT_T *);

  zherk_(Uplo, Trans, &n, &k, &alpha, a, &lda, &beta, c, &ldc); 
}


static __inline void zher2k(char *Uplo, 
			    char *Trans, 
			    SCSL_INT_T n, 
			    SCSL_INT_T k,
			    SCSL_ZOMPLEX_T *alpha, 
			    SCSL_ZOMPLEX_T *a, 
			    SCSL_INT_T lda, 
			    SCSL_ZOMPLEX_T *b, 
			    SCSL_INT_T ldb,
			    double beta, 
			    SCSL_ZOMPLEX_T *c, 
			    SCSL_INT_T ldc) {
  void zher2k_(char *, 
	       char *, 
	       SCSL_INT_T *, 
	       SCSL_INT_T *,
	       SCSL_ZOMPLEX_T *,
	       SCSL_ZOMPLEX_T *, 
	       SCSL_INT_T *, 
	       SCSL_ZOMPLEX_T *,
	       SCSL_INT_T *, 
	       double *, 
	       SCSL_ZOMPLEX_T *, 
	       SCSL_INT_T *);

  zher2k_(Uplo, Trans, &n, &k, alpha, a, &lda, b, &ldb, &beta, c, &ldc); 
}


static __inline void ztrmm(char *Side, 
			   char *Uplo, 
			   char *Trans, 
			   char *Diag,
			   SCSL_INT_T m, 
			   SCSL_INT_T n, 
			   SCSL_ZOMPLEX_T *alpha, 
			   SCSL_ZOMPLEX_T *a, 
			   SCSL_INT_T lda, 
			   SCSL_ZOMPLEX_T *b, 
			   SCSL_INT_T ldb) {
  void ztrmm_(char *, 
	      char *,
	      char *,
	      char *,
	      SCSL_INT_T *, 
	      SCSL_INT_T *, 
	      SCSL_ZOMPLEX_T *, 
	      SCSL_ZOMPLEX_T *,
	      SCSL_INT_T *, 
	      SCSL_ZOMPLEX_T *, 
	      SCSL_INT_T *);

  ztrmm_(Side, Uplo, Trans, Diag, &m, &n, alpha, a, &lda, b, &ldb);
}


static __inline void ztrsm(char *Side, 
			   char *Uplo, 
			   char *Trans, 
			   char *Diag,
			   SCSL_INT_T m, 
			   SCSL_INT_T n, 
			   SCSL_ZOMPLEX_T *alpha, 
			   SCSL_ZOMPLEX_T *a,
			   SCSL_INT_T lda, 
			   SCSL_ZOMPLEX_T *b, 
			   SCSL_INT_T ldb) {
  void ztrsm_(char *, 
	      char *,
	      char *, 
	      char *,
	      SCSL_INT_T *, 
	      SCSL_INT_T *, 
	      SCSL_ZOMPLEX_T *, 
	      SCSL_ZOMPLEX_T *,
	      SCSL_INT_T *, 
	      SCSL_ZOMPLEX_T *, 
	      SCSL_INT_T *);

  ztrsm_(Side, Uplo, Trans, Diag, &m, &n, alpha, a, &lda, b, &ldb);
}

/*
 * auxiliary functions
 */

static __inline void xerbla(char *srname, 
			    SCSL_INT_T info) {
  void xerbla_(char *, 
	       SCSL_INT_T *, 
	       const int);

  xerbla_(srname, &info, 6);
}

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

#endif /* SCSL_BLAS_H */
