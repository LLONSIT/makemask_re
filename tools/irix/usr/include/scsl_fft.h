/*
 *	(C) COPYRIGHT SILICON GRAPHICS, INC.
 *	UNPUBLISHED PROPRIETARY INFORMATION.
 *	ALL RIGHTS RESERVED.
 */


#ifndef _SGI_FFT_
#define _SGI_FFT_


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
 * other attempts to define complex types. SCSL 1.0--1.2 used the
 * names complex and zomplex, so to prevent breaking old code, the
 * old names are preserved, but can be disbaled bt defining
 * SCSL_DONT_USE_OLD_TYPES (e.g., cc -DSCSL_DONT_USE_OLD_TYPES ...).
 */
# if defined(__cplusplus) && defined(__sgi_template_complex)
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
#  if !defined(SCSL_DONT_USE_OLD_TYPES)
   typedef scsl_complex complex;
   typedef scsl_zomplex zomplex;
#  endif
# endif

#endif

/* Integer arguments are 4 bytes in the standard version of SCSL,
 * 8 bytes in the I8 version.
 */
#if defined(SCSL_I8_INT_ARGS)
# define SCSL_INT_T	long long
#else
# define SCSL_INT_T	int
#endif


/* ******************************************************************** */
/* ************************* Single Precision ************************* */
/* ******************************************************************** */


/* Complex-to-Complex 1D FFT's */
SCSL_INT_T
ccfft(SCSL_INT_T isign, SCSL_INT_T n, float scale,
      SCSL_COMPLEX_T *input, SCSL_COMPLEX_T *output,
      float *table, float *work, SCSL_INT_T *isys);

SCSL_INT_T
ccfft_(SCSL_INT_T *isign, SCSL_INT_T *n, float *scale,
       SCSL_COMPLEX_T *input, SCSL_COMPLEX_T *output,
       float *table, float *work, SCSL_INT_T *isys);


/* Complex-to-Complex 2D FFT's */
SCSL_INT_T
ccfft2d(SCSL_INT_T isign,
	SCSL_INT_T nx, SCSL_INT_T ny, float scale,
	SCSL_COMPLEX_T *input, SCSL_INT_T l_col_i,
	SCSL_COMPLEX_T *output, SCSL_INT_T l_col_o,
	float *table, float *work, SCSL_INT_T *isys);

SCSL_INT_T
ccfft2d_(SCSL_INT_T *isign,
	 SCSL_INT_T *nx, SCSL_INT_T *ny, float *scale,
	 SCSL_COMPLEX_T *input, SCSL_INT_T *l_col_i,
	 SCSL_COMPLEX_T *output, SCSL_INT_T *l_col_o,
	 float *table, float *work, SCSL_INT_T *isys);


/* Complex-to-Complex 3D FFT's */
SCSL_INT_T
ccfft3d(SCSL_INT_T isign,
	SCSL_INT_T nx, SCSL_INT_T ny, SCSL_INT_T nz, float scale,
	SCSL_COMPLEX_T *input, SCSL_INT_T l_x_i, SCSL_INT_T l_y_i,
	SCSL_COMPLEX_T *output, SCSL_INT_T l_x_o, SCSL_INT_T l_y_o,
	float *table, float *work, SCSL_INT_T *isys);

SCSL_INT_T
ccfft3d_(SCSL_INT_T *isign,
	 SCSL_INT_T *nx, SCSL_INT_T *ny, SCSL_INT_T *nz,
	 float *scale,
	 SCSL_COMPLEX_T *input, SCSL_INT_T *l_x_i, SCSL_INT_T *l_y_i,
	 SCSL_COMPLEX_T *output, SCSL_INT_T *l_x_o, SCSL_INT_T *l_y_o,
	 float *table, float *work, SCSL_INT_T *isys);


/* Complex-to-Complex Multiple 1D FFT's */
SCSL_INT_T
ccfftm(SCSL_INT_T isign,
       SCSL_INT_T n, SCSL_INT_T n_fft, float scale,
       SCSL_COMPLEX_T *input, SCSL_INT_T l_col_i,
       SCSL_COMPLEX_T *output, SCSL_INT_T l_col_o,
       float *table, float *work, SCSL_INT_T *isys);

SCSL_INT_T
ccfftm_(SCSL_INT_T *isign,
	SCSL_INT_T *n, SCSL_INT_T *n_fft, float *scale,
	SCSL_COMPLEX_T *input, SCSL_INT_T *l_col_i,
	SCSL_COMPLEX_T *output, SCSL_INT_T *l_col_o,
	float *table, float *work, SCSL_INT_T *isys);

SCSL_INT_T
ccfftmr(SCSL_INT_T isign,
	SCSL_INT_T n, SCSL_INT_T n_fft, float scale,
        SCSL_COMPLEX_T *input, SCSL_INT_T l_col_i,
        SCSL_COMPLEX_T *output, SCSL_INT_T l_col_o,
        float *table, float *work, SCSL_INT_T *isys);

SCSL_INT_T
ccfftmr_(SCSL_INT_T *isign,
	 SCSL_INT_T *n, SCSL_INT_T *n_fft, float *scale,
	 SCSL_COMPLEX_T *input, SCSL_INT_T *l_col_i,
	 SCSL_COMPLEX_T *output, SCSL_INT_T *l_col_o,
	 float *table, float *work, SCSL_INT_T *isys);


/* Real-to-Complex 1D FFT's */
SCSL_INT_T
scfft(SCSL_INT_T isign, SCSL_INT_T n, float scale, 
      float *input, SCSL_COMPLEX_T *output,
      float *table, float *work, SCSL_INT_T *isys);

SCSL_INT_T
scfft_(SCSL_INT_T *isign, SCSL_INT_T *n, float *scale, 
       float *input, SCSL_COMPLEX_T *output,
       float *table, float *work, SCSL_INT_T *isys);


/* Real-to-Complex 2D FFT's */
SCSL_INT_T
scfft2d(SCSL_INT_T isign,
	SCSL_INT_T nx, SCSL_INT_T ny, float scale,
	float *input, SCSL_INT_T l_col_i,
	SCSL_COMPLEX_T *output, SCSL_INT_T l_col_o,
	float *table, float *work, SCSL_INT_T *isys);

SCSL_INT_T
scfft2d_(SCSL_INT_T *isign,
	 SCSL_INT_T *nx, SCSL_INT_T *ny, float *scale,
	 float *input, SCSL_INT_T *l_col_i,
	 SCSL_COMPLEX_T *output, SCSL_INT_T *l_col_o,
	 float *table, float *work, SCSL_INT_T *isys);


/* Real-to-Complex 3D FFT's */
SCSL_INT_T
scfft3d(SCSL_INT_T isign,
	SCSL_INT_T nx, SCSL_INT_T ny, SCSL_INT_T nz, float scale,
	float *input, SCSL_INT_T l_x_i, SCSL_INT_T l_y_i,
	SCSL_COMPLEX_T *output, SCSL_INT_T l_x_o, SCSL_INT_T l_y_o,
	float *table, float *work, SCSL_INT_T *isys);

SCSL_INT_T
scfft3d_(SCSL_INT_T *isign,
	 SCSL_INT_T *nx, SCSL_INT_T *ny, SCSL_INT_T *nz,
	 float *scale,
	 float *input, SCSL_INT_T *l_x_i, SCSL_INT_T *l_y_i,
	 SCSL_COMPLEX_T *output, SCSL_INT_T *l_x_o, SCSL_INT_T *l_y_o,
	 float *table, float *work, SCSL_INT_T *isys);


/* Real-to-Complex Multiple 1D FFT's */
SCSL_INT_T
scfftm(SCSL_INT_T isign,
       SCSL_INT_T n, SCSL_INT_T n_fft, float scale,
       float *input, SCSL_INT_T l_col_i,
       SCSL_COMPLEX_T *output, SCSL_INT_T l_col_o,
       float *table, float *work, SCSL_INT_T *isys);

SCSL_INT_T
scfftm_(SCSL_INT_T *isign,
	SCSL_INT_T *n, SCSL_INT_T *n_fft, float *scale,
	float *input, SCSL_INT_T *l_col_i,
	SCSL_COMPLEX_T *output, SCSL_INT_T *l_col_o,
	float *table, float *work, SCSL_INT_T *isys);

SCSL_INT_T
scfftmr(SCSL_INT_T isign,
	SCSL_INT_T n, SCSL_INT_T n_fft, float scale,
        float *input, SCSL_INT_T l_col_i,
        SCSL_COMPLEX_T *output, SCSL_INT_T l_col_o,
        float *table, float *work, SCSL_INT_T *isys);

SCSL_INT_T
scfftmr_(SCSL_INT_T *isign,
	 SCSL_INT_T *n, SCSL_INT_T *n_fft, float *scale,
	 float *input, SCSL_INT_T *l_col_i,
	 SCSL_COMPLEX_T *output, SCSL_INT_T *l_col_o,
	 float *table, float *work, SCSL_INT_T *isys);


/* Complex-to-Real 1D FFT's */
SCSL_INT_T
csfft(SCSL_INT_T isign, SCSL_INT_T n, float scale, 
      SCSL_COMPLEX_T *input, float *output,
      float *table, float *work, SCSL_INT_T *isys);

SCSL_INT_T
csfft_(SCSL_INT_T *isign, SCSL_INT_T *n, float *scale, 
       SCSL_COMPLEX_T *input, float *output,
       float *table, float *work, SCSL_INT_T *isys);


/* Complex-to-Real 2D FFT's */
SCSL_INT_T
csfft2d(SCSL_INT_T isign,
	SCSL_INT_T nx, SCSL_INT_T ny, float scale,
	SCSL_COMPLEX_T *input, SCSL_INT_T l_col_i,
	float *output, SCSL_INT_T l_col_o,
	float *table, float *work, SCSL_INT_T *isys);

SCSL_INT_T
csfft2d_(SCSL_INT_T *isign,
	 SCSL_INT_T *nx, SCSL_INT_T *ny, float *scale,
	 SCSL_COMPLEX_T *input, SCSL_INT_T *l_col_i,
	 float *output, SCSL_INT_T *l_col_o,
	 float *table, float *work, SCSL_INT_T *isys);


/* Complex-to-Real 3D FFT's */
SCSL_INT_T
csfft3d(SCSL_INT_T isign,
	SCSL_INT_T nx, SCSL_INT_T ny, SCSL_INT_T nz, float scale,
	SCSL_COMPLEX_T *input, SCSL_INT_T l_x_i, SCSL_INT_T l_y_i,
	float *output, SCSL_INT_T l_x_o, SCSL_INT_T l_y_o,
	float *table, float *work, SCSL_INT_T *isys);

SCSL_INT_T
csfft3d_(SCSL_INT_T *isign,
	 SCSL_INT_T *nx, SCSL_INT_T *ny, SCSL_INT_T *nz,
	 float *scale,
	 SCSL_COMPLEX_T *input, SCSL_INT_T *l_x_i, SCSL_INT_T *l_y_i,
	 float *output, SCSL_INT_T *l_x_o, SCSL_INT_T *l_y_o,
	 float *table, float *work, SCSL_INT_T *isys);


/* Complex-to-Real Multiple 1D FFT's */
SCSL_INT_T
csfftm(SCSL_INT_T isign,
       SCSL_INT_T n, SCSL_INT_T n_fft, float scale,
       SCSL_COMPLEX_T *input, SCSL_INT_T l_col_i,
       float *output, SCSL_INT_T l_col_o,
       float *table, float *work, SCSL_INT_T *isys);

SCSL_INT_T
csfftm_(SCSL_INT_T *isign,
	SCSL_INT_T *n, SCSL_INT_T *n_fft, float *scale,
	SCSL_COMPLEX_T *input, SCSL_INT_T *l_col_i,
	float *output, SCSL_INT_T *l_col_o,
	float *table, float *work, SCSL_INT_T *isys);


SCSL_INT_T
csfftmr(SCSL_INT_T isign,
	SCSL_INT_T n, SCSL_INT_T n_fft, float scale,
        SCSL_COMPLEX_T *input, SCSL_INT_T l_col_i,
        float *output, SCSL_INT_T l_col_o,
        float *table, float *work, SCSL_INT_T *isys);

SCSL_INT_T
csfftmr_(SCSL_INT_T *isign,
	 SCSL_INT_T *n, SCSL_INT_T *n_fft, float *scale,
	 SCSL_COMPLEX_T *input, SCSL_INT_T *l_col_i,
	 float *output, SCSL_INT_T *l_col_o,
	 float *table, float *work, SCSL_INT_T *isys);


/* Complex 1D Convolution */
void
cfir1d( SCSL_COMPLEX_T *x, SCSL_INT_T incx,
	SCSL_INT_T ix0, SCSL_INT_T nx,
        SCSL_COMPLEX_T *h, SCSL_INT_T inch,
	SCSL_INT_T ih0, SCSL_INT_T nh,
        SCSL_COMPLEX_T *y, SCSL_INT_T incy,
	SCSL_INT_T iy0, SCSL_INT_T ny,
        SCSL_COMPLEX_T *alpha, SCSL_COMPLEX_T *beta );

void
ciir1d( SCSL_COMPLEX_T *x, SCSL_INT_T incx,
	SCSL_INT_T ix0, SCSL_INT_T nx,
        SCSL_COMPLEX_T *h, SCSL_INT_T inch,
	SCSL_INT_T ih0, SCSL_INT_T nh,
        SCSL_COMPLEX_T *y, SCSL_INT_T incy,
	SCSL_INT_T iy0, SCSL_INT_T ny );

/* Complex Multiple 1D Convolutions */
void
cfirm1d( SCSL_COMPLEX_T *x, SCSL_INT_T incx,
	 SCSL_INT_T ldx, SCSL_INT_T ix0,
	 SCSL_INT_T nx, SCSL_INT_T n_seq,
         SCSL_COMPLEX_T *h, SCSL_INT_T inch,
	 SCSL_INT_T ih0, SCSL_INT_T nh,
         SCSL_COMPLEX_T *y, SCSL_INT_T incy,
	 SCSL_INT_T ldy, SCSL_INT_T iy0, SCSL_INT_T ny,
         SCSL_COMPLEX_T *alpha, SCSL_COMPLEX_T *beta );

void
ciirm1d( SCSL_COMPLEX_T *x, SCSL_INT_T incx,
	 SCSL_INT_T ldx, SCSL_INT_T ix0,
	 SCSL_INT_T nx, SCSL_INT_T n_seq,
         SCSL_COMPLEX_T *h, SCSL_INT_T inch,
	 SCSL_INT_T ih0, SCSL_INT_T nh,
         SCSL_COMPLEX_T *y, SCSL_INT_T incy,
	 SCSL_INT_T ldy, SCSL_INT_T iy0, SCSL_INT_T ny );


/* Complex 2D Convolutions */
void
cfir2d( SCSL_COMPLEX_T *x, SCSL_INT_T incx, SCSL_INT_T ldx,
	SCSL_INT_T i1x0, SCSL_INT_T nx1, SCSL_INT_T i2x0, SCSL_INT_T nx2,
        SCSL_COMPLEX_T *h, SCSL_INT_T inch, SCSL_INT_T ldh,
	SCSL_INT_T i1h0, SCSL_INT_T nh1, SCSL_INT_T i2h0, SCSL_INT_T nh2,
        SCSL_COMPLEX_T *y, SCSL_INT_T incy, SCSL_INT_T ldy,
	SCSL_INT_T i1y0, SCSL_INT_T ny1, SCSL_INT_T i2y0, SCSL_INT_T ny2,
        SCSL_COMPLEX_T *alpha, SCSL_COMPLEX_T *beta );

void
ciir2d( SCSL_COMPLEX_T *x, SCSL_INT_T incx, SCSL_INT_T ldx,
	SCSL_INT_T i1x0, SCSL_INT_T nx1, SCSL_INT_T i2x0, SCSL_INT_T nx2,
        SCSL_COMPLEX_T *h, SCSL_INT_T inch, SCSL_INT_T ldh,
	SCSL_INT_T i1h0, SCSL_INT_T nh1, SCSL_INT_T i2h0, SCSL_INT_T nh2,
        SCSL_COMPLEX_T *y, SCSL_INT_T incy, SCSL_INT_T ldy,
	SCSL_INT_T i1y0, SCSL_INT_T ny1, SCSL_INT_T i2y0, SCSL_INT_T ny2 );


/* Complex 1D Correlation */
void
ccor1d( SCSL_COMPLEX_T *x, SCSL_INT_T incx, SCSL_INT_T ix0, SCSL_INT_T nx,
        SCSL_COMPLEX_T *h, SCSL_INT_T inch, SCSL_INT_T ih0, SCSL_INT_T nh,
        SCSL_COMPLEX_T *y, SCSL_INT_T incy, SCSL_INT_T iy0, SCSL_INT_T ny );


/* Complex Multiple 1D Correlations */
void
ccorm1d( SCSL_COMPLEX_T *x, SCSL_INT_T incx, SCSL_INT_T ldx,
	 SCSL_INT_T ix0, SCSL_INT_T nx, SCSL_INT_T n_seq,
         SCSL_COMPLEX_T *h, SCSL_INT_T inch,
	 SCSL_INT_T ih0, SCSL_INT_T nh,
         SCSL_COMPLEX_T *y, SCSL_INT_T incy, SCSL_INT_T ldy,
	 SCSL_INT_T iy0, SCSL_INT_T ny );


/* Complex 2D Correlation */
void
ccor2d( SCSL_COMPLEX_T *x, SCSL_INT_T incx, SCSL_INT_T ldx,
	SCSL_INT_T i1x0, SCSL_INT_T nx1, SCSL_INT_T i2x0, SCSL_INT_T nx2,
        SCSL_COMPLEX_T *h, SCSL_INT_T inch, SCSL_INT_T ldh,
	SCSL_INT_T i1h0, SCSL_INT_T nh1, SCSL_INT_T i2h0, SCSL_INT_T nh2,
        SCSL_COMPLEX_T *y, SCSL_INT_T incy, SCSL_INT_T ldy,
	SCSL_INT_T i1y0, SCSL_INT_T ny1, SCSL_INT_T i2y0, SCSL_INT_T ny2 );


/* Real 1D Convolution */
void
sfir1d( float *x, SCSL_INT_T incx, SCSL_INT_T ix0, SCSL_INT_T nx,
        float *h, SCSL_INT_T inch, SCSL_INT_T ih0, SCSL_INT_T nh,
        float *y, SCSL_INT_T incy, SCSL_INT_T iy0, SCSL_INT_T ny,
        float alpha, float beta );

void
siir1d( float *x, SCSL_INT_T incx, SCSL_INT_T ix0, SCSL_INT_T nx,
        float *h, SCSL_INT_T inch, SCSL_INT_T ih0, SCSL_INT_T nh,
        float *y, SCSL_INT_T incy, SCSL_INT_T iy0, SCSL_INT_T ny );

/* Real Multiple 1D Convolutions */
void
sfirm1d( float *x, SCSL_INT_T incx, SCSL_INT_T ldx, SCSL_INT_T ix0,
	 SCSL_INT_T nx, SCSL_INT_T n_seq,
         float *h, SCSL_INT_T inch, SCSL_INT_T ih0, SCSL_INT_T nh,
         float *y, SCSL_INT_T incy, SCSL_INT_T ldy, SCSL_INT_T iy0,
	 SCSL_INT_T ny,  float alpha, float beta );

void
siirm1d( float *x, SCSL_INT_T incx, SCSL_INT_T ldx, SCSL_INT_T ix0,
	 SCSL_INT_T nx, SCSL_INT_T n_seq,
         float *h, SCSL_INT_T inch,          SCSL_INT_T ih0, SCSL_INT_T nh,
         float *y, SCSL_INT_T incy, SCSL_INT_T ldy, SCSL_INT_T iy0, SCSL_INT_T ny );


/* Real 2D Convolutions */
void
sfir2d( float *x, SCSL_INT_T incx, SCSL_INT_T ldx, SCSL_INT_T i1x0, SCSL_INT_T nx1, SCSL_INT_T i2x0, SCSL_INT_T nx2,
        float *h, SCSL_INT_T inch, SCSL_INT_T ldh, SCSL_INT_T i1h0, SCSL_INT_T nh1, SCSL_INT_T i2h0, SCSL_INT_T nh2,
        float *y, SCSL_INT_T incy, SCSL_INT_T ldy, SCSL_INT_T i1y0, SCSL_INT_T ny1, SCSL_INT_T i2y0, SCSL_INT_T ny2,
        float alpha, float beta );

void
siir2d( float *x, SCSL_INT_T incx, SCSL_INT_T ldx, SCSL_INT_T i1x0, SCSL_INT_T nx1, SCSL_INT_T i2x0, SCSL_INT_T nx2,
        float *h, SCSL_INT_T inch, SCSL_INT_T ldh, SCSL_INT_T i1h0, SCSL_INT_T nh1, SCSL_INT_T i2h0, SCSL_INT_T nh2,
        float *y, SCSL_INT_T incy, SCSL_INT_T ldy, SCSL_INT_T i1y0, SCSL_INT_T ny1, SCSL_INT_T i2y0, SCSL_INT_T ny2 );


/* Real 1D Correlation */
void
scor1d( float *x, SCSL_INT_T incx, SCSL_INT_T ix0, SCSL_INT_T nx,
        float *h, SCSL_INT_T inch, SCSL_INT_T ih0, SCSL_INT_T nh,
        float *y, SCSL_INT_T incy, SCSL_INT_T iy0, SCSL_INT_T ny );


/* Real Multiple 1D Correlations */
void
scorm1d( float *x, SCSL_INT_T incx, SCSL_INT_T ldx, SCSL_INT_T ix0, SCSL_INT_T nx, SCSL_INT_T n_seq,
         float *h, SCSL_INT_T inch,          SCSL_INT_T ih0, SCSL_INT_T nh,
         float *y, SCSL_INT_T incy, SCSL_INT_T ldy, SCSL_INT_T iy0, SCSL_INT_T ny );


/* Real 2D Correlation */
void
scor2d( float *x, SCSL_INT_T incx, SCSL_INT_T ldx, SCSL_INT_T i1x0, SCSL_INT_T nx1, SCSL_INT_T i2x0, SCSL_INT_T nx2,
        float *h, SCSL_INT_T inch, SCSL_INT_T ldh, SCSL_INT_T i1h0, SCSL_INT_T nh1, SCSL_INT_T i2h0, SCSL_INT_T nh2,
        float *y, SCSL_INT_T incy, SCSL_INT_T ldy, SCSL_INT_T i1y0, SCSL_INT_T ny1, SCSL_INT_T i2y0, SCSL_INT_T ny2 );



/* ******************************************************************** */
/* ************************* Double Precision ************************* */
/* ******************************************************************** */


/* Zomplex-to-Zomplex 1D FFT's */
SCSL_INT_T
zzfft(SCSL_INT_T isign, SCSL_INT_T n, double scale,
      SCSL_ZOMPLEX_T *input, SCSL_ZOMPLEX_T *output,
      double *table, double *work, SCSL_INT_T *isys);

SCSL_INT_T
zzfft_(SCSL_INT_T *isign, SCSL_INT_T *n, double *scale,
       SCSL_ZOMPLEX_T *input, SCSL_ZOMPLEX_T *output,
       double *table, double *work, SCSL_INT_T *isys);


/* Zomplex-to-Zomplex 2D FFT's */
SCSL_INT_T
zzfft2d(SCSL_INT_T isign, SCSL_INT_T nx, SCSL_INT_T ny, double scale,
	SCSL_ZOMPLEX_T *input, SCSL_INT_T l_col_i,
	SCSL_ZOMPLEX_T *output, SCSL_INT_T l_col_o,
	double *table, double *work, SCSL_INT_T *isys);

SCSL_INT_T
zzfft2d_(SCSL_INT_T *isign, SCSL_INT_T *nx, SCSL_INT_T *ny, double *scale,
	 SCSL_ZOMPLEX_T *input, SCSL_INT_T *l_col_i,
	 SCSL_ZOMPLEX_T *output, SCSL_INT_T *l_col_o,
	 double *table, double *work, SCSL_INT_T *isys);


/* Zomplex-to-Zomplex 3D FFT's */
SCSL_INT_T
zzfft3d(SCSL_INT_T isign,
	SCSL_INT_T nx, SCSL_INT_T ny, SCSL_INT_T nz, double scale,
	SCSL_ZOMPLEX_T *input, SCSL_INT_T l_x_i, SCSL_INT_T l_y_i,
	SCSL_ZOMPLEX_T *output, SCSL_INT_T l_x_o, SCSL_INT_T l_y_o,
	double *table, double *work, SCSL_INT_T *isys);

SCSL_INT_T
zzfft3d_(SCSL_INT_T *isign,
	 SCSL_INT_T *nx, SCSL_INT_T *ny, SCSL_INT_T *nz, double *scale,
	 SCSL_ZOMPLEX_T *input, SCSL_INT_T *l_x_i, SCSL_INT_T *l_y_i,
	 SCSL_ZOMPLEX_T *output, SCSL_INT_T *l_x_o, SCSL_INT_T *l_y_o,
	 double *table, double *work, SCSL_INT_T *isys);


/* Zomplex-to-Zomplex Multiple 1D FFT's */
SCSL_INT_T
zzfftm(SCSL_INT_T isign, SCSL_INT_T n, SCSL_INT_T n_fft, double scale,
       SCSL_ZOMPLEX_T *input, SCSL_INT_T l_col_i,
       SCSL_ZOMPLEX_T *output, SCSL_INT_T l_col_o,
       double *table, double *work, SCSL_INT_T *isys);

SCSL_INT_T
zzfftm_(SCSL_INT_T *isign, SCSL_INT_T *n, SCSL_INT_T *n_fft, double *scale,
	SCSL_ZOMPLEX_T *input, SCSL_INT_T *l_col_i,
	SCSL_ZOMPLEX_T *output, SCSL_INT_T *l_col_o,
	double *table, double *work, SCSL_INT_T *isys);

SCSL_INT_T
zzfftmr(SCSL_INT_T isign, SCSL_INT_T n, SCSL_INT_T n_fft, double scale,
        SCSL_ZOMPLEX_T *input, SCSL_INT_T l_col_i,
        SCSL_ZOMPLEX_T *output, SCSL_INT_T l_col_o,
        double *table, double *work, SCSL_INT_T *isys);

SCSL_INT_T
zzfftmr_(SCSL_INT_T *isign, SCSL_INT_T *n, SCSL_INT_T *n_fft, double *scale,
	 SCSL_ZOMPLEX_T *input, SCSL_INT_T *l_col_i,
	 SCSL_ZOMPLEX_T *output, SCSL_INT_T *l_col_o,
	 double *table, double *work, SCSL_INT_T *isys);


/* Double-to-Zomplex 1D FFT's */
SCSL_INT_T
dzfft(SCSL_INT_T isign, SCSL_INT_T n, double scale, 
      double *input, SCSL_ZOMPLEX_T *output,
      double *table, double *work, SCSL_INT_T *isys);

SCSL_INT_T
dzfft_(SCSL_INT_T *isign, SCSL_INT_T *n, double *scale, 
       double *input, SCSL_ZOMPLEX_T *output,
       double *table, double *work, SCSL_INT_T *isys);


/* Double-to-Zomplex 2D FFT's */
SCSL_INT_T
dzfft2d(SCSL_INT_T isign, SCSL_INT_T nx, SCSL_INT_T ny, double scale,
	double *input, SCSL_INT_T l_col_i,
	SCSL_ZOMPLEX_T *output, SCSL_INT_T l_col_o,
	double *table, double *work, SCSL_INT_T *isys);

SCSL_INT_T
dzfft2d_(SCSL_INT_T *isign, SCSL_INT_T *nx, SCSL_INT_T *ny, double *scale,
	 double *input, SCSL_INT_T *l_col_i,
	 SCSL_ZOMPLEX_T *output, SCSL_INT_T *l_col_o,
	 double *table, double *work, SCSL_INT_T *isys);


/* Double-to-Zomplex 3D FFT's */
SCSL_INT_T
dzfft3d(SCSL_INT_T isign,
	SCSL_INT_T nx, SCSL_INT_T ny, SCSL_INT_T nz, double scale,
	double *input, SCSL_INT_T l_x_i, SCSL_INT_T l_y_i,
	SCSL_ZOMPLEX_T *output, SCSL_INT_T l_x_o, SCSL_INT_T l_y_o,
	double *table, double *work, SCSL_INT_T *isys);

SCSL_INT_T
dzfft3d_(SCSL_INT_T *isign,
	 SCSL_INT_T *nx, SCSL_INT_T *ny, SCSL_INT_T *nz, double *scale,
	 double *input, SCSL_INT_T *l_x_i, SCSL_INT_T *l_y_i,
	 SCSL_ZOMPLEX_T *output, SCSL_INT_T *l_x_o, SCSL_INT_T *l_y_o,
	 double *table, double *work, SCSL_INT_T *isys);


/* Double-to-Zomplex Multiple 1D FFT's */
SCSL_INT_T 
dzfftm(SCSL_INT_T isign, SCSL_INT_T n, SCSL_INT_T n_fft, double scale,
       double *input, SCSL_INT_T l_col_i,
       SCSL_ZOMPLEX_T *output, SCSL_INT_T l_col_o,
       double *table, double *work, SCSL_INT_T *isys);

SCSL_INT_T 
dzfftm_(SCSL_INT_T *isign,
	SCSL_INT_T *n, SCSL_INT_T *n_fft, double *scale,
	double *input, SCSL_INT_T *l_col_i,
	SCSL_ZOMPLEX_T *output, SCSL_INT_T *l_col_o,
	double *table, double *work, SCSL_INT_T *isys);


SCSL_INT_T 
dzfftmr(SCSL_INT_T isign, SCSL_INT_T n, SCSL_INT_T n_fft, double scale,
        double *input, SCSL_INT_T l_col_i,
        SCSL_ZOMPLEX_T *output, SCSL_INT_T l_col_o,
        double *table, double *work, SCSL_INT_T *isys);

SCSL_INT_T 
dzfftmr_(SCSL_INT_T *isign, SCSL_INT_T *n, SCSL_INT_T *n_fft, double *scale,
	 double *input, SCSL_INT_T *l_col_i,
	 SCSL_ZOMPLEX_T *output, SCSL_INT_T *l_col_o,
	 double *table, double *work, SCSL_INT_T *isys);


/* Zomplex-to-Double 1D FFT's */
SCSL_INT_T
zdfft(SCSL_INT_T isign, SCSL_INT_T n, double scale, 
      SCSL_ZOMPLEX_T *input, double *output,
      double *table, double *work, SCSL_INT_T *isys);

SCSL_INT_T
zdfft_(SCSL_INT_T *isign, SCSL_INT_T *n, double *scale, 
       SCSL_ZOMPLEX_T *input, double *output,
       double *table, double *work, SCSL_INT_T *isys);


/* Zomplex-to-Double 2D FFT's */
SCSL_INT_T
zdfft2d(SCSL_INT_T isign, SCSL_INT_T nx, SCSL_INT_T ny, double scale,
	SCSL_ZOMPLEX_T *input, SCSL_INT_T l_col_i,
	double *output, SCSL_INT_T l_col_o,
	double *table, double *work, SCSL_INT_T *isys);

SCSL_INT_T
zdfft2d_(SCSL_INT_T *isign, SCSL_INT_T *nx, SCSL_INT_T *ny, double *scale,
	 SCSL_ZOMPLEX_T *input, SCSL_INT_T *l_col_i,
	 double *output, SCSL_INT_T *l_col_o,
	 double *table, double *work, SCSL_INT_T *isys);


/* Zomplex-to-Double 3D FFT's */
SCSL_INT_T
zdfft3d(SCSL_INT_T isign,
	SCSL_INT_T nx, SCSL_INT_T ny, SCSL_INT_T nz, double scale,
	SCSL_ZOMPLEX_T *input, SCSL_INT_T l_x_i, SCSL_INT_T l_y_i,
	double *output, SCSL_INT_T l_x_o, SCSL_INT_T l_y_o,
	double *table, double *work, SCSL_INT_T *isys);

SCSL_INT_T
zdfft3d_(SCSL_INT_T *isign,
	 SCSL_INT_T *nx, SCSL_INT_T *ny, SCSL_INT_T *nz, double *scale,
	 SCSL_ZOMPLEX_T *input, SCSL_INT_T *l_x_i, SCSL_INT_T *l_y_i,
	 double *output, SCSL_INT_T *l_x_o, SCSL_INT_T *l_y_o,
	 double *table, double *work, SCSL_INT_T *isys);


/* Zomplex-to-Double Multiple 1D FFT's */
SCSL_INT_T
zdfftm(SCSL_INT_T isign, SCSL_INT_T n, SCSL_INT_T n_fft, double scale,
       SCSL_ZOMPLEX_T *input, SCSL_INT_T l_col_i,
       double *output, SCSL_INT_T l_col_o,
       double *table, double *work, SCSL_INT_T *isys);

SCSL_INT_T
zdfftm_(SCSL_INT_T *isign, SCSL_INT_T *n, SCSL_INT_T *n_fft, double *scale,
	SCSL_ZOMPLEX_T *input, SCSL_INT_T *l_col_i,
	double *output, SCSL_INT_T *l_col_o,
	double *table, double *work, SCSL_INT_T *isys);


SCSL_INT_T
zdfftmr(SCSL_INT_T isign, SCSL_INT_T n, SCSL_INT_T n_fft, double scale,
        SCSL_ZOMPLEX_T *input, SCSL_INT_T l_col_i,
        double *output, SCSL_INT_T l_col_o,
        double *table, double *work, SCSL_INT_T *isys);

SCSL_INT_T
zdfftmr_(SCSL_INT_T *isign, SCSL_INT_T *n, SCSL_INT_T *n_fft, double *scale,
	 SCSL_ZOMPLEX_T *input, SCSL_INT_T *l_col_i,
	 double *output, SCSL_INT_T *l_col_o,
	 double *table, double *work, SCSL_INT_T *isys);



/* Zomplex 1D Convolution */
void
zfir1d( SCSL_ZOMPLEX_T *x, SCSL_INT_T incx, SCSL_INT_T ix0, SCSL_INT_T nx,
        SCSL_ZOMPLEX_T *h, SCSL_INT_T inch, SCSL_INT_T ih0, SCSL_INT_T nh,
        SCSL_ZOMPLEX_T *y, SCSL_INT_T incy, SCSL_INT_T iy0, SCSL_INT_T ny,
        SCSL_ZOMPLEX_T *alpha, SCSL_ZOMPLEX_T *beta );

void
ziir1d( SCSL_ZOMPLEX_T *x, SCSL_INT_T incx, SCSL_INT_T ix0, SCSL_INT_T nx,
        SCSL_ZOMPLEX_T *h, SCSL_INT_T inch, SCSL_INT_T ih0, SCSL_INT_T nh,
        SCSL_ZOMPLEX_T *y, SCSL_INT_T incy, SCSL_INT_T iy0, SCSL_INT_T ny );

/* Zomplex Multiple 1D Convolutions */
void
zfirm1d( SCSL_ZOMPLEX_T *x, SCSL_INT_T incx, SCSL_INT_T ldx,
	 SCSL_INT_T ix0, SCSL_INT_T nx, SCSL_INT_T n_seq,
         SCSL_ZOMPLEX_T *h, SCSL_INT_T inch, SCSL_INT_T ih0, SCSL_INT_T nh,
         SCSL_ZOMPLEX_T *y, SCSL_INT_T incy, SCSL_INT_T ldy,
	 SCSL_INT_T iy0, SCSL_INT_T ny,
         SCSL_ZOMPLEX_T *alpha, SCSL_ZOMPLEX_T *beta );

void
ziirm1d( SCSL_ZOMPLEX_T *x, SCSL_INT_T incx, SCSL_INT_T ldx,
	 SCSL_INT_T ix0, SCSL_INT_T nx, SCSL_INT_T n_seq,
         SCSL_ZOMPLEX_T *h, SCSL_INT_T inch, SCSL_INT_T ih0, SCSL_INT_T nh,
         SCSL_ZOMPLEX_T *y, SCSL_INT_T incy, SCSL_INT_T ldy,
	 SCSL_INT_T iy0, SCSL_INT_T ny );


/* Zomplex 2D Convolutions */
void
zfir2d( SCSL_ZOMPLEX_T *x, SCSL_INT_T incx, SCSL_INT_T ldx,
	SCSL_INT_T i1x0, SCSL_INT_T nx1, SCSL_INT_T i2x0, SCSL_INT_T nx2,
        SCSL_ZOMPLEX_T *h, SCSL_INT_T inch, SCSL_INT_T ldh,
	SCSL_INT_T i1h0, SCSL_INT_T nh1, SCSL_INT_T i2h0, SCSL_INT_T nh2,
        SCSL_ZOMPLEX_T *y, SCSL_INT_T incy, SCSL_INT_T ldy,
	SCSL_INT_T i1y0, SCSL_INT_T ny1, SCSL_INT_T i2y0, SCSL_INT_T ny2,
        SCSL_ZOMPLEX_T *alpha, SCSL_ZOMPLEX_T *beta );

void
ziir2d( SCSL_ZOMPLEX_T *x, SCSL_INT_T incx, SCSL_INT_T ldx,
	SCSL_INT_T i1x0, SCSL_INT_T nx1, SCSL_INT_T i2x0, SCSL_INT_T nx2,
        SCSL_ZOMPLEX_T *h, SCSL_INT_T inch, SCSL_INT_T ldh,
	SCSL_INT_T i1h0, SCSL_INT_T nh1, SCSL_INT_T i2h0, SCSL_INT_T nh2,
        SCSL_ZOMPLEX_T *y, SCSL_INT_T incy, SCSL_INT_T ldy,
	SCSL_INT_T i1y0, SCSL_INT_T ny1, SCSL_INT_T i2y0, SCSL_INT_T ny2 );


/* Zomplex 1D Correlation */
void
zcor1d( SCSL_ZOMPLEX_T *x, SCSL_INT_T incx, SCSL_INT_T ix0, SCSL_INT_T nx,
        SCSL_ZOMPLEX_T *h, SCSL_INT_T inch, SCSL_INT_T ih0, SCSL_INT_T nh,
        SCSL_ZOMPLEX_T *y, SCSL_INT_T incy, SCSL_INT_T iy0, SCSL_INT_T ny );


/* Zomplex Multiple 1D Correlations */
void
zcorm1d( SCSL_ZOMPLEX_T *x, SCSL_INT_T incx, SCSL_INT_T ldx,
	 SCSL_INT_T ix0, SCSL_INT_T nx, SCSL_INT_T n_seq,
         SCSL_ZOMPLEX_T *h, SCSL_INT_T inch, SCSL_INT_T ih0, SCSL_INT_T nh,
         SCSL_ZOMPLEX_T *y, SCSL_INT_T incy, SCSL_INT_T ldy,
	 SCSL_INT_T iy0, SCSL_INT_T ny );


/* Zomplex 2D Correlation */
void
zcor2d( SCSL_ZOMPLEX_T *x, SCSL_INT_T incx, SCSL_INT_T ldx,
	SCSL_INT_T i1x0, SCSL_INT_T nx1, SCSL_INT_T i2x0, SCSL_INT_T nx2,
        SCSL_ZOMPLEX_T *h, SCSL_INT_T inch, SCSL_INT_T ldh,
	SCSL_INT_T i1h0, SCSL_INT_T nh1, SCSL_INT_T i2h0, SCSL_INT_T nh2,
        SCSL_ZOMPLEX_T *y, SCSL_INT_T incy, SCSL_INT_T ldy,
	SCSL_INT_T i1y0, SCSL_INT_T ny1, SCSL_INT_T i2y0, SCSL_INT_T ny2 );


/* Double 1D Convolution */
void
dfir1d( double *x, SCSL_INT_T incx, SCSL_INT_T ix0, SCSL_INT_T nx,
        double *h, SCSL_INT_T inch, SCSL_INT_T ih0, SCSL_INT_T nh,
        double *y, SCSL_INT_T incy, SCSL_INT_T iy0, SCSL_INT_T ny,
        double alpha, double beta );

void
diir1d( double *x, SCSL_INT_T incx, SCSL_INT_T ix0, SCSL_INT_T nx,
        double *h, SCSL_INT_T inch, SCSL_INT_T ih0, SCSL_INT_T nh,
        double *y, SCSL_INT_T incy, SCSL_INT_T iy0, SCSL_INT_T ny );

/* Double Multiple 1D Convolutions */
void
dfirm1d( double *x, SCSL_INT_T incx, SCSL_INT_T ldx,
	 SCSL_INT_T ix0, SCSL_INT_T nx, SCSL_INT_T n_seq,
         double *h, SCSL_INT_T inch, SCSL_INT_T ih0, SCSL_INT_T nh,
         double *y, SCSL_INT_T incy, SCSL_INT_T ldy,
	 SCSL_INT_T iy0, SCSL_INT_T ny,
         double alpha, double beta );

void
diirm1d( double *x, SCSL_INT_T incx, SCSL_INT_T ldx,
	 SCSL_INT_T ix0, SCSL_INT_T nx, SCSL_INT_T n_seq,
         double *h, SCSL_INT_T inch, SCSL_INT_T ih0, SCSL_INT_T nh,
         double *y, SCSL_INT_T incy, SCSL_INT_T ldy,
	 SCSL_INT_T iy0, SCSL_INT_T ny );


/* Double 2D Convolutions */
void
dfir2d( double *x, SCSL_INT_T incx, SCSL_INT_T ldx, SCSL_INT_T i1x0,
	SCSL_INT_T nx1, SCSL_INT_T i2x0, SCSL_INT_T nx2,
        double *h, SCSL_INT_T inch, SCSL_INT_T ldh, SCSL_INT_T i1h0,
	SCSL_INT_T nh1, SCSL_INT_T i2h0, SCSL_INT_T nh2,
        double *y, SCSL_INT_T incy, SCSL_INT_T ldy, SCSL_INT_T i1y0,
	SCSL_INT_T ny1, SCSL_INT_T i2y0, SCSL_INT_T ny2,
        double alpha, double beta );

void
diir2d( double *x, SCSL_INT_T incx, SCSL_INT_T ldx, SCSL_INT_T i1x0,
	SCSL_INT_T nx1, SCSL_INT_T i2x0, SCSL_INT_T nx2,
        double *h, SCSL_INT_T inch, SCSL_INT_T ldh, SCSL_INT_T i1h0,
	SCSL_INT_T nh1, SCSL_INT_T i2h0, SCSL_INT_T nh2,
        double *y, SCSL_INT_T incy, SCSL_INT_T ldy, SCSL_INT_T i1y0,
	SCSL_INT_T ny1, SCSL_INT_T i2y0, SCSL_INT_T ny2 );


/* Double 1D Correlation */
void
dcor1d( double *x, SCSL_INT_T incx, SCSL_INT_T ix0, SCSL_INT_T nx,
        double *h, SCSL_INT_T inch, SCSL_INT_T ih0, SCSL_INT_T nh,
        double *y, SCSL_INT_T incy, SCSL_INT_T iy0, SCSL_INT_T ny );


/* Double Multiple 1D Correlations */
void
dcorm1d( double *x, SCSL_INT_T incx, SCSL_INT_T ldx, SCSL_INT_T ix0,
	 SCSL_INT_T nx, SCSL_INT_T n_seq,
         double *h, SCSL_INT_T inch, SCSL_INT_T ih0, SCSL_INT_T nh,
         double *y, SCSL_INT_T incy, SCSL_INT_T ldy, SCSL_INT_T iy0,
	 SCSL_INT_T ny );


/* Double 2D Correlation */
void
dcor2d( double *x, SCSL_INT_T incx, SCSL_INT_T ldx, SCSL_INT_T i1x0,
	SCSL_INT_T nx1, SCSL_INT_T i2x0, SCSL_INT_T nx2,
        double *h, SCSL_INT_T inch, SCSL_INT_T ldh, SCSL_INT_T i1h0,
	SCSL_INT_T nh1, SCSL_INT_T i2h0, SCSL_INT_T nh2,
        double *y, SCSL_INT_T incy, SCSL_INT_T ldy, SCSL_INT_T i1y0,
	SCSL_INT_T ny1, SCSL_INT_T i2y0, SCSL_INT_T ny2 );


/* ******************************************************************** */
/* ********************** Memory release routines ********************* */
/* ******************************************************************** */
/* Complex-to-Complex */
SCSL_INT_T ccfftf(SCSL_INT_T n, float *table);
SCSL_INT_T ccfftf_(SCSL_INT_T *n, float *table);
SCSL_INT_T ccfftmf(SCSL_INT_T n, float *table);
SCSL_INT_T ccfftmf_(SCSL_INT_T *n, float *table);
SCSL_INT_T ccfftmrf(SCSL_INT_T n, float *table);
SCSL_INT_T ccfftmrf_(SCSL_INT_T *n, float *table);
SCSL_INT_T ccfft2df(SCSL_INT_T n1, SCSL_INT_T n2, float *table);
SCSL_INT_T ccfft2df_(SCSL_INT_T *n1, SCSL_INT_T *n2, float *table);
SCSL_INT_T ccfft3df(SCSL_INT_T n1, SCSL_INT_T n2,
		    SCSL_INT_T n3, float *table);
SCSL_INT_T ccfft3df_(SCSL_INT_T *n1, SCSL_INT_T *n2,
		     SCSL_INT_T *n3, float *table);

/* Real-to-Complex */
SCSL_INT_T scfftf(SCSL_INT_T n, float *table);
SCSL_INT_T scfftf_(SCSL_INT_T *n, float *table);
SCSL_INT_T scfftmf(SCSL_INT_T n, float *table);
SCSL_INT_T scfftmf_(SCSL_INT_T *n, float *table);
SCSL_INT_T scfftmrf(SCSL_INT_T n, float *table);
SCSL_INT_T scfftmrf_(SCSL_INT_T *n, float *table);
SCSL_INT_T scfft2df(SCSL_INT_T n1, SCSL_INT_T n2, float *table);
SCSL_INT_T scfft2df_(SCSL_INT_T *n1, SCSL_INT_T *n2, float *table);
SCSL_INT_T scfft3df(SCSL_INT_T n1, SCSL_INT_T n2,
		    SCSL_INT_T n3, float *table);
SCSL_INT_T scfft3df_(SCSL_INT_T *n1, SCSL_INT_T *n2,
		     SCSL_INT_T *n3, float *table);

/* Double Complex-to-Double Complex */
SCSL_INT_T zzfftf(SCSL_INT_T n, double *table);
SCSL_INT_T zzfftf_(SCSL_INT_T *n, double *table);
SCSL_INT_T zzfftmf(SCSL_INT_T n, double *table);
SCSL_INT_T zzfftmf_(SCSL_INT_T *n, double *table);
SCSL_INT_T zzfftmrf(SCSL_INT_T n, double *table);
SCSL_INT_T zzfftmrf_(SCSL_INT_T *n, double *table);
SCSL_INT_T zzfft2df(SCSL_INT_T n1, SCSL_INT_T n2, double *table);
SCSL_INT_T zzfft2df_(SCSL_INT_T *n1, SCSL_INT_T *n2, double *table);
SCSL_INT_T zzfft3df(SCSL_INT_T n1, SCSL_INT_T n2,
		    SCSL_INT_T n3, double *table);
SCSL_INT_T zzfft3df_(SCSL_INT_T *n1, SCSL_INT_T *n2,
		     SCSL_INT_T *n3, double *table);

/* Double-to-Double Complex */
SCSL_INT_T dzfftf(SCSL_INT_T n, double *table);
SCSL_INT_T dzfftf_(SCSL_INT_T *n, double *table);
SCSL_INT_T dzfftmf(SCSL_INT_T n, double *table);
SCSL_INT_T dzfftmf_(SCSL_INT_T *n, double *table);
SCSL_INT_T dzfftmrf(SCSL_INT_T n, double *table);
SCSL_INT_T dzfftmrf_(SCSL_INT_T *n, double *table);
SCSL_INT_T dzfft2df(SCSL_INT_T n1, SCSL_INT_T n2, double *table);
SCSL_INT_T dzfft2df_(SCSL_INT_T *n1, SCSL_INT_T *n2, double *table);
SCSL_INT_T dzfft3df(SCSL_INT_T n1, SCSL_INT_T n2, SCSL_INT_T n3, double *table);
SCSL_INT_T dzfft3df_(SCSL_INT_T *n1, SCSL_INT_T *n2, SCSL_INT_T *n3, double *table);


#undef SCSL_COMPLEX_T
#undef SCSL_ZOMPLEX_T
#undef SCSL_INT_T

#ifdef __cplusplus
}
#endif

#endif /* #ifdef _SGI_FFT */
