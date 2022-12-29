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
 |   $Revision: 2.12 $
 |
 |   Description:
 |	Defines the SoFieldContainer class, which is the base class of
 |	all classes that contain fields (engines and nodes)
 |
 |   Classes:
 |	SoFieldContainer
 |
 |   Author(s)		: Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_FIELD_CONTAINER_
#define  _SO_FIELD_CONTAINER_

#include <Inventor/misc/SoBase.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoFieldContainer
//
//  Base class for engines and nodes.  This takes care of keeping
//  track of the fields in a node, or the input fields of an engine;
//  reading them, writing them, copying them, etc.
//
//////////////////////////////////////////////////////////////////////////////

class SbDict;
class SoFieldData;
class SoFieldList;

class SoFieldContainer : public SoBase {

  public:

    // Returns type identifier for SoFieldContainer class
    static SoType	getClassTypeId()	{ return classTypeId; }

    // Sets all fields to default values
    void		setToDefaults();

    // Returns TRUE if all fields have their default values (even if
    // the isDefault() flags are not all set)
    SbBool		hasDefaultValues() const;

    // Returns TRUE if the field values match those of the passed
    // instance, which is assumed to be of the same type as this
    SbBool		fieldsAreEqual(const SoFieldContainer *fc) const;

    // Copies field values from the passed instance, which is assumed
    // to be of the same type as this. If the copyConnections flag is
    // TRUE (it is FALSE by default), any connections to (but not
    // from) fields of the instance are copied, as well.
    void		copyFieldValues(const SoFieldContainer *fc,
					SbBool copyConnections = FALSE);

    // Set one or more fields of from the Inventor data file format
    // information in the fieldData string.  Returns TRUE if successful,
    // FALSE otherwise
    SbBool		set(const char *fieldDataString)
	{ return set(fieldDataString, NULL); }

    // Stores field data (in the same format expected by the set()
    // method) in the given SbString
    void		get(SbString &fieldDataString)
	{ get(fieldDataString, NULL); }

    // Returns a list of fields in this node/engine.  This is virtual
    // so private fields can be hidden.  Use getFieldName to get the
    // names of the fields, and use SoField::getType() to figure out
    // their types.  The number of fields added to the list is
    // returned. 
    virtual int		getFields(SoFieldList &list) const;

    // Returns a pointer to the field with the given name. If no such
    // field exists, NULL is returned.
    virtual SoField *	getField(const SbName &fieldName) const;

    // Returns (in fieldName) the name of the field pointed to.
    // Returns FALSE if the field is not contained within the field
    // container instance.
    SbBool		getFieldName(const SoField *field,
				     SbName &fieldName) const;

    // Indicates whether notification will propagate as the result of
    // setting the value of any of the contained fields. This is on by
    // default. Turning this off should be done with caution, since it
    // may prevent data sensors from being triggered.
    SbBool		enableNotify(SbBool flag)	// returns old value
	{ SbBool e = notifyEnabled; notifyEnabled = flag; return e; }
    SbBool		isNotifyEnabled() const	   { return notifyEnabled; }

  SoINTERNAL public:
    // Setup type information
    static void		initClass();

    // Versions of set() and get() that take SoInput or SoOutput from
    // which to inherit reference dictionary.
    SbBool		set(const char *fieldDataString, SoInput *dictIn);
    void		get(SbString &fieldDataString, SoOutput *dictOut);

    // Propagates modification notification through an instance.
    virtual void	notify(SoNotList *);

    // Adds a reference to the instance when writing. isFromField
    // indicates whether the reference is from a field-to-field
    // connection.
    virtual void	addWriteReference(SoOutput *out,
					  SbBool isFromField = FALSE);

    // Writes instance to SoOutput. (Used only for last stage of writing)
    virtual void	writeInstance(SoOutput *out);

    // Returns whether or not instance is considered 'built-in' to the
    // library.  Used during writing.
    SbBool		getIsBuiltIn() const { return isBuiltIn; }

    // Returns an SoFieldData structure for the node. Objects with no
    // fields should return NULL, which is what the default method does.
    virtual const SoFieldData *	getFieldData() const;

    ////////////////////////////////////////////
    //
    // During a copy operation, copies of nodes and engines are
    // stored in a dictionary, keyed by the original node or engine
    // pointer, so that copies can be re-used. These methods
    // operate on that dictionary.

    // Initializes a new copy dictionary
    static void			initCopyDict();

    // Adds an instance to the dictionary
    static void			addCopy(const SoFieldContainer *orig,
					const SoFieldContainer *copy);

    // If a copy of the given instance is in the dictionary, this
    // returns it. Otherwise, it returns NULL. The copy is not changed
    // in any way.
    static SoFieldContainer *	checkCopy(const SoFieldContainer *orig);

    // If a copy of the given instance is not in the dictionary, this
    // returns NULL. Otherwise, this copies the contents of the
    // original into the copy (if not already done) and returns a
    // pointer to the copy.
    static SoFieldContainer *	findCopy(const SoFieldContainer *orig,
					 SbBool copyConnections);

    // Cleans up the dictionary when done. 
    static void			copyDone();

    //
    ////////////////////////////////////////////

    // Copies the contents of the given node into this instance. The
    // default implementation copies just field values and the name.
    virtual void		copyContents(const SoFieldContainer *fromFC,
					     SbBool copyConnections);

    // During a copy operation, this copies an instance that is
    // encountered through a field connection. The default
    // implementation just returns the original pointer - no copy is
    // done. Subclasses such as nodes and engines handle this
    // differently.
    virtual SoFieldContainer *	copyThroughConnection() const;

  protected:

    // Is the subclass a built-in Inventor subclass or an extender subclass?
    // This is used to determine whether to read/write field type information.
    SbBool		isBuiltIn;

    SoFieldContainer();
    ~SoFieldContainer();

    // Reads stuff into instance. Returns FALSE on error
    virtual SbBool	readInstance(SoInput *in, unsigned short flags);

  private:
    static SoType	classTypeId;
    SbBool		notifyEnabled;	// Whether notification is enabled

    // This holds a list of SbDict instances used during copy
    // operations. It is a list to allow recursive copying.
    static SbPList	*copyDictList;

    // And this callback is used to unref() all instances in the
    // copyDict when copyDone() is called
    static void		unrefCopy(unsigned long key, void *instPtr);

    // These are used by SoFieldContainer::get() to hold
    // the returned field string
    static char		*fieldBuf;
    static int		fieldBufSize;

    // This is used to reallocate the string buffer used by
    // SoFieldContainer::get()
    static void *	reallocFieldBuf(void *ptr, size_t newSize);
};

#endif  /* _SO_FIELD_CONTAINER_ */
