#if 0 

    Copyright (c) 1991 SGI   All Rights Reserved
    THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF SGI
    The copyright notice above does not evidence any
    actual or intended publication of such source code,
    and is an unpublished work by Silicon Graphics, Inc.
    This material contains CONFIDENTIAL INFORMATION that
    is the property of Silicon Graphics, Inc. Any use,
    duplication or disclosure not specifically authorized
    by Silicon Graphics is strictly prohibited.
    
    RESTRICTED RIGHTS LEGEND:
    
    Use, duplication or disclosure by the Government is
    subject to restrictions as set forth in subdivision
    (c)(1)(ii) of the Rights in Technical Data and Computer
    Software clause at DFARS 52.227-7013, and/or in similar
    or successor clauses in the FAR, DOD or NASA FAR
    Supplement.  Unpublished- rights reserved under the
    Copyright Laws of the United States.  Contractor is
    SILICON GRAPHICS, INC., 2011 N. Shoreline Blvd.,
    Mountain View, CA 94039-7311

#endif
#ifndef _iflCoord_h_
#define _iflCoord_h_

#include <ifl/iflDefs.h>
#include <ifl/iflTypes.h>

#ifdef __cplusplus

// iflXY<type> is an x,y pair of scalars, for any type
// XXX The iflXYS<type> versions are here because of a bug in the compiler
// XXX which causes the null constructor to be called for every element of
// XXX an array of a type when there is *any* constructor declared.  So we
// XXX have a version of iflXY<type> that contains the data fields but no
// XXX constructor.  This hack should be removed when BUG# 262092 is fixed.
template<class T> struct iflXYS {
    T x,y;
};

template<class T> 
class iflXY : public iflXYS<T> {

public:
    // Constructing

    iflXY() {}
    iflXY(T s)			{ init(s); }
    iflXY(T x, T y)		{ init(x,y); }
    iflXY(const iflXY& that)	{ init(that.x,that.y); }

    // Initializing

    iflXY& init(T X, T Y) { x=X; y=Y; return *this; }
    iflXY& init(T s) { x=s; y=s; return *this; }

    // Assignment operators

    inline iflXY& operator= (const iflXY& that);
    inline iflXY& operator+=(const iflXY& that);
    inline iflXY& operator-=(const iflXY& that);
    inline iflXY& operator*=(const iflXY& that);
    inline iflXY& operator/=(const iflXY& that);
    inline iflXY& operator%=(const iflXY& that);
    inline iflXY& operator&=(const iflXY& that);
    inline iflXY& operator|=(const iflXY& that);

    // Comparison operators

    inline int operator==(const iflXY& that) const;
    inline int operator!=(const iflXY& that) const;
    inline int operator<=(const iflXY& that) const;
    inline int operator>=(const iflXY& that) const;
    inline int operator<(const iflXY& that) const;
    inline int operator>(const iflXY& that) const;

    // Componentwise arithmetic operators

    inline iflXY operator+(const iflXY& that) const;
    inline iflXY operator-(const iflXY& that) const;
    inline iflXY operator*(const iflXY& that) const;
    inline iflXY operator/(const iflXY& that) const;
    inline iflXY operator%(const iflXY& that) const;
    inline iflXY operator&(const iflXY& that) const;
    inline iflXY operator|(const iflXY& that) const;

    // Indexed member access

    T& operator[](iflAxis axis) { return ((T*) this)[int(axis)]; }
};

// Arithmetic ops that take a scalar and a vector and return a vector
template <class T> inline iflXY<T> operator+(const iflXY<T>&, T s);
template <class T> inline iflXY<T> operator-(const iflXY<T>&, T s);
template <class T> inline iflXY<T> operator*(const iflXY<T>&, T s);
template <class T> inline iflXY<T> operator/(const iflXY<T>&, T s);
template <class T> inline iflXY<T> operator%(const iflXY<T>&, T s);
template <class T> inline iflXY<T> operator&(const iflXY<T>&, T s);
template <class T> inline iflXY<T> operator|(const iflXY<T>&, T s);
template <class T> inline iflXY<T> operator+(T s, const iflXY<T>&);
template <class T> inline iflXY<T> operator-(T s, const iflXY<T>&);
template <class T> inline iflXY<T> operator*(T s, const iflXY<T>&);
template <class T> inline iflXY<T> operator/(T s, const iflXY<T>&);
template <class T> inline iflXY<T> operator%(T s, const iflXY<T>&);
template <class T> inline iflXY<T> operator&(T s, const iflXY<T>&);
template <class T> inline iflXY<T> operator|(T s, const iflXY<T>&);
// Dot product
template<class T> inline T iflDot(const iflXY<T>& a, const iflXY<T>& b);
// "Cross" of a single iflXY is the point rotated 90 degrees
// CCW about the origin
template<class T> inline iflXY<T> iflCross(const iflXY<T>& a);


// iflXYZ<type> is an x,y,z triple of scalars, for any type
// XXX The iflXYZS<type> versions are here because of a bug in the compiler
// XXX which causes the null constructor to be called for every element of
// XXX an array of a type when there is *any* constructor declared.  So we
// XXX have a version of iflXYZ<type> that contains the data fields but no
// XXX constructor.  This hack should be removed when BUG# 262092 is fixed.
template<class T> struct iflXYZS {
    T x,y,z;
};

template<class T> 
class iflXYZ : public iflXYZS<T> {

public:
    // Constructing

    iflXYZ() {}
    iflXYZ(T s)			{ init(s,s,s); }
    iflXYZ(T x, T y, T z)	{ init(x,y,z); }
    iflXYZ(const iflXYZ& that)	{ init(that.x,that.y,that.z); }

    // Initializing

    iflXYZ& init(T X, T Y, T Z) { x=X; y=Y; z=Z; return *this; }

    // Assignment operators

    inline iflXYZ& operator= (const iflXYZ& that);
    inline iflXYZ& operator+=(const iflXYZ& that);
    inline iflXYZ& operator-=(const iflXYZ& that);
    inline iflXYZ& operator*=(const iflXYZ& that);
    inline iflXYZ& operator/=(const iflXYZ& that);
    inline iflXYZ& operator%=(const iflXYZ& that);
    inline iflXYZ& operator&=(const iflXYZ& that);
    inline iflXYZ& operator|=(const iflXYZ& that);

    // Comparison operators

    inline int operator==(const iflXYZ& that) const;
    inline int operator!=(const iflXYZ& that) const;
    inline int operator<=(const iflXYZ& that) const;
    inline int operator>=(const iflXYZ& that) const;
    inline int operator<(const iflXYZ& that) const;
    inline int operator>(const iflXYZ& that) const;

    // Componentwise arithmetic operators

    inline iflXYZ operator+(const iflXYZ& that) const;
    inline iflXYZ operator-(const iflXYZ& that) const;
    inline iflXYZ operator*(const iflXYZ& that) const;
    inline iflXYZ operator/(const iflXYZ& that) const;
    inline iflXYZ operator%(const iflXYZ& that) const;
    inline iflXYZ operator&(const iflXYZ& that) const;
    inline iflXYZ operator|(const iflXYZ& that) const;

    // Indexed member access

    T& operator[](iflAxis axis) { return ((T*) this)[int(axis)]; }
};
// Arithmetic ops that take a scalar and a vector and return a vector
template <class T> inline iflXYZ<T> operator+(const iflXYZ<T>&, T s);
template <class T> inline iflXYZ<T> operator-(const iflXYZ<T>&, T s);
template <class T> inline iflXYZ<T> operator*(const iflXYZ<T>&, T s);
template <class T> inline iflXYZ<T> operator/(const iflXYZ<T>&, T s);
template <class T> inline iflXYZ<T> operator%(const iflXYZ<T>&, T s);
template <class T> inline iflXYZ<T> operator&(const iflXYZ<T>&, T s);
template <class T> inline iflXYZ<T> operator|(const iflXYZ<T>&, T s);
template <class T> inline iflXYZ<T> operator+(T s, const iflXYZ<T>&);
template <class T> inline iflXYZ<T> operator-(T s, const iflXYZ<T>&);
template <class T> inline iflXYZ<T> operator*(T s, const iflXYZ<T>&);
template <class T> inline iflXYZ<T> operator/(T s, const iflXYZ<T>&);
template <class T> inline iflXYZ<T> operator%(T s, const iflXYZ<T>&);
template <class T> inline iflXYZ<T> operator&(T s, const iflXYZ<T>&);
template <class T> inline iflXYZ<T> operator|(T s, const iflXYZ<T>&);
// Dot product
template<class T> inline T iflDot(const iflXYZ<T>& a, const iflXYZ<T>& b);
// Cross product
template<class T> 
inline iflXYZ<T> iflCross(const iflXYZ<T>& a, const iflXYZ<T>& b);


// iflXYZC<type> is an x,y,z,c quadruple of scalars, for any type
// XXX The iflXYZCS<type> versions are here because of a bug in the compiler
// XXX which causes the null constructor to be called for every element of
// XXX an array of a type when there is *any* constructor declared.  So we
// XXX have a version of iflXYZC<type> that contains the data fields but no
// XXX constructor.  This hack should be removed when BUG# 262092 is fixed.
template<class T> struct iflXYZCS {
    T x,y,z,c;
};

template<class T> 
class iflXYZC : public iflXYZCS<T> {

public:
    // Constructing

    iflXYZC() {}
    iflXYZC(T s)		    { init(s,s,s,s); }
    iflXYZC(T x, T y, T z, T c)	    { init(x,y,z,c); }
    iflXYZC(const iflXYZC& that)    { init(that.x,that.y,that.z,that.c); }

    // Initializing

    iflXYZC& init(T X, T Y, T Z, T C) { x=X; y=Y; z=Z; c=C; return *this; }

    // Assignment operators

    inline iflXYZC& operator= (const iflXYZC& that);
    inline iflXYZC& operator+=(const iflXYZC& that);
    inline iflXYZC& operator-=(const iflXYZC& that);
    inline iflXYZC& operator*=(const iflXYZC& that);
    inline iflXYZC& operator/=(const iflXYZC& that);
    inline iflXYZC& operator%=(const iflXYZC& that);
    inline iflXYZC& operator&=(const iflXYZC& that);
    inline iflXYZC& operator|=(const iflXYZC& that);

    // Comparison operators

    inline int operator==(const iflXYZC& that) const;
    inline int operator!=(const iflXYZC& that) const;
    inline int operator<=(const iflXYZC& that) const;
    inline int operator>=(const iflXYZC& that) const;
    inline int operator<(const iflXYZC& that) const;
    inline int operator>(const iflXYZC& that) const;

    // Componentwise arithmetic operators

    inline iflXYZC operator+(const iflXYZC& that) const;
    inline iflXYZC operator-(const iflXYZC& that) const;
    inline iflXYZC operator*(const iflXYZC& that) const;
    inline iflXYZC operator/(const iflXYZC& that) const;
    inline iflXYZC operator%(const iflXYZC& that) const;
    inline iflXYZC operator&(const iflXYZC& that) const;
    inline iflXYZC operator|(const iflXYZC& that) const;

    // Indexed member access

    T& operator[](iflAxis axis) { return ((T*) this)[int(axis)]; }
};

// Arithmetic ops that take a scalar and a vector and return a vector...
template <class T> inline iflXYZC<T> operator+(const iflXYZC<T>&, T s);
template <class T> inline iflXYZC<T> operator-(const iflXYZC<T>&, T s);
template <class T> inline iflXYZC<T> operator*(const iflXYZC<T>&, T s);
template <class T> inline iflXYZC<T> operator/(const iflXYZC<T>&, T s);
template <class T> inline iflXYZC<T> operator%(const iflXYZC<T>&, T s);
template <class T> inline iflXYZC<T> operator&(const iflXYZC<T>&, T s);
template <class T> inline iflXYZC<T> operator|(const iflXYZC<T>&, T s);
template <class T> inline iflXYZC<T> operator+(T s, const iflXYZC<T>&);
template <class T> inline iflXYZC<T> operator-(T s, const iflXYZC<T>&);
template <class T> inline iflXYZC<T> operator*(T s, const iflXYZC<T>&);
template <class T> inline iflXYZC<T> operator/(T s, const iflXYZC<T>&);
template <class T> inline iflXYZC<T> operator%(T s, const iflXYZC<T>&);
template <class T> inline iflXYZC<T> operator&(T s, const iflXYZC<T>&);
template <class T> inline iflXYZC<T> operator|(T s, const iflXYZC<T>&);
// Dot product
template<class T> inline T iflDot(const iflXYZC<T>& a, const iflXYZC<T>& b);


// Define specific types such as iflXYchar, iflXYZCint
// for ease of typing...
#define _DEFINEOBJS(type) \
    typedef iflXY<type>    iflCAT2(iflXY,type); \
    typedef iflXYZ<type>   iflCAT2(iflXYZ,type); \
    typedef iflXYZC<type>  iflCAT2(iflXYZC,type); \
    typedef iflXYS<type>   iflCAT2(iflXYS,type); \
    typedef iflXYZS<type>  iflCAT2(iflXYZS,type); \
    typedef iflXYZCS<type> iflCAT2(iflXYZCS,type);
#else /* !__cplusplus */
#define _DEFINEOBJS(type) \
    typedef struct iflCAT2(iflXY,type) { type x, y; } iflCAT2(iflXY,type); \
    typedef struct iflCAT2(iflXYZ,type) { type x, y, z; } iflCAT2(iflXYZ,type); \
    typedef struct iflCAT2(iflXYZC,type) { type x, y, z, c; } iflCAT2(iflXYZC,type);
#endif /* !__cplusplus */

_DEFINEOBJS(char)
_DEFINEOBJS(int)
_DEFINEOBJS(float)
_DEFINEOBJS(double)

#undef _DEFINEOBJS

/*
 *          (end of API -- the rest of this file is implementation) 
 * ============================================================================
 */

#ifdef __cplusplus
// Macros to help with implementations...
#define _XY_OP(RETURNTYPE, OP, SEP, RETURNCAST, CONSTMAYBE) \
    template<class T> inline \
    RETURNTYPE iflXY<T>::operator OP(const iflXY<T>& that) CONSTMAYBE\
    { \
	return RETURNCAST((x OP that.x) \
		      SEP (y OP that.y)); \
    }
#define _XYZ_OP(RETURNTYPE, OP, SEP, RETURNCAST, CONSTMAYBE) \
    template<class T> inline \
    RETURNTYPE iflXYZ<T>::operator OP(const iflXYZ<T>& that) CONSTMAYBE\
    { \
	return RETURNCAST((x OP that.x) \
		      SEP (y OP that.y) \
		      SEP (z OP that.z)); \
    }
#define _XYZC_OP(RETURNTYPE, OP, SEP, RETURNCAST, CONSTMAYBE) \
    template<class T> inline \
    RETURNTYPE iflXYZC<T>::operator OP(const iflXYZC<T>& that) CONSTMAYBE\
    { \
	return RETURNCAST((x OP that.x) \
		      SEP (y OP that.y) \
		      SEP (z OP that.z) \
		      SEP (c OP that.c)); \
    }
#define _SCALAROPS(CLASS, OP) \
    template <class T> inline CLASS<T> operator OP(const CLASS<T>& obj, T s) \
	{ return obj OP CLASS<T>(s); } \
    template <class T> inline CLASS<T> operator OP(T s, const CLASS<T>& obj) \
	{ return CLASS<T>(s) OP obj; }

// Implementations...

#define __COMMA ,

_XY_OP(iflXY<T>&, =,  __COMMA, init, )
_XY_OP(iflXY<T>&, +=, __COMMA, init, )
_XY_OP(iflXY<T>&, -=, __COMMA, init, )
_XY_OP(iflXY<T>&, *=, __COMMA, init, )
_XY_OP(iflXY<T>&, /=, __COMMA, init, )
_XY_OP(iflXY<T>&, %=, __COMMA, init, )
_XY_OP(iflXY<T>&, &=, __COMMA, init, )
_XY_OP(iflXY<T>&, |=, __COMMA, init, )
_XY_OP(int, ==, &&, , const)
_XY_OP(int, !=, ||, , const)
_XY_OP(int, <=, &&, , const)
_XY_OP(int, >=, &&, , const)
_XY_OP(int, <,  &&, , const)
_XY_OP(int, >,  &&, , const)
_XY_OP(iflXY<T>, +, __COMMA, iflXY<T>, const)
_XY_OP(iflXY<T>, -, __COMMA, iflXY<T>, const)
_XY_OP(iflXY<T>, *, __COMMA, iflXY<T>, const)
_XY_OP(iflXY<T>, /, __COMMA, iflXY<T>, const)
_XY_OP(iflXY<T>, %, __COMMA, iflXY<T>, const)
_XY_OP(iflXY<T>, &, __COMMA, iflXY<T>, const)
_XY_OP(iflXY<T>, |, __COMMA, iflXY<T>, const)
_SCALAROPS(iflXY, +)
_SCALAROPS(iflXY, -)
_SCALAROPS(iflXY, *)
_SCALAROPS(iflXY, /)
_SCALAROPS(iflXY, %)
_SCALAROPS(iflXY, &)
_SCALAROPS(iflXY, |)
template<class T> inline T iflDot(const iflXY<T>& a, const iflXY<T>& b)
    { return a.x*b.x + a.y*b.y; }
template<class T> inline iflXY<T> iflCross(const iflXY<T>& a)
    { return iflXY<T>(-a.y, a.x); }

_XYZ_OP(iflXYZ<T>&, =,  __COMMA, init, )
_XYZ_OP(iflXYZ<T>&, +=, __COMMA, init, )
_XYZ_OP(iflXYZ<T>&, -=, __COMMA, init, )
_XYZ_OP(iflXYZ<T>&, *=, __COMMA, init, )
_XYZ_OP(iflXYZ<T>&, /=, __COMMA, init, )
_XYZ_OP(iflXYZ<T>&, %=, __COMMA, init, )
_XYZ_OP(iflXYZ<T>&, &=, __COMMA, init, )
_XYZ_OP(iflXYZ<T>&, |=, __COMMA, init, )
_XYZ_OP(int, ==, &&, , const)
_XYZ_OP(int, !=, ||, , const)
_XYZ_OP(int, <=, &&, , const)
_XYZ_OP(int, >=, &&, , const)
_XYZ_OP(int, <,  &&, , const)
_XYZ_OP(int, >,  &&, , const)
_XYZ_OP(iflXYZ<T>, +, __COMMA, iflXYZ<T>, const)
_XYZ_OP(iflXYZ<T>, -, __COMMA, iflXYZ<T>, const)
_XYZ_OP(iflXYZ<T>, *, __COMMA, iflXYZ<T>, const)
_XYZ_OP(iflXYZ<T>, /, __COMMA, iflXYZ<T>, const)
_XYZ_OP(iflXYZ<T>, %, __COMMA, iflXYZ<T>, const)
_XYZ_OP(iflXYZ<T>, &, __COMMA, iflXYZ<T>, const)
_XYZ_OP(iflXYZ<T>, |, __COMMA, iflXYZ<T>, const)
_SCALAROPS(iflXYZ, +)
_SCALAROPS(iflXYZ, -)
_SCALAROPS(iflXYZ, *)
_SCALAROPS(iflXYZ, /)
_SCALAROPS(iflXYZ, %)
_SCALAROPS(iflXYZ, &)
_SCALAROPS(iflXYZ, |)
template<class T> inline T iflDot(const iflXYZ<T>& a, const iflXYZ<T>& b)
    { return a.x*b.x + a.y*b.y + a.z*b.z; }
template<class T> 
inline iflXYZ<T> iflCross(const iflXYZ<T>& a, const iflXYZ<T>& b)
    { return iflXYZ<T>(a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x); }

_XYZC_OP(iflXYZC<T>&, =,  __COMMA, init, )
_XYZC_OP(iflXYZC<T>&, +=, __COMMA, init, )
_XYZC_OP(iflXYZC<T>&, -=, __COMMA, init, )
_XYZC_OP(iflXYZC<T>&, *=, __COMMA, init, )
_XYZC_OP(iflXYZC<T>&, /=, __COMMA, init, )
_XYZC_OP(iflXYZC<T>&, %=, __COMMA, init, )
_XYZC_OP(iflXYZC<T>&, &=, __COMMA, init, )
_XYZC_OP(iflXYZC<T>&, |=, __COMMA, init, )
_XYZC_OP(int, ==, &&, , const)
_XYZC_OP(int, !=, ||, , const)
_XYZC_OP(int, <=, &&, , const)
_XYZC_OP(int, >=, &&, , const)
_XYZC_OP(int, <,  &&, , const)
_XYZC_OP(int, >,  &&, , const)
_XYZC_OP(iflXYZC<T>, +, __COMMA, iflXYZC<T>, const)
_XYZC_OP(iflXYZC<T>, -, __COMMA, iflXYZC<T>, const)
_XYZC_OP(iflXYZC<T>, *, __COMMA, iflXYZC<T>, const)
_XYZC_OP(iflXYZC<T>, /, __COMMA, iflXYZC<T>, const)
_XYZC_OP(iflXYZC<T>, %, __COMMA, iflXYZC<T>, const)
_XYZC_OP(iflXYZC<T>, &, __COMMA, iflXYZC<T>, const)
_XYZC_OP(iflXYZC<T>, |, __COMMA, iflXYZC<T>, const)
_SCALAROPS(iflXYZC, +)
_SCALAROPS(iflXYZC, -)
_SCALAROPS(iflXYZC, *)
_SCALAROPS(iflXYZC, /)
_SCALAROPS(iflXYZC, %)
_SCALAROPS(iflXYZC, &)
_SCALAROPS(iflXYZC, |)
template<class T> inline T iflDot(const iflXYZC<T>& a, const iflXYZC<T>& b)
    { return a.x*b.x + a.y*b.y + a.z*b.z + a.c*b.c; }

#undef _XY_OP
#undef _XYZ_OP
#undef _XYZC_OP
#undef _SCALAROPS

#endif /* __cplusplus */

#ifdef FOR_IMGTCL
struct iflXYchar	{ char   x, y; };
struct iflXYint		{ int    x, y; };
struct iflXYfloat	{ float  x, y; };
struct iflXYdouble	{ double x, y; };
struct iflXYZchar	{ char   x, y, z; };
struct iflXYZint	{ int    x, y, z; };
struct iflXYZfloat	{ float  x, y, z; };
struct iflXYZdouble	{ double x, y, z; };
struct iflXYZCchar	{ char   x, y, z, c; };
struct iflXYZCint	{ int    x, y, z, c; };
struct iflXYZCfloat	{ float  x, y, z, c; };
struct iflXYZCdouble	{ double x, y, z, c; };
#endif

#undef __COMMA

#endif
