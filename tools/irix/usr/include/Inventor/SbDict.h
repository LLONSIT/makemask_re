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
 |   $Revision: 2.2 $
 |
 |   Description:
 |	This file defines dictionaries. A dictionary maps some sort of
 |	unique key to a data pointer. Keys are unsigned long integers.
 |
 |   Classes:
 |	SbDictEntry, SbDict
 |
 |   Author(s)		: Paul S. Strauss, Nick Thompson
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */


#ifndef _SB_DICT_
#define _SB_DICT_

#include <Inventor/SbBasic.h>
#include <Inventor/SbString.h>
#include <Inventor/SbPList.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbDictEntry (internal to SB)
//
//  A dictionary is stored as a collection of entries, each of which
//  is an SbDictEntry. It contains the key and value for the entry and
//  a link to create lists of entries.
//
//////////////////////////////////////////////////////////////////////////////

SoINTERNAL class SbDictEntry {
  private:
    unsigned long		key;
    void *		value;

    SbDictEntry *	next;

    // Constructor
    SbDictEntry(unsigned long k, void *v)	{ key = k; value = v; };

friend class SbDict;
};

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbDict
//
//  This is a dictionary mapping (unsigned long) integer keys to (void *) data
//  pointers.
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class SbDict {
  public:

    // Constructor
    SbDict( int entries = 251 );

    // Destructor
    ~SbDict();

    // Calls given routine (passing value) for each entry in dictionary.
    //  The order of entries is not guaranteed to mean anything.
    void	applyToAll(void (*rtn)(unsigned long key, void *value) );

    // Calls given routine (passing value,data) for each entry in dictionary.
    //  The order of entries is not guaranteed to mean anything.
    void	applyToAll(void (*rtn)(unsigned long key, void *value, void *data), 
			   void *data );

    // Removes all entries from dictionary.
    void	clear();

    // Enters a key,value pair into the dictionary. Overwrites entry and
    //  returns FALSE if key already exists.
    SbBool	enter(unsigned long key, void *value);

    // Finds entry with given key, setting value to point to value.
    //  Returns FALSE if no such entry.
    SbBool	find(unsigned long key, void *&value) const;

    // Makes two SbPLists, one for keys and the other for values.
    //  The order of entries is not guaranteed to mean anything.
    void	makePList(SbPList &keys, SbPList &values);

    // Removes the entry with the given key. Returns FALSE if no such entry.
    SbBool	remove(unsigned long key);

  private:
    // Entries are stored as an external hash table of SbDictEntry instances.
    int			tableSize;			// Entries in table
    SbDictEntry *	*buckets;			// Hash table

    SbDictEntry *&	findEntry(unsigned long key) const;
    static void		addEntryToPLists(unsigned long key, void *value, void *data);
};

#endif /* _SB_DICT_ */
