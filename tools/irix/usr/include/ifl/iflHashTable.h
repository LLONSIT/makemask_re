#if 0 

    Copyright (c) 1991 SGI   All Rights Reserved
    THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF SGI
    The copyright notice above does not evidence any
    actual or intended publication of such source code,
    and is an unpublished work by Silicon Graphics, Inc.
    This material contains CONFIDENTIAL INFORMATION that
    is the property of Silicon Graphics, Inc. Any use,
    duplication or disclosure not specifically authorized
    by Silicon Graphics is strictly prohibited.
    
    RESTRICTED RIGHTS LEGEND:
    
    Use, duplication or disclosure by the Government is
    subject to restrictions as set forth in subdivision
    (c)(1)(ii) of the Rights in Technical Data and Computer
    Software clause at DFARS 52.227-7013, and/or in similar
    or successor clauses in the FAR, DOD or NASA FAR
    Supplement.  Unpublished- rights reserved under the
    Copyright Laws of the United States.  Contractor is
    SILICON GRAPHICS, INC., 2011 N. Shoreline Blvd.,
    Mountain View, CA 94039-7311

#endif
/*
    This class implements an abstract hash-based lookup table.
*/
#ifndef _iflHashTable_h_
#define _iflHashTable_h_

const int iflHashMultiplier = 2;
const int iflHashIncrement = 127;
const float iflDefaultHashFullFraction = 0.5;

class iflHashElem {

public:
    unsigned int hashIndex;
};


class iflHashTable {

public:
    // Creating and destroying

    iflHashTable(int maxEntries=0);

    virtual ~iflHashTable();

    // Manipulating

    void clear();				// wipe all entries

    int insert(iflHashElem* elem);		// returns FALSE if table full

    int remove(iflHashElem* elem);		// returns FALSE if no such elem

    // Query

    iflHashElem* find(unsigned int index, const void* key);

    iflHashElem* next(int& index);		// returns next valid entry

    int getNumEntries() const { return count; }
    
    // Tuning

    float getFullFraction() const { return fullFraction; }

    void setFullFraction(const float fraction) { fullFraction = fraction; }

    void clearStats();

    // Performance Statistics

    int lookCount;

    int totalLook;

    int maxLook;

protected:
    // Key matching

    virtual int match(const void* key, const iflHashElem* elem) = 0;

private:
    iflHashElem** table;
    int	size;
    int count;
    float fullFraction;

    unsigned int advance(int idx) const 
	{ return (idx+iflHashIncrement) % size; }
    int locate(iflHashElem* elem);
    int normalize(unsigned int index) const { return index % size; }
    int pickSize(int maxEntries) const;
    void grow();

    void upStats(int count);
};
#endif
