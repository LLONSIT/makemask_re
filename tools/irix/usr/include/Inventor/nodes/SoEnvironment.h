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
 |   $Revision $
 |
 |   Description:
 |	This file defines the SoEnvironment node class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_ENVIRONMENT_
#define  _SO_ENVIRONMENT_

#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/nodes/SoSubNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoEnvironment
//
//  Node that describes global environmental attributes such as
//  ambient lighting, light attenuation, and fog.
//
//  Ambient lighting is the amount of extra light impinging on each
//  surface point when computing Phong lighting. 
//
//  Light attenuation affects all subsequent lights in a scene. It is
//  a quadratic function of distance from a light source to a surface
//  point. The three coefficients are specified in the attenuation
//  field. Attenuation works only for light sources with a fixed
//  location, such as point and spot lights.
//
//  Fog has one of four types, each of which blends each surface point
//  with the specified fog color. Each type interprets the visibility
//  field to be the distance at which fog totally obscures objects. A
//  visibility value of 0 (the default) causes the SoEnvironment node
//  to set up fog so that the visibility is the distance to the far
//  clipping plane of the current camera.
//
//  Note that this node has effect only during rendering, and that it
//  does not inherit field values from other SoEnvironment nodes.
//
//////////////////////////////////////////////////////////////////////////////

class SoEnvironment : public SoNode {

    SO_NODE_HEADER(SoEnvironment);

  public:
    enum FogType {	// Type of fog:
	NONE,			// No fog
	HAZE,			// Linear increase in opacity with distance
	FOG,			// Exponential increase in opacity
	SMOKE			// Exponential squared increase in opacity
    };

    // Fields

    // Intensity and RGB color of ambient lighting
    SoSFFloat		ambientIntensity;
    SoSFColor		ambientColor;

    // Squared, linear, and constant light attenuation coefficients
    // (in order) with respect to distance of light from surface (for
    // Phong lighting)
    SoSFVec3f		attenuation;

    // Type of fog, color of fog, and visibility factor. 
    SoSFEnum		fogType;
    SoSFColor		fogColor;
    SoSFFloat		fogVisibility;

    // Constructor
    SoEnvironment();

  SoEXTENDER public:
    virtual void	GLRender(SoGLRenderAction *action);
    virtual void	callback(SoCallbackAction *action);

  SoINTERNAL public:
    static void		initClass();

  protected:
    virtual ~SoEnvironment();

  private:
    // Computes fog density based on visibility
    static float	computeDensity(float visibility, SbBool squared);
};

#endif /* _SO_ENVIRONMENT_ */
