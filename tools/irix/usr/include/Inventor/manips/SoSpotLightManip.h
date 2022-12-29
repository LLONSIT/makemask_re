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
////////////////////////////////////////////////////////////////////////
//
// Description:
//	This file defines a manipulator for a spot light nodes.
//      It is subclassed from SoSpotLight.
//
////////////////////////////////////////////////////////////////////////

 
#ifndef  _SO_SPOT_LIGHT_MANIP_
#define  _SO_SPOT_LIGHT_MANIP_

#include <Inventor/SbLinear.h>
#include <Inventor/draggers/SoDragger.h>
#include <Inventor/nodes/SoSpotLight.h>
#include <Inventor/sensors/SoFieldSensor.h>

class SoSpotLightManip : public SoSpotLight
{
    SO_NODE_HEADER(SoSpotLightManip);

  public:
    // Constructors
    SoSpotLightManip();

    SoDragger *getDragger();

    SbBool replaceNode( SoPath *p );
    SbBool replaceManip(SoPath *p, SoSpotLight *newOne ) const;

  SoEXTENDER public:

    // These functions implement all actions for nodekits.
    // They first traverse the children, then use the SoSpotLight
    // version of the actions. They traverse first so that the light
    // will affect objects which follow it in the tree, but not the
    // dragger-child.
    virtual void doAction( SoAction *action );
    virtual void callback( SoCallbackAction *action );
    virtual void GLRender( SoGLRenderAction *action );
    virtual void getBoundingBox( SoGetBoundingBoxAction *action );
    virtual void getMatrix(SoGetMatrixAction *action );
    virtual void handleEvent( SoHandleEventAction *action );
    virtual void pick( SoPickAction *action );
    virtual void search( SoSearchAction *action );

  SoINTERNAL public:

    static void initClass();

    virtual SoChildList *getChildren() const;

  protected:

    // Redefines this to also copy the dragger
    virtual void	copyContents(const SoFieldContainer *fromFC,
				     SbBool copyConnections);

    static void transferFieldValues( const SoSpotLight *from, 
				    SoSpotLight *to);

    SoFieldSensor *locationFieldSensor;
    SoFieldSensor *directionFieldSensor;
    SoFieldSensor *angleFieldSensor;
    SoFieldSensor *colorFieldSensor;
    static void fieldSensorCB(void *, SoSensor *);
    static void valueChangedCB(void *,SoDragger *);

    void setDragger( SoDragger *newDragger );

    SoChildList *children;

    virtual ~SoSpotLightManip();

  private:
    int getNumChildren() const { return (children->getLength()); }
};    

#endif  /* _SO_SPOT_LIGHT_MANIP_ */
