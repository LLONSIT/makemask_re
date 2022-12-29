
#ifndef _SGI_FFT_
#define	_SGI_FFT_

#ifdef __cplusplus
extern "C" {
#endif

#define	    FACTOR_SPACE    15
#define	    FAST_MALLOC_STRING	"FFT_FAST_MALLOC"

/* *******************************************************
    Complex structures definitions
******************************************************* */

typedef struct {
    float re;
    float im;
} complex;

typedef struct {
    double re;
    double im;
} zomplex;


/* *******************************************************
    C Functions prototypes
******************************************************* */
/* *******************************************************
	complex <---> complex FFTs
******************************************************* */
complex *cfft1di( int n, complex *save);
int cfft1d( int sign, int n, complex *array, int inc, complex *save);

complex *cfftm1di( int m, complex *save);
int cfftm1d( int sign, int m, int n, complex *array, int incI, int incJ, complex *save);

complex *cfft2di( int n1, int n2, complex *save);
int cfft2d( int sign, int n1, int n2, complex *array, int ld, complex *save);

complex *cfft3di( int n1, int n2, int n3, complex *save);
int cfft3d( int sign, int n1, int n2, int n3, complex *array, int ld1, int ld2, complex *save);

/* *******************************************************
	zomplex <---> zomplex FFTs
******************************************************* */
zomplex *zfft1di( int n, zomplex *save);
int zfft1d( int sign, int n, zomplex *array, int inc, zomplex *save);

zomplex *zfftm1di( int m, zomplex *save);
int zfftm1d( int sign, int m, int n, zomplex *array, int incI, int incJ, zomplex *save);

zomplex *zfft2di( int n1, int n2, zomplex *save);
int zfft2d( int sign, int n1, int n2, zomplex *array, int ld, zomplex *save);

zomplex *zfft3di( int n1, int n2, int n3, zomplex *save);
int zfft3d( int sign, int n1, int n2, int n3, zomplex *array, int ld1, int ld2, zomplex *save);

/************************************************************************
    Product modules ... 
	    Performs convolution in 1 Domain by Product in the other
********************************************************************** */

void cprod1d( int n, complex *y, int incy, complex *filter, int incx);
void zprod1d( int n, zomplex *y, int incy, zomplex *filter, int incx);
		
void cprodm1d( int n1, int n2, complex *y, int incy, int ldy, complex *filter, int incx, int ldx);
void zprodm1d( int n1, int n2, zomplex *y, int incy, int ldy, zomplex *filter, int incx, int ldx);

void cprod2d( int n1, int n2, complex *y, int ldy, complex *filter, int ldx);
void zprod2d( int n1, int n2, zomplex *y, int ldy, zomplex *filter, int ldx);

void cprod3d( int n1, int n2, int n3, complex *y, int ldy1, int ldy2, 
	    complex *filter, int ldx1, int ldx2);
void zprod3d( int n1, int n2, int n3, zomplex *y, int ldy1, int ldy2, 
	    zomplex *filter, int ldx1, int ldx2);

/************************************************************************
    Scaling modules ... 
	    Scale the sequence by value APLHA ... 
		to keep absolute values after Direct+Inverse transform.
********************************************************************** */

void cscal1d( int n, float alpha, complex *y, int inc);
void zscal1d( int n, double alpha, zomplex *y, int inc);

void cscalm1d( int m, int n, float alpha, complex *array, int incI, int incJ);
void zscalm1d( int m, int n, double alpha, zomplex *array, int incI, int incJ);

void cscal2d( int nx, int ny, float alpha, complex *y, int ld);
void zscal2d( int nx, int ny, double alpha, zomplex *y, int ld);

void cscal3d( int nx, int ny, int nz, float alpha, complex *y, int ld1,int ld2);
void zscal3d( int nx, int ny, int nz, double alpha, zomplex *y,int ld1,int ld2);


/* *******************************************************
    Fortran Subroutines prototypes
******************************************************* */
/* *******************************************************
	complex <---> complex FFTs
******************************************************* */
void cfft1di_( int *n, complex *save);
void cfft1d_( int *sign, int *n, complex *array, int *inc, complex *save);

complex *cfftm1di_( int *m, complex *save);
void cfftm1d_( int *sign, int *m, int *n, complex *array, int *incI, int *incJ, complex *save);

void cfft2di_( int *n1, int *n2, complex *save);
void cfft2d_( int *sign, int *n1, int *n2, complex *array, int *ld, complex *save);

void cfft3di_( int *n1, int *n2, int *n3, complex *save);
void cfft3d_( int *sign, int *n1, int *n2, int *n3, complex *array, int *ld1, int *ld2, complex *save);

/* ****************************
	zomplex <---> zomplex FFTs
**************************** */
void zfft1di_( int *n, zomplex *save);
void zfft1d_( int *sign, int *n, zomplex *array, int *inc, zomplex *save);

zomplex *zfftm1di_( int *m, zomplex *save);
void zfftm1d_( int *sign, int *m, int *n, zomplex *array, int *incI, int *incJ, zomplex *save);

void zfft2di_( int *n1, int *n2, zomplex *save);
void zfft2d_( int *sign, int *n1, int *n2, zomplex *array, int *ld, zomplex *save);

void zfft3di_( int *n1, int *n2, int *n3, zomplex *save);
void zfft3d_( int *sign, int *n1, int *n2, int *n3, zomplex *array, int *ld1, int *ld2, zomplex *save);

/************************************************************************
    Product modules ... 
	    Performs convolution in 1 Domain by Product in the other
********************************************************************** */

void cprod1d_( int *n, complex *y, int *incy, complex *filter, int *incx);
void zprod1d_( int *n, zomplex *y, int *incy, zomplex *filter, int *incx);
		
void cprodm1d_( int *n1, int *n2, complex *y, int *incy, int *ldy, complex *filter, int *incx, int *ldx);
void zprodm1d_( int *n1, int *n2, zomplex *y, int *incy, int *ldy, zomplex *filter, int *incx, int *ldx);

void cprod2d_( int *n1, int *n2, complex *y, int *ldy, complex *filter, int *ldx);
void zprod2d_( int *n1, int *n2, zomplex *y, int *ldy, zomplex *filter, int *ldx);

void cprod3d_( int *n1, int *n2, int *n3, complex *y, int *ldy1, int *ldy2, 
	    complex *filter, int *ldx1, int *ldx2);
void zprod3d_( int *n1, int *n2, int *n3, zomplex *y, int *ldy1, int *ldy2, 
	    zomplex *filter, int *ldx1, int *ldx2);

/************************************************************************
    Scaling modules ... 
	    Scale the sequence by value APLHA ... 
		to keep absolute values after Direct+Inverse transform.
********************************************************************** */

void cscal1d_( int *n, float *alpha, complex *y, int *inc);
void zscal1d_( int *n, double *alpha, zomplex *y, int *inc);

void cscalm1d_( int *m, int *n, float *alpha, complex *array, int *inc, int *lda);
void zscalm1d_( int *m, int *n, double *alpha, zomplex *array, int *inc, int *lda);

void cscal2d_( int *nx, int *ny, float *alpha, complex *y, int *ld);
void zscal2d_( int *nx, int *ny, double *alpha, zomplex *y, int *ld);

void cscal3d_( int *nx, int *ny, int *nz, float *alpha, complex *y, int *ld1,int *ld2);
void zscal3d_( int *nx, int *ny, int *nz, double *alpha, zomplex *y,int *ld1,int *ld2);








/* *******************************************************
	C  real <---> complex FFTs
******************************************************* */
float *sfft1di( int n, float *save);
float *sfft1dui( int n, float *save);
int sfft1d( int sign, int n, float *array, int inc, float *save);
int sfft1du( int sign, int n, float *array, int inc, float *save);

float *sfftm1di( int m, float *save);
int sfftm1d( int sign, int m, int n, float *array, int incI, int incJ, float *save);
float *sfftm1dui( int m, float *save);
int sfftm1du( int sign, int m, int n, float *array, int incI, int incJ, float *save);

float *sfft2di( int n1, int n2, float *save);
float *sfft2dui( int n1, int n2, float *save);
int sfft2d( int sign, int n1, int n2, float *array, int ld, float *save);
int sfft2du( int sign, int n1, int n2, float *array, int ld, float *save);

float *sfft3di( int n1, int n2, int n3, float *save);
float *sfft3dui( int n1, int n2, int n3, float *save);
int sfft3d( int sign, int n1, int n2, int n3, float *array, int ld1, int ld2, float *save);
int sfft3du( int sign, int n1, int n2, int n3, float *array, int ld1, int ld2, float *save);


/* *******************************************************
	C  double <---> zomplex FFTs
******************************************************* */
double *dfft1di( int n, double *save);
double *dfft1dui( int n, double *save);
int dfft1d( int sign, int n, double *array, int inc, double *save);
int dfft1du( int sign, int n, double *array, int inc, double *save);

double *dfftm1di( int m, double *save);
int dfftm1d( int sign, int m, int n, double *array, int incI, int incJ, double *save);
double *dfftm1dui( int m, double *save);
int dfftm1du( int sign, int m, int n, double *array, int incI, int incJ, double *save);

double *dfft2di( int n1, int n2, double *save);
double *dfft2dui( int n1, int n2, double *save);
int dfft2d( int sign, int n1, int n2, double *array, int ld, double *save);
int dfft2du( int sign, int n1, int n2, double *array, int ld, double *save);

double *dfft3di( int n1, int n2, int n3, double *save);
double *dfft3dui( int n1, int n2, int n3, double *save);
int dfft3d( int sign, int n1, int n2, int n3, double *array, int ld1, int ld2, double *save);
int dfft3du( int sign, int n1, int n2, int n3, double *array, int ld1, int ld2, double *save);

/* *******************************************************
	NEW ... C  double <---> zomplex FFTs
******************************************************* */
double *dzfft1dui( int n, double *save);
int dzfft1du( int sign, int n, double *array, int inc, double *save);
int zdfft1du( int sign, int n, double *array, int inc, double *save);

double *dzfftm1dui( int m, double *save);
int dzfftm1du( int sign, int m, int n, double *array, int incI, int incJ, double *save);
int zdfftm1du( int sign, int m, int n, double *array, int incI, int incJ, double *save);

double *dzfft2dui( int n1, int n2, double *save);
int dzfft2du( int sign, int n1, int n2, double *array, int ld, double *save);
int zdfft2du( int sign, int n1, int n2, double *array, int ld, double *save);

double *dzfft3dui( int n1, int n2, int n3, double *save);
int dzfft3du( int sign, int n1, int n2, int n3, double *array, int ld1, int ld2, double *save);
int zdfft3du( int sign, int n1, int n2, int n3, double *array, int ld1, int ld2, double *save);

float *scfft1dui( int n, float *save);
int scfft1du( int sign, int n, float *array, int inc, float *save);
int csfft1du( int sign, int n, float *array, int inc, float *save);

float *scfftm1dui( int m, float *save);
int scfftm1du( int sign, int m, int n, float *array, int incI, int incJ, float *save);
int csfftm1du( int sign, int m, int n, float *array, int incI, int incJ, float *save);

float *scfft2dui( int n1, int n2, float *save);
int scfft2du( int sign, int n1, int n2, float *array, int ld, float *save);
int csfft2du( int sign, int n1, int n2, float *array, int ld, float *save);

float *scfft3dui( int n1, int n2, int n3, float *save);
int scfft3du( int sign, int n1, int n2, int n3, float *array, int ld1, int ld2, float *save);
int csfft3du( int sign, int n1, int n2, int n3, float *array, int ld1, int ld2, float *save);

/*
* 	Fortran Interface
*/
void dzfft1dui_( int *n, double *save);
void dzfft1du_( int *sign, int *n, double *array, int *inc, double *save);
void zdfft1du_( int *sign, int *n, double *array, int *inc, double *save);

void dzfftm1dui_( int *m, double *save);
void dzfftm1du_( int *sign, int *m, int *n, double *array, int *incI, int *incJ, double *save);
void zdfftm1du_( int *sign, int *m, int *n, double *array, int *incI, int *incJ, double *save);

void dzfft2dui_( int *n1, int *n2, double *save);
void dzfft2du_( int *sign, int *n1, int *n2, double *array, int *ld, double *save);
void zdfft2du_( int *sign, int *n1, int *n2, double *array, int *ld, double *save);

void dzfft3dui_( int *n1, int *n2, int *n3, double *save);
void dzfft3du_( int *sign, int *n1, int *n2, int *n3, double *array, int *ld1, int *ld2, double *save);
void zdfft3du_( int *sign, int *n1, int *n2, int *n3, double *array, int *ld1, int *ld2, double *save);

void scfft1dui_( int *n, float *save);
void scfft1du_( int *sign, int *n, float *array, int *inc, float *save);
void csfft1du_( int *sign, int *n, float *array, int *inc, float *save);

void scfftm1dui_( int *m, float *save);
void scfftm1du_( int *sign, int *m, int *n, float *array, int *incI, int *incJ, float *save);
void csfftm1du_( int *sign, int *m, int *n, float *array, int *incI, int *incJ, float *save);

void scfft2dui_( int *n1, int *n2, float *save);
void scfft2du_( int *sign, int *n1, int *n2, float *array, int *ld, float *save);
void csfft2du_( int *sign, int *n1, int *n2, float *array, int *ld, float *save);

void scfft3dui_( int *n1, int *n2, int *n3, float *save);
void scfft3du_( int *sign, int *n1, int *n2, int *n3, float *array, int *ld1, int *ld2, float *save);
void csfft3du_( int *sign, int *n1, int *n2, int *n3, float *array, int *ld1, int *ld2, float *save);

/* *******************************************************
	NEW ... Packed C  double <---> zomplex FFTs
******************************************************* */
double *dzfft1di( int n, double *save);
int dzfft1d( int sign, int n, double *array, int inc, double *save);
int zdfft1d( int sign, int n, double *array, int inc, double *save);

double *dzfftm1di( int m, double *save);
int dzfftm1d( int sign, int m, int n, double *array, int incI, int incJ, double *save);
int zdfftm1d( int sign, int m, int n, double *array, int incI, int incJ, double *save);

double *dzfft2di( int n1, int n2, double *save);
int dzfft2d( int sign, int n1, int n2, double *array, int ld, double *save);
int zdfft2d( int sign, int n1, int n2, double *array, int ld, double *save);

double *dzfft3di( int n1, int n2, int n3, double *save);
int dzfft3d( int sign, int n1, int n2, int n3, double *array, int ld1, int ld2, double *save);
int zdfft3d( int sign, int n1, int n2, int n3, double *array, int ld1, int ld2, double *save);

float *scfft1di( int n, float *save);
int scfft1d( int sign, int n, float *array, int inc, float *save);
int csfft1d( int sign, int n, float *array, int inc, float *save);

float *scfftm1di( int m, float *save);
int scfftm1d( int sign, int m, int n, float *array, int incI, int incJ, float *save);
int csfftm1d( int sign, int m, int n, float *array, int incI, int incJ, float *save);

float *scfft2di( int n1, int n2, float *save);
int scfft2d( int sign, int n1, int n2, float *array, int ld, float *save);
int csfft2d( int sign, int n1, int n2, float *array, int ld, float *save);

float *scfft3di( int n1, int n2, int n3, float *save);
int scfft3d( int sign, int n1, int n2, int n3, float *array, int ld1, int ld2, float *save);
int csfft3d( int sign, int n1, int n2, int n3, float *array, int ld1, int ld2, float *save);

/*
* 	Fortran Interface
*/
void dzfft1di_( int *n, double *save);
void dzfft1d_( int *sign, int *n, double *array, int *inc, double *save);
void zdfft1d_( int *sign, int *n, double *array, int *inc, double *save);

void dzfftm1di_( int *m, double *save);
void dzfftm1d_( int *sign, int *m, int *n, double *array, int *incI, int *incJ, double *save);
void zdfftm1d_( int *sign, int *m, int *n, double *array, int *incI, int *incJ, double *save);

void dzfft2di_( int *n1, int *n2, double *save);
void dzfft2d_( int *sign, int *n1, int *n2, double *array, int *ld, double *save);
void zdfft2d_( int *sign, int *n1, int *n2, double *array, int *ld, double *save);

void dzfft3di_( int *n1, int *n2, int *n3, double *save);
void dzfft3d_( int *sign, int *n1, int *n2, int *n3, double *array, int *ld1, int *ld2, double *save);
void zdfft3d_( int *sign, int *n1, int *n2, int *n3, double *array, int *ld1, int *ld2, double *save);

void scfft1di_( int *n, float *save);
void scfft1d_( int *sign, int *n, float *array, int *inc, float *save);
void csfft1d_( int *sign, int *n, float *array, int *inc, float *save);

void scfftm1di_( int *m, float *save);
void scfftm1d_( int *sign, int *m, int *n, float *array, int *incI, int *incJ, float *save);
void csfftm1d_( int *sign, int *m, int *n, float *array, int *incI, int *incJ, float *save);

void scfft2di_( int *n1, int *n2, float *save);
void scfft2d_( int *sign, int *n1, int *n2, float *array, int *ld, float *save);
void csfft2d_( int *sign, int *n1, int *n2, float *array, int *ld, float *save);

void scfft3di_( int *n1, int *n2, int *n3, float *save);
void scfft3d_( int *sign, int *n1, int *n2, int *n3, float *array, int *ld1, int *ld2, float *save);
void csfft3d_( int *sign, int *n1, int *n2, int *n3, float *array, int *ld1, int *ld2, float *save);

/************************************************************************
    C  Product modules ... 
	    Performs convolution in 1 Domain by Product in the other
********************************************************************** */

void sprod1du( int n, float *y, int incy, float *filter, int incx);
void dprod1du( int n, double *y, int incy, double *filter, int incx);
		
void sprodm1du( int n1, int n2, float *y, int incy, int ldy, float *filter, int incx, int ldx);
void dprodm1du( int n1, int n2, double *y, int incy, int ldy, double *filter, int incx, int ldx);

void sprod2du( int n1, int n2, float *y, int ldy, float *filter, int ldx);
void dprod2du( int n1, int n2, double *y, int ldy, double *filter, int ldx);

void sprod3du( int n1, int n2, int n3, float *y, int ldy1, int ldy2, 
	    float *filter, int ldx1, int ldx2);
void dprod3du( int n1, int n2, int n3, double *y, int ldy1, int ldy2, 
	    double *filter, int ldx1, int ldx2);

void sprod1d( int n, float *y, int incy, float *filter, int incx);
void dprod1d( int n, double *y, int incy, double *filter, int incx);
		
void sprodm1d( int n1, int n2, float *y, int incy, int ldy, float *filter, int incx, int ldx);
void dprodm1d( int n1, int n2, double *y, int incy, int ldy, double *filter, int incx, int ldx);

void sprod2d( int n1, int n2, float *y, int ldy, float *filter, int ldx);
void dprod2d( int n1, int n2, double *y, int ldy, double *filter, int ldx);

void sprod3d( int n1, int n2, int n3, float *y, int ldy1, int ldy2, 
	    float *filter, int ldx1, int ldx2);
void dprod3d( int n1, int n2, int n3, double *y, int ldy1, int ldy2, 
	    double *filter, int ldx1, int ldx2);

/************************************************************************
    C Scaling modules ... 
	    Scale the sequence by value APLHA ... 
		to keep absolute values after Direct+Inverse transform.
********************************************************************** */

void sscal1d( int n, float alpha, float *y, int inc);
void dscal1d( int n, double alpha, double *y, int inc);

void sscalm1d( int m, int n, float alpha, float *array, int incI, int incJ);
void dscalm1d( int m, int n, double alpha, double *array, int incI, int incJ);

void sscal2d( int nx, int ny, float alpha, float *y, int ld);
void dscal2d( int nx, int ny, double alpha, double *y, int ld);

void sscal3d( int nx, int ny, int nz, float alpha, float *y, int ld1,int ld2);
void dscal3d( int nx, int ny, int nz, double alpha, double *y, int ld1,int ld2);

/* ********************************************************
	Fortran real <---> complex FFTs
******************************************************** */
void sfft1di_( int *n, float *save);
void sfft1dui_( int *n, float *save);

void sfft1d_( int *sign, int *n, float *array, int *inc, float *save);
void sfft1du_( int *sign, int *n, float *array, int *inc, float *save);

void sfftm1di_( int *m, float *save);
void sfftm1d_( int *sign, int *m, int *n, float *array, int *incI, int *incJ, float *save);
void sfftm1dui_( int *m, float *save);
void sfftm1du_( int *sign, int *m, int *n, float *array, int *incI, int *incJ, float *save);

void sfft2di_( int *n1, int *n2, void *save);
void sfft2dui_( int *n1, int *n2, void *save);
void sfft2d_( int *sign, int *n1, int *n2, void *array, int *ld, void *save);
void sfft2du_( int *sign, int *n1, int *n2, void *array, int *ld, void *save);

void sfft3di_( int *n1, int *n2, int *n3, void *save);
void sfft3dui_( int *n1, int *n2, int *n3, void *save);
void sfft3d_( int *sign, int *n1, int *n2, int *n3, void *array, int *ld1, int *ld2, void *save);
void sfft3du_( int *sign, int *n1, int *n2, int *n3, void *array, int *ld1, int *ld2, void *save);

/* ********************************************************
	Fortran double <---> zomplex FFTs
******************************************************** */
void dfft1di_( int *n, double *save);
void dfft1dui_( int *n, double *save);

void dfft1d_( int *sign, int *n, double *array, int *inc, double *save);
void dfft1du_( int *sign, int *n, double *array, int *inc, double *save);

void dfftm1di_( int *m, double *save);
void dfftm1d_( int *sign, int *m, int *n, double *array, int *incI, int *incJ, double *save);
void dfftm1dui_( int *m, double *save);
void dfftm1du_( int *sign, int *m, int *n, double *array, int *incI, int *incJ, double *save);

void dfft2di_( int *n1, int *n2, void *save);
void dfft2dui_( int *n1, int *n2, void *save);
void dfft2d_( int *sign, int *n1, int *n2, void *array, int *ld, void *save);
void dfft2du_( int *sign, int *n1, int *n2, void *array, int *ld, void *save);

void dfft3di_( int *n1, int *n2, int *n3, void *save);
void dfft3dui_( int *n1, int *n2, int *n3, void *save);
void dfft3d_( int *sign, int *n1, int *n2, int *n3, void *array, int *ld1, int *ld2, void *save);
void dfft3du_( int *sign, int *n1, int *n2, int *n3, void *array, int *ld1, int *ld2, void *save);

/************************************************************************
    C  Product modules ... 
	    Performs convolution in 1 Domain by Product in the other
********************************************************************** */

void sprod1du_( int *n, float *y, int *incy, float *filter, int *incx);
void dprod1du_( int *n, double *y, int *incy, double *filter, int *incx);
		
void sprodm1du_( int *n1, int *n2, float *y, int *incy, int *ldy, float *filter, int *incx, int *ldx);
void dprodm1du_( int *n1, int *n2, double *y, int *incy, int *ldy, double *filter, int *incx, int *ldx);

void sprod2du_( int *n1, int *n2, float *y, int *ldy, float *filter, int *ldx);
void dprod2du_( int *n1, int *n2, double *y, int *ldy, double *filter, int *ldx);

void sprod3du_( int *n1, int *n2, int *n3, float *y, int *ldy1, int *ldy2, 
	    float *filter, int *ldx1, int *ldx2);
void dprod3du_( int *n1, int *n2, int *n3, double *y, int *ldy1, int *ldy2, 
	    double *filter, int *ldx1, int *ldx2);

void sprod1d_( int *n, float *y, int *incy, float *filter, int *incx);
void dprod1d_( int *n, double *y, int *incy, double *filter, int *incx);
		
void sprodm1d_( int *n1, int *n2, float *y, int *incy, int *ldy, float *filter, int *incx, int *ldx);
void dprodm1d_( int *n1, int *n2, double *y, int *incy, int *ldy, double *filter, int *incx, int *ldx);

void sprod2d_( int *n1, int *n2, float *y, int *ldy, float *filter, int *ldx);
void dprod2d_( int *n1, int *n2, double *y, int *ldy, double *filter, int *ldx);

void sprod3d_( int *n1, int *n2, int *n3, float *y, int *ldy1, int *ldy2, 
	    float *filter, int *ldx1, int *ldx2);
void dprod3d_( int *n1, int *n2, int *n3, double *y, int *ldy1, int *ldy2, 
	    double *filter, int *ldx1, int *ldx2);

/************************************************************************
    Fortran Scaling modules ... 
	    Scale the sequence by value APLHA ... 
		to keep absolute values after Direct+Inverse transform.
********************************************************************** */ 

void sscal1d_( int *n, float *alpha, float *y, int *inc);
void dscal1d_( int *n, double *alpha, double *y, int *inc);

void sscalm1d_( int *m, int *n, float *alpha, float *array, int *incI, int *incJ);
void dscalm1d_( int *m, int *n, double *alpha, double *array, int *incI, int *incJ);

void sscal2d_( int *nx, int *ny, float *alpha, float *y, int *ld);
void dscal2d_( int *nx, int *ny, double *alpha, double *y, int *ld);

void sscal3d_( int *nx, int *ny, int *nz, float *alpha, float *y, int *ld1,int *ld2);
void dscal3d_( int *nx, int *ny, int *nz, double *alpha, double *y, int *ld1,int *ld2);

#ifdef __cplusplus
}
#endif

#endif
