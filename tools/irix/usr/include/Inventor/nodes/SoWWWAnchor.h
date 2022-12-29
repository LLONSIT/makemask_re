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
 |   $Revision: 1.13 $
 |
 |   Description:
 |	Defines the SoWWWAnchor class
 |
 |   Author(s): David Mott, Jim Kent, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_WWWANCHOR_
#define  _SO_WWWANCHOR_

#include <Inventor/fields/SoSFString.h>
#include <Inventor/nodes/SoLocateHighlight.h>

class SoWWWAnchor;

// This is the format for callbacks during anchor activation (left mouse click)
// and highlight (move over the anchor).
// The URL for the anchor is passed, with additional information as described by the
// map field tagged onto the URL.
typedef void SoWWWAnchorCB(
    const SbString &url, void *userData, SoWWWAnchor *node);


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoWWWAnchor
//
//////////////////////////////////////////////////////////////////////////////

class SoWWWAnchor : public SoLocateHighlight {

    SO_NODE_HEADER(SoWWWAnchor);

  public:
    // Constructor
    SoWWWAnchor();

    enum Mapping {
	NONE,		    // Do no add information to the URL
	POINT		    // Add object-space coordinates to URL
    };

    // Fields
    SoSFString	name;	     // URL to fetch when activated by mouse click
    SoSFString	description; // Description of the URL that will be grabbed
    SoSFEnum	map;	     // What additional info to add to the URL
    
    // If the name field contains a relative URL (e.g. "foo.wrl" 
    // instead of "http://bogus.com/foo.wrl"), the anchor cannot 
    // resolve the URL reference. This method allows the application 
    // to tell the anchor what it's full URL should be. 
    // getFullURLName returns the fullURL set here, or if not set, returns 
    // the contents of the name field.
    void		setFullURLName(const SbString &url) { fullURL = url; }
    const SbString &	getFullURLName();

    // Application callbacks invoked when the mouse is clicked on an 
    // anchor (activate) so that the app can fetch the URL or call
    // netscape/mosaic to fetch the URL.
    static void setFetchURLCallBack( 
        SoWWWAnchorCB *f, void *userData); 

    // Application callbacks invoked when the mouse is moved over an
    // anchor so that the app can provide feedback such as changing the
    // cursor, or displaying the anchor description or URL.
    static void setHighlightURLCallBack(
	SoWWWAnchorCB *f, void *userData);

  SoEXTENDER public:
    // Override handleEvent to look for left-mouse clicks, to do a
    // pick:
    virtual void	handleEvent(SoHandleEventAction *action);

  SoINTERNAL public:
    static void		initClass();

  protected:
    virtual ~SoWWWAnchor();
    
    // redefine this to also invoke the app callbacks...
    // This is called when the locate highlight status of this node changes.
    virtual void	redrawHighlighted(SoAction *act, SbBool isNowHighlighting);

    static SoWWWAnchorCB	    *fetchURLcb;
    static void			    *fetchURLdata;
    static SoWWWAnchorCB	    *highlightURLcb;
    static void			    *highlightURLdata;
    static SbString		    emptyString;
  
  private:  
    SbString			    fullURL;
};

#endif /* _SO_WWWANCHOR_ */
