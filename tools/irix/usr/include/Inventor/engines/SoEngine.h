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
 |	This file defines the base SoEngine class, and the
 |      SoEngineOutput class.
 |
 |   Author(s)		: Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_ENGINE_
#define  _SO_ENGINE_

#include <Inventor/fields/SoFieldContainer.h>
#include <Inventor/SoLists.h>
#include <Inventor/SbString.h>
#include <Inventor/SoType.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoEngine
//
//  Base SoEngine class (abstract).
//
//////////////////////////////////////////////////////////////////////////////


class SoFieldData;
class SoEngineList;
class SoEngineOutput;
class SoEngineOutputList;
class SoEngineOutputData;
class SoField;
class SoOutput;
class SoInput;

class SoEngine : public SoFieldContainer {

  public:

    // Returns type identifier for SoEngine class
    static SoType	getClassTypeId() { return classTypeId; }

    // Returns a list of outputs in this engine.  This is virtual
    // so private outputs can be hidden.  Use getOutputName() to get the
    // names of the fields, and use getConnectionType() to figure out
    // their types.  Returns the number of outputs added to the list.
    virtual int		getOutputs(SoEngineOutputList &list) const;

    // Returns a pointer to the engine output with the given name.
    // If no such output exists, NULL is returned.
    SoEngineOutput *	getOutput(const SbName &outputName) const;

    // Returns (in outputName) the name of the output pointed to.
    // Returns FALSE if the output is not contained within the
    // engine instance.
    SbBool		getOutputName(const SoEngineOutput *output,
				     SbName &outputName) const;

    // Creates and returns a copy of the engine. All connections to
    // inputs are copied as is (without copying what's at the other
    // end).
    SoEngine *		copy() const;

    // A engine can be given a name using setName() (which is a
    // method on SoBase).  These methods allow enginess to be looked
    // up by name.
    static SoEngine *	getByName(const SbName &name);
    static int		getByName(const SbName &name, SoEngineList &list);

  protected:

    // User-written evaluation engine.
    virtual void	evaluate() = 0;

  SoINTERNAL public:

    // wrapper for the user's evaluate() engine
    void		evaluateWrapper();

    // Propagates modification notification through an instance.
    virtual void	notify(SoNotList *list);

    // Initializes base engine class
    static void		initClass();

    // Info on outputs:
    virtual const SoEngineOutputData *getOutputData() const = 0;

    // Initialize ALL Inventor engine classes
    static void		initClasses();

    // Writes instance to SoOutput. (Used only for last stage of writing)
    virtual void	writeInstance(SoOutput *out);

    // Copies an instance that is encountered through a field connection
    virtual SoFieldContainer *	copyThroughConnection() const;

    // Recursive procedure that determines if this engine should be
    // copied during a copy operation, or just referenced as is
    SbBool		shouldCopy() const;

    // A very annoying double notification occurs with engines
    // that enable their outputs during inputChanged; this flag
    // prevents that:
    SbBool		isNotifying() const { return notifying; }

  protected:

    // Constructor, destructor
    SoEngine();
    ~SoEngine();

    // Reads stuff into instance. Returns FALSE on error
    virtual SbBool	readInstance(SoInput *in, unsigned short flags);

    // This is called whenever the value of an input is changed. The
    // default method does nothing. Subclasses can override this to
    // detect when a specific field is changed.
    virtual void	inputChanged(SoField *whichField);

    // This is used by the input&output inheritence mechanism, hidden in
    // the SoSubEngine macros
    static const SoFieldData		**getInputDataPtr()  { return NULL; }
    static const SoEngineOutputData	**getOutputDataPtr() { return NULL; }

    // Write output type information for engines that are not built-in.
    void		writeOutputTypes(SoOutput *out);

  private:
    static SoType	classTypeId;		// Type identifier

    SbBool		needsEvaluation;	// Dirty bit
    SbBool		notifying;
friend class SoEngineOutput;
};

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoEngineOutput
//
//  Engine outputs.  They are lists of fields to be written into,
//  and a pointer back to the containing engine.
//
//////////////////////////////////////////////////////////////////////////////

class SoEngineOutput {

  public:
    // type of field this output can connect to
    SoType		getConnectionType() const;

    // Returns the number of fields this output is writing to, and
    // adds pointers to those fields to the given list:
    int			getForwardConnections(SoFieldList &list) const;

    // Enables or disables all connections from this output. If the
    // connections are disabled, notification will not propagate
    // through them and values will not be output along them. The
    // default state is enabled.
    void		enable(SbBool flag);
    SbBool		isEnabled() const	{ return enabled; }

    // Returns containing engine
    SoEngine *		getContainer() const		{ return container; }

  SoINTERNAL public:
    SoEngineOutput();

    virtual ~SoEngineOutput();

    void		setContainer(SoEngine *eng)	{ container = eng; }

    // Adds/removes connection to field
    void		addConnection(SoField *);
    void		removeConnection(SoField *);

    // Number of connections this output currently has
    int			getNumConnections() const
	{ return connections.getLength(); }

    // Returns the fields this output is writing into
    SoField *		operator[](int i) const
	{ return connections.get(i); }

    // Before evaluating (which is done with the regular field API),
    // we must disable notification on all the fields we're about to
    // write into.  After evaluating, the bits are restored:
    void		prepareToWrite() const;
    void		doneWriting() const;

  private:
    SbBool		enabled;
    SoFieldList		connections;
    SoEngine		*container;
};

#endif /* _SO_ENGINE_ */

