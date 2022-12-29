/*
 *      (C) COPYRIGHT SILICON GRAPHICS, INC.
 *      UNPUBLISHED PROPRIETARY INFORMATION.
 *      ALL RIGHTS RESERVED.
 */

/* Declarations for SCSL sparse solver routines */

#ifndef _SCSL_SPARSE_H
#define _SCSL_SPARSE_H

#ifdef __cplusplus
extern "C"
{
#endif

#if defined(SCSL_COMPLEX_T)
# undef SCSL_COMPLEX_T
#endif
#if defined(SCSL_ZOMPLEX_T)
# undef SCSL_ZOMPLEX_T
#endif
#if defined(SCSL_INT_T)
# undef SCSL_INT_T
#endif

/*
 * There are several possible approaches to handling arguments of
 * complex type. Our default is to define our own complex types,
 * scsl_complex and scsl_zomplex, and prototype the library routines
 * using pointers to these types. For compatibility with the 1.0--1.2
 * releases of SCSL, these types are aliased to complex and zomplex,
 * respectively. But if the C++ STL complex types are being used, this
 * will be detected and they will be used rather than the SCSL complex
 * types. Either way, the compiler will be able to check the types of
 * complex arguments since they have been fully prototyped.
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

#if defined(SCSL_VOID_ARGS)

/* Omit type checking; just prototype the complex arguments as void *.
 */
# define  SCSL_COMPLEX_T void
# define  SCSL_ZOMPLEX_T void

#elif defined(SCSL_USER_COMPLEX_T) && defined(SCSL_USER_ZOMPLEX_T)

/* Use user-supplied complex types in the prototypes.
 */
# define  SCSL_COMPLEX_T SCSL_USER_COMPLEX_T
# define  SCSL_ZOMPLEX_T SCSL_USER_ZOMPLEX_T

#else

/* Use SCSL-defined complex types
 */
typedef struct
{
  float re;
  float im;
} scsl_complex;

typedef struct
{
  double re;
  double im;
} scsl_zomplex;

/* C++ has it's own class/template for complex arithmetic. If it is
 * used, the function prototypes should match the C++ conventions.
 * For the cases when it is not used, the SCSL-defined complex types
 * are used, but we now use names that aren't likely to conflict with
 * other attempts to define complex types.
 */
# if defined(__cplusplus) && (defined(__sgi_template_complex) || defined(__STD_COMPLEX))
#  if !defined(SCSL_USE_SCSL_TYPES)
#   define SCSL_COMPLEX_T complex<float>
#   define SCSL_ZOMPLEX_T complex<double>
#  else
#   define SCSL_COMPLEX_T scsl_complex
#   define SCSL_ZOMPLEX_T scsl_zomplex
#  endif
# else
#  define SCSL_COMPLEX_T scsl_complex
#  define SCSL_ZOMPLEX_T scsl_zomplex
# endif

#endif

#if defined(SCSL_I8_INT_ARGS)
#  define SCSL_INT_T long long
#else
#  define SCSL_INT_T int
#endif

/* interface for SCSL 1.3 and earlier...
   These names are deprecated and will disappear
   in a future SCSL release ! */
void PSLDLT_Destroy(SCSL_INT_T token);

void PSLDU_Destroy(SCSL_INT_T token);


void PSLDLT_ExtractPerm(SCSL_INT_T token,
                        SCSL_INT_T *perm);

void PSLDU_ExtractPerm(SCSL_INT_T token,
		       SCSL_INT_T *perm);
                        

void PSLDLT_Factor(SCSL_INT_T token, 
		   SCSL_INT_T n,
		   SCSL_INT_T *pointers, 
		   SCSL_INT_T *indices, 
		   double *nz);

void PSLDU_Factor(SCSL_INT_T token, 
		  SCSL_INT_T n, 
		  SCSL_INT_T *pointers, 
		  SCSL_INT_T *indices,
		  double *nz);


void PSLDLT_FactorOOC(SCSL_INT_T token, 
		      SCSL_INT_T n, 
		      SCSL_INT_T *pointers, 
		      SCSL_INT_T *indices, 
		      double *nz);

void PSLDU_FactorOOC(SCSL_INT_T token, 
		     SCSL_INT_T n, 
		     SCSL_INT_T *pointers, 
		     SCSL_INT_T *indices, 
		     double *nz);


void PSLDLT_OOCLimit(SCSL_INT_T token, 
		     double limit);

void PSLDU_OOCLimit(SCSL_INT_T token, 
		    double limit);


void PSLDLT_OOCPath(SCSL_INT_T token, 
		    char *path);

void PSLDU_OOCPath(SCSL_INT_T token, 
		   char *path);


void PSLDLT_Ordering(SCSL_INT_T token, 
		     SCSL_INT_T ordering);

void PSLDU_Ordering(SCSL_INT_T token, 
		    SCSL_INT_T ordering);


void PSLDLT_Preprocess(SCSL_INT_T token, 
		       SCSL_INT_T n, 
		       SCSL_INT_T *pointers, 
		       SCSL_INT_T *indices,
		       long long *non_zeros, 
		       double *operations);

void PSLDU_Preprocess(SCSL_INT_T token, 
		      SCSL_INT_T n, 
		      SCSL_INT_T *pointers, 
		      SCSL_INT_T *indices,
		      long long *non_zeros, 
		      double *operations);


void PSLDLT_PreprocessZ(SCSL_INT_T token, 
			SCSL_INT_T n, 
			SCSL_INT_T *pointers, 
			SCSL_INT_T *indices,
			SCSL_INT_T *possibly_zero, 
			long long *non_zeros, 
			double *operations);

void PSLDU_PreprocessZ(SCSL_INT_T token, 
		       SCSL_INT_T n, 
		       SCSL_INT_T *pointers,
		       SCSL_INT_T *indices,
		       SCSL_INT_T *possibly_zero, 
		       long long *non_zeros, 
		       double *operations);


void PSLDLT_Solve(SCSL_INT_T token, 
		  double *x, 
		  double *b);

void PSLDU_Solve(SCSL_INT_T token, 
		 double *x,
		 double *b);


void PSLDLT_SolveM(SCSL_INT_T token, 
		   double *X, 
		   double *B, 
		   SCSL_INT_T n);

void PSLDU_SolveM(SCSL_INT_T token, 
		  double *X, 
		  double *B, 
		  SCSL_INT_T n);


double PSLDLT_Storage(SCSL_INT_T token);

double PSLDU_Storage(SCSL_INT_T token);


/* interface for SCSL 1.4 and later,
   double precision routines */
void DPSLDLT_Destroy(SCSL_INT_T token);

void DPSLDU_Destroy(SCSL_INT_T token);


void DPSLDLT_ExtractPerm(SCSL_INT_T token,
			 SCSL_INT_T *perm);

void DPSLDU_ExtractPerm(SCSL_INT_T token,
                        SCSL_INT_T *perm);
                        

void DPSLDLT_Factor(SCSL_INT_T token, 
		    SCSL_INT_T n,
		    SCSL_INT_T *pointers, 
		    SCSL_INT_T *indices, 
		    double *nz);

void DPSLDU_Factor(SCSL_INT_T token, 
		   SCSL_INT_T n, 
		   SCSL_INT_T *pointers, 
		   SCSL_INT_T *indices,
		   double *nz);


void DPSLDLT_FactorOOC(SCSL_INT_T token, 
		       SCSL_INT_T n, 
		       SCSL_INT_T *pointers, 
		       SCSL_INT_T *indices, 
		       double *nz);

void DPSLDU_FactorOOC(SCSL_INT_T token, 
		      SCSL_INT_T n, 
		      SCSL_INT_T *pointers, 
		      SCSL_INT_T *indices, 
		      double *nz);


void DPSLDLT_OOCLimit(SCSL_INT_T token, 
		      double limit);

void DPSLDU_OOCLimit(SCSL_INT_T token, 
		     double limit);


void DPSLDLT_OOCPath(SCSL_INT_T token, 
		     char *path);

void DPSLDU_OOCPath(SCSL_INT_T token, 
		    char *path);


void DPSLDLT_Ordering(SCSL_INT_T token, 
		      SCSL_INT_T ordering);

void DPSLDU_Ordering(SCSL_INT_T token, 
		     SCSL_INT_T ordering);


void DPSLDLT_Preprocess(SCSL_INT_T token, 
			SCSL_INT_T n, 
			SCSL_INT_T *pointers, 
			SCSL_INT_T *indices,
			long long *non_zeros, 
			double *operations);

void DPSLDU_Preprocess(SCSL_INT_T token, 
		       SCSL_INT_T n, 
		       SCSL_INT_T *pointers, 
		       SCSL_INT_T *indices,
		       long long *non_zeros, 
		       double *operations);


void DPSLDLT_PreprocessZ(SCSL_INT_T token, 
			 SCSL_INT_T n, 
			 SCSL_INT_T *pointers, 
			 SCSL_INT_T *indices,
			 SCSL_INT_T *possibly_zero, 
			 long long *non_zeros, 
			 double *operations);

void DPSLDU_PreprocessZ(SCSL_INT_T token, 
			SCSL_INT_T n, 
			SCSL_INT_T *pointers,
			SCSL_INT_T *indices,
			SCSL_INT_T *possibly_zero, 
			long long *non_zeros, 
			double *operations);


void DPSLDLT_Solve(SCSL_INT_T token, 
		   double *x, 
		   double *b);

void DPSLDU_Solve(SCSL_INT_T token, 
		  double *x,
		  double *b);


void DPSLDLT_SolveM(SCSL_INT_T token, 
		    double *X,
		    SCSL_INT_T ldx,
		    double *B,
		    SCSL_INT_T ldb,
		    SCSL_INT_T n);

void DPSLDU_SolveM(SCSL_INT_T token, 
		   double *X,
		   SCSL_INT_T ldx,
		   double *B,
		   SCSL_INT_T ldb,
		   SCSL_INT_T n);


double DPSLDLT_Storage(SCSL_INT_T token);

double DPSLDU_Storage(SCSL_INT_T token);


/* interface for SCSL 1.4 and later,
   complex routines */
void ZPSLDLT_Destroy(SCSL_INT_T token);

void ZPSLDU_Destroy(SCSL_INT_T token);


void ZPSLDLT_ExtractPerm(SCSL_INT_T token,
			 SCSL_INT_T *perm);

void ZPSLDU_ExtractPerm(SCSL_INT_T token,
                        SCSL_INT_T *perm);
                        

void ZPSLDLT_Factor(SCSL_INT_T token, 
		    SCSL_INT_T n,
		    SCSL_INT_T *pointers, 
		    SCSL_INT_T *indices, 
		    SCSL_ZOMPLEX_T *nz);

void ZPSLDU_Factor(SCSL_INT_T token, 
		   SCSL_INT_T n, 
		   SCSL_INT_T *pointers, 
		   SCSL_INT_T *indices,
		   SCSL_ZOMPLEX_T *nz);


void ZPSLDLT_FactorOOC(SCSL_INT_T token, 
		       SCSL_INT_T n, 
		       SCSL_INT_T *pointers, 
		       SCSL_INT_T *indices, 
		       SCSL_ZOMPLEX_T *nz);

void ZPSLDU_FactorOOC(SCSL_INT_T token, 
		      SCSL_INT_T n, 
		      SCSL_INT_T *pointers, 
		      SCSL_INT_T *indices, 
		      SCSL_ZOMPLEX_T *nz);


void ZPSLDLT_OOCLimit(SCSL_INT_T token, 
		      double limit);

void ZPSLDU_OOCLimit(SCSL_INT_T token, 
		     double limit);


void ZPSLDLT_OOCPath(SCSL_INT_T token, 
		     char *path);

void ZPSLDU_OOCPath(SCSL_INT_T token, 
		    char *path);


void ZPSLDLT_Ordering(SCSL_INT_T token, 
		      SCSL_INT_T ordering);

void ZPSLDU_Ordering(SCSL_INT_T token, 
		     SCSL_INT_T ordering);


void ZPSLDLT_Preprocess(SCSL_INT_T token, 
			SCSL_INT_T n, 
			SCSL_INT_T *pointers, 
			SCSL_INT_T *indices,
			long long *non_zeros, 
			double *operations);

void ZPSLDU_Preprocess(SCSL_INT_T token, 
		       SCSL_INT_T n, 
		       SCSL_INT_T *pointers, 
		       SCSL_INT_T *indices,
		       long long *non_zeros, 
		       double *operations);


void ZPSLDLT_PreprocessZ(SCSL_INT_T token, 
			 SCSL_INT_T n, 
			 SCSL_INT_T *pointers, 
			 SCSL_INT_T *indices,
			 SCSL_INT_T *possibly_zero, 
			 long long *non_zeros, 
			 double *operations);

void ZPSLDU_PreprocessZ(SCSL_INT_T token, 
			SCSL_INT_T n, 
			SCSL_INT_T *pointers,
			SCSL_INT_T *indices,
			SCSL_INT_T *possibly_zero, 
			long long *non_zeros, 
			double *operations);


void ZPSLDLT_Solve(SCSL_INT_T token, 
		   SCSL_ZOMPLEX_T *x, 
		   SCSL_ZOMPLEX_T *b);

void ZPSLDU_Solve(SCSL_INT_T token, 
		  SCSL_ZOMPLEX_T *x,
		  SCSL_ZOMPLEX_T *b);


void ZPSLDLT_SolveM(SCSL_INT_T token, 
		    SCSL_ZOMPLEX_T *X,
		    SCSL_INT_T ldx,
		    SCSL_ZOMPLEX_T *B,
		    SCSL_INT_T ldb,
		    SCSL_INT_T n);

void ZPSLDU_SolveM(SCSL_INT_T token, 
		   SCSL_ZOMPLEX_T *X,
		   SCSL_INT_T ldx,
		   SCSL_ZOMPLEX_T *B,
		   SCSL_INT_T ldb,
		   SCSL_INT_T n);


double ZPSLDLT_Storage(SCSL_INT_T token);

double ZPSLDU_Storage(SCSL_INT_T token);


/* Iterative routines */
void DIterative(SCSL_INT_T,
		SCSL_INT_T *,
		SCSL_INT_T *,
		double *,
		SCSL_INT_T,
		double *,
		double *,
		SCSL_INT_T,
		SCSL_INT_T,
		SCSL_INT_T,
		double,
		SCSL_INT_T *,
		double *);

void DIterative_DropTol(double);

void DIterative_DropStorage(double);

/* Old iterative interfaces, included for backwards
   compatibility.  These will disappear in a future
   SCSL release! */
void Iterative(SCSL_INT_T,
	       SCSL_INT_T *,
	       SCSL_INT_T *,
	       double *,
	       SCSL_INT_T,
	       double *,
	       double *,
	       SCSL_INT_T,
	       SCSL_INT_T,
	       SCSL_INT_T,
	       double,
	       SCSL_INT_T *,
	       double *);

void Iterative_DropTol(double);

void Iterative_DropStorage(double);


#undef SCSL_INT_T

#ifdef __cplusplus
}
#endif

#endif /* SCSL_SPARSE_H */
