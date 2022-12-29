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
#ifndef _iflTile_h_
#define _iflTile_h_

/*
 * This header defines classes for two- and three-dimensional tiles,
 * (x,y) to (x+nx,y+ny) and (x,y,z) to (x+nx,y+ny,z+nz) respectively.  We
 * use C++ templates in order to support this with arbitrary arithmetic
 * types.
 *
 * As a backwards compatibility sop for IL 2.4 we declare iflTile and
 * iflTileFloat as three-dimensional int and float tiles respectively.  Also,
 * for C and TCL we simply declare two- and three-dimensional int and float
 * structs.
 */

#if defined(__cplusplus)

#include <ifl/iflMinMax.h>
#include <ifl/iflCoord.h>
#include <ifl/iflTypes.h>

// iflTile2D<tileType> is a two-dimensional tile (x,y) to (x+nx,y+ny) for
// type "tileType".
template<class tileType> class iflTile2D {

public:
    tileType x, y;			
    tileType nx, ny;

    // Constructors

    iflTile2D() {}
    iflTile2D(tileType x, tileType y, tileType nx, tileType ny)
	{ init(x, y, nx, ny); }
    iflTile2D(const iflTile2D& that)
	{ init(that); }
    iflTile2D(const iflTile2D& a, const iflTile2D& b)
	{ intersect(a, b); }
    iflTile2D(const iflTile2D& a, const iflTile2D& b, const iflTile2D& c)
	{ intersect(a, b, c); }

    // Initialization

    iflTile2D& init(tileType X, tileType Y, tileType Nx, tileType Ny)
	{ x = X; y = Y; nx = Nx; ny = Ny; return *this; }
    iflTile2D& init(const iflTile2D& tile)
	{ x = tile.x; nx = tile.nx; y = tile.y; ny = tile.ny; return *this; }

    // Intersection

    iflTile2D& intersect(const iflTile2D& a, const iflTile2D& b)
    {
	x = iflMax(a.x, b.x);
	nx = iflMin(a.x+a.nx, b.x+b.nx) - x;
	y = iflMax(a.y, b.y);
	ny = iflMin(a.y+a.ny, b.y+b.ny) - y;
	return *this;
    }
    iflTile2D& intersect(const iflTile2D& a, const iflTile2D& b, 
			 const iflTile2D& c)
    {
	x = iflMax(a.x, b.x, c.x);
	nx = iflMin(a.x+a.nx, b.x+b.nx, c.x+c.nx) - x;
	y = iflMax(a.y, b.y, c.y);
	ny = iflMin(a.y+a.ny, b.y+b.ny, c.y+c.ny) - y;
	return *this;
    }
    
    // Bounding box

    iflTile2D& boundingBox(const iflTile2D& a, const iflTile2D& b)
    {
	x = iflMin(a.x, b.x);
	nx = iflMax(a.x+a.nx, b.x+b.nx) - x;
	y = iflMin(a.y, b.y);
	ny = iflMax(a.y+a.ny, b.y+b.ny) - y;
	return *this;
    }
    iflTile2D& boundingBox(const iflTile2D& a, const iflTile2D& b, 
			   const iflTile2D& c)
    {
	x = iflMin(a.x, b.x, c.x);
	nx = iflMax(a.x+a.nx, b.x+b.nx, c.x+c.nx) - x;
	y = iflMin(a.y, b.y, c.y);
	ny = iflMax(a.y+a.ny, b.y+b.ny, c.y+c.ny) - y;
	return *this;
    }

    // Checking for containment

    int contains(tileType X, tileType Y) const
	{ return x <= X && X <= x+nx && y <= Y && Y <= y+ny; }
    int contains(const iflTile2D& tile) const
    { 
	return x <= tile.x && tile.x+tile.nx <= x+nx &&
	       y <= tile.y && tile.y+tile.ny <= y+ny; 
    }
    int contains(const iflTile2D& tile, tileType xMax, tileType yMax) const
    { 
	return x <= tile.x && (tile.x+tile.nx <= x+nx || xMax <= x+nx) &&
	       y <= tile.y && (tile.y+tile.ny <= y+ny || yMax <= y+ny); 
    }

    // Comparison operators

    int operator==(const iflTile2D& tile) const
	{ return x == tile.x && tile.nx == nx && y == tile.y && tile.ny == ny; }

    int operator!=(const iflTile2D& tile) const
	{ return x != tile.x || tile.nx != nx || y != tile.y || tile.ny != ny; }
	
    // Offsetting and growing

    void operator+=(const iflXY<tileType>& offset) 
	{ x += offset.x; y += offset.y; }

    void operator-=(const iflXY<tileType>& offset) 
	{ x -= offset.x; y -= offset.y; }

    void grow(const iflXY<tileType>& delta)
	{ nx += delta.x; ny += delta.y; }

    void shrink(const iflXY<tileType>& delta)
	{ nx -= delta.x; ny -= delta.y; }

    // Indexed member access
    
    tileType& origin(iflAxis axis)
        { return axis == iflX? x : y; }

    tileType& size(iflAxis axis)
        { return axis == iflX? nx : ny; }
};


// iflTile3D<tileType> is a three-dimensional tile (x,y,z) to
// (x+nx,y+ny,z+nz) for type "tileType".
template<class tileType> class iflTile3D : public iflTile2D<tileType> {

public:
    tileType z;
    tileType nz;

    // Constructors

    iflTile3D() {}
    iflTile3D(tileType x, tileType y, tileType z,
	      tileType nx, tileType ny, tileType nz)
	{ init(x, y, z, nx, ny, nz); }
    iflTile3D(const iflTile3D& that)
	{ init(that); }
    iflTile3D(const iflTile2D<tileType>& that, tileType z=0, tileType nz=1)
	{ init(that, z, nz); }
    iflTile3D(const iflTile3D& a, const iflTile3D& b)
	{ intersect(a, b); }
    iflTile3D(const iflTile3D& a, const iflTile3D& b, const iflTile3D& c)
	{ intersect(a, b, c); }

    // Initialization

    iflTile3D& init(tileType X, tileType Y, tileType Z,
		    tileType Nx, tileType Ny, tileType Nz)
    {
	iflTile2D<tileType>::init(X, Y, Nx, Ny);
	z = Z; nz = Nz;
	return *this;
    }
    iflTile3D& init(const iflTile3D& tile)
    {
	iflTile2D<tileType>::init(tile);
	z = tile.z; nz = tile.nz;
	return *this;
    }
    iflTile3D& init(const iflTile2D<tileType>& tile, tileType Z=0, 
		    tileType Nz=1)
    {
	iflTile2D<tileType>::init(tile);
	z = Z; nz = Nz;
	return *this;
    }

    // Intersection

    iflTile3D& intersect(const iflTile3D& a, const iflTile3D& b)
    {
	iflTile2D<tileType>::intersect(a, b);
	z = iflMax(a.z, b.z);
	nz = iflMin(a.z+a.nz, b.z+b.nz) - z;
	return *this;
    }
    iflTile3D& intersect(const iflTile3D& a, const iflTile3D& b, 
			 const iflTile3D& c)
    {
	iflTile2D<tileType>::intersect(a, b, c);
	z = iflMax(a.z, b.z, c.z);
	nz = iflMin(a.z+a.nz, b.z+b.nz, c.z+c.nz) - z;
	return *this;
    }
    
    // Bounding box

    iflTile3D& boundingBox(const iflTile3D& a, const iflTile3D& b)
    {
	iflTile2D<tileType>::boundingBox(a, b);
	z = iflMin(a.z, b.z);
	nz = iflMax(a.z+a.nz, b.z+b.nz) - z;
	return *this;
    }
    iflTile3D& boundingBox(const iflTile3D& a, const iflTile3D& b, 
			   const iflTile3D& c)
    {
	iflTile2D<tileType>::boundingBox(a, b, c);
	z = iflMin(a.z, b.z, c.z);
	nz = iflMax(a.z+a.nz, b.z+b.nz, c.z+c.nz) - z;
	return *this;
    }

    // Checking for containment

    int contains(tileType X, tileType Y, tileType Z) const
    { 
	return iflTile2D<tileType>::contains(X, Y) &&
	       z <= Z && Z <= z+nz; 
    }
    int contains(const iflTile3D& tile) const
    { 
	return iflTile2D<tileType>::contains(tile) &&
	       z <= tile.z && tile.z+tile.nz <= z+nz; 
    }
    int contains(const iflTile3D& tile,
		 tileType xMax, tileType yMax, tileType zMax) const
    { 
	return iflTile2D<tileType>::contains(tile, xMax, yMax) &&
	       z <= tile.z && (tile.z+tile.nz <= z+nz || zMax <= z+nz); 
    }

    // Comparison operators

    int operator==(const iflTile3D& tile) const
    { 
	return iflTile2D<tileType>::operator==(tile) &&
	       z == tile.z && tile.nz == nz; 
    }

    int operator!=(const iflTile3D& tile) const
    { 
	return iflTile2D<tileType>::operator!=(tile) ||
	       z != tile.z || tile.nz != nz; 
    }
	
    // Offsetting and growing

    void operator+=(const iflXY<tileType>& offset) 
	{ x += offset.x; y += offset.y; }
    void operator+=(const iflXYZ<tileType>& offset) 
	{ x += offset.x; y += offset.y; z += offset.z; }

    void operator-=(const iflXY<tileType>& offset) 
	{ x -= offset.x; y -= offset.y; }
    void operator-=(const iflXYZ<tileType>& offset) 
	{ x -= offset.x; y -= offset.y; z += offset.z; }

    void grow(const iflXYZ<tileType>& delta)
	{ nx += delta.x; ny += delta.y; nz += delta.z; }
    void grow(const iflXY<tileType>& delta)
	{ nx += delta.x; ny += delta.y; }

    void shrink(const iflXY<tileType>& delta)
	{ nx -= delta.x; ny -= delta.y; }
    void shrink(const iflXYZ<tileType>& delta)
	{ nx -= delta.x; ny -= delta.y; nz -= delta.z; }

    // Copying

    iflTile3D& operator=(const iflTile2D<tileType>& tile)
	{ init(tile); return *this; }
    iflTile3D& operator=(const iflTile3D& tile)
	{ init(tile); return *this; }

    // Indexed member access
    
    tileType& origin(iflAxis axis) 
        { return axis == iflX? x : axis == iflY? y : z; }

    tileType& size(iflAxis axis)
        { return axis == iflX? nx : axis == iflY? ny : nz; }
};

/* backwards compatibility for IL 2.4 */
typedef iflTile3D<int>   iflTile;
typedef iflTile3D<float> iflTileFloat;

/* non-template versions (for external api usage) */
typedef iflTile2D<int> iflTile2Dint;
typedef iflTile2D<float> iflTile2Dfloat;
typedef iflTile3D<int> iflTile3Dint;
typedef iflTile3D<float> iflTile3Dfloat;

#else /* _cplusplus */

/*
 * Foreign language interfaces.
 */
struct iflTile2Dint { int   x, y,    nx, ny;     };
struct iflTile2Dfloat { float x, y,    nx, ny;     };
struct iflTile3Dint { int   x, y, z, nx, ny, nz; };
struct iflTile3Dfloat { float x, y, z, nx, ny, nz; };
typedef struct iflTile2Dint iflTile2Dint;
typedef struct iflTile2Dfloat iflTile2Dfloat;
typedef struct iflTile3Dint iflTile3Dint;
typedef struct iflTile3Dfloat iflTile3Dfloat;

/* backwards compatibility for IL 2.4 */
typedef struct iflTile3DInt   iflTile;
typedef struct iflTile3DFloat iflTileFloat;

#endif /* !__cplusplus */

#endif
