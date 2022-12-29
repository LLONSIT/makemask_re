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
 |   $Revision: 2.8 $
 |
 |   Description:
 |	This file defines the SoMaterialBundle class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_MATERIAL_BUNDLE
#define  _SO_MATERIAL_BUNDLE

#include <Inventor/bundles/SoBundle.h>

class SoGLLazyElement;


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoMaterialBundle
//
//  Bundle that allows shapes to deal with materials more easily.
//  Since materials deal with several elements simultaneously, this
//  bundle hides a lot of this work from shapes.
//
//  Much of the functionality of this bundle has been replaced by the
//  SoLazyElement. 
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SoMaterialBundle : public SoBundle {

  public:
    // Constructor - takes the action the bundle is used for
    SoMaterialBundle(SoAction *action);

    // Destructor
    ~SoMaterialBundle();

    // This can be called by shapes to prepare for sending multiple
    // materials later on. It is not required, since all of the send
    // methods call it if necessary. However, it allows the bundle to
    // set up some optimizations that are not possible to do later on.
    // This should never be called between calls to glBegin() and
    // glEnd().
    void		setUpMultiple()	   
	    { accessElements(FALSE, FALSE);
	      sendMultiple = TRUE; }

    // Makes sure the first defined material in the state is sent to
    // GL. This should never be called between calls to glBegin() and
    // glEnd().
    void		sendFirst()		{ send(0, FALSE); }

    // Sends indexed material to the GL if it's not already there.
    // The second paramater should be TRUE if this send is between a
    // glBegin() and glEnd() call, in which case the stipple pattern
    // commands for screen-door transparency won't be sent.
    void		send(int index, SbBool isBetweenBeginEnd)
	{  reallySend(index, isBetweenBeginEnd, FALSE);  }
	    
    // Sends indexed material to the GL even if it's already there.
    // This method can be used by SoMaterial and related nodes to send
    // the base material to the GL to avoid cache dependencies on materials.
    void		forceSend(int index)
	{ reallySend(index, FALSE, TRUE); }

    // Returns TRUE if only base color part of material is used
    SbBool		isColorOnly() const	{ return colorOnly; }

  private:
    SbBool		firstTime;	// TRUE if nothing sent yet
    int			lastIndex;	// Last index reallySend()ed
    SbBool		colorOnly;	// TRUE if only base color sent
    SbBool		fastColor;	// TRUE if can send color for diffColor
    int			numMaterials;	// Number of materials 
    SbBool		sendMultiple;	// indicates multiple diffuse are sent.

    // Material component elements:
    const SoGLLazyElement		*lazyElt;

    // Really sends stuff to GL
    void		reallySend(int index, SbBool isBetweenBeginEnd,
				   SbBool avoidFastColor);

    // Accesses and stores pointers to necessary elements
    void		accessElements(SbBool isBetweenBeginEnd,
				       SbBool avoidFastColor);
};

#endif /* _SO_MATERIAL_BUNDLE */
