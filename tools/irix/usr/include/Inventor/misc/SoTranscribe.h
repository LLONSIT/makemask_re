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
 |	This file contains definitions of the SoTranSender and SoTranReceiver
 |	classes used for transcribing Inventor data. Transcribing is the
 |	process of packaging changes to a database and sending them over a
 |	"wire" to another database.
 |
 |   Classes:
 |	SoTranSender, SoTranReceiver
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_TRANSCRIBE_
#define  _SO_TRANSCRIBE_

#include <Inventor/misc/SoBasic.h>
#include <Inventor/SbString.h>
#include <Inventor/SbDict.h>

class SoGroup;
class SoInput;
class SoNode;
class SoOutput;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTranSender
//
// This stores database changes that are to be transcribed. The
// changes are written to an SoOutput instance allocated and managed
// by the caller.
//
// These database change routines are supported:
//
//   INSERT node [parent n]
//	Creates and adds a node to other database. With 1 argument,
//	the node is added as the last child of the root of the
//	database. With 3 arguments, the node is added as the nth
//	child of the given parent. (The parent may be NULL to
//	indicate the root.) Note that if the inserted node is already
//	in the graph, a link is made from the parent to the existing
//	version of the node. (Therefore, if the new node is different
//	from the old one, any changes are lost.)
//
//   REMOVE parent n
//	Removes nth child from the given parent node. (The parent may
//	be NULL to indicate the root.)
//
//   REPLACE parent n newNode
//	This is exactly equivalent to "REMOVE parent n" followed by
//	"INSERT newNode parent n".
//
//   MODIFY node
//	Updates the field data for the given node to the new
//	contents. Note that this changes only field data; children of
//	groups are not affected, nor is any non-field instance data.
//
//////////////////////////////////////////////////////////////////////////////

class SoTranSender {
  public:

    // Constructor: takes pointer to SoOutput instance
    SoTranSender(SoOutput *output);

    // Destructor
    ~SoTranSender()				{}

    // Returns pointer to SoOutput
    SoOutput *		getOutput() const	{ return out; }

    // Database change routines
    void		insert(SoNode *node);
    void		insert(SoNode *node, SoNode *parent, int n);
    void		remove(SoNode *parent, int n);
    void		replace(SoNode *parent, int n, SoNode *newNode);
    void		modify(SoNode *node);

    // This is called to make sure the data is ready to send
    void		prepareToSend();

  private:
    SoOutput		*out;

    // Adding items to send
    void		addBytes(const void *bytes, size_t nBytes);
    void		addCommand(int command);
    void		addInt(int n);
    void		addNode(SoNode *node, SbBool addNames = TRUE);
    void		addNodeNames(const SoNode *root);
    void		addNodeRef(const SoNode *node);
    void		addString(const char *cmdString);

friend class SoTranReceiver;
};

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTranReceiver
//
// An SoTranReceiver is used on the receiving end to interpret the
// data packaged up by an SoTranSender. It is given a root node that
// is the default place to add incoming nodes. The input for the
// receiver comes from an SoInput.
//
//////////////////////////////////////////////////////////////////////////////

class SoTranReceiver {

  public:

    // Constructor takes default root node
    SoTranReceiver(SoGroup *rootNode);

    // Destructor
    ~SoTranReceiver();

    // Interprets data from SoInput
    SbBool	interpret(SoInput *in);

  private:
    SoGroup	*root;
    SbDict	nameToEntryDict;	// Maps node keyname to SoTranDictEntry
    SbDict	nodeToNameDict;		// Maps node pointer to node keyname

    // Interprets one database change command (with given code) from stream.
    // Sets done to TRUE if end command was found. Returns T/F error status.
    SbBool	interpretCommand(int commandCode, SoInput *in, SbBool &done);

    // Gets a node and node names from the input
    SbBool	getNodeAndNames(SoInput *in, SoNode *&node);

    // Gets node from input
    SbBool	getNode(SoInput *in, SoNode *&root);

    // Recursively gets node names and sets up dictionaries.
    SbBool	getNodeNames(SoInput *in, SoNode *root,
			     SbBool lookForNode, SoNode *&oldRoot);

    // Gets reference to a node, looks it up in dictionary, returns
    // node pointer.
    SbBool	getNodeReference(SoInput *in, SoNode *&node);

    // Removes reference to node in dictionaries, recursively.
    void	removeNodeReferences(SoNode *node);

    // Adds an entry to the dictionaries
    void	addEntry(SoNode *node, SbName &name);

    // Deletes (frees up) an entry from the nodeDict
    static void	deleteDictEntry(unsigned long key, void *value);

    // Returns 

};

#endif /* _SO_TRANSCRIBE_ */

