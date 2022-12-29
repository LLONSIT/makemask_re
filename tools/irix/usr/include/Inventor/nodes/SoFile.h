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
 |	This file defines the SoFile node class.
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_FILE_
#define  _SO_FILE_

#include <Inventor/misc/SoChildList.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFString.h>

class SoSensor;
class SoFieldSensor;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoFile
//
//  This node represents a subgraph that was read from a
//  named input file. When a file node is written out, just the field
//  containing the name of the file is written. (No children are
//  written out.) When one is encountered during reading, reading
//  continues from the named file, and all children found in the file
//  are added as hidden children of this node.
//
//  Whenever the name of the input file changes
//  (name.setValue("foo.iv")), the old children are removed and the
//  contents of the new file is read in.  The file node remembers
//  what directory the last file was read from, and will read the new
//  file from the same directory after checking the standard list of
//  directories (see the static methods on SoInput), assuming the
//  field isn't set to an absolute path name.
//
//////////////////////////////////////////////////////////////////////////////

class SoGroup;

class SoFile : public SoNode {

    SO_NODE_HEADER(SoFile);

  public:
    // Fields
    SoSFString		name;		// File name

    // Constructor
    SoFile();

    // Method that returns a copy of the File node's children added to
    // a group.
    SoGroup 		*copyChildren() const;

  SoEXTENDER public:
    // Traversal methods for all the actions:
    virtual void	doAction(SoAction *action);
    virtual void	callback(SoCallbackAction *action);
    virtual void	GLRender(SoGLRenderAction *action);
    virtual void	getBoundingBox(SoGetBoundingBoxAction *action);
    virtual void	getMatrix(SoGetMatrixAction *action);
    virtual void	handleEvent(SoHandleEventAction *action);
    virtual void	pick(SoPickAction *action);

  SoINTERNAL public:
    static void		initClass();

    // Returns pointer to children
    virtual SoChildList *getChildren() const;

    // Copies the contents of the given node into this instance.
    // This copies without re-reading the file.
    virtual void	copyContents(const SoFieldContainer *fromFC,
				     SbBool copyConnections);

  protected:
    // Reads stuff into instance of SoFile. Returns FALSE on error.
    virtual SbBool	readInstance(SoInput *in, unsigned short flags);

    virtual ~SoFile();

  private:
    SoChildList		children;

    // These keep the image and filename fields in sync.
    SoFieldSensor *	nameChangedSensor;
    static void		nameChangedCB(void *, SoSensor *);

    SbBool		readOK;		// FALSE on read error.
};

#endif /* _SO_FILE_ */
