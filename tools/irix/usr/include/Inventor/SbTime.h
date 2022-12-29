/*
 * Copyright 1991-1996, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED
 *
 * UNPUBLISHED -- Rights reserved under the copyright laws of the United
 * States.   Use of a copyright notice is precautionary only and does not
 * imply publication or disclosure.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to restrictions
 * as set forth in FAR 52.227.19(c)(2) or subparagraph (c)(1)(ii) of the Rights
 * in Technical Data and Computer Software clause at DFARS 252.227-7013 and/or
 * in similar or successor clauses in the FAR, or the DOD or NASA FAR
 * Supplement.  Contractor/manufacturer is Silicon Graphics, Inc.,
 * 2011 N. Shoreline Blvd. Mountain View, CA 94039-7311.
 *
 * THE CONTENT OF THIS WORK CONTAINS CONFIDENTIAL AND PROPRIETARY
 * INFORMATION OF SILICON GRAPHICS, INC. ANY DUPLICATION, MODIFICATION,
 * DISTRIBUTION, OR DISCLOSURE IN ANY FORM, IN WHOLE, OR IN PART, IS STRICTLY
 * PROHIBITED WITHOUT THE PRIOR EXPRESS WRITTEN PERMISSION OF SILICON
 * GRAPHICS, INC.
 */
//  -*- C++ -*-

/*
 *
 _______________________________________________________________________
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 |
 |   $Revision: 2.3 $
 |
 |   Description:
 |	This file defines the SbTime class for manipulating times
 |
 |   Classes:
 |	SbTime
 |
 |   Author(s)		: Nick Thompson
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef _SB_TIME_
#define _SB_TIME_

#include <sys/time.h>
#include <math.h>
#include <limits.h>
#include <Inventor/SbBasic.h>
#include <Inventor/SbString.h>

#ifdef _CRAY
#define trunc(x) x
#endif /* _CRAY */


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbTime
//
//  Representation of a time.  Some parts are not adequately debugged:
//  for example, it is not clear when it is legal to have negative
//  values.
//
//////////////////////////////////////////////////////////////////////////////

class SbTime {
  public:

    // Default constructor
    SbTime()					{}

    // Constructor taking a double (in seconds)
    SbTime(double sec);

    // Constructor taking seconds + microseconds
    SbTime(time_t sec, long usec)		// System long from <sys/time.h>
	{ t.tv_sec = sec; t.tv_usec = usec; }

  private:
    // Constructor taking milliseconds
    //
    // NOTE! This constructor has been removed.  Change existing uses of
    // 		SbTime(msec)
    // to
    //		time_t secs = msec / 1000;
    //		SbTime(secs, 1000 * (msec - 1000 * sec))
    // The constructor was removed because it led to unexpected results --
    // while SbTime(1.0) results in 1 second, SbTime(1) resulted in 1
    // MILLIsecond).  Its declaration has been kept, as "private", so that 
    // existing code using it will get compilation errors; if it was removed
    // completely, an existing use of SbTime(1) would silently cast to
    // SbTime(1.0) resulting in hard-to-find bugs.  This declaration
    // will be removed entirely in a future release, so that SbTime(1)
    // will be equivalent to SbTime(1.0).
    SbTime(uint32_t msec);
  public:

    // Constructor taking struct timeval
    SbTime(const struct timeval *tv)
	{ t.tv_sec = tv->tv_sec; t.tv_usec = tv->tv_usec; }

    // Destructors for C
    // C-api.h: void	SbTimeDelete(SbTime *);
    // C-api.c++: void	SbTimeDelete(SbTime *_this)
    // C-api.c++: { delete _this; }

    // Get the current time (seconds since Jan 1, 1970)
    static SbTime		getTimeOfDay();

    // Set to the current time (seconds since Jan 1, 1970)
    void			setToTimeOfDay();

    // Get a zero time
    static SbTime		zero()
	{ return SbTime(0, 0); }

    // Get a time far, far into the future
    static SbTime		max()
	{ return SbTime(INT32_MAX, 999999); }

    // Set time from a double (in seconds)
    void		setValue(double sec)
	{ t.tv_sec = time_t(trunc(sec)); 
	  t.tv_usec = long((sec - t.tv_sec) * 1000000.0); }

    // Set time from seconds + microseconds
    void		setValue(time_t sec, long usec)  	// System long
	{ t.tv_sec = sec; t.tv_usec = usec; }

    // Set time from a struct timeval
    void		setValue(const struct timeval *tv)
	{ t.tv_sec = tv->tv_sec; t.tv_usec = tv->tv_usec; }

    // Set time from milliseconds
    void		setMsecValue(unsigned long msec)  	// System long
	{ t.tv_sec = time_t(msec/1000); 
	  t.tv_usec = long(1000 * (msec % 1000)); }

    // Get time in seconds as a double
    double		getValue() const
	{ return (double) t.tv_sec + (double) t.tv_usec / 1000000.0; }

    // Get time in seconds & microseconds
    void		getValue(time_t &sec, long &usec) const  // System long
	{ sec = t.tv_sec; usec = t.tv_usec; }

    // Get time in a struct timeval
    void		getValue(struct timeval *tv) const
	{ tv->tv_sec = t.tv_sec; tv->tv_usec = t.tv_usec; }

    // Get time in milliseconds (for Xt)
    unsigned long	getMsecValue() const			// System long
	{ return t.tv_sec * 1000 + t.tv_usec / 1000; }

    // Convert to a string.  The default format is seconds with
    // 3 digits of fraction precision.  See the SbTime man page for
    // explanation of the format string.
    SbString			format(const char *fmt = "%S.%i") const;

    // Convert to a date string, interpreting the time as seconds since
    // Jan 1, 1970.  The default format gives "Tuesday, 01/26/93 11:23:41 AM".
    // See the 'cftime()' man page for explanation of the format string.
    SbString			formatDate(const char *fmt = "%A, %D %r") const;

    // Addition
    friend SbTime		operator +(const SbTime &t0, const SbTime &t1);

    // Subtraction
    friend SbTime		operator -(const SbTime &t0, const SbTime &t1);

    // Destructive addition
    SbTime &			operator +=(const SbTime &tm)
	{ return (*this = *this + tm); }

    // Destructive subtraction
    SbTime &			operator -=(const SbTime &tm)
	{ return (*this = *this - tm); }

    // Unary negation
    SbTime			operator -() const
	{ return (t.tv_usec == 0) ? SbTime(- t.tv_sec, 0)
	      : SbTime(- t.tv_sec - 1, 1000000 - t.tv_usec); }

    // multiplication by scalar
    friend SbTime		operator *(const SbTime &tm, double s);

    friend SbTime		operator *(double s, const SbTime &tm)
	{ return tm * s; }

    // destructive multiplication by scalar
    SbTime &			operator *=(double s)
	{ *this = *this * s; return *this; }

    // division by scalar
    friend SbTime		operator /(const SbTime &tm, double s);

    // destructive division by scalar
    SbTime &			operator /=(double s)
	{ return (*this = *this / s); }

    // division by another time
    double			operator /(const SbTime &tm) const
	{ return getValue() / tm.getValue(); }

    // modulus for two times
    SbTime			operator %(const SbTime &tm) const
	{ return *this - tm * floor(*this / tm); }

    // equality operators
    int				operator ==(const SbTime &tm) const
	{ return (t.tv_sec == tm.t.tv_sec) && (t.tv_usec == tm.t.tv_usec); }

    int				operator !=(const SbTime &tm) const
	{ return ! (*this == tm); }

    // relational operators
    inline SbBool		operator <(const SbTime &tm) const;
    inline SbBool		operator >(const SbTime &tm) const;
    inline SbBool		operator <=(const SbTime &tm) const;
    inline SbBool		operator >=(const SbTime &tm) const;

  private:
    struct timeval		t;
};



inline SbBool
SbTime::operator <(const SbTime &tm) const
{
    if ((t.tv_sec < tm.t.tv_sec) ||
	(t.tv_sec == tm.t.tv_sec && t.tv_usec < tm.t.tv_usec))
	return TRUE;
    else
	return FALSE;
}

inline SbBool
SbTime::operator >(const SbTime &tm) const
{
    if ((t.tv_sec > tm.t.tv_sec) ||
	(t.tv_sec == tm.t.tv_sec && t.tv_usec > tm.t.tv_usec))
	return TRUE;
    else
	return FALSE;
}

inline SbBool
SbTime::operator <=(const SbTime &tm) const
{
    if ((t.tv_sec < tm.t.tv_sec) ||
	(t.tv_sec == tm.t.tv_sec && t.tv_usec <= tm.t.tv_usec))
	return TRUE;
    else
	return FALSE;
}

inline SbBool
SbTime::operator >=(const SbTime &tm) const
{
    if ((t.tv_sec > tm.t.tv_sec) ||
	(t.tv_sec == tm.t.tv_sec && t.tv_usec >= tm.t.tv_usec))
	return TRUE;
    else
	return FALSE;
}


#endif /* _SB_TIME_ */
