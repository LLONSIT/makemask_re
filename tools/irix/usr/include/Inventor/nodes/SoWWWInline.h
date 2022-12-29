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
 |   $Revision: 1.27 $
 |
 |   Description:
 |	Defines the SoWWWInline class
 |
 |   Author(s): Gavin Bell, David Mott, Jim Kent
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_WWWINLINE_
#define  _SO_WWWINLINE_

#include <Inventor/misc/SoChildList.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFVec3f.h>

#include <Inventor/actions/SoCallbackAction.h>

class SoWWWInline;
class SoGroup;
class SoWriteAction;

// This is the format for callbacks that will get URL data for us.
// Once they get the data, they should call the setChildData() method.
typedef void SoWWWInlineFetchURLCB(
    const SbString &url, void *userData, SoWWWInline *node);
		

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoWWWInline
//
//////////////////////////////////////////////////////////////////////////////

class SoWWWInline : public SoNode {

    SO_NODE_HEADER(SoWWWInline);

  public:
    // Constructor
    SoWWWInline();

    enum BboxVisibility {
	NEVER,             // Do not show bounding box
	UNTIL_LOADED,      // Show bounding box (if specified) until data is loaded
	ALWAYS            // Show bounding box along with data
    };

    SoSFVec3f	bboxCenter;	// Bounding box center
    SoSFVec3f	bboxSize;	// Bounding box size
    SoSFString	name;		// URL specifying children (might be relative)
    SoSFNode	alternateRep;	// Child data if app cannot fetch URL
    
    // If the name field contains a relative URL (e.g. "foo.wrl" 
    // instead of "http://bogus.com/foo.wrl"), the anchor cannot 
    // resolve the URL reference. This method allows the application 
    // to tell the anchor what it's full URL should be. 
    // getFullURLName returns the fullURL set here, or if not set, returns 
    // the contents of the name field.
    void		setFullURLName(const SbString &url) { fullURL = url; }
    const SbString &	getFullURLName();

    // Return (hidden) children as Group
    SoGroup             *copyChildren() const;
    
    // Request that URL data be fetched, and tell whether the URL data is here
    void		requestURLData() 
			    { if (! kidsRequested) requestChildrenFromURL(); }
    SbBool		isURLDataRequested() const { return kidsRequested; }
    SbBool		isURLDataHere() const { return kidsAreHere; }
    void		cancelURLDataRequest() 
			    { if (!kidsAreHere) kidsRequested = FALSE; }

    // Set/get the child data the inline should display. Application should call
    // this after it has fetched data for the inline node.
    void		setChildData(SoNode *urlData);
    SoNode *		getChildData() const;

    // Allow the viewer to fetch URLs when needed.
    static void setFetchURLCallBack(SoWWWInlineFetchURLCB *f, void *userData);

    // Allow the user to specify how bounding boxes are displayed
    static void setBoundingBoxVisibility(BboxVisibility b) { bboxVisibility = b; } 
    static BboxVisibility getBoundingBoxVisibility() { return bboxVisibility; }

    // Allow the user to specify the bounding box color
    static void setBoundingBoxColor(SbColor &c) { bboxColor = c; }
    static const SbColor &getBoundingBoxColor() { return bboxColor; }


  SoEXTENDER public:
    // Traversal methods for all the actions:
    virtual void	doAction(SoAction *action);
    virtual void	doActionOnKidsOrBox(SoAction *action);
    virtual void	callback(SoCallbackAction *action);
    virtual void	GLRender(SoGLRenderAction *action);
    virtual void	getBoundingBox(SoGetBoundingBoxAction *action);
    virtual void	getMatrix(SoGetMatrixAction *action);
    virtual void	handleEvent(SoHandleEventAction *action);
    virtual void	search(SoSearchAction *action);
    virtual void	pick(SoPickAction *action);

  SoINTERNAL public:
    static void		initClass();

    // Returns pointer to children, or NULL if none
    virtual SoChildList *getChildren() const;

  protected:
    virtual ~SoWWWInline();

    virtual void        addBoundingBoxChild(SbVec3f center, SbVec3f size);

    // Reads into instance of SoWWWInline. Returns FALSE on error.
    virtual SbBool	readInstance(SoInput *in, unsigned short flags);

    // Copies the child data as well as the rest of the node (if
    // the child data has been set)
    virtual void        copyContents(const SoFieldContainer *fromFC,
				     SbBool copyConnections);

  private:
    void		requestChildrenFromURL();

    SoChildList		*children;
    SbBool		kidsRequested;
    SbBool		kidsAreHere;
    SbString		fullURL;

    static SbColor            bboxColor;
    static BboxVisibility     bboxVisibility;

    // Static methods
    static SoWWWInlineFetchURLCB	*fetchURLcb;
    static void				*fetchURLdata;
};

#endif /* _SO_WWWINLINE_ */

