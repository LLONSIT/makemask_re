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
 |	This file contains definitions of SbBoxes, 2D/3D boxes. A
 |	box has planes parallel to the major axes and can therefore
 |	be specified by two points on a diagonal.  The points with minimum
 |	and maximum x, y, and z coordinates are used.
 |
 |   Author(s)		: Paul S. Strauss, Nick Thompson, David Mott
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef _SB_BOX_
#define _SB_BOX_

#include <Inventor/SbBasic.h>
#include <Inventor/SbLinear.h>

class SbBox3f {
  public:
    // Default constructor - leaves box totally empty
    SbBox3f()						{ makeEmpty(); }

    // Constructor given bounds 
    SbBox3f(float xmin, float ymin, float zmin,
	    float xmax, float ymax, float zmax)
	{ min.setValue(xmin, ymin, zmin); max.setValue(xmax, ymax, zmax); }

    // Constructor given minimum and maximum points 
    SbBox3f(const SbVec3f &_min, const SbVec3f &_max)
	{ min = _min; max = _max; }

    ~SbBox3f()						{ }

    // Returns the min and max points
    const SbVec3f &	getMin() const { return min; }
    const SbVec3f &	getMax() const { return max; }
    SbVec3f &	        getMin()       { return min; }
    SbVec3f &	        getMax()       { return max; }

    // Returns the center of a box
    SbVec3f	getCenter() const;

    // Extends Box3f (if necessary) to contain given 3D point
    void	extendBy(const SbVec3f &pt);

    // Extends Box3f (if necessary) to contain given Box3f
    void	extendBy(const SbBox3f &bb);

    // Returns TRUE if intersection of given point and Box3f is not empty
    SbBool	intersect(const SbVec3f &pt) const;

    // Returns TRUE if intersection of given Box3f and Box3f is not empty
    SbBool	intersect(const SbBox3f &bb) const;

    // Returns TRUE if bounding box is completely outside the
    // view-volume defined by the model+view+projection matrix given.
    // "cullBits" keeps track of which view-volume clipping planes the
    // box is completely inside of; if a 'parent' bounding box of this
    // bounding box was found to be completely inside the left/right
    // clipping planes, the low bit of cullBits will be set to zero,
    // and this routine will not test this box against those planes.
    // When cullBits is zero, it is a waste of time to call this
    // function!  Before calling this the first time, set cullBits to
    // 7 (SoGLRenderAction and SoSeparator will handle this
    // automatically for render culling).
    SbBool	outside(const SbMatrix &MVP, int &cullBits) const;

    // Common get and set functions
    void	setBounds(float xmin, float ymin, float zmin,
			  float xmax, float ymax, float zmax)
	{ min.setValue(xmin, ymin, zmin); max.setValue(xmax, ymax, zmax); }

    void	setBounds(const SbVec3f &_min, const SbVec3f &_max)
	{ min = _min; max = _max; }

    void	getBounds(float &xmin, float &ymin, float &zmin,
			  float &xmax, float &ymax, float &zmax) const
	{ min.getValue(xmin, ymin, zmin); max.getValue(xmax, ymax, zmax); }

    void	getBounds(SbVec3f &_min, SbVec3f &_max) const
	{ _min = min; _max = max; }

    // Returns the closest point on the box to the given point.
    // (Returns the point on the center of the Z face if passed the center.)
    SbVec3f	getClosestPoint(const SbVec3f &point);
    
    // Returns origin (minimum point) of box
    void	getOrigin(float &originX,
			  float &originY,
			  float &originZ) const
	{ originX = min[0]; originY = min[1]; originZ = min[2]; }

    // Returns size of box
    void	getSize(float &sizeX, float &sizeY, float &sizeZ) const
	{ sizeX = max[0] - min[0];
	  sizeY = max[1] - min[1];
          sizeZ = max[2] - min[2]; }

    // Sets Box3f to contain nothing
    void	makeEmpty();

    // Checks if the box is empty (degenerate)
    // note that this relies on boxes being completely degenerate if
    // they are degenerate at all.  All member functions preserve this
    // invariant.
    SbBool	isEmpty()  const		{ return max[0] < min[0]; }

    // Checks if the box has volume; i.e., all three dimensions have
    // positive size
    SbBool	hasVolume() const
	{ return (max[0] > min[0] && max[1] > min[1] && max[2] > min[2] ); }

    // Finds the extent of a box along a particular direction
    void	getSpan(const SbVec3f &direction,
			float &dMin, float &dMax) const;

    // Transforms Box3f by matrix, enlarging Box3f to contain result
    void	transform(const SbMatrix &m);

    // Gives the volume of the box (0 for an empty box)
    float	getVolume() const;

    // Equality comparisons
    friend int          operator ==(const SbBox3f &b1, const SbBox3f &b2);
    friend int          operator !=(const SbBox3f &b1, const SbBox3f &b2)
	{ return !(b1 == b2); }

  private:
    // Minimum and maximum points
    SbVec3f	min, max;
};

class SbXfBox3f : private SbBox3f {
  public:
    // Default constructor - leaves box totally empty
    SbXfBox3f();

    // Constructor given minimum and maximum points 
    SbXfBox3f(const SbVec3f &_min, const SbVec3f &_max);

    // Constructor given Box3f
    SbXfBox3f(const SbBox3f &box);

    ~SbXfBox3f()						{ }

    // Set the transformation on the box
    void		setTransform(const SbMatrix &m);

    // Get the transformation on the box, and its inverse.
    const SbMatrix &	getTransform() const	    { return xform; }
    const SbMatrix &	getInverse() const	    { return xformInv; }
    
    // Returns the center of a box
    SbVec3f		getCenter() const;

    // Extends XfBox3f (if necessary) to contain given 3D point
    void		extendBy(const SbVec3f &pt);

    // Extends XfBox3f (if necessary) to contain given Box3f
    void		extendBy(const SbBox3f &bb)
	{ extendBy(SbXfBox3f(bb)); }

    // Extends XfBox3f (if necessary) to contain given XfBox3f
    void		extendBy(const SbXfBox3f &bb);

    // Returns TRUE if intersection of given point and Box3f is not empty
    SbBool		intersect(const SbVec3f &pt) const;

    // Returns TRUE if intersection of given XfBox3f and Box3f is not empty
    SbBool		intersect(const SbBox3f &bb) const
	{ return project().intersect(bb); }

    // Common get and set functions
    void	setBounds(float xmin, float ymin, float zmin,
			  float xmax, float ymax, float zmax)
	{ SbBox3f::setBounds(xmin, ymin, zmin, xmax, ymax, zmax); }

    void	setBounds(const SbVec3f &_min, const SbVec3f &_max)
	{ SbBox3f::setBounds(_min, _max); }

    void	getBounds(float &xmin, float &ymin, float &zmin,
			  float &xmax, float &ymax, float &zmax) const
	{ SbBox3f::getBounds(xmin, ymin, zmin, xmax, ymax, zmax); }

    void	getBounds(SbVec3f &_min, SbVec3f &_max) const
	{ SbBox3f::getBounds(_min, _max); }

    // Returns origin (minimum point) of box
    void	getOrigin(float &originX,
			  float &originY,
			  float &originZ)
	{ SbBox3f::getOrigin(originX, originY, originZ); }

    // Returns size of box
    void	getSize(float &sizeX, float &sizeY, float &sizeZ)
	{ SbBox3f::getSize(sizeX, sizeY, sizeZ); }

    // Gives the volume of the box (0 for an empty box)
    float	getVolume() const;

    // Sets Box3f to contain nothing
    void		makeEmpty()		{ SbBox3f::makeEmpty(); }

    // Checks if the box is empty (degenerate)
    // note that this relies on boxes being completely degenerate if
    // they are degenerate at all.  All member functions preserve this
    // invariant.
    SbBool		isEmpty() const	{ return SbBox3f::isEmpty(); }

    // Checks if the box has volume; i.e., all three dimensions have
    // positive size
    SbBool		hasVolume() const { return SbBox3f::hasVolume(); }

    // Finds the extent of a box along a particular direction
    void		getSpan(const SbVec3f &direction,
				float &dMin, float &dMax) const
	{ project().getSpan(direction, dMin, dMax); }

    // Transforms Box3f by matrix
    void		transform(const SbMatrix &m);

    // Projects an SbXfBox3f to an SbBox3f
    SbBox3f		project() const;

    // Equality comparisons
    friend int          operator ==(const SbXfBox3f &b1, const SbXfBox3f &b2);
    friend int          operator !=(const SbXfBox3f &b1, const SbXfBox3f &b2)
	{ return !(b1 == b2); }

  private:
    // These are incorrect for SbXfBox3f, so we hide them
    const SbVec3f &	getMin() const			{ return SbBox3f::getMin(); }
    const SbVec3f &	getMax() const			{ return SbBox3f::getMax(); }

    // The box is transformed by this xform
    SbMatrix		xform;
    SbMatrix		xformInv;
};

class SbBox2f {
  public:
    // Default constructor - leaves box totally empty
    SbBox2f()					{ makeEmpty(); };

    // Constructor given bounds 
    SbBox2f(float xmin, float ymin, float xmax, float ymax)
	{ min.setValue(xmin, ymin); max.setValue(xmax, ymax); }

    // Constructor given minimum and maximum points 
    SbBox2f(const SbVec2f &_min, const SbVec2f &_max)
	{ min = _min; max = _max; }

    ~SbBox2f()						{ }

    // Returns the min and max points
    const SbVec2f &	getMin() const			{ return min; }
    const SbVec2f &	getMax() const			{ return max; }

    // Returns the center of a box
    SbVec2f		getCenter() const;

    // Extends Box2f (if necessary) to contain given 2D point
    void	extendBy(const SbVec2f &pt);

    // Extends Box2f (if necessary) to contain given Box2f
    void	extendBy(const SbBox2f &r);

    // Returns TRUE if intersection of given point and Box2f is not empty
    SbBool	intersect(const SbVec2f &pt) const;

    // Returns TRUE if intersection of given Box2f and Box2f is not empty
    SbBool	intersect(const SbBox2f &bb) const;

    // Common get and set functions
    void	setBounds(float xmin, float ymin, float xmax, float ymax)
	{ min.setValue(xmin, ymin); max.setValue(xmax, ymax); }

    void	setBounds(const SbVec2f &_min, const SbVec2f &_max)
	{ min = _min; max = _max; }

    void	getBounds(float &xmin, float &ymin,
			  float &xmax, float &ymax) const
	{ min.getValue(xmin, ymin); max.getValue(xmax, ymax); }

    void	getBounds(SbVec2f &_min, SbVec2f &_max) const
	{ _min = min; _max = max; }

    // Returns the closest point on the box to the given point.
    // (Returns the point on the center of the X side if passed the center.)
    SbVec2f	getClosestPoint(const SbVec2f &point);
    
    // Returns origin (minimum point) of box
    void	getOrigin(float &originX, float &originY) const
	{ originX = min[0]; originY = min[1]; }

    // Returns size of box
    void	getSize(float &sizeX, float &sizeY) const
	{ sizeX = max[0] - min[0]; sizeY = max[1] - min[1]; }

    // Returns aspect ratio (ratio of width to height) of box
    float	getAspectRatio() const
	{ return (max[0] - min[0]) / (max[1] - min[1]); }

    // Sets rect to contain nothing
    void	makeEmpty();

    // Checks if the box is empty (degenerate)
    // note that this relies on boxes being completely degenerate if
    // they are degenerate at all.  All member functions preserve this
    // invariant.
    SbBool	isEmpty() const		{ return max[0] < min[0]; }

    // Checks if the box has area; i.e., both dimensions have positive size
    SbBool	hasArea() const
	{ return (max[0] > min[0] && max[1] > min[1]); }

    // Equality comparisons
    friend int          operator ==(const SbBox2f &b1, const SbBox2f &b2);
    friend int          operator !=(const SbBox2f &b1, const SbBox2f &b2)
	{ return !(b1 == b2); }

  private:
    // Minimum and maximum points
    SbVec2f	min, max;
};

class SbBox2s {
  public:
    // Default constructor - leaves box totally empty
    SbBox2s()					{ makeEmpty(); };

    // Constructor given bounds 
    SbBox2s(short xmin, short ymin, short xmax, short ymax)
	{ min.setValue(xmin, ymin); max.setValue(xmax, ymax); }

    // Constructor given minimum and maximum points 
    SbBox2s(const SbVec2s &_min, const SbVec2s &_max)
	{ min = _min; max = _max; }

    ~SbBox2s()						{ }

    // Returns the min and max points
    const SbVec2s &	getMin() const			{ return min; }
    const SbVec2s &	getMax() const			{ return max; }

    // Extends Box2s (if necessary) to contain given 2D point
    void	extendBy(const SbVec2s &pt);

    // Extends Box2s (if necessary) to contain given Box2s
    void	extendBy(const SbBox2s &r);

    // Returns TRUE if intersection of given point and Box2s is not empty
    SbBool	intersect(const SbVec2s &pt) const;

    // Returns TRUE if intersection of given Box2s and Box2s is not empty
    SbBool	intersect(const SbBox2s &bb) const;

    // Common get and set functions
    void	setBounds(short xmin, short ymin, short xmax, short ymax)
	{ min.setValue(xmin, ymin); max.setValue(xmax, ymax); }

    void	setBounds(const SbVec2s &_min, const SbVec2s &_max)
	{ min = _min; max = _max; }

    void	getBounds(short &xmin, short &ymin,
			  short &xmax, short &ymax) const
	{ min.getValue(xmin, ymin); max.getValue(xmax, ymax); }

    void	getBounds(SbVec2s &_min, SbVec2s &_max) const
	{ _min = min; _max = max; }

    // Returns origin (minimum point) of box
    void	getOrigin(short &originX, short &originY) const
	{ originX = min[0]; originY = min[1]; }

    // Returns size of box
    void	getSize(short &sizeX, short &sizeY) const
	{ sizeX = max[0] - min[0]; sizeY = max[1] - min[1]; }

    // Returns aspect ratio (ratio of width to height) of box
    float	getAspectRatio() const
	{ return float(max[0] - min[0]) / float(max[1] - min[1]); }

    // Sets rect to contain nothing
    void	makeEmpty();

    // Equality comparisons
    friend int          operator ==(const SbBox2s &b1, const SbBox2s &b2);
    friend int          operator !=(const SbBox2s &b1, const SbBox2s &b2)
	{ return !(b1 == b2); }

  private:
    // Minimum and maximum points
    SbVec2s	min, max;
};

#endif /* _SB_BOX_ */
