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
 |   $Revision: 2.0 $
 |
 |   Description:
 |	This class provides an easy to use interface to get X resource
 |   values for a widget. Special care is taken for SoComponents. 
 |
 |   Author(s): David Mott
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef _SO_XTRESOURCE_
#define _SO_XTRESOURCE_

#include <X11/Intrinsic.h>
#include <X11/Xresource.h>
#include <Inventor/SbBasic.h>
#include <Inventor/SbColor.h>

class SoXtResource {
  public:
    // pass in the widget for which X resource values are desired
    SoXtResource(Widget w);
    ~SoXtResource();
    
    //
    // These methods look up X resource values by calling XrmQGetResource.
    // They return TRUE if successfully located the resource.
    //
    // NOTE: you do not have to specify the complete widget hierarchy.
    // This is automatically performed by this class. Simply name the
    // specific resource that should be searched for. The most efficient
    // use of this class is to construct an instance for a widget, then 
    // call getResource repeatedly with different resource strings which
    // are valid for the widget.
    //
    // For example:
    //	  SoXtResource xr(colorEditor->getWidget());
    //	  xr.getResource("wysiwyg", "Wysiwyg", onOrOff);
    //	  xr.getResource("colorSliders", "ColorSliders", rgbOrHsv);
    //	  xr.getResource("updateFrequency", "UpdateFrequency", freq);
    
    SbBool   	getResource(char *resName, char *resClass, SbColor &c);
    SbBool   	getResource(char *resName, char *resClass, short &i);
    SbBool   	getResource(char *resName, char *resClass, unsigned short &u);
    SbBool   	getResource(char *resName, char *resClass, char *&s);
    SbBool   	getResource(char *resName, char *resClass, SbBool &b);
    SbBool   	getResource(char *resName, char *resClass, float &f);

  private:
    XrmQuarkList    nameList;
    XrmQuarkList    classList;
    int	    	    listSize;
    Display	    *display;

    // These methods look up X resource values by calling XrmGetResource.
    // e.g. getResource("*backgroundColor", "*BackgroundColor", c);
    // They return TRUE if successfully located the resource.
    
    static SbBool getResource(Display *, char *sName, char *sClass, SbColor &c);
    static SbBool getResource(Display *, char *sName, char *sClass, short &i);
    static SbBool getResource(Display *, char *sName, char *sClass, unsigned short &u);
    static SbBool getResource(Display *, char *sName, char *sClass, char *&s);
    static SbBool getResource(Display *, char *sName, char *sClass, SbBool &b);
    static SbBool getResource(Display *, char *sName, char *sClass, float &f);


    // These methods look up X resource values by calling XrmQGetResource.
    // That is, they use XrmQuarks instead of strings. (A quark is an Xrm
    // notion - it is simply a key into a hash table of strings.)
    // They are used by SoXtResource for SoComponents.
    // They return TRUE if successfully located the resource.
    
    static SbBool getResource(Display *, XrmQuarkList qName, XrmQuarkList qClass, SbColor &c);
    static SbBool getResource(Display *, XrmQuarkList qName, XrmQuarkList qClass, short &i);
    static SbBool getResource(Display *, XrmQuarkList qName, XrmQuarkList qClass, unsigned short &u);
    static SbBool getResource(Display *, XrmQuarkList qName, XrmQuarkList qClass, char *&s);
    static SbBool getResource(Display *, XrmQuarkList qName, XrmQuarkList qClass, SbBool &b);
    static SbBool getResource(Display *, XrmQuarkList qName, XrmQuarkList qClass, float &f);
};

#endif /* _SO_XTRESOURCE_ */
