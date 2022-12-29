#ifndef _SGI_CONV_
#define _SGI_CONV_

typedef struct{
    float real;
    float imag;
} complex;

typedef struct{
    double real;
    double imag;
} zomplex;

void dfir1d(	double *f, int incf, int if0, int nf, 
		double *g, int incg, int ig0, int ng,
		double *h, int inch, int ih0, int nh,
		double alpha, double beta);

void diir1d(	double *f, int incf, int if0, int nf, 
		double *g, int incg, int ig0, int ng,
		double *h, int inch, int ih0, int nh);

void dcor1d(	double *f, int incf, int if0, int nf, 
		double *g, int incg, int ig0, int ng,
		double *h, int inch, int ih0, int nh);


void sfir1d(	float *f, int incf, int if0, int nf, 
		float *g, int incg, int ig0, int ng,
		float *h, int inch, int ih0, int nh,
		float alpha, float beta);

void siir1d(	float *f, int incf, int if0, int nf, 
		float *g, int incg, int ig0, int ng,
		float *h, int inch, int ih0, int nh);

void scor1d(	float *f, int incf, int if0, int nf, 
		float *g, int incg, int ig0, int ng,
		float *h, int inch, int ih0, int nh);


void zfir1d(	zomplex *f, int incf, int if0, int nf, 
		zomplex *g, int incg, int ig0, int ng,
		zomplex *h, int inch, int ih0, int nh,
		zomplex *alpha, zomplex *beta);

void ziir1d(	zomplex *f, int incf, int if0, int nf, 
		zomplex *g, int incg, int ig0, int ng,
		zomplex *h, int inch, int ih0, int nh);

void zcor1d(	zomplex *f, int incf, int if0, int nf, 
		zomplex *g, int incg, int ig0, int ng,
		zomplex *h, int inch, int ih0, int nh);


void cfir1d(	complex *f, int incf, int if0, int nf, 
		complex *g, int incg, int ig0, int ng,
		complex *h, int inch, int ih0, int nh,
		complex *alpha, complex *beta);

void ciir1d(	complex *f, int incf, int if0, int nf, 
		complex *g, int incg, int ig0, int ng,
		complex *h, int inch, int ih0, int nh);

void ccor1d(	complex *f, int incf, int if0, int nf, 
		complex *g, int incg, int ig0, int ng,
		complex *h, int inch, int ih0, int nh);


void zfir2d(	zomplex *f,int incf,int ldf,int ifx0,int n_fx,int ify0,int n_fy,
		zomplex *g,int incg,int ldg,int igx0,int n_gx,int igy0,int n_gy,
		zomplex *h,int inch,int ldh,int ihx0,int n_hx,int ihy0,int n_hy,
		zomplex *alpha, zomplex *beta);

void ziir2d(	zomplex *f,int incf,int ldf,int ifx0,int n_fx,int ify0,int n_fy,
		zomplex *g,int incg,int ldg,int igx0,int n_gx,int igy0,int n_gy,
		zomplex *h,int inch,int ldh,int ihx0,int n_hx,int ihy0,int n_hy);

void zcor2d(	zomplex *f,int incf,int ldf,int ifx0,int n_fx,int ify0,int n_fy,
		zomplex *g,int incg,int ldg,int igx0,int n_gx,int igy0,int n_gy,
		zomplex *h,int inch,int ldh,int ihx0,int n_hx,int ihy0,int n_hy);

void zfirm1d(	zomplex *f,int incf,int ldf,int ifx0,int n_fx,int n_seq, 
		zomplex *g,int incg,int igx0,int n_gx,
		zomplex *h,int inch,int ldh,int ihx0,int n_hx,
		zomplex *alpha, zomplex *beta);

void ziirm1d(	zomplex *f,int incf,int ldf,int ifx0,int n_fx,int n_seq, 
		zomplex *g,int incg,int igx0,int n_gx,
		zomplex *h,int inch,int ldh,int ihx0,int n_hx);

void zcorm1d(	zomplex *f,int incf,int ldf,int ifx0,int n_fx,int n_seq, 
		zomplex *g,int incg,int igx0,int n_gx,
		zomplex *h,int inch,int ldh,int ihx0,int n_hx);



void cfir2d(	complex *f,int incf,int ldf,int ifx0,int n_fx,int ify0,int n_fy,
		complex *g,int incg,int ldg,int igx0,int n_gx,int igy0,int n_gy,
		complex *h,int inch,int ldh,int ihx0,int n_hx,int ihy0,int n_hy,
		complex *alpha, complex *beta);

void ciir2d(	complex *f,int incf,int ldf,int ifx0,int n_fx,int ify0,int n_fy,
		complex *g,int incg,int ldg,int igx0,int n_gx,int igy0,int n_gy,
		complex *h,int inch,int ldh,int ihx0,int n_hx,int ihy0,int n_hy);

void ccor2d(	complex *f,int incf,int ldf,int ifx0,int n_fx,int ify0,int n_fy,
		complex *g,int incg,int ldg,int igx0,int n_gx,int igy0,int n_gy,
		complex *h,int inch,int ldh,int ihx0,int n_hx,int ihy0,int n_hy);

void cfirm1d(	complex *f,int incf,int ldf,int ifx0,int n_fx,int n_seq, 
		complex *g,int incg,int igx0,int n_gx,
		complex *h,int inch,int ldh,int ihx0,int n_hx,
		complex *alpha, complex *beta);

void ciirm1d(	complex *f,int incf,int ldf,int ifx0,int n_fx,int n_seq, 
		complex *g,int incg,int igx0,int n_gx,
		complex *h,int inch,int ldh,int ihx0,int n_hx);

void ccorm1d(	complex *f,int incf,int ldf,int ifx0,int n_fx,int n_seq, 
		complex *g,int incg,int igx0,int n_gx,
		complex *h,int inch,int ldh,int ihx0,int n_hx);

void dfir2d(	double *f,int incf,int ldf,int ifx0,int n_fx,int ify0,int n_fy,
		double *g,int incg,int ldg,int igx0,int n_gx,int igy0,int n_gy,
		double *h,int inch,int ldh,int ihx0,int n_hx,int ihy0,int n_hy,
		double alpha, double beta);

void diir2d(	double *f,int incf,int ldf,int ifx0,int n_fx,int ify0,int n_fy,
		double *g,int incg,int ldg,int igx0,int n_gx,int igy0,int n_gy,
		double *h,int inch,int ldh,int ihx0,int n_hx,int ihy0,int n_hy);

void dcor2d(	double *f,int incf,int ldf,int ifx0,int n_fx,int ify0,int n_fy,
		double *g,int incg,int ldg,int igx0,int n_gx,int igy0,int n_gy,
		double *h,int inch,int ldh,int ihx0,int n_hx,int ihy0,int n_hy);

void dfirm1d(	double *f,int incf,int ldf,int ifx0,int n_fx,int n_seq, 
		double *g,int incg,int igx0,int n_gx,
		double *h,int inch,int ldh,int ihx0,int n_hx,
		double alpha, double beta);

void diirm1d(	double *f,int incf,int ldf,int ifx0,int n_fx,int n_seq, 
		double *g,int incg,int igx0,int n_gx,
		double *h,int inch,int ldh,int ihx0,int n_hx);

void dcorm1d(	double *f,int incf,int ldf,int ifx0,int n_fx,int n_seq, 
		double *g,int incg,int igx0,int n_gx,
		double *h,int inch,int ldh,int ihx0,int n_hx);

void sfir2d(	float *f,int incf,int lsf,int ifx0,int n_fx,int ify0,int n_fy,
		float *g,int incg,int ldg,int igx0,int n_gx,int igy0,int n_gy,
		float *h,int inch,int ldh,int ihx0,int n_hx,int ihy0,int n_hy,
		float alpha, float beta);

void siir2d(	float *f,int incf,int lsf,int ifx0,int n_fx,int ify0,int n_fy,
		float *g,int incg,int ldg,int igx0,int n_gx,int igy0,int n_gy,
		float *h,int inch,int ldh,int ihx0,int n_hx,int ihy0,int n_hy);

void scor2d(	float *f,int incf,int lsf,int ifx0,int n_fx,int ify0,int n_fy,
		float *g,int incg,int ldg,int igx0,int n_gx,int igy0,int n_gy,
		float *h,int inch,int ldh,int ihx0,int n_hx,int ihy0,int n_hy);

void sfirm1d(	float *f,int incf,int lsf,int ifx0,int n_fx,int n_seq, 
		float *g,int incg,int igx0,int n_gx,
		float *h,int inch,int ldh,int ihx0,int n_hx,
		float alpha, float beta);

void siirm1d(	float *f,int incf,int lsf,int ifx0,int n_fx,int n_seq, 
		float *g,int incg,int igx0,int n_gx,
		float *h,int inch,int ldh,int ihx0,int n_hx);

void scorm1d(	float *f,int incf,int lsf,int ifx0,int n_fx,int n_seq, 
		float *g,int incg,int igx0,int n_gx,
		float *h,int inch,int ldh,int ihx0,int n_hx);

#endif
