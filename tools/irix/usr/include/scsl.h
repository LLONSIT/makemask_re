/*
 *      (C) COPYRIGHT SILICON GRAPHICS, INC.
 *      UNPUBLISHED PROPRIETARY INFORMATION.
 *      ALL RIGHTS RESERVED.
 */

/* Declarations for SCSL utility routines */

#ifndef _SCSL_H
#define _SCSL_H

#if defined(SCSL_I8_INT_ARGS)
#  define SCSL_INT_T long long
#else
#  define SCSL_INT_T int
#endif

#ifdef __cplusplus
extern "C"
{
#endif

  /* 64-bit parallel random number routines */

  float srand64(float *);

  double drand64(double *);

  void drand64_advance(long long);

  void drand64_get(long long *, 
		   long long *, 
		   SCSL_INT_T);

  void drand64_getv(long long *, 
		    long long *);

  SCSL_INT_T drand64_maxthreads(void);

  void drand64_set(long long);

  void drand64_setv(long long *, 
		    long long *);

  SCSL_INT_T drand64_thread(SCSL_INT_T);

#ifdef __cplusplus
}
#endif

#undef SCSL_INT_T

#endif
